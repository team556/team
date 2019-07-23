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
	m_f = true;
	//クリックされた時の場所
	for (int i = 0; i < 4; i++)
	{
		if (i == 0)
		{
			click_win[i] = 250;
		}
		else
		{
			click_win[i] = 250 + 63 * i;
		}
	}

	for (int i = 0; i < 13; i++)
	{
		if(i==0)
		{ 
			word_x[i] = 250;
		}
		else
		{
			word_x[i] =250 + 63*i;
		}
	}
	//for (int j = 0; j < 9; j++)
	//{
	//	if (j % 2== 0)
	//	{
	//		word_x[j] = 300+30;
	//	}
	//	else
	//	{
	//		word_x[j] = 250 + 50 * j;
	//	}
	//}
	for (int i = 0; i < 9; i++)
	{
			switch (i)
			{
			case 0:
				word_y[i] = 245;
				break;
			case 1:
				word_y[i] = 300;
				break;
			case 2:
				word_y[i] = 330;
				break;
			case 3:
				word_y[i] = 385;
				break;
			case 4:
				word_y[i] = 415;
				break;
			case 5:
				word_y[i] = 470;
				break;
			case 6:
				word_y[i] = 500;
				break;
			case 7:
				word_y[i] = 555;
				break;
			case 8:
				word_y[i] = 585;
				break;
			default:
				break;
				
			}
		
	}
	click_cut=0;

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

	/*if()*/
	word_x[50];
	word[100][100];
	word_y[100];

	//名前入力の処理
	if (word_y[0] < m_mou_y&& m_mou_y < word_y[1])
	{
		//あ
		if (m_mou_l == true && word_x[0] < m_mou_x&&m_mou_x < word_x[1])
		{
			if (m_f == false)
			{
				word_w[0][0] = true;
				click_cut++;
				m_f = true;
			}
		}
		else
			m_f = false;
		//い
		if (m_mou_l == true && word_x[1] < m_mou_x&&m_mou_x < word_x[2])
		{
			word_w[0][1] = true;
			click_cut++;
		}
	}



	////テスト条件が入ったら育成画面に飛ぶようにした
	//if (m_mou_x > 500 && m_mou_l == true)
	//{
	//	Scene::SetScene(new CSceneHome());//育成画面へシーン移行
	//}

	//if ((m_mou_x > 337 && m_mou_x<357)&&m_mou_l==true)
	//{
	//	Scene::SetScene(new CSceneHome());//育成画面へシーン移行
	//}




}
//ドロー
void CObjNameInput::Draw()
{
	//文字の色(白)
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//切り取り位置
	RECT_F dst;//表示位置

	/*FontDraw(L"と", 0.0f, 250.0, 30.0f, 30.0f, c, false);*/

	//↓クリックされた時の描画----------------------------------
	if (word_w[0][0] == true)
	{
		FontDraw(L"あ", click_win[click_cut], 100.0, 30.0f, 30.0f, c, false);
	}
	if (word_w[0][1] == true)
	{
		FontDraw(L"い", click_win[click_cut], 100.0, 30.0f, 30.0f, c, false);
	}
	//-----------------------------------------------------------

	//名前を入力してもらう画像の適用
	src.m_top = 0.0f;

	src.m_left = 0.0f;
	src.m_right =1056.0f;
	src.m_bottom = 649.0f;

	dst.m_top = 250.0f;
	dst.m_left = 250.0f;
	dst.m_right = 950.0f;
	dst.m_bottom = 650.0f;
	Draw::Draw(1, &src, &dst, c, 0.0f);

	//デバッグ用仮マウス位置表示
	wchar_t test_mou[256];
	swprintf_s(test_mou, L"x=%f,y=%f", m_mou_x, m_mou_y);
	Font::StrDraw(test_mou, 20.0f, 20.0f, 12.0f, c);
}
