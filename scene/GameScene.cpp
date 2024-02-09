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

	

	// 軸方向の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	//Skydome

	// 3Dモデル
	modelSkeydome_.reset(Model::CreateFromOBJ("skydome", true));

	modelGround_.reset(Model::CreateFromOBJ("ground", true));

	modelFighterBody_.reset(Model::CreateFromOBJ("float_Body", true));
	modelFighterHead_.reset(Model::CreateFromOBJ("float_Head", true));
	modelFighterL_arm_.reset(Model::CreateFromOBJ("float_L_arm", true));
	modelFighterR_arm_.reset(Model::CreateFromOBJ("float_R_arm", true));

	//エネミー
	modelEnemyBody_.reset(Model::CreateFromOBJ("needle_Body", true));
	modelEnemyL_arm_.reset(Model::CreateFromOBJ("needle_L_arm", true));
	modelEnemyR_arm_.reset(Model::CreateFromOBJ("needle_R_arm", true));

	//ハンマーモデル
	modelHammer_.reset(Model::CreateFromOBJ("hammer", true));

	// 自キャラモデルまとめ
	//(追加)自キャラにハンマーを持たせる
	std::vector<Model*> playerModels = {
		modelFighterBody_.get(), modelFighterHead_.get(), modelFighterL_arm_.get(),
		modelFighterR_arm_.get(), modelHammer_.get()
	};

	//エネミーまとめ
	std::vector<Model*> enemyModels =
	{
	    modelEnemyBody_.get(), modelEnemyL_arm_.get(), modelEnemyR_arm_.get()
	};


	// フェードイン
	uint32_t fadeTextureHandle = TextureManager::Load("Title.png");
	fadeSprite_ = Sprite::Create(fadeTextureHandle, {0, 0});
	
	//フェードアウト
	uint32_t fadeOutTextureHandle = TextureManager::Load("End.png");
	fadeOutSprite_ = Sprite::Create(fadeOutTextureHandle, {0, 0});


	//生成
	 
	// 自キャラ生成と初期化
	player_ = std::make_unique<Player>();

	player_->Initialize(playerModels); 

	//エネミー生成と初期化
	enemy_ = std::make_unique<Enemy>();

	enemy_->Initialize(enemyModels);

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

	//エネミー更新
	enemy_->Update();

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

	//フェードイン
	fadeColor.w -= 0.005f;
	fadeSprite_->SetColor(fadeColor);


	if (ClearTimer <= 0)
	{
		// フェードアウト
		fadeOutColor_.w += 0.01f;
	}
	fadeOutSprite_->SetColor(fadeOutColor_);
	if (fadeOutColor_.w >= 1.0f)
	{
		fadeOutColor_.w = 1.0f;

		fadeOutCount = 1;
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

	// 自キャラ
	player_->Draw(viewProjection_);

	//エネミー
	enemy_->Draw(viewProjection_);

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


	if (ClearTimer <= 0) {
		// フェードアウト
		fadeOutSprite_->Draw();

	}
	
	// フェードイン
	fadeSprite_->Draw();

	

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::sceneReset()
{ 
	isSceneEnd = false;
	isClear = true;
	ClearTimer = 500;
	Initialize();
	fadeColor = {1.0f, 1.0f, 1.0f, 1.0f};
	fadeOutCount = 0;
	fadeOutColor_ = {1.0f, 1.0f, 1.0f, 0.0f};
}

void GameScene::ClearTime() 
{
	if (isClear == true) {
		ClearTimer--;
		if (fadeOutCount == 1) {
			isClear = false;
			isSceneEnd = true;
			
		}
	}
}
