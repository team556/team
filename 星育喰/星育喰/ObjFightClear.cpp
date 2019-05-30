//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"

//使用するネームスペース
using namespace GameL;

//グローバル変数の定義
int g_Iron_num = 1000;
int g_Wood_num = 1000;
int g_Silver_num = 1000;
int g_Plastic_num = 1000;
int g_Aluminum_num = 1000;
int g_gus_num = 1000;
int g_Raremetal_num = 1000;

//マクロ
#define INI_ALPHA (1.0f) //その他透過度(アルファ値)の初期値

//コンストラクタ
CObjFightClear::CObjFightClear(int people, int large, wchar_t Mat_nameA[20], int *Mat_typeA, int Mat_numA, int skill)
{
	//作成時に渡された値を代入
	m_people = people;
	m_large = large;
	swprintf_s(m_mat_name[0], Mat_nameA);//文字配列に文字データを入れる
	swprintf_s(m_mat_name[1], L"");		 //文字データをクリアする
	m_mat_type[0] = Mat_typeA;
	m_mat_type[1] = nullptr;
	m_mat_num[0] = Mat_numA;
	m_mat_num[1] = NULL;
	m_skill = skill;
}

CObjFightClear::CObjFightClear(int people, int large, wchar_t Mat_nameA[20], int *Mat_typeA, int Mat_numA, wchar_t Mat_nameB[20], int *Mat_typeB, int Mat_numB, int skill)
{
	//作成時に渡された値を代入
	m_people = people;
	m_large = large;
	swprintf_s(m_mat_name[0], Mat_nameA);//文字配列に文字データを入れる
	swprintf_s(m_mat_name[1], Mat_nameB);//文字配列に文字データを入れる
	m_mat_type[0] = Mat_typeA;
	m_mat_type[1] = Mat_typeB;
	m_mat_num[0] = Mat_numA;
	m_mat_num[1] = Mat_numB;
	m_skill = skill;
}


//イニシャライズ
void CObjFightClear::Init()
{
	//m_mou_x = 0.0f;	//マウスX座標
	//m_mou_y = 0.0f; //マウスY座標
	//m_mou_r = false;//右クリック
	m_mou_l = false;//左クリック

	m_click_a = 0.0f;
	m_click_a_vec = 0.0f;
	m_click_a_f = false;
	m_result_a = 0.0f;
	m_alpha = INI_ALPHA;

	m_cnt_max = 60 * 2;	//2秒
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

	//1ステージクリア後、ゲームクリアフラグを立てる。
	//※処理内容的にはステージを進めた後の値が、
	//2ステージ以上であった場合という条件式にしている。
	if (g_Stage_progress >= 2)
	{
		m_Game_Clear_f = true;
	}

	//▼獲得したものをグローバル変数に代入する
	g_Remain_num += m_people;		//獲得住民数を加算
	g_Player_max_size += m_large;	//獲得サイズ(HP)数を加算

	//獲得資材数を加算
	for (int i = 0; i < 2; i++)
	{
		if (m_mat_type[i] != nullptr)
		{
			*m_mat_type[i] += m_mat_num[i];
		}
	}
	
	if (m_skill != 0)			//スキル取得している場合
	{							//その番号を取得する
		g_Special_mastering[m_skill - 1] = true;
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


	//▼カウント終了後の処理
	if (m_result_a >= 6.0f || m_click_a_f == true)
	{											
		m_click_a_f = true;			//フラグ有効
		
		//左クリックした場合、実行(一度クリックすると以後、クリックせずともこの処理に入る)
		//※ゲームクリアフラグON時は、何もしなくてもこの処理の中に入る。
		if (m_mou_l == true || m_alpha < INI_ALPHA || m_Game_Clear_f == true)					
		{
			//▽ゲーム未クリア時の処理
			//完全に透過された後、ホーム画面へステージ移行する。
			if (m_Game_Clear_f == false)
			{
				//クリック音を鳴らす(複数回実行されないように条件文でコントロールしている)
				if (m_alpha == INI_ALPHA)
				{
					Audio::Start(3);
				}

				m_alpha -= 0.01f;	//透過度を徐々に減少する
				m_click_a -= 0.03f;
				m_result_a -= 0.5f;

				//完全透過後の処理
				if (m_alpha <= 0.0f)
				{
					Scene::SetScene(new CSceneHome());	//シーン移行
				}
			}
			//▽ゲームクリア時の処理
			//2秒毎にゲームクリアメッセージを見せていき、
			//全てのクリアメッセージ表示後、クリックを促し
			//ゲームクリア(エンディング)画面にシーン移行する。
			else //(m_Game_Clear_f == true)
			{
				//全てのクリアメッセージ表示後の処理
				if (m_page_nam == 2)
				{	
					if (m_mou_l == true)//左クリック
					{
						//▼まだ作ってないが、ここでも透過処理行い、0.0fになったらシーン移行するようにする。
						//いや、ゲームオーバーの時と同じ処理にする。

						//クリック音を鳴らす(複数回実行されないように条件文でコントロールしている)
						//if (m_click_alpha == INI_ALPHA)
						//{
						//	Audio::Start(3);
						//}

						Scene::SetScene(new CSceneGameClear());	//シーン移行
					}
				}
				//全てのクリアメッセージ表示前の処理
				else
				{
					m_page_nam++;		//ページ数を進める
					m_cnt = m_cnt_max;	//カウントをMAXにする(元に戻す)
				}
			}
		}
	}
	//▼カウントダウン中の処理
	else
	{
		//m_cnt--;	//0でない場合カウントダウン

		//戦闘結果ウインドウ&フォント透過度増加
		//※順に戦闘結果ウインドウ&フォントが表示される
		m_result_a += 0.03f;



		CObjPlanet* Planet = (CObjPlanet*)Objs::GetObj(OBJ_PLANET);

		//プレイヤー惑星X座標を徐々に200.0fに近づける(画面左の方に移動)
		if (Planet->GetX() >= 200.0f)
		{
			Planet->SetVX(-4.0f);
		}

		////プレイヤー惑星Y座標を徐々に400.0fに近づける(微妙に下に移動)
		//if (Planet->GetY() < 400.0f)
		//{
		//	Planet->SetVY(+0.5f);
		//}
	}

	
	//▼「クリックでホーム画面」＆「クリックで進める」の文字点滅処理
	//ゲームクリアフラグOFF時はカウント終了後実行されるが、
	//一度でもクリックされるとその後実行されなくなる。
	//ゲームクリアフラグON時はゲームクリアメッセージ全表示後のみ実行される。
	if (m_Game_Clear_f == false && m_alpha == INI_ALPHA || m_page_nam == 2)
	{
		//フラグ有効の場合
		if (m_click_a_f == true)
		{
			if (m_click_a <= 0.5)			//0.5で切り替えて、クリック文字のalpha調整
				m_click_a_vec += 0.003f;	//ベクトルに加算
			else
				m_click_a_vec -= 0.003f;	//ベクトルに減算
		}
		//フラグ無効の場合
		else
		{
			m_click_a = 0;		//alpha = 0
			m_click_a_vec = 0;	//	vec = 0
		}

		m_click_a += m_click_a_vec;	//ベクトルを反映
	}
}

//ドロー
void CObjFightClear::Draw()
{
	//▽描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	float c0[4] = { 1.0f,1.0f,1.0f,m_click_a };//クリック催促フォント用
	
	//戦闘結果ウインドウ&フォント用
	float c[6][4] = 
	{ 
		{ 1.0f,1.0f,0.0f,m_result_a },			//捕食成功フォントは黄色
		{ 1.0f,1.0f,1.0f,m_result_a - 1.0f },	//ウインドウ表示用
		{ 0.0f,0.0f,0.0f,m_result_a - 2.0f },	//住民フォントは黒色
		{ 0.0f,0.0f,0.0f,m_result_a - 3.0f },	//サイズ(HP)フォントは黒色
		{ 0.0f,0.0f,0.0f,m_result_a - 4.0f },	//資材フォントは黒色
		{ 1.0f,0.0f,0.0f,m_result_a - 5.0f },	//スペシャル技フォントは赤色
	};

	float d[4] = { 1.0f,1.0f, 1.0f, m_alpha };//その他画像用

	//▽フォント準備
	//獲得数表示用(住民、資材、サイズ(HP)で使用)
	wchar_t str[256];//256文字分格納可能な文字配列を宣言


	RECT_F src;//切り取り位置
	RECT_F dst;//表示位置
	
	src.m_top   =  0.0f;
	src.m_left  =  0.0f;
	src.m_right = 64.0f;
	src.m_bottom= 64.0f;
	
	//▽ゲーム未クリア時の処理
	if (m_Game_Clear_f == false)
	{
		//▼ウインドウ表示
		dst.m_top    =  50.0f;
		dst.m_left   = 650.0f;
		dst.m_right  =1100.0f;
		dst.m_bottom = 600.0f;
		Draw::Draw(33, &src, &dst, c[1], 0.0f);


		//▼戦闘結果フォント表示
		//捕食成功フォント
		Font::StrDraw(L"捕食成功！", 670, 50, 50, c[0]);

		//住民
		Font::StrDraw(L"住民：",	670, 100, 50, c[2]);
		swprintf_s(str, L"＋%d人", m_people);
		Font::StrDraw(str, 800, 100, 50, c[2]);

		//サイズ(HP)
		Font::StrDraw(L"サイズ(HP)：", 670, 300, 50, c[3]);
		swprintf_s(str, L"＋%d", m_large);
		Font::StrDraw(str, 800, 300, 50, c[3]);

		//資材
		Font::StrDraw(L"資材：",	670, 200, 50, c[4]);
		Font::StrDraw(m_mat_name[0], 800, 200, 50, c[4]);
		swprintf_s(str, L"＋%d個", m_mat_num[0]);
		Font::StrDraw(str, 900, 200, 50, c[4]);
		Font::StrDraw(m_mat_name[1], 800, 250, 50, c[4]);
		swprintf_s(str, L"＋%d個", m_mat_num[1]);
		Font::StrDraw(str, 900, 250, 50, c[4]);

		//スペシャル技
		if (m_skill != 0)
		{
			Font::StrDraw(L"スペシャル技：",670, 400, 50, c[5]);
		}

		switch (m_skill)						
		{
		case 1:Font::StrDraw(L"Explosion", 800, 410, 40, c[5]); break;
		case 2:Font::StrDraw(L"Fracture Ray", 800, 410, 40, c[5]); break;
		case 3:Font::StrDraw(L"Immortality", 800, 410, 40, c[5]); break;
		case 4:Font::StrDraw(L"リミットブレイク", 800, 410, 40, c[5]); break;
		case 5:Font::StrDraw(L"ステロイド投与", 800, 410, 40, c[5]); break;
		default: break;
		}


		//資材
		//switch (m_mrl)
		//{
		//case 0:Font::StrDraw(L"　  木40", 800, 200, 50, c); break;
		//case 1:Font::StrDraw(L"　  木80", 800, 200, 50, c); break;
		//case 2:Font::StrDraw(L"　  鉄40", 800, 200, 50, c); break;
		//case 3:Font::StrDraw(L"　  鉄40", 800, 200, 50, c); break;
		//case 4:Font::StrDraw(L"    木60", 800, 175, 50, c);
		//	Font::StrDraw(L"    鉄60", 800, 225, 50, c);
		//	break;
		//}

		//▼クリック催促フォント表示
		Font::StrDraw(L"クリックでホーム画面", 350, 600, 50, c0);
	}
	//▽ゲームクリア時の処理
	else
	{
		//▼ゲームクリアメッセージ表示
		if(m_page_nam == 1)
		{
			//dst.m_top    =  50.0f;
			//dst.m_left   = 200.0f;
			//dst.m_right  =1000.0f;
			//dst.m_bottom = 250.0f;
			//Draw::Draw(33, &src, &dst, d, 0.0f);

			float c[4] = { 0.0f,0.0f,0.0f,1.0f };//charの色
			Font::StrDraw(L"すべての惑星を捕食した",	 300,  80, 50, c);
			//Font::StrDraw(L"この銀河のトップに君臨した", 250, 180, 50, c);
		}
		else if(m_page_nam == 2)
		{
			//dst.m_top    =  50.0f;
			//dst.m_left   = 200.0f;
			//dst.m_right  =1000.0f;
			//dst.m_bottom = 250.0f;
			//Draw::Draw(33, &src, &dst, d, 0.0f);

			float c[4] = { 0.0f,0.0f,0.0f,1.0f };//charの色
			Font::StrDraw(L"すべての惑星を捕食した",	 300,  80, 50, c);
			Font::StrDraw(L"この銀河のトップに君臨した", 250, 180, 50, c);

			float c0[4] = { 1.0f,1.0f,1.0f,m_click_a };//charの色
			Font::StrDraw(L"クリックで進む", 350, 600, 50, c0);
		}
	}
}
