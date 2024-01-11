#pragma once
//ヘッダーファイルのインクルード
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"

class BaseCharacter
{
public:
	virtual void Initialize(const std::vector<Model*>&models);  //初期化
	virtual void Update();		// 更新
	virtual void Draw(const ViewProjection& viewProjection);		//描画

	const WorldTransform& GetWorldTransform() { return worldTransform_; }

	protected:

		//モデルデータの配列
	    std::vector<Model*> models_;
		//ワールド変換データ
	    WorldTransform worldTransform_;
		//ビュープロジェクション
	    ViewProjection viewProjection_;
};