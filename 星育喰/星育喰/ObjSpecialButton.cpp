//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
//#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

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

	m_special_staging_f = false;
	m_staging_font_color = 0.0f;

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
	//���X�y�V�����Z�������o���͂��̉e�����󂯂Ȃ��悤�ɂ���
	if (battle_start == false && m_special_staging_f == false)
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
		m_is_invocating[PLAYER] = true;		//�������Ǘ��t���OON
		Special_staging_message(PLAYER, g_Special_equipment);//�X�y�V�����Z�������o���b�Z�[�W��ݒ肷��


		//���X�y�V�����Z�������o(�G�f���ł��g���̂Ŋ֐����K�{)
		if (m_is_used_special[PLAYER] == false)
		{
			m_special_staging_f = true;		//�X�y�V�����Z�������o�t���OON
			battle_start = false;			//�퓬�J�n�t���O��false�ɂ��鎖�Ő퓬�S�̂��ꎞ��~������

			m_count[PLAYER]++;//���o���Ԍv��

			//2�b�o�ߌ�A�X�y�V�����Z�������o���I������
			if (m_count[PLAYER] > 60 * 2)
			{
				m_count[PLAYER] = 0;				//���̌���g�p����̂�0�ŏ���������
				m_special_staging_f = false;		//�X�y�V�����Z�������o�t���OOFF
				battle_start = true;				//�퓬�J�n�t���O��true�ɂ��鎖�ňꎞ��~����������
				m_is_used_special[PLAYER] = true;	//�X�y�V�����Z�g�p�σt���O����
			}

			return;
		}
			
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
			//���X�y�V�����Z(FRACTURE_RAY)�̓����蔻���ݒu����
			//���̓����蔻��Ƀ~�T�C���|�b�h��HIT����ƁA���ŏ��������s�����B
			//�U�����莞�Ԃ�0.05�b�B

			//�I�����C���������C���̎�(���̏����͈�x�̂ݎ��s�����)
			if (FightScene->GetLine() == 1 && m_count[PLAYER] == 0)	
			{
				Hits::SetHitBox(this, 0.0f, 280.0f, 1200.0f, 110.0f, ELEMENT_NULL, OBJ_FRACTURE_RAY, PLAYER);	//�����C���͈̔͂ɓ����蔻���ݒu
			}
			//�I�����C���������C���̎�(���̏����͈�x�̂ݎ��s�����)
			else if (FightScene->GetLine() == 2 && m_count[PLAYER] == 0)
			{
				Hits::SetHitBox(this, 0.0f, 390.0f, 1200.0f, 310.0f, ELEMENT_NULL, OBJ_FRACTURE_RAY, PLAYER);	//�����C���͈̔͂ɓ����蔻���ݒu
			}
			//�I�����C�����ド�C���̎�(���̏����͈�x�̂ݎ��s�����)
			else if (m_count[PLAYER] == 0)
			{
				Hits::SetHitBox(this, 0.0f, 0.0f, 1200.0f, 280.0f, ELEMENT_NULL, OBJ_FRACTURE_RAY, PLAYER);		//�ド�C���͈̔͂ɓ����蔻���ݒu
			}

			m_count[PLAYER]++;//���ʎ��Ԍv��

			//0.05�b�o�ߌ�A�X�y�V�����Z�̌��ʂ��I������
			if (m_count[PLAYER] > 60 * 0.05)
			{
				Hits::DeleteHitBox(this);			//�X�y�V�����Z(FRACTURE_RAY)�̓����蔻����폜
				m_is_invocating[PLAYER] = false;	//�������Ǘ��t���OOFF
			}
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
	float button[4] = { 1.0f,1.0f,1.0f,m_a };		//�X�y�V�����Z�{�^���p
	float blackout[4] = { 1.0f,1.0f,1.0f,0.5f };	//��ʑS�̂��Ó]�摜�p

	//�X�y�V�����Z�������o�t�H���g�p
	float staging_font[2][4] =
	{
		{ m_staging_font_color,0.0f,(1.0f - m_staging_font_color),1.0f },//1�s�ڂ̓v���C���[�Ȃ�F�A�G�l�~�[�Ȃ�ԐF
		{ 1.0f,1.0f,0.0f,1.0f },//2�s�ڂ͉��F
	};

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
		Draw::Draw(19, &src, &dst, button, 0.0f);
	}

	//�X�y�V�����Z�������o���A�ȉ��̂��̂�`�悷��
	if (m_special_staging_f == true)
	{
		//���X�y�V�����Z�������o���̔w�i(��ʑS�̂��Ó])�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1200.0f;
		src.m_bottom = 700.0f;

		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = 1200.0f;
		dst.m_bottom = 700.0f;
		Draw::Draw(20, &src, &dst, blackout, 0.0f);

		//���X�y�V�����Z�������o�t�H���g�\��
		for (int i = 0; i < 2; i++)
		{
			Font::StrDraw(m_staging_message[i], 50.0f, 50.0f + i * 40.0f, 25.0f, staging_font[i]);
		}
	}
}

//---Special_staging_message�֐�
//����1�@int Planet_id		:�f�����ʔԍ�(0:�v���C���[�f���@1:�G�f��)
//����2�@int Special_equip	:�������̃X�y�V�����Z(0:�������@1:�G�ɑ�_���[�W�@2:���E���@3:��莞�Ԗ��G�@4:���Y�������A�b�v�@5:�Z���̎m�C���A�b�v)
//�����e
//�X�y�V�����Z�𔭓������f���A���ݑ������̃X�y�V�����Z���l������
//�X�y�V�����Z�������o���b�Z�[�W��ݒ肷��B
void CObjSpecialButton::Special_staging_message(int Planet_id, int Special_equip)
{
	if (Planet_id == 0)
	{
		swprintf_s(m_staging_message[0], L"�v���C���["); //�����z��ɕ����f�[�^������
		m_staging_font_color = 0.0f;	//�t�H���g�̃J���[��F�ɐݒ肷��
	}
	else
	{
		swprintf_s(m_staging_message[0], L"�G�l�~�["); //�����z��ɕ����f�[�^������
		m_staging_font_color = 1.0f;	//�t�H���g�̃J���[��ԐF�ɐݒ肷��
	}

	if (Special_equip == 1)
	{
		swprintf_s(m_staging_message[1], L"Explosion"); //�����z��ɕ����f�[�^������
	}
	else if (Special_equip == 2)
	{
		swprintf_s(m_staging_message[1], L"Fracture Ray"); //�����z��ɕ����f�[�^������
	}
	else if (Special_equip == 3)
	{
		swprintf_s(m_staging_message[1], L"Immortality"); //�����z��ɕ����f�[�^������
	}
	else if (Special_equip == 4)
	{
		swprintf_s(m_staging_message[1], L"���~�b�g�u���C�N"); //�����z��ɕ����f�[�^������
	}
	else if (Special_equip == 5)
	{
		swprintf_s(m_staging_message[1], L"�X�e���C�h���^"); //�����z��ɕ����f�[�^������
	}
}
