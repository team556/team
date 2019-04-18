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
int g_Ins_Level = 1;
int g_Mis_Recast_Level = 0;
int g_Pow_equip_Level = 1;	
int g_Pow_equip_Lv_achieve = 1;
int g_Def_equip_Level = 1;		
int g_Def_equip_Lv_achieve = 1;	
int g_Spe_equip_Level = 1;		
int g_Spe_equip_Lv_achieve = 1;	
int g_Bal_equip_Level = 1;
int g_Bal_equip_Lv_achieve = 1;
int g_Pod_equip_Level = 1;
int g_Pod_equip_Lv_achieve = 1;
int g_Power_num = 0;
int g_Defense_num = 0;
int g_Speed_num = 0;
int g_Balance_num = 0;
int g_Research_num = 0;
int g_Remain_num = 1000;

int g_Material_num_test = 400;

//�C�j�V�����C�Y
void CObjTraining::Init()
{
	m_size = INI_PLAYER_SIZE;
	m_Mig_time = 0;

	m_mou_x = 0.0f;
	m_mou_y = 0.0f;
	m_mou_r = false;
	m_mou_l = false;
	m_key_lf = false;

	m_Back_Button_color = INI_COLOR;

	//���ȉ���static�ϐ��͑��V�[������琬��ʂɓ���x�ɏ��������s��
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
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

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
		src.m_right = 62.0f;
		src.m_bottom = 62.0f;

		dst.m_top = 250.0f - m_size;
		dst.m_left = 450.0f - m_size;
		dst.m_right = 750.0f + m_size;
		dst.m_bottom = 550.0f + m_size;
		Draw::Draw(16, &src, &dst, d, 0.0f);
	}



	//�f�o�b�O�p���}�E�X�ʒu�\��
	wchar_t str[256];
	swprintf_s(str, L"x=%f,y=%f", m_mou_x, m_mou_y);
	Font::StrDraw(str, 20.0f, 20.0f, 12.0f, d);
}

//---Allocation�֐�
//����1�@int type_num		:�Z���^�C�v����
//����2�@int up_down_check	:�U�蕪��UP / DOWN�`�F�b�N(+1=�U�蕪��UP / -1=�U�蕪��DOWN)
//�߂�l int				:�U�蕪����̒l
//�����e
//�Z���^�C�v�ƐU�蕪��UP or DOWN�������œn���΁A
//�ȉ��̏������s���A���̏Z���^�C�v�̐U�蕪����̒l��Ԃ��B
//�������ɃO���[�o���ϐ��ł���"�c��Z����(g_Remain_num)"�̒l���ω������Ă���B
int CObjTraining::Allocation(int type_num, int up_down_check)
{
	//�����ꂼ�ꉼ�̕ϐ��ɑ��
	int Tmp_human = type_num;
	int Tmp_remain = g_Remain_num;

	//�����̕ϐ��ŕω������Ă݂�
	Tmp_human += 100 * up_down_check;
	Tmp_remain -= 100 * up_down_check;

	//�����̕ϐ����ȉ��̏�����S�Ė������Ă���΁A���ۂ̒l��ω�������B
	//�������Ă��Ȃ���΁A����ɉ������G���[���b�Z�[�W���o���A
	//���ۂ̒l��ω��������Ɋ֐����I��������B
	if (0 <= Tmp_human && Tmp_human <= 999900 && Tmp_remain >= 0)
	{
		type_num += 100 * up_down_check;
		g_Remain_num -= 100 * up_down_check;
	}
	else if (Tmp_remain < 0) //�c��Z���������Ȃ��ꍇ
	{
		swprintf_s(m_message, L"�c��Z���������܂���");//�����z��ɕ����f�[�^������
		
		//���G���[���b�Z�[�W�̃J���[��ԐF�ɂ���
		m_message_red_color = 1.0f;
		m_message_green_color = 0.0f;
		m_message_blue_color = 0.0f;
		
		m_alpha = 1.0f;		//�G���[���b�Z�[�W��\�����邽�߁A���ߓx��1.0f�ɂ���
	}
	else  //(Tmp_human < 0 || 999900 < Tmp_human) ����ȏ�U�蕪�����Ȃ��ꍇ
	{
		swprintf_s(m_message, L"����ȏ�U�蕪�����܂���");//�����z��ɕ����f�[�^������

		//���G���[���b�Z�[�W�̃J���[��ԐF�ɂ���
		m_message_red_color = 1.0f;
		m_message_green_color = 0.0f;
		m_message_blue_color = 0.0f;

		m_alpha = 1.0f;		//�G���[���b�Z�[�W��\�����邽�߁A���ߓx��1.0f�ɂ���
	}

	return type_num;
}
