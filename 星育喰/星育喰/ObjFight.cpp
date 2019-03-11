//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"
#include "ObjFight.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjFight::Init()
{
	m_mou_x = 0.0f;	//�}�E�XX���W
	m_mou_y = 0.0f; //�}�E�XY���W
	m_mou_r = false;//�E�N���b�N
	m_mou_l = false;//���N���b�N
	
	m_line = 3;		//�����l�A
	m_line_nam = 3; //�����l�A���I��
}

//�A�N�V����
void CObjFight::Action()
{
	//�}�E�X�̈ʒu���擾
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//�}�E�X�̃{�^���̏��
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();
	

	m_line = 6;

	if (400 <= m_mou_x && m_mou_x <= 800) 
	{
		if (200 <= m_mou_y && m_mou_y <= 260) {					
			if (m_mou_l == true) { m_line_nam = 0; }//�ド�C��------
			else { m_line = 0; }
		}
		else if (310 <= m_mou_y && m_mou_y <= 370) {			
			if (m_mou_l == true) { m_line_nam = 1; }//�����C��------
			else { m_line = 1; }
		}
		else if (420 <= m_mou_y && m_mou_y <= 480) {			
			if (m_mou_l == true) { m_line_nam = 2; }//�����C��------
			else { m_line = 2; }
		}
		else {};//���C���O�������Ȃ�
	}
	else {};//�͈͊O�̏ꍇ�A�����l�ɖ߂�

}

//�h���[
void CObjFight::Draw()
{
	//�`��J���[���  R=RED  G=Green  B=Blue A=alpha(���ߏ��)
	float d0[4] = { 1.0f,1.0f,1.0f,0.3f };
	float d1[4] = { 1.0f,1.0f,1.0f,0.3f };
	float d2[4] = { 1.0f,1.0f,1.0f,0.3f };

	if (m_line == 0)		//�I�����Ɋe���C����s������
		d0[3] = 0.6f;
	else if (m_line == 1)
		d1[3] = 0.6f;
	else if (m_line == 2)
		d2[3] = 0.6f;

	if (m_line_nam == 0)	//�J�[�\�����ɔ��s������
		d0[3] = 1.0f;
	else if (m_line_nam == 1)
		d1[3] = 1.0f;
	else if (m_line_nam == 2)
		d2[3] = 1.0f;

	
	
	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu

	//���w�i�\��
	src.m_top   =  0.0f;
	src.m_left  =  0.0f;
	src.m_right =100.0f;
	src.m_bottom=100.0f;

	dst.m_top   =200.0f;
	dst.m_left  =400.0f;
	dst.m_right =800.0f;
	dst.m_bottom=260.0f;
	Draw::Draw(2, &src, &dst, d0, 0.0f);

	dst.m_top   =310.0f;
	dst.m_left  =400.0f;
	dst.m_right =800.0f;
	dst.m_bottom=370.0f;
	Draw::Draw(2, &src, &dst, d1, 0.0f);

	dst.m_top   =420.0f;
	dst.m_left  =400.0f;
	dst.m_right =800.0f;
	dst.m_bottom=480.0f;
	Draw::Draw(2, &src, &dst, d2, 0.0f);
}
