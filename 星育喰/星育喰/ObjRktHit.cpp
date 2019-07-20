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
	m_vx	= 0.0f;
	m_vy	= 0.0f;
	m_mov	= 0.0f;
	m_size = 50.0f;
	m_del_cnt = 0;
	m_pnam = p_pnam -1;
	m_enam = e_pnam -1;
	m_stop_f = false;
	m_del_f = false;

	m_pod_nam = (g_Power_num + g_Defense_num + g_Speed_num + g_Balance_num) / 1200;//�e�|�b�h�̏Z������

	if (m_type == false)
	{								//����HitBox�쐬
		CObjFight* fit = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
		m_get_line = fit->GetLine();//�I��Line�擾

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
	{								//�GHitBox�쐬
		CObjPlanet* ene = (CObjPlanet*)Objs::GetObj(OBJ_ENEMY);
		m_get_line = ene->GetLine();//�I��Line�擾

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

	if (m_get_line == 1) { m_y = 310; }	//�擾Line�i���o�[�ō����ύX
	else if (m_get_line == 2) { m_y = 420; }

}

//�A�N�V����
void CObjRktHit::Action()
{
	CHitBox* hit = Hits::GetHitBox(this);		//HitBox���擾
	hit->SetPos(m_x, m_y, m_size, m_size);		//HitBox�X�V

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
			m_vx -= 0.3f;
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

	
	if (m_type == false && hit->CheckElementHit(ELEMENT_NULL) == true)		//this������ ���G��HitBox�ɓ���������
	{
		m_stop_f = true;		//��~
		if ((hit->CheckElementHit(ELEMENT_POD) == true ||
			hit->CheckElementHit(ELEMENT_POD1) == true ||
			hit->CheckElementHit(ELEMENT_POD2) == true ||
			hit->CheckElementHit(ELEMENT_POD3) == true ||
			hit->CheckElementHit(ELEMENT_POD4) == true) == true)		//������POD�ɓ���������
		{
			m_del_f = false;
		}
		else
			m_del_f = true;	//�폜
	}
	else if (m_type == true && hit->CheckElementHit(ELEMENT_NULL) == true)	//this���G ��������HitBox�ɓ���������
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

	/*if (hit->CheckElementHit(ELEMENT_ENEMY) == true || hit->CheckElementHit(ELEMENT_PLAYER) == true)
		m_del_f = true;*/

	if (m_del_f == true || battle_end == true)	//�폜�t���O
	{
		m_del_cnt++;
		if (m_del_cnt == 7)//�폜
		{
			this->SetStatus(false);
			Hits::DeleteHitBox(this);
		}
	}
}

//�h���[
void CObjRktHit::Draw()
{
	;
}