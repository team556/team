//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�}�N��
#define HELP_X_POS (1120.0f) //�w���v�{�^����X�ʒu
#define HELP_Y_POS (30.0f)	 //�w���v�{�^����Y�ʒu
#define HELP_SIZE (50.0f)	 //�w���v�{�^���̃T�C�Y(width & height)
#define INI_COLOR (0.9f) //�S�J���[���x�̏����l(�A�C�R�����I�𒆂̃J���[)
#define INI_PAGE (1)	 //�y�[�W�̏����l(0�y�[�W�ڂ��Ɗ��o�I�ɕ�����ɂ����̂�1�Ƃ����B)

//�C�j�V�����C�Y
void CObjHelp::Init()
{
	m_mou_x = 0.0f;
	m_mou_y = 0.0f;
	m_mou_r = false;
	m_mou_l = false;
	m_key_f = false;

	m_Help_Button_color = INI_COLOR;
	m_Back_Button_color = INI_COLOR;

	m_help_f = false;
	m_page_num = INI_PAGE;

	//���݂̃V�[���ŉ摜�̓o�^�ԍ��A�w���v�摜(�y�[�W)�̍ő吔�����߂�
	if (m_Scene_num == 1)//�z�[��	1											
	{
		m_page_max = 1;
		m_help_reg_num = 4;
		m_Back_reg_num = 3;
	}
	else if (m_Scene_num == 2)//�琬	2
	{
		m_page_max = 1;
		m_help_reg_num = 47;
		m_Back_reg_num = 1;
	}
	else  //(m_Scene_num == 3)//����	3
	{
		m_page_max = 2;
		m_help_reg_num = 21;
		m_Back_reg_num = 56;
	}
}

//�A�N�V����
void CObjHelp::Action()
{
	//�}�E�X�̈ʒu���擾
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//�}�E�X�̃{�^���̏��
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	//���L�[�t���O
	//�����N���b�NPush��ԁ����N���b�N��Push��ԂɂȂ�܂ŁA
	//�ēx���N���b�N���鎖�͏o���Ȃ������B
	if (m_mou_l == false)	//���N���b�NOFF
	{
		m_key_f = false;	//�L�[�t���OOFF
	}

	//���w���v��\�����̏���
	if (m_help_f == false)						
	{											
		//�w���v�{�^���I��͈�
		if (HELP_X_POS - 10.0f < m_mou_x && m_mou_x < HELP_X_POS - 10.0f + HELP_SIZE && HELP_Y_POS < m_mou_y && m_mou_y < HELP_Y_POS + HELP_SIZE)
		{		
			m_Help_Button_color = 1.0f;

			if (m_mou_l == true && m_key_f == false)//�}�E�X���N���b�N
			{
				m_help_f = true;//�w���v�\������
				m_key_f = true;	//�A�Ő���(�L�[�t���OON)

				//�I����
				Audio::Start(1);
			}
		}
		else
		{
			//�I��͈͊O�̎��͖��I���J���[�ɂ���
			m_Help_Button_color = INI_COLOR;
		}
	}
	//���w���v�\�����̏���
	else										
	{
		//���y�[�W�i�߂�{�^��
		if (1100.0f < m_mou_x && m_mou_x < 1150.0f && 330.0f < m_mou_y && m_mou_y < 380.0f &&
			m_mou_l == true && m_key_f == false)//�}�E�X���N���b�N
		{
			if (m_page_num + 1 > m_page_max)
			{
				m_page_num = INI_PAGE;//���̃y�[�W���Ō�̃y�[�W�ł���΁A�ŏ��̃y�[�W�Ɉړ�������
			}
			else
			{
				m_page_num++;	//�y�[�W��i�߂�
			}

			m_key_f = true;		//�A�Ő���(�L�[�t���OON)
		}

		//���y�[�W�߂��{�^��
		if (50.0f < m_mou_x && m_mou_x < 100.0f && 330.0f < m_mou_y && m_mou_y < 380.0f &&
			m_mou_l == true && m_key_f == false)//�}�E�X���N���b�N
		{
			if (m_page_num - 1 < INI_PAGE)
			{
				m_page_num = m_page_max;//���̃y�[�W���ŏ��̃y�[�W�ł���΁A�Ō�̃y�[�W�Ɉړ�������
			}
			else
			{
				m_page_num--;		//�y�[�W��߂�
			}

			m_key_f = true;		//�A�Ő���(�L�[�t���OON)
		}

		//�߂�{�^��
		if (30 < m_mou_x && m_mou_x < 80 && 30 < m_mou_y && m_mou_y < 80 || m_mou_r == true)
		{
			m_Back_Button_color = 1.0f;

			if (m_mou_l == true || m_mou_r == true)
			{
				m_help_f = false;//�w���v��\���ɂ���

				m_page_num = INI_PAGE;//�y�[�W������������

				//�琬��ʂ�퓬������ʂł͉E�N���b�N���鎖�ɂ��A
				//�����Ɋe�V�[���̖߂�{�^���������ɋN������鋰���Ȃ̂ŃL�[�t���O�p�ӂ���

				//���ƁA�Q�b�^�[�Z�b�^�[�֘A�������������肷��

				//page_max��1�A�܂�w���v�摜���ꖇ�����Ȃ����̓y�[�W�i�߂�{�^���Ɩ߂�{�^���\�����Ȃ��B
				//���ƁA�I�����Ă鎖��������悤�ɃJ���[���x�ύX���s���B

				//�߂�{�^����
				Audio::Start(2);
			}
		}
		else
		{
			//�I��͈͊O�̎��͖��I���J���[�ɂ���
			m_Back_Button_color = INI_COLOR;
		}
	}
}

//�h���[
void CObjHelp::Draw()
{
	//�`��J���[���  R=RED  G=Green  B=Blue A=alpha(���ߏ��)
	float d[4] = { 1.0f,1.0f,1.0f,1.0f };

	float help[4] = { m_Help_Button_color,m_Help_Button_color,m_Help_Button_color,1.0f };

	float back[4] = { m_Back_Button_color,m_Back_Button_color,m_Back_Button_color,1.0f };

	RECT_F src;//�؂���ʒu
	RECT_F dst;//�\���ʒu
	

	//���w���v�{�^���\��
	src.m_top   =  0.0f;
	src.m_left  =  0.0f;
	src.m_right =128.0f;
	src.m_bottom=128.0f;
	
	dst.m_top   = HELP_Y_POS;
	dst.m_left  = HELP_X_POS;
	dst.m_right = HELP_X_POS + HELP_SIZE;
	dst.m_bottom= HELP_Y_POS + HELP_SIZE;
	Draw::Draw(m_help_reg_num, &src, &dst, help, 0.0f);


	//�w���v�\�����A�ȉ��̂��̂�`�悷��
	if (m_help_f == true)
	{
		//���w���v�摜�\��
		src.m_top   = 150.0f;
		src.m_left  =   0.0f;
		src.m_right =1280.0f;
		src.m_bottom= 870.0f;
			
		dst.m_top   =  20.0f;
		dst.m_left  =  20.0f;
		dst.m_right =1180.0f;
		dst.m_bottom= 680.0f;
		Draw::Draw(m_help_reg_num + m_page_num, &src, &dst, d, 0.0f);
			
		//���߂�{�^���\��
		src.m_top   =  0.0f;
		src.m_left  =  0.0f;
		src.m_right = 64.0f;
		src.m_bottom= 64.0f;
	
		dst.m_top   = 30.0f;
		dst.m_left  = 30.0f;
		dst.m_right = 80.0f;
		dst.m_bottom= 80.0f;
		Draw::Draw(m_Back_reg_num, &src, &dst, back, 0.0f);			

		//���y�[�W��i�߂�{�^���\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 330.0f;
		dst.m_left = 1100.0f;
		dst.m_right = 1150.0f;
		dst.m_bottom = 380.0f;
		Draw::Draw(46, &src, &dst, d, 0.0f);

		//���y�[�W��߂��{�^���\��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = -64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 330.0f;
		dst.m_left = 50.0f;
		dst.m_right = 100.0f;
		dst.m_bottom = 380.0f;
		Draw::Draw(46, &src, &dst, d, 0.0f);
	}

	

	//�f�o�b�O�p���}�E�X�ʒu�\��
	wchar_t str[256];
	swprintf_s(str, L"x=%f,y=%f", m_mou_x, m_mou_y);
	Font::StrDraw(str, 20.0f, 20.0f, 12.0f, d);
}
