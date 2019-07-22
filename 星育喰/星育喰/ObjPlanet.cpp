//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjPlanet.h"
#include <stdlib.h>
#include <time.h>

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�}�N��
#define ONE_DELAY (150)
#define SEC_DELAY (120)
#define THI_DELAY (105)
#define FOU_DELAY (120)
#define FIV_DELAY (105)
#define MIN_SIZE (60.0f)//�e�f���̍ŏ��T�C�Y(����ȏ�͏������Ȃ�Ȃ�)

#define MOAI_NAM (1)	//���A�C�̔ԍ�type�ݒ�(��

//�R���X�g���N�^
CObjPlanet::CObjPlanet(float x, float y, float size, int type)
{
	//�쐬���ɓn���ꂽ�l���A�e�X�e�[�^�X�ɑ��
	m_px = x;
	m_py = y;
	m_size = size;
	m_siz_max = size;
	m_type = type + 1;
	//m_get_siz = siz;
}

//�C�j�V�����C�Y
void CObjPlanet::Init()
{
	//�e�X�e�[�^�X������
	//m_size = 50.0f;//�T�C�Y
	//m_siz_max= 50.0f;
	//m_siz_vec=  0.0f;
	m_siz_change_range = 60.0f;
	m_scale_down_move = 0.0f;
	m_r = 0.0f;

	m_cnt = 0;		//�J�E���g

	//m_get_hp = 0;	//�擾HP

	m_invincible_f = false;
	m_enemy_recast_buff = 1.0f;

	m_time = 0; //�^�C���J�E���g������
	m_attackf = 0;

	Enemy_Attack_pattern_x = 0;

	srand(time(NULL));
	Enemy_Attack_pattern_y = rand() % 5;//�����s���p�^�[���������_���Ō��߂�(���̏����Ȃ��Ə����s���p�^�[�����K��0�̂��̂ɂȂ�)

	Enemy_Line_pattern_x = 0;

	srand(time(NULL));
	Enemy_Line_pattern_y = rand() % 3;//�����s���p�^�[���������_���Ō��߂�(���̏����Ȃ��Ə����s���p�^�[�����K��0�̂��̂ɂȂ�)

	CObjFight* fit = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
	m_mov_spd = 0.093f* 30 / (fit->GetCount() / 70);//�������x
	//*m_siz_spd*/ = 0.07f * 30 / (fit->GetCount() / 40);//�g�呬�x

	if (m_type == 0)
		m_px += 0.0f;
	else
		m_px -= 0.0f;

	m_mani[0] = 4;
	m_mani[1] = 0;
	m_mani[2] = 1;
	m_mani[3] = 0;
	m_mani[4] = 2;
	m_mani[5] = 3;

	m_ani[0] = 0;//�A�j���[�V�����f�[�^�̏�����
	m_ani[1] = 1;
	m_ani[2] = 2;
	m_ani[3] = 1;

	m_ani_frame[0] = 0;
	m_ani_frame[1] = 0;
	m_ani_time = 0;
	m_cntf = 0;
	m_eat_f = false;	//�򂤃t���O(true = ��)
	m_eat_me = false;
	m_eat_spd = fit->GetCount();
	m_del_f = false;	//�����t���O(true = ����)

	m_r2 = 0.0f;		
	m_vy = 0.0f;
	m_sweat_vy = 0.0f;

	m_subsize = 0.0f;

	//m_img_nam = 0;
	
	//�����蔻��pHitBox���쐬(�A�N�V�������ɍX�V�����ׁA���ƍ����͂��̎��_�ł�0.0f��OK�B)
	//����ɉ����e�f����HP�A�摜�ԍ������ݒ肵�Ă���B
	if (m_type == 0) {		//�v���C���[�f��
		Hits::SetHitBox(this, m_px, m_py, 0.0f, 0.0f, ELEMENT_PLAYER, OBJ_PLANET, 1);
		m_img_nam = 3 + ((int)((g_Bar_Level + g_Ins_Level) / 2)) - 1;
	}
	else if (m_type == 1) {	//������1�Ԗڂ̓G�f��
		Hits::SetHitBox(this, m_px, m_py, 0.0f, 0.0f, ELEMENT_ENEMY, OBJ_PLANET, 1);
		m_img_nam = 26;
		m_size = 100;
		m_siz_max = 100;
	}
	else if (m_type == 2) {	//������2�Ԗڂ̓G�f��
		Hits::SetHitBox(this, m_px, m_py, 0.0f, 0.0f, ELEMENT_ENEMY, OBJ_PLANET, 1);
		m_img_nam = 27;
		m_size = 270;
		m_siz_max = 270;
	}
	else if (m_type == 3) { //������3�Ԗڂ̓G�f��
		Hits::SetHitBox(this, m_px, m_py, 0.0f, 0.0f, ELEMENT_ENEMY, OBJ_PLANET, 1);
		m_img_nam = 28;
		m_size = 360;
		m_siz_max = 360;
	}
	else if (m_type == 4) { //������4�Ԗڂ̓G�f��
		Hits::SetHitBox(this, m_px, m_py, 0.0f, 0.0f, ELEMENT_ENEMY, OBJ_PLANET, 1);
		m_img_nam = 29;
		m_size = 150;
		m_siz_max = 150;
	}
	else  //(m_type == 5)   //�{�X�f��
	{
		Hits::SetHitBox(this, m_px, m_py, 0.0f, 0.0f, ELEMENT_ENEMY, OBJ_PLANET, 1);
		m_img_nam = 30;
		m_size = 500;
		m_siz_max = 500;
	}
}

//�A�N�V����
void CObjPlanet::Action()
{
	CObjSpecialButton* Special = (CObjSpecialButton*)Objs::GetObj(OBJ_SPECIAL);

	//���퓬�J�n�O�͐퓬����(�G�f���̍s����)�����s���Ȃ��悤�ɂ���
	if (battle_start == false)
	{
		return;
	}

	CObjFight* fit = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
	//if (fit->GetCount() != 0)		//�ΐ펞�Ԃ�0�łȂ��ꍇ
	//	/*m_siz_vec += m_siz_spd*/; //�g�����x�N�g���ɉ��Z


	CHitBox* hit = Hits::GetHitBox(this);	//CHitBox�|�C���^�擾
	if (((hit->CheckElementHit(ELEMENT_ENEMY) == true)
		|| (hit->CheckElementHit(ELEMENT_PLAYER) == true))	//���݂��������Ă��邩��
		&& (m_cnt < (2.5 * 60) * m_mov_spd)) {		//2.5�b�J�E���g���ĂȂ��ꍇ
		m_cnt++;
	}	

	//-------------------------------------------------�A�j���[�V�����A���̓���
	if (m_ani_time == 60) {	//�t���[���؂�ւ�����
		m_ani_time = 0;		//�^�C�����Z�b�g
		m_ani_frame[0]++;		//�t���[���؂�ւ�
		m_ani_frame[1]++;
		CObjPlanet* pla = (CObjPlanet*)Objs::GetObj(OBJ_PLANET);
		if(pla != nullptr)
			pla->SetEmF();
		if (m_ani_frame[0] == 4) {			//�ŏI�����t���[���ɂ���O
			m_eat_f = false;	//�H�ׂ�t���O��OFF
			m_ani_time = -1;							//���[�v���䁙
			if (m_type == 0) {		//��l���̏ꍇ
				//CObjFightClear* crer = new CObjFightClear(100,50,0,20);	//(�Z�l,����,�X�L��,�傫��)
				//Objs::InsertObj(crer, OBJ_FIGHT_CLEAR, 15);	//�N���A���
				fit->SetEnd();

				//�퓬���y��j�����������y�Đ�
				Audio::Stop(0);
				Audio::Start(1);
			}
			else {
				CObjFightOver* over = new CObjFightOver();	//�G�̏ꍇ
				Objs::InsertObj(over, OBJ_FIGHT_CLEAR, 15);	//�Q�[���I�[�o�[���

				//�퓬���y��j�����s�k���y�Đ�
				Audio::Stop(0);
				Audio::Start(2);
			}
		}
	}
	else if (m_ani_time == 30) {
		m_ani_frame[1]++;		//����ani�t���[���؂�ւ�
	}
	if (m_ani_frame[1] == 6) {
		m_ani_frame[1] = 0;
	}
	//2.5�b
	if (m_cnt < (2.5 * 60) * m_mov_spd)	//�J�E���g���I����ĂȂ��ꍇ
		if (m_type == 0)//------(�퓬��)
		{
			if(hit->CheckElementHit(ELEMENT_LINE) != true)
				m_px -= m_mov_spd;	//�����̓���
			else
			{

			}
		}
		else
		{
			if (m_type >= 1)
			{
				if(hit->CheckElementHit(ELEMENT_LINE) != true)
				m_px += m_mov_spd;	//�G���̓���
				else
				{}
			}
		}
	else { 						//�J�E���g���I������� (��~��)
		if (m_ani_time == 0) {					//time�Ń��[�v���䁙
			
			//���퓬�I��������
			//�v���C���[�f���A�G�f���̃T�C�Y(����HP�ƍő�HP)�����ꂼ��擾���A���s������s��
			//���f���T�C�Y���傫�����̏����B
			//�܂��A�T�C�Y(HP)���������̘f���摜����O�ɗ���悤�ɂ���
			if (m_type == 0) {
				CObjPlanet* ene = (CObjPlanet*)Objs::GetObj(OBJ_ENEMY);
				if (ene != nullptr)
				{
					m_get_siz = ene->GetSiz();
					m_get_max_siz = ene->GetMaxSiz();
				}	
			}
			else {
				CObjPlanet* pla = (CObjPlanet*)Objs::GetObj(OBJ_PLANET);
				if (pla != nullptr)
				{
					m_get_siz = pla->GetSiz();
					m_get_max_siz = pla->GetMaxSiz();
				}
			}
			if (m_type == 0) {
				if ((m_size / m_siz_max) >= (m_get_siz / m_get_max_siz)) 
				{
					m_eat_f = true;		//�򂤃t���O�L��
				}
			}

			else {
				if ((m_size / m_siz_max) > (m_get_siz / m_get_max_siz))
				{
					m_eat_f = true;		//�򂤃t���O�L��
					m_r = 20.0f;		//���A�C�p�x�ύX

					CObjPlanet* ene = (CObjPlanet*)Objs::GetObj(OBJ_ENEMY);
					ene->SetPrio(11);	//�I�u�W�F�N�g�̗D�揇�ʕύX���A�G�f������O�ɗ���悤�ɂ���
				}
			}
		}
	}

	if (m_eat_f == true) {	//�H�ׂ�t���O������
		m_ani_time++;		//ani_time ���Z
		if ((m_ani_frame[0] == 3) && (m_ani_time == 1)) {//�������u��
			//�����o�p�T�C�Y�ύX����
			m_size = m_siz_max;//m_size(HP)�𖞃^���ɐݒ�
			m_siz_change_range *= 1.5f;//���̌�A1.5�{������
			m_r = 0.0f;
			
			if (m_type == 0) {
				CObjPlanet* ene = (CObjPlanet*)Objs::GetObj(OBJ_ENEMY);
				ene->SetDelF();
				Audio::Start(9);

			}
			else {
				CObjPlanet* pla = (CObjPlanet*)Objs::GetObj(OBJ_PLANET);
				pla->SetDelF();
				Audio::Start(9);

			}	
		}
	}
	else
	{
		m_ani_frame[0] = 0;	//�����t���[��
		m_ani_frame[1] = 0;
	}

	if (m_ani_frame[0] == 2)		//�򂤃t���[���̈ړ�
	{

		CObjPlanet* ene = (CObjPlanet*)Objs::GetObj(OBJ_ENEMY);
		CObjPlanet* pla = (CObjPlanet*)Objs::GetObj(OBJ_PLANET);

		if (m_type == MOAI_NAM) {
			if (m_ani_time == 1)
				pla->SetEmF();
		}
		else
		{
			if (m_type == 0)
			{
				if (m_px > ene->GetX() + ene->GetScale_down_move() - pla->GetScale_down_move())		//�G��X���W��莩�f�����傫���Ȃ�ƈړ����~�߂�
				{
					m_px -= 4.0f;
				}
			}
			else
			{
				if (m_px < pla->GetX() + pla->GetScale_down_move() - ene->GetScale_down_move())		//������X���W���G�f�����������Ȃ�ƈړ����~�߂�
				{
					m_px += 4.0f;
				}
			}
		}
	}
	else if (m_eat_me == true && m_eat_f != true)
	{
		CObjPlanet* ene = (CObjPlanet*)Objs::GetObj(OBJ_ENEMY);
		CObjPlanet* pla = (CObjPlanet*)Objs::GetObj(OBJ_PLANET);
		if (ene != nullptr) {
			if (m_px > ene->GetX() + ene->GetScale_down_move() - pla->GetScale_down_move())		//�G��X���W��莩�f�����傫���Ȃ�ƈړ����~�߂�
			{
				m_px -= 2.0f;
				m_size -= 1.4f;
				if (m_py < 365)
					m_vy += 0.1f;
				else
					m_vy -= 0.1f;
				m_py += m_vy;
			}
		}
	}

	//-------------------------------------------------------------

	
	hit->SetPos(m_px + m_scale_down_move - MIN_SIZE - ((m_size / m_siz_max) * m_siz_change_range),	//HitBox�X�V
				m_py - MIN_SIZE - ((m_size / m_siz_max) * m_siz_change_range),
				(MIN_SIZE + ((m_size / m_siz_max) * m_siz_change_range)) * 2,
				(MIN_SIZE + ((m_size / m_siz_max) * m_siz_change_range)) * 2);

	//���_���[�W����
	//���v���C���[�̃_���[�W����(�~�T�C���|�b�hHIT��)
	if ((hit->CheckElementHit(ELEMENT_ENEMYPOD) == true) && (m_type == 0) && (m_size > 0))
	{							
		//���G�t���O��true�̎��͈ȉ��̃_���[�W�������΂�
		if (m_invincible_f == false)
		{
			//�|�b�h���^�����_���[�W�ʂ�Rocket.cpp����O���[�o���ϐ��ň��������Ă���
			if (hit->CheckObjNameHit(OBJ_PODP) != nullptr)//�p���[�|�b�hHIT���̏���
			{
				m_size -= g_P_Planet_damage * damage_buff[1];	//�T�C�Y(HP)����
			}
			else if (hit->CheckObjNameHit(OBJ_PODS) != nullptr)	//�X�s�[�h�|�b�hHIT���̏���
			{
				m_size -= g_P_Planet_damage * damage_buff[1];	//�T�C�Y(HP)����
			}
			else if (hit->CheckObjNameHit(OBJ_PODD) != nullptr)	//�f�B�t�F���X�|�b�hHIT���̏���
			{
				m_size -= g_P_Planet_damage * damage_buff[1];	//�T�C�Y(HP)����
			}
			else if (hit->CheckObjNameHit(OBJ_PODB) != nullptr)	//�o�����X�|�b�hHIT���̏���
			{
				m_size -= g_P_Planet_damage * damage_buff[1];	//�T�C�Y(HP)����
			}
			else if (hit->CheckObjNameHit(OBJ_ROCKET) != nullptr)//�~�T�C��HIT���̏���
			{
				m_size -= 3 * damage_buff[1];	//�T�C�Y(HP)����
			}


			m_scale_down_move = -((1 - (m_size / m_siz_max)) * m_siz_change_range);	//�k�ޕ��������Ɉړ�
		}
	}
	//���G�l�~�[�̃_���[�W����(�~�T�C���|�b�hHIT��)
	else if ((hit->CheckElementHit(ELEMENT_POD) == true) && (m_type != 0) && (m_size > 0))
	{
		//���G�t���O��true�̎��͈ȉ��̃_���[�W�������΂�
		if (m_invincible_f == false)
		{
			//�_���[�W�ʂ͕���̃��x���~10
			if (hit->CheckObjNameHit(OBJ_PODP) != nullptr)		//�p���[�|�b�hHIT���̏���
			{
				m_size -= (g_Pow_equip_Level * 10) * damage_buff[0];	//�T�C�Y(HP)����
			}
			else if (hit->CheckObjNameHit(OBJ_PODS) != nullptr)	//�X�s�[�h�|�b�hHIT���̏���
			{
				m_size -= (g_Spe_equip_Level*10) * damage_buff[0];	//�T�C�Y(HP)����
			}
			else if (hit->CheckObjNameHit(OBJ_PODD) != nullptr)	//�f�B�t�F���X�|�b�hHIT���̏���
			{
				m_size -= (g_Def_equip_Level * 10) * damage_buff[0];	//�T�C�Y(HP)����
			}
			else if (hit->CheckObjNameHit(OBJ_PODB) != nullptr)	//�o�����X�|�b�hHIT���̏���
			{
				m_size -= (g_Bal_equip_Level * 10) * damage_buff[0];	//�T�C�Y(HP)����
			}
			else if (hit->CheckObjNameHit(OBJ_ROCKET) != nullptr)//�~�T�C��HIT���̏���
			{
				m_size -= 3 * damage_buff[0];	//�T�C�Y(HP)����
			}


			m_scale_down_move = ((1 - (m_size / m_siz_max)) * m_siz_change_range);//�k�ޕ������E�Ɉړ�
		}
	}

	//�ǂ��炩�̘f����HP0�ȉ��ɒB�������A
	//�������Ԃ��]���Ă��Ă��퓬�I���������s��
	if (m_size <= 0.0f && battle_end == false)
	{
		m_size = 0.0f;		//0�����̒l�ɂȂ��Ă���ꍇ�A0�ɐݒ肷��

		if (m_type == 0)//�v���C���[�̎�
		{
			m_scale_down_move = -((1 - (m_size / m_siz_max)) * m_siz_change_range);	//�k�ޕ��������Ɉړ�
		}
		else if (m_type != 0)//�G�f���̎�
		{
			m_scale_down_move = ((1 - (m_size / m_siz_max)) * m_siz_change_range);	//�k�ޕ������E�Ɉړ�
		}

		battle_end = true;	//�퓬�I���t���O�𗧂Ă�
		fit->SetEndCount();	//�퓬���Ԃ��c��1�b�ɐݒ肷��
	}

	if (m_del_f == true) {				//�����t���O���聕����
		this->SetStatus(false);	 //�I�u�W�F�N�g�폜
		Hits::DeleteHitBox(this);//HitBox�폜
	}

	

	//���G�f���U���p�^�[��
	if (m_type >= 1 && battle_end == false)//�f�����G�̎��̂ݒe�𔭎˂��A�퓬�I�����ɒe��ł��Ȃ��悤�ɂ���B
	{
		//���G�s���p�^�[������
		if (m_time <= 0)
		{
			int Enemy_Fight_type[6][5][6] =   //�G�U���p�̔z��쐬
			{
				//m_type==0 ����͌Ăяo����Ȃ�
				{
					//1=��,2=��,3=��,4=�D�F,5=�~�T�C��,6=�X�y�V�����Z
					{ 2,3,2,2,5,0 }, //0�Ԗ�
					{ 2,2,2,4,2,0 }, //1�Ԗ�
					{ 2,5,3,2,4,0 }, //2�Ԗ�
					{ 5,2,3,2,2,0 }, //3�Ԗ�
					{ 2,1,2,5,6,0 }, //4�Ԗ�
				},
				//m_type==1
				{
					//1=��,2=��,3=��,4=�D�F,5=�~�T�C��,6=�X�y�V�����Z
					{ 2,3,2,2,5,0 }, //0�Ԗ�
					{ 1,2,2,4,2,0 }, //1�Ԗ�
					{ 2,5,3,2,4,0 }, //2�Ԗ�
					{ 5,2,3,2,2,0 }, //3�Ԗ�
					{ 2,1,2,5,6,0 }, //4�Ԗ�
				},
				//m_type==2
				{
					//1=��,2=��,3=��,4=�D�F,5=�~�T�C��,6=�X�y�V�����Z
					{ 1,3,1,1,5,0 }, //0�Ԗ�
					{ 2,1,1,4,1,0 }, //1�Ԗ�
					{ 1,5,3,1,4,0 }, //2�Ԗ�
					{ 5,1,3,1,1,0 }, //3�Ԗ�
					{ 1,2,1,5,6,0 }, //4�Ԗ�
				},
				//m_type==3
				{
					//1=��,2=��,3=��,4=�D�F,5=�~�T�C��,6=�X�y�V�����Z
					{ 4,3,4,4,5,0 }, //0�Ԗ�
					{ 2,4,4,2,4,0 }, //1�Ԗ�
					{ 4,5,3,4,2,0 }, //2�Ԗ�
					{ 5,4,3,4,4,0 }, //3�Ԗ�
					{ 4,1,4,5,6,0 }, //4�Ԗ�
				},
				//m_type==4
				{
					//1=��,2=��,3=��,4=�D�F,5=�~�T�C��,6=�X�y�V�����Z
					{ 3,2,3,3,5,0 }, //0�Ԗ�
					{ 2,3,3,4,3,0 }, //1�Ԗ�
					{ 3,5,2,3,4,0 }, //2�Ԗ�
					{ 5,3,2,3,3,0 }, //3�Ԗ�
					{ 3,1,3,5,6,0 }, //4�Ԗ�
				},
				//m_type==5
				{
					//1=��,2=��,3=��,4=�D�F,5=�~�T�C��,6=�X�y�V�����Z
					{ 1,5,2,1,1,0 }, //0�Ԗ�
					{ 2,6,3,2,2,0 }, //1�Ԗ�
					{ 3,5,4,3,3,0 }, //2�Ԗ�
					{ 4,2,5,4,4,0 }, //3�Ԗ�
					{ 5,1,1,5,5,0 }, //4�Ԗ�
				},
				/*
				�@�U���p�^�[���ǉ�����ۂ́A��̔z��̐�����ς�
				  ���̃R�����g�A�E�g������āA�o��������ނ̐������J���}���Ƃɏ��Ԃɓ���Ă��������B
				{,,,,,}, //5�Ԗ�
				{,,,,,}, //6�Ԗ�
				{,,,,,}, //7�Ԗ�
				{,,,,,}, //8�Ԗ�
				*/
			};

			m_attackf = Enemy_Fight_type[m_type][Enemy_Attack_pattern_y][Enemy_Attack_pattern_x];
			if (m_attackf == 0)//--------�z�񂪍Ō�ɍs�����Ƃ�(0�̎�)
			{
				Enemy_Attack_pattern_x = 0;//�z���ԍ��̏�Ԃɖ߂�
				//���s���p�^�[�������߂�,�����_���������Ă��鐔���Ɣz��̎�ނ𑝂₷�ƍU���p�^�[����������	
				srand(time(NULL));
				Enemy_Attack_pattern_y = rand() % 5;
				//��m_attack�ɍU���p�^�[�������鏈��
				m_attackf = Enemy_Fight_type[m_type][Enemy_Attack_pattern_y][Enemy_Attack_pattern_x];
				Enemy_Attack_pattern_x++;
			}
			else
			{
				Enemy_Attack_pattern_x++;
			}
		}

		//���G�f���U���p�^�[��
		if (m_type >= 1 && battle_end == false)//�f�����G�̎��̂ݒe�𔭎˂��A�퓬�I�����ɒe��ł��Ȃ��悤�ɂ���B
		{
			//�G�̔�������X�y�V�����Z�����߂�(0:�������@1:Explosion�@2:Fracture_Ray�@3:Immortality�@4:���~�b�g�u���C�N�@5:�X�e���C�h���^)
			switch (m_type) {
			case 1:
				Special->SetSpecial_Equip(2);
				break;
			case 2:
				Special->SetSpecial_Equip(1);
				break;
			case 3:
				Special->SetSpecial_Equip(5);
				break;
			case 4:
				Special->SetSpecial_Equip(3);
				break;
			case 5:
				Special->SetSpecial_Equip(4);
				break;
			}

			//���G�s���p�^�[������
			if (m_time <= 0)
			{
				int Enemy_Fight_line[5][6] =   //�G�U���p�̔z��쐬
				{
					//1=��,2=��,3=��,4=�D�F,5=�~�T�C��
					{ 3,2,1,1,2,0 }, //0�Ԗ�
					{ 2,3,2,3,1,0 }, //1�Ԗ�
					{ 1,2,3,2,2,0 }, //2�Ԗ�
					{ 2,1,1,2,3,0 }, //3�Ԗ�
					{ 1,3,2,2,1,0 }, //4�Ԗ�

									 /*
									 �U���p�^�[���ǉ�����ۂ́A��̔z��̐�����ς�
									 ���̃R�����g�A�E�g������āA�o��������ނ̐������J���}���Ƃɏ��Ԃɓ���Ă��������B
									 {,,,,,}, //5�Ԗ�
									 {,,,,,}, //6�Ԗ�
									 {,,,,,}, //7�Ԗ�
									 {,,,,,}, //8�Ԗ�
									 */
				};

				m_get_line = Enemy_Fight_line[Enemy_Line_pattern_y][Enemy_Line_pattern_x];
				if (m_get_line == 0)//--------�z�񂪍Ō�ɍs�����Ƃ�(0�̎�)
				{
					Enemy_Line_pattern_x = 0;//�z���ԍ��̏�Ԃɖ߂�
											 //���s���p�^�[�������߂�,�����_���������Ă��鐔���Ɣz��̎�ނ𑝂₷�ƍU���p�^�[����������	
					srand(time(NULL));
					Enemy_Line_pattern_x = rand() % 5;
					//��m_attack�ɍU���p�^�[�������鏈��
					m_get_line = Enemy_Fight_line[Enemy_Line_pattern_y][Enemy_Line_pattern_x];
					Enemy_Line_pattern_x++;
				}
				else
				{
					Enemy_Line_pattern_x++;
				}
			}
		}

		//���~�T�C���|�b�h�쐬X�ʒu��ݒ�
		if (m_attackf == 1 && m_time <= 0 && m_type != 0)//�ԐF�|�b�h
		{
			CObjRocket* M = new CObjRocket(m_px + (140.0f + m_scale_down_move + ((m_size / m_siz_max) * m_siz_change_range)), 225, m_type,1);//�I�u�W�F�N�g�쐬
			Objs::InsertObj(M, OBJ_ROCKET, 20);		//�I�u�W�F�N�g�o�^


			switch (m_type)
			{

			case 1:
				m_time = ONE_DELAY * m_enemy_recast_buff;
				break;
			case 2:
				m_time = SEC_DELAY * m_enemy_recast_buff;
				break;
			case 3:
				m_time = THI_DELAY * m_enemy_recast_buff;
				break;
			case 4:
				m_time = FOU_DELAY * m_enemy_recast_buff;
				break;
			case 5:
				m_time = FIV_DELAY * m_enemy_recast_buff;
				break;
			}
		}
		else if (m_attackf == 2 && m_time <= 0 && m_type != 0)//�F�|�b�h
		{
			CObjRocket* M = new CObjRocket(m_px + (140.0f + m_scale_down_move + ((m_size / m_siz_max) * m_siz_change_range)), 225, m_type,2);//�I�u�W�F�N�g�쐬
			Objs::InsertObj(M, OBJ_ROCKET, 20);		//�I�u�W�F�N�g�o�^
			/*m_time = 100 * m_enemy_recast_buff;*/
			switch (m_type)//�G�̎�ނɂ���čU���̃��L���X�g�^�C���ύX
			{

			case 1:
				m_time = ONE_DELAY * m_enemy_recast_buff;
				break;
			case 2:
				m_time = SEC_DELAY * m_enemy_recast_buff;
				break;
			case 3:
				m_time = THI_DELAY * m_enemy_recast_buff;
				break;
			case 4:
				m_time = FOU_DELAY * m_enemy_recast_buff;
				break;
			case 5:
				m_time = FIV_DELAY * m_enemy_recast_buff;
				break;
			}
		}
		else if (m_attackf == 3 && m_time <= 0 && m_type != 0)//�ΐF�|�b�h
		{
			CObjRocket* M = new CObjRocket(m_px + (140.0f + m_scale_down_move + ((m_size / m_siz_max) * m_siz_change_range)), 225, m_type,3);//�I�u�W�F�N�g�쐬
			Objs::InsertObj(M, OBJ_ROCKET, 20);		//�I�u�W�F�N�g�o�^
		/*	m_time = 100 * m_enemy_recast_buff;*/
			switch (m_type)
			{

			case 1:
				m_time = ONE_DELAY * m_enemy_recast_buff;
				break;
			case 2:
				m_time = SEC_DELAY * m_enemy_recast_buff;
				break;
			case 3:
				m_time = THI_DELAY * m_enemy_recast_buff;
				break;
			case 4:
				m_time = FOU_DELAY * m_enemy_recast_buff;
				break;
			case 5:
				m_time = FIV_DELAY * m_enemy_recast_buff;
				break;
			}
		}
		else if (m_attackf == 4 && m_time <= 0 && m_type != 0)//�D�F�|�b�h(���͉��F)
		{
			CObjRocket* M = new CObjRocket(m_px + (140.0f + m_scale_down_move + ((m_size / m_siz_max) * m_siz_change_range)), 225, m_type,4);//�I�u�W�F�N�g�쐬
			Objs::InsertObj(M, OBJ_ROCKET, 20);		//�I�u�W�F�N�g�o�^
			//m_time = 100 * m_enemy_recast_buff;
			switch (m_type)
			{

			case 1:
				m_time = ONE_DELAY * m_enemy_recast_buff;
				break;
			case 2:
				m_time = SEC_DELAY * m_enemy_recast_buff;
				break;
			case 3:
				m_time = THI_DELAY * m_enemy_recast_buff;
				break;
			case 4:
				m_time = FOU_DELAY * m_enemy_recast_buff;
				break;
			case 5:
				m_time = FIV_DELAY * m_enemy_recast_buff;
				break;
			}
		}
		else if (m_attackf == 5 && m_time <= 0 && m_type != 0)//�~�T�C��
		{
			CObjRocket* M = new CObjRocket(m_px + (140.0f + m_scale_down_move + ((m_size / m_siz_max) * m_siz_change_range)), 225, m_type, 5);//�I�u�W�F�N�g�쐬
			Objs::InsertObj(M, OBJ_ROCKET, 20);		//�I�u�W�F�N�g�o�^
			//m_time = 100 * m_enemy_recast_buff;
			switch (m_type)
			{

			case 1:
				m_time = ONE_DELAY * m_enemy_recast_buff;
				break;
			case 2:
				m_time = SEC_DELAY * m_enemy_recast_buff;
				break;
			case 3:
				m_time = THI_DELAY * m_enemy_recast_buff;
				break;
			case 4:
				m_time = FOU_DELAY * m_enemy_recast_buff;
				break;
			case 5:
				m_time = FIV_DELAY * m_enemy_recast_buff;
				break;
			}

		}
		else if (m_attackf == 6 && m_time <= 0 && m_type != 0)//�X�y�V�����Z
		{
			//�G���X�y�V�����Z���g�p��(true)�ł���ꍇ�A
			//���L���X�g�^�C�������ɖ߂����A�ēx�s���p�^�[�����߂��s��
			//���g�p(false)�ł���΁A�ȉ��̏������s��
			if (Special->GetEnemy_Used_Special() == false)
			{
				Special->SetSpecial_Start();	//�X�y�V�����Z�𔭓�������
				m_time = 100 * m_enemy_recast_buff;
			}
		}

		m_time--;
	}

	CObjFight* obj = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
	m_cntf = obj->GetCount();	//CObjFight�̃J�E���g���������Ă���

	if (m_cntf <= 0)			//�J�E���g����0�ȉ��ɂȂ�����
	{
		if (m_cnt < m_mov_spd)	//�f�����m���d�Ȃ��Ă��Ȃ��Ƃ�
		{
			if (m_type == 0)
				m_px -= 1.0f;
				
			else
				m_px += 1.0f;
		}
	}

	if (battle_end == false)	//�o�g���I�����A�������Ȃ�
	{
		if (m_size >= 60.0f) {
			m_subsize = m_size;
			if (m_subsize >= MIN_SIZE)
				m_subsize = MIN_SIZE;
		}
	}
}

//�h���[
void CObjPlanet::Draw()
{
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };//�f���摜&HP�Q�[�W(���ݒl)�p
	float g[4] = { 0.0f,1.0f, 0.0f, 1.0f };//��HP�Q�[�W(���ݒl)�p
	float r[4] = { 1.0f,0.0f, 0.0f, 1.0f };//��HP�Q�[�W(���ݒl)�p
	float b[4] = { 0.0f,0.0f, 0.0f, 1.0f };//HP�Q�[�W(�ő�l)�p
	RECT_F src;
	RECT_F dst;
	//�؂���ʒu
	src.m_top   =  0.0f;
	src.m_left  = m_ani[m_ani_frame[0]] * 448.0f;
	src.m_right = m_ani[m_ani_frame[0]] * 448.0f + 448.0f;
	src.m_bottom= 448.0f;
	//�\���ʒu
	dst.m_top	= m_py - MIN_SIZE - ((m_size / m_siz_max) * m_siz_change_range);
	dst.m_left	= m_px - MIN_SIZE - ((m_size / m_siz_max) * m_siz_change_range) + m_scale_down_move;
	dst.m_right = m_px + MIN_SIZE + ((m_size / m_siz_max) * m_siz_change_range) + m_scale_down_move;
	dst.m_bottom= m_py + MIN_SIZE + ((m_size / m_siz_max) * m_siz_change_range);

	
	if (m_type != 0)//�G�̂ݐ؂���T�C�Y�ύX
	{
		src.m_top	= 0.0f;
		src.m_left	= m_ani[m_ani_frame[0]] * 300.0f;
		src.m_right	= m_ani[m_ani_frame[0]] * 300.0f + 300.0f;
		src.m_bottom= 300.0f;
	}

	if (m_type == MOAI_NAM)//���A�C��,m_mani[ani_frame[1]]���g��
	{
		src.m_top   = 0.0f;
		src.m_left  = m_mani[m_ani_frame[1]] * 300.0f;
		src.m_right = m_mani[m_ani_frame[1]] * 300.0f + 300.0f;
		src.m_bottom= 300.0f;
		Draw::Draw(m_img_nam, &src, &dst, c, m_r);
	}
	else {
		//m_img_nam�̐��ŁA�o�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
		Draw::Draw(m_img_nam, &src, &dst, c, 0.0f);
	}




	//��HP�Q�[�W�\��(�퓬�I����͕\�����Ȃ�)
	if (battle_end == false)
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 128.0f;
		src.m_bottom = 10.0f;

		dst.m_top	= m_py + MIN_SIZE + ((m_size / m_siz_max) * m_siz_change_range) - 5.0f;
		dst.m_left	= m_px - MIN_SIZE + m_scale_down_move;
		dst.m_bottom= m_py + MIN_SIZE + ((m_size / m_siz_max) * m_siz_change_range);

		//���ő�l�\��
		dst.m_right = m_px - MIN_SIZE + m_scale_down_move + (MIN_SIZE * 2);
		Draw::Draw(32, &src, &dst, b, 0.0f);

		//�����ݒl�\��		
		dst.m_right = m_px - MIN_SIZE + m_scale_down_move + ((MIN_SIZE * 2) * (m_size / m_siz_max));

		
		if(m_size/m_siz_max >= 0.20f)				//HP��20%�ȏ�̎�HP�o�[��ΐF�ɂ���
			Draw::Draw(32, &src, &dst, g, 0.0f);
		else {										//HP��20%�ȉ��̎������o����HP�o�[��Ԃ�����
			Draw::Draw(32, &src, &dst, r, 0.0f);

			//���퓬�������Ă���Ƃ�(�~�܂��Ă��Ȃ��Ƃ�)�㉺����"��"��\��
			if (battle_start == true) {
				//�p�x���Z
				m_r2 += 10.0f;

				//360���ŏ����l�ɖ߂�
				if (m_r2 > 360.0f)
					m_r2 = 0.0f;

				//�ړ�����
				m_sweat_vy = sin(3.14f / 90 * m_r2);

				//���x�t����B
				m_sweat_vy *= 10.0f;
			}

			//����\��
			src.m_top	= 0.0f;
			src.m_left	= 0.0f;
			src.m_right = 128.0f;
			src.m_bottom= 128.0f;

			dst.m_top	= m_py - ((m_subsize / m_siz_max) * m_siz_change_range) + m_sweat_vy - (m_subsize * 1);
			dst.m_left	= m_px - ((m_subsize / m_siz_max) * m_siz_change_range) + m_scale_down_move + (m_subsize * 1);
			dst.m_right = m_px + ((m_subsize / m_siz_max) * m_siz_change_range) + m_scale_down_move + (m_subsize * 1);
			dst.m_bottom= m_py + ((m_subsize / m_siz_max) * m_siz_change_range) + m_sweat_vy - (m_subsize * 1);

			if (m_type != 0)//�f�����v���C���[�ȊO�̎��A���̈ʒu������ɕ\�����Ĕ��]������
			{
				dst.m_left = m_px + ((m_subsize / m_siz_max) * m_siz_change_range) + m_scale_down_move + (m_subsize * 1) * -1;
				dst.m_right= m_px - ((m_subsize / m_siz_max) * m_siz_change_range) + m_scale_down_move + (m_subsize * 1) * -1;
			}
			
			//��
			Draw::Draw(34, &src, &dst, c, 1.0f);
		}
	}

}
