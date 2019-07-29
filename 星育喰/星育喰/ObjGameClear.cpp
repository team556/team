//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjGameClear.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;

//�}�N��
#define INI_ALPHA (1.0f) //���ߓx(�A���t�@�l)�̏����l

////�R���X�g���N�^
//CObjTest::CObjTest(float x, float y)
//{
//	//�쐬���ɓn���ꂽ�l���A���W�̏����l�ɑ��
//	m_x = x;
//	m_y = y;
//}

//�C�j�V�����C�Y
void CObjGameClear::Init()
{
	m_mou_x = 0.0f;	//�}�E�XX���W
	m_mou_y = 0.0f; //�}�E�XY���W
	m_mou_r = false;//�E�N���b�N
	m_mou_l = false;//���N���b�N

	m_f = false;
	m_y_vec = 1.0;

	for (int i = 0; i < 100; i++)//�z��̏�����
		m_cy[i] = i * 25 + 700;	//�s�Ԃ̊Ԋu���󂯂�̂ƁA��ʂ�艺�ɂ���
	m_c_nam = 0;

	m_speed = 0;
	m_alpha = INI_ALPHA;
	m_right_alpha = 3.0f;

	m_flag = false;
	m_end_f = false;
}

//�A�N�V����
void CObjGameClear::Action()
{
	////�}�E�X�̈ʒu���擾
	//m_mou_x = (float)Input::GetPosX();
	//m_mou_y = (float)Input::GetPosY();
	//�}�E�X�̃{�^���̏��
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	//�������Ɉړ������鏈��
	for (int i = 0; i < 100; i++)
	{
		m_cy[i] -= m_y_vec + m_speed;
	}

	if (m_right_alpha >= 0.0f)
	{
		m_right_alpha -= 0.01f;
	}

	//�E�N���b�N�������Ă���ԁA�G���h���[���̗���鑬�x�������Ȃ�
	if (m_mou_r == true && m_end_f == false)
	{
		m_speed = 10;
		m_right_alpha -= 0.1f;//�E�N���b�N�������Ɠ��ߑ��x�������Ȃ�
	}
	//else if (m_mou_l == true && m_end_f == false)
	//{
	//	m_speed = -10;
	//	m_right_alpha -= 0.1f;//�E�N���b�N�������Ɠ��ߑ��x�������Ȃ�
	//}
	else
	{
		m_speed = 0;
	}

	
	//���N���b�N�Ń^�C�g����ʂփV�[���ڍs
	if (m_flag == true)
	{
		m_alpha -= 0.01f;

		if (m_alpha <= 0.0f)
		{
			Scene::SetScene(new CSceneTitle());//�^�C�g����ʂփV�[���ڍs
		}

		return;
	}
	//���N���b�N�ƃG���h�t���O��true�ɂȂ�����
	else if (m_mou_l == true && m_end_f == true)
	{
		m_flag = true;

		//�I����
		Audio::Start(1);
	}

	//23�ԖڃX�N���[���ɓo�^���ꂽ�摜���������ɗ���Ă�����
	if (m_cy[79]+125.0f <= 0.0f)
	{
		m_y_vec = 0;	//�X�N���[�����~�߂�
		m_end_f = true;
	}
}
//�h���[
void CObjGameClear::Draw()
{
	//�`��J���[���  R=RED  G=Green  B=Blue A=alpha(���ߏ��)
	float d[4] = { 0.0f,0.0f, 0.0f, 1.0f };

	//�摜�p[�V�[���ڍs���t�F�[�h�A�E�g]
	float w[4] = { 1.0f,1.0f, 1.0f, m_alpha };

	//�摜�p[�V�[���ڍs���t�F�[�h�A�E�g]
	float w2[4] = { 1.0f,1.0f, 1.0f, m_right_alpha };

	//�����̐F(��)
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//�؂���ʒu
	RECT_F dst;//�\���ʒu
	
	src.m_top   =  0.0f;
	src.m_left  =  0.0f;
	src.m_right =100.0f;
	src.m_bottom=100.0f;
	
	dst.m_top   =  0.0f;
	dst.m_left  =  0.0f;
	dst.m_right =1200.0f;
	dst.m_bottom= 700.0f;

	//0�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
	Draw::Draw(0, &src, &dst, d, 0.0f);

	//�g�p�������y�A���ʉ��T�C�g�`��
	src.m_top = 3.0f;
	src.m_left = 3.0f;
	src.m_right = 1606.0f;
	src.m_bottom = 114.0f;

	dst.m_top = 0.0f + m_cy[0];
	dst.m_left = 350.0f;
	dst.m_right = 850.0f;
	dst.m_bottom = 0.0f + m_cy[1];
	Draw::Draw(3, &src, &dst, w, 0.0);

	//���l�`��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 185.0f;
	src.m_bottom = 90.0f;

	dst.m_top = 0.0f + m_cy[2];
	dst.m_left = 575.0f;
	dst.m_right = 625.0f;
	dst.m_bottom = 0.0f + m_cy[3];
	Draw::Draw(7, &src, &dst, w, 0.0);

	//���lURL�`��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 870.0f;
	src.m_bottom = 84.0f;

	dst.m_top = 10.0f + m_cy[3];
	dst.m_left = 475.0f;
	dst.m_right = 725.0f;
	dst.m_bottom = 10.0f + m_cy[4];
	Draw::Draw(8, &src, &dst, w, 0.0);

	//�������`��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 282.0f;
	src.m_bottom = 90.0f;

	dst.m_top = 20.0f + m_cy[6];
	dst.m_left = 565.0f;
	dst.m_right = 635.0f;
	dst.m_bottom = 20.0f + m_cy[7];
	Draw::Draw(9, &src, &dst, w, 0.0);

	//������URL1�`��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1060.0f;
	src.m_bottom = 84.0f;

	dst.m_top = 30.0f + m_cy[7];
	dst.m_left = 425.0f;
	dst.m_right = 775.0f;
	dst.m_bottom = 30.0f + m_cy[8];
	Draw::Draw(10, &src, &dst, w, 0.0);

	//������URL2�`��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 876.0f;
	src.m_bottom = 84.0f;

	dst.m_top = 30.0f + m_cy[8];
	dst.m_left = 475.0f;
	dst.m_right = 725.0f;
	dst.m_bottom = 30.0f + m_cy[9];
	Draw::Draw(11, &src, &dst, w, 0.0);

	//TAMM�`��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1005.0f;
	src.m_bottom = 84.0f;

	dst.m_top = 30.0f + m_cy[11];
	dst.m_left = 505.0f;
	dst.m_right = 690.0f;
	dst.m_bottom = 30.0f + m_cy[12];
	Draw::Draw(12, &src, &dst, w, 0.0);

	//TAMMURL�`��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1341.0f;
	src.m_bottom = 84.0f;

	dst.m_top = 40.0f + m_cy[12];
	dst.m_left = 400.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 40.0f + m_cy[13];
	Draw::Draw(13, &src, &dst, w, 0.0);

	//DOVA-SYN_DROME�`��
	src.m_top = 2.0f;
	src.m_left = 0.0f;
	src.m_right = 945.0f;
	src.m_bottom = 77.0f;

	dst.m_top = 40.0f + m_cy[15];
	dst.m_left = 505.0f;
	dst.m_right = 690.0f;
	dst.m_bottom = 40.0f + m_cy[16];
	Draw::Draw(14, &src, &dst, w, 0.0);

	//DOVA-SYN_DROMEURL�`��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 819.0f;
	src.m_bottom = 84.0f;

	dst.m_top = 50.0f + m_cy[16];
	dst.m_left = 480.0f;
	dst.m_right = 720.0f;
	dst.m_bottom = 50.0f + m_cy[17];
	Draw::Draw(15, &src, &dst, w, 0.0);

	//�������ʉ��ŗV�ڂ��`��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 852.0f;
	src.m_bottom = 90.0f;

	dst.m_top = 50.0f + m_cy[19];
	dst.m_left = 495.0f;
	dst.m_right = 705.0f;
	dst.m_bottom = 50.0f + m_cy[20];
	Draw::Draw(16, &src, &dst, w, 0.0);

	//�������ʉ��ŗV�ڂ�URL�`��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1842.0f;
	src.m_bottom = 84.0f;

	dst.m_top = 60.0f + m_cy[20];
	dst.m_left = 400.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 60.0f + m_cy[21];
	Draw::Draw(17, &src, &dst, w, 0.0);

	//���ʉ����{�`��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 474.0f;
	src.m_bottom = 90.0f;

	dst.m_top = 70.0f + m_cy[23];
	dst.m_left = 542.0f;
	dst.m_right = 658.0f;
	dst.m_bottom = 70.0f + m_cy[24];
	Draw::Draw(18, &src, &dst, w, 0.0);

	//���ʉ����{url�`��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1364.0f;
	src.m_bottom = 84.0f;

	dst.m_top = 80.0f + m_cy[24];
	dst.m_left = 400.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 80.0f + m_cy[25];
	Draw::Draw(19, &src, &dst, w, 0.0);

	//OtoLogic�`��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 444.0f;
	src.m_bottom = 84.0f;

	dst.m_top = 90.0f + m_cy[27];
	dst.m_left = 550.0f;
	dst.m_right = 650.0f;
	dst.m_bottom = 90.0f + m_cy[28];
	Draw::Draw(20, &src, &dst, w, 0.0);

	//OtoLogic�`��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 882.0f;
	src.m_bottom = 84.0f;

	dst.m_top = 100.0f + m_cy[28];
	dst.m_left = 450.0f;
	dst.m_right = 750.0f;
	dst.m_bottom = 100.0f + m_cy[29];
	Draw::Draw(21, &src, &dst, w, 0.0);

	//�g�p�t�H���g�`��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 672.0f;
	src.m_bottom = 105.0f;

	dst.m_top = 110.0f + m_cy[33];
	dst.m_left = 500.0f;
	dst.m_right = 700.0f;
	dst.m_bottom = 110.0f + m_cy[34];
	Draw::Draw(32, &src, &dst, w, 0.0);

	//�g�p�t�H���g�s���I�h�`��
	src.m_top = 1.0f;
	src.m_left = 1444.0f;
	src.m_right = 0.0f;
	src.m_bottom = 101.0f;

	dst.m_top = 120.0f + m_cy[34];
	dst.m_left = 750.0f;
	dst.m_right = 450.0f;
	dst.m_bottom = 120.0f + m_cy[35];
	Draw::Draw(33, &src, &dst, w, 0.0);

	//��ҏЉ�
	src.m_top = 1.0f;
	src.m_left = 290.0f;
	src.m_right = 10.0f;
	src.m_bottom = 100.0f;

	dst.m_top = 130.0f + m_cy[36];
	dst.m_left = 650.0f;
	dst.m_right = 550.0f;
	dst.m_bottom = 130.0f + m_cy[37];
	Draw::Draw(35, &src, &dst, w, 0.0);

	//��Җ��Љ�
	src.m_top = 1.0f;
	src.m_left = 290.0f;
	src.m_right = 30.0f;
	src.m_bottom = 100.0f;

	dst.m_top =140.0f + m_cy[37];
	dst.m_left = 650.0f;
	dst.m_right = 550.0f;
	dst.m_bottom = 140.0f + m_cy[38];
	Draw::Draw(34, &src, &dst, w, 0.0);

	//�T�C�g�Љ�
	src.m_top =2.0f;
	src.m_left = 486.0f;
	src.m_right = 105.0f;
	src.m_bottom = 100.0f;

	dst.m_top = 150.0f + m_cy[39];
	dst.m_left = 650.0f;
	dst.m_right = 550.0f;
	dst.m_bottom = 150.0f + m_cy[40];
	Draw::Draw(29, &src, &dst, w, 0.0);

	//��ׂȂ����Љ�
	src.m_top = 1.0f;
	src.m_left = 0.0f;
	src.m_right = 716.0f;
	src.m_bottom = 93.0f;

	dst.m_top = 160.0f + m_cy[40];
	dst.m_left = 500.0f;
	dst.m_right = 700.0f;
	dst.m_bottom = 160.0f + m_cy[41];
	Draw::Draw(30, &src, &dst, w, 0.0);

	//�g�p�t�H���gURL
	src.m_top		= 1.0f;
	src.m_left		= 0.0f;
	src.m_right		= 1649.0f;
	src.m_bottom	= 94.0f;

	dst.m_top = 170.0f + m_cy[41];
	dst.m_left = 400.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 170.0f + m_cy[42];
	Draw::Draw(31, &src, &dst, w, 0.0);

	//�����f�B���N�^
	src.m_top = 1.0f;
	src.m_left = 0.0f;
	src.m_right = 795.0f;
	src.m_bottom = 129.0f;

	dst.m_top = 180.0f + m_cy[46];
	dst.m_left = 450.0f;
	dst.m_right = 750.0f;
	dst.m_bottom = 180.0f + m_cy[47];
	Draw::Draw(36, &src, &dst, w, 0.0);

	//�r�c�`��
	src.m_top = 5.0f;
	src.m_left = 0.0f;
	src.m_right = 497.0f;
	src.m_bottom = 99.0f;

	dst.m_top = 190.0f + m_cy[47];
	dst.m_left = 550.0f;
	dst.m_right = 650.0f;
	dst.m_bottom = 190.0f + m_cy[48];
	Draw::Draw(22, &src, &dst, w, 0.0);

	//�v���O���}
	src.m_top = 1.0f;
	src.m_left = 0.0f;
	src.m_right = 490.0f;
	src.m_bottom = 100.0f;

	dst.m_top = 200.0f + m_cy[50];
	dst.m_left = 500.0f;
	dst.m_right = 700.0f;
	dst.m_bottom = 200.0f + m_cy[51];
	Draw::Draw(37, &src, &dst, w, 0.0);

	//����`��
	src.m_top = 1.0f;
	src.m_left = 0.0f;
	src.m_right = 398.0f;
	src.m_bottom = 99.0f;

	dst.m_top = 210.0f + m_cy[51];
	dst.m_left = 550.0f;
	dst.m_right = 650.0f;
	dst.m_bottom = 210.0f + m_cy[52];
	Draw::Draw(23, &src, &dst, w, 0.0);

	//�ؑ��`��
	src.m_top = 1.0f;
	src.m_left = 0.0f;
	src.m_right = 393.0f;
	src.m_bottom = 100.0f;

	dst.m_top = 220.0f + m_cy[52];
	dst.m_left = 550.0f;
	dst.m_right = 650.0f;
	dst.m_bottom = 220.0f + m_cy[53];
	Draw::Draw(24, &src, &dst, w, 0.0);

	//����`��
	src.m_top = 1.0f;
	src.m_left = 0.0f;
	src.m_right = 392.0f;
	src.m_bottom = 100.0f;

	dst.m_top = 230.0f + m_cy[53];
	dst.m_left = 550.0f;
	dst.m_right = 650.0f;
	dst.m_bottom = 230.0f + m_cy[54];
	Draw::Draw(26, &src, &dst, w, 0.0);

	//�O���t�B�b�J�[
	src.m_top = 1.0f;
	src.m_left = 0.0f;
	src.m_right = 674.0f;
	src.m_bottom = 125.0f;

	dst.m_top = 240.0f + m_cy[56];
	dst.m_left = 500.0f;
	dst.m_right = 700.0f;
	dst.m_bottom = 240.0f + m_cy[57];
	Draw::Draw(38, &src, &dst, w, 0.0);

	//�z�K�`��
	src.m_top = 1.0f;
	src.m_left = 0.0f;
	src.m_right = 488.0f;
	src.m_bottom = 100.0f;

	dst.m_top = 250.0f + m_cy[57];
	dst.m_left = 550.0f;
	dst.m_right = 650.0f;
	dst.m_bottom = 250.0f + m_cy[58];
	Draw::Draw(28, &src, &dst, w, 0.0);

	//��c�`��
	src.m_top = 1.0f;
	src.m_left = 0.0f;
	src.m_right = 484.0f;
	src.m_bottom = 90.0f;

	dst.m_top = 260.0f + m_cy[58];
	dst.m_left = 550.0f;
	dst.m_right = 650.0f;
	dst.m_bottom = 260.0f + m_cy[59];
	Draw::Draw(27, &src, &dst, w, 0.0);

	//�v�����i�[�`��
	src.m_top = 1.0f;
	src.m_left = 0.0f;
	src.m_right = 497.0f;
	src.m_bottom = 100.0f;

	dst.m_top = 270.0f + m_cy[61];
	dst.m_left = 500.0f;
	dst.m_right = 700.0f;
	dst.m_bottom = 270.0f + m_cy[62];
	Draw::Draw(39, &src, &dst, w, 0.0);

	//�e�c�`��
	src.m_top = 1.0f;
	src.m_left = 0.0f;
	src.m_right = 490.0f;
	src.m_bottom = 100.0f;

	dst.m_top = 280.0f + m_cy[62];
	dst.m_left = 550.0f;
	dst.m_right = 650.0f;
	dst.m_bottom = 280.0f + m_cy[63];
	Draw::Draw(25, &src, &dst, w, 0.0);

	//END�`��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 269.0f;
	src.m_bottom = 117.0f;

	dst.m_top = 290.0f + m_cy[71];
	dst.m_left = 525.0f;
	dst.m_right = 675.0f;
	dst.m_bottom = 290.0f + m_cy[72];
	Draw::Draw(2, &src, &dst, w, 0.0);

	//�^�C�g�����S�`��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1557.0f;
	src.m_bottom = 929.0f;

	dst.m_top = 300.0f + m_cy[78];
	dst.m_left = 300.0f;
	dst.m_right = 851.0f;
	dst.m_bottom = 650.0f + m_cy[79];
	Draw::Draw(1, &src, &dst, w, 0.0);
	


	//�E�N���b�N������ƕ`��
	src.m_top = 3.0f;
	src.m_left = 3.0f;
	src.m_right = 1481.0f;
	src.m_bottom = 114.0f;

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 200.0f;
	dst.m_bottom = 32.0f;
	Draw::Draw(4, &src, &dst, w2, 0.0);

	//�G���h���[������������܂��`��
	src.m_top = 3.0f;
	src.m_left = 3.0f;
	src.m_right = 1663.0f;
	src.m_bottom = 116.0f;

	dst.m_top = 40.0f;
	dst.m_left = 50.0f;
	dst.m_right = 300.0f;
	dst.m_bottom = 72.0f;
	Draw::Draw(5, &src, &dst, w2, 0.0);

	//Font::StrDraw(L"�E�N���b�N�������������", 0, 0, 20, w2);
	//Font::StrDraw(L"�G���h���[������������܂��B", 0,25, 20, w2);

	//Font::StrDraw(L"�g�p�������y�A���ʉ��T�C�g", 260, m_cy[0], 50, c);


	/*Font::StrDraw(L"End", 550, m_cy[20] , 60, c);*/

	//�G���h�t���O��true�ɂȂ�����
	if (m_end_f == true)
	{
		src.m_top = 3.0f;
		src.m_left = 3.0f;
		src.m_right = 1483.0f;
		src.m_bottom = 116.0f;

		dst.m_top = 630.0f;
		dst.m_left = 400.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 660.0f;
		Draw::Draw(6, &src, &dst, w, 0.0);
	}
}
