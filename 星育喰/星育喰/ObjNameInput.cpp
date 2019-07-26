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

wchar_t g_Player_Name[6];

//�C�j�V�����C�Y
void CObjNameInput::Init()
{
	m_mou_x = 0.0f;	//�}�E�XX���W
	m_mou_y = 0.0f; //�}�E�XY���W
	m_mou_r = false;//�E�N���b�N
	m_mou_l = false;//���N���b�N
	m_f = true;
	m_cut = 0;
	m_finalcheck_f = false;
	m_key_f = false;
	m_Yes_Button_color=0;
	m_No_Button_color =0;
	m_num_cnt = 0;
	m_c_cut = 0;
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
		m_c[i] = '?';
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
	for (int i = 0; i < 10; i++)
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
		case 9:
			word_y[i] = 630;
			break;
		default:
			break;

		}

	}
	click_cut=0;

	m_tex_clar = true;
	for (int i = 0; i < 6; i++)
	{
		m_tex_discri[i] = 99;
		
	}
	for (int i = 0; i < 50; i++)
	{
		word_w[i]=i;
	}

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

	if (m_key_f == false)
	{
		//���O���͂̏���
		//���ڂ�Y��---------------------------------------------------------
		if (word_y[0] < m_mou_y&& m_mou_y < word_y[1] && click_cut != 5)
		{
			//��
			if (m_mou_l == true && word_x[0] < m_mou_x&&m_mou_x < word_x[1])
			{
				//�N���b�N�����������񂾂��ɂ���if��
				if (m_f == false)
				{
					//m_tex_discri�z���word_w�̒l��������
					//m_tex_discri��click_cut�̒l�������邱�Ƃɂ���ĕ`�悷��ۂɉ��ɂ��炷���Ƃ��ł���
					m_tex_discri[click_cut] = word_w[0];	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
					click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
					m_c[m_cut] = L'��';
					m_cut++;
					m_f = true;
				}
			}
			//��
			else if (m_mou_l == true && word_x[1] < m_mou_x&&m_mou_x < word_x[2])
			{
				//�N���b�N�����������񂾂��ɂ���if��
				if (m_f == false)
				{
					//m_tex_discri�z���word_w�̒l��������
					//m_tex_discri��click_cut�̒l�������邱�Ƃɂ���ĕ`�悷��ۂɉ��ɂ��炷���Ƃ��ł���
					m_tex_discri[click_cut] = word_w[1];	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
					click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
					m_c[m_cut] = L'��';
					m_cut++;
					m_f = true;
				}
			}
			//��
			else if (m_mou_l == true && word_x[2] < m_mou_x&&m_mou_x < word_x[3])
			{
				//�N���b�N�����������񂾂��ɂ���if��
				if (m_f == false)
				{
					//m_tex_discri�z���word_w�̒l��������
					//m_tex_discri��click_cut�̒l�������邱�Ƃɂ���ĕ`�悷��ۂɉ��ɂ��炷���Ƃ��ł���
					m_tex_discri[click_cut] = word_w[2];	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
					click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
					m_c[m_cut] = L'��';
					m_f = true;
					m_cut++;
				}
			}
			//��
			else if (m_mou_l == true && word_x[3] < m_mou_x&&m_mou_x < word_x[4])
			{
				//�N���b�N�����������񂾂��ɂ���if��
				if (m_f == false)
				{
					//m_tex_discri�z���word_w�̒l��������
					//m_tex_discri��click_cut�̒l�������邱�Ƃɂ���ĕ`�悷��ۂɉ��ɂ��炷���Ƃ��ł���
					m_tex_discri[click_cut] = word_w[3];	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
					click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
					m_c[m_cut] = L'��';
					m_f = true;
					m_cut++;
				}
			}
			//��
			else if (m_mou_l == true && word_x[4] < m_mou_x&&m_mou_x < word_x[5])
			{
				//�N���b�N�����������񂾂��ɂ���if��
				if (m_f == false)
				{
					//m_tex_discri�z���word_w�̒l��������
					//m_tex_discri��click_cut�̒l�������邱�Ƃɂ���ĕ`�悷��ۂɉ��ɂ��炷���Ƃ��ł���
					m_tex_discri[click_cut] = word_w[4];	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
					click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
					m_c[m_cut] = L'��';
					m_f = true;
					m_cut++;
				}
			}
			//��
			else if (m_mou_l == true && word_x[6] < m_mou_x&&m_mou_x < word_x[7])
			{
				//�N���b�N�����������񂾂��ɂ���if��
				if (m_f == false)
				{
					//m_tex_discri�z���word_w�̒l��������
					//m_tex_discri��click_cut�̒l�������邱�Ƃɂ���ĕ`�悷��ۂɉ��ɂ��炷���Ƃ��ł���
					m_tex_discri[click_cut] = word_w[5];	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
					click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
					m_c[m_cut] = L'��';
					m_f = true;
					m_cut++;
				}
			}
			//��
			else if (m_mou_l == true && word_x[7] < m_mou_x&&m_mou_x < word_x[8])
			{
				//�N���b�N�����������񂾂��ɂ���if��
				if (m_f == false)
				{
					//m_tex_discri�z���word_w�̒l��������
					//m_tex_discri��click_cut�̒l�������邱�Ƃɂ���ĕ`�悷��ۂɉ��ɂ��炷���Ƃ��ł���
					m_tex_discri[click_cut] = word_w[6];	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
					click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
					m_c[m_cut] = L'��';
					m_f = true;
					m_cut++;
				}
			}
			//��
			else if (m_mou_l == true && word_x[8] < m_mou_x&&m_mou_x < word_x[9])
			{
				//�N���b�N�����������񂾂��ɂ���if��
				if (m_f == false)
				{
					//m_tex_discri�z���word_w�̒l��������
					//m_tex_discri��click_cut�̒l�������邱�Ƃɂ���ĕ`�悷��ۂɉ��ɂ��炷���Ƃ��ł���
					m_tex_discri[click_cut] = word_w[7];	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
					click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
					m_c[m_cut] = L'��';
					m_f = true;
					m_cut++;
				}
			}
			//��
			else if (m_mou_l == true && word_x[9] < m_mou_x&&m_mou_x < word_x[10])
			{
				//�N���b�N�����������񂾂��ɂ���if��
				if (m_f == false)
				{
					//m_tex_discri�z���word_w�̒l��������
					//m_tex_discri��click_cut�̒l�������邱�Ƃɂ���ĕ`�悷��ۂɉ��ɂ��炷���Ƃ��ł���
					m_tex_discri[click_cut] = word_w[8];	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
					click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
					m_c[m_cut] = L'��';
					m_f = true;
					m_cut++;
				}
			}
			//��
			else if (m_mou_l == true && word_x[10] < m_mou_x&&m_mou_x < word_x[11])
			{
				//�N���b�N�����������񂾂��ɂ���if��
				if (m_f == false)
				{
					//m_tex_discri�z���word_w�̒l��������
					//m_tex_discri��click_cut�̒l�������邱�Ƃɂ���ĕ`�悷��ۂɉ��ɂ��炷���Ƃ��ł���
					m_tex_discri[click_cut] = word_w[9];	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
					click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
					m_c[m_cut] = L'��';
					m_f = true;
					m_cut++;
				}
			}
			else
			{
				m_f = false;
			}
		}
		//2��ڂ�y���̔���
		else if (word_y[2] < m_mou_y&& m_mou_y < word_y[3] && click_cut != 5)
		{
			//��
			if (m_mou_l == true && word_x[0] < m_mou_x&&m_mou_x < word_x[1])
			{
				//�N���b�N�����������񂾂��ɂ���if��
				if (m_f == false)
				{
					//m_tex_discri�z���word_w�̒l��������
					//m_tex_discri��click_cut�̒l�������邱�Ƃɂ���ĕ`�悷��ۂɉ��ɂ��炷���Ƃ��ł���
					m_tex_discri[click_cut] = word_w[10];	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
					click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
					m_c[m_cut] = L'��';
					m_f = true;
					m_cut++;
				}
			}
			//��
			else if (m_mou_l == true && word_x[1] < m_mou_x&&m_mou_x < word_x[2])
			{
				//�N���b�N�����������񂾂��ɂ���if��
				if (m_f == false)
				{
					//m_tex_discri�z���word_w�̒l��������
					//m_tex_discri��click_cut�̒l�������邱�Ƃɂ���ĕ`�悷��ۂɉ��ɂ��炷���Ƃ��ł���
					m_tex_discri[click_cut] = word_w[11];	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
					click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
					m_c[m_cut] = L'��';
					m_f = true;
					m_cut++;
				}
			}
			//��
			else if (m_mou_l == true && word_x[2] < m_mou_x&&m_mou_x < word_x[3])
			{
				//�N���b�N�����������񂾂��ɂ���if��
				if (m_f == false)
				{
					//m_tex_discri�z���word_w�̒l��������
					//m_tex_discri��click_cut�̒l�������邱�Ƃɂ���ĕ`�悷��ۂɉ��ɂ��炷���Ƃ��ł���
					m_tex_discri[click_cut] = word_w[12];	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
					click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
					m_c[m_cut] = L'��';
					m_f = true;
					m_cut++;
				}
			}
			//��
			else if (m_mou_l == true && word_x[3] < m_mou_x&&m_mou_x < word_x[4])
			{
				//�N���b�N�����������񂾂��ɂ���if��
				if (m_f == false)
				{
					//m_tex_discri�z���word_w�̒l��������
					//m_tex_discri��click_cut�̒l�������邱�Ƃɂ���ĕ`�悷��ۂɉ��ɂ��炷���Ƃ��ł���
					m_tex_discri[click_cut] = word_w[13];	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
					click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
					m_c[m_cut] = L'��';
					m_f = true;
					m_cut++;
				}
			}
			//��
			else if (m_mou_l == true && word_x[4] < m_mou_x&&m_mou_x < word_x[5])
			{
				//�N���b�N�����������񂾂��ɂ���if��
				if (m_f == false)
				{
					//m_tex_discri�z���word_w�̒l��������
					//m_tex_discri��click_cut�̒l�������邱�Ƃɂ���ĕ`�悷��ۂɉ��ɂ��炷���Ƃ��ł���
					m_tex_discri[click_cut] = word_w[14];	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
					click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
					m_c[m_cut] = L'��';
					m_f = true;
					m_cut++;
				}
			}
			//��
			else if (m_mou_l == true && word_x[6] < m_mou_x&&m_mou_x < word_x[7])
			{
				//�N���b�N�����������񂾂��ɂ���if��
				if (m_f == false)
				{
					//m_tex_discri�z���word_w�̒l��������
					//m_tex_discri��click_cut�̒l�������邱�Ƃɂ���ĕ`�悷��ۂɉ��ɂ��炷���Ƃ��ł���
					m_tex_discri[click_cut] = word_w[15];	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
					click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
					m_c[m_cut] = L'��';
					m_f = true;
					m_cut++;
				}
			}
			//��
			else if (m_mou_l == true && word_x[7] < m_mou_x&&m_mou_x < word_x[8])
			{
				//�N���b�N�����������񂾂��ɂ���if��
				if (m_f == false)
				{
					//m_tex_discri�z���word_w�̒l��������
					//m_tex_discri��click_cut�̒l�������邱�Ƃɂ���ĕ`�悷��ۂɉ��ɂ��炷���Ƃ��ł���
					m_tex_discri[click_cut] = word_w[16];	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
					click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
					m_c[m_cut] = L'��';
					m_f = true;
					m_cut++;
				}
			}
			//��
			else if (m_mou_l == true && word_x[8] < m_mou_x&&m_mou_x < word_x[9])
			{
				//�N���b�N�����������񂾂��ɂ���if��
				if (m_f == false)
				{
					//m_tex_discri�z���word_w�̒l��������
					//m_tex_discri��click_cut�̒l�������邱�Ƃɂ���ĕ`�悷��ۂɉ��ɂ��炷���Ƃ��ł���
					m_tex_discri[click_cut] = word_w[17];	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
					click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
					m_c[m_cut] = L'��';
					m_f = true;
					m_cut++;
				}
			}
			//��
			else if (m_mou_l == true && word_x[9] < m_mou_x&&m_mou_x < word_x[10])
			{
				//�N���b�N�����������񂾂��ɂ���if��
				if (m_f == false)
				{
					//m_tex_discri�z���word_w�̒l��������
					//m_tex_discri��click_cut�̒l�������邱�Ƃɂ���ĕ`�悷��ۂɉ��ɂ��炷���Ƃ��ł���
					m_tex_discri[click_cut] = word_w[18];	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
					click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
					m_c[m_cut] = L'��';
					m_f = true;
					m_cut++;
				}
			}
			//��
			else if (m_mou_l == true && word_x[10] < m_mou_x&&m_mou_x < word_x[11])
			{
				//�N���b�N�����������񂾂��ɂ���if��
				if (m_f == false)
				{
					//m_tex_discri�z���word_w�̒l��������
					//m_tex_discri��click_cut�̒l�������邱�Ƃɂ���ĕ`�悷��ۂɉ��ɂ��炷���Ƃ��ł���
					m_tex_discri[click_cut] = word_w[19];	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
					click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
					m_c[m_cut] = L'��';
					m_f = true;
					m_cut++;
				}
			}
			else
			{
				m_f = false;
			}
		}
		//3��ڂ�y���̔���
		else if (word_y[4] < m_mou_y&& m_mou_y < word_y[5] && click_cut != 5)
		{
			//��
			if (m_mou_l == true && word_x[0] < m_mou_x&&m_mou_x < word_x[1])
			{
				//�N���b�N�����������񂾂��ɂ���if��
				if (m_f == false)
				{
					//m_tex_discri�z���word_w�̒l��������
					//m_tex_discri��click_cut�̒l�������邱�Ƃɂ���ĕ`�悷��ۂɉ��ɂ��炷���Ƃ��ł���
					m_tex_discri[click_cut] = word_w[20];	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
					click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
					m_c[m_cut] = L'��';
					m_f = true;
					m_cut++;
				}
			}
			//��
			else if (m_mou_l == true && word_x[1] < m_mou_x&&m_mou_x < word_x[2])
			{
				//�N���b�N�����������񂾂��ɂ���if��
				if (m_f == false)
				{
					//m_tex_discri�z���word_w�̒l��������
					//m_tex_discri��click_cut�̒l�������邱�Ƃɂ���ĕ`�悷��ۂɉ��ɂ��炷���Ƃ��ł���
					m_tex_discri[click_cut] = word_w[21];	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
					click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
					m_c[m_cut] = L'��';
					m_f = true;
					m_cut++;
				}
			}
			//��
			else if (m_mou_l == true && word_x[2] < m_mou_x&&m_mou_x < word_x[3])
			{
				//�N���b�N�����������񂾂��ɂ���if��
				if (m_f == false)
				{
					//m_tex_discri�z���word_w�̒l��������
					//m_tex_discri��click_cut�̒l�������邱�Ƃɂ���ĕ`�悷��ۂɉ��ɂ��炷���Ƃ��ł���
					m_tex_discri[click_cut] = word_w[22];	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
					click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
					m_c[m_cut] = L'��';
					m_f = true;
					m_cut++;
				}
			}
			//��
			else if (m_mou_l == true && word_x[3] < m_mou_x&&m_mou_x < word_x[4])
			{
				//�N���b�N�����������񂾂��ɂ���if��
				if (m_f == false)
				{
					//m_tex_discri�z���word_w�̒l��������
					//m_tex_discri��click_cut�̒l�������邱�Ƃɂ���ĕ`�悷��ۂɉ��ɂ��炷���Ƃ��ł���
					m_tex_discri[click_cut] = word_w[23];	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
					click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
					m_c[m_cut] = L'��';
					m_f = true;
					m_cut++;
				}
			}
			//��
			else if (m_mou_l == true && word_x[4] < m_mou_x&&m_mou_x < word_x[5])
			{
				//�N���b�N�����������񂾂��ɂ���if��
				if (m_f == false)
				{
					//m_tex_discri�z���word_w�̒l��������
					//m_tex_discri��click_cut�̒l�������邱�Ƃɂ���ĕ`�悷��ۂɉ��ɂ��炷���Ƃ��ł���
					m_tex_discri[click_cut] = word_w[24];	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
					click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
					m_c[m_cut] = L'��';
					m_f = true;
					m_cut++;
				}
			}
			//��
			else if (m_mou_l == true && word_x[6] < m_mou_x&&m_mou_x < word_x[7])
			{
				//�N���b�N�����������񂾂��ɂ���if��
				if (m_f == false)
				{
					//m_tex_discri�z���word_w�̒l��������
					//m_tex_discri��click_cut�̒l�������邱�Ƃɂ���ĕ`�悷��ۂɉ��ɂ��炷���Ƃ��ł���
					m_tex_discri[click_cut] = word_w[25];	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
					click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
					m_c[m_cut] = L'��';
					m_f = true;
					m_cut++;
				}
			}
			//��
			else if (m_mou_l == true && word_x[8] < m_mou_x&&m_mou_x < word_x[9])
			{
				//�N���b�N�����������񂾂��ɂ���if��
				if (m_f == false)
				{
					//m_tex_discri�z���word_w�̒l��������
					//m_tex_discri��click_cut�̒l�������邱�Ƃɂ���ĕ`�悷��ۂɉ��ɂ��炷���Ƃ��ł���
					m_tex_discri[click_cut] = word_w[26];	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
					click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
					m_c[m_cut] = L'��';
					m_f = true;
					m_cut++;
				}
			}
			//��
			else if (m_mou_l == true && word_x[10] < m_mou_x&&m_mou_x < word_x[11])
			{
				//�N���b�N�����������񂾂��ɂ���if��
				if (m_f == false)
				{
					//m_tex_discri�z���word_w�̒l��������
					//m_tex_discri��click_cut�̒l�������邱�Ƃɂ���ĕ`�悷��ۂɉ��ɂ��炷���Ƃ��ł���
					m_tex_discri[click_cut] = word_w[27];	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
					click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
					m_c[m_cut] = L'��';
					m_f = true;
					m_cut++;
				}
			}
			else
			{
				m_f = false;
			}
		}
		//4��ڂ�y���̔���
		else if (word_y[6] < m_mou_y&& m_mou_y < word_y[7] && click_cut != 5)
		{
			//��
			if (m_mou_l == true && word_x[0] < m_mou_x&&m_mou_x < word_x[1])
			{
				//�N���b�N�����������񂾂��ɂ���if��
				if (m_f == false)
				{
					//m_tex_discri�z���word_w�̒l��������
					//m_tex_discri��click_cut�̒l�������邱�Ƃɂ���ĕ`�悷��ۂɉ��ɂ��炷���Ƃ��ł���
					m_tex_discri[click_cut] = word_w[28];	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
					click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
					m_c[m_cut] = L'��';
					m_f = true;
					m_cut++;
				}
			}
			//��
			else if (m_mou_l == true && word_x[1] < m_mou_x&&m_mou_x < word_x[2])
			{
				//�N���b�N�����������񂾂��ɂ���if��
				if (m_f == false)
				{
					//m_tex_discri�z���word_w�̒l��������
					//m_tex_discri��click_cut�̒l�������邱�Ƃɂ���ĕ`�悷��ۂɉ��ɂ��炷���Ƃ��ł���
					m_tex_discri[click_cut] = word_w[29];	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
					click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
					m_c[m_cut] = L'��';
					m_f = true;
					m_cut++;
				}
			}
			//��
			else if (m_mou_l == true && word_x[2] < m_mou_x&&m_mou_x < word_x[3])
			{
				//�N���b�N�����������񂾂��ɂ���if��
				if (m_f == false)
				{
					//m_tex_discri�z���word_w�̒l��������
					//m_tex_discri��click_cut�̒l�������邱�Ƃɂ���ĕ`�悷��ۂɉ��ɂ��炷���Ƃ��ł���
					m_tex_discri[click_cut] = word_w[30];	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
					click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
					m_c[m_cut] = L'��';
					m_f = true;
					m_cut++;
				}
			}
			//��
			else if (m_mou_l == true && word_x[3] < m_mou_x&&m_mou_x < word_x[4])
			{
				//�N���b�N�����������񂾂��ɂ���if��
				if (m_f == false)
				{
					//m_tex_discri�z���word_w�̒l��������
					//m_tex_discri��click_cut�̒l�������邱�Ƃɂ���ĕ`�悷��ۂɉ��ɂ��炷���Ƃ��ł���
					m_tex_discri[click_cut] = word_w[31];	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
					click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
					m_c[m_cut] = L'��';
					m_f = true;
					m_cut++;
				}
			}
			//��
			else if (m_mou_l == true && word_x[4] < m_mou_x&&m_mou_x < word_x[5])
			{
				//�N���b�N�����������񂾂��ɂ���if��
				if (m_f == false)
				{
					//m_tex_discri�z���word_w�̒l��������
					//m_tex_discri��click_cut�̒l�������邱�Ƃɂ���ĕ`�悷��ۂɉ��ɂ��炷���Ƃ��ł���
					m_tex_discri[click_cut] = word_w[32];	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
					click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
					m_c[m_cut] = L'��';
					m_f = true;
					m_cut++;
				}
			}
			//��
			else if (m_mou_l == true && word_x[6] < m_mou_x&&m_mou_x < word_x[7])
			{
				//�N���b�N�����������񂾂��ɂ���if��
				if (m_f == false)
				{
					//m_tex_discri�z���word_w�̒l��������
					//m_tex_discri��click_cut�̒l�������邱�Ƃɂ���ĕ`�悷��ۂɉ��ɂ��炷���Ƃ��ł���
					m_tex_discri[click_cut] = word_w[33];	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
					click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
					m_c[m_cut] = L'��';
					m_f = true;
					m_cut++;
				}
			}
			//��
			else if (m_mou_l == true && word_x[7] < m_mou_x&&m_mou_x < word_x[8])
			{
				//�N���b�N�����������񂾂��ɂ���if��
				if (m_f == false)
				{
					//m_tex_discri�z���word_w�̒l��������
					//m_tex_discri��click_cut�̒l�������邱�Ƃɂ���ĕ`�悷��ۂɉ��ɂ��炷���Ƃ��ł���
					m_tex_discri[click_cut] = word_w[34];	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
					click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
					m_c[m_cut] = L'��';
					m_f = true;
					m_cut++;
				}
			}
			//��
			else if (m_mou_l == true && word_x[8] < m_mou_x&&m_mou_x < word_x[9])
			{
				//�N���b�N�����������񂾂��ɂ���if��
				if (m_f == false)
				{
					//m_tex_discri�z���word_w�̒l��������
					//m_tex_discri��click_cut�̒l�������邱�Ƃɂ���ĕ`�悷��ۂɉ��ɂ��炷���Ƃ��ł���
					m_tex_discri[click_cut] = word_w[35];	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
					click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
					m_c[m_cut] = L'��';
					m_f = true;
					m_cut++;
				}
			}
			//��
			else if (m_mou_l == true && word_x[9] < m_mou_x&&m_mou_x < word_x[10])
			{
				//�N���b�N�����������񂾂��ɂ���if��
				if (m_f == false)
				{
					//m_tex_discri�z���word_w�̒l��������
					//m_tex_discri��click_cut�̒l�������邱�Ƃɂ���ĕ`�悷��ۂɉ��ɂ��炷���Ƃ��ł���
					m_tex_discri[click_cut] = word_w[36];	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
					click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
					m_c[m_cut] = L'��';
					m_f = true;
					m_cut++;
				}
			}
			//��
			else if (m_mou_l == true && word_x[10] < m_mou_x&&m_mou_x < word_x[11])
			{
				//�N���b�N�����������񂾂��ɂ���if��
				if (m_f == false)
				{
					//m_tex_discri�z���word_w�̒l��������
					//m_tex_discri��click_cut�̒l�������邱�Ƃɂ���ĕ`�悷��ۂɉ��ɂ��炷���Ƃ��ł���
					m_tex_discri[click_cut] = word_w[37];	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
					click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
					m_c[m_cut] = L'��';
					m_f = true;
					m_cut++;
				}
			}
			else
			{
				m_f = false;
			}
		}
		//5��ڂ�y���̔���
		else if (word_y[8] < m_mou_y&& m_mou_y < word_y[9] && click_cut != 5)
		{
			//��
			if (m_mou_l == true && word_x[0] < m_mou_x&&m_mou_x < word_x[1])
			{
				//�N���b�N�����������񂾂��ɂ���if��
				if (m_f == false)
				{
					//m_tex_discri�z���word_w�̒l��������
					//m_tex_discri��click_cut�̒l�������邱�Ƃɂ���ĕ`�悷��ۂɉ��ɂ��炷���Ƃ��ł���
					m_tex_discri[click_cut] = word_w[38];	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
					click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
					m_c[m_cut] = L'��';
					m_f = true;
					m_cut++;
				}
			}
			//��
			else if (m_mou_l == true && word_x[1] < m_mou_x&&m_mou_x < word_x[2])
			{
				//�N���b�N�����������񂾂��ɂ���if��
				if (m_f == false)
				{
					//m_tex_discri�z���word_w�̒l��������
					//m_tex_discri��click_cut�̒l�������邱�Ƃɂ���ĕ`�悷��ۂɉ��ɂ��炷���Ƃ��ł���
					m_tex_discri[click_cut] = word_w[39];	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
					click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
					m_c[m_cut] = L'��';
					m_f = true;
					m_cut++;
				}
			}
			//��
			else if (m_mou_l == true && word_x[2] < m_mou_x&&m_mou_x < word_x[3])
			{
				//�N���b�N�����������񂾂��ɂ���if��
				if (m_f == false)
				{
					//m_tex_discri�z���word_w�̒l��������
					//m_tex_discri��click_cut�̒l�������邱�Ƃɂ���ĕ`�悷��ۂɉ��ɂ��炷���Ƃ��ł���
					m_tex_discri[click_cut] = word_w[40];	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
					click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
					m_c[m_cut] = L'��';
					m_f = true;
					m_cut++;
				}
			}
			//��
			else if (m_mou_l == true && word_x[3] < m_mou_x&&m_mou_x < word_x[4])
			{
				//�N���b�N�����������񂾂��ɂ���if��
				if (m_f == false)
				{
					//m_tex_discri�z���word_w�̒l��������
					//m_tex_discri��click_cut�̒l�������邱�Ƃɂ���ĕ`�悷��ۂɉ��ɂ��炷���Ƃ��ł���
					m_tex_discri[click_cut] = word_w[41];	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
					click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
					m_c[m_cut] = L'��';
					m_f = true;
					m_cut++;
				}
			}
			//��
			else if (m_mou_l == true && word_x[4] < m_mou_x&&m_mou_x < word_x[5])
			{
				//�N���b�N�����������񂾂��ɂ���if��
				if (m_f == false)
				{
					//m_tex_discri�z���word_w�̒l��������
					//m_tex_discri��click_cut�̒l�������邱�Ƃɂ���ĕ`�悷��ۂɉ��ɂ��炷���Ƃ��ł���
					m_tex_discri[click_cut] = word_w[42];	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
					click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
					m_c[m_cut] = L'��';
					m_f = true;
					m_cut++;
				}
			}
			//��
			else if (m_mou_l == true && word_x[6] < m_mou_x&&m_mou_x < word_x[7])
			{
				//�N���b�N�����������񂾂��ɂ���if��
				if (m_f == false)
				{
					//m_tex_discri�z���word_w�̒l��������
					//m_tex_discri��click_cut�̒l�������邱�Ƃɂ���ĕ`�悷��ۂɉ��ɂ��炷���Ƃ��ł���
					m_tex_discri[click_cut] = word_w[43];	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
					click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
					m_c[m_cut] = L'��';
					m_f = true;
					m_cut++;
				}
			}
			//��
			else if (m_mou_l == true && word_x[8] < m_mou_x&&m_mou_x < word_x[9])
			{
				//�N���b�N�����������񂾂��ɂ���if��
				if (m_f == false)
				{
					//m_tex_discri�z���word_w�̒l��������
					//m_tex_discri��click_cut�̒l�������邱�Ƃɂ���ĕ`�悷��ۂɉ��ɂ��炷���Ƃ��ł���
					m_tex_discri[click_cut] = word_w[44];	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
					click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
					m_c[m_cut] = L'��';
					m_f = true;
					m_cut++;
				}
			}
			//��
			else if (m_mou_l == true && word_x[10] < m_mou_x&&m_mou_x < word_x[11])
			{
				//�N���b�N�����������񂾂��ɂ���if��
				if (m_f == false)
				{
					//m_tex_discri�z���word_w�̒l��������
					//m_tex_discri��click_cut�̒l�������邱�Ƃɂ���ĕ`�悷��ۂɉ��ɂ��炷���Ƃ��ł���
					m_tex_discri[click_cut] = word_w[45];	//click_cut��m_tex_discri�ɓ���ĕ\��������ʒu�����߂�
					click_cut++;					//�N���b�N���ꂽ��`���Ă��Ƃ��J�E���g
					//m_c[m_cut] = L'��';

					char *tmp = "��";
					memcpy(&m_c[m_cut], tmp, 2);

					m_f = true;
					m_cut++;
				}
			}
			else
			{
				m_f = false;
			}
		}
	}
	else
	{ }
	//�����N���A�̔���
	if (m_mou_l == true && m_mou_x > 1000 && m_mou_x < 1150 && 300 < m_mou_y && 400 > m_mou_y)
	{
		m_tex_clar = false;
	}
	//����������������Ƃ��̏���
	if (m_mou_l==true && m_mou_x > 1000 && m_mou_x < 1150 && 500 < m_mou_y && 600 > m_mou_y)
	{
		m_finalcheck_f = true;
		m_key_f = true;
	}
	//�ŏI�m�F�E�B���h�E�̂͂����������Ƃ��̏���
	if (m_mou_l == true && m_mou_x > 410 && m_mou_x < 510 && 410 < m_mou_y && 460 > m_mou_y && m_finalcheck_f == true)
	{
		//���̉��ɂ��镶���O���[�o���ϐ��ɕ��������鏈��
		switch (m_cut)
		{
		case 3:
			swprintf_s(g_Player_Name, L"%c%c%c", m_c[0], m_c[1], m_c[2]);
			break;
		case 4:
			swprintf_s(g_Player_Name, L"%c%c%c%c", m_c[0], m_c[1], m_c[2], m_c[3]);
			break;
		case 5:
			swprintf_s(g_Player_Name, L"%c%c%c%c%c", m_c[0], m_c[1], m_c[2], m_c[3], m_c[4]);
			break;
		}
		Scene::SetScene(new CSceneTraining());//�琬��ʂփV�[���ڍs 
	}
	//�ŏI�m�F�E�B���h�E�̂��������������Ƃ��̏���
	if (m_mou_l == true && m_mou_x > 650 && m_mou_x < 800 && 410 < m_mou_y && 460 > m_mou_y&&m_finalcheck_f == true)
	{
		m_key_f = false;
		m_finalcheck_f = false;
	}
	else;


}
//�h���[
void CObjNameInput::Draw()
{
	//�����̐F(��)
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	//���`��J���[���  R=RED  G=Green  B=Blue A=alpha(���ߏ��)
	//�ԐF
	float red[4] = { 1.0f,0.0f,0.0f,1.0f };

	//���F
	float black[4] = { 0.0f,0.0f,0.0f,1.0f };

	//�ŏI�m�F[�͂�]�{�^���p
	float Yes[4] = { m_Yes_Button_color,0.0f,0.0f,1.0f };

	//�ŏI�m�F[������]�{�^���p
	float No[4] = { 0.0f,0.0f,m_No_Button_color,1.0f };

	RECT_F src;//�؂���ʒu
	RECT_F dst;//�\���ʒu

	if(m_tex_clar==true)
	{ 
		//���N���b�N���ꂽ���̕`��----------------------------------
		wchar_t str[46][2]
		{
			L"��",L"��",L"��",L"��",L"��",L"��",L"��",L"��",L"��",L"��",
			L"��",L"��",L"��",L"��",L"��",L"��",L"��",L"��",L"��",L"��",
			L"��",L"��",L"��",L"��",L"��",L"��",L"��",L"��",
			L"��",L"��",L"��",L"��",L"��",L"��",L"��",L"��",L"��",L"��",
			L"��",L"��",L"��",L"��",L"��",L"��",L"��",L"��",
		};
		for (int i = 0; i < 5; i++)
		{
			if (m_tex_discri[i] != 99)
			{
				FontDraw(str[m_tex_discri[i]], 590+(i * 60), 100.0, 60.0f, 60.0f, c, true);
			}
			else if (m_tex_discri[i] == 99)
			{
				FontDraw(L"�D", 590 + (i * 60), 100.0, 60.0f, 60.0f, c, true);
			}
		}

		m_num_cnt = 0;
	}
	else if(m_tex_clar == false)
	{
		for (int i = 0;i < 5;i++)
		{
			m_tex_discri[i]=99;
		}
		click_cut=0;
		m_tex_clar = true;
		m_cut = 0;
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

	//�N���A�摜�̓K�p
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 405.0f;
	src.m_bottom = 150.0f;

	dst.m_top		= 300.0f;
	dst.m_left		= 1000.0f;
	dst.m_right		= 1150.0f;
	dst.m_bottom	= 400.0f;
	Draw::Draw(2, &src, &dst, c, 0.0f);

	//����
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 280.0f;
	src.m_bottom = 150.0f;

	dst.m_top = 500.0f;
	dst.m_left = 1000.0f;
	dst.m_right = 1150.0f;
	dst.m_bottom = 600.0f;
	Draw::Draw(3, &src, &dst, c, 0.0f);

	//�f��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 242.0f;
	src.m_bottom = 117.0f;

	dst.m_top =102.0f;
	dst.m_left = 350.0f;
	dst.m_right = 450.0f;
	dst.m_bottom = 160.0f;
	Draw::Draw(4, &src, &dst, c, 0.0f);

	FontDraw(L"��", 450, 100.0, 60.0f, 60.0f, c, true);


	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 32.0f;
	src.m_bottom = 32.0f;

	//���c
	dst.m_top = 80.0f;
	dst.m_left = 330.0f;
	dst.m_right = 335.0f;
	dst.m_bottom = 190.0f;
	Draw::Draw(5, &src, &dst, c, 0.0f);

	//�E�c
	dst.m_top = 80.0f;
	dst.m_left = 910.0f;
	dst.m_right = 915.0f;
	dst.m_bottom = 190.0f;
	Draw::Draw(5, &src, &dst, c, 0.0f);

	//�㉡
	dst.m_top = 80.0f;
	dst.m_left = 330.0f;
	dst.m_right = 910.0f;
	dst.m_bottom = 85.0f;
	Draw::Draw(5, &src, &dst, c, 0.0f);

	//����
	dst.m_top = 185.0f;
	dst.m_left = 330.0f;
	dst.m_right = 910.0f;
	dst.m_bottom = 190.0f;
	Draw::Draw(5, &src, &dst, c, 0.0f);

	if (m_finalcheck_f == true && m_cut>=3)
	{
		//���N���b�N���ꂽ���̕`��----------------------------------
		wchar_t str[46][2]
		{
			L"��",L"��",L"��",L"��",L"��",L"��",L"��",L"��",L"��",L"��",
			L"��",L"��",L"��",L"��",L"��",L"��",L"��",L"��",L"��",L"��",
			L"��",L"��",L"��",L"��",L"��",L"��",L"��",L"��",
			L"��",L"��",L"��",L"��",L"��",L"��",L"��",L"��",L"��",L"��",
			L"��",L"��",L"��",L"��",L"��",L"��",L"��",L"��",
		};

		//�͂��Ƃ������̃{�^���̏�ɃJ�[�\�������킷�ƐF���ς��
		if (m_mou_x > 650 && m_mou_x < 800&&m_mou_y>410&&m_mou_y<460)
		{
			//�������{�^���̏���
			m_No_Button_color = 1;
		}
		else if (m_mou_x > 410 && m_mou_x < 510 && m_mou_y>410 && m_mou_y < 460)
		{
			//�͂��{�^���̏���
			m_Yes_Button_color = 1;
		}
		else
		{
			//����ȊO�̏�����������������
			m_No_Button_color = 0;
			m_Yes_Button_color = 0;
		}

		
		//���ŏI�m�F�E�C���h�E�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1200.0f;
		src.m_bottom = 700.0f;

		dst.m_top = 200.0f;
		dst.m_left = 320.0f;
		dst.m_right = 880.0f;
		dst.m_bottom = 480.0f;
		Draw::Draw(89, &src, &dst, c, 0.0f);

		//���͂������摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 232.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 410.0f;
		dst.m_left = 410.0f;
		dst.m_right = 510.0f;
		dst.m_bottom = 460.0f;
		Draw::Draw(66, &src, &dst, Yes, 0.0f);

		//�������������摜�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 352.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 410.0f;
		dst.m_left = 650.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 460.0f;
		Draw::Draw(67, &src, &dst, No, 0.0f);

		//�v���C���[����`�悷��ۂ̈ʒu���������邽�߂̃J�E���g
		for (int i = 0; i < 6; i++)
		{
			if (m_tex_discri[i] != 99 && m_num_cnt < 5)
				m_num_cnt++;
		}

		//�ŏI�m�F�E�B���h�E���\�����ꂽ���ɓ��͂��ꂽ�v���C���[����`�悷��
		for (int i = 0; i < 5; i++)
		{
			//m_tex_discri[i]�̒��̒l��99�o�Ȃ���Ε`��i99�̗��R�͏���������ۂ�99�������Ă��邩��j
			if (m_tex_discri[i] != 99)
			{
				FontDraw(str[m_tex_discri[i]], 600 - (m_num_cnt * 30) + (i * 60), 225.0, 60.0f, 60.0f, c, false);
			}
			if (m_c[i] == '�H')
			{
				m_c_cut++;
			}
		}
		FontDraw(L"�ł�낵���ł����H", 375, 325.0, 50.0f, 50.0f, c, false);
	}
	//����{�^������������m_cut���O�ȉ��Ȃ�x�������o������
	else if (m_finalcheck_f == true && m_cut < 3)
	{
		//���N���b�N���ꂽ���̕`��----------------------------------
		wchar_t str[46][2]
		{
			L"��",L"��",L"��",L"��",L"��",L"��",L"��",L"��",L"��",L"��",
			L"��",L"��",L"��",L"��",L"��",L"��",L"��",L"��",L"��",L"��",
			L"��",L"��",L"��",L"��",L"��",L"��",L"��",L"��",
			L"��",L"��",L"��",L"��",L"��",L"��",L"��",L"��",L"��",L"��",
			L"��",L"��",L"��",L"��",L"��",L"��",L"��",L"��",
		};

		//���ŏI�m�F�E�C���h�E�\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1200.0f;
		src.m_bottom = 700.0f;

		dst.m_top = 200.0f;
		dst.m_left = 320.0f;
		dst.m_right = 880.0f;
		dst.m_bottom = 480.0f;
		Draw::Draw(89, &src, &dst, c, 0.0f);

		FontDraw(L"���O���O�����ȏ���͂��Ă�������", 375, 325.0, 30.0f, 30.0f, c, false);
		if (m_mou_l == false)
		{
			m_f = true;
		}
		if (m_mou_l == true&&m_f==true)
		{
			m_finalcheck_f = false;
			m_f = false;
			m_key_f = false;
		}

	}
	//�f�o�b�O�p���}�E�X�ʒu�\��
	wchar_t test_mou[256];
	swprintf_s(test_mou, L"x=%f,y=%f", m_mou_x, m_mou_y);
	Font::StrDraw(test_mou, 20.0f, 20.0f, 12.0f, c);
}
