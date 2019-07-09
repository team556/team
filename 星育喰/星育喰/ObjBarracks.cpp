//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

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
	m_Yes_Button_color = 0.0f;
	m_No_Button_color = 0.0f;

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
	m_alpha = INI_ALPHA;

	//▼兵舎の次のLVUPに必要なサイズ(HP)の住民数設定
	m_Facility_next_Size_num[0] = 5.0f; //レベルが1の時の必要サイズ(HP)
	m_Facility_next_Size_num[1] = 4.0f;	//レベルが2の時の必要サイズ(HP)

	//▼兵舎の次のLVUPに必要な素材の名前設定
	swprintf_s(m_Facility_next_Mat_name[0], L"木材");			 //レベルが1の時の必要素材名
	swprintf_s(m_Facility_next_Mat_name[1], L"プラスチック");//レベルが2の時の必要素材名

	//▼兵舎の次のLVUPに必要な素材種類設定と同時にその素材の所持数を代入する
	//※以下のように所持素材数を管理しているグローバル変数のアドレスを代入する事で素材の種類設定と所持数の代入をしている。
	//ただし現在は素材種類が確定していないため、仮でTEST用の物を入れている。後で適切なものに変更すべし。
	m_Facility_next_Mat_type[0] = &g_Wood_num;	//レベルが1の時の必要素材種類
	m_Facility_next_Mat_type[1] = &g_Plastic_num;	//レベルが2の時の必要素材種類

	//▼兵舎の次のLVUPに必要な素材数設定
	m_Facility_next_Mat_num[0] = 50;		//レベルが1の時の必要素材数
	m_Facility_next_Mat_num[1] = 40;	//レベルが2の時の必要素材数


	//当たり判定用HitBoxを作成(Objhuman用)
	Hits::SetHitBox(this, 810, 460, 380, 230, ELEMENT_ENEMY, OBJ_BARRACKS, 1);
}

//アクション
void CObjBarracks::Action()
{
	//ホワイトアウト演出中は操作不能にする処理
	if (white_out_f == true)
	{
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
				m_Yes_Button_color = 1.0f;

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
						
						m_Yes_Button_color = 0.0f;

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

		//戻るボタン左クリック、もしくは右クリック(どこでも)する事で兵舎ウインドウを閉じる
		if (30 < m_mou_x && m_mou_x < 80 && 30 < m_mou_y && m_mou_y < 80 || m_mou_r == true)
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

					//ObjHelpを操作可能にする & 透過度1.0fにして表示する
					CObjHelp* help = (CObjHelp*)Objs::GetObj(OBJ_HELP);
					help->SetOperatable(true);
					help->SetAlpha(1.0f);

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
						//左クリックされたら簡易メッセージでレベルUP不可を伝える
						swprintf_s(m_message, L"LvUP出来ません");//文字配列に文字データを入れる

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
						//左クリックされたら簡易メッセージでレベルUP不可を伝える
						swprintf_s(m_message, L"LvUP出来ません");//文字配列に文字データを入れる

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
					//初回はこの処理に入る[左クリックを押すのをやめるとm_con_alo_fが"false"に戻り初回判定となる]
					if (m_con_alo_f == false)
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
					Audio::Start(1);
				}
				else
				{
					m_con_alo_f = true;//連続振り分けフラグON
					m_next_time--;//次の住民振り分けまでの時間減少処理
				}
			}
			else
			{
				m_con_alo_f = false;//連続振り分けフラグOFF
				m_next_time = 0;//次の住民振り分けまでの時間を初期化
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
					//初回はこの処理に入る[左クリックを押すのをやめるとm_con_alo_fが"false"に戻り初回判定となる]
					if (m_con_alo_f == false)
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
					Audio::Start(1);
				}
				else
				{
					m_con_alo_f = true;//連続振り分けフラグON
					m_next_time--;//次の住民振り分けまでの時間減少処理
				}
			}
			else
			{
				m_con_alo_f = false;//連続振り分けフラグOFF
				m_next_time = 0;//次の住民振り分けまでの時間を初期化
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
					//初回はこの処理に入る[左クリックを押すのをやめるとm_con_alo_fが"false"に戻り初回判定となる]
					if (m_con_alo_f == false)
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
					Audio::Start(1);
				}
				else
				{
					m_con_alo_f = true;//連続振り分けフラグON
					m_next_time--;//次の住民振り分けまでの時間減少処理
				}
			}
			else
			{
				m_con_alo_f = false;//連続振り分けフラグOFF
				m_next_time = 0;//次の住民振り分けまでの時間を初期化
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
					//初回はこの処理に入る[左クリックを押すのをやめるとm_con_alo_fが"false"に戻り初回判定となる]
					if (m_con_alo_f == false)
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
					Audio::Start(1);
				}
				else
				{
					m_con_alo_f = true;//連続振り分けフラグON
					m_next_time--;//次の住民振り分けまでの時間減少処理
				}
			}
			else
			{
				m_con_alo_f = false;//連続振り分けフラグOFF
				m_next_time = 0;//次の住民振り分けまでの時間を初期化
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
					//初回はこの処理に入る[左クリックを押すのをやめるとm_con_alo_fが"false"に戻り初回判定となる]
					if (m_con_alo_f == false)
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
				}
			}
			else
			{
				m_con_alo_f = false;//連続振り分けフラグOFF
				m_next_time = 0;//次の住民振り分けまでの時間を初期化
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
					//初回はこの処理に入る[左クリックを押すのをやめるとm_con_alo_fが"false"に戻り初回判定となる]
					if (m_con_alo_f == false)
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
				}
			}
			else
			{
				m_con_alo_f = false;//連続振り分けフラグOFF
				m_next_time = 0;//次の住民振り分けまでの時間を初期化
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
					//初回はこの処理に入る[左クリックを押すのをやめるとm_con_alo_fが"false"に戻り初回判定となる]
					if (m_con_alo_f == false)
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
				}
			}
			else
			{
				m_con_alo_f = false;//連続振り分けフラグOFF
				m_next_time = 0;//次の住民振り分けまでの時間を初期化
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
					//初回はこの処理に入る[左クリックを押すのをやめるとm_con_alo_fが"false"に戻り初回判定となる]
					if (m_con_alo_f == false)
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
				}
			}
			else
			{
				m_con_alo_f = false;//連続振り分けフラグOFF
				m_next_time = 0;//次の住民振り分けまでの時間を初期化
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
			}
		}


		return;
	}
	//ホーム画面に戻るボタンが押されたり、
	//他施設のウインドウを開いている時は操作を受け付けないようにする。
	else if (window_start_manage != Default || g_help_f == true)
	{
		m_introduce_f = false;	//施設紹介ウインドウを非表示にする(右クリックでホーム画面に戻る際、ウインドウが残らないようにするため)
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

				//ObjHelpを操作不能にする & 透過度0.0fにして非表示にする
				CObjHelp* help = (CObjHelp*)Objs::GetObj(OBJ_HELP);
				help->SetOperatable(false);
				help->SetAlpha(0.0f);

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

	//最終確認[はい]ボタン用
	float Yes[4] = { m_Yes_Button_color,0.0f,0.0f,1.0f };

	//最終確認[いいえ]ボタン用
	float No[4] = { 0.0f,0.0f,m_No_Button_color,1.0f };

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
		Draw::Draw(2 + (g_Bar_Level - 1) * 3, &src, &dst, bar, 0.0f);

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

			////▼兵舎 Lv文字画像表示
			//src.m_top = 0.0f;
			//src.m_left = 0.0f;
			//src.m_right = 508.0f;
			//src.m_bottom = 117.0f;

			//dst.m_top = m_mou_y - 45.0f;
			//dst.m_left = m_mou_x - 75.0f;
			//dst.m_right = m_mou_x + 40.0f;
			//dst.m_bottom = m_mou_y - 15.0f;
			//Draw::Draw(116, &src, &dst, black, 0.0f);

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
		src.m_right = 256.0f;
		src.m_bottom = 256.0f;

		dst.m_top = 150.0f;
		dst.m_left = 100.0f;
		dst.m_right = 400.0f;
		dst.m_bottom = 350.0f;
		Draw::Draw(2 + (g_Bar_Level - 1) * 3, &src, &dst, white, 0.0f);

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
			Draw::Draw(120, &src, &dst, up[i], 0.0f);

			//▼兵舎振り分けDOWN表示
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 64.0f;
			src.m_bottom = 64.0f;

			dst.m_top = 120.0f + i * 110.0f;
			dst.m_left = 810.0f;
			dst.m_right = 910.0f;
			dst.m_bottom = 220.0f + i * 110.0f;
			Draw::Draw(121, &src, &dst, down[i], 0.0f);

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

		////▼兵舎 Lv文字画像表示
		//src.m_top = 0.0f;
		//src.m_left = 0.0f;
		//src.m_right = 508.0f;
		//src.m_bottom = 117.0f;

		//dst.m_top = 95.0f;
		//dst.m_left = 125.0f;
		//dst.m_right = 325.0f;
		//dst.m_bottom = 145.0f;
		//Draw::Draw(116, &src, &dst, white, 0.0f);

		////▼兵舎レベルUP文字画像表示
		//src.m_top = 0.0f;
		//src.m_left = 0.0f;
		//src.m_right = 805.0f;
		//src.m_bottom = 117.0f;

		//dst.m_top = 370.0f;
		//dst.m_left = 60.0f;
		//dst.m_right = 410.0f;
		//dst.m_bottom = 420.0f;
		//Draw::Draw(117, &src, &dst, white, 0.0f);

		////▼住民振り分け文字画像表示
		//src.m_top = 0.0f;
		//src.m_left = 0.0f;
		//src.m_right = 742.0f;
		//src.m_bottom = 117.0f;

		//dst.m_top = 45.0f;
		//dst.m_left = 620.0f;
		//dst.m_right = 980.0f;
		//dst.m_bottom = 105.0f;
		//Draw::Draw(76, &src, &dst, white, 0.0f);

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
		//Font::StrDraw(L"兵舎レベルＵＰ", 60.0f, 370.0f, 50.0f, white);

		//Font::StrDraw(L"住民振り分け", 620.0f, 45.0f, 60.0f, white);

		//Font::StrDraw(L"パワー", 505.0f, 145.0f, 55.0f, red);

		//Font::StrDraw(L"ディフェンス", 450.0f, 260.0f, 40.0f, blue);

		//Font::StrDraw(L"スピード", 480.0f, 365.0f, 50.0f, green);

		//Font::StrDraw(L"バランス", 480.0f, 475.0f, 50.0f, white);

		Facility_message(g_Bar_Level);//兵舎の必要素材&サイズメッセージ描画関数呼び出す

		//エラーメッセージ
		Font::StrDraw(m_message, m_mou_x - 110.0f, m_mou_y - 45.0f, 30.0f, error);
		

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



		//デバッグ用仮マウス位置表示
		//wchar_t str[256];
		//swprintf_s(str, L"x=%f,y=%f", m_mou_x, m_mou_y);
		//Font::StrDraw(str, 20.0f, 20.0f, 12.0f, white);
	}
}