//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
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
#define INI_ALPHA (1.0f) //���ߓx(�A���t�@�l)�̏����l

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

	m_flag  = false;
	m_alpha = INI_ALPHA;

	m_mou_x = 0.0f;
	m_mou_y = 0.0f;
	m_mou_r = false;
	m_mou_l = false;

	srand(time(NULL));//�����_������������
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
	
	if (m_flag == true)
	{
		m_alpha -= 0.01f;
		
		if (m_alpha <= 0.0f)
		{
			Scene::SetScene(new CSceneHome());//�z�[����ʂփV�[���ڍs
		}
	}
	else if (m_mou_l == true || m_mou_r == true)
	{
		m_flag = true;
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
	m_time[0] += 4;
	m_time[1] += 4;
	m_time[2] += 4;

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
	Draw::Draw(20, &src, &dst, w, 0.0f);

	//�G�f��2(�w�i)�\��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 384.0f;
	src.m_bottom = 384.0f;

	dst.m_top = m_Ey[1];
	dst.m_left = 1200.0f - m_time[1];//+4��������������ϐ����������ŁA
	dst.m_right = 1250.0f - m_time[1];//�O���t�B�b�N���E���獶�ֈړ������Ă���B
	dst.m_bottom = m_Ey[1] + 50.0f;
	Draw::Draw(22, &src, &dst, w, 0.0f);

	//�G�f��3(�w�i)�\��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 384.0f;
	src.m_bottom = 384.0f;

	dst.m_top = m_Ey[2];
	dst.m_left = 1200.0f - m_time[2];//+4��������������ϐ����������ŁA
	dst.m_right = 1250.0f - m_time[2];//�O���t�B�b�N���E���獶�ֈړ������Ă���B
	dst.m_bottom = m_Ey[2] + 50.0f;
	Draw::Draw(24, &src, &dst, w, 0.0f);



	//���v���C���[�f���\��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 300.0f;
	src.m_bottom = 168.0f;

	dst.m_top = 150.0f;
	dst.m_left = 250.0f;
	dst.m_right = 950.0f;
	dst.m_bottom = 550.0f;
	Draw::Draw(50, &src, &dst, d, 0.0f);


	//��"�����"�Ƃ����^�C�g����\��
	Font::StrDraw(L"�����", 425, 50, 120, y);

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

	Font::StrDraw(L"�N���b�N�ŃX�^�[�g", 460, 600 + m_click_vy, 32, w);


	


	//�f�o�b�O�p���}�E�X�ʒu�\��
	wchar_t str[256];
	swprintf_s(str, L"x=%f,y=%f", m_mou_x, m_mou_y);
	Font::StrDraw(str, 20, 20, 12, d);
}
