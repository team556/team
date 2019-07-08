//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjWarehouse.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�}�N��
#define INI_ALPHA (0.0f) //���ߓx(�A���t�@�l)�̏����l
#define INI_COLOR (0.9f) //�S�J���[���x�̏����l

//�O���[�o���ϐ��̒�`
//int g_Ware = 1;


//�C�j�V�����C�Y
void CObjWarehouse::Init()
{
	m_Ware_color = INI_COLOR;			//�q�ɃI�u�W�F�N�g�J���[
	m_Back_Button_color = INI_COLOR;	//�߂�{�^���J���[
	m_object_ma = INI_COLOR;			//���ފm�F�{�^���J���[
	m_object_re = INI_COLOR;			//�Z���m�F�{�^���J���[
	m_object_sp = INI_COLOR;			//�X�y�V�����Z�m�F�{�^���J���[
	m_object_eq = INI_COLOR;			//�����m�F�{�^���J���[

	m_key_lf = false;
	m_key_rf = false;

	//�����蔻��pHitBox���쐬(Objhuman�p)
	Hits::SetHitBox(this, 95, 170, 225, 110, ELEMENT_ENEMY, OBJ_WAREHOUSE, 1);
}

//�A�N�V����
void CObjWarehouse::Action()
{
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

	//���q�ɃE�B���h�E�\���̏���
	if (window_start_manage == Warehouse)
	{
		//�߂�{�^�����N���b�N�A�������͉E�N���b�N(�ǂ��ł�)���鎖�ł��̃E�C���h�E�����
		if (30 < m_mou_x && m_mou_x < 80 && 30 < m_mou_y && m_mou_y < 80 || m_mou_r == true)
		{
			m_Back_Button_color = 1.0f;
			//���N���b�N���ꂽ��t���O�𗧂āA���̃E�C���h�E�����
			//�E�N���b�N���͎�
			if (m_mou_r == true)
			{
				//�O�V�[��(�ŏI�m�F�E�C���h�E)����E�N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
				if (m_key_rf == true)
				{
					//�E�C���h�E������A�����Ė߂�{�^������͂��Ȃ��悤��static�ϐ���false�����Đ���
					m_key_rf = false;

					//����K�v�f��&�l�����b�Z�[�W���\���ɂ��邽�߁A���ߓx��0.0f�ɂ���
					m_alpha = 0.0f;

					//"�q�ɃE�C���h�E���J���Ă�����"�t���O�𗧂Ă�
					window_start_manage = Default;

					//ObjHelp�𑀍�\�ɂ��� & ���ߓx1.0f�ɂ��ĕ\������
					CObjHelp* help = (CObjHelp*)Objs::GetObj(OBJ_HELP);
					help->SetOperatable(true);
					help->SetAlpha(1.0f);

					//�߂�{�^����
					Audio::Start(2);
				}
			}

			//���N���b�N���ꂽ��t���O�𗧂āA�q�ɃE�C���h�E�����
			else if (m_mou_l == true)
			{
				//�N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
				if (m_key_lf == true)
				{
					m_key_lf = false;

					//"�ǂ̃E�C���h�E���J���Ă��Ȃ����"�t���O�𗧂Ă�
					window_start_manage = Default;

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
			m_introduce_f = false;//�{�ݏЉ�E�B���h�E���\���ɂ���
			m_Back_Button_color = INI_COLOR;
		}

		//���ރ{�^���I��
		if (90 < m_mou_x && m_mou_x < 600 && 80 < m_mou_y && m_mou_y < 350)
		{
			m_object_ma = 1.0f;
			//���N���b�N���ꂽ��t���O�𗧂āA���ރE�C���h�E���J��
			if (m_mou_l == true)
			{
				//�N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
				if (m_key_lf == true)
				{
					m_key_lf = false;

					//"���ރE�B���h�E���J���Ă�����"�t���O�𗧂Ă�
					window_start_manage = Materials;

					//�I����
					Audio::Start(1);
				}
			}
			else
			{
				m_key_lf = true;
			}

		}
		else
		{
			m_object_ma = INI_COLOR;

		}

		//�Z���{�^���I��
		if (610 < m_mou_x && m_mou_x < 1120 && 80 < m_mou_y && m_mou_y < 350)
		{
			m_object_re = 1.0f;
			//���N���b�N���ꂽ��t���O�𗧂āA�Z���E�C���h�E���J��
			if (m_mou_l == true)
			{
				//�N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
				if (m_key_lf == true)
				{
					m_key_lf = false;

					//"�Z���E�B���h�E���J���Ă�����"�t���O�𗧂Ă�
					window_start_manage = Residents;

					//�I����
					Audio::Start(1);
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
		else
		{
			m_object_re = INI_COLOR;

		}

		//�X�y�V�����Z�{�^���I��
		if (90 < m_mou_x && m_mou_x < 600 && 360 < m_mou_y && m_mou_y < 630)
		{
			m_object_sp = 1.0f;
			//���N���b�N���ꂽ��t���O�𗧂āA�X�y�V�����Z�E�C���h�E���J��
			if (m_mou_l == true)
			{
				//�N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
				if (m_key_lf == true)
				{
					m_key_lf = false;

					//"�X�y�V�����Z�E�B���h�E���J���Ă�����"�t���O�𗧂Ă�
					window_start_manage = Specialskill;

					//�I����
					Audio::Start(1);
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
		else
		{
			m_object_sp = INI_COLOR;

		}

		//�����{�^���I��
		if (610 < m_mou_x && m_mou_x < 1120 && 360 < m_mou_y && m_mou_y < 630)
		{
			m_object_eq = 1.0f;
			//���N���b�N���ꂽ��t���O�𗧂āA�����E�C���h�E���J��
			if (m_mou_l == true)
			{
				//�N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
				if (m_key_lf == true)
				{
					m_key_lf = false;

					//"�����E�B���h�E���J���Ă�����"�t���O�𗧂Ă�
					window_start_manage = Soubicheck;

					//�I����
					Audio::Start(1);
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
		else
		{
			m_object_eq = INI_COLOR;
		}

		return;
	}

	//���ށA�Z���A�X�y�V�����Z�A������ʂ̖߂�{�^��
	if (window_start_manage == Materials || window_start_manage == Residents ||
		window_start_manage == Specialskill || window_start_manage == Soubicheck)
	{
		//�߂�{�^���I��
		if (50 < m_mou_x && m_mou_x < 100 && 50 < m_mou_y && m_mou_y < 100 || m_mou_r == true)
		{
			m_Back_Button_color = 1.0f;
			//���N���b�N���ꂽ��t���O�𗧂āA���̃E�C���h�E�����
			//�E�N���b�N���͎�
			if (m_mou_r == true)
			{
				//�O�V�[��(�ŏI�m�F�E�C���h�E)����E�N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
				if (m_key_rf == true)
				{
					//�E�C���h�E������A�����Ė߂�{�^������͂��Ȃ��悤��static�ϐ���false�����Đ���
					m_key_rf = false;

					//����K�v�f��&�l�����b�Z�[�W���\���ɂ��邽�߁A���ߓx��0.0f�ɂ���
					m_alpha = 0.0f;

					//"�������E�C���h�E���J���Ă�����"�t���O�𗧂Ă�
					window_start_manage = Warehouse;

					//�߂�{�^����
					Audio::Start(2);
				}
			}

			//���N���b�N���ꂽ��t���O�𗧂āA�q�ɃE�C���h�E�����
			if (m_mou_l == true)
			{
				//�߂�{�^����
				//Audio::Start(2);
				//�N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
				if (m_key_lf == true)
				{
					m_key_lf = false;

					//"�ǂ̃E�C���h�E���J���Ă��Ȃ����"�t���O�𗧂Ă�
					window_start_manage = Warehouse;

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

	//�z�[����ʂɖ߂�{�^���������ꂽ��A
	//���{�݂̃E�C���h�E���J���Ă��鎞�͑�����󂯕t���Ȃ��悤�ɂ���B
	if (window_start_manage != Default || g_help_f == true)
	{
		m_introduce_f = false;	//�{�ݏЉ�E�C���h�E���\���ɂ���(�E�N���b�N�Ńz�[����ʂɖ߂�ہA�E�C���h�E���c��Ȃ��悤�ɂ��邽��)
		return;
	}

	//�q�ɑI��
	if (95 < m_mou_x && m_mou_x < 320 && 170 < m_mou_y && m_mou_y < 280)
	{
		m_introduce_f = true;	//�{�ݏЉ�E�B���h�E��\������
		m_Ware_color = 1.0f;
		//���N���b�N���ꂽ��t���O�𗧂āA�q�ɃE�C���h�E���J��
		if (m_mou_l == true)
		{
			//�N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
			if (m_key_lf == true)
			{
				m_key_lf = false;

				m_introduce_f = false;//�{�ݏЉ�E�B���h�E���\���ɂ���

				//�q�ɂ��N���b�N����ƁA�q�ɂ��J�����
				window_start_manage = Warehouse;

				//ObjHelp�𑀍�s�\�ɂ��� & ���ߓx0.0f�ɂ��Ĕ�\���ɂ���
				CObjHelp* help = (CObjHelp*)Objs::GetObj(OBJ_HELP);
				help->SetOperatable(false);
				help->SetAlpha(0.0f);

				//�I����
				Audio::Start(1);
			}
		}
		else
		{
			m_key_lf = true;
		}
	}
	else
	{
		m_introduce_f = false;//�{�ݏЉ�E�C���h�E���\���ɂ���
		m_Ware_color = INI_COLOR;
	}
}

//�h���[
void CObjWarehouse::Draw()
{
	//���V�[���؂�ւ����o��ɔ�\���ɂ��鏈��
	if (scene_change_start == true)
	{
		return;
	}

	//�q�ɉ摜
	float wh[4] = { m_Ware_color,m_Ware_color, m_Ware_color, 1.0f };

	//�I�u�W�F�N�g�N���b�N����O�̔w�i�I�u�W�F�N�g
	float h[4] = { 1.0f,1.0f,1.0f,1.0f };

	//����ȊO�̉摜
	//�w�i�I�u�W�F�N�g
	float sb[4] = { 1.0f,1.0f,1.0f,1.0f };

	//�߂�{�^���摜
	float md[4] = { m_Back_Button_color,m_Back_Button_color,m_Back_Button_color,1.0f };

	//���ރ{�^���摜
	float ma[4] = { m_object_ma,m_object_ma,m_object_ma ,1.0f };

	//�Z���{�^���摜
	float re[4] = { m_object_re,m_object_re,m_object_re,1.0f };

	//�X�y�V�����Z�{�^���摜
	float sp[4] = { m_object_sp,m_object_sp,m_object_sp,1.0f };

	//�����{�^���摜
	float eq[4] = { m_object_eq,m_object_eq,m_object_eq,1.0f };

	//���ށE���F�E�B���h�E�摜
	float it[4] = { 1.0f,1.0f,1.0f,1.0f };

	//���F�����̑��摜�p
	float white[4] = { 1.0f,1.0f,1.0f,1.0f };

	//���F
	float black[4] = { 0.0f,0.0f,0.0f,1.0f };

	//�t�H���g�̐F
	float ware[4] = { 1.0f,1.0f,1.0f,1.0f };

	//�ԐF
	float red[4] = { 1.0f,0.0f,0.0f,1.0f };

	//�F
	float blue[4] = { 0.0f,0.0f,1.0f,1.0f };

	//�ΐF
	float green[4] = { 0.0f,1.0f,0.0f,1.0f };

	//���F
	float yellow[4] = { 1.0f,1.0f,0.0f,1.0f };

	//�D�F
	float gray[4] = { 0.4f,0.4f,0.4f,1.0f };

	//���t�H���g����
	//�q�ɗp
	wchar_t Ware[5];
	swprintf_s(Ware, L"�q��");

	//����(���O�E�����Ă��鐔)�\��
	wchar_t mrl[7][9];
	swprintf_s(mrl[0], L"%d ��", g_Wood_num);
	swprintf_s(mrl[1], L"%d ��", g_Iron_num);
	swprintf_s(mrl[2], L"%d ��", g_Silver_num);
	swprintf_s(mrl[3], L"%d ��", g_Plastic_num);
	swprintf_s(mrl[4], L"%d ��", g_Aluminum_num);
	swprintf_s(mrl[5], L"%d ��", g_gus_num);
	swprintf_s(mrl[6], L"%d ��", g_Raremetal_num);

	//�Z�����\��
	//�e�^�C�v(�p���[�A�X�s�[�h��)�̏Z�����p
	wchar_t human_num[4][9];						 //9�������i�[�\�ȕ����z���4�錾(���ꂼ��ő�l��999999)
	swprintf_s(human_num[0], L"%6d �l", g_Power_num);//�����ꂼ��̕����z��ɑΉ����镶���f�[�^������
	swprintf_s(human_num[1], L"%6d �l", g_Defense_num);
	swprintf_s(human_num[2], L"%6d �l", g_Speed_num);
	swprintf_s(human_num[3], L"%6d �l", g_Balance_num);
	//����
	//�e�^�C�v(�p���[�A�X�s�[�h��)�̌��݂̃��x���\��
	wchar_t type_num[5][9];						 //9�������i�[�\�ȕ����z���4�錾(���ꂼ��ő�l��999999)
	swprintf_s(type_num[0], L"Lv.%d ", g_Pow_equip_Level);//�����ꂼ��̕����z��ɑΉ����镶���f�[�^������
	swprintf_s(type_num[1], L"Lv.%d ", g_Def_equip_Level);
	swprintf_s(type_num[2], L"Lv.%d ", g_Spe_equip_Level);
	swprintf_s(type_num[3], L"Lv.%d ", g_Bal_equip_Level);
	swprintf_s(type_num[4], L"Lv.%d ", g_Pod_equip_Level);

	//�������̏Z�����p
	wchar_t Research_num[9];						 //9�������i�[�\�ȕ����z���錾(�ő�l��999999)
	swprintf_s(Research_num, L"%6d �l", g_Research_num);//���̕����z��ɕ����f�[�^������

	//�c��Z�����p
	wchar_t human_remain[12];						 //12�������i�[�\�ȕ����z���錾(�ő�l��999999)
	swprintf_s(human_remain, L"�c�� %6d �l", g_Remain_num);//���̕����z��ɕ����f�[�^������

	RECT_F src;//�`���؂���ʒu
	RECT_F dst;//�`���\���ʒu

	//�{�ݏЉ�E�B���h�E(���ɁA�������A�q��)���J���Ă��Ȃ����ɕ\������O���t�B�b�N
	if (window_start_manage == Default || window_start_manage == BackButton)
	{
		//���q�ɕ\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 402.0f;
		src.m_bottom = 332.0f;

		dst.m_top = 100.0f;
		dst.m_left = 100.0f;
		dst.m_right = 325.0f;
		dst.m_bottom = 325.0f;
		Draw::Draw(27, &src, &dst, wh, 0.0f);

		//�{�ݏЉ�E�C���h�E�\���Ǘ��t���O��true�̎��A�`��B
		if (m_introduce_f == true)
		{
			//���{�ݏЉ�E�C���h�E�\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 64.0f;
			src.m_bottom = 64.0f;

			dst.m_top = m_mou_y - 50.0f;
			dst.m_left = m_mou_x - 120.0f;
			dst.m_right = m_mou_x + 110.0f;
			dst.m_bottom = m_mou_y - 10.0f;
			Draw::Draw(21, &src, &dst, ware, 0.0f);//�D�F�̃E�C���h�E�ɂ����"ins"�ɂ��Ă���B

		    //���q�ɕ����摜�\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 242.0f;
			src.m_bottom = 117.0f;

			dst.m_top = m_mou_y - 43.0f;
			dst.m_left = m_mou_x - 50.0f;
			dst.m_right = m_mou_x + 30.0f;
			dst.m_bottom = m_mou_y - 15.0f;
			Draw::Draw(88, &src, &dst, black, 0.0f);

		    //���t�H���g�\��
		    //�q��
			//Font::StrDraw(Ware, m_mou_x - 40.0f, m_mou_y - 45.0f, 30.0f, black);

		}
}

	//�q�ɂ��N���b�N������
	else if (window_start_manage == Warehouse)
	{
		//���D�F�E�B���h�E�\��
		src.m_top    =    0.0f;
		src.m_left   =    0.0f;
		src.m_right  = 1160.0f;
		src.m_bottom =  660.0f;

		dst.m_top    =   20.0f;
		dst.m_left   =   20.0f;
		dst.m_right  = 1180.0f;
		dst.m_bottom =  680.0f;
		Draw::Draw(20, &src, &dst, sb, 0.0f);

		//���߂�A�C�R���\��
		src.m_top    =   0.0f;
		src.m_left   =   0.0f;
		src.m_right  = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top    =  30.0f;
		dst.m_left   =  30.0f;
		dst.m_right  =  80.0f;
		dst.m_bottom =  80.0f;
		Draw::Draw(1, &src, &dst, md, 0.0f);

		//�����ޑI���{�^���\��
		src.m_top    = 0.0f;
		src.m_left   = 0.0f;
		src.m_right  = 307.0f;
		src.m_bottom = 175.0f;

		dst.m_top    = 80.0f;
		dst.m_left   = 90.0f;
		dst.m_right  = 600.0f;
		dst.m_bottom = 350.0f;
		Draw::Draw(28, &src, &dst, ma, 0.0f);

		//���Z���I���{�^���\��
		src.m_top	 = 0.0f;
		src.m_left	 = 0.0f;
		src.m_right	 = 307.0f;
		src.m_bottom = 175.0f;

		dst.m_top    = 80.0f;
		dst.m_left   = 610.0f;
		dst.m_right  = 1120.0f;
		dst.m_bottom = 350.0f;
		Draw::Draw(29, &src, &dst, re, 0.0f);

		//���X�y�V�����Z�I���{�^���\��
		src.m_top	 = 0.0f;
		src.m_left   = 0.0f;
		src.m_right	 = 307.0f;
		src.m_bottom = 175.0f;

		dst.m_top    = 360.0f;
		dst.m_left   = 90.0f;
		dst.m_right  = 600.0f;
		dst.m_bottom = 630.0f;
		Draw::Draw(30, &src, &dst, sp, 0.0f);

		//�������I���{�^���\��
		src.m_top	 = 0.0f;
		src.m_left	 = 0.0f;
		src.m_right  = 307.0f;
		src.m_bottom = 175.0f;

		dst.m_top    = 360.0f;
		dst.m_left   = 610.0f;
		dst.m_right  = 1120.0f;
		dst.m_bottom = 630.0f;
		Draw::Draw(31, &src, &dst, eq, 0.0f);
	}

	//�߂�{�^����I�����ĕ`�悷��摜
	else if (window_start_manage == Default || window_start_manage == BackButton)
	{

		//���q�ɕ\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 225.0f;
		src.m_bottom = 225.0f;

		dst.m_top = 100.0f;
		dst.m_left = 100.0f;
		dst.m_right = 325.0f;
		dst.m_bottom = 325.0f;
		Draw::Draw(27, &src, &dst, wh, 0.0f);

		//�{�ݏЉ�E�C���h�E�\���Ǘ��t���O��true�̎��A�`��B
		if (m_introduce_f == true)
		{
			//���{�ݏЉ�E�C���h�E�\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 64.0f;
			src.m_bottom = 64.0f;

			dst.m_top = m_mou_y - 50.0f;
			dst.m_left = m_mou_x - 120.0f;
			dst.m_right = m_mou_x + 110.0f;
			dst.m_bottom = m_mou_y - 10.0f;
			Draw::Draw(21, &src, &dst, ware, 0.0f);//�D�F�̃E�C���h�E�ɂ����"ins"�ɂ��Ă���B

			//���q�ɕ����摜�\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 242.0f;
			src.m_bottom = 117.0f;

			dst.m_top = m_mou_y - 43.0f;
			dst.m_left = m_mou_x - 900.0f;
			dst.m_right = m_mou_x + 40.0f;
			dst.m_bottom = m_mou_y - 18.0f;
			Draw::Draw(88, &src, &dst, black, 0.0f);

		    //���t�H���g�\��
			//�q��
			//Font::StrDraw(Ware, m_mou_x - 95.0f, m_mou_y - 45.0f, 30.0f, black);

		}
	}

	//���ރ{�^���������ĕ`�悷��摜
	else if (window_start_manage == Materials)
	{
		//���D�F�E�B���h�E�\��(�_�~�[�q�ɃE�B���h�E�p)
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1160.0f;
		src.m_bottom = 660.0f;

		dst.m_top = 20.0f;
		dst.m_left = 20.0f;
		dst.m_right = 1180.0f;
		dst.m_bottom = 680.0f;
		Draw::Draw(20, &src, &dst, sb, 0.0f);

		//���D�F�E�B���h�E�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1160.0f;
		src.m_bottom = 660.0f;

		dst.m_top = 40.0f;
		dst.m_left = 40.0f;
		dst.m_right = 1160.0f;
		dst.m_bottom = 660.0f;
		Draw::Draw(20, &src, &dst, sb, 0.0f);

		//���߂�{�^���\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 50.0f;
		dst.m_left = 50.0f;
		dst.m_right = 100.0f;
		dst.m_bottom = 100.0f;
		Draw::Draw(1, &src, &dst, md, 0.0f);

		//�����F�E�B���h�E�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 100.0f;
		src.m_bottom = 100.0f;

		dst.m_top = 100.0f;
		dst.m_left = 100.0f;
		dst.m_right = 1100.0f;
		dst.m_bottom = 600.0f;
		Draw::Draw(32, &src, &dst, it, 0.0f);

		//���؍ޕ\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 717.0f;
		src.m_bottom = 627.0f;

		dst.m_top = 120.0f;
		dst.m_left = 150.0f;
		dst.m_right = 300.0f;
		dst.m_bottom = 270.0f;
		Draw::Draw(33, &src, &dst, it, 0.0f);

		//���؍ޕ����摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 232.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 250.0f;
		dst.m_left = 170.0f;
		dst.m_right = 250.0f;
		dst.m_bottom = 290.0f;
		Draw::Draw(89, &src, &dst, it, 0.0f);

		//Font::StrDraw(L"�؍�", 170.0f, 250.0f,40.0f, black);
		Font::StrDraw(mrl[0], 240.0f, 290.0f, 40.0f, black);

		//���S�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 160.0f;
		src.m_bottom = 160.0f;

		dst.m_top = 120.0f;
		dst.m_left = 450.0f;
		dst.m_right = 600.0f;
		dst.m_bottom = 270.0f;
		Draw::Draw(34, &src, &dst, it, 0.0f);

		//���S�����摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 112.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 250.0f;
		dst.m_left = 540.0f;
		dst.m_right = 580.0f;
		dst.m_bottom = 290.0f;
		Draw::Draw(69, &src, &dst, it, 0.0f);

		//Font::StrDraw(L"�S", 540.0f, 250.0f, 40.0f, black);
		Font::StrDraw(mrl[1], 580.0f, 290.0f, 40.0f, black);

		//����\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 160.0f;
		src.m_bottom = 160.0f;

		dst.m_top = 120.0f;
		dst.m_left = 800.0f;
		dst.m_right = 950.0f;
		dst.m_bottom = 270.0f;
		Draw::Draw(35, &src, &dst, it, 0.0f);

		//���╶���摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 112.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 250.0f;
		dst.m_left = 910.0f;
		dst.m_right = 950.0f;
		dst.m_bottom = 290.0f;
		Draw::Draw(90, &src, &dst, it, 0.0f);

		//Font::StrDraw(L"��", 910.0f, 250.0f, 40.0f, black);
		Font::StrDraw(mrl[2], 950.0f, 290.0f, 40.0f, black);

		//���v���X�`�b�N�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 135.0f;
		src.m_bottom = 245.0f;

		dst.m_top = 350.0f;
		dst.m_left = 110.0f;
		dst.m_right = 260.0f;
		dst.m_bottom = 500.0f;
		Draw::Draw(36, &src, &dst, it, 0.0f);

		//���v���X�`�b�N�����摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 712.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 500.0f;
		dst.m_left = 140.0f;
		dst.m_right = 380.0f;
		dst.m_bottom = 540.0f;
		Draw::Draw(91, &src, &dst, it, 0.0f);

		//Font::StrDraw(L"�v���X�`�b�N", 130.0f, 500.0f, 40.0f, black);
		Font::StrDraw(mrl[3], 240.0f, 540.0f, 40.0f, black);

		//���A���~�j�E���摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 160.0f;
		src.m_bottom = 160.0f;

		dst.m_top = 350.0f;
		dst.m_left = 540.0f;
		dst.m_right = 690.0f;
		dst.m_bottom = 500.0f;
		Draw::Draw(37, &src, &dst, it, 0.0f);

		//���A���~�j�E�������摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 712.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 500.0f;
		dst.m_left = 500.0f;
		dst.m_right = 740.0f;
		dst.m_bottom = 540.0f;
		Draw::Draw(91, &src, &dst, it, 0.0f);

		//Font::StrDraw(L"�A���~�j�E��", 500.0f, 500.0f, 40.0f, black);
		Font::StrDraw(mrl[4], 580.0f, 540.0f, 40.0f, black);

		//���K�X�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 300.0f;
		src.m_bottom = 300.0f;

		dst.m_top = 350.0f;
		dst.m_left = 800.0f;
		dst.m_right = 950.0f;
		dst.m_bottom = 500.0f;
		Draw::Draw(38, &src, &dst, it, 0.0f);

		//���K�X�����摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 232.0f;
		src.m_bottom = 116.0f;

		dst.m_top = 500.0f;
		dst.m_left = 910.0f;
		dst.m_right = 990.0f;
		dst.m_bottom = 540.0f;
		Draw::Draw(93, &src, &dst, it, 0.0f);

		//Font::StrDraw(L"�K�X", 910.0f, 500.0f, 40.0f, black);
		Font::StrDraw(mrl[5], 950.0f, 540.0f, 40.0f, black);
	}

	//�Z���{�^���������ĕ`�悷��摜
	else if (window_start_manage == Residents)
	{
		//���D�F�E�B���h�E�\��(�_�~�[�q�ɃE�B���h�E�p)
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1160.0f;
		src.m_bottom = 660.0f;

		dst.m_top = 20.0f;
		dst.m_left = 20.0f;
		dst.m_right = 1180.0f;
		dst.m_bottom = 680.0f;
		Draw::Draw(20, &src, &dst, sb, 0.0f);

		//���D�F�E�B���h�E�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1160.0f;
		src.m_bottom = 660.0f;

		dst.m_top = 40.0f;
		dst.m_left = 40.0f;
		dst.m_right = 1160.0f;
		dst.m_bottom = 660.0f;
		Draw::Draw(20, &src, &dst, sb, 0.0f);

		//���߂�{�^���\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 50.0f;
		dst.m_left = 50.0f;
		dst.m_right = 100.0f;
		dst.m_bottom = 100.0f;
		Draw::Draw(1, &src, &dst, md, 0.0f);

		//�����F�E�B���h�E�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 100.0f;
		src.m_bottom = 100.0f;

		dst.m_top = 100.0f;
		dst.m_left = 100.0f;
		dst.m_right = 1100.0f;
		dst.m_bottom = 600.0f;
		Draw::Draw(32, &src, &dst, it, 0.0f);
		
		//���c��Z���������܂���(�Z��������)�����摜��\��
		src.m_top = 0.0f;
		src.m_left = 230.0f;
		src.m_right = 600.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 110.0f;
		dst.m_left = 500.0f;
		dst.m_right = 650.0f;
		dst.m_bottom = 160.0f;
		Draw::Draw(94, &src, &dst, black, 0.0f);

		//�����b�h�����摜��\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 336.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 200.0f;
		dst.m_left = 120.0f;
		dst.m_right = 225.0f;
		dst.m_bottom = 235.0f;
		Draw::Draw(82, &src, &dst, red, 0.0f);

		//���u���[�����摜��\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 352.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 330.0f;
		dst.m_left = 120.0f;
		dst.m_right = 225.0f;
		dst.m_bottom = 365.0f;
		Draw::Draw(83, &src, &dst, blue, 0.0f);

		//���O���[�������摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 472.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 470.0f;
		dst.m_left = 120.0f;
		dst.m_right = 330.0f;
		dst.m_bottom = 505.0f;
		Draw::Draw(84, &src, &dst, green, 0.0f);

		//���z���C�g�����摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 464.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 200.0f;
		dst.m_left = 540.0f;
		dst.m_right = 680.0f;
		dst.m_bottom = 235.0f;
		Draw::Draw(85, &src, &dst, black, 0.0f);

		//�������������摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 352.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 330.0f;
		dst.m_left = 540.0f;
		dst.m_right = 645.0f;
		dst.m_bottom = 365.0f;
		Draw::Draw(75, &src, &dst, black, 0.0f);

		//���c��Z���������܂���(�c��Z��������)�����摜��\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 600.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 470.0f;
		dst.m_left = 540.0f;
		dst.m_right = 750.0f;
		dst.m_bottom = 505.0f;
		Draw::Draw(94, &src, &dst, black, 0.0f);

		//���c��@�@�@�l(�c��)���������摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 592.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 470.0f;
		dst.m_left = 780.0f;
		dst.m_right = 990.0f;
		dst.m_bottom = 505.0f;
		Draw::Draw(78, &src, &dst, red, 0.0f);

		//���l�����摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 112.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 470.0f;
		dst.m_left = 995.0f;
		dst.m_right = 1030.0f;
		dst.m_bottom = 505.0f;
		Draw::Draw(77, &src, &dst, red, 0.0f);

		//���t�H���g�\��
		//�Z���X�e�[�^�X

		////�Z����
		//Font::StrDraw(L"�Z����", 500.0f, 110.0f, 50.0f, black);

		////�p���[
		//Font::StrDraw(L"�p���[", 120.0f, 200.0f, 35.0f, red);
		Font::StrDraw(human_num[0], 355.0f, 200.0f, 35.0f, black);

		////�X�s�[�h
		//Font::StrDraw(L"�X�s�[�h", 120.0f, 330.0f, 35.0f, green);
		Font::StrDraw(human_num[1], 355.0f, 330.0f, 35.0f, black);

		////�f�B�t�F���X
		//Font::StrDraw(L"�f�B�t�F���X", 120.0f, 470.0f, 35.0f, blue);
		Font::StrDraw(human_num[2], 355.0f, 470.0f, 35.0f, black);

		////�o�����X
		//Font::StrDraw(L"�o�����X", 540.0f, 200.0f, 35.0f, yellow);
		Font::StrDraw(human_num[3], 865.0f, 200.0f, 35.0f, black);

		////������
		//Font::StrDraw(L"������", 540.0f, 330.0f, 35.0f, black);
		Font::StrDraw(Research_num, 865.0f, 330.0f, 35.0f, black);

		////�c��̏Z����
		//Font::StrDraw(L"�c��̏Z����", 540.0f, 470.0f, 35.0f, black);
		Font::StrDraw(human_remain, 780.0f, 470.0f, 35.0f, red);

	}

	//�X�y�V�����Z�{�^���������ĕ`�悷��摜
	else if (window_start_manage == Specialskill)
	{
		//���D�F�E�B���h�E�\��(�_�~�[�q�ɃE�B���h�E�p)
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1160.0f;
		src.m_bottom = 660.0f;

		dst.m_top = 20.0f;
		dst.m_left = 20.0f;
		dst.m_right = 1180.0f;
		dst.m_bottom = 680.0f;
		Draw::Draw(20, &src, &dst, sb, 0.0f);

		//���D�F�E�B���h�E�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1160.0f;
		src.m_bottom = 660.0f;

		dst.m_top = 40.0f;
		dst.m_left = 40.0f;
		dst.m_right = 1160.0f;
		dst.m_bottom = 660.0f;
		Draw::Draw(20, &src, &dst, sb, 0.0f);

		//���߂�{�^���\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 50.0f;
		dst.m_left = 50.0f;
		dst.m_right = 100.0f;
		dst.m_bottom = 100.0f;
		Draw::Draw(1, &src, &dst, md, 0.0f);

		//�����F�E�B���h�E�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 100.0f;
		src.m_bottom = 100.0f;

		dst.m_top = 100.0f;
		dst.m_left = 100.0f;
		dst.m_right = 1100.0f;
		dst.m_bottom = 600.0f;
		Draw::Draw(32, &src, &dst, it, 0.0f);

		//�X�y�V�����Z1���b�Z�[�W�E�B���h�E�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 200.0f;
		src.m_bottom = 100.0f;

		for (int i = 0; i < 5; i++)//���b�Z�[�W�E�B���h�E��K�؂Ȉʒu�ɂT��\��������
		{
			dst.m_top = 100.0f + ( i * 100 );
			dst.m_left = 235.0f;
			dst.m_right = 1100.0f;
			dst.m_bottom = 200.0f + (i * 100);
			Draw::Draw(45, &src, &dst, it, 0.0f);
		}

		//�X�y�V�����{�^���̋��ʐ؂���ʒu�ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 100.0f;
		src.m_bottom = 100.0f;

		//�����݂̃X�y�V�����Z�K���󋵁A�����󋵂ɉ�����
		//�X�y�V�����Z�A�C�R���̃J���[���x���ȉ��̂悤�ɐݒ肵�Ă����B
		//�u���K���v�c�c�c�c�c�c�c�c�c�c�c0.0f(���F)
		//�u�N���b�N�ő�����(�K����)�v�c�c0.4f(�D�F)
		//�u�������v�c�c�c�c�c�c�c�c�c�c�c1.0f(���F)

		//Explosion�̔���
		//�܂��\��t���ʒu��ݒ肷��
		dst.m_top = 85.0f;
		dst.m_left = 100.0f;
		dst.m_right = 230.0f;
		dst.m_bottom = 215.0f;

		//Explosion���o���Ă���Ȃ��
		if (g_Special_mastering[0] == true)
		{

			//Font::StrDraw(L"����̘f���ɌŒ�_���[�W��^����", 245.0f, 110.0f, 35.0f, black);
			//Font::StrDraw(L"�_���[�W�ʂ͘f���̍��HP��1.2�{�̃_���[�W��^����", 240.0f, 160.0f, 35.0f, black);

			if(g_Special_equipment == 1)
				Draw::Draw(40, &src, &dst, it, 0.0f);
			else
				Draw::Draw(40, &src, &dst, gray, 0.0f);

			//������̘f���ɕ����摜��\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 713.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 135.0f;
			dst.m_left = 245.0f;
			dst.m_right = 455.0f;
			dst.m_bottom = 170.0f;
			Draw::Draw(95, &src, &dst, black, 0.0f);

			//���Œ�_���[�W��^���镶���摜��\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 1182.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 135.0f;
			dst.m_left = 456.0f;
			dst.m_right = 806.0f;
			dst.m_bottom = 170.0f;
			Draw::Draw(96, &src, &dst, black, 0.0f);
		}
		else
		{
			Draw::Draw(40, &src, &dst, black, 0.0f);
		}

		//Fracture Ray�̔���
		//�X�y�V�����{�^���̋��ʐ؂���ʒu�ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 100.0f;
		src.m_bottom = 100.0f;

		//�܂��\��t���ʒu��ݒ肷��
		dst.m_top = 185.0f;
		dst.m_left = 100.0f;
		dst.m_right = 230.0f;
		dst.m_bottom = 315.0f;
		
		//Fracture Ray���o���Ă���Ȃ��
		if (g_Special_mastering[1] == true)
		{
			//Font::StrDraw(L"�I�����C�����", 245.0f, 210.0f, 35.0f, black);
			//Font::StrDraw(L"����|�b�h����j�󂷂�", 240.0f, 260.0f, 35.0f, black);
			if (g_Special_equipment == 2)
				Draw::Draw(41, &src, &dst, it, 0.0f);
			else
				Draw::Draw(41, &src, &dst, gray, 0.0f);

			//���I�����C����̕����摜��\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 832.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 210.0f;
			dst.m_left = 245.0f;
			dst.m_right = 490.0f;
			dst.m_bottom = 245.0f;
			Draw::Draw(97, &src, &dst, black, 0.0f);

			//������|�b�h����j�󂷂镶���摜��\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 1304.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 260.0f;
			dst.m_left = 245.0f;
			dst.m_right = 630.0f;
			dst.m_bottom = 295.0f;
			Draw::Draw(98, &src, &dst, black, 0.0f);


		}
		else
		{
			Draw::Draw(41, &src, &dst, black, 0.0f);
		}

		//Immotality�̔���
		//�X�y�V�����{�^���̋��ʐ؂���ʒu�ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 100.0f;
		src.m_bottom = 100.0f;

		//�܂��\��t���ʒu��ݒ肷��
		dst.m_top = 285.0f;
		dst.m_left = 100.0f;
		dst.m_right = 230.0f;
		dst.m_bottom = 415.0f;

		//Immotality���o���Ă���Ȃ��
		if (g_Special_mastering[2] == true)
		{
			//Font::StrDraw(L"��10�b�Ԗ��G�ɂȂ邱�Ƃ��ł���", 245.0f, 335.0f, 35.0f, black);

			if (g_Special_equipment == 3)
				Draw::Draw(42, &src, &dst, it, 0.0f);
			else
				Draw::Draw(42, &src, &dst, gray, 0.0f);

			//����10�b�Ԃ̕����摜��\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 532.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 335.0f;
			dst.m_left = 245.0f;
			dst.m_right = 420.0f;
			dst.m_bottom = 370.0f;
			Draw::Draw(99, &src, &dst, black, 0.0f);

			//�����G�ƂȂ�̕����摜��\��584*112
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 584.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 335.0f;
			dst.m_left = 425.0f;
			dst.m_right = 600.0f;
			dst.m_bottom = 370.0f;
			Draw::Draw(100, &src, &dst, black, 0.0f);

		}
		else
		{
			Draw::Draw(42, &src, &dst, black, 0.0f);
		}

		//���~�b�g�u���C�N�̔���
		//�X�y�V�����{�^���̋��ʐ؂���ʒu�ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 100.0f;
		src.m_bottom = 100.0f;

		//�܂��\��t���ʒu��ݒ肷��
		dst.m_top = 385.0f;
		dst.m_left = 100.0f;
		dst.m_right = 230.0f;
		dst.m_bottom = 515.0f;

		//���~�b�g�u���C�N���o���Ă���Ȃ��
		if (g_Special_mastering[3] == true)
		{
			//Font::StrDraw(L"10�b�ԍU���X�s�[�h�A�b�v", 240.0f, 410.0f, 35.0f, black);
			//Font::StrDraw(L"���퐶�Y�p�x�A�b�v", 245.0f, 460.0f, 35.0f, black);

			if (g_Special_equipment == 4)
				Draw::Draw(43, &src, &dst, it, 0.0f);
			else
				Draw::Draw(43, &src, &dst, gray, 0.0f);

			//��10�b�ԃ|�b�h���Y���x�̕����摜��\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 1252.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 410.0f;
			dst.m_left = 240.0f;
			dst.m_right = 625.0f;
			dst.m_bottom = 445.0f;
			Draw::Draw(101, &src, &dst, black, 0.0f);

			//���~�T�C�����Y���xUP�̕����摜��\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 1134.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 460.0f;
			dst.m_left = 245.0f;
			dst.m_right = 595.0f;
			dst.m_bottom = 495.0f;
			Draw::Draw(102, &src, &dst, black, 0.0f);


		}
		else
		{
			Draw::Draw(43, &src, &dst, black, 0.0f);
		}

		//�X�e���C�h���^�̔���
		//�X�y�V�����{�^���̋��ʐ؂���ʒu�ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 100.0f;
		src.m_bottom = 100.0f;

		//�܂��\��t���ʒu��ݒ肷��
		dst.m_top =485.0f;
		dst.m_left = 100.0f;
		dst.m_right = 230.0f;
		dst.m_bottom = 615.0f;

		//�X�e���C�h���^���o���Ă���Ȃ��
		if (g_Special_mastering[4] == true)
		{
			//Font::StrDraw(L"�Z���̃|�b�h5�@�U�����オ��", 245.0f, 510.0f, 35.0f, black);
			//Font::StrDraw(L"(���݃��C����ɏo�Ă���|�b�h���܂߂�)", 245.0f, 560.0f, 35.0f, black);

			if (g_Special_equipment == 6)
				Draw::Draw(44, &src, &dst, it, 0.0f);
			else
				Draw::Draw(44, &src, &dst, gray, 0.0f);

			//���o������̕����摜��\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 464.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 510.0f;
			dst.m_left = 245.0f;
			dst.m_right = 385.0f;
			dst.m_bottom = 545.0f;
			Draw::Draw(103, &src, &dst, black, 0.0f);

			//���|�b�h5�@�̍U����UP�̕����摜��\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 1222.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 560.0f;
			dst.m_left = 245.0f;
			dst.m_right = 630.0f;
			dst.m_bottom = 595.0f;
			Draw::Draw(104, &src, &dst, black, 0.0f);


		}
		else
		{
			Draw::Draw(44, &src, &dst, black, 0.0f);
		}
	}

	//�����{�^���������ĕ`�悷��摜
	else if (window_start_manage == Soubicheck)
	{
		//���D�F�E�B���h�E�\��(�_�~�[�q�ɃE�B���h�E�p)
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1160.0f;
		src.m_bottom = 660.0f;

		dst.m_top = 20.0f;
		dst.m_left = 20.0f;
		dst.m_right = 1180.0f;
		dst.m_bottom = 680.0f;
		Draw::Draw(20, &src, &dst, sb, 0.0f);

		//���D�F�E�B���h�E�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1160.0f;
		src.m_bottom = 660.0f;

		dst.m_top = 40.0f;
		dst.m_left = 40.0f;
		dst.m_right = 1160.0f;
		dst.m_bottom = 660.0f;
		Draw::Draw(20, &src, &dst, sb, 0.0f);

		//���߂�{�^���\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 50.0f;
		dst.m_left = 50.0f;
		dst.m_right = 100.0f;
		dst.m_bottom = 100.0f;
		Draw::Draw(1, &src, &dst, md, 0.0f);

		//�����F�E�B���h�E�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 100.0f;
		src.m_bottom = 100.0f;

		dst.m_top = 100.0f;
		dst.m_left = 100.0f;
		dst.m_right = 1100.0f;
		dst.m_bottom = 600.0f;
		Draw::Draw(32, &src, &dst, it, 0.0f);

		//��������(��������)�����摜��\��
		src.m_top = 0.0f;
		src.m_left = 120.0f;
		src.m_right = 367.0f;
		src.m_bottom = 117.0f;

		dst.m_top = 110.0f;
		dst.m_left = 500.0f;
		dst.m_right = 650.0f;
		dst.m_bottom = 160.0f;
		Draw::Draw(105, &src, &dst, black, 0.0f);

		//�����b�h�����摜��\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 336.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 200.0f;
		dst.m_left = 120.0f;
		dst.m_right = 240.0f;
		dst.m_bottom = 240.0f;
		Draw::Draw(82, &src, &dst, red, 0.0f);

		//���u���[�����摜��\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 352.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 330.0f;
		dst.m_left = 120.0f;
		dst.m_right = 240.0f;
		dst.m_bottom = 370.0f;
		Draw::Draw(83, &src, &dst, blue, 0.0f);

		//���O���[�������摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 472.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 460.0f;
		dst.m_left = 120.0f;
		dst.m_right = 280.0f;
		dst.m_bottom = 500.0f;
		Draw::Draw(84, &src, &dst, green, 0.0f);

		//���z���C�g�����摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 464.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 200.0f;
		dst.m_left = 620.0f;
		dst.m_right = 780.0f;
		dst.m_bottom = 240.0f;
		Draw::Draw(85, &src, &dst, black, 0.0f);

		//���|�b�h�����摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 344.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 330.0f;
		dst.m_left = 620.0f;
		dst.m_right = 740.0f;
		dst.m_bottom = 370.0f;
		Draw::Draw(86, &src, &dst, black, 0.0f);

		//���c��Z���������܂���(�c��Z��������)�����摜��\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 600.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 470.0f;
		dst.m_left = 540.0f;
		dst.m_right = 750.0f;
		dst.m_bottom = 505.0f;
		Draw::Draw(94, &src, &dst, black, 0.0f);

		//���c��@�@�@�l(�c��)���������摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 592.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 470.0f;
		dst.m_left = 780.0f;
		dst.m_right = 990.0f;
		dst.m_bottom = 505.0f;
		Draw::Draw(78, &src, &dst, red, 0.0f);

		//���l�����摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 112.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 470.0f;
		dst.m_left = 995.0f;
		dst.m_right = 1030.0f;
		dst.m_bottom = 505.0f;
		Draw::Draw(77, &src, &dst, red, 0.0f);


		//������
		//Font::StrDraw(L"����", 500.0f, 110.0f, 50.0f, black);

		////�p���[
		//Font::StrDraw(L"�p���[", 120.0f, 200.0f, 40.0f, red);
		Font::StrDraw(type_num[0], 355.0f, 200.0f, 40.0f, black);

		////�f�B�t�F���X
		//Font::StrDraw(L"�f�B�t�F���X", 120.0f, 460.0f, 40.0f, green);
		Font::StrDraw(type_num[1], 360.0f, 460.0f, 40.0f, black);

		////�X�s�[�h
		//Font::StrDraw(L"�X�s�[�h", 120.0f, 330.0f, 40.0f, blue);
		Font::StrDraw(type_num[2], 360.0f, 330.0f, 40.0f, black);

		////�o�����X
		//Font::StrDraw(L"�o�����X", 620.0f, 200.0f, 40.0f, yellow);
		Font::StrDraw(type_num[3], 880.0f, 200.0f, 40.0f, black);

		////���|�b�h
		//Font::StrDraw(L"�|�b�h", 620.0f, 330.0f, 40.0f, black);
		Font::StrDraw(type_num[4], 880.0f, 330.0f, 40.0f, black);

	}
}
