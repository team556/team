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

//イニシャライズ
void CObjHelp::Init()
{
	m_help_f = false;
	m_page_nam = 0;
	m_Scene_nam = 0;

	m_x = 1140.0f;
	m_y =   10.0f;

	m_mou_f = false;

	CObjHome* Hom = (CObjHome*)Objs::GetObj(OBJ_HOME);				//各シーン情報を取得
	CObjTraining* Tra = (CObjTraining*)Objs::GetObj(OBJ_TRAINING);
	CObjPreparation* Pre = (CObjPreparation*)Objs::GetObj(OBJ_PREPARATION);
	CObjFight* Fig = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
	

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

	if (m_help_f == false)						//ヘルプ表示してない場合かつ
	{											//ボタンクリックした場合
		if (1140 < m_mou_x && m_mou_x < 1190 && 10 < m_mou_y && m_mou_y < 60 && m_mou_l == true)
		{	
			m_help_f = true;//ヘルプ表示する
		}
	}
	else if(m_mou_l == true && m_mou_f == false)//ヘルプ表示中かつクリックした場合
	{								
		m_page_nam++;		//ページ数を進める
		m_mou_f = true;
	}

	if (m_mou_l == false)						//クリック解除時
	{
		m_mou_f = false;	//マウスフラグ解除
	}
}

//ドロー
void CObjHelp::Draw()
{
	/*float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	Font::StrDraw(L"", 230, 250, 32, c);*/
	
	//描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	float d[4] = { 1.0f,1.0f, 1.0f, 1.0f };

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
	Draw::Draw(1, &src, &dst, d, 0.0f);

	if (m_help_f == true)
	{
		if(m_Scene_nam = 1)
		{
			if(m_page_nam == 0)
			{
				src.m_top   =  0.0f;
				src.m_left  =  0.0f;
				src.m_right =100.0f;
				src.m_bottom=100.0f;
	
				dst.m_top   =   0.0f;
				dst.m_left  =   0.0f;
				dst.m_right =1200.0f;//仮フル画面
				dst.m_bottom= 700.0f;

				//0番目に登録したグラフィックをsrc,dst,c情報をもとに描画
				Draw::Draw(1, &src, &dst, d, 0.0f);
			}
			else if(m_page_nam == 1)
			{
				src.m_top   =  0.0f;
				src.m_left  =  0.0f;
				src.m_right =100.0f;
				src.m_bottom=100.0f;
	
				dst.m_top   =   0.0f;
				dst.m_left  =   0.0f;
				dst.m_right =1200.0f;//仮フル画面
				dst.m_bottom= 700.0f;

				//0番目に登録したグラフィックをsrc,dst,c情報をもとに描画
				Draw::Draw(1, &src, &dst, d, 0.0f);
			}
			else if(m_page_nam == 2)
			{
				src.m_top   =  0.0f;
				src.m_left  =  0.0f;
				src.m_right =100.0f;
				src.m_bottom=100.0f;
	
				dst.m_top   =   0.0f;
				dst.m_left  =   0.0f;
				dst.m_right =1200.0f;//仮フル画面
				dst.m_bottom= 700.0f;

				//0番目に登録したグラフィックをsrc,dst,c情報をもとに描画
				Draw::Draw(1, &src, &dst, d, 0.0f);
			}
			else if(m_page_nam == 3)
			{
				src.m_top   =  0.0f;
				src.m_left  =  0.0f;
				src.m_right =100.0f;
				src.m_bottom=100.0f;
	
				dst.m_top   =   0.0f;
				dst.m_left  =   0.0f;
				dst.m_right =1200.0f;//仮フル画面
				dst.m_bottom= 700.0f;

				//0番目に登録したグラフィックをsrc,dst,c情報をもとに描画
				Draw::Draw(1, &src, &dst, d, 0.0f);
			}
			}
	}

}
