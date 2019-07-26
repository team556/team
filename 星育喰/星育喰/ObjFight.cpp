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
float CObjFight::Pla_One_pat_dem[3] = { 1.0f,1.0f,1.0f };
float CObjFight::Ene_One_pat_dem[3] = { 1.0f,1.0f,1.0f };
int CObjFight::p_pnam = 0;
int CObjFight::e_pnam = 0;
float CObjFight::damage_buff[2] = { 1.0f,1.0f };

#define INI_COLOR (0.5f) //�S�J���[���x�̏����l(�A�C�R�����I�𒆂̃J���[)

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

	m_line_dis = false;

	m_key_U_f = false;
	m_key_D_f = false;

	m_line_choice = 1;

	//���ȉ���static�ϐ��͑��V�[������퓬��ʂɓ���x�ɏ��������s��
	battle_start = false;
	battle_end = false;
	
	for (int i = 0; i < 3; i++)
	{
		Pla_One_pat_dem[i] = 1.0f;
		Ene_One_pat_dem[i] = 1.0f;
	}
	
	p_pnam = 0;
	e_pnam = 0;

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

			if (g_tutorial_progress == 2)
			{
				//ObjMessage�̃��b�Z�[�W�i�s�x�𑝉�������
				CObjMessage* message = (CObjMessage*)Objs::GetObj(OBJ_MESSAGE);
				message->Setprogress(1);
			}
		}
		else if (m_start_count_f == true)
		{
			m_start_count--;//�퓬�J�n�J�E���g�_�E��
		}
		
		return;
	}

	//�퓬�J�n�̃J�E���g���I��������Ƀ��C����\��������
	//����x���������Ȃ�
	if (m_line_dis == false) {
		m_line_nam = 1;
		m_line_dis = true;
	}

	//���퓬�I���ԍ�(�c��1�b)�̃^�C�~���O�Ő퓬�I���t���O�𗧂Ă�
	if (m_cnt <= 60)
	{
		battle_end = true;	//�퓬�I���t���O�𗧂Ă�
	}

	//�`���[�g���A�����͐퓬���Ԃ��������Ȃ�
	if (!(2 <= g_tutorial_progress && g_tutorial_progress <= 5))
	{
		if (m_cnt > 0)	//0���傫����
			m_cnt--;	//�J�E���g�_�E��
	}

	//�w�i�g�又��
	//���퓬�I����͎��ۂ���Ȃ��B
	if (battle_end == false)
	{
		m_scale_down_cnt += m_scale_down_speed;
		if (m_scale_down_speed > 0)
			m_scale_down_speed -= 0.00001f;
	}

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


	//�`���[�g���A�����͑���o���Ȃ��悤�ɂ��������
	if (g_tutorial_progress >= 6)
	{
		//���C������L�[�őI������Ƃ��̏���
		if (m_key_U_f == false && Input::GetVKey(VK_UP) == true) {

			//�I�𒆂̃��C������ԏ�ɗ������ɉ��Ɉړ�������
			if (m_line_choice <= 0) {
				m_line_choice = 2;
			}
			else {
				m_line_choice--;
			}
			m_key_U_f = true;
		}

		if (m_key_D_f == false && Input::GetVKey(VK_DOWN) == true) {

			//�I�𒆂̃��C������ԉ��ɗ������ɏ�Ɉړ�������
			if (m_line_choice >= 2) {
				m_line_choice = 0;
			}
			else {
				m_line_choice++;
			}
			m_key_D_f = true;
		}

		//�I�����C����X�������Ƀ}�E�X�J�[�\�������銎�A�㉺�̃L�[�����͂���Ă��Ȃ��Ƃ�
		//���L�[�������Ă�Ԃ̓}�E�X�ɔ��������Ȃ�����
		if (400 <= m_mou_x && m_mou_x <= 800 && m_key_U_f == false && m_key_D_f == false) {

			if (200 <= m_mou_y && m_mou_y <= 250) {
				if (m_mou_l == true) { m_line_nam = 0; }//�ド�C��------
				else { m_line = 0; }
			}
			else if (310 <= m_mou_y && m_mou_y <= 360) {
				if (m_mou_l == true) { m_line_nam = 1; }//�����C��------
				else { m_line = 1; }
			}
			else if (420 <= m_mou_y && m_mou_y <= 470) {
				if (m_mou_l == true) { m_line_nam = 2; }//�����C��------
				else { m_line = 2; }
			}
			else {};//���C���O�������Ȃ�

		}
		else if (m_key_U_f == true || m_key_D_f == true) {
			if (m_line_choice == 0) {
				m_line_nam = 0;
			}
			else if (m_line_choice == 1) {
				m_line_nam = 1;
			}
			else if (m_line_choice == 2) {
				m_line_nam = 2;
			}
		}


		//�L�[�t���O����---------------
		if (Input::GetVKey(VK_UP) == false) {

			m_key_U_f = false;

		}

		if (Input::GetVKey(VK_DOWN) == false) {

			m_key_D_f = false;

		}
	}
	//�ȉ��̏����̓`���[�g���A�����̂ݎ��s�����B
	else if (g_tutorial_progress == 5)
	{
		if (400 <= m_mou_x && m_mou_x <= 800) {

			if (200 <= m_mou_y && m_mou_y <= 250) {
				if (m_mou_l == true) { m_line_nam = 0; }//�ド�C��------
				else { m_line = 0; }
			}
		}
	}
	


	//���N���A����
	//�G�l�~�[���Ɏ擾�o���鎑�����͈Ⴄ���߁A
	//�ȉ��ł��ꂼ�������ݒ肵�AObjFightClear���쐬����B
	if (m_end_f == true)
	{
		m_end_f = false;

		//����������
		//�ȉ��̏��Ԃň��������ĉ������B
		//(�Z�l��, �T�C�Y(HP), ����A���O, ����A�A�h���X, ���ސ�A, ����B���O, ����B�A�h���X, ���ސ�B, �X�y�V�����Z)
		//���ڍא���
		// �Z�l��:		�@�l���ł���Z�l���B���̒l���A�Z�l������������B
		// �T�C�Y(HP):	  �l���ł���T�C�Y(HP)�B���̒l���A�T�C�Y(HP)���㏸����B
		// ����A���O:	�@�l���o���鎑��(1��)�̖��O����͂��Ă��������B
		// ����A�A�h���X: �l���o���鎑��(1��)�̃O���[�o���ϐ��A�h���X����͂��Ă��������B
		// ���ސ�A:		  �l���o���鎑��(1��)�̐��B���̒l���A���ސ�����������B
		// ����B���O:	�@�l���o���鎑��(2��)�̖��O�B��2�ڂ��Ȃ��ꍇ�A���͂��Ȃ��ł��������B
		// ����B�A�h���X: �l���o���鎑��(2��)�̃A�h���X�B��2�ڂ��Ȃ��ꍇ�A���͂��Ȃ��ł��������B
		// ���ސ�B:		  �l���o���鎑��(2��)�̐��B��2�ڂ��Ȃ��ꍇ�A���͂��Ȃ��ł��������B
		// �X�y�V�����Z:  �l���ł���X�y�V�����Z�B�ȉ��̐�������͂���ƁA���̒l�ɑΉ�����X�y�V�����Z���擾�o���܂��B���l���ł��Ȃ��ꍇ��0����͂��Ă��������B
		//	(1:Explosion�@2:Fracture_Ray�@3:Immortality�@4:���~�b�g�u���C�N�@5:�X�e���C�h���^)

		//������P�Ԗ�
		if (g_Challenge_enemy == 0)									
		{				
			CObjFightClear* crer = new CObjFightClear(5500, 100, L"�؍�", &g_Wood_num, 50, L"�S", &g_Iron_num, 70, 2);
			Objs::InsertObj(crer, OBJ_FIGHT_CLEAR, 15);
		}
		//������Q�Ԗ�
		if (g_Challenge_enemy == 1)									
		{				
			CObjFightClear* crer = new CObjFightClear(10000, 350, L"�v���X�`�b�N",  &g_Plastic_num, 40, L"�K�X", &g_gus_num, 50, 1);
			Objs::InsertObj(crer, OBJ_FIGHT_CLEAR, 15);
		}
		//������R�Ԗ�
		if (g_Challenge_enemy == 2)									
		{
			CObjFightClear* crer = new CObjFightClear(12000, 400, L"��", &g_Silver_num, 65, L"�K�X", &g_gus_num, 50, 5);
			Objs::InsertObj(crer, OBJ_FIGHT_CLEAR, 15);
		}
		//������S�Ԗ�
		if (g_Challenge_enemy == 3)									
		{
			CObjFightClear* crer = new CObjFightClear(8000, 200, L"�S", &g_Iron_num, 30, L"�A���~", &g_Aluminum_num, 80, 3);
			Objs::InsertObj(crer, OBJ_FIGHT_CLEAR, 15);
		}
		//�{�X
		if (g_Challenge_enemy == 4)									
		{
			CObjFightClear* crer = new CObjFightClear(1000, 20, L"�؍�", &g_Wood_num, 80, 0);
			Objs::InsertObj(crer, OBJ_FIGHT_CLEAR, 15);
		}
		//�`���[�g���A��
		if (g_Challenge_enemy == 5)
		{
			//�G���[��������邽�߂ɖ؍ނ�0�l������悤�ɂ��Ă���
			CObjFightClear* crer = new CObjFightClear(5000, 20, L"�Ȃ�", &g_Wood_num, 0, 4);
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
	src.m_right = 1200.0f - m_scale_down_cnt;
	src.m_bottom = 700.0f - (m_scale_down_cnt * 4.5 / 6);

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 1200.0f;
	dst.m_bottom = 700.0f;
	Draw::Draw(0, &src, &dst, d, 0.0f);

	//���퓬���ԕ\��
	if (battle_end == false) {
		int s = (m_cnt / 60), m = 0;	//�~�j�b�c,�Z�R���h��錾��������
		if (s >= 60) {						//60�b�ȏ�̏ꍇ
			m += (s / 60); int n = (s / 60); s -= (n * 60);	//���ɕb��60�𑫂��āA�b�͂��̕����炷�B
		}													//n�͂��̌��炷���B

		//���c�莞�ԕ\��(�\�̈ʂ̕���)
		//���Ă��铮��͎c�蕪����10�̈ʂ��Ƃ邽�߂�
		//����/10�����ď����_�ȉ��؂�̂Ă�����
		//���̒l�ɂ���Đ؂���ʒu��ς��Ă���
		src.m_top = 1250.0f;
		src.m_left =  CUT_ZERO + (floor(m / 10) * 125);	//�����������Ƃ͂Ȃ���10���ȏ�ɐݒ肵���Ƃ���
		src.m_right = END_ZERO + (floor(m / 10) * 125);	//���삷��悤�ɂȂ��Ă���
		src.m_bottom = 1375.0f;

		dst.m_top = 50.0f;
		dst.m_left = 525.0f;
		dst.m_right = 550.0f;
		dst.m_bottom = 100.0f;
		Draw::Draw(41, &src, &dst, d, 0.0f);

		//���c�莞�ԕ\��(��̈ʂ̕���)
		//���Ă��铮��͎c�蕪����1�̈ʂ��Ƃ邽�߂�
		//����/10�̗]����o����
		//���̒l�ɂ���Đ؂���ʒu��ς��Ă���
		src.m_top = 1250.0f;
		src.m_left =  CUT_ZERO + ((m % 10) * 125);
		src.m_right = END_ZERO + ((m % 10) * 125);
		src.m_bottom = 1375.0f;

		dst.m_top = 50.0f;
		dst.m_left = 550.0f;
		dst.m_right = 575.0f;
		dst.m_bottom = 100.0f;
		Draw::Draw(41, &src, &dst, d, 0.0f);

		//���c�莞�ԕ\��(�R����)
		src.m_top = 1250.0f;
		src.m_left = 250.0f;
		src.m_right = 375.0f;
		src.m_bottom = 1375.0f;

		dst.m_top = 50.0f;
		dst.m_left = 575.0f;
		dst.m_right = 600.0f;
		dst.m_bottom = 100.0f;
		Draw::Draw(41, &src, &dst, d, 0.0f);

		//���c�莞�ԕ\��(�\�̈ʂ̕b��)
		//���Ă��铮��͎c��b����10�̈ʂ��Ƃ邽�߂�
		//�b��/10�����ď����_�ȉ��؂�̂Ă�����
		//���̒l�ɂ���Đ؂���ʒu��ς��Ă���
		src.m_top = 1250.0f;
		src.m_left =  CUT_ZERO + (floor(s / 10) * 125);
		src.m_right = END_ZERO + (floor(s / 10) * 125);
		src.m_bottom = 1375.0f;

		dst.m_top = 50.0f;
		dst.m_left = 600.0f;
		dst.m_right = 625.0f;
		dst.m_bottom = 100.0f;
		Draw::Draw(41, &src, &dst, d, 0.0f);

		//���c�莞�ԕ\��(��̈ʂ̕b��)
		//���Ă��铮��͎c��b����1�̈ʂ��Ƃ邽�߂�
		//�b��/10�̗]����o����
		//���̒l�ɂ���Đ؂���ʒu��ς��Ă���
		src.m_top = 1250.0f;
		src.m_left =  CUT_ZERO + ((s % 10) * 125);
		src.m_right = END_ZERO + ((s % 10) * 125);
		src.m_bottom = 1375.0f;

		dst.m_top = 50.0f;
		dst.m_left = 625.0f;
		dst.m_right = 650.0f;
		dst.m_bottom = 100.0f;
		Draw::Draw(41, &src, &dst, d, 0.0f);
	}

	//wchar_t str[256];
	//swprintf_s(str, L"%02d :%02d", m, s);		//2���A0�l�ߕ\��
	//Font::StrDraw(str,500 ,60 ,50 , c);


	//���U���p���C���`�揈��
	CObjFight* obj = (CObjFight*)Objs::GetObj(OBJ_FIGHT);

	//�`��J���[���  R=RED  G=Green  B=Blue A=alpha(���ߏ��)
	float d0[4] = { 1.0f,1.0f - (Pla_One_pat_dem[0] - 1.0f) * 2,1.0f - (Pla_One_pat_dem[0] - 1.0f) * 2,0.2f };
	float d1[4] = { 1.0f,1.0f - (Pla_One_pat_dem[1] - 1.0f) * 2,1.0f - (Pla_One_pat_dem[1] - 1.0f) * 2,0.2f };
	float d2[4] = { 1.0f,1.0f - (Pla_One_pat_dem[2] - 1.0f) * 2,1.0f - (Pla_One_pat_dem[2] - 1.0f) * 2,0.2f };

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
	src.m_right =400.0f;
	src.m_bottom=60.0f;

	dst.m_top   =200.0f;
	dst.m_left  =400.0f;
	dst.m_right =800.0f;
	dst.m_bottom=260.0f;
	Draw::Draw(118, &src, &dst, d0, 0.0f);

	dst.m_top   =310.0f;
	dst.m_left  =400.0f;
	dst.m_right =800.0f;
	dst.m_bottom=370.0f;
	Draw::Draw(119, &src, &dst, d1, 0.0f);

	dst.m_top   =420.0f;
	dst.m_left  =400.0f;
	dst.m_right =800.0f;
	dst.m_bottom=480.0f;
	Draw::Draw(120, &src, &dst, d2, 0.0f);

	if (battle_end == false) {
		//�|�b�h��~�T�C���̃L�[�{�[�h�I��p�摜
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		//�~�T�C���L�[�`��
		dst.m_top = 655.0f;
		dst.m_left = 230.0f;
		dst.m_right = 262.0f;
		dst.m_bottom = 680.0f;
		Draw::Draw(35, &src, &dst, d, 0.0f);

		//�ԃ|�b�h�L�[�`��
		dst.m_top = 655.0f;
		dst.m_left = 531.0f;
		dst.m_right = 563.0f;
		dst.m_bottom = 680.0f;
		Draw::Draw(36, &src, &dst, d, 0.0f);

		//�|�b�h�L�[�`��
		dst.m_top = 655.0f;
		dst.m_left = 681.0f;
		dst.m_right = 713.0f;
		dst.m_bottom = 680.0f;
		Draw::Draw(37, &src, &dst, d, 0.0f);

		//�΃|�b�h�L�[�`��
		dst.m_top = 655.0f;
		dst.m_left = 838.0f;
		dst.m_right = 870.0f;
		dst.m_bottom = 680.0f;
		Draw::Draw(38, &src, &dst, d, 0.0f);

		//�D�|�b�h�L�[�`��
		dst.m_top = 655.0f;
		dst.m_left = 979.0f;
		dst.m_right = 1011.0f;
		dst.m_bottom = 680.0f;
		Draw::Draw(39, &src, &dst, d, 0.0f);

		//�X�y�V�����Z�𑕔����Ă���Ƃ��̓A�C�R�����o��
		if (g_Special_equipment != 0)
		{
			dst.m_top = 60.0f;
			dst.m_left = 950.0f;
			dst.m_right = 990.0f;
			dst.m_bottom = 100.0f;
			Draw::Draw(40, &src, &dst, d, 0.0f);
		}

		//�O�����ݐ����摜�`��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1353.0f;
		src.m_bottom = 1050.0f;

		dst.m_top = 25.0f;
		dst.m_left = 25.0f;
		dst.m_right = 225.0f;
		dst.m_bottom = 200.0f;
		Draw::Draw(80, &src, &dst, d, 0.0f);

	}



	//���퓬�J�n�J�E���g
	//�퓬�J�n�J�E���g�̒l�ɍ��킹�āA
	//�R���Q���P�Ə��X�ɃJ�E���g�_�E�����Ă����A
	//�O�ɂȂ�Ɓu�X�^�[�g�I�v�ƕ\���B
	//���̌�u�X�^�[�g�I�v�̕����͏��X�ɓ��������Ă����A
	//�ŏI�I�Ɍ����Ȃ��Ȃ�B
	float start_font[4] = { 1.0f,1.0f,1.0f,m_font_a };
	
	if (battle_start == true)
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 547.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 225.0f;
		dst.m_left = 400.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 325.0f;
		Draw::Draw(42, &src, &dst, start_font, 0.0f);
	}
	else if (m_start_count <= 60 * 1)
	{
		src.m_top = 1250.0f;
		src.m_left = CUT_ZERO + 125;
		src.m_right = END_ZERO + 125;
		src.m_bottom = 1375.0f;

		dst.m_top = 250.0f;
		dst.m_left = 550.0f;
		dst.m_right = 650.0f;
		dst.m_bottom = 350.0f;
		Draw::Draw(41, &src, &dst, start_font, 0.0f);
	}
	else if (m_start_count <= 60 * 2)
	{
		src.m_top = 1250.0f;
		src.m_left = CUT_ZERO + 250;
		src.m_right = END_ZERO + 250;
		src.m_bottom = 1375.0f;

		dst.m_top = 250.0f;
		dst.m_left = 550.0f;
		dst.m_right = 650.0f;
		dst.m_bottom = 350.0f;
		Draw::Draw(41, &src, &dst, start_font, 0.0f);
	}
	else if (m_start_count_f == true)
	{
		src.m_top = 1250.0f;
		src.m_left = CUT_ZERO + 375;
		src.m_right = END_ZERO + 375;
		src.m_bottom = 1375.0f;

		dst.m_top = 250.0f;
		dst.m_left = 550.0f;
		dst.m_right = 650.0f;
		dst.m_bottom = 350.0f;
		Draw::Draw(41, &src, &dst, start_font, 0.0f);
	}

	//if (battle_start == true)
	//{
	//	Font::StrDraw(L"�X�^�[�g�I", 420, 250, 80, start_font);
	//}
	//else if (m_start_count <= 60 * 1)
	//{
	//	Font::StrDraw(L"�P", 495, 260, 160, start_font);
	//}
	//else if (m_start_count <= 60 * 2)
	//{
	//	Font::StrDraw(L"�Q", 495, 260, 160, start_font);
	//}
	//else if (m_start_count_f == true)
	//{
	//	Font::StrDraw(L"�R", 495, 260, 160, start_font);
	//}



	//�f�o�b�O�p���}�E�X�ʒu�\��
	//wchar_t test_mou[256];
	//swprintf_s(test_mou, L"x=%f,y=%f", m_mou_x, m_mou_y);
	//Font::StrDraw(test_mou, 20.0f, 20.0f, 12.0f, d);
}
