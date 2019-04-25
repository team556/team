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

	k = 0; //資材の所持している数
	p = 0;//住民パワーの値
	s = 0;//住民スピードの値
	d = 0;//住民ディフェンスの値
	b = 0;//住民バランスの値
	r = 0;//研究員の値
	crvp = 0;//補正値パワー
	crvs = 0;//補正値スピード
	crvd = 0;//補正値ディフェンス
	crvbh = 0;//補正値バランス	体力
	crvbp = 0;//補正値バランス	パワー
	crvbs = 0;//補正値バランス	スピード
	crvr = 0;//補正値研究員

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
			m_Back_Button_color = 1.0f;

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

	//資材、住民、スペシャル技、装備画面の戻るボタン
	if (window_start_manage == Materials|| window_start_manage == Residents||
		window_start_manage == Specialskill|| window_start_manage == Soubicheck)
	{
		//戻るボタン選択
		if (50 < m_mou_x && m_mou_x < 100 && 50 < m_mou_y && m_mou_y < 100)
		{
			m_Back_Button_color = 1.0f;

			//左クリックされたらフラグを立て、倉庫ウインドウを閉じる
			if (m_mou_l == true)
			{
				//クリック押したままの状態では入力出来ないようにしている
				if (m_key_lf == true)
				{
					m_key_lf = false;

					//"どのウインドウも開いていない状態"フラグを立てる
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
			m_Back_Button_color = INI_COLOR;

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

	//▽フォント準備
	//倉庫用
	wchar_t Ware[5];
	swprintf_s(Ware, L"倉庫", g_Ware);

	//資材(名前・持っている数)表示
	wchar_t mrl[256];
	swprintf_s(mrl, L"%d 個", k);

	//住民(各ステータス)表示
	//パワー
	wchar_t pow[256];
	swprintf_s(pow, L"Lv%d", p);

	//スピード
	wchar_t spd[256];
	swprintf_s(spd, L"Lv%d", s);

	//ディフェンス
	wchar_t dfs[256];
	swprintf_s(dfs, L"Lv%d", d);

	//バランス
	wchar_t brs[256];
	swprintf_s(brs, L"Lv%d", b);

	//研究員
	wchar_t rsc[256];
	swprintf_s(rsc, L"Lv%d", r);

	//補正値パワー
	wchar_t crvp[256];
	swprintf_s(crvp, L"攻撃力＋%d", crvp);

	//補正値スピード
	wchar_t crvs[256];
	swprintf_s(crvs, L"素早さ＋%d", crvs);

	//補正値ディフェンス
	wchar_t crvd[256];
	swprintf_s(crvd, L"体力  ＋%d", crvd);

	//補正値バランス	体力
	wchar_t crvbh[256];
	swprintf_s(crvbh, L"体力  ＋%d", crvbh);
	//補正値バランス	パワー
	wchar_t crvbp[256];
	swprintf_s(crvbp, L"攻撃力＋%d", crvbp);
	//補正値バランス	スピード
	wchar_t crvbs[256];
	swprintf_s(crvbs, L"素早さ＋%d", crvbs);

	//補正値研究員
	wchar_t crvr[256];
	swprintf_s(crvr, L"%d", crvr);

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
		Font::StrDraw(mrl, 280.0f, 170.0f, 30.0f, black);

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
		Font::StrDraw(mrl, 580.0f, 170.0f, 30.0f, black);

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
		Font::StrDraw(mrl, 950.0f, 170.0f, 30.0f, black);

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
		Font::StrDraw(mrl, 240.0f, 330.0f, 30.0f, black);

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
		Font::StrDraw(mrl, 580.0f, 330.0f, 30.0f, black);

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
		Font::StrDraw(mrl, 950.0f, 330.0f, 30.0f, black);

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
		Font::StrDraw(mrl, 580.0f, 500.0f, 30.0f, black);
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
		//パワー
		Font::StrDraw(L"パワー", 180.0f, 130.0f, 30.0f, black);
		Font::StrDraw(pow,300.0f, 130.0f, 30.0f, black);
		Font::StrDraw(L"補正値", 180.0f, 200.0f, 30.0f, black);
		Font::StrDraw(crvp, 300.0f, 200.0f, 30.0f, black);
		
		//スピード
		Font::StrDraw(L"スピード", 180.0f, 300.0f, 30.0f, black);
		Font::StrDraw(spd, 330.0f, 300.0f, 30.0f, black);
		Font::StrDraw(L"補正値", 180.0f, 370.0f, 30.0f, black);
		Font::StrDraw(crvs, 300.0f, 370.0f, 30.0f, black);

		//ディフェンス
		Font::StrDraw(L"ディフェンス", 180.0f, 470.0f, 30.0f, black);
		Font::StrDraw(dfs, 390.0f, 470.0f, 30.0f, black);
		Font::StrDraw(L"補正値", 180.0f, 540.0f, 30.0f, black);
		Font::StrDraw(crvd, 300.0f, 540.0f, 30.0f, black);

		//バランス
		Font::StrDraw(L"バランス", 620.0f, 130.0f, 30.0f, black);
		Font::StrDraw(brs, 780.0f, 130.0f, 30.0f, black);
		Font::StrDraw(L"補正値", 620.0f, 200.0f, 30.0f, black);
		Font::StrDraw(crvbh, 780.0f, 200.0f, 30.0f, black);
		Font::StrDraw(crvbp, 780.0f, 250.0f, 30.0f, black);
		Font::StrDraw(crvbs, 780.0f, 300.0f, 30.0f, black);

		//研究員
		Font::StrDraw(L"研究員", 620.0f, 470.0f, 30.0f, black);
		Font::StrDraw(brs, 780.0f, 470.0f, 30.0f, black);
		Font::StrDraw(L"補正値", 620.0f, 540.0f, 30.0f, black);
		Font::StrDraw(crvbh, 780.0f, 540.0f, 30.0f, black);


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

		//スペシャル技1選択ボタン表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 100.0f;
		src.m_bottom = 100.0f;

		dst.m_top = 100.0f;
		dst.m_left = 100.0f;
		dst.m_right = 200.0f;
		dst.m_bottom = 200.0f;
		Draw::Draw(40, &src, &dst, it, 0.0f);

		//スペシャル技2選択ボタン表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 100.0f;
		src.m_bottom = 100.0f;

		dst.m_top = 200.0f;
		dst.m_left = 100.0f;
		dst.m_right = 200.0f;
		dst.m_bottom = 300.0f;
		Draw::Draw(41, &src, &dst, it, 0.0f);

		//スペシャル技3選択ボタン表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 100.0f;
		src.m_bottom = 100.0f;

		dst.m_top = 300.0f;
		dst.m_left = 100.0f;
		dst.m_right = 200.0f;
		dst.m_bottom = 400.0f;
		Draw::Draw(42, &src, &dst, it, 0.0f);

		//スペシャル技4選択ボタン表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 100.0f;
		src.m_bottom = 100.0f;

		dst.m_top = 400.0f;
		dst.m_left = 100.0f;
		dst.m_right = 200.0f;
		dst.m_bottom = 500.0f;
		Draw::Draw(43, &src, &dst, it, 0.0f);

		//スペシャル技5選択ボタン表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 100.0f;
		src.m_bottom = 100.0f;

		dst.m_top = 500.0f;
		dst.m_left = 100.0f;
		dst.m_right = 200.0f;
		dst.m_bottom = 600.0f;
		Draw::Draw(44, &src, &dst, it, 0.0f);

		//スペシャル技1メッセージウィンドウ表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 200.0f;
		src.m_bottom = 100.0f;

		dst.m_top = 100.0f;
		dst.m_left = 300.0f;
		dst.m_right = 1100.0f;
		dst.m_bottom = 200.0f;
		Draw::Draw(45, &src, &dst, it, 0.0f);
		Font::StrDraw(L"メリット", 310.0f, 110.0f, 20.0f, black);
		Font::StrDraw(L"相手の惑星に固定ダメージを与える", 310.0f, 135.0f, 20.0f, black);
		Font::StrDraw(L"ダメージ量は惑星の削るHPの1.2倍のダメージを与える", 310.0f, 160.0f, 20.0f, black);
		Font::StrDraw(L"デメリット", 810.0f, 110.0f, 20.0f, black);
		Font::StrDraw(L"自分のHPを7%減らす", 810.0f, 135.0f, 20.0f, black);

		//スペシャル技2メッセージウィンドウ表示
		dst.m_top = 200.0f;
		dst.m_left = 300.0f;
		dst.m_right = 1100.0f;
		dst.m_bottom = 300.0f;
		Draw::Draw(45, &src, &dst, it, 0.0f);
		Font::StrDraw(L"メリット", 310.0f, 210.0f, 20.0f, black);
		Font::StrDraw(L"相手の攻撃（一列）をすべて破壊する", 310.0f, 235.0f, 20.0f, black);
		Font::StrDraw(L"デメリット", 710.0f, 210.0f, 20.0f, black);
		Font::StrDraw(L"5秒間から10秒間攻撃力ダウン", 710.0f, 235.0f, 20.0f, black);

		//スペシャル技3メッセージウィンドウ表示
		dst.m_top = 300.0f;
		dst.m_left = 300.0f;
		dst.m_right = 1100.0f;
		dst.m_bottom = 400.0f;
		Draw::Draw(45, &src, &dst, it, 0.0f);
		Font::StrDraw(L"メリット", 310.0f, 310.0f, 20.0f, black);
		Font::StrDraw(L"約10秒間無敵になることができる", 310.0f, 335.0f, 20.0f, black);
		Font::StrDraw(L"デメリット", 710.0f, 310.0f, 20.0f, black);
		Font::StrDraw(L"攻撃力を一定時間ダウン(5秒)", 710.0f, 335.0f, 20.0f, black);

		//スペシャル技4メッセージウィンドウ表示
		dst.m_top = 400.0f;
		dst.m_left = 300.0f;
		dst.m_right = 1100.0f;
		dst.m_bottom = 500.0f;
		Draw::Draw(45, &src, &dst, it, 0.0f);
		Font::StrDraw(L"メリット", 310.0f, 410.0f, 20.0f, black);
		Font::StrDraw(L"20秒間攻撃スピードアップ", 310.0f, 435.0f, 20.0f, black);
		Font::StrDraw(L"武器生産頻度アップ", 310.0f, 460.0f, 20.0f, black);
		Font::StrDraw(L"デメリット", 710.0f, 410.0f, 20.0f, black);
		Font::StrDraw(L"効果が終わると5秒間", 710.0f, 435.0f, 20.0f, black);
		Font::StrDraw(L"生産性が10%ダウン", 710.0f, 460.0f, 20.0f, black);

		//スペシャル技5メッセージウィンドウ表示
		dst.m_top = 500.0f;
		dst.m_left = 300.0f;
		dst.m_right = 1100.0f;
		dst.m_bottom = 600.0f;
		Draw::Draw(45, &src, &dst, it, 0.0f);
		Font::StrDraw(L"メリット", 310.0f, 510.0f, 20.0f, black);
		Font::StrDraw(L"住民の攻撃が上がる", 310.0f, 435.0f, 20.0f, black);
		Font::StrDraw(L"効果が終わると一定時間(5秒)", 710.0f, 435.0f, 20.0f, black);
		Font::StrDraw(L"効果が終わると一定時間(5秒)", 710.0f, 435.0f, 20.0f, black);
		Font::StrDraw(L"効果が終わると一定時間(5秒)", 710.0f, 435.0f, 20.0f, black);

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

	}
}

