#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"
#include <assert.h>
#include <cmath>
#define _USE_MATH_DEFINES

/// <summary>
/// X軸回転行列
/// </summary>
/// <param name="radian"> </param>
/// <returns></returns>
Matrix4x4 MakeRotateXmatrix(float radian);

/// <summary>
/// Y軸回転行列
/// </summary>
/// <param name="radian"></param>
/// <returns></returns>
Matrix4x4 MakeRotateYmatrix(float radian);

/// <summary>
/// Z軸回転行列
/// </summary>
/// <param name="radian"></param>
/// <returns></returns>
Matrix4x4 MakeRotateZmatrix(float radian);

/// <summary>
/// 平行移動
/// </summary>
/// <param name="translate"></param>
/// <returns></returns>
Matrix4x4 MakeTranslateMatrix(Vector3 translate);

/// <summary>
/// 拡大縮小
/// </summary>
/// <param name="scale"></param>
/// <returns></returns>
Matrix4x4 MakeScaleMatrix(const Vector3& scale);

/// <summary>
///
/// </summary>
/// <param name="m1"></param>
/// <param name="m2"></param>
/// <returns></returns>
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

/// <summary>
///
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
Vector3 Multiply(const float& v1, const Vector3& v2);

/// <summary>
/// アフィン変換
/// </summary>
/// <param name="scale"></param>
/// <param name="rot"></param>
/// <param name="translate"></param>
/// <returns></returns>
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rot, const Vector3& translate);

/// <summary>
/// ベクトル変換
/// </summary>
/// <param name="v"></param>
/// <param name="m"></param>
/// <returns></returns>
Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);

/// <summary>
/// 内積
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
float Dot(Vector3 v1, Vector3 v2);

/// <summary>
/// 長さ(ノルム)
/// </summary>
/// <param name="v"></param>
/// <returns></returns>
float Length(Vector3 v);

/// <summary>
/// ベクトルの正規化
/// </summary>
/// <param name="v"></param>
/// <returns></returns>
Vector3 Normalize(Vector3 v);

/// <summary>
///
/// </summary>
/// <param name="m"></param>
/// <returns></returns>
Matrix4x4 Inverse(const Matrix4x4& m);

Vector3 Subtract(Vector3 vector1, Vector3 vector2);

Vector3 Add(const Vector3& v1, const Vector3& v2);

// ビューポート変換行列
Matrix4x4 MakeViewPortMatrix(
    float left, float top, float width, float height, float minDepth, float maxDepth);

// 座標返還
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);
