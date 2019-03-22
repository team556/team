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
	m_f = false;

	m_x = 100;
	m_y = 100;
	//m_obx = 0;
	//m_oby = 0;

	//m_key_f = true;
	//m_turn = true;
	//m_turn0 = true;
	//
	//m_obj = true;

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
	if (m_x < m_mou_x && m_mou_x < m_x+225 && m_y < m_mou_y && m_mou_y < m_y+225)
	{
		m_Ware_color = 0.7f;

		//左クリックされたらフラグを立て、倉庫ウインドウを開く
		if (m_mou_l == true)
		{
			
			//クリック押したままの状態では入力出来ないようにしている
			if (m_key_f == true)
			{
				m_key_f = false;

				//↓test_flagのアレでやる。
				m_f = true;
			}
		}
		else
		{
			m_key_f = true;
		}
	}
	else
	{
		m_Ware_color = 1.0f;
	}

	//戻るボタン選択
	if (20 < m_mou_x && m_mou_x < 135 && 20 < m_mou_y && m_mou_y < 135)
	{
		m_Back_color = 0.7f;

		//左クリックされたらフラグを立て、倉庫ウインドウを閉じる
		if (m_mou_l == true)
		{

			//クリック押したままの状態では入力出来ないようにしている
			if (m_key_md == true)
			{
				m_key_md = false;

				//↓test_flagのアレでやる。
				m_f = true;
			}
		}
		else
		{
			m_key_md = true;
		}
	}
	else
	{
		m_Back_color = 1.0f;
	}

	//戻るボタン選択
	if (350 < m_mou_x && m_mou_x < 525 && 200 < m_mou_y && m_mou_y < 375)
	{
		m_Object_color[0] = 0.7f;

		//左クリックされたらフラグを立て、倉庫ウインドウを閉じる
		if (m_mou_l == true)
		{

			//クリック押したままの状態では入力出来ないようにしている
			if (m_key_ma == true)
			{
				m_key_ma = false;

				//↓test_flagのアレでやる。
				m_f = true;
			}
		}
		else
		{
			m_key_ma = true;
		}
	}
	else
	{
		m_Object_color[0] = 1.0f;

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

	//それ以外の画像
	float sb[4] = { 1.0f,1.0f,1.0f,1.0f };
	float mb[4] = { m_Back_color,m_Back_color,m_Back_color,1.0f };
	float bt[4] = { m_Object_color[3],m_Object_color[3],m_Object_color[3],1.0f };

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

	if (m_f == true)
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
		dst.m_right  = 135.0f;
		dst.m_bottom = 135.0f;
		Draw::Draw(4, &src, &dst, mb, 0.0f);

		//資材選択ボタン作成
		src.m_top    = 0.0f;
		src.m_left   = 0.0f;
		src.m_right  = 225.0f;
		src.m_bottom = 225.0f;

		dst.m_top    = 200.0f;
		dst.m_left   = 350.0f;
		dst.m_right  = 525.0f;
		dst.m_bottom = 375.0f;
		Draw::Draw(5, &src, &dst, bt, 0.0f);

		//住民選択ボタン作成
		src.m_top    = 0.0f;
		src.m_left   = 0.0f;
		src.m_right  = 225.0f;
		src.m_bottom = 225.0f;

		dst.m_top    = 200.0f;
		dst.m_left   = 700.0f;
		dst.m_right  = 875.0f;
		dst.m_bottom = 375.0f;
		Draw::Draw(6, &src, &dst, bt, 0.0f);

		//スペシャル技選択ボタン作成
		src.m_top    = 0.0f;
		src.m_left   = 0.0f;
		src.m_right  = 225.0f;
		src.m_bottom = 225.0f;

		dst.m_top    = 450.0f;
		dst.m_left   = 350.0f;
		dst.m_right  = 525.0f;
		dst.m_bottom = 625.0f;
		Draw::Draw(7, &src, &dst, bt, 0.0f);

		//装備選択ボタン作成
		src.m_top    = 0.0f;
		src.m_left   = 0.0f;
		src.m_right  = 225.0f;
		src.m_bottom = 225.0f;

		dst.m_top    = 450.0f;
		dst.m_left   = 700.0f;
		dst.m_right  = 875.0f;
		dst.m_bottom = 625.0f;
		Draw::Draw(8, &src, &dst, bt, 0.0f);

	}

	if (m_key_md == true)
	{
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
	}

}

