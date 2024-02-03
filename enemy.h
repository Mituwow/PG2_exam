#pragma once
#include "struct.h"

class Enemy {
private://メンバ変数
	Transform pos_;
	bool isAlive;
public:
	Speed speed_;
	int radius_;
	//静的メンバ変数・敵全体の数を記録
	static int enemyCount;

public://メンバ関数
	//コンストラクタ
	Enemy(float x, float y);
	//更新処理
	void Update(int windowWidth,int windowHeight);
	//描画処理
	void Draw();
	//再出現
	void Respawn(int windowWidth);
	//セッター・非生存
	void SetIsAliveFalse();
	//ゲッター・ポジション
	Transform GetPos() { return pos_; };
	//生存
	bool GetIsAlive() { return isAlive; };
};