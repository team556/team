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
	m_del_cnt = 0;
	m_stop_f = false;
	m_del_f = false;

	if (m_type == false)
	{								//����HitBox�쐬
		Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_NULL, OBJ_RKTHIT, 1);
		CObjFight* fit = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
		m_get_line = fit->GetLine();//�I��Line�擾
	}
	else
	{								//�GHitBox�쐬
		Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_NULL, OBJ_RKTHIT, 1);
		CObjPlanet* ene = (CObjPlanet*)Objs::GetObj(OBJ_ENEMY);
		m_get_line = ene->GetLine();//�I��Line�擾
	}

	CObjPlanet* pla = (CObjPlanet*)Objs::GetObj(OBJ_PLANET);
	m_mov_spd = 1.0f / pla->GetX();

	if (m_get_line == 1) { m_y = 310; }	//�擾Line�i���o�[�ō����ύX
	else if (m_get_line == 2) { m_y = 420; }

}

//�A�N�V����
void CObjRktHit::Action()
{
	CHitBox* hit = Hits::GetHitBox(this);		//HitBox���擾
	hit->SetPos(m_x, m_y, m_size, m_size);		//HitBox�X�V

	if (m_del_f == true)	//�폜�t���O
	{
		m_del_cnt++;
		if (m_del_cnt == 7)//�폜
		{
			this->SetStatus(false);
			Hits::DeleteHitBox(this);
		}
	}

	m_vx = 0.0f;
	m_vy = 0.0f;

	if (m_stop_f == true)	//�|�b�h�퓬��
	{
			
	}
	else					//�|�b�h�ړ���
	{
		m_mov += m_mov_spd / 2;
		hit->SetInvincibility(false);//HitBox�̖��G����OFF

		//�e���C�����̓�����
		if (m_get_line == 0 || m_get_line == 3)//------�ド�C��----
		{
			m_vx -= 0.3f;
			m_vy += (-0.15 + m_mov);
		}
		else if (m_get_line == 1)//----------------�����C��-----
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

	
	if (m_type == false && hit->CheckElementHit(ELEMENT_NULL))		//this������ ���G��HitBox�ɓ���������
	{
		m_stop_f = true;		//��~
		if (hit->CheckElementHit(ELEMENT_POD) == true)		//������POD�ɓ���������
		{
			m_del_f = false;
		}
		else
			m_del_f = true;	//�폜
	}
	else if (m_type == true && hit->CheckElementHit(ELEMENT_NULL))	//this���G ��������HitBox�ɓ���������
	{
		m_stop_f = true;
		if (hit->CheckElementHit(ELEMENT_ENEMYPOD) == true)	//�G�|�b�h�ɓ���������
		{
			m_del_f = false;	//��~
		}
		else
			m_del_f = true;	//�폜
	}
	else
		m_stop_f = false;

	if (hit->CheckElementHit(ELEMENT_ENEMY) == true || hit->CheckElementHit(ELEMENT_PLAYER) == true)
		m_del_f = true;

	if (hit->CheckElementHit(ELEMENT_NULL) == true)
		m_stop_f = true;
}

//�h���[
void CObjRktHit::Draw()
{
	;
}