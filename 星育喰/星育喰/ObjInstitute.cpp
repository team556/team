//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\Audio.h"

#include "GameHead.h"

//使用するネームスペース
using namespace GameL;

//マクロ
#define INI_ALPHA (0.0f) //透過度(アルファ値)の初期値
#define INI_COLOR (0.9f) //全カラー明度の初期値(アイコン未選択中のカラー)
#define LABO_LV_1 (1)//研究所レベルマクロ定義
#define LABO_LV_2 (2)//研究所レベルマクロ定義
#define LABO_LV_3 (3)//研究所レベルマクロ定義

#define MIS_LV_1 (3.0f)
#define MIS_LV_2 (2.5f)
#define MIS_LV_3 (2.0f)
#define MIS_LV_4 (1.5f)
#define MIS_LV_5 (1.0f)//1.0未満にはしないでください

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
	m_Yes_Button_color = 0.0f;
	m_No_Button_color = 0.0f;

	//▼武器ポッド画像集全てのカラー明度を0.1f(黒色)で初期化
	for (int i = 0; i < 15; i++)
	{
		m_Equ_pic_red_color[i] = 0.1f;
		m_Equ_pic_green_color[i] = 0.1f;
		m_Equ_pic_blue_color[i] = 0.1f;
	}
	//▼現在の各武器、ポッドレベルに応じて
	//武器ポッド画像集のカラーを以下のように設定していく。
	//「装備不可」…………………0.1f(黒色)
	//「レベルUP済(装備可)」……0.5f(灰色)
	//「装備中」……………………1.0f(白色)
	for (int i = 0; i < 15; i++)
	{
		//下記のif文(各武器レベルの最大到達度)に入るまで、
		//レベル1から順に灰色を設定していく。
		m_Equ_pic_red_color[i] = 0.5f;
		m_Equ_pic_green_color[i] = 0.5f;
		m_Equ_pic_blue_color[i] = 0.5f;
		
		//パワー武器レベルの最大到達度
		if (i == g_Pow_equip_Lv_achieve - 1)
		{
			//現在のパワー武器レベルのカラーを白色に設定する
			m_Equ_pic_red_color[g_Pow_equip_Level - 1] = 1.0f;
			m_Equ_pic_green_color[g_Pow_equip_Level - 1] = 1.0f;
			m_Equ_pic_blue_color[g_Pow_equip_Level - 1] = 1.0f;
			
			i = 2;//ディフェンス武器レベルのカラー設定処理を開始させる
		}
		//ディフェンス武器レベルの最大到達度
		else if (i == g_Def_equip_Lv_achieve + 2)
		{
			//現在のディフェンス武器レベルのカラーを白色に設定する
			m_Equ_pic_red_color[g_Def_equip_Level + 2] = 1.0f;
			m_Equ_pic_green_color[g_Def_equip_Level + 2] = 1.0f;
			m_Equ_pic_blue_color[g_Def_equip_Level + 2] = 1.0f;
			
			i = 5;//スピード武器レベルのカラー設定処理を開始させる
		}
		//スピード武器レベルの最大到達度
		else if (i == g_Spe_equip_Lv_achieve + 5)
		{
			//現在のスピード武器レベルのカラーを白色に設定する
			m_Equ_pic_red_color[g_Spe_equip_Level + 5] = 1.0f;
			m_Equ_pic_green_color[g_Spe_equip_Level + 5] = 1.0f;
			m_Equ_pic_blue_color[g_Spe_equip_Level + 5] = 1.0f;
			
			i = 8;//バランス武器レベルのカラー設定処理を開始させる
		}
		//バランス武器レベルの最大到達度
		else if (i == g_Bal_equip_Lv_achieve + 8)
		{
			//現在のバランス武器レベルのカラーを白色に設定する
			m_Equ_pic_red_color[g_Bal_equip_Level + 8] = 1.0f;
			m_Equ_pic_green_color[g_Bal_equip_Level + 8] = 1.0f;
			m_Equ_pic_blue_color[g_Bal_equip_Level + 8] = 1.0f;

			i = 11;//ポッドレベルのカラー設定処理を開始させる
		}
		//ポッドレベルの最大到達度
		else if(i == g_Pod_equip_Lv_achieve + 11)
		{
			//現在のポッドレベルのカラーを白色に設定する
			m_Equ_pic_red_color[g_Bal_equip_Level + 11] = 1.0f;
			m_Equ_pic_green_color[g_Bal_equip_Level + 11] = 1.0f;
			m_Equ_pic_blue_color[g_Bal_equip_Level + 11] = 1.0f;

			break;//カラー設定処理を終了させる
		}
	}


	m_Equ_message_window_x_size = 0.0f;
	m_Equ_message_window_y_size = 0.0f;

	m_mou_x = 0.0f;
	m_mou_y = 0.0f;
	m_mou_r = false;
	m_mou_l = false;
	m_introduce_f = false;
	m_finalcheck_f = false;
	m_key_lf = false;
	m_message_red_color = INI_COLOR;
	m_message_green_color = INI_COLOR;
	m_message_blue_color = INI_COLOR;
	m_alpha = INI_ALPHA;

	//-----------------------------------------------------------------------------------------------------

	//▼ミサイルリキャストタイム(RCT)設定
	m_Mis_recast_time[0] = MIS_LV_1;//ミサイルリキャストレベル(RCLv)が0の時のRCT(初期レベル)
	m_Mis_recast_time[1] = MIS_LV_2;//RCLvが1の時のRCT
	m_Mis_recast_time[2] = MIS_LV_3;//RCLvが2の時のRCT
	m_Mis_recast_time[3] = MIS_LV_4;//RCLvが3の時のRCT
	m_Mis_recast_time[4] = MIS_LV_5;//RCLvが4の時のRCT(最大レベル)

	//▼ミサイルリキャストの次のLVUPに必要な研究所レベル設定
	m_Mis_recast_next_Ins_Lv[0] = LABO_LV_1; //ミサイルリキャストレベル(RCLv)が0の時の必要研究所レベル
	m_Mis_recast_next_Ins_Lv[1] = LABO_LV_2; //RCLvが1の時の必要研究所レベル
	m_Mis_recast_next_Ins_Lv[2] = LABO_LV_3; //RCLvが2の時の必要研究所レベル
	m_Mis_recast_next_Ins_Lv[3] = LABO_LV_3; //RCLvが3の時の必要研究所レベル

	//▼ミサイルリキャストの次のLVUPに必要な研究員の住民数設定
	m_Mis_recast_next_Hum_num[0] = 100;  //ミサイルリキャストレベル(RCLv)が0の時の必要研究員数
	m_Mis_recast_next_Hum_num[1] = 600; //RCLvが1の時の必要研究員数
	m_Mis_recast_next_Hum_num[2] = 2000; //RCLvが2の時の必要研究員数
	m_Mis_recast_next_Hum_num[3] = 4500;//RCLvが3の時の必要研究員数

	//-----------------------------------------------------------------------------------------------------

	//▼各武器、ポッドの次のLVUPに必要な研究員の住民数設定
	//▽パワー武器
	m_Equ_next_Hum_num[0][0] = 100;  //レベルが1の時の必要研究員数
	m_Equ_next_Hum_num[0][1] = 1000; //レベルが2の時の必要研究員数
	//▽ディフェンス武器
	m_Equ_next_Hum_num[1][0] = 200;  //レベルが1の時の必要研究員数
	m_Equ_next_Hum_num[1][1] = 1000; //レベルが2の時の必要研究員数
	//▽スピード武器
	m_Equ_next_Hum_num[2][0] = 300;  //レベルが1の時の必要研究員数
	m_Equ_next_Hum_num[2][1] = 1000; //レベルが2の時の必要研究員数
	//▽バランス武器
	m_Equ_next_Hum_num[3][0] = 500;  //レベルが1の時の必要研究員数
	m_Equ_next_Hum_num[3][1] = 1000; //レベルが2の時の必要研究員数
	//▽ポッド
	m_Equ_next_Hum_num[4][0] = 300;  //レベルが1の時の必要研究員数
	m_Equ_next_Hum_num[4][1] = 1000; //レベルが2の時の必要研究員数

	//▼各武器、ポッドの次のLVUPに必要な素材の名前設定
	//▽パワー武器
	swprintf_s(m_Equ_next_Mat_name[0][0], L"鉄");			 //レベルが1の時の必要素材名
	swprintf_s(m_Equ_next_Mat_name[0][1], L"ガス");		 //レベルが2の時の必要素材名
	//▽ディフェンス武器
	swprintf_s(m_Equ_next_Mat_name[1][0], L"鉄");			 //レベルが1の時の必要素材名
	swprintf_s(m_Equ_next_Mat_name[1][1], L"銀");		 //レベルが2の時の必要素材名
	//▽スピード武器
	swprintf_s(m_Equ_next_Mat_name[2][0], L"鉄");			//レベルが1の時の必要素材名
	swprintf_s(m_Equ_next_Mat_name[2][1], L"銀");		 //レベルが2の時の必要素材名
	//▽バランス武器
	swprintf_s(m_Equ_next_Mat_name[3][0], L"アルミニウム");		//レベルが1の時の必要素材名
	swprintf_s(m_Equ_next_Mat_name[3][1], L"ガス");	//レベルが2の時の必要素材名
	//▽ポッド武器
	swprintf_s(m_Equ_next_Mat_name[4][0], L"アルミニウム");	//レベルが1の時の必要素材名
	swprintf_s(m_Equ_next_Mat_name[4][1], L"レアメタル");		 //レベルが2の時の必要素材名

	//▼各武器、ポッドの次のLVUPに必要な素材種類設定と同時にその素材の所持数を代入する
	//※以下のように所持素材数を管理しているグローバル変数のアドレスを代入する事で素材の種類設定と所持数の代入をしている。
	//ただし現在は素材種類が確定していないため、仮でTEST用の物を入れている。後で適切なものに変更すべし。
	//▽パワー武器
	m_Equ_next_Mat_type[0][0] = &g_Iron_num;	//レベルが1の時の必要素材種類
	m_Equ_next_Mat_type[0][1] = &g_gus_num;	//レベルが2の時の必要素材種類
	//▽ディフェンス武器
	m_Equ_next_Mat_type[1][0] = &g_Iron_num;	//レベルが1の時の必要素材種類
	m_Equ_next_Mat_type[1][1] = &g_Silver_num;	//レベルが2の時の必要素材種類
	//▽スピード武器
	m_Equ_next_Mat_type[2][0] = &g_Iron_num;	//レベルが1の時の必要素材種類
	m_Equ_next_Mat_type[2][1] = &g_Silver_num;	//レベルが2の時の必要素材種類
	//▽バランス武器
	m_Equ_next_Mat_type[3][0] = &g_Aluminum_num;	//レベルが1の時の必要素材種類
	m_Equ_next_Mat_type[3][1] = &g_gus_num;	//レベルが2の時の必要素材種類
	//▽ポッド
	m_Equ_next_Mat_type[4][0] = &g_Aluminum_num;	//レベルが1の時の必要素材種類
	m_Equ_next_Mat_type[4][1] = &g_Raremetal_num;	//レベルが2の時の必要素材種類

	//▼各武器、ポッドの次のLVUPに必要な素材数設定
	//▽パワー武器
	m_Equ_next_Mat_num[0][0] = 30;	 //レベルが1の時の必要素材数
	m_Equ_next_Mat_num[0][1] = 20;  //レベルが2の時の必要素材数
	//▽ディフェンス武器
	m_Equ_next_Mat_num[1][0] = 30;  //レベルが1の時の必要素材数
	m_Equ_next_Mat_num[1][1] = 40; //レベルが2の時の必要素材数
	//▽スピード武器
	m_Equ_next_Mat_num[2][0] = 30;  //レベルが1の時の必要素材数
	m_Equ_next_Mat_num[2][1] = 25; //レベルが2の時の必要素材数
	//▽バランス武器
	m_Equ_next_Mat_num[3][0] = 30;  //レベルが1の時の必要素材数
	m_Equ_next_Mat_num[3][1] = 30; //レベルが2の時の必要素材数
	//▽ポッド
	m_Equ_next_Mat_num[4][0] = 30;  //レベルが1の時の必要素材数
	m_Equ_next_Mat_num[4][1] = 50;  //レベルが2の時の必要素材数

//-----------------------------------------------------------------------------------------------------

	//▼研究所の次のLVUPに必要なサイズ(HP)の住民数設定
	m_Facility_next_Size_num[0] = 5.0f;	//レベルが1の時の必要サイズ(HP)
	m_Facility_next_Size_num[1] = 20.0f;	//レベルが2の時の必要サイズ(HP)

	//▼研究所の次のLVUPに必要な素材の名前設定
	swprintf_s(m_Facility_next_Mat_name[0], L"鉄");//レベルが1の時の必要素材名
	swprintf_s(m_Facility_next_Mat_name[1], L"アルミニウム");//レベルが2の時の必要素材名

	//▼研究所の次のLVUPに必要な素材種類設定と同時にその素材の所持数を代入する
	//※以下のように所持素材数を管理しているグローバル変数のアドレスを代入する事で素材の種類設定と所持数の代入をしている。
	//ただし現在は素材種類が確定していないため、仮でTEST用の物を入れている。後で適切なものに変更すべし。
	m_Facility_next_Mat_type[0] = &g_Iron_num;	//レベルが1の時の必要素材種類
	m_Facility_next_Mat_type[1] = &g_Aluminum_num;	//レベルが2の時の必要素材種類

	//▼研究所の次のLVUPに必要な素材数設定
	m_Facility_next_Mat_num[0] = 10;	//レベルが1の時の必要素材数
	m_Facility_next_Mat_num[1] = 20;	//レベルが2の時の必要素材数



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
		//▼(研究所)最終確認ウインドウ表示時の処理
		if (m_finalcheck_f == true)
		{
			//最終確認[はい]ボタン
			if (410 < m_mou_x && m_mou_x < 502 && 407 < m_mou_y && m_mou_y < 450)
			{
				m_Yes_Button_color = 1.0f;

				//▼クリックされたら研究所レベルUP処理を行い、このウインドウを閉じる
				//左クリック入力時
				if (m_mou_l == true)
				{
					//左クリック押したままの状態では入力出来ないようにしている
					if (m_key_lf == true)
					{
						m_key_lf = false;

						//▽研究所レベルUP処理
						//サイズ(HP)消費処理
						g_Player_max_size -= m_Facility_next_Size_num[g_Ins_Level - 1];

						//素材消費処理
						*m_Facility_next_Mat_type[g_Ins_Level - 1] -= m_Facility_next_Mat_num[g_Ins_Level - 1];

						//研究所のレベルUP処理
						g_Ins_Level++;

						//▼ミサイルリキャストレベルUPチェック
						//レベルUP条件を満たしているかチェックし、
						//満たしていればレベルUPさせる。
						Missile_Lvup_check();//ミサイルリキャストレベルUPチェック関数を呼び出す

						m_Yes_Button_color = 0.0f;

						//最終確認ウインドウを非表示にする
						m_finalcheck_f = false;

						//選択音
						Audio::Start(1);
					}
				}
				else
				{
					m_key_lf = true;
				}
			}
			else
			{
				m_Yes_Button_color = 0.0f;
			}

			//最終確認[いいえ]ボタン
			if (648 < m_mou_x && m_mou_x < 789 && 407 < m_mou_y && m_mou_y < 450 || m_mou_r == true)
			{
				m_No_Button_color = 1.0f;

				//▼クリックされたら、このウインドウを閉じる
				//右クリック入力時
				if (m_mou_r == true)
				{
					//ウインドウ閉じた後、続けて戻るボタンを入力しないようにstatic変数にfalseを入れて制御
					m_key_rf = false;

					m_No_Button_color = 0.0f;

					//最終確認ウインドウを非表示にする
					m_finalcheck_f = false;

					//戻るボタン音
					Audio::Start(2);
				}
				//左クリック入力時
				else if (m_mou_l == true)
				{
					//左クリック押したままの状態では入力出来ないようにしている
					if (m_key_lf == true)
					{
						m_key_lf = false;

						m_No_Button_color = 0.0f;

						//最終確認ウインドウを非表示にする
						m_finalcheck_f = false;

						//戻るボタン音
						Audio::Start(2);
					}
				}
				else
				{
					m_key_lf = true;
				}
			}
			else
			{
				m_No_Button_color = 0.0f;
			}


			return;
		}

		//マウスカーソル上部に表示されるエラーメッセージを徐々に非表示にする
		if (m_alpha > 0.0f)
		{
			m_alpha -= 0.01f;
		}

		//戻るボタン左クリック、もしくは右クリック(どこでも)する事で研究所ウインドウを閉じる
		if (30 < m_mou_x && m_mou_x < 80 && 30 < m_mou_y && m_mou_y < 80 || m_mou_r == true)
		{
			m_Back_Button_color = 1.0f;

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

					//戻るボタン音
					Audio::Start(2);
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

					//戻るボタン音
					Audio::Start(2);
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
			m_Back_Button_color = INI_COLOR;
		}

		//研究所レベルUP
		if (30 < m_mou_x && m_mou_x < 148 && 465 < m_mou_y && m_mou_y < 610)
		{
			m_Ins_Lvup_color = 1.0f;

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

					//▼研究所レベルUP可能チェック処理
					if (g_Ins_Level == FACILITY_MAX_LV)
					{
						//▽レベルMAX時の処理
						//左クリックされたら簡易メッセージでレベルUP不可を伝える
						swprintf_s(m_message, L"LvUP出来ません");//文字配列に文字データを入れる

						//簡易メッセージのカラーを赤色にする
						m_message_red_color = 1.0f;
						m_message_green_color = 0.0f;
						m_message_blue_color = 0.0f;

						//簡易メッセージを表示する
						m_alpha = 1.0f;
					}
					else if (g_Player_max_size > m_Facility_next_Size_num[g_Ins_Level - 1] &&
						*m_Facility_next_Mat_type[g_Ins_Level - 1] >= m_Facility_next_Mat_num[g_Ins_Level - 1])
					{
						//▽レベルUP可能時の処理
						//左クリックされたらフラグを立て、最終確認ウインドウを開く
						m_finalcheck_f = true;//最終確認ウインドウを表示する

						//簡易メッセージを非表示にする
						m_alpha = 0.0f;

						m_Ins_Lvup_color = INI_COLOR;

						//レベルアップ音
						Audio::Start(1);

						return;
					}
					else
					{
						//▽レベルUP不可時の処理
						//左クリックされたら簡易メッセージでレベルUP不可を伝える
						swprintf_s(m_message, L"LvUP出来ません");//文字配列に文字データを入れる

						//簡易メッセージのカラーを赤色にする
						m_message_red_color = 1.0f;
						m_message_green_color = 0.0f;
						m_message_blue_color = 0.0f;

						//簡易メッセージを表示する
						m_alpha = 1.0f;
					}

					//選択音
					Audio::Start(1);
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
		else
		{
			m_Ins_Lvup_color = INI_COLOR;
		}

		//研究員住民振り分けUP
		if (695 < m_mou_x && m_mou_x < 793 && 118 < m_mou_y && m_mou_y < 218)
		{
			m_Human_up_color = 1.0f;

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
					Missile_Lvup_check();//ミサイルリキャストレベルUPチェック関数を呼び出す

					//▼武器ポッドレベルUPチェック
					//既にレベルUP済みの武器ポッドの現在の研究員数をチェックし、
					//装備可能な研究員数に達していれば、レベルUPさせる。
					//▽それぞれ武器ポッドレベルUPチェック関数を呼び出す
					g_Pow_equip_Level = Equip_Lvup_check(0, g_Pow_equip_Level, g_Pow_equip_Lv_achieve);
					g_Def_equip_Level = Equip_Lvup_check(1, g_Def_equip_Level, g_Def_equip_Lv_achieve);
					g_Spe_equip_Level = Equip_Lvup_check(2, g_Spe_equip_Level, g_Spe_equip_Lv_achieve);
					g_Bal_equip_Level = Equip_Lvup_check(3, g_Bal_equip_Level, g_Bal_equip_Lv_achieve);
					g_Pod_equip_Level = Equip_Lvup_check(4, g_Pod_equip_Level, g_Pod_equip_Lv_achieve);

					//振り分けボタン音
					Audio::Start(1);
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
		else
		{
			m_Human_up_color = INI_COLOR;
		}

		//研究員住民振り分けDOWN
		if (802 < m_mou_x && m_mou_x < 902 && 118 < m_mou_y && m_mou_y < 218)
		{
			m_Human_down_color = 1.0f;

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


						//▼ミサイルリキャストがレベルDOWNした事を簡易メッセージにて知らせる
						swprintf_s(m_message, L"ミサイルリキャストレベルDOWN…");//文字配列に文字データを入れる

						//リキャストレベルDOWNメッセージのカラーを水色にする
						m_message_red_color = 0.0f;
						m_message_green_color = 1.0f;
						m_message_blue_color = 1.0f;

						m_alpha = 1.0f;		//リキャストレベルDOWNメッセージを表示するため、透過度を1.0fにする
					}

					//▼武器ポッドレベルDOWNチェック
					//既にレベルUP済みの武器ポッドの現在の研究員数をチェックし、
					//装備不可な研究員数に達していれば、レベルDOWNさせる。
					//▽それぞれ武器ポッドレベルDOWNチェック関数を呼び出す
					g_Pow_equip_Level = Equip_Lvdown_check(0, g_Pow_equip_Level);
					g_Def_equip_Level = Equip_Lvdown_check(1, g_Def_equip_Level);
					g_Spe_equip_Level = Equip_Lvdown_check(2, g_Spe_equip_Level);
					g_Bal_equip_Level = Equip_Lvdown_check(3, g_Bal_equip_Level);
					g_Pod_equip_Level = Equip_Lvdown_check(4, g_Pod_equip_Level);

					//振り分けダウン音
					Audio::Start(2);
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
		else
		{
			m_Human_down_color = INI_COLOR;
		}

		//ミサイルボタン
		if (515 < m_mou_x && m_mou_x < 1120 && 325 < m_mou_y && m_mou_y < 473)
		{
			m_Mis_Button_color = 1.0f;

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

					//選択音
					Audio::Start(1);
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
		else
		{
			m_Mis_Button_color = INI_COLOR;
		}
		
		//武器ポッドボタン
		if (515 < m_mou_x && m_mou_x < 1120 && 493 < m_mou_y && m_mou_y < 641)
		{
			m_Equ_Button_color = 1.0f;

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

					//▼武器ポッドLvUP可能チェック
					Equip_Lvup_possible_check();//武器ポッドレベルUP可能チェック関数を呼び出す
		
					//"武器ポッドウインドウを開いている状態"フラグを立てる
					window_start_manage = Equipment;

					//選択音
					Audio::Start(1);
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
		else
		{
			m_Equ_Button_color = INI_COLOR;
		}


		return;
	}
	//▼ミサイルウインドウ、もしくは武器ポッドウインドウ表示時の処理
	else if (window_start_manage == Missile || window_start_manage == Equipment)
	{
		//▼(武器ポッド)最終確認ウインドウ表示時の処理
		if (m_finalcheck_f == true)
		{
			//最終確認[はい]ボタン
			if (410 < m_mou_x && m_mou_x < 502 && 407 < m_mou_y && m_mou_y < 450)
			{
				m_Yes_Button_color = 1.0f;

				//▼クリックされたら武器ポッドレベルUP処理を行い、このウインドウを閉じる
				//左クリック入力時
				if (m_mou_l == true)
				{
					//左クリック押したままの状態では入力出来ないようにしている
					if (m_key_lf == true)
					{
						m_key_lf = false;

						//▽武器ポッドレベルUP処理
						//素材消費処理
						*m_Equ_next_Mat_type[finalcheck_Lvup_type][*finalcheck_Lvup_achieve - 1] -= m_Equ_next_Mat_num[finalcheck_Lvup_type][*finalcheck_Lvup_achieve - 1];

						//選択した武器ポッドタイプ(パワー、スピード等)のレベルUP処理
						(*finalcheck_Lvup_Level)++;
						(*finalcheck_Lvup_achieve)++;

						//LvUP後、更にレベルUP出来るか確かめる為に武器ポッドレベルUP可能チェックを行う
						Equip_Lvup_possible_check();//武器ポッドレベルUP可能チェック関数を呼び出す

						//▽レベルUP前後の装備武器ポッドカラーを適切なものに変更する
						//レベルUP後の装備武器のカラーを白色に設定する
						m_Equ_pic_red_color[*finalcheck_Lvup_achieve - 1 + finalcheck_Lvup_type * 3] = 1.0f;
						m_Equ_pic_green_color[*finalcheck_Lvup_achieve - 1 + finalcheck_Lvup_type * 3] = 1.0f;
						m_Equ_pic_blue_color[*finalcheck_Lvup_achieve - 1 + finalcheck_Lvup_type * 3] = 1.0f;

						//レベルUP前の装備武器のカラーを灰色に設定する
						m_Equ_pic_red_color[*finalcheck_Lvup_achieve - 2 + finalcheck_Lvup_type * 3] = 0.5f;
						m_Equ_pic_green_color[*finalcheck_Lvup_achieve - 2 + finalcheck_Lvup_type * 3] = 0.5f;
						m_Equ_pic_blue_color[*finalcheck_Lvup_achieve - 2 + finalcheck_Lvup_type * 3] = 0.5f;


						m_Yes_Button_color = 0.0f;

						//最終確認ウインドウを非表示にする
						m_finalcheck_f = false;

						//選択音
						Audio::Start(1);
					}
				}
				else
				{
					m_key_lf = true;
				}
			}
			else
			{
				m_Yes_Button_color = 0.0f;
			}

			//最終確認[いいえ]ボタン
			if (648 < m_mou_x && m_mou_x < 789 && 407 < m_mou_y && m_mou_y < 450 || m_mou_r == true)
			{
				m_No_Button_color = 1.0f;

				//▼クリックされたら、このウインドウを閉じる
				//右クリック入力時
				if (m_mou_r == true)
				{
					//ウインドウ閉じた後、続けて戻るボタンを入力しないようにstatic変数にfalseを入れて制御
					m_key_rf = false;

					m_No_Button_color = 0.0f;

					//最終確認ウインドウを非表示にする
					m_finalcheck_f = false;

					//戻るボタン音
					Audio::Start(2);
				}
				//左クリック入力時
				else if (m_mou_l == true)
				{
					//左クリック押したままの状態では入力出来ないようにしている
					if (m_key_lf == true)
					{
						m_key_lf = false;

						m_No_Button_color = 0.0f;

						//最終確認ウインドウを非表示にする
						m_finalcheck_f = false;

						//戻るボタン音
						Audio::Start(2);
					}
				}
				else
				{
					m_key_lf = true;
				}
			}
			else
			{
				m_No_Button_color = 0.0f;
			}


			return;
		}

		//戻るボタン左クリック、もしくは右クリック(どこでも)する事でこのウインドウを閉じる
		if (50 < m_mou_x && m_mou_x < 100 && 50 < m_mou_y && m_mou_y < 100 || m_mou_r == true)
		{
			m_Back_Button_color = 1.0f;

			//▼クリックされたらフラグを立て、このウインドウを閉じる
			//右クリック入力時
			if (m_mou_r == true)
			{
				//前シーン(最終確認ウインドウ)から右クリック押したままの状態では入力出来ないようにしている
				if (m_key_rf == true)
				{
					//ウインドウ閉じた後、続けて戻るボタンを入力しないようにstatic変数にfalseを入れて制御
					m_key_rf = false;

					//武器必要素材&人数メッセージを非表示にするため、透過度を0.0fにする
					m_alpha = 0.0f;

					//"研究所ウインドウを開いている状態"フラグを立てる
					window_start_manage = Institute;

					//戻るボタン音
					Audio::Start(2);
				}
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

					//戻るボタン音
					Audio::Start(2);
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
			m_Back_Button_color = INI_COLOR;
		}


		//武器ポッドウインドウを開いていた場合、更に以下の処理を行う
		if (window_start_manage == Equipment)
		{
			//パワー武器Lv.1
			if (277 < m_mou_x && m_mou_x < 407 && 207 < m_mou_y && m_mou_y < 336)
			{
				//▼武器ポッド必要素材&人数メッセージを表示
				Equip_message(0, 0);//武器ポッド必要素材&人数メッセージ表示関数を呼び出す
			}

			//パワー武器Lv.2
			else if (277 < m_mou_x && m_mou_x < 407 && 355 < m_mou_y && m_mou_y < 483)
			{
				//▼武器ポッド必要素材&人数メッセージを表示
				Equip_message(0, 1);//武器ポッド必要素材&人数メッセージ表示関数を呼び出す
			}

			//パワー武器Lv.3
			else if (277 < m_mou_x && m_mou_x < 407 && 503 < m_mou_y && m_mou_y < 632)
			{
				//▼武器ポッド必要素材&人数メッセージを表示
				Equip_message(0, 2);//武器ポッド必要素材&人数メッセージ表示関数を呼び出す
			}

			//ディフェンス武器Lv.1
			else if (445 < m_mou_x && m_mou_x < 575 && 207 < m_mou_y && m_mou_y < 336)
			{
				//▼武器ポッド必要素材&人数メッセージを表示
				Equip_message(1, 0);//武器ポッド必要素材&人数メッセージ表示関数を呼び出す
			}

			//ディフェンス武器Lv.2
			else if (445 < m_mou_x && m_mou_x < 575 && 355 < m_mou_y && m_mou_y < 483)
			{
				//▼武器ポッド必要素材&人数メッセージを表示
				Equip_message(1, 1);//武器ポッド必要素材&人数メッセージ表示関数を呼び出す
			}

			//ディフェンス武器Lv.3
			else if (445 < m_mou_x && m_mou_x < 575 && 503 < m_mou_y && m_mou_y < 632)
			{
				//▼武器ポッド必要素材&人数メッセージを表示
				Equip_message(1, 2);//武器ポッド必要素材&人数メッセージ表示関数を呼び出す
			}

			//スピード武器Lv.1
			else if (614 < m_mou_x && m_mou_x < 744 && 207 < m_mou_y && m_mou_y < 336)
			{
				//▼武器ポッド必要素材&人数メッセージを表示
				Equip_message(2, 0);//武器ポッド必要素材&人数メッセージ表示関数を呼び出す
			}

			//スピード武器Lv.2
			else if (614 < m_mou_x && m_mou_x < 744 && 355 < m_mou_y && m_mou_y < 483)
			{
				//▼武器ポッド必要素材&人数メッセージを表示
				Equip_message(2, 1);//武器ポッド必要素材&人数メッセージ表示関数を呼び出す
			}

			//スピード武器Lv.3
			else if (614 < m_mou_x && m_mou_x < 744 && 503 < m_mou_y && m_mou_y < 632)
			{
				//▼武器ポッド必要素材&人数メッセージを表示
				Equip_message(2, 2);//武器ポッド必要素材&人数メッセージ表示関数を呼び出す
			}

			//バランス武器Lv.1
			else if (783 < m_mou_x && m_mou_x < 913 && 207 < m_mou_y && m_mou_y < 336)
			{
				//▼武器ポッド必要素材&人数メッセージを表示
				Equip_message(3, 0);//武器ポッド必要素材&人数メッセージ表示関数を呼び出す
			}

			//バランス武器Lv.2
			else if (783 < m_mou_x && m_mou_x < 913 && 355 < m_mou_y && m_mou_y < 483)
			{
				//▼武器ポッド必要素材&人数メッセージを表示
				Equip_message(3, 1);//武器ポッド必要素材&人数メッセージ表示関数を呼び出す
			}

			//バランス武器Lv.3
			else if (783 < m_mou_x && m_mou_x < 913 && 503 < m_mou_y && m_mou_y < 632)
			{
				//▼武器ポッド必要素材&人数メッセージを表示
				Equip_message(3, 2);//武器ポッド必要素材&人数メッセージ表示関数を呼び出す
			}

			//ポッドLv.1
			else if (952 < m_mou_x && m_mou_x < 1081 && 207 < m_mou_y && m_mou_y < 336)
			{
				//▼武器ポッド必要素材&人数メッセージを表示
				Equip_message(4, 0);//武器ポッド必要素材&人数メッセージ表示関数を呼び出す
			}

			//ポッドLv.2
			else if (952 < m_mou_x && m_mou_x < 1081 && 355 < m_mou_y && m_mou_y < 483)
			{
				//▼武器ポッド必要素材&人数メッセージを表示
				Equip_message(4, 1);//武器ポッド必要素材&人数メッセージ表示関数を呼び出す
			}

			//ポッドLv.3
			else if (952 < m_mou_x && m_mou_x < 1081 && 503 < m_mou_y && m_mou_y < 632)
			{
				//▼武器ポッド必要素材&人数メッセージを表示
				Equip_message(4, 2);//武器ポッド必要素材&人数メッセージ表示関数を呼び出す
			}

			//上記の範囲外にマウスカーソルがある場合、
			//武器必要素材&人数メッセージを非表示にする
			else
			{
				m_alpha = 0.0f;//武器必要素材&人数メッセージを非表示
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
		m_Ins_color = 1.0f;

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

				//選択音
				Audio::Start(1);
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
		m_Ins_color = INI_COLOR;
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
		{ m_Equ_pic_red_color[0],m_Equ_pic_green_color[0],m_Equ_pic_blue_color[0],1.0f },
		{ m_Equ_pic_red_color[1],m_Equ_pic_green_color[1],m_Equ_pic_blue_color[1],1.0f },
		{ m_Equ_pic_red_color[2],m_Equ_pic_green_color[2],m_Equ_pic_blue_color[2],1.0f },
		{ m_Equ_pic_red_color[3],m_Equ_pic_green_color[3],m_Equ_pic_blue_color[3],1.0f },
		{ m_Equ_pic_red_color[4],m_Equ_pic_green_color[4],m_Equ_pic_blue_color[4],1.0f },
		{ m_Equ_pic_red_color[5],m_Equ_pic_green_color[5],m_Equ_pic_blue_color[5],1.0f },
		{ m_Equ_pic_red_color[6],m_Equ_pic_green_color[6],m_Equ_pic_blue_color[6],1.0f },
		{ m_Equ_pic_red_color[7],m_Equ_pic_green_color[7],m_Equ_pic_blue_color[7],1.0f },
		{ m_Equ_pic_red_color[8],m_Equ_pic_green_color[8],m_Equ_pic_blue_color[8],1.0f },
		{ m_Equ_pic_red_color[9],m_Equ_pic_green_color[9],m_Equ_pic_blue_color[9],1.0f },
		{ m_Equ_pic_red_color[10],m_Equ_pic_green_color[10],m_Equ_pic_blue_color[10],1.0f },
		{ m_Equ_pic_red_color[11],m_Equ_pic_green_color[11],m_Equ_pic_blue_color[11],1.0f },
		{ m_Equ_pic_red_color[12],m_Equ_pic_green_color[12],m_Equ_pic_blue_color[12],1.0f },
		{ m_Equ_pic_red_color[13],m_Equ_pic_green_color[13],m_Equ_pic_blue_color[13],1.0f },
		{ m_Equ_pic_red_color[14],m_Equ_pic_green_color[14],m_Equ_pic_blue_color[14],1.0f },
	};

	//武器ポッド必要素材&人数フォント用
	float Equ_message_font[EQU_MES_MAX_FONT_LINE][4] =
	{
		{ 0.0f,0.0f,1.0f,m_alpha },//1行目は青色
		{ 0.0f,0.0f,0.0f,m_alpha },//2行目以降は全て黒色
		{ 0.0f,0.0f,0.0f,m_alpha },
	};
	
	//武器ポッド必要素材&人数ウインドウ用
	float Equ_message_window[4] = { 1.0f,1.0f,1.0f,m_alpha };

	//最終確認[はい]ボタン用
	float Yes[4] = { m_Yes_Button_color,0.0f,0.0f,1.0f };

	//最終確認[いいえ]ボタン用
	float No[4] = { 0.0f,0.0f,m_No_Button_color,1.0f };

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
		src.m_right = 256.0f;
		src.m_bottom = 256.0f;

		dst.m_top = 460.0f;
		dst.m_left = 10.0f;
		dst.m_right = 390.0f;
		dst.m_bottom = 690.0f;
		Draw::Draw(3 + (g_Ins_Level - 1) * 3, &src, &dst, ins, 0.0f);

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
			Draw::Draw(21, &src, &dst, white, 0.0f);

			//▼フォント表示
			//研究所レベル
			Font::StrDraw(Ins, m_mou_x - 95.0f, m_mou_y - 45.0f, 30.0f, black);
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
		src.m_right = 256.0f;
		src.m_bottom = 256.0f;

		dst.m_top = 150.0f;
		dst.m_left = 100.0f;
		dst.m_right = 400.0f;
		dst.m_bottom = 350.0f;
		Draw::Draw(3 + (g_Ins_Level - 1) * 3, &src, &dst, white, 0.0f);

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
		src.m_right = 256.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 330.0f;
		dst.m_left = 520.0f;
		dst.m_right = 1130.0f;
		dst.m_bottom = 480.0f;
		Draw::Draw(25, &src, &dst, missile, 0.0f);

		//▼武器ポッドボタン表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 256.0f;
		src.m_bottom = 64.0f;

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

		Facility_message(g_Ins_Level);//研究所の必要素材&サイズメッセージ描画関数呼び出す

		//簡易メッセージ(エラーメッセージ、レベルUP表示等)
		Font::StrDraw(m_message, m_mou_x - 110.0f, m_mou_y - 45.0f, 30.0f, message);


		//▼最終確認ウインドウ表示管理フラグがtrueの時、描画。
		if (m_finalcheck_f == true)
		{
			//▼最終確認ウインドウ表示
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 64.0f;
			src.m_bottom = 64.0f;

			dst.m_top = 220.0f;
			dst.m_left = 320.0f;
			dst.m_right = 880.0f;
			dst.m_bottom = 480.0f;
			Draw::Draw(21, &src, &dst, white, 0.0f);

			//▼フォント表示
			//最終確認メッセージ
			Font::StrDraw(L"惑星HPと素材消費して", 347.0f, 250.0f, 30.0f, black);
			Font::StrDraw(L"レベルアップしますか？", 527.0f, 300.0f, 30.0f, black);
			Font::StrDraw(L"はい", 410.0f, 410.0f, 50.0f, Yes);
			Font::StrDraw(L"いいえ", 650.0f, 410.0f, 50.0f, No);
		}
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
			src.m_right = 64.0f;
			src.m_bottom = 64.0f;

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
					src.m_right = 150.0f;
					src.m_bottom = 150.0f;

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
			//▽ウインドウ表示 
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 64.0f;
			src.m_bottom = 64.0f;

			dst.m_top = m_mou_y - m_Equ_message_window_y_size;
			dst.m_left = m_mou_x - m_Equ_message_window_x_size;
			dst.m_right = m_mou_x + m_Equ_message_window_x_size;
			dst.m_bottom = m_mou_y + 0.0f;
			Draw::Draw(21, &src, &dst, Equ_message_window, 0.0f);

			//▽フォント表示
			//素材名を除いたフォント表示
			for (int i = 0; i < EQU_MES_MAX_FONT_LINE; i++)
			{
				Font::StrDraw(m_Equ_message[i], m_mou_x - 135.0f, m_mou_y - 160.0f + i * 40.0f, 25.0f, Equ_message_font[i]);
			}

			//素材名のフォント表示
			Font::StrDraw(m_message_Mat_name, m_mou_x - 135.0f, m_mou_y - 76.0f, 17.5f, Equ_message_font[2]);

			//最下部メッセージ表示(ウインドウ一番下にあるフォント)
			Font::StrDraw(m_message, m_mou_x - 210.0f, m_mou_y - 40.0f, 30.0f, message);



			//▼最終確認ウインドウ表示管理フラグがtrueの時、描画。
			if (m_finalcheck_f == true)
			{
				//▼最終確認ウインドウ表示
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 64.0f;
				src.m_bottom = 64.0f;

				dst.m_top = 220.0f;
				dst.m_left = 320.0f;
				dst.m_right = 880.0f;
				dst.m_bottom = 480.0f;
				Draw::Draw(21, &src, &dst, white, 0.0f);

				//▼フォント表示
				//最終確認メッセージ
				Font::StrDraw(L"素材消費してレベルアップしますか？", 347.0f, 250.0f, 30.0f, black);
				Font::StrDraw(L"※研究員は失われません。", 347.0f, 300.0f, 30.0f, black);
				Font::StrDraw(L"はい", 410.0f, 410.0f, 50.0f, Yes);
				Font::StrDraw(L"いいえ", 650.0f, 410.0f, 50.0f, No);
			}
		}
	}

	

	//デバッグ用仮マウス位置表示
	//wchar_t str[256];
	//swprintf_s(str, L"x=%f,y=%f", m_mou_x, m_mou_y);
	//Font::StrDraw(str, 20.0f, 20.0f, 12.0f, white);
}


//---Missile_Lvup_check関数
//▼内容
//ミサイルリキャストレベルUP条件を満たしているかチェックし、
//満たしていればレベルUPさせる。
void CObjInstitute::Missile_Lvup_check()
{
	if (g_Mis_Recast_Level == MIS_MAX_LV - 1)
	{
		;//最大レベルの時はこのチェック処理を飛ばす
	}
	else if (g_Ins_Level >= m_Mis_recast_next_Ins_Lv[g_Mis_Recast_Level] &&
		g_Research_num >= m_Mis_recast_next_Hum_num[g_Mis_Recast_Level])
	{
		g_Mis_Recast_Level++;//条件を満たしているのでレベルUP


		//▼ミサイルリキャストがレベルUPした事を簡易メッセージにて知らせる
		swprintf_s(m_message, L"ミサイルリキャストレベルUP！");//文字配列に文字データを入れる

		//リキャストレベルUPメッセージのカラーを黄色にする
		m_message_red_color = 1.0f;
		m_message_green_color = 1.0f;
		m_message_blue_color = 0.0f;

		m_alpha = 1.0f;		//リキャストレベルUPメッセージを表示するため、透過度を1.0fにする

		//ミサイルのレベルがアップした際にグローバル変数にリキャストタイムを代入する
		switch (g_Mis_Recast_Level)
		{
		case 1:g_Recast_time = MIS_LV_2;break;//6秒
		case 2:g_Recast_time = MIS_LV_3;break;//5秒
		case 3:g_Recast_time = MIS_LV_4;break;//4秒
		case 4:g_Recast_time = MIS_LV_5;break;//3秒
		}
	}

}

//---Equip_Lvup_check関数
//引数1　int equip_id			:識別番号(パワー武器:0　ディフェンス武器:1　スピード武器:2　バランス武器:3　ポッド:4)
//引数2　int equip_Level		:武器ポッドレベル
//引数3　int equip_Lv_achieve	:武器ポッドレベルの最大到達度
//戻り値 int					:チェック済の武器ポッドレベル
//▼内容
//既にレベルUP済みの武器ポッドの現在の研究員数をチェックし、
//装備可能な研究員数に達していれば、レベルUPさせる。
int CObjInstitute::Equip_Lvup_check(int equip_id, int equip_Level, int equip_Lv_achieve)
{
	//▼武器ポッドレベルUPチェック処理
	if (equip_Level == equip_Lv_achieve)
	{
		;//レベルが最大到達度に達している時はこのチェック処理を飛ばす
	}
	else if (g_Research_num >= m_Equ_next_Hum_num[equip_id][equip_Level - 1])
	{
		equip_Level++;//装備可能な研究員数を満たしているのでレベルUP


		//▼レベルUP前後の装備武器ポッドカラーを適切なものに変更する
		//レベルUP後の装備武器のカラーを白色に設定する
		m_Equ_pic_red_color[equip_Level - 1 + equip_id * 3] = 1.0f;
		m_Equ_pic_green_color[equip_Level - 1 + equip_id * 3] = 1.0f;
		m_Equ_pic_blue_color[equip_Level - 1 + equip_id * 3] = 1.0f;

		//レベルUP前の装備武器のカラーを灰色に設定する
		m_Equ_pic_red_color[equip_Level - 2 + equip_id * 3] = 0.5f;
		m_Equ_pic_green_color[equip_Level - 2 + equip_id * 3] = 0.5f;
		m_Equ_pic_blue_color[equip_Level - 2 + equip_id * 3] = 0.5f;


		//▼武器ポッドがレベルUPした事を簡易メッセージにて知らせる
		if (equip_id == 0)
		{
			swprintf_s(m_message, L"パワー武器レベルUP！");//文字配列に文字データを入れる
		}
		else if (equip_id == 1)
		{
			swprintf_s(m_message, L"ディフェンス武器レベルUP！");//文字配列に文字データを入れる
		}
		else if (equip_id == 2)
		{
			swprintf_s(m_message, L"スピード武器レベルUP！");//文字配列に文字データを入れる
		}
		else if (equip_id == 3)
		{
			swprintf_s(m_message, L"バランス武器レベルUP！");//文字配列に文字データを入れる
		}
		else  //(equip_id == 4)
		{
			swprintf_s(m_message, L"ポッドレベルUP！");//文字配列に文字データを入れる
		}

		//武器ポッドレベルUPメッセージのカラーを黄色にする
		m_message_red_color = 1.0f;
		m_message_green_color = 1.0f;
		m_message_blue_color = 0.0f;

		m_alpha = 1.0f;		//武器ポッドレベルUPメッセージを表示するため、透過度を1.0fにする
	}

	return equip_Level;
}

//---Equip_Lvdown_check関数
//引数1　int equip_id			:識別番号(パワー武器:0　ディフェンス武器:1　スピード武器:2　バランス武器:3　ポッド:4)
//引数2　int equip_Level		:武器ポッドレベル
//戻り値 int					:チェック済の武器ポッドレベル
//▼内容
//既にレベルUP済みの武器ポッドの現在の研究員数をチェックし、
//装備不可な研究員数に達していれば、レベルDOWNさせる。
int CObjInstitute::Equip_Lvdown_check(int equip_id, int equip_Level)
{
	//▼武器ポッドレベルDOWNチェック処理
	if (equip_Level == 1)
	{
		;//初期レベルの時はこのチェック処理を飛ばす
	}
	else if (g_Research_num < m_Equ_next_Hum_num[equip_id][equip_Level - 2])
	{
		equip_Level--;//装備不可な研究員数を満たしているのでレベルDOWN


		//▼レベルDOWN前後の装備武器ポッドカラーを適切なものに変更する
		//レベルDOWN後の装備武器のカラーを白色に設定する
		m_Equ_pic_red_color[equip_Level - 1 + equip_id * 3] = 1.0f;
		m_Equ_pic_green_color[equip_Level - 1 + equip_id * 3] = 1.0f;
		m_Equ_pic_blue_color[equip_Level - 1 + equip_id * 3] = 1.0f;

		//レベルDOWN前の装備武器のカラーを灰色に設定する
		m_Equ_pic_red_color[equip_Level + equip_id * 3] = 0.5f;
		m_Equ_pic_green_color[equip_Level + equip_id * 3] = 0.5f;
		m_Equ_pic_blue_color[equip_Level + equip_id * 3] = 0.5f;


		//▼武器ポッドがレベルDOWNした事を簡易メッセージにて知らせる
		if (equip_id == 0)
		{
			swprintf_s(m_message, L"パワー武器レベルDOWN…");//文字配列に文字データを入れる
		}
		else if (equip_id == 1)
		{
			swprintf_s(m_message, L"ディフェンス武器レベルDOWN…");//文字配列に文字データを入れる
		}
		else if (equip_id == 2)
		{
			swprintf_s(m_message, L"スピード武器レベルDOWN…");//文字配列に文字データを入れる
		}
		else if (equip_id == 3)
		{
			swprintf_s(m_message, L"バランス武器レベルDOWN…");//文字配列に文字データを入れる
		}
		else  //(equip_id == 4)
		{
			swprintf_s(m_message, L"ポッドレベルDOWN…");//文字配列に文字データを入れる
		}

		//武器ポッドレベルDOWNメッセージのカラーを水色にする
		m_message_red_color = 0.0f;
		m_message_green_color = 1.0f;
		m_message_blue_color = 1.0f;

		m_alpha = 1.0f;		//武器ポッドレベルDOWNメッセージを表示するため、透過度を1.0fにする
	}

	return equip_Level;
}

//---Equip_Lvup_possible_check関数
//▼内容
//それぞれの武器、ポッドがレベルアップ可能な状態
//(住民数と素材数それぞれが必要数を満たしており、
//現在の武器ポッドレベルと、そのレベルの最大到達度が同値)
//であるかどうかをチェックし、
//レベルアップ可能であればその武器ポッドの画像を黄色にし、
//レベルアップ不可であればその武器ポッドの画像を黒色にする。
void CObjInstitute::Equip_Lvup_possible_check()
{
	for (int i = 0; i < 5; i++)
	{
		//▼各武器レベル、そのレベルの最大到達度を管理する変数をそれぞれ宣言
		int Tmp_equip_Level;
		int Tmp_equip_Lv_achieve;

		//▼適切なタイミングで先程宣言した変数に各武器レベルと、そのレベルの最大到達度を代入
		if (i == 0)
		{
			Tmp_equip_Level = g_Pow_equip_Level;
			Tmp_equip_Lv_achieve = g_Pow_equip_Lv_achieve;
		}
		else if (i == 1)
		{
			Tmp_equip_Level = g_Def_equip_Level;
			Tmp_equip_Lv_achieve = g_Def_equip_Lv_achieve;
		}
		else if (i == 2)
		{
			Tmp_equip_Level = g_Spe_equip_Level;
			Tmp_equip_Lv_achieve = g_Spe_equip_Lv_achieve;
		}
		else if (i == 3)
		{
			Tmp_equip_Level = g_Bal_equip_Level;
			Tmp_equip_Lv_achieve = g_Bal_equip_Lv_achieve;
		}
		else  //(i == 4)
		{
			Tmp_equip_Level = g_Pod_equip_Level;
			Tmp_equip_Lv_achieve = g_Pod_equip_Lv_achieve;
		}

		//▼武器ポッドレベルUP可能チェック処理
		if (Tmp_equip_Lv_achieve == EQU_MAX_LV)
		{
			;//最大レベルの時はこの武器ポッドレベルUP可能チェック処理を飛ばす
		}
		else if (Tmp_equip_Level == Tmp_equip_Lv_achieve &&
			g_Research_num >= m_Equ_next_Hum_num[i][Tmp_equip_Lv_achieve - 1] &&
			*m_Equ_next_Mat_type[i][Tmp_equip_Lv_achieve - 1] >= m_Equ_next_Mat_num[i][Tmp_equip_Lv_achieve - 1])
		{
			//レベルアップ可能な武器ポッド画像を黄色にする。
			m_Equ_pic_red_color[Tmp_equip_Lv_achieve + i * 3] = 1.0f;
			m_Equ_pic_green_color[Tmp_equip_Lv_achieve + i * 3] = 1.0f;
			m_Equ_pic_blue_color[Tmp_equip_Lv_achieve + i * 3] = 0.0f;
		}
		else
		{
			//レベルアップ不可な武器ポッド画像は黒色にする。
			m_Equ_pic_red_color[Tmp_equip_Lv_achieve + i * 3] = 0.1f;
			m_Equ_pic_green_color[Tmp_equip_Lv_achieve + i * 3] = 0.1f;
			m_Equ_pic_blue_color[Tmp_equip_Lv_achieve + i * 3] = 0.1f;
		}
	}
}

//---Equip_message関数
//引数1　int equip_id	:武器ポッド識別番号(パワー武器:0　ディフェンス武器:1　スピード武器:2　バランス武器:3　ポッド:4)
//引数2　int Lv_id		:レベル識別番号(Lv.1 = 0  Lv.2 = 1  Lv.3 = 2)
//▼内容
//マウスで選択している武器ポッドが何であるかを識別し、
//それに対応する武器ポッド必要素材&人数メッセージを表示する。
void CObjInstitute::Equip_message(int equip_id, int Lv_id)
{
	//▼武器ポッド画像が黄色(レベルアップ可能)の時の処理
	if (m_Equ_pic_red_color[Lv_id + equip_id * 3] == 1.0f &&
		m_Equ_pic_green_color[Lv_id + equip_id * 3] == 1.0f &&
		m_Equ_pic_blue_color[Lv_id + equip_id * 3] == 0.0f)
	{
		//武器ポッド必要素材&人数メッセージ設定
		swprintf_s(m_Equ_message[0], L"LvUP条件  所持/  必要");																				 //文字配列に文字データを入れる
		swprintf_s(m_Equ_message[1], L"研究員  %6d/%6d", g_Research_num, m_Equ_next_Hum_num[equip_id][Lv_id - 1]);							 //文字配列に文字データを入れる
		swprintf_s(m_Equ_message[2], L"        %6d/%6d", *m_Equ_next_Mat_type[equip_id][Lv_id - 1], m_Equ_next_Mat_num[equip_id][Lv_id - 1]);//文字配列に文字データを入れる
		swprintf_s(m_message_Mat_name, L"%s", m_Equ_next_Mat_name[equip_id][Lv_id - 1]);												 //文字配列に文字データを入れる

		//最下部メッセージ設定
		swprintf_s(m_message, L"　　　クリックでLvUP可");//文字配列に文字データを入れる

		//最下部メッセージのカラーを青色にする
		m_message_red_color = 0.0f;
		m_message_green_color = 0.0f;
		m_message_blue_color = 1.0f;

		//武器ポッド必要素材&人数ウインドウのサイズを設定
		m_Equ_message_window_x_size = 150.0f;
		m_Equ_message_window_y_size = 170.0f;

		//左クリックされたらフラグを立て、最終確認ウインドウを開く
		if (m_mou_l == true)
		{
			//左クリック押したままの状態では入力出来ないようにしている
			if (m_key_lf == true)
			{
				m_key_lf = false;

				//▼以下の変数、ポインタにマウス選択中の武器ポッドタイプ(パワー、スピード等)、
				//現在のレベル、レベル最大到達度のアドレスをそれぞれ代入
				finalcheck_Lvup_type = equip_id;
				
				if (equip_id == 0)
				{
					finalcheck_Lvup_Level = &g_Pow_equip_Level;
					finalcheck_Lvup_achieve = &g_Pow_equip_Lv_achieve;
				}
				else if (equip_id == 1)
				{
					finalcheck_Lvup_Level = &g_Def_equip_Level;
					finalcheck_Lvup_achieve = &g_Def_equip_Lv_achieve;
				}
				else if (equip_id == 2)
				{
					finalcheck_Lvup_Level = &g_Spe_equip_Level;
					finalcheck_Lvup_achieve = &g_Spe_equip_Lv_achieve;
				}
				else if (equip_id == 3)
				{
					finalcheck_Lvup_Level = &g_Bal_equip_Level;
					finalcheck_Lvup_achieve = &g_Bal_equip_Lv_achieve;
				}
				else  //(equip_id == 4)
				{
					finalcheck_Lvup_Level = &g_Pod_equip_Level;
					finalcheck_Lvup_achieve = &g_Pod_equip_Lv_achieve;
				}

				m_alpha = 0.0f;//武器ポッド必要素材&人数メッセージを非表示にする

				m_finalcheck_f = true;//最終確認ウインドウを表示する

				 //選択音
				Audio::Start(1);
				
				return;
			}
		}
		else
		{
			m_key_lf = true;
		}
	}
	//▼武器ポッド画像が黒色(装備不可)の処理
	else if (m_Equ_pic_red_color[Lv_id + equip_id * 3] == 0.1f &&
		m_Equ_pic_green_color[Lv_id + equip_id * 3] == 0.1f &&
		m_Equ_pic_blue_color[Lv_id + equip_id * 3] == 0.1f)
	{
		//武器ポッド必要素材&人数メッセージ設定
		swprintf_s(m_Equ_message[0], L"LvUP条件  所持/  必要");																				 //文字配列に文字データを入れる
		swprintf_s(m_Equ_message[1], L"研究員  %6d/%6d", g_Research_num, m_Equ_next_Hum_num[equip_id][Lv_id - 1]);							 //文字配列に文字データを入れる
		swprintf_s(m_Equ_message[2], L"        %6d/%6d", *m_Equ_next_Mat_type[equip_id][Lv_id - 1], m_Equ_next_Mat_num[equip_id][Lv_id - 1]);//文字配列に文字データを入れる
		swprintf_s(m_message_Mat_name, L"%s", m_Equ_next_Mat_name[equip_id][Lv_id - 1]);												 //文字配列に文字データを入れる

		//最下部メッセージ設定
		swprintf_s(m_message, L"　　　　　LvUP不可");//文字配列に文字データを入れる

		//最下部メッセージのカラーを赤色にする
		m_message_red_color = 1.0f;
		m_message_green_color = 0.0f;
		m_message_blue_color = 0.0f;

		//武器ポッド必要素材&人数ウインドウのサイズを設定
		m_Equ_message_window_x_size = 150.0f;
		m_Equ_message_window_y_size = 170.0f;
	}
	//▼武器ポッド画像が白色(装備中)の処理
	else if (m_Equ_pic_red_color[Lv_id + equip_id * 3] == 1.0f &&
		m_Equ_pic_green_color[Lv_id + equip_id * 3] == 1.0f &&
		m_Equ_pic_blue_color[Lv_id + equip_id * 3] == 1.0f)
	{
		//武器ポッド必要素材&人数メッセージ設定
		swprintf_s(m_Equ_message[0], L"");//文字データをクリアする
		swprintf_s(m_Equ_message[1], L"");//文字データをクリアする
		swprintf_s(m_Equ_message[2], L"");//文字データをクリアする
		swprintf_s(m_message_Mat_name, L"");//文字データをクリアする

		//最下部メッセージ設定
		swprintf_s(m_message, L"　　　　   装備中");//文字配列に文字データを入れる

		//最下部メッセージのカラーを黒色にする
		m_message_red_color = 0.0f;
		m_message_green_color = 0.0f;
		m_message_blue_color = 0.0f;

		//武器ポッド必要素材&人数ウインドウのサイズを設定
		m_Equ_message_window_x_size = 55.0f;
		m_Equ_message_window_y_size = 50.0f;
	}
	//▼武器ポッド画像が灰色(レベルUP済[装備可])の処理
	else if (m_Equ_pic_red_color[Lv_id + equip_id * 3] == 0.5f &&
		m_Equ_pic_green_color[Lv_id + equip_id * 3] == 0.5f &&
		m_Equ_pic_blue_color[Lv_id + equip_id * 3] == 0.5f)
	{
		//▼現在の各武器レベルを管理する変数を宣言
		int Tmp_equip_Level;

		//▼先程宣言した変数にマウス選択中の武器ポッドタイプ(パワー、スピード等)の現在のレベルを代入
		if (equip_id == 0)
		{
			Tmp_equip_Level = g_Pow_equip_Level;
		}
		else if (equip_id == 1)
		{
			Tmp_equip_Level = g_Def_equip_Level;
		}
		else if (equip_id == 2)
		{
			Tmp_equip_Level = g_Spe_equip_Level;
		}
		else if (equip_id == 3)
		{
			Tmp_equip_Level = g_Bal_equip_Level;
		}
		else  //(equip_id == 4)
		{
			Tmp_equip_Level = g_Pod_equip_Level;
		}

		//武器ポッド必要素材&人数メッセージ設定
		swprintf_s(m_Equ_message[0], L"");//文字データをクリアする
		swprintf_s(m_Equ_message[1], L"");//文字データをクリアする
		swprintf_s(m_Equ_message[2], L"");//文字データをクリアする
		swprintf_s(m_message_Mat_name, L"");//文字データをクリアする

		//最下部メッセージ設定
		//マウス選択中の武器ポッドレベルがその武器の現在レベルより低かった場合
		if (Lv_id + 1 < Tmp_equip_Level) 
		{
			swprintf_s(m_message, L"研究員%6d人 未満で装備可", m_Equ_next_Hum_num[equip_id][Lv_id]);//文字配列に文字データを入れる
		}
		//マウス選択中の武器ポッドレベルがその武器の現在レベルより高かった場合
		else
		{
			swprintf_s(m_message, L"研究員%6d人 以上で装備可", m_Equ_next_Hum_num[equip_id][Lv_id - 1]);//文字配列に文字データを入れる
		}

		//最下部メッセージのカラーを黒色にする
		m_message_red_color = 0.0f;
		m_message_green_color = 0.0f;
		m_message_blue_color = 0.0f;

		//武器ポッド必要素材&人数ウインドウのサイズを設定
		m_Equ_message_window_x_size = 240.0f;
		m_Equ_message_window_y_size = 50.0f;
	}


	m_alpha = 1.0f;//武器ポッド必要素材&人数メッセージを表示
}