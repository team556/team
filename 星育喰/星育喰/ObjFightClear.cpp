//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�O���[�o���ϐ��̒�`
int g_Iron_num = 1000;
int g_Wood_num = 1000;
int g_Silver_num = 1000;
int g_Plastic_num = 1000;
int g_Aluminum_num = 1000;
int g_gus_num = 1000;
int g_Raremetal_num = 1000;

//�}�N��
#define INI_ALPHA (1.0f) //���̑����ߓx(�A���t�@�l)�̏����l

//�R���X�g���N�^
CObjFightClear::CObjFightClear(int people, int large, wchar_t Mat_nameA[20], int *Mat_typeA, int Mat_numA, int skill)
{
	//�쐬���ɓn���ꂽ�l����
	m_people = people;
	m_large = large;
	swprintf_s(m_mat_name[0], Mat_nameA);//�����z��ɕ����f�[�^������
	swprintf_s(m_mat_name[1], L"");		 //�����f�[�^���N���A����
	m_mat_type[0] = Mat_typeA;
	m_mat_type[1] = nullptr;
	m_mat_num[0] = Mat_numA;
	m_mat_num[1] = NULL;
	m_skill = skill;
}

CObjFightClear::CObjFightClear(int people, int large, wchar_t Mat_nameA[20], int *Mat_typeA, int Mat_numA, wchar_t Mat_nameB[20], int *Mat_typeB, int Mat_numB, int skill)
{
	//�쐬���ɓn���ꂽ�l����
	m_people = people;
	m_large = large;
	swprintf_s(m_mat_name[0], Mat_nameA);//�����z��ɕ����f�[�^������
	swprintf_s(m_mat_name[1], Mat_nameB);//�����z��ɕ����f�[�^������
	m_mat_type[0] = Mat_typeA;
	m_mat_type[1] = Mat_typeB;
	m_mat_num[0] = Mat_numA;
	m_mat_num[1] = Mat_numB;
	m_skill = skill;
}


//�C�j�V�����C�Y
void CObjFightClear::Init()
{
	//m_mou_x = 0.0f;	//�}�E�XX���W
	//m_mou_y = 0.0f; //�}�E�XY���W
	//m_mou_r = false;//�E�N���b�N
	m_mou_l = false;//���N���b�N

	m_click_a = 0.0f;
	m_click_a_vec = 0.0f;
	m_click_a_f = false;
	m_result_a = 0.0f;
	m_alpha = INI_ALPHA;

	m_cnt_max = 60 * 2;	//2�b
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

	//1�X�e�[�W�N���A��A�Q�[���N���A�t���O�𗧂Ă�B
	//���������e�I�ɂ̓X�e�[�W��i�߂���̒l���A
	//2�X�e�[�W�ȏ�ł������ꍇ�Ƃ����������ɂ��Ă���B
	if (g_Stage_progress >= 2)
	{
		m_Game_Clear_f = true;
	}

	//���l���������̂��O���[�o���ϐ��ɑ������
	g_Remain_num += m_people;		//�l���Z���������Z
	g_Player_max_size += m_large;	//�l���T�C�Y(HP)�������Z

	//�l�����ސ������Z
	for (int i = 0; i < 2; i++)
	{
		if (m_mat_type[i] != nullptr)
		{
			*m_mat_type[i] += m_mat_num[i];
		}
	}
	
	if (m_skill != 0)			//�X�L���擾���Ă���ꍇ
	{							//���̔ԍ����擾����
		g_Special_mastering[m_skill - 1] = true;
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


	//���J�E���g�I����̏���
	if (m_result_a >= 6.0f || m_click_a_f == true)
	{											
		m_click_a_f = true;			//�t���O�L��
		
		//���N���b�N�����ꍇ�A���s(��x�N���b�N����ƈȌ�A�N���b�N�����Ƃ����̏����ɓ���)
		//���Q�[���N���A�t���OON���́A�������Ȃ��Ă����̏����̒��ɓ���B
		if (m_mou_l == true || m_alpha < INI_ALPHA || m_Game_Clear_f == true)					
		{
			//���Q�[�����N���A���̏���
			//���S�ɓ��߂��ꂽ��A�z�[����ʂփX�e�[�W�ڍs����B
			if (m_Game_Clear_f == false)
			{
				//�N���b�N����炷(��������s����Ȃ��悤�ɏ������ŃR���g���[�����Ă���)
				if (m_alpha == INI_ALPHA)
				{
					Audio::Start(3);
				}

				m_alpha -= 0.01f;	//���ߓx�����X�Ɍ�������
				m_click_a -= 0.03f;
				m_result_a -= 0.5f;

				//���S���ߌ�̏���
				if (m_alpha <= 0.0f)
				{
					Scene::SetScene(new CSceneHome());	//�V�[���ڍs
				}
			}
			//���Q�[���N���A���̏���
			//2�b���ɃQ�[���N���A���b�Z�[�W�������Ă����A
			//�S�ẴN���A���b�Z�[�W�\����A�N���b�N�𑣂�
			//�Q�[���N���A(�G���f�B���O)��ʂɃV�[���ڍs����B
			else //(m_Game_Clear_f == true)
			{
				//�S�ẴN���A���b�Z�[�W�\����̏���
				if (m_page_nam == 2)
				{	
					if (m_mou_l == true)//���N���b�N
					{
						//���܂�����ĂȂ����A�����ł����ߏ����s���A0.0f�ɂȂ�����V�[���ڍs����悤�ɂ���B
						//����A�Q�[���I�[�o�[�̎��Ɠ��������ɂ���B

						//�N���b�N����炷(��������s����Ȃ��悤�ɏ������ŃR���g���[�����Ă���)
						//if (m_click_alpha == INI_ALPHA)
						//{
						//	Audio::Start(3);
						//}

						Scene::SetScene(new CSceneGameClear());	//�V�[���ڍs
					}
				}
				//�S�ẴN���A���b�Z�[�W�\���O�̏���
				else
				{
					m_page_nam++;		//�y�[�W����i�߂�
					m_cnt = m_cnt_max;	//�J�E���g��MAX�ɂ���(���ɖ߂�)
				}
			}
		}
	}
	//���J�E���g�_�E�����̏���
	else
	{
		//m_cnt--;	//0�łȂ��ꍇ�J�E���g�_�E��

		//�퓬���ʃE�C���h�E&�t�H���g���ߓx����
		//�����ɐ퓬���ʃE�C���h�E&�t�H���g���\�������
		m_result_a += 0.03f;



		CObjPlanet* Planet = (CObjPlanet*)Objs::GetObj(OBJ_PLANET);

		//�v���C���[�f��X���W�����X��200.0f�ɋ߂Â���(��ʍ��̕��Ɉړ�)
		if (Planet->GetX() >= 200.0f)
		{
			Planet->SetVX(-4.0f);
		}

		////�v���C���[�f��Y���W�����X��400.0f�ɋ߂Â���(�����ɉ��Ɉړ�)
		//if (Planet->GetY() < 400.0f)
		//{
		//	Planet->SetVY(+0.5f);
		//}
	}

	
	//���u�N���b�N�Ńz�[����ʁv���u�N���b�N�Ői�߂�v�̕����_�ŏ���
	//�Q�[���N���A�t���OOFF���̓J�E���g�I������s����邪�A
	//��x�ł��N���b�N�����Ƃ��̌���s����Ȃ��Ȃ�B
	//�Q�[���N���A�t���OON���̓Q�[���N���A���b�Z�[�W�S�\����̂ݎ��s�����B
	if (m_Game_Clear_f == false && m_alpha == INI_ALPHA || m_page_nam == 2)
	{
		//�t���O�L���̏ꍇ
		if (m_click_a_f == true)
		{
			if (m_click_a <= 0.5)			//0.5�Ő؂�ւ��āA�N���b�N������alpha����
				m_click_a_vec += 0.003f;	//�x�N�g���ɉ��Z
			else
				m_click_a_vec -= 0.003f;	//�x�N�g���Ɍ��Z
		}
		//�t���O�����̏ꍇ
		else
		{
			m_click_a = 0;		//alpha = 0
			m_click_a_vec = 0;	//	vec = 0
		}

		m_click_a += m_click_a_vec;	//�x�N�g���𔽉f
	}
}

//�h���[
void CObjFightClear::Draw()
{
	//���`��J���[���  R=RED  G=Green  B=Blue A=alpha(���ߏ��)
	float c0[4] = { 1.0f,1.0f,1.0f,m_click_a };//�N���b�N�Ñ��t�H���g�p
	
	//�퓬���ʃE�C���h�E&�t�H���g�p
	float c[6][4] = 
	{ 
		{ 1.0f,1.0f,0.0f,m_result_a },			//�ߐH�����t�H���g�͉��F
		{ 1.0f,1.0f,1.0f,m_result_a - 1.0f },	//�E�C���h�E�\���p
		{ 0.0f,0.0f,0.0f,m_result_a - 2.0f },	//�Z���t�H���g�͍��F
		{ 0.0f,0.0f,0.0f,m_result_a - 3.0f },	//�T�C�Y(HP)�t�H���g�͍��F
		{ 0.0f,0.0f,0.0f,m_result_a - 4.0f },	//���ރt�H���g�͍��F
		{ 1.0f,0.0f,0.0f,m_result_a - 5.0f },	//�X�y�V�����Z�t�H���g�͐ԐF
	};

	float d[4] = { 1.0f,1.0f, 1.0f, m_alpha };//���̑��摜�p

	//���t�H���g����
	//�l�����\���p(�Z���A���ށA�T�C�Y(HP)�Ŏg�p)
	wchar_t str[256];//256�������i�[�\�ȕ����z���錾


	RECT_F src;//�؂���ʒu
	RECT_F dst;//�\���ʒu
	
	src.m_top   =  0.0f;
	src.m_left  =  0.0f;
	src.m_right = 64.0f;
	src.m_bottom= 64.0f;
	
	//���Q�[�����N���A���̏���
	if (m_Game_Clear_f == false)
	{
		//���E�C���h�E�\��
		dst.m_top    =  50.0f;
		dst.m_left   = 650.0f;
		dst.m_right  =1100.0f;
		dst.m_bottom = 600.0f;
		Draw::Draw(33, &src, &dst, c[1], 0.0f);


		//���퓬���ʃt�H���g�\��
		//�ߐH�����t�H���g
		Font::StrDraw(L"�ߐH�����I", 670, 50, 50, c[0]);

		//�Z��
		Font::StrDraw(L"�Z���F",	670, 100, 50, c[2]);
		swprintf_s(str, L"�{%d�l", m_people);
		Font::StrDraw(str, 800, 100, 50, c[2]);

		//�T�C�Y(HP)
		Font::StrDraw(L"�T�C�Y(HP)�F", 670, 300, 50, c[3]);
		swprintf_s(str, L"�{%d", m_large);
		Font::StrDraw(str, 800, 300, 50, c[3]);

		//����
		Font::StrDraw(L"���ށF",	670, 200, 50, c[4]);
		Font::StrDraw(m_mat_name[0], 800, 200, 50, c[4]);
		swprintf_s(str, L"�{%d��", m_mat_num[0]);
		Font::StrDraw(str, 900, 200, 50, c[4]);
		Font::StrDraw(m_mat_name[1], 800, 250, 50, c[4]);
		swprintf_s(str, L"�{%d��", m_mat_num[1]);
		Font::StrDraw(str, 900, 250, 50, c[4]);

		//�X�y�V�����Z
		if (m_skill != 0)
		{
			Font::StrDraw(L"�X�y�V�����Z�F",670, 400, 50, c[5]);
		}

		switch (m_skill)						
		{
		case 1:Font::StrDraw(L"Explosion", 800, 410, 40, c[5]); break;
		case 2:Font::StrDraw(L"Fracture Ray", 800, 410, 40, c[5]); break;
		case 3:Font::StrDraw(L"Immortality", 800, 410, 40, c[5]); break;
		case 4:Font::StrDraw(L"���~�b�g�u���C�N", 800, 410, 40, c[5]); break;
		case 5:Font::StrDraw(L"�X�e���C�h���^", 800, 410, 40, c[5]); break;
		default: break;
		}


		//����
		//switch (m_mrl)
		//{
		//case 0:Font::StrDraw(L"�@  ��40", 800, 200, 50, c); break;
		//case 1:Font::StrDraw(L"�@  ��80", 800, 200, 50, c); break;
		//case 2:Font::StrDraw(L"�@  �S40", 800, 200, 50, c); break;
		//case 3:Font::StrDraw(L"�@  �S40", 800, 200, 50, c); break;
		//case 4:Font::StrDraw(L"    ��60", 800, 175, 50, c);
		//	Font::StrDraw(L"    �S60", 800, 225, 50, c);
		//	break;
		//}

		//���N���b�N�Ñ��t�H���g�\��
		Font::StrDraw(L"�N���b�N�Ńz�[�����", 350, 600, 50, c0);
	}
	//���Q�[���N���A���̏���
	else
	{
		//���Q�[���N���A���b�Z�[�W�\��
		if(m_page_nam == 1)
		{
			//dst.m_top    =  50.0f;
			//dst.m_left   = 200.0f;
			//dst.m_right  =1000.0f;
			//dst.m_bottom = 250.0f;
			//Draw::Draw(33, &src, &dst, d, 0.0f);

			float c[4] = { 0.0f,0.0f,0.0f,1.0f };//char�̐F
			Font::StrDraw(L"���ׂĂ̘f����ߐH����",	 300,  80, 50, c);
			//Font::StrDraw(L"���̋�͂̃g�b�v�ɌN�Ղ���", 250, 180, 50, c);
		}
		else if(m_page_nam == 2)
		{
			//dst.m_top    =  50.0f;
			//dst.m_left   = 200.0f;
			//dst.m_right  =1000.0f;
			//dst.m_bottom = 250.0f;
			//Draw::Draw(33, &src, &dst, d, 0.0f);

			float c[4] = { 0.0f,0.0f,0.0f,1.0f };//char�̐F
			Font::StrDraw(L"���ׂĂ̘f����ߐH����",	 300,  80, 50, c);
			Font::StrDraw(L"���̋�͂̃g�b�v�ɌN�Ղ���", 250, 180, 50, c);

			float c0[4] = { 1.0f,1.0f,1.0f,m_click_a };//char�̐F
			Font::StrDraw(L"�N���b�N�Ői��", 350, 600, 50, c0);
		}
	}
}
