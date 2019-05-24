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

//�C�j�V�����C�Y
void CObjHelp::Init()
{
	m_help_f = false;
	m_page_nam = 0;
	m_Scene_nam = 0;

	m_x = 1140.0f;
	m_y =   10.0f;

	m_mou_f = false;

	CObjHome* Hom = (CObjHome*)Objs::GetObj(OBJ_HOME);				//�e�V�[�������擾
	CObjTraining* Tra = (CObjTraining*)Objs::GetObj(OBJ_TRAINING);
	CObjPreparation* Pre = (CObjPreparation*)Objs::GetObj(OBJ_PREPARATION);
	CObjFight* Fig = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
	

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

	if (m_help_f == false)						//�w���v�\�����ĂȂ��ꍇ����
	{											//�{�^���N���b�N�����ꍇ
		if (1140 < m_mou_x && m_mou_x < 1190 && 10 < m_mou_y && m_mou_y < 60 && m_mou_l == true)
		{	
			m_help_f = true;//�w���v�\������
		}
	}
	else if(m_mou_l == true && m_mou_f == false)//�w���v�\�������N���b�N�����ꍇ
	{								
		m_page_nam++;		//�y�[�W����i�߂�
		m_mou_f = true;
	}

	if (m_mou_l == false)						//�N���b�N������
	{
		m_mou_f = false;	//�}�E�X�t���O����
	}
}

//�h���[
void CObjHelp::Draw()
{
	/*float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	Font::StrDraw(L"", 230, 250, 32, c);*/
	
	//�`��J���[���  R=RED  G=Green  B=Blue A=alpha(���ߏ��)
	float d[4] = { 1.0f,1.0f, 1.0f, 1.0f };

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
	Draw::Draw(1, &src, &dst, d, 0.0f);

	if (m_help_f == true)
	{
		if(m_Scene_nam = 1)
		{
			if(m_page_nam == 0)
			{
				src.m_top   =  0.0f;
				src.m_left  =  0.0f;
				src.m_right =100.0f;
				src.m_bottom=100.0f;
	
				dst.m_top   =   0.0f;
				dst.m_left  =   0.0f;
				dst.m_right =1200.0f;//���t�����
				dst.m_bottom= 700.0f;

				//0�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
				Draw::Draw(1, &src, &dst, d, 0.0f);
			}
			else if(m_page_nam == 1)
			{
				src.m_top   =  0.0f;
				src.m_left  =  0.0f;
				src.m_right =100.0f;
				src.m_bottom=100.0f;
	
				dst.m_top   =   0.0f;
				dst.m_left  =   0.0f;
				dst.m_right =1200.0f;//���t�����
				dst.m_bottom= 700.0f;

				//0�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
				Draw::Draw(1, &src, &dst, d, 0.0f);
			}
			else if(m_page_nam == 2)
			{
				src.m_top   =  0.0f;
				src.m_left  =  0.0f;
				src.m_right =100.0f;
				src.m_bottom=100.0f;
	
				dst.m_top   =   0.0f;
				dst.m_left  =   0.0f;
				dst.m_right =1200.0f;//���t�����
				dst.m_bottom= 700.0f;

				//0�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
				Draw::Draw(1, &src, &dst, d, 0.0f);
			}
			else if(m_page_nam == 3)
			{
				src.m_top   =  0.0f;
				src.m_left  =  0.0f;
				src.m_right =100.0f;
				src.m_bottom=100.0f;
	
				dst.m_top   =   0.0f;
				dst.m_left  =   0.0f;
				dst.m_right =1200.0f;//���t�����
				dst.m_bottom= 700.0f;

				//0�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
				Draw::Draw(1, &src, &dst, d, 0.0f);
			}
			}
	}

}
