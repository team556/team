//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"
#include "ObjPushUnit.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjPushUnit::CObjPushUnit(float x, float y, float h, float w, int n)
{
	//�쐬���ɓn���ꂽ�l���A���W�̏����l�ɑ��
	m_x = x;
	m_y = y;
	m_h = h;
	m_w = w;

	Button_num = n;
}

//�C�j�V�����C�Y
void CObjPushUnit::Init()
{
	m_mou_x = 0.0f;	//�}�E�XX���W
	m_mou_y = 0.0f; //�}�E�XY���W
	m_mou_r = false;//�E�N���b�N
	m_mou_l = false;//���N���b�N
	m_mou_f = false;//�}�E�X�t���O

	m_a = 1.0f;		//�����x

	m_cnt = 0;		//�J�E���g
}

//�A�N�V����
void CObjPushUnit::Action()
{

	//�}�E�X�̈ʒu���擾
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//�}�E�X�̃{�^���̏��
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();


	if ((m_x <= m_mou_x && m_mou_x <= (m_x + m_w))		//X���͈�
		&& (m_y <= m_mou_y && m_mou_y <= (m_y + m_h))	//Y���͈�
		&& m_mou_l == true) {							//�N���b�N
		if (m_mou_f == false) {
			//���|�b�h�쐬X�ʒu��ݒ�
			CObjFight* obj = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
			m_create_x = obj->GetCount() / 10 + 100;

			g_Power_num;				//�p���[�Z����
			g_Defense_num;			//�f�B�t�F���X�Z����
			g_Speed_num;				//�X�s�[�h�Z����
			g_Balance_num;			//�o�����X�Z����

			if (Button_num == 1 && g_Power_num != 0)//�p���[�{�^�����A�p���[���j�b�g��������ꍇ
			{
				//�I�u�W�F�N�g�쐬
				CObjMissile* M = new CObjMissile(575 + m_create_x, 200, true,1);//�I�u�W�F�N�g�쐬
				Objs::InsertObj(M, OBJ_MISSILE, 15);		//�I�u�W�F�N�g�o�^

			}
			else if (Button_num == 2 && g_Defense_num != 0)
			{
				//�I�u�W�F�N�g�쐬
				CObjMissile* M = new CObjMissile(575 + m_create_x, 200, true, 2);//�I�u�W�F�N�g�쐬
				Objs::InsertObj(M, OBJ_MISSILE, 15);		//�I�u�W�F�N�g�o�^

			}
			else if (Button_num == 3 && g_Speed_num != 0)
			{
				//�I�u�W�F�N�g�쐬
				CObjMissile* M = new CObjMissile(575 + m_create_x, 200, true, 3);//�I�u�W�F�N�g�쐬
				Objs::InsertObj(M, OBJ_MISSILE, 15);		//�I�u�W�F�N�g�o�^

			}

			else if (Button_num == 4 && g_Balance_num != 0)
			{
				//�I�u�W�F�N�g�쐬
				CObjMissile* M = new CObjMissile(575 + m_create_x , 200, true, 4);//�I�u�W�F�N�g�쐬
				Objs::InsertObj(M, OBJ_MISSILE, 15);		//�I�u�W�F�N�g�o�^
			}

			else if (Button_num == 5)
			{
				CObjMissile* M = new CObjMissile(575 + m_create_x , 200, true, 5);//�I�u�W�F�N�g�쐬
				Objs::InsertObj(M, OBJ_MISSILE, 15);		//�I�u�W�F�N�g�o�^
			}

			m_mou_f = true;
			m_a = 0.3f;		//������
		}
	}

	else{}

	if (m_mou_f == true) {	//�N���b�N������̏���
		m_cnt++;			//�J�E���g����
		if (m_cnt == 60 * 5) {	//5�b�Ԑ�������
			m_mou_f = false;	//�N���b�N�ł���悤�ɂ���B
			m_cnt = 0;
			m_a = 1.0f;		//�s������
		}
	}

	CObjFight* obj = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
	if (obj->GetCount() <= 60) {	//���Ԑ؂��
		m_mou_f = true;			//�}�E�X����
		m_a -= 0.03f;				//������
		if (m_a > 0.0f) 
			this->SetStatus(false);	//����
	}
}

//�h���[
void CObjPushUnit::Draw()
{
	//�`��J���[���  R=RED  G=Green  B=Blue A=alpha(���ߏ��)
	float c[4] = { 1.0f,1.0f, 1.0f, m_a };

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
}