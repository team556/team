//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"
#include "ObjHelp.h"

//使用するネームスペース
using namespace GameL;

////コンストラクタ
//CObjTest::CObjTest(float x, float y)
//{
//	//作成時に渡された値を、座標の初期値に代入
//	m_x = x;
//	m_y = y;
//}

#define INI_COLOR (0.9f) //全カラー明度の初期値(アイコン未選択中のカラー)

//イニシャライズ
void CObjHelp::Init()
{
	m_help_f = false;
	m_page_nam = 0;
	m_Scene_nam = 0;

	m_x = 1120.0f;
	m_y =   30.0f;
	m_a = INI_COLOR;
	m_a2 = INI_COLOR;

	m_key_f = false;

	CObjHome* Hom = (CObjHome*)Objs::GetObj(OBJ_HOME);				//各シーン情報を取得	ホーム	1
	CObjTraining* Tra = (CObjTraining*)Objs::GetObj(OBJ_TRAINING);						  //育成	2
	CObjPreparation* Pre = (CObjPreparation*)Objs::GetObj(OBJ_PREPARATION);				  //準備	3
	CObjFight* Fig = (CObjFight*)Objs::GetObj(OBJ_FIGHT);								  //戦闘	4
	

	if (Hom != nullptr)												//現在のシーンで数字を決める
		m_Scene_nam = 1;
	else if (Tra != nullptr)
		m_Scene_nam = 2;
	else if (Tra != nullptr)
		m_Scene_nam = 3;
	else if (Tra != nullptr)
		m_Scene_nam = 4;
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

	if (m_help_f == false)						//ヘルプ表示してない場合
	{											//常に未選択カラー
		m_a = INI_COLOR;						//範囲条件
		if (1110 < m_mou_x && m_mou_x < 1160 && 30 < m_mou_y && m_mou_y < 80)
		{										//マウスのクリック時
			if (m_mou_l == true)
			{
				m_help_f = true;//ヘルプ表示する
				m_key_f = true;	//連打制御
			}
			else
			{
				m_a = 1.0f;
			}
		}
	}
	else										//ヘルプ表示してる場合
	{
		if (m_mou_l == true && m_key_f == false)//クリック
		{
			m_page_nam++;		//ページ数を進める
			m_key_f = true;		//キーフラグON
		}
		if (30 < m_mou_x && m_mou_x < 80 && 30 < m_mou_y && m_mou_y < 80)
		{
			m_a2 = 1.0f;
			if (m_mou_l == true)
			{
				m_help_f = false;
			}
		}
		else
		{
			m_a2 = INI_COLOR;
		}
	}

	if (m_mou_l == false)						//クリックOFF
	{
		m_key_f = false;	//キーフラグOFF
	}
}

//ドロー
void CObjHelp::Draw()
{
	/*float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	Font::StrDraw(L"", 230, 250, 32, c);*/
	
	//描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	float d2[4] = { 1.0f,1.0f, 1.0f, m_a };

	RECT_F src;//切り取り位置
	RECT_F dst;//表示位置
	
	src.m_top   =  0.0f;
	src.m_left  =  0.0f;
	src.m_right =100.0f;
	src.m_bottom=100.0f;
	
	dst.m_top   = m_y;
	dst.m_left  = m_x;
	dst.m_right = m_x + 50.0f;
	dst.m_bottom= m_y + 50.0f;

	//0番目に登録したグラフィックをsrc,dst,c情報をもとに描画
	Draw::Draw(1, &src, &dst, d2, 0.0f);

	if (m_help_f == true)
	{
		float d[4] = { 1.0f,1.0f, 1.0f, 1.0f };

		if(m_Scene_nam = 1)				//ホーム画面でのヘルプ
		{
			src.m_top   =  0.0f;
			src.m_left  =  0.0f;
			src.m_right =100.0f;
			src.m_bottom=100.0f;
			
			dst.m_top   =  20.0f;
			dst.m_left  =  20.0f;
			dst.m_right =1180.0f;
			dst.m_bottom= 680.0f;

			if(m_page_nam == 0)
			{
				//0番目に登録したグラフィックをsrc,dst,c情報をもとに描画
				Draw::Draw(1, &src, &dst, d, 0.0f);
			}
			else if(m_page_nam == 1)
			{
				//0番目に登録したグラフィックをsrc,dst,c情報をもとに描画
				Draw::Draw(1, &src, &dst, d, 0.0f);
			}
			else if(m_page_nam == 2)
			{
				//0番目に登録したグラフィックをsrc,dst,c情報をもとに描画
				Draw::Draw(1, &src, &dst, d, 0.0f);
			}
			else if(m_page_nam == 3)
			{
				//0番目に登録したグラフィックをsrc,dst,c情報をもとに描画
				Draw::Draw(1, &src, &dst, d, 0.0f);
			}
			else if(m_page_nam >= 4)
			{
				m_help_f = false;//初期値に戻す
				m_page_nam = 0;
			}
			float d3[4] = { 1.0f,1.0f,1.0f, m_a2 };

			src.m_top   =  0.0f;
			src.m_left  =  0.0f;
			src.m_right =100.0f;
			src.m_bottom=100.0f;
	
			dst.m_top   = 30.0f;
			dst.m_left  = 30.0f;
			dst.m_right = 80.0f;
			dst.m_bottom= 80.0f;

			//0番目に登録したグラフィックをsrc,dst,c情報をもとに描画
			Draw::Draw(1, &src, &dst, d3, 0.0f);
		}
		else
		{
			m_help_f = false;//初期値に戻す
			m_page_nam = 0;
		}
	}

}
