//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"

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
		if (m_white_out_a <= 0.6)			//0.6�Ő؂�ւ��āA�z���C�g�A�E�g���o��alpha����
		{
			m_white_out_a_vec += 0.002f;	//�x�N�g���ɉ��Z
		}
		else
		{
			m_white_out_a_vec -= 0.002f;	//�x�N�g���Ɍ��Z
		}

		m_white_out_a += m_white_out_a_vec;	//�x�N�g���𔽉f


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

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu


	//���_(�E��)�\��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 500.0f;
	src.m_bottom = 500.0f;

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
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = -500.0f;
	src.m_bottom = -500.0f;

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
}
