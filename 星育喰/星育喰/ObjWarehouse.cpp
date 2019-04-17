//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjWarehouse.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�}�N��
#define INI_ALPHA (0.0f) //���ߓx(�A���t�@�l)�̏����l
#define INI_COLOR (1.0f) //�S�J���[���x�̏����l

//�C�j�V�����C�Y
void CObjWarehouse::Init()
{
	m_Ware_color = INI_COLOR;			//�q�ɃI�u�W�F�N�g�J���[
	m_Back_Button_color = INI_COLOR;	//�߂�{�^���J���[
	m_object_ma = INI_COLOR;			//���ފm�F�{�^���J���[
	m_object_re = INI_COLOR;			//�Z���m�F�{�^���J���[
	m_object_sp = INI_COLOR;			//�X�y�V�����Z�m�F�{�^���J���[
	m_object_eq = INI_COLOR;			//�����m�F�{�^���J���[

	for (int i = 0; i < 10; i++)
	{
		m_Ware_botton_color[i] = INI_COLOR;//�S�Ă̗v�f�̒l��INI_COLOR�ŏ��������Ă���
	}
	m_key_lf = false;

}

//�A�N�V����
void CObjWarehouse::Action()
{
	//�}�E�X�̈ʒu���擾
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//�}�E�X�̃{�^���̏��
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();


	//���q�ɃE�B���h�E�\���̏���
	 if (window_start_manage == Warehouse)
	{
		//�߂�{�^���I��
		if (30 < m_mou_x && m_mou_x < 80 && 30 < m_mou_y && m_mou_y < 80)
		{
			m_Back_Button_color = 0.7f;

			//���N���b�N���ꂽ��t���O�𗧂āA�q�ɃE�C���h�E�����
			if (m_mou_l == true)
			{
				//�N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
				if (m_key_lf == true)
				{
					m_key_lf = false;

					//"�ǂ̃E�C���h�E���J���Ă��Ȃ����"�t���O�𗧂Ă�
					window_start_manage = Default;
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
		else
		{
			m_introduce_f = false;//�{�ݏЉ�E�B���h�E���\���ɂ���
			m_Back_Button_color = 1.0f;
		}
	 if(window_start_manage==Materials)
	 {
		 //���ރ{�^���I��
		 if (350 < m_mou_x && m_mou_x < 525 && 200 < m_mou_y && m_mou_y < 375)
		 {
			 m_object_ma = 0.7f;

			 //���N���b�N���ꂽ��t���O�𗧂āA���ރE�C���h�E���J��
			 if (m_mou_l == true)
			 {
				 //�N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
				 if (m_key_lf == true)
				 {
					 m_key_lf = false;

					 //"���ރE�B���h�E���J���Ă�����"�t���O�𗧂Ă�
					 window_start_manage = Materials;
				 }
			 }
			 else
			 {
				 m_key_lf = true;
			 }
		 }
		 else
		 {
			 m_object_ma = 1.0f;

		 }

	 }

		//�Z���{�^���I��
		if (700 < m_mou_x && m_mou_x < 875 && 200 < m_mou_y && m_mou_y < 375)
		{
			m_object_re = 0.7f;

			//���N���b�N���ꂽ��t���O�𗧂āA�Z���E�C���h�E���J��
			if (m_mou_l == true)
			{
				//�N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
				if (m_key_lf == true)
				{
					m_key_lf = false;

					//"�Z���E�B���h�E���J���Ă�����"�t���O�𗧂Ă�
					window_start_manage = Residents;
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
		else
		{
			m_object_re = 1.0f;

		}

		//�X�y�V�����Z�{�^���I��
		if (350 < m_mou_x && m_mou_x < 525 && 450 < m_mou_y && m_mou_y < 625)
		{
			m_object_sp = 0.7f;

			//���N���b�N���ꂽ��t���O�𗧂āA�X�y�V�����Z�E�C���h�E���J��
			if (m_mou_l == true)
			{
				//�N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
				if (m_key_lf == true)
				{
					m_key_lf = false;

					//"�X�y�V�����Z�E�B���h�E���J���Ă�����"�t���O�𗧂Ă�
					window_start_manage = Specialskill;
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
		else
		{
			m_object_sp = 1.0f;

		}

		//�����{�^���I��
		if (700 < m_mou_x && m_mou_x < 875 && 450 < m_mou_y && m_mou_y < 625)
		{
			m_object_eq = 0.7f;

			//���N���b�N���ꂽ��t���O�𗧂āA�����E�C���h�E���J��
			if (m_mou_l == true)
			{
				//�N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
				if (m_key_lf == true)
				{
					m_key_lf = false;

					//"�����E�B���h�E���J���Ă�����"�t���O�𗧂Ă�
					window_start_manage = Soubicheck;
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
		else
		{
			m_object_eq = 1.0f;

		}
	}

	//�q�ɑI��
	if (95 < m_mou_x && m_mou_x < 320 && 170 < m_mou_y && m_mou_y < 280)
	{
		m_Ware_color = 0.7f;

		//���N���b�N���ꂽ��t���O�𗧂āA�q�ɃE�C���h�E���J��
		if (m_mou_l == true)
		{
			//�N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
			if (m_key_lf == true)
			{
				m_key_lf = false;

				//�q�ɂ��N���b�N����ƁA�q�ɂ��J�����
				window_start_manage = Warehouse;
			}
		}
		else
		{
			m_key_lf = true;
		}
	}
	else
	{
		m_Ware_color = 1.0f;
	}

	//���ރ{�^���I��
	if (350 < m_mou_x && m_mou_x < 525 && 200 < m_mou_y && m_mou_y < 375)
	{
		m_object_ma = 0.7f;

		//���N���b�N���ꂽ��t���O�𗧂āA���ރE�C���h�E���J��
		if (m_mou_l == true)
		{
			//�N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
			if (m_key_lf == true)
			{
				m_key_lf = false;

				//"���ރE�B���h�E���J���Ă�����"�t���O�𗧂Ă�
				window_start_manage = Materials;
			}
		}
		else
		{
			m_key_lf = true;
		}
	}
	else
	{
		m_object_ma = 1.0f;

	}



}

//�h���[
void CObjWarehouse::Draw()
{
	//���V�[���؂�ւ����o��ɔ�\���ɂ��鏈��
	if (scene_change_start == true)
	{
		return;
	}

	//�q�ɉ摜
	float c[4] = { m_Ware_color,m_Ware_color, m_Ware_color, 1.0f };

	//�I�u�W�F�N�g�N���b�N����O�̔w�i�I�u�W�F�N�g
	float h[4] = { 1.0f,1.0f,1.0f,1.0f };

	//����ȊO�̉摜
	//�w�i�I�u�W�F�N�g
	float sb[4] = { 1.0f,1.0f,1.0f,1.0f };

	//�߂�{�^���摜
	float md[4] = { m_Back_Button_color,m_Back_Button_color,m_Back_Button_color,1.0f };

	//���ރ{�^���摜
	float ma[4] = { m_object_ma,m_object_ma,m_object_ma ,1.0f };

	//�Z���{�^���摜
	float re[4] = { m_object_re,m_object_re,m_object_re,1.0f };

	//�X�y�V�����Z�{�^���摜
	float sp[4] = { m_object_sp,m_object_sp,m_object_sp,1.0f };

	//�����{�^���摜
	float eq[4] = { m_object_eq,m_object_eq,m_object_eq,1.0f };

	RECT_F src;//�`���؂���ʒu
	RECT_F dst;//�`���\���ʒu

	//�{�ݏЉ�E�B���h�E(���ɁA�������A�q��)���J���Ă��Ȃ����ɕ\������O���t�B�b�N
	if (window_start_manage == Default || window_start_manage == BackButton)
	{
		//���q�ɕ\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 225.0f;
		src.m_bottom = 225.0f;

		dst.m_top = 100.0f;
		dst.m_left = 100.0f;
		dst.m_right = 325.0f;
		dst.m_bottom = 325.0f;

		//2�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
		Draw::Draw(2, &src, &dst, c, 0.0f);
	}

	//�q�ɂ��N���b�N������
	else if (window_start_manage == Warehouse)
	{
		//���D�F�E�B���h�E�\��
		src.m_top    =    0.0f;
		src.m_left   =    0.0f;
		src.m_right  = 1160.0f;
		src.m_bottom =  660.0f;

		dst.m_top    =   20.0f;
		dst.m_left   =   20.0f;
		dst.m_right  = 1180.0f;
		dst.m_bottom =  680.0f;
		Draw::Draw(3, &src, &dst, sb, 0.0f);

		//���߂�A�C�R���\��
		src.m_top    =   0.0f;
		src.m_left   =   0.0f;
		src.m_right  = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top    =  30.0f;
		dst.m_left   =  30.0f;
		dst.m_right  =  80.0f;
		dst.m_bottom =  80.0f;
		Draw::Draw(4, &src, &dst, md, 0.0f);

		//�����ޑI���{�^���\��
		src.m_top    = 0.0f;
		src.m_left   = 0.0f;
		src.m_right  = 225.0f;
		src.m_bottom = 225.0f;

		dst.m_top    = 200.0f;
		dst.m_left   = 350.0f;
		dst.m_right  = 525.0f;
		dst.m_bottom = 375.0f;
		Draw::Draw(5, &src, &dst, ma, 0.0f);

		//���Z���I���{�^���\��
		src.m_top    = 0.0f;
		src.m_left   = 0.0f;
		src.m_right  = 225.0f;
		src.m_bottom = 225.0f;

		dst.m_top    = 200.0f;
		dst.m_left   = 700.0f;
		dst.m_right  = 875.0f;
		dst.m_bottom = 375.0f;
		Draw::Draw(6, &src, &dst, re, 0.0f);

		//���X�y�V�����Z�I���{�^���\��
		src.m_top    = 0.0f;
		src.m_left   = 0.0f;
		src.m_right  = 225.0f;
		src.m_bottom = 225.0f;

		dst.m_top    = 450.0f;
		dst.m_left   = 350.0f;
		dst.m_right  = 525.0f;
		dst.m_bottom = 625.0f;
		Draw::Draw(7, &src, &dst, sp, 0.0f);

		//�������I���{�^���\��
		src.m_top    = 0.0f;
		src.m_left   = 0.0f;
		src.m_right  = 225.0f;
		src.m_bottom = 225.0f;

		dst.m_top    = 450.0f;
		dst.m_left   = 700.0f;
		dst.m_right  = 875.0f;
		dst.m_bottom = 625.0f;
		Draw::Draw(8, &src, &dst, eq, 0.0f);
	}

	//�߂�{�^����I�����ĕ`�悷��摜
	else if (window_start_manage == Default || window_start_manage == BackButton)
	{
		//���w�i�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 100.0f;
		src.m_bottom = 100.0f;

		//�\��
		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = 1200.0f;
		dst.m_bottom = 800.0f;

		//0�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
		Draw::Draw(0, &src, &dst, h, 0.0f);

		//���q�ɕ\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 225.0f;
		src.m_bottom = 225.0f;

		dst.m_top = 100.0f;
		dst.m_left = 100.0f;
		dst.m_right = 325.0f;
		dst.m_bottom = 325.0f;

		//2�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
		Draw::Draw(2, &src, &dst, c, 0.0f);
	}

	//���ރ{�^���������ĕ`�悷��摜
	else if (window_start_manage == Materials)
	{
		//���D�F�E�B���h�E�\��(�_�~�[�q�ɃE�B���h�E�p)
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1160.0f;
		src.m_bottom = 660.0f;

		dst.m_top = 20.0f;
		dst.m_left = 20.0f;
		dst.m_right = 1180.0f;
		dst.m_bottom = 680.0f;
		Draw::Draw(3, &src, &dst, sb, 0.0f);

		//���D�F�E�B���h�E�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1160.0f;
		src.m_bottom = 660.0f;

		dst.m_top = 40.0f;
		dst.m_left = 40.0f;
		dst.m_right = 1160.0f;
		dst.m_bottom = 660.0f;
		Draw::Draw(3, &src, &dst, sb, 0.0f);

		//���߂�{�^���\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 50.0f;
		dst.m_left = 50.0f;
		dst.m_right = 100.0f;
		dst.m_bottom = 100.0f;
		Draw::Draw(4, &src, &dst, md, 0.0f);

	}
	//�Z���{�^���������ĕ`�悷��摜
	else if (window_start_manage == Residents)
	{
		//���D�F�E�B���h�E�\��(�_�~�[�q�ɃE�B���h�E�p)
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1160.0f;
		src.m_bottom = 660.0f;

		dst.m_top = 20.0f;
		dst.m_left = 20.0f;
		dst.m_right = 1180.0f;
		dst.m_bottom = 680.0f;
		Draw::Draw(3, &src, &dst, sb, 0.0f);

		//���D�F�E�B���h�E�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1160.0f;
		src.m_bottom = 660.0f;

		dst.m_top = 40.0f;
		dst.m_left = 40.0f;
		dst.m_right = 1160.0f;
		dst.m_bottom = 660.0f;
		Draw::Draw(3, &src, &dst, sb, 0.0f);

		//���߂�{�^���\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 50.0f;
		dst.m_left = 50.0f;
		dst.m_right = 100.0f;
		dst.m_bottom = 100.0f;
		Draw::Draw(4, &src, &dst, md, 0.0f);

	}

	//�X�y�V�����Z�{�^���������ĕ`�悷��摜
	else if (window_start_manage == Specialskill)
	{
		//���D�F�E�B���h�E�\��(�_�~�[�q�ɃE�B���h�E�p)
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1160.0f;
		src.m_bottom = 660.0f;

		dst.m_top = 20.0f;
		dst.m_left = 20.0f;
		dst.m_right = 1180.0f;
		dst.m_bottom = 680.0f;
		Draw::Draw(3, &src, &dst, sb, 0.0f);

		//���D�F�E�B���h�E�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1160.0f;
		src.m_bottom = 660.0f;

		dst.m_top = 40.0f;
		dst.m_left = 40.0f;
		dst.m_right = 1160.0f;
		dst.m_bottom = 660.0f;
		Draw::Draw(3, &src, &dst, sb, 0.0f);

		//���߂�{�^���\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 50.0f;
		dst.m_left = 50.0f;
		dst.m_right = 100.0f;
		dst.m_bottom = 100.0f;
		Draw::Draw(4, &src, &dst, md, 0.0f);

	}

	//�����{�^���������ĕ`�悷��摜
	else if (window_start_manage == Soubicheck)
	{
		//���D�F�E�B���h�E�\��(�_�~�[�q�ɃE�B���h�E�p)
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1160.0f;
		src.m_bottom = 660.0f;

		dst.m_top = 20.0f;
		dst.m_left = 20.0f;
		dst.m_right = 1180.0f;
		dst.m_bottom = 680.0f;
		Draw::Draw(3, &src, &dst, sb, 0.0f);

		//���D�F�E�B���h�E�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1160.0f;
		src.m_bottom = 660.0f;

		dst.m_top = 40.0f;
		dst.m_left = 40.0f;
		dst.m_right = 1160.0f;
		dst.m_bottom = 660.0f;
		Draw::Draw(3, &src, &dst, sb, 0.0f);

		//���߂�{�^���\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 50.0f;
		dst.m_left = 50.0f;
		dst.m_right = 100.0f;
		dst.m_bottom = 100.0f;
		Draw::Draw(4, &src, &dst, md, 0.0f);

	}

}

