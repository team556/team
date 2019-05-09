//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjPlanet.h"

#include <time.h>

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjPlanet::CObjPlanet(float x, float y, float hp, bool type, float siz)
{
	//�쐬���ɓn���ꂽ�l���A�e�X�e�[�^�X�ɑ��
	m_px = x;
	m_py = y;
	m_hp = hp;
	m_type = type;
	m_get_siz = siz;
}

//�C�j�V�����C�Y
void CObjPlanet::Init()
{
	//�e�X�e�[�^�X������
	m_size	 = 50.0f;//�T�C�Y
	m_siz_max= 50.0f;
	m_siz_vec=  0.0f;

	m_cnt = 0;		//�J�E���g

	m_get_hp = 0;	//�擾HP

	CObjFight* fit = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
	m_mov_spd = 0.093f* 30 / (fit->GetCount() / 70);//�������x
	m_siz_spd = 0.07f * 30 / (fit->GetCount() / 40);//�g�呬�x

	if (m_type == true)
		m_px += (fit->GetCount() / 30);
	else
		m_px -= (fit->GetCount() / 30);

	m_ani[0] = 0;//�A�j���[�V�����f�[�^�̏�����
	m_ani[1] = 1;
	m_ani[2] = 2;
	m_ani[3] = 1;
	m_ani_frame = 0;
	m_ani_time = 0;

	m_eat_f = false;	//�򂤃t���O(true = ��)
	m_eat_spd = fit->GetCount();
	m_del_f = false;	//�����t���O(true = ����)
	
	//�����蔻��pHitBox���쐬
	if(m_type == true)
		Hits::SetHitBox(this, m_px, m_py, m_size, m_size, ELEMENT_PLAYER, OBJ_PLANET, 1);
	else
		Hits::SetHitBox(this, m_px, m_py, m_size, m_size, ELEMENT_ENEMY, OBJ_PLANET, 1);
}

//�A�N�V����
void CObjPlanet::Action()
{
	CObjFight* fit = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
	if (fit->GetCount() != 0)		//�ΐ펞�Ԃ�0�łȂ��ꍇ
		m_siz_vec += m_siz_spd; //�g�����x�N�g���ɉ��Z


	CHitBox* hit = Hits::GetHitBox(this);	//CHitBox�|�C���^�擾
	if (((hit->CheckElementHit(ELEMENT_ENEMY) == true)
		|| (hit->CheckElementHit(ELEMENT_PLAYER) == true))	//���݂��������Ă��邩��
		&& (m_cnt < (2.5 * 60) * m_mov_spd)) {		//2.5�b�J�E���g���ĂȂ��ꍇ
		m_cnt++;
	}


	//-------------------------------------------------�A�j���[�V�����A���̓���
	if (m_ani_time == 60) {	//�t���[���؂�ւ�����
		m_ani_time = 0;		//�^�C�����Z�b�g
		m_ani_frame++;		//�t���[���؂�ւ�
		if (m_ani_frame == 4) {			//�ŏI�����t���[���ɂ���O
			m_eat_f = false;	//�H�ׂ�t���O��OFF
			m_ani_time = -1;							//���[�v���䁙
			if (m_type == true) {
				CObjFightClear* crer = new CObjFightClear();	//��l���̏ꍇ
				Objs::InsertObj(crer, OBJ_FIGHT_CLEAR, 15);	//�N���A���
			}
			else {
				CObjFightOver* over = new CObjFightOver();	//�G�̏ꍇ
				Objs::InsertObj(over, OBJ_FIGHT_CLEAR, 15);	//�Q�[���I�[�o�[���
			}
		}
	}
				//2.5�b
	if (m_cnt < (2.5 * 60) * m_mov_spd)	//�J�E���g���I����ĂȂ��ꍇ
		if (m_type == true)				//(�퓬��)
			m_px -= m_mov_spd;	//�����̓���
		else
			m_px += m_mov_spd;	//�G���̓���
	else { 						//�J�E���g���I������� (��~��)
		if (m_ani_time == 0) {					//time�Ń��[�v���䁙
			if (m_type == true) {
				m_hp -= 1;//
				CObjPlanet* ene2 = (CObjPlanet*)Objs::GetObj(OBJ_ENEMY2);
				if(ene2 != nullptr)
					m_get_hp = ene2->GetHp();
			}
			else {
				CObjPlanet* pla = (CObjPlanet*)Objs::GetObj(OBJ_PLANET);
				if (pla != nullptr)
					m_get_hp = pla->GetHp();
			}
			if (m_hp > m_get_hp) {
				m_eat_f = true;		//�򂤃t���O�L��
				fit->SetEndF();
			}
		}
	}

	if (m_eat_f == true) {	//�H�ׂ�t���O������
		m_ani_time++;		//ani_time ���Z
		if ((m_ani_frame == 3) && (m_ani_time == 1)) {//�������u��
			m_size += m_size;					//�T�C�Y�ύX(�{)
			if (m_type == true) {
				CObjPlanet* ene = (CObjPlanet*)Objs::GetObj(OBJ_ENEMY);
				ene->SetDelF();
			}
			else {
				CObjPlanet* pla = (CObjPlanet*)Objs::GetObj(OBJ_PLANET);
				pla->SetDelF();
			}	
		}
	}
	else
		m_ani_frame = 0;	//�����t���[��

	if (m_ani_frame == 2)		//�򂤃t���[���̈ړ�
		if (m_type == true)
			m_px -= m_mov_spd + m_eat_spd/160;
		else
			m_px += m_mov_spd + m_eat_spd/160;
		
	//-------------------------------------------------------------

	
	hit->SetPos(m_px - m_siz_vec - m_size,	//HitBox�X�V
				m_py - m_siz_vec - m_size,		
				2 * m_siz_vec + m_size * 2,
				2 * m_siz_vec + m_size * 2);

	//���_���[�W����
	if ((hit->CheckElementHit(ELEMENT_MAGIC) == true) && (m_type == false) && (m_hp > 0))
	{							//�~�T�C���ɓ��������ꍇ
		m_hp -= 1;				//HP-1
		m_size -= m_size / 10;	//�T�C�Y����
	}
	else if ((hit->CheckElementHit(ELEMENT_RED) == true) && (m_type == true) && (m_hp > 0))
	{
		m_hp -= 1;				//HP-1
		m_size -= m_size / 10;	//�T�C�Y����
	}

	if (m_del_f == true) {				//�����t���O���聕����
		this->SetStatus(false);	 //�I�u�W�F�N�g�폜
		Hits::DeleteHitBox(this);//HitBox�폜
	}

	//���G�f���U���p�^�[��
	if (m_type == false)
	{
		srand(time(NULL));
		m_attackf = rand() % 4 + 1;

		if (m_attackf == 1 && m_time <= 0)
		{
			CObjMissile* M = new CObjMissile(575, 200, false);//�I�u�W�F�N�g�쐬
			Objs::InsertObj(M, OBJ_MISSILE, 10);		//�I�u�W�F�N�g�o�^
			m_time = 100;
		}
		else if (m_attackf == 2 && m_time <= 0)
		{
			CObjMissile* M = new CObjMissile(575, 200, false);//�I�u�W�F�N�g�쐬
			Objs::InsertObj(M, OBJ_MISSILE, 10);		//�I�u�W�F�N�g�o�^
			m_time = 100;
		}
		else if (m_attackf == 3 && m_time <= 0)
		{
			CObjMissile* M = new CObjMissile(575, 200, false);//�I�u�W�F�N�g�쐬
			Objs::InsertObj(M, OBJ_MISSILE, 10);		//�I�u�W�F�N�g�o�^
			m_time = 100;
		}
		else if (m_attackf == 4 && m_time <= 0)
		{
			CObjMissile* M = new CObjMissile(575, 200, false);//�I�u�W�F�N�g�쐬
			Objs::InsertObj(M, OBJ_MISSILE, 10);		//�I�u�W�F�N�g�o�^
			m_time = 100;
		}

		m_time--;
	}
}

//�h���[
void CObjPlanet::Draw()
{
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	RECT_F src;
	RECT_F dst;
	//�؂���ʒu
	src.m_top   =  0.0f;
	src.m_left  = m_ani[m_ani_frame] * 64.0f;
	src.m_right = m_ani[m_ani_frame] * 64.0f + 64.0f;
	src.m_bottom= 64.0f;
	//�\���ʒu
	if(m_get_siz == 0){
		dst.m_top   = m_py - m_siz_vec - m_size;//300
		dst.m_left  = m_px - m_siz_vec - m_size;//800
		dst.m_right = m_px + m_siz_vec + m_size;
		dst.m_bottom= m_py + m_siz_vec + m_size;
	}
	else {
		dst.m_top   = m_py;//300
		dst.m_left  = m_px;//800
		dst.m_right = m_px + (m_get_siz * 2);
		dst.m_bottom= m_py + (m_get_siz * 2);
	}

	//0�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
	Draw::Draw(3, &src, &dst, c, 0.0f);
}
