#include "stdafx.h"
#include "system/system.h"
#include "Game.h"

#include <algorithm>


///////////////////////////////////////////////////////////////////
//クラスのインスタンスをグローバルな領域に置く場合は
//動的確保をしたほうが良い。
//なぜか？
//  ->アプリケーションが起動したときにコンストラクタが呼ばれるから。
//    ->なんの問題がある？
//      ->エンジンの初期化の前にコンストラクタが呼ばれると困る！
///////////////////////////////////////////////////////////////////

Game* g_game = nullptr;


///////////////////////////////////////////////////////////////////
//ゲームの更新処理。
//座標の更新とかの処理はここで呼び出すとよいかも？
///////////////////////////////////////////////////////////////////
void UpdateGame()
{
	//ゲームパッドの更新。	
	for (auto& pad : g_pad) {
		pad.Update();
	}
	//物理エンジンの更新。
	g_physics.Update();
	//ゲームの更新。
	g_game->Update();
}
///////////////////////////////////////////////////////////////////
// ゲームの描画処理。
// 描画と更新は分けてやるほうが良いかも？
///////////////////////////////////////////////////////////////////
void RenderGame()
{
	//描画開始。
	g_graphicsEngine->BegineRender();

	//ゲームの描画。
	g_game->Draw();

	//描画終了。
	g_graphicsEngine->EndRender();
}

///////////////////////////////////////////////////////////////////
// ゲームの終了処理。
///////////////////////////////////////////////////////////////////
void TermnateGame()
{
	
	
}
///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームエンジンの初期化。
	InitGameEngine(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");
	//ゲームの初期化。
	g_game = new Game;
	
	//ゲームループ。
	while (DispatchWindowMessage() == true)
	{
		//ゲームの更新。
		UpdateGame();
		//ゲームの描画処理。
		RenderGame();
	}
	//ゲームの終了処理
	TermnateGame();
}