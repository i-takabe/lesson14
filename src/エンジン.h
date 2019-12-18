﻿#pragma once
#include "DxLib.h"

// 前方宣言
namespace エンジン {
	class レンダリングサービス;
	class エンティティサービス;
	class 入力サービス;
	class 弾丸サービス;
	class システムサービス;
}

// クラス宣言
class ゲームエンジン
{
private:
	エンジン::エンティティサービス* エンティティサービス_;
	エンジン::レンダリングサービス* レンダリングサービス_;
	エンジン::入力サービス* 入力サービス_;
	エンジン::弾丸サービス* 弾丸サービス_;
	エンジン::システムサービス* システムサービス_;

	LONGLONG 前フレームのμ時刻_ = 0;

	int 初期化();
	int 更新();
	int 片付け();

public:
	ゲームエンジン();
	~ゲームエンジン();

	int 実行();
};
