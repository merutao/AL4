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
#include "Enemy.h"
#include <Scene.h>

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

	bool GetUpdateFlag() { return updateFlag; }

	// シーンのリセット
	void sceneReset();

	bool isSceneEnd = false;

	bool IsSceneEnd() { return isSceneEnd; }

	SceneType NextScene() { return SceneType::kGameClear; }

	bool GetIsClear() { return isClear; }

	void ClearTime();


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

	//エネミー
	std::unique_ptr<Model> modelEnemyBody_;
	std::unique_ptr<Model> modelEnemyL_arm_;
	std::unique_ptr<Model> modelEnemyR_arm_;

	//ハンマー
	std::unique_ptr<Model> modelHammer_;

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

	//エネミー
	std::unique_ptr<Enemy> enemy_;

	bool updateFlag = true;
	
	bool isClear =true;

	int ClearTimer = 500;

	//フェードイン
	Sprite* fadeSprite_ = nullptr;
	Vector4 fadeColor = {1.0f, 1.0f, 1.0f, 1.0f};

	//フェードアウト
	Sprite* fadeOutSprite_ = nullptr;
	Vector4 fadeOutColor_ = {1.0f, 1.0f, 1.0f, 0.0f};

	float fadeOutCount = 0;
};


