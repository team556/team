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
	for (int i = 0; i < 5; i++)
	{
		if (i == 0)
		{
			click_win[i] = 500;
		}
		else
		{
			click_win[i] =500+64*i;
		}
	}
	//テキストのx軸の当たり判定場所作成
	for (int i = 0; i < 13; i++)
	{
		if(i==0)
		{ 
			word_x[i] = 250;
		}
		else
		{
			word_x[i] =250 + 64*i;
		}
	}
	//テキストのy軸の当たり判定場所作成
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

	m_tex_clar = true;

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
	//一列目のY列---------------------------------------------------------
	if (word_y[0] < m_mou_y&& m_mou_y < word_y[1] && click_cut!=5)
	{
		//あ
		if (m_mou_l == true && word_x[0] < m_mou_x&&m_mou_x < word_x[1])
		{
			//クリックした判定を一回だけにするif文
			if (m_f == false)
			{
				word_w[0][0] = true;			//文字配列のフラグをtrueにする
				m_tex_discri[0] = click_cut;	//click_cutをm_tex_discriに入れて表示させる位置を決める
				click_cut++;					//クリックされたよ～ってことをカウント
				m_f = true;
			}
		}
		//い
		else if (m_mou_l == true && word_x[1] < m_mou_x&&m_mou_x < word_x[2])
		{
			//クリックした判定を一回だけにするif文
			if (m_f == false)
			{
				word_w[0][1] = true;			//文字配列のフラグをtrueにする
				m_tex_discri[1] = click_cut;	//click_cutをm_tex_discriに入れて表示させる位置を決める
				click_cut++;					//クリックされたよ～ってことをカウント
				m_f = true;
			}
		}
		//う
		else if (m_mou_l == true && word_x[2] < m_mou_x&&m_mou_x < word_x[3])
		{
			//クリックした判定を一回だけにするif文
			if (m_f == false)
			{
				word_w[0][2] = true;			//文字配列のフラグをtrueにする
				m_tex_discri[2] = click_cut;	//click_cutをm_tex_discriに入れて表示させる位置を決める
				click_cut++;					//クリックされたよ～ってことをカウント
				m_f = true;
			}
		}
		//え
		else if (m_mou_l == true && word_x[3] < m_mou_x&&m_mou_x < word_x[4])
		{
			//クリックした判定を一回だけにするif文
			if (m_f == false)
			{
				word_w[0][3] = true;			//文字配列のフラグをtrueにする
				m_tex_discri[3] = click_cut;	//click_cutをm_tex_discriに入れて表示させる位置を決める
				click_cut++;					//クリックされたよ～ってことをカウント
				m_f = true;
			}
		}
		//お
		else if (m_mou_l == true && word_x[4] < m_mou_x&&m_mou_x < word_x[5])
		{
			//クリックした判定を一回だけにするif文
			if (m_f == false)
			{
				word_w[0][4] = true;			//文字配列のフラグをtrueにする
				m_tex_discri[4] = click_cut;	//click_cutをm_tex_discriに入れて表示させる位置を決める
				click_cut++;					//クリックされたよ～ってことをカウント
				m_f = true;
			}
		}
		//は
		else if (m_mou_l == true && word_x[6] < m_mou_x&&m_mou_x < word_x[7])
		{
			//クリックした判定を一回だけにするif文
			if (m_f == false)
			{
				word_w[0][6] = true;			//文字配列のフラグをtrueにする
				m_tex_discri[6] = click_cut;	//click_cutをm_tex_discriに入れて表示させる位置を決める
				click_cut++;					//クリックされたよ～ってことをカウント
				m_f = true;
			}
		}
		//ひ
		else if (m_mou_l == true && word_x[7] < m_mou_x&&m_mou_x < word_x[8])
		{
			//クリックした判定を一回だけにするif文
			if (m_f == false)
			{
				word_w[0][7] = true;			//文字配列のフラグをtrueにする
				m_tex_discri[7] = click_cut;	//click_cutをm_tex_discriに入れて表示させる位置を決める
				click_cut++;					//クリックされたよ～ってことをカウント
				m_f = true;
			}
		}
		//ふ
		else if (m_mou_l == true && word_x[8] < m_mou_x&&m_mou_x < word_x[9])
		{
			//クリックした判定を一回だけにするif文
			if (m_f == false)
			{
				word_w[0][8] = true;			//文字配列のフラグをtrueにする
				m_tex_discri[8] = click_cut;	//click_cutをm_tex_discriに入れて表示させる位置を決める
				click_cut++;					//クリックされたよ～ってことをカウント
				m_f = true;
			}
		}
		//へ
		else if (m_mou_l == true && word_x[9] < m_mou_x&&m_mou_x < word_x[10])
		{
			//クリックした判定を一回だけにするif文
			if (m_f == false)
			{
				word_w[0][9] = true;			//文字配列のフラグをtrueにする
				m_tex_discri[9] = click_cut;	//click_cutをm_tex_discriに入れて表示させる位置を決める
				click_cut++;					//クリックされたよ～ってことをカウント
				m_f = true;
			}
		}
		//ほ
		else if (m_mou_l == true && word_x[10] < m_mou_x&&m_mou_x < word_x[11])
		{
			//クリックした判定を一回だけにするif文
			if (m_f == false)
			{
				word_w[0][10] = true;			//文字配列のフラグをtrueにする
				m_tex_discri[10] = click_cut;	//click_cutをm_tex_discriに入れて表示させる位置を決める
				click_cut++;					//クリックされたよ～ってことをカウント
				m_f = true;
			}
		}
		else
		{
			m_f = false;
		}
	}

	if (m_mou_x > 10 && m_mou_x < 120 && 250 < m_mou_y && 300 > m_mou_y)
	{
		m_tex_clar = false;
	}


}
//ドロー
void CObjNameInput::Draw()
{
	//文字の色(白)
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//切り取り位置
	RECT_F dst;//表示位置

	FontDraw(L"文字クリア", 10.0f, 250.0, 30.0f, 30.0f, c, false);

	if(m_tex_clar==true)
	{ 
		//↓クリックされた時の描画----------------------------------
		if (word_w[0][0] == true)
		{
			FontDraw(L"あ", click_win[m_tex_discri[0]], 100.0, 50.0f, 50.0f, c, true);
		}
		if (word_w[0][1] == true)
		{
			FontDraw(L"い", click_win[m_tex_discri[1]], 100.0, 50.0f, 50.0f, c, true);
		}
		if (word_w[0][2] == true)
		{
			FontDraw(L"う", click_win[m_tex_discri[2]], 100.0, 50.0f, 50.0f, c, true);
		}
		if (word_w[0][3] == true)
		{
			FontDraw(L"え", click_win[m_tex_discri[3]], 100.0, 50.0f, 50.0f, c, true);
		}
		if (word_w[0][4] == true)
		{
			FontDraw(L"お", click_win[m_tex_discri[4]], 100.0, 50.0f, 50.0f, c, true);
		}
		if (word_w[0][6] == true)
		{
			FontDraw(L"は", click_win[m_tex_discri[6]], 100.0, 50.0f, 50.0f, c, true);
		}
		if (word_w[0][7] == true)
		{
			FontDraw(L"ひ", click_win[m_tex_discri[7]], 100.0, 50.0f, 50.0f, c, true);
		}
		if (word_w[0][8] == true)
		{
			FontDraw(L"ふ", click_win[m_tex_discri[8]], 100.0, 50.0f, 50.0f, c, true);
		}
		if (word_w[0][9] == true)
		{
			FontDraw(L"へ", click_win[m_tex_discri[9]], 100.0, 50.0f, 50.0f, c, true);
		}
		if (word_w[0][10] == true)
		{
			FontDraw(L"ほ", click_win[m_tex_discri[10]], 100.0, 50.0f, 50.0f, c, true);
		}
	}
	else if(m_tex_clar == false)
	{
		for (int i = 0;i < 50;i++)
		{
			for (int j = 0;j < 50;j++)
			{
				word_w[i][j] = false;
			}
		}
		click_cut=0;
		m_tex_clar = true;
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
