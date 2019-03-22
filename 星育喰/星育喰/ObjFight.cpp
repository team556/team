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

	m_cnt = 2400;
}

//アクション
void CObjFight::Action()
{
	m_cnt--;//カウントダウン

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
	else {};//範囲外の場合、初期値に戻す

}

//ドロー
void CObjFight::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	int s = (m_cnt / 60), m = (s / 60);	//ミニッツ,セコンドを宣言＆初期化
	if (s >= 60) {						//60秒以上の場合
		m += (s / 60); int n = (s / 60); s -= (n * 60);	//分に秒÷60を足して、秒はその分減らす。
	}													//nはその減らす分。

	wchar_t str[256];
	swprintf_s(str, L"%02d :%02d", m, s);		//2桁、0詰め表示
	Font::StrDraw(str,500 ,60 ,50 , c);


	//描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	float d0[4] = { 1.0f,1.0f,1.0f,0.3f };
	float d1[4] = { 1.0f,1.0f,1.0f,0.3f };
	float d2[4] = { 1.0f,1.0f,1.0f,0.3f };

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
}
