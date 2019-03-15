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
}

//ドロー
void CObjCloud_Effect::Draw()
{
	//描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	//雲画像用
	float d[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置


	//▼雲(右上)表示
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 500.0f;
	src.m_bottom = 500.0f;

	dst.m_top = -1000.0f + m_Cloud_move;
	dst.m_left = 900.0f - m_Cloud_move;
	dst.m_right = 2200.0f - m_Cloud_move;
	dst.m_bottom = 100.0f + m_Cloud_move;
	Draw::Draw(15, &src, &dst, d, 0.0f);

	//以下の位置になると画面全体が隠れる
	//dst.m_top = 0.0f;
	//dst.m_left = -100.0f;
	//dst.m_right = 1200.0f;
	//dst.m_bottom = 1100.0f;


	//▼雲(左下)表示
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = -500.0f;
	src.m_bottom = -500.0f;

	dst.m_top = 600.0f - m_Cloud_move;
	dst.m_left = -1000.0f + m_Cloud_move;
	dst.m_right = 300.0f + m_Cloud_move;
	dst.m_bottom = 1700.0f - m_Cloud_move;
	Draw::Draw(15, &src, &dst, d, 0.0f);

	//以下の位置になると画面全体が隠れる
	//dst.m_top = -400.0f;
	//dst.m_left = 0.0f;
	//dst.m_right = 1300.0f;
	//dst.m_bottom = 700.0f;
}
