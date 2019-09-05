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

//�C�j�V�����C�Y
void CObjBarracks::Init()
{
	m_Back_Button_color = INI_COLOR;
	m_Bar_color = INI_COLOR;
	m_Bar_Lvup_color = INI_COLOR;
	m_Yes_Button_color = 1.0f;
	m_No_Button_color = 1.0f;

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
	m_key_rf = false;
	m_next_time = 0;
	m_con_alo_f = false;

	m_message_clip_right = 0.0f;
	m_message_clip_bottom = 0.0f;
	m_message_draw_left = 0.0f;
	m_message_draw_right = 0.0f;
	m_message_red_color = 0.0f;
	m_message_green_color = 0.0f;
	m_message_blue_color = 0.0f;
	m_alpha = INI_ALPHA;

	//�����ɂ̎���LVUP�ɕK�v�ȃT�C�Y(HP)�̏Z�����ݒ�
	m_Facility_next_Size_num[0] = 70.0f; //���x����1�̎��̕K�v�T�C�Y(HP)
	m_Facility_next_Size_num[1] = 150.0f;	//���x����2�̎��̕K�v�T�C�Y(HP)

	//�����ɂ̎���LVUP�ɕK�v�ȑf�ނ̖��O�ݒ�
	swprintf_s(m_Facility_next_Mat_name[0], L"�؍�");			 //���x����1�̎��̕K�v�f�ޖ�
	swprintf_s(m_Facility_next_Mat_name[1], L"�v���X�`�b�N");//���x����2�̎��̕K�v�f�ޖ�

	//�����ɂ̎���LVUP�ɕK�v�ȑf�ގ�ސݒ�Ɠ����ɂ��̑f�ނ̏�������������
	//���ȉ��̂悤�ɏ����f�ސ����Ǘ����Ă���O���[�o���ϐ��̃A�h���X�������鎖�őf�ނ̎�ސݒ�Ə������̑�������Ă���B
	m_Facility_next_Mat_type[0] = &g_Wood_num;	//���x����1�̎��̕K�v�f�ގ��
	m_Facility_next_Mat_type[1] = &g_Plastic_num;	//���x����2�̎��̕K�v�f�ގ��

	//�����ɂ̎���LVUP�ɕK�v�ȑf�ސ��ݒ�
	m_Facility_next_Mat_num[0] = 50;		//���x����1�̎��̕K�v�f�ސ�
	m_Facility_next_Mat_num[1] = 40;	//���x����2�̎��̕K�v�f�ސ�


	//�����蔻��pHitBox���쐬(Objhuman�p)
	//Hits::SetHitBox(this, 810, 460, 380, 230, ELEMENT_ENEMY, OBJ_BARRACKS, 1);
}

//�A�N�V����
void CObjBarracks::Action()
{
	//�z���C�g�A�E�g���o���͑���s�\�ɂ��鏈��
	//���`���[�g���A����������s�\�ɂ���B
	if (white_out_f == true || g_is_operatable == false)
	{
		return;
	}

	//�w���v��ʕ\�����͑���s�\�ɂ��鏈��
	if (g_help_f == true)
	{
		//�w���v��ʂ̖߂�{�^�������N���b�N(�������͉E�N���b�N)���A
		//���̎{�݂̖߂�{�^���������ɃN���b�N����Ȃ��悤�ɁA
		//�ȉ��̂悤�ɃL�[�t���O��false�ɂ��鎖�Ő��䂵�Ă���B
		m_key_lf = false;
		m_key_rf = false;

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

	//�����ɃE�C���h�E�\�����̏���
	if (window_start_manage == Barracks)
	{
		//��(����)�ŏI�m�F�E�C���h�E�\�����̏���
		if (m_finalcheck_f == true)
		{
			//�ŏI�m�F[�͂�]�{�^��
			if (410 < m_mou_x && m_mou_x < 502 && 407 < m_mou_y && m_mou_y < 450)
			{
				m_Yes_Button_color = 0.0f;

				//���N���b�N���ꂽ�畺�Ƀ��x��UP�������s���A���̃E�C���h�E�����
				//���N���b�N���͎�
				if (m_mou_l == true)
				{
					//���N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
					if (m_key_lf == true)
					{
						m_key_lf = false;

						//�����Ƀ��x��UP����
						//�T�C�Y(HP)�����
						g_Player_max_size -= m_Facility_next_Size_num[g_Bar_Level - 1];

						//�f�ޏ����
						*m_Facility_next_Mat_type[g_Bar_Level - 1] -= m_Facility_next_Mat_num[g_Bar_Level - 1];

						//���Ƀ��x��UP�ɂ��A�v���C���[�f�������x��UP���邩�`�F�b�N����
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
						//�v���C���[�f�������x��UP���Ȃ��ꍇ�A���ʂɕ��ɂ̃��x��UP�������s��
						else
						{
							//���ɂ̃��x��UP����
							g_Bar_Level++;

							//���x���A�b�v��
							Audio::Start(3);
						}
						
						m_Yes_Button_color = 1.0f;

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
				m_Yes_Button_color = 1.0f;
			}

			//�ŏI�m�F[������]�{�^��
			if (648 < m_mou_x && m_mou_x < 789 && 407 < m_mou_y && m_mou_y < 450 || m_mou_r == true)
			{
				m_No_Button_color = 0.0f;

				//���N���b�N���ꂽ��A���̃E�C���h�E�����
				//�E�N���b�N���͎�
				if (m_mou_r == true)
				{
					//�E�C���h�E������A�����Ė߂�{�^������͂��Ȃ��悤��static�ϐ���false�����Đ���
					m_key_rf = false;

					m_No_Button_color = 1.0f;

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

						m_No_Button_color = 1.0f;

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
				m_No_Button_color = 1.0f;
			}


			return;
		}

		//�}�E�X�J�[�\���㕔�ɕ\�������G���[���b�Z�[�W�����X�ɔ�\���ɂ���
		if (m_alpha > 0.0f)
		{
			m_alpha -= 0.01f;
		}

		//�߂�{�^�����N���b�N�A�������͉E�N���b�N(�ǂ��ł�)���鎖�ŕ��ɃE�C���h�E�����
		if (70 < m_mou_x && m_mou_x < 120 && 56 < m_mou_y && m_mou_y < 110 || m_mou_r == true)
		{
			m_Back_Button_color = 1.0f;

			//���N���b�N���ꂽ��t���O�𗧂āA���ɃE�C���h�E�����
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
			m_Back_Button_color = INI_COLOR;
		}

		if (g_tutorial_progress >= 15)
		{
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

						//�����Ƀ��x��UP�\�`�F�b�N����
						if (g_Bar_Level == FACILITY_MAX_LV)
						{
							//�����x��MAX���̏���
							//���N���b�N���ꂽ��ȈՃ��b�Z�[�W�摜�Ń��x��UP�s��`����
							//LvUP�o���܂��񕶎��摜��ǂݍ���127�Ԃɓo�^
							Draw::LoadImage(L"img\\�e�L�X�g\\�琬���\\LvUP�o���܂���.png", 127, TEX_SIZE_512);//�ȈՃ��b�Z�[�W�摜�ǂݍ��ݔԍ��ɉ摜�f�[�^������

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
						else if (g_Player_max_size > m_Facility_next_Size_num[g_Bar_Level - 1] &&
							*m_Facility_next_Mat_type[g_Bar_Level - 1] >= m_Facility_next_Mat_num[g_Bar_Level - 1])
						{
							//�����x��UP�\���̏���
							//���N���b�N���ꂽ��t���O�𗧂āA�ŏI�m�F�E�C���h�E���J��
							m_finalcheck_f = true;//�ŏI�m�F�E�C���h�E��\������

							//�ȈՃ��b�Z�[�W���\���ɂ���
							m_alpha = 0.0f;

							m_Bar_Lvup_color = INI_COLOR;

							//���x���A�b�v��
							Audio::Start(1);

							return;
						}
						else
						{
							//�����x��UP�s���̏���
							//���N���b�N���ꂽ��ȈՃ��b�Z�[�W�摜�Ń��x��UP�s��`����
							//LvUP�o���܂��񕶎��摜��ǂݍ���127�Ԃɓo�^
							Draw::LoadImage(L"img\\�e�L�X�g\\�琬���\\LvUP�o���܂���.png", 127, TEX_SIZE_512);//�ȈՃ��b�Z�[�W�摜�ǂݍ��ݔԍ��ɉ摜�f�[�^������

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
						//���x���A�b�v��
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
				m_Bar_Lvup_color = INI_COLOR;
			}


			//���Z���U�蕪��
			//���ȉ��͊e�Z���U�蕪�����������A���������������֐����\�ł���B
			//�i�I��͈͕������܂߂āA�퓬������ʂ̂悤�Ɋ֐�������̂����z�j
			//���������݁A���Ԃ̗]�T�������ׁA�֐����͌������Ă���B
			//�]�T������Ί֐������������B

			//�Z���U�蕪���A�C�R���J���[���x�𖈉񏉊�������
			for (int i = 0; i < 4; i++)
			{
				m_Human_up_color[i] = INI_COLOR;
				m_Human_down_color[i] = INI_COLOR;
			}

			//�p���[�Z���U�蕪��UP
			if (695 < m_mou_x && m_mou_x < 793 && 118 < m_mou_y && m_mou_y < 218)
			{
				m_Human_up_color[0] = 1.0f;

				//���N���b�N���ꂽ��U�蕪���֐����Ăяo���A�Z���U�蕪���̏������s��
				//�����N���b�N������������ƁA�����ŘA���U�蕪���\�B
				if (m_mou_l == true)
				{
					if (m_next_time <= 0)
					{
						//�L�[�t���OOFF�̎��͈ȉ��̏��������s�����Ȃ�
						if (m_key_lf == false)
						{
							return;
						}
						//����͂��̏����ɓ���[���N���b�N�������̂���߂��m_con_alo_f��"false"�ɖ߂菉�񔻒�ƂȂ�]
						else if (m_con_alo_f == false)
						{
							m_next_time = CON_PRE_TIME;//�A���U�蕪���O�̎��Z���U�蕪�����Ԃ�����(�ŏ��̂ݐU�蕪�����ԊԊu������)
						}
						//���ڈȍ~�͂��̏����ɓ���
						else
						{
							m_next_time = CON_MID_TIME;//�A���U�蕪�����̎��Z���U�蕪�����Ԃ�����(�U�蕪�����ԊԊu���ŏ����Z���Ȃ�)
						}

						m_Human_up_color[0] = 0.5f;

						g_Power_num = Allocation(g_Power_num, +1);//�U�蕪���֐����Ăяo��

						//�U�蕪���{�^����
						Audio::Start(5);
					}
					else
					{
						m_con_alo_f = true;//�A���U�蕪���t���OON
						m_next_time--;//���̏Z���U�蕪���܂ł̎��Ԍ�������
						m_key_lf = true;//�L�[�t���OON
					}
				}
				else
				{
					m_con_alo_f = false;//�A���U�蕪���t���OOFF
					m_next_time = 0;//���̏Z���U�蕪���܂ł̎��Ԃ�������
					m_key_lf = true;//�L�[�t���OON
				}
			}

			//�f�B�t�F���X�Z���U�蕪��UP
			else if (695 < m_mou_x && m_mou_x < 793 && 228 < m_mou_y && m_mou_y < 328)
			{
				m_Human_up_color[1] = 1.0f;

				//���N���b�N���ꂽ��U�蕪���֐����Ăяo���A�Z���U�蕪���̏������s��
				//�����N���b�N������������ƁA�����ŘA���U�蕪���\�B
				if (m_mou_l == true)
				{
					if (m_next_time <= 0)
					{
						//�L�[�t���OOFF�̎��͈ȉ��̏��������s�����Ȃ�
						if (m_key_lf == false)
						{
							return;
						}
						//����͂��̏����ɓ���[���N���b�N�������̂���߂��m_con_alo_f��"false"�ɖ߂菉�񔻒�ƂȂ�]
						else if (m_con_alo_f == false)
						{
							m_next_time = CON_PRE_TIME;//�A���U�蕪���O�̎��Z���U�蕪�����Ԃ�����(�ŏ��̂ݐU�蕪�����ԊԊu������)
						}
						//���ڈȍ~�͂��̏����ɓ���
						else
						{
							m_next_time = CON_MID_TIME;//�A���U�蕪�����̎��Z���U�蕪�����Ԃ�����(�U�蕪�����ԊԊu���ŏ����Z���Ȃ�)
						}

						m_Human_up_color[1] = 0.5f;

						g_Defense_num = Allocation(g_Defense_num, +1);//�U�蕪���֐����Ăяo��

						//�U�蕪���{�^����
						Audio::Start(5);
					}
					else
					{
						m_con_alo_f = true;//�A���U�蕪���t���OON
						m_next_time--;//���̏Z���U�蕪���܂ł̎��Ԍ�������
						m_key_lf = true;//�L�[�t���OON
					}
				}
				else
				{
					m_con_alo_f = false;//�A���U�蕪���t���OOFF
					m_next_time = 0;//���̏Z���U�蕪���܂ł̎��Ԃ�������
					m_key_lf = true;//�L�[�t���OON
				}
			}

			//�X�s�[�h�Z���U�蕪��UP
			else if (695 < m_mou_x && m_mou_x < 793 && 338 < m_mou_y && m_mou_y < 438)
			{
				m_Human_up_color[2] = 1.0f;

				//���N���b�N���ꂽ��U�蕪���֐����Ăяo���A�Z���U�蕪���̏������s��
				//�����N���b�N������������ƁA�����ŘA���U�蕪���\�B
				if (m_mou_l == true)
				{
					if (m_next_time <= 0)
					{
						//�L�[�t���OOFF�̎��͈ȉ��̏��������s�����Ȃ�
						if (m_key_lf == false)
						{
							return;
						}
						//����͂��̏����ɓ���[���N���b�N�������̂���߂��m_con_alo_f��"false"�ɖ߂菉�񔻒�ƂȂ�]
						else if (m_con_alo_f == false)
						{
							m_next_time = CON_PRE_TIME;//�A���U�蕪���O�̎��Z���U�蕪�����Ԃ�����(�ŏ��̂ݐU�蕪�����ԊԊu������)
						}
						//���ڈȍ~�͂��̏����ɓ���
						else
						{
							m_next_time = CON_MID_TIME;//�A���U�蕪�����̎��Z���U�蕪�����Ԃ�����(�U�蕪�����ԊԊu���ŏ����Z���Ȃ�)
						}

						m_Human_up_color[2] = 0.5f;

						g_Speed_num = Allocation(g_Speed_num, +1);//�U�蕪���֐����Ăяo��

						//�U�蕪���{�^����
						Audio::Start(5);
					}
					else
					{
						m_con_alo_f = true;//�A���U�蕪���t���OON
						m_next_time--;//���̏Z���U�蕪���܂ł̎��Ԍ�������
						m_key_lf = true;//�L�[�t���OON
					}
				}
				else
				{
					m_con_alo_f = false;//�A���U�蕪���t���OOFF
					m_next_time = 0;//���̏Z���U�蕪���܂ł̎��Ԃ�������
					m_key_lf = true;//�L�[�t���OON
				}
			}

			//�o�����X�Z���U�蕪��UP
			else if (695 < m_mou_x && m_mou_x < 793 && 448 < m_mou_y && m_mou_y < 548)
			{
				m_Human_up_color[3] = 1.0f;

				//���N���b�N���ꂽ��U�蕪���֐����Ăяo���A�Z���U�蕪���̏������s��
				//�����N���b�N������������ƁA�����ŘA���U�蕪���\�B
				if (m_mou_l == true)
				{
					if (m_next_time <= 0)
					{
						//�L�[�t���OOFF�̎��͈ȉ��̏��������s�����Ȃ�
						if (m_key_lf == false)
						{
							return;
						}
						//����͂��̏����ɓ���[���N���b�N�������̂���߂��m_con_alo_f��"false"�ɖ߂菉�񔻒�ƂȂ�]
						else if (m_con_alo_f == false)
						{
							m_next_time = CON_PRE_TIME;//�A���U�蕪���O�̎��Z���U�蕪�����Ԃ�����(�ŏ��̂ݐU�蕪�����ԊԊu������)
						}
						//���ڈȍ~�͂��̏����ɓ���
						else
						{
							m_next_time = CON_MID_TIME;//�A���U�蕪�����̎��Z���U�蕪�����Ԃ�����(�U�蕪�����ԊԊu���ŏ����Z���Ȃ�)
						}

						m_Human_up_color[3] = 0.5f;

						g_Balance_num = Allocation(g_Balance_num, +1);//�U�蕪���֐����Ăяo��

						//�U�蕪���{�^����
						Audio::Start(5);
					}
					else
					{
						m_con_alo_f = true;//�A���U�蕪���t���OON
						m_next_time--;//���̏Z���U�蕪���܂ł̎��Ԍ�������
						m_key_lf = true;//�L�[�t���OON
					}
				}
				else
				{
					m_con_alo_f = false;//�A���U�蕪���t���OOFF
					m_next_time = 0;//���̏Z���U�蕪���܂ł̎��Ԃ�������
					m_key_lf = true;//�L�[�t���OON
				}
			}

			//�p���[�Z���U�蕪��DOWN
			else if (802 < m_mou_x && m_mou_x < 902 && 118 < m_mou_y && m_mou_y < 218)
			{
				m_Human_down_color[0] = 1.0f;

				//���N���b�N���ꂽ��U�蕪���֐����Ăяo���A�Z���U�蕪���̏������s��
				//�����N���b�N������������ƁA�����ŘA���U�蕪���\�B
				if (m_mou_l == true)
				{
					if (m_next_time <= 0)
					{
						//�L�[�t���OOFF�̎��͈ȉ��̏��������s�����Ȃ�
						if (m_key_lf == false)
						{
							return;
						}
						//����͂��̏����ɓ���[���N���b�N�������̂���߂��m_con_alo_f��"false"�ɖ߂菉�񔻒�ƂȂ�]
						else if (m_con_alo_f == false)
						{
							m_next_time = CON_PRE_TIME;//�A���U�蕪���O�̎��Z���U�蕪�����Ԃ�����(�ŏ��̂ݐU�蕪�����ԊԊu������)
						}
						//���ڈȍ~�͂��̏����ɓ���
						else
						{
							m_next_time = CON_MID_TIME;//�A���U�蕪�����̎��Z���U�蕪�����Ԃ�����(�U�蕪�����ԊԊu���ŏ����Z���Ȃ�)
						}

						m_Human_down_color[0] = 0.5f;

						g_Power_num = Allocation(g_Power_num, -1);//�U�蕪���֐����Ăяo��

						//�U�蕪���_�E����
						Audio::Start(2);
					}
					else
					{
						m_con_alo_f = true;//�A���U�蕪���t���OON
						m_next_time--;//���̏Z���U�蕪���܂ł̎��Ԍ�������
						m_key_lf = true;//�L�[�t���OON
					}
				}
				else
				{
					m_con_alo_f = false;//�A���U�蕪���t���OOFF
					m_next_time = 0;//���̏Z���U�蕪���܂ł̎��Ԃ�������
					m_key_lf = true;//�L�[�t���OON
				}
			}

			//�f�B�t�F���X�Z���U�蕪��DOWN
			else if (802 < m_mou_x && m_mou_x < 902 && 228 < m_mou_y && m_mou_y < 328)
			{
				m_Human_down_color[1] = 1.0f;

				//���N���b�N���ꂽ��U�蕪���֐����Ăяo���A�Z���U�蕪���̏������s��
				//�����N���b�N������������ƁA�����ŘA���U�蕪���\�B
				if (m_mou_l == true)
				{
					if (m_next_time <= 0)
					{
						//�L�[�t���OOFF�̎��͈ȉ��̏��������s�����Ȃ�
						if (m_key_lf == false)
						{
							return;
						}
						//����͂��̏����ɓ���[���N���b�N�������̂���߂��m_con_alo_f��"false"�ɖ߂菉�񔻒�ƂȂ�]
						else if (m_con_alo_f == false)
						{
							m_next_time = CON_PRE_TIME;//�A���U�蕪���O�̎��Z���U�蕪�����Ԃ�����(�ŏ��̂ݐU�蕪�����ԊԊu������)
						}
						//���ڈȍ~�͂��̏����ɓ���
						else
						{
							m_next_time = CON_MID_TIME;//�A���U�蕪�����̎��Z���U�蕪�����Ԃ�����(�U�蕪�����ԊԊu���ŏ����Z���Ȃ�)
						}

						m_Human_down_color[1] = 0.5f;

						g_Defense_num = Allocation(g_Defense_num, -1);//�U�蕪���֐����Ăяo��

						//�U�蕪���_�E����
						Audio::Start(2);
					}
					else
					{
						m_con_alo_f = true;//�A���U�蕪���t���OON
						m_next_time--;//���̏Z���U�蕪���܂ł̎��Ԍ�������
						m_key_lf = true;//�L�[�t���OON
					}
				}
				else
				{
					m_con_alo_f = false;//�A���U�蕪���t���OOFF
					m_next_time = 0;//���̏Z���U�蕪���܂ł̎��Ԃ�������
					m_key_lf = true;//�L�[�t���OON
				}
			}

			//�X�s�[�h�Z���U�蕪��DOWN
			else if (802 < m_mou_x && m_mou_x < 902 && 338 < m_mou_y && m_mou_y < 438)
			{
				m_Human_down_color[2] = 1.0f;

				//���N���b�N���ꂽ��U�蕪���֐����Ăяo���A�Z���U�蕪���̏������s��
				//�����N���b�N������������ƁA�����ŘA���U�蕪���\�B
				if (m_mou_l == true)
				{
					if (m_next_time <= 0)
					{
						//�L�[�t���OOFF�̎��͈ȉ��̏��������s�����Ȃ�
						if (m_key_lf == false)
						{
							return;
						}
						//����͂��̏����ɓ���[���N���b�N�������̂���߂��m_con_alo_f��"false"�ɖ߂菉�񔻒�ƂȂ�]
						else if (m_con_alo_f == false)
						{
							m_next_time = CON_PRE_TIME;//�A���U�蕪���O�̎��Z���U�蕪�����Ԃ�����(�ŏ��̂ݐU�蕪�����ԊԊu������)
						}
						//���ڈȍ~�͂��̏����ɓ���
						else
						{
							m_next_time = CON_MID_TIME;//�A���U�蕪�����̎��Z���U�蕪�����Ԃ�����(�U�蕪�����ԊԊu���ŏ����Z���Ȃ�)
						}

						m_Human_down_color[2] = 0.5f;

						g_Speed_num = Allocation(g_Speed_num, -1);//�U�蕪���֐����Ăяo��

						//�U�蕪���_�E����
						Audio::Start(2);
					}
					else
					{
						m_con_alo_f = true;//�A���U�蕪���t���OON
						m_next_time--;//���̏Z���U�蕪���܂ł̎��Ԍ�������
						m_key_lf = true;//�L�[�t���OON
					}
				}
				else
				{
					m_con_alo_f = false;//�A���U�蕪���t���OOFF
					m_next_time = 0;//���̏Z���U�蕪���܂ł̎��Ԃ�������
					m_key_lf = true;//�L�[�t���OON
				}
			}

			//�o�����X�Z���U�蕪��DOWN
			else if (802 < m_mou_x && m_mou_x < 902 && 448 < m_mou_y && m_mou_y < 548)
			{
				m_Human_down_color[3] = 1.0f;

				//���N���b�N���ꂽ��U�蕪���֐����Ăяo���A�Z���U�蕪���̏������s��
				//�����N���b�N������������ƁA�����ŘA���U�蕪���\�B
				if (m_mou_l == true)
				{
					if (m_next_time <= 0)
					{
						//�L�[�t���OOFF�̎��͈ȉ��̏��������s�����Ȃ�
						if (m_key_lf == false)
						{
							return;
						}
						//����͂��̏����ɓ���[���N���b�N�������̂���߂��m_con_alo_f��"false"�ɖ߂菉�񔻒�ƂȂ�]
						else if (m_con_alo_f == false)
						{
							m_next_time = CON_PRE_TIME;//�A���U�蕪���O�̎��Z���U�蕪�����Ԃ�����(�ŏ��̂ݐU�蕪�����ԊԊu������)
						}
						//���ڈȍ~�͂��̏����ɓ���
						else
						{
							m_next_time = CON_MID_TIME;//�A���U�蕪�����̎��Z���U�蕪�����Ԃ�����(�U�蕪�����ԊԊu���ŏ����Z���Ȃ�)
						}

						m_Human_down_color[3] = 0.5f;

						g_Balance_num = Allocation(g_Balance_num, -1);//�U�蕪���֐����Ăяo��

						//�U�蕪���_�E����
						Audio::Start(2);
					}
					else
					{
						m_con_alo_f = true;//�A���U�蕪���t���OON
						m_next_time--;//���̏Z���U�蕪���܂ł̎��Ԍ�������
						m_key_lf = true;//�L�[�t���OON
					}
				}
				else
				{
					m_con_alo_f = false;//�A���U�蕪���t���OOFF
					m_next_time = 0;//���̏Z���U�蕪���܂ł̎��Ԃ�������
					m_key_lf = true;//�L�[�t���OON
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
					m_key_lf = true;//�L�[�t���OON
				}
			}


			return;
		}
	}
	//�z�[����ʂɖ߂�{�^���������ꂽ��A
	//���{�݂̃E�C���h�E���J���Ă��鎞�͑�����󂯕t���Ȃ��悤�ɂ���B
	else if (window_start_manage != Default)
	{
		m_introduce_f = false;	//�{�ݏЉ�E�C���h�E���\���ɂ���(�E�N���b�N�Ńz�[����ʂɖ߂�ہA�E�C���h�E���c��Ȃ��悤�ɂ��邽��)
		return;
	}

	//dst.m_top = 230.0f;
	//dst.m_left = 400.0f;
	//dst.m_right = 800.0f;
	//dst.m_bottom = 630.0f;

	//���ɑI��͈�
	if (g_tutorial_progress == 12 || g_tutorial_progress >= 14)//�`���[�g���A�����͑I��s��
	{
		if (
			((g_Bar_Level == 1) && (450 < m_mou_x && m_mou_x < 650 && 395 < m_mou_y && m_mou_y < 520)) ||		//���Ƀ��x��1�̎��̔��菈��
			((g_Bar_Level == 2) && 420 < m_mou_x && m_mou_x < 650 && 270 < m_mou_y && m_mou_y < 520 && !(472< m_mou_x&& m_mou_x <671 && 276 < m_mou_y && m_mou_y <400)) ||	//���Ƀ��x��2�̎��̔��菈��
			((g_Bar_Level == 3) && (420 < m_mou_x && m_mou_x < 778 && 270 < m_mou_y && m_mou_y < 520) && !(472< m_mou_x&& m_mou_x <789 && 264 < m_mou_y && m_mou_y <394))		//���Ƀ��x��3�̎��̔��菈��
			)
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

					//�I����
					Audio::Start(1);

					if (g_tutorial_progress == 12)
					{
						//�����\���ɂ�����
						CObjMessage* message = (CObjMessage*)Objs::GetObj(OBJ_MESSAGE);
						message->Setarrow(0);
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
			m_introduce_f = false;//�{�ݏЉ�E�C���h�E���\���ɂ���
			m_Bar_color = INI_COLOR;
		}
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
	float blue[4] = { 0.5f,0.5f,1.0f,1.0f };

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

	//�ŏI�m�F[�͂�]�{�^���p
	float Yes[4] = { 1.0f,m_Yes_Button_color,m_Yes_Button_color,1.0f };

	//�ŏI�m�F[������]�{�^���p
	float No[4] = { m_No_Button_color,m_No_Button_color,1.0f,1.0f };

	//�ȈՃ��b�Z�[�W�摜�p
	float message[4] = { m_message_red_color,m_message_green_color,m_message_blue_color,m_alpha };

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
	if (window_start_manage == Default || window_start_manage == BackButton || window_start_manage == EatButton)
	{
		//�����ɕ\�� 
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 400.0f;
		src.m_bottom = 400.0f;

		dst.m_top = 230.0f;
		dst.m_left = 400.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 630.0f;
		Draw::Draw(2 + (g_Bar_Level - 1) * 3, &src, &dst, bar, 0.0f);

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
			src.m_bottom = 800.0f;

			dst.m_top = m_mou_y - 50.0f;
			dst.m_left = m_mou_x - 40.0f;
			dst.m_right = m_mou_x + 40.0f;
			dst.m_bottom = m_mou_y - 30.0f;
			Draw::Draw(21, &src, &dst, white, 0.0f);

			//���{�ݏЉ�E�C���h�E�\��������
			src.m_top = 0.0f;
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

			//������ Lv�����摜�\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 508.0f;
			src.m_bottom = 117.0f;

			dst.m_top = m_mou_y - 43.0f;
			dst.m_left = m_mou_x - 70.0f;
			dst.m_right = m_mou_x + 35.0f;
			dst.m_bottom = m_mou_y - 18.0f;
			Draw::Draw(116, &src, &dst, white, 0.0f);

			//�����Ƀ��x��
			FontDraw(NumConversion(g_Bar_Level), m_mou_x + 45.0f, m_mou_y - 45.5f, 30.0f, 30.0f, white, true);

			////���t�H���g�\��
			////���Ƀ��x��
			//Font::StrDraw(Bar, m_mou_x - 75.0f, m_mou_y - 45.0f, 30.0f, black);
		}
	}

	//���ɃE�C���h�E�J���Ă���ۂɕ\������O���t�B�b�N
	else if (window_start_manage == Barracks)
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

		//�����ɕ\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 400.0f;
		src.m_bottom = 400.0f;

		dst.m_top = 150.0f;
		dst.m_left = 150.0f;
		dst.m_right = 450.0f;
		dst.m_bottom = 390.0f;
		Draw::Draw(2 + (g_Bar_Level - 1) * 3, &src, &dst, white, 0.0f);

		//������LVUP�\��
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
		Draw::Draw(134, &src, &dst, white, 0.0f);

		//���c��Z�����̃E�C���h�E�\��
		//���������̏Z�����E�C���h�E�\��
		//����
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 795.0f;
		src.m_bottom = 800.0f;

		dst.m_top = 580.0f;
		dst.m_left = 750.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 630.0;
		Draw::Draw(132, &src, &dst, white, 0.0f);

		//����
		src.m_top = 40.0f;
		src.m_left = 800.0f;
		src.m_right = 1600.0f;
		src.m_bottom = 800.0f;

		dst.m_top = 600.0f;
		dst.m_left = 750.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 650.0f;
		Draw::Draw(132, &src, &dst, white, 0.0f);

		for (int j = 0; j < 6; j++)
		{
			//������
			src.m_top = 0.0f;
			src.m_left = 1600.0f;
			src.m_right = 2400.0f;
			src.m_bottom = 800.0f;

			dst.m_top = 580.0f;
			dst.m_left = 800.0f + (j * 50);
			dst.m_right = 850.0f + (j * 50);
			dst.m_bottom = 630.0f;
			Draw::Draw(132, &src, &dst, white, 0.0f);

			//������
			src.m_top = 0.0f;
			src.m_left = 2400.0f;
			src.m_right = 3200.0f;
			src.m_bottom = 800.0f;

			dst.m_top = 600.0f;
			dst.m_left = 800.0f + (j * 50);
			dst.m_right = 850.0f + (j * 50);
			dst.m_bottom = 650.0f;
			Draw::Draw(132, &src, &dst, white, 0.0f);
		}

		//�E��
		src.m_top = 0.0f;
		src.m_left = 4000.0f;
		src.m_right = 4800.0f;
		src.m_bottom = 800.0f;

		dst.m_top = 580.0f;
		dst.m_left = 1080.0f;
		dst.m_right = 1130.0f;
		dst.m_bottom = 630.0f;
		Draw::Draw(132, &src, &dst, white, 0.0f);

		//�E��
		src.m_top = 0.0f;
		src.m_left = 4800.0f;
		src.m_right = 5600.0f;
		src.m_bottom = 800.0f;

		dst.m_top = 600.0f;
		dst.m_left = 1080.0f;
		dst.m_right = 1130.0f;
		dst.m_bottom = 650.0f;
		Draw::Draw(132, &src, &dst, white, 0.0f);

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
			dst.m_top = 140.0f + i * 110.0f;
			dst.m_left = 930.0f;
			dst.m_right = 1150.0f;
			dst.m_bottom = 200.0f + i * 110.0f;
			Draw::Draw(20, &src, &dst, white, 0.0f);
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 795.0f;
			src.m_bottom = 800.0f;

			dst.m_top = 140.0f + i * 110.0f;
			dst.m_left = 930.0f;
			dst.m_right = 970.0f;
			dst.m_bottom = 180.0f + i * 110.0f;
			Draw::Draw(132, &src, &dst, white, 0.0f);

			//����
			src.m_top = 40.0f;
			src.m_left = 800.0f;
			src.m_right = 1600.0f;
			src.m_bottom = 800.0f;

			dst.m_top = 160.0f + i * 110.0f;
			dst.m_left = 930.0f;
			dst.m_right = 970.0f;
			dst.m_bottom = 200.0f + i * 110.0f;
			Draw::Draw(132, &src, &dst, white, 0.0f);

			for (int j = 0; j < 4; j++)
			{
				//������
				src.m_top = 0.0f;
				src.m_left = 1600.0f;
				src.m_right = 2400.0f;
				src.m_bottom = 800.0f;

				dst.m_top = 140.0f + i * 110.0f;
				dst.m_left = 970.0f + (j * 40);
				dst.m_right = 1010.0f + (j * 40);
				dst.m_bottom = 180.0f + i * 110.0f;
				Draw::Draw(132, &src, &dst, white, 0.0f);

				//������
				src.m_top = 0.0f;
				src.m_left = 2400.0f;
				src.m_right = 3200.0f;
				src.m_bottom = 800.0f;

				dst.m_top = 160.0f + i * 110.0f;
				dst.m_left = 970.0f + (j * 40);
				dst.m_right = 1010.0f + (j * 40);
				dst.m_bottom = 200.0f + i * 110.0f;
				Draw::Draw(132, &src, &dst, white, 0.0f);
			}

			//�E��
			src.m_top = 0.0f;
			src.m_left = 4000.0f;
			src.m_right = 4800.0f;
			src.m_bottom = 800.0f;

			dst.m_top = 140.0f + i * 110.0f;
			dst.m_left = 1110.0f;
			dst.m_right = 1150.0f;
			dst.m_bottom = 180.0f + i * 110.0f;
			Draw::Draw(132, &src, &dst, white, 0.0f);

			//�E��
			src.m_top = 0.0f;
			src.m_left = 4800.0f;
			src.m_right = 5600.0f;
			src.m_bottom = 800.0f;

			dst.m_top = 160.0f + i * 110.0f;
			dst.m_left = 1110.0f;
			dst.m_right = 1150.0f;
			dst.m_bottom = 200.0f + i * 110.0f;
			Draw::Draw(132, &src, &dst, white, 0.0f);


		}

		//������ Lv�����摜�\��
		src.m_top = 2.0f;
		src.m_left = 0.0f;
		src.m_right = 508.0f;
		src.m_bottom = 117.0f;

		dst.m_top = 120.0f;
		dst.m_left = 130.0f;
		dst.m_right = 380.0f;
		dst.m_bottom = 170.0f;
		Draw::Draw(116, &src, &dst, white, 0.0f);

		//�����Ƀ��x��UP�����摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 805.0f;
		src.m_bottom = 117.0f;

		dst.m_top = 350.0f;
		dst.m_left = 80.0f;
		dst.m_right = 430.0f;
		dst.m_bottom = 400.0f;
		Draw::Draw(117, &src, &dst, white, 0.0f);

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

		//�����b�h�����摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 336.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 145.0f;
		dst.m_left = 505.0f;
		dst.m_right = 670.0f;
		dst.m_bottom = 200.0f;
		Draw::Draw(82, &src, &dst, red, 0.0f);

		//���u���[�����摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 352.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 260.0f;
		dst.m_left = 505.0f;
		dst.m_right = 670.0f;
		dst.m_bottom = 310.0f;
		Draw::Draw(83, &src, &dst, blue, 0.0f);

		//���O���[�������摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 472.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 365.0f;
		dst.m_left = 480.0f;
		dst.m_right = 680.0f;
		dst.m_bottom = 415.0f;
		Draw::Draw(84, &src, &dst, green, 0.0f);

		//���z���C�g�����摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 464.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 475.0f;
		dst.m_left = 480.0f;
		dst.m_right = 680.0f;
		dst.m_bottom = 525.0f;
		Draw::Draw(85, &src, &dst, white, 0.0f);

		//���l�����摜�\����i��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 112.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 145.0f;
		dst.m_left = 1090.0f;
		dst.m_right = 1140.0f;
		dst.m_bottom = 195.0f;
		Draw::Draw(77, &src, &dst, black, 0.0f);


		//���l�����摜�\����i��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 112.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 255.0f;
		dst.m_left = 1090.0f;
		dst.m_right = 1140.0f;
		dst.m_bottom = 305.0f;
		Draw::Draw(77, &src, &dst, black, 0.0f);

		//���l�����摜�\����i��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 112.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 365.0f;
		dst.m_left = 1090.0f;
		dst.m_right = 1140.0f;
		dst.m_bottom = 415.0f;
		Draw::Draw(77, &src, &dst, black, 0.0f);

		//���l�����摜�\����i��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 112.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 475.0f;
		dst.m_left = 1090.0f;
		dst.m_right = 1140.0f;
		dst.m_bottom = 525.0f;
		Draw::Draw(77, &src, &dst, black, 0.0f);

		//���c��@�@�@�l�����摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 712.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 590.0f;
		dst.m_left = 770.0f;
		dst.m_right = 1130.0f;
		dst.m_bottom = 640.0f;
		Draw::Draw(78, &src, &dst, black, 0.0f);

		//���t�H���g�\��
		//���Ƀ��x��
		src.m_top = 1250.0f;
		src.m_left = CUT_ZERO + (g_Bar_Level * 125);
		src.m_right = END_ZERO + (g_Bar_Level * 125);
		src.m_bottom = 1375.0f;

		dst.m_top = 117;
		dst.m_left = 385;
		dst.m_right = 435;
		dst.m_bottom = 172;
		Draw::Draw(121, &src, &dst, white, 0.0f);
		//Font::StrDraw(Bar, 125.0f, 95.0f, 50.0f, white);
		//�c��Z�����[--------�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
		//���̈�
		if (g_Remain_num >= 10000) {

			src.m_top = 1250.0f;
			src.m_left = CUT_ZERO + (floor(g_Remain_num / 10000) * 125);
			src.m_right = END_ZERO + (floor(g_Remain_num / 10000) * 125);
			src.m_bottom = 1375.0f;

			dst.m_top = 590;
			dst.m_left = 920;
			dst.m_right = 950;
			dst.m_bottom = 640;
			Draw::Draw(120, &src, &dst, black, 0.0f);
		}
		//��̈�
		if (g_Remain_num >= 1000) {
			src.m_top = 1250.0f;
			src.m_left = CUT_ZERO + (floor((g_Remain_num / 1000) % 10) * 125);
			src.m_right = END_ZERO + (floor((g_Remain_num / 1000) % 10) * 125);
			src.m_bottom = 1375.0f;

			dst.m_top = 590;
			dst.m_left = 950;
			dst.m_right = 980;
			dst.m_bottom = 640;
			Draw::Draw(120, &src, &dst, black, 0.0f);
		}
		//�S�̈�
		if (g_Remain_num >= 100) {
			src.m_top = 1250.0f;
			src.m_left = CUT_ZERO + (floor((g_Remain_num / 100) % 10) * 125);
			src.m_right = END_ZERO + (floor((g_Remain_num / 100) % 10) * 125);
			src.m_bottom = 1375.0f;

			dst.m_top = 590;
			dst.m_left = 980;
			dst.m_right = 1010;
			dst.m_bottom = 640;
			Draw::Draw(120, &src, &dst, black, 0.0f);

			//�\�̈ʂ�0
			src.m_top = 1250.0f;
			src.m_left = CUT_ZERO;
			src.m_right = END_ZERO;
			src.m_bottom = 1375.0f;

			dst.m_top = 590;
			dst.m_left = 1010;
			dst.m_right = 1040;
			dst.m_bottom = 640;
			Draw::Draw(120, &src, &dst, black, 0.0f);
		}

		//��̈�
		src.m_top = 1250.0f;
		src.m_left = CUT_ZERO;
		src.m_right = END_ZERO;
		src.m_bottom = 1375.0f;

		dst.m_top = 590;
		dst.m_left = 1040;
		dst.m_right = 1070;
		dst.m_bottom = 640;
		Draw::Draw(120, &src, &dst, black, 0.0f);
		//Font::StrDraw(human_remain, 780.0f, 590.0f, 50.0f, black);
		//----------------------------------------------------------------------------------------------

		//�e�^�C�v(�p���[�A�X�s�[�h��)�̏Z����-------------------------------------------------------------
		for (int i = 0; i < 4; i++){

			switch (i) {
			case 0:
				m_Warrior[i] = g_Power_num;
				break;
			case 1:
				m_Warrior[i] = g_Defense_num;
				break;
			case 2:
				m_Warrior[i] = g_Speed_num;
				break;
			case 3:
				m_Warrior[i] = g_Balance_num;
			}

			if (m_Warrior[i] >= 10000) {

				src.m_top = 1250.0f;
				src.m_left = CUT_ZERO + (floor(m_Warrior[i] / 10000) * 125);
				src.m_right = END_ZERO + (floor(m_Warrior[i] / 10000) * 125);
				src.m_bottom = 1375.0f;

				dst.m_top = 150 + (i * 110);
				dst.m_left = 940;
				dst.m_right = 970;
				dst.m_bottom = 190 + (i * 110);
				Draw::Draw(120, &src, &dst, black, 0.0f);
			}
			//��̈�
			if (m_Warrior[i] >= 1000) {
				src.m_top = 1250.0f;
				src.m_left = CUT_ZERO + (floor((m_Warrior[i] / 1000) % 10) * 125);
				src.m_right = END_ZERO + (floor((m_Warrior[i] / 1000) % 10) * 125);
				src.m_bottom = 1375.0f;

				dst.m_top = 150 + (i * 110);
				dst.m_left = 970;
				dst.m_right = 1000;
				dst.m_bottom = 190 + (i * 110);
				Draw::Draw(120, &src, &dst, black, 0.0f);
			}
			//�S�̈�
			if (m_Warrior[i] >= 100) {
				src.m_top = 1250.0f;
				src.m_left = CUT_ZERO + (floor((m_Warrior[i] / 100) % 10) * 125);
				src.m_right = END_ZERO + (floor((m_Warrior[i] / 100) % 10) * 125);
				src.m_bottom = 1375.0f;

				dst.m_top = 150 + (i * 110);
				dst.m_left = 1000;
				dst.m_right = 1030;
				dst.m_bottom = 190 + (i * 110);
				Draw::Draw(120, &src, &dst, black, 0.0f);

				//�\�̈ʂ�0
				src.m_top = 1250.0f;
				src.m_left = CUT_ZERO;
				src.m_right = END_ZERO;
				src.m_bottom = 1375.0f;

				dst.m_top = 150 + (i * 110);
				dst.m_left = 1030;
				dst.m_right = 1060;
				dst.m_bottom = 190 + (i * 110);
				Draw::Draw(120, &src, &dst, black, 0.0f);
			}

			//��̈�
			src.m_top = 1250.0f;
			src.m_left = CUT_ZERO;
			src.m_right = END_ZERO;
			src.m_bottom = 1375.0f;

			dst.m_top = 150 + (i * 110);
			dst.m_left = 1060;
			dst.m_right = 1090;
			dst.m_bottom = 190 + (i * 110);
			Draw::Draw(120, &src, &dst, black, 0.0f);
		}	
		//Font::StrDraw(human_num[i], 950.0f, 150.0f + i * 110.0f, 40.0f, black);
		//-------------------------------------------------------------------------------

		//���̑��t�H���g
		Facility_message(g_Bar_Level);//���ɂ̕K�v�f��&�T�C�Y���b�Z�[�W�`��֐��Ăяo��


		//���ȈՃ��b�Z�[�W�摜�\��
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
			Draw::Draw(67, &src, &dst, white, 0.0f);

			//�u�Ɓv�̕����摜��FontDraw�֐��ɂĕ\��
			FontDraw(L"��", 466.0f, 250.0, 30.0f, 30.0f, white, false);

			//���f�ޏ���ĕ����摜�\��
			src.m_top = 2.0f;
			src.m_left = 0.0f;
			src.m_right = 717.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 250.0f;
			dst.m_left = 497.0f;
			dst.m_right = 677.0f;
			dst.m_bottom = 280.0f;
			Draw::Draw(72, &src, &dst, white, 0.0f);

			//�����x���A�b�v���܂����H�����摜�\��
			src.m_top = 2.0f;
			src.m_left = 717.0f;
			src.m_right = 2017.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 300.0f;
			dst.m_left = 520.0f;
			dst.m_right = 850.0f;
			dst.m_bottom = 330.0f;
			Draw::Draw(72, &src, &dst, white, 0.0f);

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
		//�f�o�b�O�p���}�E�X�ʒu�\��
		//wchar_t str[256];
		//swprintf_s(str, L"x=%f,y=%f", m_mou_x, m_mou_y);
		//Font::StrDraw(str, 20.0f, 20.0f, 12.0f, white);
	}
}