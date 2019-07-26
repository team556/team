//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

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

	m_ani[0] = 0;
	m_ani[1] = 1;
	m_ani[2] = 2;
	m_ani[3] = 3;
	m_ani[4] = 4;
	m_ani[5] = 5;
	m_ani[6] = 6;
	m_ani[7] = 7;
	m_ani_frame = 0;
	m_ani_time = 0;

	m_pnam = p_pnam;
	m_enam = e_pnam;
	m_stop_f = false;
	m_del_f = false;
	m_fight = false;
	//m_audio_f = false;

	m_pod_nam = (g_Power_num + g_Defense_num + g_Speed_num + g_Balance_num) / 1200;//各ポッドの住民総数

	if (m_type == false)
	{								//味方HitBox作成
		CObjFight* fit = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
		m_get_line = fit->GetLine();//選択Line取得

		switch (m_pnam) {
		case 0:Hits::SetHitBox(this, m_x, m_y, m_size, m_size - 1, ELEMENT_NULL, OBJ_RKTHIT, 1); break;
		case 1:Hits::SetHitBox(this, m_x, m_y, m_size, m_size - 1, ELEMENT_NULL, OBJ_RKTHIT1, 1); break;
		case 2:Hits::SetHitBox(this, m_x, m_y, m_size, m_size - 1, ELEMENT_NULL, OBJ_RKTHIT2, 1); break;
		case 3:Hits::SetHitBox(this, m_x, m_y, m_size, m_size - 1, ELEMENT_NULL, OBJ_RKTHIT3, 1); break;
		case 4:Hits::SetHitBox(this, m_x, m_y, m_size, m_size - 1, ELEMENT_NULL, OBJ_RKTHIT4, 1); break;
		case 5:Hits::SetHitBox(this, m_x, m_y, m_size, m_size - 1, ELEMENT_NULL, OBJ_RKTHIT5, 1); break;
		case 6:Hits::SetHitBox(this, m_x, m_y, m_size, m_size - 1, ELEMENT_NULL, OBJ_RKTHIT6, 1); break;
		case 7:Hits::SetHitBox(this, m_x, m_y, m_size, m_size - 1, ELEMENT_NULL, OBJ_RKTHIT7, 1); break;
		case 8:Hits::SetHitBox(this, m_x, m_y, m_size, m_size - 1, ELEMENT_NULL, OBJ_RKTHIT8, 1); break;
		case 9:Hits::SetHitBox(this, m_x, m_y, m_size, m_size - 1, ELEMENT_NULL, OBJ_RKTHIT9, 1); break;
		}
	}
	else
	{								//敵HitBox作成
		CObjPlanet* ene = (CObjPlanet*)Objs::GetObj(OBJ_ENEMY);
		m_get_line = ene->GetLine();//選択Line取得

		switch (m_enam) {
		case 0:Hits::SetHitBox(this, m_x, m_y, m_size, m_size + 1, ELEMENT_NULL, OBJ_eRKTHIT, 1); break;
		case 1:Hits::SetHitBox(this, m_x, m_y, m_size, m_size + 1, ELEMENT_NULL, OBJ_eRKTHIT1, 1); break;
		case 2:Hits::SetHitBox(this, m_x, m_y, m_size, m_size + 1, ELEMENT_NULL, OBJ_eRKTHIT2, 1); break;
		case 3:Hits::SetHitBox(this, m_x, m_y, m_size, m_size + 1, ELEMENT_NULL, OBJ_eRKTHIT3, 1); break;
		case 4:Hits::SetHitBox(this, m_x, m_y, m_size, m_size + 1, ELEMENT_NULL, OBJ_eRKTHIT4, 1); break;
		case 5:Hits::SetHitBox(this, m_x, m_y, m_size, m_size + 1, ELEMENT_NULL, OBJ_eRKTHIT5, 1); break;
		case 6:Hits::SetHitBox(this, m_x, m_y, m_size, m_size + 1, ELEMENT_NULL, OBJ_eRKTHIT6, 1); break;
		case 7:Hits::SetHitBox(this, m_x, m_y, m_size, m_size + 1, ELEMENT_NULL, OBJ_eRKTHIT7, 1); break;
		case 8:Hits::SetHitBox(this, m_x, m_y, m_size, m_size + 1, ELEMENT_NULL, OBJ_eRKTHIT8, 1); break;
		case 9:Hits::SetHitBox(this, m_x, m_y, m_size, m_size + 1, ELEMENT_NULL, OBJ_eRKTHIT9, 1); break;
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
	//▼スペシャル技の時は操作不能にする処理
	if (battle_start == false )
	{
		return;
	}

	CHitBox* hit = Hits::GetHitBox(this);		//HitBox情報取得
	hit->SetPos(m_x, m_y, m_size, m_size);		//HitBox更新
	m_vx = 0.0f;
	m_vy = 0.0f;

	if (m_fight == true) {
		m_ani_time++;								//アニメーション処理
		if(m_ani_frame == 0 && m_ani_time == 1)
			Audio::Start(11);
		if (m_ani_time == 6) {		//フレーム切り替えタイミング
			m_ani_time = 0;
			m_ani_frame++;
			if (m_ani_frame == 8) {	//フレームループ値
				m_ani_frame = 0;
				m_fight = false;
			}
		}
		/*if (m_audio_f == false) {
			Audio::Start(11);
			m_audio_f = true;
		}*/
	}
	else {
		m_ani_time = 0;
		m_ani_frame = 0;
		//m_audio_f = false;
	}
	

	if (m_stop_f == true)	//ポッド戦闘中
	{
		
	}
	else					//ポッド移動中
	{
		m_mov += m_mov_spd / 2;

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

	//プレイヤーのミサイルポッドがエネミーのスペシャル技(FRACTURE_RAY)のオブジェクトHIT時、
	//HPの状態に関わらず消滅処理へと移行する
	if (hit->CheckObjNameHit(OBJ_FRACTURE_RAY, 1) != nullptr && //エネミーのスペシャル技にHITかつ、
		m_type == false)										//プレイヤーの射出したポッドである場合、実行
	{
		m_del_f = true;				//消滅処理フラグON
	}

	//エネミーのミサイルポッドがプレイヤーのスペシャル技(FRACTURE_RAY)のオブジェクトHIT時、
	//HPの状態に関わらず消滅処理へと移行する
	if (hit->CheckObjNameHit(OBJ_FRACTURE_RAY, 0) != nullptr && //プレイヤーのスペシャル技にHITかつ、
		m_type == true)											//エネミーの射出したポッドである場合、実行
	{
		m_del_f = true;				//消滅処理フラグON
	}
	
	if (m_type == false && hit->CheckElementHit(ELEMENT_NULL) == true)		//thisが味方 かつHitBoxに当たった時
	{
		if (hit->CheckObjNameHit(OBJ_RKTHIT) != nullptr && (m_pnam >= 1 && m_pnam <= 3))
			m_stop_f = true;
		else if (hit->CheckObjNameHit(OBJ_RKTHIT1) != nullptr && (m_pnam >= 2 && m_pnam <= 4))
			m_stop_f = true;
		else if (hit->CheckObjNameHit(OBJ_RKTHIT2) != nullptr && (m_pnam >= 3 && m_pnam <= 5))
			m_stop_f = true;
		else if (hit->CheckObjNameHit(OBJ_RKTHIT3) != nullptr && (m_pnam >= 4 && m_pnam <= 6))
			m_stop_f = true;
		else if (hit->CheckObjNameHit(OBJ_RKTHIT4) != nullptr && (m_pnam >= 5 && m_pnam <= 7))
			m_stop_f = true;
		else if (hit->CheckObjNameHit(OBJ_RKTHIT5) != nullptr && (m_pnam >= 6 && m_pnam <= 8))
			m_stop_f = true;
		else if (hit->CheckObjNameHit(OBJ_RKTHIT6) != nullptr && (m_pnam >= 7 && m_pnam <= 9))
			m_stop_f = true;
		else if (hit->CheckObjNameHit(OBJ_RKTHIT7) != nullptr && (m_pnam >= 8 || m_pnam <= 0))
			m_stop_f = true;
		else if (hit->CheckObjNameHit(OBJ_RKTHIT8) != nullptr && (m_pnam >= 9 || m_pnam <= 1))
			m_stop_f = true;
		else if (hit->CheckObjNameHit(OBJ_RKTHIT9) != nullptr && (m_pnam >= 0 || m_pnam <= 2))
			m_stop_f = true;
		else
			m_stop_f = false;

		if (hit->CheckObjNameHit(OBJ_eRKTHIT) != nullptr ||
			hit->CheckObjNameHit(OBJ_eRKTHIT1) != nullptr ||
			hit->CheckObjNameHit(OBJ_eRKTHIT2) != nullptr ||
			hit->CheckObjNameHit(OBJ_eRKTHIT3) != nullptr ||
			hit->CheckObjNameHit(OBJ_eRKTHIT4) != nullptr ||
			hit->CheckObjNameHit(OBJ_eRKTHIT5) != nullptr ||
			hit->CheckObjNameHit(OBJ_eRKTHIT6) != nullptr ||
			hit->CheckObjNameHit(OBJ_eRKTHIT7) != nullptr ||
			hit->CheckObjNameHit(OBJ_eRKTHIT8) != nullptr ||
			hit->CheckObjNameHit(OBJ_eRKTHIT9) != nullptr)
		{
			m_stop_f = true;
			m_fight = true;
			if (hit->CheckElementHit(ELEMENT_POD) == false &&
				hit->CheckElementHit(ELEMENT_POD1) == false &&
				hit->CheckElementHit(ELEMENT_POD2) == false &&
				hit->CheckElementHit(ELEMENT_POD3) == false &&
				hit->CheckElementHit(ELEMENT_POD4) == false &&
				hit->CheckElementHit(ELEMENT_POD5) == false &&
				hit->CheckElementHit(ELEMENT_POD6) == false &&
				hit->CheckElementHit(ELEMENT_POD7) == false &&
				hit->CheckElementHit(ELEMENT_POD8) == false &&
				hit->CheckElementHit(ELEMENT_POD9) == false) {
				m_del_f = true;	//削除
			}
			else 
				m_del_f = false;
		}
		else
			m_fight = false;
	}

	else if (m_type == true && hit->CheckElementHit(ELEMENT_NULL) == true)	//thisが敵 かつHitBoxに当たった時
	{
		if (hit->CheckObjNameHit(OBJ_eRKTHIT) != nullptr && (m_enam >= 1 && m_enam <= 3))
			m_stop_f = true;
		else if (hit->CheckObjNameHit(OBJ_eRKTHIT1) != nullptr && (m_enam >= 2 && m_enam <= 4))
			m_stop_f = true;
		else if (hit->CheckObjNameHit(OBJ_eRKTHIT2) != nullptr && (m_enam >= 3 && m_enam <= 5))
			m_stop_f = true;
		else if (hit->CheckObjNameHit(OBJ_eRKTHIT3) != nullptr && (m_enam >= 4 && m_enam <= 6))
			m_stop_f = true;
		else if (hit->CheckObjNameHit(OBJ_eRKTHIT4) != nullptr && (m_enam >= 5 && m_enam <= 7))
			m_stop_f = true;
		else if (hit->CheckObjNameHit(OBJ_eRKTHIT5) != nullptr && (m_enam >= 6 && m_enam <= 8))
			m_stop_f = true;
		else if (hit->CheckObjNameHit(OBJ_eRKTHIT6) != nullptr && (m_enam >= 7 && m_enam <= 9))
			m_stop_f = true;
		else if (hit->CheckObjNameHit(OBJ_eRKTHIT7) != nullptr && (m_enam >= 8 || m_enam <= 0))
			m_stop_f = true;
		else if (hit->CheckObjNameHit(OBJ_eRKTHIT8) != nullptr && (m_enam >= 9 || m_enam <= 1))
			m_stop_f = true;
		else if (hit->CheckObjNameHit(OBJ_eRKTHIT9) != nullptr && (m_enam >= 0 || m_enam <= 2))
			m_stop_f = true;
		else
			m_stop_f = false;

		if (hit->CheckObjNameHit(OBJ_RKTHIT) != nullptr ||
			hit->CheckObjNameHit(OBJ_RKTHIT1) != nullptr ||
			hit->CheckObjNameHit(OBJ_RKTHIT2) != nullptr ||
			hit->CheckObjNameHit(OBJ_RKTHIT3) != nullptr ||
			hit->CheckObjNameHit(OBJ_RKTHIT4) != nullptr ||
			hit->CheckObjNameHit(OBJ_RKTHIT5) != nullptr ||
			hit->CheckObjNameHit(OBJ_RKTHIT6) != nullptr ||
			hit->CheckObjNameHit(OBJ_RKTHIT7) != nullptr ||
			hit->CheckObjNameHit(OBJ_RKTHIT8) != nullptr ||
			hit->CheckObjNameHit(OBJ_RKTHIT9) != nullptr)
		{
			m_stop_f = true;
			m_fight = true;
			if (hit->CheckElementHit(ELEMENT_ENEMYPOD) == false &&
				hit->CheckElementHit(ELEMENT_ENEMYPOD1) == false &&
				hit->CheckElementHit(ELEMENT_ENEMYPOD2) == false &&
				hit->CheckElementHit(ELEMENT_ENEMYPOD3) == false &&
				hit->CheckElementHit(ELEMENT_ENEMYPOD4) == false &&
				hit->CheckElementHit(ELEMENT_ENEMYPOD5) == false &&
				hit->CheckElementHit(ELEMENT_ENEMYPOD6) == false &&
				hit->CheckElementHit(ELEMENT_ENEMYPOD7) == false &&
				hit->CheckElementHit(ELEMENT_ENEMYPOD8) == false &&
				hit->CheckElementHit(ELEMENT_ENEMYPOD9) == false){
				m_del_f = true;	//削除
			}
			else
				m_del_f = false;
		}
		else
			m_fight = false;
	}
	else
		m_stop_f = false;

	if ((hit->CheckObjNameHit(OBJ_eRKTHIT) != nullptr ||//敵HitBoxに当たった時
		hit->CheckObjNameHit(OBJ_eRKTHIT1) != nullptr ||
		hit->CheckObjNameHit(OBJ_eRKTHIT2) != nullptr ||
		hit->CheckObjNameHit(OBJ_eRKTHIT3) != nullptr ||
		hit->CheckObjNameHit(OBJ_eRKTHIT4) != nullptr ||
		hit->CheckObjNameHit(OBJ_eRKTHIT5) != nullptr ||
		hit->CheckObjNameHit(OBJ_eRKTHIT6) != nullptr ||
		hit->CheckObjNameHit(OBJ_eRKTHIT7) != nullptr ||
		hit->CheckObjNameHit(OBJ_eRKTHIT8) != nullptr ||
		hit->CheckObjNameHit(OBJ_eRKTHIT9) != nullptr)&&
		(hit->CheckObjNameHit(OBJ_RKTHIT) != nullptr ||//味方HitBoxに当たった時
		hit->CheckObjNameHit(OBJ_RKTHIT1) != nullptr ||
		hit->CheckObjNameHit(OBJ_RKTHIT2) != nullptr ||
		hit->CheckObjNameHit(OBJ_RKTHIT3) != nullptr ||
		hit->CheckObjNameHit(OBJ_RKTHIT4) != nullptr ||
		hit->CheckObjNameHit(OBJ_RKTHIT5) != nullptr ||
		hit->CheckObjNameHit(OBJ_RKTHIT6) != nullptr ||
		hit->CheckObjNameHit(OBJ_RKTHIT7) != nullptr ||
		hit->CheckObjNameHit(OBJ_RKTHIT8) != nullptr ||
		hit->CheckObjNameHit(OBJ_RKTHIT9) != nullptr))
	{
		m_fight = true;
	}

	if (hit->CheckElementHit(ELEMENT_PLAYER) == true && m_type == true)		//惑星に当たった時かつ敵弾
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);
	}
	else if (hit->CheckElementHit(ELEMENT_ENEMY) == true && m_type == false)//敵星に当たった時かつ自弾
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);
	}

	if (m_del_f == true || battle_end == true)	//削除フラグ
	{
		m_del_cnt++;
		if (m_del_cnt == 4)//削除
		{
			this->SetStatus(false);
			Hits::DeleteHitBox(this);
		}
	}
	else
		m_del_cnt = 0;

	
}

//ドロー
void CObjRktHit::Draw()
{
	float d[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	RECT_F src;
	RECT_F dst;

	//切り取り位置
	src.m_top   =  0.0f;
	src.m_left  = m_ani[m_ani_frame] * 24.0f;
	src.m_right = m_ani[m_ani_frame] * 24.0f + 24.0f;
	src.m_bottom= 32.0f;
	//表示位置
	
	dst.m_top    = m_y +22.0f;
	dst.m_left   = m_x;
	dst.m_right  = m_x + 50.0f;
	dst.m_bottom = m_y + 50.0f;
	if (m_type == true) {
		dst.m_left  = m_x + 50.0f;
		dst.m_right = m_x;
	}

	if(m_fight == true)
		Draw::Draw(123, &src, &dst, d, 0.0f);
}