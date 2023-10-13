#include "Player.h"

//Player初期化
void Player::Initialize(Model* model, uint32_t textureHandle)
{
	// NULLポインタチェック
	assert(model);
	
	// 3Dモデル
	model_ = model;

	// テクスチャハンドル
	textureHandle_ = textureHandle;

	// ワールドトランスフォーム
	worldTransform_.Initialize();
}

//Player処理
void Player::Update()
{
	//行列を定数バッファに転送
	worldTransform_.TransferMatrix();
}

// Player描画
void Player::Draw(const ViewProjection& viewProjection)
{ 
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
