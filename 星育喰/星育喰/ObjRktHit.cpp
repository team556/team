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
	m_vx	= 0.0f;
	m_vy	= 0.0f;
	m_mov	= 0.0f;
	m_size = 50.0f;
	m_del_cnt = 0;
	m_pnam = p_pnam -1;
	m_enam = e_pnam -1;
	m_stop_f = false;
	m_del_f = false;

	m_pod_nam = (g_Power_num + g_Defense_num + g_Speed_num + g_Balance_num) / 1200;//各ポッドの住民総数

	if (m_type == false)
	{								//味方HitBox作成
		CObjFight* fit = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
		m_get_line = fit->GetLine();//選択Line取得

		switch (m_pnam) {
		case 0:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_NULL, OBJ_RKTHIT, 1); break;
		case 1:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_NULL, OBJ_RKTHIT1, 1); break;
		case 2:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_NULL, OBJ_RKTHIT2, 1); break;
		case 3:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_NULL, OBJ_RKTHIT3, 1); break;
		case 4:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_NULL, OBJ_RKTHIT4, 1); break;
		case 5:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_NULL, OBJ_RKTHIT5, 1); break;
		case 6:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_NULL, OBJ_RKTHIT6, 1); break;
		case 7:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_NULL, OBJ_RKTHIT7, 1); break;
		case 8:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_NULL, OBJ_RKTHIT8, 1); break;
		case 9:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_NULL, OBJ_RKTHIT9, 1); break;
		}
	}
	else
	{								//敵HitBox作成
		CObjPlanet* ene = (CObjPlanet*)Objs::GetObj(OBJ_ENEMY);
		m_get_line = ene->GetLine();//選択Line取得

		switch (m_enam) {
		case 0:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_NULL, OBJ_eRKTHIT, 1); break;
		case 1:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_NULL, OBJ_eRKTHIT1, 1); break;
		case 2:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_NULL, OBJ_eRKTHIT2, 1); break;
		case 3:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_NULL, OBJ_eRKTHIT3, 1); break;
		case 4:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_NULL, OBJ_eRKTHIT4, 1); break;
		case 5:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_NULL, OBJ_eRKTHIT5, 1); break;
		case 6:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_NULL, OBJ_eRKTHIT6, 1); break;
		case 7:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_NULL, OBJ_eRKTHIT7, 1); break;
		case 8:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_NULL, OBJ_eRKTHIT8, 1); break;
		case 9:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_NULL, OBJ_eRKTHIT9, 1); break;
		}
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
			m_vx -= 0.3f;
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

	
	if (m_type == false && hit->CheckElementHit(ELEMENT_NULL) == true)		//thisが味方 かつ敵のHitBoxに当たった時
	{
		m_stop_f = true;		//停止
		if ((hit->CheckElementHit(ELEMENT_POD) == true ||
			hit->CheckElementHit(ELEMENT_POD1) == true ||
			hit->CheckElementHit(ELEMENT_POD2) == true ||
			hit->CheckElementHit(ELEMENT_POD3) == true ||
			hit->CheckElementHit(ELEMENT_POD4) == true) == true)		//味方のPODに当たった時
		{
			m_del_f = false;
		}
		else
			m_del_f = true;	//削除
	}
	else if (m_type == true && hit->CheckElementHit(ELEMENT_NULL) == true)	//thisが敵 かつ味方のHitBoxに当たった時
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

	/*if (hit->CheckElementHit(ELEMENT_ENEMY) == true || hit->CheckElementHit(ELEMENT_PLAYER) == true)
		m_del_f = true;*/

	if (m_del_f == true || battle_end == true)	//削除フラグ
	{
		m_del_cnt++;
		if (m_del_cnt == 7)//削除
		{
			this->SetStatus(false);
			Hits::DeleteHitBox(this);
		}
	}
}

//ドロー
void CObjRktHit::Draw()
{
	;
}