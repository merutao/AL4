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
	void Initialize(Model* model, uint32_t textureHandle);

	/// <summary>
	/// Player処理
	/// </summary>
	void Update();

	/// <summary>
	/// Player描画
	/// </summary>
	void Draw(const ViewProjection& viewProjection);

private:

	//ワールドトランスフォーム
	WorldTransform worldTransform_;

	// 3Dモデル
	Model* model_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;
};
