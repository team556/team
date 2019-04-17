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
#define INI_COLOR (1.0f) //�S�J���[���x�̏����l

//�C�j�V�����C�Y
void CObjWarehouse::Init()
{
	m_Ware_color = INI_COLOR;
	m_Back_Button_color = INI_COLOR;

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
				m_key_wh = true;
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

	//���ރ{�^���I��
	if (350 < m_mou_x && m_mou_x < 525 && 200 < m_mou_y && m_mou_y < 375)
	{
		m_object_ma = 0.7f;

		//���N���b�N���ꂽ��t���O�𗧂āA�q�ɃE�C���h�E�����
		if (m_mou_l == true)
		{
			//�N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
			if (m_key_ma == true)
			{
				m_key_ma = false;

			}
		}
		else
		{
			m_key_ma = true;
		}
	}
	else
	{
		m_object_ma = 1.0f;

	}

	//�Z���{�^���I��
	if (700 < m_mou_x && m_mou_x < 875 && 200 < m_mou_y && m_mou_y < 375)
	{
		m_object_re = 0.7f;

		//���N���b�N���ꂽ��t���O�𗧂āA�q�ɃE�C���h�E�����
		if (m_mou_l == true)
		{
			//�N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
			if (m_key_re == true)
			{
				m_key_re = false;

			}
		}
		else
		{
			m_key_re = true;
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

		//���N���b�N���ꂽ��t���O�𗧂āA�q�ɃE�C���h�E�����
		if (m_mou_l == true)
		{
			//�N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
			if (m_key_sp == true)
			{
				m_key_sp = false;

			}
		}
		else
		{
			m_key_sp = true;
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

		//���N���b�N���ꂽ��t���O�𗧂āA�q�ɃE�C���h�E�����
		if (m_mou_l == true)
		{
			//�N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
			if (m_key_eq == true)
			{
				m_key_eq = false;

			}
		}
		else
		{
			m_key_eq = true;
		}
	}
	else
	{
		m_object_eq = 1.0f;

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

	//�q�ɕ\��
	//�؂���
	src.m_top    =   0.0f;
	src.m_left   =   0.0f;
	src.m_right  = 225.0f;
	src.m_bottom = 225.0f;

	dst.m_top    = 100.0f;
	dst.m_left   = 100.0f;
	dst.m_right  = 325.0f;
	dst.m_bottom = 325.0f;

	//2�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
	Draw::Draw(2, &src, &dst, c, 0.0f);

	//�߂�{�^����I�����ĕ`�悷��摜
	if (window_start_manage == Default || window_start_manage == BackButton)
	{
		//�w�i
		//�؂���
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

		//�q�ɕ\��
		//�؂���
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
	else if (m_key_wh == true)
	{
		//�{�^���w�i�쐬
		src.m_top    =    0.0f;
		src.m_left   =    0.0f;
		src.m_right  = 1200.0f;
		src.m_bottom =  800.0f;

		dst.m_top    =   20.0f;
		dst.m_left   =   20.0f;
		dst.m_right  = 1180.0f;
		dst.m_bottom =  680.0f;
		Draw::Draw(3, &src, &dst, sb, 0.0f);

		//�߂�A�C�R���쐬
		src.m_top    =   0.0f;
		src.m_left   =   0.0f;
		src.m_right  = 225.0f;
		src.m_bottom = 225.0f;

		dst.m_top    =  20.0f;
		dst.m_left   =  20.0f;
		dst.m_right  =  80.0f;
		dst.m_bottom =  80.0f;
		Draw::Draw(4, &src, &dst, md, 0.0f);
		dst.m_right  =  80.0f;
		dst.m_bottom =  80.0f;
		Draw::Draw(4, &src, &dst, md, 0.0f);

		//���ޑI���{�^���쐬
		src.m_top    = 0.0f;
		src.m_left   = 0.0f;
		src.m_right  = 225.0f;
		src.m_bottom = 225.0f;

		dst.m_top    = 200.0f;
		dst.m_left   = 350.0f;
		dst.m_right  = 525.0f;
		dst.m_bottom = 375.0f;
		Draw::Draw(5, &src, &dst, ma, 0.0f);

		//�Z���I���{�^���쐬
		src.m_top    = 0.0f;
		src.m_left   = 0.0f;
		src.m_right  = 225.0f;
		src.m_bottom = 225.0f;

		dst.m_top    = 200.0f;
		dst.m_left   = 700.0f;
		dst.m_right  = 875.0f;
		dst.m_bottom = 375.0f;
		Draw::Draw(6, &src, &dst, re, 0.0f);

		//�X�y�V�����Z�I���{�^���쐬
		src.m_top    = 0.0f;
		src.m_left   = 0.0f;
		src.m_right  = 225.0f;
		src.m_bottom = 225.0f;

		dst.m_top    = 450.0f;
		dst.m_left   = 350.0f;
		dst.m_right  = 525.0f;
		dst.m_bottom = 625.0f;
		Draw::Draw(7, &src, &dst, sp, 0.0f);

		//���ޑI���{�^���쐬
		src.m_top    = 0.0f;
		src.m_left   = 0.0f;
		src.m_right  = 225.0f;
		src.m_bottom = 225.0f;
		//�����I���{�^���쐬
		src.m_top    = 0.0f;
		src.m_left   = 0.0f;
		src.m_right  = 225.0f;
		src.m_bottom = 225.0f;

		dst.m_top    = 200.0f;
		dst.m_left   = 350.0f;
		dst.m_right  = 525.0f;
		dst.m_bottom = 375.0f;
		Draw::Draw(5, &src, &dst, ma, 0.0f);
		dst.m_top    = 450.0f;
		dst.m_left   = 700.0f;
		dst.m_right  = 875.0f;
		dst.m_bottom = 625.0f;
		Draw::Draw(8, &src, &dst, eq, 0.0f);
	}

	//�߂�{�^����I�����ĕ`�悷��摜
	else if (m_key_md == true)
	{
		//�w�i
		//�؂���
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 100.0f;
		src.m_bottom = 100.0f;

		//�X�y�V�����Z�I���{�^���쐬
		src.m_top    = 0.0f;
		src.m_left   = 0.0f;
		src.m_right  = 225.0f;
		src.m_bottom = 225.0f;

		dst.m_top    = 450.0f;
		dst.m_left   = 350.0f;
		dst.m_right  = 525.0f;
		dst.m_bottom = 625.0f;
		Draw::Draw(7, &src, &dst, sp, 0.0f);

		//�q�ɕ\��
		//�؂���
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 225.0f;
		//�����I���{�^���쐬
		src.m_top    = 0.0f;
		src.m_left   = 0.0f;
		src.m_right  = 225.0f;
		src.m_bottom = 225.0f;

		dst.m_top = 100.0f;
		dst.m_left = 100.0f;
		dst.m_right = 325.0f;
		dst.m_bottom = 325.0f;

		//2�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
		Draw::Draw(2, &src, &dst, c, 0.0f);
		dst.m_top    = 450.0f;
		dst.m_left   = 700.0f;
		dst.m_right  = 875.0f;
		dst.m_bottom = 625.0f;
		Draw::Draw(8, &src, &dst, eq, 0.0f);
	}

}

