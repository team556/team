//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjPlanet.h"

#include <time.h>

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjPlanet::CObjPlanet(float x, float y, float hp, int type, float siz)
{
	//�쐬���ɓn���ꂽ�l���A�e�X�e�[�^�X�ɑ��
	m_px = x;
	m_py = y;
	m_hp = hp;
	m_type = type;
	m_get_siz = siz;
}

//�C�j�V�����C�Y
void CObjPlanet::Init()
{
	//�e�X�e�[�^�X������
	m_size	 = 50.0f;//�T�C�Y
	m_siz_max= 50.0f;
	m_siz_vec=  0.0f;

	m_cnt = 0;		//�J�E���g

	m_get_hp = 0;	//�擾HP

	m_invincible_f = false;
	m_damage_buff = 1.0f;
	m_enemy_recast_buff = 1.0f;

	m_time = 0; //�^�C���J�E���g������
	m_attackf = 0;

	Enemy_Attack_pattern_x = 0;

	srand(time(NULL));
	Enemy_Attack_pattern_y = rand() % 5;//�����s���p�^�[���������_���Ō��߂�(���̏����Ȃ��Ə����s���p�^�[�����K��0�̂��̂ɂȂ�)

	CObjFight* fit = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
	m_mov_spd = 0.093f* 30 / (fit->GetCount() / 70);//�������x
	///*m_siz_spd*/ = 0.07f * 30 / (fit->GetCount() / 40);//�g�呬�x

	if (m_type == 0) {
		m_px += (fit->GetCount() / 30);
		m_img_nam = 3;
	}
	else if (m_type == 1) {
		m_px -= (fit->GetCount() / 30);
		m_img_nam = 33;
	}
	else if (m_type == 2) {
		m_px -= (fit->GetCount() / 30);
		m_img_nam = 3;
	}
	else if (m_type == 3) {
		m_px -= (fit->GetCount() / 30);
		m_img_nam = 4;
	}

	m_ani[0] = 0;//�A�j���[�V�����f�[�^�̏�����
	m_ani[1] = 1;
	m_ani[2] = 2;
	m_ani[3] = 1;
	m_ani_frame = 0;
	m_ani_time = 0;
	m_cntf = 0;
	m_eat_f = false;	//�򂤃t���O(true = ��)
	m_eat_spd = fit->GetCount();
	m_del_f = false;	//�����t���O(true = ����)
	
	//�����蔻��pHitBox���쐬
	if(m_type == 0)
		Hits::SetHitBox(this, m_px, m_py, m_size, m_size, ELEMENT_PLAYER, OBJ_PLANET, 1);
	else
		Hits::SetHitBox(this, m_px, m_py, m_size, m_size, ELEMENT_ENEMY, OBJ_PLANET, 1);
}

//�A�N�V����
void CObjPlanet::Action()
{
	//���퓬�J�n�O�͐퓬����(�G�f���̍s����)�����s���Ȃ��悤�ɂ���
	if (battle_start == false)
	{
		return;
	}

	CObjFight* fit = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
	if (fit->GetCount() != 0)		//�ΐ펞�Ԃ�0�łȂ��ꍇ
		/*m_siz_vec += m_siz_spd*/; //�g�����x�N�g���ɉ��Z


	CHitBox* hit = Hits::GetHitBox(this);	//CHitBox�|�C���^�擾
	if (((hit->CheckElementHit(ELEMENT_ENEMY) == true)
		|| (hit->CheckElementHit(ELEMENT_PLAYER) == true))	//���݂��������Ă��邩��
		&& (m_cnt < (2.5 * 60) * m_mov_spd)) {		//2.5�b�J�E���g���ĂȂ��ꍇ
		m_cnt++;
	}	

	//-------------------------------------------------�A�j���[�V�����A���̓���
	if (m_ani_time == 60) {	//�t���[���؂�ւ�����
		m_ani_time = 0;		//�^�C�����Z�b�g
		m_ani_frame++;		//�t���[���؂�ւ�
		if (m_ani_frame == 4) {			//�ŏI�����t���[���ɂ���O
			m_eat_f = false;	//�H�ׂ�t���O��OFF
			m_ani_time = -1;							//���[�v���䁙
			if (m_type == 0) {
				CObjFightClear* crer = new CObjFightClear();	//��l���̏ꍇ
				Objs::InsertObj(crer, OBJ_FIGHT_CLEAR, 15);	//�N���A���
			}
			else {
				CObjFightOver* over = new CObjFightOver();	//�G�̏ꍇ
				Objs::InsertObj(over, OBJ_FIGHT_CLEAR, 15);	//�Q�[���I�[�o�[���
			}
		}
	}
				//2.5�b
	if (m_cnt < (2.5 * 60) * m_mov_spd)	//�J�E���g���I����ĂȂ��ꍇ
		if (m_type == 0)				//(�퓬��)
			m_px -= m_mov_spd;	//�����̓���
		else
			m_px += m_mov_spd;	//�G���̓���
	else { 						//�J�E���g���I������� (��~��)
		if (m_ani_time == 0) {					//time�Ń��[�v���䁙
			
			//���퓬�I��������
			//�v���C���[�f���A�G�f����HP�����ꂼ��擾���A���s������s��
			//�܂��AHP���������̘f���摜����O�ɗ���悤�ɂ���
			if (m_type == 0) {
				CObjPlanet* ene = (CObjPlanet*)Objs::GetObj(OBJ_ENEMY);
				if(ene != nullptr)
					m_get_hp = ene->GetHp();
			}
			else {
				CObjPlanet* pla = (CObjPlanet*)Objs::GetObj(OBJ_PLANET);
				if (pla != nullptr)
					m_get_hp = pla->GetHp();
			}
			if (m_type == 0) {
				if (m_hp >= m_get_hp) {
					m_eat_f = true;		//�򂤃t���O�L��
				}
			}
			else {
				if (m_hp > m_get_hp) {
					m_eat_f = true;		//�򂤃t���O�L��

					CObjPlanet* ene = (CObjPlanet*)Objs::GetObj(OBJ_ENEMY);
					ene->SetPrio(11);	//�I�u�W�F�N�g�̗D�揇�ʕύX���A�G�f������O�ɗ���悤�ɂ���
				}
			}
		}
	}

	if (m_eat_f == true) {	//�H�ׂ�t���O������
		m_ani_time++;		//ani_time ���Z
		if ((m_ani_frame == 3) && (m_ani_time == 1)) {//�������u��
			m_size = m_size*1.5f;					//�T�C�Y�ύX(1.5�{)
			if (m_type == 0) {
				CObjPlanet* ene = (CObjPlanet*)Objs::GetObj(OBJ_ENEMY);
				ene->SetDelF();
			}
			else {
				CObjPlanet* pla = (CObjPlanet*)Objs::GetObj(OBJ_PLANET);
				pla->SetDelF();
			}	
		}
	}
	else
		m_ani_frame = 0;	//�����t���[��

	if (m_ani_frame == 2)		//�򂤃t���[���̈ړ�
	{
		if (m_type == 0)
		{
			CObjPlanet* ene = (CObjPlanet*)Objs::GetObj(OBJ_ENEMY);
			if (m_px > ene->GetX())		//�G��X���W��莩�f�����傫���Ȃ�ƈړ����~�߂�
				m_px -= 4.0f;
		}
		else
		{
			CObjPlanet* pla = (CObjPlanet*)Objs::GetObj(OBJ_PLANET);
			if (m_px < pla->GetX())		//������X���W���G�f�����������Ȃ�ƈړ����~�߂�
				m_px += 4.0f;
		}
	}

	//-------------------------------------------------------------

	
	hit->SetPos(m_px - m_siz_vec - m_size * 2,	//HitBox�X�V
				m_py - m_siz_vec - m_size * 2,		
				2 * m_siz_vec + m_size * 4,
				2 * m_siz_vec + m_size * 4);

	//���_���[�W����
	//���v���C���[�̃_���[�W����(�~�T�C���|�b�hHIT��)
	if ((hit->CheckElementHit(ELEMENT_E_MIS) == true) && (m_type == 0) && (m_hp > 0))
	{							
		//���G�t���O��true�̎��͈ȉ��̃_���[�W�������΂�
		if (m_invincible_f == false)
		{
			m_hp -= 1 * m_damage_buff;//HP-1
			m_size -= m_size / 20;	//�T�C�Y����
		}
	}
	//���G�l�~�[�̃_���[�W����(�~�T�C���|�b�hHIT��)
	else if ((hit->CheckElementHit(ELEMENT_P_MIS) == true) && (m_type != 0) && (m_hp > 0))
	{
		//���G�t���O��true�̎��͈ȉ��̃_���[�W�������΂�
		if (m_invincible_f == false)
		{
			m_hp -= 1 * m_damage_buff;//HP-1
			m_size -= m_size / 20;	//�T�C�Y����
		}
	}

	if (m_del_f == true) {				//�����t���O���聕����
		this->SetStatus(false);	 //�I�u�W�F�N�g�폜
		Hits::DeleteHitBox(this);//HitBox�폜
	}

	//���G�f���U���p�^�[��
	if (m_type == 1 && battle_end == false)//�f�����G�̎��̂ݒe�𔭎˂��A�퓬�I�����ɒe��ł��Ȃ��悤�ɂ���B
	{
		//���G�s���p�^�[������
		if (m_time <= 0)
		{
			int Enemy_Fight_type[5][6] =   //�G�U���p�̔z��쐬
			{
				//1=��,2=��,3=��,4=�D�F,5=�~�T�C��
				{ 1,1,2,1,1,0 }, //0�Ԗ�
				{ 2,2,3,2,2,0 }, //1�Ԗ�
				{ 3,3,4,3,3,0 }, //2�Ԗ�
				{ 4,4,5,4,4,0 }, //3�Ԗ�
				{ 5,5,1,5,5,0 }, //4�Ԗ�
				/*
				�@�U���p�^�[���ǉ�����ۂ́A��̔z��̐�����ς�
				  ���̃R�����g�A�E�g������āA�o��������ނ̐������J���}���Ƃɏ��Ԃɓ���Ă��������B
				{,,,,,}, //5�Ԗ�
				{,,,,,}, //6�Ԗ�
				{,,,,,}, //7�Ԗ�
				{,,,,,}, //8�Ԗ�
				*/
			};

			m_attackf = Enemy_Fight_type[Enemy_Attack_pattern_y][Enemy_Attack_pattern_x];
			if (m_attackf == 0)//--------�z�񂪍Ō�ɍs�����Ƃ�(0�̎�)
			{
				Enemy_Attack_pattern_x = 0;//�z���ԍ��̏�Ԃɖ߂�
				//���s���p�^�[�������߂�,�����_���������Ă��鐔���Ɣz��̎�ނ𑝂₷�ƍU���p�^�[����������	
				srand(time(NULL));
				Enemy_Attack_pattern_x = rand() % 5;
				//��m_attack�ɍU���p�^�[�������鏈��
				m_attackf = Enemy_Fight_type[Enemy_Attack_pattern_y][Enemy_Attack_pattern_x];
				Enemy_Attack_pattern_x++;
			}
			else
			{
				Enemy_Attack_pattern_x++;
			}
		}


		//���~�T�C���|�b�h�쐬X�ʒu��ݒ�
		CObjFight* obj = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
		m_create_x = -(obj->GetCount() / 10 + 100);
		
		if (m_attackf == 1 && m_time <= 0)//�ԐF�|�b�h
		{
			CObjRocket* M = new CObjRocket(575 + m_create_x, 200, false,1);//�I�u�W�F�N�g�쐬
			Objs::InsertObj(M, OBJ_Rocket, 20);		//�I�u�W�F�N�g�o�^
			m_time = 100 * m_enemy_recast_buff;
		}
		else if (m_attackf == 2 && m_time <= 0)//�F�|�b�h
		{
			CObjRocket* M = new CObjRocket(575 + m_create_x, 200, false,2);//�I�u�W�F�N�g�쐬
			Objs::InsertObj(M, OBJ_Rocket, 20);		//�I�u�W�F�N�g�o�^
			m_time = 100 * m_enemy_recast_buff;
		}
		else if (m_attackf == 3 && m_time <= 0)//�ΐF�|�b�h
		{
			CObjRocket* M = new CObjRocket(575 + m_create_x, 200, false,3);//�I�u�W�F�N�g�쐬
			Objs::InsertObj(M, OBJ_Rocket, 20);		//�I�u�W�F�N�g�o�^
			m_time = 100 * m_enemy_recast_buff;
		}
		else if (m_attackf == 4 && m_time <= 0)//�D�F�|�b�h(���͉��F)
		{
			CObjRocket* M = new CObjRocket(575 + m_create_x, 200, false,4);//�I�u�W�F�N�g�쐬
			Objs::InsertObj(M, OBJ_Rocket, 20);		//�I�u�W�F�N�g�o�^
			m_time = 100 * m_enemy_recast_buff;
		}
		else if (m_attackf == 5 && m_time <= 0)//�~�T�C��
		{
			CObjRocket* M = new CObjRocket(575 + m_create_x, 200, false, 5);//�I�u�W�F�N�g�쐬
			Objs::InsertObj(M, OBJ_Rocket, 20);		//�I�u�W�F�N�g�o�^
			m_time = 100 * m_enemy_recast_buff;
		}
		else if (m_attackf == 6 && m_time <= 0)//�X�y�V�����Z
		{
			CObjSpecialButton* Special = (CObjSpecialButton*)Objs::GetObj(OBJ_SPECIAL);

			//�G���X�y�V�����Z���g�p��(true)�ł���ꍇ�A
			//���L���X�g�^�C�������ɖ߂����A�ēx�s���p�^�[�����߂��s��
			//���g�p(false)�ł���΁A�ȉ��̏������s��
			if (Special->GetEnemy_Used_Special() == false)
			{
				Special->SetSpecial_Equip(1);	//�G�̔�������X�y�V�����Z�����߂�(0:�������@1:�G�ɑ�_���[�W�@2:���E���@3:��莞�Ԗ��G�@4:���Y�������A�b�v�@5:�Z���̎m�C���A�b�v)
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

}

//�h���[
void CObjPlanet::Draw()
{
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	RECT_F src;
	RECT_F dst;
	//�؂���ʒu
	src.m_top   =  0.0f;
	src.m_left  = m_ani[m_ani_frame] * 64.0f;
	src.m_right = m_ani[m_ani_frame] * 64.0f + 64.0f;
	src.m_bottom= 64.0f;
	//�\���ʒu
	if(m_get_siz == 0){
		//dst.m_top   = m_py - m_siz_vec - m_size;//300
		//dst.m_left  = m_px - m_siz_vec - m_size;//800
		//dst.m_right = m_px + m_siz_vec + m_size;
		//dst.m_bottom= m_py + m_siz_vec + m_size;

		dst.m_top = m_py - m_size * 2;//300
		dst.m_left = m_px -m_size * 2;//800
		dst.m_right = m_px +m_size * 2;
		dst.m_bottom = m_py +m_size * 2;
	}
	else {
		dst.m_top   = m_py;//300
		dst.m_left  = m_px;//800
		dst.m_right = m_px + (m_get_siz * 2);
		dst.m_bottom= m_py + (m_get_siz * 2);
	}

	//0�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
	Draw::Draw(m_img_nam, &src, &dst, c, 0.0f);
}
