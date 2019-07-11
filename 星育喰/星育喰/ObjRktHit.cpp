//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjRktHit.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjRktHit::CObjRktHit(float x, float y, bool t)
{
	//作成時に渡された値を、座標の初期値に代入
	m_type = t;
	if(t == false)
		m_x = x - 50.0f;
	else
		m_x = x + 50.0f;
	m_y = y;
}

//イニシャライズ
void CObjRktHit::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;

	m_mov = 0.0f;
	m_size = 50.0f;
	m_del_cnt = 0;
	m_stop_f = false;
	m_del_f = false;

	if (m_type == false)
	{								//味方HitBox作成
		Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_NULL, OBJ_RKTHIT, 1);
		CObjFight* fit = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
		m_get_line = fit->GetLine();//選択Line取得
	}
	else
	{								//敵HitBox作成
		Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_NULL, OBJ_RKTHIT, 1);
		CObjPlanet* ene = (CObjPlanet*)Objs::GetObj(OBJ_ENEMY);
		m_get_line = ene->GetLine();//選択Line取得
	}

	CObjPlanet* pla = (CObjPlanet*)Objs::GetObj(OBJ_PLANET);
	m_mov_spd = 1.0f / pla->GetX();

	if (m_get_line == 1) { m_y = 310; }	//取得Lineナンバーで高さ変更
	else if (m_get_line == 2) { m_y = 420; }

}

//アクション
void CObjRktHit::Action()
{
	CHitBox* hit = Hits::GetHitBox(this);		//HitBox情報取得
	hit->SetPos(m_x, m_y, m_size, m_size);		//HitBox更新

	if (m_del_f == true)	//削除フラグ
	{
		m_del_cnt++;
		if (m_del_cnt == 7)//削除
		{
			this->SetStatus(false);
			Hits::DeleteHitBox(this);
		}
	}

	m_vx = 0.0f;
	m_vy = 0.0f;

	if (m_stop_f == true)	//ポッド戦闘中
	{
			
	}
	else					//ポッド移動中
	{
		m_mov += m_mov_spd / 2;
		hit->SetInvincibility(false);//HitBoxの無敵効果OFF

		//各ライン毎の動き方
		if (m_get_line == 0 || m_get_line == 3)//------上ライン----
		{
			m_vx -= 0.3f;
			m_vy += (-0.15 + m_mov);
		}
		else if (m_get_line == 1)//----------------中ライン-----
		{
			m_vx -= 0.5f;
		}
		else//if(m_get_line == 2)---------------下ライン------
		{
			m_vx -= 0.3f;
			m_vy -= (-0.15 + m_mov);
		}

		//-----------------------------座標更新
		if (m_type == 0) {
			m_x += m_vx * 2 - m_mov_spd * 200;	//(約0.8 or 1.2)
			m_y += m_vy * 2;
		}
		else {
			m_x -= m_vx * 2 - m_mov_spd * 200;
			m_y += m_vy * 2;
		}
	}

	
	if (m_type == false && hit->CheckElementHit(ELEMENT_NULL))		//thisが味方 かつ敵のHitBoxに当たった時
	{
		m_stop_f = true;		//停止
		if (hit->CheckElementHit(ELEMENT_POD) == true)		//味方のPODに当たった時
		{
			m_del_f = false;
		}
		else
			m_del_f = true;	//削除
	}
	else if (m_type == true && hit->CheckElementHit(ELEMENT_NULL))	//thisが敵 かつ味方のHitBoxに当たった時
	{
		m_stop_f = true;
		if (hit->CheckElementHit(ELEMENT_ENEMYPOD) == true)	//敵ポッドに当たった時
		{
			m_del_f = false;	//停止
		}
		else
			m_del_f = true;	//削除
	}
	else
		m_stop_f = false;

	if (hit->CheckElementHit(ELEMENT_ENEMY) == true || hit->CheckElementHit(ELEMENT_PLAYER) == true)
		m_del_f = true;

	if (hit->CheckElementHit(ELEMENT_NULL) == true)
		m_stop_f = true;
}

//ドロー
void CObjRktHit::Draw()
{
	;
}