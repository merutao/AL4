#include "GameClear.h"

GameClear::GameClear() {}

GameClear::~GameClear() { delete goalSprite_; }

void GameClear::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	/*audio_ = Audio::GetInstance();*/
	// ゴールのテクスチャ読み込み
	uint32_t goalTexture = TextureManager::Load("End.png");
	// ゴールの生成
	goalSprite_ = Sprite::Create(goalTexture, {0, 0});
	//// ルールテクスチャ
	// uint32_t Luletexture = TextureManager::Load("resources/Lule.png");

	// スプライト生成
	goalSprite_ = Sprite::Create(goalTexture, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});

	// BGM
	/*bgmDataHandle_ = audio_->LoadWave("BGM/BGM.mp3");
	bgmHandle_ = audio_->PlayWave(bgmDataHandle_, false, 0.15f);*/

	// フェードアウト
	uint32_t fadeOutTextureHandle = TextureManager::Load("Title.png");
	fadeOutSprite_ = Sprite::Create(fadeOutTextureHandle, {0, 0});
}

void GameClear::Update() {

	/// ゲームパッドの状態を得る変数
	XINPUT_STATE joyState;

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		if (joyState.Gamepad.wButtons == XINPUT_GAMEPAD_A) {
			Count = 1;
		}
	}
	Sleep(1 * 120);

	if (Count == 1)
	{
		// フェードアウト
		fadeOutColor_.w += 0.1f;
	}

	

	fadeOutSprite_->SetColor(fadeOutColor_);
	if (fadeOutColor_.w >= 1.0f) {
		fadeOutColor_.w = 1.0f;

		fadeOutCount = 1;
	}
	
	if (fadeOutCount == 1) {
		isSceneEnd = true;
	}
	
}

void GameClear::Draw() {
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

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	

	

	goalSprite_->Draw();

	if (Count == 1) {
		// フェードアウト
		fadeOutSprite_->Draw();
	}

	//画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameClear::sceneReset() {
	isSceneEnd = false;
	// BGMの停止
	// audio_->StopWave(bgmHandle_);
	Initialize();
	fadeOutColor_ = {1.0f, 1.0f, 1.0f, 0.0f};
	fadeOutCount = 0;

	Count = 0;
	
}