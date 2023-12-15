#include "GameScene.h"
#include "TextureManager.h"
#include "AxisIndicator.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() 
{ 

}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// スプライト
	sprite_ = Sprite::Create(textureHandle_, {100, 50});

	// テクスチャハンドル
	textureHandle_ = TextureManager::Load("mario.jpg");

	// ワールドトランスフォーム
	worldTransform_.Initialize();
	
	// ビュープロジェクション
	viewProjection_.farZ = 600;
	viewProjection_.Initialize();

	// 3Dモデルの生成
	/*model_ = Model::Create();*/
	model_.reset(Model::Create());
	
	//// サウンドデータハンドル
	//soundDataHandle_ = audio_->LoadWave("fanfare.wav");

	////音声再生
	//audio_->PlayWave(soundDataHandle_);

	// Player

	// 自キャラ生成
	player_ = std::make_unique<Player>();			//自動的にdeleteするため
													//置き換え
							 
	// 自キャラ初期化
	player_->Initialize(model_.get(), textureHandle_); // ↑同じく


	// 軸方向の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	//Skydome

	// 3Dモデル
	modelSkeydome_.reset(Model::CreateFromOBJ("skydome", true));

	modelGround_.reset(Model::CreateFromOBJ("ground", true));

	//生成
	//天球
	skydome_ = std::make_unique<Skydome>();

	//地面
	ground_ = std::make_unique<Ground>();

	//デバックカメラ
	debugCamera_ = new DebugCamera(1280, 720);

	//追従カメラ
	followCamera_ = std::make_unique<FollowCamera>();

	//初期化
	skydome_->Initialize(modelSkeydome_.get());

	ground_->Initialize(modelGround_.get());

	followCamera_->Initialize();

	// セッター呼び出し
	// 自キャラのワールドトランスフォームを追従カメラにセット
	followCamera_->SetTarget(&player_->GetWorldTransform());

		// 自キャラのビュープロジェクションに追従カメラビュープロジェクションをセットする
	// これがないとnullと返される
	player_->SetViewProjection(&followCamera_->GetViewProjection());
}

void GameScene::Update()
{
	//スプライトの今の座標を取得
	Vector2 position = sprite_->GetPosition();

	//座標を{2, 1}移動
	position.x += 2.0f;
	position.y += 1.0f;

	//移動した座標をスプライトに反映
	sprite_->SetPosition(position);

	//Player

	//自キャラ更新
	player_->Update();

	//Skydome
	skydome_->Update();

	//ground
	ground_->Update();

	//DebugCamera
	debugCamera_->Update();

	//追従カメラ
	followCamera_->Update();

	#ifdef _DEBUG
	if (input_->TriggerKey(DIK_1) && isDebugCameraActive_ == 0) {
		isDebugCameraActive_ = 1;
	} else if (input_->TriggerKey(DIK_1) && isDebugCameraActive_ == 1) {
		isDebugCameraActive_ = 0;
	}
#endif

	// カメラの処理
	if (isDebugCameraActive_ == 1) {
		// デバックカメラの更新
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;

		// ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
	} else {
		
		// ビュープロジェクション行列の更新と転送
		viewProjection_.UpdateMatrix();
	}

	

	//ビュープロジェクションの反映
	viewProjection_.matView = followCamera_->GetViewProjection().matView;
	viewProjection_.matProjection = followCamera_->GetViewProjection().matProjection;

	//ビュープロジェクション魚列の転送
	viewProjection_.TransferMatrix();
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// Player

	// 自キャラ更新
	player_->Draw(viewProjection_);

	//Skydome
	skydome_->Draw(viewProjection_);

	//ground
	ground_->Draw(viewProjection_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	sprite_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
