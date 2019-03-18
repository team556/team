//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjWarehouse.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjWarehouse::Init()
{
	m_x = 100;
	m_y = 100;
	m_obx = 0;
	m_oby = 0;

	m_key_f = true;
	m_turn = true;
	m_turn0 = true;
	
	m_obj = true;

}

//�A�N�V����
void CObjWarehouse::Action()
{
	//�}�E�X�̈ʒu���擾
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//�}�E�X�̃{�^���̏��
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	if (m_x <= m_mou_x && m_mou_x <= m_x + 225.0f) {//X���͈̔�
		if (m_y <= m_mou_y && m_mou_y <= m_y + 225.0f) {//Y���͈̔�
			if (m_mou_l == true) {//�N���b�N��
				if (m_key_f == true && m_turn == true) {
					m_key_f = false;
					m_turn = false;

					m_obx = 1150;
					m_oby = 650;
					m_obj = false;
				}
				else if (m_key_f == true && m_turn == false)//2��ڂ̃N���b�N
				{
					//�L�����Z�����͈̔�
					if (m_x <= m_mou_x && m_mou_x <= m_x + 100.0f && m_y <= m_mou_y && m_mou_y <= m_y + 100.0f)
					{
						m_key_f = false;
						m_turn0 = false;

						m_obx = 225;
						m_oby = 225;
						m_obj = true;
					}
				}
			}
			else {//�N���b�N��������
				m_key_f = true;
				if (m_turn0 == false) {
					m_turn = true;
					m_turn0 = true;
				}
			}
		}
	}

}

//�h���[
void CObjWarehouse::Draw()
{
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	RECT_F src;
	RECT_F dst;

	//�؂���
	src.m_top    =   0.0f;
	src.m_left   =   0.0f;
	src.m_right  = 225.0f;
	src.m_bottom = 225.0f;

	if (m_obj == true)
	{
		//�`��
		dst.m_top    =   0.0f + m_x;
		dst.m_left   =   0.0f + m_y;
		dst.m_right  = 225.0f + m_x;
		dst.m_bottom = 225.0f + m_y;
	}

	else
	{
		dst.m_top    = 50.0f;
		dst.m_left   = 50.0f;
		dst.m_right  = m_obx;
		dst.m_bottom = m_oby;
	}

	//2�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
	Draw::Draw(2, &src, &dst, c, 0.0f);


	//�{�^���I�u�W�F�N�g
	//�؂���
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1200.0f;
	src.m_bottom = 800.0f;

	//�\��
	dst.m_top = 50.0f;
	dst.m_left = 50.0f;
	dst.m_right = 1150.0f;
	dst.m_bottom = 650.0f;

	//3�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
	Draw::Draw(3, &src, &dst, c, 0.0f);
}

