#include "Player.h"

//Player初期化
void Player::Initialize(Model* model, uint32_t textureHandle)
{
	// NULLポインタチェック
	assert(model);
	
	// 3Dモデル
	model_ = model;

	//
	input_ = Input::GetInstance();

	// テクスチャハンドル
	textureHandle_ = textureHandle;
	
	// ワールドトランスフォーム
	worldTransform_.Initialize();
}

//Player処理
void Player::Update()
{
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
}

// Player描画
void Player::Draw(const ViewProjection& viewProjection)
{ 
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
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