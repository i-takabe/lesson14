﻿#include "共通.h"
#include "サービス・入力.h"
#include "エンティティ.h"

namespace エンジン
{

	/////////////////////////////////////////////////////
	// スプライトコンポーネント
	/////////////////////////////////////////////////////

	void スプライトコンポーネント::描画()
	{
		float2 位置 = 親_.位置取得();
		int x = static_cast<int>(位置.x + 0.5);
		int y = static_cast<int>(位置.y + 0.5);

		if (位置は中心？_) {
			システムサービス_->レンダラー取得().描画(リソースID_, x, y);
		}
		else {
			システムサービス_->レンダラー取得().描画_左上(リソースID_, x, y);
		}
	}

	/////////////////////////////////////////////////////
	// プレイヤー・エンティティ
	/////////////////////////////////////////////////////

	プレイヤー・エンティティ::プレイヤー・エンティティ()
	{
		const レンダリングサービス::情報& レンダリング情報 = システムサービス_->レンダラー取得().情報取得();
		位置設定(float2(
			レンダリング情報.画面サイズ[0] / 2,
			レンダリング情報.画面サイズ[1] * 4 / 5));

		スプライト_ = dynamic_cast<スプライトコンポーネント*>
			(コンポーネント::コンポーネント生成(L"スプライトコンポーネント", *this));
		スプライト_->リソース設定(RID_IMG_MAT04_01 + 2);
		追加(スプライト_);

		入力_ = dynamic_cast<入力コンポーネント*>(コンポーネント::コンポーネント生成(L"入力コンポーネント", *this));
		追加(入力_);

		弾丸_ = dynamic_cast<弾丸コンポーネント*>(コンポーネント::コンポーネント生成(L"弾丸コンポーネント", *this));
		追加(弾丸_);
	}

	プレイヤー・エンティティ::~プレイヤー・エンティティ()
	{

	}

	void プレイヤー・エンティティ::更新(float 経過時間)
	{
		入力データ 入力 = 入力_->データ取得();

		// 移動
		float2 位置 = 位置取得();
		float 速度 = 100.0 * 経過時間;

		if (入力.生 & 入力サービス::マスク_上) {
			位置.y -= 速度;
		}
		if (入力.生 & 入力サービス::マスク_下) {
			位置.y += 速度;
		}
		if (入力.生 & 入力サービス::マスク_左) {
			位置.x -= 速度;
		}
		if (入力.生 & 入力サービス::マスク_右) {
			位置.x += 速度;
		}
		位置設定(位置);

		// 撃つ
		if (入力.押し下げ & 入力サービス::マスク_ショット) {
			弾丸_->追加(弾丸サービス::種類::自弾, this->位置_, this->位置_);// 速度にダミーで位置を入れた
		}
	}

	void プレイヤー・エンティティ::描画()
	{
		スプライト_->描画();
	}

	/////////////////////////////////////////////////////
	// ザコ１・エンティティ
	/////////////////////////////////////////////////////

	ザコ１・エンティティ::ザコ１・エンティティ()
		:生存時間_(0.0f), 弾を撃つまでの時間_(5.0f), 残弾_(3)
	{
		スプライト_ = dynamic_cast<スプライトコンポーネント*>
			(コンポーネント::コンポーネント生成(L"スプライトコンポーネント", *this));
		スプライト_->リソース設定(RID_ENEMY_S0);
		追加(スプライト_);

		追加(dynamic_cast<弾丸コンポーネント*>(コンポーネント::コンポーネント生成(L"弾丸コンポーネント", *this)));
	}

	void ザコ１・エンティティ::更新(float 経過時間)
	{
		生存時間_ += 経過時間;
		弾を撃つまでの時間_ -= 経過時間;

		float2 位置 = 位置取得();
		// 
		// ここをAIで動かすのだ！！！！
		// 

		if (位置.y > 300.0f) {
			位置.x -= 30.0f * 経過時間;
		}
		else {
			位置.x += 30.0f * 経過時間;
		}

		位置.y += 90.0f * 経過時間;// 全体スクロール
		位置設定(位置);

		// 撃つ
		if (弾を撃つまでの時間_ < 0.0f && 0 < 残弾_) {
			残弾_--;
			弾を撃つまでの時間_ = 3.0;

			プレイヤー・エンティティ* プレイヤー = dynamic_cast<プレイヤー・エンティティ*>
				(システムサービス_->エンティティ取得().最初のエンティティ検索(エンティティサービス::種類::プレイヤー));
			float2 速度 = プレイヤー->位置取得() - 位置_;
			速度 = 速度.正規化() * 100.0f;
			弾丸コンポーネント* 弾丸 = dynamic_cast<弾丸コンポーネント*>(this->コンポーネント検索(L"弾丸コンポーネント"));
			弾丸->追加(弾丸サービス::種類::敵弾, this->位置_, 速度);
		}
	}

	void ザコ１・エンティティ::描画()
	{
		スプライト_->描画();
	}

	/////////////////////////////////////////////////////
	// ステージ１・エンティティ
	/////////////////////////////////////////////////////

	ステージ１・エンティティ::ステージ１・エンティティ()
	{
		状態_ = 0;
		時間_ = 0.0f;
		状態での時間_ = 0.0f;
	}

	void ステージ１・エンティティ::更新(float 経過時間)
	{
		状態での時間_ += 経過時間;
		時間_ += 経過時間;
		if (60.0f * 60.0f * 24.0f < 時間_) 時間_ = 60.0f * 60.0f * 24.0f;// 24時間で時間を止める(安全のため)


		switch (状態_) {
		case 0:// 最初は何も起きない
			if (3.0f < 状態での時間_) {
				状態を進める();
			}
			break;
		case 1:// 定期的に敵グループを出す
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
			if (1.0f < 状態での時間_) {
				// 敵を出す
				エンティティサービス& サービス = システムサービス_->エンティティ取得();
				int 敵ハンドル = サービス.追加(エンティティサービス::種類::ザコ１);
				ザコ１・エンティティ *敵 = dynamic_cast<ザコ１・エンティティ*>(サービス.エンティティ取得(敵ハンドル));

				// 中央上空から出る
				const レンダリングサービス::情報& レンダリング情報 = システムサービス_->レンダラー取得().情報取得();
				敵->位置設定(float2(レンダリング情報.画面サイズ[0] / 2, -100.0f));

				状態を進める();
			}
			break;
		default:
			// 何も起きない....
			break;
		}
	}

	
}// namespace エンジン
