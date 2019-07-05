//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"

//使用するネームスペース
using namespace GameL;

//マクロ
#define HELP_X_POS (1120.0f) //ヘルプボタンのX位置
#define HELP_Y_POS (30.0f)	 //ヘルプボタンのY位置
#define HELP_SIZE (50.0f)	 //ヘルプボタンのサイズ(width & height)
#define INI_COLOR (0.9f) //全カラー明度の初期値(アイコン未選択中のカラー)
#define INI_PAGE (1)	 //ページの初期値(0ページ目だと感覚的に分かりにくいので1とした。)

//イニシャライズ
void CObjHelp::Init()
{
	m_mou_x = 0.0f;
	m_mou_y = 0.0f;
	m_mou_r = false;
	m_mou_l = false;
	m_key_f = false;

	m_Help_Button_color = INI_COLOR;
	m_Back_Button_color = INI_COLOR;

	m_help_f = false;
	m_page_num = INI_PAGE;

	//現在のシーンで画像の登録番号、ヘルプ画像(ページ)の最大数を決める
	if (m_Scene_num == 1)//ホーム	1											
	{
		m_page_max = 1;
		m_help_reg_num = 4;
		m_Back_reg_num = 3;
	}
	else if (m_Scene_num == 2)//育成	2
	{
		m_page_max = 1;
		m_help_reg_num = 47;
		m_Back_reg_num = 1;
	}
	else  //(m_Scene_num == 3)//準備	3
	{
		m_page_max = 2;
		m_help_reg_num = 21;
		m_Back_reg_num = 56;
	}
}

//アクション
void CObjHelp::Action()
{
	//マウスの位置を取得
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//マウスのボタンの状態
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	//▼キーフラグ
	//※左クリックPush状態→左クリック未Push状態になるまで、
	//再度左クリックする事は出来ない処理。
	if (m_mou_l == false)	//左クリックOFF
	{
		m_key_f = false;	//キーフラグOFF
	}

	//▼ヘルプ非表示時の処理
	if (m_help_f == false)						
	{											
		//ヘルプボタン選択範囲
		if (HELP_X_POS - 10.0f < m_mou_x && m_mou_x < HELP_X_POS - 10.0f + HELP_SIZE && HELP_Y_POS < m_mou_y && m_mou_y < HELP_Y_POS + HELP_SIZE)
		{		
			m_Help_Button_color = 1.0f;

			if (m_mou_l == true && m_key_f == false)//マウス左クリック
			{
				m_help_f = true;//ヘルプ表示する
				m_key_f = true;	//連打制御(キーフラグON)

				//選択音
				Audio::Start(1);
			}
		}
		else
		{
			//選択範囲外の時は未選択カラーにする
			m_Help_Button_color = INI_COLOR;
		}
	}
	//▼ヘルプ表示時の処理
	else										
	{
		//▼ページ進めるボタン
		if (1100.0f < m_mou_x && m_mou_x < 1150.0f && 330.0f < m_mou_y && m_mou_y < 380.0f &&
			m_mou_l == true && m_key_f == false)//マウス左クリック
		{
			if (m_page_num + 1 > m_page_max)
			{
				m_page_num = INI_PAGE;//このページが最後のページであれば、最初のページに移動させる
			}
			else
			{
				m_page_num++;	//ページを進める
			}

			m_key_f = true;		//連打制御(キーフラグON)
		}

		//▼ページ戻すボタン
		if (50.0f < m_mou_x && m_mou_x < 100.0f && 330.0f < m_mou_y && m_mou_y < 380.0f &&
			m_mou_l == true && m_key_f == false)//マウス左クリック
		{
			if (m_page_num - 1 < INI_PAGE)
			{
				m_page_num = m_page_max;//このページが最初のページであれば、最後のページに移動させる
			}
			else
			{
				m_page_num--;		//ページを戻す
			}

			m_key_f = true;		//連打制御(キーフラグON)
		}

		//戻るボタン
		if (30 < m_mou_x && m_mou_x < 80 && 30 < m_mou_y && m_mou_y < 80 || m_mou_r == true)
		{
			m_Back_Button_color = 1.0f;

			if (m_mou_l == true || m_mou_r == true)
			{
				m_help_f = false;//ヘルプ非表示にする

				m_page_num = INI_PAGE;//ページを初期化する

				//育成画面や戦闘準備画面では右クリックする事により、
				//同時に各シーンの戻るボタンも同時に起動される恐れ大なのでキーフラグ用意する

				//あと、ゲッターセッター関連部分もしっかりする

				//page_maxが1、つまりヘルプ画像が一枚しかない時はページ進めるボタンと戻るボタン表示しない。
				//あと、選択してる事が分かるようにカラー明度変更も行う。

				//戻るボタン音
				Audio::Start(2);
			}
		}
		else
		{
			//選択範囲外の時は未選択カラーにする
			m_Back_Button_color = INI_COLOR;
		}
	}
}

//ドロー
void CObjHelp::Draw()
{
	//描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	float d[4] = { 1.0f,1.0f,1.0f,1.0f };

	float help[4] = { m_Help_Button_color,m_Help_Button_color,m_Help_Button_color,1.0f };

	float back[4] = { m_Back_Button_color,m_Back_Button_color,m_Back_Button_color,1.0f };

	RECT_F src;//切り取り位置
	RECT_F dst;//表示位置
	

	//▼ヘルプボタン表示
	src.m_top   =  0.0f;
	src.m_left  =  0.0f;
	src.m_right =128.0f;
	src.m_bottom=128.0f;
	
	dst.m_top   = HELP_Y_POS;
	dst.m_left  = HELP_X_POS;
	dst.m_right = HELP_X_POS + HELP_SIZE;
	dst.m_bottom= HELP_Y_POS + HELP_SIZE;
	Draw::Draw(m_help_reg_num, &src, &dst, help, 0.0f);


	//ヘルプ表示時、以下のものを描画する
	if (m_help_f == true)
	{
		//▼ヘルプ画像表示
		src.m_top   = 150.0f;
		src.m_left  =   0.0f;
		src.m_right =1280.0f;
		src.m_bottom= 870.0f;
			
		dst.m_top   =  20.0f;
		dst.m_left  =  20.0f;
		dst.m_right =1180.0f;
		dst.m_bottom= 680.0f;
		Draw::Draw(m_help_reg_num + m_page_num, &src, &dst, d, 0.0f);
			
		//▼戻るボタン表示
		src.m_top   =  0.0f;
		src.m_left  =  0.0f;
		src.m_right = 64.0f;
		src.m_bottom= 64.0f;
	
		dst.m_top   = 30.0f;
		dst.m_left  = 30.0f;
		dst.m_right = 80.0f;
		dst.m_bottom= 80.0f;
		Draw::Draw(m_Back_reg_num, &src, &dst, back, 0.0f);			

		//▼ページを進めるボタン表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 330.0f;
		dst.m_left = 1100.0f;
		dst.m_right = 1150.0f;
		dst.m_bottom = 380.0f;
		Draw::Draw(46, &src, &dst, d, 0.0f);

		//▼ページを戻すボタン表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = -64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 330.0f;
		dst.m_left = 50.0f;
		dst.m_right = 100.0f;
		dst.m_bottom = 380.0f;
		Draw::Draw(46, &src, &dst, d, 0.0f);
	}

	

	//デバッグ用仮マウス位置表示
	wchar_t str[256];
	swprintf_s(str, L"x=%f,y=%f", m_mou_x, m_mou_y);
	Font::StrDraw(str, 20.0f, 20.0f, 12.0f, d);
}
