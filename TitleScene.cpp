#include "TitleScene.h"

TitleScene::TitleScene() {}

TitleScene::~TitleScene() { delete spriteTitle_; }

void TitleScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	/*audio_ = Audio::GetInstance();*/

	// テクスチャ
	uint32_t textureTitle = TextureManager::Load("Title.png");
	uint32_t textureTitle2 = TextureManager::Load("Title2.png");
	uint32_t textureTitle3 = TextureManager::Load("Title3.png");
	//// ルールテクスチャ
	// uint32_t Luletexture = TextureManager::Load("resources/Lule.png");

	// スプライト生成
	spriteTitle_ =
	    Sprite::Create(textureTitle, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	spriteTitle2_ =
	    Sprite::Create(textureTitle2, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	spriteTitle3_ =
	    Sprite::Create(textureTitle3, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});

	// BGM
	/*bgmDataHandle_ = audio_->LoadWave("BGM/BGM.mp3");
	bgmHandle_ = audio_->PlayWave(bgmDataHandle_, false, 0.15f);*/
}

void TitleScene::Update() {

	/// ゲームパッドの状態を得る変数
	XINPUT_STATE joyState;

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		if (joyState.Gamepad.wButtons == XINPUT_GAMEPAD_A) {
			titleCount = 1;
		}
	}
	Sleep(1 * 120);

	if (titleCount == 1)
	{
		titleTimer--;
	}
	if (titleTimer <= 0)
	{
		titleCount = 2;
	}
	if (titleCount == 2) {
		titleTimer2--;
	}
	if (titleTimer2 <= 0) {
		titleCount = 3;
	}
	if (titleCount == 3) {
		titleTimer3--;
	}
	if (titleTimer3 <= 0) {
		titleCount = 4;
	}
	if (titleCount == 4) {
		isSceneEnd = true;
	}
}

void TitleScene::Draw() {
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
	if (titleCount == 0)
	{
		spriteTitle_->Draw();
	}
	if (titleCount == 1) {
		spriteTitle2_->Draw();
	}
	if (titleCount == 2) {
		spriteTitle3_->Draw();
	}
	if (titleCount == 3) {
		spriteTitle2_->Draw();
	}
	if (titleCount == 4) {
		spriteTitle_->Draw();
	}
	

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void TitleScene::sceneReset() {
	isSceneEnd = false;

	titleCount = 0;

	titleTimer = 2;
	titleTimer2 = 15;
	titleTimer3 = 2;
	// BGMの停止
	// audio_->StopWave(bgmHandle_);
}
