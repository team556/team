//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"//�f�o�b�O�p
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"

//#include <string.h> 

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjMessage::Init()
{
	//str = "";//������

	for (int i = 0; i < STR_MAX; i++)
	{
		str_column[i] = 0;
		str_line[i] = 0;
		str_draw_x[i] = 0;
		str_draw_y[i] = 0;
	}

	time = 0;
	text_count = 0;
	now_max = 0;


	m_mou_x = 0.0f;
	m_mou_y = 0.0f;
	m_mou_r = false;
	m_mou_l = false;
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

	//���p�����{�o�^����ĂȂ������͎g�p�s��
	//�u�Q�v�͋󔒁A�u���v�͉��s�A�u�G�v�ŕ��͏I��(���͏I������Ȃ��Ɖi���ɓǂݍ��ݑ����A�₪�ēǂݎ��ᔽ����������)

	swprintf_s(str[0], L"�����Q�����������R�P�Q�G");//���b�Z�[�W�P
	
	//�����񒷂�����
	if (now_max == 0)
	{
		for (int i = 0; str[0][i] != L'�G'; i++)
		{
			now_max = i;
		}
	}

	
	if (str[0][text_count] == L'�G')
	{
		;//�N���b�N�Ŏ��̕��͂ցB
	}
	else if (time <= 0)//���͕\���r���ŃN���b�N���ꂽ��A�����̒l��30(���b���ɕ\���̒l�ƈꏏ�ɂ��ďu�ԕ\��������)
	{
		if (str[0][text_count] == L'��')
		{
			str_column[text_count] = 3;
			str_line[text_count] = 1;
		}
		else if (str[0][text_count] == L'��')
		{
			str_column[text_count] = 3;
			str_line[text_count] = 2;
		}
		else if (str[0][text_count] == L'��')
		{
			str_column[text_count] = 3;
			str_line[text_count] = 3;
		}
		else if (str[0][text_count] == L'��')
		{
			str_column[text_count] = 2;
			str_line[text_count] = 1;
		}
		else if (str[0][text_count] == L'��')
		{
			str_column[text_count] = 2;
			str_line[text_count] = 2;
		}
		else if (str[0][text_count] == L'��')
		{
			str_column[text_count] = 2;
			str_line[text_count] = 3;
		}
		else if (str[0][text_count] == L'�P')
		{
			str_column[text_count] = 1;
			str_line[text_count] = 1;
		}
		else if (str[0][text_count] == L'�Q')
		{
			str_column[text_count] = 1;
			str_line[text_count] = 2;
		}
		else if (str[0][text_count] == L'�R')
		{
			str_column[text_count] = 1;
			str_line[text_count] = 3;
		}
		else if (str[0][text_count] == L'�Q')
		{
			str_column[text_count] = 0;
			str_line[text_count] = 0;
		}
		else if (str[0][text_count] == L'��')
		{
			str_column[text_count] = 0;
			str_line[text_count] = 0;

			str_draw_x[text_count + 1] = 0;
			text_count++;
			time = 60;

			for (int i = text_count; i <= now_max; i++)
			{
				str_draw_y[i]++;
			}

			return;
		}

		str_draw_x[text_count + 1] = str_draw_x[text_count] + 1;
		text_count++;
		time = 60;
	}
	else
	{
		time--;
	}
}

//�h���[
void CObjMessage::Draw()
{
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

	if (now_max != 0)
	{
		for (int i = 0; i <= now_max; i++)
		{
			//���t�H���g�\��
			src.m_top = STR_SIZE * (str_line[i] - 1);
			src.m_left = STR_SIZE * (str_column[i] - 1);
			src.m_right = STR_SIZE * str_column[i];
			src.m_bottom = STR_SIZE * str_line[i];

			//�s�A��̂ǂ��炩��0�����͂���Ă����ꍇ�A���̃t�H���g��\�����Ȃ��B
			if (src.m_right == 0.0f || src.m_bottom == 0.0f)
			{
				src.m_top = 0.0f;
				src.m_left = 0.0f;
			}

			dst.m_top = 500.0f + (STR_SIZE * str_draw_y[i]);
			dst.m_left = 50.0f + (STR_SIZE * str_draw_x[i]);
			dst.m_right = 50.0f + (STR_SIZE * (str_draw_x[i] + 1));
			dst.m_bottom = 500.0f + (STR_SIZE * (str_draw_y[i] + 1));

			Draw::Draw(3, &src, &dst, d, 0.0f);
		}
	}

	//�f�o�b�O�p���}�E�X�ʒu�\��
	wchar_t mou[256];
	swprintf_s(mou, L"x=%f,y=%f", m_mou_x, m_mou_y);
	Font::StrDraw(mou, 20.0f, 20.0f, 12.0f, d);
}
