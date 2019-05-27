//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"
#include "ObjGameClear.h"

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
void CObjGameClear::Init()
{
	m_mou_x = 0.0f;	//マウスX座標
	m_mou_y = 0.0f; //マウスY座標
	m_mou_r = false;//右クリック
	m_mou_l = false;//左クリック

	m_f = false;
	m_y_vec = 0.6;

	for (int i = 0; i < 20; i++)//配列の初期化
		m_cy[i] = i * 80 + 700;	//行間の間隔を空けるのと、画面より下にする
	m_c_nam = 0;
}

//アクション
void CObjGameClear::Action()
{



	//マウスの位置を取得
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//マウスのボタンの状態
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();


}

//ドロー
void CObjGameClear::Draw()
{
	//描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	float d[4] = { 0.0f,0.0f, 0.0f, 1.0f };

	RECT_F src;//切り取り位置
	RECT_F dst;//表示位置
	
	src.m_top   =  0.0f;
	src.m_left  =  0.0f;
	src.m_right =100.0f;
	src.m_bottom=100.0f;
	
	dst.m_top   =  0.0f;
	dst.m_left  =  0.0f;
	dst.m_right =1200.0f;
	dst.m_bottom= 700.0f;

	//0番目に登録したグラフィックをsrc,dst,c情報をもとに描画
	Draw::Draw(1, &src, &dst, d, 0.0f);

	for (int i = 0; i < 20; i++)
	{
		m_cy[i] -= m_y_vec;
	}

	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	Font::StrDraw(L"当プロジェクトメンバー", 500, m_cy[0], 32, c);

	Font::StrDraw(L"プログラマ",	400, m_cy[1], 32, c);

	Font::StrDraw(L"木村　巧",		800, m_cy[1], 32, c);

	Font::StrDraw(L"後庵　穣",		800, m_cy[2], 32, c);

	Font::StrDraw(L"グラフィッカ",	400, m_cy[3], 32, c);

	Font::StrDraw(L"脇田",			800, m_cy[3], 32, c);

	Font::StrDraw(L"かしわん",		800, m_cy[4], 32, c);

	Font::StrDraw(L"サウンド",		400, m_cy[5], 32, c);

	Font::StrDraw(L"池田",			800, m_cy[5], 32, c);

	Font::StrDraw(L"プランナ",		400, m_cy[6], 32, c);

	Font::StrDraw(L"メンバー全員",	800, m_cy[6], 32, c);
}
