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
	m_size	 = 50.0f;
	m_siz_vec=  0.0f;

	m_hp = 10;

	m_cnt_f = false;

	CObjFight* obj = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
	m_mov_spd = 0.09f * 30 / (obj->GetCount() / 60);
	m_siz_spd = 0.07f * 30 / (obj->GetCount() / 60);


	//当たり判定用HitBoxを作成
	if(m_type == true)
		Hits::SetHitBox(this, m_px, m_py, m_size, m_size, ELEMENT_PLAYER, OBJ_PLANET, 1);
	else
		Hits::SetHitBox(this, m_px, m_py, m_size, m_size, ELEMENT_ENEMY, OBJ_PLANET, 1);
}

//アクション
void CObjPlanet::Action()
{
	CObjFight* obj = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
	if (obj->GetCount() != 0)
		m_siz_vec += m_siz_spd;

	if (m_type == true)
		m_px -= m_mov_spd;
	else
		m_px += m_mov_spd;

	CHitBox* hit = Hits::GetHitBox(this);	//CHitBoxポインタ取得
	hit->SetPos(m_px - m_siz_vec - m_size,
				m_py - m_siz_vec - m_size,
				2 * m_siz_vec + m_size * 2,
				2 * m_siz_vec + m_size * 2);//位置を更新

	if ((hit->CheckElementHit(ELEMENT_MAGIC) == true) && (m_type == false) && (m_hp > 0))
	{//敵のミサイルに当たった場合
		m_hp -= 1;
		m_size -= m_size / 10;
	}

	if (obj->GetCount() == 0)
		m_cnt_f = true;
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
	src.m_right = 62.0f;
	src.m_bottom= 62.0f;
	//表示位置
	dst.m_top   = m_py - m_siz_vec - m_size;//300
	dst.m_left  = m_px - m_siz_vec - m_size;//800
	dst.m_right = m_px + m_siz_vec + m_size;
	dst.m_bottom= m_py + m_siz_vec + m_size;

	//0番目に登録したグラフィックをsrc,dst,c情報をもとに描画
	Draw::Draw(3, &src, &dst, c, 0.0f);
}
