//使用するヘッダーファイル
//#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"

//使用するネームスペース
using namespace GameL;

//マクロ
#define HELP_X_POS (1120.0f) //ヘルプボタンのX位置
#define HELP_Y_POS (30.0f)	 //ヘルプボタンのY位置
#define INI_COLOR (0.9f) //全カラー明度の初期値(アイコン未選択中のカラー)

//イニシャライズ
void CObjHelp::Init()
{
	m_mou_x = 0.0f;
	m_mou_y = 0.0f;
	m_mou_r = false;
	m_mou_l = false;
	m_key_f = false;

	m_Help_Button_color = INI_COLOR;
	m_Back_Button_color = INI_COLOR;

	m_help_f = false;
	m_page_num = 0;









	//現在のシーンで画像の登録番号、ヘルプ画像(ページ)の最大数を決める
	if (m_Scene_num == 1)//ホーム	1											
	{
		m_page_max = 1;
		m_Img_num = 3;
	}
	else if (m_Scene_num == 2)//育成	2
	{
		m_page_max = 1;
		m_Img_num = 46;

		if (60 < m_mou_x && m_mou_x < 325 && 505 < m_mou_y && m_mou_y < 637)
		{
			if (1110 < m_mou_x && m_mou_x < 1160 &&
				30 < m_mou_y && m_mou_y < 80)
			{
				m_Img_num = 11;
			}
		}

	}
	else  //(m_Scene_num == 3)//準備	3
	{
		m_page_max = 1;
		m_Img_num = 20;
	}

	//コンストラクタで値を代入している為、以下の処理は不要
	//CObjHome* Hom = (CObjHome*)Objs::GetObj(OBJ_HOME);				//各シーン情報を取得  //ホーム	1
	//CObjTraining* Tra = (CObjTraining*)Objs::GetObj(OBJ_TRAINING);						  //育成	2
	//CObjPreparation* Pre = (CObjPreparation*)Objs::GetObj(OBJ_PREPARATION);				  //準備	3
	//CObjFight* Fig = (CObjFight*)Objs::GetObj(OBJ_FIGHT);									  //戦闘	4
}

//アクション
void CObjHelp::Action()
{
	//マウスの位置を取得
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//マウスのボタンの状態
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	//▼キーフラグ
	//※左クリックPush状態→左クリック未Push状態になるまで、
	//再度左クリックする事は出来ない処理。
	if (m_mou_l == false)	//左クリックOFF
	{
		m_key_f = false;	//キーフラグOFF
	}

	//▼ヘルプ非表示時の処理
	if (m_help_f == false)						
	{											//常に未選択カラー
		m_Help_Button_color = INI_COLOR;						//範囲条件
		if (1110 < m_mou_x && m_mou_x < 1160 && 30 < m_mou_y && m_mou_y < 80)
		{										
			if (m_mou_l == true && m_key_f == false)//マウス左クリック
			{
				m_help_f = true;//ヘルプ表示する
				m_key_f = true;	//連打制御(キーフラグON)

				//選択音
				Audio::Start(1);
			}
			else
			{
				m_Help_Button_color = 1.0f;
			}
		}
	}
	//▼ヘルプ表示時の処理
	else										
	{
		if (m_mou_l == true && m_key_f == false)//マウス左クリック
		{
			m_page_num++;		//ページ数を進める
			m_key_f = true;		//連打制御(キーフラグON)
		}
		if (30 < m_mou_x && m_mou_x < 80 && 30 < m_mou_y && m_mou_y < 80)
		{
			m_Back_Button_color = 1.0f;
			if (m_mou_l == true)
			{
				m_help_f = false;

				//戻るボタン音
				Audio::Start(2);
			}
		}
		else
		{
			m_Back_Button_color = INI_COLOR;
		}
	}
}

//ドロー
void CObjHelp::Draw()
{
	//描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	float d[4] = { 1.0f,1.0f,1.0f,1.0f };

	float d2[4] = { 1.0f,1.0f,1.0f,m_Help_Button_color };

	RECT_F src;//切り取り位置
	RECT_F dst;//表示位置
	

	//▼ヘルプボタン表示
	src.m_top   =  0.0f;
	src.m_left  =  0.0f;
	src.m_right =128.0f;
	src.m_bottom=128.0f;
	
	dst.m_top   = HELP_Y_POS;
	dst.m_left  = HELP_X_POS;
	dst.m_right = HELP_X_POS + 50.0f;
	dst.m_bottom= HELP_Y_POS + 50.0f;

	//m_Img_numに登録したグラフィックをsrc,dst,c情報をもとに描画
	Draw::Draw(m_Img_num, &src, &dst, d2, 0.0f);


	if (m_help_f == true)
	{
		//一旦コメントアウト中
		//if(m_Scene_num == 1)				//ホーム画面でのヘルプ
		//{
		if(1)
		{
			src.m_top   = 150.0f;
			src.m_left  =   0.0f;
			src.m_right =1280.0f;
			src.m_bottom= 870.0f;
			
			dst.m_top   =  20.0f;
			dst.m_left  =  20.0f;
			dst.m_right =1180.0f;
			dst.m_bottom= 680.0f;

			//ページが最端までいくと、ループさせる(2ページが最大の場合、2→0,0→2にいけるように)
			if (m_page_num < 0 || m_page_max <= m_page_num)
			{
				//内部処理はまだ作ってない。

				m_help_f = false;//初期値に戻す
				m_page_num = 0;
			}

			if(m_page_num == 0)
			{
				//0番目に登録したグラフィックをsrc,dst,c情報をもとに描画
				Draw::Draw(m_Img_num + 2, &src, &dst, d, 0.0f);
			}
			
			float d3[4] = { 1.0f,1.0f,1.0f, m_Back_Button_color };

			src.m_top   =  0.0f;
			src.m_left  =  0.0f;
			src.m_right = 64.0f;
			src.m_bottom= 64.0f;
	
			dst.m_top   = 30.0f;
			dst.m_left  = 30.0f;
			dst.m_right = 80.0f;
			dst.m_bottom= 80.0f;

			//0番目に登録したグラフィックをsrc,dst,c情報をもとに描画
			Draw::Draw(m_Img_num + 1, &src, &dst, d3, 0.0f);			//戻るボタンの表示
		}
		else
		{
			m_help_f = false;//初期値に戻す
			m_page_num = 0;
		}
	}

}
