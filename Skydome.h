//Skydomeのヘッダー
#pragma once

//ヘッダファイルのインクルード
#include "WorldTransform.h"
#include "Model.h"

//クラス
class Skydome
{
public:

	//初期化
	void Initialize(Model* model);
	//更新
	void Update();
	//描画
	void Draw(const ViewProjection& viewProjection);

private:

	// ワールドトランスフォーム
	WorldTransform worldTransform_;

	// 3Dモデル
	Model* model_ = nullptr;
};
