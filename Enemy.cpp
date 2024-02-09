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


	////ImGui
	//ImGui::Begin("Enemy");
	//float Body[3] = {
	//    worldTransformBody_.translation_.x, worldTransformBody_.translation_.y,
	//    worldTransformBody_.translation_.z};

	//float ArmL[3] = {
	//    worldTransformL_arm_.translation_.x, worldTransformL_arm_.translation_.y,
	//    worldTransformL_arm_.translation_.z};

	//float ArmR[3] = {
	//    worldTransformR_arm_.translation_.x, worldTransformR_arm_.translation_.y,
	//    worldTransformR_arm_.translation_.z};

	//ImGui::SliderFloat3("Head Translation", Body, -30.0f, 30.0f);
	//ImGui::SliderFloat3("ArmL Translation", ArmL, -10, 10);
	//ImGui::SliderFloat3("ArmR Translation", ArmR, -30, 30);

	//worldTransformBody_.translation_.x = Body[0];
	//worldTransformBody_.translation_.y = Body[1];
	//worldTransformBody_.translation_.z = Body[2];

	//worldTransformL_arm_.translation_.x = ArmL[0];
	//worldTransformL_arm_.translation_.y = ArmL[1];
	//worldTransformL_arm_.translation_.z = ArmL[2];

	//worldTransformR_arm_.translation_.x = ArmR[0];
	//worldTransformR_arm_.translation_.y = ArmR[1];
	//worldTransformR_arm_.translation_.z = ArmR[2];

	//ImGui::End();

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

