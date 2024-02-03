#pragma once
#include "struct.h"
class Collision {
public://メンバ変数
	float distance_;
	bool checker_;
public://メンバ関数
	//距離を測る
	float Distance(float x1, float y1, float x2, float y2);
	//測った距離を基に真偽を求める
	void Checker(Transform a, int aRadius, Transform b, int bRadius);
};