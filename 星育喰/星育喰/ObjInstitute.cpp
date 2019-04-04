//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"

#include "GameHead.h"

//使用するネームスペース
using namespace GameL;

//マクロ
#define INI_ALPHA (0.0f) //透過度(アルファ値)の初期値
#define INI_COLOR (1.0f) //全カラー明度の初期値

//イニシャライズ
void CObjInstitute::Init()
{
	m_Back_Button_color = INI_COLOR;
	m_Ins_color = INI_COLOR;
	m_Ins_Lvup_color = INI_COLOR;
	m_Human_up_color = INI_COLOR;
	m_Human_down_color = INI_COLOR;

	m_introduce_f = false;
	m_key_lf = false;
	m_alpha = INI_ALPHA;
}

//アクション
void CObjInstitute::Action()
{
	//マウスの位置を取得
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//マウスのボタンの状態
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	//▼研究所ウインドウ表示時の処理
	if (window_start_manage == Institute)
	{
		//マウスカーソル上部に表示されるエラーメッセージを徐々に非表示にする
		if (m_alpha > 0.0f)
		{
			m_alpha -= 0.01f;
		}

		//戻るボタン左クリック、もしくは右クリック(どこでも)する事で研究所ウインドウを閉じる
		if (30 < m_mou_x && m_mou_x < 80 && 30 < m_mou_y && m_mou_y < 80 || m_mou_r == true)
		{
			m_Back_Button_color = 0.7f;

			//▼クリックされたらフラグを立て、研究所ウインドウを閉じる
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
			m_Back_Button_color = 1.0f;
		}

		//研究所レベルUP
		if (30 < m_mou_x && m_mou_x < 148 && 465 < m_mou_y && m_mou_y < 610)
		{
			m_Ins_Lvup_color = 0.7f;

			//左クリックされたらLvUP条件を満たしているかチェックを行い、
			//満たしていれば、研究所LvUPの処理を行う。
			//満たしていなければ、エラーメッセージを表示する。
			if (m_mou_l == true)
			{
				//左クリック押したままの状態では入力出来ないようにしている
				if (m_key_lf == true)
				{
					m_key_lf = false;

					m_Ins_Lvup_color = 0.0f;

					//ここで研究所LvUP処理を行う。
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
			m_Ins_Lvup_color = 1.0f;
		}

		//研究員住民振り分けUP
		if (695 < m_mou_x && m_mou_x < 793 && 118 < m_mou_y && m_mou_y < 218)
		{
			m_Human_up_color = 0.7f;

			//左クリックされたら振り分け関数を呼び出し、住民振り分けの処理を行う
			if (m_mou_l == true)
			{
				//左クリック押したままの状態では入力出来ないようにしている
				if (m_key_lf == true)
				{
					m_key_lf = false;

					m_Human_up_color = 0.0f;

					g_Research_num = Allocation(g_Research_num, +1);//振り分け関数を呼び出す
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
		else
		{
			m_Human_up_color = 1.0f;
		}

		//研究員住民振り分けDOWN
		if (802 < m_mou_x && m_mou_x < 902 && 118 < m_mou_y && m_mou_y < 218)
		{
			m_Human_down_color = 0.7f;

			//左クリックされたら振り分け関数を呼び出し、住民振り分けの処理を行う
			if (m_mou_l == true)
			{
				//左クリック押したままの状態では入力出来ないようにしている
				if (m_key_lf == true)
				{
					m_key_lf = false;

					m_Human_down_color = 0.0f;

					g_Research_num = Allocation(g_Research_num, -1);//振り分け関数を呼び出す
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
		else
		{
			m_Human_down_color = 1.0f;
		}

		//ミサイルボタン
		if (515 < m_mou_x && m_mou_x < 1120 && 325 < m_mou_y && m_mou_y < 473)
		{
			m_Mis_Button_color = 0.7f;

			//左クリックされたらフラグを立て、ミサイルウインドウを開く
			if (m_mou_l == true)
			{
				//左クリック押したままの状態では入力出来ないようにしている
				if (m_key_lf == true)
				{
					m_key_lf = false;

					m_Mis_Button_color = 0.0f;

					//エラーメッセージを非表示にするため、透過度を0.0fにする
					m_alpha = 0.0f;

					//"ミサイルウインドウを開いている状態"フラグを立てる
					window_start_manage = Missile;
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
		else
		{
			m_Mis_Button_color = 1.0f;
		}
		
		//武器ポッドボタン
		if (515 < m_mou_x && m_mou_x < 1120 && 493 < m_mou_y && m_mou_y < 641)
		{
			m_Equ_Button_color = 0.7f;

			//左クリックされたらフラグを立て、武器ポッドウインドウを開く
			if (m_mou_l == true)
			{
				//左クリック押したままの状態では入力出来ないようにしている
				if (m_key_lf == true)
				{
					m_key_lf = false;

					m_Equ_Button_color = 0.0f;

					//エラーメッセージを非表示にするため、透過度を0.0fにする
					m_alpha = 0.0f;

					//"武器ポッドウインドウを開いている状態"フラグを立てる
					window_start_manage = Equipment;
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
		else
		{
			m_Equ_Button_color = 1.0f;
		}


		return;
	}
	//▼ミサイルウインドウ表示時の処理
	else if (window_start_manage == Missile)
	{
		return;
	}
	//▼武器ポッドウインドウ表示時の処理
	else if (window_start_manage == Equipment)
	{
		return;
	}
	//ホーム画面に戻るボタンが押されたり、
	//他施設のウインドウを開いている時は操作を受け付けないようにする。
	else if (window_start_manage != Default)
	{
		return;
	}


	//研究所選択範囲
	if (60 < m_mou_x && m_mou_x < 325 && 505 < m_mou_y && m_mou_y < 637)
	{
		m_introduce_f = true;	//施設紹介ウインドウを表示する
		m_Ins_color = 0.7f;

		//左クリックされたらフラグを立て、研究所ウインドウを開く
		if (m_mou_l == true)
		{
			//左クリック押したままの状態では入力出来ないようにしている
			if (m_key_lf == true)
			{
				m_key_lf = false;

				m_introduce_f = false;//施設紹介ウインドウを非表示にする(研究所ウインドウ閉じた時に一瞬映り込むため)

				//"研究所ウインドウを開いている状態"フラグを立てる
				window_start_manage = Institute;
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
		m_Ins_color = 1.0f;
	}
}

//ドロー
void CObjInstitute::Draw()
{
	//▼シーン切り替え演出後に非表示にする処理
	if (scene_change_start == true)
	{
		return;
	}


	//▽描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	//青色(若干緑入り)
	float blue[4] = { 0.0f,0.3f,0.9f,1.0f };

	//黒色
	float black[4] = { 0.0f,0.0f,0.0f,1.0f };

	//白色＆その他画像用
	float white[4] = { 1.0f,1.0f,1.0f,1.0f };

	//戻るボタン用
	float back[4] = { m_Back_Button_color,m_Back_Button_color,m_Back_Button_color,1.0f };

	//研究所画像用
	float ins[4] = { m_Ins_color,m_Ins_color,m_Ins_color,1.0f };

	//研究所LvUP画像用
	float Lvup[4] = { m_Ins_Lvup_color, m_Ins_Lvup_color, m_Ins_Lvup_color,1.0f };

	//住民振り分けUP画像用
	float up[4] = { m_Human_up_color,m_Human_up_color,m_Human_up_color,1.0f };

	//住民振り分けDOWN画像用
	float down[4] = { m_Human_down_color,m_Human_down_color,m_Human_down_color,1.0f };

	//ミサイルボタン用
	float missile[4] = { m_Mis_Button_color,m_Mis_Button_color,m_Mis_Button_color,1.0f };

	//武器ポッドボタン用
	float equip[4] = { m_Equ_Button_color,m_Equ_Button_color,m_Equ_Button_color,1.0f };

	//エラーメッセージ用
	float error[4] = { 1.0f,0.0f,0.0f,m_alpha };

	//▽フォント準備
	//研究所レベル用
	wchar_t Ins[10];								 //10文字分格納可能な文字配列を宣言(99レベル以上はいかないと想定した文字分)
	swprintf_s(Ins, L"研究所 Lv.%d", g_Ins_Level);//その文字配列に文字データを入れる

	//残り住民数用
	wchar_t human_remain[12];						 //12文字分格納可能な文字配列を宣言(最大値は999999)
	swprintf_s(human_remain, L"残り %6d 人", g_Remain_num);//その文字配列に文字データを入れる

	//研究員の住民数用
	wchar_t Research_num[9];						 //9文字分格納可能な文字配列を4つ宣言(それぞれ最大値は999999)
	swprintf_s(Research_num, L"%6d 人", g_Research_num);//その文字配列に文字データを入れる


	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

	//施設ウインドウ(兵舎、研究所、倉庫)が開いてない時に表示するグラフィック
	if (window_start_manage == Default || window_start_manage == BackButton)
	{
		//▼研究所表示 
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 75.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 460.0f;
		dst.m_left = 10.0f;
		dst.m_right = 390.0f;
		dst.m_bottom = 690.0f;
		Draw::Draw(3, &src, &dst, ins, 0.0f);

		//施設紹介ウインドウ表示管理フラグがtrueの時、描画。
		if (m_introduce_f == true)
		{
			//▼施設紹介ウインドウ表示
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 64.0f;
			src.m_bottom = 64.0f;

			dst.m_top = m_mou_y - 50.0f;
			dst.m_left = m_mou_x - 120.0f;
			dst.m_right = m_mou_x + 110.0f;
			dst.m_bottom = m_mou_y - 10.0f;
			Draw::Draw(21, &src, &dst, ins, 0.0f);//灰色のウインドウにする為"ins"にしている。

			//▼フォント表示
			//研究所レベル
			Font::StrDraw(Ins, m_mou_x - 95.0f, m_mou_y - 45.0f, 30.0f, white);
		}
	}
	
	//研究所ウインドウ開いている際に表示するグラフィック
	else if (window_start_manage == Institute)
	{
		//▼灰色ウインドウ表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1160.0f;
		src.m_bottom = 660.0f;

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

		//▼研究所表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 75.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 150.0f;
		dst.m_left = 100.0f;
		dst.m_right = 400.0f;
		dst.m_bottom = 350.0f;
		Draw::Draw(3, &src, &dst, white, 0.0f);

		//▼研究所LVUP表示
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

		dst.m_top = 235.0f;
		dst.m_left = 750.0f;
		dst.m_right = 1160.0f;
		dst.m_bottom = 305.0f;
		Draw::Draw(21, &src, &dst, white, 0.0f);

		//▼研究所振り分けUP表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 120.0f;
		dst.m_left = 700.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 220.0f;
		Draw::Draw(23, &src, &dst, up, 0.0f);

		//▼研究所振り分けDOWN表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 120.0f;
		dst.m_left = 810.0f;
		dst.m_right = 910.0f;
		dst.m_bottom = 220.0f;
		Draw::Draw(24, &src, &dst, down, 0.0f);

		//▼研究員の住民数ウインドウ表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 140.0f;
		dst.m_left = 930.0f;
		dst.m_right = 1150.0f;
		dst.m_bottom = 200.0f;
		Draw::Draw(21, &src, &dst, white, 0.0f);

		//▼ミサイルボタン表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 269.0f;
		src.m_bottom = 96.0f;

		dst.m_top = 330.0f;
		dst.m_left = 520.0f;
		dst.m_right = 1130.0f;
		dst.m_bottom = 480.0f;
		Draw::Draw(25, &src, &dst, missile, 0.0f);

		//▼武器ポッドボタン表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 269.0f;
		src.m_bottom = 96.0f;

		dst.m_top = 500.0f;
		dst.m_left = 520.0f;
		dst.m_right = 1130.0f;
		dst.m_bottom = 650.0f;
		Draw::Draw(26, &src, &dst, equip, 0.0f);

		//▼フォント表示
		//研究所レベル
		Font::StrDraw(Ins, 105.0f, 95.0f, 50.0f, white);

		//残り住民数
		Font::StrDraw(human_remain, 780.0f, 245.0f, 50.0f, black);

		//研究員の住民数
		Font::StrDraw(Research_num, 950.0f, 150.0f, 40.0f, black);

		Font::StrDraw(L"研究所レベルＵＰ", 40.0f, 370.0f, 50.0f, white);

		Font::StrDraw(L"住民振り分け", 620.0f, 45.0f, 60.0f, white);

		Font::StrDraw(L"研究員", 505.0f, 145.0f, 55.0f, blue);

		Font::StrDraw(L"▼レベルUP条件", 175.0f, 440.0f, 25.0f, black);
		Font::StrDraw(L"α版では", 175.0f, 470.0f, 25.0f, black);
		Font::StrDraw(L"レベルUP出来ません。", 175.0f, 500.0f, 25.0f, black);

		//エラーメッセージ
		Font::StrDraw(m_error, m_mou_x - 110.0f, m_mou_y - 45.0f, 30.0f, error);
	}
	
	//ミサイルウインドウ開いている際に表示するグラフィック
	else if (window_start_manage == Missile)
	{
		//▽研究所ウインドウの上に開いているように見せるため、
		//ダミーの研究所ウインドウのグラフィックを描画する。

		//▼灰色ウインドウ表示(ダミー研究所ウインドウ用)
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1160.0f;
		src.m_bottom = 660.0f;

		dst.m_top = 20.0f;
		dst.m_left = 20.0f;
		dst.m_right = 1180.0f;
		dst.m_bottom = 680.0f;
		Draw::Draw(20, &src, &dst, white, 0.0f);

		//▼戻るボタン表示(ダミー研究所ウインドウ用)
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 30.0f;
		dst.m_left = 30.0f;
		dst.m_right = 80.0f;
		dst.m_bottom = 80.0f;
		Draw::Draw(1, &src, &dst, back, 0.0f);

		//▼研究所LVUP表示(ダミー研究所ウインドウ用)
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 48.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 470.0f;
		dst.m_left = 30.0f;
		dst.m_right = 150.0f;
		dst.m_bottom = 620.0f;
		Draw::Draw(22, &src, &dst, Lvup, 0.0f);

		//▼レベルUP条件ウインドウ表示(ダミー研究所ウインドウ用)
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 420.0f;
		dst.m_left = 150.0f;
		dst.m_right = 450.0f;
		dst.m_bottom = 670.0f;
		Draw::Draw(21, &src, &dst, white, 0.0f);


		//▽以下はミサイルウインドウで描画するもの

		//▼灰色ウインドウ表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1160.0f;
		src.m_bottom = 660.0f;

		dst.m_top = 40.0f;
		dst.m_left = 40.0f;
		dst.m_right = 1160.0f;
		dst.m_bottom = 660.0f;
		Draw::Draw(20, &src, &dst, white, 0.0f);

		//▼戻るボタン表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 50.0f;
		dst.m_left = 50.0f;
		dst.m_right = 100.0f;
		dst.m_bottom = 100.0f;
		Draw::Draw(1, &src, &dst, back, 0.0f);

		//▼ミサイル表示 
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 80.0f;
		src.m_bottom = 82.0f;

		dst.m_top = 150.0f;
		dst.m_left = 100.0f;
		dst.m_right = 400.0f;
		dst.m_bottom = 350.0f;
		Draw::Draw(4, &src, &dst, white, 0.0f);
	}

	//武器ポッドウインドウ開いている際に表示するグラフィック
	else if (window_start_manage == Equipment)
	{
		//▽研究所ウインドウの上に開いているように見せるため、
		//ダミーの研究所ウインドウのグラフィックを描画する。

		//▼灰色ウインドウ表示(ダミー研究所ウインドウ用)
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1160.0f;
		src.m_bottom = 660.0f;

		dst.m_top = 20.0f;
		dst.m_left = 20.0f;
		dst.m_right = 1180.0f;
		dst.m_bottom = 680.0f;
		Draw::Draw(20, &src, &dst, white, 0.0f);

		//▼戻るボタン表示(ダミー研究所ウインドウ用)
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 30.0f;
		dst.m_left = 30.0f;
		dst.m_right = 80.0f;
		dst.m_bottom = 80.0f;
		Draw::Draw(1, &src, &dst, back, 0.0f);

		//▼研究所LVUP表示(ダミー研究所ウインドウ用)
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 48.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 470.0f;
		dst.m_left = 30.0f;
		dst.m_right = 150.0f;
		dst.m_bottom = 620.0f;
		Draw::Draw(22, &src, &dst, Lvup, 0.0f);

		//▼レベルUP条件ウインドウ表示(ダミー研究所ウインドウ用)
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 420.0f;
		dst.m_left = 150.0f;
		dst.m_right = 450.0f;
		dst.m_bottom = 670.0f;
		Draw::Draw(21, &src, &dst, white, 0.0f);


		//▽以下は武器ポッドウインドウで描画するもの

		//▼灰色ウインドウ表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1160.0f;
		src.m_bottom = 660.0f;

		dst.m_top = 40.0f;
		dst.m_left = 40.0f;
		dst.m_right = 1160.0f;
		dst.m_bottom = 660.0f;
		Draw::Draw(20, &src, &dst, white, 0.0f);

		//▼戻るボタン表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 50.0f;
		dst.m_left = 50.0f;
		dst.m_right = 100.0f;
		dst.m_bottom = 100.0f;
		Draw::Draw(1, &src, &dst, back, 0.0f);
	}



	//デバッグ用仮マウス位置表示
	wchar_t str[256];
	swprintf_s(str, L"x=%f,y=%f", m_mou_x, m_mou_y);
	Font::StrDraw(str, 20, 20, 12, white);
}

