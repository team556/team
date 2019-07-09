//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

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
	m_Yes_Button_color = 0.0f;
	m_No_Button_color = 0.0f;

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
	m_alpha = INI_ALPHA;

	//�����ɂ̎���LVUP�ɕK�v�ȃT�C�Y(HP)�̏Z�����ݒ�
	m_Facility_next_Size_num[0] = 5.0f; //���x����1�̎��̕K�v�T�C�Y(HP)
	m_Facility_next_Size_num[1] = 4.0f;	//���x����2�̎��̕K�v�T�C�Y(HP)

	//�����ɂ̎���LVUP�ɕK�v�ȑf�ނ̖��O�ݒ�
	swprintf_s(m_Facility_next_Mat_name[0], L"�؍�");			 //���x����1�̎��̕K�v�f�ޖ�
	swprintf_s(m_Facility_next_Mat_name[1], L"�v���X�`�b�N");//���x����2�̎��̕K�v�f�ޖ�

	//�����ɂ̎���LVUP�ɕK�v�ȑf�ގ�ސݒ�Ɠ����ɂ��̑f�ނ̏�������������
	//���ȉ��̂悤�ɏ����f�ސ����Ǘ����Ă���O���[�o���ϐ��̃A�h���X�������鎖�őf�ނ̎�ސݒ�Ə������̑�������Ă���B
	//���������݂͑f�ގ�ނ��m�肵�Ă��Ȃ����߁A����TEST�p�̕������Ă���B��œK�؂Ȃ��̂ɕύX���ׂ��B
	m_Facility_next_Mat_type[0] = &g_Wood_num;	//���x����1�̎��̕K�v�f�ގ��
	m_Facility_next_Mat_type[1] = &g_Plastic_num;	//���x����2�̎��̕K�v�f�ގ��

	//�����ɂ̎���LVUP�ɕK�v�ȑf�ސ��ݒ�
	m_Facility_next_Mat_num[0] = 50;		//���x����1�̎��̕K�v�f�ސ�
	m_Facility_next_Mat_num[1] = 40;	//���x����2�̎��̕K�v�f�ސ�


	//�����蔻��pHitBox���쐬(Objhuman�p)
	Hits::SetHitBox(this, 810, 460, 380, 230, ELEMENT_ENEMY, OBJ_BARRACKS, 1);
}

//�A�N�V����
void CObjBarracks::Action()
{
	//�z���C�g�A�E�g���o���͑���s�\�ɂ��鏈��
	if (white_out_f == true)
	{
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
				m_Yes_Button_color = 1.0f;

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

		//�߂�{�^�����N���b�N�A�������͉E�N���b�N(�ǂ��ł�)���鎖�ŕ��ɃE�C���h�E�����
		if (30 < m_mou_x && m_mou_x < 80 && 30 < m_mou_y && m_mou_y < 80 || m_mou_r == true)
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
						//���N���b�N���ꂽ��ȈՃ��b�Z�[�W�Ń��x��UP�s��`����
						swprintf_s(m_message, L"LvUP�o���܂���");//�����z��ɕ����f�[�^������

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
						//���N���b�N���ꂽ��ȈՃ��b�Z�[�W�Ń��x��UP�s��`����
						swprintf_s(m_message, L"LvUP�o���܂���");//�����z��ɕ����f�[�^������

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

					m_Human_up_color[0] = 0.5f;

					g_Power_num = Allocation(g_Power_num, +1);//�U�蕪���֐����Ăяo��

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

					m_Human_up_color[1] = 0.5f;

					g_Defense_num = Allocation(g_Defense_num, +1);//�U�蕪���֐����Ăяo��

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

					m_Human_up_color[2] = 0.5f;

					g_Speed_num = Allocation(g_Speed_num, +1);//�U�蕪���֐����Ăяo��

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

					m_Human_up_color[3] = 0.5f;

					g_Balance_num = Allocation(g_Balance_num, +1);//�U�蕪���֐����Ăяo��

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

					m_Human_down_color[0] = 0.5f;

					g_Power_num = Allocation(g_Power_num, -1);//�U�蕪���֐����Ăяo��

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

					m_Human_down_color[1] = 0.5f;

					g_Defense_num = Allocation(g_Defense_num, -1);//�U�蕪���֐����Ăяo��

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

					m_Human_down_color[2] = 0.5f;

					g_Speed_num = Allocation(g_Speed_num, -1);//�U�蕪���֐����Ăяo��
					
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

					m_Human_down_color[3] = 0.5f;

					g_Balance_num = Allocation(g_Balance_num, -1);//�U�蕪���֐����Ăяo��

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


		return;
	}
	//�z�[����ʂɖ߂�{�^���������ꂽ��A
	//���{�݂̃E�C���h�E���J���Ă��鎞�͑�����󂯕t���Ȃ��悤�ɂ���B
	else if (window_start_manage != Default || g_help_f == true)
	{
		m_introduce_f = false;	//�{�ݏЉ�E�C���h�E���\���ɂ���(�E�N���b�N�Ńz�[����ʂɖ߂�ہA�E�C���h�E���c��Ȃ��悤�ɂ��邽��)
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

	//�ŏI�m�F[�͂�]�{�^���p
	float Yes[4] = { m_Yes_Button_color,0.0f,0.0f,1.0f };

	//�ŏI�m�F[������]�{�^���p
	float No[4] = { 0.0f,0.0f,m_No_Button_color,1.0f };

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
		Draw::Draw(2 + (g_Bar_Level - 1) * 3, &src, &dst, bar, 0.0f);

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

			////������ Lv�����摜�\��
			//src.m_top = 0.0f;
			//src.m_left = 0.0f;
			//src.m_right = 508.0f;
			//src.m_bottom = 117.0f;

			//dst.m_top = m_mou_y - 45.0f;
			//dst.m_left = m_mou_x - 75.0f;
			//dst.m_right = m_mou_x + 40.0f;
			//dst.m_bottom = m_mou_y - 15.0f;
			//Draw::Draw(116, &src, &dst, black, 0.0f);

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
		src.m_right = 256.0f;
		src.m_bottom = 256.0f;

		dst.m_top = 150.0f;
		dst.m_left = 100.0f;
		dst.m_right = 400.0f;
		dst.m_bottom = 350.0f;
		Draw::Draw(2 + (g_Bar_Level - 1) * 3, &src, &dst, white, 0.0f);

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
			Draw::Draw(120, &src, &dst, up[i], 0.0f);

			//�����ɐU�蕪��DOWN�\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 64.0f;
			src.m_bottom = 64.0f;

			dst.m_top = 120.0f + i * 110.0f;
			dst.m_left = 810.0f;
			dst.m_right = 910.0f;
			dst.m_bottom = 220.0f + i * 110.0f;
			Draw::Draw(121, &src, &dst, down[i], 0.0f);

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

		////������ Lv�����摜�\��
		//src.m_top = 0.0f;
		//src.m_left = 0.0f;
		//src.m_right = 508.0f;
		//src.m_bottom = 117.0f;

		//dst.m_top = 95.0f;
		//dst.m_left = 125.0f;
		//dst.m_right = 325.0f;
		//dst.m_bottom = 145.0f;
		//Draw::Draw(116, &src, &dst, white, 0.0f);

		////�����Ƀ��x��UP�����摜�\��
		//src.m_top = 0.0f;
		//src.m_left = 0.0f;
		//src.m_right = 805.0f;
		//src.m_bottom = 117.0f;

		//dst.m_top = 370.0f;
		//dst.m_left = 60.0f;
		//dst.m_right = 410.0f;
		//dst.m_bottom = 420.0f;
		//Draw::Draw(117, &src, &dst, white, 0.0f);

		////���Z���U�蕪�������摜�\��
		//src.m_top = 0.0f;
		//src.m_left = 0.0f;
		//src.m_right = 742.0f;
		//src.m_bottom = 117.0f;

		//dst.m_top = 45.0f;
		//dst.m_left = 620.0f;
		//dst.m_right = 980.0f;
		//dst.m_bottom = 105.0f;
		//Draw::Draw(76, &src, &dst, white, 0.0f);

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
		//Font::StrDraw(L"���Ƀ��x���t�o", 60.0f, 370.0f, 50.0f, white);

		//Font::StrDraw(L"�Z���U�蕪��", 620.0f, 45.0f, 60.0f, white);

		//Font::StrDraw(L"�p���[", 505.0f, 145.0f, 55.0f, red);

		//Font::StrDraw(L"�f�B�t�F���X", 450.0f, 260.0f, 40.0f, blue);

		//Font::StrDraw(L"�X�s�[�h", 480.0f, 365.0f, 50.0f, green);

		//Font::StrDraw(L"�o�����X", 480.0f, 475.0f, 50.0f, white);

		Facility_message(g_Bar_Level);//���ɂ̕K�v�f��&�T�C�Y���b�Z�[�W�`��֐��Ăяo��

		//�G���[���b�Z�[�W
		Font::StrDraw(m_message, m_mou_x - 110.0f, m_mou_y - 45.0f, 30.0f, error);
		

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



		//�f�o�b�O�p���}�E�X�ʒu�\��
		//wchar_t str[256];
		//swprintf_s(str, L"x=%f,y=%f", m_mou_x, m_mou_y);
		//Font::StrDraw(str, 20.0f, 20.0f, 12.0f, white);
	}
}