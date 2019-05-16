//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"
#include "ObjFightClear.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjFightClear::CObjFightClear(int p, int m, int s, int l)
{
	//�쐬���ɓn���ꂽ�l����
	m_people = p;
	m_mrl = m;
	m_skill = s;
	m_large = l;
}

//�C�j�V�����C�Y
void CObjFightClear::Init()
{
	//m_mou_x = 0.0f;	//�}�E�XX���W
	//m_mou_y = 0.0f; //�}�E�XY���W
	//m_mou_r = false;//�E�N���b�N
	m_mou_l = false;//���N���b�N

	m_a = 0.0f;
	m_a_vec = 0.0f;
	m_a_f = false;

	m_cnt = 3 * 60;	//3�b�J�E���g
}

//�A�N�V����
void CObjFightClear::Action()
{
	////�}�E�X�̈ʒu���擾
	//m_mou_x = (float)Input::GetPosX();
	//m_mou_y = (float)Input::GetPosY();
	////�}�E�X�̃{�^���̏��
	//m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	if (m_cnt == 0) {							//�J�E���g�I����
		if (m_mou_l == true)					//�N���b�N�����ꍇ
			Scene::SetScene(new CSceneHome());	//�V�[���ڍs
		m_a_f = true;			//�t���O�L��
	}
	else
		m_cnt--;	//0�łȂ��ꍇ�J�E���g�_�E��

	if (m_a_f == true)			//�t���O�L���̏ꍇ
		if (m_a <= 0.5)						//0.5�Ő؂�ւ�
			m_a_vec += 0.003f;	//�x�N�g���ɉ��Z
		else
			m_a_vec -= 0.003f;	//�x�N�g���Ɍ��Z

	m_a += m_a_vec;	//�x�N�g���𔽉f
}

//�h���[
void CObjFightClear::Draw()
{
	//�`��J���[���  R=RED  G=Green  B=Blue A=alpha(���ߏ��)
	float d[4] = { 1.0f,1.0f, 1.0f, 1.0f };//�摜�̐F

	RECT_F src;//�؂���ʒu
	RECT_F dst;//�\���ʒu
	
	src.m_top   =  0.0f;
	src.m_left  =  0.0f;
	src.m_right =100.0f;
	src.m_bottom=100.0f;
	
	dst.m_top   =  50.0f;
	dst.m_left  = 650.0f;
	dst.m_right =1100.0f;
	dst.m_bottom= 600.0f;
	//0�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
	Draw::Draw(2, &src, &dst, d, 0.0f);

	float c0[4] = { 1.0f,1.0f,1.0f,m_a };//char�̐F
	Font::StrDraw(L"�N���b�N�Ńz�[�����", 350, 600, 50, c0);

	float c[4] = { 0.0f,0.0f,0.0f,1.0f };//char�̐F
	Font::StrDraw(L"�Z��", 700, 100, 50, c);

	Font::StrDraw(L"����", 700, 250, 50, c);

	Font::StrDraw(L"�Z", 700, 400, 50, c);

	//Font::StrDraw(L"�傫��", 0, 300, 32, c);

	wchar_t str[256];
	swprintf_s(str, L"�{%d�l",m_people);		//�Z��
	Font::StrDraw(str, 900, 100, 50, c);

	swprintf_s(str, L"�{%d��", m_mrl);			//����
	Font::StrDraw(str, 900, 250, 50, c);

	switch (m_skill)						 //�X�y�V�����Z
	{
	case 0:Font::StrDraw(L"�Z", 700, 400, 50, c); break;
	}		
	
	
}
