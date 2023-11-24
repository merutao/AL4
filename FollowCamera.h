//FollowCameraのヘッダーファイル
#pragma once

//ヘッダファイルのインクルード
#include "Input.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

/// <summary>
/// 追従カメラ
/// </summary>
class FollowCamera
{
//メンバ関数
public:
	FollowCamera();	//コンストラクタ
	~FollowCamera();//デストラクタ

	void Initialize();	//初期化
	void Update();		//更新

	void SetTarget(const WorldTransform* target) 
	{ 
		target_ = target;
	}

	//ビュープロジェクションの取得
	const ViewProjection& GetViewProjection()
	{ 
		return viewProjection_;
	}

	//プロジェクション行列計算用の
	//メンバ設定関数
	void SetFovAngleY(float value) { viewProjection_.fovAngleY = value; }
	void SetAspectRatio(float value) { viewProjection_.aspectRatio = value; }
	void SetNearZ(float value) { viewProjection_.nearZ = value; }
	void SetFarZ(float value) { viewProjection_.farZ = value; }

private:
	Input* input_ = nullptr;

	//ビュープロジェクション
	ViewProjection viewProjection_;

	//追従対象
	const WorldTransform* target_ = nullptr;
};
