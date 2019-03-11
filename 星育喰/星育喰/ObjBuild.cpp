//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjBuild.h"

#define TESTX m_x + 100
#define TESTY m_y + 100

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjBuild::Init()
{
	m_x = 200;
	m_y = 200;

	m_key_f = true;
	m_turn = true;

	//m_build = true;

	////当たり判定用HitBoxを作成
	//Hits::SetHitBox(this, m_x, m_y, 450, 468, ELEMENT_BUILD, OBJ_BUILD, 1);

}

//アクション
void CObjBuild::Action()
{
	////マウスの位置を取得+
	//m_mou_x = (float)Input::GetPosX();
	//m_mou_y = (float)Input::GetPosY();
	////マウスのボタンの状態
	//m_mou_r = Input::GetMouButtonR();
	//m_mou_l = Input::GetMouButtonL();


	////左クリックで選択または決定
	//if (Input::GetMouButtonL() == true && m_x < m_mou_x && m_mou_x < m_x && m_y < m_mou_y && m_mou_y < m_y)
	//{
	//	//test用オブジェクト作成
	//	Draw::LoadImage(L"オブジェクト.png", 1, TEX_SIZE_512);

	//}
	//else if (m_x < m_mou_x && m_mou_x < m_x + 100 && m_y < m_mou_y && m_mou_y < m_y + 100)
	//{
	//	if (m_mou_l == true && m_build ==true)
	//	{
	//		Draw::LoadImage(L"建物.jpg", 1, TEX_SIZE_512);
	//		m_mou_l = false;
	//		m_build = false;
	//	}
	//}

	//else if (m_x < m_mou_x && m_mou_x < m_x + 450 && m_y < m_mou_y && m_mou_y < m_y + 468)
	//{
	//	//マウスのボタンが押されたら……
	//	if (m_mou_l == true && m_build == true)
	//	{
	//		Draw::LoadImage(L"オブジェクト.png", 1, TEX_SIZE_512);
	//		m_mou_l = false;
	//		m_build = false;
	//	}
	//}

	//else
	//{
	//	m_build = true;
	//}

	/*マウスの位置を取得
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	マウスのボタンの状態
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	if (m_mou_l == true)
	{
		if (TESTX < m_mou_x && m_mou_x < m_x + 450 && TESTY < m_mou_y && m_mou_y < m_y + 468
			&& m_build == false)
		{
			Draw::LoadImage(L"オブジェクト.png", 1, TEX_SIZE_512);
			m_build = true;
		}

		else if (m_x < m_mou_x && m_mou_x < TESTX && m_y < m_mou_y && m_mou_y < TESTY
			&& m_return == false)
		{
			Draw::LoadImage(L"建物.jpg", 1, TEX_SIZE_512);
			m_return = true;
		}
	}
	else
	{
		m_build = false;
		m_return = false;
	}*/

	//マウスの位置を取得
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//マウスのボタンの状態
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();
	
	if (m_x <= m_mou_x && m_mou_x <= m_x + 450.0f) {//X軸の範囲
		if (m_y <= m_mou_y && m_mou_y <= m_y + 468.0f) {//Y軸の範囲
			if (m_mou_l == true) {//クリック時
				if (m_key_f == true && m_turn == true) {
					Draw::LoadImage(L"オブジェクト.png", 1, TEX_SIZE_512);
					m_key_f = false;
					m_turn = false;
				}
				else if(m_turn == false)//2回目のクリック
				{
					Draw::LoadImage(L"建物.jpg", 1, TEX_SIZE_512);
				}
			}
			else{//クリック離した時
				m_key_f = true;
			}
		}
	}
	
	
	


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
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 450.0f;
	src.m_bottom =468.0f;

	//描画
	dst.m_top = 0.0f + m_x;
	dst.m_left = 0.0f + m_y;
	dst.m_right = 450.0f + m_x;
	dst.m_bottom = 468.0f + m_y;

	//2番目に登録したグラフィックをsrc,dst,c情報をもとに描画
	Draw::Draw(1, &src, &dst, c, 0.0f);
}

