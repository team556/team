//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameHead.h"
#include "ObjHuman.h"
#include "UtilityModule.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjHuman::CObjHuman(float x, float y)
{
	//�쐬���ɓn���ꂽ�l���A���W�̏����l�ɑ��
	m_hx = x;
	m_hy = y;
}

//�C�j�V�����C�Y
void CObjHuman::Init()
{
	m_pos = 0;
	m_move = false;
	m_cnt = 0;
}

//�A�N�V����
void CObjHuman::Action()
{
	m_cnt++;

	if (m_cnt == 60) {
		m_pos = Rand(0, 3);
		m_move = true;
	}
	else if (m_cnt == 120) {
		m_cnt = 0;
		m_move = false;
	}

	if (m_move == true) {//�����Ă鎞
		switch (m_pos) {
		case 0:m_hx -= 1.0f; break;
		case 1:m_hy -= 1.0f; break;
		case 2:m_hy += 1.0f; break;
		case 3:m_hx += 1.0f; break;
		}
		m_ani_time += 1;//�A�j���[�V������i�߂�
	}
	else{
		m_ani_frame = 1;	//�L�[���͂��Ȃ��ꍇ�͐Î~�t���[���ɂ���
		m_ani_time = 0;		//�A�j���[�V�������~�߂�
	}

	if (m_ani_time > 6) {	//�A�j���[�V��������Ԋu
		m_ani_frame += 1;
		m_ani_time = 0;
	}

	if (m_ani_frame == 4)
		m_ani_frame = 0;	//�t���[��4��0�ɖ߂�
}

//�h���[
void CObjHuman::Draw()
{
	int AniData[4] = { 0,1,2,1, };

	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	RECT_F src;
	RECT_F dst;

	src.m_top   =  0.0f;
	src.m_left  =  0.0f;
	src.m_right =100.0f;
	src.m_bottom=100.0f;

	dst.m_top   = m_hy +  0.0f;
	dst.m_left  = m_hx +  0.0f;
	dst.m_right = m_hx + 50.0f;
	dst.m_bottom= m_hy + 50.0f;

	//0�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
	Draw::Draw(0, &src, &dst, c, 0.0f);
}