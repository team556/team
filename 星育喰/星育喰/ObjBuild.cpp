//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjBuild.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjBuild::Init()
{
	m_x = 50;
	m_y = 50;

	m_key_f = true;
	m_turn = true;
	m_turn0 = true;

}

//�A�N�V����
void CObjBuild::Action()
{

	//�}�E�X�̈ʒu���擾
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//�}�E�X�̃{�^���̏��
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();
	
	//if (m_x <= m_mou_x && m_mou_x <= m_x + 250.0f) {//X���͈̔�
	//	if (m_y <= m_mou_y && m_mou_y <= m_y + 268.0f) {//Y���͈̔�
	//		if (m_mou_l == true) {//�N���b�N��
	//			if (m_key_f == true && m_turn == true) {
	//				Draw::LoadImage(L"�I�u�W�F�N�g.png", 1, TEX_SIZE_512);
	//				m_key_f = false;
	//				m_turn = false;
	//			}
	//			else if(m_key_f == true && m_turn == false)//2��ڂ̃N���b�N
	//			{
	//				//�L�����Z�����͈̔�
	//				if (m_x <= m_mou_x && m_mou_x <= m_x + 100.0f && m_y <= m_mou_y && m_mou_y <= m_y + 100.0f)
	//				{
	//					Draw::LoadImage(L"����.jpg", 1, TEX_SIZE_512);
	//					m_key_f = false;
	//					m_turn0 = false;
	//				}
	//			}
	//		}
	//		else{//�N���b�N��������
	//			m_key_f = true;
	//			if (m_turn0 == false) {
	//				m_turn = true;
	//				m_turn0 = true;
	//			}
	//		}
	//	}
	//}
	
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
	src.m_top    =   0.0f;
	src.m_left   =   0.0f;
	src.m_right  = 450.0f;
	src.m_bottom = 468.0f;

	//�`��
	dst.m_top    =   0.0f + m_x;
	dst.m_left   =   0.0f + m_y;
	dst.m_right  = 250.0f + m_x;
	dst.m_bottom = 268.0f + m_y;

	//1�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
	Draw::Draw(1, &src, &dst, c, 0.0f);
}

