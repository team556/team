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

wchar_t g_Player_Name[6];

//イニシャライズ
void CObjNameInput::Init()
{
	m_mou_x = 0.0f;	//マウスX座標
	m_mou_y = 0.0f; //マウスY座標
	m_mou_r = false;//右クリック
	m_mou_l = false;//左クリック
	m_f = true;
	m_cut = 0;
	m_finalcheck_f = false;
	m_key_f = false;
	m_Yes_Button_color=0;
	m_No_Button_color =0;
	m_num_cnt = 0;
	m_c_cut = 0;
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
		m_c[i] = '?';
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
	for (int i = 0; i < 10; i++)
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
		case 9:
			word_y[i] = 630;
			break;
		default:
			break;

		}

	}
	click_cut=0;

	m_tex_clar = true;
	for (int i = 0; i < 6; i++)
	{
		m_tex_discri[i] = 99;
		
	}
	for (int i = 0; i < 50; i++)
	{
		word_w[i]=i;
	}

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

	if (m_key_f == false)
	{
		//名前入力の処理
		//一列目のY列---------------------------------------------------------
		if (word_y[0] < m_mou_y&& m_mou_y < word_y[1] && click_cut != 5)
		{
			//あ
			if (m_mou_l == true && word_x[0] < m_mou_x&&m_mou_x < word_x[1])
			{
				//クリックした判定を一回だけにするif文
				if (m_f == false)
				{
					//m_tex_discri配列にword_wの値を代入する
					//m_tex_discriにclick_cutの値を代入することによって描画する際に横にずらすことができる
					m_tex_discri[click_cut] = word_w[0];	//click_cutをm_tex_discriに入れて表示させる位置を決める
					click_cut++;					//クリックされたよ～ってことをカウント
					m_c[m_cut] = L'あ';
					m_cut++;
					m_f = true;
				}
			}
			//い
			else if (m_mou_l == true && word_x[1] < m_mou_x&&m_mou_x < word_x[2])
			{
				//クリックした判定を一回だけにするif文
				if (m_f == false)
				{
					//m_tex_discri配列にword_wの値を代入する
					//m_tex_discriにclick_cutの値を代入することによって描画する際に横にずらすことができる
					m_tex_discri[click_cut] = word_w[1];	//click_cutをm_tex_discriに入れて表示させる位置を決める
					click_cut++;					//クリックされたよ～ってことをカウント
					m_c[m_cut] = L'い';
					m_cut++;
					m_f = true;
				}
			}
			//う
			else if (m_mou_l == true && word_x[2] < m_mou_x&&m_mou_x < word_x[3])
			{
				//クリックした判定を一回だけにするif文
				if (m_f == false)
				{
					//m_tex_discri配列にword_wの値を代入する
					//m_tex_discriにclick_cutの値を代入することによって描画する際に横にずらすことができる
					m_tex_discri[click_cut] = word_w[2];	//click_cutをm_tex_discriに入れて表示させる位置を決める
					click_cut++;					//クリックされたよ～ってことをカウント
					m_c[m_cut] = L'う';
					m_f = true;
					m_cut++;
				}
			}
			//え
			else if (m_mou_l == true && word_x[3] < m_mou_x&&m_mou_x < word_x[4])
			{
				//クリックした判定を一回だけにするif文
				if (m_f == false)
				{
					//m_tex_discri配列にword_wの値を代入する
					//m_tex_discriにclick_cutの値を代入することによって描画する際に横にずらすことができる
					m_tex_discri[click_cut] = word_w[3];	//click_cutをm_tex_discriに入れて表示させる位置を決める
					click_cut++;					//クリックされたよ～ってことをカウント
					m_c[m_cut] = L'え';
					m_f = true;
					m_cut++;
				}
			}
			//お
			else if (m_mou_l == true && word_x[4] < m_mou_x&&m_mou_x < word_x[5])
			{
				//クリックした判定を一回だけにするif文
				if (m_f == false)
				{
					//m_tex_discri配列にword_wの値を代入する
					//m_tex_discriにclick_cutの値を代入することによって描画する際に横にずらすことができる
					m_tex_discri[click_cut] = word_w[4];	//click_cutをm_tex_discriに入れて表示させる位置を決める
					click_cut++;					//クリックされたよ～ってことをカウント
					m_c[m_cut] = L'お';
					m_f = true;
					m_cut++;
				}
			}
			//は
			else if (m_mou_l == true && word_x[6] < m_mou_x&&m_mou_x < word_x[7])
			{
				//クリックした判定を一回だけにするif文
				if (m_f == false)
				{
					//m_tex_discri配列にword_wの値を代入する
					//m_tex_discriにclick_cutの値を代入することによって描画する際に横にずらすことができる
					m_tex_discri[click_cut] = word_w[5];	//click_cutをm_tex_discriに入れて表示させる位置を決める
					click_cut++;					//クリックされたよ～ってことをカウント
					m_c[m_cut] = L'は';
					m_f = true;
					m_cut++;
				}
			}
			//ひ
			else if (m_mou_l == true && word_x[7] < m_mou_x&&m_mou_x < word_x[8])
			{
				//クリックした判定を一回だけにするif文
				if (m_f == false)
				{
					//m_tex_discri配列にword_wの値を代入する
					//m_tex_discriにclick_cutの値を代入することによって描画する際に横にずらすことができる
					m_tex_discri[click_cut] = word_w[6];	//click_cutをm_tex_discriに入れて表示させる位置を決める
					click_cut++;					//クリックされたよ～ってことをカウント
					m_c[m_cut] = L'ひ';
					m_f = true;
					m_cut++;
				}
			}
			//ふ
			else if (m_mou_l == true && word_x[8] < m_mou_x&&m_mou_x < word_x[9])
			{
				//クリックした判定を一回だけにするif文
				if (m_f == false)
				{
					//m_tex_discri配列にword_wの値を代入する
					//m_tex_discriにclick_cutの値を代入することによって描画する際に横にずらすことができる
					m_tex_discri[click_cut] = word_w[7];	//click_cutをm_tex_discriに入れて表示させる位置を決める
					click_cut++;					//クリックされたよ～ってことをカウント
					m_c[m_cut] = L'ふ';
					m_f = true;
					m_cut++;
				}
			}
			//へ
			else if (m_mou_l == true && word_x[9] < m_mou_x&&m_mou_x < word_x[10])
			{
				//クリックした判定を一回だけにするif文
				if (m_f == false)
				{
					//m_tex_discri配列にword_wの値を代入する
					//m_tex_discriにclick_cutの値を代入することによって描画する際に横にずらすことができる
					m_tex_discri[click_cut] = word_w[8];	//click_cutをm_tex_discriに入れて表示させる位置を決める
					click_cut++;					//クリックされたよ～ってことをカウント
					m_c[m_cut] = L'へ';
					m_f = true;
					m_cut++;
				}
			}
			//ほ
			else if (m_mou_l == true && word_x[10] < m_mou_x&&m_mou_x < word_x[11])
			{
				//クリックした判定を一回だけにするif文
				if (m_f == false)
				{
					//m_tex_discri配列にword_wの値を代入する
					//m_tex_discriにclick_cutの値を代入することによって描画する際に横にずらすことができる
					m_tex_discri[click_cut] = word_w[9];	//click_cutをm_tex_discriに入れて表示させる位置を決める
					click_cut++;					//クリックされたよ～ってことをカウント
					m_c[m_cut] = L'ほ';
					m_f = true;
					m_cut++;
				}
			}
			else
			{
				m_f = false;
			}
		}
		//2列目のy軸の判定
		else if (word_y[2] < m_mou_y&& m_mou_y < word_y[3] && click_cut != 5)
		{
			//か
			if (m_mou_l == true && word_x[0] < m_mou_x&&m_mou_x < word_x[1])
			{
				//クリックした判定を一回だけにするif文
				if (m_f == false)
				{
					//m_tex_discri配列にword_wの値を代入する
					//m_tex_discriにclick_cutの値を代入することによって描画する際に横にずらすことができる
					m_tex_discri[click_cut] = word_w[10];	//click_cutをm_tex_discriに入れて表示させる位置を決める
					click_cut++;					//クリックされたよ～ってことをカウント
					m_c[m_cut] = L'か';
					m_f = true;
					m_cut++;
				}
			}
			//き
			else if (m_mou_l == true && word_x[1] < m_mou_x&&m_mou_x < word_x[2])
			{
				//クリックした判定を一回だけにするif文
				if (m_f == false)
				{
					//m_tex_discri配列にword_wの値を代入する
					//m_tex_discriにclick_cutの値を代入することによって描画する際に横にずらすことができる
					m_tex_discri[click_cut] = word_w[11];	//click_cutをm_tex_discriに入れて表示させる位置を決める
					click_cut++;					//クリックされたよ～ってことをカウント
					m_c[m_cut] = L'き';
					m_f = true;
					m_cut++;
				}
			}
			//く
			else if (m_mou_l == true && word_x[2] < m_mou_x&&m_mou_x < word_x[3])
			{
				//クリックした判定を一回だけにするif文
				if (m_f == false)
				{
					//m_tex_discri配列にword_wの値を代入する
					//m_tex_discriにclick_cutの値を代入することによって描画する際に横にずらすことができる
					m_tex_discri[click_cut] = word_w[12];	//click_cutをm_tex_discriに入れて表示させる位置を決める
					click_cut++;					//クリックされたよ～ってことをカウント
					m_c[m_cut] = L'く';
					m_f = true;
					m_cut++;
				}
			}
			//け
			else if (m_mou_l == true && word_x[3] < m_mou_x&&m_mou_x < word_x[4])
			{
				//クリックした判定を一回だけにするif文
				if (m_f == false)
				{
					//m_tex_discri配列にword_wの値を代入する
					//m_tex_discriにclick_cutの値を代入することによって描画する際に横にずらすことができる
					m_tex_discri[click_cut] = word_w[13];	//click_cutをm_tex_discriに入れて表示させる位置を決める
					click_cut++;					//クリックされたよ～ってことをカウント
					m_c[m_cut] = L'け';
					m_f = true;
					m_cut++;
				}
			}
			//こ
			else if (m_mou_l == true && word_x[4] < m_mou_x&&m_mou_x < word_x[5])
			{
				//クリックした判定を一回だけにするif文
				if (m_f == false)
				{
					//m_tex_discri配列にword_wの値を代入する
					//m_tex_discriにclick_cutの値を代入することによって描画する際に横にずらすことができる
					m_tex_discri[click_cut] = word_w[14];	//click_cutをm_tex_discriに入れて表示させる位置を決める
					click_cut++;					//クリックされたよ～ってことをカウント
					m_c[m_cut] = L'こ';
					m_f = true;
					m_cut++;
				}
			}
			//ま
			else if (m_mou_l == true && word_x[6] < m_mou_x&&m_mou_x < word_x[7])
			{
				//クリックした判定を一回だけにするif文
				if (m_f == false)
				{
					//m_tex_discri配列にword_wの値を代入する
					//m_tex_discriにclick_cutの値を代入することによって描画する際に横にずらすことができる
					m_tex_discri[click_cut] = word_w[15];	//click_cutをm_tex_discriに入れて表示させる位置を決める
					click_cut++;					//クリックされたよ～ってことをカウント
					m_c[m_cut] = L'ま';
					m_f = true;
					m_cut++;
				}
			}
			//み
			else if (m_mou_l == true && word_x[7] < m_mou_x&&m_mou_x < word_x[8])
			{
				//クリックした判定を一回だけにするif文
				if (m_f == false)
				{
					//m_tex_discri配列にword_wの値を代入する
					//m_tex_discriにclick_cutの値を代入することによって描画する際に横にずらすことができる
					m_tex_discri[click_cut] = word_w[16];	//click_cutをm_tex_discriに入れて表示させる位置を決める
					click_cut++;					//クリックされたよ～ってことをカウント
					m_c[m_cut] = L'み';
					m_f = true;
					m_cut++;
				}
			}
			//む
			else if (m_mou_l == true && word_x[8] < m_mou_x&&m_mou_x < word_x[9])
			{
				//クリックした判定を一回だけにするif文
				if (m_f == false)
				{
					//m_tex_discri配列にword_wの値を代入する
					//m_tex_discriにclick_cutの値を代入することによって描画する際に横にずらすことができる
					m_tex_discri[click_cut] = word_w[17];	//click_cutをm_tex_discriに入れて表示させる位置を決める
					click_cut++;					//クリックされたよ～ってことをカウント
					m_c[m_cut] = L'む';
					m_f = true;
					m_cut++;
				}
			}
			//め
			else if (m_mou_l == true && word_x[9] < m_mou_x&&m_mou_x < word_x[10])
			{
				//クリックした判定を一回だけにするif文
				if (m_f == false)
				{
					//m_tex_discri配列にword_wの値を代入する
					//m_tex_discriにclick_cutの値を代入することによって描画する際に横にずらすことができる
					m_tex_discri[click_cut] = word_w[18];	//click_cutをm_tex_discriに入れて表示させる位置を決める
					click_cut++;					//クリックされたよ～ってことをカウント
					m_c[m_cut] = L'め';
					m_f = true;
					m_cut++;
				}
			}
			//も
			else if (m_mou_l == true && word_x[10] < m_mou_x&&m_mou_x < word_x[11])
			{
				//クリックした判定を一回だけにするif文
				if (m_f == false)
				{
					//m_tex_discri配列にword_wの値を代入する
					//m_tex_discriにclick_cutの値を代入することによって描画する際に横にずらすことができる
					m_tex_discri[click_cut] = word_w[19];	//click_cutをm_tex_discriに入れて表示させる位置を決める
					click_cut++;					//クリックされたよ～ってことをカウント
					m_c[m_cut] = L'も';
					m_f = true;
					m_cut++;
				}
			}
			else
			{
				m_f = false;
			}
		}
		//3列目のy軸の判定
		else if (word_y[4] < m_mou_y&& m_mou_y < word_y[5] && click_cut != 5)
		{
			//さ
			if (m_mou_l == true && word_x[0] < m_mou_x&&m_mou_x < word_x[1])
			{
				//クリックした判定を一回だけにするif文
				if (m_f == false)
				{
					//m_tex_discri配列にword_wの値を代入する
					//m_tex_discriにclick_cutの値を代入することによって描画する際に横にずらすことができる
					m_tex_discri[click_cut] = word_w[20];	//click_cutをm_tex_discriに入れて表示させる位置を決める
					click_cut++;					//クリックされたよ～ってことをカウント
					m_c[m_cut] = L'さ';
					m_f = true;
					m_cut++;
				}
			}
			//し
			else if (m_mou_l == true && word_x[1] < m_mou_x&&m_mou_x < word_x[2])
			{
				//クリックした判定を一回だけにするif文
				if (m_f == false)
				{
					//m_tex_discri配列にword_wの値を代入する
					//m_tex_discriにclick_cutの値を代入することによって描画する際に横にずらすことができる
					m_tex_discri[click_cut] = word_w[21];	//click_cutをm_tex_discriに入れて表示させる位置を決める
					click_cut++;					//クリックされたよ～ってことをカウント
					m_c[m_cut] = L'し';
					m_f = true;
					m_cut++;
				}
			}
			//す
			else if (m_mou_l == true && word_x[2] < m_mou_x&&m_mou_x < word_x[3])
			{
				//クリックした判定を一回だけにするif文
				if (m_f == false)
				{
					//m_tex_discri配列にword_wの値を代入する
					//m_tex_discriにclick_cutの値を代入することによって描画する際に横にずらすことができる
					m_tex_discri[click_cut] = word_w[22];	//click_cutをm_tex_discriに入れて表示させる位置を決める
					click_cut++;					//クリックされたよ～ってことをカウント
					m_c[m_cut] = L'す';
					m_f = true;
					m_cut++;
				}
			}
			//せ
			else if (m_mou_l == true && word_x[3] < m_mou_x&&m_mou_x < word_x[4])
			{
				//クリックした判定を一回だけにするif文
				if (m_f == false)
				{
					//m_tex_discri配列にword_wの値を代入する
					//m_tex_discriにclick_cutの値を代入することによって描画する際に横にずらすことができる
					m_tex_discri[click_cut] = word_w[23];	//click_cutをm_tex_discriに入れて表示させる位置を決める
					click_cut++;					//クリックされたよ～ってことをカウント
					m_c[m_cut] = L'せ';
					m_f = true;
					m_cut++;
				}
			}
			//そ
			else if (m_mou_l == true && word_x[4] < m_mou_x&&m_mou_x < word_x[5])
			{
				//クリックした判定を一回だけにするif文
				if (m_f == false)
				{
					//m_tex_discri配列にword_wの値を代入する
					//m_tex_discriにclick_cutの値を代入することによって描画する際に横にずらすことができる
					m_tex_discri[click_cut] = word_w[24];	//click_cutをm_tex_discriに入れて表示させる位置を決める
					click_cut++;					//クリックされたよ～ってことをカウント
					m_c[m_cut] = L'そ';
					m_f = true;
					m_cut++;
				}
			}
			//や
			else if (m_mou_l == true && word_x[6] < m_mou_x&&m_mou_x < word_x[7])
			{
				//クリックした判定を一回だけにするif文
				if (m_f == false)
				{
					//m_tex_discri配列にword_wの値を代入する
					//m_tex_discriにclick_cutの値を代入することによって描画する際に横にずらすことができる
					m_tex_discri[click_cut] = word_w[25];	//click_cutをm_tex_discriに入れて表示させる位置を決める
					click_cut++;					//クリックされたよ～ってことをカウント
					m_c[m_cut] = L'や';
					m_f = true;
					m_cut++;
				}
			}
			//ゆ
			else if (m_mou_l == true && word_x[8] < m_mou_x&&m_mou_x < word_x[9])
			{
				//クリックした判定を一回だけにするif文
				if (m_f == false)
				{
					//m_tex_discri配列にword_wの値を代入する
					//m_tex_discriにclick_cutの値を代入することによって描画する際に横にずらすことができる
					m_tex_discri[click_cut] = word_w[26];	//click_cutをm_tex_discriに入れて表示させる位置を決める
					click_cut++;					//クリックされたよ～ってことをカウント
					m_c[m_cut] = L'ゆ';
					m_f = true;
					m_cut++;
				}
			}
			//よ
			else if (m_mou_l == true && word_x[10] < m_mou_x&&m_mou_x < word_x[11])
			{
				//クリックした判定を一回だけにするif文
				if (m_f == false)
				{
					//m_tex_discri配列にword_wの値を代入する
					//m_tex_discriにclick_cutの値を代入することによって描画する際に横にずらすことができる
					m_tex_discri[click_cut] = word_w[27];	//click_cutをm_tex_discriに入れて表示させる位置を決める
					click_cut++;					//クリックされたよ～ってことをカウント
					m_c[m_cut] = L'よ';
					m_f = true;
					m_cut++;
				}
			}
			else
			{
				m_f = false;
			}
		}
		//4列目のy軸の判定
		else if (word_y[6] < m_mou_y&& m_mou_y < word_y[7] && click_cut != 5)
		{
			//た
			if (m_mou_l == true && word_x[0] < m_mou_x&&m_mou_x < word_x[1])
			{
				//クリックした判定を一回だけにするif文
				if (m_f == false)
				{
					//m_tex_discri配列にword_wの値を代入する
					//m_tex_discriにclick_cutの値を代入することによって描画する際に横にずらすことができる
					m_tex_discri[click_cut] = word_w[28];	//click_cutをm_tex_discriに入れて表示させる位置を決める
					click_cut++;					//クリックされたよ～ってことをカウント
					m_c[m_cut] = L'た';
					m_f = true;
					m_cut++;
				}
			}
			//ち
			else if (m_mou_l == true && word_x[1] < m_mou_x&&m_mou_x < word_x[2])
			{
				//クリックした判定を一回だけにするif文
				if (m_f == false)
				{
					//m_tex_discri配列にword_wの値を代入する
					//m_tex_discriにclick_cutの値を代入することによって描画する際に横にずらすことができる
					m_tex_discri[click_cut] = word_w[29];	//click_cutをm_tex_discriに入れて表示させる位置を決める
					click_cut++;					//クリックされたよ～ってことをカウント
					m_c[m_cut] = L'ち';
					m_f = true;
					m_cut++;
				}
			}
			//つ
			else if (m_mou_l == true && word_x[2] < m_mou_x&&m_mou_x < word_x[3])
			{
				//クリックした判定を一回だけにするif文
				if (m_f == false)
				{
					//m_tex_discri配列にword_wの値を代入する
					//m_tex_discriにclick_cutの値を代入することによって描画する際に横にずらすことができる
					m_tex_discri[click_cut] = word_w[30];	//click_cutをm_tex_discriに入れて表示させる位置を決める
					click_cut++;					//クリックされたよ～ってことをカウント
					m_c[m_cut] = L'つ';
					m_f = true;
					m_cut++;
				}
			}
			//て
			else if (m_mou_l == true && word_x[3] < m_mou_x&&m_mou_x < word_x[4])
			{
				//クリックした判定を一回だけにするif文
				if (m_f == false)
				{
					//m_tex_discri配列にword_wの値を代入する
					//m_tex_discriにclick_cutの値を代入することによって描画する際に横にずらすことができる
					m_tex_discri[click_cut] = word_w[31];	//click_cutをm_tex_discriに入れて表示させる位置を決める
					click_cut++;					//クリックされたよ～ってことをカウント
					m_c[m_cut] = L'て';
					m_f = true;
					m_cut++;
				}
			}
			//と
			else if (m_mou_l == true && word_x[4] < m_mou_x&&m_mou_x < word_x[5])
			{
				//クリックした判定を一回だけにするif文
				if (m_f == false)
				{
					//m_tex_discri配列にword_wの値を代入する
					//m_tex_discriにclick_cutの値を代入することによって描画する際に横にずらすことができる
					m_tex_discri[click_cut] = word_w[32];	//click_cutをm_tex_discriに入れて表示させる位置を決める
					click_cut++;					//クリックされたよ～ってことをカウント
					m_c[m_cut] = L'と';
					m_f = true;
					m_cut++;
				}
			}
			//ら
			else if (m_mou_l == true && word_x[6] < m_mou_x&&m_mou_x < word_x[7])
			{
				//クリックした判定を一回だけにするif文
				if (m_f == false)
				{
					//m_tex_discri配列にword_wの値を代入する
					//m_tex_discriにclick_cutの値を代入することによって描画する際に横にずらすことができる
					m_tex_discri[click_cut] = word_w[33];	//click_cutをm_tex_discriに入れて表示させる位置を決める
					click_cut++;					//クリックされたよ～ってことをカウント
					m_c[m_cut] = L'ら';
					m_f = true;
					m_cut++;
				}
			}
			//り
			else if (m_mou_l == true && word_x[7] < m_mou_x&&m_mou_x < word_x[8])
			{
				//クリックした判定を一回だけにするif文
				if (m_f == false)
				{
					//m_tex_discri配列にword_wの値を代入する
					//m_tex_discriにclick_cutの値を代入することによって描画する際に横にずらすことができる
					m_tex_discri[click_cut] = word_w[34];	//click_cutをm_tex_discriに入れて表示させる位置を決める
					click_cut++;					//クリックされたよ～ってことをカウント
					m_c[m_cut] = L'り';
					m_f = true;
					m_cut++;
				}
			}
			//る
			else if (m_mou_l == true && word_x[8] < m_mou_x&&m_mou_x < word_x[9])
			{
				//クリックした判定を一回だけにするif文
				if (m_f == false)
				{
					//m_tex_discri配列にword_wの値を代入する
					//m_tex_discriにclick_cutの値を代入することによって描画する際に横にずらすことができる
					m_tex_discri[click_cut] = word_w[35];	//click_cutをm_tex_discriに入れて表示させる位置を決める
					click_cut++;					//クリックされたよ～ってことをカウント
					m_c[m_cut] = L'る';
					m_f = true;
					m_cut++;
				}
			}
			//れ
			else if (m_mou_l == true && word_x[9] < m_mou_x&&m_mou_x < word_x[10])
			{
				//クリックした判定を一回だけにするif文
				if (m_f == false)
				{
					//m_tex_discri配列にword_wの値を代入する
					//m_tex_discriにclick_cutの値を代入することによって描画する際に横にずらすことができる
					m_tex_discri[click_cut] = word_w[36];	//click_cutをm_tex_discriに入れて表示させる位置を決める
					click_cut++;					//クリックされたよ～ってことをカウント
					m_c[m_cut] = L'れ';
					m_f = true;
					m_cut++;
				}
			}
			//ろ
			else if (m_mou_l == true && word_x[10] < m_mou_x&&m_mou_x < word_x[11])
			{
				//クリックした判定を一回だけにするif文
				if (m_f == false)
				{
					//m_tex_discri配列にword_wの値を代入する
					//m_tex_discriにclick_cutの値を代入することによって描画する際に横にずらすことができる
					m_tex_discri[click_cut] = word_w[37];	//click_cutをm_tex_discriに入れて表示させる位置を決める
					click_cut++;					//クリックされたよ～ってことをカウント
					m_c[m_cut] = L'ろ';
					m_f = true;
					m_cut++;
				}
			}
			else
			{
				m_f = false;
			}
		}
		//5列目のy軸の判定
		else if (word_y[8] < m_mou_y&& m_mou_y < word_y[9] && click_cut != 5)
		{
			//な
			if (m_mou_l == true && word_x[0] < m_mou_x&&m_mou_x < word_x[1])
			{
				//クリックした判定を一回だけにするif文
				if (m_f == false)
				{
					//m_tex_discri配列にword_wの値を代入する
					//m_tex_discriにclick_cutの値を代入することによって描画する際に横にずらすことができる
					m_tex_discri[click_cut] = word_w[38];	//click_cutをm_tex_discriに入れて表示させる位置を決める
					click_cut++;					//クリックされたよ～ってことをカウント
					m_c[m_cut] = L'な';
					m_f = true;
					m_cut++;
				}
			}
			//に
			else if (m_mou_l == true && word_x[1] < m_mou_x&&m_mou_x < word_x[2])
			{
				//クリックした判定を一回だけにするif文
				if (m_f == false)
				{
					//m_tex_discri配列にword_wの値を代入する
					//m_tex_discriにclick_cutの値を代入することによって描画する際に横にずらすことができる
					m_tex_discri[click_cut] = word_w[39];	//click_cutをm_tex_discriに入れて表示させる位置を決める
					click_cut++;					//クリックされたよ～ってことをカウント
					m_c[m_cut] = L'に';
					m_f = true;
					m_cut++;
				}
			}
			//ぬ
			else if (m_mou_l == true && word_x[2] < m_mou_x&&m_mou_x < word_x[3])
			{
				//クリックした判定を一回だけにするif文
				if (m_f == false)
				{
					//m_tex_discri配列にword_wの値を代入する
					//m_tex_discriにclick_cutの値を代入することによって描画する際に横にずらすことができる
					m_tex_discri[click_cut] = word_w[40];	//click_cutをm_tex_discriに入れて表示させる位置を決める
					click_cut++;					//クリックされたよ～ってことをカウント
					m_c[m_cut] = L'ぬ';
					m_f = true;
					m_cut++;
				}
			}
			//ね
			else if (m_mou_l == true && word_x[3] < m_mou_x&&m_mou_x < word_x[4])
			{
				//クリックした判定を一回だけにするif文
				if (m_f == false)
				{
					//m_tex_discri配列にword_wの値を代入する
					//m_tex_discriにclick_cutの値を代入することによって描画する際に横にずらすことができる
					m_tex_discri[click_cut] = word_w[41];	//click_cutをm_tex_discriに入れて表示させる位置を決める
					click_cut++;					//クリックされたよ～ってことをカウント
					m_c[m_cut] = L'ね';
					m_f = true;
					m_cut++;
				}
			}
			//の
			else if (m_mou_l == true && word_x[4] < m_mou_x&&m_mou_x < word_x[5])
			{
				//クリックした判定を一回だけにするif文
				if (m_f == false)
				{
					//m_tex_discri配列にword_wの値を代入する
					//m_tex_discriにclick_cutの値を代入することによって描画する際に横にずらすことができる
					m_tex_discri[click_cut] = word_w[42];	//click_cutをm_tex_discriに入れて表示させる位置を決める
					click_cut++;					//クリックされたよ～ってことをカウント
					m_c[m_cut] = L'の';
					m_f = true;
					m_cut++;
				}
			}
			//わ
			else if (m_mou_l == true && word_x[6] < m_mou_x&&m_mou_x < word_x[7])
			{
				//クリックした判定を一回だけにするif文
				if (m_f == false)
				{
					//m_tex_discri配列にword_wの値を代入する
					//m_tex_discriにclick_cutの値を代入することによって描画する際に横にずらすことができる
					m_tex_discri[click_cut] = word_w[43];	//click_cutをm_tex_discriに入れて表示させる位置を決める
					click_cut++;					//クリックされたよ～ってことをカウント
					m_c[m_cut] = L'わ';
					m_f = true;
					m_cut++;
				}
			}
			//を
			else if (m_mou_l == true && word_x[8] < m_mou_x&&m_mou_x < word_x[9])
			{
				//クリックした判定を一回だけにするif文
				if (m_f == false)
				{
					//m_tex_discri配列にword_wの値を代入する
					//m_tex_discriにclick_cutの値を代入することによって描画する際に横にずらすことができる
					m_tex_discri[click_cut] = word_w[44];	//click_cutをm_tex_discriに入れて表示させる位置を決める
					click_cut++;					//クリックされたよ～ってことをカウント
					m_c[m_cut] = L'を';
					m_f = true;
					m_cut++;
				}
			}
			//ん
			else if (m_mou_l == true && word_x[10] < m_mou_x&&m_mou_x < word_x[11])
			{
				//クリックした判定を一回だけにするif文
				if (m_f == false)
				{
					//m_tex_discri配列にword_wの値を代入する
					//m_tex_discriにclick_cutの値を代入することによって描画する際に横にずらすことができる
					m_tex_discri[click_cut] = word_w[45];	//click_cutをm_tex_discriに入れて表示させる位置を決める
					click_cut++;					//クリックされたよ～ってことをカウント
					//m_c[m_cut] = L'ん';

					char *tmp = "ん";
					memcpy(&m_c[m_cut], tmp, 2);

					m_f = true;
					m_cut++;
				}
			}
			else
			{
				m_f = false;
			}
		}
	}
	else
	{ }
	//文字クリアの判定
	if (m_mou_l == true && m_mou_x > 1000 && m_mou_x < 1150 && 300 < m_mou_y && 400 > m_mou_y)
	{
		m_tex_clar = false;
	}
	//文字決定を押したときの処理
	if (m_mou_l==true && m_mou_x > 1000 && m_mou_x < 1150 && 500 < m_mou_y && 600 > m_mou_y)
	{
		m_finalcheck_f = true;
		m_key_f = true;
	}
	//最終確認ウィンドウのはいを押したときの処理
	if (m_mou_l == true && m_mou_x > 410 && m_mou_x < 510 && 410 < m_mou_y && 460 > m_mou_y && m_finalcheck_f == true)
	{
		//この下にある文がグローバル変数に文字を入れる処理
		switch (m_cut)
		{
		case 3:
			swprintf_s(g_Player_Name, L"%c%c%c", m_c[0], m_c[1], m_c[2]);
			break;
		case 4:
			swprintf_s(g_Player_Name, L"%c%c%c%c", m_c[0], m_c[1], m_c[2], m_c[3]);
			break;
		case 5:
			swprintf_s(g_Player_Name, L"%c%c%c%c%c", m_c[0], m_c[1], m_c[2], m_c[3], m_c[4]);
			break;
		}
		Scene::SetScene(new CSceneTraining());//育成画面へシーン移行 
	}
	//最終確認ウィンドウのいいえを押したときの処理
	if (m_mou_l == true && m_mou_x > 650 && m_mou_x < 800 && 410 < m_mou_y && 460 > m_mou_y&&m_finalcheck_f == true)
	{
		m_key_f = false;
		m_finalcheck_f = false;
	}
	else;


}
//ドロー
void CObjNameInput::Draw()
{
	//文字の色(白)
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	//▽描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	//赤色
	float red[4] = { 1.0f,0.0f,0.0f,1.0f };

	//黒色
	float black[4] = { 0.0f,0.0f,0.0f,1.0f };

	//最終確認[はい]ボタン用
	float Yes[4] = { m_Yes_Button_color,0.0f,0.0f,1.0f };

	//最終確認[いいえ]ボタン用
	float No[4] = { 0.0f,0.0f,m_No_Button_color,1.0f };

	RECT_F src;//切り取り位置
	RECT_F dst;//表示位置

	if(m_tex_clar==true)
	{ 
		//↓クリックされた時の描画----------------------------------
		wchar_t str[46][2]
		{
			L"あ",L"い",L"う",L"え",L"お",L"は",L"ひ",L"ふ",L"へ",L"ほ",
			L"か",L"き",L"く",L"け",L"こ",L"ま",L"み",L"む",L"め",L"も",
			L"さ",L"し",L"す",L"せ",L"そ",L"や",L"ゆ",L"よ",
			L"た",L"ち",L"つ",L"て",L"と",L"ら",L"り",L"る",L"れ",L"ろ",
			L"な",L"に",L"ぬ",L"ね",L"の",L"わ",L"を",L"ん",
		};
		for (int i = 0; i < 5; i++)
		{
			if (m_tex_discri[i] != 99)
			{
				FontDraw(str[m_tex_discri[i]], 590+(i * 60), 100.0, 60.0f, 60.0f, c, true);
			}
			else if (m_tex_discri[i] == 99)
			{
				FontDraw(L"．", 590 + (i * 60), 100.0, 60.0f, 60.0f, c, true);
			}
		}

		m_num_cnt = 0;
	}
	else if(m_tex_clar == false)
	{
		for (int i = 0;i < 5;i++)
		{
			m_tex_discri[i]=99;
		}
		click_cut=0;
		m_tex_clar = true;
		m_cut = 0;
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

	//クリア画像の適用
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 405.0f;
	src.m_bottom = 150.0f;

	dst.m_top		= 300.0f;
	dst.m_left		= 1000.0f;
	dst.m_right		= 1150.0f;
	dst.m_bottom	= 400.0f;
	Draw::Draw(2, &src, &dst, c, 0.0f);

	//決定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 280.0f;
	src.m_bottom = 150.0f;

	dst.m_top = 500.0f;
	dst.m_left = 1000.0f;
	dst.m_right = 1150.0f;
	dst.m_bottom = 600.0f;
	Draw::Draw(3, &src, &dst, c, 0.0f);

	//惑星
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 242.0f;
	src.m_bottom = 117.0f;

	dst.m_top =102.0f;
	dst.m_left = 350.0f;
	dst.m_right = 450.0f;
	dst.m_bottom = 160.0f;
	Draw::Draw(4, &src, &dst, c, 0.0f);

	FontDraw(L"名", 450, 100.0, 60.0f, 60.0f, c, true);


	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 32.0f;
	src.m_bottom = 32.0f;

	//左縦
	dst.m_top = 80.0f;
	dst.m_left = 330.0f;
	dst.m_right = 335.0f;
	dst.m_bottom = 190.0f;
	Draw::Draw(5, &src, &dst, c, 0.0f);

	//右縦
	dst.m_top = 80.0f;
	dst.m_left = 910.0f;
	dst.m_right = 915.0f;
	dst.m_bottom = 190.0f;
	Draw::Draw(5, &src, &dst, c, 0.0f);

	//上横
	dst.m_top = 80.0f;
	dst.m_left = 330.0f;
	dst.m_right = 910.0f;
	dst.m_bottom = 85.0f;
	Draw::Draw(5, &src, &dst, c, 0.0f);

	//下横
	dst.m_top = 185.0f;
	dst.m_left = 330.0f;
	dst.m_right = 910.0f;
	dst.m_bottom = 190.0f;
	Draw::Draw(5, &src, &dst, c, 0.0f);

	if (m_finalcheck_f == true && m_cut>=3)
	{
		//↓クリックされた時の描画----------------------------------
		wchar_t str[46][2]
		{
			L"あ",L"い",L"う",L"え",L"お",L"は",L"ひ",L"ふ",L"へ",L"ほ",
			L"か",L"き",L"く",L"け",L"こ",L"ま",L"み",L"む",L"め",L"も",
			L"さ",L"し",L"す",L"せ",L"そ",L"や",L"ゆ",L"よ",
			L"た",L"ち",L"つ",L"て",L"と",L"ら",L"り",L"る",L"れ",L"ろ",
			L"な",L"に",L"ぬ",L"ね",L"の",L"わ",L"を",L"ん",
		};

		//はいといいえのボタンの上にカーソルを合わすと色が変わる
		if (m_mou_x > 650 && m_mou_x < 800&&m_mou_y>410&&m_mou_y<460)
		{
			//いいえボタンの処理
			m_No_Button_color = 1;
		}
		else if (m_mou_x > 410 && m_mou_x < 510 && m_mou_y>410 && m_mou_y < 460)
		{
			//はいボタンの処理
			m_Yes_Button_color = 1;
		}
		else
		{
			//それ以外の処理文字を黒くする
			m_No_Button_color = 0;
			m_Yes_Button_color = 0;
		}

		
		//▼最終確認ウインドウ表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1200.0f;
		src.m_bottom = 700.0f;

		dst.m_top = 200.0f;
		dst.m_left = 320.0f;
		dst.m_right = 880.0f;
		dst.m_bottom = 480.0f;
		Draw::Draw(89, &src, &dst, c, 0.0f);

		//▼はい文字画像表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 232.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 410.0f;
		dst.m_left = 410.0f;
		dst.m_right = 510.0f;
		dst.m_bottom = 460.0f;
		Draw::Draw(66, &src, &dst, Yes, 0.0f);

		//▼いいえ文字画像表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 352.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 410.0f;
		dst.m_left = 650.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 460.0f;
		Draw::Draw(67, &src, &dst, No, 0.0f);

		//プレイヤー名を描画する際の位置調整をするためのカウント
		for (int i = 0; i < 6; i++)
		{
			if (m_tex_discri[i] != 99 && m_num_cnt < 5)
				m_num_cnt++;
		}

		//最終確認ウィンドウが表示された時に入力されたプレイヤー名を描画する
		for (int i = 0; i < 5; i++)
		{
			//m_tex_discri[i]の中の値が99出なければ描画（99の理由は初期化する際に99を代入しているから）
			if (m_tex_discri[i] != 99)
			{
				FontDraw(str[m_tex_discri[i]], 600 - (m_num_cnt * 30) + (i * 60), 225.0, 60.0f, 60.0f, c, false);
			}
			if (m_c[i] == '？')
			{
				m_c_cut++;
			}
		}
		FontDraw(L"でよろしいですか？", 375, 325.0, 50.0f, 50.0f, c, false);
	}
	//決定ボタンをおした時m_cutが三以下なら警告文を出させる
	else if (m_finalcheck_f == true && m_cut < 3)
	{
		//↓クリックされた時の描画----------------------------------
		wchar_t str[46][2]
		{
			L"あ",L"い",L"う",L"え",L"お",L"は",L"ひ",L"ふ",L"へ",L"ほ",
			L"か",L"き",L"く",L"け",L"こ",L"ま",L"み",L"む",L"め",L"も",
			L"さ",L"し",L"す",L"せ",L"そ",L"や",L"ゆ",L"よ",
			L"た",L"ち",L"つ",L"て",L"と",L"ら",L"り",L"る",L"れ",L"ろ",
			L"な",L"に",L"ぬ",L"ね",L"の",L"わ",L"を",L"ん",
		};

		//▼最終確認ウインドウ表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1200.0f;
		src.m_bottom = 700.0f;

		dst.m_top = 200.0f;
		dst.m_left = 320.0f;
		dst.m_right = 880.0f;
		dst.m_bottom = 480.0f;
		Draw::Draw(89, &src, &dst, c, 0.0f);

		FontDraw(L"名前を三文字以上入力してください", 375, 325.0, 30.0f, 30.0f, c, false);
		if (m_mou_l == false)
		{
			m_f = true;
		}
		if (m_mou_l == true&&m_f==true)
		{
			m_finalcheck_f = false;
			m_f = false;
			m_key_f = false;
		}

	}
	//デバッグ用仮マウス位置表示
	wchar_t test_mou[256];
	swprintf_s(test_mou, L"x=%f,y=%f", m_mou_x, m_mou_y);
	Font::StrDraw(test_mou, 20.0f, 20.0f, 12.0f, c);
}
