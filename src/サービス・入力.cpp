#include "サービス・入力.h"
#include "DxLib.h"

namespace エンジン {

	void 入力サービス::更新()
	{
		static const unsigned char 表[][2] = {
			{KEY_INPUT_SPACE,	マスク_スタート},
			{KEY_INPUT_ESCAPE,	マスク_キャンセル},
			{KEY_INPUT_Z,		マスク_ショット},
			{KEY_INPUT_X,		マスク_スペシャル},
			{KEY_INPUT_UP,		マスク_上},
			{KEY_INPUT_DOWN,	マスク_下},
			{KEY_INPUT_LEFT,	マスク_左},
			{KEY_INPUT_RIGHT,	マスク_右},
			{0xff, }
		};

		// 前の値を保存
		前フレーム_ = 入力データ_.生;

		// 全キーの状態を補足
		char buf[256];
		GetHitKeyStateAll(buf);

		// 8bitに収める
		unsigned char 生 = 0;
		for (int i = 0; 表[i][0] != 0xff; i++) {
			if (buf[表[i][0]])
			{
				生 |= 表[i][1];
			}
		}
		入力データ_.生 = 生;

		// トリガ情報を生成
		unsigned char 違い = 生 ^ 前フレーム_;
		入力データ_.押し下げ = 違い & 生;
		入力データ_.引き上げ = 違い & 前フレーム_;

		//		printfDx(L"%x %x %x\n", 生_, 押し下げ_, 引き上げ_);
	}

}// namespace エンジン