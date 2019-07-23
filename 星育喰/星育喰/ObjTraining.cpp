//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "UtilityModule.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�}�N��
#define INI_PLAYER_SIZE (1500.0f) //�v���C���[�f���̏����T�C�Y
#define INI_COLOR (0.9f) //�S�J���[���x�̏����l(�A�C�R�����I�𒆂̃J���[)

//static�ϐ��̒�`
bool CObjTraining::scene_change_start = false;
bool CObjTraining::white_out_f = false;
int  CObjTraining::player_level = 0;
int  CObjTraining::window_start_manage = Default;

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
	m_key_rf = false;

	m_Back_Button_color = INI_COLOR;

	m_message_clip_right = 0.0f;
	m_message_clip_bottom = 0.0f;
	m_message_draw_left = 0.0f;
	m_message_draw_right = 0.0f;
	m_message_red_color = 0.0f;
	m_message_green_color = 0.0f;
	m_message_blue_color = 0.0f;
	m_alpha = 0.0f;

	//���ȉ���static�ϐ��͑��V�[������琬��ʂɓ���x�ɏ��������s��
	scene_change_start = false;
	white_out_f = false;
	player_level = (int)((g_Bar_Level + g_Ins_Level) / 2);
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
			//�z�[����ʂ̔w�i���v���C���[�f���̃��x���ɍ��킹���ǂݍ��ݔԍ������ɓo�^
			//Draw::LoadImage(L"TitleBackgroundTest.jpg", 7 * (((int)((g_Bar_Level + g_Ins_Level) / 2)) - 1), TEX_SIZE_512);
			Draw::LoadImage(L"�w�i.png", 7 * (((int)((g_Bar_Level + g_Ins_Level) / 2)) - 1), TEX_SIZE_512);

			//ObjHelp�ɃV�[���ڍs���o��`����
			CObjHelp* help = (CObjHelp*)Objs::GetObj(OBJ_HELP);
			help->SetMig_stageF();

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
	else if (window_start_manage != Default || g_help_f == true)
	{
		//���{�݃E�C���h�E(�w���v��ʂ��܂�)�̖߂�{�^�������N���b�N(�������͉E�N���b�N)���A
		//�z�[����ʂɖ߂�{�^���������ɃN���b�N����Ȃ��悤�ɁA
		//�ȉ��̂悤�ɃL�[�t���O��false�ɂ��鎖�Ő��䂵�Ă���B
		m_key_lf = false;
		m_key_rf = false;

		return;
	}


	//�}�E�X�̈ʒu���擾
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//�}�E�X�̃{�^���̏��
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	//���L�[�t���O
	//���E�N���b�NPush��ԁ��E�N���b�N��Push��ԂɂȂ�܂ŁA
	//�ēx�E�N���b�N���鎖�͏o���Ȃ������B
	if (m_mou_r == false)	//�E�N���b�NOFF
	{
		m_key_rf = true;
	}

	//�߂�{�^�����N���b�N�A�������͉E�N���b�N���鎖�Ńz�[����ʂɖ߂�
	if (10 < m_mou_x && m_mou_x < 60 && 10 < m_mou_y && m_mou_y < 60 || m_mou_r == true)
	{
		m_Back_Button_color = 1.0f;

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

				//�߂�{�^����
				Audio::Start(2);
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

				//�߂�{�^����
				Audio::Start(2);
			}
		}
		else
		{
			m_key_lf = true;
		}
	}
	else
	{
		m_Back_Button_color = INI_COLOR;
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
	src.m_right = 1200.0f;
	src.m_bottom = 700.0f;

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 1200.0f;
	dst.m_bottom = 700.0f;
	Draw::Draw(7 * (((int)((g_Bar_Level + g_Ins_Level) / 2)) - 1), &src, &dst, d, 0.0f);

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
		src.m_right = 448.0f;
		src.m_bottom = 448.0f;

		dst.m_top = 250.0f - m_size;
		dst.m_left = 450.0f - m_size;
		dst.m_right = 750.0f + m_size;
		dst.m_bottom = 550.0f + m_size;
		Draw::Draw(16 + ((int)((g_Bar_Level + g_Ins_Level) / 2)) - 1, &src, &dst, d, 0.0f);

	}



	//�f�o�b�O�p���}�E�X�ʒu�\��
	//wchar_t str[256];
	//swprintf_s(str, L"x=%f,y=%f", m_mou_x, m_mou_y);
	//Font::StrDraw(str, 20.0f, 20.0f, 12.0f, d);
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
		//�c��Z���������܂��񕶎��摜��ǂݍ���127�Ԃɓo�^
		Draw::LoadImage(L"�c��Z���������܂���.png", 127, TEX_SIZE_512);//�ȈՃ��b�Z�[�W�摜�ǂݍ��ݔԍ��ɉ摜�f�[�^������

		//�؂���ʒu��ݒ肷��
		m_message_clip_right = 1192.0f;
		m_message_clip_bottom = 112.0f;

		//�`��ʒu��ݒ肷��
		m_message_draw_left = -150.0f;
		m_message_draw_right = 150.0f;

		//���G���[���b�Z�[�W�̃J���[��ԐF�ɂ���
		m_message_red_color = 1.0f;
		m_message_green_color = 0.0f;
		m_message_blue_color = 0.0f;
		
		m_alpha = 1.0f;		//�G���[���b�Z�[�W��\�����邽�߁A���ߓx��1.0f�ɂ���
	}
	else  //(Tmp_human < 0 || 999900 < Tmp_human) ����ȏ�U�蕪�����Ȃ��ꍇ
	{
		//����ȏ�U�蕪�����܂��񕶎��摜��ǂݍ���127�Ԃɓo�^
		Draw::LoadImage(L"����ȏ�U�蕪�����܂���.png", 127, TEX_SIZE_512);//�ȈՃ��b�Z�[�W�摜�ǂݍ��ݔԍ��ɉ摜�f�[�^������

		//�؂���ʒu��ݒ肷��
		m_message_clip_right = 1552.0f;
		m_message_clip_bottom = 112.0f;

		//�`��ʒu��ݒ肷��
		m_message_draw_left = -200.0f;
		m_message_draw_right = 200.0f;

		//���G���[���b�Z�[�W�̃J���[��ԐF�ɂ���
		m_message_red_color = 1.0f;
		m_message_green_color = 0.0f;
		m_message_blue_color = 0.0f;

		m_alpha = 1.0f;		//�G���[���b�Z�[�W��\�����邽�߁A���ߓx��1.0f�ɂ���
	}

	return type_num;
}

//---Facility_message�֐�
//����1�@int Facility_Level	:���݂̎{��(����or������)���x��
//�����e
//���݂̎{��(����or������)���x�����l������
//�K�v�f��&�T�C�Y���b�Z�[�W��`�悷��B
void CObjTraining::Facility_message(int Facility_Level)
{
	//���`��J���[���  R=RED  G=Green  B=Blue A=alpha(���ߏ��)
	//�ԐF
	float red[4] = { 1.0f,0.0f,0.0f,1.0f };

	//�F
	float blue[4] = { 0.0f,0.0f,1.0f,1.0f };

	//���F
	float black[4] = { 0.0f,0.0f,0.0f,1.0f };

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu


	//��LvUP�����@�����K�v�����摜�\��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1335.0f;
	src.m_bottom = 112.0f;

	dst.m_top = 440.0f;
	dst.m_left = 165.0f;
	dst.m_right = 433.0f;
	dst.m_bottom = 465.0f;
	Draw::Draw(66, &src, &dst, blue, 0.0f);

	//���{�݃��x��MAX���̏���
	if (Facility_Level == FACILITY_MAX_LV)
	{
		//���ő�Lv���B!�����摜�\��
		src.m_top = 0.0f;
		src.m_left = 1.5f;//�摜�̍��[�Ɍ����s���̍��������������̂Ő؂���ʒu�𒲐����A���̕������f��Ȃ����Ă���B
		src.m_right = 907.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 475.0f;
		dst.m_left = 167.5f;
		dst.m_right = 338.5f;
		dst.m_bottom = 500.0f;
		Draw::Draw(107, &src, &dst, black, 0.0f);

		//������ȏ�LVUP�s�ł��B�����摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1350.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 510.0f;
		dst.m_left = 167.5f;
		dst.m_right = 433.0f;
		dst.m_bottom = 535.0f;
		Draw::Draw(108, &src, &dst, black, 0.0f);
	}

	//���{�݃��x��MAX�ł͂Ȃ����̏���
	else
	{
		//���f��HP�����摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 412.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 475.0f;
		dst.m_left = 165.0f;
		dst.m_right = 255.0f;
		dst.m_bottom = 500.0f;
		Draw::Draw(67, &src, &dst, black, 0.0f);

		//�����݂̘f��HP��\��
		FontDraw(NumConversion((unsigned int)g_Player_max_size), 338.0f, 475.0f, 15.0f, 25.0f, black, true);

		//���{��(���ɁA������)�̎���LVUP�ɕK�v�ȃT�C�Y(HP)�\��
		FontDraw(NumConversion((unsigned int)m_Facility_next_Size_num[Facility_Level - 1]), 420.0f, 475.0f, 15.0f, 25.0f, black, true);

		//���{��(���ɁA������)�̎���LVUP�ɕK�v�ȑf�ޖ��\��
		FontDraw(m_Facility_next_Mat_name[Facility_Level - 1], 165.0f, 510.0f, 25.0f, 25.0f, black, false);

		//���{��(���ɁA������)�̎���LVUP�ɕK�v�Ȍ��݂̑f�ޏ�������\��
		FontDraw(NumConversion(*m_Facility_next_Mat_type[Facility_Level - 1]), 338.0f, 510.0f, 15.0f, 25.0f, black, true);

		//���{��(���ɁA������)�̎���LVUP�ɕK�v�ȑf�ސ���\��
		FontDraw(NumConversion(m_Facility_next_Mat_num[Facility_Level - 1]), 420.0f, 510.0f, 15.0f, 25.0f, black, true);

		//���u���� / �K�v�v�̒l����؂�d�؂�\��
		FontDraw(L"�^", 354.0f, 475.0f, 20.0f, 25.0f, black, false);
		FontDraw(L"�^", 354.0f, 510.0f, 20.0f, 25.0f, black, false);

		//�����x��UP�\���̏���
		if (g_Player_max_size > m_Facility_next_Size_num[Facility_Level - 1] &&
			*m_Facility_next_Mat_type[Facility_Level - 1] >= m_Facility_next_Mat_num[Facility_Level - 1])
		{
			//��LvUP�\!�����摜�\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 607.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 545.0f;
			dst.m_left = 245.0f;
			dst.m_right = 355.0f;
			dst.m_bottom = 570.0f;
			Draw::Draw(70, &src, &dst, blue, 0.0f);
		}
		//�����x��UP�s���̏���
		else
		{
			//��LvUP�s�����摜�\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 577.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 545.0f;
			dst.m_left = 245.0f;
			dst.m_right = 345.0f;
			dst.m_bottom = 570.0f;
			Draw::Draw(71, &src, &dst, red, 0.0f);


			//�ȉ��̃��b�Z�[�W�͌��݂̃T�C�Y(HP)�����x��UP�ɕK�v�ȃT�C�Y(HP)�ȉ��������ꍇ�̂ݕ\������
			if (g_Player_max_size <= m_Facility_next_Size_num[Facility_Level - 1])
			{
				//��"���f��HP��0�ȉ��ɂȂ�ꍇ"�����摜�\��
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 1577.0f;
				src.m_bottom = 112.0f;

				dst.m_top = 580.0f;
				dst.m_left = 167.5f;
				dst.m_right = 433.0f;
				dst.m_bottom = 605.0f;
				Draw::Draw(106, &src, &dst, red, 0.0f);

				//��"LvUP�͏o���܂���"�����摜�\��
				src.m_top = 0.0f;
				src.m_left = 1577.0f;
				src.m_right = 2639.0f;
				src.m_bottom = 112.0f;

				dst.m_top = 615.0f;
				dst.m_left = 212.5f;
				dst.m_right = 398.0f;
				dst.m_bottom = 640.0f;
				Draw::Draw(106, &src, &dst, red, 0.0f);
			}
		}
	}
}