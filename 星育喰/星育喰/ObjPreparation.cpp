//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�}�N��
#define INI_ENEMY_X_POS (1150.0f)	//�G�f��4�S�̂̏���X�ʒu
#define INI_ENEMY_Y_POS (150.0f)	//�G�f��4�S�̂̏���Y�ʒu
#define INI_ENEMY_SPEED (50.0f)		//�G�f��4�̏����ړ��X�s�[�h
#define INI_ALPHA (0.0f) //���ߓx(�A���t�@�l)�̏����l
#define INI_COLOR (1.0f) //�S�J���[���x�̏����l

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
	m_boost = 0.0f;
	m_rx = 0.0f;
	m_ry = 0.0f;
	m_size = 0.0f;

	m_Evx = 0.0f;
	m_Espeed = INI_ENEMY_SPEED;

	m_staging_time = 0;

	m_Back_Button_color = INI_COLOR;
	m_Yes_Button_color = INI_COLOR;
	m_No_Button_color = INI_COLOR;
	m_alpha = INI_ALPHA;

	m_Enemy_detail_message_window_x_size = 0.0f;
	m_Enemy_detail_message_window_y_size = 0.0f;
}

//�A�N�V����
void CObjPreparation::Action()
{
	////�}�E�X�̈ʒu���擾
	//m_mou_x = (float)Input::GetPosX();
	//m_mou_y = (float)Input::GetPosY();
	////�}�E�X�̃{�^���̏��
	//m_mou_r = Input::GetMouButtonR();
	//m_mou_l = Input::GetMouButtonL();

	////���A�C�R���A�G�f��(�w�i)�����X�ɕ\��������
	//if (m_alpha < 1.0f)
	//{
	//	m_alpha += 0.01f;
	//}

	////��A�C�R��
	//if (20 < m_mou_x && m_mou_x < 220 && 480 < m_mou_y && m_mou_y < 680)
	//{
	//	//m_Tra_color = 0.7f;

	//	//���N���b�N���ꂽ��t���O�𗧂āA�琬��ʂ։��o�������Ȃ���V�[���ڍs
	//	if (m_mou_l == true)
	//	{
	//		//�N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
	//		if (m_key_lf == true)
	//		{
	//			m_key_lf = false;

	//			//m_Tra_flag = true;
	//		}
	//	}
	//	else
	//	{
	//		m_key_lf = true;
	//	}
	//}
	//else
	//{
	//	//m_Tra_color = 1.0f;
	//}

	//���퓬������ʊJ�n���o
	if (m_Evx > -1000.0f)
	{
		m_staging_time++;

		m_Espeed -= m_Espeed * 0.047;

		m_Evx -= m_Espeed;

		return;
	}

	//�}�E�X�̈ʒu���擾
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//�}�E�X�̃{�^���̏��
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();
}

//�h���[
void CObjPreparation::Draw()
{
	//�`��J���[���  R=RED  G=Green  B=Blue A=alpha(���ߏ��)
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

	//���G�f��1�\��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 384.0f;
	src.m_bottom = 384.0f;

	dst.m_top = INI_ENEMY_Y_POS;
	dst.m_left = INI_ENEMY_X_POS + m_Evx;
	dst.m_right = INI_ENEMY_X_POS + 200.0f + m_Evx;
	dst.m_bottom = INI_ENEMY_Y_POS + 200.0f;
	Draw::Draw(1, &src, &dst, d, 0.0f);

	//���G�f��2�\��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 384.0f;
	src.m_bottom = 384.0f;

	dst.m_top = INI_ENEMY_Y_POS - 100.0f;
	dst.m_left = INI_ENEMY_X_POS + 300.0f + m_Evx;
	dst.m_right = INI_ENEMY_X_POS + 400.0f + m_Evx;
	dst.m_bottom = INI_ENEMY_Y_POS;
	Draw::Draw(2, &src, &dst, d, 0.0f);

	//���G�f��3�\��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 384.0f;
	src.m_bottom = 384.0f;

	dst.m_top = INI_ENEMY_Y_POS + 200.0f;
	dst.m_left = INI_ENEMY_X_POS + 500.0f + m_Evx;
	dst.m_right = INI_ENEMY_X_POS + 800.0f + m_Evx;
	dst.m_bottom = INI_ENEMY_Y_POS + 500.0f;
	Draw::Draw(3, &src, &dst, d, 0.0f);

	//���G�f��4�\��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 384.0f;
	src.m_bottom = 384.0f;

	dst.m_top = INI_ENEMY_Y_POS - 50.0f;
	dst.m_left = INI_ENEMY_X_POS + 700.0f + m_Evx;
	dst.m_right = INI_ENEMY_X_POS + 900.0f + m_Evx;
	dst.m_bottom = INI_ENEMY_Y_POS + 150.0f;
	Draw::Draw(4, &src, &dst, d, 0.0f);

	//���v���C���[�f���\��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 62.0f;
	src.m_bottom = 62.0f;

	dst.m_top = 250.0f + m_Pvy - m_size;
	dst.m_left = 450.0f + m_Pvx - m_size;
	dst.m_right = 750.0f + m_Pvx + m_size;
	dst.m_bottom = 550.0f + m_Pvy + m_size;
	Draw::Draw(63, &src, &dst, d, 0.0f);



	//�f�o�b�O�p���}�E�X�ʒu�\��
	wchar_t str[256];
	swprintf_s(str, L"x=%f,y=%f", m_mou_x, m_mou_y);
	Font::StrDraw(str, 20.0f, 20.0f, 12.0f, d);
}
