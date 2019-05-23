//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�}�N��
#define PLAYER (0)	//�v���C���[(�z��𕪂���₷������p)
#define ENEMY  (1)	//�G�l�~�[	(�z��𕪂���₷������p)
#define RECAST_BUFF_MAGNIFICATION (0.5f)	//�~�T�C���|�b�h���L���X�g�^�C���̃o�t�{��(���L���X�g�^�C����0.5�{�����L���X�g�^�C���������ōς�)
#define DAMAGE_BUFF_MAGNIFICATION (1.5f)	//�^����_���[�W�̃o�t�{��(�^����_���[�W��1.5�{�ɂȂ�)
#define INI_BUFF (1.0f)						//��L2�̃o�t�{�������l
#define INI_WIDTH (200.0f)					//[�X�y�V�����Z:Explosion / Fracture_Ray]�G�t�F�N�g�摜�̏�����
#define INI_ALPHA (1.0f)					//�X�y�V�����Z�G�t�F�N�g�摜�̏������ߓx

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

	m_staging_font_color = 0.0f;

	for (int i = 0; i < 2; i++)
	{
		m_count[i] = 0;
		m_is_used_special[i] = false;
		m_is_invocating[i] = false;
		m_special_staging_f[i] = false;

		m_Explosion_size[i] = 0.0f;
		m_Explosion_width[i] = INI_WIDTH;
		m_Explosion_pos[i] = 0.0f;
		m_Explosion_target[i] = 0;
		m_Explosion_angle[i] = 0.0f;

		m_Fracture_Ray_pos[i] = 0.0f;
		m_Fracture_Ray_width[i] = INI_WIDTH;

		m_Immortality_size[i] = 0.0f;
		
		m_Special_effect_alpha[i] = INI_ALPHA;
		m_Special_effect_alpha_vec[i] = 0.0f;
	}

	m_Enemy_line = 0;

	for (int i = 0; i < 3; i++)
	{
		m_PodMissile_count[i] = 0;
	}

	m_enemy_special_equipment = 0;
	m_enemy_special_button = false;

	//�����ۂɃI�u�W�F�N�g�����擾����
	FightScene = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
	Planet[PLAYER] = (CObjPlanet*)Objs::GetObj(OBJ_PLANET);
	Planet[ENEMY] =  (CObjPlanet*)Objs::GetObj(OBJ_ENEMY);
	PodMissile[0] = (CObjRocketButton*)Objs::GetObj(OBJ_POD_BUTTON1);
	PodMissile[1] = (CObjRocketButton*)Objs::GetObj(OBJ_POD_BUTTON2);
	PodMissile[2] = (CObjRocketButton*)Objs::GetObj(OBJ_POD_BUTTON3);
	PodMissile[3] = (CObjRocketButton*)Objs::GetObj(OBJ_POD_BUTTON4);
	PodMissile[4] = (CObjRocketButton*)Objs::GetObj(OBJ_MISSILE_BUTTON);
}

//�A�N�V����
void CObjSpecialButton::Action()
{
	//���퓬�J�n�O�͑���s�\�ɂ��鏈��
	//���X�y�V�����Z�������o���͂��̉e�����󂯂Ȃ��悤�ɂ���
	if (battle_start == false && m_special_staging_f[PLAYER] == false && m_special_staging_f[ENEMY] == false)
	{
		return;
	}

	//�}�E�X�̈ʒu���擾
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//�}�E�X�̃{�^���̏��
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();


	//���v���C���[�f���X�y�V�����Z����
	if ((m_x <= m_mou_x && m_mou_x <= (m_x + m_w)) && 	//X���͈�
		(m_y <= m_mou_y && m_mou_y <= (m_y + m_h)) &&	//Y���͈�
		(m_mou_l == true) &&							//���N���b�N
		(g_Special_equipment != 0) &&					//�X�y�V�����Z�������Ă邩�`�F�b�N
		(m_is_used_special[PLAYER] == false) ||			//�X�y�V�����Z�����g�p�ł���Ύ��s
		(m_is_invocating[PLAYER] == true))				//�܂��A���݃X�y�V�����Z�������ł����Ă����s
	{
		//�G�l�~�[���X�y�V�����Z�������o���ł���ꍇ�A
		//�ȉ��̏��������s���Ȃ��悤�ɂ���B
		if (m_special_staging_f[ENEMY] == false)
		{
			Special_process(PLAYER, ENEMY, g_Special_equipment);	//�X�y�V�����Z�����֐����Ăяo��
			m_a = 0.3f;		//�X�y�V�����Z�{�^���𓧖���
		}
	}

	//���G�f���X�y�V�����Z����
	if ((m_enemy_special_button == true) &&				//�G�X�y�V�����Z�����`�F�b�N
		(m_enemy_special_equipment != 0) &&				//�X�y�V�����Z�������Ă邩�`�F�b�N
		(m_is_used_special[ENEMY] == false) ||			//�X�y�V�����Z�����g�p�ł���Ύ��s
		(m_is_invocating[ENEMY] == true))				//�܂��A���݃X�y�V�����Z�������ł����Ă����s
	{
		//�v���C���[���X�y�V�����Z�������o���ł���ꍇ�A
		//�ȉ��̏��������s���Ȃ��悤�ɂ���B
		if (m_special_staging_f[PLAYER] == false)
		{
			Special_process(ENEMY, PLAYER, m_enemy_special_equipment);//�X�y�V�����Z�����֐����Ăяo��
		}
	}

	//�����Ԑ؂�̎��̏���
	if (FightScene->GetCount() <= 60)
	{	
		//���Ԑ؂�ŃX�y�V�����Z�����s�ɂ���
		m_is_used_special[PLAYER] = true;	
		m_is_invocating[PLAYER] = false;

		//�������G���X�y�V�����Z�����s�ɂ���
		m_is_used_special[ENEMY]  = true;	
		m_is_invocating[ENEMY] = false;

		m_a -= 0.03f;				//���X�ɓ���������
		if (m_a > 0.0f)
			this->SetStatus(false);	//���S�����ɂȂ������_�ŏ���
	}
}

//�h���[
void CObjSpecialButton::Draw()
{
	//���`��J���[���  R=RED  G=Green  B=Blue A=alpha(���ߏ��)
	float button[4] = { 1.0f,1.0f,1.0f,m_a };		//�X�y�V�����Z�{�^���p
	float blackout[4] = { 1.0f,1.0f,1.0f,0.5f };	//��ʑS�̂��Ó]�摜�p

	//�X�y�V�����Z�������o�t�H���g�p
	float staging_font[3][4] =
	{
		{ m_staging_font_color,0.0f,(1.0f - m_staging_font_color),1.0f },//1�s�ڂ̓v���C���[�Ȃ�F�A�G�l�~�[�Ȃ�ԐF
		{ 1.0f,1.0f,0.0f,1.0f },//2�s�ڂ͉��F
		{ 1.0f,1.0f,1.0f,1.0f },//3�s�ڂ͔��F
	};

	float d[4] = { 1.0f,1.0f,1.0f,1.0f };	//���̑��摜�p


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


	//�X�y�V�����Z���o(�G�t�F�N�g)
	//���v���C���[�̎��̏���
	if ((m_is_invocating[PLAYER] == true) &&	//���݃X�y�V�����Z���������ŁA
		(m_is_used_special[PLAYER] == true))	//�X�y�V�����Z�������o�I���ς݂ł���Ε`��
	{
		Special_effect(PLAYER, g_Special_equipment);//�X�y�V�����Z�G�t�F�N�g�`��֐����Ăяo��
	}

	//���G�l�~�[�̎��̏���
	if ((m_is_invocating[ENEMY] == true) &&	//���݃X�y�V�����Z���������ŁA
		(m_is_used_special[ENEMY] == true))	//�X�y�V�����Z�������o�I���ς݂ł���Ε`��
	{
		Special_effect(ENEMY, m_enemy_special_equipment);//�X�y�V�����Z�G�t�F�N�g�`��֐����Ăяo��
	}


	//�X�y�V�����Z�������o���A�ȉ��̂��̂�`�悷��
	if (m_special_staging_f[PLAYER] == true || m_special_staging_f[ENEMY] == true)
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
			Font::StrDraw(m_staging_message[i], 280.0f, 150.0f + i * 150.0f, 80.0f, staging_font[i]);
		}

		Font::StrDraw(L"�����I", 490.0f, 450.0f, 80.0f, staging_font[2]);
	}
}

//---Special_staging_message�֐�
//����1�@int Planet_id		:�f�����ʔԍ�(0:�v���C���[�f���@1:�G�f��)
//����2�@int Special_equip	:�������̃X�y�V�����Z(0:�������@1:Explosion�@2:Fracture_Ray�@3:Immortality�@4:���~�b�g�u���C�N�@5:�X�e���C�h���^)
//�����e
//�X�y�V�����Z�𔭓������f���A���ݑ������̃X�y�V�����Z���l������
//�X�y�V�����Z�������o���b�Z�[�W��ݒ肷��B
void CObjSpecialButton::Special_staging_message(int Planet_id, int Special_equip)
{
	if (Planet_id == 0)
	{
		swprintf_s(m_staging_message[0], L"   �v���C���["); //�����z��ɕ����f�[�^������
		m_staging_font_color = 0.0f;	//�t�H���g�̃J���[��F�ɐݒ肷��
	}
	else
	{
		swprintf_s(m_staging_message[0], L"�@  �G�l�~�["); //�����z��ɕ����f�[�^������
		m_staging_font_color = 1.0f;	//�t�H���g�̃J���[��ԐF�ɐݒ肷��
	}

	if (Special_equip == 1)
	{
		swprintf_s(m_staging_message[1], L"   Explosion"); //�����z��ɕ����f�[�^������
	}
	else if (Special_equip == 2)
	{
		swprintf_s(m_staging_message[1], L"  Fracture Ray"); //�����z��ɕ����f�[�^������
	}
	else if (Special_equip == 3)
	{
		swprintf_s(m_staging_message[1], L"  Immortality"); //�����z��ɕ����f�[�^������
	}
	else if (Special_equip == 4)
	{
		swprintf_s(m_staging_message[1], L"���~�b�g�u���C�N"); //�����z��ɕ����f�[�^������
	}
	else if (Special_equip == 5)
	{
		swprintf_s(m_staging_message[1], L" �X�e���C�h���^"); //�����z��ɕ����f�[�^������
	}
}

//---Special_process�֐�
//����1�@int Planet_id		:�����̘f�����ʔԍ�(0:�v���C���[�f���@1:�G�f��)
//����2�@int Opponent_id	:����̘f�����ʔԍ�(0:�v���C���[�f���@1:�G�f��)
//����3�@int Special_equip	:�������̃X�y�V�����Z(0:�������@1:Explosion�@2:Fracture_Ray�@3:Immortality�@4:���~�b�g�u���C�N�@5:�X�e���C�h���^)
//�����e
//�X�y�V�����Z�������o�A�X�y�V�����Z���ʏ����Ƃ������A
//�X�y�V�����Z���������s����B
void CObjSpecialButton::Special_process(int Planet_id, int Opponent_id, int Special_equip)
{
	m_is_invocating[Planet_id] = true;		//�������Ǘ��t���OON


	//���X�y�V�����Z�������o
	if (m_is_used_special[Planet_id] == false)
	{
		SetPrio(90);	//�I�u�W�F�N�g�D�揇�ʂ��ύX����Ă����ꍇ�A���ɖ߂��B
		Special_staging_message(Planet_id, Special_equip);//�X�y�V�����Z�������o���b�Z�[�W��ݒ肷��
		m_special_staging_f[Planet_id] = true;	//�X�y�V�����Z�������o�t���OON
		battle_start = false;			//�퓬�J�n�t���O��false�ɂ��鎖�Ő퓬�S�̂��ꎞ��~������


		//���G��[�X�y�V�����Z:Fracture_Ray]�𔭓����̂ݎ��s
		//�퓬���ꎞ��~���Ă��锭�����o���ɁA
		//[�X�y�V�����Z:Fracture_Ray]�𔭎˂��郉�C�������肷�鏈�����s���B
		//�����菈���ɂ͖�0.07�b�̎��Ԃ�v����B
		//�����˂��郉�C�������͈ȉ��̏����͎��s����Ȃ��B
		//���퓬�ꎞ��~��(���I�u�W�F�N�g�̏�����~��)�Ȃ̂�
		//"ObjRocket"��[OBJ_FRACTURE_RAY]��HIT���Ă��A
		//"ObjRocket"�̏��ŏ����͎��s����Ȃ��B
		if (Planet_id == ENEMY && Special_equip == 2 && m_Enemy_line == 0)
		{
			CHitBox* hit = Hits::GetHitBox(this);	//CHitBox�|�C���^�擾

			//0�b���̏���
			if (m_count[ENEMY] == 0)
			{
				//�����C���͈̔͂Ƀq�b�g���萔�J�E���g�p�̓����蔻���ݒu
				Hits::SetHitBox(this, 0.0f, 280.0f, 1200.0f, 110.0f, ELEMENT_ENEMYPOD, OBJ_FRACTURE_RAY, ENEMY);
			}
			//0.01�`0.05�b���̏���
			else if (1 <= m_count[ENEMY] && m_count[ENEMY] <= 3)
			{
				//�����C���������C�����ド�C���̏��Ԃ�
				//HitBox�ɓ������Ă���q�b�g����̐����J�E���g���A
				//���̐���������B
				m_PodMissile_count[m_count[ENEMY] - 1] = hit->GetCount();

				//�v���C���[�f���A�G�f������L�̃J�E���g���Ɋ܂܂�Ă����ꍇ�A
				//���̕����ȉ��̏����Ō��炵�Ă����B
				if (hit->CheckElementHit(ELEMENT_PLAYER) == true)
				{
					m_PodMissile_count[m_count[ENEMY] - 1] -= 1;
				}
				if (hit->CheckElementHit(ELEMENT_ENEMY) == true)
				{
					m_PodMissile_count[m_count[ENEMY] - 1] -= 1;
				}

				//�������o�I����A�q�b�g���萔�J�E���g�p�̓����蔻�肪���̂܂ܑ��݂��Ă���ƁA
				//"ObjRocket"�̏��ŏ��������s����Ă��܂��̂ŁA
				//�ȉ��̏����ŐV���������蔻��ݒu�O�ɁA���݂̓����蔻����폜����B
				Hits::DeleteHitBox(this);

				//�����C���̃q�b�g���萔�J�E���g�I����A���s�B
				if (m_count[ENEMY] == 1)
				{
					//���̏����ׂ̈ɁA
					//�����C���͈̔͂Ƀq�b�g���萔�J�E���g�p�̓����蔻���ݒu
					Hits::SetHitBox(this, 0.0f, 390.0f, 1200.0f, 310.0f, ELEMENT_ENEMYPOD, OBJ_FRACTURE_RAY, ENEMY);

					//�����C���ɂ̂݁A
					//�e�f�������C�����ʉ߂��Ȃ��悤�ɂ��铖���蔻�肪���݂��Ă���A
					//�J�E���g���Ɋ܂܂�Ă���ׁA���̕������炵�Ă����B
					m_PodMissile_count[m_count[ENEMY] - 1] -= 1;
				}
				else if (m_count[ENEMY] == 2)
				{
					//���̏����ׂ̈ɁA
					//�ド�C���͈̔͂Ƀq�b�g���萔�J�E���g�p�̓����蔻���ݒu
					Hits::SetHitBox(this, 0.0f, 0.0f, 1200.0f, 280.0f, ELEMENT_ENEMYPOD, OBJ_FRACTURE_RAY, ENEMY);
				}
			}
			//0.06�b���̏���
			else if (m_count[ENEMY] == 4)
			{
				//���I�����C�����菈��
				//��L�̏����ɂ��A�e���C���ɑ��݂���"�v���C���[�̃|�b�h�~�T�C����"��
				//�z�񂻂ꂼ��ɑ�����ꂽ��Ԃł���ׁA�����̐����r���A
				//��Ԑ����������C����[�X�y�V�����Z:Fracture_Ray]�𔭎˂���悤�ɐݒ肷��B
				//���������l�ł���ꍇ�A�ȉ��̗D�揇�ʂőI�����C�������肷��B
				//�u�����C���������C�����ド�C���v

				//�����C���Ƒ����C���Ƃ̐���r
				if (m_PodMissile_count[0] >= m_PodMissile_count[1] && m_PodMissile_count[0] >= m_PodMissile_count[2])
				{
					m_Enemy_line = 1;//�����C���Ɍ���
				}
				//�����C���Ƒ����C���Ƃ̐���r
				else if (m_PodMissile_count[1] >= m_PodMissile_count[0] && m_PodMissile_count[1] >= m_PodMissile_count[2])
				{
					m_Enemy_line = 2;//�����C���Ɍ���
				}
				else
				{
					m_Enemy_line = 3;//�ド�C���Ɍ���
				}
			}
		}

		m_count[Planet_id]++;//���o���Ԍv��

		//2�b�o�ߌ�A�X�y�V�����Z�������o���I������
		if (m_count[Planet_id] > 60 * 2)
		{
			m_count[Planet_id] = 0;				//���̌���g�p����̂�0�ŏ���������
			m_special_staging_f[Planet_id] = false;	//�X�y�V�����Z�������o�t���OOFF
			battle_start = true;				//�퓬�J�n�t���O��true�ɂ��鎖�ňꎞ��~����������
			m_is_used_special[Planet_id] = true;//�X�y�V�����Z�g�p�σt���O����
		}

		return;
	}


	//���ݑ������̃X�y�V�����Z�𔻕ʂ��A
	//���̃X�y�V�����Z�̌��ʂ̏������s���B

	//��[Explosion]�̏���
	if (Special_equip == 1)
	{
		//�X�y�V�����Z���ʏ����J�n�����1.7�b��A
		//���肪���G�ł͂Ȃ��A�������HP��0����̎��A
		//��0.1�b���ɑ����HP������������B
		//������A�v5�_���[�W�^����ݒ�ƂȂ��Ă���B
		if (m_count[Planet_id] >= 100 && m_count[Planet_id] % 5 == 0 && Planet[Opponent_id]->GetInvincible() == false && Planet[Opponent_id]->GetSiz() > 0)
		{
			Planet[Opponent_id]->SetDamage();//�T�C�Y(HP)����
			Planet[Opponent_id]->SetScale_down_move(Opponent_id);//�k�ޕ������ړ�

			//size30�ȉ��ɂȂ鎞��if���A�����ɂ��p�ӁB
		}
	
		m_count[Planet_id]++;//���ʎ��Ԍv��

		//[Explosion]�̉��o����(������̏�̏��Ԃŏ��X�Ɏ��s�����)
		if (m_Explosion_width[Planet_id] >= 860.0f)
		{
			//���G�t�F�N�g�摜�̕������܂�A��ʂ����\���ɂȂ�Ǝ��s�B
			//�I�u�W�F�N�g�D�揇�ʂ����ɖ߂��A���o�I���B
			SetPrio(90);	//�I�u�W�F�N�g�D�揇�ʂ����ɖ߂��B
		}
		else if (m_Explosion_size[Planet_id] <= -860.0f)
		{
			//���G�t�F�N�g�摜�T�C�Y����ʊO(��)�ɓ��B����Ǝ��s�B
			//�T�C�Y�ύX(������)����߂āA�G�t�F�N�g�摜�̕������X�ɋ��߂Ă����B
			SetPrio(2);//�I�u�W�F�N�g�D�揇�ʂ�ύX���A�G�t�F�N�g�摜������f���̌��ɂ����悤�ɂ���
			m_Explosion_width[Planet_id] += 10.0f;//�G�t�F�N�g�摜�̕������߂�
		}
		else if (m_Explosion_pos[Planet_id] == -1000.0f)
		{
			//�����o�����I����A���s�B
			//�G�t�F�N�g�摜����ʊO(����f���̐^��)���N�_�ɉ��ւƔ��˂��A����f�����т��B
			SetPrio(2);//�I�u�W�F�N�g�D�揇�ʂ�ύX���A�G�t�F�N�g�摜������f���̌��ɂ����悤�ɂ���
			m_Explosion_size[Planet_id] -= 20.0f;//�G�t�F�N�g�摜�T�C�Y��ύX���A�������ɉ摜��L�΂�
			m_Explosion_width[Planet_id] += 10.0f;//�G�t�F�N�g�摜�̕������߂�
		}
		else if (m_Explosion_width[Planet_id] + m_Explosion_size[Planet_id] <= 0)
		{
			//���G�t�F�N�g�摜�̕������܂�A��ʂ����\���ɂȂ�Ǝ��s�B
			//���̉��o�ׂ̈̏������s��
			m_Explosion_size[Planet_id] = 0.0f;			//�G�t�F�N�g�摜�T�C�Y�������l�ɖ߂�
			m_Explosion_width[Planet_id] = INI_WIDTH;	//�G�t�F�N�g�摜���������l�ɖ߂�
			m_Explosion_pos[Planet_id] = -1000.0f;		//�G�t�F�N�g�摜�ʒu����ʊO(��)�Ɉړ�������
			m_Explosion_target[Planet_id] = Opponent_id;//�G�t�F�N�g�Ώۂ𑊎�ɐݒ�
			m_Explosion_angle[Planet_id] = 270.0f;		//�G�t�F�N�g�p�x�����Ɍ����悤�ɐݒ�
		}
		else if (m_Explosion_size[Planet_id] > 200.0f && m_Explosion_width[Planet_id] + m_Explosion_size[Planet_id] > 0)
		{
			//���G�t�F�N�g�摜�T�C�Y����ʊO(��)�ɓ��B����Ǝ��s�B
			//�T�C�Y�ύX(�㔭��)����߂āA�G�t�F�N�g�摜�̕������X�ɋ��߂Ă����B
			m_Explosion_width[Planet_id] -= 10.0f;//�G�t�F�N�g�摜�̕������߂�
		}
		else if (m_Explosion_size[Planet_id] <= 200.0f)
		{
			//���ŏ��Ɏ��s�����B
			//�G�t�F�N�g�摜���v���C���[���N�_�ɏ�ւƔ��˂����
			m_Explosion_target[Planet_id] = Planet_id;//�G�t�F�N�g�Ώۂ������ɐݒ�
			m_Explosion_angle[Planet_id] = 90.0f;//�G�t�F�N�g�p�x����Ɍ����悤�ɐݒ�
			m_Explosion_size[Planet_id] += 20.0f;//�G�t�F�N�g�摜�T�C�Y��ύX���A������ɉ摜��L�΂�
		}
		
		//2�b�o�ߌ�A�X�y�V�����Z�̌��ʂ��I������
		if (m_count[Planet_id] > 60 * 2)
		{
			m_is_invocating[Planet_id] = false;	//�������Ǘ��t���OOFF
		}
	}
	//��[Fracture_Ray]�̏���
	else if (Special_equip == 2)
	{
		//���X�y�V�����Z(FRACTURE_RAY)�̓����蔻���ݒu����
		//���̓����蔻��Ƀ~�T�C���|�b�h��HIT����ƁA���ŏ��������s�����B
		//�U�����莞�Ԃ�0.05�b�B
		//���G�l�~�[�̑I�����C�����菈���͔������o���ɍs���Ă���B
		//������@�F�v���C���[�̃~�T�C���|�b�g����ԑ����ꏊ�ɔ��˂���

		//�I�����C���������C���̎�(���̏����͈�x�̂ݎ��s�����)
		if (FightScene->GetLine() == 1 && m_count[Planet_id] == 0 && Planet_id == PLAYER ||	//�v���C���[�̎��̏�����
			m_Enemy_line == 1 && m_count[Planet_id] == 0 && Planet_id == ENEMY)				//�G�l�~�[�̎��̏�����
		{
			Hits::SetHitBox(this, 0.0f, 280.0f, 1200.0f, 110.0f, ELEMENT_NULL, OBJ_FRACTURE_RAY, Planet_id);	//�����C���͈̔͂ɓ����蔻���ݒu
			m_Fracture_Ray_pos[Planet_id] = -5.0f;	//�����蔻��ݒu���łɃG�t�F�N�g�摜�̈ʒu�����߂�
		}
		//�I�����C���������C���̎�(���̏����͈�x�̂ݎ��s�����)
		else if (FightScene->GetLine() == 2 && m_count[Planet_id] == 0 && Planet_id == PLAYER ||//�v���C���[�̎��̏�����
				 m_Enemy_line == 2 && m_count[Planet_id] == 0 && Planet_id == ENEMY)			//�G�l�~�[�̎��̏�����
		{
			Hits::SetHitBox(this, 0.0f, 390.0f, 1200.0f, 310.0f, ELEMENT_NULL, OBJ_FRACTURE_RAY, Planet_id);	//�����C���͈̔͂ɓ����蔻���ݒu
			m_Fracture_Ray_pos[Planet_id] = 100.0f;	//�����蔻��ݒu���łɃG�t�F�N�g�摜�̈ʒu�����߂�
		}
		//�I�����C�����ド�C���̎�(���̏����͈�x�̂ݎ��s�����)
		else if (m_count[Planet_id] == 0)
		{
			Hits::SetHitBox(this, 0.0f, 0.0f, 1200.0f, 280.0f, ELEMENT_NULL, OBJ_FRACTURE_RAY, Planet_id);		//�ド�C���͈̔͂ɓ����蔻���ݒu
			m_Fracture_Ray_pos[Planet_id] = -120.0f;//�����蔻��ݒu���łɃG�t�F�N�g�摜�̈ʒu�����߂�
		}

		//[Fracture_Ray]�̉��o����(������̏�̏��Ԃŏ��X�Ɏ��s�����)
		if (m_Fracture_Ray_width[Planet_id] <= 0.0f)
		{
			//���G�t�F�N�g�摜�̕������܂�A��ʂ����\���ɂȂ�Ɖ��o�I��
		}
		else
		{
			//���ŏ��Ɏ��s�����B
			//�G�t�F�N�g�摜�������f�����瑊��f���ɑ΂��Ĕ��˂����
			//���̌�A�G�t�F�N�g�摜�̕������X�ɋ��߂Ă����B
			m_Fracture_Ray_width[Planet_id] -= 10.0f;//�G�t�F�N�g�摜�̕����߂�
		}

		m_count[Planet_id]++;//���ʎ��Ԍv��

		//0.35�b�o�ߌ�A�X�y�V�����Z�̌��ʂ��I������
		if (m_count[Planet_id] > 60 * 0.35)
		{
			m_is_invocating[Planet_id] = false;	//�������Ǘ��t���OOFF
		}
		//0.05�b�o�ߌ�A�����蔻����폜����
		else if (m_count[Planet_id] > 60 * 0.05)
		{
			Hits::DeleteHitBox(this);			//�X�y�V�����Z(FRACTURE_RAY)�̓����蔻����폜
		}
	}
	//��[Immortality]�̏���
	else if (Special_equip == 3)
	{
		//���G�t�F�N�g�摜�_�ŏ���
		//�������ߓx��1.0f�A�؂�ւ��|�C���g��0.75f�B
		//1.0f��0.75f�ֈړ�����ہA0.003���x�N�g�������Z����Ă����A
		//�����ɓ��ߓx���������Ă����B
		//�؂�ւ��|�C���g��0.75f�ɓ��B���A0.003���x�N�g�������Z����Ă������A
		//���܂ňړ������x�N�g�������c���Ă���ׁA�����ɓ��ߓx�͏㏸�����A
		//���܂ňړ������x�N�g������0.0f�ɂȂ�܂œ��ߓx�͌�������B
		//���ߓx���㏸����̂́A�؂�ւ��|�C���g�I�ɓ��ߓx��0.5f�ɂȂ������ł���B
		//���̌�͐���ƑS���^�t�̏������s���A
		//���ʓI�ɓ��ߓx��1.0f��0.5f���s��������v���O�����ƂȂ��Ă���B
		if (m_Special_effect_alpha[Planet_id] >= 0.75)
		{
			m_Special_effect_alpha_vec[Planet_id] -= 0.003f;	//�x�N�g���Ɍ��Z
		}
		else
		{
			m_Special_effect_alpha_vec[Planet_id] += 0.003f;	//�x�N�g���ɉ��Z
		}
			
		m_Special_effect_alpha[Planet_id] += m_Special_effect_alpha_vec[Planet_id];	//�x�N�g���𔽉f

		m_count[Planet_id]++;//���ʎ��Ԍv��


		//[Immortality]�̉��o����(������̏�̏��Ԃŏ��X�Ɏ��s�����)

		//�G�t�F�N�g�摜���f�����S�Ɉړ����A��ʂ����\���ɂȂ�Ɖ��o�I���B
		//���o�I����A�������Ǘ��t���O��OFF�ɂ���
		if (m_Immortality_size[Planet_id] <= 0.0f && m_count[Planet_id] > 60 * 10)
		{
			m_is_invocating[Planet_id] = false;	//�������Ǘ��t���OOFF
		}
		//10�b�o�ߌ�A�X�y�V�����Z�̌��ʂ��I�����A
		//�I�����o���s���B
		else if (m_count[Planet_id] > 60 * 10)
		{
			Planet[Planet_id]->SetInvincible(false);	//�v���C���[���G�t���O��OFF
			m_Immortality_size[Planet_id] -= 1.5f;		//�G�t�F�N�g�摜�T�C�Y��ύX���A�f�����S�ɏ��X�Ɉړ�������
		}
		//�X�y�V�����Z���ʏI���܂Ŏ����f���̎��͂ɃG�t�F�N�g�摜���o���A
		//���G�t���O��ON�ɂ���
		else
		{
			m_Immortality_size[Planet_id] = 150.0f;	//�G�t�F�N�g�摜�T�C�Y��ύX���A�����f���̎��͂ɃG�t�F�N�g�摜���o��
			Planet[Planet_id]->SetInvincible(true);	//�v���C���[���G�t���O��ON
		}
	}
	//��[���~�b�g�u���C�N]�̏���
	else if (Special_equip == 4)
	{
		//�~�T�C���|�b�h���L���X�g�^�C���̃o�t�{����ύX����
		//���v���C���[�̎��̏���
		if (Planet_id == PLAYER)
		{
			//���ꂼ��̃{�^����ύX����
			for (int i = 0; i < 5; i++)
			{
				PodMissile[i]->SetRecastBuff(RECAST_BUFF_MAGNIFICATION);//�o�t�{���ύX
			}
		}
		//���G�l�~�[�̎��̏���
		else //(Planet_id == ENEMY)
		{
			Planet[Planet_id]->SetRecastBuff(RECAST_BUFF_MAGNIFICATION);//�o�t�{���ύX
		}

		m_count[Planet_id]++;//���ʎ��Ԍv��

		//20�b�o�ߌ�A�X�y�V�����Z�̌��ʂ��I������
		if (m_count[Planet_id] > 60 * 20)
		{
			//�~�T�C���|�b�h���L���X�g�^�C���̃o�t�{�������ɖ߂�
			//���v���C���[�̎��̏���
			if (Planet_id == PLAYER)
			{
				//���ꂼ��̃{�^����ύX����
				for (int i = 0; i < 5; i++)
				{
					PodMissile[i]->SetRecastBuff(INI_BUFF);//�o�t�{�����ɖ߂�
				}
			}
			//���G�l�~�[�̎��̏���
			else //(Planet_id == ENEMY)
			{
				Planet[Planet_id]->SetRecastBuff(INI_BUFF);//�o�t�{�����ɖ߂�
			}

			m_is_invocating[Planet_id] = false;//�������Ǘ��t���OOFF
		}
		//15�b�o�ߌ�A�G�t�F�N�g�摜�_�ŏ���
		//���_�ŏ����̃v���O�������e�́A
		//��L��Immortality�̏����Ɠ����Ȃ̂ŁA
		//�ׂ��������͏ȗ�����B
		else if (m_count[Planet_id] > 60 * 15)
		{
			//�������ߓx��1.0f�A�؂�ւ��|�C���g��0.5f�B
			if (m_Special_effect_alpha[Planet_id] >= 0.5)
			{
				m_Special_effect_alpha_vec[Planet_id] -= 0.003f;	//�x�N�g���Ɍ��Z
			}
			else
			{
				m_Special_effect_alpha_vec[Planet_id] += 0.003f;	//�x�N�g���ɉ��Z
			}

			m_Special_effect_alpha[Planet_id] += m_Special_effect_alpha_vec[Planet_id];	//�x�N�g���𔽉f
		}
	}
	//��[�X�e���C�h���^]�̏���
	else if (Special_equip == 5)
	{
		damage_buff[Planet_id] = DAMAGE_BUFF_MAGNIFICATION;	//�_���[�W�o�t�{����ύX����

		//�ˏo�����|�b�h���j�󂳂��x��
		//m_count��1����������悤��ObjRocket�Őݒ肵�Ă���

		//�X�y�V�����Z�������Ă���|�b�h5�@�S�Ĕj�󂳂ꂽ��A
		//�X�y�V�����Z�̌��ʂ��I������
		if (m_count[Planet_id] >= 5)
		{
			damage_buff[Planet_id] = INI_BUFF;//�_���[�W�o�t�{�������ɖ߂�
			m_is_invocating[Planet_id] = false;	//�������Ǘ��t���OOFF
		}
	}
}

//---Special_effect�֐�
//����1�@int Planet_id		:�f�����ʔԍ�(0:�v���C���[�f���@1:�G�f��)
//����2�@int Special_equip	:�������̃X�y�V�����Z(0:�������@1:Explosion�@2:Fracture_Ray�@3:Immortality�@4:���~�b�g�u���C�N�@5:�X�e���C�h���^)
//�����e
//�X�y�V�����Z�������ɃG�t�F�N�g��`�悷��B
void CObjSpecialButton::Special_effect(int Planet_id, int Special_equip)
{
	//���`��J���[���  R=RED  G=Green  B=Blue A=alpha(���ߏ��)
	//���ߓx�ύX���K�v�ȃX�y�V�����Z�G�t�F�N�g�摜�p
	float special_effect[2][4] =
	{
		{ 1.0f,1.0f,1.0f,m_Special_effect_alpha[PLAYER] },
		{ 1.0f,1.0f,1.0f,m_Special_effect_alpha[ENEMY] },
	};

	float d[4] = { 1.0f,1.0f,1.0f,1.0f };	//���̑��摜�p


	//���t�H���g����
	wchar_t power_up_pod_count[2][2];	//������Ԃ̃|�b�h���\���p


	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu


	//��[Explosion]�̕`�揈��
	if (Special_equip == 1)
	{
		//��Explosion�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		//������1�F
		//�摜���g��k�����ƕό`����ہA
		//�ϓ���top��left��right��bottom��L�΂��Ȃ���΁A
		//���̌덷���A�摜�������L�΂���A
		//�~�����摜�ƂȂ�Ȃ��̂�
		//��{�I�ɂǂ�ȏ󋵂ł��ϓ��ɐL�΂��Ȃ��Ƃ����Ȃ��B
		//���������top�����ɉ摜��L�΂��Abottom�̈ʒu�͌Œ�Ƃ������ׁA
		//bottom�𓮂����Ȃ����Atop��2�{���������ł���ɑΉ����Ă���B
		//������2:
		//����̉摜��90�x&270�x��]�����Ďg�p���Ă���ׁA
		//top��bottom�̒l�̍���ϓ������鎖�ŁA
		//�~�����摜�ł���"���E���珙�X�ɏ����Ă������o"���s���Ă���B
		dst.m_top = Planet[m_Explosion_target[Planet_id]]->GetY() - m_Explosion_size[Planet_id] * 2 - m_Explosion_width[Planet_id] + m_Explosion_pos[Planet_id];
		dst.m_left = Planet[m_Explosion_target[Planet_id]]->GetX() - m_Explosion_size[Planet_id] + Planet[m_Explosion_target[Planet_id]]->GetScale_down_move();
		dst.m_right = Planet[m_Explosion_target[Planet_id]]->GetX() + m_Explosion_size[Planet_id] + Planet[m_Explosion_target[Planet_id]]->GetScale_down_move();
		dst.m_bottom = Planet[m_Explosion_target[Planet_id]]->GetY() + m_Explosion_width[Planet_id] + m_Explosion_pos[Planet_id];
		Draw::Draw(21, &src, &dst, d, m_Explosion_angle[Planet_id]);
	}

	//��[Fracture_Ray]�̕`�揈��
	else if (Special_equip == 2)
	{
		//��Fracture_Ray�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = -64.0f + (Planet_id * 128.0f);//�v���C���[�̎��͍������A�G�l�~�[�̎��͉E�����ɂȂ�悤�ɐݒ�B
		src.m_bottom = 32.0f;

		dst.m_top = Planet[Planet_id]->GetY() - m_Fracture_Ray_width[Planet_id] + m_Fracture_Ray_pos[Planet_id];

		//left��right�̕`�揈���̓v���C���[�ƃG�l�~�[�ő傫���Ⴄ�ׁA�ʁX�ŏ������s���B
		if (Planet_id == PLAYER)
		{
			dst.m_left = 0.0f;
			dst.m_right = Planet[Planet_id]->GetX() + Planet[Planet_id]->GetScale_down_move();
		}
		else //(Planet_id == ENEMY)
		{
			dst.m_left = Planet[Planet_id]->GetX() + Planet[Planet_id]->GetScale_down_move();
			dst.m_right = 1200.0f;
		}

		dst.m_bottom = Planet[Planet_id]->GetY() + m_Fracture_Ray_width[Planet_id] + m_Fracture_Ray_pos[Planet_id];
		Draw::Draw(22, &src, &dst, d, 0.0f);
	}

	//��[Immortality]�̕`�揈��
	else if (Special_equip == 3)
	{
		//��Immortality�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = Planet[Planet_id]->GetY() - m_Immortality_size[Planet_id];
		dst.m_left = Planet[Planet_id]->GetX() - m_Immortality_size[Planet_id] + Planet[Planet_id]->GetScale_down_move();
		dst.m_right = Planet[Planet_id]->GetX() + m_Immortality_size[Planet_id] + Planet[Planet_id]->GetScale_down_move();
		dst.m_bottom = Planet[Planet_id]->GetY() + m_Immortality_size[Planet_id];
		Draw::Draw(23, &src, &dst, special_effect[Planet_id], 0.0f);
	}

	//��[���~�b�g�u���C�N]�̕`�揈��
	else if (Special_equip == 4)
	{
		//�����~�b�g�u���C�N�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		//�������f���̏�ɕ`�悷��悤�ɐݒ肵�Ă���
		dst.m_top = Planet[Planet_id]->GetY() - 190.0f;
		dst.m_left = Planet[Planet_id]->GetX() - 37.5f + Planet[Planet_id]->GetScale_down_move();
		dst.m_right = Planet[Planet_id]->GetX() + 37.5f + Planet[Planet_id]->GetScale_down_move();
		dst.m_bottom = Planet[Planet_id]->GetY() - 115.0f;
		Draw::Draw(24, &src, &dst, special_effect[Planet_id], 0.0f);
	}

	//��[�X�e���C�h���^]�̕`�揈��
	else if (Special_equip == 5)
	{
		//���X�e���C�h���^�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		//�������f���̏�ɕ`�悷��悤�ɐݒ肵�Ă���
		dst.m_top = Planet[Planet_id]->GetY() - 190.0f;
		dst.m_left = Planet[Planet_id]->GetX() - 60.0f + Planet[Planet_id]->GetScale_down_move();
		dst.m_right = Planet[Planet_id]->GetX() + 15.0f + Planet[Planet_id]->GetScale_down_move();
		dst.m_bottom = Planet[Planet_id]->GetY() - 115.0f;
		Draw::Draw(25, &src, &dst, d, 0.0f);

		//��������Ԃ̃|�b�h���\��
		swprintf_s(power_up_pod_count[Planet_id], L"%d", (5 - m_count[Planet_id]));
		Font::StrDraw(power_up_pod_count[Planet_id], Planet[Planet_id]->GetX() + 15.0f + Planet[Planet_id]->GetScale_down_move(), Planet[Planet_id]->GetY() - 190.0f, 75.0f, d);
	}
}
