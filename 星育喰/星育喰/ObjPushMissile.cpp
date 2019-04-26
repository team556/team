//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"
#include "ObjPushMissile.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjPushMissile::CObjPushMissile(float x, float y, float h, float w)
{
	//�쐬���ɓn���ꂽ�l���A���W�̏����l�ɑ��
	m_x = x;
	m_y = y;
	m_h = h;
	m_w = w;
}

//�C�j�V�����C�Y
void CObjPushMissile::Init()
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
void CObjPushMissile::Action()
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
			//�I�u�W�F�N�g�쐬
			CObjMissile* M = new CObjMissile(575, 200, false);//�I�u�W�F�N�g�쐬
			Objs::InsertObj(M, OBJ_MISSILE, 10);		//�I�u�W�F�N�g�o�^

			m_mou_f = true;
			m_a = 0.3f;		//������
		}
	}
	else {}

	if (m_mou_f == true) {	//�N���b�N������̏���
		m_cnt++;			//�J�E���g����
		if (m_cnt == 60 * 5) {	//5�b�Ԑ�������
			m_mou_f = false;	//�N���b�N�ł���悤�ɂ���B
			m_cnt = 0;
			m_a = 1.0f;		//�s������
		}
	}

	CObjFight* obj = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
	if (obj->GetCount() == 0) {	//���Ԑ؂��
		m_mou_f = true;			//�}�E�X����
		m_a -= 0.03f;				//������
		if (m_a > 0.0f)
			this->SetStatus(false);	//����
	}
}

//�h���[
void CObjPushMissile::Draw()
{
	//�`��J���[���  R=RED  G=Green  B=Blue A=alpha(���ߏ��)
	float c[4] = { 1.0f,1.0f, 1.0f, m_a };

	RECT_F src;//�؂���ʒu
	RECT_F dst;//�\���ʒu

	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 300.0f;
	src.m_bottom = 180.0f;

	dst.m_top = m_y;
	dst.m_left = m_x;
	dst.m_right = m_x + m_h;
	dst.m_bottom = m_y + m_w;

	
	//15�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
	Draw::Draw(15, &src, &dst, c, 0.0f);
}