//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"

#include "GameHead.h"

//使用するネームスペース
using namespace GameL;

//マクロ
#define INI_ALPHA (0.0f) //透過度(アルファ値)の初期値
#define INI_COLOR (0.9f) //全カラー明度の初期値(アイコン未選択中のカラー)

//イニシャライズ
void CObjBarracks::Init()
{
	m_Back_Button_color = INI_COLOR;
	m_Bar_color = INI_COLOR;
	m_Bar_Lvup_color = INI_COLOR;

	for (int i = 0; i < 4; i++)
	{
		m_Human_up_color[i] = INI_COLOR;	//全ての要素の値をINI_COLORで初期化している
		m_Human_down_color[i] = INI_COLOR;	//全ての要素の値をINI_COLORで初期化している
	}

	m_mou_x = 0.0f;
	m_mou_y = 0.0f;
	m_mou_r = false;
	m_mou_l = false;
	m_introduce_f = false;
	m_finalcheck_f = false;
	m_key_lf = false;
	m_alpha = INI_ALPHA;
}

//アクション
void CObjBarracks::Action()
{
	//マウスの位置を取得
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//マウスのボタンの状態
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	//▼兵舎ウインドウ表示時の処理
	if (window_start_manage == Barracks)
	{
		//マウスカーソル上部に表示されるエラーメッセージを徐々に非表示にする
		if (m_alpha > 0.0f)
		{
			m_alpha -= 0.01f;
		}

		//戻るボタン左クリック、もしくは右クリック(どこでも)する事で兵舎ウインドウを閉じる
		if (30 < m_mou_x && m_mou_x < 80 && 30 < m_mou_y && m_mou_y < 80 || m_mou_r == true)
		{
			m_Back_Button_color = 1.0f;

			//▼クリックされたらフラグを立て、兵舎ウインドウを閉じる
			//右クリック入力時
			if (m_mou_r == true)
			{
				//ウインドウ閉じた後、続けて戻るボタンを入力しないようにstatic変数にfalseを入れて制御
				m_key_rf = false;

				//エラーメッセージを非表示にするため、透過度を0.0fにする
				m_alpha = 0.0f;

				//"どのウインドウも開いていない状態"フラグを立てる
				window_start_manage = Default;
			}
			//左クリック入力時
			else if (m_mou_l == true)
			{
				//左クリック押したままの状態では入力出来ないようにしている
				if (m_key_lf == true)
				{
					m_key_lf = false;

					//エラーメッセージを非表示にするため、透過度を0.0fにする
					m_alpha = 0.0f;

					//"どのウインドウも開いていない状態"フラグを立てる
					window_start_manage = Default;
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
		else
		{
			m_Back_Button_color = INI_COLOR;
		}

		//兵舎レベルUP
		if (30 < m_mou_x && m_mou_x < 148 && 465 < m_mou_y && m_mou_y < 610)
		{
			m_Bar_Lvup_color = 1.0f;
			
			//左クリックされたらLvUP条件を満たしているかチェックを行い、
			//満たしていれば、兵舎LvUPの処理を行う。
			//満たしていなければ、エラーメッセージを表示する。
			if (m_mou_l == true)
			{
				//左クリック押したままの状態では入力出来ないようにしている
				if (m_key_lf == true)
				{
					m_key_lf = false;

					m_Bar_Lvup_color = 0.0f;

					//ここで兵舎LvUP処理を行う。
					//しかし、現状未実装である。
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
		else
		{
			m_Bar_Lvup_color = INI_COLOR;
		}

		//パワー住民振り分けUP
		if (695 < m_mou_x && m_mou_x < 793 && 118 < m_mou_y && m_mou_y < 218)
		{
			m_Human_up_color[0] = 1.0f;

			//左クリックされたら振り分け関数を呼び出し、住民振り分けの処理を行う
			if (m_mou_l == true)
			{
				//左クリック押したままの状態では入力出来ないようにしている
				if (m_key_lf == true)
				{
					m_key_lf = false;

					m_Human_up_color[0] = 0.0f;
			
					g_Power_num = Allocation(g_Power_num, +1);//振り分け関数を呼び出す
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
		else
		{
			m_Human_up_color[0] = INI_COLOR;
		}

		//ディフェンス住民振り分けUP
		if (695 < m_mou_x && m_mou_x < 793 && 228 < m_mou_y && m_mou_y < 328)
		{
			m_Human_up_color[1] = 1.0f;

			//左クリックされたら振り分け関数を呼び出し、住民振り分けの処理を行う
			if (m_mou_l == true)
			{
				//左クリック押したままの状態では入力出来ないようにしている
				if (m_key_lf == true)
				{
					m_key_lf = false;

					m_Human_up_color[1] = 0.0f;

					g_Defense_num = Allocation(g_Defense_num, +1);//振り分け関数を呼び出す
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
		else
		{
			m_Human_up_color[1] = INI_COLOR;
		}

		//スピード住民振り分けUP
		if (695 < m_mou_x && m_mou_x < 793 && 338 < m_mou_y && m_mou_y < 438)
		{
			m_Human_up_color[2] = 1.0f;

			//左クリックされたら振り分け関数を呼び出し、住民振り分けの処理を行う
			if (m_mou_l == true)
			{
				//左クリック押したままの状態では入力出来ないようにしている
				if (m_key_lf == true)
				{
					m_key_lf = false;

					m_Human_up_color[2] = 0.0f;

					g_Speed_num = Allocation(g_Speed_num, +1);//振り分け関数を呼び出す
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
		else
		{
			m_Human_up_color[2] = INI_COLOR;
		}

		//バランス住民振り分けUP
		if (695 < m_mou_x && m_mou_x < 793 && 448 < m_mou_y && m_mou_y < 548)
		{
			m_Human_up_color[3] = 1.0f;

			//左クリックされたら振り分け関数を呼び出し、住民振り分けの処理を行う
			if (m_mou_l == true)
			{
				//左クリック押したままの状態では入力出来ないようにしている
				if (m_key_lf == true)
				{
					m_key_lf = false;

					m_Human_up_color[3] = 0.0f;

					g_Balance_num = Allocation(g_Balance_num, +1);//振り分け関数を呼び出す
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
		else
		{
			m_Human_up_color[3] = INI_COLOR;
		}
		
		//パワー住民振り分けDOWN
		if (802 < m_mou_x && m_mou_x < 902 && 118 < m_mou_y && m_mou_y < 218)
		{
			m_Human_down_color[0] = 1.0f;

			//左クリックされたら振り分け関数を呼び出し、住民振り分けの処理を行う
			if (m_mou_l == true)
			{
				//左クリック押したままの状態では入力出来ないようにしている
				if (m_key_lf == true)
				{
					m_key_lf = false;

					m_Human_down_color[0] = 0.0f;

					g_Power_num = Allocation(g_Power_num, -1);//振り分け関数を呼び出す
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
		else
		{
			m_Human_down_color[0] = INI_COLOR;
		}

		//ディフェンス住民振り分けDOWN
		if (802 < m_mou_x && m_mou_x < 902 && 228 < m_mou_y && m_mou_y < 328)
		{
			m_Human_down_color[1] = 1.0f;

			//左クリックされたら振り分け関数を呼び出し、住民振り分けの処理を行う
			if (m_mou_l == true)
			{
				//左クリック押したままの状態では入力出来ないようにしている
				if (m_key_lf == true)
				{
					m_key_lf = false;

					m_Human_down_color[1] = 0.0f;

					g_Defense_num = Allocation(g_Defense_num, -1);//振り分け関数を呼び出す
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
		else
		{
			m_Human_down_color[1] = INI_COLOR;
		}

		//スピード住民振り分けDOWN
		if (802 < m_mou_x && m_mou_x < 902 && 338 < m_mou_y && m_mou_y < 438)
		{
			m_Human_down_color[2] = 1.0f;

			//左クリックされたら振り分け関数を呼び出し、住民振り分けの処理を行う
			if (m_mou_l == true)
			{
				//左クリック押したままの状態では入力出来ないようにしている
				if (m_key_lf == true)
				{
					m_key_lf = false;

					m_Human_down_color[2] = 0.0f;

					g_Speed_num = Allocation(g_Speed_num, -1);//振り分け関数を呼び出す
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
		else
		{
			m_Human_down_color[2] = INI_COLOR;
		}

		//バランス住民振り分けDOWN
		if (802 < m_mou_x && m_mou_x < 902 && 448 < m_mou_y && m_mou_y < 548)
		{
			m_Human_down_color[3] = 1.0f;

			//左クリックされたら振り分け関数を呼び出し、住民振り分けの処理を行う
			if (m_mou_l == true)
			{
				//左クリック押したままの状態では入力出来ないようにしている
				if (m_key_lf == true)
				{
					m_key_lf = false;

					m_Human_down_color[3] = 0.0f;

					g_Balance_num = Allocation(g_Balance_num, -1);//振り分け関数を呼び出す
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
		else
		{
			m_Human_down_color[3] = INI_COLOR;
		}


		return;
	}
	//ホーム画面に戻るボタンが押されたり、
	//他施設のウインドウを開いている時は操作を受け付けないようにする。
	else if (window_start_manage != Default)
	{
		return;
	}


	//兵舎選択範囲
	if (810 < m_mou_x && m_mou_x < 1190 && 460 < m_mou_y && m_mou_y < 690)
	{
		m_introduce_f = true;	//施設紹介ウインドウを表示する
		m_Bar_color = 1.0f;

		//左クリックされたらフラグを立て、兵舎ウインドウを開く
		if (m_mou_l == true)
		{
			//左クリック押したままの状態では入力出来ないようにしている
			if (m_key_lf == true)
			{
				m_key_lf = false;

				m_introduce_f = false;//施設紹介ウインドウを非表示にする(兵舎ウインドウ閉じた時に一瞬映り込むため)

				//"兵舎ウインドウを開いている状態"フラグを立てる
				window_start_manage = Barracks;
			}
		}
		else
		{
			m_key_lf = true;
		}
	}
	else
	{
		m_introduce_f = false;//施設紹介ウインドウを非表示にする
		m_Bar_color = INI_COLOR;
	}
}

//ドロー
void CObjBarracks::Draw()
{
	//▼シーン切り替え演出後に非表示にする処理
	if (scene_change_start == true)
	{
		return;
	}


	//▽描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	//赤色
	float red[4] = { 1.0f,0.0f,0.0f,1.0f };

	//青色
	float blue[4] = { 0.0f,0.0f,1.0f,1.0f };

	//緑色
	float green[4] = { 0.0f,1.0f,0.0f,1.0f };

	//黒色
	float black[4] = { 0.0f,0.0f,0.0f,1.0f };

	//白色＆その他画像用
	float white[4] = { 1.0f,1.0f,1.0f,1.0f };

	//戻るボタン用
	float back[4] = { m_Back_Button_color,m_Back_Button_color,m_Back_Button_color,1.0f };

	//兵舎画像用
	float bar[4] = { m_Bar_color,m_Bar_color,m_Bar_color,1.0f };

	//兵舎LvUP画像用
	float Lvup[4] = { m_Bar_Lvup_color, m_Bar_Lvup_color, m_Bar_Lvup_color,1.0f };

	//住民振り分けUP画像用
	float up[4][4] =
	{
		{ m_Human_up_color[0],m_Human_up_color[0],m_Human_up_color[0],1.0f },
		{ m_Human_up_color[1],m_Human_up_color[1],m_Human_up_color[1],1.0f },
		{ m_Human_up_color[2],m_Human_up_color[2],m_Human_up_color[2],1.0f },
		{ m_Human_up_color[3],m_Human_up_color[3],m_Human_up_color[3],1.0f },
	};

	//住民振り分けDOWN画像用
	float down[4][4] =
	{
		{ m_Human_down_color[0],m_Human_down_color[0],m_Human_down_color[0],1.0f },
		{ m_Human_down_color[1],m_Human_down_color[1],m_Human_down_color[1],1.0f },
		{ m_Human_down_color[2],m_Human_down_color[2],m_Human_down_color[2],1.0f },
		{ m_Human_down_color[3],m_Human_down_color[3],m_Human_down_color[3],1.0f },
	};

	//エラーメッセージ用
	float error[4] = { 1.0f,0.0f,0.0f,m_alpha };

	//▽フォント準備
	//兵舎レベル用
	wchar_t Bar[9];									 //9文字分格納可能な文字配列を宣言(99レベル以上はいかないと想定した文字分)
	swprintf_s(Bar, L"兵舎 Lv.%d", g_Bar_Level);//その文字配列に文字データを入れる

	//残り住民数用
	wchar_t human_remain[12];						 //12文字分格納可能な文字配列を宣言(最大値は999999)
	swprintf_s(human_remain, L"残り %6d 人", g_Remain_num);//その文字配列に文字データを入れる

	//各タイプ(パワー、スピード等)の住民数用
	wchar_t human_num[4][9];						 //9文字分格納可能な文字配列を4つ宣言(それぞれ最大値は999999)
	swprintf_s(human_num[0], L"%6d 人", g_Power_num);//▽それぞれの文字配列に対応する文字データを入れる
	swprintf_s(human_num[1], L"%6d 人", g_Defense_num);
	swprintf_s(human_num[2], L"%6d 人", g_Speed_num);
	swprintf_s(human_num[3], L"%6d 人", g_Balance_num);


	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

	//施設ウインドウ(兵舎、研究所、倉庫)が開いてない時に表示するグラフィック
	if (window_start_manage == Default || window_start_manage == BackButton)
	{
		//▼兵舎表示 
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 256.0f;
		src.m_bottom = 256.0f;

		dst.m_top = 460.0f;
		dst.m_left = 810.0f;
		dst.m_right = 1190.0f;
		dst.m_bottom = 690.0f;
		Draw::Draw(2, &src, &dst, bar, 0.0f);

		//施設紹介ウインドウ表示管理フラグがtrueの時、描画。
		if (m_introduce_f == true)
		{
			//▼施設紹介ウインドウ表示
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 64.0f;
			src.m_bottom = 64.0f;

			dst.m_top = m_mou_y - 50.0f;
			dst.m_left = m_mou_x - 100.0f;
			dst.m_right = m_mou_x + 100.0f;
			dst.m_bottom = m_mou_y - 10.0f;
			Draw::Draw(21, &src, &dst, white, 0.0f);

			//▼フォント表示
			//兵舎レベル
			Font::StrDraw(Bar, m_mou_x - 75.0f, m_mou_y - 45.0f, 30.0f, black);
		}
	}

	//兵舎ウインドウ開いている際に表示するグラフィック
	else if (window_start_manage == Barracks)
	{
		//▼灰色ウインドウ表示
		src.m_top    =    0.0f;
		src.m_left   =    0.0f;
		src.m_right  = 1160.0f;
		src.m_bottom =  660.0f;

		dst.m_top = 20.0f;
		dst.m_left = 20.0f;
		dst.m_right = 1180.0f;
		dst.m_bottom = 680.0f;
		Draw::Draw(20, &src, &dst, white, 0.0f);

		//▼戻るボタン表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 30.0f;
		dst.m_left = 30.0f;
		dst.m_right = 80.0f;
		dst.m_bottom = 80.0f;
		Draw::Draw(1, &src, &dst, back, 0.0f);

		//▼兵舎表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 245.0f;
		src.m_bottom = 206.0f;

		dst.m_top = 150.0f;
		dst.m_left = 100.0f;
		dst.m_right = 400.0f;
		dst.m_bottom = 350.0f;
		Draw::Draw(2, &src, &dst, white, 0.0f);

		//▼兵舎LVUP表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 48.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 470.0f;
		dst.m_left = 30.0f;
		dst.m_right = 150.0f;
		dst.m_bottom = 620.0f;
		Draw::Draw(22, &src, &dst, Lvup, 0.0f);

		//▼レベルUP条件ウインドウ表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 420.0f;
		dst.m_left = 150.0f;
		dst.m_right = 450.0f;
		dst.m_bottom = 670.0f;
		Draw::Draw(21, &src, &dst, white, 0.0f);

		//▼残り住民数のウインドウ表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 580.0f;
		dst.m_left = 750.0f;
		dst.m_right = 1160.0f;
		dst.m_bottom = 650.0f;
		Draw::Draw(21, &src, &dst, white, 0.0f);

		for (int i = 0; i < 4; i++)
		{
			//▼兵舎振り分けUP表示
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 64.0f;
			src.m_bottom = 64.0f;

			dst.m_top = 120.0f + i * 110.0f;
			dst.m_left = 700.0f;
			dst.m_right = 800.0f;
			dst.m_bottom = 220.0f + i * 110.0f;
			Draw::Draw(23, &src, &dst, up[i], 0.0f);

			//▼兵舎振り分けDOWN表示
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 64.0f;
			src.m_bottom = 64.0f;

			dst.m_top = 120.0f + i * 110.0f;
			dst.m_left = 810.0f;
			dst.m_right = 910.0f;
			dst.m_bottom = 220.0f + i * 110.0f;
			Draw::Draw(24, &src, &dst, down[i], 0.0f);

			//▼各タイプ(パワー、スピード等)の住民数ウインドウ表示
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 64.0f;
			src.m_bottom = 64.0f;

			dst.m_top = 140.0f + i * 110.0f;
			dst.m_left = 930.0f;
			dst.m_right = 1150.0f;
			dst.m_bottom = 200.0f + i * 110.0f;
			Draw::Draw(21, &src, &dst, white, 0.0f);
		}

		//▼フォント表示
		//兵舎レベル
		Font::StrDraw(Bar, 125.0f, 95.0f, 50.0f, white);

		//残り住民数
		Font::StrDraw(human_remain, 780.0f, 590.0f, 50.0f, black);

		//各タイプ(パワー、スピード等)の住民数
		for (int i = 0; i < 4; i++)
		{
			Font::StrDraw(human_num[i], 950.0f, 150.0f + i * 110.0f, 40.0f, black);
		}

		//その他フォント
		Font::StrDraw(L"兵舎レベルＵＰ", 60.0f, 370.0f, 50.0f, white);

		Font::StrDraw(L"住民振り分け", 620.0f, 45.0f, 60.0f, white);

		Font::StrDraw(L"パワー", 505.0f, 145.0f, 55.0f, red);

		Font::StrDraw(L"ディフェンス", 450.0f, 260.0f, 40.0f, blue);

		Font::StrDraw(L"スピード", 480.0f, 365.0f, 50.0f, green);

		Font::StrDraw(L"バランス", 480.0f, 475.0f, 50.0f, white);

		Font::StrDraw(L"▼レベルUP条件", 175.0f, 440.0f, 25.0f, black);
		Font::StrDraw(L"α版では", 175.0f, 470.0f, 25.0f, red);
		Font::StrDraw(L"レベルUP出来ません。", 175.0f, 500.0f, 25.0f, red);

		//エラーメッセージ
		Font::StrDraw(m_message, m_mou_x - 110.0f, m_mou_y - 45.0f, 30.0f, error);
		


		//デバッグ用仮マウス位置表示
		wchar_t str[256];
		swprintf_s(str, L"x=%f,y=%f", m_mou_x, m_mou_y);
		Font::StrDraw(str, 20.0f, 20.0f, 12.0f, white);
	}
}