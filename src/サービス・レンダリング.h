#pragma once
#include <windows.h>

#define IMG_MAT04_01 0
#define IMG_MAT04_02 1
#define IMG_MAT04_03 2
#define IMG_MAT04_04 3
#define 画像_枚数 (IMG_MAT04_04+1)

// IMG_MAT04_01
#define RID_IMG_MAT04_01 0
#define RID_MY_SHIP RID_IMG_MAT04_01
#define RID_MY_SHIP_NUM 5
#define RID_INJECTION (RID_MY_SHIP+RID_MY_SHIP_NUM)
#define RID_INJECTION_NUM 4
#define RID_SHOT (RID_INJECTION+RID_INJECTION_NUM)
#define RID_SHOT_NUM 1
#define RID_BULLET (RID_SHOT+RID_SHOT_NUM)
#define RID_BULLET_NUM 1
#define RID_FORMING (RID_BULLET+RID_BULLET_NUM)
#define RID_FORMING_NUM 16
#define RID_BULLET_ANIM (RID_FORMING+RID_FORMING_NUM)
#define RID_BULLET_ANIM_NUM 8
#define RID_EXPLOSION_L (RID_BULLET_ANIM+RID_BULLET_ANIM_NUM)
#define RID_EXPLOSION_L_NUM 6
#define RID_EXPLOSION_M (RID_EXPLOSION_L+RID_EXPLOSION_L_NUM)
#define RID_EXPLOSION_M_NUM 6
#define RID_EXPLOSION_SR (RID_EXPLOSION_M+RID_EXPLOSION_M_NUM)
#define RID_EXPLOSION_SR_NUM 6
#define RID_EXPLOSION_SB (RID_EXPLOSION_SR+RID_EXPLOSION_SR_NUM)
#define RID_EXPLOSION_SB_NUM 6

// IMG_MAT04_02
#define RID_IMG_MAT04_02 (RID_EXPLOSION_SB+RID_EXPLOSION_SB_NUM)

// IMG_MAT04_03
#define RID_IMG_MAT04_03 (RID_IMG_MAT04_02+0)
#define RID_ENEMY_S0 RID_IMG_MAT04_03
#define RID_ENEMY_S0_NUM 2
#define RID_ENEMY_S1 (RID_ENEMY_S0+RID_ENEMY_S0_NUM)
#define RID_ENEMY_S1_NUM 2
#define RID_ENEMY_S2 (RID_ENEMY_S1+RID_ENEMY_S1_NUM)
#define RID_ENEMY_S2_NUM 2
#define RID_ENEMY_S3 (RID_ENEMY_S2+RID_ENEMY_S2_NUM)
#define RID_ENEMY_S3_NUM 2
#define RID_ENEMY_S4 (RID_ENEMY_S3+RID_ENEMY_S3_NUM)
#define RID_ENEMY_S4_NUM 2
#define RID_ENEMY_M0 (RID_ENEMY_S4+RID_ENEMY_S4_NUM)
#define RID_ENEMY_M0_NUM 2
#define RID_ENEMY_M1 (RID_ENEMY_M0+RID_ENEMY_M0_NUM)
#define RID_ENEMY_M1_NUM 2
#define RID_ENEMY_L0 (RID_ENEMY_M1+RID_ENEMY_M1_NUM)
#define RID_ENEMY_L0_NUM 2
#define RID_ENEMY_L1 (RID_ENEMY_L0+RID_ENEMY_L0_NUM)
#define RID_ENEMY_L1_NUM 2
#define RID_ENEMY_BOSS (RID_ENEMY_L1+RID_ENEMY_L1_NUM)
#define RID_ENEMY_BOSS_NUM 2
#define RID_MISSILE (RID_ENEMY_BOSS+RID_ENEMY_BOSS_NUM)
#define RID_MISSILE_NUM 16
#define RID_MISSILE_BREAK (RID_MISSILE+RID_MISSILE_NUM)
#define RID_MISSILE_BREAK_NUM 1

#define RID_個数 (RID_MISSILE_BREAK+RID_MISSILE_BREAK_NUM)

namespace エンジン {
	
	// 前方宣言
	class リソース_ローダー;

	struct UVテーブル {
		int 画像; // 画像
		int u, v; // 左上
		int w, h; // 幅高さ
	};

	class レンダリングサービス {
	public:// 型情報
		struct 情報 {
			int 画面サイズ[2] = {0,0};
		};

	private:
		リソース_ローダー *ローダー;
		情報 情報_ = { {0,0} };
	public:

		レンダリングサービス();
		~レンダリングサービス();

		int 初期化();
		int 片付け();

		const 情報& 情報取得() const { return 情報_; }
		int サイズ取得(unsigned int リソースID, int(&出力先)[2]) const ;

		void 描画_左上(unsigned int リソースID, int x, int y);
		void 描画(unsigned int リソースID, int x, int y);
	};

	class リソース_ローダー
	{
	public:// friend宣言
		friend レンダリングサービス;

	private:
		static UVテーブル uvテーブル_[RID_個数];
		static TCHAR *画像パス_[画像_枚数];

		int ハンドル配列_[画像_枚数];

		void ハンドル初期化();

		static const UVテーブル &UVテーブル(int リソースID) { return uvテーブル_[リソースID]; }
		int ハンドル所得(int 画像) { return ハンドル配列_[画像]; }

	public:
		リソース_ローダー();
		~リソース_ローダー();

		int 初期化();
		int 片付け();
	};

}
