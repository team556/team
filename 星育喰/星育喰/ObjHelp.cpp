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
#define HELP_X_POS (1120.0f) //ヘルプボタンの初期X位置
#define HELP_Y_POS (30.0f)	 //ヘルプボタンの初期Y位置
#define HELP_SIZE (50.0f)	 //ヘルプボタンのサイズ(width & height)
#define INI_ALPHA (0.0f) //透過度(アルファ値)の初期値
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

	m_px = HELP_X_POS;
	m_py = HELP_Y_POS;
	m_vec = 0.0f;

	m_Help_Button_color = INI_COLOR;
	m_Back_Button_color = INI_COLOR;
	m_Page_Back_Button_color = INI_COLOR;
	m_Page_Next_Button_color = INI_COLOR;

	m_Help_Button_alpha = INI_ALPHA;

	m_mig_staging_f = false;
	m_Tra_Eat_f = false;
	m_is_operatable = true;
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

		//ついでにヘルプボタン表示処理を1回のみ行うように準備しておく
		m_Help_Button_alpha = -0.1f;
	}
	else  //(m_Scene_num == 3)//準備	3
	{
		m_page_max = 2;
		m_help_reg_num = 21;
		m_Back_reg_num = 56;

		//ついでにこのタイミングでシーン移行演出用の座標変更等もしておく
		m_px += 407.3f;
		m_py -= 407.3f;
		m_vec = 50.0f;
		m_Help_Button_alpha = 1.0f;
		m_is_operatable = false;
	}
}

//アクション
void CObjHelp::Action()
{
	//▼シーン移行演出処理(ヘルプボタン非表示処理)
	//※なお、各シーン毎にヘルプボタンの非表示方法は違う。
	if (m_mig_staging_f == true)
	{
		if (m_Scene_num == 1)//ホーム	1										
		{
			//育成画面移行演出
			if (m_Tra_Eat_f == true)
			{
				//画面外(右上)に向かってヘルプボタンを移動させ、非表示状態にする
				if (m_px < 1200.0f || m_py > 0.0f)
				{
					m_px += 5.0f;
					m_py -= 5.0f;
				}
			}
			//戦闘準備画面移行演出
			else
			{
				//ヘルプボタンを徐々に非表示にさせる
				if (m_Help_Button_alpha > 0.0f)
				{
					m_Help_Button_alpha -= 0.01f;
				}
			}
		}
		else if (m_Scene_num == 2)//育成	2
		{
			//即座に非表示にする
			m_Help_Button_alpha = 0.0f;
		}
		else  //(m_Scene_num == 3)//準備	3
		{
			//▼画面外(右上)に向かってヘルプボタンを移動させ、非表示状態にする

			//画面外(右上)に行くまで移動させる
			if (m_px < HELP_X_POS + 407.3f)
			{
				m_px += m_vec * 0.37;//X移動処理
				m_py -= m_vec * 0.37;//Y移動処理
				m_vec /= 0.956f;//移動速度増加処理
			}
		}
		
		return;//演出中はヘルプボタンが反応しないようにする。
	}

	//▼ヘルプボタン表示処理
	//※なお、各シーン毎にヘルプボタンの表示方法は違う。
	else
	{
		if (m_Scene_num == 1)//ホーム	1											
		{
			//ヘルプボタンを徐々に表示させる
			if (m_Help_Button_alpha < 1.0f)
			{
				m_Help_Button_alpha += 0.01f;
			}
		}
		else if (m_Scene_num == 2)//育成	2
		{
			//即座に表示する(1回のみ行われる)
			if (m_Help_Button_alpha == -0.1f)
			{
				m_Help_Button_alpha = 1.0f;
			}
		}
		else  //(m_Scene_num == 3)//準備	3
		{
			//▼画面外右上から左下に向かってヘルプボタンを移動させ、画面内に表示させる
			
			//初期X位置に来るまで移動させる
			if (m_px >= HELP_X_POS)
			{
				m_px -= m_vec * 0.37f;//X移動処理
				m_py += m_vec * 0.37f;//Y移動処理
				m_vec *= 0.956f;//移動速度減少処理
			}
		}
	}

	//操作不可処理
	if (m_is_operatable == false)
	{
		return;//操作不可中はヘルプボタンが反応しないようにする。
	}

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
	if (g_help_f == false)						
	{											
		//ヘルプボタン選択範囲
		if (m_px - 10.0f < m_mou_x && m_mou_x < m_px - 10.0f + HELP_SIZE && m_py < m_mou_y && m_mou_y < m_py + HELP_SIZE)
		{		
			m_Help_Button_color = 1.0f;//選択中はカラー明度を上げる

			if (m_mou_l == true && m_key_f == false)//マウス左クリック
			{
				g_help_f = true;//ヘルプ表示する
				m_key_f = true;	//連打制御(キーフラグON)

				//選択音
				Audio::Start(1);

				m_Help_Button_color = 0.5f;//選択時はカラー明度を一旦下げる
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
		//▼ページ戻すボタン
		if (30.0f < m_mou_x && m_mou_x < 80.0f && 326.0f < m_mou_y && m_mou_y < 375.0f &&
			m_page_max != 1)//ページ最大数が1ではない
		{
			m_Page_Back_Button_color = 1.0f;//選択中はカラー明度を上げる

			if (m_mou_l == true && m_key_f == false)//マウス左クリック
			{
				if (m_page_num - 1 < INI_PAGE)
				{
					m_page_num = m_page_max;//このページが最初のページであれば、最後のページに移動させる
				}
				else
				{
					m_page_num--;		//ページを戻す
				}

				//選択音
				Audio::Start(1);

				m_Page_Back_Button_color = 0.5f;//選択時はカラー明度を一旦下げる

				m_key_f = true;		//連打制御(キーフラグON)
			}
		}
		else
		{
			//選択範囲外の時は未選択カラーにする
			m_Page_Back_Button_color = INI_COLOR;
		}

		//▼ページ進めるボタン
		if (1110.0f < m_mou_x && m_mou_x < 1160.0f && 326.0f < m_mou_y && m_mou_y < 375.0f &&
			m_page_max != 1)//ページ最大数が1ではない
		{
			m_Page_Next_Button_color = 1.0f;//選択中はカラー明度を上げる

			if (m_mou_l == true && m_key_f == false)//マウス左クリック
			{
				if (m_page_num + 1 > m_page_max)
				{
					m_page_num = INI_PAGE;//このページが最後のページであれば、最初のページに移動させる
				}
				else
				{
					m_page_num++;	//ページを進める
				}

				//選択音
				Audio::Start(1);

				m_Page_Next_Button_color = 0.5f;//選択時はカラー明度を一旦下げる

				m_key_f = true;		//連打制御(キーフラグON)
			}
		}
		else
		{
			//選択範囲外の時は未選択カラーにする
			m_Page_Next_Button_color = INI_COLOR;
		}

		//戻るボタン
		if (30 < m_mou_x && m_mou_x < 80 && 30 < m_mou_y && m_mou_y < 80 || m_mou_r == true)
		{
			m_Back_Button_color = 1.0f;//選択中はカラー明度を上げる

			if (m_mou_l == true || m_mou_r == true)
			{
				g_help_f = false;//ヘルプ非表示にする

				m_Help_Button_color = INI_COLOR;//ヘルプボタンカラー明度を初期化する

				m_page_num = INI_PAGE;//ページを初期化する

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
	//ヘルプボタン用
	float help[4] = { m_Help_Button_color,m_Help_Button_color,m_Help_Button_color,m_Help_Button_alpha };

	//戻るボタン用
	float back[4] = { m_Back_Button_color,m_Back_Button_color,m_Back_Button_color,1.0f };

	//ページ戻すボタン用
	float page_back[4] = { m_Page_Back_Button_color,m_Page_Back_Button_color,m_Page_Back_Button_color,1.0f };

	//ページ進めるボタン用
	float page_next[4] = { m_Page_Next_Button_color,m_Page_Next_Button_color,m_Page_Next_Button_color,1.0f };

	//その他画像用
	float d[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//切り取り位置
	RECT_F dst;//表示位置
	

	//▼ヘルプボタン表示
	src.m_top   =  0.0f;
	src.m_left  =  0.0f;
	src.m_right =128.0f;
	src.m_bottom=128.0f;
	
	dst.m_top   = m_py;
	dst.m_left  = m_px;
	dst.m_right = m_px + HELP_SIZE;
	dst.m_bottom= m_py + HELP_SIZE;
	Draw::Draw(m_help_reg_num, &src, &dst, help, 0.0f);


	//ヘルプ表示時、以下のものを描画する
	if (g_help_f == true)
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

		//ページ最大数が1でなければ表示する
		if (m_page_max != 1)
		{
			//▼ページを戻すボタン表示
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = -128.0f;
			src.m_bottom = 128.0f;

			dst.m_top = 330.0f;
			dst.m_left = 30.0f;
			dst.m_right = 80.0f;
			dst.m_bottom = 380.0f;
			Draw::Draw(46, &src, &dst, page_back, 0.0f);

			//▼ページを進めるボタン表示
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 128.0f;
			src.m_bottom = 128.0f;

			dst.m_top = 330.0f;
			dst.m_left = 1120.0f;
			dst.m_right = 1170.0f;
			dst.m_bottom = 380.0f;
			Draw::Draw(46, &src, &dst, page_next, 0.0f);
		}
	}

	

	//デバッグ用仮マウス位置表示
	wchar_t str[256];
	swprintf_s(str, L"x=%f,y=%f", m_mou_x, m_mou_y);
	Font::StrDraw(str, 20.0f, 20.0f, 12.0f, d);
}
