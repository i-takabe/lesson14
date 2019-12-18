// メモリリークチェックコード
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
// メモリリークチェックコード

#include <windows.h>
#include "エンジン.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// メモリリークチェックコード
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// メモリリークチェックコード

	ゲームエンジン *エンジン= new ゲームエンジン();

	if (!エンジン) return -1;// メモリ確保に失敗

	エンジン->実行();

	delete エンジン;

	return 0;				// ソフトの終了 
}