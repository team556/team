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
#define INI_ALPHA (0.0f) //透過度(アルファ値)の初期値
#define INI_COLOR (0.9f) //全カラー明度の初期値(アイコン未選択中のカラー)

//イニシャライズ
void CObjHome::Init()
{
	m_Pvx = 0.0f;	
	m_Pvy = 0.0f;
	m_boost = 0.0f;
	m_rx = 0.0f;
	m_ry = 0.0f;
	m_size = 0.0f;

	m_Mig_time = 0;

	m_Ey[3] = {};//全ての要素の値を0で初期化している
	m_time[0] = ENEMY_PLANET1_START_TIME;
	m_time[1] = ENEMY_PLANET2_START_TIME;
	m_time[2] = ENEMY_PLANET3_START_TIME;
	m_Enemy_id = 0;
	m_Planet_id = 0;
	m_speed = 0;

	m_Tra_move = 0.0f;
	m_Eat_move = 0.0f;
	m_Tra_color = INI_COLOR;
	m_Eat_color = INI_COLOR;
	m_alpha = INI_ALPHA;
	m_Tra_flag = false;
	m_Eat_flag = false;
	m_status_flag = false;

	m_special_clip_right = 0.0f;
	m_special_clip_bottom = 0.0f;
	m_special_draw_left = 0.0f;
	m_special_draw_right = 0.0f;

	m_mou_x = 0.0f;
	m_mou_y = 0.0f;
	m_mou_r = false;
	m_mou_l = false;

	m_key_f = false;

	srand(time(NULL));//ランダム情報を初期化
}

//アクション
void CObjHome::Action()
{
	//チュートリアル中は操作を受け付けないようにする。
	if (g_is_operatable == false)
	{
		return;
	}

	//育アイコン、もしくは喰アイコンクリック時実行
	if (m_Tra_flag == true || m_Eat_flag == true)
	{
		//▼育アイコンクリック処理
		if (m_Tra_flag == true)
		{
			//プレイヤー惑星を拡大、育喰アイコンをそれぞれ画面外へ移動させるズーム演出、
			//雲が画面全体を覆い隠す処理を同時に行う。
			if (m_size >= 2000.0f)
			{
				//雲が画面全体を完全に覆い隠したタイミング(m_sizeが2000.0f以上)で上記の処理を終了し、
				//同時にm_Mig_timeを作動させ、約0.5秒後(m_Mig_timeが20より上)にシーン移行を行う
				m_Mig_time++;

				if (m_Mig_time > 20)
				{
					Scene::SetScene(new CSceneTraining());//育成画面へシーン移行
				}
			}
			//雲演出オブジェクトを複数生成しないための条件分岐
			else if (m_size > 0.0f)
			{
				m_size += 20.0f;
				m_Tra_move += 5.0f;
				m_Eat_move += 5.0f;
			}
			else
			{
				m_size += 20.0f;
				m_Tra_move += 5.0f;
				m_Eat_move += 5.0f;

				//雲演出オブジェクト(雲演出IN)
				CObjCloud_Effect* obj_cloud = new CObjCloud_Effect(true);	//雲演出オブジェクト作成
				Objs::InsertObj(obj_cloud, OBJ_CLOUD, 100);					//雲演出オブジェクト登録
			}
		}
		//▼喰アイコンクリック処理
		else //(m_Eat_flag == true)
		{
			//育喰アイコン、敵惑星(背景)を徐々に非表示にする
			if (m_alpha > 0.0f)
			{
				m_alpha -= 0.01f;
			}

			//プレイヤー惑星移動演出
			if (m_Pvx < -750.0f)
			{
				//画面外に出たため、移動を停止させる
				//その後m_Mig_timeを作動させ、約1秒後(m_Mig_timeが60より上)にシーン移行を行う
				m_Mig_time++;

				if (m_Mig_time > 60)
				{
					Scene::SetScene(new CScenePreparation());//戦闘準備画面へシーン移行
				}
			}
			else //画面内にいるため、移動を行う
			{
				//▼プレイヤー惑星X移動処理
				//角度加算
				m_rx += 1.0f;

				//360°で初期値に戻す
				if (m_rx > 360.0f)
					m_rx = 0.0f;

				//移動方向
				m_Pvx = sin(3.14f / 90 * m_rx);

				//速度付ける。
				m_Pvx *= 80.0f + m_boost;

				//X移動速度を移動ベクトルXの状況に応じて増加させる
				if (m_Pvx < 0.0f)
				{
					m_boost += 24.0f;
				}
				else
				{
					m_boost += 6.0f;
				}


				//▼プレイヤー惑星Y移動処理
				//角度加算
				m_ry += 2.0f;

				//360°で初期値に戻す
				if (m_ry > 360.0f)
					m_ry = 0.0f;

				//移動方向
				m_Pvy = sin(3.14f / 90 * m_ry);

				//速度付ける。
				m_Pvy *= 80.0f;
			}
		}

		return;
	}


	//マウスの位置を取得
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//マウスのボタンの状態
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	//育喰アイコン、敵惑星(背景)を徐々に表示させる
	if (m_alpha < 1.0f && (g_tutorial_progress == 1 || g_tutorial_progress >= 8))
	{
		m_alpha += 0.01f;
	}

	//育アイコン
	if (20 < m_mou_x && m_mou_x < 220 && 480 < m_mou_y && m_mou_y < 680 && (g_tutorial_progress >= 8))
	{
		m_Tra_color = 1.0f;

		//左クリックされたらフラグを立て、育成画面へ演出を交えながらシーン移行
		if (m_mou_l == true)
		{
			//クリック押したままの状態では入力出来ないようにしている
			if (m_key_f == true)
			{
				m_key_f = false;

				m_Tra_flag = true;

				//ObjHelpにシーン移行演出を伝える
				//CObjHelp* help = (CObjHelp*)Objs::GetObj(OBJ_HELP);
				//help->SetMig_stageF();
				//help->SetTra_EatF(true);

				if (g_tutorial_progress == 8)
				{
					//矢印を非表示にさせる
					CObjMessage* message = (CObjMessage*)Objs::GetObj(OBJ_MESSAGE);
					message->Setarrow(0);
				}

				//選択音
				Audio::Start(1);
			}
		}
		else
		{
			m_key_f = true;
		}
	}
	else
	{
		m_Tra_color = INI_COLOR;
	}

	//喰アイコン
	if (980 < m_mou_x && m_mou_x < 1180 && 480 < m_mou_y && m_mou_y < 680 && (g_tutorial_progress == 1 || g_tutorial_progress >= 15))
	{
		m_Eat_color = 1.0f;

		//左クリックされたらフラグを立て、戦闘準備画面へ演出を交えながらシーン移行
		if (m_mou_l == true)
		{	
			//クリック押したままの状態では入力出来ないようにしている
			if (m_key_f == true)
			{
				m_key_f = false;

				m_Eat_flag = true;

				//ObjHelpにシーン移行演出を伝える
				//CObjHelp* help = (CObjHelp*)Objs::GetObj(OBJ_HELP);
				//help->SetMig_stageF();
				//help->SetTra_EatF(false);

				if (g_tutorial_progress == 1)
				{
					//矢印を非表示にさせる
					CObjMessage* message = (CObjMessage*)Objs::GetObj(OBJ_MESSAGE);
					message->Setarrow(0);
				}

				//選択音
				Audio::Start(1);
			}
		}
		else
		{
			m_key_f = true;
		}
	}
	else
	{
		m_Eat_color = INI_COLOR;
	}

	//プレイヤー惑星にマウスカーソルが合わさると、
	//プレイヤー惑星のステータスを表示する
	//※合わさっていない場合は非表示にする
	if (450 < m_mou_x && m_mou_x < 750 && 250 < m_mou_y && m_mou_y < 550)
	{
		m_status_flag = true;	//ステータス表示フラグON
	}
	else
	{
		m_status_flag = false;	//ステータス表示フラグOFF
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
void CObjHome::Draw()
{
	//描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	//敵惑星(背景)用
	float p[4] = { 1.0f,1.0f,1.0f,m_alpha };

	//育アイコン用
	float t[4] = { m_Tra_color,m_Tra_color,m_Tra_color,m_alpha };

	//喰アイコン用
	float e[4] = { m_Eat_color,m_Eat_color,m_Eat_color,m_alpha };

	//プレイヤー惑星ステータスのフォントカラー用
	float status_font_color[4][4] =
	{
		{ 1.0f,1.0f,1.0f,1.0f },//1行目は白色
		{ 1.0f,1.0f,1.0f,1.0f },//2行目は白色
		{ 1.0f,1.0f,1.0f,1.0f },//3行目は白色
		{ 1.0f,0.0f,0.0f,1.0f },//4行目は赤色
	};

	//それ以外の画像用
	float d[4] = { 1.0f,1.0f,1.0f,1.0f };

	//▽フォント準備
	//プレイヤー惑星ステータスのフォント用
	wchar_t status_font[3][13];										//13文字分格納可能な文字配列を3つ宣言
	swprintf_s(status_font[0], L"惑星HP：%.0f", g_Player_max_size);	//文字配列に文字データを入れる
	swprintf_s(status_font[1], L"装備中のスペシャル技：");			//文字配列に文字データを入れる


	//▽現在装備中のスペシャル技文字画像を読み込み127番に登録する
	switch (g_Special_equipment)
	{
	case 1:
		//エクスプロージョン文字画像を読み込み127番に登録
		Draw::LoadImage(L"img\\テキスト\\スペシャル技\\エクスプロージョン.png", 127, TEX_SIZE_512);

		//切り取り位置を設定する
		m_special_clip_right = 1072.0f;
		m_special_clip_bottom = 112.0f;

		//描画位置を設定する
		m_special_draw_left = 33.0f;
		m_special_draw_right = 260.0f;

		break;
	case 2:
		//フラクチャーレイ文字画像を読み込み127番に登録
		Draw::LoadImage(L"img\\テキスト\\スペシャル技\\フラクチャーレイ.png", 127, TEX_SIZE_512);

		//切り取り位置を設定する
		m_special_clip_right = 952.0f;
		m_special_clip_bottom = 112.0f;

		//描画位置を設定する
		m_special_draw_left = 33.0f;
		m_special_draw_right = 235.0f;

		break;
	case 3:
		//イモータリティ文字画像を読み込み127番に登録
		Draw::LoadImage(L"img\\テキスト\\スペシャル技\\イモータリティ.png", 127, TEX_SIZE_512);

		//切り取り位置を設定する
		m_special_clip_right = 817.0f;
		m_special_clip_bottom = 112.0f;

		//描画位置を設定する
		m_special_draw_left = 33.0f;
		m_special_draw_right = 210.0f;

		break;
	case 4:
		//オーバーワーク文字画像を読み込み127番に登録
		Draw::LoadImage(L"img\\テキスト\\スペシャル技\\オーバーワーク.png", 127, TEX_SIZE_512);

		//切り取り位置を設定する
		m_special_clip_right = 832.0f;
		m_special_clip_bottom = 112.0f;

		//描画位置を設定する
		m_special_draw_left = 33.0f;
		m_special_draw_right = 210.0f;

		break;
	case 5:
		//リミットブレイク文字画像を読み込み127番に登録
		Draw::LoadImage(L"リミットブレイク.png", 127, TEX_SIZE_512);

		//切り取り位置を設定する
		m_special_clip_right = 952.0f;
		m_special_clip_bottom = 112.0f;

		//描画位置を設定する
		m_special_draw_left = 33.0f;
		m_special_draw_right = 235.0f;

		break;
	default:
		//未装備文字画像を読み込み127番に登録
		Draw::LoadImage(L"img\\テキスト\\スペシャル技\\未装備.png", 127, TEX_SIZE_512);

		//切り取り位置を設定する
		m_special_clip_right = 367.0f;
		m_special_clip_bottom = 117.0f;

		//描画位置を設定する
		m_special_draw_left = 33.0f;
		m_special_draw_right = 108.0f;

		break;
	}

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
	src.m_right = 300.0f;
	src.m_bottom = 300.0f;

	dst.m_top = m_Ey[0];
	dst.m_left = 1200.0f - m_time[0];//+4ずつ増加し続ける変数を引く事で、
	dst.m_right = 1250.0f - m_time[0];//グラフィックを右から左へ移動させている。
	dst.m_bottom = m_Ey[0] + 50.0f;
	Draw::Draw(20, &src, &dst, p, 0.0f);

	//敵惑星2(背景)表示
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 300.0f;
	src.m_bottom = 300.0f;

	dst.m_top = m_Ey[1];
	dst.m_left = 1200.0f - m_time[1];//+4ずつ増加し続ける変数を引く事で、
	dst.m_right = 1250.0f - m_time[1];//グラフィックを右から左へ移動させている。
	dst.m_bottom = m_Ey[1] + 50.0f;
	Draw::Draw(22, &src, &dst, p, 0.0f);

	//敵惑星3(背景)表示
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 300.0f;
	src.m_bottom = 300.0f;

	dst.m_top = m_Ey[2];
	dst.m_left = 1200.0f - m_time[2];//+4ずつ増加し続ける変数を引く事で、
	dst.m_right = 1250.0f - m_time[2];//グラフィックを右から左へ移動させている。
	dst.m_bottom = m_Ey[2] + 50.0f;
	Draw::Draw(24, &src, &dst, p, 0.0f);

	//▼プレイヤー惑星表示
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 448.0f;
	src.m_bottom = 448.0f;

	dst.m_top = 250.0f + m_Pvy - m_size;
	dst.m_left = 450.0f + m_Pvx - m_size;
	dst.m_right = 750.0f + m_Pvx + m_size;
	dst.m_bottom = 550.0f + m_Pvy + m_size;
	Draw::Draw(50 + ((int)((g_Bar_Level + g_Ins_Level) / 2)) - 1, &src, &dst, d, 0.0f);

	if (g_tutorial_progress >= 8)
	{
		//▼育アイコン表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 200.0f;
		src.m_bottom = 200.0f;

		dst.m_top = 480.0f + m_Tra_move;
		dst.m_left = 20.0f - m_Tra_move;
		dst.m_right = 220.0f - m_Tra_move;
		dst.m_bottom = 680.0f + m_Tra_move;
		Draw::Draw(1, &src, &dst, t, 0.0f);
	}

	if (g_tutorial_progress == 1 || g_tutorial_progress >= 15)
	{
		//▼喰アイコン表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 200.0f;
		src.m_bottom = 200.0f;

		dst.m_top = 480.0f + m_Eat_move;
		dst.m_left = 980.0f + m_Eat_move;
		dst.m_right = 1180.0f + m_Eat_move;
		dst.m_bottom = 680.0f + m_Eat_move;
		Draw::Draw(2, &src, &dst, e, 0.0f);
	}

	//プレイヤー惑星ステータス表示(フラグtrue時のみ描画)
	if (m_status_flag == true)
	{
		////▽ウインドウ表示左上 
		//src.m_top = 0.0f;
		//src.m_left = 0.0f;
		//src.m_right = 800.0f;
		//src.m_bottom = 790.0f;

		//dst.m_top = m_mou_y - 125.0f;
		//dst.m_left = m_mou_x + 20.0f;
		//dst.m_right = m_mou_x + 120.0f;
		//dst.m_bottom = m_mou_y - 65.0f;
		//Draw::Draw(6, &src, &dst, d, 0.0f);

		////▽ウインドウ表示左下
		//src.m_top = 30.0f;
		//src.m_left = 800.0f;
		//src.m_right = 1600.0f;
		//src.m_bottom = 795.0f;

		//dst.m_top = m_mou_y - 65.0f;
		//dst.m_left = m_mou_x + 20.0f;
		//dst.m_right = m_mou_x + 120.0f;
		//dst.m_bottom = m_mou_y + 45.0f;
		//Draw::Draw(6, &src, &dst, d, 0.0f);

		////▽ウインドウ表示中央上 
		//src.m_top = 0.0f;
		//src.m_left = 1600.0f;
		//src.m_right = 2400.0f;
		//src.m_bottom = 795.0f;

		//dst.m_top = m_mou_y - 125.0f;
		//dst.m_left = m_mou_x + 120.0f;
		//dst.m_right = m_mou_x + 220.0f;
		//dst.m_bottom = m_mou_y - 65.0f;
		//Draw::Draw(6, &src, &dst, d, 0.0f);

		////▽ウインドウ表示中央下 
		//src.m_top = 5.0f;
		//src.m_left = 2400.0f;
		//src.m_right = 3200.0f;
		//src.m_bottom = 800.0f;

		//dst.m_top = m_mou_y - 65.0f;
		//dst.m_left = m_mou_x + 120.0f;
		//dst.m_right = m_mou_x + 220.0f;
		//dst.m_bottom = m_mou_y + 45.0f;
		//Draw::Draw(6, &src, &dst, d, 0.0f);

		////▼ウインドウ右上
		//src.m_top = 0.0f;
		//src.m_left = 4000.0f;
		//src.m_right = 4800.0f;
		//src.m_bottom = 795.0f;

		//dst.m_top = m_mou_y - 125.0f;
		//dst.m_left = m_mou_x + 220.0f;
		//dst.m_right = m_mou_x + 320.0f;
		//dst.m_bottom = m_mou_y - 65.0f;
		//Draw::Draw(6, &src, &dst, d, 0.0f);

		////▼ウインドウ右下
		//src.m_top = 5.0f;
		//src.m_left = 4800.0f;
		//src.m_right = 5600.0f;
		//src.m_bottom = 800.0f;

		//dst.m_top = m_mou_y - 65.0f;
		//dst.m_left = m_mou_x + 220.0f;
		//dst.m_right = m_mou_x + 320.0f;
		//dst.m_bottom = m_mou_y + 45.0f;
		//Draw::Draw(6, &src, &dst, d, 0.0f);

		//▼ウインドウ
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1200.0f;
		src.m_bottom = 700.0f;

		dst.m_top = m_mou_y - 125.0f;
		dst.m_left = m_mou_x + 20.0f;
		dst.m_right = m_mou_x + 320.0f;
		dst.m_bottom = m_mou_y + 45.0f;
		Draw::Draw(7, &src, &dst, d, 0.0f);

		//▽フォント画像表示
		//「惑星名：」表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 342.0f;
		src.m_bottom = 90.0f;

		dst.m_top = m_mou_y - 113.0f;
		dst.m_left = m_mou_x + 33.0f;
		dst.m_right = m_mou_x + 122.0f;
		dst.m_bottom = m_mou_y - 88.0f;
		Draw::Draw(128, &src, &dst, status_font_color[0], 0.0f);

		//プレイヤー名の表示
		FontDraw(g_Player_Name, m_mou_x + 128.0f, m_mou_y - 113.0f, 25.0f, 25.0f, status_font_color[0], false);

		//惑星HP文字画像表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 412.0f;
		src.m_bottom = 112.0f;

		dst.m_top = m_mou_y - 73.0f;
		dst.m_left = m_mou_x + 33.0f;
		dst.m_right = m_mou_x + 133.0f;
		dst.m_bottom = m_mou_y  -48.0f;
		Draw::Draw(53, &src, &dst, status_font_color[1], 0.0f);

		//装備中のスペシャル技文字画像
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1242.0f;
		src.m_bottom = 117.0f;

		dst.m_top = m_mou_y - 33.0f;
		dst.m_left = m_mou_x + 33.0f;
		dst.m_right = m_mou_x + 285.0f;
		dst.m_bottom = m_mou_y - 8.0f;
		Draw::Draw(54, &src, &dst, status_font_color[2], 0.0f);

		//「：」を表示
		FontDraw(L"：", m_mou_x + 133.0f, m_mou_y - 73.0f, 25.0f, 25.0f, status_font_color[1], false);
		FontDraw(L"：", m_mou_x + 285.0f, m_mou_y - 33.0f, 25.0f, 25.0f, status_font_color[2], false);

		//現在の最大惑星HPを表示
		FontDraw(NumConversion((int)g_Player_max_size), m_mou_x + 158.0f, m_mou_y - 73.0f, 15.0f, 25.0f, status_font_color[1], false);

		//現在装備中のスペシャル技[未装備/エクスプロージョン等]文字画像
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = m_special_clip_right;
		src.m_bottom = m_special_clip_bottom;

		dst.m_top = m_mou_y + 7.0f;
		dst.m_left = m_mou_x + m_special_draw_left;
		dst.m_right = m_mou_x + m_special_draw_right;
		dst.m_bottom = m_mou_y + 32.0f;
		Draw::Draw(127, &src, &dst, status_font_color[3], 0.0f);
	}

	//デバッグ用仮マウス位置表示
	//wchar_t str[256];
	//swprintf_s(str, L"x=%f,y=%f", m_mou_x, m_mou_y);
	//Font::StrDraw(str, 20.0f, 20.0f, 12.0f, d);
}
