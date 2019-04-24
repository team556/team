//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjPlanet.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjPlanet::CObjPlanet(float x, float y, bool type)
{
	//�쐬���ɓn���ꂽ�l���A���W�̏����l�ɑ��
	m_px = x;
	m_py = y;
	m_type = type;
}

//�C�j�V�����C�Y
void CObjPlanet::Init()
{
	m_size	 = 50.0f;
	m_siz_max= 50.0f;
	m_siz_vec=  0.0f;

	m_cnt = 0;

	m_hp = 10;

	CObjFight* obj = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
	m_mov_spd = 0.093f* 30 / (obj->GetCount() / 60);
	m_siz_spd = 0.07f * 30 / (obj->GetCount() / 60);

	m_ani[0] = 3;
	m_ani[1] = 4;
	m_ani[2] = 5;
	m_ani[3] = 4;
	m_ani_frame = 0;
	m_ani_time = 0;

	m_eat_f = false;
	
	//�����蔻��pHitBox���쐬
	if(m_type == true)
		Hits::SetHitBox(this, m_px, m_py, m_size, m_size, ELEMENT_PLAYER, OBJ_PLANET, 1);
	else
		Hits::SetHitBox(this, m_px, m_py, m_size, m_size, ELEMENT_ENEMY, OBJ_PLANET, 1);
}

//�A�N�V����
void CObjPlanet::Action()
{
	CObjFight* obj = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
	if (obj->GetCount() != 0)	//�ΐ펞�Ԃ�0�łȂ��ꍇ
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
		if (m_ani_frame == 4) {	//�ŏI�����t���[���ɂ���O
			m_eat_f = false;	//�H�ׂ�t���O��OFF
			m_ani_time = -1;							//���[�v���䁙
			//�I�u�W�F�N�g�쐬
			CObjFightClear* obj = new CObjFightClear();	//�I�u�W�F�N�g�쐬
			Objs::InsertObj(obj, OBJ_FIGHT_CLEAR, 10);	//�I�u�W�F�N�g�o�^
		}
	}
				//2.5�b
	if (m_cnt < (2.5 * 60) * m_mov_spd)//�J�E���g���I����ĂȂ��ꍇ
		if (m_type == true)
			m_px -= m_mov_spd;	//���ꂼ��ړ�������
		else
			m_px += m_mov_spd;
	else { 						//�J�E���g���I������� (��~��)
		if((m_type == true) && (m_ani_time == 0))	//time�Ń��[�v���䁙
			m_eat_f = true;	//�H�ׂ�t���O��ON
	}

	if (m_eat_f == true) {	//�H�ׂ�t���O������
		m_ani_time++;		//ani_time ���Z
		if((m_ani_frame == 3)&&(m_ani_time == 1))//�������u��
			m_size += m_size;					//�T�C�Y�ύX
	}
	else
		m_ani_frame = 0;	//�����t���[��

	if (m_ani_frame == 2)		//�򂤃t���[���̈ړ�
		m_px -= m_mov_spd * 20;	//�X�s�[�h�~20���Z
		
	//-------------------------------------------------------------

	
	hit->SetPos(m_px - m_siz_vec - m_size,	//HitBox�X�V
				m_py - m_siz_vec - m_size,		
				2 * m_siz_vec + m_size * 2,
				2 * m_siz_vec + m_size * 2);

	if ((hit->CheckElementHit(ELEMENT_MAGIC) == true) && (m_type == false) && (m_hp > 0))
	{							//�G�̃~�T�C���ɓ��������ꍇ
		m_hp -= 1;				//HP-1
		m_size -= m_size / 10;	//�T�C�Y����
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
	src.m_left  =  0.0f;
	src.m_right = 62.0f;
	src.m_bottom= 62.0f;
	//�\���ʒu
	dst.m_top   = m_py - m_siz_vec - m_size;//300
	dst.m_left  = m_px - m_siz_vec - m_size;//800
	dst.m_right = m_px + m_siz_vec + m_size;
	dst.m_bottom= m_py + m_siz_vec + m_size;

	//0�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
	Draw::Draw(m_ani[m_ani_frame], &src, &dst, c, 0.0f);
}
