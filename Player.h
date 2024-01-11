//プレイヤーヘッダファイル
#pragma once

//ヘッダファイルのインクルード
#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "BaseCharacter.h"
#include "Easings.h"


#include <cassert>
#include <optional>
#include <math.h>

#define _USE_MATH_DEFINES

class Player:public BaseCharacter
{
	enum class Behavior
	{
		kRoot,	//通常状態
		kAttack,//攻撃状態
	};

public:

	/// <summary>
	/// Player初期化
	/// </summary>
	void Initialize(const std::vector<Model*>& models) override;

	/// <summary>
	/// Player処理
	/// </summary>
	void Update() override;


	/// <summary>
	/// Player描画
	/// </summary>
	void Draw(const ViewProjection& viewProjection) override;

	/// <summary>
	///  ワールド座標を取得
	/// </summary>
	/// <returns></returns>
	Vector3 GetWorldPosition();
	const WorldTransform& GetWorldTransform();

	void SetViewProjection(const ViewProjection* viewProjection) {
		viewProjection_ = viewProjection;
	}

	//浮遊ギミック
	void InitializeFloatingGimmick();	//初期化
	void UpdateFloatingGimmick();	//更新

	void SetParent(const WorldTransform* parent)
	{
		worldTransform_.parent_ = parent;
	}
	//通常鼓動
	void BehaviorRootInitialize();	//初期化

	void BehaviorRootUpdate();		//更新
	
	//攻撃行動
	void BehaviorAttackInitialize();//初期化
											
	void BehaviorAttackUpdate();	//更新

	//振るまい
	Behavior behavior_ = Behavior::kRoot;

private:
	//次の振るまい
	std::optional<Behavior> behaviorRequest_ = std::nullopt;

	//Input
	Input* input_ = nullptr;

	//ワールドトランスフォーム
	WorldTransform worldTransform_;

	enum PlayerNum
	{
		kModeIndexBody,
		kModeIndexHead,
		kModeIndexL_arm,
		kModeIndexR_arm,
		kModelHammer
	};

	WorldTransform worldTransformBody_;
	WorldTransform worldTransformHead_;
	WorldTransform worldTransformL_arm_;
	WorldTransform worldTransformR_arm_;
	WorldTransform worldTransformHammer_;

	//// 3Dモデル
	//Model* model_ = nullptr;

	//3Dモデル
	//  モデル
	Model* modelFighterBody_;
	Model* modelFighterHead_;
	Model* modelFighterL_arm_;
	Model* modelFighterR_arm_;

	

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;

	//カメラビュープロジェクション
	const ViewProjection* viewProjection_ = nullptr;
	
	// 浮遊ギミックの媒介変数
	float floatingParameter_ = 0.0f;

	// 攻撃時間
	float attackTime_ = 0;

	// 攻撃時間Max時間
	const float attackTimeMax_ = 120;

	// フレーム
	float frameEnd_ = 120;
};
