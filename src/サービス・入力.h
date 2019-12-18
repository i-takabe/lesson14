#pragma once

namespace エンジン {

	struct 入力データ{
		unsigned char 生 = 0;
		unsigned char 押し下げ = 0;
		unsigned char 引き上げ = 0;
	};

	class 入力サービス {
	public:// 定数宣言
		enum 種類 {
			スタート = 0,
			キャンセル,
			ショット,
			スペシャル,
			上,
			下,
			左,
			右,
		};

		static constexpr unsigned int マスク_スタート	= (1 << スタート);
		static constexpr unsigned int マスク_キャンセル = (1 << キャンセル);
		static constexpr unsigned int マスク_ショット	= (1 << ショット);
		static constexpr unsigned int マスク_スペシャル = (1 << スペシャル);
		static constexpr unsigned int マスク_上			= (1 << 上);
		static constexpr unsigned int マスク_下			= (1 << 下);
		static constexpr unsigned int マスク_左			= (1 << 左);
		static constexpr unsigned int マスク_右			= (1 << 右);

	private:
		unsigned char 前フレーム_ = 0;
		入力データ 入力データ_;
	public:
		入力サービス() {}
		~入力サービス() {}

		void 更新();

		inline const 入力データ &データ取得() { return 入力データ_; }
	};

}// namespace エンジン