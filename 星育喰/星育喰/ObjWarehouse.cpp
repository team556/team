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
	m_f = false;

	m_x = 100;
	m_y = 100;
	//m_obx = 0;
	//m_oby = 0;

	//m_key_f = true;
	//m_turn = true;
	//m_turn0 = true;
	//
	//m_obj = true;

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
	if (m_x < m_mou_x && m_mou_x < m_x+225 && m_y < m_mou_y && m_mou_y < m_y+225)
	{
		m_Ware_color = 0.7f;

		//���N���b�N���ꂽ��t���O�𗧂āA�q�ɃE�C���h�E���J��
		if (m_mou_l == true)
		{
			
			//�N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
			if (m_key_f == true)
			{
				m_key_f = false;

				//��test_flag�̃A���ł��B
				m_f = true;
			}
		}
		else
		{
			m_key_f = true;
		}
	}
	else
	{
		m_Ware_color = 1.0f;
	}

	//�߂�{�^���I��
	if (20 < m_mou_x && m_mou_x < 135 && 20 < m_mou_y && m_mou_y < 135)
	{
		m_Back_color = 0.7f;

		//���N���b�N���ꂽ��t���O�𗧂āA�q�ɃE�C���h�E�����
		if (m_mou_l == true)
		{

			//�N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
			if (m_key_md == true)
			{
				m_key_md = false;

				//��test_flag�̃A���ł��B
				m_f = true;
			}
		}
		else
		{
			m_key_md = true;
		}
	}
	else
	{
		m_Back_color = 1.0f;
	}

	//�߂�{�^���I��
	if (350 < m_mou_x && m_mou_x < 525 && 200 < m_mou_y && m_mou_y < 375)
	{
		m_Object_color[0] = 0.7f;

		//���N���b�N���ꂽ��t���O�𗧂āA�q�ɃE�C���h�E�����
		if (m_mou_l == true)
		{

			//�N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
			if (m_key_ma == true)
			{
				m_key_ma = false;

				//��test_flag�̃A���ł��B
				m_f = true;
			}
		}
		else
		{
			m_key_ma = true;
		}
	}
	else
	{
		m_Object_color[0] = 1.0f;

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

	//����ȊO�̉摜
	float sb[4] = { 1.0f,1.0f,1.0f,1.0f };
	float mb[4] = { m_Back_color,m_Back_color,m_Back_color,1.0f };
	float bt[4] = { m_Object_color[3],m_Object_color[3],m_Object_color[3],1.0f };

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

	if (m_f == true)
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
		dst.m_right  = 135.0f;
		dst.m_bottom = 135.0f;
		Draw::Draw(4, &src, &dst, mb, 0.0f);

		//���ޑI���{�^���쐬
		src.m_top    = 0.0f;
		src.m_left   = 0.0f;
		src.m_right  = 225.0f;
		src.m_bottom = 225.0f;

		dst.m_top    = 200.0f;
		dst.m_left   = 350.0f;
		dst.m_right  = 525.0f;
		dst.m_bottom = 375.0f;
		Draw::Draw(5, &src, &dst, bt, 0.0f);

		//�Z���I���{�^���쐬
		src.m_top    = 0.0f;
		src.m_left   = 0.0f;
		src.m_right  = 225.0f;
		src.m_bottom = 225.0f;

		dst.m_top    = 200.0f;
		dst.m_left   = 700.0f;
		dst.m_right  = 875.0f;
		dst.m_bottom = 375.0f;
		Draw::Draw(6, &src, &dst, bt, 0.0f);

		//�X�y�V�����Z�I���{�^���쐬
		src.m_top    = 0.0f;
		src.m_left   = 0.0f;
		src.m_right  = 225.0f;
		src.m_bottom = 225.0f;

		dst.m_top    = 450.0f;
		dst.m_left   = 350.0f;
		dst.m_right  = 525.0f;
		dst.m_bottom = 625.0f;
		Draw::Draw(7, &src, &dst, bt, 0.0f);

		//�����I���{�^���쐬
		src.m_top    = 0.0f;
		src.m_left   = 0.0f;
		src.m_right  = 225.0f;
		src.m_bottom = 225.0f;

		dst.m_top    = 450.0f;
		dst.m_left   = 700.0f;
		dst.m_right  = 875.0f;
		dst.m_bottom = 625.0f;
		Draw::Draw(8, &src, &dst, bt, 0.0f);

	}

	if (m_key_md == true)
	{
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
	}

}

