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
	m_Mis_Button_color = INI_COLOR;
	m_Equ_Button_color = INI_COLOR;

	for (int i = 0; i < 15; i++)
	{
		m_Equ_pic_color[i] = INI_COLOR;//�S�Ă̗v�f�̒l��INI_COLOR�ŏ��������Ă���
	}

	m_mou_x = 0.0f;
	m_mou_y = 0.0f;
	m_mou_r = false;
	m_mou_l = false;
	m_introduce_f = false;
	m_key_lf = false;
	m_message_red_color = INI_COLOR;
	m_message_green_color = INI_COLOR;
	m_message_blue_color = INI_COLOR;
	m_alpha = INI_ALPHA;

	//���~�T�C�����L���X�g�^�C��(RCT)�ݒ�
	m_Mis_recast_time[0] = 5.0f;//�~�T�C�����L���X�g���x��(RCLv)��0�̎���RCT(�������x��)
	m_Mis_recast_time[1] = 4.2f;//RCLv��1�̎���RCT
	m_Mis_recast_time[2] = 3.4f;//RCLv��2�̎���RCT
	m_Mis_recast_time[3] = 2.6f;//RCLv��3�̎���RCT
	m_Mis_recast_time[4] = 1.8f;//RCLv��4�̎���RCT(�ő僌�x��)

	//���~�T�C�����L���X�g�̎���LVUP�ɕK�v�Ȍ��������x���ݒ�
	m_Mis_recast_next_Ins_Lv[0] = 1; //�~�T�C�����L���X�g���x��(RCLv)��0�̎��̕K�v���������x��
	m_Mis_recast_next_Ins_Lv[1] = 3; //RCLv��1�̎��̕K�v���������x��
	m_Mis_recast_next_Ins_Lv[2] = 6; //RCLv��2�̎��̕K�v���������x��
	m_Mis_recast_next_Ins_Lv[3] = 10; //RCLv��3�̎��̕K�v���������x��

	//���~�T�C�����L���X�g�̎���LVUP�ɕK�v�Ȍ������̏Z�����ݒ�
	m_Mis_recast_next_Hum_num[0] = 100;  //�~�T�C�����L���X�g���x��(RCLv)��0�̎��̕K�v��������
	m_Mis_recast_next_Hum_num[1] = 1000; //RCLv��1�̎��̕K�v��������
	m_Mis_recast_next_Hum_num[2] = 5000; //RCLv��2�̎��̕K�v��������
	m_Mis_recast_next_Hum_num[3] = 10000;//RCLv��3�̎��̕K�v��������
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
				//�O�V�[��(�~�T�C���E�C���h�E��)����E�N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
				if (m_key_rf == true)
				{
					//�E�C���h�E������A�����Ė߂�{�^������͂��Ȃ��悤��static�ϐ���false�����Đ���
					m_key_rf = false;

					//�G���[���b�Z�[�W���\���ɂ��邽�߁A���ߓx��0.0f�ɂ���
					m_alpha = 0.0f;

					//"�ǂ̃E�C���h�E���J���Ă��Ȃ����"�t���O�𗧂Ă�
					window_start_manage = Default;
				}
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
			m_key_rf = true;
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

					//���~�T�C�����L���X�g���x��UP�`�F�b�N
					//���x��UP�����𖞂����Ă��邩�`�F�b�N���A
					//�������Ă���΃��x��UP������B
					if (g_Mis_Recast_Level == MIS_MAX_LV - 1)
					{
						;//�ő僌�x���̎��͂��̃`�F�b�N�������΂�
					}
					else if (g_Ins_Level >= m_Mis_recast_next_Ins_Lv[g_Mis_Recast_Level] &&
						g_Research_num >= m_Mis_recast_next_Hum_num[g_Mis_Recast_Level])
					{
						g_Mis_Recast_Level++;//�����𖞂����Ă���̂Ń��x��UP
					}
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

					//���~�T�C�����L���X�g���x��DOWN�`�F�b�N
					//���x��DOWN�����𖞂����Ă��邩�`�F�b�N���A
					//�������Ă���΃��x��DOWN������B
					if (g_Mis_Recast_Level == 0)
					{
						;//�������x���̎��͂��̃`�F�b�N�������΂�
					}
					else if (g_Research_num < m_Mis_recast_next_Hum_num[g_Mis_Recast_Level - 1])
					{
						g_Mis_Recast_Level--;//�����𖞂����Ă���̂Ń��x��DOWN
					}
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
	//���~�T�C���E�C���h�E�A�������͕���|�b�h�E�C���h�E�\�����̏���
	else if (window_start_manage == Missile || window_start_manage == Equipment)
	{
		//�߂�{�^�����N���b�N�A�������͉E�N���b�N(�ǂ��ł�)���鎖�ł��̃E�C���h�E�����
		if (50 < m_mou_x && m_mou_x < 100 && 50 < m_mou_y && m_mou_y < 100 || m_mou_r == true)
		{
			m_Back_Button_color = 0.7f;

			//���N���b�N���ꂽ��t���O�𗧂āA���̃E�C���h�E�����
			//�E�N���b�N���͎�
			if (m_mou_r == true)
			{
				//�E�C���h�E������A�����Ė߂�{�^������͂��Ȃ��悤��static�ϐ���false�����Đ���
				m_key_rf = false;

				//����K�v�f��&�l�����b�Z�[�W���\���ɂ��邽�߁A���ߓx��0.0f�ɂ���
				m_alpha = 0.0f;

				//"�������E�C���h�E���J���Ă�����"�t���O�𗧂Ă�
				window_start_manage = Institute;
			}
			//���N���b�N���͎�
			else if (m_mou_l == true)
			{
				//���N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
				if (m_key_lf == true)
				{
					m_key_lf = false;

					//����K�v�f��&�l�����b�Z�[�W���\���ɂ��邽�߁A���ߓx��0.0f�ɂ���
					m_alpha = 0.0f;

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
			m_Back_Button_color = 1.0f;
		}


		//����|�b�h�E�C���h�E���J���Ă����ꍇ�A�X�Ɉȉ��̏������s��
		if (window_start_manage == Equipment)
		{
			//�p���[����Lv.1
			if (277 < m_mou_x && m_mou_x < 407 && 207 < m_mou_y && m_mou_y < 336)
			{
				m_alpha = 1.0f;
			}

			//�p���[����Lv.2
			else if (277 < m_mou_x && m_mou_x < 407 && 355 < m_mou_y && m_mou_y < 483)
			{
				m_alpha = 1.0f;
			}

			//�p���[����Lv.3
			else if (277 < m_mou_x && m_mou_x < 407 && 503 < m_mou_y && m_mou_y < 632)
			{
				m_alpha = 1.0f;
			}

			//�f�B�t�F���X����Lv.1
			else if (445 < m_mou_x && m_mou_x < 575 && 207 < m_mou_y && m_mou_y < 336)
			{
				m_alpha = 1.0f;
			}

			//�f�B�t�F���X����Lv.2
			else if (445 < m_mou_x && m_mou_x < 575 && 355 < m_mou_y && m_mou_y < 483)
			{
				m_alpha = 1.0f;
			}

			//�f�B�t�F���X����Lv.3
			else if (445 < m_mou_x && m_mou_x < 575 && 503 < m_mou_y && m_mou_y < 632)
			{
				m_alpha = 1.0f;
			}

			//�X�s�[�h����Lv.1
			else if (614 < m_mou_x && m_mou_x < 744 && 207 < m_mou_y && m_mou_y < 336)
			{
				m_alpha = 1.0f;
			}

			//�X�s�[�h����Lv.2
			else if (614 < m_mou_x && m_mou_x < 744 && 355 < m_mou_y && m_mou_y < 483)
			{
				m_alpha = 1.0f;
			}

			//�X�s�[�h����Lv.3
			else if (614 < m_mou_x && m_mou_x < 744 && 503 < m_mou_y && m_mou_y < 632)
			{
				m_alpha = 1.0f;
			}

			//�o�����X����Lv.1
			else if (783 < m_mou_x && m_mou_x < 913 && 207 < m_mou_y && m_mou_y < 336)
			{
				m_alpha = 1.0f;
			}

			//�o�����X����Lv.2
			else if (783 < m_mou_x && m_mou_x < 913 && 355 < m_mou_y && m_mou_y < 483)
			{
				m_alpha = 1.0f;
			}

			//�o�����X����Lv.3
			else if (783 < m_mou_x && m_mou_x < 913 && 503 < m_mou_y && m_mou_y < 632)
			{
				m_alpha = 1.0f;
			}

			//�|�b�hLv.1
			else if (952 < m_mou_x && m_mou_x < 1081 && 207 < m_mou_y && m_mou_y < 336)
			{
				m_alpha = 1.0f;
			}

			//�|�b�hLv.2
			else if (952 < m_mou_x && m_mou_x < 1081 && 355 < m_mou_y && m_mou_y < 483)
			{
				m_alpha = 1.0f;
			}

			//�|�b�hLv.3
			else if (952 < m_mou_x && m_mou_x < 1081 && 503 < m_mou_y && m_mou_y < 632)
			{
				m_alpha = 1.0f;
			}

			//��L�͈̔͊O�Ƀ}�E�X�J�[�\��������ꍇ�A
			//����K�v�f��&�l�����b�Z�[�W���\���ɂ���
			else
			{
				m_alpha = 0.0f;
			}
		}


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
	//�ԐF
	float red[4] = { 1.0f,0.0f,0.0f,1.0f };

	//�F
	float blue[4] = { 0.0f,0.0f,1.0f,1.0f };

	//�F(�኱�Γ���)
	float blue2[4] = { 0.0f,0.3f,0.9f,1.0f };

	//�ΐF
	float green[4] = { 0.0f,1.0f,0.0f,1.0f };

	//���F
	float yellow[4] = { 1.0f,1.0f,0.0f,1.0f };

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

	//����|�b�h�摜�W�p
	float equip_pic[15][4] =
	{
		{ m_Equ_pic_color[0],m_Equ_pic_color[0],m_Equ_pic_color[0],1.0f },
		{ m_Equ_pic_color[1],m_Equ_pic_color[1],m_Equ_pic_color[1],1.0f },
		{ m_Equ_pic_color[2],m_Equ_pic_color[2],m_Equ_pic_color[2],1.0f },
		{ m_Equ_pic_color[3],m_Equ_pic_color[3],m_Equ_pic_color[3],1.0f },
		{ m_Equ_pic_color[4],m_Equ_pic_color[4],m_Equ_pic_color[4],1.0f },
		{ m_Equ_pic_color[5],m_Equ_pic_color[5],m_Equ_pic_color[5],1.0f },
		{ m_Equ_pic_color[6],m_Equ_pic_color[6],m_Equ_pic_color[6],1.0f },
		{ m_Equ_pic_color[7],m_Equ_pic_color[7],m_Equ_pic_color[7],1.0f },
		{ m_Equ_pic_color[8],m_Equ_pic_color[8],m_Equ_pic_color[8],1.0f },
		{ m_Equ_pic_color[9],m_Equ_pic_color[9],m_Equ_pic_color[9],1.0f },
		{ m_Equ_pic_color[10],m_Equ_pic_color[10],m_Equ_pic_color[10],1.0f },
		{ m_Equ_pic_color[11],m_Equ_pic_color[11],m_Equ_pic_color[11],1.0f },
		{ m_Equ_pic_color[12],m_Equ_pic_color[12],m_Equ_pic_color[12],1.0f },
		{ m_Equ_pic_color[13],m_Equ_pic_color[13],m_Equ_pic_color[13],1.0f },
		{ m_Equ_pic_color[14],m_Equ_pic_color[14],m_Equ_pic_color[14],1.0f },
	};

	//����K�v�f��&�l���t�H���g�p
	float Wep_message_font[4] = { 0.0f,0.0f,0.0f,m_alpha };

	//����K�v�f��&�l���E�C���h�E�p
	float Wep_message_window[4] = { 1.0f,1.0f,1.0f,m_alpha };

	//�ȈՃ��b�Z�[�W(�G���[���b�Z�[�W�A���x��UP�\����)�p
	float message[4] = { m_message_red_color,m_message_green_color,m_message_blue_color,m_alpha };

	//���t�H���g����
	//���������x���p
	wchar_t Ins[10];								 //10�������i�[�\�ȕ����z���錾(99���x���ȏ�͂����Ȃ��Ƒz�肵��������)
	swprintf_s(Ins, L"������ Lv.%d", g_Ins_Level);//���̕����z��ɕ����f�[�^������

	//�c��Z�����p
	wchar_t human_remain[12];						 //12�������i�[�\�ȕ����z���錾(�ő�l��999999)
	swprintf_s(human_remain, L"�c�� %6d �l", g_Remain_num);//���̕����z��ɕ����f�[�^������

	//�������̏Z�����p
	wchar_t Research_num[9];						 //9�������i�[�\�ȕ����z���錾(�ő�l��999999)
	swprintf_s(Research_num, L"%6d �l", g_Research_num);//���̕����z��ɕ����f�[�^������

	//�~�T�C�����L���X�g�^�C���p
	wchar_t Mis_recast[7];							 //7�������i�[�\�ȕ����z���錾(�ő�l��99.9f)
	swprintf_s(Mis_recast, L"%4.1f s", m_Mis_recast_time[g_Mis_Recast_Level]);//���̕����z��ɕ����f�[�^������

	//�~�T�C�����L���X�g����LVUP�Ɋւ�����p
	wchar_t Next_Lvup[26];							 //26�������i�[�\�ȕ����z���錾
	//�ő僌�x���̎��̏���
	if (g_Mis_Recast_Level == MIS_MAX_LV - 1)
	{
		swprintf_s(Next_Lvup, L"����ȏヌ�x��UP�o���܂���");//���̕����z��ɕ����f�[�^������
	}
	//����ȊO�̃��x���̎��̏���
	else
	{
		swprintf_s(Next_Lvup, L"Lv.%2d & %6d �l = %4.1f s", 
			m_Mis_recast_next_Ins_Lv[g_Mis_Recast_Level], 
			m_Mis_recast_next_Hum_num[g_Mis_Recast_Level], 
			m_Mis_recast_time[g_Mis_Recast_Level + 1]);//���̕����z��ɕ����f�[�^������
	}
	

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

		Font::StrDraw(L"������", 505.0f, 145.0f, 55.0f, blue2);

		Font::StrDraw(L"�����x��UP����", 175.0f, 440.0f, 25.0f, black);
		Font::StrDraw(L"���łł�", 175.0f, 470.0f, 25.0f, red);
		Font::StrDraw(L"���x��UP�o���܂���B", 175.0f, 500.0f, 25.0f, red);

		//�ȈՃ��b�Z�[�W(�G���[���b�Z�[�W�A���x��UP�\����)
		Font::StrDraw(m_message, m_mou_x - 110.0f, m_mou_y - 45.0f, 30.0f, message);
	}
	
	//�~�T�C���E�C���h�E�A�������͕���|�b�h�E�C���h�E�J���Ă���ۂɕ\������O���t�B�b�N
	else if (window_start_manage == Missile || window_start_manage == Equipment)
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
		Draw::Draw(1, &src, &dst, white, 0.0f);

		//��������LVUP�\��(�_�~�[�������E�C���h�E�p)
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 48.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 470.0f;
		dst.m_left = 30.0f;
		dst.m_right = 150.0f;
		dst.m_bottom = 620.0f;
		Draw::Draw(22, &src, &dst, white, 0.0f);

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


		//���ȉ��̓~�T�C���E�C���h�E�A����|�b�h�E�C���h�E�̂ǂ���ł��`��

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


		//���ȉ��̓~�T�C���E�C���h�E�ŕ`�悷�����
		if (window_start_manage == Missile)
		{
			//���~�T�C���\�� 
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 80.0f;
			src.m_bottom = 82.0f;

			dst.m_top = 325.0f;
			dst.m_left = 75.0f;
			dst.m_right = 375.0f;
			dst.m_bottom = 575.0f;
			Draw::Draw(4, &src, &dst, white, 0.0f);

			//�����b�Z�[�W�E�C���h�E��3�\��
			for (int i = 0; i < 3; i++)
			{
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 64.0f;
				src.m_bottom = 64.0f;

				dst.m_top = 75.0f + 190.0f * i;
				dst.m_left = 400.0f;
				dst.m_right = 1150.0f;
				dst.m_bottom = 255.0f + 190.0f * i;
				Draw::Draw(21, &src, &dst, white, 0.0f);
			}

			//���t�H���g�\��
			//���������x��
			Font::StrDraw(Ins, 590.0f, 95.0f, 65.0f, black);

			//�������̏Z����
			Font::StrDraw(L"������", 510.0f, 175.0f, 65.0f, black);
			Font::StrDraw(Research_num, 750.0f, 175.0f, 65.0f, black);

			//�~�T�C�����L���X�g�^�C��
			Font::StrDraw(L"�Đ��Y�X�s�[�h(���L���X�g)", 455.0f, 285.0f, 50.0f, black);
			Font::StrDraw(Mis_recast, 660.0f, 350.0f, 75.0f, black);

			//�~�T�C�����L���X�g����LVUP�Ɋւ�����
			Font::StrDraw(L"NEXT LV UP", 740.0f, 475.0f, 65.0f, black);
			Font::StrDraw(Next_Lvup, 450.0f, 560.0f, 50.0f, black);
		}

		//���ȉ��͕���|�b�h�E�C���h�E�ŕ`�悷�����
		else // (window_start_manage == Equipment)
		{
			//������|�b�h�摜�W��\��
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					src.m_top = 0.0f;
					src.m_left = 0.0f;
					src.m_right = 64.0f;
					src.m_bottom = 64.0f;

					dst.m_top = 210.0f + j * 150.0f;
					dst.m_left = 280.0f + i * 170.0f;
					dst.m_right = 410.0f + i * 170.0f;
					dst.m_bottom = 340.0f + j * 150.0f;
					Draw::Draw(49 + j + i * 3, &src, &dst, equip_pic[j + i * 3], 0.0f);
				}
			}

			//���t�H���g�\��
			//���탌�x��
			wchar_t weapon_Lv[5];
			for (int i = 0; i < 3; i++)
			{
				swprintf_s(weapon_Lv, L"Lv.%d", i + 1);
				Font::StrDraw(weapon_Lv, 80.0f, 250.0f + i * 150.0f, 50.0f, white);
			}

			//�e�^�C�v(�p���[�A�X�s�[�h��)�A�|�b�h�̃t�H���g
			Font::StrDraw(L"�p���[", 285.0f, 98.0f, 40.0f, red);

			Font::StrDraw(L"�f�B�t�F���X", 440.0f, 105.0f, 25.0f, blue);

			Font::StrDraw(L"�X�s�[�h", 615.0f, 100.0f, 35.0f, green);

			Font::StrDraw(L"�o�����X", 785.0f, 100.0f, 35.0f, white);

			Font::StrDraw(L"�|�b�h", 965.0f, 97.0f, 40.0f, yellow);

			//������K�v�f��&�l�����b�Z�[�W�\��
			//�E�C���h�E�\�� 
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 64.0f;
			src.m_bottom = 64.0f;

			dst.m_top = m_mou_y - 210.0f;
			dst.m_left = m_mou_x - 150.0f;
			dst.m_right = m_mou_x + 150.0f;
			dst.m_bottom = m_mou_y + 0.0f;
			Draw::Draw(21, &src, &dst, Wep_message_window, 0.0f);
		}
	}

	

	//�f�o�b�O�p���}�E�X�ʒu�\��
	wchar_t str[256];
	swprintf_s(str, L"x=%f,y=%f", m_mou_x, m_mou_y);
	Font::StrDraw(str, 20.0f, 20.0f, 12.0f, white);
}

