//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjFight.h"
#include "UtilityModule.h"

//使用するネームスペース
using namespace GameL;

//static変数の定義
bool CObjFight::battle_start = false;
bool CObjFight::battle_end = false;
float CObjFight::damage_buff[2] = { 1.0f,1.0f };

#define INI_COLOR (0.9f) //全カラー明度の初期値(アイコン未選択中のカラー)

//c = cnt(戦闘時間),e_n = m_ene_nam(敵ナンバー)
CObjFight::CObjFight(int c)
{
	m_cnt = c * 60;
}

//イニシャライズ
void CObjFight::Init()
{
	m_mou_x = 0.0f;	//マウスX座標
	m_mou_y = 0.0f; //マウスY座標
	m_mou_r = false;//右クリック
	m_mou_l = false;//左クリック
	
	m_line = 3;		//初期値、
	m_line_nam = 3; //初期値、無選択

	m_cnt = 60 * 300;//戦闘時間(60 * X = X秒)
	m_a = 1;		//初期値、不透明

	m_ex = 0;
	m_ey = 0;

	m_scale_down_cnt = 0;
	m_scale_down_speed = 0.04f;
	m_font_a = 1.0f;

	m_start_count = 60 * 3;	//3秒経過後、戦闘開始
	m_start_count_f = false;

	m_end_f = false;

	//▼以下のstatic変数は他シーンから戦闘画面に入る度に初期化を行う
	battle_start = false;
	battle_end = false;
	for (int i = 0; i < 2; i++)
	{
		damage_buff[i] = 1.0f;
	}

	Hits::SetHitBox(this, 400, 310, 400, 60, ELEMENT_LINE, OBJ_FIGHT, 1);
}

//アクション
void CObjFight::Action()
{
	//▼戦闘開始前は戦闘処理を実行しないようにする＆
	//戦闘開始カウントの処理
	if (battle_start == false)
	{
		//戦闘前演出オブジェクトから「戦闘開始カウント」開始フラグをtrueにした時に実行
		//戦闘開始カウントを徐々に減らしていき、0になった時、戦闘開始フラグ等を立てる。
		if (m_start_count <= 60 * 0)
		{
			//ポーズ画面等で戦闘を一時停止する際、
			//battle_startの[true / false]で一時停止を行うが、
			//再度この戦闘開始カウントの処理が行われると厄介である為、
			//[m_start_count_f]をfalseに、[m_start_count]を初期値に戻す事で、
			//この処理が行われないようにする。
			m_start_count_f = false;
			m_start_count = 60 * 3;

			battle_start = true;//戦闘開始フラグを立てる
		}
		else if (m_start_count_f == true)
		{
			m_start_count--;//戦闘開始カウントダウン
		}

		return;
	}

	//▼戦闘終了間際(残り1秒)のタイミングで戦闘終了フラグを立てる
	if (m_cnt <= 60)
	{
		battle_end = true;	//戦闘終了フラグを立てる
	}

	if (m_cnt > 0)	//0より大きい時
		m_cnt--;	//カウントダウン
	
	//背景縮小処理
	m_scale_down_cnt += m_scale_down_speed;
	if (m_scale_down_speed > 0)
		m_scale_down_speed -= 0.00001f;

	//戦闘開始時表示される"スタート"の文字を徐々に透明化
	if (m_scale_down_cnt >= 0.5 && m_font_a >= 0) {
		m_font_a -= 0.01f;
	}

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

	//▼クリア処理
	//エネミー毎に取得出来る資源等は違うため、
	//以下でそれぞれ引数を設定し、ObjFightClearを作成する。
	if (m_end_f == true)
	{
		m_end_f = false;
		if (g_Challenge_enemy == 0)									//左から１番目
		{//							(住人, 資材, 大きさ, 技 1～5取得スキル)
			CObjFightClear* crer = new CObjFightClear(2000, 0, 20, 1);	
			Objs::InsertObj(crer, OBJ_FIGHT_CLEAR, 15);
		}
		if (g_Challenge_enemy == 1)									//左から２番目
		{//							(住人, 資材, 大きさ, 技 1～5取得スキル)
			CObjFightClear* crer = new CObjFightClear(10000, 1, 60, 0);
			Objs::InsertObj(crer, OBJ_FIGHT_CLEAR, 15);
		}
		if (g_Challenge_enemy == 2)									//左から３番目
		{//							(住人, 資材, 大きさ, 技 1～5取得スキル)
			CObjFightClear* crer = new CObjFightClear(15000, 2, 80, 0);
			Objs::InsertObj(crer, OBJ_FIGHT_CLEAR, 15);
		}
		if (g_Challenge_enemy == 3)									//左から４番目
		{//							(住人, 資材, 大きさ, 技 1～5取得スキル)
			CObjFightClear* crer = new CObjFightClear(3000, 3, 30, 0);
			Objs::InsertObj(crer, OBJ_FIGHT_CLEAR, 15);
		}
		if (g_Challenge_enemy == 4)									//ボス
		{//							(住人, 資材, 大きさ, 技 1～5取得スキル)
			CObjFightClear* crer = new CObjFightClear(1000, 4, 90, 2);
			Objs::InsertObj(crer, OBJ_FIGHT_CLEAR, 15);
		}
	}
}

//ドロー
void CObjFight::Draw()
{	
	//描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	float c[4] = { 1.0f,1.0f,1.0f,m_a };
	float d[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

	//▼背景表示
	src.m_top = 0.0f + (m_scale_down_cnt * 4.5 / 6);
	src.m_left = 0.0f + m_scale_down_cnt;
	src.m_right = 960.0f - m_scale_down_cnt;
	src.m_bottom = 638.0f - (m_scale_down_cnt * 4.5 / 6);

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 1200.0f;
	dst.m_bottom = 700.0f;
	Draw::Draw(0, &src, &dst, d, 0.0f);


	//▼戦闘時間表示
	int s = (m_cnt / 60), m = 0;	//ミニッツ,セコンドを宣言＆初期化
	if (s >= 60) {						//60秒以上の場合
		m += (s / 60); int n = (s / 60); s -= (n * 60);	//分に秒÷60を足して、秒はその分減らす。
	}													//nはその減らす分。

	wchar_t str[256];
	swprintf_s(str, L"%02d :%02d", m, s);		//2桁、0詰め表示
	Font::StrDraw(str,500 ,60 ,50 , c);


	//▼攻撃用ライン描画処理
	CObjFight* obj = (CObjFight*)Objs::GetObj(OBJ_FIGHT);

	//描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	float d0[4] = { 1.0f,1.0f,1.0f,0.2f };
	float d1[4] = { 1.0f,1.0f,1.0f,0.2f };
	float d2[4] = { 1.0f,1.0f,1.0f,0.2f };

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
			d0[3] = INI_COLOR;
		else if (m_line == 1)
			d1[3] = INI_COLOR;
		else if (m_line == 2)
			d2[3] = INI_COLOR;

		if (m_line_nam == 0)	//カーソル時に半不透明化
			d0[3] = 1.0f;
		else if (m_line_nam == 1)
			d1[3] = 1.0f;
		else if (m_line_nam == 2)
			d2[3] = 1.0f;
	}

	//攻撃用ライン画像
	src.m_top   =  0.0f;
	src.m_left  =  0.0f;
	src.m_right =100.0f;
	src.m_bottom=100.0f;

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

	//▼戦闘開始カウント
	//戦闘開始カウントの値に合わせて、
	//３→２→１と徐々にカウントダウンしていき、
	//０になると「スタート！」と表示。
	//その後「スタート！」の文字は徐々に透明化していき、
	//最終的に見えなくなる。
	float start_font[4] = { 1.0f,1.0f,1.0f,m_font_a };
	
	if (battle_start == true)
	{
		Font::StrDraw(L"スタート！", 420, 250, 80, start_font);
	}
	else if (m_start_count <= 60 * 1)
	{
		Font::StrDraw(L"１", 495, 260, 160, start_font);
	}
	else if (m_start_count <= 60 * 2)
	{
		Font::StrDraw(L"２", 495, 260, 160, start_font);
	}
	else if (m_start_count_f == true)
	{
		Font::StrDraw(L"３", 495, 260, 160, start_font);
	}



	////デバッグ用仮マウス位置表示
	//wchar_t test_mou[256];
	//swprintf_s(test_mou, L"x=%f,y=%f", m_mou_x, m_mou_y);
	//Font::StrDraw(test_mou, 20.0f, 20.0f, 12.0f, d);
}
