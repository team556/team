//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"

#include "GameHead.h"
#include "ObjBuild.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjBuild::Init()
{

}

//アクション
void CObjBuild::Action()
{

}

//ドロー
void CObjBuild::Draw()
{
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	RECT_F src;
	RECT_F dst;

	//切り取り
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 100.0f;
	src.m_bottom = 100.0f;

	//描画
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 50.0f;
	dst.m_bottom = 50.0f;

	//2番目に登録したグラフィックをsrc,dst,c情報をもとに描画
	Draw::Draw(2, &src, &dst, c, 0.0f);

}