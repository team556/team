//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjWarehouse.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�}�N��
#define INI_ALPHA (0.0f) //���ߓx(�A���t�@�l)�̏����l
#define INI_COLOR (0.9f) //�S�J���[���x�̏����l

//�O���[�o���ϐ��̒�`
int g_Ware = 1;


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

	k = 0; //���ނ̏������Ă��鐔
	p = 0;//�Z���p���[�̒l
	s = 0;//�Z���X�s�[�h�̒l
	d = 0;//�Z���f�B�t�F���X�̒l
	b = 0;//�Z���o�����X�̒l
	r = 0;//�������̒l
	crvp = 0;//�␳�l�p���[
	crvs = 0;//�␳�l�X�s�[�h
	crvd = 0;//�␳�l�f�B�t�F���X
	crvbh = 0;//�␳�l�o�����X	�̗�
	crvbp = 0;//�␳�l�o�����X	�p���[
	crvbs = 0;//�␳�l�o�����X	�X�s�[�h
	crvr = 0;//�␳�l������

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


	//���q�ɃE�B���h�E�\���̏���
	if (window_start_manage == Warehouse)
	{
		//�߂�{�^���I��
		if (30 < m_mou_x && m_mou_x < 80 && 30 < m_mou_y && m_mou_y < 80)
		{
			m_Back_Button_color = 1.0f;

			//���N���b�N���ꂽ��t���O�𗧂āA�q�ɃE�C���h�E�����
			if (m_mou_l == true)
			{
				//�N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
				if (m_key_lf == true)
				{
					m_key_lf = false;

					//"�ǂ̃E�C���h�E���J���Ă��Ȃ����"�t���O�𗧂Ă�
					window_start_manage = Default;
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
		if (245 < m_mou_x && m_mou_x < 560 && 150 < m_mou_y && m_mou_y < 325)
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
		if (680 < m_mou_x && m_mou_x < 1005 && 150 < m_mou_y && m_mou_y < 325)
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
		if (245 < m_mou_x && m_mou_x < 560 && 390 < m_mou_y && m_mou_y < 570)
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
		if (680 < m_mou_x && m_mou_x < 1005 && 390 < m_mou_y && m_mou_y < 570)
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

	//���ށA�Z���A�X�y�V�����Z�A������ʂ̖߂�{�^��
	if (window_start_manage == Materials|| window_start_manage == Residents||
		window_start_manage == Specialskill|| window_start_manage == Soubicheck)
	{
		//�߂�{�^���I��
		if (50 < m_mou_x && m_mou_x < 100 && 50 < m_mou_y && m_mou_y < 100)
		{
			m_Back_Button_color = 1.0f;

			//���N���b�N���ꂽ��t���O�𗧂āA�q�ɃE�C���h�E�����
			if (m_mou_l == true)
			{
				//�N���b�N�������܂܂̏�Ԃł͓��͏o���Ȃ��悤�ɂ��Ă���
				if (m_key_lf == true)
				{
					m_key_lf = false;

					//"�ǂ̃E�C���h�E���J���Ă��Ȃ����"�t���O�𗧂Ă�
					window_start_manage = Warehouse;
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

	//���t�H���g����
	//�q�ɗp
	wchar_t Ware[5];
	swprintf_s(Ware, L"�q��", g_Ware);

	//����(���O�E�����Ă��鐔)�\��
	wchar_t mrl[256];
	swprintf_s(mrl, L"%d ��", k);

	//�Z��(�e�X�e�[�^�X)�\��
	//�p���[
	wchar_t pow[256];
	swprintf_s(pow, L"Lv%d", p);

	//�X�s�[�h
	wchar_t spd[256];
	swprintf_s(spd, L"Lv%d", s);

	//�f�B�t�F���X
	wchar_t dfs[256];
	swprintf_s(dfs, L"Lv%d", d);

	//�o�����X
	wchar_t brs[256];
	swprintf_s(brs, L"Lv%d", b);

	//������
	wchar_t rsc[256];
	swprintf_s(rsc, L"Lv%d", r);

	//�␳�l�p���[
	wchar_t crvp[256];
	swprintf_s(crvp, L"�U���́{%d", crvp);

	//�␳�l�X�s�[�h
	wchar_t crvs[256];
	swprintf_s(crvs, L"�f�����{%d", crvs);

	//�␳�l�f�B�t�F���X
	wchar_t crvd[256];
	swprintf_s(crvd, L"�̗�  �{%d", crvd);

	//�␳�l�o�����X	�̗�
	wchar_t crvbh[256];
	swprintf_s(crvbh, L"�̗�  �{%d", crvbh);
	//�␳�l�o�����X	�p���[
	wchar_t crvbp[256];
	swprintf_s(crvbp, L"�U���́{%d", crvbp);
	//�␳�l�o�����X	�X�s�[�h
	wchar_t crvbs[256];
	swprintf_s(crvbs, L"�f�����{%d", crvbs);

	//�␳�l������
	wchar_t crvr[256];
	swprintf_s(crvr, L"%d", crvr);

	RECT_F src;//�`���؂���ʒu
	RECT_F dst;//�`���\���ʒu

	//�{�ݏЉ�E�B���h�E(���ɁA�������A�q��)���J���Ă��Ȃ����ɕ\������O���t�B�b�N
	if (window_start_manage == Default || window_start_manage == BackButton)
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

		    //���t�H���g�\��
		    //�q��
			Font::StrDraw(Ware, m_mou_x - 40.0f, m_mou_y - 45.0f, 30.0f, black);

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

		dst.m_top    = 150.0f;
		dst.m_left   = 250.0f;
		dst.m_right  = 560.0f;
		dst.m_bottom = 325.0f;
		Draw::Draw(28, &src, &dst, ma, 0.0f);

		//���Z���I���{�^���\��
		src.m_top	 = 0.0f;
		src.m_left	 = 0.0f;
		src.m_right	 = 307.0f;
		src.m_bottom = 175.0f;

		dst.m_top    = 150.0f;
		dst.m_left   = 700.0f;
		dst.m_right  = 1005.0f;
		dst.m_bottom = 325.0f;
		Draw::Draw(29, &src, &dst, re, 0.0f);

		//���X�y�V�����Z�I���{�^���\��
		src.m_top	 = 0.0f;
		src.m_left   = 0.0f;
		src.m_right	 = 307.0f;
		src.m_bottom = 175.0f;

		dst.m_top    = 400.0f;
		dst.m_left   = 250.0f;
		dst.m_right  = 560.0f;
		dst.m_bottom = 570.0f;
		Draw::Draw(30, &src, &dst, sp, 0.0f);

		//�������I���{�^���\��
		src.m_top	 = 0.0f;
		src.m_left	 = 0.0f;
		src.m_right  = 307.0f;
		src.m_bottom = 175.0f;

		dst.m_top    = 400.0f;
		dst.m_left   = 700.0f;
		dst.m_right  = 1005.0f;
		dst.m_bottom = 570.0f;
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

		    //���t�H���g�\��
			//���������x��
			Font::StrDraw(Ware, m_mou_x - 95.0f, m_mou_y - 45.0f, 30.0f, black);

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
		dst.m_left = 120.0f;
		dst.m_right = 257.0f;
		dst.m_bottom = 197.0f;
		Draw::Draw(33, &src, &dst, it, 0.0f);
		Font::StrDraw(L"�؍�", 280.0f, 130.0f,30.0f, black);
		Font::StrDraw(mrl, 280.0f, 170.0f, 30.0f, black);

		//���S�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 160.0f;
		src.m_bottom = 160.0f;

		dst.m_top = 120.0f;
		dst.m_left = 450.0f;
		dst.m_right = 560.0f;
		dst.m_bottom = 230.0f;
		Draw::Draw(34, &src, &dst, it, 0.0f);
		Font::StrDraw(L"�S", 580.0f, 130.0f, 30.0f, black);
		Font::StrDraw(mrl, 580.0f, 170.0f, 30.0f, black);

		//����\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 160.0f;
		src.m_bottom = 160.0f;

		dst.m_top = 120.0f;
		dst.m_left = 800.0f;
		dst.m_right = 910.0f;
		dst.m_bottom = 230.0f;
		Draw::Draw(35, &src, &dst, it, 0.0f);
		Font::StrDraw(L"��", 950.0f, 130.0f, 30.0f, black);
		Font::StrDraw(mrl, 950.0f, 170.0f, 30.0f, black);

		//���v���X�`�b�N�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 135.0f;
		src.m_bottom = 245.0f;

		dst.m_top = 240.0f;
		dst.m_left = 110.0f;
		dst.m_right = 245.0f;
		dst.m_bottom = 390.0f;
		Draw::Draw(36, &src, &dst, it, 0.0f);
		Font::StrDraw(L"�v���X�`�b�N", 240.0f, 280.0f, 30.0f, black);
		Font::StrDraw(mrl, 240.0f, 330.0f, 30.0f, black);

		//���A���~�j�E���\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 160.0f;
		src.m_bottom = 160.0f;

		dst.m_top = 270.0f;
		dst.m_left = 450.0f;
		dst.m_right = 560.0f;
		dst.m_bottom = 380.0f;
		Draw::Draw(37, &src, &dst, it, 0.0f);
		Font::StrDraw(L"�A���~�j�E��", 580.0f, 280.0f, 30.0f, black);
		Font::StrDraw(mrl, 580.0f, 330.0f, 30.0f, black);

		//���K�X�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 300.0f;
		src.m_bottom = 300.0f;

		dst.m_top = 240.0f;
		dst.m_left = 780.0f;
		dst.m_right = 930.0f;
		dst.m_bottom = 390.0f;
		Draw::Draw(38, &src, &dst, it, 0.0f);
		Font::StrDraw(L"�K�X", 950.0f, 280.0f, 30.0f, black);
		Font::StrDraw(mrl, 950.0f, 330.0f, 30.0f, black);

		//�����A���^���\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 160.0f;
		src.m_bottom = 160.0f;

		dst.m_top = 440.0f;
		dst.m_left = 450.0f;
		dst.m_right = 560.0f;
		dst.m_bottom = 550.0f;
		Draw::Draw(39, &src, &dst, it, 0.0f);
		Font::StrDraw(L"���A���^��", 580.0f, 450.0f, 30.0f, black);
		Font::StrDraw(mrl, 580.0f, 500.0f, 30.0f, black);
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
		
		//���t�H���g�\��
		//�Z���X�e�[�^�X
		//�p���[
		Font::StrDraw(L"�p���[", 180.0f, 130.0f, 30.0f, black);
		Font::StrDraw(pow,300.0f, 130.0f, 30.0f, black);
		Font::StrDraw(L"�␳�l", 180.0f, 200.0f, 30.0f, black);
		Font::StrDraw(crvp, 300.0f, 200.0f, 30.0f, black);
		
		//�X�s�[�h
		Font::StrDraw(L"�X�s�[�h", 180.0f, 300.0f, 30.0f, black);
		Font::StrDraw(spd, 330.0f, 300.0f, 30.0f, black);
		Font::StrDraw(L"�␳�l", 180.0f, 370.0f, 30.0f, black);
		Font::StrDraw(crvs, 300.0f, 370.0f, 30.0f, black);

		//�f�B�t�F���X
		Font::StrDraw(L"�f�B�t�F���X", 180.0f, 470.0f, 30.0f, black);
		Font::StrDraw(dfs, 390.0f, 470.0f, 30.0f, black);
		Font::StrDraw(L"�␳�l", 180.0f, 540.0f, 30.0f, black);
		Font::StrDraw(crvd, 300.0f, 540.0f, 30.0f, black);

		//�o�����X
		Font::StrDraw(L"�o�����X", 620.0f, 130.0f, 30.0f, black);
		Font::StrDraw(brs, 780.0f, 130.0f, 30.0f, black);
		Font::StrDraw(L"�␳�l", 620.0f, 200.0f, 30.0f, black);
		Font::StrDraw(crvbh, 780.0f, 200.0f, 30.0f, black);
		Font::StrDraw(crvbp, 780.0f, 250.0f, 30.0f, black);
		Font::StrDraw(crvbs, 780.0f, 300.0f, 30.0f, black);

		//������
		Font::StrDraw(L"������", 620.0f, 470.0f, 30.0f, black);
		Font::StrDraw(brs, 780.0f, 470.0f, 30.0f, black);
		Font::StrDraw(L"�␳�l", 620.0f, 540.0f, 30.0f, black);
		Font::StrDraw(crvbh, 780.0f, 540.0f, 30.0f, black);


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

		//�X�y�V�����Z1�I���{�^���\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 100.0f;
		src.m_bottom = 100.0f;

		dst.m_top = 100.0f;
		dst.m_left = 100.0f;
		dst.m_right = 200.0f;
		dst.m_bottom = 200.0f;
		Draw::Draw(40, &src, &dst, it, 0.0f);

		//�X�y�V�����Z2�I���{�^���\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 100.0f;
		src.m_bottom = 100.0f;

		dst.m_top = 200.0f;
		dst.m_left = 100.0f;
		dst.m_right = 200.0f;
		dst.m_bottom = 300.0f;
		Draw::Draw(41, &src, &dst, it, 0.0f);

		//�X�y�V�����Z3�I���{�^���\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 100.0f;
		src.m_bottom = 100.0f;

		dst.m_top = 300.0f;
		dst.m_left = 100.0f;
		dst.m_right = 200.0f;
		dst.m_bottom = 400.0f;
		Draw::Draw(42, &src, &dst, it, 0.0f);

		//�X�y�V�����Z4�I���{�^���\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 100.0f;
		src.m_bottom = 100.0f;

		dst.m_top = 400.0f;
		dst.m_left = 100.0f;
		dst.m_right = 200.0f;
		dst.m_bottom = 500.0f;
		Draw::Draw(43, &src, &dst, it, 0.0f);

		//�X�y�V�����Z5�I���{�^���\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 100.0f;
		src.m_bottom = 100.0f;

		dst.m_top = 500.0f;
		dst.m_left = 100.0f;
		dst.m_right = 200.0f;
		dst.m_bottom = 600.0f;
		Draw::Draw(44, &src, &dst, it, 0.0f);

		//�X�y�V�����Z1���b�Z�[�W�E�B���h�E�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 200.0f;
		src.m_bottom = 100.0f;

		dst.m_top = 100.0f;
		dst.m_left = 300.0f;
		dst.m_right = 1100.0f;
		dst.m_bottom = 200.0f;
		Draw::Draw(45, &src, &dst, it, 0.0f);
		Font::StrDraw(L"�����b�g", 310.0f, 110.0f, 20.0f, black);
		Font::StrDraw(L"����̘f���ɌŒ�_���[�W��^����", 310.0f, 135.0f, 20.0f, black);
		Font::StrDraw(L"�_���[�W�ʂ͘f���̍��HP��1.2�{�̃_���[�W��^����", 310.0f, 160.0f, 20.0f, black);
		Font::StrDraw(L"�f�����b�g", 810.0f, 110.0f, 20.0f, black);
		Font::StrDraw(L"������HP��7%���炷", 810.0f, 135.0f, 20.0f, black);

		//�X�y�V�����Z2���b�Z�[�W�E�B���h�E�\��
		dst.m_top = 200.0f;
		dst.m_left = 300.0f;
		dst.m_right = 1100.0f;
		dst.m_bottom = 300.0f;
		Draw::Draw(45, &src, &dst, it, 0.0f);
		Font::StrDraw(L"�����b�g", 310.0f, 210.0f, 20.0f, black);
		Font::StrDraw(L"����̍U���i���j�����ׂĔj�󂷂�", 310.0f, 235.0f, 20.0f, black);
		Font::StrDraw(L"�f�����b�g", 710.0f, 210.0f, 20.0f, black);
		Font::StrDraw(L"5�b�Ԃ���10�b�ԍU���̓_�E��", 710.0f, 235.0f, 20.0f, black);

		//�X�y�V�����Z3���b�Z�[�W�E�B���h�E�\��
		dst.m_top = 300.0f;
		dst.m_left = 300.0f;
		dst.m_right = 1100.0f;
		dst.m_bottom = 400.0f;
		Draw::Draw(45, &src, &dst, it, 0.0f);
		Font::StrDraw(L"�����b�g", 310.0f, 310.0f, 20.0f, black);
		Font::StrDraw(L"��10�b�Ԗ��G�ɂȂ邱�Ƃ��ł���", 310.0f, 335.0f, 20.0f, black);
		Font::StrDraw(L"�f�����b�g", 710.0f, 310.0f, 20.0f, black);
		Font::StrDraw(L"�U���͂���莞�ԃ_�E��(5�b)", 710.0f, 335.0f, 20.0f, black);

		//�X�y�V�����Z4���b�Z�[�W�E�B���h�E�\��
		dst.m_top = 400.0f;
		dst.m_left = 300.0f;
		dst.m_right = 1100.0f;
		dst.m_bottom = 500.0f;
		Draw::Draw(45, &src, &dst, it, 0.0f);
		Font::StrDraw(L"�����b�g", 310.0f, 410.0f, 20.0f, black);
		Font::StrDraw(L"20�b�ԍU���X�s�[�h�A�b�v", 310.0f, 435.0f, 20.0f, black);
		Font::StrDraw(L"���퐶�Y�p�x�A�b�v", 310.0f, 460.0f, 20.0f, black);
		Font::StrDraw(L"�f�����b�g", 710.0f, 410.0f, 20.0f, black);
		Font::StrDraw(L"���ʂ��I����5�b��", 710.0f, 435.0f, 20.0f, black);
		Font::StrDraw(L"���Y����10%�_�E��", 710.0f, 460.0f, 20.0f, black);

		//�X�y�V�����Z5���b�Z�[�W�E�B���h�E�\��
		dst.m_top = 500.0f;
		dst.m_left = 300.0f;
		dst.m_right = 1100.0f;
		dst.m_bottom = 600.0f;
		Draw::Draw(45, &src, &dst, it, 0.0f);
		Font::StrDraw(L"�����b�g", 310.0f, 510.0f, 20.0f, black);
		Font::StrDraw(L"�Z���̍U�����オ��", 310.0f, 435.0f, 20.0f, black);
		Font::StrDraw(L"���ʂ��I���ƈ�莞��(5�b)", 710.0f, 435.0f, 20.0f, black);
		Font::StrDraw(L"���ʂ��I���ƈ�莞��(5�b)", 710.0f, 435.0f, 20.0f, black);
		Font::StrDraw(L"���ʂ��I���ƈ�莞��(5�b)", 710.0f, 435.0f, 20.0f, black);

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

	}
}

