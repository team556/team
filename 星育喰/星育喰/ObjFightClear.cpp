//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjFightClear.h"

//使用するネームスペース
using namespace GameL;

//グローバル変数の定義
int g_Iron_num = 0;
int g_Wood_num = 0;
int g_Silver_num = 0;
int g_Plastic_num = 0;
int g_Aluminum_num = 0;
int g_gus_num = 0;
int g_Raremetal_num = 0;


//コンストラクタ
CObjFightClear::CObjFightClear(int p, int m, int l, int s)
{
	//作成時に渡された値を代入
	m_people = p;
	m_mrl = m;
	m_skill = s;
	m_large = l;
}

//イニシャライズ
void CObjFightClear::Init()
{
	//m_mou_x = 0.0f;	//マウスX座標
	//m_mou_y = 0.0f; //マウスY座標
	//m_mou_r = false;//右クリック
	m_mou_l = false;//左クリック

	m_a = 0.0f;
	m_a_vec = 0.0f;
	m_a_f = false;

	m_cnt_max = 2 * 60;	//2秒
	m_cnt = m_cnt_max;	//最大値を入れておく

	m_Stage_Clear_f = false;	//ステージクリアフラグ
	m_Game_Clear_f = false;		//ゲーム　クリアフラグ

	m_page_nam = 0;				//ページ数0

	if (g_Stage_progress == 1 &&		//1ステージクリアした場合
		g_destroy_progress[0] == true &&	
		g_destroy_progress[1] == true &&
		g_destroy_progress[2] == true &&
		g_destroy_progress[3] == true)	
	{
		g_Stage_progress += 1;	//ステージを進める
		for (int i = 0; i < 4; i++)	
			g_destroy_progress[i] = false;
	}		//敵の撃破状態をすべて戻す

	g_Remain_num += m_people;	//取得住民を加算

	if (m_skill != 0)				//スキル取得している場合
	{							//その番号を取得する
		g_Special_mastering[m_skill] = true;
	}
	else { ; }

	if (m_mrl == 0)
	{
		g_Wood_num += 40;
	}
	else if (m_mrl == 1)
	{
		g_Wood_num += 80;
	}
	else if (m_mrl == 2)
	{
		g_Iron_num += 40;
	}

}

//アクション
void CObjFightClear::Action()
{
	////マウスの位置を取得
	//m_mou_x = (float)Input::GetPosX();
	//m_mou_y = (float)Input::GetPosY();
	////マウスのボタンの状態
	//m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	if (m_cnt == 0) 
	{											//カウント終了後
		m_a_f = true;			//フラグ有効
		if (m_mou_l == true)					//クリックした場合
		{
			if (m_Game_Clear_f == false)
			{
				
				if(g_Stage_progress == 1)
					Scene::SetScene(new CSceneHome());	//シーン移行
				else
					m_Game_Clear_f = true;

				//戦闘音楽を破棄し勝利音楽再生
				Audio::Stop(0);
				Audio::Start(1);
			}
			else
			{
				m_page_nam++;		//ページ数を進める
				m_cnt = m_cnt_max;	//カウントをMAXにする
				m_a_f = false;
			}
		}
	}
	else
		m_cnt--;	//0でない場合カウントダウン

	if (m_a_f == true)				//フラグ有効の場合
		if (m_a <= 0.5)					//0.5で切り替えて、クリック文字のalpha調整
			m_a_vec += 0.003f;	//ベクトルに加算
		else
			m_a_vec -= 0.003f;	//ベクトルに減算
	else
	{								//フラグ無効の場合
		m_a = 0;		//alpha = 0
		m_a_vec = 0;	//	vec = 0
	}

	m_a += m_a_vec;	//ベクトルを反映

}

//ドロー
void CObjFightClear::Draw()
{
	//描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	float d[4] = { 1.0f,1.0f, 1.0f, 1.0f };//画像の色

	RECT_F src;//切り取り位置
	RECT_F dst;//表示位置
	
	src.m_top   =  0.0f;
	src.m_left  =  0.0f;
	src.m_right =100.0f;
	src.m_bottom=100.0f;
	
	if (m_Game_Clear_f == false)
	{
		dst.m_top    =  50.0f;
		dst.m_left   = 650.0f;
		dst.m_right  =1100.0f;
		dst.m_bottom = 600.0f;
		//0番目に登録したグラフィックをsrc,dst,c情報をもとに描画
		Draw::Draw(2, &src, &dst, d, 0.0f);

		float c0[4] = { 1.0f,1.0f,1.0f,m_a };//charの色
		Font::StrDraw(L"クリックでホーム画面", 350, 600, 50, c0);

		float c[4] = { 0.0f,0.0f,0.0f,1.0f };//charの色
		Font::StrDraw(L"住民　＋",	700, 100, 50, c);

		Font::StrDraw(L"資材　＋",	700, 200, 50, c);

		Font::StrDraw(L"サイズ　＋",700, 300, 50, c);

		if (m_skill != 0)
		{
			Font::StrDraw(L"技　＋",700, 400, 50, c);
		}
		else { ; }
		//Font::StrDraw(L"大きさ", 0, 300, 32, c);

		wchar_t str[256];
		swprintf_s(str, L"　 %d人", m_people);		//住民
		Font::StrDraw(str, 900, 100, 50, c);

		switch (m_mrl)
		{
		case 0:Font::StrDraw(L"　 木40", 900, 200, 50, c); break;
		case 1:Font::StrDraw(L"　 木80", 900, 200, 50, c); break;
		case 2:Font::StrDraw(L"　 鉄40", 900, 200, 50, c); break;
		case 3:Font::StrDraw(L"　 鉄40", 900, 200, 50, c); break;
		case 4:Font::StrDraw(L"   木60", 900, 175, 50, c);
			Font::StrDraw(L"   鉄60", 900, 225, 50, c);
			break;
		}

		swprintf_s(str, L"　 %d", m_large);		//大きさ
		Font::StrDraw(str, 900, 300, 50, c);

		switch (m_skill)						 //スペシャル技
		{
		case 0: break;
		case 1:Font::StrDraw(L"　 Explosion",			800, 410, 40, c); break;
		case 2:Font::StrDraw(L"　 Fracture Ray",		800, 410, 40, c); break;
		case 3:Font::StrDraw(L"　 Immortality",			800, 410, 40, c); break;
		case 4:Font::StrDraw(L"　 リミットブレイク",	800, 410, 40, c); break;
		case 5:Font::StrDraw(L"　 ステロイド投与",		800, 410, 40, c); break;
		}
	}
	else
	{
		if(m_page_nam == 1)
		{
			dst.m_top    =  50.0f;
			dst.m_left   = 200.0f;
			dst.m_right  =1000.0f;
			dst.m_bottom = 250.0f;

			//0番目に登録したグラフィックをsrc,dst,c情報をもとに描画
			Draw::Draw(2, &src, &dst, d, 0.0f);

			float c[4] = { 0.0f,0.0f,0.0f,1.0f };//charの色
			Font::StrDraw(L"すべての惑星を捕食した",	 300,  80, 50, c);
			//Font::StrDraw(L"この銀河のトップに君臨した", 250, 180, 50, c);
		}
		else if(m_page_nam == 2)
		{
			dst.m_top    =  50.0f;
			dst.m_left   = 200.0f;
			dst.m_right  =1000.0f;
			dst.m_bottom = 250.0f;

			//0番目に登録したグラフィックをsrc,dst,c情報をもとに描画
			Draw::Draw(2, &src, &dst, d, 0.0f);

			float c[4] = { 0.0f,0.0f,0.0f,1.0f };//charの色
			Font::StrDraw(L"すべての惑星を捕食した",	 300,  80, 50, c);
			Font::StrDraw(L"この銀河のトップに君臨した", 250, 180, 50, c);
		}
		else if(m_page_nam == 3)
		{
			Scene::SetScene(new CSceneGameClear());	//シーン移行
		}

		float c0[4] = { 1.0f,1.0f,1.0f,m_a };//charの色
		Font::StrDraw(L"クリックで進める", 350, 600, 50, c0);
	}
	
}
