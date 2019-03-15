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
#define INI_ALPHA (0.0f) //透過度(アルファ値)の初期値
#define INI_COLOR (1.0f) //全カラー明度の初期値

//static変数の定義
bool CObjTraining::test_flag = false;

//イニシャライズ
void CObjTraining::Init()
{
	m_size = INI_PLAYER_SIZE;

	m_mou_x = 0.0f;
	m_mou_y = 0.0f;
	m_mou_r = false;
	m_mou_l = false;

	m_Back_Button_color = INI_COLOR;
	m_Back_Button_flag = false;
	m_Player_Display_flag = false;

	m_Mig_time = 0;
	m_key_f = false;
}

//アクション
void CObjTraining::Action()
{
	//戻るボタンクリック、もしくは右クリック時実行
	if (m_Back_Button_flag == true)
	{
		m_Mig_time++;

		if (m_Player_Display_flag == true)
		{
			m_size -= 20.0f;

			if (m_size <= 0.0f)
			{
				Scene::SetScene(new CSceneHome());//ホーム画面へシーン移行
			}
		}
		else if (m_Mig_time >= 120)
		{
			//背景を読み込み0番に登録
			Draw::LoadImage(L"TitleBackgroundTest.jpg", 0, TEX_SIZE_512);

			//雲演出OUTを行う
			CObjCloud_Effect* obj_cloud = (CObjCloud_Effect*)Objs::GetObj(OBJ_CLOUD);
			obj_cloud->SetCheck(false);

			m_Player_Display_flag = true;
		}

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
		m_Back_Button_color = 0.7f;

		//▼移行フラグを立て、ホーム画面へ演出を交えながらシーン移行
		//右クリック入力時
		if (m_mou_r == true)
		{
			//雲演出INを行う
			CObjCloud_Effect* obj_cloud = (CObjCloud_Effect*)Objs::GetObj(OBJ_CLOUD);
			obj_cloud->SetCheck(true);

			//移行フラグ立て
			m_Back_Button_flag = true;
		}
		//左クリック入力時
		else if (m_mou_l == true)
		{
			//左クリック押したままの状態では入力出来ないようにしている
			if (m_key_f == true)
			{
				m_key_f = false;

				//雲演出INを行う
				CObjCloud_Effect* obj_cloud = (CObjCloud_Effect*)Objs::GetObj(OBJ_CLOUD);
				obj_cloud->SetCheck(true);

				//移行フラグ立て
				m_Back_Button_flag = true;
			}
		}
		else
		{
			m_key_f = true;
		}
	}
	else
	{
		m_Back_Button_color = 1.0f;
	}
}

//ドロー
void CObjTraining::Draw()
{
	//描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	////敵惑星(背景)用
	//float p[4] = { 1.0f,1.0f,1.0f,m_alpha };

	////育アイコン用
	//float t[4] = { m_Tra_color,m_Tra_color,m_Tra_color,m_alpha };

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

	//▼(仮)戻るボタン表示
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 225.0f;
	src.m_bottom = 225.0f;

	dst.m_top = 10.0f;
	dst.m_left = 10.0f;
	dst.m_right = 60.0f;
	dst.m_bottom = 60.0f;
	Draw::Draw(1, &src, &dst, b, 0.0f);


	if (m_Player_Display_flag == true)
	{
		//▼プレイヤー惑星表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 300.0f;
		src.m_bottom = 168.0f;

		dst.m_top = 150.0f - m_size;
		dst.m_left = 250.0f - m_size;
		dst.m_right = 950.0f + m_size;
		dst.m_bottom = 550.0f + m_size;
		Draw::Draw(50, &src, &dst, d, 0.0f);
	}



	//デバッグ用仮マウス位置表示
	wchar_t str[256];
	swprintf_s(str, L"x=%f,y=%f", m_mou_x, m_mou_y);
	Font::StrDraw(str, 20, 20, 12, d);
}
