//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"

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
			Draw::LoadImage(L"TitleBackgroundTest.jpg", 7 * (((int)((g_Bar_Level + g_Ins_Level) / 2)) - 1), TEX_SIZE_512);

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
	src.m_right = 960.0f;
	src.m_bottom = 638.0f;

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
		src.m_right = 62.0f;
		src.m_bottom = 62.0f;

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

//---Facility_message�֐�
//����1�@int Facility_Level	:���݂̎{��(����or������)���x��
//�����e
//���݂̎{��(����or������)���x�����l������
//�K�v�f��&�T�C�Y���b�Z�[�W��`�悷��B
void CObjTraining::Facility_message(int Facility_Level)
{
	//���{��(���ɁA������)�K�v�f��&�T�C�Y�t�H���g�p
	float Facility_message_font[FACILITY_MES_MAX_FONT_LINE][4] =
	{
		{ 0.0f,0.0f,1.0f,1.0f },//1�s�ڂ͐F
		{ 0.0f,0.0f,0.0f,1.0f },//2�s�ڂ͍��F
		{ 0.0f,0.0f,0.0f,1.0f },//3�s�ڂ͍��F
		{ 0.0f,0.0f,0.0f,1.0f },//4�s�ڂ͐ԐF�A�܂��͐F(�ȉ��̏����ŕύX����)
		{ 1.0f,0.0f,0.0f,1.0f },//5�s�ڂ͐ԐF
		{ 1.0f,0.0f,0.0f,1.0f },//6�s�ڂ͐ԐF
	};


	//���{�݃��x��MAX���̏���
	if (Facility_Level == FACILITY_MAX_LV)
	{
		//�{�ݕK�v�f��&�T�C�Y���b�Z�[�W�ݒ�
		swprintf_s(m_Facility_message[0], L"LvUP����  ����/  �K�v");	//�����z��ɕ����f�[�^������
		swprintf_s(m_Facility_message[1], L"�ő僌�x�����B�I");			//�����z��ɕ����f�[�^������
		swprintf_s(m_Facility_message[2], L"����ȏ�LVUP�s�ł��B");	//�����z��ɕ����f�[�^������
		swprintf_s(m_Facility_message[3], L"");							//�����f�[�^���N���A����
		swprintf_s(m_message_Mat_name, L"");							//�����f�[�^���N���A����
	}

	//���{�݃��x��MAX�ł͂Ȃ����̏���
	else
	{
		//���{�ݕK�v�f��&�T�C�Y���b�Z�[�W�ݒ�(���ʏ���)
		swprintf_s(m_Facility_message[0], L"LvUP����  ����/  �K�v");																						//�����z��ɕ����f�[�^������
		swprintf_s(m_Facility_message[1], L"�f��HP  %6.0f/%6.0f", g_Player_max_size, m_Facility_next_Size_num[Facility_Level - 1]);							//�����z��ɕ����f�[�^������
		swprintf_s(m_Facility_message[2], L"        %6d/%6d", *m_Facility_next_Mat_type[Facility_Level - 1], m_Facility_next_Mat_num[Facility_Level - 1]);	//�����z��ɕ����f�[�^������
		swprintf_s(m_message_Mat_name, L"%s", m_Facility_next_Mat_name[Facility_Level - 1]);																//�����z��ɕ����f�[�^������


		//�����x��UP�\���̏���
		if (g_Player_max_size > m_Facility_next_Size_num[Facility_Level - 1] &&
			*m_Facility_next_Mat_type[Facility_Level - 1] >= m_Facility_next_Mat_num[Facility_Level - 1])
		{
			//�{�ݕK�v�f��&�T�C�Y���b�Z�[�W�ݒ�
			swprintf_s(m_Facility_message[3], L"      LvUP�\!");	//�����z��ɕ����f�[�^������
			swprintf_s(m_Facility_message[4], L"");					//�����f�[�^���N���A����
			swprintf_s(m_Facility_message[5], L"");					//�����f�[�^���N���A����

			//�{�ݕK�v�f��&�T�C�Y���b�Z�[�W4�s�ڂ̃J���[��F�ɐݒ�
			Facility_message_font[3][0] = 0.0f;
			Facility_message_font[3][2] = 1.0f;
		}
		//�����x��UP�s���̏���
		else
		{
			//�{�ݕK�v�f��&�T�C�Y���b�Z�[�W�ݒ�
			swprintf_s(m_Facility_message[3], L"      LvUP�s��");	//�����z��ɕ����f�[�^������
			
			//�ȉ��̃��b�Z�[�W�͌��݂̃T�C�Y(HP)�����x��UP�ɕK�v�ȃT�C�Y(HP)�ȉ��������ꍇ�̂ݕ\������
			if (g_Player_max_size <= m_Facility_next_Size_num[Facility_Level - 1])
			{
				swprintf_s(m_Facility_message[4], L"���f��HP��0�ȉ��ɂȂ�");	//�����z��ɕ����f�[�^������
				swprintf_s(m_Facility_message[5], L"�ꍇLvUP�͏o���܂���");		//�����z��ɕ����f�[�^������
			}
			else
			{
				swprintf_s(m_Facility_message[4], L"");	//�����f�[�^���N���A����
				swprintf_s(m_Facility_message[5], L"");	//�����f�[�^���N���A����
			}
		
			//�{�ݕK�v�f��&�T�C�Y���b�Z�[�W4�s�ڂ̃J���[��ԐF�ɐݒ�
			Facility_message_font[3][0] = 1.0f;
			Facility_message_font[3][2] = 0.0f;
		}
	}


	//���`�揈��
	//�f�ޖ����������t�H���g�\��
	for (int i = 0; i < FACILITY_MES_MAX_FONT_LINE; i++)
	{
		Font::StrDraw(m_Facility_message[i], 167.5f, 440.0f + i * 35.0f, 25.0f, Facility_message_font[i]);
	}

	//�f�ޖ��̃t�H���g�\��
	Font::StrDraw(m_message_Mat_name, 167.5f, 514.0f, 17.5f, Facility_message_font[2]);
}



//�����̊֐������A�܂��ł��ĂȂ��B

//���������������t�H���g�������łɎw��ꏊ(x,y,size)�ɐF���߂�(color)�\�����Ă����֐�

//����|�b�h�E�C���h�E�̕K�v���ސ��A�e�{�݂̃��x���A�b�v�ɕK�v��HP���Ƃ������A
//���l���ϓ����镔���̃t���[�t�H���g�`����y�ɂ���ׂɍ쐬�����֐��B
void CObjTraining::FontDraw(int id, int conversion, float x, float y, float x_size, float y_size, float color[4])
{
	#define WIDTH_DATA_NUM (10)//���p�S�p�f�[�^���̐�

	//�����̔��p�S�p�f�[�^���
	//�����p���S�p�ɕϊ��̍ۂɎg�p�B
	wchar_t halfwidth_data[WIDTH_DATA_NUM] = { L'0',L'1',L'2',L'3',L'4',L'5',L'6',L'7',L'8',L'9' };
	wchar_t fullwidth_data[WIDTH_DATA_NUM] = { L'�O',L'�P',L'�Q',L'�R',L'�S',L'�T',L'�U',L'�V',L'�W',L'�X' };

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu



	//������(int)������(wchar_t)������
	//�����łɕ����̏I��蕔���Ɉ�(�G)������
	swprintf_s(font[id], L"%d�G", conversion);

	//������������������̒������擾	
	for (int i = 0; font[id][i] != L'�G'; i++)
	{
		length = i + 1;
	}

	//�����p���S�p�ϊ�����
	for (int i = 0; i <= length; i++)
	{
		for (int j = 0; j <= WIDTH_DATA_NUM; j++)
		{
			//���������������ƈ�v���锼�p�f�[�^��T���A
			//�����������ƁA���̔z�񕔕��ɔ��p�ɑΉ�����S�p�f�[�^������B
			if (font[id][i] == halfwidth_data[j])
			{
				font[id][i] = fullwidth_data[j];
				
				break;//�S�p�f�[�^�������̂ŁA���p���S�p�ϊ��������甲����
			}
		}
	}

	FontDraw(id, font[id], x, y, x_size, y_size, color);//�������A�S�p�������ׁA�ʏ��FontDraw�̏����ɓ����
}



//�����̊֐������A�܂��ł��ĂȂ��B

//���b�Z�[�W���͕K���S�p������p���鎖�B
//���p�����A�t�H���g�f�[�^�ɓo�^����ĂȂ��������͎g�p�s�Ȃ̂Œ��ӁB(���͂���Ƌ󔒈����ƂȂ�)
void CObjTraining::FontDraw(int id, wchar_t *conversion, float x, float y, float x_size, float y_size, float color[4])
{
	draw_x[id] = x;
	draw_y[id] = y;
	draw_x_size[id] = x_size;
	draw_y_size[id] = y_size;

	//�t�H���g�f�[�^���
	//���z��ʒu�����̂܂ܐ؂���ʒu�ƂȂ�ׁA�t�H���g�摜�̔z�u�Ɠ����悤�ɕ����o�^����悤��
	wchar_t font_data[FONT_DATA_Y][FONT_DATA_X] =
	{
		{ L'��',L'��',L'��',L'��',L'��',L'�A',L'�C',L'�E',L'�G',L'�I' },
		{ L'��',L'��',L'��',L'��',L'��',L'�J',L'�L',L'�N',L'�P',L'�R',L'��',L'��',L'��',L'��',L'��',L'�K',L'�M',L'�O',L'�Q',L'�S' },
		{ L'��',L'��',L'��',L'��',L'��',L'�T',L'�V',L'�X',L'�Z',L'�\',L'��',L'��',L'��',L'��',L'��',L'�U',L'�W',L'�Y',L'�[',L'�]' },
		{ L'��',L'��',L'��',L'��',L'��',L'�^',L'�`',L'�c',L'�e',L'�g',L'��',L'��',L'��',L'��',L'��',L'�_',L'�a',L'�d',L'�f',L'�h' },
		{ L'��',L'��',L'��',L'��',L'��',L'�i',L'�j',L'�k',L'�l',L'�m' },
		{ L'��',L'��',L'��',L'��',L'��',L'�n',L'�q',L'�t',L'�w',L'�z',L'��',L'��',L'��',L'��',L'��',L'�o',L'�r',L'�u',L'�x',L'�{' },
		{ L'��',L'��',L'��',L'��',L'��',L'�}',L'�~',L'��',L'��',L'��' },
		{ L'��',L'��',L'��',L'��',L'��',L'��' },
		{ L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��' },
		{ L'��',L'��',L'��',L'��',L'��',L'��' },
		{ L'�~',L'��',L'�F',L'�{',L'�|',L'�c',L'�B',L'�I',L'�H',L'�A',L'��',L'�D',L'��',L'�O',L'�P',L'�Q',L'�R',L'�S',L'�T',L'�U',L'�V',L'�W',L'�X',L'��',L'��',L'�O',L'�l',L'��',L'�Z',L'��',L'��',L'��',L'��' },
		{ L'��',L'��',L'�l',L'��',L'��',L'��',L'�R',L'�c',L'��',L'�G',L'�f',L'��',L'��',L'��',L'�s',L'��',L'��',L'��',L'�O',L'�s' },
		{ L'��',L'��',L'��',L'�v',L'��',L'��',L'�z',L'��',L'��',L'��',L'�U',L'��',L'�X',L'��',L'��',L'��',L'�K',L'�E',L'�Z',L'��',L'��',L'�H',L'�D' },
		{ L'��',L'��',L'��',L'��',L'�C',L'�d',L'��',L'��',L'�o',L'��',L'��',L'��',L'�Z',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��' },
		{ L'�L',L'��',L'�s',L'��',L'��',L'��',L'��',L'�D',L'�F',L'��',L'��',L'�@',L'��',L'�P',L'��',L'�p',L'��',L'��',L'��',L'�^',L'��',L'��' },
		{ L'�z',L'��',L'�t',L'��',L'��',L'��',L'�m',L'��',L'��',L'��',L'��',L'��',L'��',L'�F',L'��',L'��',L'��',L'�o',L'�K',L'��',L'�l' },
		{ L'�f',L'��',L'��',L'��',L'�z',L'�u',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��' },
		{ L'��',L'�l',L'��',L'�W',L'��',L'�D',L'��',L'��',L'��',L'�e',L'��',L'��',L'�~',L'�c',L'��',L'�c',L'��',L'��',L'��',L'�f',L'�D' },
		{ L'��',L'�@',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'�p',L'��',L'�v',L'��',L'��',L'��',L'�U',L'��',L'�Y',L'��',L'��',L'��' },
		{ L'��',L'��',L'��',L'��',L'�x',L'��',L'��',L'�\',L'��',L'��',L'�x',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'�I',L'��' },
		{ L'�Q',L'��',L'��',L'�U',L'��',L'��',L'�F',L'�o',L'��',L'�v',L'��',L'��',L'��',L'��',L'�q',L'��',L'��',L'��',L'��',L'�U',L'��' },
		{ L'��',L'�W',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'�N',L'��',L'��',L'��',L'�S',L'�x',L'�V',L'��' },
	};

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu

	//�������̏I��蕔���Ɉ�(�G)������
	swprintf_s(font[id], L"%s�G", conversion);

	//������������������̒������擾	
	for (int i = 0; font[id][i] != L'�G'; i++)
	{
		length = i + 1;
	}

	//���t�H���g�\������
	//������̒���(�����̐�)���A�t�H���g�\���������s��
	//���t�H���g�P�P��for���ŕ����̑������񂵂āA�\�����Ă���B
	for (int i = 0; i <= length; i++)
	{
		//�t�H���g�f�[�^�ǂݍ��ݏ���
		//���\���������������������W.png�̂ǂ��ɂ��邩����
		for (int j = 0; j < FONT_DATA_Y; j++)
		{
			for (int k = 0; k < FONT_DATA_X; k++)
			{
				//�t�H���g�f�[�^�̒[���ɓ��B����ƁA���̍s�Ɉڂ鏈��
				if (font_data[j][k] == NULL)
				{
					break;
				}
				//����HIT������A���̐؂���ʒu��������
				else if (font[id][i] == font_data[j][k])
				{
					font_column[id][i] = k + 1;
					font_line[id][i] = j + 1;

					break;//����HIT�����̂ŁA�t�H���g�f�[�^�ǂݍ��ݏ������甲����
				}
			}

			//�����I�����Ă���΁A�t�H���g�f�[�^�ǂݍ��ݏ������甲����
			if (font_column[i] != 0 || font_line[i] != 0)
			{
				break;
			}
		}

		//���t�H���g�\��
		src.m_top = FONT_CLIP_SIZE * (font_line[id][i] - 1);
		src.m_left = FONT_CLIP_SIZE * (font_column[id][i] - 1);
		src.m_right = FONT_CLIP_SIZE * font_column[id][i];
		src.m_bottom = FONT_CLIP_SIZE * font_line[id][i];

		dst.m_top = draw_y[id];
		dst.m_left = draw_x[id] + (draw_x_size[id] * i);
		dst.m_right = draw_x[id] + (draw_x_size[id] * (i + 1));
		dst.m_bottom = draw_y[id] + (draw_y_size[id]);

		//�ȉ��̓t�H���g�؂���ʒu(��A�s)�̂ǂ��炩��0�����͂���Ă����ꍇ�A
		//���̃t�H���g��\�����Ȃ������B
		if (src.m_right == 0.0f || src.m_bottom == 0.0f)
		{
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 0.0f;
			src.m_bottom = 0.0f;

			dst.m_top = 0.0f;
			dst.m_left = 0.0f;
			dst.m_right = 0.0f;
			dst.m_bottom = 0.0f;
		}

		//�ǂݍ��ݔԍ�121�Ԃɔ������W.png�̉摜��������ΐ���ɓ��삵�Ȃ��̂Œ��ӁB
		Draw::Draw(121, &src, &dst, color, 0.0f);
	}
}
