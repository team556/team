//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"		//使用されているのはマウスデバッグの部分のみ
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"

//使用するネームスペース
using namespace GameL;

//マクロ
#define INI_PLAYER_SIZE (1500.0f) //プレイヤー惑星の初期サイズ
#define INI_COLOR (0.9f) //全カラー明度の初期値(アイコン未選択中のカラー)

//static変数の定義
bool CObjTraining::m_key_rf = false;
bool CObjTraining::scene_change_start = false;
int  CObjTraining::window_start_manage = Default;

//グローバル変数の定義
int g_Bar_Level = 1;
int g_Ins_Level = 1;
int g_Mis_Recast_Level = 0;
int g_Pow_equip_Level = 1;	
int g_Pow_equip_Lv_achieve = 1;
int g_Def_equip_Level = 1;		
int g_Def_equip_Lv_achieve = 1;	
int g_Spe_equip_Level = 1;		
int g_Spe_equip_Lv_achieve = 1;	
int g_Bal_equip_Level = 1;
int g_Bal_equip_Lv_achieve = 1;
int g_Pod_equip_Level = 1;
int g_Pod_equip_Lv_achieve = 1;
int g_Power_num = 0;
int g_Defense_num = 0;
int g_Speed_num = 0;
int g_Balance_num = 0;
int g_Research_num = 0;
int g_Remain_num = 1000;

int g_Material_num_test = 400;

//イニシャライズ
void CObjTraining::Init()
{
	m_size = INI_PLAYER_SIZE;
	m_Mig_time = 0;

	m_mou_x = 0.0f;
	m_mou_y = 0.0f;
	m_mou_r = false;
	m_mou_l = false;
	m_key_lf = false;

	m_Back_Button_color = INI_COLOR;

	//▼以下のstatic変数は他シーンから育成画面に入る度に初期化を行う
	m_key_rf = false;
	scene_change_start = false;
	window_start_manage = Default;
}

//アクション
void CObjTraining::Action()
{
	//戻るボタンクリック、もしくは右クリック(どこでも)時実行
	if (window_start_manage == BackButton)
	{
		m_Mig_time++;

		//▼シーン切り替え演出
		//雲演出INが終了するまで(m_Mig_timeが120以上になるまで)待機。
		//終了すると背景をホーム画面のものに切り替え、
		//同じくオブジェクトもホーム画面のものに切り替えた後に
		//雲演出OUTを行い、画面を見せる。
		//プレイヤー惑星サイズがデフォルトの状態に戻った事を確認すると
		//ホーム画面へシーン移行を行う。
		if (scene_change_start == true)
		{
			m_size -= 20.0f;

			if (m_size <= 0.0f)
			{
				Scene::SetScene(new CSceneHome());//ホーム画面へシーン移行
			}
		}
		else if (m_Mig_time >= 120)
		{
			//ホーム画面の背景を読み込み0番に登録
			Draw::LoadImage(L"TitleBackgroundTest.jpg", 0, TEX_SIZE_512);

			//雲演出OUTを行う
			CObjCloud_Effect* obj_cloud = (CObjCloud_Effect*)Objs::GetObj(OBJ_CLOUD);
			obj_cloud->SetCheck(false);

			//シーン切り替え演出にて不必要なオブジェクトを非表示、
			//また必要なオブジェクトを表示するフラグを立てる
			scene_change_start = true;
		}

		return;
	}
	//他施設のウインドウを開いている時は操作を受け付けないようにする。
	else if (window_start_manage != Default)
	{
		return;
	}


	//マウスの位置を取得
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//マウスのボタンの状態
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();


	//戻るボタン左クリック、もしくは右クリックする事でホーム画面に戻る
	if (10 < m_mou_x && m_mou_x < 60 && 10 < m_mou_y && m_mou_y < 60 || m_mou_r == true)
	{
		m_Back_Button_color = 1.0f;

		//▼移行フラグを立て、ホーム画面へ演出を交えながらシーン移行
		//右クリック入力時
		if (m_mou_r == true)
		{
			//前シーン(兵舎ウインドウ等)から右クリック押したままの状態では入力出来ないようにしている
			if (m_key_rf == true)
			{
				//雲演出INを行う
				CObjCloud_Effect* obj_cloud = (CObjCloud_Effect*)Objs::GetObj(OBJ_CLOUD);
				obj_cloud->SetCheck(true);

				//移行フラグ立て
				window_start_manage = BackButton;
			}
		}
		//左クリック入力時
		else if (m_mou_l == true)
		{
			//左クリック押したままの状態では入力出来ないようにしている
			if (m_key_lf == true)
			{
				m_key_lf = false;

				//雲演出INを行う
				CObjCloud_Effect* obj_cloud = (CObjCloud_Effect*)Objs::GetObj(OBJ_CLOUD);
				obj_cloud->SetCheck(true);

				//移行フラグ立て
				window_start_manage = BackButton;
			}
		}
		else
		{
			m_key_lf = true;
		}
	}
	else
	{
		m_key_rf = true;
		m_Back_Button_color = INI_COLOR;
	}
}

//ドロー
void CObjTraining::Draw()
{
	//描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	//戻るボタン用
	float b[4] = { m_Back_Button_color,m_Back_Button_color,m_Back_Button_color,1.0f };

	//それ以外の画像用
	float d[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置


	//▼背景(地面)表示
	//シーン移行の演出処理的に、
	//この切り取り位置はホーム画面と同じが好ましい
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 960.0f;
	src.m_bottom = 638.0f;

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 1200.0f;
	dst.m_bottom = 700.0f;
	Draw::Draw(0, &src, &dst, d, 0.0f);


	//▼シーン切り替え演出前に表示するグラフィック
	if (scene_change_start == false)
	{
		//▼戻るボタン表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 10.0f;
		dst.m_left = 10.0f;
		dst.m_right = 60.0f;
		dst.m_bottom = 60.0f;
		Draw::Draw(1, &src, &dst, b, 0.0f);
	}
	//▼シーン切り替え演出後に表示するグラフィック
	else
	{
		//▼プレイヤー惑星表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 62.0f;
		src.m_bottom = 62.0f;

		dst.m_top = 250.0f - m_size;
		dst.m_left = 450.0f - m_size;
		dst.m_right = 750.0f + m_size;
		dst.m_bottom = 550.0f + m_size;
		Draw::Draw(16, &src, &dst, d, 0.0f);
	}



	//デバッグ用仮マウス位置表示
	wchar_t str[256];
	swprintf_s(str, L"x=%f,y=%f", m_mou_x, m_mou_y);
	Font::StrDraw(str, 20.0f, 20.0f, 12.0f, d);
}

//---Allocation関数
//引数1　int type_num		:住民タイプ決定
//引数2　int up_down_check	:振り分けUP / DOWNチェック(+1=振り分けUP / -1=振り分けDOWN)
//戻り値 int				:振り分け後の値
//▼内容
//住民タイプと振り分けUP or DOWNを引数で渡せば、
//以下の処理を行い、その住民タイプの振り分け後の値を返す。
//※同時にグローバル変数である"残り住民数(g_Remain_num)"の値も変化させている。
int CObjTraining::Allocation(int type_num, int up_down_check)
{
	//▼それぞれ仮の変数に代入
	int Tmp_human = type_num;
	int Tmp_remain = g_Remain_num;

	//▼仮の変数で変化させてみる
	Tmp_human += 100 * up_down_check;
	Tmp_remain -= 100 * up_down_check;

	//▼仮の変数が以下の条件を全て満たしていれば、実際の値を変化させる。
	//満たしていなければ、それに応じたエラーメッセージを出し、
	//実際の値を変化させずに関数を終了させる。
	if (0 <= Tmp_human && Tmp_human <= 999900 && Tmp_remain >= 0)
	{
		type_num += 100 * up_down_check;
		g_Remain_num -= 100 * up_down_check;
	}
	else if (Tmp_remain < 0) //残り住民数がいない場合
	{
		swprintf_s(m_message, L"残り住民数がいません");//文字配列に文字データを入れる
		
		//▼エラーメッセージのカラーを赤色にする
		m_message_red_color = 1.0f;
		m_message_green_color = 0.0f;
		m_message_blue_color = 0.0f;
		
		m_alpha = 1.0f;		//エラーメッセージを表示するため、透過度を1.0fにする
	}
	else  //(Tmp_human < 0 || 999900 < Tmp_human) これ以上振り分けられない場合
	{
		swprintf_s(m_message, L"これ以上振り分けられません");//文字配列に文字データを入れる

		//▼エラーメッセージのカラーを赤色にする
		m_message_red_color = 1.0f;
		m_message_green_color = 0.0f;
		m_message_blue_color = 0.0f;

		m_alpha = 1.0f;		//エラーメッセージを表示するため、透過度を1.0fにする
	}

	return type_num;
}
