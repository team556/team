//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"//�f�o�b�O�p
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjMessage::Init()
{
	for (int i = 0; i < FONT_MAX; i++)
	{
		m_font_column[i] = 0;
		m_font_line[i] = 0;
		m_font_draw_x[i] = 0;
		m_font_draw_y[i] = 0;
	}

	m_time = 0;
	m_font_count = 0;
	m_progress = 0;
	m_length = 0;
	m_fast_f = false;
	m_skip_f = false;

	m_mou_x = 0.0f;
	m_mou_y = 0.0f;
	m_mou_r = false;
	m_mou_l = false;
	m_key_f = false;

	m_run_switch = true;


	//-------------------------------------------------------------------------------
	//�����b�Z�[�W���ݒ�
	//�ȉ��̂悤�Ɂu�V�[��ID(if��)�ƃ��b�Z�[�W��(swprintf_s)�v�̂Q�łP�Z�b�g�Ƃ��Đݒ肷��B
	//���b�Z�[�W���͕K���S�p������p���鎖�B
	//���p�����A�o�^����ĂȂ��������͎g�p�s�Ȃ̂Œ��ӁB(���͂���Ƌ󔒈����ƂȂ�)
	//�����ꏈ���ɂ���
	//�ȉ��̑S�p������ł����ނƁA���ꂼ����ꏈ�����s���܂��B
	//�u�Q�v�c�c��
	//�u���v�c�c���s
	//�u�G�v�c�c���b�Z�[�W�I��
	//�����b�Z�[�W�I�������Ȃ���Ήi���ɓǂݍ��ݑ����A�₪�ēǂݎ��ᔽ����������)
	//�u�b�v�c�c���b�Z�[�W�\���@�\��~
	//���S�Ẵ��b�Z�[�W�I����A
	//�܂��̓��b�Z�[�W�r���Ƀv���C���[��
	//�������삳���������ɂ��̑S�p�����������ĉ������B

	//�e�X�g
	if (Scene_id == 0)
	{
		swprintf_s(m_font[0], L"�����������������Q���������P�Q�R�Q�P�R�Q�R�P�Q�P�R�P�Q�P�R�Q�G");//���b�Z�[�W�P
		swprintf_s(m_font[1], L"�������������P�Q�R�G");//���b�Z�[�W�Q
		swprintf_s(m_font[2], L"�����P�Q�Q�Q�R�G");//���b�Z�[�W�R
		swprintf_s(m_font[3], L"|");//���b�Z�[�W�S
		swprintf_s(m_font[4], L"�����P�Q�Q�Q�R�G");//���b�Z�[�W�T
		swprintf_s(m_font[5], L"|");//���b�Z�[�W�S
	}
	//�e�X�g
	if (Scene_id == 1)
	{

	}
}

//�A�N�V����
void CObjMessage::Action()
{
	//�}�E�X�̈ʒu���擾
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//�}�E�X�̃{�^���̏��
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	//���ēx�N��������ꍇ�A�y�[�W���₵��m_run_switch��true�ɂ���
	//��~�ݒ�
	if (m_run_switch == false)
	{
		if (m_progress == 3)
		{
			if (Input::GetVKey('A') == true)
			{
				m_progress++;
				m_run_switch = true;
			}
		}

		return;
	}
	if (m_font[m_progress][m_font_count] == L'|')
	{
		m_run_switch = false;
		m_skip_f = false;
		return;
	}

	//�����񒷂�����
	if (m_length == 0)
	{
		for (int i = 0; m_font[m_progress][i] != L'�G'; i++)
		{
			m_length = i;
		}
	}

	//�L�[�t���O
	if (m_mou_l == false)
	{
		m_key_f = false;
	}

	
	if (m_font[m_progress][m_font_count] == L'�G' || m_skip_f == true)
	{
		//�N���b�N�Ŏ��̕��͂ցB
		if (m_mou_l == true && m_key_f == false || m_skip_f == true)
		{
			for (int i = 0; i < FONT_MAX; i++)
			{
				m_font_column[i] = 0;
				m_font_line[i] = 0;
				m_font_draw_x[i] = 0;
				m_font_draw_y[i] = 0;
			}

			m_time = 0;
			m_font_count = 0;
			m_progress++;
			m_length = 0;
			m_fast_f = false;

			m_key_f = true;
		}
	}
	else if (m_time <= 0 || m_fast_f == true)
	{
		//�o�^���ꂽ�������猻�݂̕����ɓ��Ă͂܂���̂�T���A
		//������΁A�K�؂Ȑ؂���ʒu��Ԃ��B
		//��������Ȃ���΋󔒂�Ԃ��B
		//���V���ɕ�����o�^�������ꍇ�A
		//�ȉ��̂悤��if���ŕ�����o�^���A�K�؂Ȑ؂���ʒu��ݒ肷�ׂ��B
		//���Ȃ݂ɁA�]�T������΂��̕����͊֐�������\��B
		if (m_font[m_progress][m_font_count] == L'��')
		{
			m_font_column[m_font_count] = 3;
			m_font_line[m_font_count] = 1;
		}
		else if (m_font[m_progress][m_font_count] == L'��')
		{
			m_font_column[m_font_count] = 3;
			m_font_line[m_font_count] = 2;
		}
		else if (m_font[m_progress][m_font_count] == L'��')
		{
			m_font_column[m_font_count] = 3;
			m_font_line[m_font_count] = 3;
		}
		else if (m_font[m_progress][m_font_count] == L'��')
		{
			m_font_column[m_font_count] = 2;
			m_font_line[m_font_count] = 1;
		}
		else if (m_font[m_progress][m_font_count] == L'��')
		{
			m_font_column[m_font_count] = 2;
			m_font_line[m_font_count] = 2;
		}
		else if (m_font[m_progress][m_font_count] == L'��')
		{
			m_font_column[m_font_count] = 2;
			m_font_line[m_font_count] = 3;
		}
		else if (m_font[m_progress][m_font_count] == L'�P')
		{
			m_font_column[m_font_count] = 1;
			m_font_line[m_font_count] = 1;
		}
		else if (m_font[m_progress][m_font_count] == L'�Q')
		{
			m_font_column[m_font_count] = 1;
			m_font_line[m_font_count] = 2;
		}
		else if (m_font[m_progress][m_font_count] == L'�R')
		{
			m_font_column[m_font_count] = 1;
			m_font_line[m_font_count] = 3;
		}
		else if (m_font[m_progress][m_font_count] == L'�Q')
		{
			m_font_column[m_font_count] = 0;
			m_font_line[m_font_count] = 0;
		}
		else if (m_font[m_progress][m_font_count] == L'��')
		{
			m_font_column[m_font_count] = 0;
			m_font_line[m_font_count] = 0;

			m_font_draw_x[m_font_count + 1] = 0;
			m_font_count++;

			for (int i = m_font_count; i <= m_length; i++)
			{
				m_font_draw_y[i]++;
			}

			return;
		}

		m_font_draw_x[m_font_count + 1] = m_font_draw_x[m_font_count] + 1;
		m_font_count++;
		m_time = 5;
	}
	else
	{
		m_time--;
	}


	//���N���b�N���ꂽ��t�H���g�����\��
	if (m_mou_l == true && m_key_f == false)
	{
		m_fast_f = true;
		m_key_f = true;
	}
	//Z�L�[�����͂��ꂽ�烁�b�Z�[�W��S�Ĕ�΂�
	else if (Input::GetVKey('Z') == true)
	{
		m_skip_f = true;
	}
}

//�h���[
void CObjMessage::Draw()
{
	//�����b�Z�[�W�\���@�\OFF���̓h���[���������s���Ȃ�����
	if (m_run_switch == false)
	{
		return;
	}


	float d[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu

	//�����b�Z�[�W�E�C���h�E�\��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	dst.m_top = 630.0f;
	dst.m_left = 20.0f;
	dst.m_right = 1180.0f;
	dst.m_bottom = 680.0f;
	Draw::Draw(2, &src, &dst, d, 0.0f);

	if (m_length != 0)
	{
		for (int i = 0; i <= m_length; i++)
		{
			//���t�H���g�\��
			src.m_top = FONT_CLIP_SIZE * (m_font_line[i] - 1);
			src.m_left = FONT_CLIP_SIZE * (m_font_column[i] - 1);
			src.m_right = FONT_CLIP_SIZE * m_font_column[i];
			src.m_bottom = FONT_CLIP_SIZE * m_font_line[i];

			dst.m_top = 500.0f + (FONT_DRAW_SIZE * m_font_draw_y[i]);
			dst.m_left = 50.0f + (FONT_DRAW_SIZE * m_font_draw_x[i]);
			dst.m_right = 50.0f + (FONT_DRAW_SIZE * (m_font_draw_x[i] + 1));
			dst.m_bottom = 500.0f + (FONT_DRAW_SIZE * (m_font_draw_y[i] + 1));

			//�ȉ��̓t�H���g�؂���ʒu(��A�s)�̂ǂ��炩��0�����͂���Ă����ꍇ�A
			//���̃t�H���g��\�����Ȃ������B
			if (src.m_right == 0.0f || src.m_bottom == 0.0f)
			{
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 0.0f;
				src.m_bottom = 0.0f;

				dst.m_top = 0.0f;
				dst.m_left = 0.0f;
				dst.m_right = 0.0f;
				dst.m_bottom = 0.0f;
			}

			Draw::Draw(3, &src, &dst, d, 0.0f);
		}
	}

	//�f�o�b�O�p���}�E�X�ʒu�\��
	wchar_t mou[256];
	swprintf_s(mou, L"x=%f,y=%f", m_mou_x, m_mou_y);
	Font::StrDraw(mou, 20.0f, 20.0f, 12.0f, d);
}
