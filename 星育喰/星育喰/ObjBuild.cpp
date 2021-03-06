//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjBuild.h"


//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjBuild::Init()
{
	m_x = 50;
	m_y = 50;

	m_key_f = true;
	m_turn = true;
	m_turn0 = true;

}

//アクション
void CObjBuild::Action()
{

	//マウスの位置を取得
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//マウスのボタンの状態
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();
	
	//if (m_x <= m_mou_x && m_mou_x <= m_x + 250.0f) {//X軸の範囲
	//	if (m_y <= m_mou_y && m_mou_y <= m_y + 268.0f) {//Y軸の範囲
	//		if (m_mou_l == true) {//クリック時
	//			if (m_key_f == true && m_turn == true) {
	//				Draw::LoadImage(L"オブジェクト.png", 1, TEX_SIZE_512);
	//				m_key_f = false;
	//				m_turn = false;
	//			}
	//			else if(m_key_f == true && m_turn == false)//2回目のクリック
	//			{
	//				//キャンセル時の範囲
	//				if (m_x <= m_mou_x && m_mou_x <= m_x + 100.0f && m_y <= m_mou_y && m_mou_y <= m_y + 100.0f)
	//				{
	//					Draw::LoadImage(L"建物.jpg", 1, TEX_SIZE_512);
	//					m_key_f = false;
	//					m_turn0 = false;
	//				}
	//			}
	//		}
	//		else{//クリック離した時
	//			m_key_f = true;
	//			if (m_turn0 == false) {
	//				m_turn = true;
	//				m_turn0 = true;
	//			}
	//		}
	//	}
	//}
	
}

////初期化メソッド
//void CObjBuild::InitScene()
//{
//	//
//}
//


//ドロー
void CObjBuild::Draw()
{
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	RECT_F src;
	RECT_F dst;

	//切り取り
	src.m_top    =   0.0f;
	src.m_left   =   0.0f;
	src.m_right  = 450.0f;
	src.m_bottom = 468.0f;

	//描画
	dst.m_top    =   0.0f + m_x;
	dst.m_left   =   0.0f + m_y;
	dst.m_right  = 250.0f + m_x;
	dst.m_bottom = 268.0f + m_y;

	//1番目に登録したグラフィックをsrc,dst,c情報をもとに描画
	Draw::Draw(1, &src, &dst, c, 0.0f);
}

