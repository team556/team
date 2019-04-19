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
#define INI_COLOR (1.0f) //全カラー明度の初期値

//イニシャライズ
void CObjWarehouse::Init()
{
	m_Ware_color = INI_COLOR;
	m_Back_Button_color = INI_COLOR;

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

	//倉庫選択
	if (95 < m_mou_x && m_mou_x < 320 && 170 < m_mou_y && m_mou_y < 280)
	{
		m_Ware_color = 0.7f;

		//左クリックされたらフラグを立て、倉庫ウインドウを開く
		if (m_mou_l == true)
		{
			//クリック押したままの状態では入力出来ないようにしている
			if (m_key_lf == true)
			{
				m_key_lf = false;

				//倉庫をクリックすると、倉庫が開かれる
				m_key_wh = true;
			}
		}
		else
		{
			m_key_lf = true;
		}
	}
	else
	{
		m_Ware_color = 1.0f;
	}

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

	//資材ボタン選択
	if (350 < m_mou_x && m_mou_x < 525 && 200 < m_mou_y && m_mou_y < 375)
	{
		m_object_ma = 0.7f;

		//左クリックされたらフラグを立て、倉庫ウインドウを閉じる
		if (m_mou_l == true)
		{
			//クリック押したままの状態では入力出来ないようにしている
			if (m_key_ma == true)
			{
				m_key_ma = false;

			}
		}
		else
		{
			m_key_ma = true;
		}
	}
	else
	{
		m_object_ma = 1.0f;

	}

	//住民ボタン選択
	if (700 < m_mou_x && m_mou_x < 875 && 200 < m_mou_y && m_mou_y < 375)
	{
		m_object_re = 0.7f;

		//左クリックされたらフラグを立て、倉庫ウインドウを閉じる
		if (m_mou_l == true)
		{
			//クリック押したままの状態では入力出来ないようにしている
			if (m_key_re == true)
			{
				m_key_re = false;

			}
		}
		else
		{
			m_key_re = true;
		}
	}
	else
	{
		m_object_re = 1.0f;

	}

	//スペシャル技ボタン選択
	if (350 < m_mou_x && m_mou_x < 525 && 450 < m_mou_y && m_mou_y < 625)
	{
		m_object_sp = 0.7f;

		//左クリックされたらフラグを立て、倉庫ウインドウを閉じる
		if (m_mou_l == true)
		{
			//クリック押したままの状態では入力出来ないようにしている
			if (m_key_sp == true)
			{
				m_key_sp = false;

			}
		}
		else
		{
			m_key_sp = true;
		}
	}
	else
	{
		m_object_sp = 1.0f;

	}

	//装備ボタン選択
	if (700 < m_mou_x && m_mou_x < 875 && 450 < m_mou_y && m_mou_y < 625)
	{
		m_object_eq = 0.7f;

		//左クリックされたらフラグを立て、倉庫ウインドウを閉じる
		if (m_mou_l == true)
		{
			//クリック押したままの状態では入力出来ないようにしている
			if (m_key_eq == true)
			{
				m_key_eq = false;

			}
		}
		else
		{
			m_key_eq = true;
		}
	}
	else
	{
		m_object_eq = 1.0f;

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
	float c[4] = { m_Ware_color,m_Ware_color, m_Ware_color, 1.0f };

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

	RECT_F src;//描画先切り取り位置
	RECT_F dst;//描画先表示位置

	//倉庫表示
	//切り取り
	src.m_top    =   0.0f;
	src.m_left   =   0.0f;
	src.m_right  = 225.0f;
	src.m_bottom = 225.0f;

	dst.m_top    = 100.0f;
	dst.m_left   = 100.0f;
	dst.m_right  = 325.0f;
	dst.m_bottom = 325.0f;

	//2番目に登録したグラフィックをsrc,dst,c情報をもとに描画
	Draw::Draw(2, &src, &dst, c, 0.0f);

	//戻るボタンを選択して描画する画像
	if (window_start_manage == Default || window_start_manage == BackButton)
	{
		//背景
		//切り取り
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 100.0f;
		src.m_bottom = 100.0f;

		//表示
		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = 1200.0f;
		dst.m_bottom = 800.0f;

		//0番目に登録したグラフィックをsrc,dst,c情報をもとに描画
		Draw::Draw(0, &src, &dst, h, 0.0f);

		//倉庫表示
		//切り取り
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 225.0f;
		src.m_bottom = 225.0f;

		dst.m_top = 100.0f;
		dst.m_left = 100.0f;
		dst.m_right = 325.0f;
		dst.m_bottom = 325.0f;

		//2番目に登録したグラフィックをsrc,dst,c情報をもとに描画
		Draw::Draw(2, &src, &dst, c, 0.0f);
	}

	//倉庫をクリックした時
	else if (m_key_wh == true)
	{
		//ボタン背景作成
		src.m_top    =    0.0f;
		src.m_left   =    0.0f;
		src.m_right  = 1200.0f;
		src.m_bottom =  800.0f;

		dst.m_top    =   20.0f;
		dst.m_left   =   20.0f;
		dst.m_right  = 1180.0f;
		dst.m_bottom =  680.0f;
		Draw::Draw(3, &src, &dst, sb, 0.0f);

		//戻るアイコン作成
		src.m_top    =   0.0f;
		src.m_left   =   0.0f;
		src.m_right  = 225.0f;
		src.m_bottom = 225.0f;

		dst.m_top    =  20.0f;
		dst.m_left   =  20.0f;
		dst.m_right  =  80.0f;
		dst.m_bottom =  80.0f;
		Draw::Draw(4, &src, &dst, md, 0.0f);
		dst.m_right  =  80.0f;
		dst.m_bottom =  80.0f;
		Draw::Draw(4, &src, &dst, md, 0.0f);

		//資材選択ボタン作成
		src.m_top    = 0.0f;
		src.m_left   = 0.0f;
		src.m_right  = 225.0f;
		src.m_bottom = 225.0f;

		dst.m_top    = 200.0f;
		dst.m_left   = 350.0f;
		dst.m_right  = 525.0f;
		dst.m_bottom = 375.0f;
		Draw::Draw(5, &src, &dst, ma, 0.0f);

		//住民選択ボタン作成
		src.m_top    = 0.0f;
		src.m_left   = 0.0f;
		src.m_right  = 225.0f;
		src.m_bottom = 225.0f;

		dst.m_top    = 200.0f;
		dst.m_left   = 700.0f;
		dst.m_right  = 875.0f;
		dst.m_bottom = 375.0f;
		Draw::Draw(6, &src, &dst, re, 0.0f);

		//スペシャル技選択ボタン作成
		src.m_top    = 0.0f;
		src.m_left   = 0.0f;
		src.m_right  = 225.0f;
		src.m_bottom = 225.0f;

		dst.m_top    = 450.0f;
		dst.m_left   = 350.0f;
		dst.m_right  = 525.0f;
		dst.m_bottom = 625.0f;
		Draw::Draw(7, &src, &dst, sp, 0.0f);

		//資材選択ボタン作成
		src.m_top    = 0.0f;
		src.m_left   = 0.0f;
		src.m_right  = 225.0f;
		src.m_bottom = 225.0f;
		//装備選択ボタン作成
		src.m_top    = 0.0f;
		src.m_left   = 0.0f;
		src.m_right  = 225.0f;
		src.m_bottom = 225.0f;

		dst.m_top    = 200.0f;
		dst.m_left   = 350.0f;
		dst.m_right  = 525.0f;
		dst.m_bottom = 375.0f;
		Draw::Draw(5, &src, &dst, ma, 0.0f);
		dst.m_top    = 450.0f;
		dst.m_left   = 700.0f;
		dst.m_right  = 875.0f;
		dst.m_bottom = 625.0f;
		Draw::Draw(8, &src, &dst, eq, 0.0f);
	}

	//戻るボタンを選択して描画する画像
	else if (m_key_md == true)
	{
		//背景
		//切り取り
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 100.0f;
		src.m_bottom = 100.0f;

		//スペシャル技選択ボタン作成
		src.m_top    = 0.0f;
		src.m_left   = 0.0f;
		src.m_right  = 225.0f;
		src.m_bottom = 225.0f;

		dst.m_top    = 450.0f;
		dst.m_left   = 350.0f;
		dst.m_right  = 525.0f;
		dst.m_bottom = 625.0f;
		Draw::Draw(7, &src, &dst, sp, 0.0f);

		//倉庫表示
		//切り取り
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 225.0f;
		//装備選択ボタン作成
		src.m_top    = 0.0f;
		src.m_left   = 0.0f;
		src.m_right  = 225.0f;
		src.m_bottom = 225.0f;

		dst.m_top = 100.0f;
		dst.m_left = 100.0f;
		dst.m_right = 325.0f;
		dst.m_bottom = 325.0f;

		//2番目に登録したグラフィックをsrc,dst,c情報をもとに描画
		Draw::Draw(2, &src, &dst, c, 0.0f);
		dst.m_top    = 450.0f;
		dst.m_left   = 700.0f;
		dst.m_right  = 875.0f;
		dst.m_bottom = 625.0f;
		Draw::Draw(8, &src, &dst, eq, 0.0f);
	}

}

