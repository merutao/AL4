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
#include <cassert>

class Player
{
public:

	/// <summary>
	/// Player初期化
	/// </summary>
	void Initialize(Model* modelBody, Model* modelHead, Model* modelL_arm, Model* modelR_arm);

	/// <summary>
	/// Player処理
	/// </summary>
	void Update();

	/// <summary>
	/// Player描画
	/// </summary>
	void Draw(const ViewProjection& viewProjection);

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

private:
	//Input
	Input* input_ = nullptr;

	//ワールドトランスフォーム
	WorldTransform worldTransform_;

	WorldTransform worldTransformBody_;
	WorldTransform worldTransformHead_;
	WorldTransform worldTransformL_arm_;
	WorldTransform worldTransformR_arm_;

	//// 3Dモデル
	//Model* model_ = nullptr;

	//3Dモデル
	//  モデル
	Model* modelFighterBody_;
	Model* modelFighterHead_;
	Model* modelFighterL_arm_;
	Model* modelFighterR_arm_;

	enum PlayerNum
	{

	};

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;

	//カメラビュープロジェクション
	const ViewProjection* viewProjection_ = nullptr;
	
	// 浮遊ギミックの媒介変数
	float floatingParameter_ = 0.0f;
};
