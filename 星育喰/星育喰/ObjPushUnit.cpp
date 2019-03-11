//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"
#include "ObjPushUnit.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjPushUnit::CObjPushUnit(float x, float y, float h, float w, int t)
{
	//作成時に渡された値を、座標の初期値に代入
	m_x = x;
	m_y = y;
	m_h = h;
	m_w = w;
	m_type = t;
}

//イニシャライズ
void CObjPushUnit::Init()
{
	m_mou_x = 0.0f;	//マウスX座標
	m_mou_y = 0.0f; //マウスY座標
	m_mou_r = false;//右クリック
	m_mou_l = false;//左クリック

	m_a = 1.0f;
}

//アクション
void CObjPushUnit::Action()
{
	//マウスの位置を取得
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//マウスのボタンの状態
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	if ((m_x <= m_mou_x && m_mou_x <= (m_x + m_w))		//X軸範囲
		&& (m_y <= m_mou_y && m_mou_y <= (m_y + m_h))	//Y軸範囲
		&& m_mou_l == true) {							//クリック
		if (m_type == 0) {		//タイプごとの処理
			m_a = 0;
		}
		else if (m_type == 1)
		{
			m_a = 0.3;
		}
		else if (m_type == 2)
		{
			m_a = 0.6;
		}
	}
}

//ドロー
void CObjPushUnit::Draw()
{
	//描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	float c[4] = { 1.0f,1.0f, 1.0f, m_a };

	RECT_F src;//切り取り位置
	RECT_F dst;//表示位置
	
	src.m_top   =  0.0f;
	src.m_left  =  0.0f;
	src.m_right =100.0f;
	src.m_bottom=100.0f;
	
	dst.m_top   = m_y;
	dst.m_left  = m_x;
	dst.m_right = m_x + m_h;
	dst.m_bottom= m_y + m_w;

	//2番目に登録したグラフィックをsrc,dst,c情報をもとに描画
	Draw::Draw(2, &src, &dst, c, 0.0f);
}