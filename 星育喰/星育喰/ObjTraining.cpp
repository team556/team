//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"		//�g�p����Ă���̂̓}�E�X�f�o�b�O�̕����̂�
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�}�N��
#define INI_PLAYER_SIZE (1500.0f) //�v���C���[�f���̏����T�C�Y
#define INI_COLOR (1.0f) //�S�J���[���x�̏����l

//static�ϐ��̒�`
bool CObjTraining::m_key_rf = false;
bool CObjTraining::scene_change_start = false;
int  CObjTraining::window_start_manage = Default;

//�O���[�o���ϐ��̒�`
int g_Bar_Level = 1;
int g_Power_num = 0;
int g_Defense_num = 0;
int g_Speed_num = 0;
int g_Balance_num = 0;
int g_Remain_num = 1000;

//�C�j�V�����C�Y
void CObjTraining::Init()
{
	m_size = INI_PLAYER_SIZE;

	m_mou_x = 0.0f;
	m_mou_y = 0.0f;
	m_mou_r = false;
	m_mou_l = false;

	m_Back_Button_color = INI_COLOR;
	
	m_Mig_time = 0;
	m_key_lf = false;

	scene_change_start = false;
	window_start_manage = Default;
}

//�A�N�V����
void CObjTraining::Action()
{
	//�߂�{�^���N���b�N�A�������͉E�N���b�N(�ǂ��ł�)�����s
	if (window_start_manage == BackButton)
	{
		m_Mig_time++;

		//���V�[���؂�ւ����o
		//�_���oIN���I������܂�(m_Mig_time��120�ȏ�ɂȂ�܂�)�ҋ@�B
		//�I������Ɣw�i���z�[����ʂ̂��̂ɐ؂�ւ��A
		//�������I�u�W�F�N�g���z�[����ʂ̂��̂ɐ؂�ւ������
		//�_���oOUT���s���A��ʂ�������B
		//�v���C���[�f���T�C�Y���f�t�H���g�̏�Ԃɖ߂��������m�F�����
		//�z�[����ʂփV�[���ڍs���s���B
		if (scene_change_start == true)
		{
			m_size -= 20.0f;

			if (m_size <= 0.0f)
			{
				Scene::SetScene(new CSceneHome());//�z�[����ʂփV�[���ڍs
			}
		}
		else if (m_Mig_time >= 120)
		{
			//�z�[����ʂ̔w�i��ǂݍ���0�Ԃɓo�^
			Draw::LoadImage(L"TitleBackgroundTest.jpg", 0, TEX_SIZE_512);

			//�_���oOUT���s��
			CObjCloud_Effect* obj_cloud = (CObjCloud_Effect*)Objs::GetObj(OBJ_CLOUD);
			obj_cloud->SetCheck(false);

			//�V�[���؂�ւ����o�ɂĕs�K�v�ȃI�u�W�F�N�g���\���A
			//�܂��K�v�ȃI�u�W�F�N�g��\������t���O�𗧂Ă�
			scene_change_start = true;
		}

		return;
	}
	//���{�݂̃E�C���h�E���J���Ă��鎞�͑�����󂯕t���Ȃ��悤�ɂ���B
	else if (window_start_manage != Default)
	{
		return;
	}


	//�}�E�X�̈ʒu���擾
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//�}�E�X�̃{�^���̏��
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();


	//�߂�{�^�����N���b�N�A�������͉E�N���b�N���鎖�Ńz�[����ʂɖ߂�
	if (10 < m_mou_x && m_mou_x < 60 && 10 < m_mou_y && m_mou_y < 60 || m_mou_r == true)
	{
		m_Back_Button_color = 0.7f;

		//���ڍs�t���O�𗧂āA�z�[����ʂ։��o�������Ȃ���V�[���ڍs
		//�E�N���b�N���͎�
		if (m_mou_r == true)
		{
			//�O�V�[��(���ɃE�C���h�E��)����E�N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
			if (m_key_rf == true)
			{
				//�_���oIN���s��
				CObjCloud_Effect* obj_cloud = (CObjCloud_Effect*)Objs::GetObj(OBJ_CLOUD);
				obj_cloud->SetCheck(true);

				//�ڍs�t���O����
				window_start_manage = BackButton;
			}
		}
		//���N���b�N���͎�
		else if (m_mou_l == true)
		{
			//���N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
			if (m_key_lf == true)
			{
				m_key_lf = false;

				//�_���oIN���s��
				CObjCloud_Effect* obj_cloud = (CObjCloud_Effect*)Objs::GetObj(OBJ_CLOUD);
				obj_cloud->SetCheck(true);

				//�ڍs�t���O����
				window_start_manage = BackButton;
			}
		}
		else
		{
			m_key_lf = true;
		}
	}
	else
	{
		m_key_rf = true;
		m_Back_Button_color = 1.0f;
	}
}

//�h���[
void CObjTraining::Draw()
{
	//�`��J���[���  R=RED  G=Green  B=Blue A=alpha(���ߏ��)
	//�߂�{�^���p
	float b[4] = { m_Back_Button_color,m_Back_Button_color,m_Back_Button_color,1.0f };

	//����ȊO�̉摜�p
	float d[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu


	//���w�i(�n��)�\��
	//�V�[���ڍs�̉��o�����I�ɁA
	//���̐؂���ʒu�̓z�[����ʂƓ������D�܂���
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 960.0f;
	src.m_bottom = 638.0f;

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 1200.0f;
	dst.m_bottom = 700.0f;
	Draw::Draw(0, &src, &dst, d, 0.0f);


	//���V�[���؂�ւ����o�O�ɕ\������O���t�B�b�N
	if (scene_change_start == false)
	{
		//���߂�{�^���\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 225.0f;
		src.m_bottom = 225.0f;

		dst.m_top = 10.0f;
		dst.m_left = 10.0f;
		dst.m_right = 60.0f;
		dst.m_bottom = 60.0f;
		Draw::Draw(1, &src, &dst, b, 0.0f);
	}
	//���V�[���؂�ւ����o��ɕ\������O���t�B�b�N
	else
	{
		//���v���C���[�f���\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 300.0f;
		src.m_bottom = 168.0f;

		dst.m_top = 150.0f - m_size;
		dst.m_left = 250.0f - m_size;
		dst.m_right = 950.0f + m_size;
		dst.m_bottom = 550.0f + m_size;
		Draw::Draw(50, &src, &dst, d, 0.0f);
	}



	//�f�o�b�O�p���}�E�X�ʒu�\��
	wchar_t str[256];
	swprintf_s(str, L"x=%f,y=%f", m_mou_x, m_mou_y);
	Font::StrDraw(str, 20, 20, 12, d);
}
