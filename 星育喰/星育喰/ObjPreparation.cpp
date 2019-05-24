//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�}�N��
#define INI_ENEMY_X_POS (1250.0f)	//�G�f��4�S�̂̏���X�ʒu(�G�f��1�)
#define INI_ENEMY_Y_POS (190.0f)	//�G�f��4�S�̂̏���Y�ʒu(�G�f��1�)
#define INI_WARNING_MESSAGE_X_POS (125.0f)	//�x�����b�Z�[�W�S�̂̏���X�ʒu
#define INI_WARNING_MESSAGE_Y_POS (250.0f)	//�x�����b�Z�[�W�S�̂̏���Y�ʒu
#define INI_WARNING_MESSAGE_SIZE  (100.0f)	//�x�����b�Z�[�W�S�̂̃T�C�Y
#define INI_SPEED (50.0f)//�e���o�ňړ�����e�I�u�W�F�N�g�̏����ړ����x
#define INI_ALPHA (0.0f) //���ߓx(�A���t�@�l)�̏����l
#define INI_COLOR (0.9f) //�S�J���[���x�̏����l(�A�C�R�����I�𒆂̃J���[)
#define INI_PLANET (128.0f)

//�O���[�o���ϐ��̒�`
int g_Stage_progress = 1;
int g_Challenge_enemy = 0;
int g_Special_equipment = 2;//�f�o�b�O�p��2�ɂ��Ă���B���0�ɖ߂��悤�ɁB
bool g_Special_mastering[5] = { true,true,true,true,true };//�f�o�b�O�p�ɑS��true�ɂ��Ă���B���false�ɖ߂��悤�ɁB
bool g_destroy_progress[4] = { false,false,false,false };//�G�̌��j���

//�C�j�V�����C�Y
void CObjPreparation::Init()
{
	m_mou_x = 0.0f;
	m_mou_y = 0.0f;
	m_mou_r = false;
	m_mou_l = false;

	m_key_lf = false;
	m_key_rf = false;

	m_Pvx = 0.0f;
	m_Pvy = 0.0f;
	m_Pr = 0.0f;
	m_Psize = 0.0f;

	m_Svy = 0.0f;

	m_Bvx = 0.0f;
	m_Bvy = 0.0f;

	m_Evx = 0.0f;

	for (int i = 0; i < 2; i++)
	{
		m_warning_message_x[i] = INI_WARNING_MESSAGE_X_POS;
		m_warning_message_y[i] = INI_WARNING_MESSAGE_Y_POS;
	}

	m_warning_message_size = INI_WARNING_MESSAGE_SIZE;
	m_warning_message_alpha = INI_ALPHA;

	for (int i = 0; i < 3; i++)
	{
		m_Boss_vx[i] = 0.0f;
		m_Boss_vy[i] = 0.0f;
	}

	m_Boss_clip_pos_x = -1.0f;//0.0f���ƈӐ}���ĂȂ��^�C�~���O�ŏ������ɓ���ׁA�����l��-1.0f�ɂ��鎖�Ō���Ή��B
	m_Boss_clip_pos_y = 0.0f;

	m_speed = INI_SPEED;
	m_save_speed = 0.0f;

	m_black_star_effect_size = 0.0f;
	m_staging_time = 0;
	m_is_operatable = false;

	m_Back_Button_color = INI_COLOR;
	m_Yes_Button_color = INI_COLOR;
	m_No_Button_color = INI_COLOR;

	m_Back_flag = false;
	m_finalcheck_f = false;

	m_detail_message_window_top = 0.0f;
	m_detail_message_window_left = 0.0f;
	m_detail_message_window_right = 0.0f;
	m_detail_message_window_bottom = 0.0f;
	m_detail_message_font_x = 0.0f;
	m_detail_message_font_y = 0.0f;
	m_detail_message_alpha = INI_ALPHA;

	m_destroy_count = 0;

	//���݂̌��j�����J�E���g
	for (int i = 0; i < 4; i++)
	{
		if (g_destroy_progress[i] == true)
		{
			m_destroy_count++;
		}
	}

	//�����݂̃X�y�V�����Z�K���󋵁A�����󋵂ɉ�����
	//�X�y�V�����Z�A�C�R���̃J���[���x���ȉ��̂悤�ɐݒ肵�Ă����B
	//�u���K���v�c�c�c�c�c�c�c�c�c�c�c0.0f(���F)
	//�u�N���b�N�ő�����(�K����)�v�c�c0.4f(�D�F)
	//�u�������v�c�c�c�c�c�c�c�c�c�c�c1.0f(���F)
	for (int i = 0; i < 5; i++)
	{
		//�������̏���
		if (g_Special_equipment == i + 1)
		{
			m_Special_icon_color[i] = 1.0f;
		}
		//�N���b�N�ő�����(�K����)�̏���
		else if (g_Special_mastering[i] == true)
		{
			m_Special_icon_color[i] = 0.4f;
		}
		//���K���̏���
		else
		{
			m_Special_icon_color[i] = 0.0f;
		}
	}

	//���e�G�f���̏ڍא������ݒ�
	//��1�X�e�[�W�@�G�f��1(������1�Ԗڂ̓G�f��)
	swprintf_s(m_Enemy_detail_message[0][0][0], L"�e�X�g");//1�s��
	swprintf_s(m_Enemy_detail_message[0][0][1], L"�e�X�g");//2�s��
	swprintf_s(m_Enemy_detail_message[0][0][2], L"�e�X�g");//3�s��
	swprintf_s(m_Enemy_detail_message[0][0][3], L"�e�X�g");//4�s��
	//��1�X�e�[�W�@�G�f��2(������2�Ԗڂ̓G�f��)
	swprintf_s(m_Enemy_detail_message[0][1][0], L"�e�X�g");//1�s��
	swprintf_s(m_Enemy_detail_message[0][1][1], L"�e�X�g");//2�s��
	swprintf_s(m_Enemy_detail_message[0][1][2], L"�e�X�g");//3�s��
	swprintf_s(m_Enemy_detail_message[0][1][3], L"�e�X�g");//4�s��
	//��1�X�e�[�W�@�G�f��3(������3�Ԗڂ̓G�f��)
	swprintf_s(m_Enemy_detail_message[0][2][0], L"�e�X�g");//1�s��
	swprintf_s(m_Enemy_detail_message[0][2][1], L"�e�X�g");//2�s��
	swprintf_s(m_Enemy_detail_message[0][2][2], L"�e�X�g");//3�s��
	swprintf_s(m_Enemy_detail_message[0][2][3], L"�e�X�g");//4�s��
	//��1�X�e�[�W�@�G�f��4(������4�Ԗڂ̓G�f��)
	swprintf_s(m_Enemy_detail_message[0][3][0], L"�e�X�g");//1�s��
	swprintf_s(m_Enemy_detail_message[0][3][1], L"�e�X�g");//2�s��
	swprintf_s(m_Enemy_detail_message[0][3][2], L"�e�X�g");//3�s��
	swprintf_s(m_Enemy_detail_message[0][3][3], L"�e�X�g");//4�s��
	//��1�X�e�[�W�@�{�X�f��
	swprintf_s(m_Enemy_detail_message[0][4][0], L"�e�X�g");//1�s��
	swprintf_s(m_Enemy_detail_message[0][4][1], L"�e�X�g");//2�s��
	swprintf_s(m_Enemy_detail_message[0][4][2], L"�e�X�g");//3�s��
	swprintf_s(m_Enemy_detail_message[0][4][3], L"�e�X�g");//4�s��
	//��2�X�e�[�W�@�G�f��1(������1�Ԗڂ̓G�f��)
	swprintf_s(m_Enemy_detail_message[1][0][0], L"�e�X�g");//1�s��
	swprintf_s(m_Enemy_detail_message[1][0][1], L"�e�X�g");//2�s��
	swprintf_s(m_Enemy_detail_message[1][0][2], L"�e�X�g");//3�s��
	swprintf_s(m_Enemy_detail_message[1][0][3], L"�e�X�g");//4�s��
	//��2�X�e�[�W�@�G�f��2(������2�Ԗڂ̓G�f��)
	swprintf_s(m_Enemy_detail_message[1][1][0], L"�e�X�g");//1�s��
	swprintf_s(m_Enemy_detail_message[1][1][1], L"�e�X�g");//2�s��
	swprintf_s(m_Enemy_detail_message[1][1][2], L"�e�X�g");//3�s��
	swprintf_s(m_Enemy_detail_message[1][1][3], L"�e�X�g");//4�s��
	//��2�X�e�[�W�@�G�f��3(������3�Ԗڂ̓G�f��)
	swprintf_s(m_Enemy_detail_message[1][2][0], L"�e�X�g");//1�s��
	swprintf_s(m_Enemy_detail_message[1][2][1], L"�e�X�g");//2�s��
	swprintf_s(m_Enemy_detail_message[1][2][2], L"�e�X�g");//3�s��
	swprintf_s(m_Enemy_detail_message[1][2][3], L"�e�X�g");//4�s��
	//��2�X�e�[�W�@�G�f��4(������4�Ԗڂ̓G�f��)
	swprintf_s(m_Enemy_detail_message[1][3][0], L"�e�X�g");//1�s��
	swprintf_s(m_Enemy_detail_message[1][3][1], L"�e�X�g");//2�s��
	swprintf_s(m_Enemy_detail_message[1][3][2], L"�e�X�g");//3�s��
	swprintf_s(m_Enemy_detail_message[1][3][3], L"�e�X�g");//4�s��
	//��2�X�e�[�W�@�{�X�f��
	swprintf_s(m_Enemy_detail_message[1][4][0], L"�e�X�g");//1�s��
	swprintf_s(m_Enemy_detail_message[1][4][1], L"�e�X�g");//2�s��
	swprintf_s(m_Enemy_detail_message[1][4][2], L"�e�X�g");//3�s��
	swprintf_s(m_Enemy_detail_message[1][4][3], L"�e�X�g");//4�s��
	//��3�X�e�[�W�@�G�f��1(������1�Ԗڂ̓G�f��)
	swprintf_s(m_Enemy_detail_message[2][0][0], L"�e�X�g");//1�s��
	swprintf_s(m_Enemy_detail_message[2][0][1], L"�e�X�g");//2�s��
	swprintf_s(m_Enemy_detail_message[2][0][2], L"�e�X�g");//3�s��
	swprintf_s(m_Enemy_detail_message[2][0][3], L"�e�X�g");//4�s��
	//��3�X�e�[�W�@�G�f��2(������2�Ԗڂ̓G�f��)
	swprintf_s(m_Enemy_detail_message[2][1][0], L"�e�X�g");//1�s��
	swprintf_s(m_Enemy_detail_message[2][1][1], L"�e�X�g");//2�s��
	swprintf_s(m_Enemy_detail_message[2][1][2], L"�e�X�g");//3�s��
	swprintf_s(m_Enemy_detail_message[2][1][3], L"�e�X�g");//4�s��
	//��3�X�e�[�W�@�G�f��3(������3�Ԗڂ̓G�f��)
	swprintf_s(m_Enemy_detail_message[2][2][0], L"�e�X�g");//1�s��
	swprintf_s(m_Enemy_detail_message[2][2][1], L"�e�X�g");//2�s��
	swprintf_s(m_Enemy_detail_message[2][2][2], L"�e�X�g");//3�s��
	swprintf_s(m_Enemy_detail_message[2][2][3], L"�e�X�g");//4�s��
	//��3�X�e�[�W�@�G�f��4(������4�Ԗڂ̓G�f��)
	swprintf_s(m_Enemy_detail_message[2][3][0], L"�e�X�g");//1�s��
	swprintf_s(m_Enemy_detail_message[2][3][1], L"�e�X�g");//2�s��
	swprintf_s(m_Enemy_detail_message[2][3][2], L"�e�X�g");//3�s��
	swprintf_s(m_Enemy_detail_message[2][3][3], L"�e�X�g");//4�s��
	//��3�X�e�[�W�@�{�X�f��
	swprintf_s(m_Enemy_detail_message[2][4][0], L"�e�X�g");//1�s��
	swprintf_s(m_Enemy_detail_message[2][4][1], L"�e�X�g");//2�s��
	swprintf_s(m_Enemy_detail_message[2][4][2], L"�e�X�g");//3�s��
	swprintf_s(m_Enemy_detail_message[2][4][3], L"�e�X�g");//4�s��
}

//�A�N�V����
void CObjPreparation::Action()
{
	//���z�[����ʈڍs���o
	if (m_Back_flag == true)
	{
		if (m_Pvx >= 950.0f)
		{
			//�v���C���[�f������ʒ����Ɉړ�������A�z�[����ʂֈڍs����B
			Scene::SetScene(new CSceneHome());//�z�[����ʂփV�[���ڍs
		}
		else if (m_Psize == -150.0f)
		{
			//��ʊO(����)�����ʒ����Ɍ������ăv���C���[�f�����ړ�������
			//���v���C���[�f��X�ړ�����
			m_Pvx += m_speed;

			//���v���C���[�f��Y�ړ�����
			//�p�x���Z
			m_Pr += 1.0f;

			//360���ŏ����l�ɖ߂�
			if (m_Pr > 360.0f)
				m_Pr = 0.0f;

			//�ړ�����
			m_Pvy = sin(3.14f / 90 * m_Pr) - 550.0f;

			//���x�t����B
			m_Pvy -= m_speed;


			//���X�Ƀv���C���[�f���̈ړ����x������������
			m_speed *= 0.948f;
		}
		else if(m_Evx >= 0.0f)
		{
			m_staging_time++;

			//��0.5�b��A�ȉ��̏��������s�B
			if (m_staging_time >= 30)
			{
				//�v���C���[�f���̈ʒu����ʊO(����)�Ɉړ��B
				//�܂��A�T�C�Y���z�[����ʂ̃v���C���[�f���Ɠ����T�C�Y�ɂ���B
				m_Pvx = 0.0f;
				m_Pvy = -550.0f;
				m_Psize = -150.0f;

				//�ړ����x�������l�ɖ߂��B
				m_speed = INI_SPEED;
			}
		}
		else if (m_Evx < 0.0f)
		{
			//�e�f���A�X�y�V�����Z�A�C�R���A�߂�{�^���A
			//�{�X�o���x�����b�Z�[�W�������ꂼ���ʊO�Ɉړ�������
			m_Evx += m_speed;			//�ړ����x�͋��ʂ̕ϐ����g���A�G�f������ɐݒ肵�Ă���B
			m_Pvx -= m_speed * 0.37;	//�Ⴆ�΃v���C���[�f���͓G�f���قǑ傫���ړ������ł͂Ȃ��ׁA
			m_Pvy += m_speed * 0.37;	//0.37�{�̒l���ړ����x�ɉ��Z���āA�ړ��ʂ𒲐߂��Ă���B
			m_Svy += m_speed * 0.37;
			m_Bvx -= m_speed * 0.065;
			m_Bvy -= m_speed * 0.065;

			m_warning_message_y[0] -= m_speed * 0.1;
			m_warning_message_y[1] -= m_speed * 0.1;

			//�{�X�f���o�����A�ȉ��̏������s��
			if (m_destroy_count == 4)
			{
				m_Boss_vx[2] += m_speed * 0.91;
			}

			//���X�ɏ�L�I�u�W�F�N�g�̉�ʊO�ړ����x�𑝉�������
			m_speed /= 0.956f;
		}

		return;
	}
	//���퓬��ʈڍs���o
	else if (m_Go_flag == true)
	{
		if (m_black_star_effect_size >= 1400.0f)
		{
			//���摜����ʑS�̂𕢂���������A���L�̌��j�t���O���������s
			//���̌�A�퓬��ʂփV�[���ڍs����B

			//�ēx���̐퓬������ʂɖ߂��Ă��遁���ݒ��킷��G�f�������j�����Ƃ������B
			//���ׁ̈A���̃^�C�~���O�Ŋ��Ɍ��j�t���O��true�ɂ��Ă����B
			//�����������킷��̂��{�X�f���̏ꍇ�A�ȉ��̏������΂��B
			//�{�X�f�����j��A�G�̌��j��Ԃ����ɖ߂�����A�X�e�[�W��i�߂鏈����
			//ObjFightClear�ōs���Ă���B
			if (m_destroy_count != 4)
			{
				g_destroy_progress[g_Challenge_enemy] = true;
			}

			Scene::SetScene(new CSceneFight());//�퓬��ʂփV�[���ڍs
		}
		else if (m_black_star_effect_size < 1400.0f)
		{
			//��ʒ������N�_�Ƃ��āA���̉摜�����X�Ɋg��
			//���̂܂܉�ʑS�̂𕢂������B
			m_black_star_effect_size += 20.0f;
		}


		return;
	}



	//������\���̏���
	if (m_is_operatable == true)
	{
		//�}�E�X�̈ʒu���擾
		m_mou_x = (float)Input::GetPosX();
		m_mou_y = (float)Input::GetPosY();
		//�}�E�X�̃{�^���̏��
		m_mou_r = Input::GetMouButtonR();
		m_mou_l = Input::GetMouButtonL();


		//���ŏI�m�F�E�C���h�E�\�����̏���
		if (m_finalcheck_f == true)
		{
			//�ŏI�m�F[�͂�]�{�^��
			if (410 < m_mou_x && m_mou_x < 502 && 407 < m_mou_y && m_mou_y < 450)
			{
				m_Yes_Button_color = 1.0f;

				//���N���b�N���ꂽ��ڍs�J�n�t���O�𗧂āA
				//���o�������Ȃ���A�퓬��ʂɃV�[���ڍs����
				//���N���b�N���͎�
				if (m_mou_l == true)
				{
					//���N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
					if (m_key_lf == true)
					{
						m_key_lf = false;

						m_Yes_Button_color = 0.0f;

						//�ڍs�J�n�t���O����
						m_Go_flag = true;

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
					//�E�C���h�E������A�����Ė߂�{�^������͏o���Ȃ��悤�ɂ���
					m_key_rf = false;

					m_No_Button_color = 0.0f;

					//�ŏI�m�F�E�C���h�E���\���ɂ���
					m_finalcheck_f = false;
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

		//�߂�{�^�����N���b�N�A�������͉E�N���b�N���鎖�Ńz�[����ʂɖ߂�
		if (10 < m_mou_x && m_mou_x < 60 && 10 < m_mou_y && m_mou_y < 60 || m_mou_r == true)
		{
			m_Back_Button_color = 1.0f;

			//���ڍs�J�n�t���O�𗧂āA�z�[����ʂ։��o�������Ȃ���V�[���ڍs
			//�E�N���b�N���͎�
			if (m_mou_r == true)
			{
				//�ŏI�m�F�E�C���h�E����E�N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
				if (m_key_rf == true)
				{
					//�ڍs�J�n�t���O����
					m_Back_flag = true;
				}
			}
			//���N���b�N���͎�
			else if (m_mou_l == true)
			{
				//���N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
				if (m_key_lf == true)
				{
					m_key_lf = false;

					//�ڍs�J�n�t���O����
					m_Back_flag = true;
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


		//�G�f��1(������1�Ԗڂ̓G�f��)[�����j���̂ݑI���\]
		if (147 < m_mou_x && m_mou_x < 346 && 187 < m_mou_y && m_mou_y < 383 && g_destroy_progress[0] == false)
		{
			//���G�f���ڍא�����\��
			Enemy_message(0);//�G�f���ڍא����\���֐����Ăяo��
		}

		//�G�f��2(������2�Ԗڂ̓G�f��)[�����j���̂ݑI���\]
		else if (446 < m_mou_x && m_mou_x < 544 && 158 < m_mou_y && m_mou_y < 255 && g_destroy_progress[1] == false)
		{
			//���G�f���ڍא�����\��
			Enemy_message(1);//�G�f���ڍא����\���֐����Ăяo��
		}

		//�G�f��3(������3�Ԗڂ̓G�f��)[�����j���̂ݑI���\]
		else if (744 < m_mou_x && m_mou_x < 941 && 137 < m_mou_y && m_mou_y < 334 && g_destroy_progress[2] == false)
		{
			//���G�f���ڍא�����\��
			Enemy_message(2);//�G�f���ڍא����\���֐����Ăяo��
		}

		//�G�f��4(������4�Ԗڂ̓G�f��)[�����j���̂ݑI���\]
		else if (892 < m_mou_x && m_mou_x < 1139 && 433 < m_mou_y && m_mou_y < 679 && g_destroy_progress[3] == false)
		{
			//���G�f���ڍא�����\��
			Enemy_message(3);//�G�f���ڍא����\���֐����Ăяo��
		}

		//�{�X�f��[�{�X�f���o�����̂ݑI���\]
		else if (426 < m_mou_x && m_mou_x < 767 && 123 < m_mou_y && m_mou_y < 460 && m_destroy_count == 4)
		{
			//���G�f���ڍא�����\��
			Enemy_message(4);//�G�f���ڍא����\���֐����Ăяo��
		}

		//�X�y�V�����Z(Explosion)
		else if (377 < m_mou_x && m_mou_x < 455 && 579 < m_mou_y && m_mou_y < 637)
		{
			//���X�y�V�����Z�ڍא�����\��
			Special_message(0);//�X�y�V�����Z�ڍא����\���֐����Ăяo��
		}

		//�X�y�V�����Z(Fracture_Ray)
		else if (471 < m_mou_x && m_mou_x < 549 && 579 < m_mou_y && m_mou_y < 637)
		{
			//���X�y�V�����Z�ڍא�����\��
			Special_message(1);//�X�y�V�����Z�ڍא����\���֐����Ăяo��
		}

		//�X�y�V�����Z(Immortality)
		else if (565 < m_mou_x && m_mou_x < 643 && 579 < m_mou_y && m_mou_y < 637)
		{
			//���X�y�V�����Z�ڍא�����\��
			Special_message(2);//�X�y�V�����Z�ڍא����\���֐����Ăяo��
		}

		//�X�y�V�����Z(���~�b�g�u���C�N)
		else if (660 < m_mou_x && m_mou_x < 737 && 579 < m_mou_y && m_mou_y < 637)
		{
			//���X�y�V�����Z�ڍא�����\��
			Special_message(3);//�X�y�V�����Z�ڍא����\���֐����Ăяo��
		}

		//�X�y�V�����Z(�X�e���C�h���^)
		else if (754 < m_mou_x && m_mou_x < 831 && 579 < m_mou_y && m_mou_y < 637)
		{
			//���X�y�V�����Z�ڍא�����\��
			Special_message(4);//�X�y�V�����Z�ڍא����\���֐����Ăяo��
		}

		//��L�͈̔͊O�Ƀ}�E�X�J�[�\��������ꍇ�A
		//�ڍא���(�G�f���A�X�y�V�����Z)���\���ɂ���
		else
		{
			m_detail_message_alpha = 0.0f;//�ڍא���(�G�f���A�X�y�V�����Z)���\��
		}


		return;
	}



	//���{�X�f���o�����o
	//�{�X�f���o���J�E���g��0�ɂȂ������A�ȉ��̏��������s
	if (m_boss_emerge_staging_f == true)
	{
		if (m_destroy_count == 4)
		{
			//���b�Z�[�W���e��ύX�����ׁA
			//�x�����b�Z�[�W�����X�ɕ\��������
			//���S�ɕ\����A����\�ȏ�Ԃɂ���B
			if (m_warning_message_alpha >= 1.0f)
			{
				m_is_operatable = true;
			}
			else if (m_warning_message_alpha < 1.0f)
			{
				m_warning_message_alpha += 0.02f;
			}
		}
		else if (m_Boss_vy[2] < 0.0f)
		{
			//��ʒ����܂ňړ�������A�ȉ���2�̏����𓯎��ɍs���B

			//�x�����b�Z�[�W�����X�ɔ�\���ɂ���
			//���S�ɔ�\����A�G�f�����j����4�ɐݒ肷�鎖��
			//�{�X�o���x�����b�Z�[�W���e��ς���B
			//�܂��A�ړ����x��ۑ����Ă������̂ɖ߂�
			if (m_warning_message_alpha <= 0.0f)
			{
				m_destroy_count = 4;
				m_speed = m_save_speed;
			}
			else if (m_warning_message_alpha > 0.0f)
			{
				m_warning_message_alpha -= 0.01f;
			}

			//�{�X�f���`�挳�؂���ʒu�����X�ɕύX���A�ŏI�I�Ɍ��������Ԃɂ���
			if (m_warning_message_alpha <= 0.0f)
			{
				if (g_Stage_progress == 1)//�X�e�[�W1�̃p���_�f���̎��̂݁A�ȉ��̏��������s�B
				{
					m_Boss_clip_pos_y = 128.0f;//���ʂ���������
				}
			}
			else if (m_warning_message_alpha <= 0.4f)
			{
				m_Boss_clip_pos_x = 256.0f;
			}
			else if (m_warning_message_alpha <= 0.8f)
			{
				m_Boss_clip_pos_x = 128.0f;
			}
			
		}
		else if (m_Boss_clip_pos_x == 0.0f)
		{
			//�{�X�f���̏���������A
			//�{�X�f������ʊO(�E��)�����ʒ����ւƓG�f���̏��ʂ�Ȃ���ʉ߁B
			//�ʉ߃^�C�~���O�œG�f�����\���ɂ��A�H�ׂĂ���悤�ɉ��o�B

			//�{�X�f�����G�f���̏��ʉ߂��A
			//�B�����^�C�~���O�Ō��j�t���O�𗧂Ă�
			if (m_Boss_vy[2] <= 270.0f)
			{
				g_destroy_progress[3] = true;
			}

			//�{�X�f��3�ړ�
			m_Boss_vx[2] -= m_speed;
			m_Boss_vy[2] -= m_speed * 0.65;

			//���X�Ƀ{�X�f���̈ړ����x������������
			m_speed *= 0.951f;
		}
		else if (m_Boss_vx[1] >= 1520.0f)
		{
			//�����̉��o�̏���
			//�{�X�f���ʒuY��K�؂Ȉʒu�Ɉړ�������
			m_Boss_vy[2] = 650.0f;

			//�{�X�f���`�挳�؂���ʒu��K�؂Ȉʒu�ɐݒ肵�A�����J������Ԃɂ���
			m_Boss_clip_pos_x = 0.0f;

			//���݂̈ړ����x��ʕϐ��ɕۑ�������A�ړ����x������������
			m_save_speed = m_speed;
			m_speed = INI_SPEED;
		}
		else if (m_Boss_vx[0] <= -1420.0f)
		{
			//���o�p�̃{�X�f��1����ʊO(��)�Ɉړ�������A
			//���o�p�̃{�X�f��2����ʊO(��)�����ʊO(�E)�ւƓG�f��2�̏��ʂ�Ȃ���ʉ߁B
			//�ʉ߃^�C�~���O�œG�f�������ꂼ���\���ɂ��A�H�ׂĂ���悤�ɉ��o�B

			//�{�X�f�����G�f���̏��ʉ߂��A
			//�B�����^�C�~���O�Ō��j�t���O�𗧂Ă�
			if (m_Boss_vx[1] >= 1010.0f)
			{
				g_destroy_progress[2] = true;
			}
			else if (m_Boss_vx[1] >= 380.0f)
			{
				g_destroy_progress[0] = true;
			}

			//�{�X�f��2�ړ�
			m_Boss_vx[1] += 20.0f;
			m_Boss_vy[1] -= 2.0f;
		}
		else if (m_Boss_vx[0] > -1420.0f)
		{
			//���o�p�̃{�X�f��1����ʊO(�E)�����ʊO(��)�ւƓG�f���̏��ʂ�Ȃ���ʉ߁B
			//�ʉ߃^�C�~���O�œG�f�����\���ɂ��A�H�ׂĂ���悤�ɉ��o�B

			//�{�X�f�����G�f���̏��ʉ߂��A
			//�B�����^�C�~���O�Ō��j�t���O�𗧂Ă�
			if (m_Boss_vx[0] <= -820.0f)
			{
				g_destroy_progress[1] = true;
			}

			//�{�X�f��1�ړ�
			m_Boss_vx[0] -= 20.0f;
			m_Boss_vy[0] -= 5.0f;
		}
	}

	//���퓬������ʊJ�n���o
	//�퓬������ʂɓ���ƁA�܂��ȉ��̏��������s�����
	else if (m_warning_message_y[0] < 30.0f)
	{
		//�x�����b�Z�[�W�ړ�������A
		//�{�X�f���o���J�E���g��0�ł���΁A�{�X�f���o�����o�Ɉڍs����B
		//�����łȂ���΁A����\�ȏ�Ԃɂ���B
		//���{�X���o�����Ɍ��Ă���ꍇ������\�ȏ�Ԃɂ���B
		if (3 - m_destroy_count == 0)
		{
			m_boss_emerge_staging_f = true;
		}
		else
		{
			m_is_operatable = true;
		}
	}
	else if (m_warning_message_alpha >= 1.2f)
	{
		//�x�����b�Z�[�W���S�\����A
		//�x�����b�Z�[�W�T�C�Y�����X�ɏ��������Ȃ���A
		//��ʏ㕔�ւƌx�����b�Z�[�W���ړ�������

		//�{�X�f���o�����̏���
		if (m_destroy_count == 4)
		{
			m_warning_message_x[0] += 7.35f;
		}
		//����ȊO�̎��̏���
		else
		{
			m_warning_message_x[0] += 1.5f;
		}

		m_warning_message_y[0] -= 5.0f;
		m_warning_message_x[1] += 8.5f;
		m_warning_message_y[1] -= 7.9f;
		m_warning_message_size -= 1.0f;
	}
	else if (m_Evx <= -1100.0f)
	{
		//��ʓ��ړ�������A
		//�x�����b�Z�[�W�����X�ɕ\��������
		//1.0f�ȏ�ɂ���Ӗ��́A�t�H���g�ړ��܂ł̎��Ԓ��߂����łɍs���Ă���ׁB
		if (m_warning_message_alpha < 1.2f)
		{
			m_warning_message_alpha += 0.01f;
		}
	}
	else if (m_Evx > -1100.0f)
	{
		//�e�f���A�X�y�V�����Z�A�C�R���A�߂�{�^������
		//���ꂼ���ʊO����ʓ��Ɉړ�������
		m_Evx -= m_speed;			//�ړ����x�͋��ʂ̕ϐ����g���A�G�f������ɐݒ肵�Ă���B
		m_Pvx += m_speed * 0.37;	//�Ⴆ�΃v���C���[�f���͓G�f���قǑ傫���ړ������ł͂Ȃ��ׁA
		m_Pvy -= m_speed * 0.37;	//0.37�{�̒l���ړ����x�ɉ��Z���āA�ړ��ʂ𒲐߂��Ă���B
		m_Svy -= m_speed * 0.37;
		m_Bvx += m_speed * 0.065;
		m_Bvy += m_speed * 0.065;

		//�{�X�f���o�����A�ȉ��̏������s��
		if (m_destroy_count == 4)
		{
			m_Boss_vx[2] -= m_speed * 0.91;
			m_warning_message_x[0] = -130.0f;//�{�X�o���x�����b�Z�[�W�̏���X�ʒu��ύX����
		}

		//���X�ɏ�L�I�u�W�F�N�g�̉�ʓ��ړ����x������������
		m_speed *= 0.956f;
	}
}

//�h���[
void CObjPreparation::Draw()
{
	//���`��J���[���  R=RED  G=Green  B=Blue A=alpha(���ߏ��)
	//�ԐF
	float red[4] = { 1.0f,0.0f,0.0f,1.0f };

	//���F
	float black[4] = { 0.0f,0.0f,0.0f,1.0f };

	//�߂�{�^���p
	float back[4] = { m_Back_Button_color,m_Back_Button_color,m_Back_Button_color,1.0f };

	//�{�X�o���x�����b�Z�[�W�p
	float warning_message[4] = { 1.0f,0.0f,0.0f,m_warning_message_alpha };

	//�X�y�V�����Z�A�C�R���p
	float Special_icon[5][4] =
	{
		{ m_Special_icon_color[0],m_Special_icon_color[0],m_Special_icon_color[0],1.0f },
		{ m_Special_icon_color[1],m_Special_icon_color[1],m_Special_icon_color[1],1.0f },
		{ m_Special_icon_color[2],m_Special_icon_color[2],m_Special_icon_color[2],1.0f },
		{ m_Special_icon_color[3],m_Special_icon_color[3],m_Special_icon_color[3],1.0f },
		{ m_Special_icon_color[4],m_Special_icon_color[4],m_Special_icon_color[4],1.0f },	
	};

	//�ڍא���(�G�f���A�X�y�V�����Z)�E�C���h�E�p
	float detail_message_window[4] = { 1.0f,1.0f,1.0f,m_detail_message_alpha };

	//�ڍא���(�G�f���A�X�y�V�����Z)�t�H���g�p
	float detail_message_font[DETAIL_MES_MAX_FONT_LINE][4] =
	{
		{ 1.0f,0.0f,0.0f,m_detail_message_alpha },//1�s�ڂ͐ԐF
		{ 0.0f,0.0f,0.0f,m_detail_message_alpha },//2�s�ڂ͍��F
		{ 0.0f,0.0f,0.0f,m_detail_message_alpha },//3�s�ڂ͍��F
		{ 0.0f,0.0f,1.0f,m_detail_message_alpha },//4�s�ڂ͐F
	};

	//�ŏI�m�F[�͂�]�{�^���p
	float Yes[4] = { m_Yes_Button_color,0.0f,0.0f,1.0f };

	//�ŏI�m�F[������]�{�^���p
	float No[4] = { 0.0f,0.0f,m_No_Button_color,1.0f };

	//���̑��摜�p
	float d[4] = { 1.0f,1.0f,1.0f,1.0f };


	//���t�H���g����
	//���{�X�f���o���J�E���g
	wchar_t Until_fight_boss_count[2][14];									//14�������i�[�\�ȕ����z���2�錾
	//�{�X�f���o����
	if (m_destroy_count == 4)
	{
		swprintf_s(Until_fight_boss_count[0], L"�@�@�@����Șf�� �o����!");	//���̕����z��ɕ����f�[�^������
		swprintf_s(Until_fight_boss_count[1], L"");							//�����f�[�^���N���A����
	}
	//����ȊO�̎�
	else
	{
		swprintf_s(Until_fight_boss_count[0], L"����Șf�� �ڋ߂܂�");			 //���̕����z��ɕ����f�[�^������
		swprintf_s(Until_fight_boss_count[1], L"���� %d��", 3 - m_destroy_count);//���̕����z��ɕ����f�[�^������
	}



	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu

	//���w�i�\��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 960.0f;
	src.m_bottom = 638.0f;

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 1200.0f;
	dst.m_bottom = 700.0f;
	Draw::Draw(0, &src, &dst, d, 0.0f);

	//���߂�{�^���\��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	dst.m_top = -60.0f + m_Bvy;
	dst.m_left = -60.0f + m_Bvx;
	dst.m_right = -10.0f + m_Bvx;
	dst.m_bottom = -10.0f + m_Bvy;
	Draw::Draw(56, &src, &dst, back, 0.0f);

	//�����j���̂ݕ\��
	if (g_destroy_progress[1] == false)
	{
		//���G�f��2(������2�Ԗڂ̓G�f��)�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = INI_PLANET;
		src.m_bottom = INI_PLANET;

		dst.m_top = INI_ENEMY_Y_POS - 30.0f;
		dst.m_left = INI_ENEMY_X_POS + 300.0f + m_Evx;
		dst.m_right = INI_ENEMY_X_POS + 400.0f + m_Evx;
		dst.m_bottom = INI_ENEMY_Y_POS + 70.0f;
		Draw::Draw(2 + 5 * (g_Stage_progress - 1), &src, &dst, d, 0.0f);
	}

	//���{�X�f��1�\��(���o�p)
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = -128.0f;
	src.m_bottom = 128.0f;

	dst.m_top = 360.0f + m_Boss_vy[0];
	dst.m_left = 1260.0f + m_Boss_vx[0];
	dst.m_right = 1410.0f + m_Boss_vx[0];
	dst.m_bottom = 510.0f + m_Boss_vy[0];
	Draw::Draw(5 + 5 * (g_Stage_progress - 1), &src, &dst, d, 0.0f);

	//�����j���̂ݕ\��
	if (g_destroy_progress[0] == false)
	{
		//���G�f��1(������1�Ԗڂ̓G�f��)�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = INI_PLANET;
		src.m_bottom = INI_PLANET;

		dst.m_top = INI_ENEMY_Y_POS;
		dst.m_left = INI_ENEMY_X_POS + m_Evx;
		dst.m_right = INI_ENEMY_X_POS + 200.0f + m_Evx;
		dst.m_bottom = INI_ENEMY_Y_POS + 200.0f;
		Draw::Draw(1 + 5 * (g_Stage_progress - 1), &src, &dst, d, 0.0f);
	}

	//�����j���̂ݕ\��
	if (g_destroy_progress[2] == false)
	{
		//���G�f��3(������3�Ԗڂ̓G�f��)�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = INI_PLANET;
		src.m_bottom = INI_PLANET;

		dst.m_top = INI_ENEMY_Y_POS - 50.0f;
		dst.m_left = INI_ENEMY_X_POS + 600.0f + m_Evx;
		dst.m_right = INI_ENEMY_X_POS + 800.0f + m_Evx;
		dst.m_bottom = INI_ENEMY_Y_POS + 150.0f;
		Draw::Draw(3 + 5 * (g_Stage_progress - 1), &src, &dst, d, 0.0f);
	}

	//���{�X�f��2�\��(���o�p)
	src.m_top = 0.0f;
	src.m_left = 256.0f;
	src.m_right = 384.0f;
	src.m_bottom = 128.0f;

	dst.m_top = 200.0f + m_Boss_vy[1];
	dst.m_left = -310.0f + m_Boss_vx[1];
	dst.m_right = -10.0f + m_Boss_vx[1];
	dst.m_bottom = 500.0f + m_Boss_vy[1];
	Draw::Draw(5 + 5 * (g_Stage_progress - 1), &src, &dst, d, 0.0f);

	//�����j���̂ݕ\��
	if (g_destroy_progress[3] == false)
	{
		//���G�f��4(������4�Ԗڂ̓G�f��)�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = INI_PLANET;
		src.m_bottom = INI_PLANET;

		dst.m_top = INI_ENEMY_Y_POS + 250.0f;
		dst.m_left = INI_ENEMY_X_POS + 750.0f + m_Evx;
		dst.m_right = INI_ENEMY_X_POS + 1000.0f + m_Evx;
		dst.m_bottom = INI_ENEMY_Y_POS + 500.0f;
		Draw::Draw(4 + 5 * (g_Stage_progress - 1), &src, &dst, d, 0.0f);
	}

	//���{�X�f��3�\��
	src.m_top = m_Boss_clip_pos_y;
	src.m_left = 0.0f - m_Boss_clip_pos_x;
	src.m_right = -(INI_PLANET) - m_Boss_clip_pos_x;
	src.m_bottom = INI_PLANET + m_Boss_clip_pos_y;

	dst.m_top = 100.0f + m_Boss_vy[2];
	dst.m_left = 1400.0f + m_Boss_vx[2];
	dst.m_right = 1800.0f + m_Boss_vx[2];
	dst.m_bottom = 500.0f + m_Boss_vy[2];
	Draw::Draw(5 + 5 * (g_Stage_progress - 1), &src, &dst, d, 0.0f);

	//���v���C���[�f���\��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 62.0f;
	src.m_bottom = 62.0f;

	dst.m_top = 800.0f + m_Pvy;
	dst.m_left = -500.0f + m_Pvx;
	dst.m_right = -50.0f + m_Pvx + m_Psize;
	dst.m_bottom = 1250.0f + m_Pvy + m_Psize;
	Draw::Draw(63, &src, &dst, d, 0.0f);

	//���X�y�V�����Z�I���E�C���h�E�\��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 500.0f;
	src.m_bottom = 200.0f;

	dst.m_top = 900.0f + m_Svy;
	dst.m_left = 360.0f;
	dst.m_right = 860.0f;
	dst.m_bottom = 1100.0f + m_Svy;
	Draw::Draw(62, &src, &dst, d, 0.0f);

	//���X�y�V�����Z�A�C�R���W�\��
	for (int i = 0; i < 5; i++)
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 100.0f;
		src.m_bottom = 100.0f;

		dst.m_top = 985.0f + m_Svy;
		dst.m_left = 380.0f + i * 95.0f;
		dst.m_right = 460.0f + i * 95.0f;
		dst.m_bottom = 1065.0f + m_Svy;
		Draw::Draw(57 + i, &src, &dst, Special_icon[i], 0.0f);
	}



	//���t�H���g�\��
	//�X�y�V�����Z�I��
	Font::StrDraw(L"�X�y�V�����Z�I��", 445.0f, 915.0f + m_Svy, 40.0f, black);

	//�{�X�o���x�����b�Z�[�W
	Font::StrDraw(Until_fight_boss_count[0], m_warning_message_x[0], m_warning_message_y[0], m_warning_message_size, warning_message);
	Font::StrDraw(Until_fight_boss_count[1], m_warning_message_x[1] + 250.0f, m_warning_message_y[1] + 130.0f, m_warning_message_size, warning_message);


	//���ڍא���(�G�f���A�X�y�V�����Z)���b�Z�[�W�\��
	//���E�C���h�E�\�� 
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	dst.m_top = m_mou_y + m_detail_message_window_top;
	dst.m_left = m_mou_x + m_detail_message_window_left;
	dst.m_right = m_mou_x + m_detail_message_window_right;
	dst.m_bottom = m_mou_y + m_detail_message_window_bottom;
	Draw::Draw(55, &src, &dst, detail_message_window, 0.0f);

	//���t�H���g�\��
	for (int i = 0; i < DETAIL_MES_MAX_FONT_LINE; i++)
	{
		Font::StrDraw(m_detail_message[i], m_mou_x + m_detail_message_font_x, m_mou_y + m_detail_message_font_y + i * 40.0f, 25.0f, detail_message_font[i]);
	}



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
		Draw::Draw(55, &src, &dst, d, 0.0f);

		//���t�H���g�\��
		//�ŏI�m�F���b�Z�[�W
		Font::StrDraw(L"�򂤁H", 460.0f, 250.0f, 100.0f, black);
		Font::StrDraw(L"�͂�", 410.0f, 410.0f, 50.0f, Yes);
		Font::StrDraw(L"������", 650.0f, 410.0f, 50.0f, No);
	}



	//���퓬��ʈڍs���o(����)�\��
	//���ڍs���o�܂ŕ`���\���ʒu�̐ݒ��A��\����ԂɂȂ�B
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 256.0f;
	src.m_bottom = 256.0f;

	dst.m_top = 350.0f - m_black_star_effect_size;
	dst.m_left = 600.0f - m_black_star_effect_size;
	dst.m_right = 600.0f + m_black_star_effect_size;
	dst.m_bottom = 350.0f + m_black_star_effect_size;
	Draw::Draw(50, &src, &dst, d, 0.0f);




	//�f�o�b�O�p���}�E�X�ʒu�\��
	wchar_t str[256];
	swprintf_s(str, L"x=%f,y=%f", m_mou_x, m_mou_y);
	Font::StrDraw(str, 20.0f, 20.0f, 12.0f, d);
}

//---Enemy_message�֐�
//����1�@int enemy_id	:�G�f�����ʔԍ�(0:������1�Ԗڂ̓G�f���@1:������2�Ԗڂ̓G�f���@2:������3�Ԗڂ̓G�f���@3:������4�Ԗڂ̓G�f���@4:�{�X�f��)
//�����e
//�}�E�X�őI�����Ă���G�f�������ł��邩�����ʂ��A
//����ɑΉ�����G�f���ڍא�����\������B
void CObjPreparation::Enemy_message(int enemy_id)
{
	//���ȉ��͊e�G�f�����ɈقȂ�l��������ʏ���
	if (enemy_id == 0)
	{
		//�G�f���ڍא����E�C���h�E�̃T�C�Y��ݒ�
		m_detail_message_window_top = -85.0f;
		m_detail_message_window_left = 20.0f;
		m_detail_message_window_right = 320.0f;
		m_detail_message_window_bottom = 85.0f;

		//�G�f���ڍא����t�H���g�̈ʒu��ݒ�
		m_detail_message_font_x = 33.0f;
		m_detail_message_font_y = -73.0f;
	}
	else if (enemy_id == 3)
	{
		//�G�f���ڍא����E�C���h�E�̃T�C�Y��ݒ�
		m_detail_message_window_top = -85.0f;
		m_detail_message_window_left = 0.0f;
		m_detail_message_window_right = -300.0f;
		m_detail_message_window_bottom = 85.0f;

		//�G�f���ڍא����t�H���g�̈ʒu��ݒ�
		m_detail_message_font_x = -288.0f;
		m_detail_message_font_y = -73.0f;
	}
	else  //(enemy_id == 1 || enemy_id == 2 || enemy_id == 4)
	{
		//�G�f���ڍא����E�C���h�E�̃T�C�Y��ݒ�
		m_detail_message_window_top = 20.0f;
		m_detail_message_window_left = -150.0f;
		m_detail_message_window_right = 150.0f;
		m_detail_message_window_bottom = 190.0f;

		//�G�f���ڍא����t�H���g�̈ʒu��ݒ�
		m_detail_message_font_x = -138.0f;
		m_detail_message_font_y = 33.0f;
	}

	//���ȉ��͊e�G�f���֌W�Ȃ��s�����ʏ���
	//�G�f���ڍא����t�H���g�ݒ�
	swprintf_s(m_detail_message[0], m_Enemy_detail_message[g_Stage_progress - 1][enemy_id][0]);//�����z��ɕ����f�[�^������
	swprintf_s(m_detail_message[1], m_Enemy_detail_message[g_Stage_progress - 1][enemy_id][1]);//�����z��ɕ����f�[�^������
	swprintf_s(m_detail_message[2], m_Enemy_detail_message[g_Stage_progress - 1][enemy_id][2]);//�����z��ɕ����f�[�^������
	swprintf_s(m_detail_message[3], m_Enemy_detail_message[g_Stage_progress - 1][enemy_id][3]);//�����z��ɕ����f�[�^������

	m_detail_message_alpha = 1.0f;//�G�f���ڍא�����\��


	//���N���b�N���ꂽ��t���O�𗧂āA�ŏI�m�F�E�C���h�E���J��
	if (m_mou_l == true)
	{
		//���N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
		if (m_key_lf == true)
		{
			m_key_lf = false;

			m_detail_message_alpha = 0.0f;//�G�f���ڍא������\���ɂ���

			g_Challenge_enemy = enemy_id;//�}�E�X�I�𒆂̓G�f�����ʔԍ����擾

			m_finalcheck_f = true;//�ŏI�m�F�E�C���h�E��\������

			return;
		}
	}
	else
	{
		m_key_lf = true;
	}
}

//---Special_message�֐�
//����1�@int special_id	:�X�y�V�����Z�A�C�R�����ʔԍ�(0:Explosion�@1:Fracture_Ray�@2:Immortality�@3:���~�b�g�u���C�N�@4:�X�e���C�h���^)
//�����e
//�}�E�X�őI�����Ă���X�y�V�����Z�A�C�R�������ł��邩�����ʂ��A
//����ɑΉ�����X�y�V�����Z�ڍא�����\������B
void CObjPreparation::Special_message(int special_id)
{
	//���X�y�V�����Z�A�C�R�������F(���K��)�̎��̏���
	if (m_Special_icon_color[special_id] == 0.0f)
	{
		//�X�y�V�����Z�ڍא����t�H���g�ݒ�
		swprintf_s(m_detail_message[0], L"");		//�����f�[�^���N���A����
		swprintf_s(m_detail_message[1], L"���K��"); //�����z��ɕ����f�[�^������
		swprintf_s(m_detail_message[2], L"");		//�����f�[�^���N���A����
		swprintf_s(m_detail_message[3], L"");		//�����f�[�^���N���A����

		//�X�y�V�����Z�ڍא����E�C���h�E�̃T�C�Y��ݒ�
		m_detail_message_window_top = -50.0f;
		m_detail_message_window_left = -50.0f;
		m_detail_message_window_right = 50.0f;
		m_detail_message_window_bottom = 0.0f;

		//�X�y�V�����Z�ڍא����t�H���g�̈ʒu��ݒ�
		m_detail_message_font_x = -38.0f;
		m_detail_message_font_y = -78.0f;
	}
	//���X�y�V�����Z�A�C�R�����D�F(�N���b�N�ő�����)�A�������͔��F(������)�̎��̏���
	else  //(m_Special_icon_color[special_id] == 0.4f || m_Special_icon_color[special_id] == 1.0f)
	{
		//���ȉ��͊D�F�A���F�̂ǂ���ł��s�����ʏ���
		//�X�y�V�����Z�ڍא����t�H���g�ݒ�
		if (special_id == 0)
		{
			swprintf_s(m_detail_message[0], L"Explosion");				//�����z��ɕ����f�[�^������
			swprintf_s(m_detail_message[1], L"����̘f����");			//�����z��ɕ����f�[�^������
			swprintf_s(m_detail_message[2], L"�Œ�_���[�W��^����");	//�����z��ɕ����f�[�^������
		}
		else if (special_id == 1)
		{
			swprintf_s(m_detail_message[0], L"Fracture Ray");			//�����z��ɕ����f�[�^������
			swprintf_s(m_detail_message[1], L"�I�����C�����");			//�����z��ɕ����f�[�^������
			swprintf_s(m_detail_message[2], L"����|�b�h����j�󂷂�");	//�����z��ɕ����f�[�^������
		}
		else if (special_id == 2)
		{
			swprintf_s(m_detail_message[0], L"Immortality");//�����z��ɕ����f�[�^������
			swprintf_s(m_detail_message[1], L"��10�b��");	//�����z��ɕ����f�[�^������
			swprintf_s(m_detail_message[2], L"���G�ƂȂ�");	//�����z��ɕ����f�[�^������
		}
		else if (special_id == 3)
		{
			swprintf_s(m_detail_message[0], L"���~�b�g�u���C�N");		//�����z��ɕ����f�[�^������
			swprintf_s(m_detail_message[1], L"20�b�ԃ|�b�h���Y���x");	//�����z��ɕ����f�[�^������
			swprintf_s(m_detail_message[2], L"�~�T�C�����Y���xUP");		//�����z��ɕ����f�[�^������
		}
		else  //(special_id == 4)
		{
			swprintf_s(m_detail_message[0], L"�X�e���C�h���^");		//�����z��ɕ����f�[�^������
			swprintf_s(m_detail_message[1], L"�o������");			//�����z��ɕ����f�[�^������
			swprintf_s(m_detail_message[2], L"�|�b�h5�@�̍U����UP");//�����z��ɕ����f�[�^������
		}
		
		//�X�y�V�����Z�ڍא����E�C���h�E�̃T�C�Y��ݒ�
		m_detail_message_window_top = -170.0f;
		m_detail_message_window_left = -150.0f;
		m_detail_message_window_right = 150.0f;
		m_detail_message_window_bottom = 0.0f;

		//�X�y�V�����Z�ڍא����t�H���g�̈ʒu��ݒ�
		m_detail_message_font_x = -138.0f;
		m_detail_message_font_y = -158.0f;


		//���ȉ��̓X�y�V�����Z�A�C�R�����D�F(�N���b�N�ő�����)�̎��̂ݍs������
		if (m_Special_icon_color[special_id] == 0.4f)
		{
			swprintf_s(m_detail_message[3], L"�N���b�N�ő�����");//�����z��ɕ����f�[�^������

			//���N���b�N���ꂽ��}�E�X�őI�𒆂̃X�y�V�����Z�𑕔�����
			if (m_mou_l == true)
			{
				//���N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
				if (m_key_lf == true)
				{
					m_key_lf = false;

					//��������Ԃ̎��͈ȉ��̏������΂�
					if (g_Special_equipment != 0)
					{
						//���ݑ������̃X�y�V�����Z�A�C�R���̃J���[���D�F�ɂ���
						m_Special_icon_color[g_Special_equipment - 1] = 0.4f;
					}

					//�}�E�X�I�𒆂̃X�y�V�����Z�𑕔�����
					g_Special_equipment = special_id + 1;

					//�}�E�X�I�𒆂̃X�y�V�����Z�A�C�R���̃J���[�𔒐F�ɂ���
					m_Special_icon_color[g_Special_equipment - 1] = 1.0f;
				}
			}
			else
			{
				m_key_lf = true;
			}
		}

		//���ȉ��̓X�y�V�����Z�A�C�R�������F(������)�̎��̂ݍs������
		else  //(m_Special_icon_color[special_id] == 1.0f)
		{
			swprintf_s(m_detail_message[3], L"������");//�����z��ɕ����f�[�^������

			//���N���b�N���ꂽ�猻�ݑ������̃X�y�V�����Z���O���A��������Ԃɂ���
			if (m_mou_l == true)
			{
				//���N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
				if (m_key_lf == true)
				{
					m_key_lf = false;

					//���ݑ������̃X�y�V�����Z�A�C�R���̃J���[���D�F�ɂ���
					m_Special_icon_color[g_Special_equipment - 1] = 0.4f;

					//��������Ԃɂ���
					g_Special_equipment = 0;
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
	}


	m_detail_message_alpha = 1.0f;//�X�y�V�����Z�ڍא�����\��
}
