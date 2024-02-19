#include "Enemy.h"

//初期化
void Enemy::Initialize(const std::vector<Model*>& models)
{
	//1.基底クラスの初期化
	BaseCharacter::Initialize(models);
	
	//それぞれのパーツの初期化
	worldTransform_.Initialize();
	worldTransformBody_.Initialize();
	worldTransformL_arm_.Initialize();
	worldTransformR_arm_.Initialize();

	//腕の初期位置
	worldTransformL_arm_.translation_ = {0.8f, 2.0f, 0.0f};
	worldTransformR_arm_.translation_ = {-0.8f, 2.0f, 0.0f};

}

//更新
void Enemy::Update()
{
	//親子付け
	worldTransformBody_.parent_ = &worldTransform_;
	worldTransformL_arm_.parent_ = &worldTransformBody_;
	worldTransformR_arm_.parent_ = &worldTransformBody_;

	//速度
	Vector3 move = {0, 0, 5.0f};

	move = TransformNormal(move, worldTransform_.matWorld_);

	worldTransform_.translation_ = Add(worldTransform_.translation_, move);

	worldTransform_.rotation_.y += 0.3f;

	//体の部位行列を定数バッファに転送
	worldTransform_.UpdateMatrix();
	worldTransformBody_.UpdateMatrix();
	worldTransformL_arm_.UpdateMatrix();
	worldTransformR_arm_.UpdateMatrix();

	BaseCharacter::Update();




}

//描画
void Enemy::Draw(const ViewProjection& viewProjection) 
{
	models_[kModeIndexBody]->Draw(worldTransformBody_, viewProjection);
	models_[kModeIndexL_arm]->Draw(worldTransformL_arm_, viewProjection);
	models_[kModeIndexR_arm]->Draw(worldTransformR_arm_, viewProjection);
}

//ワールド座標系
const WorldTransform& Enemy::GetWorldTransform() {
	// TODO: return ステートメントをここに挿入します
	return worldTransform_;
}

