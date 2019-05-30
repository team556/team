//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjHelp.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�}�N��
#define INI_COLOR (0.9f) //�S�J���[���x�̏����l(�A�C�R�����I�𒆂̃J���[)

////�R���X�g���N�^
//CObjTest::CObjTest(float x, float y)
//{
//	//�쐬���ɓn���ꂽ�l���A���W�̏����l�ɑ��
//	m_x = x;
//	m_y = y;
//}

//�C�j�V�����C�Y
void CObjHelp::Init()
{
	m_help_f = false;
	m_page_nam = 0;
	//m_Scene_nam = 0;//�R���X�g���N�^�Œl�������Ă���ׁA���������Ȃ��ėǂ�

	m_x = 1120.0f;
	m_y = 30.0f;
	m_a = INI_COLOR;
	m_a2 = INI_COLOR;

	m_key_f = false;

	m_mou_x = 0.0f;
	m_mou_y = 0.0f;
	m_mou_r = false;
	m_mou_l = false;

	//�R���X�g���N�^�Œl�������Ă���ׁA�ȉ��̏����͕s�v
	//CObjHome* Hom = (CObjHome*)Objs::GetObj(OBJ_HOME);				//�e�V�[�������擾	�z�[��	1
	//CObjTraining* Tra = (CObjTraining*)Objs::GetObj(OBJ_TRAINING);						  //�琬	2
	//CObjPreparation* Pre = (CObjPreparation*)Objs::GetObj(OBJ_PREPARATION);				  //����	3
	//CObjFight* Fig = (CObjFight*)Objs::GetObj(OBJ_FIGHT);								  //�퓬	4

	//���݂̃V�[���ŉ摜�̓o�^�ԍ������߂�
	if (m_Scene_nam == 1)//�z�[��	1											
	{
		m_Img_nam = 3;
	}
	else if (m_Scene_nam == 2)//�琬	2
	{
		m_Img_nam = 46;

		////�z�[����ʂɖ߂�{�^���������ꂽ��A
		////���{�݂̃E�C���h�E���J���Ă��鎞�͑�����󂯕t���Ȃ��悤�ɂ���B
		//if (window_start_manage != Default)
		//{
		//	return;
		//}

		if (60 < m_mou_x && m_mou_x < 325 && 505 < m_mou_y && m_mou_y < 637)
		{
			if (1110 < m_mou_x && m_mou_x < 1160 &&
				30 < m_mou_y && m_mou_y < 80)
			{
				m_Img_nam = 11;
			}

			////�z�[����ʂɖ߂�{�^���������ꂽ��A
			////���{�݂̃E�C���h�E���J���Ă��鎞�͑�����󂯕t���Ȃ��悤�ɂ���B
			//else if (window_start_manage != Default)
			//{
			//	return;
			//}
		}

	}
	else if (m_Scene_nam == 3)//����	3
	{
		m_Img_nam = 20;
	}
	//else if (m_Scene_nam == 4)//�퓬	4
	//{
	//	m_Img_nam = 33;

	//}
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

				//�I����
				Audio::Start(1);
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

				//�߂�{�^����
				Audio::Start(2);
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
	src.m_right =128.0f;
	src.m_bottom=128.0f;
	
	dst.m_top   = m_y;
	dst.m_left  = m_x;
	dst.m_right = m_x + 50.0f;
	dst.m_bottom= m_y + 50.0f;

	//m_Img_nam�ɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
	Draw::Draw(m_Img_nam, &src, &dst, d2, 0.0f);		//�w���v�{�^���̕\��

	if (m_help_f == true)
	{
		float d[4] = { 1.0f,1.0f, 1.0f, 1.0f };

		//��U�R�����g�A�E�g��
		//if(m_Scene_nam == 1)				//�z�[����ʂł̃w���v
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

			if(m_page_nam == 0)
			{
				//0�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
				Draw::Draw(m_Img_nam + 2, &src, &dst, d, 0.0f);
			}
			else if(m_page_nam >= 1)
			{
				m_help_f = false;//�����l�ɖ߂�
				m_page_nam = 0;
			}
			float d3[4] = { 1.0f,1.0f,1.0f, m_a2 };

			src.m_top   =  0.0f;
			src.m_left  =  0.0f;
			src.m_right = 64.0f;
			src.m_bottom= 64.0f;
	
			dst.m_top   = 30.0f;
			dst.m_left  = 30.0f;
			dst.m_right = 80.0f;
			dst.m_bottom= 80.0f;

			//0�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
			Draw::Draw(m_Img_nam + 1, &src, &dst, d3, 0.0f);			//�߂�{�^���̕\��
		}
		else
		{
			m_help_f = false;//�����l�ɖ߂�
			m_page_nam = 0;
		}
	}

}
