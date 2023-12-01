#include "FollowCamera.h"

FollowCamera::FollowCamera() {} // コンストラクタ

FollowCamera::~FollowCamera() {} // デストラクタ

// 初期化
void FollowCamera::Initialize() 
{
	input_ = Input::GetInstance();
	viewProjection_.Initialize();
}

// 更新
void FollowCamera::Update()
{
	//ゲームパッドの状態を得るための変数
	XINPUT_STATE joyState;

	//ゲームパッドが有効なときのif文
	if (Input::GetInstance()->GetJoystickState(0, joyState))
	{
		//速度
		const float Speed = 0.3f;

		viewProjection_.rotation_.y += (float)joyState.Gamepad.sThumbRX / SHRT_MAX * Speed;
	}

	//追従対象がいれば
	if (target_)
	{
		//追従対象からカメラまでのオフセット
		Vector3 offset = {0.0f, 2.0f, -10.0f};

		Matrix4x4 rotationMatrix;

		rotationMatrix = MakeRotateYmatrix(viewProjection_.rotation_.y);

		offset = Transform(offset, rotationMatrix);

		// 座標をコピーしてオフセット分ずらす
		viewProjection_.translation_ = Add(target_->translation_, offset);

	}
	//ビュー行列の更新
	viewProjection_.UpdateMatrix();
}

