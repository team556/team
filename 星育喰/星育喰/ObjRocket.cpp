//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"


#include "GameHead.h"
#include "UtilityModule.h"
#include "ObjRocket.h"

#include <time.h>

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjRocket::CObjRocket(float x, float y, bool type,int n)
{
	m_x = x;
	m_y = y;
	m_type = type;
	ButtonU = n;

}

//�C�j�V�����C�Y
void CObjRocket::Init()
{
	CObjPlanet* pla = (CObjPlanet*)Objs::GetObj(OBJ_PLANET);

	if (m_type == true) {
		CObjFight* obj = (CObjFight*)Objs::GetObj(OBJ_FIGHT);

		if (obj != nullptr) {					//��񂪎擾�o���Ă�����
			m_get_line = obj->GetLine();		//���C���i���o�[���擾
			if (m_get_line == 1) { m_y = 310; }	//�擾�i���o�[�ō����ύX
			else if (m_get_line == 2) { m_y = 420; }

			m_get_cnt = obj->GetCount();		//�J�E���g���擾
			//m_x += obj->GetCount() / 10;
			m_x += 0.0f;
			m_mov_spd = 1.0f / pla->GetX();
		}
	}
	else {
		CObjFight* obj = (CObjFight*)Objs::GetObj(OBJ_FIGHT);

		srand(time(NULL));
		m_get_line = rand() % 3 + 1;
		if (m_get_line == 1) { m_y = 310; }	//�擾�i���o�[�ō����ύX
		else if (m_get_line == 2) { m_y = 420; }

		m_get_cnt = obj->GetCount();		//�J�E���g���擾
		m_mov_spd = 1.0f / pla->GetX();

		srand(time(NULL));
		//�G�̃|�b�h�̔ԍ��������_���ɂ��鏈��
		Enemypod = rand() % 5 + 1;	
	}

	m_size = 50.0f;//�T�C�Y
	
	m_time = 100;

	m_Enemy_Pod_Level = 1;

	m_vx = 0.0f;//�x�N�g��
	m_vy = 0.0f;
	m_mov = 0;
	
	m_r = 0.0f;

	m_mou_x = 0.0f;	//�}�E�X���
	m_mou_y = 0.0f;
	m_mou_r = false;
	m_mou_l = false;
	
	m_mou_f = false;//�}�E�X�t���O

	//�����蔻��pHitBox�쐬
	if (m_type == true) 
	{
		m_x += 100;
		if (ButtonU == 1)
		{
			Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD, OBJ_PODP, 1);
		}
		else if (ButtonU == 2)
		{
			Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD, OBJ_PODS, 1);
		}
		else if (ButtonU == 3)
		{
			Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD, OBJ_PODD, 1);
		}
		else if (ButtonU == 4)
		{
			Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD, OBJ_PODB, 1);
		}
		else if (ButtonU == 5)
		{
			Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD, OBJ_Rocket, 1);
		}

	}
	else 
	{
		m_x -= 100;
		if (ButtonU == 1)
		{
			Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_ENEMYPOD, OBJ_PODP, 1);
		}
		else if (ButtonU == 2)
		{
			Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_ENEMYPOD, OBJ_PODS, 1);
		}
		else if (ButtonU == 3)
		{
			Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_ENEMYPOD, OBJ_PODD, 1);
		}
		else if (ButtonU == 4)
		{
			Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_ENEMYPOD, OBJ_PODB, 1);
		}
		else if (ButtonU == 5)
		{
			Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_ENEMYPOD, OBJ_Rocket, 1);
		}

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

	m_podhp = 10;

	m_hp_cnt = 0;		//���G�^�C��
	m_hp_f = false;		//���G�t���O
}

//�A�N�V����
void CObjRocket::Action()
{
	m_vx = 0.0f;//�x�N�g��������
	m_vy = 0.0f;

	CObjFight* obj = (CObjFight*)Objs::GetObj(OBJ_FIGHT);

	m_mov += m_mov_spd / 2;

	//�}�E�X�̈ʒu���擾
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//�}�E�X�̃{�^���̏��
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	if (obj->GetCount() <= 60)
		m_del = true;

	if (m_mou_l == false && m_mou_f == false)
	{
		m_mou_f = true;
	}
	else
	{
		m_mou_f = false;
	}


	//�����G�t�F�N�g�񐔏���
	if (m_del == true)
	{
		/*if (m_ani == 4)
		{
			m_ani = 0;
			m_ani_max++;
		}*/
	}
	else//�|�b�h���m��������Ɠ������~�ߏ��s�����߂鏈��
	{
		//�e���C�����̓�����
		if (m_get_line == 0 || m_get_line == 3)//------�ド�C��----
		{
			m_vx -= 0.3f;
			m_vy += (-0.15 + m_mov);
		}
		else if (m_get_line == 1)//---------------�����C��-----
		{
			m_vx -= 0.5f;
		}
		else//if(m_get_line == 2)---------------�����C��------
		{
			m_vx -= 0.3f;
			m_vy -= (-0.15 + m_mov);
		}

		//-----------------------���W�X�V
		if (m_type == true) {
			m_x += m_vx - m_mov_spd * 200;
			m_y += m_vy;
		}
		else {
			m_x -= m_vx - m_mov_spd * 200;
			m_y += m_vy;
		}
	}
	//-----------------------���W�X�V
	if (m_type == true) {
		m_x += m_vx;
		m_y += m_vy;
	}
	else {
		m_x -= m_vx;
		m_y += m_vy;
	}

	CHitBox* hit = Hits::GetHitBox(this);		//HitBox���擾
	hit->SetPos(m_x, m_y, m_size, m_size);		//HitBox�X�V

	

	//�����G�t�F�N�g
	m_eff = GetPodEffec(&m_ani, &m_ani_time, m_del, 10);	//�G�ƃv���C���[�̃|�b�h�������Ă���Ƃ�����
	
	//�|�b�h���ŏ���
	if (m_del == true)
	{
		if(m_bom != 5)	//�T�ȊO�̏ꍇ
			m_bom = Rand(0, 4);//�����_���Ȕ������N����
		if (m_ani == 4 && m_bom == 5)
		{
			this->SetStatus(false);
			Hits::DeleteHitBox(this);
		}
		if (m_ani == 4)
		{
			m_ani = 0;
			m_bom = 5;
		}
		
	}


	if (hit->CheckElementHit(ELEMENT_PLAYER) == true && m_type == false)//�f���ɓ��������������e
	{
		//�ʒu���X�V//�f���ƐڐG���Ă��邩�ǂ����𒲂ׂ�
		m_del = true;
		hit->SetInvincibility(true);
		
	}
	else if (hit->CheckElementHit(ELEMENT_ENEMY) == true && m_type == true)//�G�̘f���ɓ��������������e
	{
		//�ʒu���X�V//�f���ƐڐG���Ă��邩�ǂ����𒲂ׂ�
		m_del = true;
		hit->SetInvincibility(true);
		
	}

	



	//�G�̃|�b�h���v���C���[�̃|�b�h�ɂԂ��������̔���
	if (hit->CheckElementHit(ELEMENT_POD) == true)
	{
		if (ButtonU == 1)//�G�̎�ނP(�p���[)���v���C���[�̃|�b�h�Ɠ��������ꍇ
		{
			if (hit->CheckObjNameHit(OBJ_PODD) != nullptr)	//�v���C���[�̃f�B�t�F���X�|�b�h�����莞��HP
			{
				m_podhp -= 8;
			}
			else if (hit->CheckObjNameHit(OBJ_PODS) != nullptr)	//�v���C���[�̃X�s�[�h�|�b�h�����莞��HP
			{
				m_podhp -= 12;
			}
			else											//�v���C���[�̃p���[�|�b�h�A�o�����X�|�b�h�A�~�T�C�������莞��HP
			{
				m_podhp -= 10;
			}
		}
		else if (ButtonU == 2)//�G�̎�ނQ(�X�s�[�h)���v���C���[�̃|�b�h�Ɠ��������ꍇ
		{
			if (hit->CheckObjNameHit(OBJ_PODP) != nullptr)	//�v���C���[�̃p���[�|�b�h�����莞��HP
			{
				m_podhp -= 8;
			}
			else if (hit->CheckObjNameHit(OBJ_PODD) != nullptr)	//�v���C���[�̃f�B�t�F���X�|�b�h�����莞��HP
			{
				m_podhp -= 12;
			}
			else											//�v���C���[�̃X�s�[�h�|�b�h�A�o�����X�|�b�h�A�~�T�C�������莞��HP
			{
				m_podhp -= 10;
			}
		}
		else if (ButtonU == 3)//�G�̎�ނR(�f�B�t�F���X)���v���C���[�̃|�b�h�Ɠ��������ꍇ
		{
			if (hit->CheckObjNameHit(OBJ_PODP) != nullptr)	//�v���C���[�̃p���[�|�b�h�����莞��HP
			{
				m_podhp -= 12;
			}
			else if (hit->CheckObjNameHit(OBJ_PODS) != nullptr)	//�v���C���[�̃X�s�[�h�|�b�h�����莞��HP
			{
				m_podhp -= 8;
			}
			else											//�v���C���[�̃f�B�t�F���X�|�b�h�A�o�����X�|�b�h�A�~�T�C���ɓ����莞��HP
			{
				m_podhp -= 10;
			}
		}
		else if (ButtonU == 4)//�G�̎�ނS(�o�����X)���v���C���[�̃|�b�h�ƃ~�T�C���ɓ��������ꍇ
		{
			m_podhp -= 10;
		}
		else if (ButtonU == 5)//�G�̎�ނT(�~�T�C��)���v���C���[�̃|�b�h�ɓ��������ꍇ
		{
			;
		}
	}

	//�v���C���[�̃|�b�h���G�̃|�b�h�ƂԂ��������̔���
	if (hit->CheckElementHit(ELEMENT_ENEMYPOD) == true)
	{
		if (ButtonU == 1)//�����̎�ނP(�p���[)���G�̃|�b�h�Ɠ��������ꍇ
		{
			if (hit->CheckObjNameHit(OBJ_PODD) != nullptr)	//�G�̃f�B�t�F���X�|�b�h�����莞��HP
			{
				m_podhp -= 8;
			}
			else if (hit->CheckObjNameHit(OBJ_PODS) != nullptr)	//�G�̃X�s�[�h�|�b�h�����莞��HP
			{
				m_podhp -= 12;
			}
			else											//�G�̃p���[�|�b�h�A�o�����X�|�b�h�A�~�T�C�������莞��HP
			{
				m_podhp -= 10;
			}
		}
		else if (ButtonU == 2)//�����̎�ނQ(�X�s�[�h)���G�̃|�b�h�Ɠ��������ꍇ
		{
			if (hit->CheckObjNameHit(OBJ_PODP) != nullptr)	//�G�̃p���[�|�b�h�����莞��HP
			{
				m_podhp -= 8;
			}
			else if (hit->CheckObjNameHit(OBJ_PODD) != nullptr)	//�G�̃f�B�t�F���X�|�b�h�����莞��HP
			{
				m_podhp -= 12;
			}
			else											//�G�̃X�s�[�h�|�b�h�A�o�����X�|�b�h�A�~�T�C�������莞��HP
			{
				m_podhp -= 10;
			}
		}
		else if (ButtonU == 3)//�����̎�ނR(�f�B�t�F���X)���G�̃|�b�h�Ɠ��������ꍇ
		{
			if (hit->CheckObjNameHit(OBJ_PODP) != nullptr)	//�G�̃p���[�|�b�h�����莞��HP
			{
				m_podhp -= 12;
			}
			else if (hit->CheckObjNameHit(OBJ_PODS) != nullptr)	//�G�̃X�s�[�h�|�b�h�����莞��HP
			{
				m_podhp -= 8;
			}
			else											//�G�̃f�B�t�F���X�|�b�h�A�o�����X�|�b�h�A�~�T�C�������莞��HP
			{
				m_podhp -= 10;
			}

		}
		else if (ButtonU == 4)//�����̎�ނS(�o�����X)���G�̃|�b�h�ƃ~�T�C���ɓ��������ꍇ
		{
			m_podhp -= 10;
		}
		else if (ButtonU == 5)//�����̎�ނT(�~�T�C��)���G�̃|�b�h�ƃ~�T�C���ɓ��������ꍇ
		{
			;
		}
	}
	
	if (m_podhp <= 0)//HP
	{
		m_del = true;
		hit->SetInvincibility(true);
	}
}

//�h���[
void CObjRocket::Draw()
{
	//�`��J���[���  R=RED  G=Green  B=Blue A=alpha(���ߏ��)
	float d[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; //���̐F
	float r[4] = { 1.0f, 0.0f, 0.0f, 1.0f }; //��
	float g[4] = { 0.0f, 1.0f, 0.0f, 1.0f }; //��
	float b[4] = { 0.0f, 0.2f, 2.0f, 1.0f }; //��
	float c[4] = { 1.0f,1.0f,1.0f,m_a };


	RECT_F src;//�؂���ʒu
	RECT_F dst;//�\���ʒu

	if (m_type == true) 
	{
		m_r += 0.05 + m_mov_spd * 2;
		if (ButtonU >= 1 && ButtonU <= 4)
		{
			//�|�b�h�̕`����
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 128.0f;
			src.m_bottom = 64.0f;

			dst.m_top = m_y;
			dst.m_left = m_x;
			dst.m_right = m_x + m_size;
			dst.m_bottom = m_y + m_size;
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
		

		switch (ButtonU) {
		case 1:
			Draw::Draw(8 + (g_Pod_equip_Level - 1), &src, &dst, r, m_r + 180);  //�ԃ|�b�h
			break;
		case 2:
			Draw::Draw(8 + (g_Pod_equip_Level - 1), &src, &dst, b, m_r + 180);  //�|�b�h
			break;
		case 3:
			Draw::Draw(8 + (g_Pod_equip_Level - 1), &src, &dst, g, m_r + 180);   //�΃|�b�h
			break;
		case 4:
			Draw::Draw(8 + (g_Pod_equip_Level - 1), &src, &dst, d, m_r + 180);   //�D�F�|�b�h
			break;
		case 5:
			Draw::Draw(17, &src, &dst, d, m_r + 35);   //�~�T�C��
			break;
		}
		//Draw::Draw(10, &src, &dst, d, m_r - 15);
	}

	if(m_type==false)
	{
		//�G�|�b�h��1�`4�̔ԍ�(�|�b�h)�̕`����
		if (ButtonU >= 1 && ButtonU <= 4)
		{
			//�|�b�h�̕`����
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 128.0f;
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

		if (m_type == false) { //-----------�G�̐ԁE�E�΂𕪂��锻��
			m_r += 0.05 + m_mov_spd * 2;

			switch (ButtonU) {
			case 1://---------�����_���̏��1�Ȃ�
				Draw::Draw(8 + (m_Enemy_Pod_Level - 1), &src, &dst, r, m_r);  //�ԃ|�b�h
				break;
			case 2://---------�����_���̏��2�Ȃ�
				Draw::Draw(8 + (m_Enemy_Pod_Level - 1), &src, &dst, b, m_r);  //�|�b�h
				break;
			case 3://---------�����_���̏��3�Ȃ�
				Draw::Draw(8 + (m_Enemy_Pod_Level - 1), &src, &dst, g, m_r);   //�΃|�b�h
				break;
			case 4://---------�����_���̏��4�Ȃ�
				Draw::Draw(8 + (m_Enemy_Pod_Level - 1), &src, &dst, d, m_r);   //�D�F�|�b�h
				break;
			case 5://---------�����_���̏��5�Ȃ�
				Draw::Draw(17, &src, &dst, d, m_r-145);   //�~�T�C��
				break;
			}
		}
	}

	//�G�t�F�N�g
	//���΂ߏ�
	if (m_bom== 0) 
	{
		dst.m_top = 0.0f + m_y;
		dst.m_left = 0.0f + m_x;
		dst.m_right = 32.0f + m_x;
		dst.m_bottom = 29.0f + m_y;
	}

	//�^��
	else if (m_bom == 1)
	{
		dst.m_top = 0.0f + m_y+10;
		dst.m_left = 0.0f + m_x+10;
		dst.m_right = 42.0f + m_x;
		dst.m_bottom = 39.0f + m_y;
	}

	//�E�΂ߏ�
	else if (m_bom == 2)
	{
		dst.m_top = 0.0f + m_y;
		dst.m_left = 32.0f + m_x;
		dst.m_right = 64.0f + m_x;
		dst.m_bottom = 29.0f + m_y;
	}

	//���΂߉�
	if (m_bom == 3)
	{
		dst.m_top = 29.0f + m_y;
		dst.m_left = 0.0f + m_x;
		dst.m_right = 32.0f + m_x;
		dst.m_bottom = 58.0f + m_y;
	}

	//�E�΂߉�
	if (m_bom == 4)
	{
		dst.m_top = 29.0f + m_y;
		dst.m_left = 32.0f + m_x;
		dst.m_right = 64.0f + m_x;
		dst.m_bottom = 58.0f + m_y;
	}
	//�傫�����
	if (m_bom == 5)
	{
		dst.m_top = 0.0f + m_y;
		dst.m_left = 0.0f + m_x;
		dst.m_right = 50.0f + m_x;
		dst.m_bottom = 50.0f + m_y;
	}

	
	if (m_del == true) 
		Draw::Draw(16, &m_eff, &dst, c, 180.0f);
	



}