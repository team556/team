//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"

//使用するネームスペース
using namespace GameL;

//マクロ
//▼雲演出IN か OUT なのかで初期位置が変わる
//INなら 0.0f,OUTなら 1000.0f。
#define INI_CLOUD_POS (m_In_Out_Check == true ? 0.0f : 1000.0f) //雲の初期位置

//コンストラクタ
CObjCloud_Effect::CObjCloud_Effect(bool check)
{
	//作成時に渡された値にて、雲演出IN / OUTを判断する
	m_In_Out_Check = check;
}

//イニシャライズ
void CObjCloud_Effect::Init()
{
	m_Cloud_move = INI_CLOUD_POS;
	m_white_out_a = 0.0f;
	m_white_out_a_vec = 0.0f;
}

//アクション
void CObjCloud_Effect::Action()
{
	//▼雲演出INの処理
	if (m_In_Out_Check == true)
	{
		//雲が画面全体を覆い隠す処理を行う
		if (m_Cloud_move <= 1000.0f)
		{
			m_Cloud_move += 10.0f;
		}
	}

	//▼雲演出OUTの処理
	else 
	{
		//雲を画面外に移動させ、画面を見せる
		if (m_Cloud_move >= 0.0f)
		{
			m_Cloud_move -= 10.0f;
		}
	}

	//▼ホワイトアウト演出の処理(育成画面背景変更時に実行される)
	if (white_out_f == true)
	{
		if (m_white_out_a <= 0.6)			//0.6で切り替えて、ホワイトアウト演出のalpha調整
		{
			m_white_out_a_vec += 0.002f;	//ベクトルに加算
		}
		else
		{
			m_white_out_a_vec -= 0.002f;	//ベクトルに減算
		}

		m_white_out_a += m_white_out_a_vec;	//ベクトルを反映


		//完全にホワイトアウトした時点で実際に施設レベルを1UPさせる
		if (m_white_out_a >= 1.0f)
		{
			//研究所の場合
			if (window_start_manage == Institute && player_level != ((int)((g_Bar_Level + g_Ins_Level) / 2)))
			{
				g_Ins_Level++;
			}
			//兵舎の場合
			else if(window_start_manage == Barracks && player_level != ((int)((g_Bar_Level + g_Ins_Level) / 2)))
			{
				g_Bar_Level++;
			}
		}
		//ホワイトアウト演出処理終了時点(画面が見える)でこの演出処理から抜ける
		else if (m_white_out_a <= 0.0f)
		{
			//次回のホワイトアウト演出の為に以下の変数を初期化しておく
			m_white_out_a = 0.0f;
			m_white_out_a_vec = 0.0f;

			white_out_f = false;//ホワイトアウト演出フラグをOFF
		}
	}
}

//ドロー
void CObjCloud_Effect::Draw()
{
	//描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	//雲画像用
	float d[4] = { 1.0f,1.0f,1.0f,1.0f };
	//ホワイトアウト演出画像用
	float c[4] = { 1.0f,1.0f,1.0f,m_white_out_a };

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置


	//▼雲(右上)表示
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 500.0f;
	src.m_bottom = 500.0f;

	dst.m_top = -1100.0f + m_Cloud_move;
	dst.m_left = 700.0f - m_Cloud_move;
	dst.m_right = 2300.0f - m_Cloud_move;
	dst.m_bottom = 300.0f + m_Cloud_move;
	Draw::Draw(15, &src, &dst, d, 0.0f);

	//以下の位置になると画面全体が隠れる
	//dst.m_top = -100.0f;
	//dst.m_left = -300.0f;
	//dst.m_right = 1300.0f;
	//dst.m_bottom = 1300.0f;


	//▼雲(左下)表示
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = -500.0f;
	src.m_bottom = -500.0f;

	dst.m_top = 400.0f - m_Cloud_move;
	dst.m_left = -1100.0f + m_Cloud_move;
	dst.m_right = 500.0f + m_Cloud_move;
	dst.m_bottom = 1800.0f - m_Cloud_move;
	Draw::Draw(15, &src, &dst, d, 0.0f);

	//以下の位置になると画面全体が隠れる
	//dst.m_top = -600.0f;
	//dst.m_left = -100.0f;
	//dst.m_right = 1500.0f;
	//dst.m_bottom = 800.0f;


	//▼ホワイトアウト演出画像表示
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1200.0f;
	src.m_bottom = 700.0f;

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 1200.0f;
	dst.m_bottom = 700.0f;
	Draw::Draw(19, &src, &dst, c, 0.0f);
}
