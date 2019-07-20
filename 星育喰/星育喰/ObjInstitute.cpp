//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "UtilityModule.h"

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
#define MIS_LV_5 (1.0f)//1.0�����ɂ͂��Ȃ��ł�������(�ǋL�F�o�O�C�������̂ŁA1.0����OK�ł���B)

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

	m_equip_id = 0;
	m_Lv_id = 0;
	m_equipable_count = 0;

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
	m_key_rf = false;
	m_next_time = 0;
	m_con_alo_f = false;
	m_message_clip_right = 0.0f;
	m_message_clip_bottom = 0.0f;
	m_message_draw_left = 0.0f;
	m_message_draw_right = 0.0f;
	m_message_red_color = INI_COLOR;
	m_message_green_color = INI_COLOR;
	m_message_blue_color = INI_COLOR;
	m_alpha = INI_ALPHA;
	m_Equ_alpha = INI_ALPHA;

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
	m_Equ_next_Hum_num[4][0] = 400;  //���x����1�̎��̕K�v��������
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
	swprintf_s(m_Equ_next_Mat_name[3][0], L"�A���~");		//���x����1�̎��̕K�v�f�ޖ�
	swprintf_s(m_Equ_next_Mat_name[3][1], L"�K�X");	//���x����2�̎��̕K�v�f�ޖ�
	//���|�b�h����
	swprintf_s(m_Equ_next_Mat_name[4][0], L"�A���~");	//���x����1�̎��̕K�v�f�ޖ�
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
	swprintf_s(m_Facility_next_Mat_name[1], L"�A���~");//���x����2�̎��̕K�v�f�ޖ�

	//���������̎���LVUP�ɕK�v�ȑf�ގ�ސݒ�Ɠ����ɂ��̑f�ނ̏�������������
	//���ȉ��̂悤�ɏ����f�ސ����Ǘ����Ă���O���[�o���ϐ��̃A�h���X�������鎖�őf�ނ̎�ސݒ�Ə������̑�������Ă���B
	//���������݂͑f�ގ�ނ��m�肵�Ă��Ȃ����߁A����TEST�p�̕������Ă���B��œK�؂Ȃ��̂ɕύX���ׂ��B
	m_Facility_next_Mat_type[0] = &g_Iron_num;	//���x����1�̎��̕K�v�f�ގ��
	m_Facility_next_Mat_type[1] = &g_Aluminum_num;	//���x����2�̎��̕K�v�f�ގ��

	//���������̎���LVUP�ɕK�v�ȑf�ސ��ݒ�
	m_Facility_next_Mat_num[0] = 10;	//���x����1�̎��̕K�v�f�ސ�
	m_Facility_next_Mat_num[1] = 20;	//���x����2�̎��̕K�v�f�ސ�






	//�����蔻��pHitBox���쐬(Objhuman�p)
	//Hits::SetHitBox(this, 60, 505, 265, 132, ELEMENT_ENEMY, OBJ_INSTITUTE, 1);
}

//�A�N�V����
void CObjInstitute::Action()
{
	//�z���C�g�A�E�g���o���͑���s�\�ɂ��鏈��
	//���������~�T�C�����L���X�g���x��UP�`�F�b�N�����͍s���B
	//���}�E�X�ʒu�擾�̓~�T�C�����L���X�g�^�C�����x��UP�`�F�b�N�ɕK�v�Ȃ̂œ���Ă�B
	if (white_out_f == true)
	{
		//�}�E�X�̈ʒu���擾
		m_mou_x = (float)Input::GetPosX();
		m_mou_y = (float)Input::GetPosY();

		//���~�T�C�����L���X�g���x��UP�`�F�b�N
		//���x��UP�����𖞂����Ă��邩�`�F�b�N���A
		//�������Ă���΃��x��UP������B
		Missile_Lvup_check();//�~�T�C�����L���X�g���x��UP�`�F�b�N�֐����Ăяo��

		return;
	}

	//�}�E�X�̈ʒu���擾
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//�}�E�X�̃{�^���̏��
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	//���L�[�t���O
	//���E�N���b�NPush��ԁ��E�N���b�N��Push��ԂɂȂ�܂ŁA
	//�ēx�E�N���b�N���鎖�͏o���Ȃ������B
	if (m_mou_r == false)	//�E�N���b�NOFF
	{
		m_key_rf = true;
	}

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


						//���������x��UP�ɂ��A�v���C���[�f�������x��UP���邩�`�F�b�N����
						//��if���������ɓ��遁���x��UP����
						if (player_level != (int)((g_Bar_Level + g_Ins_Level + 1) / 2))
						{
							//�v���C���[�f�������x��UP����ꍇ�A
							//�琬��ʔw�i�̕ύX���s��Ȃ��Ƃ����Ȃ��ׁA
							//�z���C�g�A�E�g���������݁A�w�i�ύX���s���B
							//���z���C�g�A�E�g�����̓I�u�W�F�N�g�D�揇�ʓI��ObjCloud_Effect�ɂčs���B

							//�v���C���[�f�����x�����X�V����(���̃��x��UP�`�F�b�N����̈�)
							player_level = (int)((g_Bar_Level + g_Ins_Level + 1) / 2);

							//�z���C�g�A�E�g���o�t���O��ON
							white_out_f = true;
						}
						//�v���C���[�f�������x��UP���Ȃ��ꍇ�A���ʂɌ������̃��x��UP�������s��
						else
						{
							//�������̃��x��UP����
							g_Ins_Level++;

							//���~�T�C�����L���X�g���x��UP�`�F�b�N
							//���x��UP�����𖞂����Ă��邩�`�F�b�N���A
							//�������Ă���΃��x��UP������B
							Missile_Lvup_check();//�~�T�C�����L���X�g���x��UP�`�F�b�N�֐����Ăяo��

							//���x���A�b�v��
							Audio::Start(3);
						}

						m_Yes_Button_color = 0.0f;

						//�ŏI�m�F�E�C���h�E���\���ɂ���
						m_finalcheck_f = false;
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
		if (70 < m_mou_x && m_mou_x < 120 && 60 < m_mou_y && m_mou_y < 110 || m_mou_r == true)
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

					//ObjHelp�𑀍�\�ɂ��� & ���ߓx1.0f�ɂ��ĕ\������
					CObjHelp* help = (CObjHelp*)Objs::GetObj(OBJ_HELP);
					help->SetOperatable(true);
					help->SetAlpha(1.0f);

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
						//���N���b�N���ꂽ��ȈՃ��b�Z�[�W�摜�Ń��x��UP�s��`����
						//LvUP�o���܂��񕶎��摜��ǂݍ���127�Ԃɓo�^
						Draw::LoadImage(L"LvUP�o���܂���.png", 127, TEX_SIZE_512);//�ȈՃ��b�Z�[�W�摜�ǂݍ��ݔԍ��ɉ摜�f�[�^������

						//�؂���ʒu��ݒ肷��
						m_message_clip_right = 937.0f;
						m_message_clip_bottom = 112.0f;

						//�`��ʒu��ݒ肷��
						m_message_draw_left = -100.0f;
						m_message_draw_right = 100.0f;

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
						//���N���b�N���ꂽ��ȈՃ��b�Z�[�W�摜�Ń��x��UP�s��`����
						//LvUP�o���܂��񕶎��摜��ǂݍ���127�Ԃɓo�^
						Draw::LoadImage(L"LvUP�o���܂���.png", 127, TEX_SIZE_512);//�ȈՃ��b�Z�[�W�摜�ǂݍ��ݔԍ��ɉ摜�f�[�^������

						//�؂���ʒu��ݒ肷��
						m_message_clip_right = 937.0f;
						m_message_clip_bottom = 112.0f;

						//�`��ʒu��ݒ肷��
						m_message_draw_left = -100.0f;
						m_message_draw_right = 100.0f;

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


		//���Z���U�蕪��

		//�Z���U�蕪���A�C�R���J���[���x�𖈉񏉊�������
		m_Human_up_color = INI_COLOR;
		m_Human_down_color = INI_COLOR;

		//�������Z���U�蕪��UP
		if (695 < m_mou_x && m_mou_x < 793 && 118 < m_mou_y && m_mou_y < 218)
		{
			m_Human_up_color = 1.0f;

			//���N���b�N���ꂽ��U�蕪���֐����Ăяo���A�Z���U�蕪���̏������s��
			//�����N���b�N������������ƁA�����ŘA���U�蕪���\�B
			if (m_mou_l == true)
			{
				if (m_next_time <= 0)
				{
					//����͂��̏����ɓ���[���N���b�N�������̂���߂��m_con_alo_f��"false"�ɖ߂菉�񔻒�ƂȂ�]
					if (m_con_alo_f == false)
					{
						m_next_time = CON_PRE_TIME;//�A���U�蕪���O�̎��Z���U�蕪�����Ԃ�����(�ŏ��̂ݐU�蕪�����ԊԊu������)
					}
					//���ڈȍ~�͂��̏����ɓ���
					else
					{
						m_next_time = CON_MID_TIME;//�A���U�蕪�����̎��Z���U�蕪�����Ԃ�����(�U�蕪�����ԊԊu���ŏ����Z���Ȃ�)
					}

					m_Human_up_color = 0.5f;

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
				else
				{
					m_con_alo_f = true;//�A���U�蕪���t���OON
					m_next_time--;//���̏Z���U�蕪���܂ł̎��Ԍ�������
				}
			}
			else
			{
				m_con_alo_f = false;//�A���U�蕪���t���OOFF
				m_next_time = 0;//���̏Z���U�蕪���܂ł̎��Ԃ�������
			}
		}

		//�������Z���U�蕪��DOWN
		else if (802 < m_mou_x && m_mou_x < 902 && 118 < m_mou_y && m_mou_y < 218)
		{
			m_Human_down_color = 1.0f;

			//���N���b�N���ꂽ��U�蕪���֐����Ăяo���A�Z���U�蕪���̏������s��
			//�����N���b�N������������ƁA�����ŘA���U�蕪���\�B
			if (m_mou_l == true)
			{
				if (m_next_time <= 0)
				{
					//����͂��̏����ɓ���[���N���b�N�������̂���߂��m_con_alo_f��"false"�ɖ߂菉�񔻒�ƂȂ�]
					if (m_con_alo_f == false)
					{
						m_next_time = CON_PRE_TIME;//�A���U�蕪���O�̎��Z���U�蕪�����Ԃ�����(�ŏ��̂ݐU�蕪�����ԊԊu������)
					}
					//���ڈȍ~�͂��̏����ɓ���
					else
					{
						m_next_time = CON_MID_TIME;//�A���U�蕪�����̎��Z���U�蕪�����Ԃ�����(�U�蕪�����ԊԊu���ŏ����Z���Ȃ�)
					}

					m_Human_down_color = 0.5f;

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

						switch (g_Mis_Recast_Level)
						{
						case 0:g_Recast_time = MIS_LV_1; break;
						case 1:g_Recast_time = MIS_LV_2; break;//6�b
						case 2:g_Recast_time = MIS_LV_3; break;//5�b
						case 3:g_Recast_time = MIS_LV_4; break;//4�b
						case 4:g_Recast_time = MIS_LV_5; break;//3�b
						}

						//���~�T�C�����L���X�g�����x��DOWN���������ȈՃ��b�Z�[�W�摜�ɂĒm�点��
						
						//�~�T�C�����L���X�g���x��DOWN�c�����摜��ǂݍ���127�Ԃɓo�^
						Draw::LoadImage(L"�~�T�C�����L���X�g���x��DOWN�c.png", 127, TEX_SIZE_512);//�ȈՃ��b�Z�[�W�摜�ǂݍ��ݔԍ��ɉ摜�f�[�^������

						//�؂���ʒu��ݒ肷��
						m_message_clip_right = 1919.0f;
						m_message_clip_bottom = 112.0f;

						//�`��ʒu��ݒ肷��
						m_message_draw_left = -200.0f;
						m_message_draw_right = 200.0f;

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
				else
				{
					m_con_alo_f = true;//�A���U�蕪���t���OON
					m_next_time--;//���̏Z���U�蕪���܂ł̎��Ԍ�������
				}
			}
			else
			{
				m_con_alo_f = false;//�A���U�蕪���t���OOFF
				m_next_time = 0;//���̏Z���U�蕪���܂ł̎��Ԃ�������
			}
		}

		//��L�͈̔͊O�Ƀ}�E�X�J�[�\��������ꍇ�̏���
		else
		{
			//�͈͊O�Ƀ}�E�X�J�[�\���������Ă����N���b�N�𗣂��Ȃ���΁A
			//�A���U�蕪����Ԃ��������Ȃ��悤�ɐݒ肵�Ă���B
			if (m_mou_l == false)
			{
				m_con_alo_f = false;//�A���U�蕪���t���OOFF
				m_next_time = 0;//���̏Z���U�蕪���܂ł̎��Ԃ�������
			}
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
						Audio::Start(3);
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
		if (80 < m_mou_x && m_mou_x < 130 && 80 < m_mou_y && m_mou_y < 130 || m_mou_r == true)
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
				m_Equ_alpha = 0.0f;//����|�b�h�K�v�f��&�l���t�H���g���\��
				m_alpha = 0.0f;//�ŉ������b�Z�[�W���\��
			}
		}

		return;
	}
	//�z�[����ʂɖ߂�{�^���������ꂽ��A
	//���{�݂̃E�C���h�E���J���Ă��鎞�͑�����󂯕t���Ȃ��悤�ɂ���B
	else if (window_start_manage != Default || g_help_f == true)
	{
		m_introduce_f = false;	//�{�ݏЉ�E�C���h�E���\���ɂ���(�E�N���b�N�Ńz�[����ʂɖ߂�ہA�E�C���h�E���c��Ȃ��悤�ɂ��邽��)
		return;
	}

	//�������I��͈�
	if (
		((g_Ins_Level==1)&&120 < m_mou_x && m_mou_x <= 220 && 340 < m_mou_y && m_mou_y < 550)||	//�������̃��x��1�̎��̑I��͈�
		((g_Ins_Level == 2) && 1 < m_mou_x && m_mou_x <= 220 && 340 < m_mou_y && m_mou_y < 550 && !(m_mou_y>320&& m_mou_y<450&& m_mou_x>1&& m_mou_x<117))||//�������̃��x��2�̎��̑I��͈�
		((g_Ins_Level == 3) && ((1 < m_mou_x && m_mou_x <= 220 && 340 < m_mou_y && m_mou_y < 550) || (220 <= m_mou_x && m_mou_x < 338 && 476 < m_mou_y && m_mou_y < 575) || (220 <= m_mou_x && m_mou_x < 293 && 428 < m_mou_y && m_mou_y < 482)) && !(m_mou_y>320 && m_mou_y<450 && m_mou_x>1 && m_mou_x<117) )//�������̃��x��3�̎��̑I��͈�
	)
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

				//ObjHelp�𑀍�s�\�ɂ��� & ���ߓx0.0f�ɂ��Ĕ�\���ɂ���
				CObjHelp* help = (CObjHelp*)Objs::GetObj(OBJ_HELP);
				help->SetOperatable(false);
				help->SetAlpha(0.0f);

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

	//�D�F
	float gray[4] = { 0.8f,0.8f,0.9f,1.0f };

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

	//����|�b�h�K�v�f��&�l���t�H���g�摜�p
	float Equ_message_font[EQU_MES_MAX_FONT_LINE][4] =
	{
		{ 0.0f,0.0f,1.0f,m_Equ_alpha },//1�s�ڂ͐F
		{ 0.0f,0.0f,0.0f,m_Equ_alpha },//2�s�ڈȍ~�͑S�č��F
		{ 0.0f,0.0f,0.0f,m_Equ_alpha },
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
	//�~�T�C���{�^�����������Ƃ��ɏo�鐔�l�̏�����
	m_Mis_recast = g_Recast_time * 10;										//g_Recast_time��int�^�ɂ��ĕۑ�����
	m_Mis_recast_next_f = m_Mis_recast_time[g_Mis_Recast_Level + 1] * 10;	//float�^�̕ϐ���10�{����int�^�ɓ���邽�߂ɂ����ň�x�ۑ�����
	m_Mis_recast_next = (int)m_Mis_recast_next_f;							//�����ł悤�₭int�ɑ��
	

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu

	//�{�݃E�C���h�E(���ɁA�������A�q��)���J���ĂȂ����ɕ\������O���t�B�b�N
	if (window_start_manage == Default || window_start_manage == BackButton)
	{
		//���������\�� 
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 400.0f;
		src.m_bottom = 400.0f;

		dst.m_top = 280.0f;
		dst.m_left = 0.0f;
		dst.m_right = 350.0f;
		dst.m_bottom = 680.0f;
		Draw::Draw(3 + (g_Ins_Level - 1) * 3, &src, &dst, ins, 0.0f);

		//�{�ݏЉ�E�C���h�E�\���Ǘ��t���O��true�̎��A�`��B
		if (m_introduce_f == true)
		{
			//���{�ݏЉ�E�C���h�E�\������
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 790.0f;
			src.m_bottom = 800.0f;

			dst.m_top = m_mou_y - 50.0f;
			dst.m_left = m_mou_x - 120.0f;
			dst.m_right = m_mou_x - 40.0f;
			dst.m_bottom = m_mou_y - 30.0f;
			Draw::Draw(21, &src, &dst, white, 0.0f);

			//���{�ݏЉ�E�C���h�E�\������
			src.m_top = 10.0f;
			src.m_left = 800.0f;
			src.m_right = 1595.0f;
			src.m_bottom = 800.0f;

			dst.m_top = m_mou_y - 30.0f;
			dst.m_left = m_mou_x - 120.0f;
			dst.m_right = m_mou_x - 40.0f;
			dst.m_bottom = m_mou_y - 10.0f;
			Draw::Draw(21, &src, &dst, white, 0.0f);

			//���{�ݏЉ�E�C���h�E�\��������
			src.m_top = 0.0f;
			src.m_left = 1600.0f;
			src.m_right = 2400.0f;
			src.m_bottom = 790.0f;

			dst.m_top = m_mou_y - 50.0f;
			dst.m_left = m_mou_x - 40.0f;
			dst.m_right = m_mou_x + 40.0f;
			dst.m_bottom = m_mou_y - 30.0f;
			Draw::Draw(21, &src, &dst, white, 0.0f);

			//���{�ݏЉ�E�C���h�E�\��������
			src.m_top = 10.0f;
			src.m_left = 2400.0f;
			src.m_right = 3200.0f;
			src.m_bottom = 800.0f;

			dst.m_top = m_mou_y - 30.0f;
			dst.m_left = m_mou_x - 40.0f;
			dst.m_right = m_mou_x + 40.0f;
			dst.m_bottom = m_mou_y - 10.0f;
			Draw::Draw(21, &src, &dst, white, 0.0f);

			//���{�ݏЉ�E�C���h�E�\���E��
			src.m_top = 0.0f;
			src.m_left = 4000.0f;
			src.m_right = 4800.0f;
			src.m_bottom = 800.0f;

			dst.m_top = m_mou_y - 50.0f;
			dst.m_left = m_mou_x + 40.0f;
			dst.m_right = m_mou_x + 120.0f;
			dst.m_bottom = m_mou_y - 30.0f;
			Draw::Draw(21, &src, &dst, white, 0.0f);

			//���{�ݏЉ�E�C���h�E�\��������
			src.m_top = 0.0f;
			src.m_left = 4805.0f;
			src.m_right = 5600.0f;
			src.m_bottom = 800.0f;

			dst.m_top = m_mou_y - 30.0f;
			dst.m_left = m_mou_x + 40.0f;
			dst.m_right = m_mou_x + 120.0f;
			dst.m_bottom = m_mou_y - 10.0f;
			Draw::Draw(21, &src, &dst, white, 0.0f);

			//�������� LV.�����摜�\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 607.0f;
			src.m_bottom = 112.0f;

			dst.m_top = m_mou_y - 43.0f;
			dst.m_left = m_mou_x - 90.0f;
			dst.m_right = m_mou_x + 40.0f;
			dst.m_bottom = m_mou_y - 18.0f;
			Draw::Draw(64, &src, &dst, white, 0.0f);

			//�����������x��
			FontDraw(NumConversion(g_Ins_Level), m_mou_x + 60.0f, m_mou_y - 45.5f, 30.0f, 30.0f, white, true);
		}
	}
	
	//�������E�C���h�E�J���Ă���ۂɕ\������O���t�B�b�N
	else if (window_start_manage == Institute)
	{
		//���E�B���h�E�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1200.0f;
		src.m_bottom = 700.0f;

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

		dst.m_top = 60.0f;
		dst.m_left = 70.0f;
		dst.m_right = 120.0f;
		dst.m_bottom = 110.0f;
		Draw::Draw(1, &src, &dst, back, 0.0f);

		//���������\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 400.0f;
		src.m_bottom = 400.0f;

		dst.m_top = 160.0f;
		dst.m_left = 100.0f;
		dst.m_right = 400.0f;
		dst.m_bottom = 400.0f;
		Draw::Draw(3 + (g_Ins_Level - 1) * 3, &src, &dst, white, 0.0f);

		//��������LVUP�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 120.0f;
		src.m_bottom = 150.0f;

		dst.m_top = 470.0f;
		dst.m_left = 48.0f;
		dst.m_right = 148.0f;
		dst.m_bottom = 620.0f;
		Draw::Draw(22, &src, &dst, Lvup, 0.0f);

		//�����x��UP�����E�C���h�E�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1200.0f;
		src.m_bottom = 700.0f;

		dst.m_top = 420.0f;
		dst.m_left = 150.0f;
		dst.m_right = 450.0f;
		dst.m_bottom = 650.0f;
		Draw::Draw(20, &src, &dst, white, 0.0f);

		//���c��Z�����̃E�C���h�E�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1200.0f;
		src.m_bottom = 700.0f;

		dst.m_top = 235.0f;
		dst.m_left = 750.0f;
		dst.m_right = 1160.0f;
		dst.m_bottom = 305.0f;
		Draw::Draw(20, &src, &dst, white, 0.0f);

		//���������U�蕪��DOWN�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 120.0f;
		dst.m_left = 810.0f;
		dst.m_right = 910.0f;
		dst.m_bottom = 220.0f;
		Draw::Draw(118, &src, &dst, down, 0.0f);

		//���������U�蕪��UP�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 120.0f;
		dst.m_left = 700.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 220.0f;
		Draw::Draw(119, &src, &dst, up, 0.0f);

		//���������̏Z�����E�C���h�E�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1200.0f;
		src.m_bottom = 700.0f;

		dst.m_top = 140.0f;
		dst.m_left = 930.0f;
		dst.m_right = 1150.0f;
		dst.m_bottom = 200.0f;
		Draw::Draw(20, &src, &dst, white, 0.0f);

		//���~�T�C���{�^���\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 305.0f;
		src.m_bottom = 75.0f;

		dst.m_top = 330.0f;
		dst.m_left = 520.0f;
		dst.m_right = 1130.0f;
		dst.m_bottom = 480.0f;
		Draw::Draw(25, &src, &dst, missile, 0.0f);

		//���|�b�h���j���[�{�^���\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 305.0f;
		src.m_bottom = 75.0f;

		dst.m_top = 500.0f;
		dst.m_left = 520.0f;
		dst.m_right = 1130.0f;
		dst.m_bottom = 650.0f;
		Draw::Draw(26, &src, &dst, equip, 0.0f);

		//�������� LV.�����摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 607.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 120.0f;
		dst.m_left = 130.0f;
		dst.m_right = 380.0f;
		dst.m_bottom = 170.0f;
		Draw::Draw(64, &src, &dst, white, 0.0f);

		//�����������x��UP�����摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 930.0f;
		src.m_bottom = 117.0f;

		dst.m_top = 365.0f;
		dst.m_left = 50.0f;
		dst.m_right = 450.0f;
		dst.m_bottom = 415.0f;
		Draw::Draw(65, &src, &dst, white, 0.0f);

		//�������������摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 352.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 145.0f;
		dst.m_left = 505.0f;
		dst.m_right = 670.0f;
		dst.m_bottom = 200.0f;
		Draw::Draw(75, &src, &dst, gray, 0.0f);

		//���Z���U�蕪�������摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 742.0f;
		src.m_bottom = 117.0f;

		dst.m_top = 50.0f;
		dst.m_left = 620.0f;
		dst.m_right = 980.0f;
		dst.m_bottom = 110.0f;
		Draw::Draw(76, &src, &dst, white, 0.0f);

		//���l�����摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 112.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 145.0f;
		dst.m_left = 1090.0f;
		dst.m_right = 1140.0f;
		dst.m_bottom = 195.0f;
		Draw::Draw(77, &src, &dst, black, 0.0f);

		//���c��@�@�@�l�����摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 712.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 245.0f;
		dst.m_left = 770.0f;
		dst.m_right = 1130.0f;
		dst.m_bottom = 295.0f;
		Draw::Draw(78, &src, &dst, black, 0.0f);


		//���t�H���g�\��
		//���������x��
		src.m_top = 1250.0f;
		src.m_left = CUT_ZERO + (g_Ins_Level * 125);
		src.m_right = END_ZERO + (g_Ins_Level * 125);
		src.m_bottom = 1375.0f;

		dst.m_top = 115;
		dst.m_left = 385;
		dst.m_right = 435;
		dst.m_bottom = 175;
		Draw::Draw(121, &src, &dst, white, 0.0f);
		//Font::StrDraw(Ins, 105.0f, 95.0f, 50.0f, white);

		//�c��Z����---------------------------------------------
		//���̈�
		if (g_Remain_num >= 10000) {
			
			src.m_top = 1250.0f;
			src.m_left = CUT_ZERO + (floor(g_Remain_num / 10000) * 125);
			src.m_right = END_ZERO + (floor(g_Remain_num / 10000) * 125);
			src.m_bottom = 1375.0f;

			dst.m_top = 245;
			dst.m_left = 920;
			dst.m_right = 950;
			dst.m_bottom = 295;
			Draw::Draw(120, &src, &dst, black, 0.0f);
		}
		//��̈�
		if (g_Remain_num >= 1000) {
			src.m_top = 1250.0f;
			src.m_left = CUT_ZERO + (floor((g_Remain_num / 1000) % 10) * 125);
			src.m_right = END_ZERO + (floor((g_Remain_num / 1000) % 10) * 125);
			src.m_bottom = 1375.0f;

			dst.m_top = 245;
			dst.m_left = 950;
			dst.m_right = 980;
			dst.m_bottom = 295;
			Draw::Draw(120, &src, &dst, black, 0.0f);
		}
		//�S�̈�
		if (g_Remain_num >= 100) {
			src.m_top = 1250.0f;
			src.m_left = CUT_ZERO + (floor((g_Remain_num / 100) % 10) * 125);
			src.m_right = END_ZERO + (floor((g_Remain_num / 100) % 10) * 125);
			src.m_bottom = 1375.0f;

			dst.m_top = 245;
			dst.m_left = 980;
			dst.m_right = 1010;
			dst.m_bottom = 295;
			Draw::Draw(120, &src, &dst, black, 0.0f);

		    //�\�̈�
			//�S�ȉ��̎��͐�΂ɕ`�悵�Ȃ�
			src.m_top = 1250.0f;
			src.m_left = CUT_ZERO;
			src.m_right = END_ZERO;
			src.m_bottom = 1375.0f;

			dst.m_top = 245;
			dst.m_left = 1010;
			dst.m_right = 1040;
			dst.m_bottom = 295;
			Draw::Draw(120, &src, &dst, black, 0.0f);
		}

		//��̈ʂ�0
		src.m_top = 1250.0f;
		src.m_left = CUT_ZERO;
		src.m_right = END_ZERO;
		src.m_bottom = 1375.0f;

		dst.m_top = 245;
		dst.m_left = 1040;
		dst.m_right = 1070;
		dst.m_bottom = 295;
		Draw::Draw(120, &src, &dst, black, 0.0f);
		//Font::StrDraw(human_remain, 780.0f, 245.0f, 50.0f, black);
		//---------------------------------------------------------------------------

		//�������̏Z����-------------------------------------------------------------
		//���̈�
		if (g_Research_num >= 10000) {

			src.m_top = 1250.0f;
			src.m_left = CUT_ZERO + (floor(g_Research_num / 10000) * 125);
			src.m_right = END_ZERO + (floor(g_Research_num / 10000) * 125);
			src.m_bottom = 1375.0f;

			dst.m_top = 145;
			dst.m_left = 940;
			dst.m_right = 970;
			dst.m_bottom = 195;
			Draw::Draw(120, &src, &dst, black, 0.0f);
		}
		//��̈�
		if (g_Research_num >= 1000) {
			src.m_top = 1250.0f;
			src.m_left = CUT_ZERO + (floor((g_Research_num / 1000) % 10) * 125);
			src.m_right = END_ZERO + (floor((g_Research_num / 1000) % 10) * 125);
			src.m_bottom = 1375.0f;

			dst.m_top = 145;
			dst.m_left = 970;
			dst.m_right = 1000;
			dst.m_bottom = 195;
			Draw::Draw(120, &src, &dst, black, 0.0f);
		}
		//�S�̈�
		if (g_Research_num >= 100) {
			src.m_top = 1250.0f;
			src.m_left = CUT_ZERO + (floor((g_Research_num / 100) % 10) * 125);
			src.m_right = END_ZERO + (floor((g_Research_num / 100) % 10) * 125);
			src.m_bottom = 1375.0f;

			dst.m_top = 145;
			dst.m_left = 1000;
			dst.m_right = 1030;
			dst.m_bottom = 195;
			Draw::Draw(120, &src, &dst, black, 0.0f);

			//�\�̈ʂ�0
			src.m_top = 1250.0f;
			src.m_left = CUT_ZERO;
			src.m_right = END_ZERO;
			src.m_bottom = 1375.0f;

			dst.m_top = 145;
			dst.m_left = 1030;
			dst.m_right = 1060;
			dst.m_bottom = 195;
			Draw::Draw(120, &src, &dst, black, 0.0f);
		}

		//��̈�
		src.m_top = 1250.0f;
		src.m_left = CUT_ZERO;
		src.m_right = END_ZERO;
		src.m_bottom = 1375.0f;

		dst.m_top = 145;
		dst.m_left = 1060;
		dst.m_right = 1090;
		dst.m_bottom = 195;
		Draw::Draw(120, &src, &dst, black, 0.0f);
		//Font::StrDraw(Research_num, 950.0f, 150.0f, 40.0f, black);
		//---------------------------------------------------------------------------

		Facility_message(g_Ins_Level);//�������̕K�v�f��&�T�C�Y���b�Z�[�W�`��֐��Ăяo��


		//���ȈՃ��b�Z�[�W(�G���[���b�Z�[�W�A���x��UP�\����)�摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = m_message_clip_right;
		src.m_bottom = m_message_clip_bottom;

		dst.m_top = m_mou_y + MES_DRAW_TOP;
		dst.m_left = m_mou_x + m_message_draw_left;
		dst.m_right = m_mou_x + m_message_draw_right;
		dst.m_bottom = m_mou_y + MES_DRAW_BOTTOM;
		Draw::Draw(127, &src, &dst, message, 0.0f);


		//���ŏI�m�F�E�C���h�E�\���Ǘ��t���O��true�̎��A�`��B
		if (m_finalcheck_f == true)
		{
			//���ŏI�m�F�E�C���h�E�\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 1200.0f;
			src.m_bottom = 700.0f;

			dst.m_top = 220.0f;
			dst.m_left = 320.0f;
			dst.m_right = 880.0f;
			dst.m_bottom = 480.0f;
			Draw::Draw(20, &src, &dst, white, 0.0f);

			//���f��HP�����摜�\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 412.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 250.0f;
			dst.m_left = 345.0f;
			dst.m_right = 465.0f;
			dst.m_bottom = 280.0f;
			Draw::Draw(67, &src, &dst, black, 0.0f);

			//�u�Ɓv�̕����摜��FontDraw�֐��ɂĕ\��
			FontDraw(L"��", 466.0f, 250.0, 30.0f, 30.0f, black, false);

			//���f�ޏ���ĕ����摜�\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 717.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 250.0f;
			dst.m_left = 497.0f;
			dst.m_right = 677.0f;
			dst.m_bottom = 280.0f;
			Draw::Draw(72, &src, &dst, black, 0.0f);

			//�����x���A�b�v���܂����H�����摜�\��
			src.m_top = 0.0f;
			src.m_left = 717.0f;
			src.m_right = 2017.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 300.0f;
			dst.m_left = 520.0f;
			dst.m_right = 850.0f;
			dst.m_bottom = 330.0f;
			Draw::Draw(72, &src, &dst, black, 0.0f);

			//���͂������摜�\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 232.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 410.0f;
			dst.m_left = 410.0f;
			dst.m_right = 510.0f;
			dst.m_bottom = 460.0f;
			Draw::Draw(73, &src, &dst, Yes, 0.0f);

			//�������������摜�\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 352.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 410.0f;
			dst.m_left = 650.0f;
			dst.m_right = 800.0f;
			dst.m_bottom = 460.0f;
			Draw::Draw(74, &src, &dst, No, 0.0f);
		}
	}
	
	//�~�T�C���E�C���h�E�A�������͕���|�b�h�E�C���h�E�J���Ă���ۂɕ\������O���t�B�b�N
	else if (window_start_manage == Missile || window_start_manage == Equipment)
	{
		//���������E�C���h�E�̏�ɊJ���Ă���悤�Ɍ����邽�߁A
		//�_�~�[�̌������E�C���h�E�̃O���t�B�b�N��`�悷��B

		//���D�F�E�C���h�E�\��(�_�~�[�������E�C���h�E�p)
		//src.m_top = 0.0f;
		//src.m_left = 0.0f;
		//src.m_right = 1160.0f;
		//src.m_bottom = 660.0f;

		//dst.m_top = 20.0f;
		//dst.m_left = 20.0f;
		//dst.m_right = 1180.0f;
		//dst.m_bottom = 680.0f;
		//Draw::Draw(20, &src, &dst, white, 0.0f);

		////���߂�{�^���\��(�_�~�[�������E�C���h�E�p)
		//src.m_top = 0.0f;
		//src.m_left = 0.0f;
		//src.m_right = 64.0f;
		//src.m_bottom = 64.0f;

		//dst.m_top = 30.0f;
		//dst.m_left = 30.0f;
		//dst.m_right = 80.0f;
		//dst.m_bottom = 80.0f;
		//Draw::Draw(1, &src, &dst, white, 0.0f);

		////��������LVUP�\��(�_�~�[�������E�C���h�E�p)
		//src.m_top = 0.0f;
		//src.m_left = 0.0f;
		//src.m_right = 48.0f;
		//src.m_bottom = 64.0f;

		//dst.m_top = 470.0f;
		//dst.m_left = 30.0f;
		//dst.m_right = 150.0f;
		//dst.m_bottom = 620.0f;
		//Draw::Draw(22, &src, &dst, white, 0.0f);

		////�����x��UP�����E�C���h�E�\��(�_�~�[�������E�C���h�E�p)
		//src.m_top = 0.0f;
		//src.m_left = 0.0f;
		//src.m_right = 64.0f;
		//src.m_bottom = 64.0f;

		//dst.m_top = 420.0f;
		//dst.m_left = 150.0f;
		//dst.m_right = 450.0f;
		//dst.m_bottom = 670.0f;
		//Draw::Draw(21, &src, &dst, white, 0.0f);


		//���ȉ��̓~�T�C���E�C���h�E�A����|�b�h�E�C���h�E�̂ǂ���ł��`��

		//���E�B���h�E�\��(�_�~�[�q�ɃE�B���h�E�p)
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1200.0f;
		src.m_bottom = 700.0f;

		dst.m_top = 20.0f;
		dst.m_left = 20.0f;
		dst.m_right = 1180.0f;
		dst.m_bottom = 680.0f;
		Draw::Draw(20, &src, &dst, white, 0.0f);

		//���E�B���h�E�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1200.0f;
		src.m_bottom = 700.0f;

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

		dst.m_top = 80.0f;
		dst.m_left = 80.0f;
		dst.m_right = 130.0f;
		dst.m_bottom = 130.0f;
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
				src.m_right = 1200.0f;
				src.m_bottom = 700.0f;

				dst.m_top = 75.0f + 190.0f * i;
				dst.m_left = 400.0f;
				dst.m_right = 1130.0f;
				dst.m_bottom = 255.0f + 190.0f * i;
				Draw::Draw(20, &src, &dst, white, 0.0f);
			}

			//�������� LV.�����摜�\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 607.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 95.0f;
			dst.m_left = 545.0f;
			dst.m_right = 905.0f;
			dst.m_bottom = 155.0f;
			Draw::Draw(64, &src, &dst, black, 0.0f);

			//�������������摜�\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 352.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 175.0f;
			dst.m_left = 510.0f;
			dst.m_right = 705.0f;
			dst.m_bottom = 240.0f;
			Draw::Draw(75, &src, &dst, black, 0.0f);

			//���l�����摜�\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 112.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 175.0f;
			dst.m_left = 970.0f;
			dst.m_right = 1035.0f;
			dst.m_bottom = 240.0f;
			Draw::Draw(77, &src, &dst, black, 0.0f);

			//���Đ��Y�X�s�[�h(���L���X�g)�����摜�\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 1522.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 285.0f;
			dst.m_left = 455.0f;
			dst.m_right = 1085.0f;
			dst.m_bottom = 335.0f;
			Draw::Draw(79, &src, &dst, black, 0.0f);

			//��S�����摜
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 112.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 375.0f;
			dst.m_left = 810.0f;
			dst.m_right = 850.0f;
			dst.m_bottom = 415.0f;
			Draw::Draw(122, &src, &dst, black, 0.0f);

			//���t�H���g�\��
			//���������x��
			src.m_top = 1250.0f;
			src.m_left = CUT_ZERO + (g_Ins_Level * 125);
			src.m_right = END_ZERO + (g_Ins_Level * 125);
			src.m_bottom = 1375.0f;

			dst.m_top = 92;
			dst.m_left = 920;
			dst.m_right = 960;
			dst.m_bottom = 157;
			Draw::Draw(121, &src, &dst, black, 0.0f);
			//Font::StrDraw(Ins, 590.0f, 95.0f, 65.0f, black);

			//�������̏Z����--------------------------------------------------
			//���̈�
			if (g_Research_num >= 10000) {

				src.m_top = 1250.0f;
				src.m_left = CUT_ZERO + (floor(g_Research_num / 10000) * 125);
				src.m_right = END_ZERO + (floor(g_Research_num / 10000) * 125);
				src.m_bottom = 1375.0f;

				dst.m_top = 175;
				dst.m_left = 760;
				dst.m_right = 800;
				dst.m_bottom = 240;
				Draw::Draw(120, &src, &dst, black, 0.0f);
			}
			//��̈�
			if (g_Research_num >= 1000) {
				src.m_top = 1250.0f;
				src.m_left = CUT_ZERO + (floor((g_Research_num / 1000) % 10) * 125);
				src.m_right = END_ZERO + (floor((g_Research_num / 1000) % 10) * 125);
				src.m_bottom = 1375.0f;

				dst.m_top = 175;
				dst.m_left = 800;
				dst.m_right = 840;
				dst.m_bottom = 240;
				Draw::Draw(120, &src, &dst, black, 0.0f);
			}
			//�S�̈�
			if (g_Research_num >= 100) {
				src.m_top = 1250.0f;
				src.m_left = CUT_ZERO + (floor((g_Research_num / 100) % 10) * 125);
				src.m_right = END_ZERO + (floor((g_Research_num / 100) % 10) * 125);
				src.m_bottom = 1375.0f;

				dst.m_top = 175;
				dst.m_left = 840;
				dst.m_right = 880;
				dst.m_bottom = 240;
				Draw::Draw(120, &src, &dst, black, 0.0f);

				//�\�̈ʂ�0
				src.m_top = 1250.0f;
				src.m_left = CUT_ZERO;
				src.m_right = END_ZERO;
				src.m_bottom = 1375.0f;

				dst.m_top = 175;
				dst.m_left = 880;
				dst.m_right = 920;
				dst.m_bottom = 240;
				Draw::Draw(120, &src, &dst, black, 0.0f);
			}

			//��̈�
			src.m_top = 1250.0f;
			src.m_left = CUT_ZERO;
			src.m_right = END_ZERO;
			src.m_bottom = 1375.0f;

			dst.m_top = 175;
			dst.m_left = 920;
			dst.m_right = 960;
			dst.m_bottom = 240;
			Draw::Draw(120, &src, &dst, black, 0.0f);
			//Font::StrDraw(Research_num, 750.0f, 175.0f, 65.0f, black);
			//---------------------------------------------------------------------------

			//�~�T�C�����L���X�g�^�C��
			//��̈ʂ�\������̂ŏ����_�؂�グ�Ă����̂�g_Recast_time
			src.m_top = 1250.0f;
			src.m_left = CUT_ZERO + (floor((int)g_Recast_time) * 125);
			src.m_right = END_ZERO + (floor((int)g_Recast_time) * 125);
			src.m_bottom = 1375.0f;

			dst.m_top = 350;
			dst.m_left = 660;
			dst.m_right = 730;
			dst.m_bottom = 420;
			Draw::Draw(120, &src, &dst, black, 0.0f);

			//�s���I�h
			src.m_top = 1250.0f;
			src.m_left = CUT_ZERO - 250;
			src.m_right = END_ZERO - 250;
			src.m_bottom = 1375.0f;

			dst.m_top = 350;
			dst.m_left = 710;
			dst.m_right = 780;
			dst.m_bottom = 420;
			Draw::Draw(120, &src, &dst, black, 0.0f);

			//�������ʂȂ̂�m_Mis_recast�̈�̈�
			src.m_top = 1250.0f;
			src.m_left = CUT_ZERO + ((m_Mis_recast % 10) * 125);
			src.m_right = END_ZERO + ((m_Mis_recast % 10) * 125);
			src.m_bottom = 1375.0f;

			dst.m_top = 350;
			dst.m_left = 750;
			dst.m_right = 820;
			dst.m_bottom = 420;
			Draw::Draw(120, &src, &dst, black, 0.0f);
			//Font::StrDraw(Mis_recast, 660.0f, 350.0f, 75.0f, black);

			//�~�T�C�����L���X�g����LVUP�Ɋւ�����--------------------------------
			if (g_Mis_Recast_Level < 4) {
				//��NEXT LV UP�����摜�\��
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 832.0f;
				src.m_bottom = 112.0f;

				dst.m_top = 475.0f;
				dst.m_left = 740.0f;
				dst.m_right = 1070.0f;
				dst.m_bottom = 540.0f;
				Draw::Draw(80, &src, &dst, black, 0.0f);

				//��LV �����摜�\��
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 190.0f;
				src.m_bottom = 107.0f;

				dst.m_top = 560.0f;
				dst.m_left = 450.0f;
				dst.m_right = 510.0f;
				dst.m_bottom = 610.0f;
				Draw::Draw(81, &src, &dst, black, 0.0f);

				//��50��(����)�����摜�\��
				src.m_top = 1250.0f;
				src.m_left = CUT_ZERO + (m_Mis_recast_next_Ins_Lv[g_Mis_Recast_Level] * 125);
				src.m_right = END_ZERO + (m_Mis_recast_next_Ins_Lv[g_Mis_Recast_Level] * 125);
				src.m_bottom = 1375.0f;

				dst.m_top = 555.0f;
				dst.m_left = 535.0f;
				dst.m_right = 595.0f;
				dst.m_bottom = 615.0f;
				Draw::Draw(121, &src, &dst, black, 0.0f);

				//��50��(��)�����摜�\��
				src.m_top = 1250.0f;
				src.m_left = CUT_ZERO - 375;
				src.m_right = END_ZERO - 375;
				src.m_bottom = 1375.0f;

				dst.m_top = 560.0f;
				dst.m_left = 605.0f;
				dst.m_right = 645.0f;
				dst.m_bottom = 610.0f;
				Draw::Draw(121, &src, &dst, black, 0.0f);

				//���~�T�C�������x���K�v�l���\��
				if (m_Mis_recast_next_Hum_num[g_Mis_Recast_Level] >= 1000) {
					src.m_top = 1250.0f;
					src.m_left = CUT_ZERO + (floor((m_Mis_recast_next_Hum_num[g_Mis_Recast_Level] / 1000) % 10) * 125);
					src.m_right = END_ZERO + (floor((m_Mis_recast_next_Hum_num[g_Mis_Recast_Level] / 1000) % 10) * 125);
					src.m_bottom = 1375.0f;

					dst.m_top = 560;
					dst.m_left = 660;
					dst.m_right = 700;
					dst.m_bottom = 610;
					Draw::Draw(120, &src, &dst, black, 0.0f);
				}
				//�S�̈�
				if (m_Mis_recast_next_Hum_num[g_Mis_Recast_Level] >= 100) {
					src.m_top = 1250.0f;
					src.m_left = CUT_ZERO + (floor((m_Mis_recast_next_Hum_num[g_Mis_Recast_Level] / 100) % 10) * 125);
					src.m_right = END_ZERO + (floor((m_Mis_recast_next_Hum_num[g_Mis_Recast_Level] / 100) % 10) * 125);
					src.m_bottom = 1375.0f;

					dst.m_top = 560;
					dst.m_left = 700;
					dst.m_right = 740;
					dst.m_bottom = 610;
					Draw::Draw(120, &src, &dst, black, 0.0f);

					//�\�̈ʂ�0
					src.m_top = 1250.0f;
					src.m_left = CUT_ZERO;
					src.m_right = END_ZERO;
					src.m_bottom = 1375.0f;

					dst.m_top = 560;
					dst.m_left = 740;
					dst.m_right = 780;
					dst.m_bottom = 610;
					Draw::Draw(120, &src, &dst, black, 0.0f);
				}

				//��̈�
				src.m_top = 1250.0f;
				src.m_left = CUT_ZERO;
				src.m_right = END_ZERO;
				src.m_bottom = 1375.0f;

				dst.m_top = 560;
				dst.m_left = 780;
				dst.m_right = 820;
				dst.m_bottom = 610;
				Draw::Draw(120, &src, &dst, black, 0.0f);

				//���l�����摜�\��
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 112.0f;
				src.m_bottom = 112.0f;

				dst.m_top = 560.0f;
				dst.m_left = 820.0f;
				dst.m_right = 880.0f;
				dst.m_bottom = 610.0f;
				Draw::Draw(77, &src, &dst, black, 0.0f);

				//��50��(��)�����摜�\�� (��)�ɐl�����摜��\�����Ă��܂�
				src.m_top = 1250.0f;
				src.m_left = CUT_ZERO - 125;
				src.m_right = END_ZERO - 125;
				src.m_bottom = 1375.0f;

				dst.m_top = 560.0f;
				dst.m_left = 890.0f;
				dst.m_right = 950.0f;
				dst.m_bottom = 610.0f;
				Draw::Draw(121, &src, &dst, black, 0.0f);

				//�~�T�C���̎��̃��x���ł̃��L���X�g�̈�̈�
				src.m_top = 1250.0f;
				src.m_left = CUT_ZERO + (floor(m_Mis_recast_time[g_Mis_Recast_Level + 1]) * 125);
				src.m_right = END_ZERO + (floor(m_Mis_recast_time[g_Mis_Recast_Level + 1]) * 125);
				src.m_bottom = 1375.0f;

				dst.m_top = 560;
				dst.m_left = 950;
				dst.m_right = 990;
				dst.m_bottom = 610;
				Draw::Draw(120, &src, &dst, black, 0.0f);

				//�s���I�h
				src.m_top = 1250.0f;
				src.m_left = CUT_ZERO - 250;
				src.m_right = END_ZERO - 250;
				src.m_bottom = 1375.0f;

				dst.m_top = 560;
				dst.m_left = 975;
				dst.m_right = 1015;
				dst.m_bottom = 610;
				Draw::Draw(120, &src, &dst, black, 0.0f);

				//��������
				src.m_top = 1250.0f;
				src.m_left = CUT_ZERO + ((m_Mis_recast_next % 10) * 125);
				src.m_right = END_ZERO + ((m_Mis_recast_next % 10) * 125);
				src.m_bottom = 1375.0f;

				dst.m_top = 560;
				dst.m_left = 1000;
				dst.m_right = 1040;
				dst.m_bottom = 610;
				Draw::Draw(120, &src, &dst, black, 0.0f);

				//��50��(s)�����摜�\��(��)�ɐl�����摜��\�����Ă��܂�
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 112.0f;
				src.m_bottom = 112.0f;

				dst.m_top = 580.0f;
				dst.m_left = 1040.0f;
				dst.m_right = 1070.0f;
				dst.m_bottom = 610.0f;
				Draw::Draw(122, &src, &dst, black, 0.0f);
				//Font::StrDraw(Next_Lvup, 450.0f, 560.0f, 50.0f, black);
			}

			//�~�T�C���̃��L���X�g���x�����}�b�N�X�ł͂Ȃ��Ƃ�
			else {
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 1605.0f;
				src.m_bottom = 112.0f;

				dst.m_top = 525.0f;
				dst.m_left = 440.0f;
				dst.m_right = 1090.0f;
				dst.m_bottom = 525.0f + 50.0f;
				Draw::Draw(131, &src, &dst, black, 0.0f);
			}
			//-----------------------------------------
		}

		//���ȉ��͕���|�b�h�E�C���h�E�ŕ`�悷�����
		else // (window_start_manage == Equipment)
		{
			//������(�R�A)�摜�W��\��
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					src.m_top = 0.0f;
					src.m_left = 0.0f;
					src.m_right = 130.0f;
					src.m_bottom = 130.0f;

					dst.m_top = 210.0f + j * 150.0f;
					dst.m_left = 280.0f + i * 170.0f;
					dst.m_right = 410.0f + i * 170.0f;
					dst.m_bottom = 340.0f + j * 150.0f;
					Draw::Draw(49 + j + i * 3, &src, &dst, equip_pic[j + i * 3], 0.0f);
				}
			}

			//���|�b�g�摜�W��\��
			for (int p = 0;p < 3;p++)
			{
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 130.0f;
				src.m_bottom = 130.0f;

				dst.m_top = 210.0f + p * 150.0f;
				dst.m_left = 950.0f;
				dst.m_right = 1080.0f;
				dst.m_bottom = 340.0f + p * 150.0f;
				Draw::Draw(128 + p, &src, &dst, equip_pic[12 + p], 0.0f);
			}

			//���t�H���g�\��
			//���탌�x��
			wchar_t weapon_Lv[5];
			for (int i = 0; i < 3; i++)
			{
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 313.0f;
				src.m_bottom = 107.0f;

				dst.m_top = 250 + (i * 150);
				dst.m_left = 80;
				dst.m_right = 200;
				dst.m_bottom = 300 + (i * 150);
				Draw::Draw(123 + i, &src, &dst,white, 0.0f);
				//swprintf_s(weapon_Lv, L"Lv.%d", i + 1);
				//Font::StrDraw(weapon_Lv, 80.0f, 250.0f + i * 150.0f, 50.0f, white);
			}

			//�����b�h�����摜�\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 334.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 98.0f;
			dst.m_left = 285.0f;
			dst.m_right = 405.0f;
			dst.m_bottom = 138.0f;
			Draw::Draw(82, &src, &dst, red, 0.0f);

			//���u���[�����摜�\��
			src.m_top = 2.0f;
			src.m_left = 0.0f;
			src.m_right = 352.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 98.0f;
			dst.m_left = 460.0f;
			dst.m_right = 585.0f;
			dst.m_bottom = 138.0f;
			Draw::Draw(83, &src, &dst, blue, 0.0f);

			//���O���[�������摜�\��
			src.m_top = 2.0f;
			src.m_left = 2.0f;
			src.m_right = 472.0f;
			src.m_bottom = 110.0f;

			dst.m_top = 103.0f;
			dst.m_left = 625.0f;
			dst.m_right = 745.0f;
			dst.m_bottom = 133.0f;
			Draw::Draw(84, &src, &dst, green, 0.0f);

			//���z���C�g�����摜�\��
			src.m_top = 2.0f;
			src.m_left = 0.0f;
			src.m_right = 464.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 103.0f;
			dst.m_left = 805.0f;
			dst.m_right = 925.0f;
			dst.m_bottom = 133.0f;
			Draw::Draw(85, &src, &dst, white, 0.0f);

			//���|�b�h�����摜�\��
			src.m_top = 2.0f;
			src.m_left = 2.0f;
			src.m_right = 344.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 98.0f;
			dst.m_left = 965.0f;
			dst.m_right = 1085.0f;
			dst.m_bottom = 138.0f;
			Draw::Draw(86, &src, &dst, yellow, 0.0f);

			//������K�v�f��&�l�����b�Z�[�W�\��
			//���E�C���h�E�\�� 
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 1200.0f;
			src.m_bottom = 700.0f;

			dst.m_top = m_mou_y - m_Equ_message_window_y_size;
			dst.m_left = m_mou_x - m_Equ_message_window_x_size;
			dst.m_right = m_mou_x + m_Equ_message_window_x_size;
			dst.m_bottom = m_mou_y + 0.0f;
			Draw::Draw(20, &src, &dst, Equ_message_window, 0.0f);

			//��LvUP�����@�����K�v�����摜�\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 1335.0f;
			src.m_bottom = 112.0f;

			dst.m_top = m_mou_y -160.0f;
			dst.m_left = m_mou_x - 135.0f;
			dst.m_right = m_mou_x + 135.0f;
			dst.m_bottom = m_mou_y - 135.0f;
			Draw::Draw(66, &src, &dst, Equ_message_font[0], 0.0f);

			//�������������摜�\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 352.0f;
			src.m_bottom = 112.0f;

			dst.m_top = m_mou_y - 120.0f;
			dst.m_left = m_mou_x - 135.0f;
			dst.m_right = m_mou_x - 60.0f;
			dst.m_bottom = m_mou_y - 95.0f;
			Draw::Draw(75, &src, &dst, Equ_message_font[1], 0.0f);

			//�����݂̌���������\��
			FontDraw(NumConversion(g_Research_num), m_mou_x + 40.0f, m_mou_y - 120.0f, 15.0f, 25.0f, Equ_message_font[1], true);

			//������|�b�h�摜���D�F(���x��UP��[������])�̎��̂ݕ`�悷�����
			if (m_Equ_alpha == -0.1f)
			{
				//�������\�ƂȂ錤�������\��
				FontDraw(NumConversion(m_equipable_count), m_mou_x - 40.0f, m_mou_y - 40.0f, 20.0f, 30.0f, black, true);
			}
			//������|�b�h�摜�����F(���x���A�b�v�\)�A���F(�����s��)�̎��̂ݕ`�悷�����
			//������|�b�h�K�v�f��&�l���t�H���g���ߓx��0.0f�̎��͏����������Ȃ��悤�ɂ���B
			else if (m_Equ_alpha != 0.0f)
			{
				//���e����A�|�b�h�̎���LVUP�ɕK�v�Ȍ������̏Z�����\��
				FontDraw(NumConversion(m_Equ_next_Hum_num[m_equip_id][m_Lv_id - 1]), m_mou_x + 120.0f, m_mou_y - 120.0f, 15.0f, 25.0f, Equ_message_font[1], true);

				//���e����A�|�b�h�̎���LVUP�ɕK�v�ȑf�ޖ��\��
				FontDraw(m_Equ_next_Mat_name[m_equip_id][m_Lv_id - 1], m_mou_x - 135.0f, m_mou_y - 80.0f, 25.0f, 25.0f, Equ_message_font[2], false);

				//���e����A�|�b�h�̎���LVUP�ɕK�v�Ȍ��݂̑f�ޏ�������\��
				FontDraw(NumConversion(*m_Equ_next_Mat_type[m_equip_id][m_Lv_id - 1]), m_mou_x + 40.0f, m_mou_y - 80.0f, 15.0f, 25.0f, Equ_message_font[2], true);

				//���e����A�|�b�h�̎���LVUP�ɕK�v�ȑf�ސ���\��
				FontDraw(NumConversion(m_Equ_next_Mat_num[m_equip_id][m_Lv_id - 1]), m_mou_x + 120.0f, m_mou_y - 80.0f, 15.0f, 25.0f, Equ_message_font[2], true);

				//���u���� / �K�v�v�̒l����؂�d�؂�\��
				FontDraw(L"�^", m_mou_x + 55.0f, m_mou_y - 120.0f, 20.0f, 25.0f, Equ_message_font[1], false);
				FontDraw(L"�^", m_mou_x + 55.0f, m_mou_y - 80.0f, 20.0f, 25.0f, Equ_message_font[2], false);
			}

			//���ŉ������b�Z�[�W(�E�C���h�E��ԉ��ɂ���t�H���g)�摜�\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = m_message_clip_right;
			src.m_bottom = m_message_clip_bottom;

			dst.m_top = m_mou_y + MES_DRAW_TOP;
			dst.m_left = m_mou_x + m_message_draw_left;
			dst.m_right = m_mou_x + m_message_draw_right;
			dst.m_bottom = m_mou_y + MES_DRAW_BOTTOM;
			Draw::Draw(127, &src, &dst, message, 0.0f);



			//���ŏI�m�F�E�C���h�E�\���Ǘ��t���O��true�̎��A�`��B
			if (m_finalcheck_f == true)
			{
				//���ŏI�m�F�E�C���h�E�\��
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 1200.0f;
				src.m_bottom = 700.0f;

				dst.m_top = 220.0f;
				dst.m_left = 320.0f;
				dst.m_right = 880.0f;
				dst.m_bottom = 480.0f;
				Draw::Draw(20, &src, &dst, white, 0.0f);

				//���f�ޏ���ă��x���A�b�v���܂����H�����摜�\��
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 2017.0f;
				src.m_bottom = 112.0f;

				dst.m_top = 250.0f;
				dst.m_left = 345.0f;
				dst.m_right = 855.0f;
				dst.m_bottom = 280.0f;
				Draw::Draw(72, &src, &dst, black, 0.0f);

				//�����������͎����܂��񕶎��摜�\��
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 1304.0f;
				src.m_bottom = 112.0f;

				dst.m_top = 300.0f;
				dst.m_left = 347.0f;
				dst.m_right = 707.0f;
				dst.m_bottom = 330.0f;
				Draw::Draw(87, &src, &dst, black, 0.0f);

				//���͂������摜�\��
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 232.0f;
				src.m_bottom = 112.0f;

				dst.m_top = 410.0f;
				dst.m_left = 410.0f;
				dst.m_right = 510.0f;
				dst.m_bottom = 460.0f;
				Draw::Draw(73, &src, &dst, Yes, 0.0f);

				//�������������摜�\��
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 352.0f;
				src.m_bottom = 112.0f;

				dst.m_top = 410.0f;
				dst.m_left = 650.0f;
				dst.m_right = 800.0f;
				dst.m_bottom = 460.0f;
				Draw::Draw(74, &src, &dst, No, 0.0f);

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

		//�~�T�C�����L���X�g���x��UP�����摜��ǂݍ���127�Ԃɓo�^
		Draw::LoadImage(L"�~�T�C�����L���X�g���x��UP.png", 127, TEX_SIZE_512);//�ȈՃ��b�Z�[�W�摜�ǂݍ��ݔԍ��ɉ摜�f�[�^������

		//�؂���ʒu��ݒ肷��
		m_message_clip_right = 1690.0f;
		m_message_clip_bottom = 112.0f;

		//�`��ʒu��ݒ肷��
		m_message_draw_left = -200.0f;
		m_message_draw_right = 200.0f;

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


		//������|�b�h�����x��UP���������ȈՃ��b�Z�[�W�摜�ɂĒm�点��
		if (equip_id == 0)
		{
			//���b�h���탌�x��UP!�����摜��ǂݍ���127�Ԃɓo�^1200*112
			Draw::LoadImage(L"���b�h���탌�x��UP!.png", 127, TEX_SIZE_512);

			//�؂���ʒu��ݒ肷��
			m_message_clip_right = 1200.0f;
			m_message_clip_bottom = 112.0f;

			//�`��ʒu��ݒ肷��
			m_message_draw_left = -160.0f;
			m_message_draw_right = 160.0f;
		}
		else if (equip_id == 1)
		{
			//�u���[���탌�x��UP!�����摜��ǂݍ���127�Ԃɓo�^1200*112
			Draw::LoadImage(L"�u���[���탌�x��UP!.png", 127, TEX_SIZE_512);										 
			
			//�؂���ʒu��ݒ肷��
			m_message_clip_right = 1200.0f;
			m_message_clip_bottom = 112.0f;

			//�`��ʒu��ݒ肷��
			m_message_draw_left = -160.0f;
			m_message_draw_right = 160.0f;
		}
		else if (equip_id == 2)
		{
			//�O���[�����탌�x��UP!�����摜��ǂݍ���127�Ԃɓo�^1327*112
			Draw::LoadImage(L"�O���[�����탌�x��UP!.png", 127, TEX_SIZE_512);

			//�؂���ʒu��ݒ肷��
			m_message_clip_right = 1327.0f;
			m_message_clip_bottom = 112.0f;

			//�`��ʒu��ݒ肷��
			m_message_draw_left = -170.0f;
			m_message_draw_right = 170.0f;
		}
		else if (equip_id == 3)
		{
			//�z���C�g���탌�x��UP!�����摜��ǂݍ���127�Ԃɓo�^1327*112
			Draw::LoadImage(L"�z���C�g���탌�x��UP!.png", 127, TEX_SIZE_512);

			//�؂���ʒu��ݒ肷��
			m_message_clip_right = 1327.0f;
			m_message_clip_bottom = 112.0f;

			//�`��ʒu��ݒ肷��
			m_message_draw_left = -170.0f;
			m_message_draw_right = 170.0f;
		}
		else  //(equip_id == 4)
		{
			//�|�b�h���x��UP!�����摜��ǂݍ���127�Ԃɓo�^967*112
			Draw::LoadImage(L"�|�b�h���x��UP!.png", 127, TEX_SIZE_512);

			//�؂���ʒu��ݒ肷��
			m_message_clip_right = 967.0f;
			m_message_clip_bottom = 112.0f;

			//�`��ʒu��ݒ肷��
			m_message_draw_left = -120.0f;
			m_message_draw_right = 120.0f;
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
			//���b�h���탌�x��DOWN�c�����摜��ǂݍ���127�Ԃɓo�^1431*112
			Draw::LoadImage(L"���b�h���탌�x��DOWN�c.png", 127, TEX_SIZE_512);

			//�؂���ʒu��ݒ肷��
			m_message_clip_right = 1431.0f;
			m_message_clip_bottom = 112.0f;

			//�`��ʒu��ݒ肷��
			m_message_draw_left = -180.0f;
			m_message_draw_right = 180.0f;
		}
		else if (equip_id == 1)
		{
			//�u���[���탌�x��DOWN�c�����摜��ǂݍ���127�Ԃɓo�^1435*112
			Draw::LoadImage(L"�u���[���탌�x��DOWN�c.png", 127, TEX_SIZE_512);

			//�؂���ʒu��ݒ肷��
			m_message_clip_right = 1435.0f;
			m_message_clip_bottom = 112.0f;

			//�`��ʒu��ݒ肷��
			m_message_draw_left = -180.0f;
			m_message_draw_right = 180.0f;
		}
		else if (equip_id == 2)
		{
			//�O���[�����탌�x��DOWN�c�����摜��ǂݍ���127�Ԃɓo�^1559*112
			Draw::LoadImage(L"�O���[�����탌�x��DOWN�c.png", 127, TEX_SIZE_512);

			//�؂���ʒu��ݒ肷��
			m_message_clip_right = 1559.0f;
			m_message_clip_bottom = 112.0f;

			//�`��ʒu��ݒ肷��
			m_message_draw_left = -200.0f;
			m_message_draw_right = 200.0f;
		}
		else if (equip_id == 3)
		{
			//�z���C�g���탌�x��DOWN�c�����摜��ǂݍ���127�Ԃɓo�^1559*112
			Draw::LoadImage(L"�z���C�g���탌�x��DOWN�c.png", 127, TEX_SIZE_512);

			//�؂���ʒu��ݒ肷��
			m_message_clip_right = 1559.0f;
			m_message_clip_bottom = 112.0f;

			//�`��ʒu��ݒ肷��
			m_message_draw_left = -200.0f;
			m_message_draw_right = 200.0f;
		}
		else  //(equip_id == 4)
		{
			//�|�b�h���x��DOWN�c�����摜��ǂݍ���127�Ԃɓo�^1199*112
			Draw::LoadImage(L"�|�b�h���x��DOWN�c.png", 127, TEX_SIZE_512);

			//�؂���ʒu��ݒ肷��
			m_message_clip_right = 1199.0f;
			m_message_clip_bottom = 112.0f;

			//�`��ʒu��ݒ肷��
			m_message_draw_left = -150.0f;
			m_message_draw_right = 150.0f;
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
	//�t���[�t�H���g�摜�ŕ\�����鎖�ɂȂ�A
	//���̈������h���[�ł��g�p���鎖�ɂȂ����̂ŁA
	//�ȉ��̕ϐ��ɓ���Ďg����悤�ɂ���B
	m_equip_id = equip_id;
	m_Lv_id = Lv_id;

	//������|�b�h�摜�����F(���x���A�b�v�\)�̎��̏���
	if (m_Equ_pic_red_color[Lv_id + equip_id * 3] == 1.0f &&
		m_Equ_pic_green_color[Lv_id + equip_id * 3] == 1.0f &&
		m_Equ_pic_blue_color[Lv_id + equip_id * 3] == 0.0f)
	{
		//���ŉ������b�Z�[�W�摜�ݒ�
		//�N���b�N��LvUP�����摜��ǂݍ���127�Ԃɓo�^
		Draw::LoadImage(L"�N���b�N��LvUP��.png", 127, TEX_SIZE_512);//�ȈՃ��b�Z�[�W�摜�ǂݍ��ݔԍ��ɉ摜�f�[�^������

		//�؂���ʒu��ݒ肷��
		m_message_clip_right = 1057.0f;
		m_message_clip_bottom = 112.0f;

		//�`��ʒu��ݒ肷��
		m_message_draw_left = -110.0f;
		m_message_draw_right = 110.0f;

		//�ŉ������b�Z�[�W�̃J���[��F�ɂ���
		m_message_red_color = 0.0f;
		m_message_green_color = 0.0f;
		m_message_blue_color = 1.0f;

		//����|�b�h�K�v�f��&�l���E�C���h�E�̃T�C�Y��ݒ�
		m_Equ_message_window_x_size = 150.0f;
		m_Equ_message_window_y_size = 170.0f;

		//����|�b�h�K�v�f��&�l���t�H���g��\��
		m_Equ_alpha = 1.0f;

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

				m_Equ_alpha = 0.0f;//����|�b�h�K�v�f��&�l���t�H���g���\��
				m_alpha = 0.0f;//�ŉ������b�Z�[�W���\���ɂ���

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
		//���ŉ������b�Z�[�W�摜�ݒ�
		//LvUP�s�����摜��ǂݍ���127�Ԃɓo�^
		Draw::LoadImage(L"LvUP�s��.png", 127, TEX_SIZE_512);//�ȈՃ��b�Z�[�W�摜�ǂݍ��ݔԍ��ɉ摜�f�[�^������

		//�؂���ʒu��ݒ肷��
		m_message_clip_right = 577.0f;
		m_message_clip_bottom = 112.0f;

		//�`��ʒu��ݒ肷��
		m_message_draw_left = -60.0f;
		m_message_draw_right = 60.0f;

		//�ŉ������b�Z�[�W�̃J���[��ԐF�ɂ���
		m_message_red_color = 1.0f;
		m_message_green_color = 0.0f;
		m_message_blue_color = 0.0f;

		//����|�b�h�K�v�f��&�l���E�C���h�E�̃T�C�Y��ݒ�
		m_Equ_message_window_x_size = 150.0f;
		m_Equ_message_window_y_size = 170.0f;

		//����|�b�h�K�v�f��&�l���t�H���g��\��
		m_Equ_alpha = 1.0f;
	}
	//������|�b�h�摜�����F(������)�̏���
	else if (m_Equ_pic_red_color[Lv_id + equip_id * 3] == 1.0f &&
		m_Equ_pic_green_color[Lv_id + equip_id * 3] == 1.0f &&
		m_Equ_pic_blue_color[Lv_id + equip_id * 3] == 1.0f)
	{
		//���ŉ������b�Z�[�W�摜�ݒ�
		//�����������摜��ǂݍ���127�Ԃɓo�^
		Draw::LoadImage(L"������.png", 127, TEX_SIZE_512);//�ȈՃ��b�Z�[�W�摜�ǂݍ��ݔԍ��ɉ摜�f�[�^������

		//�؂���ʒu��ݒ肷��
		m_message_clip_right = 352.0f;
		m_message_clip_bottom = 112.0f;

		//�`��ʒu��ݒ肷��
		m_message_draw_left = -40.0f;
		m_message_draw_right = 40.0f;

		//�ŉ������b�Z�[�W�̃J���[�����F�ɂ���
		m_message_red_color = 0.0f;
		m_message_green_color = 0.0f;
		m_message_blue_color = 0.0f;

		//����|�b�h�K�v�f��&�l���E�C���h�E�̃T�C�Y��ݒ�
		m_Equ_message_window_x_size = 55.0f;
		m_Equ_message_window_y_size = 50.0f;

		//����|�b�h�K�v�f��&�l���t�H���g���\��
		m_Equ_alpha = 0.0f;
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

		//���ŉ������b�Z�[�W�摜�ݒ�
		//�}�E�X�I�𒆂̕���|�b�h���x�������̕���̌��݃��x�����Ⴉ�����ꍇ
		if (Lv_id + 1 < Tmp_equip_Level) 
		{
			//������%6d�l�@�����ő��������摜��ǂݍ���127�Ԃɓo�^
			Draw::LoadImage(L"������%6d�l�@�����ő�����.png", 127, TEX_SIZE_512);//�ȈՃ��b�Z�[�W�摜�ǂݍ��ݔԍ��ɉ摜�f�[�^������

			m_equipable_count = m_Equ_next_Hum_num[equip_id][Lv_id];//�����\�ƂȂ錤��������ϐ��ɕۑ��B(�h���[���������Ŏg�p)
		}
		//�}�E�X�I�𒆂̕���|�b�h���x�������̕���̌��݃��x����荂�������ꍇ
		else
		{
			//������%6d�l�@�ȏ�ő��������摜��ǂݍ���127�Ԃɓo�^
			Draw::LoadImage(L"������%6d�l�@�ȏ�ő�����.png", 127, TEX_SIZE_512);//�ȈՃ��b�Z�[�W�摜�ǂݍ��ݔԍ��ɉ摜�f�[�^������

			m_equipable_count = m_Equ_next_Hum_num[equip_id][Lv_id - 1];//�����\�ƂȂ錤��������ϐ��ɕۑ��B(�h���[���������Ŏg�p)
		}

		//�؂���ʒu��ݒ肷��
		m_message_clip_right = 1559.0f;
		m_message_clip_bottom = 112.0f;

		//�`��ʒu��ݒ肷��
		m_message_draw_left = -200.0f;
		m_message_draw_right = 200.0f;

		//�ŉ������b�Z�[�W�̃J���[�����F�ɂ���
		m_message_red_color = 0.0f;
		m_message_green_color = 0.0f;
		m_message_blue_color = 0.0f;

		//����|�b�h�K�v�f��&�l���E�C���h�E�̃T�C�Y��ݒ�
		m_Equ_message_window_x_size = 240.0f;
		m_Equ_message_window_y_size = 50.0f;

		//����|�b�h�K�v�f��&�l���t�H���g���\��
		m_Equ_alpha = -0.1f;//-0.1f�ɂ��闝�R�́A�h���[�����ŊD�F�I�𒆂Ɨ���������ׁB
	}


	m_alpha = 1.0f;//����|�b�h�K�v�f��&�l�����b�Z�[�W��\��
}