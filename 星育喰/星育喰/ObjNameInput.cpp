//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjNameInput.h"
#include"UtilityModule.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjNameInput::Init()
{
	m_mou_x = 0.0f;	//�}�E�XX���W
	m_mou_y = 0.0f; //�}�E�XY���W
	m_mou_r = false;//�E�N���b�N
	m_mou_l = false;//���N���b�N
	m_f = true;
	//�N���b�N���ꂽ���̏ꏊ
	for (int i = 0; i < 5; i++)
	{
		if (i == 0)
		{
			click_win[i] = 500;
		}
		else
		{
			click_win[i] =500+64*i;
		}
	}
	//�e�L�X�g��x���̓����蔻��ꏊ�쐬
	for (int i = 0; i < 13; i++)
	{
		if(i==0)
		{ 
			word_x[i] = 250;
		}
		else
		{
			word_x[i] =250 + 64*i;
		}
	}
	//�e�L�X�g��y���̓����蔻��ꏊ�쐬
	for (int i = 0; i < 9; i++)
	{
		switch (i)
		{
		case 0:
			word_y[i] = 245;
			break;
		case 1:
			word_y[i] = 300;
			break;
		case 2:
			word_y[i] = 330;
			break;
		case 3:
			word_y[i] = 385;
			break;
		case 4:
			word_y[i] = 415;
			break;
		case 5:
			word_y[i] = 470;
			break;
		case 6:
			word_y[i] = 500;
			break;
		case 7:
			word_y[i] = 555;
			break;
		case 8:
			word_y[i] = 585;
			break;
		default:
			break;

		}

	}
	click_cut=0;

	m_tex_clar = true;

}

//�A�N�V����
void CObjNameInput::Action()
{
	//�}�E�X�̈ʒu���擾
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//�}�E�X�̃{�^���̏��
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	/*if()*/
	word_x[50];
	word[100][100];
	word_y[100];

	//���O���͂̏���
	//���ڂ�Y��---------------------------------------------------------
	if (word_y[0] < m_mou_y&& m_mou_y < word_y[1] && click_cut!=5)
	{
		//��
		if (m_mou_l == true && word_x[0] < m_mou_x&&m_mou_x < word_x[1])
		{
			//�N���b�N�����������񂾂��ɂ���if��
			if (m_f == false)
			{
				word_w[0][0] = true;			//�����z��̃t���O��true�ɂ���
				m_tex_discri[0] = click_cut;	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
				click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
				m_f = true;
			}
		}
		//��
		else if (m_mou_l == true && word_x[1] < m_mou_x&&m_mou_x < word_x[2])
		{
			//�N���b�N�����������񂾂��ɂ���if��
			if (m_f == false)
			{
				word_w[0][1] = true;			//�����z��̃t���O��true�ɂ���
				m_tex_discri[1] = click_cut;	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
				click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
				m_f = true;
			}
		}
		//��
		else if (m_mou_l == true && word_x[2] < m_mou_x&&m_mou_x < word_x[3])
		{
			//�N���b�N�����������񂾂��ɂ���if��
			if (m_f == false)
			{
				word_w[0][2] = true;			//�����z��̃t���O��true�ɂ���
				m_tex_discri[2] = click_cut;	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
				click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
				m_f = true;
			}
		}
		//��
		else if (m_mou_l == true && word_x[3] < m_mou_x&&m_mou_x < word_x[4])
		{
			//�N���b�N�����������񂾂��ɂ���if��
			if (m_f == false)
			{
				word_w[0][3] = true;			//�����z��̃t���O��true�ɂ���
				m_tex_discri[3] = click_cut;	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
				click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
				m_f = true;
			}
		}
		//��
		else if (m_mou_l == true && word_x[4] < m_mou_x&&m_mou_x < word_x[5])
		{
			//�N���b�N�����������񂾂��ɂ���if��
			if (m_f == false)
			{
				word_w[0][4] = true;			//�����z��̃t���O��true�ɂ���
				m_tex_discri[4] = click_cut;	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
				click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
				m_f = true;
			}
		}
		//��
		else if (m_mou_l == true && word_x[6] < m_mou_x&&m_mou_x < word_x[7])
		{
			//�N���b�N�����������񂾂��ɂ���if��
			if (m_f == false)
			{
				word_w[0][6] = true;			//�����z��̃t���O��true�ɂ���
				m_tex_discri[6] = click_cut;	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
				click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
				m_f = true;
			}
		}
		//��
		else if (m_mou_l == true && word_x[7] < m_mou_x&&m_mou_x < word_x[8])
		{
			//�N���b�N�����������񂾂��ɂ���if��
			if (m_f == false)
			{
				word_w[0][7] = true;			//�����z��̃t���O��true�ɂ���
				m_tex_discri[7] = click_cut;	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
				click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
				m_f = true;
			}
		}
		//��
		else if (m_mou_l == true && word_x[8] < m_mou_x&&m_mou_x < word_x[9])
		{
			//�N���b�N�����������񂾂��ɂ���if��
			if (m_f == false)
			{
				word_w[0][8] = true;			//�����z��̃t���O��true�ɂ���
				m_tex_discri[8] = click_cut;	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
				click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
				m_f = true;
			}
		}
		//��
		else if (m_mou_l == true && word_x[9] < m_mou_x&&m_mou_x < word_x[10])
		{
			//�N���b�N�����������񂾂��ɂ���if��
			if (m_f == false)
			{
				word_w[0][9] = true;			//�����z��̃t���O��true�ɂ���
				m_tex_discri[9] = click_cut;	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
				click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
				m_f = true;
			}
		}
		//��
		else if (m_mou_l == true && word_x[10] < m_mou_x&&m_mou_x < word_x[11])
		{
			//�N���b�N�����������񂾂��ɂ���if��
			if (m_f == false)
			{
				word_w[0][10] = true;			//�����z��̃t���O��true�ɂ���
				m_tex_discri[10] = click_cut;	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
				click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
				m_f = true;
			}
		}
		else
		{
			m_f = false;
		}
	}

	if (m_mou_x > 10 && m_mou_x < 120 && 250 < m_mou_y && 300 > m_mou_y)
	{
		m_tex_clar = false;
	}


}
//�h���[
void CObjNameInput::Draw()
{
	//�����̐F(��)
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//�؂���ʒu
	RECT_F dst;//�\���ʒu

	FontDraw(L"�����N���A", 10.0f, 250.0, 30.0f, 30.0f, c, false);

	if(m_tex_clar==true)
	{ 
		//���N���b�N���ꂽ���̕`��----------------------------------
		if (word_w[0][0] == true)
		{
			FontDraw(L"��", click_win[m_tex_discri[0]], 100.0, 50.0f, 50.0f, c, true);
		}
		if (word_w[0][1] == true)
		{
			FontDraw(L"��", click_win[m_tex_discri[1]], 100.0, 50.0f, 50.0f, c, true);
		}
		if (word_w[0][2] == true)
		{
			FontDraw(L"��", click_win[m_tex_discri[2]], 100.0, 50.0f, 50.0f, c, true);
		}
		if (word_w[0][3] == true)
		{
			FontDraw(L"��", click_win[m_tex_discri[3]], 100.0, 50.0f, 50.0f, c, true);
		}
		if (word_w[0][4] == true)
		{
			FontDraw(L"��", click_win[m_tex_discri[4]], 100.0, 50.0f, 50.0f, c, true);
		}
		if (word_w[0][6] == true)
		{
			FontDraw(L"��", click_win[m_tex_discri[6]], 100.0, 50.0f, 50.0f, c, true);
		}
		if (word_w[0][7] == true)
		{
			FontDraw(L"��", click_win[m_tex_discri[7]], 100.0, 50.0f, 50.0f, c, true);
		}
		if (word_w[0][8] == true)
		{
			FontDraw(L"��", click_win[m_tex_discri[8]], 100.0, 50.0f, 50.0f, c, true);
		}
		if (word_w[0][9] == true)
		{
			FontDraw(L"��", click_win[m_tex_discri[9]], 100.0, 50.0f, 50.0f, c, true);
		}
		if (word_w[0][10] == true)
		{
			FontDraw(L"��", click_win[m_tex_discri[10]], 100.0, 50.0f, 50.0f, c, true);
		}
	}
	else if(m_tex_clar == false)
	{
		for (int i = 0;i < 50;i++)
		{
			for (int j = 0;j < 50;j++)
			{
				word_w[i][j] = false;
			}
		}
		click_cut=0;
		m_tex_clar = true;
	}
	//-----------------------------------------------------------

	//���O����͂��Ă��炤�摜�̓K�p
	src.m_top = 0.0f;

	src.m_left = 0.0f;
	src.m_right =1056.0f;
	src.m_bottom = 649.0f;

	dst.m_top = 250.0f;
	dst.m_left = 250.0f;
	dst.m_right = 950.0f;
	dst.m_bottom = 650.0f;
	Draw::Draw(1, &src, &dst, c, 0.0f);

	//�f�o�b�O�p���}�E�X�ʒu�\��
	wchar_t test_mou[256];
	swprintf_s(test_mou, L"x=%f,y=%f", m_mou_x, m_mou_y);
	Font::StrDraw(test_mou, 20.0f, 20.0f, 12.0f, c);
}
