//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjGameClear.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;

//�}�N��
#define INI_ALPHA (1.0f) //���ߓx(�A���t�@�l)�̏����l

////�R���X�g���N�^
//CObjTest::CObjTest(float x, float y)
//{
//	//�쐬���ɓn���ꂽ�l���A���W�̏����l�ɑ��
//	m_x = x;
//	m_y = y;
//}

//�C�j�V�����C�Y
void CObjGameClear::Init()
{
	m_mou_x = 0.0f;	//�}�E�XX���W
	m_mou_y = 0.0f; //�}�E�XY���W
	m_mou_r = false;//�E�N���b�N
	m_mou_l = false;//���N���b�N

	m_f = false;
	m_y_vec = 1.0;

	for (int i = 0; i < 100; i++)//�z��̏�����
		m_cy[i] = i * 80 + 700;	//�s�Ԃ̊Ԋu���󂯂�̂ƁA��ʂ�艺�ɂ���
	m_c_nam = 0;

	m_speed = 0;
	m_alpha = INI_ALPHA;
	m_right_alpha = 3.0f;

	m_flag = false;
	m_end_f = false;
}

//�A�N�V����
void CObjGameClear::Action()
{
	////�}�E�X�̈ʒu���擾
	//m_mou_x = (float)Input::GetPosX();
	//m_mou_y = (float)Input::GetPosY();
	//�}�E�X�̃{�^���̏��
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	//�������Ɉړ������鏈��
	for (int i = 0; i < 100; i++)
	{
		m_cy[i] -= m_y_vec + m_speed;
	}

	if (m_right_alpha >= 0.0f)
	{
		m_right_alpha -= 0.01f;
	}

	//�E�N���b�N�������Ă���ԁA�G���h���[���̗���鑬�x�������Ȃ�
	if (m_mou_r == true && m_end_f == false)
	{
		m_speed = 10;
		m_right_alpha -= 0.1f;//�E�N���b�N�������Ɠ��ߑ��x�������Ȃ�
	}
	else
	{
		m_speed = 0;
	}

	
	//���N���b�N�Ń^�C�g����ʂփV�[���ڍs
	if (m_flag == true)
	{
		m_alpha -= 0.01f;

		if (m_alpha <= 0.0f)
		{
			Scene::SetScene(new CSceneTitle());//�^�C�g����ʂփV�[���ڍs
		}

		return;
	}
	//���N���b�N�ƃG���h�t���O��true�ɂȂ�����
	else if (m_mou_l == true && m_end_f == true)
	{
		m_flag = true;

		//�I����
		Audio::Start(1);
	}

	//23�ԖڃX�N���[���ɓo�^���ꂽ�摜���������ɗ���Ă�����
	if (m_cy[23] <= 0.0f)
	{
		m_y_vec = 0;	//�X�N���[�����~�߂�
		m_end_f = true;
	}
}
//�h���[
void CObjGameClear::Draw()
{
	//�`��J���[���  R=RED  G=Green  B=Blue A=alpha(���ߏ��)
	float d[4] = { 0.0f,0.0f, 0.0f, 1.0f };

	//�摜�p[�V�[���ڍs���t�F�[�h�A�E�g]
	float w[4] = { 1.0f,1.0f, 1.0f, m_alpha };

	//�摜�p[�V�[���ڍs���t�F�[�h�A�E�g]
	float w2[4] = { 1.0f,1.0f, 1.0f, m_right_alpha };

	//�����̐F(��)
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//�؂���ʒu
	RECT_F dst;//�\���ʒu
	
	src.m_top   =  0.0f;
	src.m_left  =  0.0f;
	src.m_right =100.0f;
	src.m_bottom=100.0f;
	
	dst.m_top   =  0.0f;
	dst.m_left  =  0.0f;
	dst.m_right =1200.0f;
	dst.m_bottom= 700.0f;

	//0�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
	Draw::Draw(0, &src, &dst, d, 0.0f);

	//�^�C�g�����S�`��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1557.0f;
	src.m_bottom = 929.0f;

	dst.m_top = 0.0f + m_cy[24];
	dst.m_left = 300.0f;
	dst.m_right = 851.0f;
	dst.m_bottom = 350.0f + m_cy[24];
	Draw::Draw(1, &src, &dst, w, m_alpha);

	Font::StrDraw(L"�E�N���b�N�������������", 0, 0, 20, w2);
	Font::StrDraw(L"�G���h���[������������܂��B", 0,25, 20, w2);

	Font::StrDraw(L"�g�p�������y�A���ʉ��T�C�g", 260, m_cy[0], 50, c);

	Font::StrDraw(L"���l",	550, m_cy[2], 45, c);
	Font::StrDraw(L"https://on-jin.com/",375, m_cy[3]-20, 45, c);

	Font::StrDraw(L"������",525, m_cy[4]+20, 45, c);
	Font::StrDraw(L"https://m aoudam ashii.jokersounds.com/",	160, m_cy[5], 45, c);

	Font::StrDraw(L"TA M M usic Factory",380, m_cy[6] + 20, 45, c);
	Font::StrDraw(L"https://w w w.tam - music.com/",300, m_cy[7], 45, c);

	Font::StrDraw(L"DOVA-SYN DROME", 450,m_cy[8] + 20, 45, c);
	Font::StrDraw(L"https://dova-s.jp/",400, m_cy[9], 45, c);

	Font::StrDraw(L"�������ʉ��ŗV�ڂ�",400, m_cy[10] + 20, 45, c);
	Font::StrDraw(L"https://taira-ko m ori.jpn.org/in dex.htm l",160, m_cy[11], 45, c);

	Font::StrDraw(L"���ʉ����{",480, m_cy[12] + 20, 45, c);
	Font::StrDraw(L"https://soun deffect-lab.info/",300, m_cy[13], 45, c);

	Font::StrDraw(L"OtoLogic",500, m_cy[14] + 20, 45, c);
	Font::StrDraw(L"https://otologic.jp/",380, m_cy[15], 45, c);

	Font::StrDraw(L"End", 550, m_cy[20] , 60, c);

	//�G���h�t���O��true�ɂȂ�����
	if (m_end_f == true)
	{
		Font::StrDraw(L"�N���b�N�Ń^�C�g���ɖ߂�", 250, 600, 60, w);
	}
}
