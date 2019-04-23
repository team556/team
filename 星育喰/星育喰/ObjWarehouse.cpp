//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjWarehouse.h"

//使用するネームスペース
using namespace GameL;

//マクロ
#define INI_ALPHA (0.0f) //透過度(アルファ値)の初期値
#define INI_COLOR (1.0f) //全カラー明度の初期値

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
		//戻るボタン選択
		if (30 < m_mou_x && m_mou_x < 80 && 30 < m_mou_y && m_mou_y < 80)
		{
			m_Back_Button_color = 0.7f;

			//左クリックされたらフラグを立て、倉庫ウインドウを閉じる
			if (m_mou_l == true)
			{
				//クリック押したままの状態では入力出来ないようにしている
				if (m_key_lf == true)
				{
					m_key_lf = false;

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
			m_introduce_f = false;//施設紹介ウィンドウを非表示にする
			m_Back_Button_color = 1.0f;
		}
		if (window_start_manage == Materials)
		{
			//資材ボタン選択
			if (350 < m_mou_x && m_mou_x < 525 && 200 < m_mou_y && m_mou_y < 375)
			{
				m_object_ma = 0.7f;

				//左クリックされたらフラグを立て、資材ウインドウを開く
				if (m_mou_l == true)
				{
					//クリック押したままの状態では入力出来ないようにしている
					if (m_key_lf == true)
					{
						m_key_lf = false;

						//"資材ウィンドウを開いている状態"フラグを立てる
						window_start_manage = Materials;
					}
				}
				else
				{
					m_key_lf = true;
				}
			}
			else
			{
				m_object_ma = 1.0f;

			}

		}

		//住民ボタン選択
		if (680 < m_mou_x && m_mou_x < 1005 && 150 < m_mou_y && m_mou_y < 325)
		{
			m_object_re = 0.7f;

			//左クリックされたらフラグを立て、住民ウインドウを開く
			if (m_mou_l == true)
			{
				//クリック押したままの状態では入力出来ないようにしている
				if (m_key_lf == true)
				{
					m_key_lf = false;

					//"住民ウィンドウを開いている状態"フラグを立てる
					window_start_manage = Residents;
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
		else
		{
			m_object_re = 1.0f;

		}

		//スペシャル技ボタン選択
		if (245 < m_mou_x && m_mou_x < 560 && 390 < m_mou_y && m_mou_y < 570)
		{
			m_object_sp = 0.7f;

			//左クリックされたらフラグを立て、スペシャル技ウインドウを開く
			if (m_mou_l == true)
			{
				//クリック押したままの状態では入力出来ないようにしている
				if (m_key_lf == true)
				{
					m_key_lf = false;

					//"スペシャル技ウィンドウを開いている状態"フラグを立てる
					window_start_manage = Specialskill;
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
		else
		{
			m_object_sp = 1.0f;

		}

		//装備ボタン選択
		if (680 < m_mou_x && m_mou_x < 1005 && 390 < m_mou_y && m_mou_y < 570)
		{
			m_object_eq = 0.7f;

			//左クリックされたらフラグを立て、装備ウインドウを開く
			if (m_mou_l == true)
			{
				//クリック押したままの状態では入力出来ないようにしている
				if (m_key_lf == true)
				{
					m_key_lf = false;

					//"装備ウィンドウを開いている状態"フラグを立てる
					window_start_manage = Soubicheck;
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
		else
		{
			m_object_eq = 1.0f;

		}
	}

	//倉庫選択
	if (95 < m_mou_x && m_mou_x < 320 && 170 < m_mou_y && m_mou_y < 280)
	{
		m_introduce_f = true;	//施設紹介ウィンドウを表示する
		m_Ware_color = 0.7f;
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
		m_Ware_color = 1.0f;
	}

	//資材ボタン選択
	if (245 < m_mou_x && m_mou_x < 560 && 150 < m_mou_y && m_mou_y < 325)
	{
		m_object_ma = 0.7f;

		//左クリックされたらフラグを立て、資材ウインドウを開く
		if (m_mou_l == true)
		{
			//クリック押したままの状態では入力出来ないようにしている
			if (m_key_lf == true)
			{
				m_key_lf = false;

				//"資材ウィンドウを開いている状態"フラグを立てる
				window_start_manage = Materials;
			}
		}
		else
		{
			m_key_lf = true;
		}
	}
	else
	{
		m_object_ma = 1.0f;

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

	//フォントの色
	float Ware[4] = { 1.0f,1.0f,1.0f,1.0f };

	//▽フォント準備
	//倉庫用
	wchar_t g_Ware[5];
	swprintf_s(g_Ware, L"倉庫", g_Ware);

	RECT_F src;//描画先切り取り位置
	RECT_F dst;//描画先表示位置

	//施設紹介ウィンドウ(兵舎、研究所、倉庫)が開いていない時に表示するグラフィック
	if (window_start_manage == Default || window_start_manage == BackButton)
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
			Draw::Draw(21, &src, &dst, Ware, 0.0f);//灰色のウインドウにする為"ins"にしている。

		    //▼フォント表示
		    //倉庫
			Font::StrDraw(g_Ware, m_mou_x - 95.0f, m_mou_y - 45.0f, 30.0f, white);

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
		src.m_top    = 2.0f;
		src.m_left   = 4.0f;
		src.m_right  = 768.0f;
		src.m_bottom = 614.0f;

		dst.m_top    = 150.0f;
		dst.m_left   = 250.0f;
		dst.m_right  = 1018.0f;
		dst.m_bottom = 764.0f;
		Draw::Draw(28, &src, &dst, ma, 0.0f);

		//▼住民選択ボタン表示
		src.m_top    = 2.0f;
		src.m_left   = 4.0f;
		src.m_right  = 768.0f;
		src.m_bottom = 614.0f;

		dst.m_top    = 150.0f;
		dst.m_left   = 700.0f;
		dst.m_right  = 1468.0f;
		dst.m_bottom = 764.0f;
		Draw::Draw(29, &src, &dst, re, 0.0f);

		//▼スペシャル技選択ボタン表示
		src.m_top    = 2.0f;
		src.m_left   = 4.0f;
		src.m_right  = 768.0f;
		src.m_bottom = 614.0f;

		dst.m_top    = 400.0f;
		dst.m_left   = 250.0f;
		dst.m_right  = 1018.0f;
		dst.m_bottom = 1014.0f;
		Draw::Draw(30, &src, &dst, sp, 0.0f);

		//▼装備選択ボタン表示
		src.m_top    = 2.0f;
		src.m_left   = 4.0f;
		src.m_right  = 768.0f;
		src.m_bottom = 614.0f;

		dst.m_top    = 400.0f;
		dst.m_left   = 700.0f;
		dst.m_right  = 1468.0f;
		dst.m_bottom = 1014.0f;
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
			Draw::Draw(21, &src, &dst, Ware, 0.0f);//灰色のウインドウにする為"ins"にしている。

		    //▼フォント表示
			//研究所レベル
			Font::StrDraw(g_Ware, m_mou_x - 95.0f, m_mou_y - 45.0f, 30.0f, white);
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

		//▼鉄表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 192.0f;
		src.m_bottom = 167.0f;

		dst.m_top = 120.0f;
		dst.m_left = 450.0f;
		dst.m_right = 642.0f;
		dst.m_bottom = 287.0f;
		Draw::Draw(34, &src, &dst, it, 0.0f);

		//▼銀表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 192.0f;
		src.m_bottom = 170.0f;

		dst.m_top = 120.0f;
		dst.m_left = 800.0f;
		dst.m_right = 992.0f;
		dst.m_bottom = 290.0f;
		Draw::Draw(35, &src, &dst, it, 0.0f);

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

		//▼アルミニウム表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 192.0f;
		src.m_bottom = 176.0f;

		dst.m_top = 290.0f;
		dst.m_left = 450.0f;
		dst.m_right = 642.0f;
		dst.m_bottom = 466.0f;
		Draw::Draw(37, &src, &dst, it, 0.0f);

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

		//▼レアメタル表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 179.0f;
		src.m_bottom = 179.0f;

		dst.m_top = 430.0f;
		dst.m_left = 450.0f;
		dst.m_right = 629.0f;
		dst.m_bottom = 629.0f;
		Draw::Draw(39, &src, &dst, it, 0.0f);
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
	}
}

