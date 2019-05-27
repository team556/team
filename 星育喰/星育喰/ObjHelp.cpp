//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"
#include "ObjHelp.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

////�R���X�g���N�^
//CObjTest::CObjTest(float x, float y)
//{
//	//�쐬���ɓn���ꂽ�l���A���W�̏����l�ɑ��
//	m_x = x;
//	m_y = y;
//}

#define INI_COLOR (0.9f) //�S�J���[���x�̏����l(�A�C�R�����I�𒆂̃J���[)

//�C�j�V�����C�Y
void CObjHelp::Init()
{
	m_help_f = false;
	m_page_nam = 0;
	m_Scene_nam = 0;

	m_x = 1120.0f;
	m_y =   30.0f;
	m_a = INI_COLOR;
	m_a2 = INI_COLOR;

	m_key_f = false;

	CObjHome* Hom = (CObjHome*)Objs::GetObj(OBJ_HOME);				//�e�V�[�������擾	�z�[��	1
	CObjTraining* Tra = (CObjTraining*)Objs::GetObj(OBJ_TRAINING);						  //�琬	2
	CObjPreparation* Pre = (CObjPreparation*)Objs::GetObj(OBJ_PREPARATION);				  //����	3
	CObjFight* Fig = (CObjFight*)Objs::GetObj(OBJ_FIGHT);								  //�퓬	4
	

	if (Hom != nullptr)												//���݂̃V�[���Ő��������߂�
		m_Scene_nam = 1;
	else if (Tra != nullptr)
		m_Scene_nam = 2;
	else if (Tra != nullptr)
		m_Scene_nam = 3;
	else if (Tra != nullptr)
		m_Scene_nam = 4;
}

//�A�N�V����
void CObjHelp::Action()
{


	//�}�E�X�̈ʒu���擾
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//�}�E�X�̃{�^���̏��
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	if (m_help_f == false)						//�w���v�\�����ĂȂ��ꍇ
	{											//��ɖ��I���J���[
		m_a = INI_COLOR;						//�͈͏���
		if (1110 < m_mou_x && m_mou_x < 1160 && 30 < m_mou_y && m_mou_y < 80)
		{										//�}�E�X�̃N���b�N��
			if (m_mou_l == true)
			{
				m_help_f = true;//�w���v�\������
				m_key_f = true;	//�A�Ő���
			}
			else
			{
				m_a = 1.0f;
			}
		}
	}
	else										//�w���v�\�����Ă�ꍇ
	{
		if (m_mou_l == true && m_key_f == false)//�N���b�N
		{
			m_page_nam++;		//�y�[�W����i�߂�
			m_key_f = true;		//�L�[�t���OON
		}
		if (30 < m_mou_x && m_mou_x < 80 && 30 < m_mou_y && m_mou_y < 80)
		{
			m_a2 = 1.0f;
			if (m_mou_l == true)
			{
				m_help_f = false;
			}
		}
		else
		{
			m_a2 = INI_COLOR;
		}
	}

	if (m_mou_l == false)						//�N���b�NOFF
	{
		m_key_f = false;	//�L�[�t���OOFF
	}
}

//�h���[
void CObjHelp::Draw()
{
	/*float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	Font::StrDraw(L"", 230, 250, 32, c);*/
	
	//�`��J���[���  R=RED  G=Green  B=Blue A=alpha(���ߏ��)
	float d2[4] = { 1.0f,1.0f, 1.0f, m_a };

	RECT_F src;//�؂���ʒu
	RECT_F dst;//�\���ʒu
	
	src.m_top   =  0.0f;
	src.m_left  =  0.0f;
	src.m_right =100.0f;
	src.m_bottom=100.0f;
	
	dst.m_top   = m_y;
	dst.m_left  = m_x;
	dst.m_right = m_x + 50.0f;
	dst.m_bottom= m_y + 50.0f;

	//0�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
	Draw::Draw(1, &src, &dst, d2, 0.0f);

	if (m_help_f == true)
	{
		float d[4] = { 1.0f,1.0f, 1.0f, 1.0f };

		if(m_Scene_nam = 1)				//�z�[����ʂł̃w���v
		{
			src.m_top   =  0.0f;
			src.m_left  =  0.0f;
			src.m_right =100.0f;
			src.m_bottom=100.0f;
			
			dst.m_top   =  20.0f;
			dst.m_left  =  20.0f;
			dst.m_right =1180.0f;
			dst.m_bottom= 680.0f;

			if(m_page_nam == 0)
			{
				//0�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
				Draw::Draw(1, &src, &dst, d, 0.0f);
			}
			else if(m_page_nam == 1)
			{
				//0�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
				Draw::Draw(1, &src, &dst, d, 0.0f);
			}
			else if(m_page_nam == 2)
			{
				//0�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
				Draw::Draw(1, &src, &dst, d, 0.0f);
			}
			else if(m_page_nam == 3)
			{
				//0�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
				Draw::Draw(1, &src, &dst, d, 0.0f);
			}
			else if(m_page_nam >= 4)
			{
				m_help_f = false;//�����l�ɖ߂�
				m_page_nam = 0;
			}
			float d3[4] = { 1.0f,1.0f,1.0f, m_a2 };

			src.m_top   =  0.0f;
			src.m_left  =  0.0f;
			src.m_right =100.0f;
			src.m_bottom=100.0f;
	
			dst.m_top   = 30.0f;
			dst.m_left  = 30.0f;
			dst.m_right = 80.0f;
			dst.m_bottom= 80.0f;

			//0�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
			Draw::Draw(1, &src, &dst, d3, 0.0f);
		}
		else
		{
			m_help_f = false;//�����l�ɖ߂�
			m_page_nam = 0;
		}
	}

}
