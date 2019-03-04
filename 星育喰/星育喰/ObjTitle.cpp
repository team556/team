//�g�p����w�b�_�[�t�@�C
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"
#include "ObjTitle.h"
#include "Call_Planet.h"

#include <stdlib.h>
#include <time.h>

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjTitle::Init()
{
	m_Click_vy = 0.0f;	
	m_r = 0.0f;			

	m_mou_x = 0.0f;
	m_mou_y = 0.0f;

	m_time = 0;
	m_enemy_time = 0;
	m_Planet_Count = 0;
	m_enemy_y = 0;

	srand(time(NULL));//�����_������������
}

//�A�N�V����
void CObjTitle::Action()
{
	//�}�E�X�̈ʒu���擾(�f�o�b�N�p)
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
}

//�h���[
void CObjTitle::Draw()
{
	//�`��J���[���  R=RED  G=Green  B=Blue A=alpha(���ߏ��)
	float d[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu

	//�w�i�\��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 960.0f;
	src.m_bottom = 638.0f;

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 1200.0f;
	dst.m_bottom = 800.0f;
	Draw::Draw(0, &src, &dst, d, 0.0f);

	//�v���C���[�f���\��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 300.0f;
	src.m_bottom = 168.0f;

	dst.m_top = 220.0f;
	dst.m_left = 250.0f;
	dst.m_right = 950.0f;
	dst.m_bottom = 620.0f;
	Draw::Draw(10, &src, &dst, d, 0.0f);


	//��
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	//���F
	float y[4] = { 1.0f,1.0f,0.0f,1.0f };
	//Font::StrDraw(L"", 230, 250, 32, c);

	//��"�����"�Ƃ����^�C�g����\��
	Font::StrDraw(L"�����", 425, 100, 120, y);

	//���㉺�ӂ�ӂ킷��"�N���b�N�ŃX�^�[�g"��\��
	//�p�x���Z
	m_r += 2.0f;

	//360���ŏ����l�ɖ߂�
	if (m_r > 360.0f)
		m_r = 0.0f;

	//�ړ�����
	m_Click_vy = sin(3.14f / 90 * m_r);

	//���x�t����B
	m_Click_vy *= 10.0f;

	Font::StrDraw(L"�N���b�N�ŃX�^�[�g", 460, 700 + m_Click_vy, 32, c);


	//�G�f��
	m_time++;
	m_enemy_time+= 5;

	if (m_enemy_time >= 1500.0f)
	{
		m_enemy_time = 0;
		Call_Planet(1, 1);
		m_enemy_y = rand() % 601 + 100;
	}

	//if (rand() % 101 + 150 == m_time)
	//{
		m_time = 0;
		
	/*	if (m_Planet_Count == 0)
		{
			m_Planet_Count++;
			m_enemy_time = 0;
			Call_Planet(1, 1);
			m_enemy_y = rand () % 601 + 100;

			
		}*/

		//�G�f��1�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 384.0f;
		src.m_bottom = 384.0f;

		dst.m_top = m_enemy_y;
		dst.m_left = 1199.0f - m_enemy_time;
		dst.m_right = 1249.0f - m_enemy_time;
		dst.m_bottom = m_enemy_y + 50.0f;
		Draw::Draw(20, &src, &dst, d, 0.0f);



	//}


	//�f�o�b�N�p���}�E�X�ʒu�\��
	wchar_t str[256];
	swprintf_s(str, L"x=%f,y=%f", m_mou_x, m_mou_y);
	Font::StrDraw(str, 20, 20, 12, c);
}
