//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameHead.h"
#include "ObjHuman.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjHuman::Init()
{

}

//アクション
void CObjHuman::Action()
{

}

//ドロー
void CObjHuman::Draw()
{

	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	RECT_F src;
	RECT_F dst;

	src.m_top   = 0.0f;
	src.m_left  = 0.0f;
	src.m_right =32.0f;
	src.m_bottom=32.0f;

	dst.m_top   = 0.0f;
	dst.m_left  = 0.0f;
	dst.m_right =32.0f;
	dst.m_bottom=32.0f;
}