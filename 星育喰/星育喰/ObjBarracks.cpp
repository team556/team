//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"

#include "GameHead.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�}�N��
#define INI_ALPHA (0.0f) //���ߓx(�A���t�@�l)�̏����l
#define INI_COLOR (0.9f) //�S�J���[���x�̏����l(�A�C�R�����I�𒆂̃J���[)

//�C�j�V�����C�Y
void CObjBarracks::Init()
{
	m_Back_Button_color = INI_COLOR;
	m_Bar_color = INI_COLOR;
	m_Bar_Lvup_color = INI_COLOR;

	for (int i = 0; i < 4; i++)
	{
		m_Human_up_color[i] = INI_COLOR;	//�S�Ă̗v�f�̒l��INI_COLOR�ŏ��������Ă���
		m_Human_down_color[i] = INI_COLOR;	//�S�Ă̗v�f�̒l��INI_COLOR�ŏ��������Ă���
	}

	m_mou_x = 0.0f;
	m_mou_y = 0.0f;
	m_mou_r = false;
	m_mou_l = false;
	m_introduce_f = false;
	m_finalcheck_f = false;
	m_key_lf = false;
	m_alpha = INI_ALPHA;
}

//�A�N�V����
void CObjBarracks::Action()
{
	//�}�E�X�̈ʒu���擾
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//�}�E�X�̃{�^���̏��
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	//�����ɃE�C���h�E�\�����̏���
	if (window_start_manage == Barracks)
	{
		//�}�E�X�J�[�\���㕔�ɕ\�������G���[���b�Z�[�W�����X�ɔ�\���ɂ���
		if (m_alpha > 0.0f)
		{
			m_alpha -= 0.01f;
		}

		//�߂�{�^�����N���b�N�A�������͉E�N���b�N(�ǂ��ł�)���鎖�ŕ��ɃE�C���h�E�����
		if (30 < m_mou_x && m_mou_x < 80 && 30 < m_mou_y && m_mou_y < 80 || m_mou_r == true)
		{
			m_Back_Button_color = 1.0f;

			//���N���b�N���ꂽ��t���O�𗧂āA���ɃE�C���h�E�����
			//�E�N���b�N���͎�
			if (m_mou_r == true)
			{
				//�E�C���h�E������A�����Ė߂�{�^������͂��Ȃ��悤��static�ϐ���false�����Đ���
				m_key_rf = false;

				//�G���[���b�Z�[�W���\���ɂ��邽�߁A���ߓx��0.0f�ɂ���
				m_alpha = 0.0f;

				//"�ǂ̃E�C���h�E���J���Ă��Ȃ����"�t���O�𗧂Ă�
				window_start_manage = Default;
			}
			//���N���b�N���͎�
			else if (m_mou_l == true)
			{
				//���N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
				if (m_key_lf == true)
				{
					m_key_lf = false;

					//�G���[���b�Z�[�W���\���ɂ��邽�߁A���ߓx��0.0f�ɂ���
					m_alpha = 0.0f;

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
			m_Back_Button_color = INI_COLOR;
		}

		//���Ƀ��x��UP
		if (30 < m_mou_x && m_mou_x < 148 && 465 < m_mou_y && m_mou_y < 610)
		{
			m_Bar_Lvup_color = 1.0f;
			
			//���N���b�N���ꂽ��LvUP�����𖞂����Ă��邩�`�F�b�N���s���A
			//�������Ă���΁A����LvUP�̏������s���B
			//�������Ă��Ȃ���΁A�G���[���b�Z�[�W��\������B
			if (m_mou_l == true)
			{
				//���N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
				if (m_key_lf == true)
				{
					m_key_lf = false;

					m_Bar_Lvup_color = 0.0f;

					//�����ŕ���LvUP�������s���B
					//�������A���󖢎����ł���B
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
		else
		{
			m_Bar_Lvup_color = INI_COLOR;
		}

		//�p���[�Z���U�蕪��UP
		if (695 < m_mou_x && m_mou_x < 793 && 118 < m_mou_y && m_mou_y < 218)
		{
			m_Human_up_color[0] = 1.0f;

			//���N���b�N���ꂽ��U�蕪���֐����Ăяo���A�Z���U�蕪���̏������s��
			if (m_mou_l == true)
			{
				//���N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
				if (m_key_lf == true)
				{
					m_key_lf = false;

					m_Human_up_color[0] = 0.0f;
			
					g_Power_num = Allocation(g_Power_num, +1);//�U�蕪���֐����Ăяo��
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
		else
		{
			m_Human_up_color[0] = INI_COLOR;
		}

		//�f�B�t�F���X�Z���U�蕪��UP
		if (695 < m_mou_x && m_mou_x < 793 && 228 < m_mou_y && m_mou_y < 328)
		{
			m_Human_up_color[1] = 1.0f;

			//���N���b�N���ꂽ��U�蕪���֐����Ăяo���A�Z���U�蕪���̏������s��
			if (m_mou_l == true)
			{
				//���N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
				if (m_key_lf == true)
				{
					m_key_lf = false;

					m_Human_up_color[1] = 0.0f;

					g_Defense_num = Allocation(g_Defense_num, +1);//�U�蕪���֐����Ăяo��
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
		else
		{
			m_Human_up_color[1] = INI_COLOR;
		}

		//�X�s�[�h�Z���U�蕪��UP
		if (695 < m_mou_x && m_mou_x < 793 && 338 < m_mou_y && m_mou_y < 438)
		{
			m_Human_up_color[2] = 1.0f;

			//���N���b�N���ꂽ��U�蕪���֐����Ăяo���A�Z���U�蕪���̏������s��
			if (m_mou_l == true)
			{
				//���N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
				if (m_key_lf == true)
				{
					m_key_lf = false;

					m_Human_up_color[2] = 0.0f;

					g_Speed_num = Allocation(g_Speed_num, +1);//�U�蕪���֐����Ăяo��
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
		else
		{
			m_Human_up_color[2] = INI_COLOR;
		}

		//�o�����X�Z���U�蕪��UP
		if (695 < m_mou_x && m_mou_x < 793 && 448 < m_mou_y && m_mou_y < 548)
		{
			m_Human_up_color[3] = 1.0f;

			//���N���b�N���ꂽ��U�蕪���֐����Ăяo���A�Z���U�蕪���̏������s��
			if (m_mou_l == true)
			{
				//���N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
				if (m_key_lf == true)
				{
					m_key_lf = false;

					m_Human_up_color[3] = 0.0f;

					g_Balance_num = Allocation(g_Balance_num, +1);//�U�蕪���֐����Ăяo��
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
		else
		{
			m_Human_up_color[3] = INI_COLOR;
		}
		
		//�p���[�Z���U�蕪��DOWN
		if (802 < m_mou_x && m_mou_x < 902 && 118 < m_mou_y && m_mou_y < 218)
		{
			m_Human_down_color[0] = 1.0f;

			//���N���b�N���ꂽ��U�蕪���֐����Ăяo���A�Z���U�蕪���̏������s��
			if (m_mou_l == true)
			{
				//���N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
				if (m_key_lf == true)
				{
					m_key_lf = false;

					m_Human_down_color[0] = 0.0f;

					g_Power_num = Allocation(g_Power_num, -1);//�U�蕪���֐����Ăяo��
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
		else
		{
			m_Human_down_color[0] = INI_COLOR;
		}

		//�f�B�t�F���X�Z���U�蕪��DOWN
		if (802 < m_mou_x && m_mou_x < 902 && 228 < m_mou_y && m_mou_y < 328)
		{
			m_Human_down_color[1] = 1.0f;

			//���N���b�N���ꂽ��U�蕪���֐����Ăяo���A�Z���U�蕪���̏������s��
			if (m_mou_l == true)
			{
				//���N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
				if (m_key_lf == true)
				{
					m_key_lf = false;

					m_Human_down_color[1] = 0.0f;

					g_Defense_num = Allocation(g_Defense_num, -1);//�U�蕪���֐����Ăяo��
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
		else
		{
			m_Human_down_color[1] = INI_COLOR;
		}

		//�X�s�[�h�Z���U�蕪��DOWN
		if (802 < m_mou_x && m_mou_x < 902 && 338 < m_mou_y && m_mou_y < 438)
		{
			m_Human_down_color[2] = 1.0f;

			//���N���b�N���ꂽ��U�蕪���֐����Ăяo���A�Z���U�蕪���̏������s��
			if (m_mou_l == true)
			{
				//���N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
				if (m_key_lf == true)
				{
					m_key_lf = false;

					m_Human_down_color[2] = 0.0f;

					g_Speed_num = Allocation(g_Speed_num, -1);//�U�蕪���֐����Ăяo��
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
		else
		{
			m_Human_down_color[2] = INI_COLOR;
		}

		//�o�����X�Z���U�蕪��DOWN
		if (802 < m_mou_x && m_mou_x < 902 && 448 < m_mou_y && m_mou_y < 548)
		{
			m_Human_down_color[3] = 1.0f;

			//���N���b�N���ꂽ��U�蕪���֐����Ăяo���A�Z���U�蕪���̏������s��
			if (m_mou_l == true)
			{
				//���N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
				if (m_key_lf == true)
				{
					m_key_lf = false;

					m_Human_down_color[3] = 0.0f;

					g_Balance_num = Allocation(g_Balance_num, -1);//�U�蕪���֐����Ăяo��
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
		else
		{
			m_Human_down_color[3] = INI_COLOR;
		}


		return;
	}
	//�z�[����ʂɖ߂�{�^���������ꂽ��A
	//���{�݂̃E�C���h�E���J���Ă��鎞�͑�����󂯕t���Ȃ��悤�ɂ���B
	else if (window_start_manage != Default)
	{
		return;
	}


	//���ɑI��͈�
	if (810 < m_mou_x && m_mou_x < 1190 && 460 < m_mou_y && m_mou_y < 690)
	{
		m_introduce_f = true;	//�{�ݏЉ�E�C���h�E��\������
		m_Bar_color = 1.0f;

		//���N���b�N���ꂽ��t���O�𗧂āA���ɃE�C���h�E���J��
		if (m_mou_l == true)
		{
			//���N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
			if (m_key_lf == true)
			{
				m_key_lf = false;

				m_introduce_f = false;//�{�ݏЉ�E�C���h�E���\���ɂ���(���ɃE�C���h�E�������Ɉ�u�f�荞�ނ���)

				//"���ɃE�C���h�E���J���Ă�����"�t���O�𗧂Ă�
				window_start_manage = Barracks;
			}
		}
		else
		{
			m_key_lf = true;
		}
	}
	else
	{
		m_introduce_f = false;//�{�ݏЉ�E�C���h�E���\���ɂ���
		m_Bar_color = INI_COLOR;
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


	//���`��J���[���  R=RED  G=Green  B=Blue A=alpha(���ߏ��)
	//�ԐF
	float red[4] = { 1.0f,0.0f,0.0f,1.0f };

	//�F
	float blue[4] = { 0.0f,0.0f,1.0f,1.0f };

	//�ΐF
	float green[4] = { 0.0f,1.0f,0.0f,1.0f };

	//���F
	float black[4] = { 0.0f,0.0f,0.0f,1.0f };

	//���F�����̑��摜�p
	float white[4] = { 1.0f,1.0f,1.0f,1.0f };

	//�߂�{�^���p
	float back[4] = { m_Back_Button_color,m_Back_Button_color,m_Back_Button_color,1.0f };

	//���ɉ摜�p
	float bar[4] = { m_Bar_color,m_Bar_color,m_Bar_color,1.0f };

	//����LvUP�摜�p
	float Lvup[4] = { m_Bar_Lvup_color, m_Bar_Lvup_color, m_Bar_Lvup_color,1.0f };

	//�Z���U�蕪��UP�摜�p
	float up[4][4] =
	{
		{ m_Human_up_color[0],m_Human_up_color[0],m_Human_up_color[0],1.0f },
		{ m_Human_up_color[1],m_Human_up_color[1],m_Human_up_color[1],1.0f },
		{ m_Human_up_color[2],m_Human_up_color[2],m_Human_up_color[2],1.0f },
		{ m_Human_up_color[3],m_Human_up_color[3],m_Human_up_color[3],1.0f },
	};

	//�Z���U�蕪��DOWN�摜�p
	float down[4][4] =
	{
		{ m_Human_down_color[0],m_Human_down_color[0],m_Human_down_color[0],1.0f },
		{ m_Human_down_color[1],m_Human_down_color[1],m_Human_down_color[1],1.0f },
		{ m_Human_down_color[2],m_Human_down_color[2],m_Human_down_color[2],1.0f },
		{ m_Human_down_color[3],m_Human_down_color[3],m_Human_down_color[3],1.0f },
	};

	//�G���[���b�Z�[�W�p
	float error[4] = { 1.0f,0.0f,0.0f,m_alpha };

	//���t�H���g����
	//���Ƀ��x���p
	wchar_t Bar[9];									 //9�������i�[�\�ȕ����z���錾(99���x���ȏ�͂����Ȃ��Ƒz�肵��������)
	swprintf_s(Bar, L"���� Lv.%d", g_Bar_Level);//���̕����z��ɕ����f�[�^������

	//�c��Z�����p
	wchar_t human_remain[12];						 //12�������i�[�\�ȕ����z���錾(�ő�l��999999)
	swprintf_s(human_remain, L"�c�� %6d �l", g_Remain_num);//���̕����z��ɕ����f�[�^������

	//�e�^�C�v(�p���[�A�X�s�[�h��)�̏Z�����p
	wchar_t human_num[4][9];						 //9�������i�[�\�ȕ����z���4�錾(���ꂼ��ő�l��999999)
	swprintf_s(human_num[0], L"%6d �l", g_Power_num);//�����ꂼ��̕����z��ɑΉ����镶���f�[�^������
	swprintf_s(human_num[1], L"%6d �l", g_Defense_num);
	swprintf_s(human_num[2], L"%6d �l", g_Speed_num);
	swprintf_s(human_num[3], L"%6d �l", g_Balance_num);


	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu

	//�{�݃E�C���h�E(���ɁA�������A�q��)���J���ĂȂ����ɕ\������O���t�B�b�N
	if (window_start_manage == Default || window_start_manage == BackButton)
	{
		//�����ɕ\�� 
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 256.0f;
		src.m_bottom = 256.0f;

		dst.m_top = 460.0f;
		dst.m_left = 810.0f;
		dst.m_right = 1190.0f;
		dst.m_bottom = 690.0f;
		Draw::Draw(2, &src, &dst, bar, 0.0f);

		//�{�ݏЉ�E�C���h�E�\���Ǘ��t���O��true�̎��A�`��B
		if (m_introduce_f == true)
		{
			//���{�ݏЉ�E�C���h�E�\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 64.0f;
			src.m_bottom = 64.0f;

			dst.m_top = m_mou_y - 50.0f;
			dst.m_left = m_mou_x - 100.0f;
			dst.m_right = m_mou_x + 100.0f;
			dst.m_bottom = m_mou_y - 10.0f;
			Draw::Draw(21, &src, &dst, white, 0.0f);

			//���t�H���g�\��
			//���Ƀ��x��
			Font::StrDraw(Bar, m_mou_x - 75.0f, m_mou_y - 45.0f, 30.0f, black);
		}
	}

	//���ɃE�C���h�E�J���Ă���ۂɕ\������O���t�B�b�N
	else if (window_start_manage == Barracks)
	{
		//���D�F�E�C���h�E�\��
		src.m_top    =    0.0f;
		src.m_left   =    0.0f;
		src.m_right  = 1160.0f;
		src.m_bottom =  660.0f;

		dst.m_top = 20.0f;
		dst.m_left = 20.0f;
		dst.m_right = 1180.0f;
		dst.m_bottom = 680.0f;
		Draw::Draw(20, &src, &dst, white, 0.0f);

		//���߂�{�^���\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 30.0f;
		dst.m_left = 30.0f;
		dst.m_right = 80.0f;
		dst.m_bottom = 80.0f;
		Draw::Draw(1, &src, &dst, back, 0.0f);

		//�����ɕ\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 245.0f;
		src.m_bottom = 206.0f;

		dst.m_top = 150.0f;
		dst.m_left = 100.0f;
		dst.m_right = 400.0f;
		dst.m_bottom = 350.0f;
		Draw::Draw(2, &src, &dst, white, 0.0f);

		//������LVUP�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 48.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 470.0f;
		dst.m_left = 30.0f;
		dst.m_right = 150.0f;
		dst.m_bottom = 620.0f;
		Draw::Draw(22, &src, &dst, Lvup, 0.0f);

		//�����x��UP�����E�C���h�E�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 420.0f;
		dst.m_left = 150.0f;
		dst.m_right = 450.0f;
		dst.m_bottom = 670.0f;
		Draw::Draw(21, &src, &dst, white, 0.0f);

		//���c��Z�����̃E�C���h�E�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 580.0f;
		dst.m_left = 750.0f;
		dst.m_right = 1160.0f;
		dst.m_bottom = 650.0f;
		Draw::Draw(21, &src, &dst, white, 0.0f);

		for (int i = 0; i < 4; i++)
		{
			//�����ɐU�蕪��UP�\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 64.0f;
			src.m_bottom = 64.0f;

			dst.m_top = 120.0f + i * 110.0f;
			dst.m_left = 700.0f;
			dst.m_right = 800.0f;
			dst.m_bottom = 220.0f + i * 110.0f;
			Draw::Draw(23, &src, &dst, up[i], 0.0f);

			//�����ɐU�蕪��DOWN�\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 64.0f;
			src.m_bottom = 64.0f;

			dst.m_top = 120.0f + i * 110.0f;
			dst.m_left = 810.0f;
			dst.m_right = 910.0f;
			dst.m_bottom = 220.0f + i * 110.0f;
			Draw::Draw(24, &src, &dst, down[i], 0.0f);

			//���e�^�C�v(�p���[�A�X�s�[�h��)�̏Z�����E�C���h�E�\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 64.0f;
			src.m_bottom = 64.0f;

			dst.m_top = 140.0f + i * 110.0f;
			dst.m_left = 930.0f;
			dst.m_right = 1150.0f;
			dst.m_bottom = 200.0f + i * 110.0f;
			Draw::Draw(21, &src, &dst, white, 0.0f);
		}

		//���t�H���g�\��
		//���Ƀ��x��
		Font::StrDraw(Bar, 125.0f, 95.0f, 50.0f, white);

		//�c��Z����
		Font::StrDraw(human_remain, 780.0f, 590.0f, 50.0f, black);

		//�e�^�C�v(�p���[�A�X�s�[�h��)�̏Z����
		for (int i = 0; i < 4; i++)
		{
			Font::StrDraw(human_num[i], 950.0f, 150.0f + i * 110.0f, 40.0f, black);
		}

		//���̑��t�H���g
		Font::StrDraw(L"���Ƀ��x���t�o", 60.0f, 370.0f, 50.0f, white);

		Font::StrDraw(L"�Z���U�蕪��", 620.0f, 45.0f, 60.0f, white);

		Font::StrDraw(L"�p���[", 505.0f, 145.0f, 55.0f, red);

		Font::StrDraw(L"�f�B�t�F���X", 450.0f, 260.0f, 40.0f, blue);

		Font::StrDraw(L"�X�s�[�h", 480.0f, 365.0f, 50.0f, green);

		Font::StrDraw(L"�o�����X", 480.0f, 475.0f, 50.0f, white);

		Font::StrDraw(L"�����x��UP����", 175.0f, 440.0f, 25.0f, black);
		Font::StrDraw(L"���łł�", 175.0f, 470.0f, 25.0f, red);
		Font::StrDraw(L"���x��UP�o���܂���B", 175.0f, 500.0f, 25.0f, red);

		//�G���[���b�Z�[�W
		Font::StrDraw(m_message, m_mou_x - 110.0f, m_mou_y - 45.0f, 30.0f, error);
		


		//�f�o�b�O�p���}�E�X�ʒu�\��
		wchar_t str[256];
		swprintf_s(str, L"x=%f,y=%f", m_mou_x, m_mou_y);
		Font::StrDraw(str, 20.0f, 20.0f, 12.0f, white);
	}
}