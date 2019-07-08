//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjWarehouse.h"

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
	Hits::SetHitBox(this, 95, 170, 225, 110, ELEMENT_ENEMY, OBJ_WAREHOUSE, 1);
}

//アクション
void CObjWarehouse::Action()
{
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
		if (30 < m_mou_x && m_mou_x < 80 && 30 < m_mou_y && m_mou_y < 80 || m_mou_r == true)
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

					//ObjHelpを操作可能にする & 透過度1.0fにして表示する
					CObjHelp* help = (CObjHelp*)Objs::GetObj(OBJ_HELP);
					help->SetOperatable(true);
					help->SetAlpha(1.0f);

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

		//資材ボタン選択
		if (90 < m_mou_x && m_mou_x < 600 && 80 < m_mou_y && m_mou_y < 350)
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
		if (610 < m_mou_x && m_mou_x < 1120 && 80 < m_mou_y && m_mou_y < 350)
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
		if (90 < m_mou_x && m_mou_x < 600 && 360 < m_mou_y && m_mou_y < 630)
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
		if (610 < m_mou_x && m_mou_x < 1120 && 360 < m_mou_y && m_mou_y < 630)
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

	//資材、住民、スペシャル技、装備画面の戻るボタン
	if (window_start_manage == Materials || window_start_manage == Residents ||
		window_start_manage == Specialskill || window_start_manage == Soubicheck)
	{
		//戻るボタン選択
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
	if (window_start_manage != Default || g_help_f == true)
	{
		m_introduce_f = false;	//施設紹介ウインドウを非表示にする(右クリックでホーム画面に戻る際、ウインドウが残らないようにするため)
		return;
	}

	//倉庫選択
	if (95 < m_mou_x && m_mou_x < 320 && 170 < m_mou_y && m_mou_y < 280)
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
		m_Ware_color = INI_COLOR;
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
	float blue[4] = { 0.0f,0.0f,1.0f,1.0f };

	//緑色
	float green[4] = { 0.0f,1.0f,0.0f,1.0f };

	//黄色
	float yellow[4] = { 1.0f,1.0f,0.0f,1.0f };

	//灰色
	float gray[4] = { 0.4f,0.4f,0.4f,1.0f };

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
	swprintf_s(mrl[6], L"%d 個", g_Raremetal_num);

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
	if (window_start_manage == Default || window_start_manage == BackButton)
	{
		//▼倉庫表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 402.0f;
		src.m_bottom = 332.0f;

		dst.m_top = 100.0f;
		dst.m_left = 100.0f;
		dst.m_right = 325.0f;
		dst.m_bottom = 325.0f;
		Draw::Draw(27, &src, &dst, wh, 0.0f);

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
			Draw::Draw(21, &src, &dst, ware, 0.0f);//灰色のウインドウにする為"ins"にしている。

		    //▼倉庫文字画像表示
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 242.0f;
			src.m_bottom = 117.0f;

			dst.m_top = m_mou_y - 43.0f;
			dst.m_left = m_mou_x - 50.0f;
			dst.m_right = m_mou_x + 30.0f;
			dst.m_bottom = m_mou_y - 15.0f;
			Draw::Draw(88, &src, &dst, black, 0.0f);

		    //▼フォント表示
		    //倉庫
			//Font::StrDraw(Ware, m_mou_x - 40.0f, m_mou_y - 45.0f, 30.0f, black);

		}
}

	//倉庫をクリックした時
	else if (window_start_manage == Warehouse)
	{
		//▼灰色ウィンドウ表示
		src.m_top    =    0.0f;
		src.m_left   =    0.0f;
		src.m_right  = 1160.0f;
		src.m_bottom =  660.0f;

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

		dst.m_top    =  30.0f;
		dst.m_left   =  30.0f;
		dst.m_right  =  80.0f;
		dst.m_bottom =  80.0f;
		Draw::Draw(1, &src, &dst, md, 0.0f);

		//▼資材選択ボタン表示
		src.m_top    = 0.0f;
		src.m_left   = 0.0f;
		src.m_right  = 307.0f;
		src.m_bottom = 175.0f;

		dst.m_top    = 80.0f;
		dst.m_left   = 90.0f;
		dst.m_right  = 600.0f;
		dst.m_bottom = 350.0f;
		Draw::Draw(28, &src, &dst, ma, 0.0f);

		//▼住民選択ボタン表示
		src.m_top	 = 0.0f;
		src.m_left	 = 0.0f;
		src.m_right	 = 307.0f;
		src.m_bottom = 175.0f;

		dst.m_top    = 80.0f;
		dst.m_left   = 610.0f;
		dst.m_right  = 1120.0f;
		dst.m_bottom = 350.0f;
		Draw::Draw(29, &src, &dst, re, 0.0f);

		//▼スペシャル技選択ボタン表示
		src.m_top	 = 0.0f;
		src.m_left   = 0.0f;
		src.m_right	 = 307.0f;
		src.m_bottom = 175.0f;

		dst.m_top    = 360.0f;
		dst.m_left   = 90.0f;
		dst.m_right  = 600.0f;
		dst.m_bottom = 630.0f;
		Draw::Draw(30, &src, &dst, sp, 0.0f);

		//▼装備選択ボタン表示
		src.m_top	 = 0.0f;
		src.m_left	 = 0.0f;
		src.m_right  = 307.0f;
		src.m_bottom = 175.0f;

		dst.m_top    = 360.0f;
		dst.m_left   = 610.0f;
		dst.m_right  = 1120.0f;
		dst.m_bottom = 630.0f;
		Draw::Draw(31, &src, &dst, eq, 0.0f);
	}

	//戻るボタンを選択して描画する画像
	else if (window_start_manage == Default || window_start_manage == BackButton)
	{

		//▼倉庫表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 225.0f;
		src.m_bottom = 225.0f;

		dst.m_top = 100.0f;
		dst.m_left = 100.0f;
		dst.m_right = 325.0f;
		dst.m_bottom = 325.0f;
		Draw::Draw(27, &src, &dst, wh, 0.0f);

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
			Draw::Draw(21, &src, &dst, ware, 0.0f);//灰色のウインドウにする為"ins"にしている。

			//▼倉庫文字画像表示
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 242.0f;
			src.m_bottom = 117.0f;

			dst.m_top = m_mou_y - 43.0f;
			dst.m_left = m_mou_x - 900.0f;
			dst.m_right = m_mou_x + 40.0f;
			dst.m_bottom = m_mou_y - 18.0f;
			Draw::Draw(88, &src, &dst, black, 0.0f);

		    //▼フォント表示
			//倉庫
			//Font::StrDraw(Ware, m_mou_x - 95.0f, m_mou_y - 45.0f, 30.0f, black);

		}
	}

	//資材ボタンを押して描画する画像
	else if (window_start_manage == Materials)
	{
		//▼灰色ウィンドウ表示(ダミー倉庫ウィンドウ用)
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1160.0f;
		src.m_bottom = 660.0f;

		dst.m_top = 20.0f;
		dst.m_left = 20.0f;
		dst.m_right = 1180.0f;
		dst.m_bottom = 680.0f;
		Draw::Draw(20, &src, &dst, sb, 0.0f);

		//▼灰色ウィンドウ表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1160.0f;
		src.m_bottom = 660.0f;

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

		dst.m_top = 50.0f;
		dst.m_left = 50.0f;
		dst.m_right = 100.0f;
		dst.m_bottom = 100.0f;
		Draw::Draw(1, &src, &dst, md, 0.0f);

		//▼白色ウィンドウ表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 100.0f;
		src.m_bottom = 100.0f;

		dst.m_top = 100.0f;
		dst.m_left = 100.0f;
		dst.m_right = 1100.0f;
		dst.m_bottom = 600.0f;
		Draw::Draw(32, &src, &dst, it, 0.0f);

		//▼木材表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 717.0f;
		src.m_bottom = 627.0f;

		dst.m_top = 120.0f;
		dst.m_left = 150.0f;
		dst.m_right = 300.0f;
		dst.m_bottom = 270.0f;
		Draw::Draw(33, &src, &dst, it, 0.0f);

		//▼木材文字画像表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 232.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 250.0f;
		dst.m_left = 170.0f;
		dst.m_right = 250.0f;
		dst.m_bottom = 290.0f;
		Draw::Draw(89, &src, &dst, it, 0.0f);

		//Font::StrDraw(L"木材", 170.0f, 250.0f,40.0f, black);
		Font::StrDraw(mrl[0], 240.0f, 290.0f, 40.0f, black);

		//▼鉄表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 160.0f;
		src.m_bottom = 160.0f;

		dst.m_top = 120.0f;
		dst.m_left = 450.0f;
		dst.m_right = 600.0f;
		dst.m_bottom = 270.0f;
		Draw::Draw(34, &src, &dst, it, 0.0f);

		//▼鉄文字画像表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 112.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 250.0f;
		dst.m_left = 540.0f;
		dst.m_right = 580.0f;
		dst.m_bottom = 290.0f;
		Draw::Draw(69, &src, &dst, it, 0.0f);

		//Font::StrDraw(L"鉄", 540.0f, 250.0f, 40.0f, black);
		Font::StrDraw(mrl[1], 580.0f, 290.0f, 40.0f, black);

		//▼銀表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 160.0f;
		src.m_bottom = 160.0f;

		dst.m_top = 120.0f;
		dst.m_left = 800.0f;
		dst.m_right = 950.0f;
		dst.m_bottom = 270.0f;
		Draw::Draw(35, &src, &dst, it, 0.0f);

		//▼銀文字画像表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 112.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 250.0f;
		dst.m_left = 910.0f;
		dst.m_right = 950.0f;
		dst.m_bottom = 290.0f;
		Draw::Draw(90, &src, &dst, it, 0.0f);

		//Font::StrDraw(L"銀", 910.0f, 250.0f, 40.0f, black);
		Font::StrDraw(mrl[2], 950.0f, 290.0f, 40.0f, black);

		//▼プラスチック表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 135.0f;
		src.m_bottom = 245.0f;

		dst.m_top = 350.0f;
		dst.m_left = 110.0f;
		dst.m_right = 260.0f;
		dst.m_bottom = 500.0f;
		Draw::Draw(36, &src, &dst, it, 0.0f);

		//▼プラスチック文字画像表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 712.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 500.0f;
		dst.m_left = 140.0f;
		dst.m_right = 380.0f;
		dst.m_bottom = 540.0f;
		Draw::Draw(91, &src, &dst, it, 0.0f);

		//Font::StrDraw(L"プラスチック", 130.0f, 500.0f, 40.0f, black);
		Font::StrDraw(mrl[3], 240.0f, 540.0f, 40.0f, black);

		//▼アルミニウム画像表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 160.0f;
		src.m_bottom = 160.0f;

		dst.m_top = 350.0f;
		dst.m_left = 540.0f;
		dst.m_right = 690.0f;
		dst.m_bottom = 500.0f;
		Draw::Draw(37, &src, &dst, it, 0.0f);

		//▼アルミニウム文字画像表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 712.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 500.0f;
		dst.m_left = 500.0f;
		dst.m_right = 740.0f;
		dst.m_bottom = 540.0f;
		Draw::Draw(91, &src, &dst, it, 0.0f);

		//Font::StrDraw(L"アルミニウム", 500.0f, 500.0f, 40.0f, black);
		Font::StrDraw(mrl[4], 580.0f, 540.0f, 40.0f, black);

		//▼ガス表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 300.0f;
		src.m_bottom = 300.0f;

		dst.m_top = 350.0f;
		dst.m_left = 800.0f;
		dst.m_right = 950.0f;
		dst.m_bottom = 500.0f;
		Draw::Draw(38, &src, &dst, it, 0.0f);

		//▼ガス文字画像表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 232.0f;
		src.m_bottom = 116.0f;

		dst.m_top = 500.0f;
		dst.m_left = 910.0f;
		dst.m_right = 990.0f;
		dst.m_bottom = 540.0f;
		Draw::Draw(93, &src, &dst, it, 0.0f);

		//Font::StrDraw(L"ガス", 910.0f, 500.0f, 40.0f, black);
		Font::StrDraw(mrl[5], 950.0f, 540.0f, 40.0f, black);
	}

	//住民ボタンを押して描画する画像
	else if (window_start_manage == Residents)
	{
		//▼灰色ウィンドウ表示(ダミー倉庫ウィンドウ用)
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1160.0f;
		src.m_bottom = 660.0f;

		dst.m_top = 20.0f;
		dst.m_left = 20.0f;
		dst.m_right = 1180.0f;
		dst.m_bottom = 680.0f;
		Draw::Draw(20, &src, &dst, sb, 0.0f);

		//▼灰色ウィンドウ表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1160.0f;
		src.m_bottom = 660.0f;

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

		dst.m_top = 50.0f;
		dst.m_left = 50.0f;
		dst.m_right = 100.0f;
		dst.m_bottom = 100.0f;
		Draw::Draw(1, &src, &dst, md, 0.0f);

		//▼白色ウィンドウ表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 100.0f;
		src.m_bottom = 100.0f;

		dst.m_top = 100.0f;
		dst.m_left = 100.0f;
		dst.m_right = 1100.0f;
		dst.m_bottom = 600.0f;
		Draw::Draw(32, &src, &dst, it, 0.0f);
		
		//▼残り住民数がいません(住民数だけ)文字画像を表示
		src.m_top = 0.0f;
		src.m_left = 230.0f;
		src.m_right = 600.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 110.0f;
		dst.m_left = 500.0f;
		dst.m_right = 650.0f;
		dst.m_bottom = 160.0f;
		Draw::Draw(94, &src, &dst, black, 0.0f);

		//▼レッド文字画像を表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 336.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 200.0f;
		dst.m_left = 120.0f;
		dst.m_right = 225.0f;
		dst.m_bottom = 235.0f;
		Draw::Draw(82, &src, &dst, red, 0.0f);

		//▼ブルー文字画像を表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 352.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 330.0f;
		dst.m_left = 120.0f;
		dst.m_right = 225.0f;
		dst.m_bottom = 365.0f;
		Draw::Draw(83, &src, &dst, blue, 0.0f);

		//▼グリーン文字画像表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 472.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 470.0f;
		dst.m_left = 120.0f;
		dst.m_right = 330.0f;
		dst.m_bottom = 505.0f;
		Draw::Draw(84, &src, &dst, green, 0.0f);

		//▼ホワイト文字画像表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 464.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 200.0f;
		dst.m_left = 540.0f;
		dst.m_right = 680.0f;
		dst.m_bottom = 235.0f;
		Draw::Draw(85, &src, &dst, black, 0.0f);

		//▼研究員文字画像表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 352.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 330.0f;
		dst.m_left = 540.0f;
		dst.m_right = 645.0f;
		dst.m_bottom = 365.0f;
		Draw::Draw(75, &src, &dst, black, 0.0f);

		//▼残り住民数がいません(残り住民数だけ)文字画像を表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 600.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 470.0f;
		dst.m_left = 540.0f;
		dst.m_right = 750.0f;
		dst.m_bottom = 505.0f;
		Draw::Draw(94, &src, &dst, black, 0.0f);

		//▼残り　　　人(残り)だけ文字画像表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 592.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 470.0f;
		dst.m_left = 780.0f;
		dst.m_right = 990.0f;
		dst.m_bottom = 505.0f;
		Draw::Draw(78, &src, &dst, red, 0.0f);

		//▼人文字画像表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 112.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 470.0f;
		dst.m_left = 995.0f;
		dst.m_right = 1030.0f;
		dst.m_bottom = 505.0f;
		Draw::Draw(77, &src, &dst, red, 0.0f);

		//▼フォント表示
		//住民ステータス

		////住民数
		//Font::StrDraw(L"住民数", 500.0f, 110.0f, 50.0f, black);

		////パワー
		//Font::StrDraw(L"パワー", 120.0f, 200.0f, 35.0f, red);
		Font::StrDraw(human_num[0], 355.0f, 200.0f, 35.0f, black);

		////スピード
		//Font::StrDraw(L"スピード", 120.0f, 330.0f, 35.0f, green);
		Font::StrDraw(human_num[1], 355.0f, 330.0f, 35.0f, black);

		////ディフェンス
		//Font::StrDraw(L"ディフェンス", 120.0f, 470.0f, 35.0f, blue);
		Font::StrDraw(human_num[2], 355.0f, 470.0f, 35.0f, black);

		////バランス
		//Font::StrDraw(L"バランス", 540.0f, 200.0f, 35.0f, yellow);
		Font::StrDraw(human_num[3], 865.0f, 200.0f, 35.0f, black);

		////研究員
		//Font::StrDraw(L"研究員", 540.0f, 330.0f, 35.0f, black);
		Font::StrDraw(Research_num, 865.0f, 330.0f, 35.0f, black);

		////残りの住民数
		//Font::StrDraw(L"残りの住民数", 540.0f, 470.0f, 35.0f, black);
		Font::StrDraw(human_remain, 780.0f, 470.0f, 35.0f, red);

	}

	//スペシャル技ボタンを押して描画する画像
	else if (window_start_manage == Specialskill)
	{
		//▼灰色ウィンドウ表示(ダミー倉庫ウィンドウ用)
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1160.0f;
		src.m_bottom = 660.0f;

		dst.m_top = 20.0f;
		dst.m_left = 20.0f;
		dst.m_right = 1180.0f;
		dst.m_bottom = 680.0f;
		Draw::Draw(20, &src, &dst, sb, 0.0f);

		//▼灰色ウィンドウ表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1160.0f;
		src.m_bottom = 660.0f;

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

		dst.m_top = 50.0f;
		dst.m_left = 50.0f;
		dst.m_right = 100.0f;
		dst.m_bottom = 100.0f;
		Draw::Draw(1, &src, &dst, md, 0.0f);

		//▼白色ウィンドウ表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 100.0f;
		src.m_bottom = 100.0f;

		dst.m_top = 100.0f;
		dst.m_left = 100.0f;
		dst.m_right = 1100.0f;
		dst.m_bottom = 600.0f;
		Draw::Draw(32, &src, &dst, it, 0.0f);

		//スペシャル技1メッセージウィンドウ表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 200.0f;
		src.m_bottom = 100.0f;

		for (int i = 0; i < 5; i++)//メッセージウィンドウを適切な位置に５回表示させる
		{
			dst.m_top = 100.0f + ( i * 100 );
			dst.m_left = 235.0f;
			dst.m_right = 1100.0f;
			dst.m_bottom = 200.0f + (i * 100);
			Draw::Draw(45, &src, &dst, it, 0.0f);
		}

		//スペシャルボタンの共通切り取り位置設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 100.0f;
		src.m_bottom = 100.0f;

		//▼現在のスペシャル技習得状況、装備状況に応じて
		//スペシャル技アイコンのカラー明度を以下のように設定していく。
		//「未習得」……………………………0.0f(黒色)
		//「クリックで装備可(習得済)」……0.4f(灰色)
		//「装備中」……………………………1.0f(白色)

		//Explosionの判定
		//まず貼り付け位置を設定する
		dst.m_top = 85.0f;
		dst.m_left = 100.0f;
		dst.m_right = 230.0f;
		dst.m_bottom = 215.0f;

		//Explosionを覚えているならば
		if (g_Special_mastering[0] == true)
		{

			//Font::StrDraw(L"相手の惑星に固定ダメージを与える", 245.0f, 110.0f, 35.0f, black);
			//Font::StrDraw(L"ダメージ量は惑星の削るHPの1.2倍のダメージを与える", 240.0f, 160.0f, 35.0f, black);

			if(g_Special_equipment == 1)
				Draw::Draw(40, &src, &dst, it, 0.0f);
			else
				Draw::Draw(40, &src, &dst, gray, 0.0f);

			//▼相手の惑星に文字画像を表示
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 713.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 135.0f;
			dst.m_left = 245.0f;
			dst.m_right = 455.0f;
			dst.m_bottom = 170.0f;
			Draw::Draw(95, &src, &dst, black, 0.0f);

			//▼固定ダメージを与える文字画像を表示
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 1182.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 135.0f;
			dst.m_left = 456.0f;
			dst.m_right = 806.0f;
			dst.m_bottom = 170.0f;
			Draw::Draw(96, &src, &dst, black, 0.0f);
		}
		else
		{
			Draw::Draw(40, &src, &dst, black, 0.0f);
		}

		//Fracture Rayの判定
		//スペシャルボタンの共通切り取り位置設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 100.0f;
		src.m_bottom = 100.0f;

		//まず貼り付け位置を設定する
		dst.m_top = 185.0f;
		dst.m_left = 100.0f;
		dst.m_right = 230.0f;
		dst.m_bottom = 315.0f;
		
		//Fracture Rayを覚えているならば
		if (g_Special_mastering[1] == true)
		{
			//Font::StrDraw(L"選択ライン上の", 245.0f, 210.0f, 35.0f, black);
			//Font::StrDraw(L"相手ポッド等を破壊する", 240.0f, 260.0f, 35.0f, black);
			if (g_Special_equipment == 2)
				Draw::Draw(41, &src, &dst, it, 0.0f);
			else
				Draw::Draw(41, &src, &dst, gray, 0.0f);

			//▼選択ライン上の文字画像を表示
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 832.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 210.0f;
			dst.m_left = 245.0f;
			dst.m_right = 490.0f;
			dst.m_bottom = 245.0f;
			Draw::Draw(97, &src, &dst, black, 0.0f);

			//▼相手ポッド等を破壊する文字画像を表示
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 1304.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 260.0f;
			dst.m_left = 245.0f;
			dst.m_right = 630.0f;
			dst.m_bottom = 295.0f;
			Draw::Draw(98, &src, &dst, black, 0.0f);


		}
		else
		{
			Draw::Draw(41, &src, &dst, black, 0.0f);
		}

		//Immotalityの判定
		//スペシャルボタンの共通切り取り位置設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 100.0f;
		src.m_bottom = 100.0f;

		//まず貼り付け位置を設定する
		dst.m_top = 285.0f;
		dst.m_left = 100.0f;
		dst.m_right = 230.0f;
		dst.m_bottom = 415.0f;

		//Immotalityを覚えているならば
		if (g_Special_mastering[2] == true)
		{
			//Font::StrDraw(L"約10秒間無敵になることができる", 245.0f, 335.0f, 35.0f, black);

			if (g_Special_equipment == 3)
				Draw::Draw(42, &src, &dst, it, 0.0f);
			else
				Draw::Draw(42, &src, &dst, gray, 0.0f);

			//▼約10秒間の文字画像を表示
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 532.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 335.0f;
			dst.m_left = 245.0f;
			dst.m_right = 420.0f;
			dst.m_bottom = 370.0f;
			Draw::Draw(99, &src, &dst, black, 0.0f);

			//▼無敵となるの文字画像を表示584*112
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 584.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 335.0f;
			dst.m_left = 425.0f;
			dst.m_right = 600.0f;
			dst.m_bottom = 370.0f;
			Draw::Draw(100, &src, &dst, black, 0.0f);

		}
		else
		{
			Draw::Draw(42, &src, &dst, black, 0.0f);
		}

		//リミットブレイクの判定
		//スペシャルボタンの共通切り取り位置設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 100.0f;
		src.m_bottom = 100.0f;

		//まず貼り付け位置を設定する
		dst.m_top = 385.0f;
		dst.m_left = 100.0f;
		dst.m_right = 230.0f;
		dst.m_bottom = 515.0f;

		//リミットブレイクを覚えているならば
		if (g_Special_mastering[3] == true)
		{
			//Font::StrDraw(L"10秒間攻撃スピードアップ", 240.0f, 410.0f, 35.0f, black);
			//Font::StrDraw(L"武器生産頻度アップ", 245.0f, 460.0f, 35.0f, black);

			if (g_Special_equipment == 4)
				Draw::Draw(43, &src, &dst, it, 0.0f);
			else
				Draw::Draw(43, &src, &dst, gray, 0.0f);

			//▼10秒間ポッド生産速度の文字画像を表示
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 1252.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 410.0f;
			dst.m_left = 240.0f;
			dst.m_right = 625.0f;
			dst.m_bottom = 445.0f;
			Draw::Draw(101, &src, &dst, black, 0.0f);

			//▼ミサイル生産速度UPの文字画像を表示
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 1134.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 460.0f;
			dst.m_left = 245.0f;
			dst.m_right = 595.0f;
			dst.m_bottom = 495.0f;
			Draw::Draw(102, &src, &dst, black, 0.0f);


		}
		else
		{
			Draw::Draw(43, &src, &dst, black, 0.0f);
		}

		//ステロイド投与の判定
		//スペシャルボタンの共通切り取り位置設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 100.0f;
		src.m_bottom = 100.0f;

		//まず貼り付け位置を設定する
		dst.m_top =485.0f;
		dst.m_left = 100.0f;
		dst.m_right = 230.0f;
		dst.m_bottom = 615.0f;

		//ステロイド投与を覚えているならば
		if (g_Special_mastering[4] == true)
		{
			//Font::StrDraw(L"住民のポッド5機攻撃が上がる", 245.0f, 510.0f, 35.0f, black);
			//Font::StrDraw(L"(現在ライン上に出ているポッドを含めて)", 245.0f, 560.0f, 35.0f, black);

			if (g_Special_equipment == 6)
				Draw::Draw(44, &src, &dst, it, 0.0f);
			else
				Draw::Draw(44, &src, &dst, gray, 0.0f);

			//▼出撃するの文字画像を表示
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 464.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 510.0f;
			dst.m_left = 245.0f;
			dst.m_right = 385.0f;
			dst.m_bottom = 545.0f;
			Draw::Draw(103, &src, &dst, black, 0.0f);

			//▼ポッド5機の攻撃力UPの文字画像を表示
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 1222.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 560.0f;
			dst.m_left = 245.0f;
			dst.m_right = 630.0f;
			dst.m_bottom = 595.0f;
			Draw::Draw(104, &src, &dst, black, 0.0f);


		}
		else
		{
			Draw::Draw(44, &src, &dst, black, 0.0f);
		}
	}

	//装備ボタンを押して描画する画像
	else if (window_start_manage == Soubicheck)
	{
		//▼灰色ウィンドウ表示(ダミー倉庫ウィンドウ用)
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1160.0f;
		src.m_bottom = 660.0f;

		dst.m_top = 20.0f;
		dst.m_left = 20.0f;
		dst.m_right = 1180.0f;
		dst.m_bottom = 680.0f;
		Draw::Draw(20, &src, &dst, sb, 0.0f);

		//▼灰色ウィンドウ表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1160.0f;
		src.m_bottom = 660.0f;

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

		dst.m_top = 50.0f;
		dst.m_left = 50.0f;
		dst.m_right = 100.0f;
		dst.m_bottom = 100.0f;
		Draw::Draw(1, &src, &dst, md, 0.0f);

		//▼白色ウィンドウ表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 100.0f;
		src.m_bottom = 100.0f;

		dst.m_top = 100.0f;
		dst.m_left = 100.0f;
		dst.m_right = 1100.0f;
		dst.m_bottom = 600.0f;
		Draw::Draw(32, &src, &dst, it, 0.0f);

		//▼未装備(装備だけ)文字画像を表示
		src.m_top = 0.0f;
		src.m_left = 120.0f;
		src.m_right = 367.0f;
		src.m_bottom = 117.0f;

		dst.m_top = 110.0f;
		dst.m_left = 500.0f;
		dst.m_right = 650.0f;
		dst.m_bottom = 160.0f;
		Draw::Draw(105, &src, &dst, black, 0.0f);

		//▼レッド文字画像を表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 336.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 200.0f;
		dst.m_left = 120.0f;
		dst.m_right = 240.0f;
		dst.m_bottom = 240.0f;
		Draw::Draw(82, &src, &dst, red, 0.0f);

		//▼ブルー文字画像を表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 352.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 330.0f;
		dst.m_left = 120.0f;
		dst.m_right = 240.0f;
		dst.m_bottom = 370.0f;
		Draw::Draw(83, &src, &dst, blue, 0.0f);

		//▼グリーン文字画像表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 472.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 460.0f;
		dst.m_left = 120.0f;
		dst.m_right = 280.0f;
		dst.m_bottom = 500.0f;
		Draw::Draw(84, &src, &dst, green, 0.0f);

		//▼ホワイト文字画像表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 464.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 200.0f;
		dst.m_left = 620.0f;
		dst.m_right = 780.0f;
		dst.m_bottom = 240.0f;
		Draw::Draw(85, &src, &dst, black, 0.0f);

		//▼ポッド文字画像表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 344.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 330.0f;
		dst.m_left = 620.0f;
		dst.m_right = 740.0f;
		dst.m_bottom = 370.0f;
		Draw::Draw(86, &src, &dst, black, 0.0f);

		//▼残り住民数がいません(残り住民数だけ)文字画像を表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 600.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 470.0f;
		dst.m_left = 540.0f;
		dst.m_right = 750.0f;
		dst.m_bottom = 505.0f;
		Draw::Draw(94, &src, &dst, black, 0.0f);

		//▼残り　　　人(残り)だけ文字画像表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 592.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 470.0f;
		dst.m_left = 780.0f;
		dst.m_right = 990.0f;
		dst.m_bottom = 505.0f;
		Draw::Draw(78, &src, &dst, red, 0.0f);

		//▼人文字画像表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 112.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 470.0f;
		dst.m_left = 995.0f;
		dst.m_right = 1030.0f;
		dst.m_bottom = 505.0f;
		Draw::Draw(77, &src, &dst, red, 0.0f);


		//▼装備
		//Font::StrDraw(L"装備", 500.0f, 110.0f, 50.0f, black);

		////パワー
		//Font::StrDraw(L"パワー", 120.0f, 200.0f, 40.0f, red);
		Font::StrDraw(type_num[0], 355.0f, 200.0f, 40.0f, black);

		////ディフェンス
		//Font::StrDraw(L"ディフェンス", 120.0f, 460.0f, 40.0f, green);
		Font::StrDraw(type_num[1], 360.0f, 460.0f, 40.0f, black);

		////スピード
		//Font::StrDraw(L"スピード", 120.0f, 330.0f, 40.0f, blue);
		Font::StrDraw(type_num[2], 360.0f, 330.0f, 40.0f, black);

		////バランス
		//Font::StrDraw(L"バランス", 620.0f, 200.0f, 40.0f, yellow);
		Font::StrDraw(type_num[3], 880.0f, 200.0f, 40.0f, black);

		////▼ポッド
		//Font::StrDraw(L"ポッド", 620.0f, 330.0f, 40.0f, black);
		Font::StrDraw(type_num[4], 880.0f, 330.0f, 40.0f, black);

	}
}
