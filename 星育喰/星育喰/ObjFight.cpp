//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"
#include "ObjFight.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjFight::Init()
{
	m_mou_x = 0.0f;	//マウスX座標
	m_mou_y = 0.0f; //マウスY座標
	m_mou_r = false;//右クリック
	m_mou_l = false;//左クリック
	
	m_line = 3;		//初期値、
	m_line_nam = 3; //初期値、無選択

	m_cnt = 60 * 20;//戦闘時間(60 * X = X秒)
	m_a = 1;		//初期値、不透明

	m_end_f = false;

	m_hp = 0;
	m_hp2 = 0;
	m_ex = 0;
	m_ey = 0;
}

//アクション
void CObjFight::Action()
{
	if (m_cnt > 0)	//0より大きい時
		m_cnt--;	//カウントダウン
	
	//マウスの位置を取得
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//マウスのボタンの状態
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();
	

	m_line = 6;//常に選択前ラインを初期化

	if (400 <= m_mou_x && m_mou_x <= 800) 
	{
		if (200 <= m_mou_y && m_mou_y <= 260) {					
			if (m_mou_l == true) { m_line_nam = 0; }//上ライン------
			else { m_line = 0; }
		}
		else if (310 <= m_mou_y && m_mou_y <= 370) {			
			if (m_mou_l == true) { m_line_nam = 1; }//中ライン------
			else { m_line = 1; }
		}
		else if (420 <= m_mou_y && m_mou_y <= 480) {			
			if (m_mou_l == true) { m_line_nam = 2; }//下ライン------
			else { m_line = 2; }
		}
		else {};//ライン外何もしない
	}
	else {};

	//▼戦闘終了時処理
	//プレイヤー惑星、敵惑星のHPをそれぞれ取得し、比べ、
	//HPが多い方の惑星画像が手前に来るようにする
	if (m_end_f == true) {
		CObjPlanet* ene = (CObjPlanet*)Objs::GetObj(OBJ_ENEMY);
		if (ene != nullptr)
			m_hp = ene->GetHp();

		CObjPlanet* pnt = (CObjPlanet*)Objs::GetObj(OBJ_PLANET);
		if (pnt != nullptr)
			m_hp2 = pnt->GetHp();

		if (m_hp > m_hp2) {
			if (ene != nullptr)
				ene->SetDelF();
		}
		else {
			CObjPlanet* ene2 = (CObjPlanet*)Objs::GetObj(OBJ_ENEMY2);
			if (ene2 != nullptr)
				ene2->SetDelF();
		}
	}

	m_end_f = false;
}

//ドロー
void CObjFight::Draw()
{	//描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	float c[4] = { 1.0f,1.0f,1.0f,m_a };
	int s = (m_cnt / 60), m = 0;	//ミニッツ,セコンドを宣言＆初期化
	if (s >= 60) {						//60秒以上の場合
		m += (s / 60); int n = (s / 60); s -= (n * 60);	//分に秒÷60を足して、秒はその分減らす。
	}													//nはその減らす分。

	wchar_t str[256];
	swprintf_s(str, L"%02d :%02d", m, s);		//2桁、0詰め表示
	Font::StrDraw(str,500 ,60 ,50 , c);


	CObjFight* obj = (CObjFight*)Objs::GetObj(OBJ_FIGHT);

	//描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	float d0[4] = { 1.0f,1.0f,1.0f,0.3f };
	float d1[4] = { 1.0f,1.0f,1.0f,0.3f };
	float d2[4] = { 1.0f,1.0f,1.0f,0.3f };

	if (obj->GetCount() == 0) {//-------------------------時間切れの場合----
		if (m_a > 0.0f) {
			m_a -= 0.03f;				//透明化
		}
		d0[3] = { m_a };//個別に初期化
		d1[3] = { m_a };
		d2[3] = { m_a };
	}
	else {//------------------------------------------対戦時間中のみ動作-----
		if (m_line == 0)		//選択時に各ラインを不透明化
			d0[3] = 0.6f;
		else if (m_line == 1)
			d1[3] = 0.6f;
		else if (m_line == 2)
			d2[3] = 0.6f;

		if (m_line_nam == 0)	//カーソル時に半不透明化
			d0[3] = 1.0f;
		else if (m_line_nam == 1)
			d1[3] = 1.0f;
		else if (m_line_nam == 2)
			d2[3] = 1.0f;
	}
	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

	//▼背景表示
	src.m_top   =  0.0f;
	src.m_left  =  0.0f;
	src.m_right =100.0f;
	src.m_bottom=100.0f;

	//攻撃用ライン画像
	dst.m_top   =200.0f;
	dst.m_left  =400.0f;
	dst.m_right =800.0f;
	dst.m_bottom=260.0f;
	Draw::Draw(2, &src, &dst, d0, 0.0f);

	dst.m_top   =310.0f;
	dst.m_left  =400.0f;
	dst.m_right =800.0f;
	dst.m_bottom=370.0f;
	Draw::Draw(2, &src, &dst, d1, 0.0f);

	dst.m_top   =420.0f;
	dst.m_left  =400.0f;
	dst.m_right =800.0f;
	dst.m_bottom=480.0f;
	Draw::Draw(2, &src, &dst, d2, 0.0f);

	//if()



	//デバッグ用仮マウス位置表示
	float d[4] = { 1.0f,1.0f,1.0f,1.0f };
	wchar_t test_mou[256];
	swprintf_s(test_mou, L"x=%f,y=%f", m_mou_x, m_mou_y);
	Font::StrDraw(test_mou, 20.0f, 20.0f, 12.0f, d);
}
