//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjFightClear.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�O���[�o���ϐ��̒�`
int g_Iron_num = 0;
int g_Wood_num = 0;
int g_Silver_num = 0;
int g_Plastic_num = 0;
int g_Aluminum_num = 0;
int g_gus_num = 0;
int g_Raremetal_num = 0;


//�R���X�g���N�^
CObjFightClear::CObjFightClear(int p, int m, int l, int s)
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

	m_cnt_max = 2 * 60;	//2�b
	m_cnt = m_cnt_max;	//�ő�l�����Ă���

	m_Stage_Clear_f = false;	//�X�e�[�W�N���A�t���O
	m_Game_Clear_f = false;		//�Q�[���@�N���A�t���O

	m_page_nam = 0;				//�y�[�W��0

	if (g_Stage_progress == 1 &&		//1�X�e�[�W�N���A�����ꍇ
		g_destroy_progress[0] == true &&	
		g_destroy_progress[1] == true &&
		g_destroy_progress[2] == true &&
		g_destroy_progress[3] == true)	
	{
		g_Stage_progress += 1;	//�X�e�[�W��i�߂�
		for (int i = 0; i < 4; i++)	
			g_destroy_progress[i] = false;
	}		//�G�̌��j��Ԃ����ׂĖ߂�

	g_Remain_num += m_people;	//�擾�Z�������Z

	if (m_skill != 0)				//�X�L���擾���Ă���ꍇ
	{							//���̔ԍ����擾����
		g_Special_mastering[m_skill] = true;
	}
	else { ; }

	if (m_mrl == 0)
	{
		g_Wood_num += 40;
	}
	else if (m_mrl == 1)
	{
		g_Wood_num += 80;
	}
	else if (m_mrl == 2)
	{
		g_Iron_num += 40;
	}

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

	if (m_cnt == 0) 
	{											//�J�E���g�I����
		m_a_f = true;			//�t���O�L��
		if (m_mou_l == true)					//�N���b�N�����ꍇ
		{
			if (m_Game_Clear_f == false)
			{
				
				if(g_Stage_progress == 1)
					Scene::SetScene(new CSceneHome());	//�V�[���ڍs
				else
					m_Game_Clear_f = true;

				//�퓬���y��j�����������y�Đ�
				Audio::Stop(0);
				Audio::Start(1);
			}
			else
			{
				m_page_nam++;		//�y�[�W����i�߂�
				m_cnt = m_cnt_max;	//�J�E���g��MAX�ɂ���
				m_a_f = false;
			}
		}
	}
	else
		m_cnt--;	//0�łȂ��ꍇ�J�E���g�_�E��

	if (m_a_f == true)				//�t���O�L���̏ꍇ
		if (m_a <= 0.5)					//0.5�Ő؂�ւ��āA�N���b�N������alpha����
			m_a_vec += 0.003f;	//�x�N�g���ɉ��Z
		else
			m_a_vec -= 0.003f;	//�x�N�g���Ɍ��Z
	else
	{								//�t���O�����̏ꍇ
		m_a = 0;		//alpha = 0
		m_a_vec = 0;	//	vec = 0
	}

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
	
	if (m_Game_Clear_f == false)
	{
		dst.m_top    =  50.0f;
		dst.m_left   = 650.0f;
		dst.m_right  =1100.0f;
		dst.m_bottom = 600.0f;
		//0�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
		Draw::Draw(2, &src, &dst, d, 0.0f);

		float c0[4] = { 1.0f,1.0f,1.0f,m_a };//char�̐F
		Font::StrDraw(L"�N���b�N�Ńz�[�����", 350, 600, 50, c0);

		float c[4] = { 0.0f,0.0f,0.0f,1.0f };//char�̐F
		Font::StrDraw(L"�Z���@�{",	700, 100, 50, c);

		Font::StrDraw(L"���ށ@�{",	700, 200, 50, c);

		Font::StrDraw(L"�T�C�Y�@�{",700, 300, 50, c);

		if (m_skill != 0)
		{
			Font::StrDraw(L"�Z�@�{",700, 400, 50, c);
		}
		else { ; }
		//Font::StrDraw(L"�傫��", 0, 300, 32, c);

		wchar_t str[256];
		swprintf_s(str, L"�@ %d�l", m_people);		//�Z��
		Font::StrDraw(str, 900, 100, 50, c);

		switch (m_mrl)
		{
		case 0:Font::StrDraw(L"�@ ��40", 900, 200, 50, c); break;
		case 1:Font::StrDraw(L"�@ ��80", 900, 200, 50, c); break;
		case 2:Font::StrDraw(L"�@ �S40", 900, 200, 50, c); break;
		case 3:Font::StrDraw(L"�@ �S40", 900, 200, 50, c); break;
		case 4:Font::StrDraw(L"   ��60", 900, 175, 50, c);
			Font::StrDraw(L"   �S60", 900, 225, 50, c);
			break;
		}

		swprintf_s(str, L"�@ %d", m_large);		//�傫��
		Font::StrDraw(str, 900, 300, 50, c);

		switch (m_skill)						 //�X�y�V�����Z
		{
		case 0: break;
		case 1:Font::StrDraw(L"�@ Explosion",			800, 410, 40, c); break;
		case 2:Font::StrDraw(L"�@ Fracture Ray",		800, 410, 40, c); break;
		case 3:Font::StrDraw(L"�@ Immortality",			800, 410, 40, c); break;
		case 4:Font::StrDraw(L"�@ ���~�b�g�u���C�N",	800, 410, 40, c); break;
		case 5:Font::StrDraw(L"�@ �X�e���C�h���^",		800, 410, 40, c); break;
		}
	}
	else
	{
		if(m_page_nam == 1)
		{
			dst.m_top    =  50.0f;
			dst.m_left   = 200.0f;
			dst.m_right  =1000.0f;
			dst.m_bottom = 250.0f;

			//0�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
			Draw::Draw(2, &src, &dst, d, 0.0f);

			float c[4] = { 0.0f,0.0f,0.0f,1.0f };//char�̐F
			Font::StrDraw(L"���ׂĂ̘f����ߐH����",	 300,  80, 50, c);
			//Font::StrDraw(L"���̋�͂̃g�b�v�ɌN�Ղ���", 250, 180, 50, c);
		}
		else if(m_page_nam == 2)
		{
			dst.m_top    =  50.0f;
			dst.m_left   = 200.0f;
			dst.m_right  =1000.0f;
			dst.m_bottom = 250.0f;

			//0�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
			Draw::Draw(2, &src, &dst, d, 0.0f);

			float c[4] = { 0.0f,0.0f,0.0f,1.0f };//char�̐F
			Font::StrDraw(L"���ׂĂ̘f����ߐH����",	 300,  80, 50, c);
			Font::StrDraw(L"���̋�͂̃g�b�v�ɌN�Ղ���", 250, 180, 50, c);
		}
		else if(m_page_nam == 3)
		{
			Scene::SetScene(new CSceneGameClear());	//�V�[���ڍs
		}

		float c0[4] = { 1.0f,1.0f,1.0f,m_a };//char�̐F
		Font::StrDraw(L"�N���b�N�Ői�߂�", 350, 600, 50, c0);
	}
	
}
