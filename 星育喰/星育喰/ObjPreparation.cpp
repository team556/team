//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"

//使用するネームスペース
using namespace GameL;

//マクロ
#define INI_ENEMY_X_POS (1150.0f)	//敵惑星4つ全体の初期X位置
#define INI_ENEMY_Y_POS (150.0f)	//敵惑星4つ全体の初期Y位置
#define INI_ENEMY_SPEED (50.0f)		//敵惑星4つの初期移動スピード
#define INI_ALPHA (0.0f) //透過度(アルファ値)の初期値
#define INI_COLOR (1.0f) //全カラー明度の初期値

//イニシャライズ
void CObjPreparation::Init()
{
	m_mou_x = 0.0f;
	m_mou_y = 0.0f;
	m_mou_r = false;
	m_mou_l = false;

	m_key_lf = false;
	m_key_rf = false;

	m_Pvx = 0.0f;
	m_Pvy = 0.0f;
	m_boost = 0.0f;
	m_rx = 0.0f;
	m_ry = 0.0f;
	m_size = 0.0f;

	m_Evx = 0.0f;
	m_Espeed = INI_ENEMY_SPEED;

	m_staging_time = 0;

	m_Back_Button_color = INI_COLOR;
	m_Yes_Button_color = INI_COLOR;
	m_No_Button_color = INI_COLOR;
	m_alpha = INI_ALPHA;

	m_Enemy_detail_message_window_x_size = 0.0f;
	m_Enemy_detail_message_window_y_size = 0.0f;
}

//アクション
void CObjPreparation::Action()
{
	////マウスの位置を取得
	//m_mou_x = (float)Input::GetPosX();
	//m_mou_y = (float)Input::GetPosY();
	////マウスのボタンの状態
	//m_mou_r = Input::GetMouButtonR();
	//m_mou_l = Input::GetMouButtonL();

	////育喰アイコン、敵惑星(背景)を徐々に表示させる
	//if (m_alpha < 1.0f)
	//{
	//	m_alpha += 0.01f;
	//}

	////育アイコン
	//if (20 < m_mou_x && m_mou_x < 220 && 480 < m_mou_y && m_mou_y < 680)
	//{
	//	//m_Tra_color = 0.7f;

	//	//左クリックされたらフラグを立て、育成画面へ演出を交えながらシーン移行
	//	if (m_mou_l == true)
	//	{
	//		//クリック押したままの状態では入力出来ないようにしている
	//		if (m_key_lf == true)
	//		{
	//			m_key_lf = false;

	//			//m_Tra_flag = true;
	//		}
	//	}
	//	else
	//	{
	//		m_key_lf = true;
	//	}
	//}
	//else
	//{
	//	//m_Tra_color = 1.0f;
	//}

	//▼戦闘準備画面開始演出
	if (m_Evx > -1000.0f)
	{
		m_staging_time++;

		m_Espeed -= m_Espeed * 0.047;

		m_Evx -= m_Espeed;

		return;
	}

	//マウスの位置を取得
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//マウスのボタンの状態
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();
}

//ドロー
void CObjPreparation::Draw()
{
	//描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	//それ以外の画像用
	float d[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置


	//▼背景表示
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 960.0f;
	src.m_bottom = 638.0f;

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 1200.0f;
	dst.m_bottom = 700.0f;
	Draw::Draw(0, &src, &dst, d, 0.0f);

	//▼敵惑星1表示
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 384.0f;
	src.m_bottom = 384.0f;

	dst.m_top = INI_ENEMY_Y_POS;
	dst.m_left = INI_ENEMY_X_POS + m_Evx;
	dst.m_right = INI_ENEMY_X_POS + 200.0f + m_Evx;
	dst.m_bottom = INI_ENEMY_Y_POS + 200.0f;
	Draw::Draw(1, &src, &dst, d, 0.0f);

	//▼敵惑星2表示
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 384.0f;
	src.m_bottom = 384.0f;

	dst.m_top = INI_ENEMY_Y_POS - 100.0f;
	dst.m_left = INI_ENEMY_X_POS + 300.0f + m_Evx;
	dst.m_right = INI_ENEMY_X_POS + 400.0f + m_Evx;
	dst.m_bottom = INI_ENEMY_Y_POS;
	Draw::Draw(2, &src, &dst, d, 0.0f);

	//▼敵惑星3表示
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 384.0f;
	src.m_bottom = 384.0f;

	dst.m_top = INI_ENEMY_Y_POS + 200.0f;
	dst.m_left = INI_ENEMY_X_POS + 500.0f + m_Evx;
	dst.m_right = INI_ENEMY_X_POS + 800.0f + m_Evx;
	dst.m_bottom = INI_ENEMY_Y_POS + 500.0f;
	Draw::Draw(3, &src, &dst, d, 0.0f);

	//▼敵惑星4表示
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 384.0f;
	src.m_bottom = 384.0f;

	dst.m_top = INI_ENEMY_Y_POS - 50.0f;
	dst.m_left = INI_ENEMY_X_POS + 700.0f + m_Evx;
	dst.m_right = INI_ENEMY_X_POS + 900.0f + m_Evx;
	dst.m_bottom = INI_ENEMY_Y_POS + 150.0f;
	Draw::Draw(4, &src, &dst, d, 0.0f);

	//▼プレイヤー惑星表示
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 62.0f;
	src.m_bottom = 62.0f;

	dst.m_top = 250.0f + m_Pvy - m_size;
	dst.m_left = 450.0f + m_Pvx - m_size;
	dst.m_right = 750.0f + m_Pvx + m_size;
	dst.m_bottom = 550.0f + m_Pvy + m_size;
	Draw::Draw(63, &src, &dst, d, 0.0f);



	//デバッグ用仮マウス位置表示
	wchar_t str[256];
	swprintf_s(str, L"x=%f,y=%f", m_mou_x, m_mou_y);
	Font::StrDraw(str, 20.0f, 20.0f, 12.0f, d);
}
