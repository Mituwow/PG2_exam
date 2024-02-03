#pragma once
#include "struct.h"
#include "collision.h"

class Bullet : public Collision{
private://メンバ変数
	Transform pos_;
public:
	Speed speed_;
	int radius_;
	bool isShot_;
	float distance_;
	bool checker_;
public://メンバ関数
	//コンストラクタ
	Bullet();
	//更新処理
	void Update();
	//描画処理
	void Draw();
	//弾と敵の当たり判定
	void Checker(Transform a, int aRadius, Transform b, int bRadius);
	//セッター・ポジション
	void SetPosition(float x,float y);
	//ゲッター・ポジション
	Transform GetPos() { return pos_; };
};