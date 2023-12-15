#include "Player.h"

//Player初期化
void Player::Initialize(Model* modelBody, Model* modelHead, Model* modelL_arm, Model* modelR_arm) {
	// NULLポインタチェック
	assert(modelBody);
	assert(modelHead);
	assert(modelL_arm);
	assert(modelR_arm);

	// シングルだから
	input_ = Input::GetInstance();

	//引数として受け取ったデータをメンバ変数に記録する
	modelFighterBody_ = modelBody;
	modelFighterHead_ = modelHead;
	modelFighterL_arm_ = modelL_arm;
	modelFighterR_arm_ = modelR_arm;
	
	//// 3Dモデル
	//model_ = model;

	//// テクスチャハンドル
	//textureHandle_ = textureHandle;
	
	// ワールドトランスフォーム
	worldTransform_.Initialize();
	// 自機のworldTransfotm初期化
	worldTransformBody_.Initialize();
	worldTransformHead_.Initialize();
	worldTransformL_arm_.Initialize();
	worldTransformR_arm_.Initialize();

	// 自機の頭・両腕の初期位置
	worldTransformHead_.translation_ = {0.0f, 1.3f, 0.0f};
	worldTransformL_arm_.translation_ = {-0.5f, 1.0f, 0.0f};
	worldTransformR_arm_.translation_ = {0.5f, 1.0f, 0.0f};

	worldTransformL_arm_.rotation_ = {-0.2f, 0.0f, 0.0f};

	InitializeFloatingGimmick();
}

//Player処理
void Player::Update()
{

	UpdateFloatingGimmick();

	//ゲームパッドの取得
	XINPUT_STATE joyState;

	//ゲームパッド移動処理
	if (Input::GetInstance()->GetJoystickState(0, joyState))
	{
		//速度
		const float Speed = 0.4f;

		//移動量計算
		Vector3 move = {
		    (float)joyState.Gamepad.sThumbLX / SHRT_MAX * Speed, // Lスティックの横軸
		    0.0f,
		    (float)joyState.Gamepad.sThumbLY / SHRT_MAX * Speed, // Lスティックの縦軸
		};

		Matrix4x4 rotationXMatrix = MakeRotateXmatrix(viewProjection_->rotation_.x);
		Matrix4x4 rotationYMatrix = MakeRotateYmatrix(viewProjection_->rotation_.y);
		Matrix4x4 rotationZMatrix = MakeRotateZmatrix(viewProjection_->rotation_.z);
		Matrix4x4 rotationXYZMatrix =
		    Multiply(rotationXMatrix, Multiply(rotationYMatrix, rotationZMatrix));

		move = Multiply(Speed, Normalize(move));

		move = Transform(move, rotationXYZMatrix);

		if (move.y != 0 || move.z != 0)
		{
			worldTransform_.rotation_.y = std::atan2(move.x, move.z);
		}

		//移動
		worldTransform_.translation_ = Add(worldTransform_.translation_, move);
	}
	//行列を定数バッファに転送
	/*worldTransform_.TransferMatrix();*/

	worldTransform_.UpdateMatrix();

	// 体の部位を行列を定数バッファに転送
	worldTransformBody_.UpdateMatrix();
	worldTransformHead_.UpdateMatrix();
	worldTransformL_arm_.UpdateMatrix();
	worldTransformR_arm_.UpdateMatrix();
}

// Player描画
void Player::Draw(const ViewProjection& viewProjection)
{ 
	// 3Dモデルを描画
	modelFighterBody_->Draw(worldTransformBody_, viewProjection);
	modelFighterHead_->Draw(worldTransformHead_, viewProjection);
	modelFighterL_arm_->Draw(worldTransformL_arm_, viewProjection);
	modelFighterR_arm_->Draw(worldTransformR_arm_, viewProjection);
}


Vector3 Player::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;

	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

const WorldTransform& Player::GetWorldTransform() {
	// TODO: return ステートメントをここに挿入します
	return worldTransform_;
}

//浮遊ギミック
void Player::InitializeFloatingGimmick()
{
	floatingParameter_ = 0.0f; 
}

void Player::UpdateFloatingGimmick()
{
	// 浮遊移動のサイクルフレーム
	const uint16_t cycle = 30;
	// 1フレームでパラメータ加算値
	const float step = 2.0f * 3.14f / cycle;
	// パラメータを１ステップ分加算
	floatingParameter_ += step;
	// 2πを超えたらθに戻す
	floatingParameter_ = std::fmod(floatingParameter_, 2.0f * 3.14f);
	// 浮遊の振幅＜m＞
	const float floatingAmplitude = 1.0f;
	// 浮遊を座標に反映
	worldTransformBody_.translation_.y = std::sin(floatingParameter_) * floatingAmplitude;
}


