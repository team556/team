//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�}�N��
//���_���oIN �� OUT �Ȃ̂��ŏ����ʒu���ς��
//IN�Ȃ� 0.0f,OUT�Ȃ� 1000.0f�B
#define INI_CLOUD_POS (m_In_Out_Check == true ? 0.0f : 1000.0f) //�_�̏����ʒu

//�R���X�g���N�^
CObjCloud_Effect::CObjCloud_Effect(bool check)
{
	//�쐬���ɓn���ꂽ�l�ɂāA�_���oIN / OUT�𔻒f����
	m_In_Out_Check = check;
}

//�C�j�V�����C�Y
void CObjCloud_Effect::Init()
{
	m_Cloud_move = INI_CLOUD_POS;
	m_white_out_a = 0.0f;
	m_white_out_a_vec = 0.0f;

	m_time = 0;
	m_level_se = false;
	m_white_se = false;
}

//�A�N�V����
void CObjCloud_Effect::Action()
{
	//���_���oIN�̏���
	if (m_In_Out_Check == true)
	{
		//�_����ʑS�̂𕢂��B���������s��
		if (m_Cloud_move <= 1000.0f)
		{
			m_Cloud_move += 10.0f;
		}
	}

	//���_���oOUT�̏���
	else 
	{
		//�_����ʊO�Ɉړ������A��ʂ�������
		if (m_Cloud_move >= 0.0f)
		{
			m_Cloud_move -= 10.0f;
		}
	}

	//���z���C�g�A�E�g���o�̏���(�琬��ʔw�i�ύX���Ɏ��s�����)
	if (white_out_f == true)
	{
		m_time++;//���ԉ��Z����

		if (m_white_out_a <= 1.0)			//1.0�Ő؂�ւ��āA�z���C�g�A�E�g���o��alpha����
		{
			m_white_out_a_vec += 0.0005f;	//�x�N�g���ɉ��Z
		}
		else
		{
			m_white_out_a_vec -= 0.0003f;	//�x�N�g���Ɍ��Z
		}

		m_white_out_a += m_white_out_a_vec;	//�x�N�g���𔽉f


		//�z���C�g�A�E�g���o�����J�n�Ɠ�����1��炷
		if (m_white_se == false)
		{
			//�z���C�g�A�E�g��
			Audio::Start(4);

			m_white_se = true;
		}

		//�z���C�g�A�E�g���o�����J�n����2.3�b��A1��炷
		if (m_level_se == false && m_time >= 60 * 2.3)
		{
			//���x���A�b�v��
			Audio::Start(3);

			m_level_se = true;
		}

		//���S�Ƀz���C�g�A�E�g�������_�Ŏ��ۂɎ{�݃��x����1UP������
		if (m_white_out_a >= 1.0f)
		{
			//�������̏ꍇ
			if (window_start_manage == Institute && player_level != ((int)((g_Bar_Level + g_Ins_Level) / 2)))
			{
				g_Ins_Level++;
			}
			//���ɂ̏ꍇ
			else if(window_start_manage == Barracks && player_level != ((int)((g_Bar_Level + g_Ins_Level) / 2)))
			{
				g_Bar_Level++;
			}
		}
		//�z���C�g�A�E�g���o�����I�����_(��ʂ�������)�ł��̉��o�������甲����
		else if (m_white_out_a <= 0.0f)
		{
			//����̃z���C�g�A�E�g���o�ׂ̈Ɉȉ��̕ϐ������������Ă���
			m_white_out_a = 0.0f;
			m_white_out_a_vec = 0.0f;

			m_time = 0;
			m_level_se = false;	//���x���A�b�v���t���OOFF	
			m_white_se = false;	//�z���C�g�A�E�g���t���OOFF
			white_out_f = false;//�z���C�g�A�E�g���o�t���O��OFF
		}
	}
}

//�h���[
void CObjCloud_Effect::Draw()
{
	//�`��J���[���  R=RED  G=Green  B=Blue A=alpha(���ߏ��)
	//�_�摜�p
	float d[4] = { 1.0f,1.0f,1.0f,1.0f };
	//�z���C�g�A�E�g���o�摜�p
	float c[4] = { 1.0f,1.0f,1.0f,m_white_out_a };
	//�z���C�g�A�E�g���ɕ\������t�H���g�摜�p
	float f[4] = { 0.0f,0.0f,1.0f,m_white_out_a - 1.0f };

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu


	//���_(�E��)�\��
	src.m_top = 0.0f;
	src.m_left = 40.0f;
	src.m_right = 300.0f;
	src.m_bottom = 165.0f;

	dst.m_top = -1100.0f + m_Cloud_move;
	dst.m_left = 700.0f - m_Cloud_move;
	dst.m_right = 2300.0f - m_Cloud_move;
	dst.m_bottom = 300.0f + m_Cloud_move;
	Draw::Draw(15, &src, &dst, d, 0.0f);

	//�ȉ��̈ʒu�ɂȂ�Ɖ�ʑS�̂��B���
	//dst.m_top = -100.0f;
	//dst.m_left = -300.0f;
	//dst.m_right = 1300.0f;
	//dst.m_bottom = 1300.0f;


	//���_(����)�\��
	src.m_top = -10.0f;
	src.m_left = 10.0f;
	src.m_right = -280.0f;
	src.m_bottom = -170.0f;

	dst.m_top = 400.0f - m_Cloud_move;
	dst.m_left = -1100.0f + m_Cloud_move;
	dst.m_right = 500.0f + m_Cloud_move;
	dst.m_bottom = 1800.0f - m_Cloud_move;
	Draw::Draw(15, &src, &dst, d, 0.0f);

	//�ȉ��̈ʒu�ɂȂ�Ɖ�ʑS�̂��B���
	//dst.m_top = -600.0f;
	//dst.m_left = -100.0f;
	//dst.m_right = 1500.0f;
	//dst.m_bottom = 800.0f;


	//���z���C�g�A�E�g���o�摜�\��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1200.0f;
	src.m_bottom = 700.0f;

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 1200.0f;
	dst.m_bottom = 700.0f;
	Draw::Draw(19, &src, &dst, c, 0.0f);


	//���z���C�g�A�E�g���̃t�H���g�摜(�f�����W�xUP�I)�\��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 891.0f;
	src.m_bottom = 117.0f;

	dst.m_top = 275.0f;
	dst.m_left = 200.0f;
	dst.m_right = 1000.0f;
	dst.m_bottom = 425.0f;
	Draw::Draw(133, &src, &dst, f, 0.0f);
}
