//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"
#include "ObjTest.h"

//使用するネームスペース
using namespace GameL;

////コンストラクタ
//CObjTest::CObjTest(float x, float y)
//{
//	//作成時に渡された値を、座標の初期値に代入
//	m_x = x;
//	m_y = y;
//}

//イニシャライズ
void CObjTest::Init()
{
	//m_f = false;
}

//アクション
void CObjTest::Action()
{
	//testA


	////マウスの位置を取得
	//m_mou_x = (float)Input::GetPosX();
	//m_mou_y = (float)Input::GetPosY();
	////マウスのボタンの状態
	//m_mou_r = Input::GetMouButtonR();
	//m_mou_l = Input::GetMouButtonL();

	//if (700 < m_mou_x && m_mou_x < 900 && 300 < m_mou_y && m_mou_y < 500)
	//{
	//	m_f = true;
	//	test_flag = true;
	//}
	//else
	//{
	//	m_f = false;
	//	test_flag = false;
	//}
}

//ドロー
void CObjTest::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	Font::StrDraw(L"", 230, 250, 32, c);
	
	//描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	float d[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	RECT_F src;//切り取り位置
	RECT_F dst;//表示位置
	
	src.m_top   =  0.0f;
	src.m_left  =  0.0f;
	src.m_right =100.0f;
	src.m_bottom=100.0f;
	
	dst.m_top   =  0.0f;
	dst.m_left  =  0.0f;
	dst.m_right =100.0f;
	dst.m_bottom=100.0f;

	//0番目に登録したグラフィックをsrc,dst,c情報をもとに描画
	Draw::Draw(0, &src, &dst, d, 0.0f);





	//src.m_top = 0.0f;
	//src.m_left = 0.0f;
	//src.m_right = 300.0f;
	//src.m_bottom = 168.0f;

	//dst.m_top = 300.0f;
	//dst.m_left = 700.0f;
	//dst.m_right = 900.0f;
	//dst.m_bottom = 500.0f;

	////50番目に登録したグラフィックをsrc,dst,c情報をもとに描画
	//Draw::Draw(50, &src, &dst, d, 0.0f);

	//if (m_f == true || test_flag == true)
	//{
	//	Font::StrDraw(L"OK", 230, 250, 32, c);
	//}
}
