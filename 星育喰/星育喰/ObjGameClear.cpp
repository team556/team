//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjGameClear.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;

////�R���X�g���N�^
//CObjTest::CObjTest(float x, float y)
//{
//	//�쐬���ɓn���ꂽ�l���A���W�̏����l�ɑ��
//	m_x = x;
//	m_y = y;
//}

//�C�j�V�����C�Y
void CObjGameClear::Init()
{
	m_mou_x = 0.0f;	//�}�E�XX���W
	m_mou_y = 0.0f; //�}�E�XY���W
	m_mou_r = false;//�E�N���b�N
	m_mou_l = false;//���N���b�N

	m_f = false;
	m_y_vec = 0.6;

	for (int i = 0; i < 20; i++)//�z��̏�����
		m_cy[i] = i * 80 + 700;	//�s�Ԃ̊Ԋu���󂯂�̂ƁA��ʂ�艺�ɂ���
	m_c_nam = 0;

	m_speed = 0;
}

//�A�N�V����
void CObjGameClear::Action()
{
	//�}�E�X�̈ʒu���擾
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//�}�E�X�̃{�^���̏��
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	//Z�L�[�������Ă���ԁA�G���h���[���̗���鑬�x�������Ȃ�
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
void CObjGameClear::Draw()
{
	//�`��J���[���  R=RED  G=Green  B=Blue A=alpha(���ߏ��)
	float d[4] = { 0.0f,0.0f, 0.0f, 1.0f };

	RECT_F src;//�؂���ʒu
	RECT_F dst;//�\���ʒu
	
	src.m_top   =  0.0f;
	src.m_left  =  0.0f;
	src.m_right =100.0f;
	src.m_bottom=100.0f;
	
	dst.m_top   =  0.0f;
	dst.m_left  =  0.0f;
	dst.m_right =1200.0f;
	dst.m_bottom= 700.0f;

	//0�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
	Draw::Draw(1, &src, &dst, d, 0.0f);

	for (int i = 0; i < 20; i++)
	{
		m_cy[i] -= m_y_vec;
	}

	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	Font::StrDraw(L"�g�p�������y�A���ʉ��T�C�g", 260, m_cy[0], 50, c);

	Font::StrDraw(L"���l",	550, m_cy[2], 45, c);

	Font::StrDraw(L"https://on-jin.com/",375, m_cy[3], 45, c);

	Font::StrDraw(L"������",525, m_cy[4], 45, c);

	Font::StrDraw(L"https://maoudamashii.jokersounds.com/",	150, m_cy[5], 45, c);

	//Font::StrDraw(L"�e�c",			800, m_cy[6], 32, c);

	//Font::StrDraw(L"�������",		800, m_cy[7], 32, c);

	//Font::StrDraw(L"�T�E���h",		400, m_cy[8], 32, c);

	//Font::StrDraw(L"�r�c",			800, m_cy[9], 32, c);

	//Font::StrDraw(L"�v�����i",		400, m_cy[10], 32, c);

	//Font::StrDraw(L"�����o�[�S��",	800, m_cy[11], 32, c);
}
