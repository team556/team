//���ރ{�^���I�u�W�F�N�g

//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjMaterialBotton::Init()
{

}

//�A�N�V����
void CObjMaterialBotton::Action()
{

	////�}�E�X�̈ʒu���擾
	//m_mou_x = (float)Input::GetPosX();
	//m_mou_y = (float)Input::GetPosY();
	////�}�E�X�̃{�^���̏��
	//m_mou_r = Input::GetMouButtonR();
	//m_mou_l = Input::GetMouButtonL();

	//if (m_x <= m_mou_x && m_mou_x <= m_x + 225.0f) {//X���͈̔�
	//	if (m_y <= m_mou_y && m_mou_y <= m_y + 225.0f) {//Y���͈̔�
	//		if (m_mou_l == true) {//�N���b�N��
	//			if (m_key_f == true && m_turn == true) {
	//				Draw::LoadImage(L"�I�u�W�F�N�g.png", 2, TEX_SIZE_512);
	//				m_key_f = false;
	//				m_turn = false;

	//				m_obx = 1150;
	//				m_oby = 650;
	//				m_obj = false;
	//			}
	//			else if (m_key_f == true && m_turn == false)//2��ڂ̃N���b�N
	//			{
	//				//�L�����Z�����͈̔�
	//				if (m_x <= m_mou_x && m_mou_x <= m_x + 100.0f && m_y <= m_mou_y && m_mou_y <= m_y + 100.0f)
	//				{
	//					Draw::LoadImage(L"�q��.png", 2, TEX_SIZE_512);
	//					m_key_f = false;
	//					m_turn0 = false;

	//				}
	//			}
	//		}
	//		else {//�N���b�N��������
	//			m_key_f = true;
	//			if (m_turn0 == false) {
	//				m_turn = true;
	//				m_turn0 = true;
	//			}
	//		}
	//	}
	//}

}


//�h���[
void CObjMaterialBotton::Draw()
{

}

