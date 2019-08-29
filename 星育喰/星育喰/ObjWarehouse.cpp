//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjWarehouse.h"
#include "UtilityModule.h"

//使用するネームスペース
using namespace GameL;

//マクロ
#define INI_ALPHA (0.0f) //透過度(アルファ値)の初期値
#define INI_COLOR (0.9f) //全カラー明度の初期値

//グローバル変数の定義
//int g_Ware = 1;


//イニシャライズ
void CObjWarehouse::Init()
{
	m_Ware_color = INI_COLOR;			//倉庫オブジェクトカラー
	m_Back_Button_color = INI_COLOR;	//戻るボタンカラー
	m_object_ma = INI_COLOR;			//資材確認ボタンカラー
	m_object_re = INI_COLOR;			//住民確認ボタンカラー
	m_object_sp = INI_COLOR;			//スペシャル技確認ボタンカラー
	m_object_eq = INI_COLOR;			//装備確認ボタンカラー

	m_key_lf = false;
	m_key_rf = false;

	//当たり判定用HitBoxを作成(Objhuman用)
	//Hits::SetHitBox(this, 95, 170, 225, 110, ELEMENT_ENEMY, OBJ_WAREHOUSE, 1);
}

//アクション
void CObjWarehouse::Action()
{
	//チュートリアル説明中は操作不能にする処理
	if (g_is_operatable == false)
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

	//▼倉庫ウィンドウ表示の処理
	if (window_start_manage == Warehouse)
	{
		//戻るボタン左クリック、もしくは右クリック(どこでも)する事でこのウインドウを閉じる
		if (70 < m_mou_x && m_mou_x < 120 && 56 < m_mou_y && m_mou_y < 110 || m_mou_r == true)
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

					//"倉庫ウインドウを開いている状態"フラグを立てる
					window_start_manage = Default;

					//戻るボタン音
					Audio::Start(2);
				}
			}

			//左クリックされたらフラグを立て、倉庫ウインドウを閉じる
			else if (m_mou_l == true)
			{
				//クリック押したままの状態では入力出来ないようにしている
				if (m_key_lf == true)
				{
					m_key_lf = false;

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
			m_introduce_f = false;//施設紹介ウィンドウを非表示にする
			m_Back_Button_color = INI_COLOR;
		}

		if (g_tutorial_progress >= 15)
		{
			//資材ボタン選択
			if (110 < m_mou_x && m_mou_x < 610 && 110 < m_mou_y && m_mou_y < 360)
			{
				m_object_ma = 1.0f;
				//左クリックされたらフラグを立て、資材ウインドウを開く
				if (m_mou_l == true)
				{
					//クリック押したままの状態では入力出来ないようにしている
					if (m_key_lf == true)
					{
						m_key_lf = false;

						//"資材ウィンドウを開いている状態"フラグを立てる
						window_start_manage = Materials;

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
				m_object_ma = INI_COLOR;

			}

			//住民ボタン選択
			if (620 < m_mou_x && m_mou_x < 1120 && 110 < m_mou_y && m_mou_y < 360)
			{
				m_object_re = 1.0f;
				//左クリックされたらフラグを立て、住民ウインドウを開く
				if (m_mou_l == true)
				{
					//クリック押したままの状態では入力出来ないようにしている
					if (m_key_lf == true)
					{
						m_key_lf = false;

						//"住民ウィンドウを開いている状態"フラグを立てる
						window_start_manage = Residents;

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
				m_object_re = INI_COLOR;

			}

			//スペシャル技ボタン選択
			if (110 < m_mou_x && m_mou_x < 610 && 370 < m_mou_y && m_mou_y < 620)
			{
				m_object_sp = 1.0f;
				//左クリックされたらフラグを立て、スペシャル技ウインドウを開く
				if (m_mou_l == true)
				{
					//クリック押したままの状態では入力出来ないようにしている
					if (m_key_lf == true)
					{
						m_key_lf = false;

						//"スペシャル技ウィンドウを開いている状態"フラグを立てる
						window_start_manage = Specialskill;

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
				m_object_sp = INI_COLOR;

			}

			//装備ボタン選択
			if (620 < m_mou_x && m_mou_x < 1120 && 370 < m_mou_y && m_mou_y < 620)
			{
				m_object_eq = 1.0f;
				//左クリックされたらフラグを立て、装備ウインドウを開く
				if (m_mou_l == true)
				{
					//クリック押したままの状態では入力出来ないようにしている
					if (m_key_lf == true)
					{
						m_key_lf = false;

						//"装備ウィンドウを開いている状態"フラグを立てる
						window_start_manage = Soubicheck;

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
				m_object_eq = INI_COLOR;
			}

			return;
		}
	}

	//資材、住民、スペシャル技、装備画面の戻るボタン
	if (window_start_manage == Materials || window_start_manage == Residents ||
		window_start_manage == Specialskill || window_start_manage == Soubicheck)
	{
		//戻るボタン選択
		if (80 < m_mou_x && m_mou_x < 130 && 74 < m_mou_y && m_mou_y < 130 || m_mou_r == true)
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
					window_start_manage = Warehouse;

					//戻るボタン音
					Audio::Start(2);
				}
			}

			//左クリックされたらフラグを立て、倉庫ウインドウを閉じる
			if (m_mou_l == true)
			{
				//戻るボタン音
				//Audio::Start(2);
				//クリック押したままの状態では入力出来ないようにしている
				if (m_key_lf == true)
				{
					m_key_lf = false;

					//"どのウインドウも開いていない状態"フラグを立てる
					window_start_manage = Warehouse;

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
	}

	//ホーム画面に戻るボタンが押されたり、
	//他施設のウインドウを開いている時は操作を受け付けないようにする。
	if (window_start_manage != Default)
	{
		m_introduce_f = false;	//施設紹介ウインドウを非表示にする(右クリックでホーム画面に戻る際、ウインドウが残らないようにするため)
		return;
	}

	//倉庫選択
	if (g_tutorial_progress >= 13)//チュートリアル中は選択不可
	{
		if (850 < m_mou_x && m_mou_x < 1250 && 430 < m_mou_y && m_mou_y < 550)
		{
			m_introduce_f = true;	//施設紹介ウィンドウを表示する
			m_Ware_color = 1.0f;
			//左クリックされたらフラグを立て、倉庫ウインドウを開く
			if (m_mou_l == true)
			{
				//クリック押したままの状態では入力出来ないようにしている
				if (m_key_lf == true)
				{
					m_key_lf = false;

					m_introduce_f = false;//施設紹介ウィンドウを非表示にする

					//倉庫をクリックすると、倉庫が開かれる
					window_start_manage = Warehouse;

					//選択音
					Audio::Start(1);

					if (g_tutorial_progress == 13)
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
			m_Ware_color = INI_COLOR;
		}
	}
}

//ドロー
void CObjWarehouse::Draw()
{
	//▼シーン切り替え演出後に非表示にする処理
	if (scene_change_start == true)
	{
		return;
	}

	//倉庫画像
	float wh[4] = { m_Ware_color,m_Ware_color, m_Ware_color, 1.0f };

	//オブジェクトクリックする前の背景オブジェクト
	float h[4] = { 1.0f,1.0f,1.0f,1.0f };

	//それ以外の画像
	//背景オブジェクト
	float sb[4] = { 1.0f,1.0f,1.0f,1.0f };

	//戻るボタン画像
	float md[4] = { m_Back_Button_color,m_Back_Button_color,m_Back_Button_color,1.0f };

	//資材ボタン画像
	float ma[4] = { m_object_ma,m_object_ma,m_object_ma ,1.0f };

	//住民ボタン画像
	float re[4] = { m_object_re,m_object_re,m_object_re,1.0f };

	//スペシャル技ボタン画像
	float sp[4] = { m_object_sp,m_object_sp,m_object_sp,1.0f };

	//装備ボタン画像
	float eq[4] = { m_object_eq,m_object_eq,m_object_eq,1.0f };

	//資材・白色ウィンドウ画像
	float it[4] = { 1.0f,1.0f,1.0f,1.0f };

	//白色＆その他画像用
	float white[4] = { 1.0f,1.0f,1.0f,1.0f };

	//黒色
	float black[4] = { 0.0f,0.0f,0.0f,1.0f };

	//フォントの色
	float ware[4] = { 1.0f,1.0f,1.0f,1.0f };

	//赤色
	float red[4] = { 1.0f,0.0f,0.0f,1.0f };

	//青色
	float blue[4] = { 0.5f,0.5f,1.0f,1.0f };

	//緑色
	float green[4] = { 0.0f,1.0f,0.0f,1.0f };

	//黄色
	float yellow[4] = { 1.0f,1.0f,0.0f,1.0f };

	//灰色
	float gray[4] = { 0.8f,0.8f,0.9f,1.0f };

	//▽フォント準備
	//倉庫用
	wchar_t Ware[5];
	swprintf_s(Ware, L"倉庫");

	//資材(名前・持っている数)表示
	wchar_t mrl[7][9];
	swprintf_s(mrl[0], L"%d 個", g_Wood_num);
	swprintf_s(mrl[1], L"%d 個", g_Iron_num);
	swprintf_s(mrl[2], L"%d 個", g_Silver_num);
	swprintf_s(mrl[3], L"%d 個", g_Plastic_num);
	swprintf_s(mrl[4], L"%d 個", g_Aluminum_num);
	swprintf_s(mrl[5], L"%d 個", g_gus_num);

	//住民数表示
	//各タイプ(パワー、スピード等)の住民数用
	wchar_t human_num[4][9];						 //9文字分格納可能な文字配列を4つ宣言(それぞれ最大値は999999)
	swprintf_s(human_num[0], L"%6d 人", g_Power_num);//▽それぞれの文字配列に対応する文字データを入れる
	swprintf_s(human_num[1], L"%6d 人", g_Defense_num);
	swprintf_s(human_num[2], L"%6d 人", g_Speed_num);
	swprintf_s(human_num[3], L"%6d 人", g_Balance_num);
	//装備
	//各タイプ(パワー、スピード等)の現在のレベル表示
	wchar_t type_num[5][9];						 //9文字分格納可能な文字配列を4つ宣言(それぞれ最大値は999999)
	swprintf_s(type_num[0], L"Lv.%d ", g_Pow_equip_Level);//▽それぞれの文字配列に対応する文字データを入れる
	swprintf_s(type_num[1], L"Lv.%d ", g_Def_equip_Level);
	swprintf_s(type_num[2], L"Lv.%d ", g_Spe_equip_Level);
	swprintf_s(type_num[3], L"Lv.%d ", g_Bal_equip_Level);
	swprintf_s(type_num[4], L"Lv.%d ", g_Pod_equip_Level);

	//研究員の住民数用
	wchar_t Research_num[9];						 //9文字分格納可能な文字配列を宣言(最大値は999999)
	swprintf_s(Research_num, L"%6d 人", g_Research_num);//その文字配列に文字データを入れる

	//残り住民数用
	wchar_t human_remain[12];						 //12文字分格納可能な文字配列を宣言(最大値は999999)
	swprintf_s(human_remain, L"残り %6d 人", g_Remain_num);//その文字配列に文字データを入れる

	RECT_F src;//描画先切り取り位置
	RECT_F dst;//描画先表示位置

	//施設紹介ウィンドウ(兵舎、研究所、倉庫)が開いていない時に表示するグラフィック
	if (window_start_manage == Default || window_start_manage == BackButton || window_start_manage == EatButton)
	{
		//▼倉庫表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 400.0f;
		src.m_bottom = 400.0f;

		dst.m_top = 350.0f;
		dst.m_left = 850.0f;
		dst.m_right = 1250.0f;
		dst.m_bottom = 650.0f;
		Draw::Draw(27, &src, &dst, wh, 0.0f);

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

			//▼倉庫文字画像表示
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 242.0f;
			src.m_bottom = 117.0f;

			dst.m_top = m_mou_y - 43.0f;
			dst.m_left = m_mou_x - 30.0f;
			dst.m_right = m_mou_x + 20.0f;
			dst.m_bottom = m_mou_y - 18.0f;
			Draw::Draw(88, &src, &dst, white, 0.0f);
		}
}

	//倉庫をクリックした時
	else if (window_start_manage == Warehouse)
	{
		//▼ウィンドウ表示
		src.m_top    =    0.0f;
		src.m_left   =    0.0f;
		src.m_right  = 1200.0f;
		src.m_bottom =  700.0f;

		dst.m_top    =   20.0f;
		dst.m_left   =   20.0f;
		dst.m_right  = 1180.0f;
		dst.m_bottom =  680.0f;
		Draw::Draw(20, &src, &dst, sb, 0.0f);

		//▼戻るアイコン表示
		src.m_top    =   0.0f;
		src.m_left   =   0.0f;
		src.m_right  = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top    =  60.0f;
		dst.m_left   =  70.0f;
		dst.m_right  =  120.0f;
		dst.m_bottom =  110.0f;
		Draw::Draw(1, &src, &dst, md, 0.0f);

		//▼資材選択ボタン表示
		src.m_top    = 0.0f;
		src.m_left   = 0.0f;
		src.m_right  = 300.0f;
		src.m_bottom = 170.0f;

		dst.m_top    = 110.0f;
		dst.m_left   = 110.0f;
		dst.m_right  = 610.0f;
		dst.m_bottom = 360.0f;
		Draw::Draw(28, &src, &dst, ma, 0.0f);

		//▼住民選択ボタン表示
		src.m_top	 = 0.0f;
		src.m_left	 = 0.0f;
		src.m_right	 = 300.0f;
		src.m_bottom = 170.0f;

		dst.m_top    = 110.0f;
		dst.m_left   = 620.0f;
		dst.m_right  = 1120.0f;
		dst.m_bottom = 360.0f;
		Draw::Draw(29, &src, &dst, re, 0.0f);

		//▼スペシャル技選択ボタン表示
		src.m_top	 = 0.0f;
		src.m_left   = 0.0f;
		src.m_right	 = 300.0f;
		src.m_bottom = 170.0f;

		dst.m_top    = 370.0f;
		dst.m_left   = 110.0f;
		dst.m_right  = 610.0f;
		dst.m_bottom = 620.0f;
		Draw::Draw(30, &src, &dst, sp, 0.0f);

		//▼装備選択ボタン表示
		src.m_top	 = 0.0f;
		src.m_left	 = 0.0f;
		src.m_right  = 300.0f;
		src.m_bottom = 170.0f;

		dst.m_top    = 370.0f;
		dst.m_left   = 620.0f;
		dst.m_right  = 1120.0f;
		dst.m_bottom = 620.0f;
		Draw::Draw(31, &src, &dst, eq, 0.0f);
	}

	//戻るボタン、喰ボタンを選択して描画する画像（どのウインドウも開いてない時も描画する）
	else if (window_start_manage == Default || window_start_manage == BackButton || window_start_manage == EatButton)
	{
		//▼倉庫表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 400.0f;
		src.m_bottom = 400.0f;

		dst.m_top = 350.0f;
		dst.m_left = 850.0f;
		dst.m_right = 1250.0f;
		dst.m_bottom = 650.0f;
		Draw::Draw(27, &src, &dst, wh, 0.0f);

		//施設紹介ウインドウ表示管理フラグがtrueの時、描画。
		if (m_introduce_f == true)
		{
			//▼施設紹介ウインドウ表示左上
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 790.0f;
			src.m_bottom = 780.0f;

			dst.m_top = m_mou_y - 50.0f;
			dst.m_left = m_mou_x - 120.0f;
			dst.m_right = m_mou_x - 40.0f;
			dst.m_bottom = m_mou_y - 30.0f;
			Draw::Draw(21, &src, &dst, white, 0.0f);

			//▼施設紹介ウインドウ表示左下
			src.m_top = 0.0f;
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
		}
	}

	//資材ボタンを押して描画する画像
	else if (window_start_manage == Materials)
	{
		//▼ウィンドウ表示(ダミー倉庫ウィンドウ用)
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1200.0f;
		src.m_bottom = 700.0f;

		dst.m_top = 20.0f;
		dst.m_left = 20.0f;
		dst.m_right = 1180.0f;
		dst.m_bottom = 680.0f;
		Draw::Draw(20, &src, &dst, sb, 0.0f);

		//▼ウィンドウ表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1200.0f;
		src.m_bottom = 700.0f;

		dst.m_top = 40.0f;
		dst.m_left = 40.0f;
		dst.m_right = 1160.0f;
		dst.m_bottom = 660.0f;
		Draw::Draw(20, &src, &dst, sb, 0.0f);

		//▼資材文字画像表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 232.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 80.0f;
		dst.m_left = 550.0f;
		dst.m_right = 650.0f;
		dst.m_bottom = 130.0f;
		Draw::Draw(147, &src, &dst, white, 0.0f);

		//▼戻るボタン表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 80.0f;
		dst.m_left = 80.0f;
		dst.m_right = 130.0f;
		dst.m_bottom = 130.0f;
		Draw::Draw(1, &src, &dst, md, 0.0f);

		//▼大きいウィンドウ
		//▼メッセージウインドウ表示左上
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 798.0f;
		src.m_bottom = 798.0f;

		dst.m_top = 150.0f;
		dst.m_left = 105.0f;
		dst.m_right = 350.0f;
		dst.m_bottom = 395.0f;
		Draw::Draw(155, &src, &dst, white, 0.0f);

		//▼メッセージウインドウ表示左下
		src.m_top = 35.0f;
		src.m_left = 800.0f;
		src.m_right = 1600.0f;
		src.m_bottom = 798.0f;

		dst.m_top = 395.0f;
		dst.m_left = 105.0f;
		dst.m_right = 350.0f;
		dst.m_bottom = 640.0f;
		Draw::Draw(155, &src, &dst, white, 0.0f);

		for(int i=0;i<3;i++)
		{
			//▼メッセージウインドウ表示中央上
			src.m_top = 0.0f;
			src.m_left = 1600.0f;
			src.m_right = 2400.0f;
			src.m_bottom = 798.0f;

			dst.m_top = 150.0f;
			dst.m_left = 350.0f + ( i * 245);
			dst.m_right = 595.0f + ( i * 245);
			dst.m_bottom = 395.0f;
			Draw::Draw(155, &src, &dst, white, 0.0f);

			//▼メッセージウインドウ表示中央下
			src.m_top = 2.0f;
			src.m_left = 2402.0f;
			src.m_right = 3200.0f;
			src.m_bottom = 798.0f;

			dst.m_top = 395.0f;
			dst.m_left = 350.0f + (i * 245);
			dst.m_right = 595.0f + (i * 245);
			dst.m_bottom = 640.0f;
			Draw::Draw(155, &src, &dst, white, 0.0f);
		}
		//▼メッセージウインドウ表示右上
		src.m_top = 0.0f;
		src.m_left = 4000.0f;
		src.m_right = 4800.0f;
		src.m_bottom = 798.0f;

		dst.m_top = 150.0f;
		dst.m_left = 860.0f;
		dst.m_right = 1105.0f;
		dst.m_bottom = 395.0f;
		Draw::Draw(155, &src, &dst, white, 0.0f);

		//▼メッセージウインドウ表示右下
		src.m_top = 35.0f;
		src.m_left = 4802.0f;
		src.m_right = 5600.0f;
		src.m_bottom = 798.0f;

		dst.m_top = 395.0f;
		dst.m_left = 860.0f;
		dst.m_right = 1105.0f;
		dst.m_bottom = 640.0f;
		Draw::Draw(155, &src, &dst, white, 0.0f);

		for(int j=0;j<3;j++)
		{
			//▼小さいウィンドウ木材・プラスチック
			//▼メッセージウインドウ表示左上
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 798.0f;
			src.m_bottom = 798.0f;

			dst.m_top = 290.0f + (j * 230);
			dst.m_left = 130.0f;
			dst.m_right = 180.0f;
			dst.m_bottom = 340.0f + (j * 230);
			Draw::Draw(21, &src, &dst, white, 0.0f);

			//▼メッセージウインドウ表示左下
			src.m_top = 35.0f;
			src.m_left = 800.0f;
			src.m_right = 1600.0f;
			src.m_bottom = 798.0f;

			dst.m_top = 340.0f + (j * 230);
			dst.m_left = 130.0f;
			dst.m_right = 180.0f;
			dst.m_bottom = 390.0f + (j * 230);
			Draw::Draw(21, &src, &dst, white, 0.0f);

			for (int i = 0; i<4; i++)
			{
				//▼メッセージウインドウ表示中央上
				src.m_top = 0.0f;
				src.m_left = 1600.0f;
				src.m_right = 2400.0f;
				src.m_bottom = 798.0f;

				dst.m_top = 290.0f + (j * 230);
				dst.m_left = 180.0f + (i * 50);
				dst.m_right = 230.0f + (i * 50);
				dst.m_bottom = 340.0f + (j * 230);
				Draw::Draw(21, &src, &dst, white, 0.0f);

				//▼メッセージウインドウ表示中央下
				src.m_top = 2.0f;
				src.m_left = 2402.0f;
				src.m_right = 3200.0f;
				src.m_bottom = 798.0f;

				dst.m_top = 340.0f + (j * 230);
				dst.m_left = 180.0f + (i * 50);
				dst.m_right = 230.0f + (i * 50);
				dst.m_bottom = 390.0f + (j * 230);
				Draw::Draw(21, &src, &dst, white, 0.0f);
			}
			//▼メッセージウインドウ表示右上
			src.m_top = 0.0f;
			src.m_left = 4000.0f;
			src.m_right = 4800.0f;
			src.m_bottom = 798.0f;

			dst.m_top = 290.0f + (j * 230);
			dst.m_left = 350.0f;
			dst.m_right = 400.0f;
			dst.m_bottom = 340.0f + (j * 230);
			Draw::Draw(21, &src, &dst, white, 0.0f);

			//▼メッセージウインドウ表示右下
			src.m_top = 35.0f;
			src.m_left = 4802.0f;
			src.m_right = 5600.0f;
			src.m_bottom = 798.0f;

			dst.m_top = 340.0f + (j * 230);
			dst.m_left = 350.0f;
			dst.m_right = 400.0f;
			dst.m_bottom = 390.0f + (j * 230);
			Draw::Draw(21, &src, &dst, white, 0.0f);
		}

		for (int j = 0; j<2; j++)
		{
			//▼小さいウィンドウ鉄・アルミ
			//▼メッセージウインドウ表示左上
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 798.0f;
			src.m_bottom = 798.0f;

			dst.m_top = 290.0f + (j * 230);
			dst.m_left = 520.0f;
			dst.m_right = 570.0f;
			dst.m_bottom = 340.0f + (j * 230);
			Draw::Draw(21, &src, &dst, white, 0.0f);

			//▼メッセージウインドウ表示左下
			src.m_top = 35.0f;
			src.m_left = 800.0f;
			src.m_right = 1600.0f;
			src.m_bottom = 798.0f;

			dst.m_top = 340.0f + (j * 230);
			dst.m_left = 520.0f;
			dst.m_right = 570.0f;
			dst.m_bottom = 390.0f + (j * 230);
			Draw::Draw(21, &src, &dst, white, 0.0f);

			for (int i = 0; i<2; i++)
			{
				//▼メッセージウインドウ表示中央上
				src.m_top = 0.0f;
				src.m_left = 1600.0f;
				src.m_right = 2400.0f;
				src.m_bottom = 798.0f;

				dst.m_top = 290.0f + (j * 230);
				dst.m_left = 570.0f + (i * 50);
				dst.m_right = 620.0f + (i * 50);
				dst.m_bottom = 340.0f + (j * 230);
				Draw::Draw(21, &src, &dst, white, 0.0f);

				//▼メッセージウインドウ表示中央下
				src.m_top = 2.0f;
				src.m_left = 2402.0f;
				src.m_right = 3200.0f;
				src.m_bottom = 798.0f;

				dst.m_top = 340.0f + (j * 230);
				dst.m_left = 570.0f + (i * 50);
				dst.m_right = 620.0f + (i * 50);
				dst.m_bottom = 390.0f + (j * 230);
				Draw::Draw(21, &src, &dst, white, 0.0f);
			}
			//▼メッセージウインドウ表示右上
			src.m_top = 0.0f;
			src.m_left = 4000.0f;
			src.m_right = 4800.0f;
			src.m_bottom = 798.0f;

			dst.m_top = 290.0f + (j * 230);
			dst.m_left = 670.0f;
			dst.m_right = 720.0f;
			dst.m_bottom = 340.0f + (j * 230);
			Draw::Draw(21, &src, &dst, white, 0.0f);

			//▼メッセージウインドウ表示右下
			src.m_top = 35.0f;
			src.m_left = 4802.0f;
			src.m_right = 5600.0f;
			src.m_bottom = 798.0f;

			dst.m_top = 340.0f + (j * 230);
			dst.m_left = 670.0f;
			dst.m_right = 720.0f;
			dst.m_bottom = 390.0f + (j * 230);
			Draw::Draw(21, &src, &dst, white, 0.0f);
		}

		for (int j = 0; j<2; j++)
		{
			//▼小さいウィンドウ銀・ガス
			//▼メッセージウインドウ表示左上
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 798.0f;
			src.m_bottom = 798.0f;

			dst.m_top = 290.0f + (j * 230);
			dst.m_left = 870.0f;
			dst.m_right = 920.0f;
			dst.m_bottom = 340.0f + (j * 230);
			Draw::Draw(21, &src, &dst, white, 0.0f);

			//▼メッセージウインドウ表示左下
			src.m_top = 35.0f;
			src.m_left = 800.0f;
			src.m_right = 1600.0f;
			src.m_bottom = 798.0f;

			dst.m_top = 340.0f + (j * 230);
			dst.m_left = 870.0f;
			dst.m_right = 920.0f;
			dst.m_bottom = 390.0f + (j * 230);
			Draw::Draw(21, &src, &dst, white, 0.0f);

			for (int i = 0; i<2; i++)
			{
				//▼メッセージウインドウ表示中央上
				src.m_top = 0.0f;
				src.m_left = 1600.0f;
				src.m_right = 2400.0f;
				src.m_bottom = 798.0f;

				dst.m_top = 290.0f + (j * 230);
				dst.m_left = 910.0f + (i * 50);
				dst.m_right = 960.0f + (i * 50);
				dst.m_bottom = 340.0f + (j * 230);
				Draw::Draw(21, &src, &dst, white, 0.0f);

				//▼メッセージウインドウ表示中央下
				src.m_top = 2.0f;
				src.m_left = 2402.0f;
				src.m_right = 3200.0f;
				src.m_bottom = 798.0f;

				dst.m_top = 340.0f + (j * 230);
				dst.m_left = 910.0f + (i * 50);
				dst.m_right = 960.0f + (i * 50);
				dst.m_bottom = 390.0f + (j * 230);
				Draw::Draw(21, &src, &dst, white, 0.0f);
			}
			//▼メッセージウインドウ表示右上
			src.m_top = 0.0f;
			src.m_left = 4000.0f;
			src.m_right = 4800.0f;
			src.m_bottom = 798.0f;

			dst.m_top = 290.0f + (j * 230);
			dst.m_left = 1010.0f;
			dst.m_right = 1060.0f;
			dst.m_bottom = 340.0f + (j * 230);
			Draw::Draw(21, &src, &dst, white, 0.0f);

			//▼メッセージウインドウ表示右下
			src.m_top = 35.0f;
			src.m_left = 4802.0f;
			src.m_right = 5600.0f;
			src.m_bottom = 798.0f;

			dst.m_top = 340.0f + (j * 230);
			dst.m_left = 1010.0f;
			dst.m_right = 1060.0f;
			dst.m_bottom = 390.0f + (j * 230);
			Draw::Draw(21, &src, &dst, white, 0.0f);
		}

		//▼木材表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 180.0f;
		dst.m_left = 200.0f;
		dst.m_right = 300.0f;
		dst.m_bottom = 280.0f;
		Draw::Draw(33, &src, &dst, white, 0.0f);

		//▼木材文字画像表示
		src.m_top = 2.0f;
		src.m_left = 0.0f;
		src.m_right = 230.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 300.0f;
		dst.m_left = 170.0f;
		dst.m_right = 250.0f;
		dst.m_bottom = 340.0f;
		Draw::Draw(89, &src, &dst, white, 0.0f);

		FontDraw(NumConversion(g_Wood_num), 270, 340, 30, 40, white, true);
		FontDraw(L"コ", 315, 360, 15, 20, white, true);
		//Font::StrDraw(mrl[0], 240.0f, 290.0f, 40.0f, black);

		//▼鉄表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 180.0f;
		dst.m_left = 550.0f;
		dst.m_right = 650.0f;
		dst.m_bottom = 280.0f;
		Draw::Draw(34, &src, &dst, it, 0.0f);

		//▼鉄文字画像表示
		src.m_top = 2.0f;
		src.m_left = 0.0f;
		src.m_right = 110.0f;
		src.m_bottom = 110.0f;

		dst.m_top = 300.0f;
		dst.m_left = 540.0f;
		dst.m_right = 580.0f;
		dst.m_bottom = 340.0f;
		Draw::Draw(69, &src, &dst, white, 0.0f);

		FontDraw(NumConversion(g_Iron_num), 620, 340, 30, 40, white, true);
		FontDraw(L"コ", 665, 360, 15, 20, white, true);
		//Font::StrDraw(mrl[1], 580.0f, 290.0f, 40.0f, black);

		//▼銀表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 180.0f;
		dst.m_left = 900.0f;
		dst.m_right = 1000.0f;
		dst.m_bottom = 280.0f;
		Draw::Draw(35, &src, &dst, it, 0.0f);

		//▼銀文字画像表示
		src.m_top = 2.0f;
		src.m_left = 2.0f;
		src.m_right = 110.0f;
		src.m_bottom = 110.0f;

		dst.m_top = 300.0f;
		dst.m_left = 910.0f;
		dst.m_right = 950.0f;
		dst.m_bottom = 340.0f;
		Draw::Draw(90, &src, &dst, white, 0.0f);

		FontDraw(NumConversion(g_Silver_num), 970, 340, 30, 40, white, true);
		FontDraw(L"コ", 1015, 360, 15, 20, white, true);
		//Font::StrDraw(mrl[2], 950.0f, 290.0f, 40.0f, black);

		//▼プラスチック表示
		src.m_top = 2.0f;
		src.m_left = 0.0f;
		src.m_right = 62.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 400.0f;
		dst.m_left = 200.0f;
		dst.m_right = 300.0f;
		dst.m_bottom = 500.0f;
		Draw::Draw(36, &src, &dst, it, 0.0f);

		//▼プラスチック文字画像表示
		src.m_top = 2.0f;
		src.m_left = 2.0f;
		src.m_right = 712.0f;
		src.m_bottom = 110.0f;

		dst.m_top = 530.0f;
		dst.m_left = 140.0f;
		dst.m_right = 380.0f;
		dst.m_bottom = 570.0f;
		Draw::Draw(91, &src, &dst, white, 0.0f);


		FontDraw(NumConversion(g_Plastic_num), 270, 570, 30, 40, white, true);
		FontDraw(L"コ", 315, 590, 15, 20, white, true);
		//Font::StrDraw(mrl[3], 240.0f, 540.0f, 40.0f, black);

		//▼アルミニウム画像表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 400.0f;
		dst.m_left = 550.0f;
		dst.m_right = 650.0f;
		dst.m_bottom = 500.0f;
		Draw::Draw(37, &src, &dst, it, 0.0f);

		//▼アルミ文字画像表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 352.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 530.0f;
		dst.m_left = 530.0f;
		dst.m_right = 650.0f;
		dst.m_bottom = 570.0f;
		Draw::Draw(92, &src, &dst, white, 0.0f);

		FontDraw(NumConversion(g_Aluminum_num), 620, 570, 30, 40, white, true);
		FontDraw(L"コ", 665, 590, 15, 20, white, true);
		//Font::StrDraw(mrl[4], 580.0f, 540.0f, 40.0f, black);

		//▼ガス表示
		src.m_top = 2.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 400.0f;
		dst.m_left = 900.0f;
		dst.m_right = 1000.0f;
		dst.m_bottom = 500.0f;
		Draw::Draw(38, &src, &dst, it, 0.0f);

		//▼ガス文字画像表示
		src.m_top = 2.0f;
		src.m_left = 0.0f;
		src.m_right = 232.0f;
		src.m_bottom = 116.0f;

		dst.m_top = 530.0f;
		dst.m_left = 910.0f;
		dst.m_right = 990.0f;
		dst.m_bottom = 570.0f;
		Draw::Draw(93, &src, &dst, white, 0.0f);

		FontDraw(NumConversion(g_gus_num), 970, 570, 30, 40, white, true);
		FontDraw(L"コ", 1015, 590, 15, 20, white, true);
		//Font::StrDraw(mrl[5], 950.0f, 540.0f, 40.0f, black);
	}

	//住民ボタンを押して描画する画像
	else if (window_start_manage == Residents)
	{
		//▼ウィンドウ表示(ダミー倉庫ウィンドウ用)
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1200.0f;
		src.m_bottom = 700.0f;

		dst.m_top = 20.0f;
		dst.m_left = 20.0f;
		dst.m_right = 1180.0f;
		dst.m_bottom = 680.0f;
		Draw::Draw(20, &src, &dst, sb, 0.0f);

		//▼ウィンドウ表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1200.0f;
		src.m_bottom = 700.0f;

		dst.m_top = 40.0f;
		dst.m_left = 40.0f;
		dst.m_right = 1160.0f;
		dst.m_bottom = 660.0f;
		Draw::Draw(20, &src, &dst, sb, 0.0f);

		//▼戻るボタン表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 80.0f;
		dst.m_left = 80.0f;
		dst.m_right = 130.0f;
		dst.m_bottom = 130.0f;
		Draw::Draw(1, &src, &dst, md, 0.0f);
		
		//▼残り住民数がいません(住民数だけ)文字画像を表示
		src.m_top = 0.0f;
		src.m_left = 230.0f;
		src.m_right = 600.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 80.0f;
		dst.m_left = 500.0f;
		dst.m_right = 650.0f;
		dst.m_bottom = 130.0f;
		Draw::Draw(94, &src, &dst, white, 0.0f);

		//▼赤住民画像を表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 130.0f;
		src.m_bottom = 130.0f;

		dst.m_top = 150.0f;
		dst.m_left = 150.0f;
		dst.m_right = 270.0f;
		dst.m_bottom = 270.0f;
		Draw::Draw(150, &src, &dst, white, 0.0f);

		//▼青住民画像を表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 130.0f;
		src.m_bottom = 130.0f;

		dst.m_top = 290.0f;
		dst.m_left = 150.0f;
		dst.m_right = 270.0f;
		dst.m_bottom = 410.0f;
		Draw::Draw(151, &src, &dst, white, 0.0f);

		//▼緑住民画像表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 130.0f;
		src.m_bottom = 130.0f;

		dst.m_top = 430.0f;
		dst.m_left = 150.0f;
		dst.m_right = 270.0f;
		dst.m_bottom = 550.0f;
		Draw::Draw(152, &src, &dst, white, 0.0f);

		//▼白住民画像表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 130.0f;
		src.m_bottom = 130.0f;

		dst.m_top = 150.0f;
		dst.m_left = 560.0f;
		dst.m_right = 680.0f;
		dst.m_bottom = 270.0f;
		Draw::Draw(153, &src, &dst, white, 0.0f);

		//▼白研究員文字画像表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 130;
		src.m_bottom = 130;

		dst.m_top = 290.0f;
		dst.m_left = 560.0f;
		dst.m_right = 680.0f;
		dst.m_bottom = 410.0f;
		Draw::Draw(154, &src, &dst, white, 0.0f);

		//▼残り住民数がいません(残り住民数だけ)文字画像を表示
		src.m_top = 2.0f;
		src.m_left = 0.0f;
		src.m_right = 600.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 470.0f;
		dst.m_left = 560.0f;
		dst.m_right = 770.0f;
		dst.m_bottom = 510.0f;
		Draw::Draw(94, &src, &dst, white, 0.0f);

		//▼人文字画像表示(pow数)
		src.m_top = 2.0f;
		src.m_left = 0.0f;
		src.m_right = 112.0f;
		src.m_bottom = 110.0f;

		dst.m_top = 200.0f;
		dst.m_left = 470.0f;
		dst.m_right = 510.0f;
		dst.m_bottom = 240.0f;
		Draw::Draw(77, &src, &dst, white, 0.0f);

		//▼人文字画像表示(spe数)
		src.m_top = 2.0f;
		src.m_left = 0.0f;
		src.m_right = 112.0f;
		src.m_bottom = 110.0f;

		dst.m_top = 330.0f;
		dst.m_left = 470.0f;
		dst.m_right = 510.0f;
		dst.m_bottom = 370.0f;
		Draw::Draw(77, &src, &dst, white, 0.0f);

		//▼人文字画像表示(def数)
		src.m_top = 2.0f;
		src.m_left = 0.0f;
		src.m_right = 112.0f;
		src.m_bottom = 110.0f;

		dst.m_top = 470.0f;
		dst.m_left = 470.0f;
		dst.m_right = 510.0f;
		dst.m_bottom = 510.0f;
		Draw::Draw(77, &src, &dst, white, 0.0f);

		//▼人文字画像表示(bal数)
		src.m_top = 2.0f;
		src.m_left = 0.0f;
		src.m_right = 112.0f;
		src.m_bottom = 110.0f;

		dst.m_top = 200.0f;
		dst.m_left = 1050.0f;
		dst.m_right = 1090.0f;
		dst.m_bottom = 240.0f;
		Draw::Draw(77, &src, &dst, white, 0.0f);

		//▼人文字画像表示(研究員数)
		src.m_top = 2.0f;
		src.m_left = 0.0f;
		src.m_right = 112.0f;
		src.m_bottom = 110.0f;

		dst.m_top = 330.0f;
		dst.m_left = 1050.0f;
		dst.m_right = 1090.0f;
		dst.m_bottom = 370.0f;
		Draw::Draw(77, &src, &dst, white, 0.0f);

		//▼残り　　　人(残り)だけ文字画像表示
		src.m_top = 2.0f;
		src.m_left = 0.0f;
		src.m_right = 592.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 470.0f;
		dst.m_left = 800.0f;
		dst.m_right = 1010.0f;
		dst.m_bottom = 510.0f;
		Draw::Draw(78, &src, &dst, red, 0.0f);

		//▼人文字画像表示(残り住民数)
		src.m_top = 2.0f;
		src.m_left = 0.0f;
		src.m_right = 112.0f;
		src.m_bottom = 110.0f;

		dst.m_top = 470.0f;
		dst.m_left = 1050.0f;
		dst.m_right = 1090.0f;
		dst.m_bottom = 510.0f;
		Draw::Draw(77, &src, &dst, red, 0.0f);

		//▼フォント表示
		//住民ステータス
		//レッド
		FontDraw(NumConversion(g_Power_num)   , 440, 200, 30, 40, white, true);
		//Font::StrDraw(human_num[0], 355.0f, 200.0f, 35.0f, black);

		//ブルー
		FontDraw(NumConversion(g_Defense_num) , 440, 330, 30, 40, white, true);
		//Font::StrDraw(human_num[1], 355.0f, 330.0f, 35.0f, black);

		//グリーン
		FontDraw(NumConversion(g_Speed_num)   , 440, 470, 30, 40, white, true);
		//Font::StrDraw(human_num[2], 355.0f, 470.0f, 35.0f, black);

		//ホワイト
		FontDraw(NumConversion(g_Balance_num) , 1020, 200, 30, 40, white, true);
		//Font::StrDraw(human_num[3], 865.0f, 200.0f, 35.0f, black);

		//研究員
		FontDraw(NumConversion(g_Research_num), 1020, 330, 30, 40, white, true);
		//Font::StrDraw(Research_num, 865.0f, 330.0f, 35.0f, black);

		//残りの住民数
		FontDraw(NumConversion(g_Remain_num), 1020, 470, 30, 40, red, true);
		//Font::StrDraw(human_remain, 780.0f, 470.0f, 35.0f, red);

	}

	//スペシャル技ボタンを押して描画する画像
	else if (window_start_manage == Specialskill)
	{
		//▼ウィンドウ表示(ダミー倉庫ウィンドウ用)
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1200.0f;
		src.m_bottom = 700.0f;

		dst.m_top = 20.0f;
		dst.m_left = 20.0f;
		dst.m_right = 1180.0f;
		dst.m_bottom = 680.0f;
		Draw::Draw(20, &src, &dst, sb, 0.0f);

		//▼ウィンドウ表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1200.0f;
		src.m_bottom = 700.0f;

		dst.m_top = 40.0f;
		dst.m_left = 40.0f;
		dst.m_right = 1160.0f;
		dst.m_bottom = 660.0f;
		Draw::Draw(20, &src, &dst, sb, 0.0f);

		//▼戻るボタン表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 80.0f;
		dst.m_left = 80.0f;
		dst.m_right = 130.0f;
		dst.m_bottom = 130.0f;
		Draw::Draw(1, &src, &dst, md, 0.0f);

		//▼スペシャル技文字画像表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 712.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 80.0f;
		dst.m_left = 405.0f;
		dst.m_right = 755.0f;
		dst.m_bottom = 130.0f;
		Draw::Draw(148, &src, &dst, white, 0.0f);

		for (int i = 0; i < 5; i++)//メッセージウィンドウを適切な位置に５回表示させる
		{
			//スペシャル技メッセージウィンドウ表示左上
			src.m_top = -10.0f;
			src.m_left = 0.0f;
			src.m_right = 795.0f;
			src.m_bottom = 800.0f;

			dst.m_top = 140.0f + (i * 100);
			dst.m_left = 290.0f;
			dst.m_right = 340.0f;
			dst.m_bottom = 190.0f + (i * 100);
			Draw::Draw(132, &src, &dst, it, 0.0f);

			//スペシャル技メッセージウィンドウ表示左下
			src.m_top = 40.0f;
			src.m_left = 800.0f;
			src.m_right = 1600.0f;
			src.m_bottom = 800.0f;

			dst.m_top = 180.0f + (i * 100);
			dst.m_left = 290.0f;
			dst.m_right = 340.0f;
			dst.m_bottom = 230.0f + (i * 100);
			Draw::Draw(132, &src, &dst, it, 0.0f);

			for (int j = 0; j < 14; j++)
			{
				//スペシャル技メッセージウィンドウ表示中央上
				src.m_top = -10.0f;
				src.m_left = 1600.0f;
				src.m_right = 2400.0f;
				src.m_bottom = 800.0f;

				dst.m_top = 140.0f + (i * 100);
				dst.m_left = 340.0f + (j * 50);
				dst.m_right = 390.0f + (j * 50);
				dst.m_bottom = 190.0f + (i * 100);
				Draw::Draw(132, &src, &dst, it, 0.0f);

				//スペシャル技メッセージウィンドウ表示中央下
				src.m_top = 0.0f;
				src.m_left = 2400.0f;
				src.m_right = 3200.0f;
				src.m_bottom = 800.0f;

				dst.m_top = 180.0f + (i * 100);
				dst.m_left = 340.0f + (j * 50);
				dst.m_right = 390.0f + (j * 50);
				dst.m_bottom = 230.0f + (i * 100);
				Draw::Draw(132, &src, &dst, it, 0.0f);

			}

			//スペシャル技メッセージウィンドウ表示右上
			src.m_top = -10.0f;
			src.m_left = 4000.0f;
			src.m_right = 4800.0f;
			src.m_bottom = 800.0f;

			dst.m_top = 140.0f + (i * 100);
			dst.m_left = 1013.0f;
			dst.m_right = 1063.0f;
			dst.m_bottom = 190.0f + (i * 100);
			Draw::Draw(132, &src, &dst, it, 0.0f);

			//スペシャル技メッセージウィンドウ表示右下
			src.m_top = 0.0f;
			src.m_left = 4800.0f;
			src.m_right = 5600.0f;
			src.m_bottom = 800.0f;

			dst.m_top = 180.0f + (i * 100);
			dst.m_left = 1013.0f;
			dst.m_right = 1063.0f;
			dst.m_bottom = 230.0f + (i * 100);
			Draw::Draw(132, &src, &dst, it, 0.0f);
		}

		//スペシャルボタンの共通切り取り位置設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 130.0f;
		src.m_bottom = 130.0f;

		//▼現在のスペシャル技習得状況、装備状況に応じて
		//スペシャル技アイコンのカラー明度を以下のように設定していく。
		//「未習得」……………………………0.0f(黒色)
		//「クリックで装備可(習得済)」……0.4f(灰色)
		//「装備中」……………………………1.0f(白色)



		//Explosionの判定
		//まず貼り付け位置を設定する
		dst.m_top = 122.5f;
		dst.m_left = 130.0f;
		dst.m_right = 260.0f;
		dst.m_bottom = 252.5f;
		Draw::Draw(40, &src, &dst, it, 0.0f);

		//▼相手の惑星に文字画像を表示
		src.m_top = 2.0f;
		src.m_left = 0.0f;
		src.m_right = 713.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 168.5f;
		dst.m_left = 310.0f;
		dst.m_right = 520.0f;
		dst.m_bottom = 203.5f;
		Draw::Draw(95, &src, &dst, black, 0.0f);

		//▼固定ダメージを与える文字画像を表示
		src.m_top = 2.0f;
		src.m_left = 0.0f;
		src.m_right = 1180.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 168.5f;
		dst.m_left = 525.0f;
		dst.m_right = 875.0f;
		dst.m_bottom = 203.5f;
		Draw::Draw(96, &src, &dst, black, 0.0f);

		//Fracture Rayの判定
		//スペシャルボタンの共通切り取り位置設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 130.0f;
		src.m_bottom = 130.0f;

		//まず貼り付け位置を設定する
		dst.m_top = 222.5f;
		dst.m_left = 130.0f;
		dst.m_right = 260.0f;
		dst.m_bottom = 352.5f;
		Draw::Draw(41, &src, &dst, it, 0.0f);

		//▼選択ライン上の文字画像を表示
		src.m_top = 2.0f;
		src.m_left = 0.0f;
		src.m_right = 832.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 268.5f;
		dst.m_left = 310.0f;
		dst.m_right = 555.0f;
		dst.m_bottom = 303.5f;
		Draw::Draw(97, &src, &dst, black, 0.0f);

		//▼相手ポッド等を破壊する文字画像を表示
		src.m_top = 2.0f;
		src.m_left = 0.0f;
		src.m_right = 1304.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 268.5f;
		dst.m_left = 558.0f;
		dst.m_right = 943.0f;
		dst.m_bottom = 303.5f;
		Draw::Draw(98, &src, &dst, black, 0.0f);

		//Immotalityの判定
		//スペシャルボタンの共通切り取り位置設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 130.0f;
		src.m_bottom = 130.0f;

		//まず貼り付け位置を設定する
		dst.m_top = 322.5f;
		dst.m_left = 130.0f;
		dst.m_right = 260.0f;
		dst.m_bottom = 452.5f;
		Draw::Draw(42, &src, &dst, it, 0.0f);

		//▼約10秒間の文字画像を表示
		src.m_top = 2.0f;
		src.m_left = 0.0f;
		src.m_right = 532.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 368.5f;
		dst.m_left = 310.0f;
		dst.m_right = 485.0f;
		dst.m_bottom = 403.5f;
		Draw::Draw(99, &src, &dst, black, 0.0f);

		//▼無敵となる文字画像を表示
		src.m_top = 2.0f;
		src.m_left = 0.0f;
		src.m_right = 584.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 368.5f;
		dst.m_left = 488.0f;
		dst.m_right = 663.0f;
		dst.m_bottom = 403.5f;
		Draw::Draw(100, &src, &dst, black, 0.0f);

		//オーバーワークの判定
		//スペシャルボタンの共通切り取り位置設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 130.0f;
		src.m_bottom = 130.0f;

		//まず貼り付け位置を設定する
		dst.m_top = 422.5f;
		dst.m_left = 130.0f;
		dst.m_right = 260.0f;
		dst.m_bottom = 552.5f;
		Draw::Draw(43, &src, &dst, it, 0.0f);

		//▼10秒間ポッド生産速度の文字画像を表示
		src.m_top = 2.0f;
		src.m_left = 0.0f;
		src.m_right = 1252.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 466.5f;
		dst.m_left = 305.0f;
		dst.m_right = 690.0f;
		dst.m_bottom = 501.5f;
		Draw::Draw(101, &src, &dst, black, 0.0f);

		//▼ミサイル生産速度UPの文字画像を表示
		src.m_top = 2.0f;
		src.m_left = 0.0f;
		src.m_right = 1134.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 466.5f;
		dst.m_left = 693.0f;
		dst.m_right = 1043.0f;
		dst.m_bottom = 501.5f;
		Draw::Draw(102, &src, &dst, black, 0.0f);

		//リミットブレイクの判定
		//スペシャルボタンの共通切り取り位置設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 130.0f;
		src.m_bottom = 130.0f;

		//まず貼り付け位置を設定する
		dst.m_top = 522.5f;
		dst.m_left = 130.0f;
		dst.m_right = 260.0f;
		dst.m_bottom = 652.5f;
		Draw::Draw(44, &src, &dst, it, 0.0f);

		//▼出撃する文字画像を表示
		src.m_top = 2.0f;
		src.m_left = 0.0f;
		src.m_right = 464.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 566.5f;
		dst.m_left = 310.0f;
		dst.m_right = 450.0f;
		dst.m_bottom = 601.5f;
		Draw::Draw(103, &src, &dst, black, 0.0f);

		//▼ポッド5機の攻撃力UP文字画像を表示
		src.m_top = 2.0f;
		src.m_left = 0.0f;
		src.m_right = 1222.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 566.5f;
		dst.m_left = 453.0f;
		dst.m_right = 838.0f;
		dst.m_bottom = 601.5f;
		Draw::Draw(104, &src, &dst, black, 0.0f);

	}
		//装備ボタンを押して描画する画像
		else if (window_start_manage == Soubicheck)
		{
			//▼ウィンドウ表示(ダミー倉庫ウィンドウ用)
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 1200.0f;
			src.m_bottom = 700.0f;

			dst.m_top = 20.0f;
			dst.m_left = 20.0f;
			dst.m_right = 1180.0f;
			dst.m_bottom = 680.0f;
			Draw::Draw(20, &src, &dst, sb, 0.0f);

			//▼ウィンドウ表示
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 1200.0f;
			src.m_bottom = 700.0f;

			dst.m_top = 40.0f;
			dst.m_left = 40.0f;
			dst.m_right = 1160.0f;
			dst.m_bottom = 660.0f;
			Draw::Draw(20, &src, &dst, sb, 0.0f);

			//▼戻るボタン表示
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 64.0f;
			src.m_bottom = 64.0f;

			dst.m_top = 80.0f;
			dst.m_left = 80.0f;
			dst.m_right = 130.0f;
			dst.m_bottom = 130.0f;
			Draw::Draw(1, &src, &dst, md, 0.0f);

			//▼ポッド文字画像文字画像を表示
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 344.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 80.0f;
			dst.m_left = 525.0f;
			dst.m_right = 675.0f;
			dst.m_bottom = 130.0f;
			Draw::Draw(149, &src, &dst, white, 0.0f);

			//▼レッド文字画像を表示
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 336.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 200.0f;
			dst.m_left = 150.0f;
			dst.m_right = 270.0f;
			dst.m_bottom = 240.0f;
			Draw::Draw(82, &src, &dst, red, 0.0f);

			//▼コア文字画像を表示
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 186.0f;
			src.m_bottom = 84.0f;

			dst.m_top = 202.5f;
			dst.m_left = 283.0f;
			dst.m_right = 358.0f;
			dst.m_bottom = 237.5f;
			Draw::Draw(146, &src, &dst, red, 0.0f);

			if (g_Pow_equip_Level == 1)
			{
				//▼レッドコアLv.1画像を表示
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 130.0f;
				src.m_bottom = 130.0f;

				dst.m_top = 150.0f;
				dst.m_left = 420.0f;
				dst.m_right = 540.0f;
				dst.m_bottom = 270.0f;
				Draw::Draw(49, &src, &dst, white, 0.0f);
			}

			if (g_Pow_equip_Level == 2)
			{
				//▼レッドコアLv.2画像を表示
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 130.0f;
				src.m_bottom = 130.0f;

				dst.m_top = 150.0f;
				dst.m_left = 420.0f;
				dst.m_right = 540.0f;
				dst.m_bottom = 270.0f;
				Draw::Draw(50, &src, &dst, white, 0.0f);
			}

			if (g_Pow_equip_Level == 3)
			{
				//▼レッドコアLv.3画像を表示
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 130.0f;
				src.m_bottom = 130.0f;

				dst.m_top = 150.0f;
				dst.m_left = 420.0f;
				dst.m_right = 540.0f;
				dst.m_bottom = 270.0f;
				Draw::Draw(51, &src, &dst, white, 0.0f);
			}

			//▼ブルー文字画像を表示
			src.m_top = 2.0f;
			src.m_left = 0.0f;
			src.m_right = 352.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 350.0f;
			dst.m_left = 150.0f;
			dst.m_right = 270.0f;
			dst.m_bottom = 390.0f;
			Draw::Draw(83, &src, &dst, blue, 0.0f);

			//▼コア文字画像を表示
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 186.0f;
			src.m_bottom = 84.0f;

			dst.m_top = 352.5f;
			dst.m_left = 283.0f;
			dst.m_right = 358.0f;
			dst.m_bottom = 390.0f;
			Draw::Draw(146, &src, &dst, blue, 0.0f);

			if (g_Def_equip_Level == 1)
			{
				//▼ブルーコアLv.1画像を表示
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 130.0f;
				src.m_bottom = 130.0f;

				dst.m_top = 300.0f;
				dst.m_left = 420.0f;
				dst.m_right = 540.0f;
				dst.m_bottom = 420.0f;
				Draw::Draw(52, &src, &dst, white, 0.0f);
			}

			if (g_Def_equip_Level == 2)
			{
				//▼ブルーコアLv.2画像を表示
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 130.0f;
				src.m_bottom = 130.0f;

				dst.m_top = 300.0f;
				dst.m_left = 420.0f;
				dst.m_right = 540.0f;
				dst.m_bottom = 420.0f;
				Draw::Draw(53, &src, &dst, white, 0.0f);
			}

			if (g_Def_equip_Level == 3)
			{
				//▼ブルーコアLv.3画像を表示
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 130.0f;
				src.m_bottom = 130.0f;

				dst.m_top = 300.0f;
				dst.m_left = 420.0f;
				dst.m_right = 540.0f;
				dst.m_bottom = 420.0f;
				Draw::Draw(54, &src, &dst, white, 0.0f);
			}

			//▼グリーン文字画像表示
			src.m_top = 2.0f;
			src.m_left = 2.0f;
			src.m_right = 472.0f;
			src.m_bottom = 110.0f;

			dst.m_top = 490.0f;
			dst.m_left = 150.0f;
			dst.m_right = 310.0f;
			dst.m_bottom = 530.0f;
			Draw::Draw(84, &src, &dst, green, 0.0f);

			//▼コア文字画像を表示
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 186.0f;
			src.m_bottom = 84.0f;

			dst.m_top = 492.5f;
			dst.m_left = 318.0f;
			dst.m_right = 398.0f;
			dst.m_bottom = 530.0f;
			Draw::Draw(146, &src, &dst, green, 0.0f);

			if (g_Spe_equip_Level == 1)
			{
				//▼グリーンコアLv.1画像を表示
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 130.0f;
				src.m_bottom = 130.0f;

				dst.m_top = 450.0f;
				dst.m_left = 420.0f;
				dst.m_right = 540.0f;
				dst.m_bottom = 570.0f;
				Draw::Draw(55, &src, &dst, white, 0.0f);
			}

			if (g_Spe_equip_Level == 2)
			{
				//▼グリーンコアLv.2画像を表示
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 130.0f;
				src.m_bottom = 130.0f;

				dst.m_top = 450.0f;
				dst.m_left = 420.0f;
				dst.m_right = 540.0f;
				dst.m_bottom = 570.0f;
				Draw::Draw(56, &src, &dst, white, 0.0f);
			}

			if (g_Spe_equip_Level == 3)
			{
				//▼グリーンコアLv.3画像を表示
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 130.0f;
				src.m_bottom = 130.0f;

				dst.m_top = 430.0f;
				dst.m_left = 420.0f;
				dst.m_right = 540.0f;
				dst.m_bottom = 550.0f;
				Draw::Draw(57, &src, &dst, white, 0.0f);
			}

			//▼ホワイト文字画像表示
			src.m_top = 2.0f;
			src.m_left = 0.0f;
			src.m_right = 464.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 280.0f;
			dst.m_left = 590.0f;
			dst.m_right = 750.0f;
			dst.m_bottom = 320.0f;
			Draw::Draw(85, &src, &dst, white, 0.0f);

			//▼コア文字画像を表示
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 186.0f;
			src.m_bottom = 84.0f;

			dst.m_top = 282.5f;
			dst.m_left = 758.0f;
			dst.m_right = 838.0f;
			dst.m_bottom = 320.0f;
			Draw::Draw(146, &src, &dst, white, 0.0f);

			if (g_Bal_equip_Level == 1)
			{
				//▼ホワイトコアLv.1画像を表示
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 130.0f;
				src.m_bottom = 130.0f;

				dst.m_top = 230.0f;
				dst.m_left = 860.0f;
				dst.m_right = 980.0f;
				dst.m_bottom = 350.0f;
				Draw::Draw(58, &src, &dst, white, 0.0f);
			}

			if (g_Bal_equip_Level == 2)
			{
				//▼ホワイトコアLv.2画像を表示
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 130.0f;
				src.m_bottom = 130.0f;

				dst.m_top = 230.0f;
				dst.m_left = 860.0f;
				dst.m_right = 980.0f;
				dst.m_bottom = 350.0f;
				Draw::Draw(59, &src, &dst, white, 0.0f);
			}

			if (g_Bal_equip_Level == 3)
			{
				//▼ホワイトコアLv.3画像を表示
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 130.0f;
				src.m_bottom = 130.0f;

				dst.m_top = 230.0f;
				dst.m_left = 860.0f;
				dst.m_right = 980.0f;
				dst.m_bottom = 350.0f;
				Draw::Draw(60, &src, &dst, white, 0.0f);
			}

			//▼ポッド文字画像表示
			src.m_top = 2.0f;
			src.m_left = 0.0f;
			src.m_right = 344.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 420.0f;
			dst.m_left = 590.0f;
			dst.m_right = 710.0f;
			dst.m_bottom = 460.0f;
			Draw::Draw(86, &src, &dst, yellow, 0.0f);

			if (g_Pod_equip_Level == 1)
			{
				//▼ポッドLv.1画像を表示
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 130.0f;
				src.m_bottom = 130.0f;

				dst.m_top = 380.0f;
				dst.m_left = 860.0f;
				dst.m_right = 980.0f;
				dst.m_bottom = 500.0f;
				Draw::Draw(128, &src, &dst, white, 0.0f);
			}

			if (g_Pod_equip_Level == 2)
			{
				//▼ポッドLv.2画像を表示
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 130.0f;
				src.m_bottom = 130.0f;

				dst.m_top = 380.0f;
				dst.m_left = 860.0f;
				dst.m_right = 980.0f;
				dst.m_bottom = 500.0f;
				Draw::Draw(129, &src, &dst, white, 0.0f);
			}

			if (g_Pod_equip_Level == 3)
			{
				//▼ポッドLv.3画像を表示
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 130.0f;
				src.m_bottom = 130.0f;

				dst.m_top = 380.0f;
				dst.m_left = 860.0f;
				dst.m_right = 980.0f;
				dst.m_bottom = 500.0f;
				Draw::Draw(130, &src, &dst, white, 0.0f);
			}

			////レッドレベル表示文字画像
			//src.m_top = 0.0f;
			//src.m_left = 0.0f;
			//src.m_right = 312.0f;
			//src.m_bottom = 107.0f;

			//dst.m_top = 200.0f;
			//dst.m_left = 360.0f;
			//dst.m_right = 480.0f;
			//dst.m_bottom = 240.0f;
			//Draw::Draw(122 + g_Pow_equip_Level, &src, &dst, black, 0.0f);
			////Font::StrDraw(type_num[0], 355.0f, 200.0f, 40.0f, black);

			////ブルーレベル表示文字画像
			//src.m_top = 0.0f;
			//src.m_left = 0.0f;
			//src.m_right = 312.0f;
			//src.m_bottom = 107.0f;

			//dst.m_top = 330.0f;
			//dst.m_left = 360.0f;
			//dst.m_right = 480.0f;
			//dst.m_bottom = 370.0f;
			//Draw::Draw(122 + g_Def_equip_Level, &src, &dst, black, 0.0f);
			////Font::StrDraw(type_num[1], 360.0f, 460.0f, 40.0f, black);

			////グリーンレベル表示文字画像
			//src.m_top = 0.0f;
			//src.m_left = 0.0f;
			//src.m_right = 312.0f;
			//src.m_bottom = 107.0f;

			//dst.m_top = 460.0f;
			//dst.m_left = 360.0f;
			//dst.m_right = 480.0f;
			//dst.m_bottom = 500.0f;
			//Draw::Draw(122 + g_Spe_equip_Level, &src, &dst, black, 0.0f);
			////Font::StrDraw(type_num[2], 360.0f, 330.0f, 40.0f, black);

			////ホワイトレベル表示文字画像
			//src.m_top = 0.0f;
			//src.m_left = 0.0f;
			//src.m_right = 312.0f;
			//src.m_bottom = 107.0f;

			//dst.m_top = 260.0f;
			//dst.m_left = 900.0f;
			//dst.m_right = 1020.0f;
			//dst.m_bottom = 300.0f;
			//Draw::Draw(122 + g_Bal_equip_Level, &src, &dst, black, 0.0f);
			////Font::StrDraw(type_num[3], 880.0f, 200.0f, 40.0f, black);

			////▼ポッドレベル表示文字画像
			//src.m_top = 0.0f;
			//src.m_left = 0.0f;
			//src.m_right = 312.0f;
			//src.m_bottom = 107.0f;

			//dst.m_top = 400.0f;
			//dst.m_left = 900.0f;
			//dst.m_right = 1020.0f;
			//dst.m_bottom = 440.0f;
			//Draw::Draw(122 + g_Pod_equip_Level, &src, &dst, black, 0.0f);
			////Font::StrDraw(type_num[4], 880.0f, 330.0f, 40.0f, black);

		}
	}
