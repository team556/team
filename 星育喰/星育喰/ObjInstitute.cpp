//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\Audio.h"

#include "GameHead.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�}�N��
#define INI_ALPHA (0.0f) //���ߓx(�A���t�@�l)�̏����l
#define INI_COLOR (0.9f) //�S�J���[���x�̏����l(�A�C�R�����I�𒆂̃J���[)
#define LABO_LV_1 (1)//���������x���}�N����`
#define LABO_LV_2 (2)//���������x���}�N����`
#define LABO_LV_3 (3)//���������x���}�N����`

#define MIS_LV_1 (3.0f)
#define MIS_LV_2 (2.5f)
#define MIS_LV_3 (2.0f)
#define MIS_LV_4 (1.5f)
#define MIS_LV_5 (1.0f)//1.0�����ɂ͂��Ȃ��ł�������

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
	m_Yes_Button_color = 0.0f;
	m_No_Button_color = 0.0f;

	//������|�b�h�摜�W�S�ẴJ���[���x��0.1f(���F)�ŏ�����
	for (int i = 0; i < 15; i++)
	{
		m_Equ_pic_red_color[i] = 0.1f;
		m_Equ_pic_green_color[i] = 0.1f;
		m_Equ_pic_blue_color[i] = 0.1f;
	}
	//�����݂̊e����A�|�b�h���x���ɉ�����
	//����|�b�h�摜�W�̃J���[���ȉ��̂悤�ɐݒ肵�Ă����B
	//�u�����s�v�c�c�c�c�c�c�c0.1f(���F)
	//�u���x��UP��(������)�v�c�c0.5f(�D�F)
	//�u�������v�c�c�c�c�c�c�c�c1.0f(���F)
	for (int i = 0; i < 15; i++)
	{
		//���L��if��(�e���탌�x���̍ő哞�B�x)�ɓ���܂ŁA
		//���x��1���珇�ɊD�F��ݒ肵�Ă����B
		m_Equ_pic_red_color[i] = 0.5f;
		m_Equ_pic_green_color[i] = 0.5f;
		m_Equ_pic_blue_color[i] = 0.5f;
		
		//�p���[���탌�x���̍ő哞�B�x
		if (i == g_Pow_equip_Lv_achieve - 1)
		{
			//���݂̃p���[���탌�x���̃J���[�𔒐F�ɐݒ肷��
			m_Equ_pic_red_color[g_Pow_equip_Level - 1] = 1.0f;
			m_Equ_pic_green_color[g_Pow_equip_Level - 1] = 1.0f;
			m_Equ_pic_blue_color[g_Pow_equip_Level - 1] = 1.0f;
			
			i = 2;//�f�B�t�F���X���탌�x���̃J���[�ݒ菈�����J�n������
		}
		//�f�B�t�F���X���탌�x���̍ő哞�B�x
		else if (i == g_Def_equip_Lv_achieve + 2)
		{
			//���݂̃f�B�t�F���X���탌�x���̃J���[�𔒐F�ɐݒ肷��
			m_Equ_pic_red_color[g_Def_equip_Level + 2] = 1.0f;
			m_Equ_pic_green_color[g_Def_equip_Level + 2] = 1.0f;
			m_Equ_pic_blue_color[g_Def_equip_Level + 2] = 1.0f;
			
			i = 5;//�X�s�[�h���탌�x���̃J���[�ݒ菈�����J�n������
		}
		//�X�s�[�h���탌�x���̍ő哞�B�x
		else if (i == g_Spe_equip_Lv_achieve + 5)
		{
			//���݂̃X�s�[�h���탌�x���̃J���[�𔒐F�ɐݒ肷��
			m_Equ_pic_red_color[g_Spe_equip_Level + 5] = 1.0f;
			m_Equ_pic_green_color[g_Spe_equip_Level + 5] = 1.0f;
			m_Equ_pic_blue_color[g_Spe_equip_Level + 5] = 1.0f;
			
			i = 8;//�o�����X���탌�x���̃J���[�ݒ菈�����J�n������
		}
		//�o�����X���탌�x���̍ő哞�B�x
		else if (i == g_Bal_equip_Lv_achieve + 8)
		{
			//���݂̃o�����X���탌�x���̃J���[�𔒐F�ɐݒ肷��
			m_Equ_pic_red_color[g_Bal_equip_Level + 8] = 1.0f;
			m_Equ_pic_green_color[g_Bal_equip_Level + 8] = 1.0f;
			m_Equ_pic_blue_color[g_Bal_equip_Level + 8] = 1.0f;

			i = 11;//�|�b�h���x���̃J���[�ݒ菈�����J�n������
		}
		//�|�b�h���x���̍ő哞�B�x
		else if(i == g_Pod_equip_Lv_achieve + 11)
		{
			//���݂̃|�b�h���x���̃J���[�𔒐F�ɐݒ肷��
			m_Equ_pic_red_color[g_Bal_equip_Level + 11] = 1.0f;
			m_Equ_pic_green_color[g_Bal_equip_Level + 11] = 1.0f;
			m_Equ_pic_blue_color[g_Bal_equip_Level + 11] = 1.0f;

			break;//�J���[�ݒ菈�����I��������
		}
	}


	m_Equ_message_window_x_size = 0.0f;
	m_Equ_message_window_y_size = 0.0f;

	m_mou_x = 0.0f;
	m_mou_y = 0.0f;
	m_mou_r = false;
	m_mou_l = false;
	m_introduce_f = false;
	m_finalcheck_f = false;
	m_key_lf = false;
	m_message_red_color = INI_COLOR;
	m_message_green_color = INI_COLOR;
	m_message_blue_color = INI_COLOR;
	m_alpha = INI_ALPHA;

	//-----------------------------------------------------------------------------------------------------

	//���~�T�C�����L���X�g�^�C��(RCT)�ݒ�
	m_Mis_recast_time[0] = MIS_LV_1;//�~�T�C�����L���X�g���x��(RCLv)��0�̎���RCT(�������x��)
	m_Mis_recast_time[1] = MIS_LV_2;//RCLv��1�̎���RCT
	m_Mis_recast_time[2] = MIS_LV_3;//RCLv��2�̎���RCT
	m_Mis_recast_time[3] = MIS_LV_4;//RCLv��3�̎���RCT
	m_Mis_recast_time[4] = MIS_LV_5;//RCLv��4�̎���RCT(�ő僌�x��)

	//���~�T�C�����L���X�g�̎���LVUP�ɕK�v�Ȍ��������x���ݒ�
	m_Mis_recast_next_Ins_Lv[0] = LABO_LV_1; //�~�T�C�����L���X�g���x��(RCLv)��0�̎��̕K�v���������x��
	m_Mis_recast_next_Ins_Lv[1] = LABO_LV_2; //RCLv��1�̎��̕K�v���������x��
	m_Mis_recast_next_Ins_Lv[2] = LABO_LV_3; //RCLv��2�̎��̕K�v���������x��
	m_Mis_recast_next_Ins_Lv[3] = LABO_LV_3; //RCLv��3�̎��̕K�v���������x��

	//���~�T�C�����L���X�g�̎���LVUP�ɕK�v�Ȍ������̏Z�����ݒ�
	m_Mis_recast_next_Hum_num[0] = 100;  //�~�T�C�����L���X�g���x��(RCLv)��0�̎��̕K�v��������
	m_Mis_recast_next_Hum_num[1] = 600; //RCLv��1�̎��̕K�v��������
	m_Mis_recast_next_Hum_num[2] = 2000; //RCLv��2�̎��̕K�v��������
	m_Mis_recast_next_Hum_num[3] = 4500;//RCLv��3�̎��̕K�v��������

	//-----------------------------------------------------------------------------------------------------

	//���e����A�|�b�h�̎���LVUP�ɕK�v�Ȍ������̏Z�����ݒ�
	//���p���[����
	m_Equ_next_Hum_num[0][0] = 100;  //���x����1�̎��̕K�v��������
	m_Equ_next_Hum_num[0][1] = 1000; //���x����2�̎��̕K�v��������
	//���f�B�t�F���X����
	m_Equ_next_Hum_num[1][0] = 200;  //���x����1�̎��̕K�v��������
	m_Equ_next_Hum_num[1][1] = 1000; //���x����2�̎��̕K�v��������
	//���X�s�[�h����
	m_Equ_next_Hum_num[2][0] = 300;  //���x����1�̎��̕K�v��������
	m_Equ_next_Hum_num[2][1] = 1000; //���x����2�̎��̕K�v��������
	//���o�����X����
	m_Equ_next_Hum_num[3][0] = 500;  //���x����1�̎��̕K�v��������
	m_Equ_next_Hum_num[3][1] = 1000; //���x����2�̎��̕K�v��������
	//���|�b�h
	m_Equ_next_Hum_num[4][0] = 300;  //���x����1�̎��̕K�v��������
	m_Equ_next_Hum_num[4][1] = 1000; //���x����2�̎��̕K�v��������

	//���e����A�|�b�h�̎���LVUP�ɕK�v�ȑf�ނ̖��O�ݒ�
	//���p���[����
	swprintf_s(m_Equ_next_Mat_name[0][0], L"�S");			 //���x����1�̎��̕K�v�f�ޖ�
	swprintf_s(m_Equ_next_Mat_name[0][1], L"�K�X");		 //���x����2�̎��̕K�v�f�ޖ�
	//���f�B�t�F���X����
	swprintf_s(m_Equ_next_Mat_name[1][0], L"�S");			 //���x����1�̎��̕K�v�f�ޖ�
	swprintf_s(m_Equ_next_Mat_name[1][1], L"��");		 //���x����2�̎��̕K�v�f�ޖ�
	//���X�s�[�h����
	swprintf_s(m_Equ_next_Mat_name[2][0], L"�S");			//���x����1�̎��̕K�v�f�ޖ�
	swprintf_s(m_Equ_next_Mat_name[2][1], L"��");		 //���x����2�̎��̕K�v�f�ޖ�
	//���o�����X����
	swprintf_s(m_Equ_next_Mat_name[3][0], L"�A���~�j�E��");		//���x����1�̎��̕K�v�f�ޖ�
	swprintf_s(m_Equ_next_Mat_name[3][1], L"�K�X");	//���x����2�̎��̕K�v�f�ޖ�
	//���|�b�h����
	swprintf_s(m_Equ_next_Mat_name[4][0], L"�A���~�j�E��");	//���x����1�̎��̕K�v�f�ޖ�
	swprintf_s(m_Equ_next_Mat_name[4][1], L"���A���^��");		 //���x����2�̎��̕K�v�f�ޖ�

	//���e����A�|�b�h�̎���LVUP�ɕK�v�ȑf�ގ�ސݒ�Ɠ����ɂ��̑f�ނ̏�������������
	//���ȉ��̂悤�ɏ����f�ސ����Ǘ����Ă���O���[�o���ϐ��̃A�h���X�������鎖�őf�ނ̎�ސݒ�Ə������̑�������Ă���B
	//���������݂͑f�ގ�ނ��m�肵�Ă��Ȃ����߁A����TEST�p�̕������Ă���B��œK�؂Ȃ��̂ɕύX���ׂ��B
	//���p���[����
	m_Equ_next_Mat_type[0][0] = &g_Iron_num;	//���x����1�̎��̕K�v�f�ގ��
	m_Equ_next_Mat_type[0][1] = &g_gus_num;	//���x����2�̎��̕K�v�f�ގ��
	//���f�B�t�F���X����
	m_Equ_next_Mat_type[1][0] = &g_Iron_num;	//���x����1�̎��̕K�v�f�ގ��
	m_Equ_next_Mat_type[1][1] = &g_Silver_num;	//���x����2�̎��̕K�v�f�ގ��
	//���X�s�[�h����
	m_Equ_next_Mat_type[2][0] = &g_Iron_num;	//���x����1�̎��̕K�v�f�ގ��
	m_Equ_next_Mat_type[2][1] = &g_Silver_num;	//���x����2�̎��̕K�v�f�ގ��
	//���o�����X����
	m_Equ_next_Mat_type[3][0] = &g_Aluminum_num;	//���x����1�̎��̕K�v�f�ގ��
	m_Equ_next_Mat_type[3][1] = &g_gus_num;	//���x����2�̎��̕K�v�f�ގ��
	//���|�b�h
	m_Equ_next_Mat_type[4][0] = &g_Aluminum_num;	//���x����1�̎��̕K�v�f�ގ��
	m_Equ_next_Mat_type[4][1] = &g_Raremetal_num;	//���x����2�̎��̕K�v�f�ގ��

	//���e����A�|�b�h�̎���LVUP�ɕK�v�ȑf�ސ��ݒ�
	//���p���[����
	m_Equ_next_Mat_num[0][0] = 30;	 //���x����1�̎��̕K�v�f�ސ�
	m_Equ_next_Mat_num[0][1] = 20;  //���x����2�̎��̕K�v�f�ސ�
	//���f�B�t�F���X����
	m_Equ_next_Mat_num[1][0] = 30;  //���x����1�̎��̕K�v�f�ސ�
	m_Equ_next_Mat_num[1][1] = 40; //���x����2�̎��̕K�v�f�ސ�
	//���X�s�[�h����
	m_Equ_next_Mat_num[2][0] = 30;  //���x����1�̎��̕K�v�f�ސ�
	m_Equ_next_Mat_num[2][1] = 25; //���x����2�̎��̕K�v�f�ސ�
	//���o�����X����
	m_Equ_next_Mat_num[3][0] = 30;  //���x����1�̎��̕K�v�f�ސ�
	m_Equ_next_Mat_num[3][1] = 30; //���x����2�̎��̕K�v�f�ސ�
	//���|�b�h
	m_Equ_next_Mat_num[4][0] = 30;  //���x����1�̎��̕K�v�f�ސ�
	m_Equ_next_Mat_num[4][1] = 50;  //���x����2�̎��̕K�v�f�ސ�

//-----------------------------------------------------------------------------------------------------

	//���������̎���LVUP�ɕK�v�ȃT�C�Y(HP)�̏Z�����ݒ�
	m_Facility_next_Size_num[0] = 5.0f;	//���x����1�̎��̕K�v�T�C�Y(HP)
	m_Facility_next_Size_num[1] = 20.0f;	//���x����2�̎��̕K�v�T�C�Y(HP)

	//���������̎���LVUP�ɕK�v�ȑf�ނ̖��O�ݒ�
	swprintf_s(m_Facility_next_Mat_name[0], L"�S");//���x����1�̎��̕K�v�f�ޖ�
	swprintf_s(m_Facility_next_Mat_name[1], L"�A���~�j�E��");//���x����2�̎��̕K�v�f�ޖ�

	//���������̎���LVUP�ɕK�v�ȑf�ގ�ސݒ�Ɠ����ɂ��̑f�ނ̏�������������
	//���ȉ��̂悤�ɏ����f�ސ����Ǘ����Ă���O���[�o���ϐ��̃A�h���X�������鎖�őf�ނ̎�ސݒ�Ə������̑�������Ă���B
	//���������݂͑f�ގ�ނ��m�肵�Ă��Ȃ����߁A����TEST�p�̕������Ă���B��œK�؂Ȃ��̂ɕύX���ׂ��B
	m_Facility_next_Mat_type[0] = &g_Iron_num;	//���x����1�̎��̕K�v�f�ގ��
	m_Facility_next_Mat_type[1] = &g_Aluminum_num;	//���x����2�̎��̕K�v�f�ގ��

	//���������̎���LVUP�ɕK�v�ȑf�ސ��ݒ�
	m_Facility_next_Mat_num[0] = 10;	//���x����1�̎��̕K�v�f�ސ�
	m_Facility_next_Mat_num[1] = 20;	//���x����2�̎��̕K�v�f�ސ�



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
		//��(������)�ŏI�m�F�E�C���h�E�\�����̏���
		if (m_finalcheck_f == true)
		{
			//�ŏI�m�F[�͂�]�{�^��
			if (410 < m_mou_x && m_mou_x < 502 && 407 < m_mou_y && m_mou_y < 450)
			{
				m_Yes_Button_color = 1.0f;

				//���N���b�N���ꂽ�猤�������x��UP�������s���A���̃E�C���h�E�����
				//���N���b�N���͎�
				if (m_mou_l == true)
				{
					//���N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
					if (m_key_lf == true)
					{
						m_key_lf = false;

						//�����������x��UP����
						//�T�C�Y(HP)�����
						g_Player_max_size -= m_Facility_next_Size_num[g_Ins_Level - 1];

						//�f�ޏ����
						*m_Facility_next_Mat_type[g_Ins_Level - 1] -= m_Facility_next_Mat_num[g_Ins_Level - 1];

						//�������̃��x��UP����
						g_Ins_Level++;

						//���~�T�C�����L���X�g���x��UP�`�F�b�N
						//���x��UP�����𖞂����Ă��邩�`�F�b�N���A
						//�������Ă���΃��x��UP������B
						Missile_Lvup_check();//�~�T�C�����L���X�g���x��UP�`�F�b�N�֐����Ăяo��

						m_Yes_Button_color = 0.0f;

						//�ŏI�m�F�E�C���h�E���\���ɂ���
						m_finalcheck_f = false;

						//�I����
						Audio::Start(1);
					}
				}
				else
				{
					m_key_lf = true;
				}
			}
			else
			{
				m_Yes_Button_color = 0.0f;
			}

			//�ŏI�m�F[������]�{�^��
			if (648 < m_mou_x && m_mou_x < 789 && 407 < m_mou_y && m_mou_y < 450 || m_mou_r == true)
			{
				m_No_Button_color = 1.0f;

				//���N���b�N���ꂽ��A���̃E�C���h�E�����
				//�E�N���b�N���͎�
				if (m_mou_r == true)
				{
					//�E�C���h�E������A�����Ė߂�{�^������͂��Ȃ��悤��static�ϐ���false�����Đ���
					m_key_rf = false;

					m_No_Button_color = 0.0f;

					//�ŏI�m�F�E�C���h�E���\���ɂ���
					m_finalcheck_f = false;

					//�߂�{�^����
					Audio::Start(2);
				}
				//���N���b�N���͎�
				else if (m_mou_l == true)
				{
					//���N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
					if (m_key_lf == true)
					{
						m_key_lf = false;

						m_No_Button_color = 0.0f;

						//�ŏI�m�F�E�C���h�E���\���ɂ���
						m_finalcheck_f = false;

						//�߂�{�^����
						Audio::Start(2);
					}
				}
				else
				{
					m_key_lf = true;
				}
			}
			else
			{
				m_No_Button_color = 0.0f;
			}


			return;
		}

		//�}�E�X�J�[�\���㕔�ɕ\�������G���[���b�Z�[�W�����X�ɔ�\���ɂ���
		if (m_alpha > 0.0f)
		{
			m_alpha -= 0.01f;
		}

		//�߂�{�^�����N���b�N�A�������͉E�N���b�N(�ǂ��ł�)���鎖�Ō������E�C���h�E�����
		if (30 < m_mou_x && m_mou_x < 80 && 30 < m_mou_y && m_mou_y < 80 || m_mou_r == true)
		{
			m_Back_Button_color = 1.0f;

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

					//�߂�{�^����
					Audio::Start(2);
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

					//�߂�{�^����
					Audio::Start(2);
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
			m_Back_Button_color = INI_COLOR;
		}

		//���������x��UP
		if (30 < m_mou_x && m_mou_x < 148 && 465 < m_mou_y && m_mou_y < 610)
		{
			m_Ins_Lvup_color = 1.0f;

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

					//�����������x��UP�\�`�F�b�N����
					if (g_Ins_Level == FACILITY_MAX_LV)
					{
						//�����x��MAX���̏���
						//���N���b�N���ꂽ��ȈՃ��b�Z�[�W�Ń��x��UP�s��`����
						swprintf_s(m_message, L"LvUP�o���܂���");//�����z��ɕ����f�[�^������

						//�ȈՃ��b�Z�[�W�̃J���[��ԐF�ɂ���
						m_message_red_color = 1.0f;
						m_message_green_color = 0.0f;
						m_message_blue_color = 0.0f;

						//�ȈՃ��b�Z�[�W��\������
						m_alpha = 1.0f;
					}
					else if (g_Player_max_size > m_Facility_next_Size_num[g_Ins_Level - 1] &&
						*m_Facility_next_Mat_type[g_Ins_Level - 1] >= m_Facility_next_Mat_num[g_Ins_Level - 1])
					{
						//�����x��UP�\���̏���
						//���N���b�N���ꂽ��t���O�𗧂āA�ŏI�m�F�E�C���h�E���J��
						m_finalcheck_f = true;//�ŏI�m�F�E�C���h�E��\������

						//�ȈՃ��b�Z�[�W���\���ɂ���
						m_alpha = 0.0f;

						m_Ins_Lvup_color = INI_COLOR;

						//���x���A�b�v��
						Audio::Start(1);

						return;
					}
					else
					{
						//�����x��UP�s���̏���
						//���N���b�N���ꂽ��ȈՃ��b�Z�[�W�Ń��x��UP�s��`����
						swprintf_s(m_message, L"LvUP�o���܂���");//�����z��ɕ����f�[�^������

						//�ȈՃ��b�Z�[�W�̃J���[��ԐF�ɂ���
						m_message_red_color = 1.0f;
						m_message_green_color = 0.0f;
						m_message_blue_color = 0.0f;

						//�ȈՃ��b�Z�[�W��\������
						m_alpha = 1.0f;
					}

					//�I����
					Audio::Start(1);
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
		else
		{
			m_Ins_Lvup_color = INI_COLOR;
		}

		//�������Z���U�蕪��UP
		if (695 < m_mou_x && m_mou_x < 793 && 118 < m_mou_y && m_mou_y < 218)
		{
			m_Human_up_color = 1.0f;

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
					Missile_Lvup_check();//�~�T�C�����L���X�g���x��UP�`�F�b�N�֐����Ăяo��

					//������|�b�h���x��UP�`�F�b�N
					//���Ƀ��x��UP�ς݂̕���|�b�h�̌��݂̌����������`�F�b�N���A
					//�����\�Ȍ��������ɒB���Ă���΁A���x��UP������B
					//�����ꂼ�ꕐ��|�b�h���x��UP�`�F�b�N�֐����Ăяo��
					g_Pow_equip_Level = Equip_Lvup_check(0, g_Pow_equip_Level, g_Pow_equip_Lv_achieve);
					g_Def_equip_Level = Equip_Lvup_check(1, g_Def_equip_Level, g_Def_equip_Lv_achieve);
					g_Spe_equip_Level = Equip_Lvup_check(2, g_Spe_equip_Level, g_Spe_equip_Lv_achieve);
					g_Bal_equip_Level = Equip_Lvup_check(3, g_Bal_equip_Level, g_Bal_equip_Lv_achieve);
					g_Pod_equip_Level = Equip_Lvup_check(4, g_Pod_equip_Level, g_Pod_equip_Lv_achieve);

					//�U�蕪���{�^����
					Audio::Start(1);
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
		else
		{
			m_Human_up_color = INI_COLOR;
		}

		//�������Z���U�蕪��DOWN
		if (802 < m_mou_x && m_mou_x < 902 && 118 < m_mou_y && m_mou_y < 218)
		{
			m_Human_down_color = 1.0f;

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


						//���~�T�C�����L���X�g�����x��DOWN���������ȈՃ��b�Z�[�W�ɂĒm�点��
						swprintf_s(m_message, L"�~�T�C�����L���X�g���x��DOWN�c");//�����z��ɕ����f�[�^������

						//���L���X�g���x��DOWN���b�Z�[�W�̃J���[�𐅐F�ɂ���
						m_message_red_color = 0.0f;
						m_message_green_color = 1.0f;
						m_message_blue_color = 1.0f;

						m_alpha = 1.0f;		//���L���X�g���x��DOWN���b�Z�[�W��\�����邽�߁A���ߓx��1.0f�ɂ���
					}

					//������|�b�h���x��DOWN�`�F�b�N
					//���Ƀ��x��UP�ς݂̕���|�b�h�̌��݂̌����������`�F�b�N���A
					//�����s�Ȍ��������ɒB���Ă���΁A���x��DOWN������B
					//�����ꂼ�ꕐ��|�b�h���x��DOWN�`�F�b�N�֐����Ăяo��
					g_Pow_equip_Level = Equip_Lvdown_check(0, g_Pow_equip_Level);
					g_Def_equip_Level = Equip_Lvdown_check(1, g_Def_equip_Level);
					g_Spe_equip_Level = Equip_Lvdown_check(2, g_Spe_equip_Level);
					g_Bal_equip_Level = Equip_Lvdown_check(3, g_Bal_equip_Level);
					g_Pod_equip_Level = Equip_Lvdown_check(4, g_Pod_equip_Level);

					//�U�蕪���_�E����
					Audio::Start(2);
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
		else
		{
			m_Human_down_color = INI_COLOR;
		}

		//�~�T�C���{�^��
		if (515 < m_mou_x && m_mou_x < 1120 && 325 < m_mou_y && m_mou_y < 473)
		{
			m_Mis_Button_color = 1.0f;

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

					//�I����
					Audio::Start(1);
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
		else
		{
			m_Mis_Button_color = INI_COLOR;
		}
		
		//����|�b�h�{�^��
		if (515 < m_mou_x && m_mou_x < 1120 && 493 < m_mou_y && m_mou_y < 641)
		{
			m_Equ_Button_color = 1.0f;

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

					//������|�b�hLvUP�\�`�F�b�N
					Equip_Lvup_possible_check();//����|�b�h���x��UP�\�`�F�b�N�֐����Ăяo��
		
					//"����|�b�h�E�C���h�E���J���Ă�����"�t���O�𗧂Ă�
					window_start_manage = Equipment;

					//�I����
					Audio::Start(1);
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
		else
		{
			m_Equ_Button_color = INI_COLOR;
		}


		return;
	}
	//���~�T�C���E�C���h�E�A�������͕���|�b�h�E�C���h�E�\�����̏���
	else if (window_start_manage == Missile || window_start_manage == Equipment)
	{
		//��(����|�b�h)�ŏI�m�F�E�C���h�E�\�����̏���
		if (m_finalcheck_f == true)
		{
			//�ŏI�m�F[�͂�]�{�^��
			if (410 < m_mou_x && m_mou_x < 502 && 407 < m_mou_y && m_mou_y < 450)
			{
				m_Yes_Button_color = 1.0f;

				//���N���b�N���ꂽ�畐��|�b�h���x��UP�������s���A���̃E�C���h�E�����
				//���N���b�N���͎�
				if (m_mou_l == true)
				{
					//���N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
					if (m_key_lf == true)
					{
						m_key_lf = false;

						//������|�b�h���x��UP����
						//�f�ޏ����
						*m_Equ_next_Mat_type[finalcheck_Lvup_type][*finalcheck_Lvup_achieve - 1] -= m_Equ_next_Mat_num[finalcheck_Lvup_type][*finalcheck_Lvup_achieve - 1];

						//�I����������|�b�h�^�C�v(�p���[�A�X�s�[�h��)�̃��x��UP����
						(*finalcheck_Lvup_Level)++;
						(*finalcheck_Lvup_achieve)++;

						//LvUP��A�X�Ƀ��x��UP�o���邩�m���߂�ׂɕ���|�b�h���x��UP�\�`�F�b�N���s��
						Equip_Lvup_possible_check();//����|�b�h���x��UP�\�`�F�b�N�֐����Ăяo��

						//�����x��UP�O��̑�������|�b�h�J���[��K�؂Ȃ��̂ɕύX����
						//���x��UP��̑�������̃J���[�𔒐F�ɐݒ肷��
						m_Equ_pic_red_color[*finalcheck_Lvup_achieve - 1 + finalcheck_Lvup_type * 3] = 1.0f;
						m_Equ_pic_green_color[*finalcheck_Lvup_achieve - 1 + finalcheck_Lvup_type * 3] = 1.0f;
						m_Equ_pic_blue_color[*finalcheck_Lvup_achieve - 1 + finalcheck_Lvup_type * 3] = 1.0f;

						//���x��UP�O�̑�������̃J���[���D�F�ɐݒ肷��
						m_Equ_pic_red_color[*finalcheck_Lvup_achieve - 2 + finalcheck_Lvup_type * 3] = 0.5f;
						m_Equ_pic_green_color[*finalcheck_Lvup_achieve - 2 + finalcheck_Lvup_type * 3] = 0.5f;
						m_Equ_pic_blue_color[*finalcheck_Lvup_achieve - 2 + finalcheck_Lvup_type * 3] = 0.5f;


						m_Yes_Button_color = 0.0f;

						//�ŏI�m�F�E�C���h�E���\���ɂ���
						m_finalcheck_f = false;

						//�I����
						Audio::Start(1);
					}
				}
				else
				{
					m_key_lf = true;
				}
			}
			else
			{
				m_Yes_Button_color = 0.0f;
			}

			//�ŏI�m�F[������]�{�^��
			if (648 < m_mou_x && m_mou_x < 789 && 407 < m_mou_y && m_mou_y < 450 || m_mou_r == true)
			{
				m_No_Button_color = 1.0f;

				//���N���b�N���ꂽ��A���̃E�C���h�E�����
				//�E�N���b�N���͎�
				if (m_mou_r == true)
				{
					//�E�C���h�E������A�����Ė߂�{�^������͂��Ȃ��悤��static�ϐ���false�����Đ���
					m_key_rf = false;

					m_No_Button_color = 0.0f;

					//�ŏI�m�F�E�C���h�E���\���ɂ���
					m_finalcheck_f = false;

					//�߂�{�^����
					Audio::Start(2);
				}
				//���N���b�N���͎�
				else if (m_mou_l == true)
				{
					//���N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
					if (m_key_lf == true)
					{
						m_key_lf = false;

						m_No_Button_color = 0.0f;

						//�ŏI�m�F�E�C���h�E���\���ɂ���
						m_finalcheck_f = false;

						//�߂�{�^����
						Audio::Start(2);
					}
				}
				else
				{
					m_key_lf = true;
				}
			}
			else
			{
				m_No_Button_color = 0.0f;
			}


			return;
		}

		//�߂�{�^�����N���b�N�A�������͉E�N���b�N(�ǂ��ł�)���鎖�ł��̃E�C���h�E�����
		if (50 < m_mou_x && m_mou_x < 100 && 50 < m_mou_y && m_mou_y < 100 || m_mou_r == true)
		{
			m_Back_Button_color = 1.0f;

			//���N���b�N���ꂽ��t���O�𗧂āA���̃E�C���h�E�����
			//�E�N���b�N���͎�
			if (m_mou_r == true)
			{
				//�O�V�[��(�ŏI�m�F�E�C���h�E)����E�N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
				if (m_key_rf == true)
				{
					//�E�C���h�E������A�����Ė߂�{�^������͂��Ȃ��悤��static�ϐ���false�����Đ���
					m_key_rf = false;

					//����K�v�f��&�l�����b�Z�[�W���\���ɂ��邽�߁A���ߓx��0.0f�ɂ���
					m_alpha = 0.0f;

					//"�������E�C���h�E���J���Ă�����"�t���O�𗧂Ă�
					window_start_manage = Institute;

					//�߂�{�^����
					Audio::Start(2);
				}
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

					//�߂�{�^����
					Audio::Start(2);
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
			m_Back_Button_color = INI_COLOR;
		}


		//����|�b�h�E�C���h�E���J���Ă����ꍇ�A�X�Ɉȉ��̏������s��
		if (window_start_manage == Equipment)
		{
			//�p���[����Lv.1
			if (277 < m_mou_x && m_mou_x < 407 && 207 < m_mou_y && m_mou_y < 336)
			{
				//������|�b�h�K�v�f��&�l�����b�Z�[�W��\��
				Equip_message(0, 0);//����|�b�h�K�v�f��&�l�����b�Z�[�W�\���֐����Ăяo��
			}

			//�p���[����Lv.2
			else if (277 < m_mou_x && m_mou_x < 407 && 355 < m_mou_y && m_mou_y < 483)
			{
				//������|�b�h�K�v�f��&�l�����b�Z�[�W��\��
				Equip_message(0, 1);//����|�b�h�K�v�f��&�l�����b�Z�[�W�\���֐����Ăяo��
			}

			//�p���[����Lv.3
			else if (277 < m_mou_x && m_mou_x < 407 && 503 < m_mou_y && m_mou_y < 632)
			{
				//������|�b�h�K�v�f��&�l�����b�Z�[�W��\��
				Equip_message(0, 2);//����|�b�h�K�v�f��&�l�����b�Z�[�W�\���֐����Ăяo��
			}

			//�f�B�t�F���X����Lv.1
			else if (445 < m_mou_x && m_mou_x < 575 && 207 < m_mou_y && m_mou_y < 336)
			{
				//������|�b�h�K�v�f��&�l�����b�Z�[�W��\��
				Equip_message(1, 0);//����|�b�h�K�v�f��&�l�����b�Z�[�W�\���֐����Ăяo��
			}

			//�f�B�t�F���X����Lv.2
			else if (445 < m_mou_x && m_mou_x < 575 && 355 < m_mou_y && m_mou_y < 483)
			{
				//������|�b�h�K�v�f��&�l�����b�Z�[�W��\��
				Equip_message(1, 1);//����|�b�h�K�v�f��&�l�����b�Z�[�W�\���֐����Ăяo��
			}

			//�f�B�t�F���X����Lv.3
			else if (445 < m_mou_x && m_mou_x < 575 && 503 < m_mou_y && m_mou_y < 632)
			{
				//������|�b�h�K�v�f��&�l�����b�Z�[�W��\��
				Equip_message(1, 2);//����|�b�h�K�v�f��&�l�����b�Z�[�W�\���֐����Ăяo��
			}

			//�X�s�[�h����Lv.1
			else if (614 < m_mou_x && m_mou_x < 744 && 207 < m_mou_y && m_mou_y < 336)
			{
				//������|�b�h�K�v�f��&�l�����b�Z�[�W��\��
				Equip_message(2, 0);//����|�b�h�K�v�f��&�l�����b�Z�[�W�\���֐����Ăяo��
			}

			//�X�s�[�h����Lv.2
			else if (614 < m_mou_x && m_mou_x < 744 && 355 < m_mou_y && m_mou_y < 483)
			{
				//������|�b�h�K�v�f��&�l�����b�Z�[�W��\��
				Equip_message(2, 1);//����|�b�h�K�v�f��&�l�����b�Z�[�W�\���֐����Ăяo��
			}

			//�X�s�[�h����Lv.3
			else if (614 < m_mou_x && m_mou_x < 744 && 503 < m_mou_y && m_mou_y < 632)
			{
				//������|�b�h�K�v�f��&�l�����b�Z�[�W��\��
				Equip_message(2, 2);//����|�b�h�K�v�f��&�l�����b�Z�[�W�\���֐����Ăяo��
			}

			//�o�����X����Lv.1
			else if (783 < m_mou_x && m_mou_x < 913 && 207 < m_mou_y && m_mou_y < 336)
			{
				//������|�b�h�K�v�f��&�l�����b�Z�[�W��\��
				Equip_message(3, 0);//����|�b�h�K�v�f��&�l�����b�Z�[�W�\���֐����Ăяo��
			}

			//�o�����X����Lv.2
			else if (783 < m_mou_x && m_mou_x < 913 && 355 < m_mou_y && m_mou_y < 483)
			{
				//������|�b�h�K�v�f��&�l�����b�Z�[�W��\��
				Equip_message(3, 1);//����|�b�h�K�v�f��&�l�����b�Z�[�W�\���֐����Ăяo��
			}

			//�o�����X����Lv.3
			else if (783 < m_mou_x && m_mou_x < 913 && 503 < m_mou_y && m_mou_y < 632)
			{
				//������|�b�h�K�v�f��&�l�����b�Z�[�W��\��
				Equip_message(3, 2);//����|�b�h�K�v�f��&�l�����b�Z�[�W�\���֐����Ăяo��
			}

			//�|�b�hLv.1
			else if (952 < m_mou_x && m_mou_x < 1081 && 207 < m_mou_y && m_mou_y < 336)
			{
				//������|�b�h�K�v�f��&�l�����b�Z�[�W��\��
				Equip_message(4, 0);//����|�b�h�K�v�f��&�l�����b�Z�[�W�\���֐����Ăяo��
			}

			//�|�b�hLv.2
			else if (952 < m_mou_x && m_mou_x < 1081 && 355 < m_mou_y && m_mou_y < 483)
			{
				//������|�b�h�K�v�f��&�l�����b�Z�[�W��\��
				Equip_message(4, 1);//����|�b�h�K�v�f��&�l�����b�Z�[�W�\���֐����Ăяo��
			}

			//�|�b�hLv.3
			else if (952 < m_mou_x && m_mou_x < 1081 && 503 < m_mou_y && m_mou_y < 632)
			{
				//������|�b�h�K�v�f��&�l�����b�Z�[�W��\��
				Equip_message(4, 2);//����|�b�h�K�v�f��&�l�����b�Z�[�W�\���֐����Ăяo��
			}

			//��L�͈̔͊O�Ƀ}�E�X�J�[�\��������ꍇ�A
			//����K�v�f��&�l�����b�Z�[�W���\���ɂ���
			else
			{
				m_alpha = 0.0f;//����K�v�f��&�l�����b�Z�[�W���\��
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
		m_Ins_color = 1.0f;

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

				//�I����
				Audio::Start(1);
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
		m_Ins_color = INI_COLOR;
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
		{ m_Equ_pic_red_color[0],m_Equ_pic_green_color[0],m_Equ_pic_blue_color[0],1.0f },
		{ m_Equ_pic_red_color[1],m_Equ_pic_green_color[1],m_Equ_pic_blue_color[1],1.0f },
		{ m_Equ_pic_red_color[2],m_Equ_pic_green_color[2],m_Equ_pic_blue_color[2],1.0f },
		{ m_Equ_pic_red_color[3],m_Equ_pic_green_color[3],m_Equ_pic_blue_color[3],1.0f },
		{ m_Equ_pic_red_color[4],m_Equ_pic_green_color[4],m_Equ_pic_blue_color[4],1.0f },
		{ m_Equ_pic_red_color[5],m_Equ_pic_green_color[5],m_Equ_pic_blue_color[5],1.0f },
		{ m_Equ_pic_red_color[6],m_Equ_pic_green_color[6],m_Equ_pic_blue_color[6],1.0f },
		{ m_Equ_pic_red_color[7],m_Equ_pic_green_color[7],m_Equ_pic_blue_color[7],1.0f },
		{ m_Equ_pic_red_color[8],m_Equ_pic_green_color[8],m_Equ_pic_blue_color[8],1.0f },
		{ m_Equ_pic_red_color[9],m_Equ_pic_green_color[9],m_Equ_pic_blue_color[9],1.0f },
		{ m_Equ_pic_red_color[10],m_Equ_pic_green_color[10],m_Equ_pic_blue_color[10],1.0f },
		{ m_Equ_pic_red_color[11],m_Equ_pic_green_color[11],m_Equ_pic_blue_color[11],1.0f },
		{ m_Equ_pic_red_color[12],m_Equ_pic_green_color[12],m_Equ_pic_blue_color[12],1.0f },
		{ m_Equ_pic_red_color[13],m_Equ_pic_green_color[13],m_Equ_pic_blue_color[13],1.0f },
		{ m_Equ_pic_red_color[14],m_Equ_pic_green_color[14],m_Equ_pic_blue_color[14],1.0f },
	};

	//����|�b�h�K�v�f��&�l���t�H���g�p
	float Equ_message_font[EQU_MES_MAX_FONT_LINE][4] =
	{
		{ 0.0f,0.0f,1.0f,m_alpha },//1�s�ڂ͐F
		{ 0.0f,0.0f,0.0f,m_alpha },//2�s�ڈȍ~�͑S�č��F
		{ 0.0f,0.0f,0.0f,m_alpha },
	};
	
	//����|�b�h�K�v�f��&�l���E�C���h�E�p
	float Equ_message_window[4] = { 1.0f,1.0f,1.0f,m_alpha };

	//�ŏI�m�F[�͂�]�{�^���p
	float Yes[4] = { m_Yes_Button_color,0.0f,0.0f,1.0f };

	//�ŏI�m�F[������]�{�^���p
	float No[4] = { 0.0f,0.0f,m_No_Button_color,1.0f };

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
		src.m_right = 256.0f;
		src.m_bottom = 256.0f;

		dst.m_top = 460.0f;
		dst.m_left = 10.0f;
		dst.m_right = 390.0f;
		dst.m_bottom = 690.0f;
		Draw::Draw(3 + (g_Ins_Level - 1) * 3, &src, &dst, ins, 0.0f);

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
			Draw::Draw(21, &src, &dst, white, 0.0f);

			//���t�H���g�\��
			//���������x��
			Font::StrDraw(Ins, m_mou_x - 95.0f, m_mou_y - 45.0f, 30.0f, black);
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
		src.m_right = 256.0f;
		src.m_bottom = 256.0f;

		dst.m_top = 150.0f;
		dst.m_left = 100.0f;
		dst.m_right = 400.0f;
		dst.m_bottom = 350.0f;
		Draw::Draw(3 + (g_Ins_Level - 1) * 3, &src, &dst, white, 0.0f);

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
		src.m_right = 256.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 330.0f;
		dst.m_left = 520.0f;
		dst.m_right = 1130.0f;
		dst.m_bottom = 480.0f;
		Draw::Draw(25, &src, &dst, missile, 0.0f);

		//������|�b�h�{�^���\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 256.0f;
		src.m_bottom = 64.0f;

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

		Facility_message(g_Ins_Level);//�������̕K�v�f��&�T�C�Y���b�Z�[�W�`��֐��Ăяo��

		//�ȈՃ��b�Z�[�W(�G���[���b�Z�[�W�A���x��UP�\����)
		Font::StrDraw(m_message, m_mou_x - 110.0f, m_mou_y - 45.0f, 30.0f, message);


		//���ŏI�m�F�E�C���h�E�\���Ǘ��t���O��true�̎��A�`��B
		if (m_finalcheck_f == true)
		{
			//���ŏI�m�F�E�C���h�E�\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 64.0f;
			src.m_bottom = 64.0f;

			dst.m_top = 220.0f;
			dst.m_left = 320.0f;
			dst.m_right = 880.0f;
			dst.m_bottom = 480.0f;
			Draw::Draw(21, &src, &dst, white, 0.0f);

			//���t�H���g�\��
			//�ŏI�m�F���b�Z�[�W
			Font::StrDraw(L"�f��HP�Ƒf�ޏ����", 347.0f, 250.0f, 30.0f, black);
			Font::StrDraw(L"���x���A�b�v���܂����H", 527.0f, 300.0f, 30.0f, black);
			Font::StrDraw(L"�͂�", 410.0f, 410.0f, 50.0f, Yes);
			Font::StrDraw(L"������", 650.0f, 410.0f, 50.0f, No);
		}
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
			src.m_right = 64.0f;
			src.m_bottom = 64.0f;

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
					src.m_right = 150.0f;
					src.m_bottom = 150.0f;

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
			//���E�C���h�E�\�� 
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 64.0f;
			src.m_bottom = 64.0f;

			dst.m_top = m_mou_y - m_Equ_message_window_y_size;
			dst.m_left = m_mou_x - m_Equ_message_window_x_size;
			dst.m_right = m_mou_x + m_Equ_message_window_x_size;
			dst.m_bottom = m_mou_y + 0.0f;
			Draw::Draw(21, &src, &dst, Equ_message_window, 0.0f);

			//���t�H���g�\��
			//�f�ޖ����������t�H���g�\��
			for (int i = 0; i < EQU_MES_MAX_FONT_LINE; i++)
			{
				Font::StrDraw(m_Equ_message[i], m_mou_x - 135.0f, m_mou_y - 160.0f + i * 40.0f, 25.0f, Equ_message_font[i]);
			}

			//�f�ޖ��̃t�H���g�\��
			Font::StrDraw(m_message_Mat_name, m_mou_x - 135.0f, m_mou_y - 76.0f, 17.5f, Equ_message_font[2]);

			//�ŉ������b�Z�[�W�\��(�E�C���h�E��ԉ��ɂ���t�H���g)
			Font::StrDraw(m_message, m_mou_x - 210.0f, m_mou_y - 40.0f, 30.0f, message);



			//���ŏI�m�F�E�C���h�E�\���Ǘ��t���O��true�̎��A�`��B
			if (m_finalcheck_f == true)
			{
				//���ŏI�m�F�E�C���h�E�\��
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 64.0f;
				src.m_bottom = 64.0f;

				dst.m_top = 220.0f;
				dst.m_left = 320.0f;
				dst.m_right = 880.0f;
				dst.m_bottom = 480.0f;
				Draw::Draw(21, &src, &dst, white, 0.0f);

				//���t�H���g�\��
				//�ŏI�m�F���b�Z�[�W
				Font::StrDraw(L"�f�ޏ���ă��x���A�b�v���܂����H", 347.0f, 250.0f, 30.0f, black);
				Font::StrDraw(L"���������͎����܂���B", 347.0f, 300.0f, 30.0f, black);
				Font::StrDraw(L"�͂�", 410.0f, 410.0f, 50.0f, Yes);
				Font::StrDraw(L"������", 650.0f, 410.0f, 50.0f, No);
			}
		}
	}

	

	//�f�o�b�O�p���}�E�X�ʒu�\��
	//wchar_t str[256];
	//swprintf_s(str, L"x=%f,y=%f", m_mou_x, m_mou_y);
	//Font::StrDraw(str, 20.0f, 20.0f, 12.0f, white);
}


//---Missile_Lvup_check�֐�
//�����e
//�~�T�C�����L���X�g���x��UP�����𖞂����Ă��邩�`�F�b�N���A
//�������Ă���΃��x��UP������B
void CObjInstitute::Missile_Lvup_check()
{
	if (g_Mis_Recast_Level == MIS_MAX_LV - 1)
	{
		;//�ő僌�x���̎��͂��̃`�F�b�N�������΂�
	}
	else if (g_Ins_Level >= m_Mis_recast_next_Ins_Lv[g_Mis_Recast_Level] &&
		g_Research_num >= m_Mis_recast_next_Hum_num[g_Mis_Recast_Level])
	{
		g_Mis_Recast_Level++;//�����𖞂����Ă���̂Ń��x��UP


		//���~�T�C�����L���X�g�����x��UP���������ȈՃ��b�Z�[�W�ɂĒm�点��
		swprintf_s(m_message, L"�~�T�C�����L���X�g���x��UP�I");//�����z��ɕ����f�[�^������

		//���L���X�g���x��UP���b�Z�[�W�̃J���[�����F�ɂ���
		m_message_red_color = 1.0f;
		m_message_green_color = 1.0f;
		m_message_blue_color = 0.0f;

		m_alpha = 1.0f;		//���L���X�g���x��UP���b�Z�[�W��\�����邽�߁A���ߓx��1.0f�ɂ���

		//�~�T�C���̃��x�����A�b�v�����ۂɃO���[�o���ϐ��Ƀ��L���X�g�^�C����������
		switch (g_Mis_Recast_Level)
		{
		case 1:g_Recast_time = MIS_LV_2;break;//6�b
		case 2:g_Recast_time = MIS_LV_3;break;//5�b
		case 3:g_Recast_time = MIS_LV_4;break;//4�b
		case 4:g_Recast_time = MIS_LV_5;break;//3�b
		}
	}

}

//---Equip_Lvup_check�֐�
//����1�@int equip_id			:���ʔԍ�(�p���[����:0�@�f�B�t�F���X����:1�@�X�s�[�h����:2�@�o�����X����:3�@�|�b�h:4)
//����2�@int equip_Level		:����|�b�h���x��
//����3�@int equip_Lv_achieve	:����|�b�h���x���̍ő哞�B�x
//�߂�l int					:�`�F�b�N�ς̕���|�b�h���x��
//�����e
//���Ƀ��x��UP�ς݂̕���|�b�h�̌��݂̌����������`�F�b�N���A
//�����\�Ȍ��������ɒB���Ă���΁A���x��UP������B
int CObjInstitute::Equip_Lvup_check(int equip_id, int equip_Level, int equip_Lv_achieve)
{
	//������|�b�h���x��UP�`�F�b�N����
	if (equip_Level == equip_Lv_achieve)
	{
		;//���x�����ő哞�B�x�ɒB���Ă��鎞�͂��̃`�F�b�N�������΂�
	}
	else if (g_Research_num >= m_Equ_next_Hum_num[equip_id][equip_Level - 1])
	{
		equip_Level++;//�����\�Ȍ��������𖞂����Ă���̂Ń��x��UP


		//�����x��UP�O��̑�������|�b�h�J���[��K�؂Ȃ��̂ɕύX����
		//���x��UP��̑�������̃J���[�𔒐F�ɐݒ肷��
		m_Equ_pic_red_color[equip_Level - 1 + equip_id * 3] = 1.0f;
		m_Equ_pic_green_color[equip_Level - 1 + equip_id * 3] = 1.0f;
		m_Equ_pic_blue_color[equip_Level - 1 + equip_id * 3] = 1.0f;

		//���x��UP�O�̑�������̃J���[���D�F�ɐݒ肷��
		m_Equ_pic_red_color[equip_Level - 2 + equip_id * 3] = 0.5f;
		m_Equ_pic_green_color[equip_Level - 2 + equip_id * 3] = 0.5f;
		m_Equ_pic_blue_color[equip_Level - 2 + equip_id * 3] = 0.5f;


		//������|�b�h�����x��UP���������ȈՃ��b�Z�[�W�ɂĒm�点��
		if (equip_id == 0)
		{
			swprintf_s(m_message, L"�p���[���탌�x��UP�I");//�����z��ɕ����f�[�^������
		}
		else if (equip_id == 1)
		{
			swprintf_s(m_message, L"�f�B�t�F���X���탌�x��UP�I");//�����z��ɕ����f�[�^������
		}
		else if (equip_id == 2)
		{
			swprintf_s(m_message, L"�X�s�[�h���탌�x��UP�I");//�����z��ɕ����f�[�^������
		}
		else if (equip_id == 3)
		{
			swprintf_s(m_message, L"�o�����X���탌�x��UP�I");//�����z��ɕ����f�[�^������
		}
		else  //(equip_id == 4)
		{
			swprintf_s(m_message, L"�|�b�h���x��UP�I");//�����z��ɕ����f�[�^������
		}

		//����|�b�h���x��UP���b�Z�[�W�̃J���[�����F�ɂ���
		m_message_red_color = 1.0f;
		m_message_green_color = 1.0f;
		m_message_blue_color = 0.0f;

		m_alpha = 1.0f;		//����|�b�h���x��UP���b�Z�[�W��\�����邽�߁A���ߓx��1.0f�ɂ���
	}

	return equip_Level;
}

//---Equip_Lvdown_check�֐�
//����1�@int equip_id			:���ʔԍ�(�p���[����:0�@�f�B�t�F���X����:1�@�X�s�[�h����:2�@�o�����X����:3�@�|�b�h:4)
//����2�@int equip_Level		:����|�b�h���x��
//�߂�l int					:�`�F�b�N�ς̕���|�b�h���x��
//�����e
//���Ƀ��x��UP�ς݂̕���|�b�h�̌��݂̌����������`�F�b�N���A
//�����s�Ȍ��������ɒB���Ă���΁A���x��DOWN������B
int CObjInstitute::Equip_Lvdown_check(int equip_id, int equip_Level)
{
	//������|�b�h���x��DOWN�`�F�b�N����
	if (equip_Level == 1)
	{
		;//�������x���̎��͂��̃`�F�b�N�������΂�
	}
	else if (g_Research_num < m_Equ_next_Hum_num[equip_id][equip_Level - 2])
	{
		equip_Level--;//�����s�Ȍ��������𖞂����Ă���̂Ń��x��DOWN


		//�����x��DOWN�O��̑�������|�b�h�J���[��K�؂Ȃ��̂ɕύX����
		//���x��DOWN��̑�������̃J���[�𔒐F�ɐݒ肷��
		m_Equ_pic_red_color[equip_Level - 1 + equip_id * 3] = 1.0f;
		m_Equ_pic_green_color[equip_Level - 1 + equip_id * 3] = 1.0f;
		m_Equ_pic_blue_color[equip_Level - 1 + equip_id * 3] = 1.0f;

		//���x��DOWN�O�̑�������̃J���[���D�F�ɐݒ肷��
		m_Equ_pic_red_color[equip_Level + equip_id * 3] = 0.5f;
		m_Equ_pic_green_color[equip_Level + equip_id * 3] = 0.5f;
		m_Equ_pic_blue_color[equip_Level + equip_id * 3] = 0.5f;


		//������|�b�h�����x��DOWN���������ȈՃ��b�Z�[�W�ɂĒm�点��
		if (equip_id == 0)
		{
			swprintf_s(m_message, L"�p���[���탌�x��DOWN�c");//�����z��ɕ����f�[�^������
		}
		else if (equip_id == 1)
		{
			swprintf_s(m_message, L"�f�B�t�F���X���탌�x��DOWN�c");//�����z��ɕ����f�[�^������
		}
		else if (equip_id == 2)
		{
			swprintf_s(m_message, L"�X�s�[�h���탌�x��DOWN�c");//�����z��ɕ����f�[�^������
		}
		else if (equip_id == 3)
		{
			swprintf_s(m_message, L"�o�����X���탌�x��DOWN�c");//�����z��ɕ����f�[�^������
		}
		else  //(equip_id == 4)
		{
			swprintf_s(m_message, L"�|�b�h���x��DOWN�c");//�����z��ɕ����f�[�^������
		}

		//����|�b�h���x��DOWN���b�Z�[�W�̃J���[�𐅐F�ɂ���
		m_message_red_color = 0.0f;
		m_message_green_color = 1.0f;
		m_message_blue_color = 1.0f;

		m_alpha = 1.0f;		//����|�b�h���x��DOWN���b�Z�[�W��\�����邽�߁A���ߓx��1.0f�ɂ���
	}

	return equip_Level;
}

//---Equip_Lvup_possible_check�֐�
//�����e
//���ꂼ��̕���A�|�b�h�����x���A�b�v�\�ȏ��
//(�Z�����Ƒf�ސ����ꂼ�ꂪ�K�v���𖞂����Ă���A
//���݂̕���|�b�h���x���ƁA���̃��x���̍ő哞�B�x�����l)
//�ł��邩�ǂ������`�F�b�N���A
//���x���A�b�v�\�ł���΂��̕���|�b�h�̉摜�����F�ɂ��A
//���x���A�b�v�s�ł���΂��̕���|�b�h�̉摜�����F�ɂ���B
void CObjInstitute::Equip_Lvup_possible_check()
{
	for (int i = 0; i < 5; i++)
	{
		//���e���탌�x���A���̃��x���̍ő哞�B�x���Ǘ�����ϐ������ꂼ��錾
		int Tmp_equip_Level;
		int Tmp_equip_Lv_achieve;

		//���K�؂ȃ^�C�~���O�Ő���錾�����ϐ��Ɋe���탌�x���ƁA���̃��x���̍ő哞�B�x����
		if (i == 0)
		{
			Tmp_equip_Level = g_Pow_equip_Level;
			Tmp_equip_Lv_achieve = g_Pow_equip_Lv_achieve;
		}
		else if (i == 1)
		{
			Tmp_equip_Level = g_Def_equip_Level;
			Tmp_equip_Lv_achieve = g_Def_equip_Lv_achieve;
		}
		else if (i == 2)
		{
			Tmp_equip_Level = g_Spe_equip_Level;
			Tmp_equip_Lv_achieve = g_Spe_equip_Lv_achieve;
		}
		else if (i == 3)
		{
			Tmp_equip_Level = g_Bal_equip_Level;
			Tmp_equip_Lv_achieve = g_Bal_equip_Lv_achieve;
		}
		else  //(i == 4)
		{
			Tmp_equip_Level = g_Pod_equip_Level;
			Tmp_equip_Lv_achieve = g_Pod_equip_Lv_achieve;
		}

		//������|�b�h���x��UP�\�`�F�b�N����
		if (Tmp_equip_Lv_achieve == EQU_MAX_LV)
		{
			;//�ő僌�x���̎��͂��̕���|�b�h���x��UP�\�`�F�b�N�������΂�
		}
		else if (Tmp_equip_Level == Tmp_equip_Lv_achieve &&
			g_Research_num >= m_Equ_next_Hum_num[i][Tmp_equip_Lv_achieve - 1] &&
			*m_Equ_next_Mat_type[i][Tmp_equip_Lv_achieve - 1] >= m_Equ_next_Mat_num[i][Tmp_equip_Lv_achieve - 1])
		{
			//���x���A�b�v�\�ȕ���|�b�h�摜�����F�ɂ���B
			m_Equ_pic_red_color[Tmp_equip_Lv_achieve + i * 3] = 1.0f;
			m_Equ_pic_green_color[Tmp_equip_Lv_achieve + i * 3] = 1.0f;
			m_Equ_pic_blue_color[Tmp_equip_Lv_achieve + i * 3] = 0.0f;
		}
		else
		{
			//���x���A�b�v�s�ȕ���|�b�h�摜�͍��F�ɂ���B
			m_Equ_pic_red_color[Tmp_equip_Lv_achieve + i * 3] = 0.1f;
			m_Equ_pic_green_color[Tmp_equip_Lv_achieve + i * 3] = 0.1f;
			m_Equ_pic_blue_color[Tmp_equip_Lv_achieve + i * 3] = 0.1f;
		}
	}
}

//---Equip_message�֐�
//����1�@int equip_id	:����|�b�h���ʔԍ�(�p���[����:0�@�f�B�t�F���X����:1�@�X�s�[�h����:2�@�o�����X����:3�@�|�b�h:4)
//����2�@int Lv_id		:���x�����ʔԍ�(Lv.1 = 0  Lv.2 = 1  Lv.3 = 2)
//�����e
//�}�E�X�őI�����Ă��镐��|�b�h�����ł��邩�����ʂ��A
//����ɑΉ����镐��|�b�h�K�v�f��&�l�����b�Z�[�W��\������B
void CObjInstitute::Equip_message(int equip_id, int Lv_id)
{
	//������|�b�h�摜�����F(���x���A�b�v�\)�̎��̏���
	if (m_Equ_pic_red_color[Lv_id + equip_id * 3] == 1.0f &&
		m_Equ_pic_green_color[Lv_id + equip_id * 3] == 1.0f &&
		m_Equ_pic_blue_color[Lv_id + equip_id * 3] == 0.0f)
	{
		//����|�b�h�K�v�f��&�l�����b�Z�[�W�ݒ�
		swprintf_s(m_Equ_message[0], L"LvUP����  ����/  �K�v");																				 //�����z��ɕ����f�[�^������
		swprintf_s(m_Equ_message[1], L"������  %6d/%6d", g_Research_num, m_Equ_next_Hum_num[equip_id][Lv_id - 1]);							 //�����z��ɕ����f�[�^������
		swprintf_s(m_Equ_message[2], L"        %6d/%6d", *m_Equ_next_Mat_type[equip_id][Lv_id - 1], m_Equ_next_Mat_num[equip_id][Lv_id - 1]);//�����z��ɕ����f�[�^������
		swprintf_s(m_message_Mat_name, L"%s", m_Equ_next_Mat_name[equip_id][Lv_id - 1]);												 //�����z��ɕ����f�[�^������

		//�ŉ������b�Z�[�W�ݒ�
		swprintf_s(m_message, L"�@�@�@�N���b�N��LvUP��");//�����z��ɕ����f�[�^������

		//�ŉ������b�Z�[�W�̃J���[��F�ɂ���
		m_message_red_color = 0.0f;
		m_message_green_color = 0.0f;
		m_message_blue_color = 1.0f;

		//����|�b�h�K�v�f��&�l���E�C���h�E�̃T�C�Y��ݒ�
		m_Equ_message_window_x_size = 150.0f;
		m_Equ_message_window_y_size = 170.0f;

		//���N���b�N���ꂽ��t���O�𗧂āA�ŏI�m�F�E�C���h�E���J��
		if (m_mou_l == true)
		{
			//���N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
			if (m_key_lf == true)
			{
				m_key_lf = false;

				//���ȉ��̕ϐ��A�|�C���^�Ƀ}�E�X�I�𒆂̕���|�b�h�^�C�v(�p���[�A�X�s�[�h��)�A
				//���݂̃��x���A���x���ő哞�B�x�̃A�h���X�����ꂼ����
				finalcheck_Lvup_type = equip_id;
				
				if (equip_id == 0)
				{
					finalcheck_Lvup_Level = &g_Pow_equip_Level;
					finalcheck_Lvup_achieve = &g_Pow_equip_Lv_achieve;
				}
				else if (equip_id == 1)
				{
					finalcheck_Lvup_Level = &g_Def_equip_Level;
					finalcheck_Lvup_achieve = &g_Def_equip_Lv_achieve;
				}
				else if (equip_id == 2)
				{
					finalcheck_Lvup_Level = &g_Spe_equip_Level;
					finalcheck_Lvup_achieve = &g_Spe_equip_Lv_achieve;
				}
				else if (equip_id == 3)
				{
					finalcheck_Lvup_Level = &g_Bal_equip_Level;
					finalcheck_Lvup_achieve = &g_Bal_equip_Lv_achieve;
				}
				else  //(equip_id == 4)
				{
					finalcheck_Lvup_Level = &g_Pod_equip_Level;
					finalcheck_Lvup_achieve = &g_Pod_equip_Lv_achieve;
				}

				m_alpha = 0.0f;//����|�b�h�K�v�f��&�l�����b�Z�[�W���\���ɂ���

				m_finalcheck_f = true;//�ŏI�m�F�E�C���h�E��\������

				 //�I����
				Audio::Start(1);
				
				return;
			}
		}
		else
		{
			m_key_lf = true;
		}
	}
	//������|�b�h�摜�����F(�����s��)�̏���
	else if (m_Equ_pic_red_color[Lv_id + equip_id * 3] == 0.1f &&
		m_Equ_pic_green_color[Lv_id + equip_id * 3] == 0.1f &&
		m_Equ_pic_blue_color[Lv_id + equip_id * 3] == 0.1f)
	{
		//����|�b�h�K�v�f��&�l�����b�Z�[�W�ݒ�
		swprintf_s(m_Equ_message[0], L"LvUP����  ����/  �K�v");																				 //�����z��ɕ����f�[�^������
		swprintf_s(m_Equ_message[1], L"������  %6d/%6d", g_Research_num, m_Equ_next_Hum_num[equip_id][Lv_id - 1]);							 //�����z��ɕ����f�[�^������
		swprintf_s(m_Equ_message[2], L"        %6d/%6d", *m_Equ_next_Mat_type[equip_id][Lv_id - 1], m_Equ_next_Mat_num[equip_id][Lv_id - 1]);//�����z��ɕ����f�[�^������
		swprintf_s(m_message_Mat_name, L"%s", m_Equ_next_Mat_name[equip_id][Lv_id - 1]);												 //�����z��ɕ����f�[�^������

		//�ŉ������b�Z�[�W�ݒ�
		swprintf_s(m_message, L"�@�@�@�@�@LvUP�s��");//�����z��ɕ����f�[�^������

		//�ŉ������b�Z�[�W�̃J���[��ԐF�ɂ���
		m_message_red_color = 1.0f;
		m_message_green_color = 0.0f;
		m_message_blue_color = 0.0f;

		//����|�b�h�K�v�f��&�l���E�C���h�E�̃T�C�Y��ݒ�
		m_Equ_message_window_x_size = 150.0f;
		m_Equ_message_window_y_size = 170.0f;
	}
	//������|�b�h�摜�����F(������)�̏���
	else if (m_Equ_pic_red_color[Lv_id + equip_id * 3] == 1.0f &&
		m_Equ_pic_green_color[Lv_id + equip_id * 3] == 1.0f &&
		m_Equ_pic_blue_color[Lv_id + equip_id * 3] == 1.0f)
	{
		//����|�b�h�K�v�f��&�l�����b�Z�[�W�ݒ�
		swprintf_s(m_Equ_message[0], L"");//�����f�[�^���N���A����
		swprintf_s(m_Equ_message[1], L"");//�����f�[�^���N���A����
		swprintf_s(m_Equ_message[2], L"");//�����f�[�^���N���A����
		swprintf_s(m_message_Mat_name, L"");//�����f�[�^���N���A����

		//�ŉ������b�Z�[�W�ݒ�
		swprintf_s(m_message, L"�@�@�@�@   ������");//�����z��ɕ����f�[�^������

		//�ŉ������b�Z�[�W�̃J���[�����F�ɂ���
		m_message_red_color = 0.0f;
		m_message_green_color = 0.0f;
		m_message_blue_color = 0.0f;

		//����|�b�h�K�v�f��&�l���E�C���h�E�̃T�C�Y��ݒ�
		m_Equ_message_window_x_size = 55.0f;
		m_Equ_message_window_y_size = 50.0f;
	}
	//������|�b�h�摜���D�F(���x��UP��[������])�̏���
	else if (m_Equ_pic_red_color[Lv_id + equip_id * 3] == 0.5f &&
		m_Equ_pic_green_color[Lv_id + equip_id * 3] == 0.5f &&
		m_Equ_pic_blue_color[Lv_id + equip_id * 3] == 0.5f)
	{
		//�����݂̊e���탌�x�����Ǘ�����ϐ���錾
		int Tmp_equip_Level;

		//������錾�����ϐ��Ƀ}�E�X�I�𒆂̕���|�b�h�^�C�v(�p���[�A�X�s�[�h��)�̌��݂̃��x������
		if (equip_id == 0)
		{
			Tmp_equip_Level = g_Pow_equip_Level;
		}
		else if (equip_id == 1)
		{
			Tmp_equip_Level = g_Def_equip_Level;
		}
		else if (equip_id == 2)
		{
			Tmp_equip_Level = g_Spe_equip_Level;
		}
		else if (equip_id == 3)
		{
			Tmp_equip_Level = g_Bal_equip_Level;
		}
		else  //(equip_id == 4)
		{
			Tmp_equip_Level = g_Pod_equip_Level;
		}

		//����|�b�h�K�v�f��&�l�����b�Z�[�W�ݒ�
		swprintf_s(m_Equ_message[0], L"");//�����f�[�^���N���A����
		swprintf_s(m_Equ_message[1], L"");//�����f�[�^���N���A����
		swprintf_s(m_Equ_message[2], L"");//�����f�[�^���N���A����
		swprintf_s(m_message_Mat_name, L"");//�����f�[�^���N���A����

		//�ŉ������b�Z�[�W�ݒ�
		//�}�E�X�I�𒆂̕���|�b�h���x�������̕���̌��݃��x�����Ⴉ�����ꍇ
		if (Lv_id + 1 < Tmp_equip_Level) 
		{
			swprintf_s(m_message, L"������%6d�l �����ő�����", m_Equ_next_Hum_num[equip_id][Lv_id]);//�����z��ɕ����f�[�^������
		}
		//�}�E�X�I�𒆂̕���|�b�h���x�������̕���̌��݃��x����荂�������ꍇ
		else
		{
			swprintf_s(m_message, L"������%6d�l �ȏ�ő�����", m_Equ_next_Hum_num[equip_id][Lv_id - 1]);//�����z��ɕ����f�[�^������
		}

		//�ŉ������b�Z�[�W�̃J���[�����F�ɂ���
		m_message_red_color = 0.0f;
		m_message_green_color = 0.0f;
		m_message_blue_color = 0.0f;

		//����|�b�h�K�v�f��&�l���E�C���h�E�̃T�C�Y��ݒ�
		m_Equ_message_window_x_size = 240.0f;
		m_Equ_message_window_y_size = 50.0f;
	}


	m_alpha = 1.0f;//����|�b�h�K�v�f��&�l�����b�Z�[�W��\��
}