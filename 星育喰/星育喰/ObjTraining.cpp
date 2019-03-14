//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"		//使用されているのはマウスデバッグの部分のみ
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"

//使用するネームスペース
using namespace GameL;

//マクロ
#define INI_ALPHA (0.0f) //透過度(アルファ値)の初期値
#define INI_COLOR (1.0f) //全カラー明度の初期値

//イニシャライズ
void CObjTraining::Init()
{
	m_Cloud_move = 0.0f;

	m_mou_x = 0.0f;
	m_mou_y = 0.0f;
	m_mou_r = false;
	m_mou_l = false;

	m_key_f = false;
}

//アクション
void CObjTraining::Action()
{
	//マウスの位置を取得
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//マウスのボタンの状態
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	
}

//ドロー
void CObjTraining::Draw()
{
	//描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	////敵惑星(背景)用
	//float p[4] = { 1.0f,1.0f,1.0f,m_alpha };

	////育アイコン用
	//float t[4] = { m_Tra_color,m_Tra_color,m_Tra_color,m_alpha };

	////喰アイコン用
	//float e[4] = { m_Eat_color,m_Eat_color,m_Eat_color,m_alpha };

	//それ以外の画像用
	float d[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置


	//▼背景(地面)表示
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 238.0f;
	src.m_bottom = 238.0f;

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 1200.0f;
	dst.m_bottom = 700.0f;
	Draw::Draw(0, &src, &dst, d, 0.0f);


	//▼プレイヤー惑星表示
	//src.m_top = 0.0f;
	//src.m_left = 0.0f;
	//src.m_right = 300.0f;
	//src.m_bottom = 168.0f;

	//dst.m_top = 150.0f + m_Pvy - m_size;
	//dst.m_left = 250.0f + m_Pvx - m_size;
	//dst.m_right = 950.0f + m_Pvx + m_size;
	//dst.m_bottom = 550.0f + m_Pvy + m_size;
	//Draw::Draw(50, &src, &dst, d, 0.0f);


	//▼雲(右上)表示
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 500.0f;
	src.m_bottom = 500.0f;

	dst.m_top = -1000.0f + m_Cloud_move;
	dst.m_left = 900.0f - m_Cloud_move;
	dst.m_right = 2200.0f - m_Cloud_move;
	dst.m_bottom = 100.0f + m_Cloud_move;
	Draw::Draw(1, &src, &dst, d, 0.0f);

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
	Draw::Draw(1, &src, &dst, d, 0.0f);

	//以下の位置になると画面全体が隠れる
	//dst.m_top = -400.0f;
	//dst.m_left = 0.0f;
	//dst.m_right = 1300.0f;
	//dst.m_bottom = 700.0f;




	//デバッグ用仮マウス位置表示
	wchar_t str[256];
	swprintf_s(str, L"x=%f,y=%f", m_mou_x, m_mou_y);
	Font::StrDraw(str, 20, 20, 12, d);
}
