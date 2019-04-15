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
	m_Mis_Button_color = INI_COLOR;
	m_Equ_Button_color = INI_COLOR;

	for (int i = 0; i < 15; i++)
	{
		m_Equ_pic_color[i] = INI_COLOR;//全ての要素の値をINI_COLORで初期化している
	}

	m_mou_x = 0.0f;
	m_mou_y = 0.0f;
	m_mou_r = false;
	m_mou_l = false;
	m_introduce_f = false;
	m_key_lf = false;
	m_message_red_color = INI_COLOR;
	m_message_green_color = INI_COLOR;
	m_message_blue_color = INI_COLOR;
	m_alpha = INI_ALPHA;

	//▼ミサイルリキャストタイム(RCT)設定
	m_Mis_recast_time[0] = 5.0f;//ミサイルリキャストレベル(RCLv)が0の時のRCT(初期レベル)
	m_Mis_recast_time[1] = 4.2f;//RCLvが1の時のRCT
	m_Mis_recast_time[2] = 3.4f;//RCLvが2の時のRCT
	m_Mis_recast_time[3] = 2.6f;//RCLvが3の時のRCT
	m_Mis_recast_time[4] = 1.8f;//RCLvが4の時のRCT(最大レベル)

	//▼ミサイルリキャストの次のLVUPに必要な研究所レベル設定
	m_Mis_recast_next_Ins_Lv[0] = 1; //ミサイルリキャストレベル(RCLv)が0の時の必要研究所レベル
	m_Mis_recast_next_Ins_Lv[1] = 3; //RCLvが1の時の必要研究所レベル
	m_Mis_recast_next_Ins_Lv[2] = 6; //RCLvが2の時の必要研究所レベル
	m_Mis_recast_next_Ins_Lv[3] = 10; //RCLvが3の時の必要研究所レベル

	//▼ミサイルリキャストの次のLVUPに必要な研究員の住民数設定
	m_Mis_recast_next_Hum_num[0] = 100;  //ミサイルリキャストレベル(RCLv)が0の時の必要研究員数
	m_Mis_recast_next_Hum_num[1] = 1000; //RCLvが1の時の必要研究員数
	m_Mis_recast_next_Hum_num[2] = 5000; //RCLvが2の時の必要研究員数
	m_Mis_recast_next_Hum_num[3] = 10000;//RCLvが3の時の必要研究員数
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
				//前シーン(ミサイルウインドウ等)から右クリック押したままの状態では入力出来ないようにしている
				if (m_key_rf == true)
				{
					//ウインドウ閉じた後、続けて戻るボタンを入力しないようにstatic変数にfalseを入れて制御
					m_key_rf = false;

					//エラーメッセージを非表示にするため、透過度を0.0fにする
					m_alpha = 0.0f;

					//"どのウインドウも開いていない状態"フラグを立てる
					window_start_manage = Default;
				}
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
			m_key_rf = true;
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

					//▼ミサイルリキャストレベルUPチェック
					//レベルUP条件を満たしているかチェックし、
					//満たしていればレベルUPさせる。
					if (g_Mis_Recast_Level == MIS_MAX_LV - 1)
					{
						;//最大レベルの時はこのチェック処理を飛ばす
					}
					else if (g_Ins_Level >= m_Mis_recast_next_Ins_Lv[g_Mis_Recast_Level] &&
						g_Research_num >= m_Mis_recast_next_Hum_num[g_Mis_Recast_Level])
					{
						g_Mis_Recast_Level++;//条件を満たしているのでレベルUP
					}
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

					//▼ミサイルリキャストレベルDOWNチェック
					//レベルDOWN条件を満たしているかチェックし、
					//満たしていればレベルDOWNさせる。
					if (g_Mis_Recast_Level == 0)
					{
						;//初期レベルの時はこのチェック処理を飛ばす
					}
					else if (g_Research_num < m_Mis_recast_next_Hum_num[g_Mis_Recast_Level - 1])
					{
						g_Mis_Recast_Level--;//条件を満たしているのでレベルDOWN
					}
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
	//▼ミサイルウインドウ、もしくは武器ポッドウインドウ表示時の処理
	else if (window_start_manage == Missile || window_start_manage == Equipment)
	{
		//戻るボタン左クリック、もしくは右クリック(どこでも)する事でこのウインドウを閉じる
		if (50 < m_mou_x && m_mou_x < 100 && 50 < m_mou_y && m_mou_y < 100 || m_mou_r == true)
		{
			m_Back_Button_color = 0.7f;

			//▼クリックされたらフラグを立て、このウインドウを閉じる
			//右クリック入力時
			if (m_mou_r == true)
			{
				//ウインドウ閉じた後、続けて戻るボタンを入力しないようにstatic変数にfalseを入れて制御
				m_key_rf = false;

				//武器必要素材&人数メッセージを非表示にするため、透過度を0.0fにする
				m_alpha = 0.0f;

				//"研究所ウインドウを開いている状態"フラグを立てる
				window_start_manage = Institute;
			}
			//左クリック入力時
			else if (m_mou_l == true)
			{
				//左クリック押したままの状態では入力出来ないようにしている
				if (m_key_lf == true)
				{
					m_key_lf = false;

					//武器必要素材&人数メッセージを非表示にするため、透過度を0.0fにする
					m_alpha = 0.0f;

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
			m_Back_Button_color = 1.0f;
		}


		//武器ポッドウインドウを開いていた場合、更に以下の処理を行う
		if (window_start_manage == Equipment)
		{
			//パワー武器Lv.1
			if (277 < m_mou_x && m_mou_x < 407 && 207 < m_mou_y && m_mou_y < 336)
			{
				m_alpha = 1.0f;
			}

			//パワー武器Lv.2
			else if (277 < m_mou_x && m_mou_x < 407 && 355 < m_mou_y && m_mou_y < 483)
			{
				m_alpha = 1.0f;
			}

			//パワー武器Lv.3
			else if (277 < m_mou_x && m_mou_x < 407 && 503 < m_mou_y && m_mou_y < 632)
			{
				m_alpha = 1.0f;
			}

			//ディフェンス武器Lv.1
			else if (445 < m_mou_x && m_mou_x < 575 && 207 < m_mou_y && m_mou_y < 336)
			{
				m_alpha = 1.0f;
			}

			//ディフェンス武器Lv.2
			else if (445 < m_mou_x && m_mou_x < 575 && 355 < m_mou_y && m_mou_y < 483)
			{
				m_alpha = 1.0f;
			}

			//ディフェンス武器Lv.3
			else if (445 < m_mou_x && m_mou_x < 575 && 503 < m_mou_y && m_mou_y < 632)
			{
				m_alpha = 1.0f;
			}

			//スピード武器Lv.1
			else if (614 < m_mou_x && m_mou_x < 744 && 207 < m_mou_y && m_mou_y < 336)
			{
				m_alpha = 1.0f;
			}

			//スピード武器Lv.2
			else if (614 < m_mou_x && m_mou_x < 744 && 355 < m_mou_y && m_mou_y < 483)
			{
				m_alpha = 1.0f;
			}

			//スピード武器Lv.3
			else if (614 < m_mou_x && m_mou_x < 744 && 503 < m_mou_y && m_mou_y < 632)
			{
				m_alpha = 1.0f;
			}

			//バランス武器Lv.1
			else if (783 < m_mou_x && m_mou_x < 913 && 207 < m_mou_y && m_mou_y < 336)
			{
				m_alpha = 1.0f;
			}

			//バランス武器Lv.2
			else if (783 < m_mou_x && m_mou_x < 913 && 355 < m_mou_y && m_mou_y < 483)
			{
				m_alpha = 1.0f;
			}

			//バランス武器Lv.3
			else if (783 < m_mou_x && m_mou_x < 913 && 503 < m_mou_y && m_mou_y < 632)
			{
				m_alpha = 1.0f;
			}

			//ポッドLv.1
			else if (952 < m_mou_x && m_mou_x < 1081 && 207 < m_mou_y && m_mou_y < 336)
			{
				m_alpha = 1.0f;
			}

			//ポッドLv.2
			else if (952 < m_mou_x && m_mou_x < 1081 && 355 < m_mou_y && m_mou_y < 483)
			{
				m_alpha = 1.0f;
			}

			//ポッドLv.3
			else if (952 < m_mou_x && m_mou_x < 1081 && 503 < m_mou_y && m_mou_y < 632)
			{
				m_alpha = 1.0f;
			}

			//上記の範囲外にマウスカーソルがある場合、
			//武器必要素材&人数メッセージを非表示にする
			else
			{
				m_alpha = 0.0f;
			}
		}


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
	//赤色
	float red[4] = { 1.0f,0.0f,0.0f,1.0f };

	//青色
	float blue[4] = { 0.0f,0.0f,1.0f,1.0f };

	//青色(若干緑入り)
	float blue2[4] = { 0.0f,0.3f,0.9f,1.0f };

	//緑色
	float green[4] = { 0.0f,1.0f,0.0f,1.0f };

	//黄色
	float yellow[4] = { 1.0f,1.0f,0.0f,1.0f };

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

	//武器ポッド画像集用
	float equip_pic[15][4] =
	{
		{ m_Equ_pic_color[0],m_Equ_pic_color[0],m_Equ_pic_color[0],1.0f },
		{ m_Equ_pic_color[1],m_Equ_pic_color[1],m_Equ_pic_color[1],1.0f },
		{ m_Equ_pic_color[2],m_Equ_pic_color[2],m_Equ_pic_color[2],1.0f },
		{ m_Equ_pic_color[3],m_Equ_pic_color[3],m_Equ_pic_color[3],1.0f },
		{ m_Equ_pic_color[4],m_Equ_pic_color[4],m_Equ_pic_color[4],1.0f },
		{ m_Equ_pic_color[5],m_Equ_pic_color[5],m_Equ_pic_color[5],1.0f },
		{ m_Equ_pic_color[6],m_Equ_pic_color[6],m_Equ_pic_color[6],1.0f },
		{ m_Equ_pic_color[7],m_Equ_pic_color[7],m_Equ_pic_color[7],1.0f },
		{ m_Equ_pic_color[8],m_Equ_pic_color[8],m_Equ_pic_color[8],1.0f },
		{ m_Equ_pic_color[9],m_Equ_pic_color[9],m_Equ_pic_color[9],1.0f },
		{ m_Equ_pic_color[10],m_Equ_pic_color[10],m_Equ_pic_color[10],1.0f },
		{ m_Equ_pic_color[11],m_Equ_pic_color[11],m_Equ_pic_color[11],1.0f },
		{ m_Equ_pic_color[12],m_Equ_pic_color[12],m_Equ_pic_color[12],1.0f },
		{ m_Equ_pic_color[13],m_Equ_pic_color[13],m_Equ_pic_color[13],1.0f },
		{ m_Equ_pic_color[14],m_Equ_pic_color[14],m_Equ_pic_color[14],1.0f },
	};

	//武器必要素材&人数フォント用
	float Wep_message_font[4] = { 0.0f,0.0f,0.0f,m_alpha };

	//武器必要素材&人数ウインドウ用
	float Wep_message_window[4] = { 1.0f,1.0f,1.0f,m_alpha };

	//簡易メッセージ(エラーメッセージ、レベルUP表示等)用
	float message[4] = { m_message_red_color,m_message_green_color,m_message_blue_color,m_alpha };

	//▽フォント準備
	//研究所レベル用
	wchar_t Ins[10];								 //10文字分格納可能な文字配列を宣言(99レベル以上はいかないと想定した文字分)
	swprintf_s(Ins, L"研究所 Lv.%d", g_Ins_Level);//その文字配列に文字データを入れる

	//残り住民数用
	wchar_t human_remain[12];						 //12文字分格納可能な文字配列を宣言(最大値は999999)
	swprintf_s(human_remain, L"残り %6d 人", g_Remain_num);//その文字配列に文字データを入れる

	//研究員の住民数用
	wchar_t Research_num[9];						 //9文字分格納可能な文字配列を宣言(最大値は999999)
	swprintf_s(Research_num, L"%6d 人", g_Research_num);//その文字配列に文字データを入れる

	//ミサイルリキャストタイム用
	wchar_t Mis_recast[7];							 //7文字分格納可能な文字配列を宣言(最大値は99.9f)
	swprintf_s(Mis_recast, L"%4.1f s", m_Mis_recast_time[g_Mis_Recast_Level]);//その文字配列に文字データを入れる

	//ミサイルリキャスト次のLVUPに関する情報用
	wchar_t Next_Lvup[26];							 //26文字分格納可能な文字配列を宣言
	//最大レベルの時の処理
	if (g_Mis_Recast_Level == MIS_MAX_LV - 1)
	{
		swprintf_s(Next_Lvup, L"これ以上レベルUP出来ません");//その文字配列に文字データを入れる
	}
	//それ以外のレベルの時の処理
	else
	{
		swprintf_s(Next_Lvup, L"Lv.%2d & %6d 人 = %4.1f s", 
			m_Mis_recast_next_Ins_Lv[g_Mis_Recast_Level], 
			m_Mis_recast_next_Hum_num[g_Mis_Recast_Level], 
			m_Mis_recast_time[g_Mis_Recast_Level + 1]);//その文字配列に文字データを入れる
	}
	

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

		Font::StrDraw(L"研究員", 505.0f, 145.0f, 55.0f, blue2);

		Font::StrDraw(L"▼レベルUP条件", 175.0f, 440.0f, 25.0f, black);
		Font::StrDraw(L"α版では", 175.0f, 470.0f, 25.0f, red);
		Font::StrDraw(L"レベルUP出来ません。", 175.0f, 500.0f, 25.0f, red);

		//簡易メッセージ(エラーメッセージ、レベルUP表示等)
		Font::StrDraw(m_message, m_mou_x - 110.0f, m_mou_y - 45.0f, 30.0f, message);
	}
	
	//ミサイルウインドウ、もしくは武器ポッドウインドウ開いている際に表示するグラフィック
	else if (window_start_manage == Missile || window_start_manage == Equipment)
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
		Draw::Draw(1, &src, &dst, white, 0.0f);

		//▼研究所LVUP表示(ダミー研究所ウインドウ用)
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 48.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 470.0f;
		dst.m_left = 30.0f;
		dst.m_right = 150.0f;
		dst.m_bottom = 620.0f;
		Draw::Draw(22, &src, &dst, white, 0.0f);

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


		//▽以下はミサイルウインドウ、武器ポッドウインドウのどちらでも描画

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


		//▽以下はミサイルウインドウで描画するもの
		if (window_start_manage == Missile)
		{
			//▼ミサイル表示 
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 80.0f;
			src.m_bottom = 82.0f;

			dst.m_top = 325.0f;
			dst.m_left = 75.0f;
			dst.m_right = 375.0f;
			dst.m_bottom = 575.0f;
			Draw::Draw(4, &src, &dst, white, 0.0f);

			//▼メッセージウインドウを3つ表示
			for (int i = 0; i < 3; i++)
			{
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 64.0f;
				src.m_bottom = 64.0f;

				dst.m_top = 75.0f + 190.0f * i;
				dst.m_left = 400.0f;
				dst.m_right = 1150.0f;
				dst.m_bottom = 255.0f + 190.0f * i;
				Draw::Draw(21, &src, &dst, white, 0.0f);
			}

			//▼フォント表示
			//研究所レベル
			Font::StrDraw(Ins, 590.0f, 95.0f, 65.0f, black);

			//研究員の住民数
			Font::StrDraw(L"研究員", 510.0f, 175.0f, 65.0f, black);
			Font::StrDraw(Research_num, 750.0f, 175.0f, 65.0f, black);

			//ミサイルリキャストタイム
			Font::StrDraw(L"再生産スピード(リキャスト)", 455.0f, 285.0f, 50.0f, black);
			Font::StrDraw(Mis_recast, 660.0f, 350.0f, 75.0f, black);

			//ミサイルリキャスト次のLVUPに関する情報
			Font::StrDraw(L"NEXT LV UP", 740.0f, 475.0f, 65.0f, black);
			Font::StrDraw(Next_Lvup, 450.0f, 560.0f, 50.0f, black);
		}

		//▽以下は武器ポッドウインドウで描画するもの
		else // (window_start_manage == Equipment)
		{
			//▼武器ポッド画像集を表示
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					src.m_top = 0.0f;
					src.m_left = 0.0f;
					src.m_right = 64.0f;
					src.m_bottom = 64.0f;

					dst.m_top = 210.0f + j * 150.0f;
					dst.m_left = 280.0f + i * 170.0f;
					dst.m_right = 410.0f + i * 170.0f;
					dst.m_bottom = 340.0f + j * 150.0f;
					Draw::Draw(49 + j + i * 3, &src, &dst, equip_pic[j + i * 3], 0.0f);
				}
			}

			//▼フォント表示
			//武器レベル
			wchar_t weapon_Lv[5];
			for (int i = 0; i < 3; i++)
			{
				swprintf_s(weapon_Lv, L"Lv.%d", i + 1);
				Font::StrDraw(weapon_Lv, 80.0f, 250.0f + i * 150.0f, 50.0f, white);
			}

			//各タイプ(パワー、スピード等)、ポッドのフォント
			Font::StrDraw(L"パワー", 285.0f, 98.0f, 40.0f, red);

			Font::StrDraw(L"ディフェンス", 440.0f, 105.0f, 25.0f, blue);

			Font::StrDraw(L"スピード", 615.0f, 100.0f, 35.0f, green);

			Font::StrDraw(L"バランス", 785.0f, 100.0f, 35.0f, white);

			Font::StrDraw(L"ポッド", 965.0f, 97.0f, 40.0f, yellow);

			//▼武器必要素材&人数メッセージ表示
			//ウインドウ表示 
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 64.0f;
			src.m_bottom = 64.0f;

			dst.m_top = m_mou_y - 210.0f;
			dst.m_left = m_mou_x - 150.0f;
			dst.m_right = m_mou_x + 150.0f;
			dst.m_bottom = m_mou_y + 0.0f;
			Draw::Draw(21, &src, &dst, Wep_message_window, 0.0f);
		}
	}

	

	//デバッグ用仮マウス位置表示
	wchar_t str[256];
	swprintf_s(str, L"x=%f,y=%f", m_mou_x, m_mou_y);
	Font::StrDraw(str, 20.0f, 20.0f, 12.0f, white);
}

