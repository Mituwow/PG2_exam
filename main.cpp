#include <Novice.h>
#include "player.h"
#include "enemy.h"
#include "collision.h"

int Enemy::enemyCount;

const char kWindowTitle[] = "GC1B_12_ハラサワミツタカ";
const int kWindowWidth = 1280;
const int kWindowHeight = 720;

const int kEnemyNum = 10;

enum Scene {
	TITLE,
	PLAY,
	CLEAR,
	OVER
};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	//宣言
	Player* player = new Player();
	Enemy* enemy[kEnemyNum];
	for (int i = 0; i < kEnemyNum; i++)
	{
		enemy[i] = new Enemy(float(kWindowWidth + i * 60), float(rand() % 680 + 20));
	}
	int playerHpPosX = 1100;
	int playerHpPosY = 680;
	const int kDamagedTimerLimit = 180;
	int damagedTimer = 0;

	int mainScene = TITLE;

	int titleHandle = Novice::LoadTexture("./images/title.png");
	int clearHandle = Novice::LoadTexture("./images/clear.png");
	int overHandle = Novice::LoadTexture("./images/over.png");

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		switch (mainScene) {

		case TITLE:
			
			for (int i = 0; i < kEnemyNum; i++)
			{
				enemy[i] = new Enemy(float(kWindowWidth + i * 60), float(rand() % 680 + 20));
			}
			player = new Player();
			Enemy::enemyCount = 0;

			if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				mainScene = PLAY;
			}
			break;
		case PLAY:
			if (player->GetIsAlive()) {
				//自機操作
				player->Update(keys, preKeys);
				//敵移動
				for (int i = 0; i < kEnemyNum; i++)
				{
					if (enemy[i]->GetIsAlive()) {
						enemy[i]->Update(kWindowWidth, kWindowHeight);
					}
				}
				//敵被攻撃時
				for (int i = 0; i < kEnemyNum; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						player->bullet_[j]->Checker(
							player->bullet_[j]->GetPos(), player->bullet_[j]->radius_,
							enemy[i]->GetPos(), enemy[i]->radius_);

						if (player->bullet_[j]->checker_ && enemy[i]->GetIsAlive()) {
							enemy[i]->SetIsAliveFalse();
						}
					}
				}
				//プレイヤー被攻撃時
				for (int i = 0; i < kEnemyNum; i++)
				{
					player->Checker(
						player->GetPos(), player->radius_,
						enemy[i]->GetPos(), enemy[i]->radius_);

					if (player->checker_ && !player->isDamaged) {
						player->SetIsAlive();
					}
				}
				if (player->isDamaged) {
					damagedTimer++;
					if (damagedTimer % 2 == 0) {
						player->color_ = 0x0000FF00;
					}
					if (damagedTimer % 2 == 1) {
						player->color_ = 0x0000FFFF;
					}
				}
				if (damagedTimer > kDamagedTimerLimit) {
					player->isDamaged = false;
					damagedTimer = 0;
					player->color_ = BLUE;
				}
				//ゲームクリア
				if (Enemy::enemyCount >= kEnemyNum) {
					mainScene = CLEAR;
				}
			}
			//ゲームオーバー
			if (!player->GetIsAlive()) {
				mainScene = OVER;
			}
			break;
		case CLEAR:
			if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				mainScene = TITLE;
			}
			break;
		case OVER:
			if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				mainScene = TITLE;
			}
			break;
		}
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		switch (mainScene) {

		case TITLE:
			Novice::DrawSprite(0, 0, titleHandle, 1, 1, 0, WHITE);
			break;

		case PLAY:
			Novice::DrawBox(0, 0, kWindowWidth, kWindowHeight, 0, BLACK, kFillModeSolid);
			player->Draw();
			for (int i = 0; i < kEnemyNum; i++)
			{
				if (enemy[i]->GetIsAlive()) {
					enemy[i]->Draw();
				}
			}
			for (int i = 0; i < player->GetHp(); i++)
			{
				Novice::DrawEllipse(playerHpPosX + i * 65, playerHpPosY,
					player->radius_, player->radius_,
					0, BLUE, kFillModeSolid);
			}
			break;

		case CLEAR:
			Novice::DrawSprite(0, 0, clearHandle, 1, 1, 0, WHITE);
			break;

		case OVER:
			Novice::DrawSprite(0, 0, overHandle, 1, 1, 0, WHITE);
			break;
		}

		Novice::ScreenPrintf(10, 10, "%d", Enemy::enemyCount);
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}
	delete player;

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
