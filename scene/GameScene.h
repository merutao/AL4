//GameSceneヘッダー
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
#include "Player.h"
#include <memory>
#include "Skydome.h"
#include "Ground.h"
#include "DebugCamera.h"
#include "FollowCamera.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	
	//テクスチャハンドル
	uint32_t textureHandle_ = 0;

	//スプライト
	Sprite* sprite_ = nullptr;

	//3Dモデル
	/*Model* model_ = nullptr*/;
	std::unique_ptr<Model> model_;

	//Skydome用
	std::unique_ptr<Model> modelSkeydome_;

	//Ground用
	std::unique_ptr<Model> modelGround_;

	//プレイヤー
	std::unique_ptr<Model> modelFighterBody_;
	std::unique_ptr<Model> modelFighterHead_;
	std::unique_ptr<Model> modelFighterL_arm_;
	std::unique_ptr<Model> modelFighterR_arm_;

	//ワールドトランスフォーム
	WorldTransform worldTransform_;
	
	//ビュープロジェクション
	ViewProjection viewProjection_;

	//デバックカメラ
	//有効
	bool isDebugCameraActive_ = false;

	DebugCamera* debugCamera_ = nullptr;

	////サウンドデータハンドル
	//uint32_t soundDataHandle_ = 0;

	//Plyer
	
	//自キャラ
	//Player* player_ = nullptr;
	std::unique_ptr<Player> player_;	//自動的にdeleteするため
										//置き換え

	//Skydome
	std::unique_ptr<Skydome> skydome_;

	//Ground
	std::unique_ptr<Ground> ground_;

	//追従カメラ
	std::unique_ptr<FollowCamera> followCamera_;
};
