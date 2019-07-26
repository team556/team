//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "Call_Planet.h"
#include "UtilityModule.h"

#include <stdlib.h>
#include <time.h>

//使用するネームスペース
using namespace GameL;

//マクロ
//▼開始時間をずらす事で惑星の出現タイミングを均等にする。
#define ENEMY_PLANET1_START_TIME (1300) //敵惑星1(背景)の開始時間
#define ENEMY_PLANET2_START_TIME (800)  //敵惑星2(背景)の開始時間
#define ENEMY_PLANET3_START_TIME (300)  //敵惑星3(背景)の開始時間
#define INI_ALPHA (1.0f) //透過度(アルファ値)の初期値
#define INI_COLOR (0.9f) //透過度(アルファ値)の初期値

//static変数の定義
bool CObjTitle::after_once = false;

//全てのグローバル変数の定義
//※ObjTitleでは、グローバル変数の定義と同時に
//イニシャライズでリセット処理も行っている為、
//初期値を変更等する際は、
//こことリセット処理の2つを変更しないといけないので注意。
//※余裕あれば、値の部分をマクロ化(出来る部分は)して便利にすべし。
int g_Stage_progress = 1;
bool g_destroy_progress[4] = { false,false,false,false };//敵の撃破状態
int g_Bar_Level = 1;
int g_Ins_Level = 1;
int g_Mis_Recast_Level		= 1;
int g_Pow_equip_Level		= 1;
int g_Pow_equip_Lv_achieve	= 1;
int g_Def_equip_Level		= 1;
int g_Def_equip_Lv_achieve	= 1;
int g_Spe_equip_Level		= 1;
int g_Spe_equip_Lv_achieve	= 1;
int g_Bal_equip_Level		= 1;
int g_Bal_equip_Lv_achieve	= 1;
int g_Pod_equip_Level		= 1;
int g_Pod_equip_Lv_achieve	= 1;
float g_Player_max_size = 100.0f;//100.0f;
int g_Special_equipment = 0;//装備中のスペシャル技
bool g_Special_mastering[5] = { false,false,false,true,false };//スペシャル技の習得状態
int g_Power_num		= 3000;
int g_Defense_num	= 3000;
int g_Speed_num		= 3000;
int g_Balance_num	= 3000;
int g_Research_num	=  500;
int g_Remain_num	= 0;
float g_Recast_time = 3.0f;
float g_P_Planet_damage = 0.0f;

int g_Iron_num		= 0;
int g_Wood_num		= 0;
int g_Silver_num	= 0;
int g_Plastic_num	= 0;
int g_Aluminum_num	= 0;
int g_gus_num		= 0;

int g_Challenge_enemy = 0;//デバッグ。0に戻すべし。
bool g_help_f = false;
int  g_tutorial_progress = 8;//デバッグ。チュートリアル完成後、0にするように。
bool g_is_operatable = true;

//イニシャライズ
void CObjTitle::Init()
{
	m_click_vy = 0.0f;	
	m_r = 0.0f;

	m_Ey[3] = {};//全ての要素の値を0で初期化している
	m_time[0] = ENEMY_PLANET1_START_TIME;
	m_time[1] = ENEMY_PLANET2_START_TIME;
	m_time[2] = ENEMY_PLANET3_START_TIME;
	m_Enemy_id = 0;
	m_Planet_id = 0;
	m_speed = 0;

	m_Yes_Button_color = 1.0f;
	m_No_Button_color = 1.0f;
	m_del_color = INI_COLOR;
	m_del_alpha = 0.0f;
	m_del_f = false;

	m_flag  = false;
	m_key_f = false;
	m_alpha = INI_ALPHA;

	//▼二回目以降訪れた時の演出
	//「画面暗転状態→明転する」
	//二回目以降はこの演出をしたい為、
	//初回かそうでないかで
	//初期値を変更する。
	//▽二回目以降
	if (after_once == true)
	{
		m_black_out_a = INI_ALPHA;
	}
	//▽初回
	else
	{
		m_black_out_a = 0.0f;
	}

	m_des_y = 200.0f;
	m_des_vec = 1.0f;
	m_des_a = 0.0f;

	m_mou_x = 0.0f;
	m_mou_y = 0.0f;
	m_mou_r = false;
	m_mou_l = false;

	srand(time(NULL));//ランダム情報を初期化


	//▼グローバル変数(全保存データ)リセット処理
	g_Stage_progress = 1;

	for (int i = 0; i < 4; i++)
	{
		g_destroy_progress[i] = true;
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
	g_Player_max_size = 100.0f;
	g_Special_equipment = 0;

	for (int i = 0; i < 5 && i != 3; i++)
	{
		g_Special_mastering[i] = false;
	}

	g_Power_num		= 1500;
	g_Defense_num	= 1500;
	g_Speed_num		= 1500;
	g_Balance_num	= 1500;
	g_Research_num	= 0;
	g_Remain_num	= 0;

	g_Iron_num		= 0;
	g_Wood_num		= 0;
	g_Silver_num	= 0;
	g_Plastic_num	= 0;
	g_Aluminum_num	= 0;
	g_gus_num		= 0;
}

//アクション
void CObjTitle::Action()
{
	//マウスの位置を取得
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//マウスのボタンの状態
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	//▼キーフラグ
	//※左クリックを制御している
	if (m_mou_l == false)
	{
		m_key_f = true;//キーフラグON(ONの時に左クリック出来る)
	}

	//▼データ消去最終確認ウインドウ表示時の処理
	if (m_del_f == true)
	{
		//最終確認[はい]ボタン
		if (410 < m_mou_x && m_mou_x < 502 && 407 < m_mou_y && m_mou_y < 450)
		{
			m_Yes_Button_color = 0.0f;

			//▼クリックされたらデータ消去し、このウインドウを閉じる
			//左クリック入力時
			if (m_mou_l == true)
			{
				//左クリック押したままの状態では入力出来ないようにしている
				if (m_key_f == true)
				{
					m_key_f = false;

					//▼ここに消去したい処理等を書く(これで足りてるか、デバッグで確かめたい。)
					g_tutorial_progress = 0;//チュートリアル進行度を初期化
					after_once = false;		//二回目以降か記憶してる変数を初期化


					m_Yes_Button_color = 1.0f;

					m_del_alpha = 1.5f;//データ消去完了通知画像を表示する

					//最終確認ウインドウを非表示にする
					m_del_f = false;

					//データを食べる音
					Audio::Start(3);
				}
			}
		}
		else
		{
			m_Yes_Button_color = 1.0f;
		}

		//最終確認[いいえ]ボタン
		if (648 < m_mou_x && m_mou_x < 789 && 407 < m_mou_y && m_mou_y < 450 || m_mou_r == true)
		{
			m_No_Button_color = 0.0f;

			//▼クリックされたら、このウインドウを閉じる
			//右クリック入力時
			if (m_mou_r == true)
			{
				m_No_Button_color = 1.0f;

				//最終確認ウインドウを非表示にする
				m_del_f = false;

				//戻るボタン音
				Audio::Start(2);
			}
			//左クリック入力時
			else if (m_mou_l == true)
			{
				//左クリック押したままの状態では入力出来ないようにしている
				if (m_key_f == true)
				{
					m_key_f = false;

					m_No_Button_color = 1.0f;

					//最終確認ウインドウを非表示にする
					m_del_f = false;

					//戻るボタン音
					Audio::Start(2);
				}
			}
		}
		else
		{
			m_No_Button_color = 1.0f;
		}


		return;
	}


	
	//左クリックもしくは右クリックでホーム画面へシーン移行(初回時の処理)
	if (m_flag == true && after_once == false)
	{
		//下から上に順に実行されていく

		/*if ()
		{
			名前入力のグローバル変数に何かしら入力されたのを確認(!= nullptr)、
			もしくは何か名前入力側から情報を送ってもらい、それを条件文に入れる。

			その後、この条件文の中で
			チュートリアルをスキップするかしないかを最終確認ウインドウのヤツで聞く。

			確認後、スキップしない処理、スキップする処理に分岐し、
			値とかいろいろ入れた後に
			m_black_out_a -= 0.01f;//画面徐々に明転
			を実行し、完全明転後、以下の処理を実行する。
			//after_once = true;//「一度タイトル画面を訪れた」と記憶

			//Scene::SetScene(new CSceneHome());//ホーム画面へシーン移行
		}
		else */if (m_alpha == 0.0f)
		{
			//名前入力中はObjTitleでは何も動作させない。
		}
		else if (m_des_y <= -550.0f)
		{
			//名前入力のオブジェクトを呼び出す

			m_alpha = 0.0f;//タイトルロゴ、後ろ敵惑星等を非表示にすると同時に次の処理へのフラグとしている。
			Scene::SetScene(new CSceneNameInput());
		}
		else if (m_des_a > 6.0f)
		{
			//世界観説明全て表示から少し経った後、
			//その全て表示した説明を画面外の上の方に移動させる。
			m_des_vec *= 1.01f;
			m_des_y -= m_des_vec;

			//クリックで移動速度上昇
			if (m_mou_l == true)
			{
				m_des_y -= m_des_vec * 10;
			}
		}
		else if (m_black_out_a > 1.2f)
		{
			m_des_a += 0.01f;//暗転後、徐々に世界観説明を表示していく。

			//クリックで表示速度上昇
			if (m_mou_l == true)
			{
				m_des_a += 0.05f;
			}
		}
		else
		{
			m_black_out_a += 0.01f;//画面徐々に暗転
		}

		return;
	}
	//左クリックもしくは右クリックでホーム画面へシーン移行(二回目以降の処理)
	else if (m_flag == true)
	{
		m_alpha -= 0.01f;

		if (m_alpha <= 0.0f)
		{
			Scene::SetScene(new CSceneHome());//ホーム画面へシーン移行
		}

		return;
	}
	
	//データ消去ボタン
	if (20 < m_mou_x && m_mou_x < 120 && 20 < m_mou_y && m_mou_y < 120)
	{
		m_del_color = 1.0f;

		if (m_mou_l == true && m_key_f == true)
		{
			m_del_f = true;//最終確認ウインドウを表示

			m_del_alpha = 0.0f;//データ消去完了通知画像を非表示

			m_del_color = INI_COLOR;

			//選択ボタン音
			Audio::Start(1);

			return;
		}
	}
	//データ消去ボタン以外の場所を左クリックするとシーン移行処理を行う。
	else if (m_mou_l == true && m_key_f == true)
	{
		m_del_color = INI_COLOR;

		m_key_f = false;//キーフラグOFF

		m_flag = true;//シーン移行処理フラグON

		//選択音
		Audio::Start(1);
	}
	else
	{
		m_del_color = INI_COLOR;
	}

	//画面暗転状態の場合、明転する処理
	if (m_black_out_a >= 0.0f)
	{
		m_black_out_a -= 0.01f;
	}

	//データ消去完了通知画像表示時、透過度を下げて非表示にする処理
	if (m_del_alpha >= 0.0f)
	{
		m_del_alpha -= 0.01f;
	}

	//Zキーを押している間、敵惑星(背景)の移動速度が速くなる(デバッグ用)
	//元々はデバッグのみの使用だったが、隠し要素という感じで残しておいても良いかも。
	if (Input::GetVKey('Z') == true)
	{
		m_speed = 10;
	}
	else
	{
		m_speed = 0;
	}
}

//ドロー
void CObjTitle::Draw()
{
	//描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	//動かない画像用[シーン移行時も消えない]
	float d[4] = { 1.0f,1.0f,1.0f,1.0f };

	//白＆動く画像用(クリックでスタート、敵惑星)[シーン移行時フェードアウト]
	float w[4] = { 1.0f,1.0f,1.0f,m_alpha };

	//黄色(☆育喰)[シーン移行時フェードアウト]
	float y[4] = { 1.0f,1.0f,0.0f,m_alpha };

	//赤色
	float red[4] = { 1.0f,0.0f,0.0f,1.0f };

	//データ消去完了通知画像用
	float notify[4] = { 1.0f,0.0f,0.0f,m_del_alpha };

	//データ消去ボタン用
	float Delete[4] = { m_del_color,m_del_color,m_del_color,m_alpha };
	
	//最終確認[はい]ボタン用
	float Yes[4] = { 1.0f,m_Yes_Button_color,m_Yes_Button_color,1.0f };

	//最終確認[いいえ]ボタン用
	float No[4] = { m_No_Button_color,m_No_Button_color,1.0f,1.0f };

	//画面全体暗転画像用
	float blackout[4] = { 1.0f,1.0f,1.0f,m_black_out_a };	

	//世界観説明フォント画像用
	float description[4][4] =
	{
		{ 1.0f,1.0f,1.0f,m_des_a },			//フォント色は全て白色
		{ 1.0f,1.0f,1.0f,m_des_a - 1.5f },
		{ 1.0f,1.0f,1.0f,m_des_a - 3.0f },
		{ 1.0f,1.0f,1.0f,m_des_a - 4.5f },
	};

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置


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


	//▼敵惑星(背景)表示
	//1500に到達するまで、それぞれ4ずつ加算されていく。
	//Zキーを押すと加算量が上昇する
	m_time[0] += 4 + m_speed;
	m_time[1] += 4 + m_speed;
	m_time[2] += 4 + m_speed;

	//m_timeが1500に到達すると、以下の処理が実行される。
	//敵惑星(背景)の開始時間の差により、
	//必ず敵惑星1→2→3→1→……の順に、この処理に入るようにしている。
	if (m_time[m_Enemy_id] >= 1500)
	{
		m_time[m_Enemy_id] = 0;//この処理に入ってきたm_timeを0に戻す。

		m_Planet_id = rand() % 4 + 1;//1～4の値をランダム取得し、以下の関数で利用する。

		//惑星グラフィックを取得する関数(Call_Planet)を呼び出す。
		//引数1にこの処理に入ってきた敵惑星の識別番号を入れ、
		//引数2に先程取得した1～4のランダム値を入れる事で、
		//それぞれの敵惑星に適応したランダムな惑星データを取得している。
		Call_Planet(m_Enemy_id, m_Planet_id);

		m_Ey[m_Enemy_id] = rand() % 501 + 100;//100～600の値をランダム取得し、敵惑星(背景)のY座標とする。

		//次の敵惑星の処理を行う為に、idを次の敵惑星のものにしておく。
		if (m_Enemy_id == 2)
		{
			m_Enemy_id = 0;
		}
		else
		{
			m_Enemy_id++;
		}
	}

	//敵惑星1(背景)表示
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 287.0f;
	src.m_bottom = 287.0f;

	dst.m_top = m_Ey[0];
	dst.m_left = 1200.0f - m_time[0];//+4ずつ増加し続ける変数を引く事で、
	dst.m_right = 1250.0f - m_time[0];//グラフィックを右から左へ移動させている。
	dst.m_bottom = m_Ey[0] + 50.0f;
	Draw::Draw(20, &src, &dst, w, 0.0f);

	//敵惑星2(背景)表示
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 287.0f;
	src.m_bottom = 287.0f;

	dst.m_top = m_Ey[1];
	dst.m_left = 1200.0f - m_time[1];//+4ずつ増加し続ける変数を引く事で、
	dst.m_right = 1250.0f - m_time[1];//グラフィックを右から左へ移動させている。
	dst.m_bottom = m_Ey[1] + 50.0f;
	Draw::Draw(22, &src, &dst, w, 0.0f);

	//敵惑星3(背景)表示
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 287.0f;
	src.m_bottom = 287.0f;

	dst.m_top = m_Ey[2];
	dst.m_left = 1200.0f - m_time[2];//+4ずつ増加し続ける変数を引く事で、
	dst.m_right = 1250.0f - m_time[2];//グラフィックを右から左へ移動させている。
	dst.m_bottom = m_Ey[2] + 50.0f;
	Draw::Draw(24, &src, &dst, w, 0.0f);

	//▼プレイヤー惑星表示
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 448.0f;
	src.m_bottom = 448.0f;

	dst.m_top = 250.0f;
	dst.m_left = 450.0f;
	dst.m_right = 750.0f;
	dst.m_bottom = 550.0f;
	Draw::Draw(50, &src, &dst, d, 0.0f);
	//Draw::Draw(50 + ((int)((g_Bar_Level + g_Ins_Level) / 2)) - 1, &src, &dst, d, 0.0f);

	//▼上下ふわふわする"クリックでスタート"を表示
	//角度加算
	m_r += 2.0f;

	//360°で初期値に戻す
	if (m_r > 360.0f)
		m_r = 0.0f;

	//移動方向
	m_click_vy = sin(3.14f / 90 * m_r);

	//速度付ける。
	m_click_vy *= 10.0f;

	//クリックでスタート文字画像を表示
	src.m_top    =   0.0f;
	src.m_left   =   0.0f;
	src.m_right  = 373.0f;
	src.m_bottom =  41.0f;

	dst.m_top    = 600.0f + m_click_vy;
	dst.m_left   = 450.0f;
	dst.m_right  = 823.0f;
	dst.m_bottom = 641.0f + m_click_vy;
	Draw::Draw(53, &src, &dst, w, 0.0f);

	//タイトルロゴ描画
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1557.0f;
	src.m_bottom = 929.0f;

	dst.m_top = 0.0f;
	dst.m_left = 350.0f;
	dst.m_right = 851.0f;
	dst.m_bottom = 280.0f;
	Draw::Draw(1, &src, &dst, w, 0.0f);

	//データ消去ボタン表示
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 522.0f;
	src.m_bottom = 390.0f;

	dst.m_top = 20.0f;
	dst.m_left = 20.0f;
	dst.m_right = 120.0f;
	dst.m_bottom = 120.0f;
	Draw::Draw(54, &src, &dst, Delete, 0.0f);

	//データ消去完了フォント画像表示
	FontDraw(L"データ消去完了", m_mou_x - 122.5f, m_mou_y - 40.0f, 35.0f, 35.0f, notify, false);

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
	Draw::Draw(2, &src, &dst, blackout, 0.0f);

	//世界観説明フォント画像表示
	FontDraw(L"意思を持つ惑星達が互いの生存をかけて喰らい合う弱肉強食の宇宙……。", 35.0f, m_des_y, 35.0f, 35.0f, description[0], false);
	FontDraw(L"喰うか喰われるか――", 35.0f, m_des_y + 100.0f, 35.0f, 35.0f, description[1], false);
	FontDraw(L"そんな宇宙で生まれたての惑星がいた。", 35.0f, m_des_y + 200.0f, 35.0f, 35.0f, description[2], false);
	FontDraw(L"その惑星の名は……？", 35.0f, m_des_y + 300.0f, 35.0f, 35.0f, description[3], false);


	//▼データ消去最終確認ウインドウ表示管理フラグがtrueの時、描画。
	if (m_del_f == true)
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
		Draw::Draw(57, &src, &dst, d, 0.0f);

		//データを消去しますか？
		FontDraw(L"データを消去しますか？", 360.0f, 250.0f, 45.0f, 45.0f, red, false);

		//▼はい文字画像表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 232.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 410.0f;
		dst.m_left = 410.0f;
		dst.m_right = 510.0f;
		dst.m_bottom = 460.0f;
		Draw::Draw(55, &src, &dst, Yes, 0.0f);

		//▼いいえ文字画像表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 352.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 410.0f;
		dst.m_left = 650.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 460.0f;
		Draw::Draw(56, &src, &dst, No, 0.0f);
	}


	//デバッグ用仮マウス位置表示
	//wchar_t str[256];
	//swprintf_s(str, L"x=%f,y=%f", m_mou_x, m_mou_y);
	//Font::StrDraw(str, 20.0f, 20.0f, 12.0f, d);
}
