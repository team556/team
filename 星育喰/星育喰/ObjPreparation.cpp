//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\Audio.h"

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
#define INI_PLANET (300.0f)

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
	m_warning_message_skip_f = false;

	for (int i = 0; i < 3; i++)
	{
		m_Boss_vx[i] = 0.0f;
		m_Boss_vy[i] = 0.0f;
	}

	m_Boss_clip_pos_x = -1.0f;//0.0f���ƈӐ}���ĂȂ��^�C�~���O�ŏ������ɓ���ׁA�����l��-1.0f�ɂ��鎖�Ō���Ή��B
	//m_Boss_clip_pos_y = 0.0f;

	m_speed = INI_SPEED;
	m_save_speed = 0.0f;

	m_black_star_effect_f = false;
	m_staging_time = 0;
	m_is_operatable = false;

	m_Back_Button_color = INI_COLOR;
	m_Yes_Button_color = 1.0f;
	m_No_Button_color = 1.0f;

	m_Back_flag = false;
	m_Go_flag = false;
	m_boss_emerge_staging_f = false;
	m_finalcheck_f = false;

	m_detail_message_window_top = 0.0f;
	m_detail_message_window_left = 0.0f;
	m_detail_message_window_right = 0.0f;
	m_detail_message_window_bottom = 0.0f;
	m_detail_message_draw_y = 0.0f;

	for (int i = 0; i < DETAIL_MES_MAX_FONT_LINE; i++)
	{
		m_detail_message_clip_right[i] = 0.0f;
		m_detail_message_clip_bottom[i] = 0.0f;
		m_detail_message_draw_right[i] = 0.0f;
	}

	m_detail_message_draw_left = 0.0f;
	m_detail_message_alpha = INI_ALPHA;
	m_level_star_num = 0;

	m_destroy_count = 0;

	//���݂̌��j�����J�E���g
	for (int i = 0; i < 4; i++)
	{
		if (g_destroy_progress[i] == true)
		{
			m_destroy_count++;
		}
	}

	//�`���[�g���A�����̂ݓ��ꏈ��
	if (g_tutorial_progress == 1)
	{
		for (int i = 0; i < 4; i++)
		{
			g_destroy_progress[i] = true;
		}

		m_destroy_count = 4;
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
	//swprintf_s(m_Enemy_detail_message[0][0][0], L"��Փx�@��");//1�s��
	//swprintf_s(m_Enemy_detail_message[0][0][1], L"�擾�\�Ȏ��ށE�Z");//2�s��
	//swprintf_s(m_Enemy_detail_message[0][0][2], L"�؍�50�E�S30");//3�s��
	//swprintf_s(m_Enemy_detail_message[0][0][3], L"Fracture ray");//4�s��
	//swprintf_s(m_Enemy_detail_message[0][0][4], L"�f�B�t�F���X�d��");//5�s��
	////��1�X�e�[�W�@�G�f��2(������2�Ԗڂ̓G�f��)
	//swprintf_s(m_Enemy_detail_message[0][1][0], L"��Փx�@������");//1�s��
	//swprintf_s(m_Enemy_detail_message[0][1][1], L"�擾�\�Ȏ��ށE�Z");//2�s��
	//swprintf_s(m_Enemy_detail_message[0][1][2], L"�v���X�`�b�N40�E�K�X50");//3�s��
	//swprintf_s(m_Enemy_detail_message[0][1][3], L"Expiosion");//4�s��
	//swprintf_s(m_Enemy_detail_message[0][1][4], L"�p���[�d��");//5�s��
	////��1�X�e�[�W�@�G�f��3(������3�Ԗڂ̓G�f��)
	//swprintf_s(m_Enemy_detail_message[0][2][0], L"��Փx�@��������");//1�s��
	//swprintf_s(m_Enemy_detail_message[0][2][1], L"�擾�\�Ȏ��ށE�Z");//2�s��
	//swprintf_s(m_Enemy_detail_message[0][2][2], L"��65�E���A���^��50");//3�s��
	//swprintf_s(m_Enemy_detail_message[0][2][3], L"�X�e���C�h���^");//4�s��
	//swprintf_s(m_Enemy_detail_message[0][2][4], L"�o�����X�d��");//5�s��
	////��1�X�e�[�W�@�G�f��4(������4�Ԗڂ̓G�f��)
	//swprintf_s(m_Enemy_detail_message[0][3][0], L"��Փx�@����");//1�s��
	//swprintf_s(m_Enemy_detail_message[0][3][1], L"�擾�\�Ȏ��ށE�Z");//2�s��
	//swprintf_s(m_Enemy_detail_message[0][3][2], L"�S70�E�A���~80");//3�s��
	//swprintf_s(m_Enemy_detail_message[0][3][3], L"Immotality");//4�s��
	//swprintf_s(m_Enemy_detail_message[0][3][4], L"�X�s�[�h�d��");//5�s��
	////��1�X�e�[�W�@�{�X�f��
	//swprintf_s(m_Enemy_detail_message[0][4][0], L"��Փx�@����s�\");//1�s��
	//swprintf_s(m_Enemy_detail_message[0][4][1], L"�擾�\�Ȏ��ށE�Z");//2�s��
	//swprintf_s(m_Enemy_detail_message[0][4][2], L"����");//3�s��
	//swprintf_s(m_Enemy_detail_message[0][4][3], L"�U���X��");//4�s��
	//swprintf_s(m_Enemy_detail_message[0][4][4], L"�s��");//4�s��
	////��2�X�e�[�W�@�G�f��1(������1�Ԗڂ̓G�f��)
	//swprintf_s(m_Enemy_detail_message[1][0][0], L"�e�X�g");//1�s��
	//swprintf_s(m_Enemy_detail_message[1][0][1], L"�e�X�g");//2�s��
	//swprintf_s(m_Enemy_detail_message[1][0][2], L"�e�X�g");//3�s��
	//swprintf_s(m_Enemy_detail_message[1][0][3], L"�e�X�g");//4�s��
	////��2�X�e�[�W�@�G�f��2(������2�Ԗڂ̓G�f��)
	//swprintf_s(m_Enemy_detail_message[1][1][0], L"�e�X�g");//1�s��
	//swprintf_s(m_Enemy_detail_message[1][1][1], L"�e�X�g");//2�s��
	//swprintf_s(m_Enemy_detail_message[1][1][2], L"�e�X�g");//3�s��
	//swprintf_s(m_Enemy_detail_message[1][1][3], L"�e�X�g");//4�s��
	////��2�X�e�[�W�@�G�f��3(������3�Ԗڂ̓G�f��)
	//swprintf_s(m_Enemy_detail_message[1][2][0], L"�e�X�g");//1�s��
	//swprintf_s(m_Enemy_detail_message[1][2][1], L"�e�X�g");//2�s��
	//swprintf_s(m_Enemy_detail_message[1][2][2], L"�e�X�g");//3�s��
	//swprintf_s(m_Enemy_detail_message[1][2][3], L"�e�X�g");//4�s��
	////��2�X�e�[�W�@�G�f��4(������4�Ԗڂ̓G�f��)
	//swprintf_s(m_Enemy_detail_message[1][3][0], L"�e�X�g");//1�s��
	//swprintf_s(m_Enemy_detail_message[1][3][1], L"�e�X�g");//2�s��
	//swprintf_s(m_Enemy_detail_message[1][3][2], L"�e�X�g");//3�s��
	//swprintf_s(m_Enemy_detail_message[1][3][3], L"�e�X�g");//4�s��
	////��2�X�e�[�W�@�{�X�f��
	//swprintf_s(m_Enemy_detail_message[1][4][0], L"�e�X�g");//1�s��
	//swprintf_s(m_Enemy_detail_message[1][4][1], L"�e�X�g");//2�s��
	//swprintf_s(m_Enemy_detail_message[1][4][2], L"�e�X�g");//3�s��
	//swprintf_s(m_Enemy_detail_message[1][4][3], L"�e�X�g");//4�s��
	////��3�X�e�[�W�@�G�f��1(������1�Ԗڂ̓G�f��)
	//swprintf_s(m_Enemy_detail_message[2][0][0], L"�e�X�g");//1�s��
	//swprintf_s(m_Enemy_detail_message[2][0][1], L"�e�X�g");//2�s��
	//swprintf_s(m_Enemy_detail_message[2][0][2], L"�e�X�g");//3�s��
	//swprintf_s(m_Enemy_detail_message[2][0][3], L"�e�X�g");//4�s��
	////��3�X�e�[�W�@�G�f��2(������2�Ԗڂ̓G�f��)
	//swprintf_s(m_Enemy_detail_message[2][1][0], L"�e�X�g");//1�s��
	//swprintf_s(m_Enemy_detail_message[2][1][1], L"�e�X�g");//2�s��
	//swprintf_s(m_Enemy_detail_message[2][1][2], L"�e�X�g");//3�s��
	//swprintf_s(m_Enemy_detail_message[2][1][3], L"�e�X�g");//4�s��
	////��3�X�e�[�W�@�G�f��3(������3�Ԗڂ̓G�f��)
	//swprintf_s(m_Enemy_detail_message[2][2][0], L"�e�X�g");//1�s��
	//swprintf_s(m_Enemy_detail_message[2][2][1], L"�e�X�g");//2�s��
	//swprintf_s(m_Enemy_detail_message[2][2][2], L"�e�X�g");//3�s��
	//swprintf_s(m_Enemy_detail_message[2][2][3], L"�e�X�g");//4�s��
	////��3�X�e�[�W�@�G�f��4(������4�Ԗڂ̓G�f��)
	//swprintf_s(m_Enemy_detail_message[2][3][0], L"�e�X�g");//1�s��
	//swprintf_s(m_Enemy_detail_message[2][3][1], L"�e�X�g");//2�s��
	//swprintf_s(m_Enemy_detail_message[2][3][2], L"�e�X�g");//3�s��
	//swprintf_s(m_Enemy_detail_message[2][3][3], L"�e�X�g");//4�s��
	////��3�X�e�[�W�@�{�X�f��
	//swprintf_s(m_Enemy_detail_message[2][4][0], L"�e�X�g");//1�s��
	//swprintf_s(m_Enemy_detail_message[2][4][1], L"�e�X�g");//2�s��
	//swprintf_s(m_Enemy_detail_message[2][4][2], L"�e�X�g");//3�s��
	//swprintf_s(m_Enemy_detail_message[2][4][3], L"�e�X�g");//4�s��
}

//�A�N�V����
void CObjPreparation::Action()
{
	//�w���v��ʕ\�����͑���s�\�ɂ��鏈��
	if (g_help_f == true)
	{
		//�w���v��ʔ�\�����A
		//�퓬������ʂ̊e�{�^���������ɃN���b�N����Ȃ��悤�ɁA
		//�ȉ��̂悤�ɃL�[�t���O��false�ɂ��鎖�Ő��䂵�Ă���B
		m_key_lf = false;
		m_key_rf = false;

		return;
	}

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

			//�G�f���ڍא������\��(�E�N���b�N�Ńz�[����ʂɖ߂�ہA�ڍא������c��Ȃ��悤�ɂ��邽��)
			m_detail_message_alpha = 0.0f;

			//ObjHelp�ɃV�[���ڍs���o��`����
			CObjHelp* help = (CObjHelp*)Objs::GetObj(OBJ_HELP);
			help->SetMig_stageF();
		}

		return;
	}
	//���퓬��ʈڍs���o
	else if (m_Go_flag == true)
	{
		if (m_black_star_effect_f == true)
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
		
		return;
	}



	//������\���̏���
	if (m_is_operatable == true)
	{
		//�`���[�g���A�����͑�����󂯕t���Ȃ��悤�ɂ���B
		if (g_is_operatable == false)
		{
			//�`���[�g���A���i�s�x��2�ɂȂ�ƁA�퓬��ʂ֋����ڍs������
			if (g_tutorial_progress == 2)
			{
				//�ڍs�J�n�t���O����
				m_Go_flag = true;

				g_Challenge_enemy = 5;//�퓬������`���[�g���A���f���ɐݒ�

				//�퓬�O���o���s���I�u�W�F�N�g�𐶐�����
				CObjBefore_Fight_Effect* before_fight_effect = new CObjBefore_Fight_Effect(true);
				Objs::InsertObj(before_fight_effect, OBJ_BEFORE_FIGHT_EFFECT, 100);
			}
			
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

		//���ŏI�m�F�E�C���h�E�\�����̏���
		if (m_finalcheck_f == true)
		{
			//�ŏI�m�F[�͂�]�{�^��
			if (410 < m_mou_x && m_mou_x < 502 && 407 < m_mou_y && m_mou_y < 450)
			{
				m_Yes_Button_color = 0.0f;

				//���N���b�N���ꂽ��ڍs�J�n�t���O�𗧂āA
				//���o�������Ȃ���A�퓬��ʂɃV�[���ڍs����
				//���N���b�N���͎�
				if (m_mou_l == true)
				{
					//���N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
					if (m_key_lf == true)
					{
						m_key_lf = false;

						m_Yes_Button_color = 1.0f;

						//�ڍs�J�n�t���O����
						m_Go_flag = true;

						//�ŏI�m�F�E�C���h�E���\���ɂ���
						m_finalcheck_f = false;

						//�퓬�O���o���s���I�u�W�F�N�g�𐶐�����
						CObjBefore_Fight_Effect* before_fight_effect = new CObjBefore_Fight_Effect(true);
						Objs::InsertObj(before_fight_effect, OBJ_BEFORE_FIGHT_EFFECT, 100);

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
					//�E�C���h�E������A�����Ė߂�{�^������͏o���Ȃ��悤�ɂ���
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

		//�߂�{�^�����N���b�N�A�������͉E�N���b�N���鎖�Ńz�[����ʂɖ߂�
		if (g_tutorial_progress != 1)
		{
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

						//�ڍs�J�n�t���O����
						m_Back_flag = true;

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
		else if (426 < m_mou_x && m_mou_x < 767 && 123 < m_mou_y && m_mou_y < 460 && m_destroy_count == 4 && g_tutorial_progress != 1)
		{
			//���G�f���ڍא�����\��
			Enemy_message(4);//�G�f���ڍא����\���֐����Ăяo��
		}

		//�`���[�g���A���f��[�`���[�g���A���f���o�����̂ݑI���\]
		else if (426 < m_mou_x && m_mou_x < 767 && 133 < m_mou_y && m_mou_y < 350 && m_destroy_count == 4 && g_tutorial_progress == 1)
		{
			//���G�f���ڍא�����\��
			Enemy_message(5);//�G�f���ڍא����\���֐����Ăяo��

			//�����\���ɂ�����
			CObjMessage* message = (CObjMessage*)Objs::GetObj(OBJ_MESSAGE);
			message->Setarrow(0);
		}

		//�X�y�V�����Z(�G�N�X�v���[�W����)
		else if (377 < m_mou_x && m_mou_x < 455 && 579 < m_mou_y && m_mou_y < 637)
		{
			//���X�y�V�����Z�ڍא�����\��
			Special_message(0);//�X�y�V�����Z�ڍא����\���֐����Ăяo��
		}

		//�X�y�V�����Z(�t���N�`���[���C)
		else if (471 < m_mou_x && m_mou_x < 549 && 579 < m_mou_y && m_mou_y < 637)
		{
			//���X�y�V�����Z�ڍא�����\��
			Special_message(1);//�X�y�V�����Z�ڍא����\���֐����Ăяo��
		}

		//�X�y�V�����Z(�C���[�^���e�B)
		else if (565 < m_mou_x && m_mou_x < 643 && 579 < m_mou_y && m_mou_y < 637)
		{
			//���X�y�V�����Z�ڍא�����\��
			Special_message(2);//�X�y�V�����Z�ڍא����\���֐����Ăяo��
		}

		//�X�y�V�����Z(�I�[�o�[���[�N)
		else if (660 < m_mou_x && m_mou_x < 737 && 579 < m_mou_y && m_mou_y < 637)
		{
			//���X�y�V�����Z�ڍא�����\��
			Special_message(3);//�X�y�V�����Z�ڍא����\���֐����Ăяo��
		}

		//�X�y�V�����Z(���~�b�g�u���C�N)
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



	//���x�����b�Z�[�W�X�L�b�v����
	if (m_warning_message_alpha != 0.0f && m_boss_emerge_staging_f == false || m_warning_message_skip_f == true)
	{
		//���̃X�L�b�v�����́A�x�����b�Z�[�W�\�����o���ɍ��N���b�N�����Ǝ��s�����B
		//�X�L�b�v�����Ƃ������̒ʂ�A���s�����ƌx�����b�Z�[�W�̉��o���f�����I������B
		//�������̗���́uif �` else if�v����g���Ă���ׁA��{�I�ɉ������Ɏ��s����Ă����B

		//�}�E�X���N���b�N��Ԃ��擾
		m_mou_l = Input::GetMouButtonL();

		if (m_warning_message_skip_f == true)
		{
			//�x�����b�Z�[�W�\�����o���Ɉ�x�ł����N���b�N�����Ƃ��̏����ɓ���B

			if (m_warning_message_alpha >= 1.2f && m_warning_message_size == 55.0f)
			{
				//�x�����b�Z�[�W���S�\����A
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

					if (g_tutorial_progress != 15)
					{
						//ObjHelp�ɑ���\��`����
						CObjHelp* help = (CObjHelp*)Objs::GetObj(OBJ_HELP);
						help->SetOperatable(true);
					}

					if (g_tutorial_progress <= 15)
					{
						g_is_operatable = false;//����s��

						//ObjMessage�̃��b�Z�[�W�i�s�x�𑝉�������
						CObjMessage* message = (CObjMessage*)Objs::GetObj(OBJ_MESSAGE);
						message->Setprogress(1);
					}
				}

				m_warning_message_skip_f = false;//�x�����b�Z�[�W�X�L�b�v�t���OOFF(�X�L�b�v�������I��������)
			}
			else if (m_warning_message_alpha < 1.2f && m_warning_message_size == 55.0f)
			{
				//�ύX��A�x�����b�Z�[�W���ߓx��f�����グ�A�\����Ԃɂ���B
				m_warning_message_alpha += 0.1f;
			}
			else if (m_warning_message_alpha <= 0.0f)
			{
				//�x�����b�Z�[�W���S��\����A
				//�x�����b�Z�[�W�T�C�Y�A�ʒu��
				//���o�I����̂��̂ɑ����ɕύX����B
				
				//�`���[�g���A���f�����̏���
				if (g_tutorial_progress == 1)
				{
					m_warning_message_x[0] = 16.25f;
				}
				//�{�X�f���o�����̏���
				else if (m_destroy_count == 4)
				{
					m_warning_message_x[0] = 97.2f;
				}
				//����ȊO�̎��̏���
				else
				{
					m_warning_message_x[0] = 192.5f;
				}

				m_warning_message_y[0] = 25.0f;
				m_warning_message_x[1] = 507.5f;
				m_warning_message_y[1] = -105.4f;
				m_warning_message_size = 55.0f;
				m_warning_message_alpha = 0.0f;
			}
			else if (m_warning_message_alpha > 0.0f)
			{
				//�x�����b�Z�[�W���ߓx��f���������A��\����Ԃɂ���B
				m_warning_message_alpha -= 0.1f;
			}

			return;//������return���鎖�ŁA�ʏ폈���ɓ���Ȃ��悤�ɂ���B
		}
		//�x�����b�Z�[�W�\�����o���ɍ��N���b�N���ꂽ��A
		//�x�����b�Z�[�W�X�L�b�v�t���O�𗧂Ă�B
		else if (m_mou_l == true)
		{
			m_warning_message_skip_f = true;//�x�����b�Z�[�W�X�L�b�v�t���OON
		}
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

				//ObjHelp�ɑ���\��`����
				CObjHelp* help = (CObjHelp*)Objs::GetObj(OBJ_HELP);
				help->SetOperatable(true);
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
				m_warning_message_x[0] = 97.2f;
				m_speed = m_save_speed;
			}
			else if (m_warning_message_alpha > 0.0f)
			{
				m_warning_message_alpha -= 0.01f;
			}

			//�{�X�f���`�挳�؂���ʒu�����X�ɕύX���A�ŏI�I�Ɍ��������Ԃɂ���
			//if (m_warning_message_alpha <= 0.0f)
			//{
			//	if (g_Stage_progress == 1)//�X�e�[�W1�̃p���_�f���̎��̂݁A�ȉ��̏��������s�B
			//	{
			//		m_Boss_clip_pos_y = 128.0f;//���ʂ���������
			//	}
			//}
			if (m_warning_message_alpha <= 0.4f)
			{
				m_Boss_clip_pos_x = -600.0f;
			}
			else if (m_warning_message_alpha <= 0.8f)
			{
				m_Boss_clip_pos_x = -300.0f;
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

			if (g_tutorial_progress != 15)
			{
				//ObjHelp�ɑ���\��`����
				CObjHelp* help = (CObjHelp*)Objs::GetObj(OBJ_HELP);
				help->SetOperatable(true);
			}
			
			if (g_tutorial_progress <= 15)
			{
				g_is_operatable = false;//����s��

				//ObjMessage�̃��b�Z�[�W�i�s�x�𑝉�������
				CObjMessage* message = (CObjMessage*)Objs::GetObj(OBJ_MESSAGE);
				message->Setprogress(1);
			}
		}
	}
	else if (m_warning_message_alpha >= 1.2f)
	{
		//�x�����b�Z�[�W���S�\����A
		//�x�����b�Z�[�W�T�C�Y�����X�ɏ��������Ȃ���A
		//��ʏ㕔�ւƌx�����b�Z�[�W���ړ�������

		//�`���[�g���A���f�����̏���
		if (g_tutorial_progress == 1)
		{
			m_warning_message_x[0] += 3.25f;
		}
		//�{�X�f���o�����̏���
		else if (m_destroy_count == 4)
		{
			m_warning_message_x[0] += 5.05f;
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
			if (g_tutorial_progress == 1)
			{
				m_Boss_vx[2] -= m_speed * 0.9f;
			}
			else
			{
				m_Boss_vx[2] -= m_speed * 0.955f;
			}
			m_warning_message_x[0] = -130.0f;//�{�X�o���x�����b�Z�[�W�̏���X�ʒu��ύX����
			m_Boss_clip_pos_x = -600.0f;

			//if (g_Stage_progress == 1)//�X�e�[�W1�̃p���_�f���̎��̂݁A�ȉ��̏��������s�B
			//{
			//	//���ʂ���������
			//	m_Boss_clip_pos_x = 256.0f;
			//	m_Boss_clip_pos_y = 128.0f;
			//}
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
		{ 1.0f,1.0f,1.0f,m_detail_message_alpha },//1�s�ڂ͔��F
		{ 1.0f,0.0f,0.0f,m_detail_message_alpha },//2�s�ڂ͐ԐF
		{ 1.0f,1.0f,1.0f,m_detail_message_alpha },//3�s�ڂ͔��F
		{ 1.0f,1.0f,1.0f,m_detail_message_alpha },//4�s�ڂ͔��F
		{ 1.0f,1.0f,1.0f,m_detail_message_alpha },//5�s�ڂ͔��F
		{ 1.0f,1.0f,0.0f,m_detail_message_alpha },//6�s�ڂ͉��F
	};

	//�ŏI�m�F[�͂�]�{�^���p
	float Yes[4] = {1.0f,m_Yes_Button_color,m_Yes_Button_color,1.0f };

	//�ŏI�m�F[������]�{�^���p
	float No[4] = { m_No_Button_color,m_No_Button_color,1.0f,1.0f };

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
	src.m_right = 1200.0f;
	src.m_bottom = 700.0f;

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 1200.0f;
	dst.m_bottom = 700.0f;
	Draw::Draw(0, &src, &dst, d, 0.0f);

	//�`���[�g���A�����͕\�����Ȃ�
	if (!(g_tutorial_progress == 1 || g_tutorial_progress == 2))
	{
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
	}

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
		Draw::Draw(128 + 5 * (g_Stage_progress - 1), &src, &dst, d, 0.0f);
	}

	//���{�X�f��1�\��(���o�p)
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = -300.0f;
	src.m_bottom = 300.0f;

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
	src.m_left = 600.0f;
	src.m_right = 900.0f;
	src.m_bottom = 300.0f;

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
	src.m_top = 0.0f;
	src.m_left = m_Boss_clip_pos_x;
	src.m_right = -(INI_PLANET) + m_Boss_clip_pos_x;
	src.m_bottom = INI_PLANET;

	dst.m_top = 100.0f + m_Boss_vy[2];
	dst.m_left = 1400.0f + m_Boss_vx[2];
	dst.m_right = 1800.0f + m_Boss_vx[2];
	dst.m_bottom = 500.0f + m_Boss_vy[2];
	
	if (g_tutorial_progress == 1 || g_tutorial_progress == 2)
	{
		src.m_right = INI_PLANET + m_Boss_clip_pos_x;

		Draw::Draw(6, &src, &dst, d, 0.0f);
	}
	else
	{
		Draw::Draw(5 + 5 * (g_Stage_progress - 1), &src, &dst, d, 0.0f);
	}
	

	//���v���C���[�f���\��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 448.0f;
	src.m_bottom = 448.0f;

	dst.m_top = 800.0f + m_Pvy;
	dst.m_left = -500.0f + m_Pvx;
	dst.m_right = -50.0f + m_Pvx + m_Psize;
	dst.m_bottom = 1250.0f + m_Pvy + m_Psize;
	Draw::Draw(47 + ((int)((g_Bar_Level + g_Ins_Level) / 2)) - 1, &src, &dst, d, 0.0f);

	//�`���[�g���A�����͕\�����Ȃ�
	if (!(g_tutorial_progress == 1 || g_tutorial_progress == 2))
	{

		//���E�C���h�E�\������ 
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 800.0f;
		src.m_bottom = 790.0f;

		dst.m_top = 940.0f + m_Svy;
		dst.m_left = 360.0f;
		dst.m_right = 440.0f;
		dst.m_bottom = 1020.0 + m_Svy;
		Draw::Draw(55, &src, &dst, d, 0.0f);

		//���E�C���h�E�\������
		src.m_top = 0.0f;
		src.m_left = 800.0f;
		src.m_right = 1600.0f;
		src.m_bottom = 795.0f;

		dst.m_top = 1020.0f + m_Svy;
		dst.m_left = 360.0f;
		dst.m_right = 440.0f;
		dst.m_bottom = 1100.0 + m_Svy;
		Draw::Draw(55, &src, &dst, d, 0.0f);

		for (int i = 0; i < 5; i++)
		{
			//���E�C���h�E�\�������� 
			src.m_top = 0.0f;
			src.m_left = 1600.0f;
			src.m_right = 2400.0f;
			src.m_bottom = 795.0f;

			dst.m_top = 940.0f + m_Svy;
			dst.m_left = 440.0f + (i * 80);
			dst.m_right = 520.0f + (i * 80);
			dst.m_bottom = 1020.0f + m_Svy;
			Draw::Draw(55, &src, &dst, d, 0.0f);

			//���E�C���h�E�\�������� 
			src.m_top = 5.0f;
			src.m_left = 2400.0f;
			src.m_right = 3200.0f;
			src.m_bottom = 800.0f;

			dst.m_top = 1020.0f + m_Svy;
			dst.m_left = 440.0f + (i * 80);
			dst.m_right = 520.0f + (i * 80);
			dst.m_bottom = 1100.0f + m_Svy;
			Draw::Draw(55, &src, &dst, d, 0.0f);
		}

		//���E�C���h�E�E��
		src.m_top = 0.0f;
		src.m_left = 4000.0f;
		src.m_right = 4800.0f;
		src.m_bottom = 795.0f;

		dst.m_top = 940.0f + m_Svy;
		dst.m_left = 780.0f;
		dst.m_right = 860.0f;
		dst.m_bottom = 1020.0 + m_Svy;
		Draw::Draw(55, &src, &dst, d, 0.0f);

		//���E�C���h�E�E��
		src.m_top = 5.0f;
		src.m_left = 4800.0f;
		src.m_right = 5600.0f;
		src.m_bottom = 800.0f;

		dst.m_top = 1020.0f + m_Svy;
		dst.m_left = 780.0f;
		dst.m_right = 860.0f;
		dst.m_bottom = 1100.0 + m_Svy;
		Draw::Draw(55, &src, &dst, d, 0.0f);

		//���E�C���h�E�\������ 
		src.m_top = 0.0f;
		src.m_left = -10.0f;
		src.m_right = 800.0f;
		src.m_bottom = 790.0f;

		dst.m_top = 905.0f + m_Svy;
		dst.m_left = 420.0f;
		dst.m_right = 470.0f;
		dst.m_bottom = 955.0 + m_Svy;
		Draw::Draw(55, &src, &dst, d, 0.0f);

		//���E�C���h�E�\������
		src.m_top = 30.0f;
		src.m_left = 780.0f;
		src.m_right = 1600.0f;
		src.m_bottom = 795.0f;

		dst.m_top = 920.0f + m_Svy;
		dst.m_left = 420.0f;
		dst.m_right = 470.0f;
		dst.m_bottom = 970.0 + m_Svy;
		Draw::Draw(55, &src, &dst, d, 0.0f);

		for (int i = 0; i < 6; i++)
		{
			//���E�C���h�E�\�������� 
			src.m_top = 0.0f;
			src.m_left = 1600.0f;
			src.m_right = 2400.0f;
			src.m_bottom = 795.0f;

			dst.m_top = 905.0f + m_Svy;
			dst.m_left = 470.0f + (i * 50);
			dst.m_right = 520.0f + (i * 50);
			dst.m_bottom = 955.0f + m_Svy;
			Draw::Draw(55, &src, &dst, d, 0.0f);

			//���E�C���h�E�\�������� 
			src.m_top = 5.0f;
			src.m_left = 2400.0f;
			src.m_right = 3200.0f;
			src.m_bottom = 800.0f;

			dst.m_top = 920.0f + m_Svy;
			dst.m_left = 470.0f + (i * 50);
			dst.m_right = 520.0f + (i * 50);
			dst.m_bottom = 970.0f + m_Svy;
			Draw::Draw(55, &src, &dst, d, 0.0f);
		}

		//���E�C���h�E�E��
		src.m_top = 0.0f;
		src.m_left = 4000.0f;
		src.m_right = 4800.0f;
		src.m_bottom = 795.0f;

		dst.m_top = 905.0f + m_Svy;
		dst.m_left = 740.0f;
		dst.m_right = 790.0f;
		dst.m_bottom = 955.0 + m_Svy;
		Draw::Draw(55, &src, &dst, d, 0.0f);

		//���E�C���h�E�E��
		src.m_top = 5.0f;
		src.m_left = 4800.0f;
		src.m_right = 5600.0f;
		src.m_bottom = 800.0f;

		dst.m_top = 920.0f + m_Svy;
		dst.m_left = 740.0f;
		dst.m_right = 790.0f;
		dst.m_bottom = 970.0 + m_Svy;
		Draw::Draw(55, &src, &dst, d, 0.0f);


		//���X�y�V�����Z�A�C�R���W�\��
		for (int i = 0; i < 5; i++)
		{
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 130.0f;
			src.m_bottom = 130.0f;

			dst.m_top = 985.0f + m_Svy;
			dst.m_left = 380.0f + i * 95.0f;
			dst.m_right = 460.0f + i * 95.0f;
			dst.m_bottom = 1065.0f + m_Svy;
			Draw::Draw(57 + i, &src, &dst, Special_icon[i], 0.0f);
		}

		//���X�y�V�����Z�I�𕶎��摜�\��
		src.m_top = 0.0f;
		src.m_left = 1.0f;
		src.m_right = 952.0f;
		src.m_bottom = 111.0f;

		dst.m_top = 915.0f + m_Svy;
		dst.m_left = 445.0f;
		dst.m_right = 765.0f;
		dst.m_bottom = 955.0f + m_Svy;
		Draw::Draw(68, &src, &dst, d, 0.0f);
	}

	//�{�X�o���x�����b�Z�[�W
	//Font::StrDraw(������,X��,Y��,�ꕶ��������̃T�C�Y,�F);
	//Font::StrDraw(Until_fight_boss_count[0], m_warning_message_x[0], m_warning_message_y[0], m_warning_message_size, warning_message);
	//Font::StrDraw(Until_fight_boss_count[1], m_warning_message_x[1] + 250.0f, m_warning_message_y[1] + 130.0f, m_warning_message_size, warning_message);


	if (m_destroy_count == 0)
	{
		//������Șf�� �ڋ߂܂ŕ����摜�\��
		src.m_top = 0.0f;
		src.m_left = 2.0f;
		src.m_right = 1132.0f;
		src.m_bottom = 112.0f;

		dst.m_top = m_warning_message_y[0];
		dst.m_left = m_warning_message_x[0];
		dst.m_right = m_warning_message_x[0] + (m_warning_message_size*9.5);
		dst.m_bottom = m_warning_message_y[0] + (m_warning_message_size);
		Draw::Draw(64, &src, &dst, warning_message, 0.0);

		//������3�̕����摜�\��
		src.m_top = 4.0f;
		src.m_left = 0.0f;
		src.m_right = 502.0f;
		src.m_bottom = 112.0f;

		dst.m_top = m_warning_message_y[1]+130.0f;
		dst.m_left = m_warning_message_x[1]+250.0f;
		dst.m_right = m_warning_message_x[1] + (m_warning_message_size*4)+250.0f;
		dst.m_bottom = m_warning_message_y[1] + (m_warning_message_size)+130.0f;
		Draw::Draw(69, &src, &dst, warning_message, 0.0);
	}

	else if (m_destroy_count == 1)
	{
		//������Șf�� �ڋ߂܂ŕ����摜�\��
		src.m_top = 0.0f;
		src.m_left = 2.0f;
		src.m_right = 1132.0f;
		src.m_bottom = 112.0f;

		dst.m_top = m_warning_message_y[0];
		dst.m_left = m_warning_message_x[0];
		dst.m_right = m_warning_message_x[0] + (m_warning_message_size*9.5);
		dst.m_bottom = m_warning_message_y[0] + (m_warning_message_size);
		Draw::Draw(64, &src, &dst, warning_message, 0.0);

		//������2�̕����摜�\��
		src.m_top = 4.0f;
		src.m_left = 0.0f;
		src.m_right = 502.0f;
		src.m_bottom = 112.0f;

		dst.m_top = m_warning_message_y[1] + 130.0f;
		dst.m_left = m_warning_message_x[1] + 250.0f;
		dst.m_right = m_warning_message_x[1] + (m_warning_message_size * 4) + 250.0f;
		dst.m_bottom = m_warning_message_y[1] + (m_warning_message_size)+130.0f;
		Draw::Draw(70, &src, &dst, warning_message, 0.0);
	}

	else if (m_destroy_count == 2)
	{
		//������Șf�� �ڋ߂܂ŕ����摜�\��
		src.m_top = 0.0f;
		src.m_left = 2.0f;
		src.m_right = 1132.0f;
		src.m_bottom = 112.0f;

		dst.m_top = m_warning_message_y[0];
		dst.m_left = m_warning_message_x[0];
		dst.m_right = m_warning_message_x[0] + (m_warning_message_size*9.5);
		dst.m_bottom = m_warning_message_y[0] + (m_warning_message_size);
		Draw::Draw(64, &src, &dst, warning_message, 0.0);

		//������1�̕����摜�\��
		src.m_top = 4.0f;
		src.m_left = 0.0f;
		src.m_right = 502.0f;
		src.m_bottom = 112.0f;

		dst.m_top = m_warning_message_y[1] + 130.0f;
		dst.m_left = m_warning_message_x[1] + 250.0f;
		dst.m_right = m_warning_message_x[1] + (m_warning_message_size * 4) + 250.0f;
		dst.m_bottom = m_warning_message_y[1] + (m_warning_message_size)+130.0f;
		Draw::Draw(71, &src, &dst, warning_message, 0.0);
	}

	else if (m_destroy_count == 3)
	{
		//������Șf�� �ڋ߂܂ŕ����摜�\��
		src.m_top = 0.0f;
		src.m_left = 2.0f;
		src.m_right = 1132.0f;
		src.m_bottom = 112.0f;

		dst.m_top = m_warning_message_y[0];
		dst.m_left = m_warning_message_x[0];
		dst.m_right = m_warning_message_x[0] + (m_warning_message_size*9.5);
		dst.m_bottom = m_warning_message_y[0] + (m_warning_message_size);
		Draw::Draw(64, &src, &dst, warning_message, 0.0);

		//������0�̕����摜�\��
		src.m_top = 4.0f;
		src.m_left = 0.0f;
		src.m_right = 502.0f;
		src.m_bottom = 112.0f;

		dst.m_top = m_warning_message_y[1] + 130.0f;
		dst.m_left = m_warning_message_x[1] + 250.0f;
		dst.m_right = m_warning_message_x[1] + (m_warning_message_size * 4) + 250.0f;
		dst.m_bottom = m_warning_message_y[1] + (m_warning_message_size)+130.0f;
		Draw::Draw(72, &src, &dst, warning_message, 0.0);
	}

	else if (m_destroy_count = 4)
	{
		//������Șf���o���������摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1012.0f;
		src.m_bottom = 112.0f;

		dst.m_top = m_warning_message_y[0];
		dst.m_left = m_warning_message_x[0] + (m_warning_message_size) + 240.0f - (m_warning_message_size - 45);
		dst.m_right = m_warning_message_x[0] + (m_warning_message_size * 8.5) + 240.0f + (m_warning_message_size - 45);
		dst.m_bottom = m_warning_message_y[0] + (m_warning_message_size);

		//�`���[�g���A���f���̎��́u�f���@�o�����v�Ƃ������ɂ��������߁A
		//�؂���ʒu�A�`��ʒu������p�ɒ������Ă���B
		if (g_tutorial_progress == 1 || g_tutorial_progress == 2)
		{
			src.m_left = 360.0f;

			dst.m_left = m_warning_message_x[0] + (m_warning_message_size) + 415.0f - (m_warning_message_size - 45);
			dst.m_right = m_warning_message_x[0] + (m_warning_message_size * 5.5) + 415.0f + (m_warning_message_size - 45);
		}

		Draw::Draw(63, &src, &dst, warning_message, 0.0);
	}

	//Font::StrDraw(Until_fight_boss_count[0], m_warning_message_x[0], m_warning_message_y[0], m_warning_message_size, warning_message);

	//���ڍא���(�G�f���A�X�y�V�����Z)���b�Z�[�W�\��
	//���E�C���h�E�\�� 
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1200.0f;
	src.m_bottom = 700.0f;

	dst.m_top = m_mou_y + m_detail_message_window_top;
	dst.m_left = m_mou_x + m_detail_message_window_left;
	dst.m_right = m_mou_x + m_detail_message_window_right;
	dst.m_bottom = m_mou_y + m_detail_message_window_bottom;
	Draw::Draw(89, &src, &dst, detail_message_window, 0.0f);

	//���ڍא����t�H���g�摜�\��
	for (int i = 0; i < DETAIL_MES_MAX_FONT_LINE; i++)
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = m_detail_message_clip_right[i];
		src.m_bottom = m_detail_message_clip_bottom[i];

		dst.m_top = m_mou_y + m_detail_message_draw_y + i * 38.0f;
		dst.m_left = m_mou_x + m_detail_message_draw_left;
		dst.m_right = m_mou_x + m_detail_message_draw_right[i];
		dst.m_bottom = m_mou_y + m_detail_message_draw_y + 25.0f + i * 38.0f;
		Draw::Draw(122 + i, &src, &dst, detail_message_font[i], 0.0f);


		//Font::StrDraw(m_detail_message[i], m_mou_x + m_detail_message_font_x, m_mou_y + m_detail_message_draw_y + i * 40.0f, 25.0f, detail_message_font[i]);

		////����Փx�����摜�\��
		//src.m_top = 0.0f;
		//src.m_left = 0.0f;
		//src.m_right = 367.0f;
		//src.m_bottom = 117.0f;

		//dst.m_top = m_mou_y + m_detail_message_draw_y + i;
		//dst.m_left = m_mou_x + m_detail_message_font_x;
		//dst.m_right = m_mou_x + m_detail_message_font_x;
		//dst.m_bottom = m_mou_y + m_detail_message_draw_y + i;
		//Draw::Draw(73, &src, &dst, d, 0.0f);

	}

	//����Փx��\�����摜��\��
	//�{�X�f���̏ꍇ
	if (m_level_star_num >= 5)
	{
		//������s�\�����摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 379.0f;
		src.m_bottom = 90.0f;

		dst.m_top = m_mou_y + m_detail_message_draw_y + 38.0f;
		dst.m_left = m_mou_x + m_detail_message_draw_left + 100.0f;
		dst.m_right = m_mou_x + m_detail_message_draw_left + 200.0f;
		dst.m_bottom = m_mou_y + m_detail_message_draw_y + 63.0f;
		Draw::Draw(74, &src, &dst, detail_message_font[1], 0.0f);
	}
	//���̑��̃U�R�f���̏ꍇ
	else
	{
		for (int i = 0; i < m_level_star_num; i++)
		{
			//�����摜�\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 101.0f;
			src.m_bottom = 107.0f;

			dst.m_top = m_mou_y + m_detail_message_draw_y + 38.0f;
			dst.m_left = m_mou_x + m_detail_message_draw_left + 100.0f + (25.0f * i);
			dst.m_right = m_mou_x + m_detail_message_draw_left + 125.0f + (25.0f * i);
			dst.m_bottom = m_mou_y + m_detail_message_draw_y + 63.0f;
			Draw::Draw(73, &src, &dst, detail_message_font[1], 0.0f);
		}
	}

	//���G�f������\���@[��Փx��������ɂǂ̘f�������f����]
	//���`���[�g���A���f����m_level_star_num == 1�̏����̒��ɁA
	//�`���[�g���A���̃O���[�o���t���O���ōX�ɕ��򂳂��Ĕ��f�����Ă���B
	if (m_level_star_num == 1)
	{
		if (g_tutorial_progress == 1 || g_tutorial_progress == 2)
		{
			//���u�{���{�����v�\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 474.0f;
			src.m_bottom = 90.0f;

			dst.m_top = m_mou_y + m_detail_message_draw_y;
			dst.m_left = m_mou_x + m_detail_message_draw_left + 100.0f;
			dst.m_right = m_mou_x + m_detail_message_draw_left + 225.0f;
			dst.m_bottom = m_mou_y + m_detail_message_draw_y + 25.0f;
			Draw::Draw(75, &src, &dst, detail_message_font[0], 0.0f);
		}
		else
		{
			//���uO�㍰�v�\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 258.0f;
			src.m_bottom = 90.0f;

			dst.m_top = m_mou_y + m_detail_message_draw_y;
			dst.m_left = m_mou_x + m_detail_message_draw_left + 100.0f;
			dst.m_right = m_mou_x + m_detail_message_draw_left + 175.0f;
			dst.m_bottom = m_mou_y + m_detail_message_draw_y + 25.0f;
			Draw::Draw(76, &src, &dst, detail_message_font[0], 0.0f);
		}
	}
	else if (m_level_star_num == 2)
	{
		//���u�Đ��v�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 186.0f;
		src.m_bottom = 90.0f;

		dst.m_top = m_mou_y + m_detail_message_draw_y;
		dst.m_left = m_mou_x + m_detail_message_draw_left + 100.0f;
		dst.m_right = m_mou_x + m_detail_message_draw_left + 150.0f;
		dst.m_bottom = m_mou_y + m_detail_message_draw_y + 25.0f;
		Draw::Draw(77, &src, &dst, detail_message_font[0], 0.0f);
	}
	else if (m_level_star_num == 3)
	{
		//���u�A���C�v�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 282.0f;
		src.m_bottom = 84.0f;

		dst.m_top = m_mou_y + m_detail_message_draw_y;
		dst.m_left = m_mou_x + m_detail_message_draw_left + 100.0f;
		dst.m_right = m_mou_x + m_detail_message_draw_left + 175.0f;
		dst.m_bottom = m_mou_y + m_detail_message_draw_y + 25.0f;
		Draw::Draw(78, &src, &dst, detail_message_font[0], 0.0f);
	}
	else if (m_level_star_num == 4)
	{
		//���u�R�����[�e�v�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 474.0f;
		src.m_bottom = 84.0f;

		dst.m_top = m_mou_y + m_detail_message_draw_y;
		dst.m_left = m_mou_x + m_detail_message_draw_left + 100.0f;
		dst.m_right = m_mou_x + m_detail_message_draw_left + 225.0f;
		dst.m_bottom = m_mou_y + m_detail_message_draw_y + 25.0f;
		Draw::Draw(79, &src, &dst, detail_message_font[0], 0.0f);
	}
	else if (m_level_star_num == 5)
	{
		//���u�A�}�e���X�v�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 474.0f;
		src.m_bottom = 84.0f;

		dst.m_top = m_mou_y + m_detail_message_draw_y;
		dst.m_left = m_mou_x + m_detail_message_draw_left + 100.0f;
		dst.m_right = m_mou_x + m_detail_message_draw_left + 225.0f;
		dst.m_bottom = m_mou_y + m_detail_message_draw_y + 25.0f;
		Draw::Draw(80, &src, &dst, detail_message_font[0], 0.0f);
	}


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
		Draw::Draw(89, &src, &dst, d, 0.0f);

		//���򂤁H�����摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 337.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 250.0f;
		dst.m_left = 460.0f;
		dst.m_right = 760.0f;
		dst.m_bottom = 350.0f;
		Draw::Draw(65, &src, &dst, d, 0.0f);

		//���͂������摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 232.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 410.0f;
		dst.m_left = 410.0f;
		dst.m_right = 510.0f;
		dst.m_bottom = 460.0f;
		Draw::Draw(66, &src, &dst, Yes, 0.0f);

		//�������������摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 352.0f;
		src.m_bottom = 112.0f;

		dst.m_top    = 410.0f;
		dst.m_left   = 650.0f;
		dst.m_right  = 800.0f;
		dst.m_bottom = 460.0f;
		Draw::Draw(67, &src, &dst, No, 0.0f);
	}



	////�f�o�b�O�p���}�E�X�ʒu�\��
	//wchar_t str[256];
	//swprintf_s(str, L"x=%f,y=%f", m_mou_x, m_mou_y);
	//Font::StrDraw(str, 20.0f, 20.0f, 12.0f, d);
}

//---Enemy_message�֐�
//����1�@int enemy_id	:�G�f�����ʔԍ�(0:������1�Ԗڂ̓G�f���@1:������2�Ԗڂ̓G�f���@2:������3�Ԗڂ̓G�f���@3:������4�Ԗڂ̓G�f���@4:�{�X�f���@5:�`���[�g���A���f��)
//�����e
//�}�E�X�őI�����Ă���G�f�������ł��邩�����ʂ��A
//����ɑΉ�����G�f���ڍא�����\������B
void CObjPreparation::Enemy_message(int enemy_id)
{
	//���ȉ��͊e�G�f�����ɈقȂ�l��������ʏ���
	//��������1�Ԗڂ̓G�f��
	if (enemy_id == 0)
	{
		//�G�f���ڍא����E�C���h�E�̃T�C�Y��ݒ�
		m_detail_message_window_top = -126.0f;
		m_detail_message_window_left = 20.0f;
		m_detail_message_window_right = 320.0f;
		m_detail_message_window_bottom = 120.0f;

		//�G�f���ڍא����摜�̕`��ʒu(right�ȊO)��ݒ�
		m_detail_message_draw_left = 33.0f;
		m_detail_message_draw_y = -108.0f;

		//��4�s��
		//�G�f���ڍא����摜��125�Ԃɓo�^
		Draw::LoadImage(L"img\\�e�L�X�g\\�f��\\�؍�50�E�S30.png", 125, TEX_SIZE_512);

		//�G�f���ڍא����摜�̐؂���ʒu��ݒ�
		m_detail_message_clip_right[3] = 666.0f;
		m_detail_message_clip_bottom[3] = 90.0f;

		//�G�f���ڍא����摜�̕`��ʒu(right)��ݒ�(�S�p�ꕶ���̑傫����25.0f)
		m_detail_message_draw_right[3] = m_detail_message_draw_left + 175.0f;


		//��5�s��
		//�G�f���ڍא����摜��126�Ԃɓo�^
		Draw::LoadImage(L"img\\�e�L�X�g\\�X�y�V�����Z\\�t���N�`���[���C.png", 126, TEX_SIZE_512);

		//�G�f���ڍא����摜�̐؂���ʒu��ݒ�
		m_detail_message_clip_right[4] = 952.0f;
		m_detail_message_clip_bottom[4] = 112.0f;

		//�G�f���ڍא����摜�̕`��ʒu(right)��ݒ�(�S�p�ꕶ���̑傫����25.0f)
		m_detail_message_draw_right[4] = m_detail_message_draw_left + 200.0f;


		//��6�s��
		//�G�f���ڍא����摜��127�Ԃɓo�^
		Draw::LoadImage(L"img\\�e�L�X�g\\�퓬�������\\�u���[�d��.png", 127, TEX_SIZE_512);

		//�G�f���ڍא����摜�̐؂���ʒu��ݒ�
		m_detail_message_clip_right[5] = 474.0f;
		m_detail_message_clip_bottom[5] = 90.0f;

		//�G�f���ڍא����摜�̕`��ʒu(right)��ݒ�(�S�p�ꕶ���̑傫����25.0f)
		m_detail_message_draw_right[5] = m_detail_message_draw_left + 125.0f;

		//��Փx��\�����̐���ݒ�
		m_level_star_num = 1;
	}
	//��������4�Ԗڂ̓G�f��
	else if (enemy_id == 3)
	{
		//�G�f���ڍא����E�C���h�E�̃T�C�Y��ݒ�
		m_detail_message_window_top = -126.0f;
		m_detail_message_window_left = -300.0f;
		m_detail_message_window_right = 0.0f;
		m_detail_message_window_bottom = 120.0f;

		//�G�f���ڍא����摜�̕`��ʒu(right�ȊO)��ݒ�
		m_detail_message_draw_left = -288.0f;
		m_detail_message_draw_y = -108.0f;

		//��4�s��
		//�G�f���ڍא����摜��125�Ԃɓo�^
		Draw::LoadImage(L"img\\�e�L�X�g\\�f��\\�S70�E�A���~80.png", 125, TEX_SIZE_512);

		//�G�f���ڍא����摜�̐؂���ʒu��ݒ�
		m_detail_message_clip_right[3] = 762.0f;
		m_detail_message_clip_bottom[3] = 90.0f;

		//�G�f���ڍא����摜�̕`��ʒu(right)��ݒ�(�S�p�ꕶ���̑傫����25.0f)
		m_detail_message_draw_right[3] = m_detail_message_draw_left + 200.0f;


		//��5�s��
		//�G�f���ڍא����摜��126�Ԃɓo�^
		Draw::LoadImage(L"img\\�e�L�X�g\\�X�y�V�����Z\\�C���[�^���e�B.png", 126, TEX_SIZE_512);

		//�G�f���ڍא����摜�̐؂���ʒu��ݒ�
		m_detail_message_clip_right[4] = 817.0f;
		m_detail_message_clip_bottom[4] = 112.0f;

		//�G�f���ڍא����摜�̕`��ʒu(right)��ݒ�(�S�p�ꕶ���̑傫����25.0f)
		m_detail_message_draw_right[4] = m_detail_message_draw_left + 175.0f;


		//��6�s��
		//�G�f���ڍא����摜��127�Ԃɓo�^
		Draw::LoadImage(L"img\\�e�L�X�g\\�퓬�������\\�O���[���d��.png", 127, TEX_SIZE_512);

		//�G�f���ڍא����摜�̐؂���ʒu��ݒ�
		m_detail_message_clip_right[5] = 570.0f;
		m_detail_message_clip_bottom[5] = 90.0f;

		//�G�f���ڍא����摜�̕`��ʒu(right)��ݒ�(�S�p�ꕶ���̑傫����25.0f)
		m_detail_message_draw_right[5] = m_detail_message_draw_left + 150.0f;



		//��Փx��\�����̐���ݒ�
		m_level_star_num = 2;
	}
	//��������2�A3�Ԗڂ̓G�f�� & �{�X�f�� & �`���[�g���A���f��
	else  //(enemy_id == 1 || enemy_id == 2 || enemy_id == 4 || enemy_id == 5)
	{
		//�G�f���ڍא����E�C���h�E�̃T�C�Y��ݒ�
		m_detail_message_window_top = 20.0f;
		m_detail_message_window_left = -150.0f;
		m_detail_message_window_right = 150.0f;
		m_detail_message_window_bottom = 266.0f;

		//�G�f���ڍא����摜�̕`��ʒu(right�ȊO)��ݒ�
		m_detail_message_draw_left = -138.0f;
		m_detail_message_draw_y = 38.0f;

		
		//��������2�Ԗڂ̓G�f��
		if (enemy_id == 1)
		{
			//��4�s��
			//�G�f���ڍא����摜��125�Ԃɓo�^
			Draw::LoadImage(L"img\\�e�L�X�g\\�f��\\�v���X�`�b�N40�E�K�X50.png", 125, TEX_SIZE_512);

			//�G�f���ڍא����摜�̐؂���ʒu��ݒ�
			m_detail_message_clip_right[3] = 1147.0f;
			m_detail_message_clip_bottom[3] = 91.0f;

			//�G�f���ڍא����摜�̕`��ʒu(right)��ݒ�(�S�p�ꕶ���̑傫����25.0f)
			m_detail_message_draw_right[3] = m_detail_message_draw_left + 275.0f;


			//��5�s��
			//�G�f���ڍא����摜��126�Ԃɓo�^
			Draw::LoadImage(L"img\\�e�L�X�g\\�X�y�V�����Z\\�G�N�X�v���[�W����.png", 126, TEX_SIZE_512);

			//�G�f���ڍא����摜�̐؂���ʒu��ݒ�
			m_detail_message_clip_right[4] = 1072.0f;
			m_detail_message_clip_bottom[4] = 112.0f;

			//�G�f���ڍא����摜�̕`��ʒu(right)��ݒ�(�S�p�ꕶ���̑傫����25.0f)
			m_detail_message_draw_right[4] = m_detail_message_draw_left + 225.0f;


			//��6�s��
			//�G�f���ڍא����摜��127�Ԃɓo�^
			Draw::LoadImage(L"img\\�e�L�X�g\\�퓬�������\\���b�h�d��.png", 127, TEX_SIZE_512);

			//�G�f���ڍא����摜�̐؂���ʒu��ݒ�
			m_detail_message_clip_right[5] = 467.0f;
			m_detail_message_clip_bottom[5] = 90.0f;

			//�G�f���ڍא����摜�̕`��ʒu(right)��ݒ�(�S�p�ꕶ���̑傫����25.0f)
			m_detail_message_draw_right[5] = m_detail_message_draw_left + 125.0f;

			

			//��Փx��\�����̐���ݒ�
			m_level_star_num = 3;
		}
		//��������3�Ԗڂ̓G�f��
		else if (enemy_id == 2)
		{
			//��4�s��
			//�G�f���ڍא����摜��125�Ԃɓo�^	(�摜���Ȃ��������ߓK�p���ĂȂ�)
			Draw::LoadImage(L"img\\�e�L�X�g\\�f��\\��65�E�K�X50.png", 125, TEX_SIZE_512);

			//�G�f���ڍא����摜�̐؂���ʒu��ݒ�
			m_detail_message_clip_right[3] = 666.0f;
			m_detail_message_clip_bottom[3] = 90.0f;

			//�G�f���ڍא����摜�̕`��ʒu(right)��ݒ�(�S�p�ꕶ���̑傫����25.0f)
			m_detail_message_draw_right[3] = m_detail_message_draw_left + 200.0f;


			//��5�s��
			//�G�f���ڍא����摜��126�Ԃɓo�^
			Draw::LoadImage(L"���~�b�g�u���C�N.png", 126, TEX_SIZE_512);

			//�G�f���ڍא����摜�̐؂���ʒu��ݒ�
			m_detail_message_clip_right[4] = 952.0f;
			m_detail_message_clip_bottom[4] = 112.0f;

			//�G�f���ڍא����摜�̕`��ʒu(right)��ݒ�(�S�p�ꕶ���̑傫����25.0f)
			m_detail_message_draw_right[4] = m_detail_message_draw_left + 200.0f;


			//��6�s��
			//�G�f���ڍא����摜��127�Ԃɓo�^
			Draw::LoadImage(L"img\\�e�L�X�g\\�퓬�������\\�z���C�g�d��.png", 127, TEX_SIZE_512);

			//�G�f���ڍא����摜�̐؂���ʒu��ݒ�
			m_detail_message_clip_right[5] = 570.0f;
			m_detail_message_clip_bottom[5] = 90.0f;

			//�G�f���ڍא����摜�̕`��ʒu(right)��ݒ�(�S�p�ꕶ���̑傫����25.0f)
			m_detail_message_draw_right[5] = m_detail_message_draw_left + 150.0f;



			//��Փx��\�����̐���ݒ�
			m_level_star_num = 4;
		}
		//���{�X�f��
		else if (enemy_id == 4)
		{
			//��4�s��
			//�G�f���ڍא����摜��125�Ԃɓo�^
			Draw::LoadImage(L"img\\�e�L�X�g\\�퓬�������\\����.png", 125, TEX_SIZE_512);

			//�G�f���ڍא����摜�̐؂���ʒu��ݒ�
			m_detail_message_clip_right[3] = 180.0f;
			m_detail_message_clip_bottom[3] = 90.0f;

			//�G�f���ڍא����摜�̕`��ʒu(right)��ݒ�(�S�p�ꕶ���̑傫����25.0f)
			m_detail_message_draw_right[3] = m_detail_message_draw_left + 50.0f;


			//��5�s��
			//�G�f���ڍא����摜��126�Ԃɓo�^
			Draw::LoadImage(L"img\\�e�L�X�g\\�퓬�������\\�U���X��.png", 126, TEX_SIZE_512);

			//�G�f���ڍא����摜�̐؂���ʒu��ݒ�
			m_detail_message_clip_right[4] = 378.0f;
			m_detail_message_clip_bottom[4] = 90.0f;

			//�G�f���ڍא����摜�̕`��ʒu(right)��ݒ�(�S�p�ꕶ���̑傫����25.0f)
			m_detail_message_draw_right[4] = m_detail_message_draw_left + 100.0f;


			//��6�s��
			//�G�f���ڍא����摜��127�Ԃɓo�^
			Draw::LoadImage(L"img\\�e�L�X�g\\�퓬�������\\�s��.png", 127, TEX_SIZE_512);

			//�G�f���ڍא����摜�̐؂���ʒu��ݒ�
			m_detail_message_clip_right[5] = 186.0f;
			m_detail_message_clip_bottom[5] = 90.0f;

			//�G�f���ڍא����摜�̕`��ʒu(right)��ݒ�(�S�p�ꕶ���̑傫����25.0f)
			m_detail_message_draw_right[5] = m_detail_message_draw_left + 50.0f;



			//��Փx��\�����̐���ݒ�
			m_level_star_num = 5;
		}
		//���`���[�g���A���f��
		else if (enemy_id == 5)
		{
			//�G�f���ڍא����E�C���h�E�̃T�C�Y��ݒ�
			m_detail_message_window_top = -126.0f;
			m_detail_message_window_left = 20.0f;
			m_detail_message_window_right = 320.0f;
			m_detail_message_window_bottom = 120.0f;

			//�G�f���ڍא����摜�̕`��ʒu(right�ȊO)��ݒ�
			m_detail_message_draw_left = 33.0f;
			m_detail_message_draw_y = -108.0f;


			//��4�s��
			//�G�f���ڍא����摜��125�Ԃɓo�^
			Draw::LoadImage(L"img\\�e�L�X�g\\�X�y�V�����Z\\�I�[�o�[���[�N.png", 125, TEX_SIZE_512);

			//�G�f���ڍא����摜�̐؂���ʒu��ݒ�
			m_detail_message_clip_right[3] = 832.0f;
			m_detail_message_clip_bottom[3] = 112.0f;

			//�G�f���ڍא����摜�̕`��ʒu(right)��ݒ�(�S�p�ꕶ���̑傫����25.0f)
			m_detail_message_draw_right[3] = m_detail_message_draw_left + 175.0f;


			//��5�s��
			//�G�f���ڍא����摜��126�Ԃɓo�^	(���������`���[�g���A���f����5�s�ڂɂ͉����\�����Ȃ�)
			//Draw::LoadImage(L"", 126, TEX_SIZE_512);

			//�G�f���ڍא����摜�̐؂���ʒu��ݒ�
			m_detail_message_clip_right[4] = 0.0f;
			m_detail_message_clip_bottom[4] = 0.0f;

			//�G�f���ڍא����摜�̕`��ʒu(right)��ݒ�(�S�p�ꕶ���̑傫����25.0f)
			m_detail_message_draw_right[4] = m_detail_message_draw_left + 0.0f;


			//��6�s��
			//�G�f���ڍא����摜��127�Ԃɓo�^
			Draw::LoadImage(L"img\\�e�L�X�g\\�퓬�������\\�z���C�g�d��.png", 127, TEX_SIZE_512);

			//�G�f���ڍא����摜�̐؂���ʒu��ݒ�
			m_detail_message_clip_right[5] = 570.0f;
			m_detail_message_clip_bottom[5] = 90.0f;

			//�G�f���ڍא����摜�̕`��ʒu(right)��ݒ�(�S�p�ꕶ���̑傫����25.0f)
			m_detail_message_draw_right[5] = m_detail_message_draw_left + 150.0f;



			//��Փx��\�����̐���ݒ�
			m_level_star_num = 1;
		}
	}


	//���ȉ��͊e�G�f���֌W�Ȃ��s�����ʏ���
	//��1�s��
	//�G�f���ڍא����摜��122�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�퓬�������\\�f����.png", 122, TEX_SIZE_512);

	//�G�f���ڍא����摜�̐؂���ʒu��ݒ�
	m_detail_message_clip_right[0] = 342.0f;
	m_detail_message_clip_bottom[0] = 90.0f;

	//�G�f���ڍא����摜�̕`��ʒu(right)��ݒ�(�S�p�ꕶ���̑傫����25.0f)
	m_detail_message_draw_right[0] = m_detail_message_draw_left + 89.0f;


	//��2�s��
	//�G�f���ڍא����摜��123�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�퓬�������\\��Փx.png", 123, TEX_SIZE_512);

	//�G�f���ڍא����摜�̐؂���ʒu��ݒ�
	m_detail_message_clip_right[1] = 367.0f;
	m_detail_message_clip_bottom[1] = 117.0f;

	//�G�f���ڍא����摜�̕`��ʒu(right)��ݒ�(�S�p�ꕶ���̑傫����25.0f)
	m_detail_message_draw_right[1] = m_detail_message_draw_left + 75.0f;


	//��3�s��
	//�G�f���ڍא����摜��124�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�퓬�������\\�擾�\�Ȏ��ށE�Z.png", 124, TEX_SIZE_512);

	//�G�f���ڍא����摜�̐؂���ʒu��ݒ�
	m_detail_message_clip_right[2] = 1117.0f;
	m_detail_message_clip_bottom[2] = 117.0f;

	//�G�f���ڍא����摜�̕`��ʒu(right)��ݒ�(�S�p�ꕶ���̑傫����25.0f)
	m_detail_message_draw_right[2] = m_detail_message_draw_left + 225.0f;



	m_detail_message_alpha = 1.0f;//�G�f���ڍא�����\��

	//���N���b�N���ꂽ��t���O�𗧂āA�ŏI�m�F�E�C���h�E���J��
	if (m_mou_l == true && g_tutorial_progress != 1)
	{
		//���N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
		if (m_key_lf == true)
		{
			m_key_lf = false;

			m_detail_message_alpha = 0.0f;//�G�f���ڍא������\���ɂ���

			g_Challenge_enemy = enemy_id;//�}�E�X�I�𒆂̓G�f�����ʔԍ����擾

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

//---Special_message�֐�
//����1�@int special_id	:�X�y�V�����Z�A�C�R�����ʔԍ�(0:�G�N�X�v���[�W�����@1:�t���N�`���[���C�@2:�C���[�^���e�B�@3:�I�[�o�[���[�N�@4:���~�b�g�u���C�N)
//�����e
//�}�E�X�őI�����Ă���X�y�V�����Z�A�C�R�������ł��邩�����ʂ��A
//����ɑΉ�����X�y�V�����Z�ڍא�����\������B
void CObjPreparation::Special_message(int special_id)
{
	//�`���[�g���A�����͎��s���Ȃ�
	if (g_tutorial_progress == 1 || g_tutorial_progress == 2)
	{
		return;
	}

	//���X�y�V�����Z�A�C�R�������F(���K��)�̎��̏���
	if (m_Special_icon_color[special_id] == 0.0f)
	{
		//�X�y�V�����Z�ڍא����E�C���h�E�̃T�C�Y��ݒ�
		m_detail_message_window_top = -50.0f;
		m_detail_message_window_left = -50.0f;
		m_detail_message_window_right = 50.0f;
		m_detail_message_window_bottom = 0.0f;

		//�X�y�V�����Z�ڍא����摜�̕`��ʒu(right�ȊO)��ݒ�
		m_detail_message_draw_left = -38.0f;
		m_detail_message_draw_y = -113.0f;

		//��3�s��
		//�X�y�V�����Z�ڍא����摜��124�Ԃɓo�^
		Draw::LoadImage(L"img\\�e�L�X�g\\�X�y�V�����Z\\���K��.png", 124, TEX_SIZE_512);

		//�X�y�V�����Z�ڍא����摜�̐؂���ʒu��ݒ�
		m_detail_message_clip_right[2] = 352.0f;
		m_detail_message_clip_bottom[2] = 112.0f;

		//�X�y�V�����Z�ڍא����摜�̕`��ʒu(right)��ݒ�(�S�p�ꕶ���̑傫����25.0f)
		m_detail_message_draw_right[2] = m_detail_message_draw_left + 75.0f;

		//3�s�ڈȊO�̉摜�̕`��ʒuright��left�Ɠ����ɂ��鎖�ŕ\�����Ȃ�����
		for (int i = 0; i < DETAIL_MES_MAX_FONT_LINE; i++)
		{
			if (i != 2)
			{
				m_detail_message_draw_right[i] = m_detail_message_draw_left;
			}
		}

		//��Փx����\�����Ȃ��悤�ɂ���
		m_level_star_num = 0;
	}
	//���X�y�V�����Z�A�C�R�����D�F(�N���b�N�ő�����)�A�������͔��F(������)�̎��̏���
	else  //(m_Special_icon_color[special_id] == 0.4f || m_Special_icon_color[special_id] == 1.0f)
	{
		//�X�y�V�����Z�ڍא����E�C���h�E�̃T�C�Y��ݒ�
		m_detail_message_window_top = -205.0f;
		m_detail_message_window_left = -150.0f;
		m_detail_message_window_right = 150.0f;
		m_detail_message_window_bottom = 0.0f;

		//�X�y�V�����Z�ڍא����t�H���g�̈ʒu(right�ȊO)��ݒ�
		m_detail_message_draw_left = -138.0f;
		m_detail_message_draw_y = -225.0f;


		//���ȉ��͊D�F�A���F�̂ǂ���ł��s�����ʏ���
		//�X�y�V�����Z�ڍא����t�H���g�ݒ�
		if (special_id == 0)
		{
			//��2�s��
			//�X�y�V�����Z�ڍא����摜��123�Ԃɓo�^
			Draw::LoadImage(L"img\\�e�L�X�g\\�X�y�V�����Z\\�G�N�X�v���[�W����.png", 123, TEX_SIZE_512);

			//�X�y�V�����Z�ڍא����摜�̐؂���ʒu��ݒ�
			m_detail_message_clip_right[1] = 1072.0f;
			m_detail_message_clip_bottom[1] = 112.0f;

			//�X�y�V�����Z�ڍא����摜�̕`��ʒu(right)��ݒ�(�S�p�ꕶ���̑傫����25.0f)
			m_detail_message_draw_right[1] = m_detail_message_draw_left + 225.0f;


			//��3�s��
			//�X�y�V�����Z�ڍא����摜��124�Ԃɓo�^
			Draw::LoadImage(L"����̘f����.png", 124, TEX_SIZE_512);

			//�X�y�V�����Z�ڍא����摜�̐؂���ʒu��ݒ�
			m_detail_message_clip_right[2] = 713.0f;
			m_detail_message_clip_bottom[2] = 112.0f;

			//�X�y�V�����Z�ڍא����摜�̕`��ʒu(right)��ݒ�(�S�p�ꕶ���̑傫����25.0f)
			m_detail_message_draw_right[2] = m_detail_message_draw_left + 150.0f;


			//��4�s��
			//�X�y�V�����Z�ڍא����摜��125�Ԃɓo�^
			Draw::LoadImage(L"�Œ�_���[�W��^����.png", 125, TEX_SIZE_512);

			//�X�y�V�����Z�ڍא����摜�̐؂���ʒu��ݒ�
			m_detail_message_clip_right[3] = 1182.0f;
			m_detail_message_clip_bottom[3] = 112.0f;

			//�X�y�V�����Z�ڍא����摜�̕`��ʒu(right)��ݒ�(�S�p�ꕶ���̑傫����25.0f)
			m_detail_message_draw_right[3] = m_detail_message_draw_left + 250.0f;
		}
		else if (special_id == 1)
		{
			//��2�s��
			//�X�y�V�����Z�ڍא����摜��123�Ԃɓo�^
			Draw::LoadImage(L"img\\�e�L�X�g\\�X�y�V�����Z\\�t���N�`���[���C.png", 123, TEX_SIZE_512);

			//�X�y�V�����Z�ڍא����摜�̐؂���ʒu��ݒ�
			m_detail_message_clip_right[1] = 952.0f;
			m_detail_message_clip_bottom[1] = 112.0f;

			//�X�y�V�����Z�ڍא����摜�̕`��ʒu(right)��ݒ�(�S�p�ꕶ���̑傫����25.0f)
			m_detail_message_draw_right[1] = m_detail_message_draw_left + 200.0f;


			//��3�s��
			//�X�y�V�����Z�ڍא����摜��124�Ԃɓo�^
			Draw::LoadImage(L"�I�����C�����.png", 124, TEX_SIZE_512);

			//�X�y�V�����Z�ڍא����摜�̐؂���ʒu��ݒ�
			m_detail_message_clip_right[2] = 832.0f;
			m_detail_message_clip_bottom[2] = 112.0f;

			//�X�y�V�����Z�ڍא����摜�̕`��ʒu(right)��ݒ�(�S�p�ꕶ���̑傫����25.0f)
			m_detail_message_draw_right[2] = m_detail_message_draw_left + 175.0f;


			//��4�s��
			//�X�y�V�����Z�ڍא����摜��125�Ԃɓo�^
			Draw::LoadImage(L"����|�b�h����j�󂷂�.png", 125, TEX_SIZE_512);

			//�X�y�V�����Z�ڍא����摜�̐؂���ʒu��ݒ�
			m_detail_message_clip_right[3] = 1304.0f;
			m_detail_message_clip_bottom[3] = 112.0f;

			//�X�y�V�����Z�ڍא����摜�̕`��ʒu(right)��ݒ�(�S�p�ꕶ���̑傫����25.0f)
			m_detail_message_draw_right[3] = m_detail_message_draw_left + 275.0f;
		}
		else if (special_id == 2)
		{
			//��2�s��
			//�X�y�V�����Z�ڍא����摜��123�Ԃɓo�^
			Draw::LoadImage(L"img\\�e�L�X�g\\�X�y�V�����Z\\�C���[�^���e�B.png", 123, TEX_SIZE_512);

			//�X�y�V�����Z�ڍא����摜�̐؂���ʒu��ݒ�
			m_detail_message_clip_right[1] = 817.0f;
			m_detail_message_clip_bottom[1] = 112.0f;

			//�X�y�V�����Z�ڍא����摜�̕`��ʒu(right)��ݒ�(�S�p�ꕶ���̑傫����25.0f)
			m_detail_message_draw_right[1] = m_detail_message_draw_left + 175.0f;


			//��3�s��
			//�X�y�V�����Z�ڍא����摜��124�Ԃɓo�^
			Draw::LoadImage(L"��10�b��.png", 124, TEX_SIZE_512);

			//�X�y�V�����Z�ڍא����摜�̐؂���ʒu��ݒ�
			m_detail_message_clip_right[2] = 532.0f;
			m_detail_message_clip_bottom[2] = 112.0f;

			//�X�y�V�����Z�ڍא����摜�̕`��ʒu(right)��ݒ�(�S�p�ꕶ���̑傫����25.0f)
			m_detail_message_draw_right[2] = m_detail_message_draw_left + 100.0f;


			//��4�s��
			//�X�y�V�����Z�ڍא����摜��125�Ԃɓo�^
			Draw::LoadImage(L"���G�ƂȂ�.png", 125, TEX_SIZE_512);

			//�X�y�V�����Z�ڍא����摜�̐؂���ʒu��ݒ�
			m_detail_message_clip_right[3] = 584.0f;
			m_detail_message_clip_bottom[3] = 112.0f;

			//�X�y�V�����Z�ڍא����摜�̕`��ʒu(right)��ݒ�(�S�p�ꕶ���̑傫����25.0f)
			m_detail_message_draw_right[3] = m_detail_message_draw_left + 125.0f;
		}
		else if (special_id == 3)
		{
			//��2�s��
			//�X�y�V�����Z�ڍא����摜��123�Ԃɓo�^
			Draw::LoadImage(L"img\\�e�L�X�g\\�X�y�V�����Z\\�I�[�o�[���[�N.png", 123, TEX_SIZE_512);

			//�X�y�V�����Z�ڍא����摜�̐؂���ʒu��ݒ�
			m_detail_message_clip_right[1] = 832.0f;
			m_detail_message_clip_bottom[1] = 112.0f;

			//�X�y�V�����Z�ڍא����摜�̕`��ʒu(right)��ݒ�(�S�p�ꕶ���̑傫����25.0f)
			m_detail_message_draw_right[1] = m_detail_message_draw_left + 175.0f;


			//��3�s��
			//�X�y�V�����Z�ڍא����摜��124�Ԃɓo�^
			Draw::LoadImage(L"10�b�ԃ|�b�h���Y���x.png", 124, TEX_SIZE_512);

			//�X�y�V�����Z�ڍא����摜�̐؂���ʒu��ݒ�
			m_detail_message_clip_right[2] = 1252.0f;
			m_detail_message_clip_bottom[2] = 112.0f;

			//�X�y�V�����Z�ڍא����摜�̕`��ʒu(right)��ݒ�(�S�p�ꕶ���̑傫����25.0f)
			m_detail_message_draw_right[2] = m_detail_message_draw_left + 262.5f;


			//��4�s��
			//�X�y�V�����Z�ڍא����摜��125�Ԃɓo�^
			Draw::LoadImage(L"�~�T�C�����Y���xUP.png", 125, TEX_SIZE_512);

			//�X�y�V�����Z�ڍא����摜�̐؂���ʒu��ݒ�
			m_detail_message_clip_right[3] = 1134.0f;
			m_detail_message_clip_bottom[3] = 112.0f;

			//�X�y�V�����Z�ڍא����摜�̕`��ʒu(right)��ݒ�(�S�p�ꕶ���̑傫����25.0f)
			m_detail_message_draw_right[3] = m_detail_message_draw_left + 237.5f;
		}
		else  //(special_id == 4)
		{
			//��2�s��
			//�X�y�V�����Z�ڍא����摜��123�Ԃɓo�^
			Draw::LoadImage(L"���~�b�g�u���C�N.png", 123, TEX_SIZE_512);

			//�X�y�V�����Z�ڍא����摜�̐؂���ʒu��ݒ�
			m_detail_message_clip_right[1] = 952.0f;
			m_detail_message_clip_bottom[1] = 112.0f;

			//�X�y�V�����Z�ڍא����摜�̕`��ʒu(right)��ݒ�(�S�p�ꕶ���̑傫����25.0f)
			m_detail_message_draw_right[1] = m_detail_message_draw_left + 200.0f;


			//��3�s��
			//�X�y�V�����Z�ڍא����摜��124�Ԃɓo�^
			Draw::LoadImage(L"�o������.png", 124, TEX_SIZE_512);

			//�X�y�V�����Z�ڍא����摜�̐؂���ʒu��ݒ�
			m_detail_message_clip_right[2] = 464.0f;
			m_detail_message_clip_bottom[2] = 112.0f;

			//�X�y�V�����Z�ڍא����摜�̕`��ʒu(right)��ݒ�(�S�p�ꕶ���̑傫����25.0f)
			m_detail_message_draw_right[2] = m_detail_message_draw_left + 100.0f;


			//��4�s��
			//�X�y�V�����Z�ڍא����摜��125�Ԃɓo�^
			Draw::LoadImage(L"�|�b�h5�@�̍U����UP.png", 125, TEX_SIZE_512);

			//�X�y�V�����Z�ڍא����摜�̐؂���ʒu��ݒ�
			m_detail_message_clip_right[3] = 1222.0f;
			m_detail_message_clip_bottom[3] = 112.0f;

			//�X�y�V�����Z�ڍא����摜�̕`��ʒu(right)��ݒ�(�S�p�ꕶ���̑傫����25.0f)
			m_detail_message_draw_right[3] = m_detail_message_draw_left + 262.5f;
		}
		

		//1�s�ڂ�5�s�ڂ͎g�p���Ȃ��̂ŁA
		//���̍s�̉摜�̕`��ʒuright��left�Ɠ����ɂ��鎖�ŕ\�����Ȃ�����
		m_detail_message_draw_right[0] = m_detail_message_draw_left;
		m_detail_message_draw_right[4] = m_detail_message_draw_left;

		//��Փx����\�����Ȃ��悤�ɂ���
		m_level_star_num = 0;


		//���ȉ��̓X�y�V�����Z�A�C�R�����D�F(�N���b�N�ő�����)�̎��̂ݍs������
		if (m_Special_icon_color[special_id] == 0.4f)
		{
			//��6�s��
			//�X�y�V�����Z�ڍא����摜��127�Ԃɓo�^
			Draw::LoadImage(L"�N���b�N�ő�����.png", 127, TEX_SIZE_512);

			//�X�y�V�����Z�ڍא����摜�̐؂���ʒu��ݒ�
			m_detail_message_clip_right[5] = 952.0f;
			m_detail_message_clip_bottom[5] = 112.0f;

			//�X�y�V�����Z�ڍא����摜�̕`��ʒu(right)��ݒ�(�S�p�ꕶ���̑傫����25.0f)
			m_detail_message_draw_right[5] = m_detail_message_draw_left + 200.0f;

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

					//�I����
					Audio::Start(1);
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
			//��6�s��
			//�X�y�V�����Z�ڍא����摜��127�Ԃɓo�^
			Draw::LoadImage(L"img\\�e�L�X�g\\�X�y�V�����Z\\������.png", 127, TEX_SIZE_512);

			//�X�y�V�����Z�ڍא����摜�̐؂���ʒu��ݒ�
			m_detail_message_clip_right[5] = 352.0f;
			m_detail_message_clip_bottom[5] = 112.0f;

			//�X�y�V�����Z�ڍא����摜�̕`��ʒu(right)��ݒ�(�S�p�ꕶ���̑傫����25.0f)
			m_detail_message_draw_right[5] = m_detail_message_draw_left + 75.0f;

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

					//�߂�{�^����
					Audio::Start(2);
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
