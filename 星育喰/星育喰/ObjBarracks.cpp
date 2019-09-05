//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "UtilityModule.h"

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
	m_Yes_Button_color = 1.0f;
	m_No_Button_color = 1.0f;

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
	m_key_rf = false;
	m_next_time = 0;
	m_con_alo_f = false;

	m_message_clip_right = 0.0f;
	m_message_clip_bottom = 0.0f;
	m_message_draw_left = 0.0f;
	m_message_draw_right = 0.0f;
	m_message_red_color = 0.0f;
	m_message_green_color = 0.0f;
	m_message_blue_color = 0.0f;
	m_alpha = INI_ALPHA;

	//▼兵舎の次のLVUPに必要なサイズ(HP)の住民数設定
	m_Facility_next_Size_num[0] = 70.0f; //レベルが1の時の必要サイズ(HP)
	m_Facility_next_Size_num[1] = 150.0f;	//レベルが2の時の必要サイズ(HP)

	//▼兵舎の次のLVUPに必要な素材の名前設定
	swprintf_s(m_Facility_next_Mat_name[0], L"木材");			 //レベルが1の時の必要素材名
	swprintf_s(m_Facility_next_Mat_name[1], L"プラスチック");//レベルが2の時の必要素材名

	//▼兵舎の次のLVUPに必要な素材種類設定と同時にその素材の所持数を代入する
	//※以下のように所持素材数を管理しているグローバル変数のアドレスを代入する事で素材の種類設定と所持数の代入をしている。
	m_Facility_next_Mat_type[0] = &g_Wood_num;	//レベルが1の時の必要素材種類
	m_Facility_next_Mat_type[1] = &g_Plastic_num;	//レベルが2の時の必要素材種類

	//▼兵舎の次のLVUPに必要な素材数設定
	m_Facility_next_Mat_num[0] = 50;		//レベルが1の時の必要素材数
	m_Facility_next_Mat_num[1] = 40;	//レベルが2の時の必要素材数


	//当たり判定用HitBoxを作成(Objhuman用)
	//Hits::SetHitBox(this, 810, 460, 380, 230, ELEMENT_ENEMY, OBJ_BARRACKS, 1);
}

//アクション
void CObjBarracks::Action()
{
	//ホワイトアウト演出中は操作不能にする処理
	//※チュートリアル中も操作不能にする。
	if (white_out_f == true || g_is_operatable == false)
	{
		return;
	}

	//ヘルプ画面表示中は操作不能にする処理
	if (g_help_f == true)
	{
		//ヘルプ画面の戻るボタンを左クリック(もしくは右クリック)時、
		//この施設の戻るボタンも同時にクリックされないように、
		//以下のようにキーフラグをfalseにする事で制御している。
		m_key_lf = false;
		m_key_rf = false;

		return;
	}

	//マウスの位置を取得
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//マウスのボタンの状態
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	//▼キーフラグ
	//※右クリックPush状態→右クリック未Push状態になるまで、
	//再度右クリックする事は出来ない処理。
	if (m_mou_r == false)	//右クリックOFF
	{
		m_key_rf = true;
	}

	//▼兵舎ウインドウ表示時の処理
	if (window_start_manage == Barracks)
	{
		//▼(兵舎)最終確認ウインドウ表示時の処理
		if (m_finalcheck_f == true)
		{
			//最終確認[はい]ボタン
			if (410 < m_mou_x && m_mou_x < 502 && 407 < m_mou_y && m_mou_y < 450)
			{
				m_Yes_Button_color = 0.0f;

				//▼クリックされたら兵舎レベルUP処理を行い、このウインドウを閉じる
				//左クリック入力時
				if (m_mou_l == true)
				{
					//左クリック押したままの状態では入力出来ないようにしている
					if (m_key_lf == true)
					{
						m_key_lf = false;

						//▽兵舎レベルUP処理
						//サイズ(HP)消費処理
						g_Player_max_size -= m_Facility_next_Size_num[g_Bar_Level - 1];

						//素材消費処理
						*m_Facility_next_Mat_type[g_Bar_Level - 1] -= m_Facility_next_Mat_num[g_Bar_Level - 1];

						//兵舎レベルUPにより、プレイヤー惑星がレベルUPするかチェック処理
						//※if文処理内に入る＝レベルUPする
						if (player_level != (int)((g_Bar_Level + g_Ins_Level + 1) / 2))
						{
							//プレイヤー惑星がレベルUPする場合、
							//育成画面背景の変更を行わないといけない為、
							//ホワイトアウト処理を挟み、背景変更を行う。
							//※ホワイトアウト処理はオブジェクト優先順位的にObjCloud_Effectにて行う。
							
							//プレイヤー惑星レベルを更新する(次のレベルUPチェック判定の為)
							player_level = (int)((g_Bar_Level + g_Ins_Level + 1) / 2);

							//ホワイトアウト演出フラグをON
							white_out_f = true;
						}
						//プレイヤー惑星がレベルUPしない場合、普通に兵舎のレベルUP処理を行う
						else
						{
							//兵舎のレベルUP処理
							g_Bar_Level++;

							//レベルアップ音
							Audio::Start(3);
						}
						
						m_Yes_Button_color = 1.0f;

						//最終確認ウインドウを非表示にする
						m_finalcheck_f = false;
					}
				}
				else
				{
					m_key_lf = true;
				}
			}
			else
			{
				m_Yes_Button_color = 1.0f;
			}

			//最終確認[いいえ]ボタン
			if (648 < m_mou_x && m_mou_x < 789 && 407 < m_mou_y && m_mou_y < 450 || m_mou_r == true)
			{
				m_No_Button_color = 0.0f;

				//▼クリックされたら、このウインドウを閉じる
				//右クリック入力時
				if (m_mou_r == true)
				{
					//ウインドウ閉じた後、続けて戻るボタンを入力しないようにstatic変数にfalseを入れて制御
					m_key_rf = false;

					m_No_Button_color = 1.0f;

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

						m_No_Button_color = 1.0f;

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
				m_No_Button_color = 1.0f;
			}


			return;
		}

		//マウスカーソル上部に表示されるエラーメッセージを徐々に非表示にする
		if (m_alpha > 0.0f)
		{
			m_alpha -= 0.01f;
		}

		//戻るボタン左クリック、もしくは右クリック(どこでも)する事で兵舎ウインドウを閉じる
		if (70 < m_mou_x && m_mou_x < 120 && 56 < m_mou_y && m_mou_y < 110 || m_mou_r == true)
		{
			m_Back_Button_color = 1.0f;

			//▼クリックされたらフラグを立て、兵舎ウインドウを閉じる
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
			m_Back_Button_color = INI_COLOR;
		}

		if (g_tutorial_progress >= 15)
		{
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

						//▼兵舎レベルUP可能チェック処理
						if (g_Bar_Level == FACILITY_MAX_LV)
						{
							//▽レベルMAX時の処理
							//左クリックされたら簡易メッセージ画像でレベルUP不可を伝える
							//LvUP出来ません文字画像を読み込み127番に登録
							Draw::LoadImage(L"img\\テキスト\\育成画面\\LvUP出来ません.png", 127, TEX_SIZE_512);//簡易メッセージ画像読み込み番号に画像データを入れる

							//切り取り位置を設定する
							m_message_clip_right = 937.0f;
							m_message_clip_bottom = 112.0f;

							//描画位置を設定する
							m_message_draw_left = -100.0f;
							m_message_draw_right = 100.0f;

							//簡易メッセージのカラーを赤色にする
							m_message_red_color = 1.0f;
							m_message_green_color = 0.0f;
							m_message_blue_color = 0.0f;

							//簡易メッセージを表示する
							m_alpha = 1.0f;
						}
						else if (g_Player_max_size > m_Facility_next_Size_num[g_Bar_Level - 1] &&
							*m_Facility_next_Mat_type[g_Bar_Level - 1] >= m_Facility_next_Mat_num[g_Bar_Level - 1])
						{
							//▽レベルUP可能時の処理
							//左クリックされたらフラグを立て、最終確認ウインドウを開く
							m_finalcheck_f = true;//最終確認ウインドウを表示する

							//簡易メッセージを非表示にする
							m_alpha = 0.0f;

							m_Bar_Lvup_color = INI_COLOR;

							//レベルアップ音
							Audio::Start(1);

							return;
						}
						else
						{
							//▽レベルUP不可時の処理
							//左クリックされたら簡易メッセージ画像でレベルUP不可を伝える
							//LvUP出来ません文字画像を読み込み127番に登録
							Draw::LoadImage(L"img\\テキスト\\育成画面\\LvUP出来ません.png", 127, TEX_SIZE_512);//簡易メッセージ画像読み込み番号に画像データを入れる

							//切り取り位置を設定する
							m_message_clip_right = 937.0f;
							m_message_clip_bottom = 112.0f;

							//描画位置を設定する
							m_message_draw_left = -100.0f;
							m_message_draw_right = 100.0f;

							//簡易メッセージのカラーを赤色にする
							m_message_red_color = 1.0f;
							m_message_green_color = 0.0f;
							m_message_blue_color = 0.0f;

							//簡易メッセージを表示する
							m_alpha = 1.0f;
						}
						//レベルアップ音
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
				m_Bar_Lvup_color = INI_COLOR;
			}


			//▼住民振り分け
			//※以下は各住民振り分け部分だが、同じ処理が多く関数化可能である。
			//（選択範囲部分も含めて、戦闘準備画面のように関数化するのが理想）
			//しかし現在、時間の余裕が無い為、関数化は見送っている。
			//余裕があれば関数化させたい。

			//住民振り分けアイコンカラー明度を毎回初期化する
			for (int i = 0; i < 4; i++)
			{
				m_Human_up_color[i] = INI_COLOR;
				m_Human_down_color[i] = INI_COLOR;
			}

			//パワー住民振り分けUP
			if (695 < m_mou_x && m_mou_x < 793 && 118 < m_mou_y && m_mou_y < 218)
			{
				m_Human_up_color[0] = 1.0f;

				//左クリックされたら振り分け関数を呼び出し、住民振り分けの処理を行う
				//※左クリックを押し続けると、自動で連続振り分け可能。
				if (m_mou_l == true)
				{
					if (m_next_time <= 0)
					{
						//キーフラグOFFの時は以下の処理を実行させない
						if (m_key_lf == false)
						{
							return;
						}
						//初回はこの処理に入る[左クリックを押すのをやめるとm_con_alo_fが"false"に戻り初回判定となる]
						else if (m_con_alo_f == false)
						{
							m_next_time = CON_PRE_TIME;//連続振り分け前の次住民振り分け時間が入る(最初のみ振り分け時間間隔が長い)
						}
						//二回目以降はこの処理に入る
						else
						{
							m_next_time = CON_MID_TIME;//連続振り分け中の次住民振り分け時間が入る(振り分け時間間隔が最初より短くなる)
						}

						m_Human_up_color[0] = 0.5f;

						g_Power_num = Allocation(g_Power_num, +1);//振り分け関数を呼び出す

						//振り分けボタン音
						Audio::Start(5);
					}
					else
					{
						m_con_alo_f = true;//連続振り分けフラグON
						m_next_time--;//次の住民振り分けまでの時間減少処理
						m_key_lf = true;//キーフラグON
					}
				}
				else
				{
					m_con_alo_f = false;//連続振り分けフラグOFF
					m_next_time = 0;//次の住民振り分けまでの時間を初期化
					m_key_lf = true;//キーフラグON
				}
			}

			//ディフェンス住民振り分けUP
			else if (695 < m_mou_x && m_mou_x < 793 && 228 < m_mou_y && m_mou_y < 328)
			{
				m_Human_up_color[1] = 1.0f;

				//左クリックされたら振り分け関数を呼び出し、住民振り分けの処理を行う
				//※左クリックを押し続けると、自動で連続振り分け可能。
				if (m_mou_l == true)
				{
					if (m_next_time <= 0)
					{
						//キーフラグOFFの時は以下の処理を実行させない
						if (m_key_lf == false)
						{
							return;
						}
						//初回はこの処理に入る[左クリックを押すのをやめるとm_con_alo_fが"false"に戻り初回判定となる]
						else if (m_con_alo_f == false)
						{
							m_next_time = CON_PRE_TIME;//連続振り分け前の次住民振り分け時間が入る(最初のみ振り分け時間間隔が長い)
						}
						//二回目以降はこの処理に入る
						else
						{
							m_next_time = CON_MID_TIME;//連続振り分け中の次住民振り分け時間が入る(振り分け時間間隔が最初より短くなる)
						}

						m_Human_up_color[1] = 0.5f;

						g_Defense_num = Allocation(g_Defense_num, +1);//振り分け関数を呼び出す

						//振り分けボタン音
						Audio::Start(5);
					}
					else
					{
						m_con_alo_f = true;//連続振り分けフラグON
						m_next_time--;//次の住民振り分けまでの時間減少処理
						m_key_lf = true;//キーフラグON
					}
				}
				else
				{
					m_con_alo_f = false;//連続振り分けフラグOFF
					m_next_time = 0;//次の住民振り分けまでの時間を初期化
					m_key_lf = true;//キーフラグON
				}
			}

			//スピード住民振り分けUP
			else if (695 < m_mou_x && m_mou_x < 793 && 338 < m_mou_y && m_mou_y < 438)
			{
				m_Human_up_color[2] = 1.0f;

				//左クリックされたら振り分け関数を呼び出し、住民振り分けの処理を行う
				//※左クリックを押し続けると、自動で連続振り分け可能。
				if (m_mou_l == true)
				{
					if (m_next_time <= 0)
					{
						//キーフラグOFFの時は以下の処理を実行させない
						if (m_key_lf == false)
						{
							return;
						}
						//初回はこの処理に入る[左クリックを押すのをやめるとm_con_alo_fが"false"に戻り初回判定となる]
						else if (m_con_alo_f == false)
						{
							m_next_time = CON_PRE_TIME;//連続振り分け前の次住民振り分け時間が入る(最初のみ振り分け時間間隔が長い)
						}
						//二回目以降はこの処理に入る
						else
						{
							m_next_time = CON_MID_TIME;//連続振り分け中の次住民振り分け時間が入る(振り分け時間間隔が最初より短くなる)
						}

						m_Human_up_color[2] = 0.5f;

						g_Speed_num = Allocation(g_Speed_num, +1);//振り分け関数を呼び出す

						//振り分けボタン音
						Audio::Start(5);
					}
					else
					{
						m_con_alo_f = true;//連続振り分けフラグON
						m_next_time--;//次の住民振り分けまでの時間減少処理
						m_key_lf = true;//キーフラグON
					}
				}
				else
				{
					m_con_alo_f = false;//連続振り分けフラグOFF
					m_next_time = 0;//次の住民振り分けまでの時間を初期化
					m_key_lf = true;//キーフラグON
				}
			}

			//バランス住民振り分けUP
			else if (695 < m_mou_x && m_mou_x < 793 && 448 < m_mou_y && m_mou_y < 548)
			{
				m_Human_up_color[3] = 1.0f;

				//左クリックされたら振り分け関数を呼び出し、住民振り分けの処理を行う
				//※左クリックを押し続けると、自動で連続振り分け可能。
				if (m_mou_l == true)
				{
					if (m_next_time <= 0)
					{
						//キーフラグOFFの時は以下の処理を実行させない
						if (m_key_lf == false)
						{
							return;
						}
						//初回はこの処理に入る[左クリックを押すのをやめるとm_con_alo_fが"false"に戻り初回判定となる]
						else if (m_con_alo_f == false)
						{
							m_next_time = CON_PRE_TIME;//連続振り分け前の次住民振り分け時間が入る(最初のみ振り分け時間間隔が長い)
						}
						//二回目以降はこの処理に入る
						else
						{
							m_next_time = CON_MID_TIME;//連続振り分け中の次住民振り分け時間が入る(振り分け時間間隔が最初より短くなる)
						}

						m_Human_up_color[3] = 0.5f;

						g_Balance_num = Allocation(g_Balance_num, +1);//振り分け関数を呼び出す

						//振り分けボタン音
						Audio::Start(5);
					}
					else
					{
						m_con_alo_f = true;//連続振り分けフラグON
						m_next_time--;//次の住民振り分けまでの時間減少処理
						m_key_lf = true;//キーフラグON
					}
				}
				else
				{
					m_con_alo_f = false;//連続振り分けフラグOFF
					m_next_time = 0;//次の住民振り分けまでの時間を初期化
					m_key_lf = true;//キーフラグON
				}
			}

			//パワー住民振り分けDOWN
			else if (802 < m_mou_x && m_mou_x < 902 && 118 < m_mou_y && m_mou_y < 218)
			{
				m_Human_down_color[0] = 1.0f;

				//左クリックされたら振り分け関数を呼び出し、住民振り分けの処理を行う
				//※左クリックを押し続けると、自動で連続振り分け可能。
				if (m_mou_l == true)
				{
					if (m_next_time <= 0)
					{
						//キーフラグOFFの時は以下の処理を実行させない
						if (m_key_lf == false)
						{
							return;
						}
						//初回はこの処理に入る[左クリックを押すのをやめるとm_con_alo_fが"false"に戻り初回判定となる]
						else if (m_con_alo_f == false)
						{
							m_next_time = CON_PRE_TIME;//連続振り分け前の次住民振り分け時間が入る(最初のみ振り分け時間間隔が長い)
						}
						//二回目以降はこの処理に入る
						else
						{
							m_next_time = CON_MID_TIME;//連続振り分け中の次住民振り分け時間が入る(振り分け時間間隔が最初より短くなる)
						}

						m_Human_down_color[0] = 0.5f;

						g_Power_num = Allocation(g_Power_num, -1);//振り分け関数を呼び出す

						//振り分けダウン音
						Audio::Start(2);
					}
					else
					{
						m_con_alo_f = true;//連続振り分けフラグON
						m_next_time--;//次の住民振り分けまでの時間減少処理
						m_key_lf = true;//キーフラグON
					}
				}
				else
				{
					m_con_alo_f = false;//連続振り分けフラグOFF
					m_next_time = 0;//次の住民振り分けまでの時間を初期化
					m_key_lf = true;//キーフラグON
				}
			}

			//ディフェンス住民振り分けDOWN
			else if (802 < m_mou_x && m_mou_x < 902 && 228 < m_mou_y && m_mou_y < 328)
			{
				m_Human_down_color[1] = 1.0f;

				//左クリックされたら振り分け関数を呼び出し、住民振り分けの処理を行う
				//※左クリックを押し続けると、自動で連続振り分け可能。
				if (m_mou_l == true)
				{
					if (m_next_time <= 0)
					{
						//キーフラグOFFの時は以下の処理を実行させない
						if (m_key_lf == false)
						{
							return;
						}
						//初回はこの処理に入る[左クリックを押すのをやめるとm_con_alo_fが"false"に戻り初回判定となる]
						else if (m_con_alo_f == false)
						{
							m_next_time = CON_PRE_TIME;//連続振り分け前の次住民振り分け時間が入る(最初のみ振り分け時間間隔が長い)
						}
						//二回目以降はこの処理に入る
						else
						{
							m_next_time = CON_MID_TIME;//連続振り分け中の次住民振り分け時間が入る(振り分け時間間隔が最初より短くなる)
						}

						m_Human_down_color[1] = 0.5f;

						g_Defense_num = Allocation(g_Defense_num, -1);//振り分け関数を呼び出す

						//振り分けダウン音
						Audio::Start(2);
					}
					else
					{
						m_con_alo_f = true;//連続振り分けフラグON
						m_next_time--;//次の住民振り分けまでの時間減少処理
						m_key_lf = true;//キーフラグON
					}
				}
				else
				{
					m_con_alo_f = false;//連続振り分けフラグOFF
					m_next_time = 0;//次の住民振り分けまでの時間を初期化
					m_key_lf = true;//キーフラグON
				}
			}

			//スピード住民振り分けDOWN
			else if (802 < m_mou_x && m_mou_x < 902 && 338 < m_mou_y && m_mou_y < 438)
			{
				m_Human_down_color[2] = 1.0f;

				//左クリックされたら振り分け関数を呼び出し、住民振り分けの処理を行う
				//※左クリックを押し続けると、自動で連続振り分け可能。
				if (m_mou_l == true)
				{
					if (m_next_time <= 0)
					{
						//キーフラグOFFの時は以下の処理を実行させない
						if (m_key_lf == false)
						{
							return;
						}
						//初回はこの処理に入る[左クリックを押すのをやめるとm_con_alo_fが"false"に戻り初回判定となる]
						else if (m_con_alo_f == false)
						{
							m_next_time = CON_PRE_TIME;//連続振り分け前の次住民振り分け時間が入る(最初のみ振り分け時間間隔が長い)
						}
						//二回目以降はこの処理に入る
						else
						{
							m_next_time = CON_MID_TIME;//連続振り分け中の次住民振り分け時間が入る(振り分け時間間隔が最初より短くなる)
						}

						m_Human_down_color[2] = 0.5f;

						g_Speed_num = Allocation(g_Speed_num, -1);//振り分け関数を呼び出す

						//振り分けダウン音
						Audio::Start(2);
					}
					else
					{
						m_con_alo_f = true;//連続振り分けフラグON
						m_next_time--;//次の住民振り分けまでの時間減少処理
						m_key_lf = true;//キーフラグON
					}
				}
				else
				{
					m_con_alo_f = false;//連続振り分けフラグOFF
					m_next_time = 0;//次の住民振り分けまでの時間を初期化
					m_key_lf = true;//キーフラグON
				}
			}

			//バランス住民振り分けDOWN
			else if (802 < m_mou_x && m_mou_x < 902 && 448 < m_mou_y && m_mou_y < 548)
			{
				m_Human_down_color[3] = 1.0f;

				//左クリックされたら振り分け関数を呼び出し、住民振り分けの処理を行う
				//※左クリックを押し続けると、自動で連続振り分け可能。
				if (m_mou_l == true)
				{
					if (m_next_time <= 0)
					{
						//キーフラグOFFの時は以下の処理を実行させない
						if (m_key_lf == false)
						{
							return;
						}
						//初回はこの処理に入る[左クリックを押すのをやめるとm_con_alo_fが"false"に戻り初回判定となる]
						else if (m_con_alo_f == false)
						{
							m_next_time = CON_PRE_TIME;//連続振り分け前の次住民振り分け時間が入る(最初のみ振り分け時間間隔が長い)
						}
						//二回目以降はこの処理に入る
						else
						{
							m_next_time = CON_MID_TIME;//連続振り分け中の次住民振り分け時間が入る(振り分け時間間隔が最初より短くなる)
						}

						m_Human_down_color[3] = 0.5f;

						g_Balance_num = Allocation(g_Balance_num, -1);//振り分け関数を呼び出す

						//振り分けダウン音
						Audio::Start(2);
					}
					else
					{
						m_con_alo_f = true;//連続振り分けフラグON
						m_next_time--;//次の住民振り分けまでの時間減少処理
						m_key_lf = true;//キーフラグON
					}
				}
				else
				{
					m_con_alo_f = false;//連続振り分けフラグOFF
					m_next_time = 0;//次の住民振り分けまでの時間を初期化
					m_key_lf = true;//キーフラグON
				}
			}

			//上記の範囲外にマウスカーソルがある場合の処理
			else
			{
				//範囲外にマウスカーソルがいっても左クリックを離さなければ、
				//連続振り分け状態を解除しないように設定している。
				if (m_mou_l == false)
				{
					m_con_alo_f = false;//連続振り分けフラグOFF
					m_next_time = 0;//次の住民振り分けまでの時間を初期化
					m_key_lf = true;//キーフラグON
				}
			}


			return;
		}
	}
	//ホーム画面に戻るボタンが押されたり、
	//他施設のウインドウを開いている時は操作を受け付けないようにする。
	else if (window_start_manage != Default)
	{
		m_introduce_f = false;	//施設紹介ウインドウを非表示にする(右クリックでホーム画面に戻る際、ウインドウが残らないようにするため)
		return;
	}

	//dst.m_top = 230.0f;
	//dst.m_left = 400.0f;
	//dst.m_right = 800.0f;
	//dst.m_bottom = 630.0f;

	//兵舎選択範囲
	if (g_tutorial_progress == 12 || g_tutorial_progress >= 14)//チュートリアル中は選択不可
	{
		if (
			((g_Bar_Level == 1) && (450 < m_mou_x && m_mou_x < 650 && 395 < m_mou_y && m_mou_y < 520)) ||		//兵舎レベル1の時の判定処理
			((g_Bar_Level == 2) && 420 < m_mou_x && m_mou_x < 650 && 270 < m_mou_y && m_mou_y < 520 && !(472< m_mou_x&& m_mou_x <671 && 276 < m_mou_y && m_mou_y <400)) ||	//兵舎レベル2の時の判定処理
			((g_Bar_Level == 3) && (420 < m_mou_x && m_mou_x < 778 && 270 < m_mou_y && m_mou_y < 520) && !(472< m_mou_x&& m_mou_x <789 && 264 < m_mou_y && m_mou_y <394))		//兵舎レベル3の時の判定処理
			)
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

					//選択音
					Audio::Start(1);

					if (g_tutorial_progress == 12)
					{
						//矢印を非表示にさせる
						CObjMessage* message = (CObjMessage*)Objs::GetObj(OBJ_MESSAGE);
						message->Setarrow(0);
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
			m_introduce_f = false;//施設紹介ウインドウを非表示にする
			m_Bar_color = INI_COLOR;
		}
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
	float blue[4] = { 0.5f,0.5f,1.0f,1.0f };

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

	//最終確認[はい]ボタン用
	float Yes[4] = { 1.0f,m_Yes_Button_color,m_Yes_Button_color,1.0f };

	//最終確認[いいえ]ボタン用
	float No[4] = { m_No_Button_color,m_No_Button_color,1.0f,1.0f };

	//簡易メッセージ画像用
	float message[4] = { m_message_red_color,m_message_green_color,m_message_blue_color,m_alpha };

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
	if (window_start_manage == Default || window_start_manage == BackButton || window_start_manage == EatButton)
	{
		//▼兵舎表示 
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 400.0f;
		src.m_bottom = 400.0f;

		dst.m_top = 230.0f;
		dst.m_left = 400.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 630.0f;
		Draw::Draw(2 + (g_Bar_Level - 1) * 3, &src, &dst, bar, 0.0f);

		//施設紹介ウインドウ表示管理フラグがtrueの時、描画。
		if (m_introduce_f == true)
		{
			//▼施設紹介ウインドウ表示左上
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 790.0f;
			src.m_bottom = 800.0f;

			dst.m_top = m_mou_y - 50.0f;
			dst.m_left = m_mou_x - 120.0f;
			dst.m_right = m_mou_x - 40.0f;
			dst.m_bottom = m_mou_y - 30.0f;
			Draw::Draw(21, &src, &dst, white, 0.0f);

			//▼施設紹介ウインドウ表示左下
			src.m_top = 10.0f;
			src.m_left = 800.0f;
			src.m_right = 1595.0f;
			src.m_bottom = 800.0f;

			dst.m_top = m_mou_y - 30.0f;
			dst.m_left = m_mou_x - 120.0f;
			dst.m_right = m_mou_x - 40.0f;
			dst.m_bottom = m_mou_y - 10.0f;
			Draw::Draw(21, &src, &dst, white, 0.0f);

			//▼施設紹介ウインドウ表示中央上
			src.m_top = 0.0f;
			src.m_left = 1600.0f;
			src.m_right = 2400.0f;
			src.m_bottom = 800.0f;

			dst.m_top = m_mou_y - 50.0f;
			dst.m_left = m_mou_x - 40.0f;
			dst.m_right = m_mou_x + 40.0f;
			dst.m_bottom = m_mou_y - 30.0f;
			Draw::Draw(21, &src, &dst, white, 0.0f);

			//▼施設紹介ウインドウ表示中央下
			src.m_top = 0.0f;
			src.m_left = 2400.0f;
			src.m_right = 3200.0f;
			src.m_bottom = 800.0f;

			dst.m_top = m_mou_y - 30.0f;
			dst.m_left = m_mou_x - 40.0f;
			dst.m_right = m_mou_x + 40.0f;
			dst.m_bottom = m_mou_y - 10.0f;
			Draw::Draw(21, &src, &dst, white, 0.0f);

			//▼施設紹介ウインドウ表示右上
			src.m_top = 0.0f;
			src.m_left = 4000.0f;
			src.m_right = 4800.0f;
			src.m_bottom = 800.0f;

			dst.m_top = m_mou_y - 50.0f;
			dst.m_left = m_mou_x + 40.0f;
			dst.m_right = m_mou_x + 120.0f;
			dst.m_bottom = m_mou_y - 30.0f;
			Draw::Draw(21, &src, &dst, white, 0.0f);

			//▼施設紹介ウインドウ表示中央下
			src.m_top = 0.0f;
			src.m_left = 4805.0f;
			src.m_right = 5600.0f;
			src.m_bottom = 800.0f;

			dst.m_top = m_mou_y - 30.0f;
			dst.m_left = m_mou_x + 40.0f;
			dst.m_right = m_mou_x + 120.0f;
			dst.m_bottom = m_mou_y - 10.0f;
			Draw::Draw(21, &src, &dst, white, 0.0f);

			//▼兵舎 Lv文字画像表示
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 508.0f;
			src.m_bottom = 117.0f;

			dst.m_top = m_mou_y - 43.0f;
			dst.m_left = m_mou_x - 70.0f;
			dst.m_right = m_mou_x + 35.0f;
			dst.m_bottom = m_mou_y - 18.0f;
			Draw::Draw(116, &src, &dst, white, 0.0f);

			//▼兵舎レベル
			FontDraw(NumConversion(g_Bar_Level), m_mou_x + 45.0f, m_mou_y - 45.5f, 30.0f, 30.0f, white, true);

			////▼フォント表示
			////兵舎レベル
			//Font::StrDraw(Bar, m_mou_x - 75.0f, m_mou_y - 45.0f, 30.0f, black);
		}
	}

	//兵舎ウインドウ開いている際に表示するグラフィック
	else if (window_start_manage == Barracks)
	{
		//▼ウィンドウ表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1200.0f;
		src.m_bottom = 700.0f;

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

		dst.m_top = 60.0f;
		dst.m_left = 70.0f;
		dst.m_right = 120.0f;
		dst.m_bottom = 110.0f;
		Draw::Draw(1, &src, &dst, back, 0.0f);

		//▼兵舎表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 400.0f;
		src.m_bottom = 400.0f;

		dst.m_top = 150.0f;
		dst.m_left = 150.0f;
		dst.m_right = 450.0f;
		dst.m_bottom = 390.0f;
		Draw::Draw(2 + (g_Bar_Level - 1) * 3, &src, &dst, white, 0.0f);

		//▼兵舎LVUP表示
		//▼研究所LVUP表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 120.0f;
		src.m_bottom = 150.0f;

		dst.m_top = 470.0f;
		dst.m_left = 48.0f;
		dst.m_right = 148.0f;
		dst.m_bottom = 620.0f;
		Draw::Draw(22, &src, &dst, Lvup, 0.0f);

		//▼レベルUP条件ウインドウ表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1200.0f;
		src.m_bottom = 700.0f;

		dst.m_top = 420.0f;
		dst.m_left = 150.0f;
		dst.m_right = 450.0f;
		dst.m_bottom = 650.0f;
		Draw::Draw(134, &src, &dst, white, 0.0f);

		//▼残り住民数のウインドウ表示
		//▼研究員の住民数ウインドウ表示
		//左上
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 795.0f;
		src.m_bottom = 800.0f;

		dst.m_top = 580.0f;
		dst.m_left = 750.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 630.0;
		Draw::Draw(132, &src, &dst, white, 0.0f);

		//左下
		src.m_top = 40.0f;
		src.m_left = 800.0f;
		src.m_right = 1600.0f;
		src.m_bottom = 800.0f;

		dst.m_top = 600.0f;
		dst.m_left = 750.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 650.0f;
		Draw::Draw(132, &src, &dst, white, 0.0f);

		for (int j = 0; j < 6; j++)
		{
			//中央上
			src.m_top = 0.0f;
			src.m_left = 1600.0f;
			src.m_right = 2400.0f;
			src.m_bottom = 800.0f;

			dst.m_top = 580.0f;
			dst.m_left = 800.0f + (j * 50);
			dst.m_right = 850.0f + (j * 50);
			dst.m_bottom = 630.0f;
			Draw::Draw(132, &src, &dst, white, 0.0f);

			//中央下
			src.m_top = 0.0f;
			src.m_left = 2400.0f;
			src.m_right = 3200.0f;
			src.m_bottom = 800.0f;

			dst.m_top = 600.0f;
			dst.m_left = 800.0f + (j * 50);
			dst.m_right = 850.0f + (j * 50);
			dst.m_bottom = 650.0f;
			Draw::Draw(132, &src, &dst, white, 0.0f);
		}

		//右上
		src.m_top = 0.0f;
		src.m_left = 4000.0f;
		src.m_right = 4800.0f;
		src.m_bottom = 800.0f;

		dst.m_top = 580.0f;
		dst.m_left = 1080.0f;
		dst.m_right = 1130.0f;
		dst.m_bottom = 630.0f;
		Draw::Draw(132, &src, &dst, white, 0.0f);

		//右下
		src.m_top = 0.0f;
		src.m_left = 4800.0f;
		src.m_right = 5600.0f;
		src.m_bottom = 800.0f;

		dst.m_top = 600.0f;
		dst.m_left = 1080.0f;
		dst.m_right = 1130.0f;
		dst.m_bottom = 650.0f;
		Draw::Draw(132, &src, &dst, white, 0.0f);

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
			dst.m_top = 140.0f + i * 110.0f;
			dst.m_left = 930.0f;
			dst.m_right = 1150.0f;
			dst.m_bottom = 200.0f + i * 110.0f;
			Draw::Draw(20, &src, &dst, white, 0.0f);
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 795.0f;
			src.m_bottom = 800.0f;

			dst.m_top = 140.0f + i * 110.0f;
			dst.m_left = 930.0f;
			dst.m_right = 970.0f;
			dst.m_bottom = 180.0f + i * 110.0f;
			Draw::Draw(132, &src, &dst, white, 0.0f);

			//左下
			src.m_top = 40.0f;
			src.m_left = 800.0f;
			src.m_right = 1600.0f;
			src.m_bottom = 800.0f;

			dst.m_top = 160.0f + i * 110.0f;
			dst.m_left = 930.0f;
			dst.m_right = 970.0f;
			dst.m_bottom = 200.0f + i * 110.0f;
			Draw::Draw(132, &src, &dst, white, 0.0f);

			for (int j = 0; j < 4; j++)
			{
				//中央上
				src.m_top = 0.0f;
				src.m_left = 1600.0f;
				src.m_right = 2400.0f;
				src.m_bottom = 800.0f;

				dst.m_top = 140.0f + i * 110.0f;
				dst.m_left = 970.0f + (j * 40);
				dst.m_right = 1010.0f + (j * 40);
				dst.m_bottom = 180.0f + i * 110.0f;
				Draw::Draw(132, &src, &dst, white, 0.0f);

				//中央下
				src.m_top = 0.0f;
				src.m_left = 2400.0f;
				src.m_right = 3200.0f;
				src.m_bottom = 800.0f;

				dst.m_top = 160.0f + i * 110.0f;
				dst.m_left = 970.0f + (j * 40);
				dst.m_right = 1010.0f + (j * 40);
				dst.m_bottom = 200.0f + i * 110.0f;
				Draw::Draw(132, &src, &dst, white, 0.0f);
			}

			//右上
			src.m_top = 0.0f;
			src.m_left = 4000.0f;
			src.m_right = 4800.0f;
			src.m_bottom = 800.0f;

			dst.m_top = 140.0f + i * 110.0f;
			dst.m_left = 1110.0f;
			dst.m_right = 1150.0f;
			dst.m_bottom = 180.0f + i * 110.0f;
			Draw::Draw(132, &src, &dst, white, 0.0f);

			//右下
			src.m_top = 0.0f;
			src.m_left = 4800.0f;
			src.m_right = 5600.0f;
			src.m_bottom = 800.0f;

			dst.m_top = 160.0f + i * 110.0f;
			dst.m_left = 1110.0f;
			dst.m_right = 1150.0f;
			dst.m_bottom = 200.0f + i * 110.0f;
			Draw::Draw(132, &src, &dst, white, 0.0f);


		}

		//▼兵舎 Lv文字画像表示
		src.m_top = 2.0f;
		src.m_left = 0.0f;
		src.m_right = 508.0f;
		src.m_bottom = 117.0f;

		dst.m_top = 120.0f;
		dst.m_left = 130.0f;
		dst.m_right = 380.0f;
		dst.m_bottom = 170.0f;
		Draw::Draw(116, &src, &dst, white, 0.0f);

		//▼兵舎レベルUP文字画像表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 805.0f;
		src.m_bottom = 117.0f;

		dst.m_top = 350.0f;
		dst.m_left = 80.0f;
		dst.m_right = 430.0f;
		dst.m_bottom = 400.0f;
		Draw::Draw(117, &src, &dst, white, 0.0f);

		//▼住民振り分け文字画像表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 742.0f;
		src.m_bottom = 117.0f;

		dst.m_top = 50.0f;
		dst.m_left = 620.0f;
		dst.m_right = 980.0f;
		dst.m_bottom = 110.0f;
		Draw::Draw(76, &src, &dst, white, 0.0f);

		//▼レッド文字画像表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 336.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 145.0f;
		dst.m_left = 505.0f;
		dst.m_right = 670.0f;
		dst.m_bottom = 200.0f;
		Draw::Draw(82, &src, &dst, red, 0.0f);

		//▼ブルー文字画像表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 352.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 260.0f;
		dst.m_left = 505.0f;
		dst.m_right = 670.0f;
		dst.m_bottom = 310.0f;
		Draw::Draw(83, &src, &dst, blue, 0.0f);

		//▼グリーン文字画像表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 472.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 365.0f;
		dst.m_left = 480.0f;
		dst.m_right = 680.0f;
		dst.m_bottom = 415.0f;
		Draw::Draw(84, &src, &dst, green, 0.0f);

		//▼ホワイト文字画像表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 464.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 475.0f;
		dst.m_left = 480.0f;
		dst.m_right = 680.0f;
		dst.m_bottom = 525.0f;
		Draw::Draw(85, &src, &dst, white, 0.0f);

		//▼人文字画像表示一段目
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 112.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 145.0f;
		dst.m_left = 1090.0f;
		dst.m_right = 1140.0f;
		dst.m_bottom = 195.0f;
		Draw::Draw(77, &src, &dst, black, 0.0f);


		//▼人文字画像表示一段目
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 112.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 255.0f;
		dst.m_left = 1090.0f;
		dst.m_right = 1140.0f;
		dst.m_bottom = 305.0f;
		Draw::Draw(77, &src, &dst, black, 0.0f);

		//▼人文字画像表示一段目
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 112.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 365.0f;
		dst.m_left = 1090.0f;
		dst.m_right = 1140.0f;
		dst.m_bottom = 415.0f;
		Draw::Draw(77, &src, &dst, black, 0.0f);

		//▼人文字画像表示一段目
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 112.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 475.0f;
		dst.m_left = 1090.0f;
		dst.m_right = 1140.0f;
		dst.m_bottom = 525.0f;
		Draw::Draw(77, &src, &dst, black, 0.0f);

		//▼残り　　　人文字画像表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 712.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 590.0f;
		dst.m_left = 770.0f;
		dst.m_right = 1130.0f;
		dst.m_bottom = 640.0f;
		Draw::Draw(78, &src, &dst, black, 0.0f);

		//▼フォント表示
		//兵舎レベル
		src.m_top = 1250.0f;
		src.m_left = CUT_ZERO + (g_Bar_Level * 125);
		src.m_right = END_ZERO + (g_Bar_Level * 125);
		src.m_bottom = 1375.0f;

		dst.m_top = 117;
		dst.m_left = 385;
		dst.m_right = 435;
		dst.m_bottom = 172;
		Draw::Draw(121, &src, &dst, white, 0.0f);
		//Font::StrDraw(Bar, 125.0f, 95.0f, 50.0f, white);
		//残り住民数ー--------ーーーーーーーーーーーーーーーーーーーーー
		//万の位
		if (g_Remain_num >= 10000) {

			src.m_top = 1250.0f;
			src.m_left = CUT_ZERO + (floor(g_Remain_num / 10000) * 125);
			src.m_right = END_ZERO + (floor(g_Remain_num / 10000) * 125);
			src.m_bottom = 1375.0f;

			dst.m_top = 590;
			dst.m_left = 920;
			dst.m_right = 950;
			dst.m_bottom = 640;
			Draw::Draw(120, &src, &dst, black, 0.0f);
		}
		//千の位
		if (g_Remain_num >= 1000) {
			src.m_top = 1250.0f;
			src.m_left = CUT_ZERO + (floor((g_Remain_num / 1000) % 10) * 125);
			src.m_right = END_ZERO + (floor((g_Remain_num / 1000) % 10) * 125);
			src.m_bottom = 1375.0f;

			dst.m_top = 590;
			dst.m_left = 950;
			dst.m_right = 980;
			dst.m_bottom = 640;
			Draw::Draw(120, &src, &dst, black, 0.0f);
		}
		//百の位
		if (g_Remain_num >= 100) {
			src.m_top = 1250.0f;
			src.m_left = CUT_ZERO + (floor((g_Remain_num / 100) % 10) * 125);
			src.m_right = END_ZERO + (floor((g_Remain_num / 100) % 10) * 125);
			src.m_bottom = 1375.0f;

			dst.m_top = 590;
			dst.m_left = 980;
			dst.m_right = 1010;
			dst.m_bottom = 640;
			Draw::Draw(120, &src, &dst, black, 0.0f);

			//十の位の0
			src.m_top = 1250.0f;
			src.m_left = CUT_ZERO;
			src.m_right = END_ZERO;
			src.m_bottom = 1375.0f;

			dst.m_top = 590;
			dst.m_left = 1010;
			dst.m_right = 1040;
			dst.m_bottom = 640;
			Draw::Draw(120, &src, &dst, black, 0.0f);
		}

		//一の位
		src.m_top = 1250.0f;
		src.m_left = CUT_ZERO;
		src.m_right = END_ZERO;
		src.m_bottom = 1375.0f;

		dst.m_top = 590;
		dst.m_left = 1040;
		dst.m_right = 1070;
		dst.m_bottom = 640;
		Draw::Draw(120, &src, &dst, black, 0.0f);
		//Font::StrDraw(human_remain, 780.0f, 590.0f, 50.0f, black);
		//----------------------------------------------------------------------------------------------

		//各タイプ(パワー、スピード等)の住民数-------------------------------------------------------------
		for (int i = 0; i < 4; i++){

			switch (i) {
			case 0:
				m_Warrior[i] = g_Power_num;
				break;
			case 1:
				m_Warrior[i] = g_Defense_num;
				break;
			case 2:
				m_Warrior[i] = g_Speed_num;
				break;
			case 3:
				m_Warrior[i] = g_Balance_num;
			}

			if (m_Warrior[i] >= 10000) {

				src.m_top = 1250.0f;
				src.m_left = CUT_ZERO + (floor(m_Warrior[i] / 10000) * 125);
				src.m_right = END_ZERO + (floor(m_Warrior[i] / 10000) * 125);
				src.m_bottom = 1375.0f;

				dst.m_top = 150 + (i * 110);
				dst.m_left = 940;
				dst.m_right = 970;
				dst.m_bottom = 190 + (i * 110);
				Draw::Draw(120, &src, &dst, black, 0.0f);
			}
			//千の位
			if (m_Warrior[i] >= 1000) {
				src.m_top = 1250.0f;
				src.m_left = CUT_ZERO + (floor((m_Warrior[i] / 1000) % 10) * 125);
				src.m_right = END_ZERO + (floor((m_Warrior[i] / 1000) % 10) * 125);
				src.m_bottom = 1375.0f;

				dst.m_top = 150 + (i * 110);
				dst.m_left = 970;
				dst.m_right = 1000;
				dst.m_bottom = 190 + (i * 110);
				Draw::Draw(120, &src, &dst, black, 0.0f);
			}
			//百の位
			if (m_Warrior[i] >= 100) {
				src.m_top = 1250.0f;
				src.m_left = CUT_ZERO + (floor((m_Warrior[i] / 100) % 10) * 125);
				src.m_right = END_ZERO + (floor((m_Warrior[i] / 100) % 10) * 125);
				src.m_bottom = 1375.0f;

				dst.m_top = 150 + (i * 110);
				dst.m_left = 1000;
				dst.m_right = 1030;
				dst.m_bottom = 190 + (i * 110);
				Draw::Draw(120, &src, &dst, black, 0.0f);

				//十の位の0
				src.m_top = 1250.0f;
				src.m_left = CUT_ZERO;
				src.m_right = END_ZERO;
				src.m_bottom = 1375.0f;

				dst.m_top = 150 + (i * 110);
				dst.m_left = 1030;
				dst.m_right = 1060;
				dst.m_bottom = 190 + (i * 110);
				Draw::Draw(120, &src, &dst, black, 0.0f);
			}

			//一の位
			src.m_top = 1250.0f;
			src.m_left = CUT_ZERO;
			src.m_right = END_ZERO;
			src.m_bottom = 1375.0f;

			dst.m_top = 150 + (i * 110);
			dst.m_left = 1060;
			dst.m_right = 1090;
			dst.m_bottom = 190 + (i * 110);
			Draw::Draw(120, &src, &dst, black, 0.0f);
		}	
		//Font::StrDraw(human_num[i], 950.0f, 150.0f + i * 110.0f, 40.0f, black);
		//-------------------------------------------------------------------------------

		//その他フォント
		Facility_message(g_Bar_Level);//兵舎の必要素材&サイズメッセージ描画関数呼び出す


		//▼簡易メッセージ画像表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = m_message_clip_right;
		src.m_bottom = m_message_clip_bottom;

		dst.m_top = m_mou_y + MES_DRAW_TOP;
		dst.m_left = m_mou_x + m_message_draw_left;
		dst.m_right = m_mou_x + m_message_draw_right;
		dst.m_bottom = m_mou_y + MES_DRAW_BOTTOM;
		Draw::Draw(127, &src, &dst, message, 0.0f);


		//▼最終確認ウインドウ表示管理フラグがtrueの時、描画。
		if (m_finalcheck_f == true)
		{
			//▼最終確認ウインドウ表示
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 1200.0f;
			src.m_bottom = 700.0f;

			dst.m_top = 220.0f;
			dst.m_left = 320.0f;
			dst.m_right = 880.0f;
			dst.m_bottom = 480.0f;
			Draw::Draw(20, &src, &dst, white, 0.0f);

			//▼惑星HP文字画像表示
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 412.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 250.0f;
			dst.m_left = 345.0f;
			dst.m_right = 465.0f;
			dst.m_bottom = 280.0f;
			Draw::Draw(67, &src, &dst, white, 0.0f);

			//「と」の文字画像をFontDraw関数にて表示
			FontDraw(L"と", 466.0f, 250.0, 30.0f, 30.0f, white, false);

			//▼素材消費して文字画像表示
			src.m_top = 2.0f;
			src.m_left = 0.0f;
			src.m_right = 717.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 250.0f;
			dst.m_left = 497.0f;
			dst.m_right = 677.0f;
			dst.m_bottom = 280.0f;
			Draw::Draw(72, &src, &dst, white, 0.0f);

			//▼レベルアップしますか？文字画像表示
			src.m_top = 2.0f;
			src.m_left = 717.0f;
			src.m_right = 2017.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 300.0f;
			dst.m_left = 520.0f;
			dst.m_right = 850.0f;
			dst.m_bottom = 330.0f;
			Draw::Draw(72, &src, &dst, white, 0.0f);

			//▼はい文字画像表示
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 232.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 410.0f;
			dst.m_left = 410.0f;
			dst.m_right = 510.0f;
			dst.m_bottom = 460.0f;
			Draw::Draw(73, &src, &dst, Yes, 0.0f);

			//▼いいえ文字画像表示
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 352.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 410.0f;
			dst.m_left = 650.0f;
			dst.m_right = 800.0f;
			dst.m_bottom = 460.0f;
			Draw::Draw(74, &src, &dst, No, 0.0f);
		}
		//デバッグ用仮マウス位置表示
		//wchar_t str[256];
		//swprintf_s(str, L"x=%f,y=%f", m_mou_x, m_mou_y);
		//Font::StrDraw(str, 20.0f, 20.0f, 12.0f, white);
	}
}