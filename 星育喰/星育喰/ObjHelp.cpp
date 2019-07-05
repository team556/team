//�g�p����w�b�_�[�t�@�C��
//#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�}�N��
#define HELP_X_POS (1120.0f) //�w���v�{�^����X�ʒu
#define HELP_Y_POS (30.0f)	 //�w���v�{�^����Y�ʒu
#define INI_COLOR (0.9f) //�S�J���[���x�̏����l(�A�C�R�����I�𒆂̃J���[)

//�C�j�V�����C�Y
void CObjHelp::Init()
{
	m_mou_x = 0.0f;
	m_mou_y = 0.0f;
	m_mou_r = false;
	m_mou_l = false;
	m_key_f = false;

	m_Help_Button_color = INI_COLOR;
	m_Back_Button_color = INI_COLOR;

	m_help_f = false;
	m_page_num = 0;









	//���݂̃V�[���ŉ摜�̓o�^�ԍ��A�w���v�摜(�y�[�W)�̍ő吔�����߂�
	if (m_Scene_num == 1)//�z�[��	1											
	{
		m_page_max = 1;
		m_Img_num = 3;
	}
	else if (m_Scene_num == 2)//�琬	2
	{
		m_page_max = 1;
		m_Img_num = 46;

		if (60 < m_mou_x && m_mou_x < 325 && 505 < m_mou_y && m_mou_y < 637)
		{
			if (1110 < m_mou_x && m_mou_x < 1160 &&
				30 < m_mou_y && m_mou_y < 80)
			{
				m_Img_num = 11;
			}
		}

	}
	else  //(m_Scene_num == 3)//����	3
	{
		m_page_max = 1;
		m_Img_num = 20;
	}

	//�R���X�g���N�^�Œl�������Ă���ׁA�ȉ��̏����͕s�v
	//CObjHome* Hom = (CObjHome*)Objs::GetObj(OBJ_HOME);				//�e�V�[�������擾  //�z�[��	1
	//CObjTraining* Tra = (CObjTraining*)Objs::GetObj(OBJ_TRAINING);						  //�琬	2
	//CObjPreparation* Pre = (CObjPreparation*)Objs::GetObj(OBJ_PREPARATION);				  //����	3
	//CObjFight* Fig = (CObjFight*)Objs::GetObj(OBJ_FIGHT);									  //�퓬	4
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

	//���L�[�t���O
	//�����N���b�NPush��ԁ����N���b�N��Push��ԂɂȂ�܂ŁA
	//�ēx���N���b�N���鎖�͏o���Ȃ������B
	if (m_mou_l == false)	//���N���b�NOFF
	{
		m_key_f = false;	//�L�[�t���OOFF
	}

	//���w���v��\�����̏���
	if (m_help_f == false)						
	{											//��ɖ��I���J���[
		m_Help_Button_color = INI_COLOR;						//�͈͏���
		if (1110 < m_mou_x && m_mou_x < 1160 && 30 < m_mou_y && m_mou_y < 80)
		{										
			if (m_mou_l == true && m_key_f == false)//�}�E�X���N���b�N
			{
				m_help_f = true;//�w���v�\������
				m_key_f = true;	//�A�Ő���(�L�[�t���OON)

				//�I����
				Audio::Start(1);
			}
			else
			{
				m_Help_Button_color = 1.0f;
			}
		}
	}
	//���w���v�\�����̏���
	else										
	{
		if (m_mou_l == true && m_key_f == false)//�}�E�X���N���b�N
		{
			m_page_num++;		//�y�[�W����i�߂�
			m_key_f = true;		//�A�Ő���(�L�[�t���OON)
		}
		if (30 < m_mou_x && m_mou_x < 80 && 30 < m_mou_y && m_mou_y < 80)
		{
			m_Back_Button_color = 1.0f;
			if (m_mou_l == true)
			{
				m_help_f = false;

				//�߂�{�^����
				Audio::Start(2);
			}
		}
		else
		{
			m_Back_Button_color = INI_COLOR;
		}
	}
}

//�h���[
void CObjHelp::Draw()
{
	//�`��J���[���  R=RED  G=Green  B=Blue A=alpha(���ߏ��)
	float d[4] = { 1.0f,1.0f,1.0f,1.0f };

	float d2[4] = { 1.0f,1.0f,1.0f,m_Help_Button_color };

	RECT_F src;//�؂���ʒu
	RECT_F dst;//�\���ʒu
	

	//���w���v�{�^���\��
	src.m_top   =  0.0f;
	src.m_left  =  0.0f;
	src.m_right =128.0f;
	src.m_bottom=128.0f;
	
	dst.m_top   = HELP_Y_POS;
	dst.m_left  = HELP_X_POS;
	dst.m_right = HELP_X_POS + 50.0f;
	dst.m_bottom= HELP_Y_POS + 50.0f;

	//m_Img_num�ɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
	Draw::Draw(m_Img_num, &src, &dst, d2, 0.0f);


	if (m_help_f == true)
	{
		//��U�R�����g�A�E�g��
		//if(m_Scene_num == 1)				//�z�[����ʂł̃w���v
		//{
		if(1)
		{
			src.m_top   = 150.0f;
			src.m_left  =   0.0f;
			src.m_right =1280.0f;
			src.m_bottom= 870.0f;
			
			dst.m_top   =  20.0f;
			dst.m_left  =  20.0f;
			dst.m_right =1180.0f;
			dst.m_bottom= 680.0f;

			//�y�[�W���Œ[�܂ł����ƁA���[�v������(2�y�[�W���ő�̏ꍇ�A2��0,0��2�ɂ�����悤��)
			if (m_page_num < 0 || m_page_max <= m_page_num)
			{
				//���������͂܂�����ĂȂ��B

				m_help_f = false;//�����l�ɖ߂�
				m_page_num = 0;
			}

			if(m_page_num == 0)
			{
				//0�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
				Draw::Draw(m_Img_num + 2, &src, &dst, d, 0.0f);
			}
			
			float d3[4] = { 1.0f,1.0f,1.0f, m_Back_Button_color };

			src.m_top   =  0.0f;
			src.m_left  =  0.0f;
			src.m_right = 64.0f;
			src.m_bottom= 64.0f;
	
			dst.m_top   = 30.0f;
			dst.m_left  = 30.0f;
			dst.m_right = 80.0f;
			dst.m_bottom= 80.0f;

			//0�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
			Draw::Draw(m_Img_num + 1, &src, &dst, d3, 0.0f);			//�߂�{�^���̕\��
		}
		else
		{
			m_help_f = false;//�����l�ɖ߂�
			m_page_num = 0;
		}
	}

}
