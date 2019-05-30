//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"

//使用するネームスペース
using namespace GameL;

//マクロ
#define INI_ALPHA (1.0f) //透過度(アルファ値)の初期値

////コンストラクタ
//CObjTest::CObjTest(float x, float y)
//{
//	//作成時に渡された値を、座標の初期値に代入
//	m_x = x;
//	m_y = y;
//}

//イニシャライズ
void CObjFightOver::Init()
{
	//m_mou_x = 0.0f;	//マウスX座標
	//m_mou_y = 0.0f; //マウスY座標
	//m_mou_r = false;//右クリック
	m_mou_l = false;//左クリック

	m_a = 0.0f;
	m_a_vec = 0.0f;
	m_a_f = false;

	m_cnt = 3 * 60;	//3秒カウント

	m_alpha = INI_ALPHA;


	//▼グローバル変数(全保存データ)リセット処理
	g_Stage_progress = 1;

	for (int i = 0; i < 4; i++)
	{
		g_destroy_progress[i] = false;
	}

	g_Bar_Level = 1;
	g_Ins_Level = 1;
	g_Mis_Recast_Level = 0;
	g_Pow_equip_Level = 1;
	g_Pow_equip_Lv_achieve = 1;
	g_Def_equip_Level = 1;
	g_Def_equip_Lv_achieve = 1;
	g_Spe_equip_Level = 1;
	g_Spe_equip_Lv_achieve = 1;
	g_Bal_equip_Level = 1;
	g_Bal_equip_Lv_achieve = 1;
	g_Pod_equip_Level = 1;
	g_Pod_equip_Lv_achieve = 1;
	g_Player_max_size = 10;
	g_Special_equipment = 0;

	for (int i = 0; i < 5; i++)
	{
		g_Special_mastering[i] = false;
	}

	g_Power_num = 0;		
	g_Defense_num = 0;		
	g_Speed_num = 0;		
	g_Balance_num = 0;		
	g_Research_num = 0;
	g_Remain_num = 1000;

	g_Iron_num = 0;
	g_Wood_num = 0;
	g_Silver_num = 0;
	g_Plastic_num = 0;
	g_Aluminum_num = 0;
	g_gus_num = 0;
	g_Raremetal_num = 0;
}

//アクション
void CObjFightOver::Action()
{

	////マウスの位置を取得
	//m_mou_x = (float)Input::GetPosX();
	//m_mou_y = (float)Input::GetPosY();
	////マウスのボタンの状態
	//m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	if (m_cnt == 0) 
	{							//カウント終了後
		m_a_f = true;			//フラグ有効
		if (m_mou_l == true || m_alpha< INI_ALPHA)					//クリックした場合
		{
			if (m_alpha == INI_ALPHA)
			{
				Audio::Start(3);
			}

			m_alpha -= 0.01f;

			if (m_alpha <= 0.0f)
			{
				Scene::SetScene(new CSceneTitle());	//シーン移行
			}
		}

	}
	else
		m_cnt--;	//0でない場合カウントダウン

	if (m_a_f == true)			//フラグ有効の場合
		if (m_a <= 0.5)						//0.5で切り替え
			m_a_vec += 0.003f;	//ベクトルに加算
		else
			m_a_vec -= 0.003f;	//ベクトルに減算

	m_a += m_a_vec;	//ベクトルを反映
}

//ドロー
void CObjFightOver::Draw()
{
	//描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	float d[4] = { 1.0f,1.0f, 1.0f, m_alpha };//画像の色

	RECT_F src;//切り取り位置
	RECT_F dst;//表示位置
	
	src.m_top   =  0.0f;
	src.m_left  =  0.0f;
	src.m_right =100.0f;
	src.m_bottom=100.0f;
	
	dst.m_top   =  75.0f;
	dst.m_left  = 300.0f;
	dst.m_right = 800.0f;
	dst.m_bottom= 175.0f;
	//0番目に登録したグラフィックをsrc,dst,c情報をもとに描画
	Draw::Draw(2, &src, &dst, d, 0.0f);

	float c0[4] = { 1.0f,1.0f,1.0f,m_a };//charの色
	Font::StrDraw(L"クリックでタイトル", 350, 600, 50, c0);

	float c[4] = { 0.7f,0.0f,0.0f,m_alpha };//charの色
	Font::StrDraw(L"ゲームオーバー", 350, 100, 50, c);

	//wchar_t str[256];
	//swprintf_s(str, L"＋%d人",m_x);		//住民
	//Font::StrDraw(str, 900, 100, 50, c);
}
