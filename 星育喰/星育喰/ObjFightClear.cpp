//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "UtilityModule.h"

//使用するネームスペース
using namespace GameL;

//マクロ
#define FONT_X (400)//戦闘結果フォント(左端)のX位置
#define FONT_Y (230)//戦闘結果フォント(左端)のX位置

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

	//コワモーテの場合、全素材という例外的な処理のため、
	//ここで木材以外の素材の獲得処理を行う。
	if (g_Challenge_enemy == 2)
	{
		//▼獲得素材数を加算
		g_Iron_num = 100;
		g_Silver_num = 100;
		g_Plastic_num = 100;
		g_Aluminum_num = 100;
		g_gus_num = 100;
	}
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
	m_key_f = false;

	m_click_a = 0.0f;
	m_click_a_vec = 0.0f;
	m_click_a_f = false;
	m_result_a = 0.0f;
	m_black_out_a = 0.0f;
	m_clear_a = 0.0f;
	m_clear_a_vec = 0.0f;

	m_scene_migration_f = false;

	//m_cnt_max = 60 * 2;	//2秒
	//m_cnt = m_cnt_max;	//最大値を入れておく

	m_Stage_Clear_f = false;	//ステージクリアフラグ
	m_Game_Clear_f = false;		//ゲーム　クリアフラグ

	//m_page_nam = 0;				//ページ数0

	m_c_p = 0;		//クリア画面住民位置調整用

	m_tuto_f = false;

	m_end_f = false;

	//ステージクリアした場合
	if (g_destroy_progress[0] == true &&	
		g_destroy_progress[1] == true &&
		g_destroy_progress[2] == true &&
		g_destroy_progress[3] == true)	
	{
		//チュートリアル惑星を倒してもステージ数を進めないようにする処理。
		if (g_tutorial_progress >= 8)
		{
			g_Stage_progress++;	//ステージを進める
		}
		
		for (int i = 0; i < 4; i++)
		{
			g_destroy_progress[i] = false;//敵の撃破状態をすべて戻す
		}
	}	

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
	
	//スキル取得している場合
	//その番号を取得する
	if (m_skill != 0)			
	{							
		g_Special_mastering[m_skill - 1] = true;
	}
}

//アクション
void CObjFightClear::Action()
{
	if (m_Game_Clear_f == false)
	{
		//▽ゲーム未クリア時の処理
		//プレイヤー惑星を左に移動させつつ、
		//戦闘結果を徐々に表示していく。
		//全て表示後クリックを促し、クリックすると
		//一旦画面暗転し、その後画面明転すると
		//ホーム画面に移行している風に見せる演出後、
		//実際にホーム画面へステージ移行する。


		//▼戦闘結果表示終了後の処理
		if (m_result_a >= 7.0f)
		{
			//チュートリアル説明中はホーム画面に戻れない処理
			if (g_tutorial_progress == 6 && m_tuto_f == true)
			{
				return;
			}
			else if (g_tutorial_progress == 6)
			{
				//ObjMessageのメッセージ進行度を増加させる
				CObjMessage* message = (CObjMessage*)Objs::GetObj(OBJ_MESSAGE);
				message->Setprogress(43);

				m_tuto_f = true;//フラグON

				return;
			}

			////マウスの位置を取得
			//m_mou_x = (float)Input::GetPosX();
			//m_mou_y = (float)Input::GetPosY();
			////マウスのボタンの状態
			//m_mou_r = Input::GetMouButtonR();
			m_mou_l = Input::GetMouButtonL();

			//▼キーフラグ
			//※左クリック押しっぱなしの状態で、この処理に入った時、
			//そのままホーム画面移行処理に入らないようにする処理。
			if (m_mou_l == false)
			{
				m_key_f = true;
			}

			m_click_a_f = true;			//フラグ有効

			//左クリックした場合、実行(一度クリックすると以後、クリックせずともこの処理に入る)
			if (m_mou_l == true && m_key_f == true || m_black_out_a != 0.0f || m_scene_migration_f == true)
			{
				//クリック音を鳴らす(1度のみしか実行されない)
				if (m_black_out_a == 0.0f && m_scene_migration_f == false)
				{
					Audio::Start(3);
				}

				//画面暗転透過度を徐々に増加させ、画面全体を暗転させた後、
				//フラグを立て、ホーム画面移行演出を行い、
				//演出終了後、本当にホーム画面へ移行させる。
				if (m_black_out_a <= 0.0f && m_scene_migration_f == true)
				{
					Scene::SetScene(new CSceneHome());	//シーン移行
				}
				else if (m_scene_migration_f == true)
				{
					m_black_out_a -= 0.01f;//画面明転
				}
				else if (m_black_out_a >= 1.0f)
				{
					m_scene_migration_f = true;//シーン移行演出フラグON
				}
				else
				{
					m_black_out_a += 0.01f;//画面暗転
					m_click_a -= 0.03f;	   //クリック催促フォントを徐々に非表示に。
				}

				m_click_a_f = false;//フラグ無効
			}
		}
		//▼戦闘結果表示中の処理
		else
		{
			//戦闘結果ウインドウ&フォント透過度増加し、
			//順に戦闘結果ウインドウ&フォントを表示していく。
			//※全て表示後、このelse文を抜ける。
			m_result_a += 0.03f;

			//プレイヤー惑星X座標(m_px)を徐々に200.0fに近づける(画面左の方に移動)
			//※以下のif文はサイズ縮小分、X座標移動しているのも考慮済。
			CObjPlanet* Planet = (CObjPlanet*)Objs::GetObj(OBJ_PLANET);
			if (Planet->GetX() >= 200.0f - Planet->GetScale_down_move())
			{
				Planet->SetVX(-4.0f);
			}
		}
	}
	else //(m_Game_Clear_f == true)
	{
		//▽ゲームクリア時の処理
		//山田との会話→クリアメッセージを見せた後に
		//自動でゲームクリア(エンディング)画面にシーン移行する。


		//以下は山田会話終了後実行される処理。
		if (g_tutorial_progress == 31)
		{
			if (m_black_out_a >= 1.0f)
			{
				if (m_clear_a <= 1.0)			//1.0で切り替えて、クリアメッセージ演出のalpha調整
				{
					m_clear_a_vec += 0.0005f;	//ベクトルに加算
				}
				else
				{
					m_clear_a_vec -= 0.0003f;	//ベクトルに減算
				}

				m_clear_a += m_clear_a_vec;	//ベクトルを反映

				//クリアメッセージ演出処理終了時点でエンディングへシーン移行
				if (m_clear_a <= 0.0f)
				{
					Scene::SetScene(new CSceneGameClear());	//シーン移行
				}
			}
			else
			{
				m_black_out_a += 0.01f;
			}
		}
		//m_end_fを使い、一度のみObjMessage(Scene_id = 30)を呼び出す。
		//ついでに、アマテラスをノーダメージクリア出来たかどうかの判定も行う。
		else if (m_end_f == false)
		{
			//「ＶＳアマテラス」のランクを表示こそはしないものの、
			//内部でランク判定処理を行い、Ｓかそれ以外かを判定する。
			//[理由：山田のセリフ変更イベントでＳかそれ以外かは重要なポイントとなるので。]
			//※ObjMessageを呼び出す前に判定しないといけない。
			//何故なら山田のセリフ決定処理はObjMessageのイニシャライズで行われるからである。
			CObjPlanet* player = (CObjPlanet*)Objs::GetObj(OBJ_PLANET);
			//Ｓランクの時の処理
			if (player->GetRank_size() == 1.0f)
			{
				;//何の処理も行わない。
			}
			//それ以外の時の処理
			else
			{
				g_no_damage_clear_f = false;//全ステージのノーダメージクリアを出来なかったと記録する
			}

			CObjMessage* message = new CObjMessage(30);	//メッセージ表示オブジェクト作成
			Objs::InsertObj(message, OBJ_MESSAGE, 90);	//メッセージ表示オブジェクト登録

			m_end_f = true;
		}

		return;

		//▼以前のクリアメッセージ処理
		////全てのクリアメッセージ表示後の処理
		//if (m_clear_a >= 3.0f)
		//{
		//	////マウスの位置を取得
		//	//m_mou_x = (float)Input::GetPosX();
		//	//m_mou_y = (float)Input::GetPosY();
		//	////マウスのボタンの状態
		//	//m_mou_r = Input::GetMouButtonR();
		//	m_mou_l = Input::GetMouButtonL();

		//	//▼キーフラグ
		//	//※左クリック押しっぱなしの状態で、この処理に入った時、
		//	//そのままホーム画面移行処理に入らないようにする処理。
		//	if (m_mou_l == false)
		//	{
		//		m_key_f = true;
		//	}

		//	m_click_a_f = true;			//フラグ有効

		//	//左クリックした場合、実行(一度クリックすると以後、クリックせずともこの処理に入る)
		//	if (m_mou_l == true && m_key_f == true || m_black_out_a != 0.0f)
		//	{
		//		//クリック音を鳴らす(1度のみしか実行されない)
		//		if (m_black_out_a == 0.0f)
		//		{
		//			Audio::Start(3);
		//		}

		//		//画面暗転透過度を徐々に増加させ、画面全体を暗転させた後、
		//		//フラグを立て、ゲームクリア画面に移行する
		//		if (m_black_out_a >= 1.0f)
		//		{
		//			Scene::SetScene(new CSceneGameClear());	//シーン移行
		//		}
		//		else
		//		{
		//			m_black_out_a += 0.01f;//画面暗転
		//			m_click_a -= 0.03f;	   //クリック催促フォントを徐々に非表示に。
		//		}

		//		m_click_a_f = false;//フラグ無効
		//	}
		//}
		////全てのクリアメッセージ表示前の処理
		//else
		//{
		//	//クリアメッセージフォントの透過度増加し、
		//	//順にクリアメッセージを表示していく。
		//	//※全て表示後、このelse文を抜ける。
		//	m_clear_a += 0.01f;
		//}
	}

	//▼「クリックでホーム画面」＆「クリックで進める」の文字点滅処理
	//ゲームクリアフラグOFF時は戦闘結果表示終了後実行されるが、
	//一度でもクリックされるとその後実行されなくなる。
	//ゲームクリアフラグON時はゲームクリアメッセージ全表示後のみ実行される。

	//フラグ有効の場合
	if (m_click_a_f == true)
	{
		if (m_click_a <= 0.5)			//0.5で切り替えて、クリック文字のalpha調整
		{
			m_click_a_vec += 0.003f;	//ベクトルに加算
		}			
		else
		{
			m_click_a_vec -= 0.003f;	//ベクトルに減算
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
	float c[7][4] = 
	{ 
		{ 1.0f,1.0f,0.0f,m_result_a },			//捕食成功フォントは黄色
		{ 1.0f,1.0f,1.0f,m_result_a - 1.0f },	//ウインドウ表示用
		{ 1.0f,1.0f,1.0f,m_result_a - 2.0f },	//住民フォントは白色
		{ 1.0f,1.0f,1.0f,m_result_a - 3.0f },	//サイズ(HP)フォントは白色
		{ 1.0f,1.0f,1.0f,m_result_a - 4.0f },	//資材フォントは白色
		{ 1.0f,1.0f,1.0f,m_result_a - 5.0f },	//スペシャル技フォントは白色
		{ 1.0f,0.5f,0.0f,m_result_a - 6.0f },	//ランクフォントは橙色
	};

	float blackout[4] = { 1.0f,1.0f,1.0f,m_black_out_a };	//画面全体暗転画像用

	//クリアメッセージフォント用
	float clear[4] = { 1.0f,1.0f,0.0f,m_clear_a };


	float d[4] = { 1.0f,1.0f, 1.0f, 1.0f };//その他画像用

	//▽フォント準備
	//獲得数表示用(住民、資材、サイズ(HP)で使用)
	//wchar_t str[256];//256文字分格納可能な文字配列を宣言


	RECT_F src;//切り取り位置
	RECT_F dst;//表示位置
	
	src.m_top   =  0.0f;
	src.m_left  =  0.0f;
	src.m_right = 64.0f;
	src.m_bottom= 64.0f;
	
	//▽ゲーム未クリア時の処理
	if (m_Game_Clear_f == false)
	{
		//シーン移行演出前に表示するグラフィック
		//※クリア画面で見せるグラフィック
		if (m_scene_migration_f == false)
		{
			////▼ウインドウ表示
			//dst.m_top = 210.0f;
			//dst.m_left = 350.0f;
			//dst.m_right = 1150.0f;
			//dst.m_bottom = 530.0f;
			//Draw::Draw(33, &src, &dst, c[1], 0.0f);

			////▼ウインドウ表示左上
			//src.m_top = 0.0f;
			//src.m_left = 0.0f;
			//src.m_right = 795.0f;
			//src.m_bottom = 800.0f;

			//dst.m_top = 210.0f;
			//dst.m_left = 350.0f;
			//dst.m_right = 510.0f;
			//dst.m_bottom = 370.0f;
			//Draw::Draw(77, &src, &dst, c[1], 0.0f);

			////▼ウインドウ表示左下
			//src.m_top = 40.0f;
			//src.m_left = 800.0f;
			//src.m_right = 1600.0f;
			//src.m_bottom = 800.0f;

			//dst.m_top = 370.0f;
			//dst.m_left = 350.0f;
			//dst.m_right = 510.0f;
			//dst.m_bottom = 530.0f;
			//Draw::Draw(77, &src, &dst, c[1], 0.0f);

			//for (int i = 0;i < 3;i++)
			//{
			//	//▼ウインドウ表示中央上
			//	src.m_top = 0.0f;
			//	src.m_left = 1600.0f;
			//	src.m_right = 2400.0f;
			//	src.m_bottom = 800.0f;

			//	dst.m_top = 210.0f;
			//	dst.m_left = 510.0f + (i * 160);
			//	dst.m_right = 670.0f + (i * 160);
			//	dst.m_bottom = 370.0f;
			//	Draw::Draw(77, &src, &dst, c[1], 0.0f);

			//	//▼ウインドウ表示中央下
			//	src.m_top = 10.0f;
			//	src.m_left = 2400.0f;
			//	src.m_right = 3200.0f;
			//	src.m_bottom = 800.0f;

			//	dst.m_top = 370.0f;
			//	dst.m_left = 510.0f + (i * 160);
			//	dst.m_right = 670.0f + (i * 160);
			//	dst.m_bottom = 530.0f;
			//	Draw::Draw(77, &src, &dst, c[1], 0.0f);
			//}
			//
			////▼ウインドウ表示右上
			//src.m_top = 0.0f;
			//src.m_left = 4000.0f;
			//src.m_right = 4800.0f;
			//src.m_bottom = 800.0f;

			//dst.m_top = 210.0f;
			//dst.m_left = 990.0f;
			//dst.m_right = 1150.0f;
			//dst.m_bottom = 370.0f;
			//Draw::Draw(77, &src, &dst, c[1], 0.0f);

			////▼ウインドウ表示右下
			//src.m_top = 15.0f;
			//src.m_left = 4800.0f;
			//src.m_right = 5600.0f;
			//src.m_bottom = 800.0f;

			//dst.m_top = 370.0f;
			//dst.m_left = 990.0f;
			//dst.m_right = 1150.0f;
			//dst.m_bottom = 530.0f;
			//Draw::Draw(77, &src, &dst, c[1], 0.0f);

			//▼ウインドウ表示
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 1200.0f;
			src.m_bottom = 700.0f;

			dst.m_top = 210.0f;
			dst.m_left = 350.0f;
			dst.m_right = 1150.0f;
			dst.m_bottom = 530.0f;
			Draw::Draw(79, &src, &dst, c[1], 0.0f);

			//▼戦闘結果フォント表示
			//捕食成功フォント
			src.m_top = 2.0f;
			src.m_left = 2.0f;
			src.m_right = 547.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 50.0f;
			dst.m_left = 370.0f;
			dst.m_right = 830.0f;
			dst.m_bottom = 150.0f;
			Draw::Draw(53, &src, &dst, c[0], 0.0f);
			//Font::StrDraw(L"捕食成功！", 370, 50, 100, c[0]);


			//住民
			src.m_top = 2.0f;
			src.m_left = 2.0f;
			src.m_right = 230.0f;
			src.m_bottom = 110.0f;

			dst.m_top = FONT_Y;
			dst.m_left = FONT_X;
			dst.m_right = FONT_X + 80;
			dst.m_bottom = FONT_Y + 40.0f;
			Draw::Draw(56, &src, &dst, c[2], 0.0f);

			src.m_top = 1250.0f;
			src.m_left = 250.0f;
			src.m_right = 375.0f;
			src.m_bottom = 1375.0f;

			dst.m_top = FONT_Y;
			dst.m_left = FONT_X + 80;
			dst.m_right = FONT_X + 120;
			dst.m_bottom = FONT_Y + 40.0f;
			Draw::Draw(41, &src, &dst, c[2], 0.0f);
			//Font::StrDraw(L"住民：", FONT_X, FONT_Y, 40, c[2]);
			
			//ここから獲得住民数表示--------------------------------------------------------------------
			//+
			src.m_top = 1250.0f;
			src.m_left = 375.0f;
			src.m_right = 500.0f;
			src.m_bottom = 1375.0f;

			dst.m_top = FONT_Y;
			dst.m_left = FONT_X + 300.0f;
			dst.m_right = FONT_X + 340.0f;
			dst.m_bottom = FONT_Y + 40.0f;
			Draw::Draw(41, &src, &dst, c[2], 0.0f);

			if (m_people >= 10000) {
				//万の位
				src.m_top = 1250.0f;
				src.m_left =  CUT_ZERO + (floor(m_people / 10000) * 125);
				src.m_right =  END_ZERO + (floor(m_people / 10000) * 125);
				src.m_bottom = 1375.0f;

				dst.m_top = FONT_Y;
				dst.m_left = FONT_X + 340;
				dst.m_right = FONT_X + 360;
				dst.m_bottom = FONT_Y + 40;
				Draw::Draw(41, &src, &dst, c[2], 0.0f);
				m_c_p = 20;
			}
			//千の位
			src.m_top = 1250.0f;
			src.m_left =  CUT_ZERO + (floor((m_people / 1000) % 10) * 125);
			src.m_right =  END_ZERO + (floor((m_people / 1000) % 10) * 125);
			src.m_bottom = 1375.0f;

			dst.m_top = FONT_Y;
			dst.m_left = FONT_X + 340 + m_c_p;
			dst.m_right = FONT_X + 360 + m_c_p;
			dst.m_bottom = FONT_Y + 40;
			Draw::Draw(41, &src, &dst, c[2], 0.0f);

			//百の位
			src.m_top = 1250.0f;
			src.m_left =  CUT_ZERO + (floor((m_people / 100) % 10) * 125);
			src.m_right =  END_ZERO + (floor((m_people / 100) % 10) * 125);
			src.m_bottom = 1375.0f;

			dst.m_top = FONT_Y;
			dst.m_left = FONT_X + 360 + m_c_p;
			dst.m_right = FONT_X + 380 + m_c_p;
			dst.m_bottom = FONT_Y + 40;
			Draw::Draw(41, &src, &dst, c[2], 0.0f);

			//十の位
			src.m_top = 1250.0f;
			src.m_left =  CUT_ZERO + (floor((m_people / 10) % 10) * 125);
			src.m_right =  END_ZERO + (floor((m_people / 10) % 10) * 125);
			src.m_bottom = 1375.0f;

			dst.m_top = FONT_Y;
			dst.m_left = FONT_X + 380 + m_c_p;
			dst.m_right = FONT_X + 400 + m_c_p;
			dst.m_bottom = FONT_Y + 40;
			Draw::Draw(41, &src, &dst, c[2], 0.0f);

			//一の位
			src.m_left =  CUT_ZERO + (((m_people / 10) % 10) * 125);
			src.m_right =  END_ZERO + (((m_people / 10) % 10) * 125);
			src.m_bottom = 1375.0f;

			dst.m_top = FONT_Y;
			dst.m_left = FONT_X + 400 + m_c_p;
			dst.m_right = FONT_X + 420 + m_c_p;
			dst.m_bottom = FONT_Y + 40;
			Draw::Draw(41, &src, &dst, c[2], 0.0f);

			//--------------------------------------------------------------------
			//swprintf_s(str, L"＋%d人", m_people);
			//Font::StrDraw(str, FONT_X + 300, FONT_Y, 40, c[2]);


			//サイズ(HP)
			src.m_top = 2.0f;
			src.m_left = 5.0f;
			src.m_right = 410.0f;
			src.m_bottom = 112.0f;

			dst.m_top = FONT_Y + 50.0f;
			dst.m_left = FONT_X;
			dst.m_right = FONT_X + 160;
			dst.m_bottom = FONT_Y + 90.0f;
			Draw::Draw(55, &src, &dst, c[3], 0.0f);

			src.m_top = 1260.0f;
			src.m_left = 250.0f;
			src.m_right = 375.0f;
			src.m_bottom = 1375.0f;

			dst.m_top = FONT_Y + 50.0f;
			dst.m_left = FONT_X + 160;
			dst.m_right = FONT_X + 200;
			dst.m_bottom = FONT_Y + 90.0f;
			Draw::Draw(41, &src, &dst, c[3], 0.0f);
			//Font::StrDraw(L"惑星HP：", FONT_X, FONT_Y + 50, 40, c[3]);
			
			//惑星取得HP表示------------------------------------------------------------------
			//+
			src.m_top = 1250.0f;
			src.m_left = 375.0f;
			src.m_right = 498.0f;
			src.m_bottom = 1373.0f;

			dst.m_top = FONT_Y + 50.0f;
			dst.m_left = FONT_X + 300.0f;
			dst.m_right = FONT_X + 340.0f;
			dst.m_bottom = FONT_Y + 90.0f;
			Draw::Draw(41, &src, &dst, c[3], 0.0f);

			////百の位
			//src.m_top = 1250.0f;
			//src.m_left =  CUT_ZERO + (floor(m_large / 100) * 125);
			//src.m_right =  END_ZERO + (floor(m_large / 100) * 125);
			//src.m_bottom = 1375.0f;

			//dst.m_top = FONT_Y + 50.0f;
			//dst.m_left = FONT_X + 340.0f;
			//dst.m_right = FONT_X + 360.0f;
			//dst.m_bottom = FONT_Y + 90.0f;
			//Draw::Draw(41, &src, &dst, c[3], 0.0f);

			////十の位
			//src.m_top = 1250.0f;
			//src.m_left =  CUT_ZERO + (floor((m_large / 10) % 10) * 125);
			//src.m_right =  END_ZERO + (floor((m_large / 10) % 10) * 125);
			//src.m_bottom = 1375.0f;

			//dst.m_top = FONT_Y + 50.0f;
			//dst.m_left = FONT_X + 360.0f;
			//dst.m_right = FONT_X + 380.0f;
			//dst.m_bottom = FONT_Y + 90.0f;
			//Draw::Draw(41, &src, &dst, c[3], 0.0f);

			////一の位
			//src.m_top = 1250.0f;
			//src.m_left =  CUT_ZERO + ((m_large % 10) * 125);
			//src.m_right =  END_ZERO + ((m_large % 10) * 125);
			//src.m_bottom = 1375.0f;

			//dst.m_top = FONT_Y + 50.0f;
			//dst.m_left = FONT_X + 380.0f;
			//dst.m_right = FONT_X + 400.0f;
			//dst.m_bottom = FONT_Y + 90.0f;
			//Draw::Draw(41, &src, &dst, c[3], 0.0f);
			FontDraw(NumConversion(m_large), FONT_X + 340, FONT_Y + 48, 20, 40, c[3], false);
			//swprintf_s(str, L"＋%d", m_large);
			//Font::StrDraw(str, FONT_X + 300, FONT_Y + 50, 40, c[3]);
			//--------------------------------------------------------------------------------

			//資材
			src.m_top = 2.0f;
			src.m_left = 2.0f;
			src.m_right = 230.0f;
			src.m_bottom = 110.0f;

			dst.m_top = FONT_Y + 100.0f;
			dst.m_left = FONT_X;
			dst.m_right = FONT_X + 80;
			dst.m_bottom = FONT_Y + 140.0f;
			Draw::Draw(57, &src, &dst, c[4], 0.0f);

			src.m_top = 1250.0f;
			src.m_left = 250.0f;
			src.m_right = 375.0f;
			src.m_bottom = 1375.0f;

			dst.m_top = FONT_Y + 100.0f;
			dst.m_left = FONT_X + 80;
			dst.m_right = FONT_X + 120;
			dst.m_bottom = FONT_Y + 140.0f;
			Draw::Draw(41, &src, &dst, c[4], 0.0f);
			//Font::StrDraw(L"資材：", FONT_X, FONT_Y + 100, 40, c[4]);

			//一つ目の資材名表示------------------------------------------------
			//▼チュートリアル惑星のリザルト時に誤った資材が表示されないように
			if (m_mat_num[0] != 0) {
				//コワモーテ(コワモーテの場合、資材名関係なしに問答無用でこの処理に入る。)
				if (g_Challenge_enemy == 2)
				{
					//▼「全素材」と表示
					src.m_top = 2.0f;
					src.m_left = 0.0f;
					src.m_right = 367.0f;
					src.m_bottom = 117.0f;

					dst.m_top = FONT_Y + 150;
					dst.m_left = FONT_X;
					dst.m_right = FONT_X + 120;
					dst.m_bottom = FONT_Y + 190;
					Draw::Draw(125, &src, &dst, c[4], 0.0f);
				}
				//木材
				else if (m_mat_type[0] == &g_Wood_num)
				{
					src.m_top = 2.0f;
					src.m_left = 0.0f;
					src.m_right = 230.0f;
					src.m_bottom = 112.0f;

					dst.m_top = FONT_Y + 150;
					dst.m_left = FONT_X;
					dst.m_right = FONT_X + 80;
					dst.m_bottom = FONT_Y + 190;
					Draw::Draw(59, &src, &dst, c[4], 0.0f);
				}
				//鉄
				else if (m_mat_type[0] == &g_Iron_num)
				{
					src.m_top = 2.0f;
					src.m_left = 0.0f;
					src.m_right = 110.0f;
					src.m_bottom = 110.0f;

					dst.m_top = FONT_Y + 150;
					dst.m_left = FONT_X;
					dst.m_right = FONT_X + 40;
					dst.m_bottom = FONT_Y + 190;
					Draw::Draw(60, &src, &dst, c[4], 0.0f);
				}
				//銀
				else if (m_mat_type[0] == &g_Silver_num)
				{
					src.m_top = 2.0f;
					src.m_left = 2.0f;
					src.m_right = 112.0f;
					src.m_bottom = 112.0f;

					dst.m_top = FONT_Y + 150;
					dst.m_left = FONT_X;
					dst.m_right = FONT_X + 40;
					dst.m_bottom = FONT_Y + 190;
					Draw::Draw(61, &src, &dst, c[4], 0.0f);
				}
				//プラスチック
				else if (m_mat_type[0] == &g_Plastic_num)
				{
					src.m_top = 2.0f;
					src.m_left = 2.0f;
					src.m_right = 712.0f;
					src.m_bottom = 110.0f;

					dst.m_top = FONT_Y + 150;
					dst.m_left = FONT_X;
					dst.m_right = FONT_X + 240;
					dst.m_bottom = FONT_Y + 190;
					Draw::Draw(62, &src, &dst, c[4], 0.0f);
				}
				//アルミ
				else if (m_mat_type[0] == &g_Aluminum_num)
				{
					src.m_top = 2.0f;
					src.m_left = 0.0f;
					src.m_right = 352.0f;
					src.m_bottom = 112.0f;

					dst.m_top = FONT_Y + 150;
					dst.m_left = FONT_X;
					dst.m_right = FONT_X + 120;
					dst.m_bottom = FONT_Y + 190;
					Draw::Draw(63, &src, &dst, c[4], 0.0f);
				}
				//ガス
				else if (m_mat_type[0] == &g_gus_num)
				{
					src.m_top = 2.0f;
					src.m_left = 0.0f;
					src.m_right = 232.0f;
					src.m_bottom = 112.0f;

					dst.m_top = FONT_Y + 150;
					dst.m_left = FONT_X;
					dst.m_right = FONT_X + 80;
					dst.m_bottom = FONT_Y + 190;
					Draw::Draw(64, &src, &dst, c[4], 0.0f);
				}
			}
			else {
				FontDraw(L"なし", FONT_X, FONT_Y + 150, 40, 40, c[4], false);
			}
			//Font::StrDraw(m_mat_name[0], FONT_X, FONT_Y + 150, 40, c[4]);	//資材名A表示
			//-----------------------------------------------

			//一つ目の資材の個数表示--------------------------
			if (m_mat_num[0] != NULL)//資材数BがNULL(0)の時は描画しない
			{
				//+
				src.m_top = 1250.0f;
				src.m_left = 375.0f;
				src.m_right = 500.0f;
				src.m_bottom = 1375.0f;

				dst.m_top = FONT_Y + 150.0f;
				dst.m_left = FONT_X + 300.0f;
				dst.m_right = FONT_X + 340.0f;
				dst.m_bottom = FONT_Y + 190.0f;
				Draw::Draw(41, &src, &dst, c[4], 0.0f);

				////十の位
				//src.m_top = 1250.0f;
				//src.m_left = CUT_ZERO + (floor(m_mat_num[0] / 10) * 125);
				//src.m_right = END_ZERO + (floor(m_mat_num[0] / 10) * 125);
				//src.m_bottom = 1375.0f;

				//dst.m_top = FONT_Y + 150.0f;
				//dst.m_left = FONT_X + 340.0f;
				//dst.m_right = FONT_X + 360.0f;
				//dst.m_bottom = FONT_Y + 190.0f;
				//Draw::Draw(41, &src, &dst, c[4], 0.0f);

				////一の位
				//src.m_top = 1250.0f;
				//src.m_left = CUT_ZERO + ((m_mat_num[0] % 10) * 125);
				//src.m_right = END_ZERO + ((m_mat_num[0] % 10) * 125);
				//src.m_bottom = 1375.0f;

				//dst.m_top = FONT_Y + 150.0f;
				//dst.m_left = FONT_X + 360.0f;
				//dst.m_right = FONT_X + 380.0f;
				//dst.m_bottom = FONT_Y + 190.0f;
				//Draw::Draw(41, &src, &dst, c[4], 0.0f);
				//swprintf_s(str, L"＋%d個", m_mat_num[0]);
				FontDraw(NumConversion(m_mat_num[0]), FONT_X + 340, FONT_Y + 150, 20, 40, c[4], false);
				//Font::StrDraw(str, FONT_X + 300, FONT_Y + 150, 40, c[4]);		//資材数A表示
			}
			//^------------------------------------------------------------------------
			

			//二つ目の資材名表示-------------------------------------------------------
			//木材
			if (m_mat_type[1] == &g_Wood_num)
			{
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 232.0f;
				src.m_bottom = 112.0f;

				dst.m_top = FONT_Y + 200;
				dst.m_left = FONT_X;
				dst.m_right = FONT_X + 80;
				dst.m_bottom = FONT_Y + 240;
				Draw::Draw(59, &src, &dst, c[4], 0.0f);
			}
			//鉄
			else if (m_mat_type[1] == &g_Iron_num)
			{
				src.m_top = 2.0f;
				src.m_left = 0.0f;
				src.m_right = 110.0f;
				src.m_bottom = 110.0f;

				dst.m_top = FONT_Y + 200;
				dst.m_left = FONT_X;
				dst.m_right = FONT_X + 40;
				dst.m_bottom = FONT_Y + 240;
				Draw::Draw(60, &src, &dst, c[4], 0.0f);
			}
			//銀
			else if (m_mat_type[1] == &g_Silver_num)
			{
				src.m_top = 2.0f;
				src.m_left = 2.0f;
				src.m_right = 112.0f;
				src.m_bottom = 112.0f;

				dst.m_top = FONT_Y + 200;
				dst.m_left = FONT_X;
				dst.m_right = FONT_X + 40;
				dst.m_bottom = FONT_Y + 240;
				Draw::Draw(61, &src, &dst, c[4], 0.0f);
			}
			//プラスチック
			else if (m_mat_type[1] == &g_Plastic_num)
			{
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 712.0f;
				src.m_bottom = 112.0f;

				dst.m_top = FONT_Y + 200;
				dst.m_left = FONT_X;
				dst.m_right = FONT_X + 240;
				dst.m_bottom = FONT_Y + 240;
				Draw::Draw(62, &src, &dst, c[4], 0.0f);
			}
			//アルミ
			else if (m_mat_type[1] == &g_Aluminum_num)
			{
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 350.0f;
				src.m_bottom = 112.0f;

				dst.m_top = FONT_Y + 200;
				dst.m_left = FONT_X;
				dst.m_right = FONT_X + 120;
				dst.m_bottom = FONT_Y + 240;
				Draw::Draw(63, &src, &dst, c[4], 0.0f);
			}
			//ガス
			else if (m_mat_type[1] == &g_gus_num)
			{
				src.m_top = 2.0f;
				src.m_left = 0.0f;
				src.m_right = 232.0f;
				src.m_bottom = 112.0f;

				dst.m_top = FONT_Y + 200;
				dst.m_left = FONT_X;
				dst.m_right = FONT_X + 80;
				dst.m_bottom = FONT_Y + 240;
				Draw::Draw(64, &src, &dst, c[4], 0.0f);
			}
			//Font::StrDraw(m_mat_name[1], FONT_X, FONT_Y + 200, 40, c[4]);	//資材名B表示
			//---------------------------------------------------------------

			if (m_mat_num[1] != NULL)//資材数BがNULL(0)の時は描画しない
			{
				//+
				src.m_top = 1252.0f;
				src.m_left = 375.0f;
				src.m_right = 500.0f;
				src.m_bottom = 1375.0f;

				dst.m_top = FONT_Y + 200.0f;
				dst.m_left = FONT_X + 300.0f;
				dst.m_right = FONT_X + 340.0f;
				dst.m_bottom = FONT_Y + 240.0f;
				Draw::Draw(41, &src, &dst, c[4], 0.0f);

				////十の位
				//src.m_top = 1250.0f;
				//src.m_left =  CUT_ZERO + (floor(m_mat_num[1] / 10) * 125);
				//src.m_right =  END_ZERO + (floor(m_mat_num[1] / 10) * 125);
				//src.m_bottom = 1375.0f;

				//dst.m_top = FONT_Y + 200.0f;
				//dst.m_left = FONT_X + 340.0f;
				//dst.m_right = FONT_X + 360.0f;
				//dst.m_bottom = FONT_Y + 240.0f;
				//Draw::Draw(41, &src, &dst, c[4], 0.0f);

				////一の位
				//src.m_top = 1250.0f;
				//src.m_left =  CUT_ZERO + ((m_mat_num[1] % 10) * 125);
				//src.m_right =  END_ZERO + ((m_mat_num[1] % 10) * 125);
				//src.m_bottom = 1375.0f;

				//dst.m_top = FONT_Y + 200.0f;
				//dst.m_left = FONT_X + 360.0f;
				//dst.m_right = FONT_X + 380.0f;
				//dst.m_bottom = FONT_Y + 240.0f;
				//Draw::Draw(41, &src, &dst, c[4], 0.0f);
				//swprintf_s(str, L"＋%d個", m_mat_num[1]);
				FontDraw(NumConversion(m_mat_num[1]), FONT_X + 340, FONT_Y + 200, 20, 40, c[4], false);
				//Font::StrDraw(str, FONT_X + 300, FONT_Y + 200, 40, c[4]);	//資材数B表示
			}


			//スペシャル技
			if (m_skill != 0)
			{
				//スペシャル技
				src.m_top = 2.0f;
				src.m_left = 0.0f;
				src.m_right = 712.0f;
				src.m_bottom = 110.0f;

				dst.m_top = FONT_Y + 250.0f;
				dst.m_left = FONT_X;
				dst.m_right = FONT_X+ (6 * 40.0f);
				dst.m_bottom = FONT_Y + 288.0f;
				Draw::Draw(54, &src, &dst, c[5], 0.0f);

				//コロン
				src.m_top = 1250.0f;
				src.m_left = 250.0f;
				src.m_right = 375.0f;
				src.m_bottom = 1375.0f;

				dst.m_top = FONT_Y + 250.0f;
				dst.m_left = FONT_X + (6 * 40.0f);
				dst.m_right = FONT_X + (7 * 40.0f);
				dst.m_bottom = FONT_Y + 288.0f;
				Draw::Draw(41, &src, &dst, c[5], 0.0f);
			//	Font::StrDraw(L"スペシャル技：", FONT_X, FONT_Y + 250, 40, c[5]);

				switch (m_skill)
				{
				case 1:
					//エクスプロージョン
					src.m_top = 2.0f;
					src.m_left = 2.0f;
					src.m_right = 1072.0f;
					src.m_bottom = 112.0f;

					dst.m_top = FONT_Y + 250.0f;
					dst.m_left = FONT_X + 300.0f;
					dst.m_right = FONT_X + 300.0f + (9 * 40.0f);
					dst.m_bottom = FONT_Y + 288.0f;
					Draw::Draw(45, &src, &dst, c[5], 0.0f);
					break;
					//Font::StrDraw(L"Explosion GET!",			FONT_X + 300, FONT_Y + 250, 40, c[5]); break;
				case 2:
					//フラクチャーレイ
					src.m_top = 2.0f;
					src.m_left = 2.0f;
					src.m_right = 952.0f;
					src.m_bottom = 110.0f;

					dst.m_top = FONT_Y + 250.0f;
					dst.m_left = FONT_X + 300.0f;
					dst.m_right = FONT_X + 300.0f + (8 * 40.0f);
					dst.m_bottom = FONT_Y + 288.0f;
					Draw::Draw(46, &src, &dst, c[5], 0.0f);
					break;
					//Font::StrDraw(L"Fracture Ray GET!",		FONT_X + 300, FONT_Y + 250, 40, c[5]); break;
				case 3:
					//イモータリティ
					src.m_top = 2.0f;
					src.m_left = 2.0f;
					src.m_right = 817.0f;
					src.m_bottom = 112.0f;

					dst.m_top = FONT_Y + 250.0f;
					dst.m_left = FONT_X + 300.0f;
					dst.m_right = FONT_X + 300.0f + (7 * 40.0f);
					dst.m_bottom = FONT_Y + 288.0f;
					Draw::Draw(47, &src, &dst, c[5], 0.0f);
					break;
					//Font::StrDraw(L"Immortality GET!",		FONT_X + 300, FONT_Y + 250, 40, c[5]); break;
				case 4:
					//オーバーワーク
					src.m_top = 2.0f;
					src.m_left = 2.0f;
					src.m_right = 830.0f;
					src.m_bottom = 112.0f;

					dst.m_top = FONT_Y + 250.0f;
					dst.m_left = FONT_X + 300.0f;
					dst.m_right = FONT_X + 300.0f + (7 * 40.0f);
					dst.m_bottom = FONT_Y + 288.0f;
					Draw::Draw(48, &src, &dst, c[5], 0.0f);
					break;
					//Font::StrDraw(L"リミットブレイク GET!",	FONT_X + 300, FONT_Y + 250, 40, c[5]); break;
				case 5:
					//リミットブレイク
					src.m_top = 2.0f;
					src.m_left = 2.0f;
					src.m_right = 952.0f;
					src.m_bottom = 110.0f;

					dst.m_top = FONT_Y + 250.0f;
					dst.m_left = FONT_X + 300.0f;
					dst.m_right = FONT_X + 300.0f + (8 * 40.0f);
					dst.m_bottom = FONT_Y + 288.0f;
					Draw::Draw(49, &src, &dst, c[5], 0.0f);
					break;
					//Font::StrDraw(L"ステロイド投与 GET!",	FONT_X + 300, FONT_Y + 250, 40, c[5]); break;
				default: 
					break;
				}
			}

			//▼ランク表示
			FontDraw(L"ランク",1000.0f,240.0f,35.0f,35.0f,c[6],false);
			
			CObjPlanet* player = (CObjPlanet*)Objs::GetObj(OBJ_PLANET);
			//Ｓランク(HPが満タン)
			if (player->GetRank_size() == 1.0f)
			{
				c[6][1] = 1.0f;//Ｓの文字を黄色に変更

				FontDraw(L"Ｓ", 1022.0f, 290.0f, 60.0f, 60.0f, c[6], false);
			}
			//Ａランク(HPが66%以上)
			else if (player->GetRank_size() >= 0.66f)
			{
				FontDraw(L"Ａ", 1022.0f, 290.0f, 60.0f, 60.0f, c[6], false);

				g_no_damage_clear_f = false;//全ステージのノーダメージクリアを出来なかったと記録する
			}
			//Ｂランク(HPが33%以上)
			else if (player->GetRank_size() >= 0.33f)
			{
				FontDraw(L"Ｂ", 1022.0f, 290.0f, 60.0f, 60.0f, c[6], false);

				g_no_damage_clear_f = false;//全ステージのノーダメージクリアを出来なかったと記録する
			}
			//Ｃランク(HPが33%未満)
			else
			{
				FontDraw(L"Ｃ", 1022.0f, 290.0f, 60.0f, 60.0f, c[6], false);

				g_no_damage_clear_f = false;//全ステージのノーダメージクリアを出来なかったと記録する
			}


			//▼クリック催促フォント表示
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 1192.0f;
			src.m_bottom = 117.0f;

			dst.m_top = 600.0f;
			dst.m_left = 375.0f;
			dst.m_right = 875.0f;
			dst.m_bottom = 650.0f;
			Draw::Draw(52, &src, &dst, c0, 0.0f);
		}
		//シーン移行演出後に表示するグラフィック
		//※ホーム画面に移行したように見せるグラフィック
		else //(m_scene_migration_f == true)
		{
			//▼背景表示
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 1200.0f;
			src.m_bottom = 700.0f;

			dst.m_top = 0.0f;
			dst.m_left = 0.0f;
			dst.m_right = 1200.0f;
			dst.m_bottom = 700.0f;
			Draw::Draw(0, &src, &dst, d, 0.0f);

			//▼プレイヤー惑星表示
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 448.0f;
			src.m_bottom = 448.0f;

			dst.m_top = 250.0f;
			dst.m_left = 450.0f;
			dst.m_right = 750.0f;
			dst.m_bottom = 550.0f;
			Draw::Draw(3 + ((int)((g_Bar_Level + g_Ins_Level) / 2)) - 1, &src, &dst, d, 0.0f);
		}
	}
	//▽ゲームクリア時の処理
	else
	{
		//▼ゲームクリアメッセージ表示
		//Font::StrDraw(L"CONGRATULATIONS!!", 180, 50, 100, clear[0]);
		//Font::StrDraw(L"すべての惑星を捕食した", 200, 250, 70, clear[1]);
		//Font::StrDraw(L"この銀河のトップに君臨した", 130, 350, 70, clear[2]);

		//▼クリック催促フォント表示
		//Font::StrDraw(L"クリックで進む", 400, 600, 50, c0);
	}


	//▽上記のどちらの処理でも使用(描画)するもの
	//▼画面全体暗転用画像表示
	//※blackoutの透過度の値で「表示/非表示」が切り替えられる
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1200.0f;
	src.m_bottom = 700.0f;

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 1200.0f;
	dst.m_bottom = 700.0f;
	Draw::Draw(20, &src, &dst, blackout, 0.0f);


	//ゲームクリア時のみ表示
	if (g_tutorial_progress == 31)
	{
		//▼ThankYou
		src.m_top = 0.0f;
		src.m_left = 2.0f;
		src.m_right = 500.0f;
		src.m_bottom = 84.0f;

		dst.m_top = 25.0f;
		dst.m_left = 325.0f;
		dst.m_right = 875.0f;
		dst.m_bottom = 100.0f;
		Draw::Draw(187, &src, &dst, clear, 0.0f);

		//▼for
		src.m_top = 0.0f;
		src.m_left = 505.0f;
		src.m_right = 650.0f;
		src.m_bottom = 84.0f;

		dst.m_top = 150.0f;
		dst.m_left = 530.0f;
		dst.m_right = 690.0f;
		dst.m_bottom = 225.0f;
		Draw::Draw(187, &src, &dst, clear, 0.0f);

		//▼Playing!!!
		src.m_top = 0.0f;
		src.m_left = 655.0f;
		src.m_right = 1080.0f;
		src.m_bottom = 84.0f;

		dst.m_top = 275.0f;
		dst.m_left = 350.0f;
		dst.m_right = 850.0f;
		dst.m_bottom = 350.0f;
		Draw::Draw(187, &src, &dst, clear, 0.0f);

		//▼このゲームを遊んでくれてありがとうございます文字画像
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1140.0f;
		src.m_bottom = 214.0f;

		dst.m_top = 410.0f;
		dst.m_left = 100.0f;
		dst.m_right = 1100.0f;
		dst.m_bottom = 670.0f;
		Draw::Draw(188, &src, &dst, clear, 0.0f);
	}	
}


