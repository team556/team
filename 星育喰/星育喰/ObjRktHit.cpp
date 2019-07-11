//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjRktHit.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjRktHit::CObjRktHit(float x, float y, bool t)
{
	//�쐬���ɓn���ꂽ�l���A���W�̏����l�ɑ��
	m_type = t;
	if(t == false)
		m_x = x - 50.0f;
	else
		m_x = x + 50.0f;
	m_y = y;
}

//�C�j�V�����C�Y
void CObjRktHit::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;

	m_mov = 0.0f;
	m_size = 50.0f;
	m_atk_f = false;

	if (m_type == false)
	{
		Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_BLUE, OBJ_RKTHIT, 1);
		CObjFight* fit = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
		m_get_line = fit->GetLine();
	}
	else
	{
		Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_RED, OBJ_RKTHIT, 1);
		CObjPlanet* ene = (CObjPlanet*)Objs::GetObj(OBJ_ENEMY);
		m_get_line = ene->GetLine();
	}

	CObjPlanet* pla = (CObjPlanet*)Objs::GetObj(OBJ_PLANET);
	m_mov_spd = 1.0f / pla->GetX();

	if (m_get_line == 1) { m_y = 310; }	//�擾�i���o�[�ō����ύX
	else if (m_get_line == 2) { m_y = 420; }

}

//�A�N�V����
void CObjRktHit::Action()
{
	m_vx = 0.0f;
	m_vy = 0.0f;

	if (m_atk_f == true)
	{

	}
	else
	{
		m_mov += m_mov_spd / 2;

		//�e���C�����̓�����
		if (m_get_line == 0 || m_get_line == 3)//------�ド�C��----
		{
			m_vx -= 0.3f;
			m_vy += (-0.15 + m_mov);
		}
		else if (m_get_line == 1)//---------------�����C��-----
		{
			m_vx -= 0.5f;
		}
		else//if(m_get_line == 2)---------------�����C��------
		{
			m_vx -= 0.3f;
			m_vy -= (-0.15 + m_mov);
		}

		//-----------------------------���W�X�V
		if (m_type == 0) {
			m_x += m_vx * 2 - m_mov_spd * 200;	//(��0.8 or 1.2)
			m_y += m_vy * 2;
		}
		else {
			m_x -= m_vx * 2 - m_mov_spd * 200;
			m_y += m_vy * 2;
		}
	}

	CHitBox* hit = Hits::GetHitBox(this);		//HitBox���擾
	if (m_type == false) 
	{
		if (hit->CheckElementHit(ELEMENT_RED) == true)
		{
			m_atk_f = true;

		}
	}
	else
	{
		if (hit->CheckElementHit(ELEMENT_BLUE) == true)
		{
			m_atk_f = true;
		}
	}
	hit->SetPos(m_x, m_y, m_size, m_size);		//HitBox�X�V

}

//�h���[
void CObjRktHit::Draw()
{
	;
}