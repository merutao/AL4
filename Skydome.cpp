//ヘッダファイルのインクルード
#include "Skydome.h"
#include <cassert>

//初期化
void Skydome::Initialize(Model* model) 
{ 
	assert(model);
	model_ = model;

	worldTransform_.Initialize();
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.UpdateMatrix();
}

//更新
void Skydome::Update() { worldTransform_.UpdateMatrix(); }

//描画
void Skydome::Draw(const ViewProjection& viewProjection)
{ 
	model_->Draw(worldTransform_, viewProjection);
}
