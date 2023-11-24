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


