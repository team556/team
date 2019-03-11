//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjBuild.h"

#define TESTX m_x + 100
#define TESTY m_y + 100

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjBuild::Init()
{
	m_x = 200;
	m_y = 200;

	m_key_f = true;
	m_turn = true;

	//m_build = true;

	////�����蔻��pHitBox���쐬
	//Hits::SetHitBox(this, m_x, m_y, 450, 468, ELEMENT_BUILD, OBJ_BUILD, 1);

}

//�A�N�V����
void CObjBuild::Action()
{
	////�}�E�X�̈ʒu���擾+
	//m_mou_x = (float)Input::GetPosX();
	//m_mou_y = (float)Input::GetPosY();
	////�}�E�X�̃{�^���̏��
	//m_mou_r = Input::GetMouButtonR();
	//m_mou_l = Input::GetMouButtonL();


	////���N���b�N�őI���܂��͌���
	//if (Input::GetMouButtonL() == true && m_x < m_mou_x && m_mou_x < m_x && m_y < m_mou_y && m_mou_y < m_y)
	//{
	//	//test�p�I�u�W�F�N�g�쐬
	//	Draw::LoadImage(L"�I�u�W�F�N�g.png", 1, TEX_SIZE_512);

	//}
	//else if (m_x < m_mou_x && m_mou_x < m_x + 100 && m_y < m_mou_y && m_mou_y < m_y + 100)
	//{
	//	if (m_mou_l == true && m_build ==true)
	//	{
	//		Draw::LoadImage(L"����.jpg", 1, TEX_SIZE_512);
	//		m_mou_l = false;
	//		m_build = false;
	//	}
	//}

	//else if (m_x < m_mou_x && m_mou_x < m_x + 450 && m_y < m_mou_y && m_mou_y < m_y + 468)
	//{
	//	//�}�E�X�̃{�^���������ꂽ��c�c
	//	if (m_mou_l == true && m_build == true)
	//	{
	//		Draw::LoadImage(L"�I�u�W�F�N�g.png", 1, TEX_SIZE_512);
	//		m_mou_l = false;
	//		m_build = false;
	//	}
	//}

	//else
	//{
	//	m_build = true;
	//}

	/*�}�E�X�̈ʒu���擾
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	�}�E�X�̃{�^���̏��
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	if (m_mou_l == true)
	{
		if (TESTX < m_mou_x && m_mou_x < m_x + 450 && TESTY < m_mou_y && m_mou_y < m_y + 468
			&& m_build == false)
		{
			Draw::LoadImage(L"�I�u�W�F�N�g.png", 1, TEX_SIZE_512);
			m_build = true;
		}

		else if (m_x < m_mou_x && m_mou_x < TESTX && m_y < m_mou_y && m_mou_y < TESTY
			&& m_return == false)
		{
			Draw::LoadImage(L"����.jpg", 1, TEX_SIZE_512);
			m_return = true;
		}
	}
	else
	{
		m_build = false;
		m_return = false;
	}*/

	//�}�E�X�̈ʒu���擾
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//�}�E�X�̃{�^���̏��
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();
	
	if (m_x <= m_mou_x && m_mou_x <= m_x + 450.0f) {//X���͈̔�
		if (m_y <= m_mou_y && m_mou_y <= m_y + 468.0f) {//Y���͈̔�
			if (m_mou_l == true) {//�N���b�N��
				if (m_key_f == true && m_turn == true) {
					Draw::LoadImage(L"�I�u�W�F�N�g.png", 1, TEX_SIZE_512);
					m_key_f = false;
					m_turn = false;
				}
				else if(m_turn == false)//2��ڂ̃N���b�N
				{
					Draw::LoadImage(L"����.jpg", 1, TEX_SIZE_512);
				}
			}
			else{//�N���b�N��������
				m_key_f = true;
			}
		}
	}
	
	
	


}

////���������\�b�h
//void CObjBuild::InitScene()
//{
//	//
//}
//


//�h���[
void CObjBuild::Draw()
{
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	RECT_F src;
	RECT_F dst;

	//�؂���
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 450.0f;
	src.m_bottom =468.0f;

	//�`��
	dst.m_top = 0.0f + m_x;
	dst.m_left = 0.0f + m_y;
	dst.m_right = 450.0f + m_x;
	dst.m_bottom = 468.0f + m_y;

	//2�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
	Draw::Draw(1, &src, &dst, c, 0.0f);
}

