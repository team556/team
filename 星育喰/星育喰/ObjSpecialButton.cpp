//�g�p����w�b�_�[�t�@�C��
//#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
//#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjSpecialButton::CObjSpecialButton(float x, float y, float h, float w)
{
	//�쐬���ɓn���ꂽ�l���A���W�̏����l�ɑ��
	m_x = x;
	m_y = y;
	m_h = h;
	m_w = w;
}

//�C�j�V�����C�Y
void CObjSpecialButton::Init()
{
	m_mou_x = 0.0f;	
	m_mou_y = 0.0f;
	m_mou_r = false;
	m_mou_l = false;

	m_a = 1.0f;	

	//���e�X�g�p
	//CObjPlanet* pla = (CObjPlanet*)Objs::GetObj(OBJ_PLANET);
	//m_invincible_f[PLAYER] = pla->GetInvincible_sp(PLAYER);
}

//�A�N�V����
void CObjSpecialButton::Action()
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


	//���v���C���[�f���X�y�V�����Z����(���̓G�f��ver�ƂقƂ�ǔ��悤�ł���Ό�Ŋ֐���)
	if ((m_x <= m_mou_x && m_mou_x <= (m_x + m_w)) && 	//X���͈�
		(m_y <= m_mou_y && m_mou_y <= (m_y + m_h)) &&	//Y���͈�
		 m_mou_l == true &&								//�N���b�N
		 m_is_used_special[PLAYER] == false)			//�X�y�V�����Z���g�p���`�F�b�N
	{
		//���X�y�V�����Z�������o(�G�f���ł��g���̂Ŋ֐����K�{)


		//���ݑ������̃X�y�V�����Z�𔻕ʌ�A
		//���̃X�y�V�����Z�̌��ʂ����ۂɔ�������


		//���e�X�g�p
		//*m_invincible_f[PLAYER] = true;



		m_is_used_special[PLAYER] = true;	//�X�y�V�����Z�g�p�σt���O����
		m_a = 0.3f;		//������
	}

	//���G�f���X�y�V�����Z����
	//if (*m_enemy_special_button == true &&				//�G�X�y�V�����Z�����`�F�b�N
	//	m_is_used_special[ENEMY] == false)				//�X�y�V�����Z���g�p���`�F�b�N
	//{
	//	m_is_used_special[ENEMY] == true;	//�X�y�V�����Z�g�p�σt���O����
	//}

	//�����Ԑ؂�̎��̏���
	CObjFight* obj = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
	if (obj->GetCount() <= 60) 
	{	
		m_is_used_special[PLAYER] = true;	//���Ԑ؂�ŃX�y�V�����Z�����s�ɂ���
		m_is_used_special[ENEMY]  = true;	//�������G���X�y�V�����Z�����s�ɂ���
		m_a -= 0.03f;				//���X�ɓ���������
		if (m_a > 0.0f)
			this->SetStatus(false);	//���S�����ɂȂ������_�ŏ���
	}
}

//�h���[
void CObjSpecialButton::Draw()
{
	//�`��J���[���  R=RED  G=Green  B=Blue A=alpha(���ߏ��)
	float c[4] = { 1.0f,1.0f, 1.0f, m_a };

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu


	//���X�y�V�����Z�{�^���\��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 175.0f;
	src.m_bottom = 114.0f;

	dst.m_top = m_y;
	dst.m_left = m_x;
	dst.m_right = m_x + m_w;
	dst.m_bottom = m_y + m_h;
	Draw::Draw(19, &src, &dst, c, 0.0f);
}