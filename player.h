#pragma once
#include "struct.h"
#include "bullet.h"
#include "collision.h"

class Player : public Collision{
private://メンバ変数
	Transform pos_;
	int hp_;
	bool isAlive_;
public :
	Speed speed;
	int radius_;
	Bullet* bullet_[10];
	bool isDamaged;
	unsigned int color_;
public://メンバ関数
	//コンストラクタ
	Player();
	//更新処理
	void Update(char* keys,char* preKeys);
	//描画処理
	void Draw();
	//敵と自機との当たり判定
	void Checker(Transform a, int aRadius, Transform b, int bRadius);
	//セッター・生存
	void SetIsAlive();
	//ゲッター・体力
	int GetHp() { return hp_; };
	//生存
	bool GetIsAlive() { return isAlive_; };
	//ポジション
	Transform GetPos() { return pos_; };
};