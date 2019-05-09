//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"


#include "GameHead.h"
#include "UtilityModule.h"
#include "ObjMissile.h"

#include <time.h>

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjMissile::CObjMissile(float x, float y, bool type)
{
	m_x = x;
	m_y = y;
	m_type = type;
}

//�C�j�V�����C�Y
void CObjMissile::Init()
{
	if (m_type == true) {
		CObjFight* obj = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
		CObjPlanet * obj2 = (CObjPlanet*)Objs::GetObj(OBJ_PLANET);

		if (obj != nullptr) {					//��񂪎擾�o���Ă�����
			m_get_line = obj->GetLine();		//���C���i���o�[���擾
			if (m_get_line == 1) { m_y = 310; }	//�擾�i���o�[�ō����ύX
			else if (m_get_line == 2) { m_y = 420; }

			m_get_cnt = obj->GetCount();		//�J�E���g���擾
			//m_psize = obj2->GetSiz();			//�T�C�Y���擾
			//m_x +=obj2->GetX() - m_psize;
			m_x += obj->GetCount() / 10;
			m_mov_spd = 1.0f / obj->GetCount();
		}
	}
	else {
		CObjFight* obj = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
		CObjPlanet * obj2 = (CObjPlanet*)Objs::GetObj(OBJ_PLANET);

		srand(time(NULL));
		m_get_line = rand() % 3 + 1;
		if (m_get_line == 1) { m_y = 310; }	//�擾�i���o�[�ō����ύX
		else if (m_get_line == 2) { m_y = 420; }

		m_get_cnt = obj->GetCount();		//�J�E���g���擾
		m_x -= obj->GetCount() / 10;
		m_mov_spd = 1.0f / obj->GetCount();
	}

	m_size = 50.0f;//�T�C�Y
	
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
	if (m_type == false) {
		Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_RED, OBJ_MISSILE, 1);
		m_x -= 100;
	}
	else {
		Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_MAGIC, OBJ_MISSILE, 1);
		m_x += 100;
	}

}

//�A�N�V����
void CObjMissile::Action()
{
	m_vx = 0.0f;//�x�N�g��������
	m_vy = 0.0f;
	
	m_mov += m_mov_spd / 2;

	//�}�E�X�̈ʒu���擾
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//�}�E�X�̃{�^���̏��
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	if (m_mou_l == false && m_mou_f == false)
	{

		m_mou_f = true;
	}
	else
	{
		m_mou_f = false;
	}

	
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


	CHitBox* hit = Hits::GetHitBox(this);		//HitBox���擾
	hit->SetPos(m_x, m_y, m_size, m_size);		//HitBox�X�V

	if (m_type == true) {
		if (hit->CheckElementHit(ELEMENT_ENEMY) == true)
		{//�ʒu���X�V//�f���ƐڐG���Ă��邩�ǂ����𒲂ׂ�
			this->SetStatus(false);		//���������ꍇ�폜
			Hits::DeleteHitBox(this);
		}
	}
	else {
		if (hit->CheckElementHit(ELEMENT_PLAYER) == true)
		{//�ʒu���X�V//�f���ƐڐG���Ă��邩�ǂ����𒲂ׂ�
			this->SetStatus(false);		//���������ꍇ�폜
			Hits::DeleteHitBox(this);
		}
	}
}

//�h���[
void CObjMissile::Draw()
{
	//�`��J���[���  R=RED  G=Green  B=Blue A=alpha(���ߏ��)
	float d[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	RECT_F src;//�؂���ʒu
	RECT_F dst;//�\���ʒu
	
	src.m_top   =  0.0f;
	src.m_left  =  0.0f;
	src.m_right =100.0f;
	src.m_bottom=100.0f;
	
	dst.m_top   = m_y;
	dst.m_left  = m_x;
	dst.m_right = m_x + m_size;
	dst.m_bottom= m_y + m_size;
	
	if (m_type == true) {
		m_r += 0.05 + m_mov_spd * 2;
		Draw::Draw(2, &src, &dst, d, m_r - 15);
	}
	else {
		m_r -= 0.05 - m_mov_spd * 2;
		Draw::Draw(2, &src, &dst, d, m_r + 15);
	}
	
}