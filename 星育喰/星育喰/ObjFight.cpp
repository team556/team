//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjFight.h"
#include "UtilityModule.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//static�ϐ��̒�`
bool CObjFight::battle_start = false;
bool CObjFight::battle_end = false;
float CObjFight::damage_buff[2] = { 1.0f,1.0f };

#define INI_COLOR (0.9f) //�S�J���[���x�̏����l(�A�C�R�����I�𒆂̃J���[)

//c = cnt(�퓬����),e_n = m_ene_nam(�G�i���o�[)
CObjFight::CObjFight(int c)
{
	m_cnt = c * 60;
}

//�C�j�V�����C�Y
void CObjFight::Init()
{
	m_mou_x = 0.0f;	//�}�E�XX���W
	m_mou_y = 0.0f; //�}�E�XY���W
	m_mou_r = false;//�E�N���b�N
	m_mou_l = false;//���N���b�N
	
	m_line = 3;		//�����l�A
	m_line_nam = 3; //�����l�A���I��

	m_cnt = 60 * 300;//�퓬����(60 * X = X�b)
	m_a = 1;		//�����l�A�s����

	m_ex = 0;
	m_ey = 0;

	m_scale_down_cnt = 0;
	m_scale_down_speed = 0.04f;
	m_font_a = 1.0f;

	m_start_count = 60 * 3;	//3�b�o�ߌ�A�퓬�J�n
	m_start_count_f = false;

	m_end_f = false;

	//���ȉ���static�ϐ��͑��V�[������퓬��ʂɓ���x�ɏ��������s��
	battle_start = false;
	battle_end = false;
	for (int i = 0; i < 2; i++)
	{
		damage_buff[i] = 1.0f;
	}

	Hits::SetHitBox(this, 400, 310, 400, 60, ELEMENT_LINE, OBJ_FIGHT, 1);
}

//�A�N�V����
void CObjFight::Action()
{
	//���퓬�J�n�O�͐퓬���������s���Ȃ��悤�ɂ��違
	//�퓬�J�n�J�E���g�̏���
	if (battle_start == false)
	{
		//�퓬�O���o�I�u�W�F�N�g����u�퓬�J�n�J�E���g�v�J�n�t���O��true�ɂ������Ɏ��s
		//�퓬�J�n�J�E���g�����X�Ɍ��炵�Ă����A0�ɂȂ������A�퓬�J�n�t���O���𗧂Ă�B
		if (m_start_count <= 60 * 0)
		{
			//�|�[�Y��ʓ��Ő퓬���ꎞ��~����ہA
			//battle_start��[true / false]�ňꎞ��~���s�����A
			//�ēx���̐퓬�J�n�J�E���g�̏������s����Ɩ��ł���ׁA
			//[m_start_count_f]��false�ɁA[m_start_count]�������l�ɖ߂����ŁA
			//���̏������s���Ȃ��悤�ɂ���B
			m_start_count_f = false;
			m_start_count = 60 * 3;

			battle_start = true;//�퓬�J�n�t���O�𗧂Ă�
		}
		else if (m_start_count_f == true)
		{
			m_start_count--;//�퓬�J�n�J�E���g�_�E��
		}

		return;
	}

	//���퓬�I���ԍ�(�c��1�b)�̃^�C�~���O�Ő퓬�I���t���O�𗧂Ă�
	if (m_cnt <= 60)
	{
		battle_end = true;	//�퓬�I���t���O�𗧂Ă�
	}

	if (m_cnt > 0)	//0���傫����
		m_cnt--;	//�J�E���g�_�E��
	
	//�w�i�k������
	m_scale_down_cnt += m_scale_down_speed;
	if (m_scale_down_speed > 0)
		m_scale_down_speed -= 0.00001f;

	//�퓬�J�n���\�������"�X�^�[�g"�̕��������X�ɓ�����
	if (m_scale_down_cnt >= 0.5 && m_font_a >= 0) {
		m_font_a -= 0.01f;
	}

	//�}�E�X�̈ʒu���擾
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//�}�E�X�̃{�^���̏��
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();
	

	m_line = 6;//��ɑI��O���C����������

	if (400 <= m_mou_x && m_mou_x <= 800) 
	{
		if (200 <= m_mou_y && m_mou_y <= 260) {					
			if (m_mou_l == true) { m_line_nam = 0; }//�ド�C��------
			else { m_line = 0; }
		}
		else if (310 <= m_mou_y && m_mou_y <= 370) {			
			if (m_mou_l == true) { m_line_nam = 1; }//�����C��------
			else { m_line = 1; }
		}
		else if (420 <= m_mou_y && m_mou_y <= 480) {			
			if (m_mou_l == true) { m_line_nam = 2; }//�����C��------
			else { m_line = 2; }
		}
		else {};//���C���O�������Ȃ�
	}
	else {};

	//���N���A����
	//�G�l�~�[���Ɏ擾�o���鎑�����͈Ⴄ���߁A
	//�ȉ��ł��ꂼ�������ݒ肵�AObjFightClear���쐬����B
	if (m_end_f == true)
	{
		m_end_f = false;
		if (g_Challenge_enemy == 0)									//������P�Ԗ�
		{//							(�Z�l, ����, �傫��, �Z 1�`5�擾�X�L��)
			CObjFightClear* crer = new CObjFightClear(2000, 0, 20, 1);	
			Objs::InsertObj(crer, OBJ_FIGHT_CLEAR, 15);
		}
		if (g_Challenge_enemy == 1)									//������Q�Ԗ�
		{//							(�Z�l, ����, �傫��, �Z 1�`5�擾�X�L��)
			CObjFightClear* crer = new CObjFightClear(10000, 1, 60, 0);
			Objs::InsertObj(crer, OBJ_FIGHT_CLEAR, 15);
		}
		if (g_Challenge_enemy == 2)									//������R�Ԗ�
		{//							(�Z�l, ����, �傫��, �Z 1�`5�擾�X�L��)
			CObjFightClear* crer = new CObjFightClear(15000, 2, 80, 0);
			Objs::InsertObj(crer, OBJ_FIGHT_CLEAR, 15);
		}
		if (g_Challenge_enemy == 3)									//������S�Ԗ�
		{//							(�Z�l, ����, �傫��, �Z 1�`5�擾�X�L��)
			CObjFightClear* crer = new CObjFightClear(3000, 3, 30, 0);
			Objs::InsertObj(crer, OBJ_FIGHT_CLEAR, 15);
		}
		if (g_Challenge_enemy == 4)									//�{�X
		{//							(�Z�l, ����, �傫��, �Z 1�`5�擾�X�L��)
			CObjFightClear* crer = new CObjFightClear(1000, 4, 90, 2);
			Objs::InsertObj(crer, OBJ_FIGHT_CLEAR, 15);
		}
	}
}

//�h���[
void CObjFight::Draw()
{	
	//�`��J���[���  R=RED  G=Green  B=Blue A=alpha(���ߏ��)
	float c[4] = { 1.0f,1.0f,1.0f,m_a };
	float d[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu

	//���w�i�\��
	src.m_top = 0.0f + (m_scale_down_cnt * 4.5 / 6);
	src.m_left = 0.0f + m_scale_down_cnt;
	src.m_right = 960.0f - m_scale_down_cnt;
	src.m_bottom = 638.0f - (m_scale_down_cnt * 4.5 / 6);

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 1200.0f;
	dst.m_bottom = 700.0f;
	Draw::Draw(0, &src, &dst, d, 0.0f);


	//���퓬���ԕ\��
	int s = (m_cnt / 60), m = 0;	//�~�j�b�c,�Z�R���h��錾��������
	if (s >= 60) {						//60�b�ȏ�̏ꍇ
		m += (s / 60); int n = (s / 60); s -= (n * 60);	//���ɕb��60�𑫂��āA�b�͂��̕����炷�B
	}													//n�͂��̌��炷���B

	wchar_t str[256];
	swprintf_s(str, L"%02d :%02d", m, s);		//2���A0�l�ߕ\��
	Font::StrDraw(str,500 ,60 ,50 , c);


	//���U���p���C���`�揈��
	CObjFight* obj = (CObjFight*)Objs::GetObj(OBJ_FIGHT);

	//�`��J���[���  R=RED  G=Green  B=Blue A=alpha(���ߏ��)
	float d0[4] = { 1.0f,1.0f,1.0f,0.2f };
	float d1[4] = { 1.0f,1.0f,1.0f,0.2f };
	float d2[4] = { 1.0f,1.0f,1.0f,0.2f };

	if (obj->GetCount() == 0) {//-------------------------���Ԑ؂�̏ꍇ----
		if (m_a > 0.0f) {
			m_a -= 0.03f;				//������
		}
		d0[3] = { m_a };//�ʂɏ�����
		d1[3] = { m_a };
		d2[3] = { m_a };
	}
	else {//------------------------------------------�ΐ펞�Ԓ��̂ݓ���-----
		if (m_line == 0)		//�I�����Ɋe���C����s������
			d0[3] = INI_COLOR;
		else if (m_line == 1)
			d1[3] = INI_COLOR;
		else if (m_line == 2)
			d2[3] = INI_COLOR;

		if (m_line_nam == 0)	//�J�[�\�����ɔ��s������
			d0[3] = 1.0f;
		else if (m_line_nam == 1)
			d1[3] = 1.0f;
		else if (m_line_nam == 2)
			d2[3] = 1.0f;
	}

	//�U���p���C���摜
	src.m_top   =  0.0f;
	src.m_left  =  0.0f;
	src.m_right =100.0f;
	src.m_bottom=100.0f;

	dst.m_top   =200.0f;
	dst.m_left  =400.0f;
	dst.m_right =800.0f;
	dst.m_bottom=260.0f;
	Draw::Draw(2, &src, &dst, d0, 0.0f);

	dst.m_top   =310.0f;
	dst.m_left  =400.0f;
	dst.m_right =800.0f;
	dst.m_bottom=370.0f;
	Draw::Draw(2, &src, &dst, d1, 0.0f);

	dst.m_top   =420.0f;
	dst.m_left  =400.0f;
	dst.m_right =800.0f;
	dst.m_bottom=480.0f;
	Draw::Draw(2, &src, &dst, d2, 0.0f);

	//���퓬�J�n�J�E���g
	//�퓬�J�n�J�E���g�̒l�ɍ��킹�āA
	//�R���Q���P�Ə��X�ɃJ�E���g�_�E�����Ă����A
	//�O�ɂȂ�Ɓu�X�^�[�g�I�v�ƕ\���B
	//���̌�u�X�^�[�g�I�v�̕����͏��X�ɓ��������Ă����A
	//�ŏI�I�Ɍ����Ȃ��Ȃ�B
	float start_font[4] = { 1.0f,1.0f,1.0f,m_font_a };
	
	if (battle_start == true)
	{
		Font::StrDraw(L"�X�^�[�g�I", 420, 250, 80, start_font);
	}
	else if (m_start_count <= 60 * 1)
	{
		Font::StrDraw(L"�P", 495, 260, 160, start_font);
	}
	else if (m_start_count <= 60 * 2)
	{
		Font::StrDraw(L"�Q", 495, 260, 160, start_font);
	}
	else if (m_start_count_f == true)
	{
		Font::StrDraw(L"�R", 495, 260, 160, start_font);
	}



	////�f�o�b�O�p���}�E�X�ʒu�\��
	//wchar_t test_mou[256];
	//swprintf_s(test_mou, L"x=%f,y=%f", m_mou_x, m_mou_y);
	//Font::StrDraw(test_mou, 20.0f, 20.0f, 12.0f, d);
}
