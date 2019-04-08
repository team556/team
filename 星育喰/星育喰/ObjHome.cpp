//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"		//�g�p����Ă���̂̓}�E�X�f�o�b�O�̕����̂�
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"
#include "Call_Planet.h"

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
#define INI_COLOR (1.0f) //�S�J���[���x�̏����l

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
					Scene::SetScene(new CSceneFight());//�퓬������ʂփV�[���ڍs
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
					m_boost += 24.0;
				}
				else
				{
					m_boost += 6.0;
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
	if (m_alpha < 1.0f)
	{
		m_alpha += 0.01f;
	}

	//��A�C�R��
	if (20 < m_mou_x && m_mou_x < 220 && 480 < m_mou_y && m_mou_y < 680)
	{
		m_Tra_color = 0.7f;

		//���N���b�N���ꂽ��t���O�𗧂āA�琬��ʂ։��o�������Ȃ���V�[���ڍs
		if (m_mou_l == true)
		{
			//�N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
			if (m_key_f == true)
			{
				m_key_f = false;

				m_Tra_flag = true;
			}
		}
		else
		{
			m_key_f = true;
		}
	}
	else
	{
		m_Tra_color = 1.0f;
	}

	//��A�C�R��
	if (980 < m_mou_x && m_mou_x < 1180 && 480 < m_mou_y && m_mou_y < 680)
	{
		m_Eat_color = 0.7f;

		//���N���b�N���ꂽ��t���O�𗧂āA�퓬������ʂ։��o�������Ȃ���V�[���ڍs
		if (m_mou_l == true)
		{	
			//�N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
			if (m_key_f == true)
			{
				m_key_f = false;

				m_Eat_flag = true;
			}
		}
		else
		{
			m_key_f = true;
		}
	}
	else
	{
		m_Eat_color = 1.0f;
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

	//����ȊO�̉摜�p
	float d[4] = { 1.0f,1.0f,1.0f,1.0f };

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
	src.m_right = 384.0f;
	src.m_bottom = 384.0f;

	dst.m_top = m_Ey[0];
	dst.m_left = 1200.0f - m_time[0];//+4��������������ϐ����������ŁA
	dst.m_right = 1250.0f - m_time[0];//�O���t�B�b�N���E���獶�ֈړ������Ă���B
	dst.m_bottom = m_Ey[0] + 50.0f;
	Draw::Draw(20, &src, &dst, p, 0.0f);

	//�G�f��2(�w�i)�\��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 384.0f;
	src.m_bottom = 384.0f;

	dst.m_top = m_Ey[1];
	dst.m_left = 1200.0f - m_time[1];//+4��������������ϐ����������ŁA
	dst.m_right = 1250.0f - m_time[1];//�O���t�B�b�N���E���獶�ֈړ������Ă���B
	dst.m_bottom = m_Ey[1] + 50.0f;
	Draw::Draw(22, &src, &dst, p, 0.0f);

	//�G�f��3(�w�i)�\��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 384.0f;
	src.m_bottom = 384.0f;

	dst.m_top = m_Ey[2];
	dst.m_left = 1200.0f - m_time[2];//+4��������������ϐ����������ŁA
	dst.m_right = 1250.0f - m_time[2];//�O���t�B�b�N���E���獶�ֈړ������Ă���B
	dst.m_bottom = m_Ey[2] + 50.0f;
	Draw::Draw(24, &src, &dst, p, 0.0f);



	//���v���C���[�f���\��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 62.0f;
	src.m_bottom = 62.0f;

	dst.m_top = 250.0f + m_Pvy - m_size;
	dst.m_left = 450.0f + m_Pvx - m_size;
	dst.m_right = 750.0f + m_Pvx + m_size;
	dst.m_bottom = 550.0f + m_Pvy + m_size;
	Draw::Draw(50, &src, &dst, d, 0.0f);


	//����A�C�R���\��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 128.0f;
	src.m_bottom = 128.0f;

	dst.m_top = 480.0f + m_Tra_move;
	dst.m_left = 20.0f - m_Tra_move;
	dst.m_right = 220.0f - m_Tra_move;
	dst.m_bottom = 680.0f + m_Tra_move;
	Draw::Draw(1, &src, &dst, t, 0.0f);

	//����A�C�R���\��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 128.0f;
	src.m_bottom = 128.0f;

	dst.m_top = 480.0f + m_Eat_move;
	dst.m_left = 980.0f + m_Eat_move;
	dst.m_right = 1180.0f + m_Eat_move;
	dst.m_bottom = 680.0f + m_Eat_move;
	Draw::Draw(2, &src, &dst, e, 0.0f);




	//�f�o�b�O�p���}�E�X�ʒu�\��
	wchar_t str[256];
	swprintf_s(str, L"x=%f,y=%f", m_mou_x, m_mou_y);
	Font::StrDraw(str, 20, 20, 12, d);
}
