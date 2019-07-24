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
	m_cut = 0;
	m_finalcheck_f = false;
	m_key_f = false;
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
	for (int i = 0; i < 5; i++)
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
					m_f = true;
					m_cut++;
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
					m_f = true;
					m_cut++;
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
	if (m_mou_l == true && m_mou_x > 410 && m_mou_x < 510 && 410 < m_mou_y && 460 > m_mou_y && m_finalcheck_f == true)
	{
		Scene::SetScene(new CSceneTraining());//育成画面へシーン移行 
	}
	if (m_mou_l == true && m_mou_x > 650 && m_mou_x < 800 && 410 < m_mou_y && 460 > m_mou_y&&m_finalcheck_f == true)
	{
		m_finalcheck_f = false;
		m_key_f = false;
	}
	else
	{

	}


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
				FontDraw(str[m_tex_discri[i]], 300+(i * 50), 100.0, 50.0f, 50.0f, c, true);
			}
		}

	}
	else if(m_tex_clar == false)
	{
		for (int i = 0;i < 5;i++)
		{
			m_tex_discri[i]=99;
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
	//src.m_top = 0.0f;
	//src.m_left = 0.0f;
	//src.m_right = 242.0f;
	//src.m_bottom = 117.0f;

	//dst.m_top = 250.0f;
	//dst.m_left = 250.0f;
	//dst.m_right = 950.0f;
	//dst.m_bottom = 650.0f;
	//Draw::Draw(4, &src, &dst, c, 0.0f);

	if (m_finalcheck_f == true)
	{
		//▼最終確認ウインドウ表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1200.0f;
		src.m_bottom = 700.0f;

		dst.m_top = 220.0f;
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
	}

	//デバッグ用仮マウス位置表示
	wchar_t test_mou[256];
	swprintf_s(test_mou, L"x=%f,y=%f", m_mou_x, m_mou_y);
	Font::StrDraw(test_mou, 20.0f, 20.0f, 12.0f, c);
}
