//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"
#include "ObjTest.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjTest::Init()
{
	
}

//アクション
void CObjTest::Action()
{
	
}

//ドロー
void CObjTest::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	Font::StrDraw(L"", 230, 250, 32, c);

	Font::StrDraw(L"", 200, 400, 32, c);
}
