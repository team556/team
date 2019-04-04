//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"

#include "GameHead.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�}�N��
#define INI_ALPHA (0.0f) //���ߓx(�A���t�@�l)�̏����l
#define INI_COLOR (1.0f) //�S�J���[���x�̏����l

//�C�j�V�����C�Y
void CObjInstitute::Init()
{
	m_Back_Button_color = INI_COLOR;
	m_Ins_color = INI_COLOR;
	m_Ins_Lvup_color = INI_COLOR;
	m_Human_up_color = INI_COLOR;
	m_Human_down_color = INI_COLOR;

	m_introduce_f = false;
	m_key_lf = false;
	m_alpha = INI_ALPHA;
}

//�A�N�V����
void CObjInstitute::Action()
{
	//�}�E�X�̈ʒu���擾
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//�}�E�X�̃{�^���̏��
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	//���������E�C���h�E�\�����̏���
	if (window_start_manage == Institute)
	{
		//�}�E�X�J�[�\���㕔�ɕ\�������G���[���b�Z�[�W�����X�ɔ�\���ɂ���
		if (m_alpha > 0.0f)
		{
			m_alpha -= 0.01f;
		}

		//�߂�{�^�����N���b�N�A�������͉E�N���b�N(�ǂ��ł�)���鎖�Ō������E�C���h�E�����
		if (30 < m_mou_x && m_mou_x < 80 && 30 < m_mou_y && m_mou_y < 80 || m_mou_r == true)
		{
			m_Back_Button_color = 0.7f;

			//���N���b�N���ꂽ��t���O�𗧂āA�������E�C���h�E�����
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
			m_Back_Button_color = 1.0f;
		}

		//���������x��UP
		if (30 < m_mou_x && m_mou_x < 148 && 465 < m_mou_y && m_mou_y < 610)
		{
			m_Ins_Lvup_color = 0.7f;

			//���N���b�N���ꂽ��LvUP�����𖞂����Ă��邩�`�F�b�N���s���A
			//�������Ă���΁A������LvUP�̏������s���B
			//�������Ă��Ȃ���΁A�G���[���b�Z�[�W��\������B
			if (m_mou_l == true)
			{
				//���N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
				if (m_key_lf == true)
				{
					m_key_lf = false;

					m_Ins_Lvup_color = 0.0f;

					//�����Ō�����LvUP�������s���B
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
			m_Ins_Lvup_color = 1.0f;
		}

		//�������Z���U�蕪��UP
		if (695 < m_mou_x && m_mou_x < 793 && 118 < m_mou_y && m_mou_y < 218)
		{
			m_Human_up_color = 0.7f;

			//���N���b�N���ꂽ��U�蕪���֐����Ăяo���A�Z���U�蕪���̏������s��
			if (m_mou_l == true)
			{
				//���N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
				if (m_key_lf == true)
				{
					m_key_lf = false;

					m_Human_up_color = 0.0f;

					g_Research_num = Allocation(g_Research_num, +1);//�U�蕪���֐����Ăяo��
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
		else
		{
			m_Human_up_color = 1.0f;
		}

		//�������Z���U�蕪��DOWN
		if (802 < m_mou_x && m_mou_x < 902 && 118 < m_mou_y && m_mou_y < 218)
		{
			m_Human_down_color = 0.7f;

			//���N���b�N���ꂽ��U�蕪���֐����Ăяo���A�Z���U�蕪���̏������s��
			if (m_mou_l == true)
			{
				//���N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
				if (m_key_lf == true)
				{
					m_key_lf = false;

					m_Human_down_color = 0.0f;

					g_Research_num = Allocation(g_Research_num, -1);//�U�蕪���֐����Ăяo��
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
		else
		{
			m_Human_down_color = 1.0f;
		}

		//�~�T�C���{�^��
		if (515 < m_mou_x && m_mou_x < 1120 && 325 < m_mou_y && m_mou_y < 473)
		{
			m_Mis_Button_color = 0.7f;

			//���N���b�N���ꂽ��t���O�𗧂āA�~�T�C���E�C���h�E���J��
			if (m_mou_l == true)
			{
				//���N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
				if (m_key_lf == true)
				{
					m_key_lf = false;

					m_Mis_Button_color = 0.0f;

					//�G���[���b�Z�[�W���\���ɂ��邽�߁A���ߓx��0.0f�ɂ���
					m_alpha = 0.0f;

					//"�~�T�C���E�C���h�E���J���Ă�����"�t���O�𗧂Ă�
					window_start_manage = Missile;
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
		else
		{
			m_Mis_Button_color = 1.0f;
		}
		
		//����|�b�h�{�^��
		if (515 < m_mou_x && m_mou_x < 1120 && 493 < m_mou_y && m_mou_y < 641)
		{
			m_Equ_Button_color = 0.7f;

			//���N���b�N���ꂽ��t���O�𗧂āA����|�b�h�E�C���h�E���J��
			if (m_mou_l == true)
			{
				//���N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
				if (m_key_lf == true)
				{
					m_key_lf = false;

					m_Equ_Button_color = 0.0f;

					//�G���[���b�Z�[�W���\���ɂ��邽�߁A���ߓx��0.0f�ɂ���
					m_alpha = 0.0f;

					//"����|�b�h�E�C���h�E���J���Ă�����"�t���O�𗧂Ă�
					window_start_manage = Equipment;
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
		else
		{
			m_Equ_Button_color = 1.0f;
		}


		return;
	}
	//���~�T�C���E�C���h�E�\�����̏���
	else if (window_start_manage == Missile)
	{
		return;
	}
	//������|�b�h�E�C���h�E�\�����̏���
	else if (window_start_manage == Equipment)
	{
		return;
	}
	//�z�[����ʂɖ߂�{�^���������ꂽ��A
	//���{�݂̃E�C���h�E���J���Ă��鎞�͑�����󂯕t���Ȃ��悤�ɂ���B
	else if (window_start_manage != Default)
	{
		return;
	}


	//�������I��͈�
	if (60 < m_mou_x && m_mou_x < 325 && 505 < m_mou_y && m_mou_y < 637)
	{
		m_introduce_f = true;	//�{�ݏЉ�E�C���h�E��\������
		m_Ins_color = 0.7f;

		//���N���b�N���ꂽ��t���O�𗧂āA�������E�C���h�E���J��
		if (m_mou_l == true)
		{
			//���N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
			if (m_key_lf == true)
			{
				m_key_lf = false;

				m_introduce_f = false;//�{�ݏЉ�E�C���h�E���\���ɂ���(�������E�C���h�E�������Ɉ�u�f�荞�ނ���)

				//"�������E�C���h�E���J���Ă�����"�t���O�𗧂Ă�
				window_start_manage = Institute;
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
		m_Ins_color = 1.0f;
	}
}

//�h���[
void CObjInstitute::Draw()
{
	//���V�[���؂�ւ����o��ɔ�\���ɂ��鏈��
	if (scene_change_start == true)
	{
		return;
	}


	//���`��J���[���  R=RED  G=Green  B=Blue A=alpha(���ߏ��)
	//�F(�኱�Γ���)
	float blue[4] = { 0.0f,0.3f,0.9f,1.0f };

	//���F
	float black[4] = { 0.0f,0.0f,0.0f,1.0f };

	//���F�����̑��摜�p
	float white[4] = { 1.0f,1.0f,1.0f,1.0f };

	//�߂�{�^���p
	float back[4] = { m_Back_Button_color,m_Back_Button_color,m_Back_Button_color,1.0f };

	//�������摜�p
	float ins[4] = { m_Ins_color,m_Ins_color,m_Ins_color,1.0f };

	//������LvUP�摜�p
	float Lvup[4] = { m_Ins_Lvup_color, m_Ins_Lvup_color, m_Ins_Lvup_color,1.0f };

	//�Z���U�蕪��UP�摜�p
	float up[4] = { m_Human_up_color,m_Human_up_color,m_Human_up_color,1.0f };

	//�Z���U�蕪��DOWN�摜�p
	float down[4] = { m_Human_down_color,m_Human_down_color,m_Human_down_color,1.0f };

	//�~�T�C���{�^���p
	float missile[4] = { m_Mis_Button_color,m_Mis_Button_color,m_Mis_Button_color,1.0f };

	//����|�b�h�{�^���p
	float equip[4] = { m_Equ_Button_color,m_Equ_Button_color,m_Equ_Button_color,1.0f };

	//�G���[���b�Z�[�W�p
	float error[4] = { 1.0f,0.0f,0.0f,m_alpha };

	//���t�H���g����
	//���������x���p
	wchar_t Ins[10];								 //10�������i�[�\�ȕ����z���錾(99���x���ȏ�͂����Ȃ��Ƒz�肵��������)
	swprintf_s(Ins, L"������ Lv.%d", g_Ins_Level);//���̕����z��ɕ����f�[�^������

	//�c��Z�����p
	wchar_t human_remain[12];						 //12�������i�[�\�ȕ����z���錾(�ő�l��999999)
	swprintf_s(human_remain, L"�c�� %6d �l", g_Remain_num);//���̕����z��ɕ����f�[�^������

	//�������̏Z�����p
	wchar_t Research_num[9];						 //9�������i�[�\�ȕ����z���4�錾(���ꂼ��ő�l��999999)
	swprintf_s(Research_num, L"%6d �l", g_Research_num);//���̕����z��ɕ����f�[�^������


	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu

	//�{�݃E�C���h�E(���ɁA�������A�q��)���J���ĂȂ����ɕ\������O���t�B�b�N
	if (window_start_manage == Default || window_start_manage == BackButton)
	{
		//���������\�� 
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 75.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 460.0f;
		dst.m_left = 10.0f;
		dst.m_right = 390.0f;
		dst.m_bottom = 690.0f;
		Draw::Draw(3, &src, &dst, ins, 0.0f);

		//�{�ݏЉ�E�C���h�E�\���Ǘ��t���O��true�̎��A�`��B
		if (m_introduce_f == true)
		{
			//���{�ݏЉ�E�C���h�E�\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 64.0f;
			src.m_bottom = 64.0f;

			dst.m_top = m_mou_y - 50.0f;
			dst.m_left = m_mou_x - 120.0f;
			dst.m_right = m_mou_x + 110.0f;
			dst.m_bottom = m_mou_y - 10.0f;
			Draw::Draw(21, &src, &dst, ins, 0.0f);//�D�F�̃E�C���h�E�ɂ����"ins"�ɂ��Ă���B

			//���t�H���g�\��
			//���������x��
			Font::StrDraw(Ins, m_mou_x - 95.0f, m_mou_y - 45.0f, 30.0f, white);
		}
	}
	
	//�������E�C���h�E�J���Ă���ۂɕ\������O���t�B�b�N
	else if (window_start_manage == Institute)
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

		//���������\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 75.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 150.0f;
		dst.m_left = 100.0f;
		dst.m_right = 400.0f;
		dst.m_bottom = 350.0f;
		Draw::Draw(3, &src, &dst, white, 0.0f);

		//��������LVUP�\��
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

		dst.m_top = 235.0f;
		dst.m_left = 750.0f;
		dst.m_right = 1160.0f;
		dst.m_bottom = 305.0f;
		Draw::Draw(21, &src, &dst, white, 0.0f);

		//���������U�蕪��UP�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 120.0f;
		dst.m_left = 700.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 220.0f;
		Draw::Draw(23, &src, &dst, up, 0.0f);

		//���������U�蕪��DOWN�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 120.0f;
		dst.m_left = 810.0f;
		dst.m_right = 910.0f;
		dst.m_bottom = 220.0f;
		Draw::Draw(24, &src, &dst, down, 0.0f);

		//���������̏Z�����E�C���h�E�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 140.0f;
		dst.m_left = 930.0f;
		dst.m_right = 1150.0f;
		dst.m_bottom = 200.0f;
		Draw::Draw(21, &src, &dst, white, 0.0f);

		//���~�T�C���{�^���\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 269.0f;
		src.m_bottom = 96.0f;

		dst.m_top = 330.0f;
		dst.m_left = 520.0f;
		dst.m_right = 1130.0f;
		dst.m_bottom = 480.0f;
		Draw::Draw(25, &src, &dst, missile, 0.0f);

		//������|�b�h�{�^���\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 269.0f;
		src.m_bottom = 96.0f;

		dst.m_top = 500.0f;
		dst.m_left = 520.0f;
		dst.m_right = 1130.0f;
		dst.m_bottom = 650.0f;
		Draw::Draw(26, &src, &dst, equip, 0.0f);

		//���t�H���g�\��
		//���������x��
		Font::StrDraw(Ins, 105.0f, 95.0f, 50.0f, white);

		//�c��Z����
		Font::StrDraw(human_remain, 780.0f, 245.0f, 50.0f, black);

		//�������̏Z����
		Font::StrDraw(Research_num, 950.0f, 150.0f, 40.0f, black);

		Font::StrDraw(L"���������x���t�o", 40.0f, 370.0f, 50.0f, white);

		Font::StrDraw(L"�Z���U�蕪��", 620.0f, 45.0f, 60.0f, white);

		Font::StrDraw(L"������", 505.0f, 145.0f, 55.0f, blue);

		Font::StrDraw(L"�����x��UP����", 175.0f, 440.0f, 25.0f, black);
		Font::StrDraw(L"���łł�", 175.0f, 470.0f, 25.0f, black);
		Font::StrDraw(L"���x��UP�o���܂���B", 175.0f, 500.0f, 25.0f, black);

		//�G���[���b�Z�[�W
		Font::StrDraw(m_error, m_mou_x - 110.0f, m_mou_y - 45.0f, 30.0f, error);
	}
	
	//�~�T�C���E�C���h�E�J���Ă���ۂɕ\������O���t�B�b�N
	else if (window_start_manage == Missile)
	{
		//���������E�C���h�E�̏�ɊJ���Ă���悤�Ɍ����邽�߁A
		//�_�~�[�̌������E�C���h�E�̃O���t�B�b�N��`�悷��B

		//���D�F�E�C���h�E�\��(�_�~�[�������E�C���h�E�p)
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1160.0f;
		src.m_bottom = 660.0f;

		dst.m_top = 20.0f;
		dst.m_left = 20.0f;
		dst.m_right = 1180.0f;
		dst.m_bottom = 680.0f;
		Draw::Draw(20, &src, &dst, white, 0.0f);

		//���߂�{�^���\��(�_�~�[�������E�C���h�E�p)
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 30.0f;
		dst.m_left = 30.0f;
		dst.m_right = 80.0f;
		dst.m_bottom = 80.0f;
		Draw::Draw(1, &src, &dst, back, 0.0f);

		//��������LVUP�\��(�_�~�[�������E�C���h�E�p)
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 48.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 470.0f;
		dst.m_left = 30.0f;
		dst.m_right = 150.0f;
		dst.m_bottom = 620.0f;
		Draw::Draw(22, &src, &dst, Lvup, 0.0f);

		//�����x��UP�����E�C���h�E�\��(�_�~�[�������E�C���h�E�p)
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 420.0f;
		dst.m_left = 150.0f;
		dst.m_right = 450.0f;
		dst.m_bottom = 670.0f;
		Draw::Draw(21, &src, &dst, white, 0.0f);


		//���ȉ��̓~�T�C���E�C���h�E�ŕ`�悷�����

		//���D�F�E�C���h�E�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1160.0f;
		src.m_bottom = 660.0f;

		dst.m_top = 40.0f;
		dst.m_left = 40.0f;
		dst.m_right = 1160.0f;
		dst.m_bottom = 660.0f;
		Draw::Draw(20, &src, &dst, white, 0.0f);

		//���߂�{�^���\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 50.0f;
		dst.m_left = 50.0f;
		dst.m_right = 100.0f;
		dst.m_bottom = 100.0f;
		Draw::Draw(1, &src, &dst, back, 0.0f);

		//���~�T�C���\�� 
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 80.0f;
		src.m_bottom = 82.0f;

		dst.m_top = 150.0f;
		dst.m_left = 100.0f;
		dst.m_right = 400.0f;
		dst.m_bottom = 350.0f;
		Draw::Draw(4, &src, &dst, white, 0.0f);
	}

	//����|�b�h�E�C���h�E�J���Ă���ۂɕ\������O���t�B�b�N
	else if (window_start_manage == Equipment)
	{
		//���������E�C���h�E�̏�ɊJ���Ă���悤�Ɍ����邽�߁A
		//�_�~�[�̌������E�C���h�E�̃O���t�B�b�N��`�悷��B

		//���D�F�E�C���h�E�\��(�_�~�[�������E�C���h�E�p)
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1160.0f;
		src.m_bottom = 660.0f;

		dst.m_top = 20.0f;
		dst.m_left = 20.0f;
		dst.m_right = 1180.0f;
		dst.m_bottom = 680.0f;
		Draw::Draw(20, &src, &dst, white, 0.0f);

		//���߂�{�^���\��(�_�~�[�������E�C���h�E�p)
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 30.0f;
		dst.m_left = 30.0f;
		dst.m_right = 80.0f;
		dst.m_bottom = 80.0f;
		Draw::Draw(1, &src, &dst, back, 0.0f);

		//��������LVUP�\��(�_�~�[�������E�C���h�E�p)
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 48.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 470.0f;
		dst.m_left = 30.0f;
		dst.m_right = 150.0f;
		dst.m_bottom = 620.0f;
		Draw::Draw(22, &src, &dst, Lvup, 0.0f);

		//�����x��UP�����E�C���h�E�\��(�_�~�[�������E�C���h�E�p)
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 420.0f;
		dst.m_left = 150.0f;
		dst.m_right = 450.0f;
		dst.m_bottom = 670.0f;
		Draw::Draw(21, &src, &dst, white, 0.0f);


		//���ȉ��͕���|�b�h�E�C���h�E�ŕ`�悷�����

		//���D�F�E�C���h�E�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1160.0f;
		src.m_bottom = 660.0f;

		dst.m_top = 40.0f;
		dst.m_left = 40.0f;
		dst.m_right = 1160.0f;
		dst.m_bottom = 660.0f;
		Draw::Draw(20, &src, &dst, white, 0.0f);

		//���߂�{�^���\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 50.0f;
		dst.m_left = 50.0f;
		dst.m_right = 100.0f;
		dst.m_bottom = 100.0f;
		Draw::Draw(1, &src, &dst, back, 0.0f);
	}



	//�f�o�b�O�p���}�E�X�ʒu�\��
	wchar_t str[256];
	swprintf_s(str, L"x=%f,y=%f", m_mou_x, m_mou_y);
	Font::StrDraw(str, 20, 20, 12, white);
}

