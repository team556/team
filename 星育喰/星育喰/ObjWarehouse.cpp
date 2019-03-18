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

//イニシャライズ
void CObjWarehouse::Init()
{
	m_x = 100;
	m_y = 100;
	m_obx = 0;
	m_oby = 0;

	m_key_f = true;
	m_turn = true;
	m_turn0 = true;
	
	m_obj = true;

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

	if (m_x <= m_mou_x && m_mou_x <= m_x + 225.0f) {//X軸の範囲
		if (m_y <= m_mou_y && m_mou_y <= m_y + 225.0f) {//Y軸の範囲
			if (m_mou_l == true) {//クリック時
				if (m_key_f == true && m_turn == true) {
					m_key_f = false;
					m_turn = false;

					m_obx = 1150;
					m_oby = 650;
					m_obj = false;
				}
				else if (m_key_f == true && m_turn == false)//2回目のクリック
				{
					//キャンセル時の範囲
					if (m_x <= m_mou_x && m_mou_x <= m_x + 100.0f && m_y <= m_mou_y && m_mou_y <= m_y + 100.0f)
					{
						m_key_f = false;
						m_turn0 = false;

						m_obx = 225;
						m_oby = 225;
						m_obj = true;
					}
				}
			}
			else {//クリック離した時
				m_key_f = true;
				if (m_turn0 == false) {
					m_turn = true;
					m_turn0 = true;
				}
			}
		}
	}

}

//ドロー
void CObjWarehouse::Draw()
{
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	RECT_F src;
	RECT_F dst;

	//切り取り
	src.m_top    =   0.0f;
	src.m_left   =   0.0f;
	src.m_right  = 225.0f;
	src.m_bottom = 225.0f;

	if (m_obj == true)
	{
		//描画
		dst.m_top    =   0.0f + m_x;
		dst.m_left   =   0.0f + m_y;
		dst.m_right  = 225.0f + m_x;
		dst.m_bottom = 225.0f + m_y;
	}

	else
	{
		dst.m_top    = 50.0f;
		dst.m_left   = 50.0f;
		dst.m_right  = m_obx;
		dst.m_bottom = m_oby;
	}

	//2番目に登録したグラフィックをsrc,dst,c情報をもとに描画
	Draw::Draw(2, &src, &dst, c, 0.0f);


	//ボタンオブジェクト
	//切り取り
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1200.0f;
	src.m_bottom = 800.0f;

	//表示
	dst.m_top = 50.0f;
	dst.m_left = 50.0f;
	dst.m_right = 1150.0f;
	dst.m_bottom = 650.0f;

	//3番目に登録したグラフィックをsrc,dst,c情報をもとに描画
	Draw::Draw(3, &src, &dst, c, 0.0f);
}

