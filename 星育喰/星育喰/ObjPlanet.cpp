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
	m_type = type;
}

//イニシャライズ
void CObjPlanet::Init()
{
	m_size	 =100.0f;
	m_siz_vec=  0.0f;
	m_mov_spd=  0.05f;
	m_siz_spd=  0.07f;


	//当たり判定用HitBoxを作成
	if(m_type == true)
		Hits::SetHitBox(this, m_px, m_py, m_size, m_size, ELEMENT_PLAYER, OBJ_PLANET, 1);
	else
		Hits::SetHitBox(this, m_px, m_py, m_size, m_size, ELEMENT_RED, OBJ_PLANET, 1);
}

//アクション
void CObjPlanet::Action()
{
	m_siz_vec += m_siz_spd;
	if (m_type == true)
		m_px -= m_mov_spd;
	else
		m_px += m_mov_spd;

	CHitBox* hit = Hits::GetHitBox(this);	//CHitBoxポインタ取得
	hit->SetPos(m_px - m_siz_vec, m_py - m_siz_vec, 2 * m_siz_vec + m_size, 2 * m_siz_vec + m_size);//位置を更新
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
	dst.m_top   = m_py - m_siz_vec;
	dst.m_left  = m_px - m_siz_vec;
	dst.m_right = m_px + m_siz_vec + m_size;
	dst.m_bottom= m_py + m_siz_vec + m_size;

	//0番目に登録したグラフィックをsrc,dst,c情報をもとに描画
	Draw::Draw(0, &src, &dst, c, 0.0f);
}
