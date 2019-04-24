//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"
#include "ObjFightClear.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

////�R���X�g���N�^
//CObjTest::CObjTest(float x, float y)
//{
//	//�쐬���ɓn���ꂽ�l���A���W�̏����l�ɑ��
//	m_x = x;
//	m_y = y;
//}

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

	m_people = 0;	//�Z��
	m_mrl = 0;		//�}�e���A���Y(����)
	m_skill = 0;	//�X�y�V�����Z

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
	float c[4] = { 1.0f,1.0f,1.0f,m_a };//char�̐F
	Font::StrDraw(L"�Z��", 0, 0, 32, c);

	Font::StrDraw(L"����", 0, 100, 32, c);

	Font::StrDraw(L"�Z", 0, 200, 32, c);

	//Font::StrDraw(L"�傫��", 0, 300, 32, c);

	wchar_t str[256];
	swprintf_s(str, L"�{%d�l",m_people);		//�Z��
	Font::StrDraw(str, 500, 60, 50, c);

	swprintf_s(str, L"�{%d��", m_mrl);			//����
	Font::StrDraw(str, 500, 60, 50, c);

	swprintf_s(str, L"Get %c", m_skill);		//�X�y�V�����Z
	Font::StrDraw(str, 500, 60, 50, c);
	
	//�`��J���[���  R=RED  G=Green  B=Blue A=alpha(���ߏ��)
	float d[4] = { 1.0f,1.0f, 1.0f, 0.3f };//�摜�̐F

	RECT_F src;//�؂���ʒu
	RECT_F dst;//�\���ʒu
	
	src.m_top   =  0.0f;
	src.m_left  =  0.0f;
	src.m_right =100.0f;
	src.m_bottom=100.0f;
	
	dst.m_top   =  0.0f;
	dst.m_left  =  0.0f;
	dst.m_right =400.0f;
	dst.m_bottom=300.0f;

	//0�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
	Draw::Draw(10, &src, &dst, d, 0.0f);
}
