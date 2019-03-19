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
	Bar_Level_test = 1;
}

//�A�N�V����
void CObjBarracks::Action()
{
	//�����ɃE�C���h�E�\�����̏���
	if (window_start_manage == Barracks)
	{

	}
	//�z�[����ʂɖ߂�{�^���������ꂽ��A
	//���{�݂̃E�C���h�E���J���Ă��鎞�͑�����󂯕t���Ȃ��悤�ɂ���B
	else if (window_start_manage != Default)
	{
		return;
	}


	//�}�E�X�̈ʒu���擾
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//�}�E�X�̃{�^���̏��
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	//���ɑI��͈�
	if (810 < m_mou_x && m_mou_x < 1190 && 460 < m_mou_y && m_mou_y < 690)
	{
		m_message_f = true;	//���b�Z�[�W�E�C���h�E��\��������
		m_Bar_color = 0.7f;

		//���N���b�N���ꂽ��t���O�𗧂āA���ɃE�C���h�E���J��
		if (m_mou_l == true)
		{
			//�N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
			if (m_key_f == true)
			{
				m_key_f = false;

				//m_message_f = false;//���b�Z�[�W�E�C���h�E���\���ɂ�����(���ɃE�C���h�E�\�����Ɍ��ɏo���Ȃ��ׂ�)

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
		m_message_f = false;//���b�Z�[�W�E�C���h�E���\���ɂ�����
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

	//���b�Z�[�W�E�C���h�E�\���Ǘ��t���O��true�̎��A�`��B
	if (m_message_f == true)
	{
		//�����b�Z�[�W�E�C���h�E�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = m_mou_y - 50.0f;
		dst.m_left = m_mou_x - 100.0f;
		dst.m_right = m_mou_x + 100.0f;
		dst.m_bottom = m_mou_y - 10.0f;
		Draw::Draw(21, &src, &dst, b, 0.0f);

		//���t�H���g�\��
		wchar_t str[9];											//9�������i�[�\�ȕ����z���錾(99���x���ȏ�͂����Ȃ��Ƒz�肵��������)
		swprintf_s(str, L"���� Lv.%d", Bar_Level_test);			//���̕����z��ɕ����f�[�^������
		Font::StrDraw(str, m_mou_x - 75, m_mou_y - 45, 30, d);	//���̕����z���Font�ŕ`��
	}

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

		//���߂�{�^���\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 225.0f;
		src.m_bottom = 225.0f;

		dst.m_top = 30.0f;
		dst.m_left = 30.0f;
		dst.m_right = 80.0f;
		dst.m_bottom = 80.0f;
		Draw::Draw(1, &src, &dst, d, 0.0f);

		//���t�H���g�W
		//wchar_t str[9];											//9�������i�[�\�ȕ����z���錾(99���x���ȏ�͂����Ȃ��Ƒz�肵��������)
		//swprintf_s(str, L"���� Lv.%d", Bar_Level_test);			//���̕����z��ɕ����f�[�^������
		//Font::StrDraw(str, m_mou_x - 75, m_mou_y - 45, 30, d);	//���̕����z���Font�ŕ`��

		//Font::StrDraw(L"���Ƀ��x��UP", 425, 50, 120, d);

		//Font::StrDraw(L"�Z���U�蕪��", 425, 50, 120, d);

		//Font::StrDraw(L"�p���[", 425, 50, 120, d);

		//Font::StrDraw(L"�f�B�t�F���X", 425, 50, 120, d);

		//Font::StrDraw(L"�X�s�[�h", 425, 50, 120, d);

		//Font::StrDraw(L"�o�����X", 425, 50, 120, d);
	}
}