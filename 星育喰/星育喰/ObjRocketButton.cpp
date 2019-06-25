//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjRocketButton.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�}�N��
#define UNIT_CONSUME_NUM (100)	//���j�b�g���
#define RECAST_COMPLETE_TIME (60.0f * g_Recast_time)//�~�T�C���̃��L���X�g�����^�C��
#define RECAST_COMPLETE_POD_TIME (60.0f * 6)//�|�b�h�̃��L���X�g�����^�C��

//�R���X�g���N�^
CObjRocketButton::CObjRocketButton(float x, float y, float h, float w, int n)
{
	//�쐬���ɓn���ꂽ�l���A���W�̏����l�ɑ��
	m_x = x;
	m_y = y;
	m_h = h;
	m_w = w;

	Button_num = n;
}

//�C�j�V�����C�Y
void CObjRocketButton::Init()
{
	m_mou_x = 0.0f;	//�}�E�XX���W
	m_mou_y = 0.0f; //�}�E�XY���W
	m_mou_r = false;//�E�N���b�N
	m_mou_l = false;//���N���b�N
	m_mou_f = false;//�}�E�X�t���O

	m_a = 1.0f;		//�����x
	m_a2 = 1.0f;	//�����x

	m_cnt = 0;		//�J�E���g

	m_player_recast_buff = 1.0f;
	m_is_empty = false;
	
	//���j�b�g������(0�ȉ�)���`�F�b�N����
	if (Button_num == 1 && g_Power_num <= 0)
	{
		g_Power_num = 0;//0�����ɂȂ��Ă����ꍇ�A0�ɖ߂��B
		m_is_empty = true;//��t���OON

		m_mou_f = true;
		m_a = 0.3f;		//������
	}
	else if (Button_num == 2 && g_Defense_num <= 0)
	{
		g_Defense_num = 0;//0�����ɂȂ��Ă����ꍇ�A0�ɖ߂��B
		m_is_empty = true;//��t���OON

		m_mou_f = true;
		m_a = 0.3f;		//������
	}
	else if (Button_num == 3 && g_Speed_num <= 0)
	{
		g_Speed_num = 0;//0�����ɂȂ��Ă����ꍇ�A0�ɖ߂��B
		m_is_empty = true;//��t���OON
	
		m_mou_f = true;
		m_a = 0.3f;		//������
	}
	else if (Button_num == 4 && g_Balance_num <= 0)
	{
		g_Balance_num = 0;//0�����ɂȂ��Ă����ꍇ�A0�ɖ߂��B
		m_is_empty = true;//��t���OON

		m_mou_f = true;
		m_a = 0.3f;		//������
	}

	m_pow_f = false;		//pow�{�^���̃t���O
	m_def_f = false;		//def�{�^���̃t���O
	m_spe_f = false;		//spe�{�^���̃t���O
	m_bal_f = false;		//bal�{�^���̃t���O
	m_mis_f = false;		//mis�{�^���̃t���O

	m_key_push = 0;
	m_key_push_f = false;
}

//�A�N�V����
void CObjRocketButton::Action()
{
	//���퓬�J�n�O�͑���s�\�ɂ��鏈��
	if (battle_start == false)
	{
		return;
	}

	//�}�E�X�̈ʒu���擾
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//�}�E�X�̃{�^���̏��
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();


	//�e�����ꂽ���̃{�^���i���o�[��ݒ��1�`5�������ꂽ�t���O��true�ɂ���
	if (Input::GetVKey('2') == true || Input::GetVKey(VK_NUMPAD2) == true) {

		//pow�{�^��
		m_key_push = 1;
		m_key_push_f = true;
	}
	if (Input::GetVKey('3') == true || Input::GetVKey(VK_NUMPAD3) == true) {

		//def�{�^��
		m_key_push = 2;
		m_key_push_f = true;
	}
	if (Input::GetVKey('4') == true || Input::GetVKey(VK_NUMPAD4) == true) {

		//spe�{�^��
		m_key_push = 3;
		m_key_push_f = true;
	}
	if (Input::GetVKey('5') == true || Input::GetVKey(VK_NUMPAD5) == true) {

		//bal�{�^��
		m_key_push = 4;
		m_key_push_f = true;
	}
	if (Input::GetVKey('1') == true || Input::GetVKey(VK_NUMPAD1) == true) {

		//mis�{�^��
		m_key_push = 5;
		m_key_push_f = true;
	}

	//�}�E�X���W���{�^���̏ォ�A�N���b�N����Ă���Ƃ�
	if (((m_x <= m_mou_x && m_mou_x <= (m_x + m_w)) && (m_y <= m_mou_y && m_mou_y <= (m_y + m_h)) && m_mou_l == true) ||	
		//�{�^����������Ă��邩�A���̔ԍ��������̃i���o�[�Ɠ����Ƃ�
		((Button_num == m_key_push) && m_key_push_f == true))
		 {
		if (m_mou_f == false) {
			//���f���̈ʒu�ƃT�C�Y�����
			CObjPlanet* objp = (CObjPlanet*)Objs::GetObj(OBJ_PLANET);
			if (objp->GetType() == 0)
			{
				m_px = objp->GetX() + objp->GetScale_down_move();
				//m_py = objp->GetY();
				m_size = objp->GetSiz();
			}

			if ((Button_num == 1 && g_Power_num > 0))//�p���[�{�^�����A�p���[���j�b�g��������ꍇ
			{
				//�I�u�W�F�N�g�쐬
				CObjRocket* M = new CObjRocket(m_px - (190.0f + ((m_size / g_Player_max_size) * 60.0f)), 225, 0, 1);//�I�u�W�F�N�g�쐬
				Objs::InsertObj(M, OBJ_ROCKET, 15);		//�I�u�W�F�N�g�o�^

				g_Power_num -= UNIT_CONSUME_NUM;	//�p���[���j�b�g������

				//���j�b�g������(0�ȉ�)���`�F�b�N����
				if (g_Power_num <= 0)
				{
					g_Power_num = 0;//0�����ɂȂ��Ă����ꍇ�A0�ɖ߂��B
					m_is_empty = true;//��t���OON
				}
			}
			else if (Button_num == 2 && g_Defense_num > 0)//�f�B�t�F���X�{�^�����A�f�B�t�F���X���j�b�g��������ꍇ
			{
				//�I�u�W�F�N�g�쐬
				CObjRocket* M = new CObjRocket(m_px - (190.0f + ((m_size / g_Player_max_size) * 60.0f)), 225, 0, 2);//�I�u�W�F�N�g�쐬
				Objs::InsertObj(M, OBJ_ROCKET, 15);		//�I�u�W�F�N�g�o�^

				g_Defense_num -= UNIT_CONSUME_NUM;	//�f�B�t�F���X���j�b�g������

				//���j�b�g������(0�ȉ�)���`�F�b�N����
				if (g_Defense_num <= 0)
				{
					g_Defense_num = 0;//0�����ɂȂ��Ă����ꍇ�A0�ɖ߂��B
					m_is_empty = true;//��t���OON
				}
			}
			else if (Button_num == 3 && g_Speed_num > 0)//�X�s�[�h�{�^�����A�X�s�[�h���j�b�g��������ꍇ
			{
				//�I�u�W�F�N�g�쐬
				CObjRocket* M = new CObjRocket(m_px - (190.0f + ((m_size / g_Player_max_size) * 60.0f)), 225, 0, 3);//�I�u�W�F�N�g�쐬
				Objs::InsertObj(M, OBJ_ROCKET, 15);		//�I�u�W�F�N�g�o�^

				g_Speed_num -= UNIT_CONSUME_NUM;	//�X�s�[�h���j�b�g������

				//���j�b�g������(0�ȉ�)���`�F�b�N����
				if (g_Speed_num <= 0)
				{
					g_Speed_num = 0;//0�����ɂȂ��Ă����ꍇ�A0�ɖ߂��B
					m_is_empty = true;//��t���OON
				}
			}
			else if (Button_num == 4 && g_Balance_num > 0)//�o�����X�{�^�����A�o�����X���j�b�g��������ꍇ
			{
				//�I�u�W�F�N�g�쐬
				CObjRocket* M = new CObjRocket(m_px - (190.0f + ((m_size / g_Player_max_size) * 60.0f)), 225, 0, 4);//�I�u�W�F�N�g�쐬
				Objs::InsertObj(M, OBJ_ROCKET, 15);		//�I�u�W�F�N�g�o�^

				g_Balance_num -= UNIT_CONSUME_NUM;	//�o�����X���j�b�g������

				//���j�b�g������(0�ȉ�)���`�F�b�N����
				if (g_Balance_num <= 0)
				{
					g_Balance_num = 0;//0�����ɂȂ��Ă����ꍇ�A0�ɖ߂��B
					m_is_empty = true;//��t���OON
				}
			}
			else if (Button_num == 5)//�~�T�C���{�^���̏ꍇ
			{
				CObjRocket* M = new CObjRocket(m_px - (190.0f + ((m_size / g_Player_max_size) * 60.0f)), 225, 0, 5);//�I�u�W�F�N�g�쐬
				Objs::InsertObj(M, OBJ_ROCKET, 15);		//�I�u�W�F�N�g�o�^
			}

			m_mou_f = true;
			m_a = 0.3f;		//������

			//�|�b�h�I����
			Audio::Start(3);
		}
	}
	else{}//�������Ȃ�

	//�~�T�C���{�^���ȊO�̃��L���X�g�^�C���̐���
	if (m_mou_f == true && m_is_empty == false && Button_num != 5) {	//�N���b�N������̏���(���j�b�g������̏ꍇ�A���s����Ȃ�)
		m_cnt++;			//�J�E���g����
		if (m_cnt >= RECAST_COMPLETE_POD_TIME * m_player_recast_buff) {	//�O���[�o���ϐ����J�E���g����
			m_mou_f = false;							//�N���b�N�ł���悤�ɂ���B
			m_cnt = 0;
			m_a = 1.0f;		//�s������
		}
	}
	//�~�T�C���̃��L���X�g�^�C������
	else if (m_mou_f == true && m_is_empty == false && Button_num == 5) {	//�N���b�N������̏���(���j�b�g������̏ꍇ�A���s����Ȃ�)
		m_cnt++;			//�J�E���g����
		if (m_cnt >= RECAST_COMPLETE_TIME * m_player_recast_buff) {	//�O���[�o���ϐ����J�E���g����
			m_mou_f = false;							//�N���b�N�ł���悤�ɂ���B
			m_cnt = 0;
			m_a = 1.0f;		//�s������
		}
	}

	CObjFight* obj = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
	if (battle_end == true) {	//���Ԑ؂��
		m_mou_f = true;			//�}�E�X����
		m_a -= 0.03f;				//������
		m_a2 -= 0.1f;		//������
		if (m_a > 0.0f && m_a2 > 0.0f)
			this->SetStatus(false);	//����
	}

}

//�h���[
void CObjRocketButton::Draw()
{
	//�`��J���[���  R=RED  G=Green  B=Blue A=alpha(���ߏ��)
	float c[4] = { 1.0f,1.0f, 1.0f, m_a };//�|�b�h�~�T�C���{�^���p
	float d[4] = { 1.0f,1.0f, 1.0f, m_a2 };//�l���s���A�C�R���A���L���X�g�Q�[�W(���ݒl)�p
	float b[4] = { 0.0f,0.0f, 0.0f, m_a2 };//���L���X�g�Q�[�W(�ő�l)�p

	RECT_F src;//�؂���ʒu
	RECT_F dst;//�\���ʒu
	
	//�{�^�����͂�1�`4�̎��̐؂���ʒu
	if (Button_num >= 1 && Button_num <= 4)
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 156.0f;
		src.m_bottom = 156.0f;
	}
	//����ȊO�Ȃ�~�T�C���̐؂���ʒu
	else
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 300.0f;
		src.m_bottom = 180.0f;
	}
		dst.m_top = m_y;
		dst.m_left = m_x;
		dst.m_right = m_x + m_w;
		dst.m_bottom = m_y + m_h;

	//�|�b�h�E�~�T�C���̕\�����邽�߂�switch��
	switch (Button_num){
	case 1:                 //-------------------------�ԐF�{�^��
		//11�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
		Draw::Draw(11, &src, &dst, c, 0.0f);
		break;
	case 2:                 //-------------------------�F�{�^��
		//12�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
		Draw::Draw(12, &src, &dst, c, 0.0f);
		break;
	case 3:                 //-------------------------�ΐF�{�^��
		//13�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
		Draw::Draw(13, &src, &dst, c, 0.0f);
		break;
	case 4:                 //-------------------------�D�F�{�^��
		//14�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
		Draw::Draw(14, &src, &dst, c, 0.0f);
		break;
	case 5:                 //-------------------------�~�T�C���{�^��
		//15�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
		Draw::Draw(15, &src, &dst, c, 0.0f);
		break;
	}

	//�l���s���A�C�R���\��(���j�b�g������̎��ɕ\�������)
	if (m_is_empty == true)
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 398.0f;
		src.m_bottom = 130.0f;

		dst.m_top = m_y + 25.0f;
		dst.m_left = m_x - 10.0f;
		dst.m_right = m_x + m_w + 10.0f;
		dst.m_bottom = m_y + m_h - 25.0f;
		Draw::Draw(31, &src, &dst, d, 0.0f);
	}

	//���L���X�g�Q�[�W�\��(���^���ɂȂ遁���L���X�g����)
	//�����L���X�g���̂ݕ\�������
	//�|�b�h�֌W�̏���
	if (m_mou_f == true && m_is_empty == false && Button_num != 5)
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 128.0f;
		src.m_bottom = 10.0f;

		dst.m_top = m_y + m_h - 15.0f;
		dst.m_left = m_x;
		dst.m_bottom = m_y + m_h - 5.0f;

		//���ő�l�\��
		dst.m_right = m_x + m_w;
		Draw::Draw(32, &src, &dst, b, 0.0f);

		//�����ݒl�\��		
		dst.m_right = m_x + (m_w * (m_cnt / (RECAST_COMPLETE_POD_TIME * m_player_recast_buff)));
		Draw::Draw(32, &src, &dst, d, 0.0f);
	}
	//�~�T�C���̏���
	else if (m_mou_f == true && m_is_empty == false &&Button_num==5)
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 128.0f;
		src.m_bottom = 10.0f;

		dst.m_top = m_y + m_h - 15.0f;
		dst.m_left = m_x;
		dst.m_bottom = m_y + m_h - 5.0f;

		//���ő�l�\��
		dst.m_right = m_x + m_w;
		Draw::Draw(32, &src, &dst, b, 0.0f);

		//�����ݒl�\��		
		dst.m_right = m_x + (m_w * (m_cnt / (RECAST_COMPLETE_TIME * m_player_recast_buff)));
		Draw::Draw(32, &src, &dst, d, 0.0f);
	}

}