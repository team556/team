//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "Call_Planet.h"
#include "UtilityModule.h"

#include <stdlib.h>
#include <time.h>

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�}�N��
//���J�n���Ԃ����炷���Řf���̏o���^�C�~���O���ϓ��ɂ���B
#define ENEMY_PLANET1_START_TIME (1300) //�G�f��1(�w�i)�̊J�n����
#define ENEMY_PLANET2_START_TIME (800)  //�G�f��2(�w�i)�̊J�n����
#define ENEMY_PLANET3_START_TIME (300)  //�G�f��3(�w�i)�̊J�n����
#define INI_ALPHA (0.0f) //���ߓx(�A���t�@�l)�̏����l
#define INI_COLOR (0.9f) //�S�J���[���x�̏����l(�A�C�R�����I�𒆂̃J���[)

//�C�j�V�����C�Y
void CObjHome::Init()
{
	m_Pvx = 0.0f;	
	m_Pvy = 0.0f;
	m_boost = 0.0f;
	m_rx = 0.0f;
	m_ry = 0.0f;
	m_size = 0.0f;

	m_Mig_time = 0;

	m_Ey[3] = {};//�S�Ă̗v�f�̒l��0�ŏ��������Ă���
	m_time[0] = ENEMY_PLANET1_START_TIME;
	m_time[1] = ENEMY_PLANET2_START_TIME;
	m_time[2] = ENEMY_PLANET3_START_TIME;
	m_Enemy_id = 0;
	m_Planet_id = 0;
	m_speed = 0;

	m_Tra_move = 0.0f;
	m_Eat_move = 0.0f;
	m_Tra_color = INI_COLOR;
	m_Eat_color = INI_COLOR;
	m_alpha = INI_ALPHA;
	m_Tra_flag = false;
	m_Eat_flag = false;
	m_status_flag = false;

	m_special_clip_right = 0.0f;
	m_special_clip_bottom = 0.0f;
	m_special_draw_left = 0.0f;
	m_special_draw_right = 0.0f;

	m_mou_x = 0.0f;
	m_mou_y = 0.0f;
	m_mou_r = false;
	m_mou_l = false;

	m_key_f = false;

	srand(time(NULL));//�����_������������
}

//�A�N�V����
void CObjHome::Action()
{
	//�`���[�g���A�����͑�����󂯕t���Ȃ��悤�ɂ���B
	if (g_is_operatable == false)
	{
		return;
	}

	//��A�C�R���A�������͋�A�C�R���N���b�N�����s
	if (m_Tra_flag == true || m_Eat_flag == true)
	{
		//����A�C�R���N���b�N����
		if (m_Tra_flag == true)
		{
			//�v���C���[�f�����g��A���A�C�R�������ꂼ���ʊO�ֈړ�������Y�[�����o�A
			//�_����ʑS�̂𕢂��B�������𓯎��ɍs���B
			if (m_size >= 2000.0f)
			{
				//�_����ʑS�̂����S�ɕ����B�����^�C�~���O(m_size��2000.0f�ȏ�)�ŏ�L�̏������I�����A
				//������m_Mig_time���쓮�����A��0.5�b��(m_Mig_time��20����)�ɃV�[���ڍs���s��
				m_Mig_time++;

				if (m_Mig_time > 20)
				{
					Scene::SetScene(new CSceneTraining());//�琬��ʂփV�[���ڍs
				}
			}
			//�_���o�I�u�W�F�N�g�𕡐��������Ȃ����߂̏�������
			else if (m_size > 0.0f)
			{
				m_size += 20.0f;
				m_Tra_move += 5.0f;
				m_Eat_move += 5.0f;
			}
			else
			{
				m_size += 20.0f;
				m_Tra_move += 5.0f;
				m_Eat_move += 5.0f;

				//�_���o�I�u�W�F�N�g(�_���oIN)
				CObjCloud_Effect* obj_cloud = new CObjCloud_Effect(true);	//�_���o�I�u�W�F�N�g�쐬
				Objs::InsertObj(obj_cloud, OBJ_CLOUD, 100);					//�_���o�I�u�W�F�N�g�o�^
			}
		}
		//����A�C�R���N���b�N����
		else //(m_Eat_flag == true)
		{
			//���A�C�R���A�G�f��(�w�i)�����X�ɔ�\���ɂ���
			if (m_alpha > 0.0f)
			{
				m_alpha -= 0.01f;
			}

			//�v���C���[�f���ړ����o
			if (m_Pvx < -750.0f)
			{
				//��ʊO�ɏo�����߁A�ړ����~������
				//���̌�m_Mig_time���쓮�����A��1�b��(m_Mig_time��60����)�ɃV�[���ڍs���s��
				m_Mig_time++;

				if (m_Mig_time > 60)
				{
					Scene::SetScene(new CScenePreparation());//�퓬������ʂփV�[���ڍs
				}
			}
			else //��ʓ��ɂ��邽�߁A�ړ����s��
			{
				//���v���C���[�f��X�ړ�����
				//�p�x���Z
				m_rx += 1.0f;

				//360���ŏ����l�ɖ߂�
				if (m_rx > 360.0f)
					m_rx = 0.0f;

				//�ړ�����
				m_Pvx = sin(3.14f / 90 * m_rx);

				//���x�t����B
				m_Pvx *= 80.0f + m_boost;

				//X�ړ����x���ړ��x�N�g��X�̏󋵂ɉ����đ���������
				if (m_Pvx < 0.0f)
				{
					m_boost += 24.0f;
				}
				else
				{
					m_boost += 6.0f;
				}


				//���v���C���[�f��Y�ړ�����
				//�p�x���Z
				m_ry += 2.0f;

				//360���ŏ����l�ɖ߂�
				if (m_ry > 360.0f)
					m_ry = 0.0f;

				//�ړ�����
				m_Pvy = sin(3.14f / 90 * m_ry);

				//���x�t����B
				m_Pvy *= 80.0f;
			}
		}

		return;
	}


	//�}�E�X�̈ʒu���擾
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//�}�E�X�̃{�^���̏��
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	//���A�C�R���A�G�f��(�w�i)�����X�ɕ\��������
	if (m_alpha < 1.0f && (g_tutorial_progress == 1 || g_tutorial_progress >= 8))
	{
		m_alpha += 0.01f;
	}

	//��A�C�R��
	if (20 < m_mou_x && m_mou_x < 220 && 480 < m_mou_y && m_mou_y < 680 && (g_tutorial_progress >= 8))
	{
		m_Tra_color = 1.0f;

		//���N���b�N���ꂽ��t���O�𗧂āA�琬��ʂ։��o�������Ȃ���V�[���ڍs
		if (m_mou_l == true)
		{
			//�N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
			if (m_key_f == true)
			{
				m_key_f = false;

				m_Tra_flag = true;

				//ObjHelp�ɃV�[���ڍs���o��`����
				//CObjHelp* help = (CObjHelp*)Objs::GetObj(OBJ_HELP);
				//help->SetMig_stageF();
				//help->SetTra_EatF(true);

				if (g_tutorial_progress == 8)
				{
					//�����\���ɂ�����
					CObjMessage* message = (CObjMessage*)Objs::GetObj(OBJ_MESSAGE);
					message->Setarrow(0);
				}

				//�I����
				Audio::Start(1);
			}
		}
		else
		{
			m_key_f = true;
		}
	}
	else
	{
		m_Tra_color = INI_COLOR;
	}

	//��A�C�R��
	if (980 < m_mou_x && m_mou_x < 1180 && 480 < m_mou_y && m_mou_y < 680 && (g_tutorial_progress == 1 || g_tutorial_progress >= 15))
	{
		m_Eat_color = 1.0f;

		//���N���b�N���ꂽ��t���O�𗧂āA�퓬������ʂ։��o�������Ȃ���V�[���ڍs
		if (m_mou_l == true)
		{	
			//�N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
			if (m_key_f == true)
			{
				m_key_f = false;

				m_Eat_flag = true;

				//ObjHelp�ɃV�[���ڍs���o��`����
				//CObjHelp* help = (CObjHelp*)Objs::GetObj(OBJ_HELP);
				//help->SetMig_stageF();
				//help->SetTra_EatF(false);

				if (g_tutorial_progress == 1)
				{
					//�����\���ɂ�����
					CObjMessage* message = (CObjMessage*)Objs::GetObj(OBJ_MESSAGE);
					message->Setarrow(0);
				}

				//�I����
				Audio::Start(1);
			}
		}
		else
		{
			m_key_f = true;
		}
	}
	else
	{
		m_Eat_color = INI_COLOR;
	}

	//�v���C���[�f���Ƀ}�E�X�J�[�\�������킳��ƁA
	//�v���C���[�f���̃X�e�[�^�X��\������
	//�����킳���Ă��Ȃ��ꍇ�͔�\���ɂ���
	if (450 < m_mou_x && m_mou_x < 750 && 250 < m_mou_y && m_mou_y < 550)
	{
		m_status_flag = true;	//�X�e�[�^�X�\���t���OON
	}
	else
	{
		m_status_flag = false;	//�X�e�[�^�X�\���t���OOFF
	}

	//Z�L�[�������Ă���ԁA�G�f��(�w�i)�̈ړ����x�������Ȃ�(�f�o�b�O�p)
	//���X�̓f�o�b�O�݂̂̎g�p���������A�B���v�f�Ƃ��������Ŏc���Ă����Ă��ǂ������B
	if (Input::GetVKey('Z') == true)
	{
		m_speed = 10;
	}
	else
	{
		m_speed = 0;
	}
}

//�h���[
void CObjHome::Draw()
{
	//�`��J���[���  R=RED  G=Green  B=Blue A=alpha(���ߏ��)
	//�G�f��(�w�i)�p
	float p[4] = { 1.0f,1.0f,1.0f,m_alpha };

	//��A�C�R���p
	float t[4] = { m_Tra_color,m_Tra_color,m_Tra_color,m_alpha };

	//��A�C�R���p
	float e[4] = { m_Eat_color,m_Eat_color,m_Eat_color,m_alpha };

	//�v���C���[�f���X�e�[�^�X�̃t�H���g�J���[�p
	float status_font_color[4][4] =
	{
		{ 1.0f,1.0f,1.0f,1.0f },//1�s�ڂ͔��F
		{ 1.0f,1.0f,1.0f,1.0f },//2�s�ڂ͔��F
		{ 1.0f,1.0f,1.0f,1.0f },//3�s�ڂ͔��F
		{ 1.0f,0.0f,0.0f,1.0f },//4�s�ڂ͐ԐF
	};

	//����ȊO�̉摜�p
	float d[4] = { 1.0f,1.0f,1.0f,1.0f };

	//���t�H���g����
	//�v���C���[�f���X�e�[�^�X�̃t�H���g�p
	wchar_t status_font[3][13];										//13�������i�[�\�ȕ����z���3�錾
	swprintf_s(status_font[0], L"�f��HP�F%.0f", g_Player_max_size);	//�����z��ɕ����f�[�^������
	swprintf_s(status_font[1], L"�������̃X�y�V�����Z�F");			//�����z��ɕ����f�[�^������


	//�����ݑ������̃X�y�V�����Z�����摜��ǂݍ���127�Ԃɓo�^����
	switch (g_Special_equipment)
	{
	case 1:
		//�G�N�X�v���[�W���������摜��ǂݍ���127�Ԃɓo�^
		Draw::LoadImage(L"img\\�e�L�X�g\\�X�y�V�����Z\\�G�N�X�v���[�W����.png", 127, TEX_SIZE_512);

		//�؂���ʒu��ݒ肷��
		m_special_clip_right = 1072.0f;
		m_special_clip_bottom = 112.0f;

		//�`��ʒu��ݒ肷��
		m_special_draw_left = 33.0f;
		m_special_draw_right = 260.0f;

		break;
	case 2:
		//�t���N�`���[���C�����摜��ǂݍ���127�Ԃɓo�^
		Draw::LoadImage(L"img\\�e�L�X�g\\�X�y�V�����Z\\�t���N�`���[���C.png", 127, TEX_SIZE_512);

		//�؂���ʒu��ݒ肷��
		m_special_clip_right = 952.0f;
		m_special_clip_bottom = 112.0f;

		//�`��ʒu��ݒ肷��
		m_special_draw_left = 33.0f;
		m_special_draw_right = 235.0f;

		break;
	case 3:
		//�C���[�^���e�B�����摜��ǂݍ���127�Ԃɓo�^
		Draw::LoadImage(L"img\\�e�L�X�g\\�X�y�V�����Z\\�C���[�^���e�B.png", 127, TEX_SIZE_512);

		//�؂���ʒu��ݒ肷��
		m_special_clip_right = 817.0f;
		m_special_clip_bottom = 112.0f;

		//�`��ʒu��ݒ肷��
		m_special_draw_left = 33.0f;
		m_special_draw_right = 210.0f;

		break;
	case 4:
		//�I�[�o�[���[�N�����摜��ǂݍ���127�Ԃɓo�^
		Draw::LoadImage(L"img\\�e�L�X�g\\�X�y�V�����Z\\�I�[�o�[���[�N.png", 127, TEX_SIZE_512);

		//�؂���ʒu��ݒ肷��
		m_special_clip_right = 832.0f;
		m_special_clip_bottom = 112.0f;

		//�`��ʒu��ݒ肷��
		m_special_draw_left = 33.0f;
		m_special_draw_right = 210.0f;

		break;
	case 5:
		//���~�b�g�u���C�N�����摜��ǂݍ���127�Ԃɓo�^
		Draw::LoadImage(L"���~�b�g�u���C�N.png", 127, TEX_SIZE_512);

		//�؂���ʒu��ݒ肷��
		m_special_clip_right = 952.0f;
		m_special_clip_bottom = 112.0f;

		//�`��ʒu��ݒ肷��
		m_special_draw_left = 33.0f;
		m_special_draw_right = 235.0f;

		break;
	default:
		//�����������摜��ǂݍ���127�Ԃɓo�^
		Draw::LoadImage(L"img\\�e�L�X�g\\�X�y�V�����Z\\������.png", 127, TEX_SIZE_512);

		//�؂���ʒu��ݒ肷��
		m_special_clip_right = 367.0f;
		m_special_clip_bottom = 117.0f;

		//�`��ʒu��ݒ肷��
		m_special_draw_left = 33.0f;
		m_special_draw_right = 108.0f;

		break;
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

	//���G�f��(�w�i)�\��
	//1500�ɓ��B����܂ŁA���ꂼ��4�����Z����Ă����B
	//Z�L�[�������Ɖ��Z�ʂ��㏸����
	m_time[0] += 4 + m_speed;
	m_time[1] += 4 + m_speed;
	m_time[2] += 4 + m_speed;

	//m_time��1500�ɓ��B����ƁA�ȉ��̏��������s�����B
	//�G�f��(�w�i)�̊J�n���Ԃ̍��ɂ��A
	//�K���G�f��1��2��3��1���c�c�̏��ɁA���̏����ɓ���悤�ɂ��Ă���B
	if (m_time[m_Enemy_id] >= 1500)
	{
		m_time[m_Enemy_id] = 0;//���̏����ɓ����Ă���m_time��0�ɖ߂��B

		m_Planet_id = rand() % 4 + 1;//1�`4�̒l�������_���擾���A�ȉ��̊֐��ŗ��p����B

		//�f���O���t�B�b�N���擾����֐�(Call_Planet)���Ăяo���B
		//����1�ɂ��̏����ɓ����Ă����G�f���̎��ʔԍ������A
		//����2�ɐ���擾����1�`4�̃����_���l�����鎖�ŁA
		//���ꂼ��̓G�f���ɓK�����������_���Șf���f�[�^���擾���Ă���B
		Call_Planet(m_Enemy_id, m_Planet_id);

		m_Ey[m_Enemy_id] = rand() % 501 + 100;//100�`600�̒l�������_���擾���A�G�f��(�w�i)��Y���W�Ƃ���B

		//���̓G�f���̏������s���ׂɁAid�����̓G�f���̂��̂ɂ��Ă����B
		if (m_Enemy_id == 2)
		{
			m_Enemy_id = 0;
		}
		else
		{
			m_Enemy_id++;
		}
	}

	//�G�f��1(�w�i)�\��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 300.0f;
	src.m_bottom = 300.0f;

	dst.m_top = m_Ey[0];
	dst.m_left = 1200.0f - m_time[0];//+4��������������ϐ����������ŁA
	dst.m_right = 1250.0f - m_time[0];//�O���t�B�b�N���E���獶�ֈړ������Ă���B
	dst.m_bottom = m_Ey[0] + 50.0f;
	Draw::Draw(20, &src, &dst, p, 0.0f);

	//�G�f��2(�w�i)�\��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 300.0f;
	src.m_bottom = 300.0f;

	dst.m_top = m_Ey[1];
	dst.m_left = 1200.0f - m_time[1];//+4��������������ϐ����������ŁA
	dst.m_right = 1250.0f - m_time[1];//�O���t�B�b�N���E���獶�ֈړ������Ă���B
	dst.m_bottom = m_Ey[1] + 50.0f;
	Draw::Draw(22, &src, &dst, p, 0.0f);

	//�G�f��3(�w�i)�\��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 300.0f;
	src.m_bottom = 300.0f;

	dst.m_top = m_Ey[2];
	dst.m_left = 1200.0f - m_time[2];//+4��������������ϐ����������ŁA
	dst.m_right = 1250.0f - m_time[2];//�O���t�B�b�N���E���獶�ֈړ������Ă���B
	dst.m_bottom = m_Ey[2] + 50.0f;
	Draw::Draw(24, &src, &dst, p, 0.0f);

	//���v���C���[�f���\��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 448.0f;
	src.m_bottom = 448.0f;

	dst.m_top = 250.0f + m_Pvy - m_size;
	dst.m_left = 450.0f + m_Pvx - m_size;
	dst.m_right = 750.0f + m_Pvx + m_size;
	dst.m_bottom = 550.0f + m_Pvy + m_size;
	Draw::Draw(50 + ((int)((g_Bar_Level + g_Ins_Level) / 2)) - 1, &src, &dst, d, 0.0f);

	if (g_tutorial_progress >= 8)
	{
		//����A�C�R���\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 200.0f;
		src.m_bottom = 200.0f;

		dst.m_top = 480.0f + m_Tra_move;
		dst.m_left = 20.0f - m_Tra_move;
		dst.m_right = 220.0f - m_Tra_move;
		dst.m_bottom = 680.0f + m_Tra_move;
		Draw::Draw(1, &src, &dst, t, 0.0f);
	}

	if (g_tutorial_progress == 1 || g_tutorial_progress >= 15)
	{
		//����A�C�R���\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 200.0f;
		src.m_bottom = 200.0f;

		dst.m_top = 480.0f + m_Eat_move;
		dst.m_left = 980.0f + m_Eat_move;
		dst.m_right = 1180.0f + m_Eat_move;
		dst.m_bottom = 680.0f + m_Eat_move;
		Draw::Draw(2, &src, &dst, e, 0.0f);
	}

	//�v���C���[�f���X�e�[�^�X�\��(�t���Otrue���̂ݕ`��)
	if (m_status_flag == true)
	{
		////���E�C���h�E�\������ 
		//src.m_top = 0.0f;
		//src.m_left = 0.0f;
		//src.m_right = 800.0f;
		//src.m_bottom = 790.0f;

		//dst.m_top = m_mou_y - 125.0f;
		//dst.m_left = m_mou_x + 20.0f;
		//dst.m_right = m_mou_x + 120.0f;
		//dst.m_bottom = m_mou_y - 65.0f;
		//Draw::Draw(6, &src, &dst, d, 0.0f);

		////���E�C���h�E�\������
		//src.m_top = 30.0f;
		//src.m_left = 800.0f;
		//src.m_right = 1600.0f;
		//src.m_bottom = 795.0f;

		//dst.m_top = m_mou_y - 65.0f;
		//dst.m_left = m_mou_x + 20.0f;
		//dst.m_right = m_mou_x + 120.0f;
		//dst.m_bottom = m_mou_y + 45.0f;
		//Draw::Draw(6, &src, &dst, d, 0.0f);

		////���E�C���h�E�\�������� 
		//src.m_top = 0.0f;
		//src.m_left = 1600.0f;
		//src.m_right = 2400.0f;
		//src.m_bottom = 795.0f;

		//dst.m_top = m_mou_y - 125.0f;
		//dst.m_left = m_mou_x + 120.0f;
		//dst.m_right = m_mou_x + 220.0f;
		//dst.m_bottom = m_mou_y - 65.0f;
		//Draw::Draw(6, &src, &dst, d, 0.0f);

		////���E�C���h�E�\�������� 
		//src.m_top = 5.0f;
		//src.m_left = 2400.0f;
		//src.m_right = 3200.0f;
		//src.m_bottom = 800.0f;

		//dst.m_top = m_mou_y - 65.0f;
		//dst.m_left = m_mou_x + 120.0f;
		//dst.m_right = m_mou_x + 220.0f;
		//dst.m_bottom = m_mou_y + 45.0f;
		//Draw::Draw(6, &src, &dst, d, 0.0f);

		////���E�C���h�E�E��
		//src.m_top = 0.0f;
		//src.m_left = 4000.0f;
		//src.m_right = 4800.0f;
		//src.m_bottom = 795.0f;

		//dst.m_top = m_mou_y - 125.0f;
		//dst.m_left = m_mou_x + 220.0f;
		//dst.m_right = m_mou_x + 320.0f;
		//dst.m_bottom = m_mou_y - 65.0f;
		//Draw::Draw(6, &src, &dst, d, 0.0f);

		////���E�C���h�E�E��
		//src.m_top = 5.0f;
		//src.m_left = 4800.0f;
		//src.m_right = 5600.0f;
		//src.m_bottom = 800.0f;

		//dst.m_top = m_mou_y - 65.0f;
		//dst.m_left = m_mou_x + 220.0f;
		//dst.m_right = m_mou_x + 320.0f;
		//dst.m_bottom = m_mou_y + 45.0f;
		//Draw::Draw(6, &src, &dst, d, 0.0f);

		//���E�C���h�E
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1200.0f;
		src.m_bottom = 700.0f;

		dst.m_top = m_mou_y - 125.0f;
		dst.m_left = m_mou_x + 20.0f;
		dst.m_right = m_mou_x + 320.0f;
		dst.m_bottom = m_mou_y + 45.0f;
		Draw::Draw(7, &src, &dst, d, 0.0f);

		//���t�H���g�摜�\��
		//�u�f�����F�v�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 342.0f;
		src.m_bottom = 90.0f;

		dst.m_top = m_mou_y - 113.0f;
		dst.m_left = m_mou_x + 33.0f;
		dst.m_right = m_mou_x + 122.0f;
		dst.m_bottom = m_mou_y - 88.0f;
		Draw::Draw(128, &src, &dst, status_font_color[0], 0.0f);

		//�v���C���[���̕\��
		FontDraw(g_Player_Name, m_mou_x + 128.0f, m_mou_y - 113.0f, 25.0f, 25.0f, status_font_color[0], false);

		//�f��HP�����摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 412.0f;
		src.m_bottom = 112.0f;

		dst.m_top = m_mou_y - 73.0f;
		dst.m_left = m_mou_x + 33.0f;
		dst.m_right = m_mou_x + 133.0f;
		dst.m_bottom = m_mou_y  -48.0f;
		Draw::Draw(53, &src, &dst, status_font_color[1], 0.0f);

		//�������̃X�y�V�����Z�����摜
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1242.0f;
		src.m_bottom = 117.0f;

		dst.m_top = m_mou_y - 33.0f;
		dst.m_left = m_mou_x + 33.0f;
		dst.m_right = m_mou_x + 285.0f;
		dst.m_bottom = m_mou_y - 8.0f;
		Draw::Draw(54, &src, &dst, status_font_color[2], 0.0f);

		//�u�F�v��\��
		FontDraw(L"�F", m_mou_x + 133.0f, m_mou_y - 73.0f, 25.0f, 25.0f, status_font_color[1], false);
		FontDraw(L"�F", m_mou_x + 285.0f, m_mou_y - 33.0f, 25.0f, 25.0f, status_font_color[2], false);

		//���݂̍ő�f��HP��\��
		FontDraw(NumConversion((int)g_Player_max_size), m_mou_x + 158.0f, m_mou_y - 73.0f, 15.0f, 25.0f, status_font_color[1], false);

		//���ݑ������̃X�y�V�����Z[������/�G�N�X�v���[�W������]�����摜
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = m_special_clip_right;
		src.m_bottom = m_special_clip_bottom;

		dst.m_top = m_mou_y + 7.0f;
		dst.m_left = m_mou_x + m_special_draw_left;
		dst.m_right = m_mou_x + m_special_draw_right;
		dst.m_bottom = m_mou_y + 32.0f;
		Draw::Draw(127, &src, &dst, status_font_color[3], 0.0f);
	}

	//�f�o�b�O�p���}�E�X�ʒu�\��
	//wchar_t str[256];
	//swprintf_s(str, L"x=%f,y=%f", m_mou_x, m_mou_y);
	//Font::StrDraw(str, 20.0f, 20.0f, 12.0f, d);
}
