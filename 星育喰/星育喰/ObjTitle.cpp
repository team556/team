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
#define INI_ALPHA (1.0f) //���ߓx(�A���t�@�l)�̏����l
#define INI_COLOR (0.9f) //���ߓx(�A���t�@�l)�̏����l

//static�ϐ��̒�`
bool CObjTitle::after_once = false;

//�S�ẴO���[�o���ϐ��̒�`
//��ObjTitle�ł́A�O���[�o���ϐ��̒�`�Ɠ�����
//�C�j�V�����C�Y�Ń��Z�b�g�������s���Ă���ׁA
//�����l��ύX������ۂ́A
//�����ƃ��Z�b�g������2��ύX���Ȃ��Ƃ����Ȃ��̂Œ��ӁB
//���]�T����΁A�l�̕������}�N����(�o���镔����)���ĕ֗��ɂ��ׂ��B
int g_Stage_progress = 1;
bool g_destroy_progress[4] = { false,false,false,false };//�G�̌��j���
int g_Bar_Level = 1;
int g_Ins_Level = 1;
int g_Mis_Recast_Level		= 1;
int g_Pow_equip_Level		= 1;
int g_Pow_equip_Lv_achieve	= 1;
int g_Def_equip_Level		= 1;
int g_Def_equip_Lv_achieve	= 1;
int g_Spe_equip_Level		= 1;
int g_Spe_equip_Lv_achieve	= 1;
int g_Bal_equip_Level		= 1;
int g_Bal_equip_Lv_achieve	= 1;
int g_Pod_equip_Level		= 1;
int g_Pod_equip_Lv_achieve	= 1;
float g_Player_max_size = 100.0f;//100.0f;
int g_Special_equipment = 0;//�������̃X�y�V�����Z
bool g_Special_mastering[5] = { false,false,false,true,false };//�X�y�V�����Z�̏K�����
int g_Power_num		= 3000;
int g_Defense_num	= 3000;
int g_Speed_num		= 3000;
int g_Balance_num	= 3000;
int g_Research_num	=  500;
int g_Remain_num	= 0;
float g_Recast_time = 3.0f;
float g_P_Planet_damage = 0.0f;

int g_Iron_num		= 0;
int g_Wood_num		= 0;
int g_Silver_num	= 0;
int g_Plastic_num	= 0;
int g_Aluminum_num	= 0;
int g_gus_num		= 0;

int g_Challenge_enemy = 0;//�f�o�b�O�B0�ɖ߂��ׂ��B
bool g_help_f = false;
int  g_tutorial_progress = 8;//�f�o�b�O�B�`���[�g���A��������A0�ɂ���悤�ɁB
bool g_is_operatable = true;

//�C�j�V�����C�Y
void CObjTitle::Init()
{
	m_click_vy = 0.0f;	
	m_r = 0.0f;

	m_Ey[3] = {};//�S�Ă̗v�f�̒l��0�ŏ��������Ă���
	m_time[0] = ENEMY_PLANET1_START_TIME;
	m_time[1] = ENEMY_PLANET2_START_TIME;
	m_time[2] = ENEMY_PLANET3_START_TIME;
	m_Enemy_id = 0;
	m_Planet_id = 0;
	m_speed = 0;

	m_Yes_Button_color = 1.0f;
	m_No_Button_color = 1.0f;
	m_del_color = INI_COLOR;
	m_del_alpha = 0.0f;
	m_del_f = false;

	m_flag  = false;
	m_key_f = false;
	m_alpha = INI_ALPHA;

	//�����ڈȍ~�K�ꂽ���̉��o
	//�u��ʈÓ]��ԁ����]����v
	//���ڈȍ~�͂��̉��o���������ׁA
	//���񂩂����łȂ�����
	//�����l��ύX����B
	//�����ڈȍ~
	if (after_once == true)
	{
		m_black_out_a = INI_ALPHA;
	}
	//������
	else
	{
		m_black_out_a = 0.0f;
	}

	m_des_y = 200.0f;
	m_des_vec = 1.0f;
	m_des_a = 0.0f;

	m_mou_x = 0.0f;
	m_mou_y = 0.0f;
	m_mou_r = false;
	m_mou_l = false;

	srand(time(NULL));//�����_������������


	//���O���[�o���ϐ�(�S�ۑ��f�[�^)���Z�b�g����
	g_Stage_progress = 1;

	for (int i = 0; i < 4; i++)
	{
		g_destroy_progress[i] = true;
	}

	g_Bar_Level = 1;
	g_Ins_Level = 1;
	g_Mis_Recast_Level = 0;
	g_Pow_equip_Level = 1;
	g_Pow_equip_Lv_achieve = 1;
	g_Def_equip_Level = 1;
	g_Def_equip_Lv_achieve = 1;
	g_Spe_equip_Level = 1;
	g_Spe_equip_Lv_achieve = 1;
	g_Bal_equip_Level = 1;
	g_Bal_equip_Lv_achieve = 1;
	g_Pod_equip_Level = 1;
	g_Pod_equip_Lv_achieve = 1;
	g_Player_max_size = 100.0f;
	g_Special_equipment = 0;

	for (int i = 0; i < 5 && i != 3; i++)
	{
		g_Special_mastering[i] = false;
	}

	g_Power_num		= 1500;
	g_Defense_num	= 1500;
	g_Speed_num		= 1500;
	g_Balance_num	= 1500;
	g_Research_num	= 0;
	g_Remain_num	= 0;

	g_Iron_num		= 0;
	g_Wood_num		= 0;
	g_Silver_num	= 0;
	g_Plastic_num	= 0;
	g_Aluminum_num	= 0;
	g_gus_num		= 0;
}

//�A�N�V����
void CObjTitle::Action()
{
	//�}�E�X�̈ʒu���擾
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//�}�E�X�̃{�^���̏��
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	//���L�[�t���O
	//�����N���b�N�𐧌䂵�Ă���
	if (m_mou_l == false)
	{
		m_key_f = true;//�L�[�t���OON(ON�̎��ɍ��N���b�N�o����)
	}

	//���f�[�^�����ŏI�m�F�E�C���h�E�\�����̏���
	if (m_del_f == true)
	{
		//�ŏI�m�F[�͂�]�{�^��
		if (410 < m_mou_x && m_mou_x < 502 && 407 < m_mou_y && m_mou_y < 450)
		{
			m_Yes_Button_color = 0.0f;

			//���N���b�N���ꂽ��f�[�^�������A���̃E�C���h�E�����
			//���N���b�N���͎�
			if (m_mou_l == true)
			{
				//���N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
				if (m_key_f == true)
				{
					m_key_f = false;

					//�������ɏ���������������������(����ő���Ă邩�A�f�o�b�O�Ŋm���߂����B)
					g_tutorial_progress = 0;//�`���[�g���A���i�s�x��������
					after_once = false;		//���ڈȍ~���L�����Ă�ϐ���������


					m_Yes_Button_color = 1.0f;

					m_del_alpha = 1.5f;//�f�[�^���������ʒm�摜��\������

					//�ŏI�m�F�E�C���h�E���\���ɂ���
					m_del_f = false;

					//�f�[�^��H�ׂ鉹
					Audio::Start(3);
				}
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
				m_No_Button_color = 1.0f;

				//�ŏI�m�F�E�C���h�E���\���ɂ���
				m_del_f = false;

				//�߂�{�^����
				Audio::Start(2);
			}
			//���N���b�N���͎�
			else if (m_mou_l == true)
			{
				//���N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
				if (m_key_f == true)
				{
					m_key_f = false;

					m_No_Button_color = 1.0f;

					//�ŏI�m�F�E�C���h�E���\���ɂ���
					m_del_f = false;

					//�߂�{�^����
					Audio::Start(2);
				}
			}
		}
		else
		{
			m_No_Button_color = 1.0f;
		}


		return;
	}


	
	//���N���b�N�������͉E�N���b�N�Ńz�[����ʂփV�[���ڍs(���񎞂̏���)
	if (m_flag == true && after_once == false)
	{
		//�������ɏ��Ɏ��s����Ă���

		/*if ()
		{
			���O���͂̃O���[�o���ϐ��ɉ���������͂��ꂽ�̂��m�F(!= nullptr)�A
			�������͉������O���͑�������𑗂��Ă��炢�A������������ɓ����B

			���̌�A���̏������̒���
			�`���[�g���A�����X�L�b�v���邩���Ȃ������ŏI�m�F�E�C���h�E�̃��c�ŕ����B

			�m�F��A�X�L�b�v���Ȃ������A�X�L�b�v���鏈���ɕ��򂵁A
			�l�Ƃ����낢����ꂽ���
			m_black_out_a -= 0.01f;//��ʏ��X�ɖ��]
			�����s���A���S���]��A�ȉ��̏��������s����B
			//after_once = true;//�u��x�^�C�g����ʂ�K�ꂽ�v�ƋL��

			//Scene::SetScene(new CSceneHome());//�z�[����ʂփV�[���ڍs
		}
		else */if (m_alpha == 0.0f)
		{
			//���O���͒���ObjTitle�ł͉������삳���Ȃ��B
		}
		else if (m_des_y <= -550.0f)
		{
			//���O���͂̃I�u�W�F�N�g���Ăяo��

			m_alpha = 0.0f;//�^�C�g�����S�A���G�f�������\���ɂ���Ɠ����Ɏ��̏����ւ̃t���O�Ƃ��Ă���B
			Scene::SetScene(new CSceneNameInput());
		}
		else if (m_des_a > 6.0f)
		{
			//���E�ϐ����S�ĕ\�����班���o������A
			//���̑S�ĕ\��������������ʊO�̏�̕��Ɉړ�������B
			m_des_vec *= 1.01f;
			m_des_y -= m_des_vec;

			//�N���b�N�ňړ����x�㏸
			if (m_mou_l == true)
			{
				m_des_y -= m_des_vec * 10;
			}
		}
		else if (m_black_out_a > 1.2f)
		{
			m_des_a += 0.01f;//�Ó]��A���X�ɐ��E�ϐ�����\�����Ă����B

			//�N���b�N�ŕ\�����x�㏸
			if (m_mou_l == true)
			{
				m_des_a += 0.05f;
			}
		}
		else
		{
			m_black_out_a += 0.01f;//��ʏ��X�ɈÓ]
		}

		return;
	}
	//���N���b�N�������͉E�N���b�N�Ńz�[����ʂփV�[���ڍs(���ڈȍ~�̏���)
	else if (m_flag == true)
	{
		m_alpha -= 0.01f;

		if (m_alpha <= 0.0f)
		{
			Scene::SetScene(new CSceneHome());//�z�[����ʂփV�[���ڍs
		}

		return;
	}
	
	//�f�[�^�����{�^��
	if (20 < m_mou_x && m_mou_x < 120 && 20 < m_mou_y && m_mou_y < 120)
	{
		m_del_color = 1.0f;

		if (m_mou_l == true && m_key_f == true)
		{
			m_del_f = true;//�ŏI�m�F�E�C���h�E��\��

			m_del_alpha = 0.0f;//�f�[�^���������ʒm�摜���\��

			m_del_color = INI_COLOR;

			//�I���{�^����
			Audio::Start(1);

			return;
		}
	}
	//�f�[�^�����{�^���ȊO�̏ꏊ�����N���b�N����ƃV�[���ڍs�������s���B
	else if (m_mou_l == true && m_key_f == true)
	{
		m_del_color = INI_COLOR;

		m_key_f = false;//�L�[�t���OOFF

		m_flag = true;//�V�[���ڍs�����t���OON

		//�I����
		Audio::Start(1);
	}
	else
	{
		m_del_color = INI_COLOR;
	}

	//��ʈÓ]��Ԃ̏ꍇ�A���]���鏈��
	if (m_black_out_a >= 0.0f)
	{
		m_black_out_a -= 0.01f;
	}

	//�f�[�^���������ʒm�摜�\�����A���ߓx�������Ĕ�\���ɂ��鏈��
	if (m_del_alpha >= 0.0f)
	{
		m_del_alpha -= 0.01f;
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
void CObjTitle::Draw()
{
	//�`��J���[���  R=RED  G=Green  B=Blue A=alpha(���ߏ��)
	//�����Ȃ��摜�p[�V�[���ڍs���������Ȃ�]
	float d[4] = { 1.0f,1.0f,1.0f,1.0f };

	//���������摜�p(�N���b�N�ŃX�^�[�g�A�G�f��)[�V�[���ڍs���t�F�[�h�A�E�g]
	float w[4] = { 1.0f,1.0f,1.0f,m_alpha };

	//���F(�����)[�V�[���ڍs���t�F�[�h�A�E�g]
	float y[4] = { 1.0f,1.0f,0.0f,m_alpha };

	//�ԐF
	float red[4] = { 1.0f,0.0f,0.0f,1.0f };

	//�f�[�^���������ʒm�摜�p
	float notify[4] = { 1.0f,0.0f,0.0f,m_del_alpha };

	//�f�[�^�����{�^���p
	float Delete[4] = { m_del_color,m_del_color,m_del_color,m_alpha };
	
	//�ŏI�m�F[�͂�]�{�^���p
	float Yes[4] = { 1.0f,m_Yes_Button_color,m_Yes_Button_color,1.0f };

	//�ŏI�m�F[������]�{�^���p
	float No[4] = { m_No_Button_color,m_No_Button_color,1.0f,1.0f };

	//��ʑS�̈Ó]�摜�p
	float blackout[4] = { 1.0f,1.0f,1.0f,m_black_out_a };	

	//���E�ϐ����t�H���g�摜�p
	float description[4][4] =
	{
		{ 1.0f,1.0f,1.0f,m_des_a },			//�t�H���g�F�͑S�Ĕ��F
		{ 1.0f,1.0f,1.0f,m_des_a - 1.5f },
		{ 1.0f,1.0f,1.0f,m_des_a - 3.0f },
		{ 1.0f,1.0f,1.0f,m_des_a - 4.5f },
	};

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
	src.m_right = 287.0f;
	src.m_bottom = 287.0f;

	dst.m_top = m_Ey[0];
	dst.m_left = 1200.0f - m_time[0];//+4��������������ϐ����������ŁA
	dst.m_right = 1250.0f - m_time[0];//�O���t�B�b�N���E���獶�ֈړ������Ă���B
	dst.m_bottom = m_Ey[0] + 50.0f;
	Draw::Draw(20, &src, &dst, w, 0.0f);

	//�G�f��2(�w�i)�\��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 287.0f;
	src.m_bottom = 287.0f;

	dst.m_top = m_Ey[1];
	dst.m_left = 1200.0f - m_time[1];//+4��������������ϐ����������ŁA
	dst.m_right = 1250.0f - m_time[1];//�O���t�B�b�N���E���獶�ֈړ������Ă���B
	dst.m_bottom = m_Ey[1] + 50.0f;
	Draw::Draw(22, &src, &dst, w, 0.0f);

	//�G�f��3(�w�i)�\��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 287.0f;
	src.m_bottom = 287.0f;

	dst.m_top = m_Ey[2];
	dst.m_left = 1200.0f - m_time[2];//+4��������������ϐ����������ŁA
	dst.m_right = 1250.0f - m_time[2];//�O���t�B�b�N���E���獶�ֈړ������Ă���B
	dst.m_bottom = m_Ey[2] + 50.0f;
	Draw::Draw(24, &src, &dst, w, 0.0f);

	//���v���C���[�f���\��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 448.0f;
	src.m_bottom = 448.0f;

	dst.m_top = 250.0f;
	dst.m_left = 450.0f;
	dst.m_right = 750.0f;
	dst.m_bottom = 550.0f;
	Draw::Draw(50, &src, &dst, d, 0.0f);
	//Draw::Draw(50 + ((int)((g_Bar_Level + g_Ins_Level) / 2)) - 1, &src, &dst, d, 0.0f);

	//���㉺�ӂ�ӂ킷��"�N���b�N�ŃX�^�[�g"��\��
	//�p�x���Z
	m_r += 2.0f;

	//360���ŏ����l�ɖ߂�
	if (m_r > 360.0f)
		m_r = 0.0f;

	//�ړ�����
	m_click_vy = sin(3.14f / 90 * m_r);

	//���x�t����B
	m_click_vy *= 10.0f;

	//�N���b�N�ŃX�^�[�g�����摜��\��
	src.m_top    =   0.0f;
	src.m_left   =   0.0f;
	src.m_right  = 373.0f;
	src.m_bottom =  41.0f;

	dst.m_top    = 600.0f + m_click_vy;
	dst.m_left   = 450.0f;
	dst.m_right  = 823.0f;
	dst.m_bottom = 641.0f + m_click_vy;
	Draw::Draw(53, &src, &dst, w, 0.0f);

	//�^�C�g�����S�`��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1557.0f;
	src.m_bottom = 929.0f;

	dst.m_top = 0.0f;
	dst.m_left = 350.0f;
	dst.m_right = 851.0f;
	dst.m_bottom = 280.0f;
	Draw::Draw(1, &src, &dst, w, 0.0f);

	//�f�[�^�����{�^���\��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 522.0f;
	src.m_bottom = 390.0f;

	dst.m_top = 20.0f;
	dst.m_left = 20.0f;
	dst.m_right = 120.0f;
	dst.m_bottom = 120.0f;
	Draw::Draw(54, &src, &dst, Delete, 0.0f);

	//�f�[�^���������t�H���g�摜�\��
	FontDraw(L"�f�[�^��������", m_mou_x - 122.5f, m_mou_y - 40.0f, 35.0f, 35.0f, notify, false);

	//����ʑS�̈Ó]�p�摜�\��
	//��blackout�̓��ߓx�̒l�Łu�\��/��\���v���؂�ւ�����
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1200.0f;
	src.m_bottom = 700.0f;

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 1200.0f;
	dst.m_bottom = 700.0f;
	Draw::Draw(2, &src, &dst, blackout, 0.0f);

	//���E�ϐ����t�H���g�摜�\��
	FontDraw(L"�ӎv�����f���B���݂��̐����������ċ�炢����������H�̉F���c�c�B", 35.0f, m_des_y, 35.0f, 35.0f, description[0], false);
	FontDraw(L"�򂤂�����邩�\�\", 35.0f, m_des_y + 100.0f, 35.0f, 35.0f, description[1], false);
	FontDraw(L"����ȉF���Ő��܂ꂽ�Ă̘f���������B", 35.0f, m_des_y + 200.0f, 35.0f, 35.0f, description[2], false);
	FontDraw(L"���̘f���̖��́c�c�H", 35.0f, m_des_y + 300.0f, 35.0f, 35.0f, description[3], false);


	//���f�[�^�����ŏI�m�F�E�C���h�E�\���Ǘ��t���O��true�̎��A�`��B
	if (m_del_f == true)
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
		Draw::Draw(57, &src, &dst, d, 0.0f);

		//�f�[�^���������܂����H
		FontDraw(L"�f�[�^���������܂����H", 360.0f, 250.0f, 45.0f, 45.0f, red, false);

		//���͂������摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 232.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 410.0f;
		dst.m_left = 410.0f;
		dst.m_right = 510.0f;
		dst.m_bottom = 460.0f;
		Draw::Draw(55, &src, &dst, Yes, 0.0f);

		//�������������摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 352.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 410.0f;
		dst.m_left = 650.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 460.0f;
		Draw::Draw(56, &src, &dst, No, 0.0f);
	}


	//�f�o�b�O�p���}�E�X�ʒu�\��
	//wchar_t str[256];
	//swprintf_s(str, L"x=%f,y=%f", m_mou_x, m_mou_y);
	//Font::StrDraw(str, 20.0f, 20.0f, 12.0f, d);
}
