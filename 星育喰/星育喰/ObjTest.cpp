//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"
#include "ObjTest.h"

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
void CObjTest::Init()
{
	//m_f = false;
}

//�A�N�V����
void CObjTest::Action()
{
	//testA


	////�}�E�X�̈ʒu���擾
	//m_mou_x = (float)Input::GetPosX();
	//m_mou_y = (float)Input::GetPosY();
	////�}�E�X�̃{�^���̏��
	//m_mou_r = Input::GetMouButtonR();
	//m_mou_l = Input::GetMouButtonL();

	//if (700 < m_mou_x && m_mou_x < 900 && 300 < m_mou_y && m_mou_y < 500)
	//{
	//	m_f = true;
	//	test_flag = true;
	//}
	//else
	//{
	//	m_f = false;
	//	test_flag = false;
	//}
}

//�h���[
void CObjTest::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	Font::StrDraw(L"", 230, 250, 32, c);
	
	//�`��J���[���  R=RED  G=Green  B=Blue A=alpha(���ߏ��)
	float d[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	RECT_F src;//�؂���ʒu
	RECT_F dst;//�\���ʒu
	
	src.m_top   =  0.0f;
	src.m_left  =  0.0f;
	src.m_right =100.0f;
	src.m_bottom=100.0f;
	
	dst.m_top   =  0.0f;
	dst.m_left  =  0.0f;
	dst.m_right =100.0f;
	dst.m_bottom=100.0f;

	//0�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
	Draw::Draw(0, &src, &dst, d, 0.0f);





	//src.m_top = 0.0f;
	//src.m_left = 0.0f;
	//src.m_right = 300.0f;
	//src.m_bottom = 168.0f;

	//dst.m_top = 300.0f;
	//dst.m_left = 700.0f;
	//dst.m_right = 900.0f;
	//dst.m_bottom = 500.0f;

	////50�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
	//Draw::Draw(50, &src, &dst, d, 0.0f);

	//if (m_f == true || test_flag == true)
	//{
	//	Font::StrDraw(L"OK", 230, 250, 32, c);
	//}
}
