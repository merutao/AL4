#pragma once
// ヘッダファイルのインクルード
#include "BaseCharacter.h"
#include "ImGuiManager.h"


class Enemy : public BaseCharacter
{
public:

	void Initialize(const std::vector<Model*>& models) override;	// 初期化
	void Update() override;											// 更新
	void Draw(const ViewProjection& viewProjection) override;       // 描画

	void SetViewProjection(const ViewProjection* viewProjection) 
	{
		viewProjection_ = viewProjection;
	}

	//ワールド座標系
	const WorldTransform& GetWorldTransform();

private:

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;

	// カメラビュープロジェクション
	const ViewProjection* viewProjection_ = nullptr;

	WorldTransform worldTransformBody_;
	WorldTransform worldTransformL_arm_;
	WorldTransform worldTransformR_arm_;

	enum EnemyNum 
	{
		kModeIndexBody,
		kModeIndexL_arm,
		kModeIndexR_arm,
	};
};
