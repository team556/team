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
#define FONT_X (400)//�퓬���ʃt�H���g(���[)��X�ʒu
#define FONT_Y (230)//�퓬���ʃt�H���g(���[)��X�ʒu

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
	m_black_out_a = 0.0f;

	m_scene_migration_f = false;

	//m_cnt_max = 60 * 2;	//2�b
	//m_cnt = m_cnt_max;	//�ő�l�����Ă���

	m_Stage_Clear_f = false;	//�X�e�[�W�N���A�t���O
	m_Game_Clear_f = false;		//�Q�[���@�N���A�t���O

	//m_page_nam = 0;				//�y�[�W��0


	//�X�e�[�W�N���A�����ꍇ
	if (g_destroy_progress[0] == true &&	
		g_destroy_progress[1] == true &&
		g_destroy_progress[2] == true &&
		g_destroy_progress[3] == true)	
	{
		g_Stage_progress++;	//�X�e�[�W��i�߂�

		for (int i = 0; i < 4; i++)
		{
			g_destroy_progress[i] = false;//�G�̌��j��Ԃ����ׂĖ߂�
		}
	}	

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
	
	//�X�L���擾���Ă���ꍇ
	//���̔ԍ����擾����
	if (m_skill != 0)			
	{							
		g_Special_mastering[m_skill - 1] = true;
	}
}

//�A�N�V����
void CObjFightClear::Action()
{
	if (m_Game_Clear_f == false)
	{
		//���Q�[�����N���A���̏���
		//�v���C���[�f�������Ɉړ������A
		//�퓬���ʂ����X�ɕ\�����Ă����B
		//�S�ĕ\����N���b�N�𑣂��A�N���b�N�����
		//��U��ʈÓ]���A���̌��ʖ��]�����
		//�z�[����ʂɈڍs���Ă��镗�Ɍ����鉉�o��A
		//���ۂɃz�[����ʂփX�e�[�W�ڍs����B


		//���퓬���ʕ\���I����̏���
		if (m_result_a >= 6.0f)
		{
			////�}�E�X�̈ʒu���擾
			//m_mou_x = (float)Input::GetPosX();
			//m_mou_y = (float)Input::GetPosY();
			////�}�E�X�̃{�^���̏��
			//m_mou_r = Input::GetMouButtonR();
			m_mou_l = Input::GetMouButtonL();

			m_click_a_f = true;			//�t���O�L��

			//���N���b�N�����ꍇ�A���s(��x�N���b�N����ƈȌ�A�N���b�N�����Ƃ����̏����ɓ���)
			if (m_mou_l == true || m_black_out_a != 0.0f || m_scene_migration_f == true)
			{
				//�N���b�N����炷(1�x�݂̂������s����Ȃ�)
				if (m_black_out_a == 0.0f && m_scene_migration_f == false)
				{
					Audio::Start(3);
				}

				//��ʈÓ]���ߓx�����X�ɑ��������A��ʑS�̂��Ó]��������A
				//�t���O�𗧂āA�z�[����ʈڍs���o���s���A
				//���o�I����A�{���Ƀz�[����ʂֈڍs������B
				if (m_black_out_a <= 0.0f && m_scene_migration_f == true)
				{
					Scene::SetScene(new CSceneHome());	//�V�[���ڍs
				}
				else if (m_scene_migration_f == true)
				{
					m_black_out_a -= 0.01f;//��ʖ��]
				}
				else if (m_black_out_a >= 1.0f)
				{
					m_scene_migration_f = true;//�V�[���ڍs���o�t���OON
				}
				else
				{
					m_black_out_a += 0.01f;//��ʈÓ]
					m_click_a -= 0.03f;	   //�N���b�N�Ñ��t�H���g�����X�ɔ�\���ɁB
				}

				m_click_a_f = false;//�t���O����
			}
		}
		//���퓬���ʕ\�����̏���
		else
		{
			//�퓬���ʃE�C���h�E&�t�H���g���ߓx�������A
			//���ɐ퓬���ʃE�C���h�E&�t�H���g��\�����Ă����B
			//���S�ĕ\����A����else���𔲂���B
			m_result_a += 0.03f;

			//�v���C���[�f��X���W(m_px)�����X��200.0f�ɋ߂Â���(��ʍ��̕��Ɉړ�)
			CObjPlanet* Planet = (CObjPlanet*)Objs::GetObj(OBJ_PLANET);
			if (Planet->GetX() >= 200.0f)
			{
				Planet->SetVX(-4.0f);
			}
		}
	}
	else //(m_Game_Clear_f == true)
	{
		//���Q�[���N���A���̏���
		//���X�ɃQ�[���N���A���b�Z�[�W�������Ă����A
		//�S�ẴN���A���b�Z�[�W�\����A�N���b�N�𑣂�
		//�Q�[���N���A(�G���f�B���O)��ʂɃV�[���ڍs����B


		//�S�ẴN���A���b�Z�[�W�\����̏���
		if (m_clear_a >= 3.0f)
		{
			////�}�E�X�̈ʒu���擾
			//m_mou_x = (float)Input::GetPosX();
			//m_mou_y = (float)Input::GetPosY();
			////�}�E�X�̃{�^���̏��
			//m_mou_r = Input::GetMouButtonR();
			m_mou_l = Input::GetMouButtonL();

			m_click_a_f = true;			//�t���O�L��

			//���N���b�N�����ꍇ�A���s(��x�N���b�N����ƈȌ�A�N���b�N�����Ƃ����̏����ɓ���)
			if (m_mou_l == true || m_black_out_a != 0.0f)
			{
				//�N���b�N����炷(1�x�݂̂������s����Ȃ�)
				if (m_black_out_a == 0.0f)
				{
					Audio::Start(3);
				}

				//��ʈÓ]���ߓx�����X�ɑ��������A��ʑS�̂��Ó]��������A
				//�t���O�𗧂āA�Q�[���N���A��ʂɈڍs����
				if (m_black_out_a >= 1.0f)
				{
					Scene::SetScene(new CSceneGameClear());	//�V�[���ڍs
				}
				else
				{
					m_black_out_a += 0.01f;//��ʈÓ]
					m_click_a -= 0.03f;	   //�N���b�N�Ñ��t�H���g�����X�ɔ�\���ɁB
				}

				m_click_a_f = false;//�t���O����
			}
		}
		//�S�ẴN���A���b�Z�[�W�\���O�̏���
		else
		{
			//�N���A���b�Z�[�W�t�H���g�̓��ߓx�������A
			//���ɃN���A���b�Z�[�W��\�����Ă����B
			//���S�ĕ\����A����else���𔲂���B
			m_clear_a += 0.01f;
		}
	}

	//���u�N���b�N�Ńz�[����ʁv���u�N���b�N�Ői�߂�v�̕����_�ŏ���
	//�Q�[���N���A�t���OOFF���͐퓬���ʕ\���I������s����邪�A
	//��x�ł��N���b�N�����Ƃ��̌���s����Ȃ��Ȃ�B
	//�Q�[���N���A�t���OON���̓Q�[���N���A���b�Z�[�W�S�\����̂ݎ��s�����B

	//�t���O�L���̏ꍇ
	if (m_click_a_f == true)
	{
		if (m_click_a <= 0.5)			//0.5�Ő؂�ւ��āA�N���b�N������alpha����
		{
			m_click_a_vec += 0.003f;	//�x�N�g���ɉ��Z
		}			
		else
		{
			m_click_a_vec -= 0.003f;	//�x�N�g���Ɍ��Z
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
		{ 0.0f,0.0f,0.0f,m_result_a - 5.0f },	//�X�y�V�����Z�t�H���g�͍��F
	};

	float blackout[4] = { 1.0f,1.0f,1.0f,m_black_out_a };	//��ʑS�̈Ó]�摜�p

	//�N���A���b�Z�[�W�t�H���g�p
	float clear[3][4] =
	{
		{ 1.0f,1.0f,0.0f,m_clear_a },			//�t�H���g�F�͑S�ĉ��F
		{ 1.0f,1.0f,0.0f,m_clear_a - 1.0f },
		{ 1.0f,1.0f,0.0f,m_clear_a - 2.0f },
	};


	float d[4] = { 1.0f,1.0f, 1.0f, 1.0f };//���̑��摜�p

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
		//�V�[���ڍs���o�O�ɕ\������O���t�B�b�N
		//���N���A��ʂŌ�����O���t�B�b�N
		if (m_scene_migration_f == false)
		{
			//���E�C���h�E�\��
			dst.m_top = 210.0f;
			dst.m_left = 350.0f;
			dst.m_right = 1150.0f;
			dst.m_bottom = 530.0f;
			Draw::Draw(33, &src, &dst, c[1], 0.0f);


			//���퓬���ʃt�H���g�\��
			//�ߐH�����t�H���g
			Font::StrDraw(L"�ߐH�����I", 370, 50, 100, c[0]);


			//�Z��
			Font::StrDraw(L"�Z���F", FONT_X, FONT_Y, 40, c[2]);
			
			swprintf_s(str, L"�{%d�l", m_people);
			Font::StrDraw(str, FONT_X + 300, FONT_Y, 40, c[2]);


			//�T�C�Y(HP)
			Font::StrDraw(L"�f��HP�F", FONT_X, FONT_Y + 50, 40, c[3]);
			
			swprintf_s(str, L"�{%d", m_large);
			Font::StrDraw(str, FONT_X + 300, FONT_Y + 50, 40, c[3]);


			//����
			Font::StrDraw(L"���ށF", FONT_X, FONT_Y + 100, 40, c[4]);

			Font::StrDraw(m_mat_name[0], FONT_X, FONT_Y + 150, 40, c[4]);	//���ޖ�A�\��

			swprintf_s(str, L"�{%d��", m_mat_num[0]);
			Font::StrDraw(str, FONT_X + 300, FONT_Y + 150, 40, c[4]);		//���ސ�A�\��
			

			Font::StrDraw(m_mat_name[1], FONT_X, FONT_Y + 200, 40, c[4]);	//���ޖ�B�\��
			
			if (m_mat_num[1] != NULL)//���ސ�B��NULL(0)�̎��͕`�悵�Ȃ�
			{
				swprintf_s(str, L"�{%d��", m_mat_num[1]);
				Font::StrDraw(str, FONT_X + 300, FONT_Y + 200, 40, c[4]);	//���ސ�B�\��
			}


			//�X�y�V�����Z
			if (m_skill != 0)
			{
				Font::StrDraw(L"�X�y�V�����Z�F", FONT_X, FONT_Y + 250, 40, c[5]);

				switch (m_skill)
				{
				case 1:Font::StrDraw(L"Explosion GET!",			FONT_X + 300, FONT_Y + 250, 40, c[5]); break;
				case 2:Font::StrDraw(L"Fracture Ray GET!",		FONT_X + 300, FONT_Y + 250, 40, c[5]); break;
				case 3:Font::StrDraw(L"Immortality GET!",		FONT_X + 300, FONT_Y + 250, 40, c[5]); break;
				case 4:Font::StrDraw(L"���~�b�g�u���C�N GET!",	FONT_X + 300, FONT_Y + 250, 40, c[5]); break;
				case 5:Font::StrDraw(L"�X�e���C�h���^ GET!",	FONT_X + 300, FONT_Y + 250, 40, c[5]); break;
				default: break;
				}
			}

			//���N���b�N�Ñ��t�H���g�\��
			Font::StrDraw(L"�N���b�N�Ńz�[�����", 350, 600, 50, c0);
		}
		//�V�[���ڍs���o��ɕ\������O���t�B�b�N
		//���z�[����ʂɈڍs�����悤�Ɍ�����O���t�B�b�N
		else //(m_scene_migration_f == true)
		{
			//���w�i�\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 960.0f;
			src.m_bottom = 638.0f;

			dst.m_top = 0.0f;
			dst.m_left = 0.0f;
			dst.m_right = 1200.0f;
			dst.m_bottom = 700.0f;
			Draw::Draw(0, &src, &dst, d, 0.0f);

			//���v���C���[�f���\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 62.0f;
			src.m_bottom = 62.0f;

			dst.m_top = 250.0f;
			dst.m_left = 450.0f;
			dst.m_right = 750.0f;
			dst.m_bottom = 550.0f;
			Draw::Draw(34, &src, &dst, d, 0.0f);
		}
	}
	//���Q�[���N���A���̏���
	else
	{
		//���Q�[���N���A���b�Z�[�W�\��
		Font::StrDraw(L"CONGRATULATIONS!!", 180, 50, 100, clear[0]);
		Font::StrDraw(L"���ׂĂ̘f����ߐH����", 200, 250, 70, clear[1]);
		Font::StrDraw(L"���̋�͂̃g�b�v�ɌN�Ղ���", 130, 350, 70, clear[2]);

		//���N���b�N�Ñ��t�H���g�\��
		Font::StrDraw(L"�N���b�N�Ői��", 400, 600, 50, c0);
	}


	//����L�̂ǂ���̏����ł��g�p(�`��)�������
	//����ʑS�̈Ó]�p�摜�\��
	//��blackout�̓��ߓx�̒l�Łu�\��/��\���v���؂�ւ�����
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1200.0f;
	src.m_bottom = 700.0f;

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 1200.0f;
	dst.m_bottom = 700.0f;
	Draw::Draw(20, &src, &dst, blackout, 0.0f);
}
