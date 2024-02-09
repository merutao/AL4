#include "Ground.h"
#include <cassert>

void Ground::Initialize(Model* model) 
{
	assert(model);
	model_ = model;

	worldTransform_.Initialize();
	worldTransform_.scale_ = {10.0f, 1.0f, 10.0f};
	worldTransform_.UpdateMatrix();                                                                        
}

void Ground::Update()
{ worldTransform_.UpdateMatrix(); }

void Ground::Draw(const ViewProjection& viewProjection) 
{
	model_->Draw(worldTransform_, viewProjection);
}
