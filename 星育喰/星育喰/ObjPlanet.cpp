//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjPlanet.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjPlanet::CObjPlanet(float x, float y, bool type)
{
	//作成時に渡された値を、座標の初期値に代入
	m_px = x;
	m_py = y;
	if (type == true)
		m_pnam = 1;
	else
		m_pnam = 0;
}

//イニシャライズ
void CObjPlanet::Init()
{
	m_size = 100;
	m_cnt = 0;
	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, m_size, m_size, ELEMENT_PLAYER, OBJ_HUMAN, 1);
}

//アクション
void CObjPlanet::Action()
{
	m_cnt += 0.07f;
	m_px += 0.02f;

	CHitBox* hit = Hits::GetHitBox(this);	//CHitBoxポインタ取得
	hit->SetPos(m_px, m_py);				//位置を更新
}

//ドロー
void CObjPlanet::Draw()
{
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	RECT_F src;
	RECT_F dst;
	//切り取り位置
	src.m_top   =  0.0f;
	src.m_left  =  0.0f;
	src.m_right =100.0f;
	src.m_bottom=100.0f;
	//表示位置
	dst.m_top   = m_py - m_cnt;
	dst.m_left  = m_px - m_cnt;
	dst.m_right = m_px + m_cnt + m_size;
	dst.m_bottom= m_py + m_cnt + m_size;

	//0番目に登録したグラフィックをsrc,dst,c情報をもとに描画
	Draw::Draw(1, &src, &dst, c, 0.0f);
}
