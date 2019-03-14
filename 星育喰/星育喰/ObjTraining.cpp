//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"		//�g�p����Ă���̂̓}�E�X�f�o�b�O�̕����̂�
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�}�N��
#define INI_ALPHA (0.0f) //���ߓx(�A���t�@�l)�̏����l
#define INI_COLOR (1.0f) //�S�J���[���x�̏����l

//�C�j�V�����C�Y
void CObjTraining::Init()
{
	m_Cloud_move = 0.0f;

	m_mou_x = 0.0f;
	m_mou_y = 0.0f;
	m_mou_r = false;
	m_mou_l = false;

	m_key_f = false;
}

//�A�N�V����
void CObjTraining::Action()
{
	//�}�E�X�̈ʒu���擾
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//�}�E�X�̃{�^���̏��
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	
}

//�h���[
void CObjTraining::Draw()
{
	//�`��J���[���  R=RED  G=Green  B=Blue A=alpha(���ߏ��)
	////�G�f��(�w�i)�p
	//float p[4] = { 1.0f,1.0f,1.0f,m_alpha };

	////��A�C�R���p
	//float t[4] = { m_Tra_color,m_Tra_color,m_Tra_color,m_alpha };

	////��A�C�R���p
	//float e[4] = { m_Eat_color,m_Eat_color,m_Eat_color,m_alpha };

	//����ȊO�̉摜�p
	float d[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu


	//���w�i(�n��)�\��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 238.0f;
	src.m_bottom = 238.0f;

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 1200.0f;
	dst.m_bottom = 700.0f;
	Draw::Draw(0, &src, &dst, d, 0.0f);


	//���v���C���[�f���\��
	//src.m_top = 0.0f;
	//src.m_left = 0.0f;
	//src.m_right = 300.0f;
	//src.m_bottom = 168.0f;

	//dst.m_top = 150.0f + m_Pvy - m_size;
	//dst.m_left = 250.0f + m_Pvx - m_size;
	//dst.m_right = 950.0f + m_Pvx + m_size;
	//dst.m_bottom = 550.0f + m_Pvy + m_size;
	//Draw::Draw(50, &src, &dst, d, 0.0f);


	//���_(�E��)�\��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 500.0f;
	src.m_bottom = 500.0f;

	dst.m_top = -1000.0f + m_Cloud_move;
	dst.m_left = 900.0f - m_Cloud_move;
	dst.m_right = 2200.0f - m_Cloud_move;
	dst.m_bottom = 100.0f + m_Cloud_move;
	Draw::Draw(1, &src, &dst, d, 0.0f);

	//�ȉ��̈ʒu�ɂȂ�Ɖ�ʑS�̂��B���
	//dst.m_top = 0.0f;
	//dst.m_left = -100.0f;
	//dst.m_right = 1200.0f;
	//dst.m_bottom = 1100.0f;


	//���_(����)�\��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = -500.0f;
	src.m_bottom = -500.0f;

	dst.m_top = 600.0f - m_Cloud_move;
	dst.m_left = -1000.0f + m_Cloud_move;
	dst.m_right = 300.0f + m_Cloud_move;
	dst.m_bottom = 1700.0f - m_Cloud_move;
	Draw::Draw(1, &src, &dst, d, 0.0f);

	//�ȉ��̈ʒu�ɂȂ�Ɖ�ʑS�̂��B���
	//dst.m_top = -400.0f;
	//dst.m_left = 0.0f;
	//dst.m_right = 1300.0f;
	//dst.m_bottom = 700.0f;




	//�f�o�b�O�p���}�E�X�ʒu�\��
	wchar_t str[256];
	swprintf_s(str, L"x=%f,y=%f", m_mou_x, m_mou_y);
	Font::StrDraw(str, 20, 20, 12, d);
}
