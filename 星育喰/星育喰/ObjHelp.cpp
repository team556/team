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
#define HELP_X_POS (1120.0f) //�w���v�{�^���̏���X�ʒu
#define HELP_Y_POS (30.0f)	 //�w���v�{�^���̏���Y�ʒu
#define HELP_SIZE (50.0f)	 //�w���v�{�^���̃T�C�Y(width & height)
#define INI_ALPHA (0.0f) //���ߓx(�A���t�@�l)�̏����l
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

	m_px = HELP_X_POS;
	m_py = HELP_Y_POS;
	m_vec = 0.0f;

	m_Help_Button_color = INI_COLOR;
	m_Back_Button_color = INI_COLOR;
	m_Page_Back_Button_color = INI_COLOR;
	m_Page_Next_Button_color = INI_COLOR;

	m_Help_Button_alpha = INI_ALPHA;

	m_mig_staging_f = false;
	m_Tra_Eat_f = false;
	m_is_operatable = true;
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

		//���łɃw���v�{�^���\��������1��̂ݍs���悤�ɏ������Ă���
		m_Help_Button_alpha = -0.1f;
	}
	else  //(m_Scene_num == 3)//����	3
	{
		m_page_max = 2;
		m_help_reg_num = 21;
		m_Back_reg_num = 56;

		//���łɂ��̃^�C�~���O�ŃV�[���ڍs���o�p�̍��W�ύX�������Ă���
		m_px += 407.3f;
		m_py -= 407.3f;
		m_vec = 50.0f;
		m_Help_Button_alpha = 1.0f;
		m_is_operatable = false;
	}
}

//�A�N�V����
void CObjHelp::Action()
{
	//���V�[���ڍs���o����(�w���v�{�^����\������)
	//���Ȃ��A�e�V�[�����Ƀw���v�{�^���̔�\�����@�͈Ⴄ�B
	if (m_mig_staging_f == true)
	{
		if (m_Scene_num == 1)//�z�[��	1										
		{
			//�琬��ʈڍs���o
			if (m_Tra_Eat_f == true)
			{
				//��ʊO(�E��)�Ɍ������ăw���v�{�^�����ړ������A��\����Ԃɂ���
				if (m_px < 1200.0f || m_py > 0.0f)
				{
					m_px += 5.0f;
					m_py -= 5.0f;
				}
			}
			//�퓬������ʈڍs���o
			else
			{
				//�w���v�{�^�������X�ɔ�\���ɂ�����
				if (m_Help_Button_alpha > 0.0f)
				{
					m_Help_Button_alpha -= 0.01f;
				}
			}
		}
		else if (m_Scene_num == 2)//�琬	2
		{
			//�����ɔ�\���ɂ���
			m_Help_Button_alpha = 0.0f;
		}
		else  //(m_Scene_num == 3)//����	3
		{
			//����ʊO(�E��)�Ɍ������ăw���v�{�^�����ړ������A��\����Ԃɂ���

			//��ʊO(�E��)�ɍs���܂ňړ�������
			if (m_px < HELP_X_POS + 407.3f)
			{
				m_px += m_vec * 0.37;//X�ړ�����
				m_py -= m_vec * 0.37;//Y�ړ�����
				m_vec /= 0.956f;//�ړ����x��������
			}
		}
		
		return;//���o���̓w���v�{�^�����������Ȃ��悤�ɂ���B
	}

	//���w���v�{�^���\������
	//���Ȃ��A�e�V�[�����Ƀw���v�{�^���̕\�����@�͈Ⴄ�B
	else
	{
		if (m_Scene_num == 1)//�z�[��	1											
		{
			//�w���v�{�^�������X�ɕ\��������
			if (m_Help_Button_alpha < 1.0f)
			{
				m_Help_Button_alpha += 0.01f;
			}
		}
		else if (m_Scene_num == 2)//�琬	2
		{
			//�����ɕ\������(1��̂ݍs����)
			if (m_Help_Button_alpha == -0.1f)
			{
				m_Help_Button_alpha = 1.0f;
			}
		}
		else  //(m_Scene_num == 3)//����	3
		{
			//����ʊO�E�ォ�獶���Ɍ������ăw���v�{�^�����ړ������A��ʓ��ɕ\��������
			
			//����X�ʒu�ɗ���܂ňړ�������
			if (m_px >= HELP_X_POS)
			{
				m_px -= m_vec * 0.37f;//X�ړ�����
				m_py += m_vec * 0.37f;//Y�ړ�����
				m_vec *= 0.956f;//�ړ����x��������
			}
		}
	}

	//����s����
	if (m_is_operatable == false)
	{
		return;//����s���̓w���v�{�^�����������Ȃ��悤�ɂ���B
	}

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
	if (g_help_f == false)						
	{											
		//�w���v�{�^���I��͈�
		if (m_px - 10.0f < m_mou_x && m_mou_x < m_px - 10.0f + HELP_SIZE && m_py < m_mou_y && m_mou_y < m_py + HELP_SIZE)
		{		
			m_Help_Button_color = 1.0f;//�I�𒆂̓J���[���x���グ��

			if (m_mou_l == true && m_key_f == false)//�}�E�X���N���b�N
			{
				g_help_f = true;//�w���v�\������
				m_key_f = true;	//�A�Ő���(�L�[�t���OON)

				//�I����
				Audio::Start(1);

				m_Help_Button_color = 0.5f;//�I�����̓J���[���x����U������
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
		//���y�[�W�߂��{�^��
		if (30.0f < m_mou_x && m_mou_x < 80.0f && 326.0f < m_mou_y && m_mou_y < 375.0f &&
			m_page_max != 1)//�y�[�W�ő吔��1�ł͂Ȃ�
		{
			m_Page_Back_Button_color = 1.0f;//�I�𒆂̓J���[���x���グ��

			if (m_mou_l == true && m_key_f == false)//�}�E�X���N���b�N
			{
				if (m_page_num - 1 < INI_PAGE)
				{
					m_page_num = m_page_max;//���̃y�[�W���ŏ��̃y�[�W�ł���΁A�Ō�̃y�[�W�Ɉړ�������
				}
				else
				{
					m_page_num--;		//�y�[�W��߂�
				}

				//�I����
				Audio::Start(1);

				m_Page_Back_Button_color = 0.5f;//�I�����̓J���[���x����U������

				m_key_f = true;		//�A�Ő���(�L�[�t���OON)
			}
		}
		else
		{
			//�I��͈͊O�̎��͖��I���J���[�ɂ���
			m_Page_Back_Button_color = INI_COLOR;
		}

		//���y�[�W�i�߂�{�^��
		if (1110.0f < m_mou_x && m_mou_x < 1160.0f && 326.0f < m_mou_y && m_mou_y < 375.0f &&
			m_page_max != 1)//�y�[�W�ő吔��1�ł͂Ȃ�
		{
			m_Page_Next_Button_color = 1.0f;//�I�𒆂̓J���[���x���グ��

			if (m_mou_l == true && m_key_f == false)//�}�E�X���N���b�N
			{
				if (m_page_num + 1 > m_page_max)
				{
					m_page_num = INI_PAGE;//���̃y�[�W���Ō�̃y�[�W�ł���΁A�ŏ��̃y�[�W�Ɉړ�������
				}
				else
				{
					m_page_num++;	//�y�[�W��i�߂�
				}

				//�I����
				Audio::Start(1);

				m_Page_Next_Button_color = 0.5f;//�I�����̓J���[���x����U������

				m_key_f = true;		//�A�Ő���(�L�[�t���OON)
			}
		}
		else
		{
			//�I��͈͊O�̎��͖��I���J���[�ɂ���
			m_Page_Next_Button_color = INI_COLOR;
		}

		//�߂�{�^��
		if (30 < m_mou_x && m_mou_x < 80 && 30 < m_mou_y && m_mou_y < 80 || m_mou_r == true)
		{
			m_Back_Button_color = 1.0f;//�I�𒆂̓J���[���x���グ��

			if (m_mou_l == true || m_mou_r == true)
			{
				g_help_f = false;//�w���v��\���ɂ���

				m_Help_Button_color = INI_COLOR;//�w���v�{�^���J���[���x������������

				m_page_num = INI_PAGE;//�y�[�W������������

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
	//�w���v�{�^���p
	float help[4] = { m_Help_Button_color,m_Help_Button_color,m_Help_Button_color,m_Help_Button_alpha };

	//�߂�{�^���p
	float back[4] = { m_Back_Button_color,m_Back_Button_color,m_Back_Button_color,1.0f };

	//�y�[�W�߂��{�^���p
	float page_back[4] = { m_Page_Back_Button_color,m_Page_Back_Button_color,m_Page_Back_Button_color,1.0f };

	//�y�[�W�i�߂�{�^���p
	float page_next[4] = { m_Page_Next_Button_color,m_Page_Next_Button_color,m_Page_Next_Button_color,1.0f };

	//���̑��摜�p
	float d[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//�؂���ʒu
	RECT_F dst;//�\���ʒu
	

	//���w���v�{�^���\��
	src.m_top   =  0.0f;
	src.m_left  =  0.0f;
	src.m_right =128.0f;
	src.m_bottom=128.0f;
	
	dst.m_top   = m_py;
	dst.m_left  = m_px;
	dst.m_right = m_px + HELP_SIZE;
	dst.m_bottom= m_py + HELP_SIZE;
	Draw::Draw(m_help_reg_num, &src, &dst, help, 0.0f);


	//�w���v�\�����A�ȉ��̂��̂�`�悷��
	if (g_help_f == true)
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

		//�y�[�W�ő吔��1�łȂ���Ε\������
		if (m_page_max != 1)
		{
			//���y�[�W��߂��{�^���\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = -128.0f;
			src.m_bottom = 128.0f;

			dst.m_top = 330.0f;
			dst.m_left = 30.0f;
			dst.m_right = 80.0f;
			dst.m_bottom = 380.0f;
			Draw::Draw(46, &src, &dst, page_back, 0.0f);

			//���y�[�W��i�߂�{�^���\��
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 128.0f;
			src.m_bottom = 128.0f;

			dst.m_top = 330.0f;
			dst.m_left = 1120.0f;
			dst.m_right = 1170.0f;
			dst.m_bottom = 380.0f;
			Draw::Draw(46, &src, &dst, page_next, 0.0f);
		}
	}

	

	//�f�o�b�O�p���}�E�X�ʒu�\��
	wchar_t str[256];
	swprintf_s(str, L"x=%f,y=%f", m_mou_x, m_mou_y);
	Font::StrDraw(str, 20.0f, 20.0f, 12.0f, d);
}
