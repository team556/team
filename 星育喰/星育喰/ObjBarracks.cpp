//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"

#include "GameHead.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�}�N��
#define INI_COLOR (1.0f) //�S�J���[���x�̏����l

//�C�j�V�����C�Y
void CObjBarracks::Init()
{
	m_Bar_color = INI_COLOR;
}

//�A�N�V����
void CObjBarracks::Action()
{
	//�z�[����ʂɖ߂�{�^���������ꂽ��A
	//���{�݂̃E�C���h�E���J���Ă��鎞�͑�����󂯕t���Ȃ��悤�ɂ���B
	if (window_start_manage != Default)
	{
		return;
	}


	//�}�E�X�̈ʒu���擾
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//�}�E�X�̃{�^���̏��
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	//���ɑI��
	if (810 < m_mou_x && m_mou_x < 1190 && 460 < m_mou_y && m_mou_y < 690)
	{
		m_Bar_color = 0.7f;

		//���N���b�N���ꂽ��t���O�𗧂āA���ɃE�C���h�E���J��
		if (m_mou_l == true)
		{
			//�N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
			if (m_key_f == true)
			{
				m_key_f = false;

				//"���ɃE�C���h�E���J���Ă�����"�t���O�𗧂Ă�
				window_start_manage = Barracks;
			}
		}
		else
		{
			m_key_f = true;
		}
	}
	else
	{
		m_Bar_color = 1.0f;
	}
}

//�h���[
void CObjBarracks::Draw()
{
	//���V�[���؂�ւ����o��ɔ�\���ɂ��鏈��
	if (scene_change_start == true)
	{
		return;
	}

	//���ɉ摜�p
	float b[4] = { m_Bar_color,m_Bar_color,m_Bar_color,1.0f };

	//����ȊO�̉摜�p
	float d[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu

	//���e�X�g
	//Font::StrDraw(L"�����", 425, 50, 120, d);

	//�����ɕ\��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 245.0f;
	src.m_bottom = 206.0f;

	dst.m_top = 460.0f;
	dst.m_left = 810.0f;
	dst.m_right = 1190.0f;
	dst.m_bottom = 690.0f;
	Draw::Draw(2, &src, &dst, b, 0.0f);

	//�����ɃE�C���h�E�J���Ă���ۂɕ\������O���t�B�b�N
	if (window_start_manage == Barracks)
	{
		//���D�F�E�C���h�E�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1160.0f;
		src.m_bottom = 660.0f;

		dst.m_top = 20.0f;
		dst.m_left = 20.0f;
		dst.m_right = 1180.0f;
		dst.m_bottom = 680.0f;
		Draw::Draw(20, &src, &dst, d, 0.0f);
	}
}