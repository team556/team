//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

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

	m_pod_nam = (g_Power_num + g_Defense_num + g_Speed_num + g_Balance_num) / 1200;//�e�|�b�h�̏Z������

	if (m_type == false)
	{								//����HitBox�쐬
		CObjFight* fit = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
		m_get_line = fit->GetLine();//�I��Line�擾

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
	{								//�GHitBox�쐬
		CObjPlanet* ene = (CObjPlanet*)Objs::GetObj(OBJ_ENEMY);
		m_get_line = ene->GetLine();//�I��Line�擾

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

	if (m_get_line == 1) { m_y = 310; }	//�擾Line�i���o�[�ō����ύX
	else if (m_get_line == 2) { m_y = 420; }

}

//�A�N�V����
void CObjRktHit::Action()
{
	//���X�y�V�����Z�̎��͑���s�\�ɂ��鏈��
	if (battle_start == false )
	{
		return;
	}

	CHitBox* hit = Hits::GetHitBox(this);		//HitBox���擾
	hit->SetPos(m_x, m_y, m_size, m_size);		//HitBox�X�V
	m_vx = 0.0f;
	m_vy = 0.0f;

	if (m_fight == true) {
		m_ani_time++;								//�A�j���[�V��������
		if(m_ani_frame == 0 && m_ani_time == 1)
			Audio::Start(11);
		if (m_ani_time == 6) {		//�t���[���؂�ւ��^�C�~���O
			m_ani_time = 0;
			m_ani_frame++;
			if (m_ani_frame == 8) {	//�t���[�����[�v�l
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
	

	if (m_stop_f == true)	//�|�b�h�퓬��
	{
		
	}
	else					//�|�b�h�ړ���
	{
		m_mov += m_mov_spd / 2;

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

	//�v���C���[�̃~�T�C���|�b�h���G�l�~�[�̃X�y�V�����Z(FRACTURE_RAY)�̃I�u�W�F�N�gHIT���A
	//HP�̏�ԂɊւ�炸���ŏ����ւƈڍs����
	if (hit->CheckObjNameHit(OBJ_FRACTURE_RAY, 1) != nullptr && //�G�l�~�[�̃X�y�V�����Z��HIT���A
		m_type == false)										//�v���C���[�̎ˏo�����|�b�h�ł���ꍇ�A���s
	{
		m_del_f = true;				//���ŏ����t���OON
	}

	//�G�l�~�[�̃~�T�C���|�b�h���v���C���[�̃X�y�V�����Z(FRACTURE_RAY)�̃I�u�W�F�N�gHIT���A
	//HP�̏�ԂɊւ�炸���ŏ����ւƈڍs����
	if (hit->CheckObjNameHit(OBJ_FRACTURE_RAY, 0) != nullptr && //�v���C���[�̃X�y�V�����Z��HIT���A
		m_type == true)											//�G�l�~�[�̎ˏo�����|�b�h�ł���ꍇ�A���s
	{
		m_del_f = true;				//���ŏ����t���OON
	}
	
	if (m_type == false && hit->CheckElementHit(ELEMENT_NULL) == true)		//this������ ����HitBox�ɓ���������
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
				m_del_f = true;	//�폜
			}
			else 
				m_del_f = false;
		}
		else
			m_fight = false;
	}

	else if (m_type == true && hit->CheckElementHit(ELEMENT_NULL) == true)	//this���G ����HitBox�ɓ���������
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
				m_del_f = true;	//�폜
			}
			else
				m_del_f = false;
		}
		else
			m_fight = false;
	}
	else
		m_stop_f = false;

	if ((hit->CheckObjNameHit(OBJ_eRKTHIT) != nullptr ||//�GHitBox�ɓ���������
		hit->CheckObjNameHit(OBJ_eRKTHIT1) != nullptr ||
		hit->CheckObjNameHit(OBJ_eRKTHIT2) != nullptr ||
		hit->CheckObjNameHit(OBJ_eRKTHIT3) != nullptr ||
		hit->CheckObjNameHit(OBJ_eRKTHIT4) != nullptr ||
		hit->CheckObjNameHit(OBJ_eRKTHIT5) != nullptr ||
		hit->CheckObjNameHit(OBJ_eRKTHIT6) != nullptr ||
		hit->CheckObjNameHit(OBJ_eRKTHIT7) != nullptr ||
		hit->CheckObjNameHit(OBJ_eRKTHIT8) != nullptr ||
		hit->CheckObjNameHit(OBJ_eRKTHIT9) != nullptr)&&
		(hit->CheckObjNameHit(OBJ_RKTHIT) != nullptr ||//����HitBox�ɓ���������
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

	if (hit->CheckElementHit(ELEMENT_PLAYER) == true && m_type == true)		//�f���ɓ������������G�e
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);
	}
	else if (hit->CheckElementHit(ELEMENT_ENEMY) == true && m_type == false)//�G���ɓ��������������e
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);
	}

	if (m_del_f == true || battle_end == true)	//�폜�t���O
	{
		m_del_cnt++;
		if (m_del_cnt == 4)//�폜
		{
			this->SetStatus(false);
			Hits::DeleteHitBox(this);
		}
	}
	else
		m_del_cnt = 0;

	
}

//�h���[
void CObjRktHit::Draw()
{
	float d[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	RECT_F src;
	RECT_F dst;

	//�؂���ʒu
	src.m_top   =  0.0f;
	src.m_left  = m_ani[m_ani_frame] * 24.0f;
	src.m_right = m_ani[m_ani_frame] * 24.0f + 24.0f;
	src.m_bottom= 32.0f;
	//�\���ʒu
	
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