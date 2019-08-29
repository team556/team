//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjWarehouse.h"
#include "UtilityModule.h"

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
	//Hits::SetHitBox(this, 95, 170, 225, 110, ELEMENT_ENEMY, OBJ_WAREHOUSE, 1);
}

//�A�N�V����
void CObjWarehouse::Action()
{
	//�`���[�g���A���������͑���s�\�ɂ��鏈��
	if (g_is_operatable == false)
	{
		return;
	}

	//�w���v��ʕ\�����͑���s�\�ɂ��鏈��
	if (g_help_f == true)
	{
		//�w���v��ʂ̖߂�{�^�������N���b�N(�������͉E�N���b�N)���A
		//���̎{�݂̖߂�{�^���������ɃN���b�N����Ȃ��悤�ɁA
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

	//���q�ɃE�B���h�E�\���̏���
	if (window_start_manage == Warehouse)
	{
		//�߂�{�^�����N���b�N�A�������͉E�N���b�N(�ǂ��ł�)���鎖�ł��̃E�C���h�E�����
		if (70 < m_mou_x && m_mou_x < 120 && 56 < m_mou_y && m_mou_y < 110 || m_mou_r == true)
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

		if (g_tutorial_progress >= 15)
		{
			//���ރ{�^���I��
			if (110 < m_mou_x && m_mou_x < 610 && 110 < m_mou_y && m_mou_y < 360)
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
			if (620 < m_mou_x && m_mou_x < 1120 && 110 < m_mou_y && m_mou_y < 360)
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
			if (110 < m_mou_x && m_mou_x < 610 && 370 < m_mou_y && m_mou_y < 620)
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
			if (620 < m_mou_x && m_mou_x < 1120 && 370 < m_mou_y && m_mou_y < 620)
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
	}

	//���ށA�Z���A�X�y�V�����Z�A������ʂ̖߂�{�^��
	if (window_start_manage == Materials || window_start_manage == Residents ||
		window_start_manage == Specialskill || window_start_manage == Soubicheck)
	{
		//�߂�{�^���I��
		if (80 < m_mou_x && m_mou_x < 130 && 74 < m_mou_y && m_mou_y < 130 || m_mou_r == true)
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
	if (window_start_manage != Default)
	{
		m_introduce_f = false;	//�{�ݏЉ�E�C���h�E���\���ɂ���(�E�N���b�N�Ńz�[����ʂɖ߂�ہA�E�C���h�E���c��Ȃ��悤�ɂ��邽��)
		return;
	}

	//�q�ɑI��
	if (g_tutorial_progress >= 13)//�`���[�g���A�����͑I��s��
	{
		if (850 < m_mou_x && m_mou_x < 1250 && 430 < m_mou_y && m_mou_y < 550)
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

					//�I����
					Audio::Start(1);

					if (g_tutorial_progress == 13)
					{
						//�����\���ɂ�����
						CObjMessage* message = (CObjMessage*)Objs::GetObj(OBJ_MESSAGE);
						message->Setarrow(0);
					}
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
	float blue[4] = { 0.5f,0.5f,1.0f,1.0f };

	//�ΐF
	float green[4] = { 0.0f,1.0f,0.0f,1.0f };

	//���F
	float yellow[4] = { 1.0f,1.0f,0.0f,1.0f };

	//�D�F
	float gray[4] = { 0.8f,0.8f,0.9f,1.0f };

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
	if (window_start_manage == Default || window_start_manage == BackButton || window_start_manage == EatButton)
	{
		//���q�ɕ\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 400.0f;
		src.m_bottom = 400.0f;

		dst.m_top = 350.0f;
		dst.m_left = 850.0f;
		dst.m_right = 1250.0f;
		dst.m_bottom = 650.0f;
		Draw::Draw(27, &src, &dst, wh, 0.0f);

		//�{�ݏЉ�E�C���h�E�\���Ǘ��t���O��true�̎��A�`��B
		if (m_introduce_f == true)
		{
			//���{�ݏЉ�E�C���h�E�\������
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 790.0f;
			src.m_bottom = 800.0f;

			dst.m_top = m_mou_y - 50.0f;
			dst.m_left = m_mou_x - 120.0f;
			dst.m_right = m_mou_x - 40.0f;
			dst.m_bottom = m_mou_y - 30.0f;
			Draw::Draw(21, &src, &dst, white, 0.0f);

			//���{�ݏЉ�E�C���h�E�\������
			src.m_top = 10.0f;
			src.m_left = 800.0f;
			src.m_right = 1595.0f;
			src.m_bottom = 800.0f;

			dst.m_top = m_mou_y - 30.0f;
			dst.m_left = m_mou_x - 120.0f;
			dst.m_right = m_mou_x - 40.0f;
			dst.m_bottom = m_mou_y - 10.0f;
			Draw::Draw(21, &src, &dst, white, 0.0f);

			//���{�ݏЉ�E�C���h�E�\��������
			src.m_top = 0.0f;
			src.m_left = 1600.0f;
			src.m_right = 2400.0f;
			src.m_bottom = 800.0f;

			dst.m_top = m_mou_y - 50.0f;
			dst.m_left = m_mou_x - 40.0f;
			dst.m_right = m_mou_x + 40.0f;
			dst.m_bottom = m_mou_y - 30.0f;
			Draw::Draw(21, &src, &dst, white, 0.0f);

			//���{�ݏЉ�E�C���h�E�\��������
			src.m_top = 0.0f;
			src.m_left = 2400.0f;
			src.m_right = 3200.0f;
			src.m_bottom = 800.0f;

			dst.m_top = m_mou_y - 30.0f;
			dst.m_left = m_mou_x - 40.0f;
			dst.m_right = m_mou_x + 40.0f;
			dst.m_bottom = m_mou_y - 10.0f;
			Draw::Draw(21, &src, &dst, white, 0.0f);

			//���{�ݏЉ�E�C���h�E�\���E��
			src.m_top = 0.0f;
			src.m_left = 4000.0f;
			src.m_right = 4800.0f;
			src.m_bottom = 800.0f;

			dst.m_top = m_mou_y - 50.0f;
			dst.m_left = m_mou_x + 40.0f;
			dst.m_right = m_mou_x + 120.0f;
			dst.m_bottom = m_mou_y - 30.0f;
			Draw::Draw(21, &src, &dst, white, 0.0f);

			//���{�ݏЉ�E�C���h�E�\��������
			src.m_top = 0.0f;
			src.m_left = 4805.0f;
			src.m_right = 5600.0f;
			src.m_bottom = 800.0f;

			dst.m_top = m_mou_y - 30.0f;
			dst.m_left = m_mou_x + 40.0f;
			dst.m_right = m_mou_x + 120.0f;
			dst.m_bottom = m_mou_y - 10.0f;
			Draw::Draw(21, &src, &dst, white, 0.0f);

			//���q�ɕ����摜�\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 242.0f;
			src.m_bottom = 117.0f;

			dst.m_top = m_mou_y - 43.0f;
			dst.m_left = m_mou_x - 30.0f;
			dst.m_right = m_mou_x + 20.0f;
			dst.m_bottom = m_mou_y - 18.0f;
			Draw::Draw(88, &src, &dst, white, 0.0f);
		}
}

	//�q�ɂ��N���b�N������
	else if (window_start_manage == Warehouse)
	{
		//���E�B���h�E�\��
		src.m_top    =    0.0f;
		src.m_left   =    0.0f;
		src.m_right  = 1200.0f;
		src.m_bottom =  700.0f;

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

		dst.m_top    =  60.0f;
		dst.m_left   =  70.0f;
		dst.m_right  =  120.0f;
		dst.m_bottom =  110.0f;
		Draw::Draw(1, &src, &dst, md, 0.0f);

		//�����ޑI���{�^���\��
		src.m_top    = 0.0f;
		src.m_left   = 0.0f;
		src.m_right  = 300.0f;
		src.m_bottom = 170.0f;

		dst.m_top    = 110.0f;
		dst.m_left   = 110.0f;
		dst.m_right  = 610.0f;
		dst.m_bottom = 360.0f;
		Draw::Draw(28, &src, &dst, ma, 0.0f);

		//���Z���I���{�^���\��
		src.m_top	 = 0.0f;
		src.m_left	 = 0.0f;
		src.m_right	 = 300.0f;
		src.m_bottom = 170.0f;

		dst.m_top    = 110.0f;
		dst.m_left   = 620.0f;
		dst.m_right  = 1120.0f;
		dst.m_bottom = 360.0f;
		Draw::Draw(29, &src, &dst, re, 0.0f);

		//���X�y�V�����Z�I���{�^���\��
		src.m_top	 = 0.0f;
		src.m_left   = 0.0f;
		src.m_right	 = 300.0f;
		src.m_bottom = 170.0f;

		dst.m_top    = 370.0f;
		dst.m_left   = 110.0f;
		dst.m_right  = 610.0f;
		dst.m_bottom = 620.0f;
		Draw::Draw(30, &src, &dst, sp, 0.0f);

		//�������I���{�^���\��
		src.m_top	 = 0.0f;
		src.m_left	 = 0.0f;
		src.m_right  = 300.0f;
		src.m_bottom = 170.0f;

		dst.m_top    = 370.0f;
		dst.m_left   = 620.0f;
		dst.m_right  = 1120.0f;
		dst.m_bottom = 620.0f;
		Draw::Draw(31, &src, &dst, eq, 0.0f);
	}

	//�߂�{�^���A��{�^����I�����ĕ`�悷��摜�i�ǂ̃E�C���h�E���J���ĂȂ������`�悷��j
	else if (window_start_manage == Default || window_start_manage == BackButton || window_start_manage == EatButton)
	{
		//���q�ɕ\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 400.0f;
		src.m_bottom = 400.0f;

		dst.m_top = 350.0f;
		dst.m_left = 850.0f;
		dst.m_right = 1250.0f;
		dst.m_bottom = 650.0f;
		Draw::Draw(27, &src, &dst, wh, 0.0f);

		//�{�ݏЉ�E�C���h�E�\���Ǘ��t���O��true�̎��A�`��B
		if (m_introduce_f == true)
		{
			//���{�ݏЉ�E�C���h�E�\������
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 790.0f;
			src.m_bottom = 780.0f;

			dst.m_top = m_mou_y - 50.0f;
			dst.m_left = m_mou_x - 120.0f;
			dst.m_right = m_mou_x - 40.0f;
			dst.m_bottom = m_mou_y - 30.0f;
			Draw::Draw(21, &src, &dst, white, 0.0f);

			//���{�ݏЉ�E�C���h�E�\������
			src.m_top = 0.0f;
			src.m_left = 800.0f;
			src.m_right = 1595.0f;
			src.m_bottom = 800.0f;

			dst.m_top = m_mou_y - 30.0f;
			dst.m_left = m_mou_x - 120.0f;
			dst.m_right = m_mou_x - 40.0f;
			dst.m_bottom = m_mou_y - 10.0f;
			Draw::Draw(21, &src, &dst, white, 0.0f);

			//���{�ݏЉ�E�C���h�E�\��������
			src.m_top = 0.0f;
			src.m_left = 1600.0f;
			src.m_right = 2400.0f;
			src.m_bottom = 800.0f;

			dst.m_top = m_mou_y - 50.0f;
			dst.m_left = m_mou_x - 40.0f;
			dst.m_right = m_mou_x + 40.0f;
			dst.m_bottom = m_mou_y - 30.0f;
			Draw::Draw(21, &src, &dst, white, 0.0f);

			//���{�ݏЉ�E�C���h�E�\��������
			src.m_top = 0.0f;
			src.m_left = 2400.0f;
			src.m_right = 3200.0f;
			src.m_bottom = 800.0f;

			dst.m_top = m_mou_y - 30.0f;
			dst.m_left = m_mou_x - 40.0f;
			dst.m_right = m_mou_x + 40.0f;
			dst.m_bottom = m_mou_y - 10.0f;
			Draw::Draw(21, &src, &dst, white, 0.0f);

			//���{�ݏЉ�E�C���h�E�\���E��
			src.m_top = 0.0f;
			src.m_left = 4000.0f;
			src.m_right = 4800.0f;
			src.m_bottom = 800.0f;

			dst.m_top = m_mou_y - 50.0f;
			dst.m_left = m_mou_x + 40.0f;
			dst.m_right = m_mou_x + 120.0f;
			dst.m_bottom = m_mou_y - 30.0f;
			Draw::Draw(21, &src, &dst, white, 0.0f);

			//���{�ݏЉ�E�C���h�E�\��������
			src.m_top = 0.0f;
			src.m_left = 4805.0f;
			src.m_right = 5600.0f;
			src.m_bottom = 800.0f;

			dst.m_top = m_mou_y - 30.0f;
			dst.m_left = m_mou_x + 40.0f;
			dst.m_right = m_mou_x + 120.0f;
			dst.m_bottom = m_mou_y - 10.0f;
			Draw::Draw(21, &src, &dst, white, 0.0f);
		}
	}

	//���ރ{�^���������ĕ`�悷��摜
	else if (window_start_manage == Materials)
	{
		//���E�B���h�E�\��(�_�~�[�q�ɃE�B���h�E�p)
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1200.0f;
		src.m_bottom = 700.0f;

		dst.m_top = 20.0f;
		dst.m_left = 20.0f;
		dst.m_right = 1180.0f;
		dst.m_bottom = 680.0f;
		Draw::Draw(20, &src, &dst, sb, 0.0f);

		//���E�B���h�E�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1200.0f;
		src.m_bottom = 700.0f;

		dst.m_top = 40.0f;
		dst.m_left = 40.0f;
		dst.m_right = 1160.0f;
		dst.m_bottom = 660.0f;
		Draw::Draw(20, &src, &dst, sb, 0.0f);

		//�����ޕ����摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 232.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 80.0f;
		dst.m_left = 550.0f;
		dst.m_right = 650.0f;
		dst.m_bottom = 130.0f;
		Draw::Draw(147, &src, &dst, white, 0.0f);

		//���߂�{�^���\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 80.0f;
		dst.m_left = 80.0f;
		dst.m_right = 130.0f;
		dst.m_bottom = 130.0f;
		Draw::Draw(1, &src, &dst, md, 0.0f);

		//���傫���E�B���h�E
		//�����b�Z�[�W�E�C���h�E�\������
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 798.0f;
		src.m_bottom = 798.0f;

		dst.m_top = 150.0f;
		dst.m_left = 105.0f;
		dst.m_right = 350.0f;
		dst.m_bottom = 395.0f;
		Draw::Draw(155, &src, &dst, white, 0.0f);

		//�����b�Z�[�W�E�C���h�E�\������
		src.m_top = 35.0f;
		src.m_left = 800.0f;
		src.m_right = 1600.0f;
		src.m_bottom = 798.0f;

		dst.m_top = 395.0f;
		dst.m_left = 105.0f;
		dst.m_right = 350.0f;
		dst.m_bottom = 640.0f;
		Draw::Draw(155, &src, &dst, white, 0.0f);

		for(int i=0;i<3;i++)
		{
			//�����b�Z�[�W�E�C���h�E�\��������
			src.m_top = 0.0f;
			src.m_left = 1600.0f;
			src.m_right = 2400.0f;
			src.m_bottom = 798.0f;

			dst.m_top = 150.0f;
			dst.m_left = 350.0f + ( i * 245);
			dst.m_right = 595.0f + ( i * 245);
			dst.m_bottom = 395.0f;
			Draw::Draw(155, &src, &dst, white, 0.0f);

			//�����b�Z�[�W�E�C���h�E�\��������
			src.m_top = 2.0f;
			src.m_left = 2402.0f;
			src.m_right = 3200.0f;
			src.m_bottom = 798.0f;

			dst.m_top = 395.0f;
			dst.m_left = 350.0f + (i * 245);
			dst.m_right = 595.0f + (i * 245);
			dst.m_bottom = 640.0f;
			Draw::Draw(155, &src, &dst, white, 0.0f);
		}
		//�����b�Z�[�W�E�C���h�E�\���E��
		src.m_top = 0.0f;
		src.m_left = 4000.0f;
		src.m_right = 4800.0f;
		src.m_bottom = 798.0f;

		dst.m_top = 150.0f;
		dst.m_left = 860.0f;
		dst.m_right = 1105.0f;
		dst.m_bottom = 395.0f;
		Draw::Draw(155, &src, &dst, white, 0.0f);

		//�����b�Z�[�W�E�C���h�E�\���E��
		src.m_top = 35.0f;
		src.m_left = 4802.0f;
		src.m_right = 5600.0f;
		src.m_bottom = 798.0f;

		dst.m_top = 395.0f;
		dst.m_left = 860.0f;
		dst.m_right = 1105.0f;
		dst.m_bottom = 640.0f;
		Draw::Draw(155, &src, &dst, white, 0.0f);

		for(int j=0;j<3;j++)
		{
			//���������E�B���h�E�؍ށE�v���X�`�b�N
			//�����b�Z�[�W�E�C���h�E�\������
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 798.0f;
			src.m_bottom = 798.0f;

			dst.m_top = 290.0f + (j * 230);
			dst.m_left = 130.0f;
			dst.m_right = 180.0f;
			dst.m_bottom = 340.0f + (j * 230);
			Draw::Draw(21, &src, &dst, white, 0.0f);

			//�����b�Z�[�W�E�C���h�E�\������
			src.m_top = 35.0f;
			src.m_left = 800.0f;
			src.m_right = 1600.0f;
			src.m_bottom = 798.0f;

			dst.m_top = 340.0f + (j * 230);
			dst.m_left = 130.0f;
			dst.m_right = 180.0f;
			dst.m_bottom = 390.0f + (j * 230);
			Draw::Draw(21, &src, &dst, white, 0.0f);

			for (int i = 0; i<4; i++)
			{
				//�����b�Z�[�W�E�C���h�E�\��������
				src.m_top = 0.0f;
				src.m_left = 1600.0f;
				src.m_right = 2400.0f;
				src.m_bottom = 798.0f;

				dst.m_top = 290.0f + (j * 230);
				dst.m_left = 180.0f + (i * 50);
				dst.m_right = 230.0f + (i * 50);
				dst.m_bottom = 340.0f + (j * 230);
				Draw::Draw(21, &src, &dst, white, 0.0f);

				//�����b�Z�[�W�E�C���h�E�\��������
				src.m_top = 2.0f;
				src.m_left = 2402.0f;
				src.m_right = 3200.0f;
				src.m_bottom = 798.0f;

				dst.m_top = 340.0f + (j * 230);
				dst.m_left = 180.0f + (i * 50);
				dst.m_right = 230.0f + (i * 50);
				dst.m_bottom = 390.0f + (j * 230);
				Draw::Draw(21, &src, &dst, white, 0.0f);
			}
			//�����b�Z�[�W�E�C���h�E�\���E��
			src.m_top = 0.0f;
			src.m_left = 4000.0f;
			src.m_right = 4800.0f;
			src.m_bottom = 798.0f;

			dst.m_top = 290.0f + (j * 230);
			dst.m_left = 350.0f;
			dst.m_right = 400.0f;
			dst.m_bottom = 340.0f + (j * 230);
			Draw::Draw(21, &src, &dst, white, 0.0f);

			//�����b�Z�[�W�E�C���h�E�\���E��
			src.m_top = 35.0f;
			src.m_left = 4802.0f;
			src.m_right = 5600.0f;
			src.m_bottom = 798.0f;

			dst.m_top = 340.0f + (j * 230);
			dst.m_left = 350.0f;
			dst.m_right = 400.0f;
			dst.m_bottom = 390.0f + (j * 230);
			Draw::Draw(21, &src, &dst, white, 0.0f);
		}

		for (int j = 0; j<2; j++)
		{
			//���������E�B���h�E�S�E�A���~
			//�����b�Z�[�W�E�C���h�E�\������
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 798.0f;
			src.m_bottom = 798.0f;

			dst.m_top = 290.0f + (j * 230);
			dst.m_left = 520.0f;
			dst.m_right = 570.0f;
			dst.m_bottom = 340.0f + (j * 230);
			Draw::Draw(21, &src, &dst, white, 0.0f);

			//�����b�Z�[�W�E�C���h�E�\������
			src.m_top = 35.0f;
			src.m_left = 800.0f;
			src.m_right = 1600.0f;
			src.m_bottom = 798.0f;

			dst.m_top = 340.0f + (j * 230);
			dst.m_left = 520.0f;
			dst.m_right = 570.0f;
			dst.m_bottom = 390.0f + (j * 230);
			Draw::Draw(21, &src, &dst, white, 0.0f);

			for (int i = 0; i<2; i++)
			{
				//�����b�Z�[�W�E�C���h�E�\��������
				src.m_top = 0.0f;
				src.m_left = 1600.0f;
				src.m_right = 2400.0f;
				src.m_bottom = 798.0f;

				dst.m_top = 290.0f + (j * 230);
				dst.m_left = 570.0f + (i * 50);
				dst.m_right = 620.0f + (i * 50);
				dst.m_bottom = 340.0f + (j * 230);
				Draw::Draw(21, &src, &dst, white, 0.0f);

				//�����b�Z�[�W�E�C���h�E�\��������
				src.m_top = 2.0f;
				src.m_left = 2402.0f;
				src.m_right = 3200.0f;
				src.m_bottom = 798.0f;

				dst.m_top = 340.0f + (j * 230);
				dst.m_left = 570.0f + (i * 50);
				dst.m_right = 620.0f + (i * 50);
				dst.m_bottom = 390.0f + (j * 230);
				Draw::Draw(21, &src, &dst, white, 0.0f);
			}
			//�����b�Z�[�W�E�C���h�E�\���E��
			src.m_top = 0.0f;
			src.m_left = 4000.0f;
			src.m_right = 4800.0f;
			src.m_bottom = 798.0f;

			dst.m_top = 290.0f + (j * 230);
			dst.m_left = 670.0f;
			dst.m_right = 720.0f;
			dst.m_bottom = 340.0f + (j * 230);
			Draw::Draw(21, &src, &dst, white, 0.0f);

			//�����b�Z�[�W�E�C���h�E�\���E��
			src.m_top = 35.0f;
			src.m_left = 4802.0f;
			src.m_right = 5600.0f;
			src.m_bottom = 798.0f;

			dst.m_top = 340.0f + (j * 230);
			dst.m_left = 670.0f;
			dst.m_right = 720.0f;
			dst.m_bottom = 390.0f + (j * 230);
			Draw::Draw(21, &src, &dst, white, 0.0f);
		}

		for (int j = 0; j<2; j++)
		{
			//���������E�B���h�E��E�K�X
			//�����b�Z�[�W�E�C���h�E�\������
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 798.0f;
			src.m_bottom = 798.0f;

			dst.m_top = 290.0f + (j * 230);
			dst.m_left = 870.0f;
			dst.m_right = 920.0f;
			dst.m_bottom = 340.0f + (j * 230);
			Draw::Draw(21, &src, &dst, white, 0.0f);

			//�����b�Z�[�W�E�C���h�E�\������
			src.m_top = 35.0f;
			src.m_left = 800.0f;
			src.m_right = 1600.0f;
			src.m_bottom = 798.0f;

			dst.m_top = 340.0f + (j * 230);
			dst.m_left = 870.0f;
			dst.m_right = 920.0f;
			dst.m_bottom = 390.0f + (j * 230);
			Draw::Draw(21, &src, &dst, white, 0.0f);

			for (int i = 0; i<2; i++)
			{
				//�����b�Z�[�W�E�C���h�E�\��������
				src.m_top = 0.0f;
				src.m_left = 1600.0f;
				src.m_right = 2400.0f;
				src.m_bottom = 798.0f;

				dst.m_top = 290.0f + (j * 230);
				dst.m_left = 910.0f + (i * 50);
				dst.m_right = 960.0f + (i * 50);
				dst.m_bottom = 340.0f + (j * 230);
				Draw::Draw(21, &src, &dst, white, 0.0f);

				//�����b�Z�[�W�E�C���h�E�\��������
				src.m_top = 2.0f;
				src.m_left = 2402.0f;
				src.m_right = 3200.0f;
				src.m_bottom = 798.0f;

				dst.m_top = 340.0f + (j * 230);
				dst.m_left = 910.0f + (i * 50);
				dst.m_right = 960.0f + (i * 50);
				dst.m_bottom = 390.0f + (j * 230);
				Draw::Draw(21, &src, &dst, white, 0.0f);
			}
			//�����b�Z�[�W�E�C���h�E�\���E��
			src.m_top = 0.0f;
			src.m_left = 4000.0f;
			src.m_right = 4800.0f;
			src.m_bottom = 798.0f;

			dst.m_top = 290.0f + (j * 230);
			dst.m_left = 1010.0f;
			dst.m_right = 1060.0f;
			dst.m_bottom = 340.0f + (j * 230);
			Draw::Draw(21, &src, &dst, white, 0.0f);

			//�����b�Z�[�W�E�C���h�E�\���E��
			src.m_top = 35.0f;
			src.m_left = 4802.0f;
			src.m_right = 5600.0f;
			src.m_bottom = 798.0f;

			dst.m_top = 340.0f + (j * 230);
			dst.m_left = 1010.0f;
			dst.m_right = 1060.0f;
			dst.m_bottom = 390.0f + (j * 230);
			Draw::Draw(21, &src, &dst, white, 0.0f);
		}

		//���؍ޕ\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 180.0f;
		dst.m_left = 200.0f;
		dst.m_right = 300.0f;
		dst.m_bottom = 280.0f;
		Draw::Draw(33, &src, &dst, white, 0.0f);

		//���؍ޕ����摜�\��
		src.m_top = 2.0f;
		src.m_left = 0.0f;
		src.m_right = 230.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 300.0f;
		dst.m_left = 170.0f;
		dst.m_right = 250.0f;
		dst.m_bottom = 340.0f;
		Draw::Draw(89, &src, &dst, white, 0.0f);

		FontDraw(NumConversion(g_Wood_num), 270, 340, 30, 40, white, true);
		FontDraw(L"�R", 315, 360, 15, 20, white, true);
		//Font::StrDraw(mrl[0], 240.0f, 290.0f, 40.0f, black);

		//���S�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 180.0f;
		dst.m_left = 550.0f;
		dst.m_right = 650.0f;
		dst.m_bottom = 280.0f;
		Draw::Draw(34, &src, &dst, it, 0.0f);

		//���S�����摜�\��
		src.m_top = 2.0f;
		src.m_left = 0.0f;
		src.m_right = 110.0f;
		src.m_bottom = 110.0f;

		dst.m_top = 300.0f;
		dst.m_left = 540.0f;
		dst.m_right = 580.0f;
		dst.m_bottom = 340.0f;
		Draw::Draw(69, &src, &dst, white, 0.0f);

		FontDraw(NumConversion(g_Iron_num), 620, 340, 30, 40, white, true);
		FontDraw(L"�R", 665, 360, 15, 20, white, true);
		//Font::StrDraw(mrl[1], 580.0f, 290.0f, 40.0f, black);

		//����\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 180.0f;
		dst.m_left = 900.0f;
		dst.m_right = 1000.0f;
		dst.m_bottom = 280.0f;
		Draw::Draw(35, &src, &dst, it, 0.0f);

		//���╶���摜�\��
		src.m_top = 2.0f;
		src.m_left = 2.0f;
		src.m_right = 110.0f;
		src.m_bottom = 110.0f;

		dst.m_top = 300.0f;
		dst.m_left = 910.0f;
		dst.m_right = 950.0f;
		dst.m_bottom = 340.0f;
		Draw::Draw(90, &src, &dst, white, 0.0f);

		FontDraw(NumConversion(g_Silver_num), 970, 340, 30, 40, white, true);
		FontDraw(L"�R", 1015, 360, 15, 20, white, true);
		//Font::StrDraw(mrl[2], 950.0f, 290.0f, 40.0f, black);

		//���v���X�`�b�N�\��
		src.m_top = 2.0f;
		src.m_left = 0.0f;
		src.m_right = 62.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 400.0f;
		dst.m_left = 200.0f;
		dst.m_right = 300.0f;
		dst.m_bottom = 500.0f;
		Draw::Draw(36, &src, &dst, it, 0.0f);

		//���v���X�`�b�N�����摜�\��
		src.m_top = 2.0f;
		src.m_left = 2.0f;
		src.m_right = 712.0f;
		src.m_bottom = 110.0f;

		dst.m_top = 530.0f;
		dst.m_left = 140.0f;
		dst.m_right = 380.0f;
		dst.m_bottom = 570.0f;
		Draw::Draw(91, &src, &dst, white, 0.0f);


		FontDraw(NumConversion(g_Plastic_num), 270, 570, 30, 40, white, true);
		FontDraw(L"�R", 315, 590, 15, 20, white, true);
		//Font::StrDraw(mrl[3], 240.0f, 540.0f, 40.0f, black);

		//���A���~�j�E���摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 400.0f;
		dst.m_left = 550.0f;
		dst.m_right = 650.0f;
		dst.m_bottom = 500.0f;
		Draw::Draw(37, &src, &dst, it, 0.0f);

		//���A���~�����摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 352.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 530.0f;
		dst.m_left = 530.0f;
		dst.m_right = 650.0f;
		dst.m_bottom = 570.0f;
		Draw::Draw(92, &src, &dst, white, 0.0f);

		FontDraw(NumConversion(g_Aluminum_num), 620, 570, 30, 40, white, true);
		FontDraw(L"�R", 665, 590, 15, 20, white, true);
		//Font::StrDraw(mrl[4], 580.0f, 540.0f, 40.0f, black);

		//���K�X�\��
		src.m_top = 2.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 400.0f;
		dst.m_left = 900.0f;
		dst.m_right = 1000.0f;
		dst.m_bottom = 500.0f;
		Draw::Draw(38, &src, &dst, it, 0.0f);

		//���K�X�����摜�\��
		src.m_top = 2.0f;
		src.m_left = 0.0f;
		src.m_right = 232.0f;
		src.m_bottom = 116.0f;

		dst.m_top = 530.0f;
		dst.m_left = 910.0f;
		dst.m_right = 990.0f;
		dst.m_bottom = 570.0f;
		Draw::Draw(93, &src, &dst, white, 0.0f);

		FontDraw(NumConversion(g_gus_num), 970, 570, 30, 40, white, true);
		FontDraw(L"�R", 1015, 590, 15, 20, white, true);
		//Font::StrDraw(mrl[5], 950.0f, 540.0f, 40.0f, black);
	}

	//�Z���{�^���������ĕ`�悷��摜
	else if (window_start_manage == Residents)
	{
		//���E�B���h�E�\��(�_�~�[�q�ɃE�B���h�E�p)
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1200.0f;
		src.m_bottom = 700.0f;

		dst.m_top = 20.0f;
		dst.m_left = 20.0f;
		dst.m_right = 1180.0f;
		dst.m_bottom = 680.0f;
		Draw::Draw(20, &src, &dst, sb, 0.0f);

		//���E�B���h�E�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1200.0f;
		src.m_bottom = 700.0f;

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

		dst.m_top = 80.0f;
		dst.m_left = 80.0f;
		dst.m_right = 130.0f;
		dst.m_bottom = 130.0f;
		Draw::Draw(1, &src, &dst, md, 0.0f);
		
		//���c��Z���������܂���(�Z��������)�����摜��\��
		src.m_top = 0.0f;
		src.m_left = 230.0f;
		src.m_right = 600.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 80.0f;
		dst.m_left = 500.0f;
		dst.m_right = 650.0f;
		dst.m_bottom = 130.0f;
		Draw::Draw(94, &src, &dst, white, 0.0f);

		//���ԏZ���摜��\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 130.0f;
		src.m_bottom = 130.0f;

		dst.m_top = 150.0f;
		dst.m_left = 150.0f;
		dst.m_right = 270.0f;
		dst.m_bottom = 270.0f;
		Draw::Draw(150, &src, &dst, white, 0.0f);

		//���Z���摜��\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 130.0f;
		src.m_bottom = 130.0f;

		dst.m_top = 290.0f;
		dst.m_left = 150.0f;
		dst.m_right = 270.0f;
		dst.m_bottom = 410.0f;
		Draw::Draw(151, &src, &dst, white, 0.0f);

		//���ΏZ���摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 130.0f;
		src.m_bottom = 130.0f;

		dst.m_top = 430.0f;
		dst.m_left = 150.0f;
		dst.m_right = 270.0f;
		dst.m_bottom = 550.0f;
		Draw::Draw(152, &src, &dst, white, 0.0f);

		//�����Z���摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 130.0f;
		src.m_bottom = 130.0f;

		dst.m_top = 150.0f;
		dst.m_left = 560.0f;
		dst.m_right = 680.0f;
		dst.m_bottom = 270.0f;
		Draw::Draw(153, &src, &dst, white, 0.0f);

		//���������������摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 130;
		src.m_bottom = 130;

		dst.m_top = 290.0f;
		dst.m_left = 560.0f;
		dst.m_right = 680.0f;
		dst.m_bottom = 410.0f;
		Draw::Draw(154, &src, &dst, white, 0.0f);

		//���c��Z���������܂���(�c��Z��������)�����摜��\��
		src.m_top = 2.0f;
		src.m_left = 0.0f;
		src.m_right = 600.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 470.0f;
		dst.m_left = 560.0f;
		dst.m_right = 770.0f;
		dst.m_bottom = 510.0f;
		Draw::Draw(94, &src, &dst, white, 0.0f);

		//���l�����摜�\��(pow��)
		src.m_top = 2.0f;
		src.m_left = 0.0f;
		src.m_right = 112.0f;
		src.m_bottom = 110.0f;

		dst.m_top = 200.0f;
		dst.m_left = 470.0f;
		dst.m_right = 510.0f;
		dst.m_bottom = 240.0f;
		Draw::Draw(77, &src, &dst, white, 0.0f);

		//���l�����摜�\��(spe��)
		src.m_top = 2.0f;
		src.m_left = 0.0f;
		src.m_right = 112.0f;
		src.m_bottom = 110.0f;

		dst.m_top = 330.0f;
		dst.m_left = 470.0f;
		dst.m_right = 510.0f;
		dst.m_bottom = 370.0f;
		Draw::Draw(77, &src, &dst, white, 0.0f);

		//���l�����摜�\��(def��)
		src.m_top = 2.0f;
		src.m_left = 0.0f;
		src.m_right = 112.0f;
		src.m_bottom = 110.0f;

		dst.m_top = 470.0f;
		dst.m_left = 470.0f;
		dst.m_right = 510.0f;
		dst.m_bottom = 510.0f;
		Draw::Draw(77, &src, &dst, white, 0.0f);

		//���l�����摜�\��(bal��)
		src.m_top = 2.0f;
		src.m_left = 0.0f;
		src.m_right = 112.0f;
		src.m_bottom = 110.0f;

		dst.m_top = 200.0f;
		dst.m_left = 1050.0f;
		dst.m_right = 1090.0f;
		dst.m_bottom = 240.0f;
		Draw::Draw(77, &src, &dst, white, 0.0f);

		//���l�����摜�\��(��������)
		src.m_top = 2.0f;
		src.m_left = 0.0f;
		src.m_right = 112.0f;
		src.m_bottom = 110.0f;

		dst.m_top = 330.0f;
		dst.m_left = 1050.0f;
		dst.m_right = 1090.0f;
		dst.m_bottom = 370.0f;
		Draw::Draw(77, &src, &dst, white, 0.0f);

		//���c��@�@�@�l(�c��)���������摜�\��
		src.m_top = 2.0f;
		src.m_left = 0.0f;
		src.m_right = 592.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 470.0f;
		dst.m_left = 800.0f;
		dst.m_right = 1010.0f;
		dst.m_bottom = 510.0f;
		Draw::Draw(78, &src, &dst, red, 0.0f);

		//���l�����摜�\��(�c��Z����)
		src.m_top = 2.0f;
		src.m_left = 0.0f;
		src.m_right = 112.0f;
		src.m_bottom = 110.0f;

		dst.m_top = 470.0f;
		dst.m_left = 1050.0f;
		dst.m_right = 1090.0f;
		dst.m_bottom = 510.0f;
		Draw::Draw(77, &src, &dst, red, 0.0f);

		//���t�H���g�\��
		//�Z���X�e�[�^�X
		//���b�h
		FontDraw(NumConversion(g_Power_num)   , 440, 200, 30, 40, white, true);
		//Font::StrDraw(human_num[0], 355.0f, 200.0f, 35.0f, black);

		//�u���[
		FontDraw(NumConversion(g_Defense_num) , 440, 330, 30, 40, white, true);
		//Font::StrDraw(human_num[1], 355.0f, 330.0f, 35.0f, black);

		//�O���[��
		FontDraw(NumConversion(g_Speed_num)   , 440, 470, 30, 40, white, true);
		//Font::StrDraw(human_num[2], 355.0f, 470.0f, 35.0f, black);

		//�z���C�g
		FontDraw(NumConversion(g_Balance_num) , 1020, 200, 30, 40, white, true);
		//Font::StrDraw(human_num[3], 865.0f, 200.0f, 35.0f, black);

		//������
		FontDraw(NumConversion(g_Research_num), 1020, 330, 30, 40, white, true);
		//Font::StrDraw(Research_num, 865.0f, 330.0f, 35.0f, black);

		//�c��̏Z����
		FontDraw(NumConversion(g_Remain_num), 1020, 470, 30, 40, red, true);
		//Font::StrDraw(human_remain, 780.0f, 470.0f, 35.0f, red);

	}

	//�X�y�V�����Z�{�^���������ĕ`�悷��摜
	else if (window_start_manage == Specialskill)
	{
		//���E�B���h�E�\��(�_�~�[�q�ɃE�B���h�E�p)
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1200.0f;
		src.m_bottom = 700.0f;

		dst.m_top = 20.0f;
		dst.m_left = 20.0f;
		dst.m_right = 1180.0f;
		dst.m_bottom = 680.0f;
		Draw::Draw(20, &src, &dst, sb, 0.0f);

		//���E�B���h�E�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1200.0f;
		src.m_bottom = 700.0f;

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

		dst.m_top = 80.0f;
		dst.m_left = 80.0f;
		dst.m_right = 130.0f;
		dst.m_bottom = 130.0f;
		Draw::Draw(1, &src, &dst, md, 0.0f);

		//���X�y�V�����Z�����摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 712.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 80.0f;
		dst.m_left = 405.0f;
		dst.m_right = 755.0f;
		dst.m_bottom = 130.0f;
		Draw::Draw(148, &src, &dst, white, 0.0f);

		for (int i = 0; i < 5; i++)//���b�Z�[�W�E�B���h�E��K�؂Ȉʒu�ɂT��\��������
		{
			//�X�y�V�����Z���b�Z�[�W�E�B���h�E�\������
			src.m_top = -10.0f;
			src.m_left = 0.0f;
			src.m_right = 795.0f;
			src.m_bottom = 800.0f;

			dst.m_top = 140.0f + (i * 100);
			dst.m_left = 290.0f;
			dst.m_right = 340.0f;
			dst.m_bottom = 190.0f + (i * 100);
			Draw::Draw(132, &src, &dst, it, 0.0f);

			//�X�y�V�����Z���b�Z�[�W�E�B���h�E�\������
			src.m_top = 40.0f;
			src.m_left = 800.0f;
			src.m_right = 1600.0f;
			src.m_bottom = 800.0f;

			dst.m_top = 180.0f + (i * 100);
			dst.m_left = 290.0f;
			dst.m_right = 340.0f;
			dst.m_bottom = 230.0f + (i * 100);
			Draw::Draw(132, &src, &dst, it, 0.0f);

			for (int j = 0; j < 14; j++)
			{
				//�X�y�V�����Z���b�Z�[�W�E�B���h�E�\��������
				src.m_top = -10.0f;
				src.m_left = 1600.0f;
				src.m_right = 2400.0f;
				src.m_bottom = 800.0f;

				dst.m_top = 140.0f + (i * 100);
				dst.m_left = 340.0f + (j * 50);
				dst.m_right = 390.0f + (j * 50);
				dst.m_bottom = 190.0f + (i * 100);
				Draw::Draw(132, &src, &dst, it, 0.0f);

				//�X�y�V�����Z���b�Z�[�W�E�B���h�E�\��������
				src.m_top = 0.0f;
				src.m_left = 2400.0f;
				src.m_right = 3200.0f;
				src.m_bottom = 800.0f;

				dst.m_top = 180.0f + (i * 100);
				dst.m_left = 340.0f + (j * 50);
				dst.m_right = 390.0f + (j * 50);
				dst.m_bottom = 230.0f + (i * 100);
				Draw::Draw(132, &src, &dst, it, 0.0f);

			}

			//�X�y�V�����Z���b�Z�[�W�E�B���h�E�\���E��
			src.m_top = -10.0f;
			src.m_left = 4000.0f;
			src.m_right = 4800.0f;
			src.m_bottom = 800.0f;

			dst.m_top = 140.0f + (i * 100);
			dst.m_left = 1013.0f;
			dst.m_right = 1063.0f;
			dst.m_bottom = 190.0f + (i * 100);
			Draw::Draw(132, &src, &dst, it, 0.0f);

			//�X�y�V�����Z���b�Z�[�W�E�B���h�E�\���E��
			src.m_top = 0.0f;
			src.m_left = 4800.0f;
			src.m_right = 5600.0f;
			src.m_bottom = 800.0f;

			dst.m_top = 180.0f + (i * 100);
			dst.m_left = 1013.0f;
			dst.m_right = 1063.0f;
			dst.m_bottom = 230.0f + (i * 100);
			Draw::Draw(132, &src, &dst, it, 0.0f);
		}

		//�X�y�V�����{�^���̋��ʐ؂���ʒu�ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 130.0f;
		src.m_bottom = 130.0f;

		//�����݂̃X�y�V�����Z�K���󋵁A�����󋵂ɉ�����
		//�X�y�V�����Z�A�C�R���̃J���[���x���ȉ��̂悤�ɐݒ肵�Ă����B
		//�u���K���v�c�c�c�c�c�c�c�c�c�c�c0.0f(���F)
		//�u�N���b�N�ő�����(�K����)�v�c�c0.4f(�D�F)
		//�u�������v�c�c�c�c�c�c�c�c�c�c�c1.0f(���F)



		//Explosion�̔���
		//�܂��\��t���ʒu��ݒ肷��
		dst.m_top = 122.5f;
		dst.m_left = 130.0f;
		dst.m_right = 260.0f;
		dst.m_bottom = 252.5f;
		Draw::Draw(40, &src, &dst, it, 0.0f);

		//������̘f���ɕ����摜��\��
		src.m_top = 2.0f;
		src.m_left = 0.0f;
		src.m_right = 713.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 168.5f;
		dst.m_left = 310.0f;
		dst.m_right = 520.0f;
		dst.m_bottom = 203.5f;
		Draw::Draw(95, &src, &dst, black, 0.0f);

		//���Œ�_���[�W��^���镶���摜��\��
		src.m_top = 2.0f;
		src.m_left = 0.0f;
		src.m_right = 1180.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 168.5f;
		dst.m_left = 525.0f;
		dst.m_right = 875.0f;
		dst.m_bottom = 203.5f;
		Draw::Draw(96, &src, &dst, black, 0.0f);

		//Fracture Ray�̔���
		//�X�y�V�����{�^���̋��ʐ؂���ʒu�ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 130.0f;
		src.m_bottom = 130.0f;

		//�܂��\��t���ʒu��ݒ肷��
		dst.m_top = 222.5f;
		dst.m_left = 130.0f;
		dst.m_right = 260.0f;
		dst.m_bottom = 352.5f;
		Draw::Draw(41, &src, &dst, it, 0.0f);

		//���I�����C����̕����摜��\��
		src.m_top = 2.0f;
		src.m_left = 0.0f;
		src.m_right = 832.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 268.5f;
		dst.m_left = 310.0f;
		dst.m_right = 555.0f;
		dst.m_bottom = 303.5f;
		Draw::Draw(97, &src, &dst, black, 0.0f);

		//������|�b�h����j�󂷂镶���摜��\��
		src.m_top = 2.0f;
		src.m_left = 0.0f;
		src.m_right = 1304.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 268.5f;
		dst.m_left = 558.0f;
		dst.m_right = 943.0f;
		dst.m_bottom = 303.5f;
		Draw::Draw(98, &src, &dst, black, 0.0f);

		//Immotality�̔���
		//�X�y�V�����{�^���̋��ʐ؂���ʒu�ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 130.0f;
		src.m_bottom = 130.0f;

		//�܂��\��t���ʒu��ݒ肷��
		dst.m_top = 322.5f;
		dst.m_left = 130.0f;
		dst.m_right = 260.0f;
		dst.m_bottom = 452.5f;
		Draw::Draw(42, &src, &dst, it, 0.0f);

		//����10�b�Ԃ̕����摜��\��
		src.m_top = 2.0f;
		src.m_left = 0.0f;
		src.m_right = 532.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 368.5f;
		dst.m_left = 310.0f;
		dst.m_right = 485.0f;
		dst.m_bottom = 403.5f;
		Draw::Draw(99, &src, &dst, black, 0.0f);

		//�����G�ƂȂ镶���摜��\��
		src.m_top = 2.0f;
		src.m_left = 0.0f;
		src.m_right = 584.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 368.5f;
		dst.m_left = 488.0f;
		dst.m_right = 663.0f;
		dst.m_bottom = 403.5f;
		Draw::Draw(100, &src, &dst, black, 0.0f);

		//�I�[�o�[���[�N�̔���
		//�X�y�V�����{�^���̋��ʐ؂���ʒu�ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 130.0f;
		src.m_bottom = 130.0f;

		//�܂��\��t���ʒu��ݒ肷��
		dst.m_top = 422.5f;
		dst.m_left = 130.0f;
		dst.m_right = 260.0f;
		dst.m_bottom = 552.5f;
		Draw::Draw(43, &src, &dst, it, 0.0f);

		//��10�b�ԃ|�b�h���Y���x�̕����摜��\��
		src.m_top = 2.0f;
		src.m_left = 0.0f;
		src.m_right = 1252.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 466.5f;
		dst.m_left = 305.0f;
		dst.m_right = 690.0f;
		dst.m_bottom = 501.5f;
		Draw::Draw(101, &src, &dst, black, 0.0f);

		//���~�T�C�����Y���xUP�̕����摜��\��
		src.m_top = 2.0f;
		src.m_left = 0.0f;
		src.m_right = 1134.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 466.5f;
		dst.m_left = 693.0f;
		dst.m_right = 1043.0f;
		dst.m_bottom = 501.5f;
		Draw::Draw(102, &src, &dst, black, 0.0f);

		//���~�b�g�u���C�N�̔���
		//�X�y�V�����{�^���̋��ʐ؂���ʒu�ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 130.0f;
		src.m_bottom = 130.0f;

		//�܂��\��t���ʒu��ݒ肷��
		dst.m_top = 522.5f;
		dst.m_left = 130.0f;
		dst.m_right = 260.0f;
		dst.m_bottom = 652.5f;
		Draw::Draw(44, &src, &dst, it, 0.0f);

		//���o�����镶���摜��\��
		src.m_top = 2.0f;
		src.m_left = 0.0f;
		src.m_right = 464.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 566.5f;
		dst.m_left = 310.0f;
		dst.m_right = 450.0f;
		dst.m_bottom = 601.5f;
		Draw::Draw(103, &src, &dst, black, 0.0f);

		//���|�b�h5�@�̍U����UP�����摜��\��
		src.m_top = 2.0f;
		src.m_left = 0.0f;
		src.m_right = 1222.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 566.5f;
		dst.m_left = 453.0f;
		dst.m_right = 838.0f;
		dst.m_bottom = 601.5f;
		Draw::Draw(104, &src, &dst, black, 0.0f);

	}
		//�����{�^���������ĕ`�悷��摜
		else if (window_start_manage == Soubicheck)
		{
			//���E�B���h�E�\��(�_�~�[�q�ɃE�B���h�E�p)
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 1200.0f;
			src.m_bottom = 700.0f;

			dst.m_top = 20.0f;
			dst.m_left = 20.0f;
			dst.m_right = 1180.0f;
			dst.m_bottom = 680.0f;
			Draw::Draw(20, &src, &dst, sb, 0.0f);

			//���E�B���h�E�\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 1200.0f;
			src.m_bottom = 700.0f;

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

			dst.m_top = 80.0f;
			dst.m_left = 80.0f;
			dst.m_right = 130.0f;
			dst.m_bottom = 130.0f;
			Draw::Draw(1, &src, &dst, md, 0.0f);

			//���|�b�h�����摜�����摜��\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 344.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 80.0f;
			dst.m_left = 525.0f;
			dst.m_right = 675.0f;
			dst.m_bottom = 130.0f;
			Draw::Draw(149, &src, &dst, white, 0.0f);

			//�����b�h�����摜��\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 336.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 200.0f;
			dst.m_left = 150.0f;
			dst.m_right = 270.0f;
			dst.m_bottom = 240.0f;
			Draw::Draw(82, &src, &dst, red, 0.0f);

			//���R�A�����摜��\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 186.0f;
			src.m_bottom = 84.0f;

			dst.m_top = 202.5f;
			dst.m_left = 283.0f;
			dst.m_right = 358.0f;
			dst.m_bottom = 237.5f;
			Draw::Draw(146, &src, &dst, red, 0.0f);

			if (g_Pow_equip_Level == 1)
			{
				//�����b�h�R�ALv.1�摜��\��
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 130.0f;
				src.m_bottom = 130.0f;

				dst.m_top = 150.0f;
				dst.m_left = 420.0f;
				dst.m_right = 540.0f;
				dst.m_bottom = 270.0f;
				Draw::Draw(49, &src, &dst, white, 0.0f);
			}

			if (g_Pow_equip_Level == 2)
			{
				//�����b�h�R�ALv.2�摜��\��
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 130.0f;
				src.m_bottom = 130.0f;

				dst.m_top = 150.0f;
				dst.m_left = 420.0f;
				dst.m_right = 540.0f;
				dst.m_bottom = 270.0f;
				Draw::Draw(50, &src, &dst, white, 0.0f);
			}

			if (g_Pow_equip_Level == 3)
			{
				//�����b�h�R�ALv.3�摜��\��
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 130.0f;
				src.m_bottom = 130.0f;

				dst.m_top = 150.0f;
				dst.m_left = 420.0f;
				dst.m_right = 540.0f;
				dst.m_bottom = 270.0f;
				Draw::Draw(51, &src, &dst, white, 0.0f);
			}

			//���u���[�����摜��\��
			src.m_top = 2.0f;
			src.m_left = 0.0f;
			src.m_right = 352.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 350.0f;
			dst.m_left = 150.0f;
			dst.m_right = 270.0f;
			dst.m_bottom = 390.0f;
			Draw::Draw(83, &src, &dst, blue, 0.0f);

			//���R�A�����摜��\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 186.0f;
			src.m_bottom = 84.0f;

			dst.m_top = 352.5f;
			dst.m_left = 283.0f;
			dst.m_right = 358.0f;
			dst.m_bottom = 390.0f;
			Draw::Draw(146, &src, &dst, blue, 0.0f);

			if (g_Def_equip_Level == 1)
			{
				//���u���[�R�ALv.1�摜��\��
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 130.0f;
				src.m_bottom = 130.0f;

				dst.m_top = 300.0f;
				dst.m_left = 420.0f;
				dst.m_right = 540.0f;
				dst.m_bottom = 420.0f;
				Draw::Draw(52, &src, &dst, white, 0.0f);
			}

			if (g_Def_equip_Level == 2)
			{
				//���u���[�R�ALv.2�摜��\��
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 130.0f;
				src.m_bottom = 130.0f;

				dst.m_top = 300.0f;
				dst.m_left = 420.0f;
				dst.m_right = 540.0f;
				dst.m_bottom = 420.0f;
				Draw::Draw(53, &src, &dst, white, 0.0f);
			}

			if (g_Def_equip_Level == 3)
			{
				//���u���[�R�ALv.3�摜��\��
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 130.0f;
				src.m_bottom = 130.0f;

				dst.m_top = 300.0f;
				dst.m_left = 420.0f;
				dst.m_right = 540.0f;
				dst.m_bottom = 420.0f;
				Draw::Draw(54, &src, &dst, white, 0.0f);
			}

			//���O���[�������摜�\��
			src.m_top = 2.0f;
			src.m_left = 2.0f;
			src.m_right = 472.0f;
			src.m_bottom = 110.0f;

			dst.m_top = 490.0f;
			dst.m_left = 150.0f;
			dst.m_right = 310.0f;
			dst.m_bottom = 530.0f;
			Draw::Draw(84, &src, &dst, green, 0.0f);

			//���R�A�����摜��\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 186.0f;
			src.m_bottom = 84.0f;

			dst.m_top = 492.5f;
			dst.m_left = 318.0f;
			dst.m_right = 398.0f;
			dst.m_bottom = 530.0f;
			Draw::Draw(146, &src, &dst, green, 0.0f);

			if (g_Spe_equip_Level == 1)
			{
				//���O���[���R�ALv.1�摜��\��
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 130.0f;
				src.m_bottom = 130.0f;

				dst.m_top = 450.0f;
				dst.m_left = 420.0f;
				dst.m_right = 540.0f;
				dst.m_bottom = 570.0f;
				Draw::Draw(55, &src, &dst, white, 0.0f);
			}

			if (g_Spe_equip_Level == 2)
			{
				//���O���[���R�ALv.2�摜��\��
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 130.0f;
				src.m_bottom = 130.0f;

				dst.m_top = 450.0f;
				dst.m_left = 420.0f;
				dst.m_right = 540.0f;
				dst.m_bottom = 570.0f;
				Draw::Draw(56, &src, &dst, white, 0.0f);
			}

			if (g_Spe_equip_Level == 3)
			{
				//���O���[���R�ALv.3�摜��\��
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 130.0f;
				src.m_bottom = 130.0f;

				dst.m_top = 430.0f;
				dst.m_left = 420.0f;
				dst.m_right = 540.0f;
				dst.m_bottom = 550.0f;
				Draw::Draw(57, &src, &dst, white, 0.0f);
			}

			//���z���C�g�����摜�\��
			src.m_top = 2.0f;
			src.m_left = 0.0f;
			src.m_right = 464.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 280.0f;
			dst.m_left = 590.0f;
			dst.m_right = 750.0f;
			dst.m_bottom = 320.0f;
			Draw::Draw(85, &src, &dst, white, 0.0f);

			//���R�A�����摜��\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 186.0f;
			src.m_bottom = 84.0f;

			dst.m_top = 282.5f;
			dst.m_left = 758.0f;
			dst.m_right = 838.0f;
			dst.m_bottom = 320.0f;
			Draw::Draw(146, &src, &dst, white, 0.0f);

			if (g_Bal_equip_Level == 1)
			{
				//���z���C�g�R�ALv.1�摜��\��
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 130.0f;
				src.m_bottom = 130.0f;

				dst.m_top = 230.0f;
				dst.m_left = 860.0f;
				dst.m_right = 980.0f;
				dst.m_bottom = 350.0f;
				Draw::Draw(58, &src, &dst, white, 0.0f);
			}

			if (g_Bal_equip_Level == 2)
			{
				//���z���C�g�R�ALv.2�摜��\��
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 130.0f;
				src.m_bottom = 130.0f;

				dst.m_top = 230.0f;
				dst.m_left = 860.0f;
				dst.m_right = 980.0f;
				dst.m_bottom = 350.0f;
				Draw::Draw(59, &src, &dst, white, 0.0f);
			}

			if (g_Bal_equip_Level == 3)
			{
				//���z���C�g�R�ALv.3�摜��\��
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 130.0f;
				src.m_bottom = 130.0f;

				dst.m_top = 230.0f;
				dst.m_left = 860.0f;
				dst.m_right = 980.0f;
				dst.m_bottom = 350.0f;
				Draw::Draw(60, &src, &dst, white, 0.0f);
			}

			//���|�b�h�����摜�\��
			src.m_top = 2.0f;
			src.m_left = 0.0f;
			src.m_right = 344.0f;
			src.m_bottom = 112.0f;

			dst.m_top = 420.0f;
			dst.m_left = 590.0f;
			dst.m_right = 710.0f;
			dst.m_bottom = 460.0f;
			Draw::Draw(86, &src, &dst, yellow, 0.0f);

			if (g_Pod_equip_Level == 1)
			{
				//���|�b�hLv.1�摜��\��
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 130.0f;
				src.m_bottom = 130.0f;

				dst.m_top = 380.0f;
				dst.m_left = 860.0f;
				dst.m_right = 980.0f;
				dst.m_bottom = 500.0f;
				Draw::Draw(128, &src, &dst, white, 0.0f);
			}

			if (g_Pod_equip_Level == 2)
			{
				//���|�b�hLv.2�摜��\��
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 130.0f;
				src.m_bottom = 130.0f;

				dst.m_top = 380.0f;
				dst.m_left = 860.0f;
				dst.m_right = 980.0f;
				dst.m_bottom = 500.0f;
				Draw::Draw(129, &src, &dst, white, 0.0f);
			}

			if (g_Pod_equip_Level == 3)
			{
				//���|�b�hLv.3�摜��\��
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 130.0f;
				src.m_bottom = 130.0f;

				dst.m_top = 380.0f;
				dst.m_left = 860.0f;
				dst.m_right = 980.0f;
				dst.m_bottom = 500.0f;
				Draw::Draw(130, &src, &dst, white, 0.0f);
			}

			////���b�h���x���\�������摜
			//src.m_top = 0.0f;
			//src.m_left = 0.0f;
			//src.m_right = 312.0f;
			//src.m_bottom = 107.0f;

			//dst.m_top = 200.0f;
			//dst.m_left = 360.0f;
			//dst.m_right = 480.0f;
			//dst.m_bottom = 240.0f;
			//Draw::Draw(122 + g_Pow_equip_Level, &src, &dst, black, 0.0f);
			////Font::StrDraw(type_num[0], 355.0f, 200.0f, 40.0f, black);

			////�u���[���x���\�������摜
			//src.m_top = 0.0f;
			//src.m_left = 0.0f;
			//src.m_right = 312.0f;
			//src.m_bottom = 107.0f;

			//dst.m_top = 330.0f;
			//dst.m_left = 360.0f;
			//dst.m_right = 480.0f;
			//dst.m_bottom = 370.0f;
			//Draw::Draw(122 + g_Def_equip_Level, &src, &dst, black, 0.0f);
			////Font::StrDraw(type_num[1], 360.0f, 460.0f, 40.0f, black);

			////�O���[�����x���\�������摜
			//src.m_top = 0.0f;
			//src.m_left = 0.0f;
			//src.m_right = 312.0f;
			//src.m_bottom = 107.0f;

			//dst.m_top = 460.0f;
			//dst.m_left = 360.0f;
			//dst.m_right = 480.0f;
			//dst.m_bottom = 500.0f;
			//Draw::Draw(122 + g_Spe_equip_Level, &src, &dst, black, 0.0f);
			////Font::StrDraw(type_num[2], 360.0f, 330.0f, 40.0f, black);

			////�z���C�g���x���\�������摜
			//src.m_top = 0.0f;
			//src.m_left = 0.0f;
			//src.m_right = 312.0f;
			//src.m_bottom = 107.0f;

			//dst.m_top = 260.0f;
			//dst.m_left = 900.0f;
			//dst.m_right = 1020.0f;
			//dst.m_bottom = 300.0f;
			//Draw::Draw(122 + g_Bal_equip_Level, &src, &dst, black, 0.0f);
			////Font::StrDraw(type_num[3], 880.0f, 200.0f, 40.0f, black);

			////���|�b�h���x���\�������摜
			//src.m_top = 0.0f;
			//src.m_left = 0.0f;
			//src.m_right = 312.0f;
			//src.m_bottom = 107.0f;

			//dst.m_top = 400.0f;
			//dst.m_left = 900.0f;
			//dst.m_right = 1020.0f;
			//dst.m_bottom = 440.0f;
			//Draw::Draw(122 + g_Pod_equip_Level, &src, &dst, black, 0.0f);
			////Font::StrDraw(type_num[4], 880.0f, 330.0f, 40.0f, black);

		}
	}
