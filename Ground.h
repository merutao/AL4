//地面のヘッダーファイル
#pragma once

// ヘッダファイルのインクルード
#include "Model.h"
#include "WorldTransform.h"

class Ground 
{
public:
	// 初期化
	void Initialize(Model* model);
	// 更新
	void Update();
	// 描画
	void Draw(const ViewProjection& viewProjection);

private:

	// ワールドトランスフォーム
	WorldTransform worldTransform_;

	// 3Dモデル
	Model* model_ = nullptr;
};
