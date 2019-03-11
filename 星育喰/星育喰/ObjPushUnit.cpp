//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"
#include "ObjPushUnit.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjPushUnit::CObjPushUnit(float x, float y, float h, float w, int t)
{
	//�쐬���ɓn���ꂽ�l���A���W�̏����l�ɑ��
	m_x = x;
	m_y = y;
	m_h = h;
	m_w = w;
	m_type = t;
}

//�C�j�V�����C�Y
void CObjPushUnit::Init()
{
	m_mou_x = 0.0f;	//�}�E�XX���W
	m_mou_y = 0.0f; //�}�E�XY���W
	m_mou_r = false;//�E�N���b�N
	m_mou_l = false;//���N���b�N

	m_a = 1.0f;
}

//�A�N�V����
void CObjPushUnit::Action()
{
	//�}�E�X�̈ʒu���擾
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//�}�E�X�̃{�^���̏��
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	if ((m_x <= m_mou_x && m_mou_x <= (m_x + m_w))		//X���͈�
		&& (m_y <= m_mou_y && m_mou_y <= (m_y + m_h))	//Y���͈�
		&& m_mou_l == true) {							//�N���b�N
		if (m_type == 0) {		//�^�C�v���Ƃ̏���
			m_a = 0;
		}
		else if (m_type == 1)
		{
			m_a = 0.3;
		}
		else if (m_type == 2)
		{
			m_a = 0.6;
		}
	}
}

//�h���[
void CObjPushUnit::Draw()
{
	//�`��J���[���  R=RED  G=Green  B=Blue A=alpha(���ߏ��)
	float c[4] = { 1.0f,1.0f, 1.0f, m_a };

	RECT_F src;//�؂���ʒu
	RECT_F dst;//�\���ʒu
	
	src.m_top   =  0.0f;
	src.m_left  =  0.0f;
	src.m_right =100.0f;
	src.m_bottom=100.0f;
	
	dst.m_top   = m_y;
	dst.m_left  = m_x;
	dst.m_right = m_x + m_h;
	dst.m_bottom= m_y + m_w;

	//2�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
	Draw::Draw(2, &src, &dst, c, 0.0f);
}