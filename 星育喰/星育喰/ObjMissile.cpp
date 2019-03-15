//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjMissile.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjMissile::CObjMissile(float x, float y)
{
	//�쐬���ɓn���ꂽ�l���A���W�̏����l�ɑ��
	m_x = x;
	m_y = y;
}

//�C�j�V�����C�Y
void CObjMissile::Init()
{
	m_size = 50.0f;//�T�C�Y
	
	m_vx = 0.0f;//�x�N�g��
	m_vy = 0.0f;
	
	m_mou_x = 0.0f;	//�}�E�X���
	m_mou_y = 0.0f;
	m_mou_r = false;
	m_mou_l = false;
	
	m_get_line = 0;//���C���擾�p

	m_mou_f = false;//�}�E�X�t���O

	//�����蔻��pHitBox�쐬
	Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_BLUE, OBJ_MISSILE, 1);
}

//�A�N�V����
void CObjMissile::Action()
{
	m_vx = 0.0f;//�x�N�g��������
	m_vy = 0.0f;

	//�}�E�X�̈ʒu���擾
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//�}�E�X�̃{�^���̏��
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	if (m_mou_l == false)
	{
		m_mou_f = true;
	}
	else
	{
		m_mou_f = false;
	}

	CObjFight* obj = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
	if (obj != nullptr) {					//��񂪎擾�o���Ă�����
		m_get_line = obj->GetLine();		//���C���i���o�[���擾
	}

	if (m_get_line == 0)
	{

	}
	else if (m_get_line == 1)
	{

	}
	else//if(m_get_line == 2)
	{

	}

	//���W�X�V
	m_x += m_vx;
	m_y += m_vy;

	CHitBox* hit = Hits::GetHitBox(this);	//CHitBox�|�C���^�擾
	hit->SetPos(m_x, m_y, m_size, m_size);	//�ʒu���X�V
}

//�h���[
void CObjMissile::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	Font::StrDraw(L"", 230, 250, 32, c);
	
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

	//2�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
	Draw::Draw(2, &src, &dst, d, 0.0f);
}