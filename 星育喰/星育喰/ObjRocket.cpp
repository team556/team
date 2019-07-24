//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"


#include "GameHead.h"
#include "UtilityModule.h"
#include "ObjRocket.h"

#include <time.h>

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjRocket::CObjRocket(float x, float y, int type,int n)
{
	m_x = x;
	m_y = y;
	m_type = type;
	ButtonU = n;
}

//�C�j�V�����C�Y
void CObjRocket::Init()
{
	if (ButtonU != 5) {
		
	}

	//�������p�^�[���f�����b�g����
	//���v���C���[�̏���
	if (m_type == 0)
	{
		CObjFight* obj = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
		
		//���˂��ꂽ���[���̃����p�^�[���f�����b�g�l���󂯎��
		m_One_pat_dem = Pla_One_pat_dem[obj->GetLine()];

		//���˂��ꂽ���[���ł̃����p�^�[���f�����b�g�l������������(����ȍ~�̃~�T�C���|�b�h�̍U���͂�����������)
		//���Œ�l��0.5�̏ꍇ�A���s����Ȃ��B
		if (Pla_One_pat_dem[obj->GetLine()] < 1.5f)
		{
			Pla_One_pat_dem[obj->GetLine()] += 0.1f;
		}

		//���˂��ꂽ���[���ȊO�̃��[���̃����p�^�[���f�����b�g�l���񕜂�����(����ȍ~�̃~�T�C���|�b�h�̍U���͂����̍U���͂ɋ߂Â�)
		//���ō��l��1.0�̏ꍇ�A���s����Ȃ��B
		for (int i = 0; i < 3; i++)
		{
			if (Pla_One_pat_dem[i] > 1.0f && obj->GetLine() != i)
			{
				Pla_One_pat_dem[i] -= 0.1f;
			}
		}
	}
	//���G�l�~�[�̏���
	else
	{
		CObjPlanet* ene = (CObjPlanet*)Objs::GetObj(OBJ_ENEMY);

		//���˂��ꂽ���[���̃����p�^�[���f�����b�g�l���󂯎��
		m_One_pat_dem = Ene_One_pat_dem[ene->GetLine() - 1];

		//���˂��ꂽ���[���ł̃����p�^�[���f�����b�g�l������������(����ȍ~�̃~�T�C���|�b�h�̍U���͂�����������)
		//���Œ�l��0.5�̏ꍇ�A���s����Ȃ��B
		if (Ene_One_pat_dem[ene->GetLine() - 1] < 1.5f)
		{
			Ene_One_pat_dem[ene->GetLine() - 1] += 0.1f;
		}

		//���˂��ꂽ���[���ȊO�̃��[���̃����p�^�[���f�����b�g�l���񕜂�����(����ȍ~�̃~�T�C���|�b�h�̍U���͂����̍U���͂ɋ߂Â�)
		//���ō��l��1.0�̏ꍇ�A���s����Ȃ��B
		for (int i = 0; i < 3; i++)
		{
			if (Ene_One_pat_dem[i] > 1.0f && ene->GetLine() - 1 != i)
			{
				Ene_One_pat_dem[i] -= 0.1f;
			}
		}
	}

	Enemy_Line_pattern_x = 0;

	srand(time(NULL));
	Enemy_Line_pattern_y = rand() % 5;//�����s���p�^�[���������_���Ō��߂�(���̏����Ȃ��Ə����s���p�^�[�����K��0�̂��̂ɂȂ�)

	CObjPlanet* pla = (CObjPlanet*)Objs::GetObj(OBJ_PLANET);

	if (m_type == 0) {
		CObjFight* obj = (CObjFight*)Objs::GetObj(OBJ_FIGHT);

		if (obj != nullptr) {					//��񂪎擾�o���Ă�����
			m_get_line = obj->GetLine();		//���C���i���o�[���擾
			if (m_get_line == 1) { m_y = 310; }	//�擾�i���o�[�ō����ύX
			else if (m_get_line == 2) { m_y = 420; }

			//m_get_cnt = obj->GetCount();		//�J�E���g���擾
			////m_x += obj->GetCount() / 10;
			//m_x += 0.0f;
			//m_mov_spd = 1.0f / pla->GetX();
		}
	}
	else if (m_type != 0 && battle_end == false)
	{
		CObjPlanet* ene = (CObjPlanet*)Objs::GetObj(OBJ_ENEMY);
		m_get_line = ene->GetLine();
	}

	CObjFight* obj = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
	if (m_get_line == 1) { m_y = 310; }	//�擾�i���o�[�ō����ύX
	else if (m_get_line == 2) { m_y = 420; }

	m_get_cnt = obj->GetCount();		//�J�E���g���擾
	m_mov_spd = 1.0f / pla->GetX();

	m_size = 50.0f;	//�T�C�Y
	
	m_atk_cnt = 0;
	m_atk_cnt_max = 20;//(1/3�b)

	m_Enemy_Pod_Level = g_Stage_progress;	//����A���݂̃X�e�[�W�i�s�x�ɍ��킹�ēG�̃|�b�h���x����ݒ肵�Ă���
	m_pod_nam = (g_Power_num + g_Defense_num + g_Speed_num + g_Balance_num) / 1200;//�e�|�b�h�̏Z������

	m_vx = 0.0f;	//�x�N�g��
	m_vy = 0.0f;
	m_schange = 3.0f;
	m_mov = 0;
	
	m_r = 0.0f;		//�p�x

	if (m_type == 0)
		ButtonUP = ButtonU;
	else
		ButtonUE = ButtonU;

	m_pnam = p_pnam;//�|�b�h��r�o������
	m_enam = e_pnam;

	//�����蔻��pHitBox�쐬
	if (m_type == 0) 
	{
		m_x += 100;
		if (ButtonUP == 1)
		{
			switch (p_pnam) {
			case 0:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD, OBJ_PODP, 1); break;
			case 1:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD1, OBJ_PODP, 1); break;
			case 2:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD2, OBJ_PODP, 1); break;
			case 3:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD3, OBJ_PODP, 1); break;
			case 4:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD4, OBJ_PODP, 1); break;
			case 5:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD5, OBJ_PODP, 1); break;
			case 6:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD6, OBJ_PODP, 1); break;
			case 7:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD7, OBJ_PODP, 1); break;
			case 8:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD8, OBJ_PODP, 1); break;
			case 9:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD9, OBJ_PODP, 1); break;
			}
		}
		else if (ButtonUP == 2)
		{
			switch (p_pnam) {
			case 0:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD, OBJ_PODD, 1); break;
			case 1:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD1, OBJ_PODD, 1); break;
			case 2:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD2, OBJ_PODD, 1); break;
			case 3:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD3, OBJ_PODD, 1); break;
			case 4:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD4, OBJ_PODD, 1); break;
			case 5:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD5, OBJ_PODP, 1); break;
			case 6:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD6, OBJ_PODP, 1); break;
			case 7:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD7, OBJ_PODP, 1); break;
			case 8:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD8, OBJ_PODP, 1); break;
			case 9:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD9, OBJ_PODP, 1); break;
			}
		}
		else if (ButtonUP == 3)
		{
			switch (p_pnam) {
			case 0:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD, OBJ_PODS, 1); break;
			case 1:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD1, OBJ_PODS, 1); break;
			case 2:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD2, OBJ_PODS, 1); break;
			case 3:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD3, OBJ_PODS, 1); break;
			case 4:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD4, OBJ_PODS, 1); break;
			case 5:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD5, OBJ_PODP, 1); break;
			case 6:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD6, OBJ_PODP, 1); break;
			case 7:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD7, OBJ_PODP, 1); break;
			case 8:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD8, OBJ_PODP, 1); break;
			case 9:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD9, OBJ_PODP, 1); break;
			}
		}
		else if (ButtonUP == 4)
		{
			switch (p_pnam) {
			case 0:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD, OBJ_PODB, 1); break;
			case 1:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD1, OBJ_PODB, 1); break;
			case 2:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD2, OBJ_PODB, 1); break;
			case 3:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD3, OBJ_PODB, 1); break;
			case 4:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD4, OBJ_PODB, 1); break;
			case 5:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD5, OBJ_PODP, 1); break;
			case 6:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD6, OBJ_PODP, 1); break;
			case 7:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD7, OBJ_PODP, 1); break;
			case 8:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD8, OBJ_PODP, 1); break;
			case 9:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD9, OBJ_PODP, 1); break;
			}
		}
		else if (ButtonUP == 5)
		{
			Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD, OBJ_ROCKET, 1);
		}
		if (ButtonUP != 5) {
			CObjRktHit* RH = new CObjRktHit(m_x, m_y, m_type);	//�q�b�g�{�b�N�X�pObj�쐬
			Objs::InsertObj(RH, OBJ_RKTHIT, 15);				//�I�u�W�F�N�g�o�^
			p_pnam++;
		}
		if (p_pnam == 9)
			p_pnam = 0;
	}
	else if(m_type != 0)
	{
		m_x -= 100;
		if (ButtonUE == 1)
		{
			Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_ENEMYPOD, OBJ_PODP, 1);
			CObjRktHit* RH = new CObjRktHit(m_x, m_y, m_type);	//�q�b�g�{�b�N�X�pObj�쐬
			Objs::InsertObj(RH, OBJ_RKTHIT, 15);				//�I�u�W�F�N�g�o�^
		}
		else if (ButtonUE == 2)
		{
			Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_ENEMYPOD, OBJ_PODD, 1);
			CObjRktHit* RH = new CObjRktHit(m_x, m_y, m_type);	//�q�b�g�{�b�N�X�pObj�쐬
			Objs::InsertObj(RH, OBJ_RKTHIT, 15);				//�I�u�W�F�N�g�o�^
		}
		else if (ButtonUE == 3)
		{
			Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_ENEMYPOD, OBJ_PODS, 1);
			CObjRktHit* RH = new CObjRktHit(m_x, m_y, m_type);	//�q�b�g�{�b�N�X�pObj�쐬
			Objs::InsertObj(RH, OBJ_RKTHIT, 15);				//�I�u�W�F�N�g�o�^
		}
		else if (ButtonUE == 4)
		{
			Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_ENEMYPOD, OBJ_PODB, 1);
			CObjRktHit* RH = new CObjRktHit(m_x, m_y, m_type);	//�q�b�g�{�b�N�X�pObj�쐬
			Objs::InsertObj(RH, OBJ_RKTHIT, 15);				//�I�u�W�F�N�g�o�^
		}
		else if (ButtonUE == 5)
		{
			Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_ENEMYPOD, OBJ_ROCKET, 1);
		}
		if (ButtonUP != 5) {
			e_pnam++;
		}
		if (e_pnam == 9)
			e_pnam = 0;
	}

	m_eff.m_top = 0;
	m_eff.m_left = 0;
	m_eff.m_right = 32;
	m_eff.m_bottom = 29;
	m_ani = 0;
	m_ani_max = 1;
	m_ani_time = 0;
	m_del = false;
	m_vx = 0.0f;

	m_a = 1.0f;
	m_bom = 0.3f;

	//�|�b�h��HP�����߂�
	if (ButtonU == 5)			//�|�b�h���~�T�C���̎��̂�HP��1�ɂ���
	{
		m_pod_max_hp = 1.0f;
	}
	else if (m_type == 0) {		//���f���̎���(�|�b�h��Lv*10)+(��������Lv*5)��HP�ɑ������
		m_pod_max_hp = (float)((g_Pod_equip_Level * 10) + ((g_Ins_Level - 1)* 5));
	}
	else if (m_type == 1) {		//�G�f���̎��͌Œ�l
		m_pod_max_hp = 10.0f;
	}
	else if (m_type == 2) {
		m_pod_max_hp = 20.0f;
	}
	else if (m_type == 3) {
		m_pod_max_hp = 20.0f;
	}
	else if (m_type == 4) {
		m_pod_max_hp = 17.0f;
	}
	else if (m_type == 5) {
		m_pod_max_hp = 30.0f;
	}
	else if (m_type == 6) {
		m_pod_max_hp = 10.0f;
	}

	m_podhp = m_pod_max_hp;

	m_hp_cnt = 0;		//���G�^�C��
	m_hp_f = false;		//���G�t���O
	m_fight = false;	//�Փ˒��t���O
	m_stop_f = false;	//��~�t���O
	//m_pstop = false;	//�|�b�h�ł̒�~�t���O
	m_stop_cnt = 0;		//�~�߂�܂ł̃J�E���g
	m_bomcount = 0;		//�����J�E���g

	////�~�T�C���̉Η͂����߂邽�߂̏���
	////�i�g��Ȃ��\����j
	//for (int i = 0; i < 4; i++)
	//{
	//	switch (i) {
	//	case 0:
	//		m_level_comp[i] = g_Pow_equip_Level;
	//		break;
	//	case 1:
	//		m_level_comp[i] = g_Def_equip_Level;
	//		break;
	//	case 2:
	//		m_level_comp[i] = g_Spe_equip_Level;
	//		break;
	//	case 3:
	//		m_level_comp[i] = g_Bal_equip_Level;
	//		break;
	//	}
	//}

	//for (int i = 1; i<4; ++i)
	//{
	//	if (m_level_comp[0] > m_level_comp[i])
	//	{
	//		g_Missile_pow = m_level_comp[i];
	//	}
	//}

	//g_Missile_pow = g_Missile_pow * (10 / 2);

	m_Enemy_damage = 2.0f;//�G�l�~�[���󂯂�_���[�W��(�v���C���[�̊�b�U����)
	m_Player_damage = 2.0f;//�v���C���[���󂯂�_���[�W��(�G�l�~�[�̊�b�U����)
	

	//�G�̉Η͂�G�ɂ���ĕς���
	switch (g_Challenge_enemy + 1) {
	case 1:
		m_Enemy_Pod_Level = 1;		//�|�b�h���x���ݒ�
		m_Player_damage = 3.0f;		//�v���C���[�ւ̃|�b�h�ɂ��U���͌���
		g_P_Planet_damage = m_Player_damage;//ObjPlanet�ɓn���p
		break;
	case 2:
		m_Enemy_Pod_Level = 2;		//�|�b�h���x���ݒ�
		m_Player_damage = 10.0f;
		g_P_Planet_damage = m_Player_damage;
		break;
	case 3:
		m_Enemy_Pod_Level = 2;		//�|�b�h���x���ݒ�
		m_Player_damage = 15.0f;
		g_P_Planet_damage = m_Player_damage;
		break;
	case 4:
		m_Enemy_Pod_Level = 1;		//�|�b�h���x���ݒ�
		m_Player_damage = 6.0f;
		g_P_Planet_damage = m_Player_damage;
		break;
	case 5:
		m_Enemy_Pod_Level = 3;		//�|�b�h���x���ݒ�
		m_Player_damage = 17.0f;
		g_P_Planet_damage = m_Player_damage;
		break;
	case 6:
		m_Enemy_Pod_Level = 1;		//�|�b�h���x���ݒ�
		m_Player_damage = 2.0f;
		g_P_Planet_damage = m_Player_damage;
	}
}

//�A�N�V����
void CObjRocket::Action()
{
	//���|�[�Y��ʓ��ɂ��ꎞ��~���Ƀ~�T�C���|�b�h�������Ȃ��悤�ɂ��鏈��
	if (battle_start == false)
	{
		return;
	}

	m_vx = 0.0f;//�x�N�g��������
	m_vy = 0.0f;

	CObjFight* obj = (CObjFight*)Objs::GetObj(OBJ_FIGHT);	//�퓬��ʂ̏��
	CHitBox* hit = Hits::GetHitBox(this);					//HitBox���擾

	if (battle_end == true)
	{					//�o�g���I�����A���݂��Ă���S�Ẵ|�b�h��j�󂷂�
		Audio::Start(5);
		m_del = true;
	}

	//�|�b�h���m�̐퓬����HitBox�ʒu�ƃT�C�Y��ύX����
	if (m_type == 0)
		if (ButtonU == 5) {//���P�b�g�̂ݒʏ�ōX�V
			hit->SetPos(m_x, m_y,m_size, m_size);		//HitBox�X�V
		}
		else
		{
			hit->SetPos(m_x, m_y, m_size, m_size);		//HitBox�X�V
			if (m_fight == true)		
				hit->SetPos(m_x - m_size * (m_schange - 1),m_y,m_size,m_size * m_schange);//�퓬���ύX
		}
	else
	{
		hit->SetPos(m_x, m_y, m_size, m_size);			//HitBox�X�V
		if(m_fight == true)				
			hit->SetPos(m_x, m_y, m_size, m_size * m_schange);				//�퓬���ύX
	}

	if (m_fight == true)
	{
		if (m_atk_cnt > m_atk_cnt_max)//max�𒴂�����
		{
			m_atk_cnt = 0;//0�Ƀ��Z�b�g
		}
		else//max�𒴂��ĂȂ���
		{
			m_atk_cnt++;//�J�E���g
		}
	}

	//if (m_pstop == true)		//�|�b�h��~�t���OON��
	//{
	//	m_stop_cnt+=0.5;
	//	if (m_stop_cnt == m_pod_nam)
	//	{
	//		hit->SetInvincibility(true);		//HitBox�̔��薳��
	//		m_schange = 4.0f;
	//		m_fight = true;
	//	}
	//	else if (m_stop_cnt == m_pod_nam + 10)
	//	{
	//		hit->SetInvincibility(false);		//HitBox�̔���L��
	//		m_stop_cnt = 0;
	//	}
	//}
	//else
	//	m_schange = 3.0f;

	//if (m_pstop == false) {
		if (m_stop_f == true)	//��~�t���OON��
		{
			m_stop_cnt++;
			if (m_stop_cnt == 8) {
				m_fight = true;
			}
			else if (m_stop_cnt == 11) {
				m_stop_cnt = 0;
			}
		}
		else if(m_del == false)//��~���ȊO�A�ړ��x�N�g�����Z
		{
			m_fight = false;
			m_mov += m_mov_spd / 2;

			//�e���C�����̓�����
			if (m_get_line == 0 || m_get_line == 3)//------�ド�C��----
			{
				m_vx -= 0.3f;
				m_vy += (-0.15 + m_mov);
			}
			else if (m_get_line == 1)//---------------�����C��-----
			{
				m_vx -= 0.3f;
			}
			else//if(m_get_line == 2)---------------�����C��------
			{
				m_vx -= 0.3f;
				m_vy -= (-0.15 + m_mov);
			}

			//-----------------------------���W�X�V
			if (m_type == 0) {
				m_x += m_vx * 2 - m_mov_spd * 200;
				m_y += m_vy * 2;
			}
			else {
				m_x -= m_vx * 2 - m_mov_spd * 200;
				m_y += m_vy * 2;
			}
		}
	//}
	

	//�����G�t�F�N�g
	m_eff = GetPodEffec(&m_ani, &m_ani_time, m_del, 4);	//�G�ƃv���C���[�̃|�b�h�������Ă���Ƃ�����
	
	//---------------------------------------�|�b�h���ŏ���
	if (m_del == true)
	{
		hit->SetInvincibility(true);		//HitBox�̔��薳��
		if (m_ani == 20 && m_bom == 0)
		{
			//[�X�y�V�����Z:�X�e���C�h���^]�������Ɏ��s
			//�|�b�h���j�󂳂��x�ɂ��̐����J�E���g����
			//���퓬�I�����͎��s���Ȃ�
			if (battle_end == false)
			{
				CObjSpecialButton* Special = (CObjSpecialButton*)Objs::GetObj(OBJ_SPECIAL);
				if (m_type == 0 && g_Special_equipment == 5 && Special->GetInvocating(0) == true && ButtonUP != 5)
				{
					Special->SetBuff_count(0);//�j�󂳂ꂽ�����|�b�h�����J�E���g����
				}
				if (m_type != 0 && Special->GetSpecial_equip() == 5 && Special->GetInvocating(1) == true && ButtonUE != 5)
				{
					Special->SetBuff_count(1);//�j�󂳂ꂽ�����|�b�h�����J�E���g����
				}
			}
				this->SetStatus(false);
				Hits::DeleteHitBox(this);
		}
	}
	
	//���|�b�h�̓����蔻�菈��
	//���퓬�I����͈ȉ��̃|�b�h�̏����͍s��Ȃ�
	if (battle_end == false)
	{
		if (ButtonU != 5) {		//�~�T�C���ȊO�̃X�g�b�v����
			if (hit->CheckElementHit(ELEMENT_NULL) == true && m_type == 0)//Hit�pOBJ�ɓ��������ꍇ
				if ((hit->CheckObjNameHit(OBJ_RKTHIT) != nullptr && m_pnam == 0)||
					(hit->CheckObjNameHit(OBJ_RKTHIT1) != nullptr && m_pnam == 1) ||
					(hit->CheckObjNameHit(OBJ_RKTHIT2) != nullptr && m_pnam == 2) ||
					(hit->CheckObjNameHit(OBJ_RKTHIT3) != nullptr && m_pnam == 3) ||
					(hit->CheckObjNameHit(OBJ_RKTHIT4) != nullptr && m_pnam == 4) ||
					(hit->CheckObjNameHit(OBJ_RKTHIT5) != nullptr && m_pnam == 5) ||
					(hit->CheckObjNameHit(OBJ_RKTHIT6) != nullptr && m_pnam == 6) ||
					(hit->CheckObjNameHit(OBJ_RKTHIT7) != nullptr && m_pnam == 7) ||
					(hit->CheckObjNameHit(OBJ_RKTHIT8) != nullptr && m_pnam == 8) ||
					(hit->CheckObjNameHit(OBJ_RKTHIT9) != nullptr && m_pnam == 9))
					m_fight = true;
				else if ((hit->CheckObjNameHit(OBJ_eRKTHIT) != nullptr && m_pnam == 0) ||
					(hit->CheckObjNameHit(OBJ_eRKTHIT1) != nullptr && m_pnam == 1) ||
					(hit->CheckObjNameHit(OBJ_eRKTHIT2) != nullptr && m_pnam == 2) ||
					(hit->CheckObjNameHit(OBJ_eRKTHIT3) != nullptr && m_pnam == 3) ||
					(hit->CheckObjNameHit(OBJ_eRKTHIT4) != nullptr && m_pnam == 4) ||
					(hit->CheckObjNameHit(OBJ_eRKTHIT5) != nullptr && m_pnam == 5) ||
					(hit->CheckObjNameHit(OBJ_eRKTHIT6) != nullptr && m_pnam == 6) ||
					(hit->CheckObjNameHit(OBJ_eRKTHIT7) != nullptr && m_pnam == 7) ||
					(hit->CheckObjNameHit(OBJ_eRKTHIT8) != nullptr && m_pnam == 8) ||
					(hit->CheckObjNameHit(OBJ_eRKTHIT9) != nullptr && m_pnam == 9))
					m_fight = true;
				else
					m_fight = false;
			else
				m_fight = false;		//�i�߂�
		}

		if (m_type == 0) {	//�����^�C�v���m�ł́A�Փ˃X�g�b�v����
			if (hit->CheckElementHit(ELEMENT_POD) == true && (m_pnam >= 1 && m_pnam <= 3))
				m_stop_f = true;
			else if (hit->CheckElementHit(ELEMENT_POD1) == true && (m_pnam >= 2 && m_pnam <= 4))
				m_stop_f = true;
			else if (hit->CheckElementHit(ELEMENT_POD2) == true && (m_pnam >= 3 && m_pnam <= 5))
				m_stop_f = true;
			else if (hit->CheckElementHit(ELEMENT_POD3) == true && (m_pnam >= 4 && m_pnam <= 6))
				m_stop_f = true;
			else if (hit->CheckElementHit(ELEMENT_POD4) == true && (m_pnam >= 5 && m_pnam <= 7))
				m_stop_f = true;
			else if (hit->CheckElementHit(ELEMENT_POD5) == true && (m_pnam >= 6 && m_pnam <= 8))
				m_stop_f = true;
			else if (hit->CheckElementHit(ELEMENT_POD6) == true && (m_pnam >= 7 && m_pnam <= 9))
				m_stop_f = true;
			else if (hit->CheckElementHit(ELEMENT_POD7) == true && (m_pnam >= 8 || m_pnam <= 0))
				m_stop_f = true;
			else if (hit->CheckElementHit(ELEMENT_POD8) == true && (m_pnam >= 9 || m_pnam <= 1))
				m_stop_f = true;
			else if (hit->CheckElementHit(ELEMENT_POD9) == true && (m_pnam >= 0 || m_pnam <= 2))
				m_stop_f = true;
			else if(m_fight == false)
				m_stop_f = false;
		}
		else {
			if (hit->CheckElementHit(ELEMENT_ENEMYPOD) == true && (m_pnam >= 1 && m_pnam <= 3))
				m_stop_f = true;
			else if (hit->CheckElementHit(ELEMENT_ENEMYPOD1) == true && (m_pnam >= 2 && m_pnam <= 4))
				m_stop_f = true;
			else if (hit->CheckElementHit(ELEMENT_ENEMYPOD2) == true && (m_pnam >= 3 && m_pnam <= 5))
				m_stop_f = true;
			else if (hit->CheckElementHit(ELEMENT_ENEMYPOD3) == true && (m_pnam >= 4 && m_pnam <= 6))
				m_stop_f = true;
			else if (hit->CheckElementHit(ELEMENT_ENEMYPOD4) == true && (m_pnam >= 5 && m_pnam <= 7))
				m_stop_f = true;
			else if (hit->CheckElementHit(ELEMENT_ENEMYPOD5) == true && (m_pnam >= 6 && m_pnam <= 8))
				m_stop_f = true;
			else if (hit->CheckElementHit(ELEMENT_ENEMYPOD6) == true && (m_pnam >= 7 && m_pnam <= 9))
				m_stop_f = true;
			else if (hit->CheckElementHit(ELEMENT_ENEMYPOD7) == true && (m_pnam >= 8 || m_pnam <= 0))
				m_stop_f = true;
			else if (hit->CheckElementHit(ELEMENT_ENEMYPOD8) == true && (m_pnam >= 9 || m_pnam <= 1))
				m_stop_f = true;
			else if (hit->CheckElementHit(ELEMENT_ENEMYPOD9) == true && (m_pnam >= 0 || m_pnam <= 2))
				m_stop_f = true;
			else if (m_fight == false)
				m_stop_f = false;
		}

		//�v���C���[�̃~�T�C���|�b�h���G�l�~�[�̃X�y�V�����Z(FRACTURE_RAY)�̃I�u�W�F�N�gHIT���A
		//HP�̏�ԂɊւ�炸���ŏ����ւƈڍs����
		if (hit->CheckObjNameHit(OBJ_FRACTURE_RAY, 1) != nullptr && //�G�l�~�[�̃X�y�V�����Z��HIT���A
			m_type == 0)											//�v���C���[�̎ˏo�����|�b�h�ł���ꍇ�A���s
		{
			m_del = true;				//���ŏ����t���OON
			Audio::Start(5);
		}

		//�G�l�~�[�̃~�T�C���|�b�h���v���C���[�̃X�y�V�����Z(FRACTURE_RAY)�̃I�u�W�F�N�gHIT���A
		//HP�̏�ԂɊւ�炸���ŏ����ւƈڍs����
		if (hit->CheckObjNameHit(OBJ_FRACTURE_RAY, 0) != nullptr && //�v���C���[�̃X�y�V�����Z��HIT���A
			m_type != 0)										//�G�l�~�[�̎ˏo�����|�b�h�ł���ꍇ�A���s
		{
			m_del = true;				//���ŏ����t���OON
			Audio::Start(5);
		}

		if (hit->CheckElementHit(ELEMENT_PLAYER) == true && m_type != 0)		//�f���ɓ������������G�e
		{
			//�f���ƐڐG���Ă��邩�ǂ����𒲂ׂ�
			m_del = true;
			hit->SetInvincibility(true);
			Audio::Start(5);
		}
		else if (hit->CheckElementHit(ELEMENT_ENEMY) == true && m_type == 0)	//�G�̘f���ɓ��������������e
		{
			//�f���ƐڐG���Ă��邩�ǂ����𒲂ׂ�
			m_del = true;
			hit->SetInvincibility(true);
			Audio::Start(5);
		}

		//�G�̃|�b�h���v���C���[�̃|�b�h�ɂԂ��������̔���
		//���G�l�~�[���_���[�W���󂯂鎞�̏���
		if ((hit->CheckElementHit(ELEMENT_POD) == true ||
			hit->CheckElementHit(ELEMENT_POD1) == true ||
			hit->CheckElementHit(ELEMENT_POD2) == true ||
			hit->CheckElementHit(ELEMENT_POD3) == true ||
			hit->CheckElementHit(ELEMENT_POD4) == true ||
			hit->CheckElementHit(ELEMENT_POD5) == true || 
			hit->CheckElementHit(ELEMENT_POD6) == true || 
			hit->CheckElementHit(ELEMENT_POD7) == true || 
			hit->CheckElementHit(ELEMENT_POD8) == true || 
			hit->CheckElementHit(ELEMENT_POD9) == true )&& m_type != 0)
		{
			m_fight = true;	//�Փ˒��t���O�n�m
			m_stop_f = true;
			
			if (ButtonUE == 1)		//�G�̎�ނP(�p���[)���v���C���[�̃|�b�h�Ɠ��������ꍇ
			{
				if (m_atk_cnt == 0)	//0�̎��̂݁A�e�_���[�W���󂯂�
				{
					if (hit->CheckObjNameHit(OBJ_PODS) != nullptr)			//�v���C���[�̃X�s�[�h�|�b�h�����莞��HP
					{
						//m_Enemy_damage += (float)g_Spe_equip_Level;//�v���C���[�̉Η͂𑕔����x���ɂ���ĕς���(+�|�b�h���x��)
						//m_Enemy_damage += (float)(g_Bar_Level - 1);//���܂����Η�+����Lv

						//m_Enemy_damage *= m_One_pat_dem;//�����p�^�[���f�����b�g�l�̏�Z���s��

						m_podhp -= m_Enemy_damage * damage_buff[0] * 0.8f * m_One_pat_dem + (float)g_Spe_equip_Level + (float)(g_Bar_Level - 1);
					}
					else if (hit->CheckObjNameHit(OBJ_PODD) != nullptr)		//�v���C���[�̃f�B�t�F���X�|�b�h�����莞��HP
					{
						//m_Enemy_damage += (float)g_Def_equip_Level;//�v���C���[�̉Η͂𑕔����x���ɂ���ĕς���(+�|�b�h���x��)
						//m_Enemy_damage += (float)(g_Bar_Level - 1);//���܂����Η�+����Lv

						//m_Enemy_damage *= m_One_pat_dem;//�����p�^�[���f�����b�g�l�̏�Z���s��

						m_podhp -= m_Enemy_damage * damage_buff[0] * 1.2f * m_One_pat_dem + (float)g_Def_equip_Level + (float)(g_Bar_Level - 1);
					}
					else if (hit->CheckObjNameHit(OBJ_PODP) != nullptr)		//�v���C���[�̃p���[�|�b�h�����莞��HP
					{
						//m_Enemy_damage += (float)g_Pow_equip_Level;//�v���C���[�̉Η͂𑕔����x���ɂ���ĕς���(+�|�b�h���x��)
						//m_Enemy_damage += (float)(g_Bar_Level - 1);//���܂����Η�+����Lv

						//m_Enemy_damage *= m_One_pat_dem;//�����p�^�[���f�����b�g�l�̏�Z���s��

						m_podhp -= m_Enemy_damage * damage_buff[0] * m_One_pat_dem + (float)g_Pow_equip_Level + (float)(g_Bar_Level - 1);
					}
					else if (hit->CheckObjNameHit(OBJ_PODB) != nullptr)//�v���C���[�̃o�����X�|�b�h�����莞��HP
					{
						//m_Enemy_damage += (float)g_Bal_equip_Level;//�v���C���[�̉Η͂𑕔����x���ɂ���ĕς���(+�|�b�h���x��)
						//m_Enemy_damage += (float)(g_Bar_Level - 1);//���܂����Η�+����Lv

						//m_Enemy_damage *= m_One_pat_dem;//�����p�^�[���f�����b�g�l�̏�Z���s��

						m_podhp -= m_Enemy_damage * damage_buff[0] * 1.1f * m_One_pat_dem + (float)g_Bal_equip_Level + (float)(g_Bar_Level - 1);
					}
				}
				if (hit->CheckObjNameHit(OBJ_ROCKET) != nullptr)//�G�̃~�T�C���ɓ�����������HP����
				{
					//m_Enemy_damage = 3.0f;//�~�T�C���̎��͉Η�3�Œ�
					//m_Enemy_damage *= m_One_pat_dem;//�����p�^�[���f�����b�g�l�̏�Z���s��

					m_podhp -= (m_Enemy_damage + 1.0f) * m_One_pat_dem;
				}
			}
			else if (ButtonUE == 2)	//�G�̎�ނQ(�f�B�t�F���X)���v���C���[�̃|�b�h�Ɠ��������ꍇ
			{
				if (m_atk_cnt == 0)	//0�̎��̂݁A�e�_���[�W���󂯂�
				{
					if (hit->CheckObjNameHit(OBJ_PODP) != nullptr)			//�v���C���[�̃p���[�|�b�h�����莞��HP
					{
						//m_Enemy_damage += (float)g_Pow_equip_Level;//�v���C���[�̉Η͂𑕔����x���ɂ���ĕς���(+�|�b�h���x��)
						//m_Enemy_damage += (float)(g_Bar_Level - 1);//���܂����Η�+����Lv

						//m_Enemy_damage *= m_One_pat_dem;//�����p�^�[���f�����b�g�l�̏�Z���s��

						m_podhp -= m_Enemy_damage * damage_buff[0] * 0.8f * m_One_pat_dem + (float)g_Pow_equip_Level + (float)(g_Bar_Level - 1);
					}
					else if (hit->CheckObjNameHit(OBJ_PODS) != nullptr)		//�v���C���[�̃X�s�[�h�|�b�h�����莞��HP
					{
						//m_Enemy_damage += (float)g_Spe_equip_Level;//�v���C���[�̉Η͂𑕔����x���ɂ���ĕς���(+�|�b�h���x��)
						//m_Enemy_damage += (float)(g_Bar_Level - 1);//���܂����Η�+����Lv

						//m_Enemy_damage *= m_One_pat_dem;//�����p�^�[���f�����b�g�l�̏�Z���s��

						m_podhp -= m_Enemy_damage * damage_buff[0] * 1.2f * m_One_pat_dem + (float)g_Spe_equip_Level + (float)(g_Bar_Level - 1);
					}
					else if (hit->CheckObjNameHit(OBJ_PODD) != nullptr)		//�v���C���[�̃f�B�t�F���X�|�b�h�����莞��HP
					{
						//m_Enemy_damage += (float)g_Def_equip_Level;//�v���C���[�̉Η͂𑕔����x���ɂ���ĕς���(+�|�b�h���x��)
						//m_Enemy_damage += (float)(g_Bar_Level - 1);//���܂����Η�+����Lv

						//m_Enemy_damage *= m_One_pat_dem;//�����p�^�[���f�����b�g�l�̏�Z���s��

						m_podhp -= m_Enemy_damage * damage_buff[0] * m_One_pat_dem + (float)g_Def_equip_Level + (float)(g_Bar_Level - 1);
					}
					else if (hit->CheckObjNameHit(OBJ_PODB) != nullptr)	//�v���C���[�̃o�����X�|�b�h�����莞��HP
					{
						//m_Enemy_damage += (float)g_Bal_equip_Level;//�v���C���[�̉Η͂𑕔����x���ɂ���ĕς���(+�|�b�h���x��)
						//m_Enemy_damage += (float)(g_Bar_Level - 1);//���܂����Η�+����Lv

						//m_Enemy_damage *= m_One_pat_dem;//�����p�^�[���f�����b�g�l�̏�Z���s��

						m_podhp -= m_Enemy_damage * damage_buff[0] * 1.1f * m_One_pat_dem + (float)g_Bal_equip_Level + (float)(g_Bar_Level - 1);
					}
				}
				if (hit->CheckObjNameHit(OBJ_ROCKET) != nullptr)//�G�̃~�T�C���ɓ�����������HP����
				{
					//m_Enemy_damage = 3.0f;//�~�T�C���̎��͉Η�3�Œ�
					//m_Enemy_damage *= m_One_pat_dem;//�����p�^�[���f�����b�g�l�̏�Z���s��

					m_podhp -= (m_Enemy_damage + 1.0f) * m_One_pat_dem;
				}
			}
			else if (ButtonUE == 3)	//�G�̎�ނR(�X�s�[�h)���v���C���[�̃|�b�h�Ɠ��������ꍇ
			{
				if (m_atk_cnt == 0)	//0�̎��̂݁A�e�_���[�W���󂯂�
				{
					if (hit->CheckObjNameHit(OBJ_PODP) != nullptr)			//�v���C���[�̃p���[�|�b�h�����莞��HP
					{
						//m_Enemy_damage += (float)g_Pow_equip_Level;//�v���C���[�̉Η͂𑕔����x���ɂ���ĕς���(+�|�b�h���x��)
						//m_Enemy_damage += (float)(g_Bar_Level - 1);//���܂����Η�+����Lv

						//m_Enemy_damage *= m_One_pat_dem;//�����p�^�[���f�����b�g�l�̏�Z���s��

						m_podhp -= m_Enemy_damage * damage_buff[0] * 1.2f * m_One_pat_dem + (float)g_Pow_equip_Level + (float)(g_Bar_Level - 1);
					}
					else if (hit->CheckObjNameHit(OBJ_PODD) != nullptr)		//�v���C���[�̃f�B�t�F���X�|�b�h�����莞��HP
					{
						//m_Enemy_damage += (float)g_Def_equip_Level;//�v���C���[�̉Η͂𑕔����x���ɂ���ĕς���(+�|�b�h���x��)
						//m_Enemy_damage += (float)(g_Bar_Level - 1);//���܂����Η�+����Lv

						//m_Enemy_damage *= m_One_pat_dem;//�����p�^�[���f�����b�g�l�̏�Z���s��

						m_podhp -= m_Enemy_damage * damage_buff[0] * 0.8f * m_One_pat_dem + (float)g_Def_equip_Level + (float)(g_Bar_Level - 1);
					}
					else if (hit->CheckObjNameHit(OBJ_PODS) != nullptr)		//�v���C���[�̃X�s�[�h�|�b�h�����莞��HP
					{
						//m_Enemy_damage += (float)g_Spe_equip_Level;//�v���C���[�̉Η͂𑕔����x���ɂ���ĕς���(+�|�b�h���x��)
						//m_Enemy_damage += (float)(g_Bar_Level - 1);//���܂����Η�+����Lv

						//m_Enemy_damage *= m_One_pat_dem;//�����p�^�[���f�����b�g�l�̏�Z���s��

						m_podhp -= m_Enemy_damage * damage_buff[0] * m_One_pat_dem + (float)g_Spe_equip_Level + (float)(g_Bar_Level - 1);
					}
					else if (hit->CheckObjNameHit(OBJ_PODB) != nullptr)	//�v���C���[�̃o�����X�|�b�h�����莞��HP
					{
						//m_Enemy_damage += (float)g_Bal_equip_Level;//�v���C���[�̉Η͂𑕔����x���ɂ���ĕς���(+�|�b�h���x��)
						//m_Enemy_damage += (float)(g_Bar_Level - 1);//���܂����Η�+����Lv

						//m_Enemy_damage *= m_One_pat_dem;//�����p�^�[���f�����b�g�l�̏�Z���s��

						m_podhp -= m_Enemy_damage * damage_buff[0] * 1.1f * m_One_pat_dem + (float)g_Bal_equip_Level + (float)(g_Bar_Level - 1);
					}
				}
				if (hit->CheckObjNameHit(OBJ_ROCKET) != nullptr)//�G�̃~�T�C���ɓ�����������HP����
				{
					//m_Enemy_damage = 3.0f;//�~�T�C���̎��͉Η�3�Œ�
					//m_Enemy_damage *= m_One_pat_dem;//�����p�^�[���f�����b�g�l�̏�Z���s��

					m_podhp -= (m_Enemy_damage + 1.0f) * m_One_pat_dem;
				}
			}
			else if (ButtonUE == 4)	//�G�̎�ނS(�o�����X)���v���C���[�̃|�b�h�ƃ~�T�C���ɓ��������ꍇ
			{
				if (m_atk_cnt == 0)	//0�̎��̂݁A�_���[�W���󂯂�
				{
					if (hit->CheckObjNameHit(OBJ_PODP) != nullptr)			//�v���C���[�̃p���[�|�b�h�����莞��HP
					{
						//m_Enemy_damage += (float)g_Pow_equip_Level;//�v���C���[�̉Η͂𑕔����x���ɂ���ĕς���(+�|�b�h���x��)
						//m_Enemy_damage += (float)(g_Bar_Level - 1);//���܂����Η�+����Lv

						//m_Enemy_damage *= m_One_pat_dem;//�����p�^�[���f�����b�g�l�̏�Z���s��

						m_podhp -= m_Enemy_damage * damage_buff[0] * 0.9f * m_One_pat_dem + (float)g_Pow_equip_Level + (float)(g_Bar_Level - 1);
					}
					else if (hit->CheckObjNameHit(OBJ_PODD) != nullptr)		//�v���C���[�̃f�B�t�F���X�|�b�h�����莞��HP
					{
						//m_Enemy_damage += (float)g_Def_equip_Level;//�v���C���[�̉Η͂𑕔����x���ɂ���ĕς���(+�|�b�h���x��)
						//m_Enemy_damage += (float)(g_Bar_Level - 1);//���܂����Η�+����Lv

						//m_Enemy_damage *= m_One_pat_dem;//�����p�^�[���f�����b�g�l�̏�Z���s��

						m_podhp -= m_Enemy_damage * damage_buff[0] * 0.9f * m_One_pat_dem + (float)g_Def_equip_Level + (float)(g_Bar_Level - 1);
					}
					else if (hit->CheckObjNameHit(OBJ_PODS) != nullptr)		//�v���C���[�̃X�s�[�h�|�b�h�����莞��HP
					{
						//m_Enemy_damage += (float)g_Spe_equip_Level;//�v���C���[�̉Η͂𑕔����x���ɂ���ĕς���(+�|�b�h���x��)
						//m_Enemy_damage += (float)(g_Bar_Level - 1);//���܂����Η�+����Lv

						//m_Enemy_damage *= m_One_pat_dem;//�����p�^�[���f�����b�g�l�̏�Z���s��

						m_podhp -= m_Enemy_damage * damage_buff[0] * 0.9f * m_One_pat_dem + (float)g_Spe_equip_Level + (float)(g_Bar_Level - 1);
					}
					else if (hit->CheckObjNameHit(OBJ_PODB) != nullptr)	//�v���C���[�̃o�����X�|�b�h�����莞��HP
					{
						//m_Enemy_damage += (float)g_Bal_equip_Level;//�v���C���[�̉Η͂𑕔����x���ɂ���ĕς���(+�|�b�h���x��)
						//m_Enemy_damage += (float)(g_Bar_Level - 1);//���܂����Η�+����Lv

						//m_Enemy_damage *= m_One_pat_dem;//�����p�^�[���f�����b�g�l�̏�Z���s��

						m_podhp -= m_Enemy_damage * damage_buff[0] * m_One_pat_dem + (float)g_Bal_equip_Level + (float)(g_Bar_Level - 1);
					}
				}
				if (hit->CheckObjNameHit(OBJ_ROCKET) != nullptr)//�G�̃~�T�C���ɓ�����������HP����
				{
					//m_Enemy_damage = 3.0f;//�~�T�C���̎��͉Η�3�Œ�
					//m_Enemy_damage *= m_One_pat_dem;//�����p�^�[���f�����b�g�l�̏�Z���s��
					
					m_podhp -= (m_pod_max_hp * 0.85) * m_One_pat_dem;//�ő�HP*0.85�{�̃_���[�W��^����
				}
			}
			else if (ButtonUE == 5)	//�G�̎�ނT(�~�T�C��)���v���C���[�̃|�b�h�ɓ��������ꍇ
			{
				m_del = true;				//���ŏ����t���OON
				Audio::Start(5);
			}
		}
		else if (m_type != 0 && m_stop_cnt == 10) {	//�G���A��~��
			m_fight = false;
			m_stop_cnt = 0;
		}
		

		//�v���C���[�̃|�b�h���G�̃|�b�h�ƂԂ��������̔���
		//���v���C���[���_���[�W���󂯂鎞�̏���
		if (hit->CheckElementHit(ELEMENT_ENEMYPOD) == true && m_type == 0)
		{
			m_fight = true;	//�Փ˒��t���O�n�m
			m_stop_f = true;
			Audio::Start(5);
			
			if (ButtonUP == 1)		//�����̎�ނP(�p���[)���G�̃|�b�h�Ɠ��������ꍇ
			{
				if (m_atk_cnt == 0)	//0�̎��̂݁A�e�_���[�W���󂯂�
				{
					if (hit->CheckObjNameHit(OBJ_PODS) != nullptr)			//�G�̃X�s�[�h�|�b�h�����莞��HP
					{
						//m_Player_damage *= m_One_pat_dem;//�����p�^�[���f�����b�g�l�̏�Z���s��

						m_podhp -= m_Player_damage * damage_buff[1] * 0.8f * m_One_pat_dem;
					}
					else if (hit->CheckObjNameHit(OBJ_PODD) != nullptr)		//�G�̃f�B�t�F���X�|�b�h�����莞��HP
					{
						//m_Player_damage *= m_One_pat_dem;//�����p�^�[���f�����b�g�l�̏�Z���s��

						m_podhp -= m_Player_damage * damage_buff[1] * 1.2f * m_One_pat_dem;
					}
					else if (hit->CheckObjNameHit(OBJ_PODP) != nullptr)		//�G�̃p���[�|�b�h�����莞��HP
					{
						// * m_One_pat_demm_Player_damage *= m_One_pat_dem;//�����p�^�[���f�����b�g�l�̏�Z���s��

						m_podhp -= m_Player_damage * damage_buff[1] * m_One_pat_dem;
					}
					else if (hit->CheckObjNameHit(OBJ_PODB) != nullptr)	//�G�̃o�����X�|�b�h�����莞��HP
					{
						//m_Player_damage *= m_One_pat_dem;//�����p�^�[���f�����b�g�l�̏�Z���s��

						m_podhp -= m_Player_damage * damage_buff[1] * 1.1f * m_One_pat_dem;
					}
				}
				if (hit->CheckObjNameHit(OBJ_ROCKET) != nullptr)//�G�̃~�T�C���ɓ�����������HP����
				{
					//m_Player_damage = 3.0f;//�~�T�C���̎��͉Η�3�Œ�

					//m_Player_damage *= m_One_pat_dem;//�����p�^�[���f�����b�g�l�̏�Z���s��

					m_podhp -= (m_Player_damage + 1.0f) * m_One_pat_dem;
				}
			}
			else if (ButtonUP == 2)	//�����̎�ނQ(�f�B�t�F���X)���G�̃|�b�h�Ɠ��������ꍇ
			{
				if (m_atk_cnt == 0)	//0�̎��̂݁A�e�_���[�W���󂯂�
				{
					if (hit->CheckObjNameHit(OBJ_PODP) != nullptr)			//�G�̃p���[�|�b�h�����莞��HP
					{
						//m_Player_damage *= m_One_pat_dem;//�����p�^�[���f�����b�g�l�̏�Z���s��

						m_podhp -= m_Player_damage * damage_buff[1] * 0.8f * m_One_pat_dem;
					}
					else if (hit->CheckObjNameHit(OBJ_PODS) != nullptr)		//�G�̃X�s�[�h�|�b�h�����莞��HP
					{
						//m_Player_damage *= m_One_pat_dem;//�����p�^�[���f�����b�g�l�̏�Z���s��

						m_podhp -= m_Player_damage * damage_buff[1] * 1.2f * m_One_pat_dem;
					}
					else if (hit->CheckObjNameHit(OBJ_PODD) != nullptr)		//�G�̃f�B�t�F���X�|�b�h�����莞��HP
					{
						//m_Player_damage *= m_One_pat_dem;//�����p�^�[���f�����b�g�l�̏�Z���s��

						m_podhp -= m_Player_damage * damage_buff[1] * m_One_pat_dem;
					}
					else if (hit->CheckObjNameHit(OBJ_PODB) != nullptr)	//�G�̃o�����X�|�b�h�����莞��HP
					{
						//m_Player_damage *= m_One_pat_dem;//�����p�^�[���f�����b�g�l�̏�Z���s��

						m_podhp -= m_Player_damage * damage_buff[1] * 1.1f * m_One_pat_dem;
					}
				}
				if (hit->CheckObjNameHit(OBJ_ROCKET) != nullptr)//�G�̃~�T�C���ɓ�����������HP����
				{
					//m_Player_damage = 3.0f;//�~�T�C���̎��͉Η�3�Œ�

					//m_Player_damage *= m_One_pat_dem;//�����p�^�[���f�����b�g�l�̏�Z���s��
					
					m_podhp -= (m_Player_damage + 1.0f) * m_One_pat_dem;
				}
			}
			else if (ButtonUP == 3)//�����̎�ނR(�X�s�[�h)���G�̃|�b�h�Ɠ��������ꍇ
			{
				if (m_atk_cnt == 0)	//0�̎��̂݁A�e�_���[�W���󂯂�
				{
					if (hit->CheckObjNameHit(OBJ_PODP) != nullptr)			//�G�̃p���[�|�b�h�����莞��HP
					{
						//m_Player_damage *= m_One_pat_dem;//�����p�^�[���f�����b�g�l�̏�Z���s��

						m_podhp -= m_Player_damage * damage_buff[1] * 1.2f * m_One_pat_dem;
					}
					else if (hit->CheckObjNameHit(OBJ_PODD) != nullptr)		//�G�̃f�B�t�F���X�|�b�h�����莞��HP
					{
						//m_Player_damage *= m_One_pat_dem;//�����p�^�[���f�����b�g�l�̏�Z���s��

						m_podhp -= m_Player_damage * damage_buff[1] * 0.8f * m_One_pat_dem;
					}
					else if (hit->CheckObjNameHit(OBJ_PODS) != nullptr)		//�G�̃X�s�[�h�|�b�h�����莞��HP
					{
						//m_Player_damage *= m_One_pat_dem;//�����p�^�[���f�����b�g�l�̏�Z���s��

						m_podhp -= m_Player_damage * damage_buff[1] * m_One_pat_dem;
					}
					else if (hit->CheckObjNameHit(OBJ_PODB) != nullptr)	//�G�̃o�����X�|�b�h�����莞��HP
					{
						//m_Player_damage *= m_One_pat_dem;//�����p�^�[���f�����b�g�l�̏�Z���s��

						m_podhp -= m_Player_damage * damage_buff[1] * 1.1f * m_One_pat_dem;
					}
				}
				if (hit->CheckObjNameHit(OBJ_ROCKET) != nullptr)//�G�̃~�T�C���ɓ�����������HP����
				{
					//m_Player_damage = 3.0f;//�~�T�C���̎��͉Η�3�Œ�
					//m_Player_damage *= m_One_pat_dem;//�����p�^�[���f�����b�g�l�̏�Z���s��

					m_podhp -= (m_Player_damage + 1.0f) * m_One_pat_dem;
				}
			}
			else if (ButtonUP == 4)//�����̎�ނS(�o�����X)���G�̃|�b�h�ƃ~�T�C���ɓ��������ꍇ
			{
				if (m_atk_cnt == 0)	//0�̎��̂݁A�_���[�W���󂯂�
				{
					if (hit->CheckObjNameHit(OBJ_PODP) != nullptr)			//�G�̃p���[�|�b�h�����莞��HP
					{
						//m_Player_damage *= m_One_pat_dem;//�����p�^�[���f�����b�g�l�̏�Z���s��

						m_podhp -= m_Player_damage * damage_buff[1] * 0.9f * m_One_pat_dem;
					}
					else if (hit->CheckObjNameHit(OBJ_PODD) != nullptr)		//�G�̃f�B�t�F���X�|�b�h�����莞��HP
					{
						//m_Player_damage *= m_One_pat_dem;//�����p�^�[���f�����b�g�l�̏�Z���s��

						m_podhp -= m_Player_damage * damage_buff[1] * 0.9f * m_One_pat_dem;
					}
					else if (hit->CheckObjNameHit(OBJ_PODS) != nullptr)		//�G�̃X�s�[�h�|�b�h�����莞��HP
					{
						//m_Player_damage *= m_One_pat_dem;//�����p�^�[���f�����b�g�l�̏�Z���s��

						m_podhp -= m_Player_damage * damage_buff[1] * 0.9f * m_One_pat_dem;
					}
					else if (hit->CheckObjNameHit(OBJ_PODB) != nullptr)	//�G�̃o�����X�|�b�h�����莞��HP
					{
						//m_Player_damage *= m_One_pat_dem;//�����p�^�[���f�����b�g�l�̏�Z���s��

						m_podhp -= m_Player_damage * damage_buff[1] * m_One_pat_dem;
					}
				}
				if (hit->CheckObjNameHit(OBJ_ROCKET) != nullptr)//�G�̃~�T�C���ɓ�����������HP����
				{
					//m_Player_damage = 3.0f;//�~�T�C���̎��͉Η�3�Œ�

					//m_Player_damage *= m_One_pat_dem;//�����p�^�[���f�����b�g�l�̏�Z���s��
					
					m_podhp -= (m_pod_max_hp * 0.85) * m_One_pat_dem;//�ő�HP*0.85�{�̃_���[�W��^����
				}
			}
			else if (ButtonUP == 5)//�����̎�ނT(�~�T�C��)���G�̃|�b�h�ƃ~�T�C���ɓ��������ꍇ
			{
				m_del = true;				//���ŏ����t���OON
				Audio::Start(5);
			}
			
		}
		else if (m_type == 0 && m_stop_cnt == 10) {	//�������A�~�܂��Ă鎞
			m_fight = false;
			m_stop_cnt = 0;
		
		}


		if (m_podhp <= 0)//���|�b�hHP�ł̍폜
		{
			m_del = true;
		}
	}

	
}

//�h���[
void CObjRocket::Draw()
{
	//�`��J���[���  R=RED  G=Green  B=Blue A=alpha(���ߏ��)
	float d[4] =	{ 1.0f, 1.0f, 1.0f, 1.0f }; //���̐F
	float r[4] =	{ 1.0f, 0.0f, 0.0f, 1.0f }; //��
	float g[4] =	{ 0.0f, 1.0f, 0.0f, 1.0f }; //��
	float b[4] =	{ 0.0f, 0.2f, 2.0f, 1.0f }; //��
	float black[4]=	{ 0.0f, 0.0f, 0.0f, 1.0f };	//��(HP�Q�[�W�ő�l�Ŏg�p)
	float c[4] =	{ 1.0f,1.0f,1.0f,m_a };


	RECT_F src;//�؂���ʒu
	RECT_F dst;//�\���ʒu
	if (m_ani < 10) {		//���e�A�j���[�V�����̓r���܂ŕ`��
		if (m_type == 0)
		{
			if (m_stop_f == false /*&& m_pstop == false*/)
			{
				switch (m_get_line) {
				case 0:m_r += 0.08 + m_mov_spd * 2; break;//�~�T�C���p�x���Z
				case 2:m_r -= 0.08 + m_mov_spd * 2; break;
				}
			}

			if (ButtonUP >= 1 && ButtonUP <= 4)
			{
				//�|�b�h�̕`����
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = -64.0f;
				src.m_bottom = 64.0f;

				dst.m_top = m_y + m_size;
				dst.m_left = m_x;
				dst.m_right = m_x + m_size;
				dst.m_bottom = m_y;
			}
			else
			{
				//�~�T�C���̕`����
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 64.0f;
				src.m_bottom = 64.0f;

				dst.m_top = m_y;
				dst.m_left = m_x;
				dst.m_right = m_x + m_size;
				dst.m_bottom = m_y + m_size;
			}

			//-----------�{�^���ԁE�E�΂𕪂��锻��



			switch (ButtonUP) {
			case 1:
				if (m_get_line == 1) { Draw::Draw(65 + (g_Pod_equip_Level - 1), &src, &dst, d, m_r - 180); }//�ԐF�|�b�h��
				else if (m_get_line == 2) { Draw::Draw(65 + (g_Pod_equip_Level - 1), &src, &dst, d, m_r - 160); }//�e���C���̊p�x����
				else { Draw::Draw(65 + (g_Pod_equip_Level - 1), &src, &dst, d, m_r - 200); }
				break;
			case 2:
				if (m_get_line == 1) { Draw::Draw(68 + (g_Pod_equip_Level - 1), &src, &dst, d, m_r - 180); }//�F�|�b�h��
				else if (m_get_line == 2) { Draw::Draw(68 + (g_Pod_equip_Level - 1), &src, &dst, d, m_r - 160); }//�e���C���̊p�x����
				else { Draw::Draw(68 + (g_Pod_equip_Level - 1), &src, &dst, d, m_r - 200); }
				break;
			case 3:
				if (m_get_line == 1) { Draw::Draw(71 + (g_Pod_equip_Level - 1), &src, &dst, d, m_r - 180); }//�ΐF�|�b�h��
				else if (m_get_line == 2) { Draw::Draw(71 + (g_Pod_equip_Level - 1), &src, &dst, d, m_r - 160); }//�e���C���̊p�x����
				else { Draw::Draw(71 + (g_Pod_equip_Level - 1), &src, &dst, d, m_r - 200); }
				break;
			case 4:
				if (m_get_line == 1) { Draw::Draw(74 + (g_Pod_equip_Level - 1), &src, &dst, d, m_r - 180); }//���F�|�b�h��
				else if (m_get_line == 2) { Draw::Draw(74 + (g_Pod_equip_Level - 1), &src, &dst, d, m_r - 160); }//�e���C���̊p�x����
				else { Draw::Draw(74 + (g_Pod_equip_Level - 1), &src, &dst, d, m_r - 200); }
				break;
			case 5:
				if (m_get_line == 1) { Draw::Draw(17, &src, &dst, d, m_r + 45); }//�~�T�C����
				else if (m_get_line == 2) { Draw::Draw(17, &src, &dst, d, m_r + 65); }//�e���C���̊p�x����
				else { Draw::Draw(17, &src, &dst, d, m_r + 25); }
				//else if ();
				break;
			}
			//Draw::Draw(10, &src, &dst, d, m_r - 15);
		}

		if (m_type != 0)
		{
			if (m_stop_f == false/* && m_pstop == false*/)
			{
				switch (m_get_line) {
				case 0:m_r -= 0.08 + m_mov_spd * 2; break;//�~�T�C���p�x���Z
				case 2:m_r += 0.08 + m_mov_spd * 2; break;
				case 3:m_r -= 0.08 + m_mov_spd * 2; break;
				}
			}

			//�G�|�b�h��1�`4�̔ԍ�(�|�b�h)�̕`����
			if (ButtonUE >= 1 && ButtonUE <= 4)
			{
				//�|�b�h�̕`����
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = -64.0f;
				src.m_bottom = 64.0f;

				dst.m_top = m_y;
				dst.m_left = m_x;
				dst.m_right = m_x + m_size;
				dst.m_bottom = m_y + m_size;
			}
			else  //------------�G�~�T�C���̕`��p
			{
				//�~�T�C���̕`����
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 64.0f;
				src.m_bottom = 64.0f;

				dst.m_top = m_y;
				dst.m_left = m_x;
				dst.m_right = m_x + m_size;
				dst.m_bottom = m_y + m_size;
			}

			switch (ButtonUE) {
			case 1://---------�����_���̏��1�Ȃ�
				if (m_get_line == 1) { Draw::Draw(65 + (m_Enemy_Pod_Level - 1), &src, &dst, d, m_r); }//�ԐF�|�b�h��
				else if (m_get_line == 2) { Draw::Draw(65 + (m_Enemy_Pod_Level - 1), &src, &dst, d, m_r - 20); }//�e���C���̊p�x����
				else { Draw::Draw(65 + (m_Enemy_Pod_Level - 1), &src, &dst, d, m_r + 20); }
				break;
			case 2://---------�����_���̏��2�Ȃ�
				if (m_get_line == 1) { Draw::Draw(68 + (m_Enemy_Pod_Level - 1), &src, &dst, d, m_r); }//�F�|�b�h��
				else if (m_get_line == 2) { Draw::Draw(68 + (m_Enemy_Pod_Level - 1), &src, &dst, d, m_r - 20); }//�e���C���̊p�x����
				else { Draw::Draw(68 + (m_Enemy_Pod_Level - 1), &src, &dst, d, m_r + 20); }
				break;
			case 3://---------�����_���̏��3�Ȃ�
				if (m_get_line == 1) { Draw::Draw(71 + (m_Enemy_Pod_Level - 1), &src, &dst, d, m_r); }//�ΐF�|�b�h��
				else if (m_get_line == 2) { Draw::Draw(71 + (m_Enemy_Pod_Level - 1), &src, &dst, d, m_r - 20); }//�e���C���̊p�x����
				else { Draw::Draw(71 + (m_Enemy_Pod_Level - 1), &src, &dst, d, m_r + 20); }
				break;
			case 4://---------�����_���̏��4�Ȃ�
				if (m_get_line == 1) { Draw::Draw(74 + (m_Enemy_Pod_Level - 1), &src, &dst, d, m_r); }//���F�|�b�h��
				else if (m_get_line == 2) { Draw::Draw(74 + (m_Enemy_Pod_Level - 1), &src, &dst, d, m_r - 20); }//�e���C���̊p�x����
				else { Draw::Draw(74 + (m_Enemy_Pod_Level - 1), &src, &dst, d, m_r + 20); }
				break;
			case 5://---------�����_���̏��5�Ȃ�
				if (m_get_line == 1) { Draw::Draw(17, &src, &dst, d, m_r - 135); }//�e���C���̊p�x����
				else if (m_get_line == 2) { Draw::Draw(17, &src, &dst, d, m_r - 155); }//�~�T�C����
				else { Draw::Draw(17, &src, &dst, d, m_r - 115); }
				break;
			}
		}
	}
	//HP�Q�[�W�\��(�~�T�C���ȊO���j�󂳂�Ă��Ȃ����ɕ\�������)
	if (ButtonU != 5 && m_del == false)
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 128.0f;
		src.m_bottom = 10.0f;

		dst.m_top = m_y + m_size;
		dst.m_left = m_x;
		dst.m_bottom = m_y + m_size + 5.0f;

		//���ő�l�\��
		dst.m_right = m_x + m_size;
		Draw::Draw(32, &src, &dst, black, 0.0f);

		//�����ݒl�\��		
		dst.m_right = m_x + (m_size * ((float)m_podhp / (float)m_pod_max_hp));
		Draw::Draw(32, &src, &dst, g, 0.0f);
	}
	

	//�����G�t�F�N�g
	if (m_del == 1)
	{
		dst.m_top = -48.0f + m_y;
		dst.m_left = -48.0f + m_x;
		dst.m_right = 80.0f + m_x;
		dst.m_bottom = 80.0f + m_y;
		Draw::Draw(16, &m_eff, &dst, c, 0.0f);
	}

	//�GPOD�̗̑͂�HP��\������(�f�o�b�O�p)
	//wchar_t test_mou[256];
	//if (m_type != 0)
	//{
	//	swprintf_s(test_mou, L"HP%d,�U��%d", m_podhp, m_Player_damage);
	//	Font::StrDraw(test_mou, 20.0f, 20.0f, 12.0f, d);
	//}
	//else
	//{
	//	swprintf_s(test_mou, L"HP%d,�U��%d", m_podhp, m_Enemy_damage);
	//	Font::StrDraw(test_mou, 1100.0f, 20.0f, 12.0f, d);
	//}
	
}
