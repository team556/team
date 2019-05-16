//�g�p����w�b�_�[�t�@�C��
//#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
//#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�}�N��
#define PLAYER (0)	//�v���C���[(�z��𕪂���₷������p)
#define ENEMY  (1)	//�G�l�~�[	(�z��𕪂���₷������p)
#define RECAST_BUFF_MAGNIFICATION (0.5f)	//�~�T�C���|�b�h���L���X�g�^�C���̃o�t�{��(���L���X�g�^�C����0.5�{�����L���X�g�^�C���������ōς�)

#define INI_BUFF (1.0f) //��L2�̃o�t�{�������l(����1�����Ȃ����c�c)

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
	m_a = 1.0f;

	m_mou_x = 0.0f;	
	m_mou_y = 0.0f;
	m_mou_r = false;
	m_mou_l = false;


	for (int i = 0; i < 2; i++)
	{
		m_count[i] = 0;
		m_is_used_special[i] = false;
		m_is_invocating[i] = false;
	}

	m_enemy_special_equipment = 0;
	m_enemy_special_button = false;

	//�����ۂɃI�u�W�F�N�g�����擾����
	FightScene = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
	Player = (CObjPlanet*)Objs::GetObj(OBJ_PLANET);
	Enemy =  (CObjPlanet*)Objs::GetObj(OBJ_ENEMY);
	Pod1 = (CObjRocketButton*)Objs::GetObj(OBJ_POD_BUTTON1);
	Pod2 = (CObjRocketButton*)Objs::GetObj(OBJ_POD_BUTTON2);
	Pod3 = (CObjRocketButton*)Objs::GetObj(OBJ_POD_BUTTON3);
	Pod4 = (CObjRocketButton*)Objs::GetObj(OBJ_POD_BUTTON4);
	Missile = (CObjRocketButton*)Objs::GetObj(OBJ_MISSILE_BUTTON);
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
		(m_mou_l == true) &&							//���N���b�N
		(g_Special_equipment != 0) &&					//�X�y�V�����Z�������Ă邩�`�F�b�N
		(m_is_used_special[PLAYER] == false) ||			//�X�y�V�����Z�����g�p�ł���Ύ��s
		(m_is_invocating[PLAYER] == true))				//�܂��A���݃X�y�V�����Z�������ł����Ă����s
	{
		m_is_used_special[PLAYER] = true;	//�X�y�V�����Z�g�p�σt���O����
		m_is_invocating[PLAYER] = true;		//�������Ǘ��t���OON


		//���X�y�V�����Z�������o(�G�f���ł��g���̂Ŋ֐����K�{)


		//���ݑ������̃X�y�V�����Z�𔻕ʌ�A
		//���̃X�y�V�����Z�̌��ʂ����ۂɔ�������


		//��[�G�ɑ�_���[�W]�̏���
		if (g_Special_equipment == 1)
		{
			//�G�l�~�[�����G�ł͂Ȃ��A���G�l�~�[��HP��0����̎��A
			//0.5�b���ɃG�l�~�[��HP������������B
			if (m_count[PLAYER] % 30 == 0 && Enemy->GetInvincible() == false && (Enemy->GetHp() > 0))
			{
				Enemy->SetDamage();		//HP-1
				Enemy->SetScale_down();	//�T�C�Y����
			}

			m_count[PLAYER]++;//���ʎ��Ԍv��

			//2�b�o�ߌ�A�X�y�V�����Z�̌��ʂ��I������
			if (m_count[PLAYER] > 60 * 2)
			{
				m_is_invocating[PLAYER] = false;	//�������Ǘ��t���OOFF
			}
		}
		//��[���E��]�̏���
		else if (g_Special_equipment == 2)
		{

		}
		//��[��莞�Ԗ��G]�̏���
		else if (g_Special_equipment == 3)
		{
			Player->SetInvincible(true);	//�v���C���[���G�t���O��ON
			
			m_count[PLAYER]++;//���ʎ��Ԍv��

			//10�b�o�ߌ�A�X�y�V�����Z�̌��ʂ��I������
			if (m_count[PLAYER] > 60 * 10)
			{
				Player->SetInvincible(false);	//�v���C���[���G�t���O��OFF
				m_is_invocating[PLAYER] = false;//�������Ǘ��t���OOFF
			}
		}
		//��[���Y�������A�b�v]�̏���
		else if (g_Special_equipment == 4)
		{
			//���~�T�C���|�b�h�̃��L���X�g�^�C����0.5�{�A
			//�܂�A���L���X�g�^�C���������̎��Ԃōςނ悤��
			//���ꂼ��̃{�^���ɐݒ�B
			Pod1->SetRecastBuff(RECAST_BUFF_MAGNIFICATION);
			Pod2->SetRecastBuff(RECAST_BUFF_MAGNIFICATION);
			Pod3->SetRecastBuff(RECAST_BUFF_MAGNIFICATION);
			Pod4->SetRecastBuff(RECAST_BUFF_MAGNIFICATION);
			Missile->SetRecastBuff(RECAST_BUFF_MAGNIFICATION);
			
			m_count[PLAYER]++;//���ʎ��Ԍv��

			//20�b�o�ߌ�A�X�y�V�����Z�̌��ʂ��I������
			if (m_count[PLAYER] > 60 * 20)
			{
				//���~�T�C���|�b�h�̃��L���X�g�^�C�������ɖ߂�
				Pod1->SetRecastBuff(INI_BUFF);
				Pod2->SetRecastBuff(INI_BUFF);
				Pod3->SetRecastBuff(INI_BUFF);
				Pod4->SetRecastBuff(INI_BUFF);
				Missile->SetRecastBuff(INI_BUFF);

				m_is_invocating[PLAYER] = false;//�������Ǘ��t���OOFF
			}
		}
		//��[�Z���̎m�C���A�b�v]�̏���
		else if (g_Special_equipment == 5)
		{
			//Player->SetDamageBuff()
		}


		//���e�X�g�p
		//Player->SetDamage();
		//Player->SetScale_down();
		//Enemy->SetDamage();
		//Enemy->SetScale_down();



		//if (m_count[0] == 0)
		//{
		//	Enemy->SetInvincible(true);
		//	m_count[0] = 1;
		//}
		//else
		//{
		//	Player->SetInvincible(false);
		//	m_count[0] = 0;
		//}




		////���G�l�~�[�̃_���[�W����
		//if (m_special_1[ENEMY] == true && (m_hp > 0))
		//{
		//	m_special_count[ENEMY]++;

		//	//���G�t���O��true�̎��͈ȉ��̃_���[�W�������΂�+1�b���Ɏ��s
		//	if (m_special_count[ENEMY] % 60 && m_invincible_f[ENEMY] == false)
		//	{
		//		m_hp -= 1;				//HP-1
		//		m_size -= m_size / 20;	//�T�C�Y����
		//	}

		//	if (m_special_count[ENEMY] >= 300)
		//	{
		//		m_special_1[ENEMY] = false;
		//	}
		//}





		//m_is_invocating[PLAYER] = false;	//�������Ǘ��t���OOFF
		
		m_a = 0.3f;		//������
	}

	//���G�f���X�y�V�����Z����
	//if (*m_enemy_special_button == true &&				//�G�X�y�V�����Z�����`�F�b�N
	//	m_is_used_special[ENEMY] == false)				//�X�y�V�����Z���g�p���`�F�b�N
	//{
	//	m_is_used_special[ENEMY] == true;	//�X�y�V�����Z�g�p�σt���O����
	//}

	//�����Ԑ؂�̎��̏���
	if (FightScene->GetCount() <= 60)
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


	//�X�y�V�����Z���������̓{�^����\���ɂ���
	if (g_Special_equipment != 0)
	{
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

	////���X�y�V�����Z�������o���̔w�i�\��
	//src.m_top = 0.0f;
	//src.m_left = 0.0f;
	//src.m_right = 175.0f;
	//src.m_bottom = 114.0f;

	//dst.m_top = m_y;
	//dst.m_left = m_x;
	//dst.m_right = m_x + m_w;
	//dst.m_bottom = m_y + m_h;
	//Draw::Draw(20, &src, &dst, c, 0.0f);
}