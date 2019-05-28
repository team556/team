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
int g_Ware = 1;


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
			m_key_rf = true;
			m_introduce_f = false;//施設紹介ウィンドウを非表示にする
			m_Back_Button_color = INI_COLOR;
		}

		//資材ボタン選択
		if (245 < m_mou_x && m_mou_x < 560 && 150 < m_mou_y && m_mou_y < 325)
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
		if (680 < m_mou_x && m_mou_x < 1005 && 150 < m_mou_y && m_mou_y < 325)
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
		if (245 < m_mou_x && m_mou_x < 560 && 390 < m_mou_y && m_mou_y < 570)
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
		if (680 < m_mou_x && m_mou_x < 1005 && 390 < m_mou_y && m_mou_y < 570)
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
			m_key_rf = true;
		}
	}

	//ホーム画面に戻るボタンが押されたり、
	//他施設のウインドウを開いている時は操作を受け付けないようにする。
	if (window_start_manage != Default)
	{
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

	//▽フォント準備
	//倉庫用
	wchar_t Ware[5];
	swprintf_s(Ware, L"倉庫", g_Ware);

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

		    //▼フォント表示
		    //倉庫
			Font::StrDraw(Ware, m_mou_x - 40.0f, m_mou_y - 45.0f, 30.0f, black);

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

		dst.m_top    = 150.0f;
		dst.m_left   = 250.0f;
		dst.m_right  = 560.0f;
		dst.m_bottom = 325.0f;
		Draw::Draw(28, &src, &dst, ma, 0.0f);

		//▼住民選択ボタン表示
		src.m_top	 = 0.0f;
		src.m_left	 = 0.0f;
		src.m_right	 = 307.0f;
		src.m_bottom = 175.0f;

		dst.m_top    = 150.0f;
		dst.m_left   = 700.0f;
		dst.m_right  = 1005.0f;
		dst.m_bottom = 325.0f;
		Draw::Draw(29, &src, &dst, re, 0.0f);

		//▼スペシャル技選択ボタン表示
		src.m_top	 = 0.0f;
		src.m_left   = 0.0f;
		src.m_right	 = 307.0f;
		src.m_bottom = 175.0f;

		dst.m_top    = 400.0f;
		dst.m_left   = 250.0f;
		dst.m_right  = 560.0f;
		dst.m_bottom = 570.0f;
		Draw::Draw(30, &src, &dst, sp, 0.0f);

		//▼装備選択ボタン表示
		src.m_top	 = 0.0f;
		src.m_left	 = 0.0f;
		src.m_right  = 307.0f;
		src.m_bottom = 175.0f;

		dst.m_top    = 400.0f;
		dst.m_left   = 700.0f;
		dst.m_right  = 1005.0f;
		dst.m_bottom = 570.0f;
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

		    //▼フォント表示
			//研究所レベル
			Font::StrDraw(Ware, m_mou_x - 95.0f, m_mou_y - 45.0f, 30.0f, black);

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
		dst.m_left = 120.0f;
		dst.m_right = 257.0f;
		dst.m_bottom = 197.0f;
		Draw::Draw(33, &src, &dst, it, 0.0f);
		Font::StrDraw(L"木材", 280.0f, 130.0f,30.0f, black);
		Font::StrDraw(mrl[0], 280.0f, 170.0f, 30.0f, black);

		//▼鉄表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 160.0f;
		src.m_bottom = 160.0f;

		dst.m_top = 120.0f;
		dst.m_left = 450.0f;
		dst.m_right = 560.0f;
		dst.m_bottom = 230.0f;
		Draw::Draw(34, &src, &dst, it, 0.0f);
		Font::StrDraw(L"鉄", 580.0f, 130.0f, 30.0f, black);
		Font::StrDraw(mrl[1], 580.0f, 170.0f, 30.0f, black);

		//▼銀表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 160.0f;
		src.m_bottom = 160.0f;

		dst.m_top = 120.0f;
		dst.m_left = 800.0f;
		dst.m_right = 910.0f;
		dst.m_bottom = 230.0f;
		Draw::Draw(35, &src, &dst, it, 0.0f);
		Font::StrDraw(L"銀", 950.0f, 130.0f, 30.0f, black);
		Font::StrDraw(mrl[2], 950.0f, 170.0f, 30.0f, black);

		//▼プラスチック表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 135.0f;
		src.m_bottom = 245.0f;

		dst.m_top = 240.0f;
		dst.m_left = 110.0f;
		dst.m_right = 245.0f;
		dst.m_bottom = 390.0f;
		Draw::Draw(36, &src, &dst, it, 0.0f);
		Font::StrDraw(L"プラスチック", 240.0f, 280.0f, 30.0f, black);
		Font::StrDraw(mrl[3], 240.0f, 330.0f, 30.0f, black);

		//▼アルミニウム表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 160.0f;
		src.m_bottom = 160.0f;

		dst.m_top = 270.0f;
		dst.m_left = 450.0f;
		dst.m_right = 560.0f;
		dst.m_bottom = 380.0f;
		Draw::Draw(37, &src, &dst, it, 0.0f);
		Font::StrDraw(L"アルミニウム", 580.0f, 280.0f, 30.0f, black);
		Font::StrDraw(mrl[4], 580.0f, 330.0f, 30.0f, black);

		//▼ガス表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 300.0f;
		src.m_bottom = 300.0f;

		dst.m_top = 240.0f;
		dst.m_left = 780.0f;
		dst.m_right = 930.0f;
		dst.m_bottom = 390.0f;
		Draw::Draw(38, &src, &dst, it, 0.0f);
		Font::StrDraw(L"ガス", 950.0f, 280.0f, 30.0f, black);
		Font::StrDraw(mrl[5], 950.0f, 330.0f, 30.0f, black);

		//▼レアメタル表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 160.0f;
		src.m_bottom = 160.0f;

		dst.m_top = 440.0f;
		dst.m_left = 450.0f;
		dst.m_right = 560.0f;
		dst.m_bottom = 550.0f;
		Draw::Draw(39, &src, &dst, it, 0.0f);
		Font::StrDraw(L"レアメタル", 580.0f, 450.0f, 30.0f, black);
		Font::StrDraw(mrl[6], 580.0f, 500.0f, 30.0f, black);
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
		
		//▼フォント表示
		//住民ステータス

		//住民数
		Font::StrDraw(L"住民数", 500.0f, 110.0f, 50.0f, black);

		//パワー
		Font::StrDraw(L"パワー", 120.0f, 200.0f, 35.0f, red);
		Font::StrDraw(human_num[0], 355.0f, 200.0f, 35.0f, black);

		//ディフェンス
		Font::StrDraw(L"ディフェンス", 120.0f, 470.0f, 35.0f, green);
		Font::StrDraw(human_num[1], 355.0f, 470.0f, 35.0f, black);

		//スピード
		Font::StrDraw(L"スピード", 120.0f, 330.0f, 35.0f, blue);
		Font::StrDraw(human_num[2], 355.0f, 330.0f, 35.0f, black);

		//バランス
		Font::StrDraw(L"バランス", 540.0f, 200.0f, 35.0f, yellow);
		Font::StrDraw(human_num[3], 865.0f, 200.0f, 35.0f, black);

		//研究員
		Font::StrDraw(L"研究員", 540.0f, 330.0f, 35.0f, black);
		Font::StrDraw(Research_num, 865.0f, 330.0f, 35.0f, black);

		//残りの住民数
		Font::StrDraw(L"残りの住民数", 540.0f, 470.0f, 35.0f, black);
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

		//▼現在のスペシャル技習得状況、装備状況に応じて
		//スペシャル技アイコンのカラー明度を以下のように設定していく。
		//「未習得」……………………………0.0f(黒色)
		//「クリックで装備可(習得済)」……0.4f(灰色)
		//「装備中」……………………………1.0f(白色)
		for (int i = 0; i < 5; i++)
		{
			//装備中の処理
			if (g_Special_equipment == i + 1)
			{
				//スペシャル技1ボタン表示
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 100.0f;
				src.m_bottom = 100.0f;

				dst.m_top = 85.0f;
				dst.m_left = 100.0f;
				dst.m_right = 230.0f;
				dst.m_bottom = 215.0f;
				Draw::Draw(40, &src, &dst, it, 0.0f);

				//スペシャル技2ボタン表示
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 100.0f;
				src.m_bottom = 100.0f;

				dst.m_top = 185.0f;
				dst.m_left = 100.0f;
				dst.m_right = 230.0f;
				dst.m_bottom = 315.0f;
				Draw::Draw(41, &src, &dst, it, 0.0f);

				//スペシャル技3ボタン表示
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 100.0f;
				src.m_bottom = 100.0f;

				dst.m_top = 285.0f;
				dst.m_left = 100.0f;
				dst.m_right = 230.0f;
				dst.m_bottom = 415.0f;
				Draw::Draw(42, &src, &dst, it, 0.0f);

				//スペシャル技4ボタン表示
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 100.0f;
				src.m_bottom = 100.0f;

				dst.m_top = 385.0f;
				dst.m_left = 100.0f;
				dst.m_right = 230.0f;
				dst.m_bottom = 515.0f;
				Draw::Draw(43, &src, &dst, it, 0.0f);

				//スペシャル技5ボタン表示
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 100.0f;
				src.m_bottom = 100.0f;

				dst.m_top = 485.0f;
				dst.m_left = 100.0f;
				dst.m_right = 230.0f;
				dst.m_bottom = 615.0f;
				Draw::Draw(44, &src, &dst, it, 0.0f);


				//スペシャル技1メッセージウィンドウ表示
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 200.0f;
				src.m_bottom = 100.0f;

				dst.m_top = 100.0f;
				dst.m_left = 235.0f;
				dst.m_right = 1100.0f;
				dst.m_bottom = 200.0f;
				Draw::Draw(45, &src, &dst, it, 0.0f);
				Font::StrDraw(L"メリット", 245.0f, 110.0f, 20.0f, black);
				Font::StrDraw(L"相手の惑星に固定ダメージを与える", 245.0f, 140.0f, 20.0f, black);
				Font::StrDraw(L"ダメージ量は惑星の削るHPの1.2倍のダメージを与える", 245.0f, 170.0f, 20.0f, black);
				Font::StrDraw(L"デメリット", 745.0f, 110.0f, 20.0f, black);
				Font::StrDraw(L"一回しか使えない", 745.0f, 140.0f, 20.0f, black);

				//スペシャル技2メッセージウィンドウ表示
				dst.m_top = 200.0f;
				dst.m_left = 235.0f;
				dst.m_right = 1100.0f;
				dst.m_bottom = 300.0f;
				Draw::Draw(45, &src, &dst, it, 0.0f);
				Font::StrDraw(L"メリット", 245.0f, 210.0f, 20.0f, black);
				Font::StrDraw(L"相手の攻撃一列を破壊する", 245.0f, 240.0f, 20.0f, black);
				Font::StrDraw(L"デメリット", 745.0f, 210.0f, 20.0f, black);
				Font::StrDraw(L"一回しか使えない", 745.0f, 240.0f, 20.0f, black);

				//スペシャル技3メッセージウィンドウ表示
				dst.m_top = 300.0f;
				dst.m_left = 235.0f;
				dst.m_right = 1100.0f;
				dst.m_bottom = 400.0f;
				Draw::Draw(45, &src, &dst, it, 0.0f);
				Font::StrDraw(L"メリット", 245.0f, 310.0f, 20.0f, black);
				Font::StrDraw(L"約10秒間無敵になることができる", 245.0f, 340.0f, 20.0f, black);
				Font::StrDraw(L"デメリット", 745.0f, 310.0f, 20.0f, black);
				Font::StrDraw(L"一回しか使えない", 745.0f, 340.0f, 20.0f, black);

				//スペシャル技4メッセージウィンドウ表示
				dst.m_top = 400.0f;
				dst.m_left = 235.0f;
				dst.m_right = 1100.0f;
				dst.m_bottom = 500.0f;
				Draw::Draw(45, &src, &dst, it, 0.0f);
				Font::StrDraw(L"メリット", 245.0f, 410.0f, 20.0f, black);
				Font::StrDraw(L"20秒間攻撃スピードアップ", 245.0f, 440.0f, 20.0f, black);
				Font::StrDraw(L"武器生産頻度アップ", 245.0f, 470.0f, 20.0f, black);
				Font::StrDraw(L"デメリット", 745.0f, 410.0f, 20.0f, black);
				Font::StrDraw(L"一回しか使えない", 745.0f, 440.0f, 20.0f, black);


				//スペシャル技5メッセージウィンドウ表示
				dst.m_top = 500.0f;
				dst.m_left = 235.0f;
				dst.m_right = 1100.0f;
				dst.m_bottom = 600.0f;
				Draw::Draw(45, &src, &dst, it, 0.0f);
				Font::StrDraw(L"メリット", 245.0f, 510.0f, 20.0f, black);
				Font::StrDraw(L"住民のポッド5機攻撃が上がる", 245.0f, 540.0f, 20.0f, black);
				Font::StrDraw(L"(現在ライン上に出ているポッドを含めて)", 245.0f, 570.0f, 20.0f, black);
				Font::StrDraw(L"デメリット", 745.0f, 510.0f, 20.0f, black);
				Font::StrDraw(L"一回しか使えない", 745.0f, 540.0f, 20.0f, black);


				m_Special_icon_color[i] = 1.0f;
			}
			//未習得の処理
			else
			{
				m_Special_icon_color[i] = 0.0f;
			}
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

		//▼装備
		Font::StrDraw(L"装備", 500.0f, 110.0f, 50.0f, black);

		//パワー
		Font::StrDraw(L"パワー", 120.0f, 200.0f, 40.0f, red);
		Font::StrDraw(type_num[0], 355.0f, 200.0f, 40.0f, black);

		//ディフェンス
		Font::StrDraw(L"ディフェンス", 120.0f, 460.0f, 40.0f, green);
		Font::StrDraw(type_num[1], 360.0f, 460.0f, 40.0f, black);

		//スピード
		Font::StrDraw(L"スピード", 120.0f, 330.0f, 40.0f, blue);
		Font::StrDraw(type_num[2], 360.0f, 330.0f, 40.0f, black);

		//バランス
		Font::StrDraw(L"バランス", 620.0f, 200.0f, 40.0f, yellow);
		Font::StrDraw(type_num[3], 880.0f, 200.0f, 40.0f, black);

		//▼ポッド
		Font::StrDraw(L"ポッド", 620.0f, 330.0f, 40.0f, black);
		Font::StrDraw(type_num[4], 880.0f, 330.0f, 40.0f, black);

	}
}
