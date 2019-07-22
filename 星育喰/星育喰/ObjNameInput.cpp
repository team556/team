//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjNameInput.h"
#include"UtilityModule.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjNameInput::Init()
{
	m_mou_x = 0.0f;	//マウスX座標
	m_mou_y = 0.0f; //マウスY座標
	m_mou_r = false;//右クリック
	m_mou_l = false;//左クリック

}

//アクション
void CObjNameInput::Action()
{
	//マウスの位置を取得
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//マウスのボタンの状態
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();



	//テスト条件が入ったら育成画面に飛ぶようにした
	if (m_mou_x > 500 && m_mou_l == true)
	{
		Scene::SetScene(new CSceneHome());//育成画面へシーン移行
	}

	if ((m_mou_x > 337 && m_mou_x<357)&&m_mou_l==true)
	{
		Scene::SetScene(new CSceneHome());//育成画面へシーン移行
	}



}
//ドロー
void CObjNameInput::Draw()
{
	//文字の色(白)
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//切り取り位置
	RECT_F dst;//表示位置


	//仮画像の適用
	src.m_top = 145.0f;
	src.m_left = 0.0f;
	src.m_right =1500.0f;
	src.m_bottom = 630.0f;

	dst.m_top = 200.0f;
	dst.m_left = 350.0f;
	dst.m_right = 850.0f;
	dst.m_bottom = 500.0f;
	Draw::Draw(1, &src, &dst, c, 0.0f);

	//デバッグ用仮マウス位置表示
	wchar_t test_mou[256];
	swprintf_s(test_mou, L"x=%f,y=%f", m_mou_x, m_mou_y);
	Font::StrDraw(test_mou, 20.0f, 20.0f, 12.0f, c);
}
