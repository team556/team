//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

////�R���X�g���N�^
//CObjTest::CObjTest(float x, float y)
//{
//	//�쐬���ɓn���ꂽ�l���A���W�̏����l�ɑ��
//	m_x = x;
//	m_y = y;
//}

//�C�j�V�����C�Y
void CObjFightOver::Init()
{
	//m_mou_x = 0.0f;	//�}�E�XX���W
	//m_mou_y = 0.0f; //�}�E�XY���W
	//m_mou_r = false;//�E�N���b�N
	m_mou_l = false;//���N���b�N

	m_a = 0.0f;
	m_a_vec = 0.0f;
	m_a_f = false;
	m_black_out_a = 0.0f;
	m_gameover_a = 0.0f;

	//m_cnt = 3 * 60;	//3�b�J�E���g


	//���O���[�o���ϐ�(�S�ۑ��f�[�^)���Z�b�g����
	g_Stage_progress = 1;

	for (int i = 0; i < 4; i++)
	{
		g_destroy_progress[i] = false;
	}

	g_Bar_Level = 1;
	g_Ins_Level = 1;
	g_Mis_Recast_Level = 0;
	g_Pow_equip_Level = 1;
	g_Pow_equip_Lv_achieve = 1;
	g_Def_equip_Level = 1;
	g_Def_equip_Lv_achieve = 1;
	g_Spe_equip_Level = 1;
	g_Spe_equip_Lv_achieve = 1;
	g_Bal_equip_Level = 1;
	g_Bal_equip_Lv_achieve = 1;
	g_Pod_equip_Level = 1;
	g_Pod_equip_Lv_achieve = 1;
	g_Player_max_size = 10;
	g_Special_equipment = 0;

	for (int i = 0; i < 5; i++)
	{
		g_Special_mastering[i] = false;
	}

	g_Power_num = 0;		
	g_Defense_num = 0;		
	g_Speed_num = 0;		
	g_Balance_num = 0;		
	g_Research_num = 0;
	g_Remain_num = 1000;

	g_Iron_num = 0;
	g_Wood_num = 0;
	g_Silver_num = 0;
	g_Plastic_num = 0;
	g_Aluminum_num = 0;
	g_gus_num = 0;
	g_Raremetal_num = 0;
}

//�A�N�V����
void CObjFightOver::Action()
{
	//�Q�[���I�[�o�[���b�Z�[�W�\����̏���
	if (m_gameover_a >= 1.0f)
	{
		////�}�E�X�̈ʒu���擾
		//m_mou_x = (float)Input::GetPosX();
		//m_mou_y = (float)Input::GetPosY();
		////�}�E�X�̃{�^���̏��
		//m_mou_r = Input::GetMouButtonR();
		m_mou_l = Input::GetMouButtonL();

		m_a_f = true;			//�t���O�L��

		//���N���b�N�����ꍇ�A���s(��x�N���b�N����ƈȌ�A�N���b�N�����Ƃ����̏����ɓ���)
		if (m_mou_l == true || m_black_out_a != 0.0f)
		{
			//�N���b�N����炷(1�x�݂̂������s����Ȃ�)
			if (m_black_out_a == 0.0f)
			{
				Audio::Start(3);
			}

			//��ʈÓ]���ߓx�����X�ɑ��������A��ʑS�̂��Ó]��������A
			//�t���O�𗧂āA�^�C�g����ʂɈڍs����
			if (m_black_out_a >= 1.0f)
			{
				Scene::SetScene(new CSceneTitle());	//�V�[���ڍs
			}
			else
			{
				m_black_out_a += 0.01f;	//��ʈÓ]
				m_a -= 0.03f;			//�N���b�N�Ñ��t�H���g�����X�ɔ�\���ɁB
			}

			m_a_f = false;//�t���O����
		}
	}
	//�Q�[���I�[�o�[���b�Z�[�W�\���O�̏���
	else
	{
		//�Q�[���I�[�o�[���b�Z�[�W�̓��ߓx�������A
		//�Q�[���I�[�o�[���b�Z�[�W��\�����Ă����B
		//���\����A����else���𔲂���B
		m_gameover_a += 0.01f;
	}

	//���u�N���b�N�Ń^�C�g���v�̕����_�ŏ���
	//�t���O�L���̏ꍇ
	if (m_a_f == true)
	{
		if (m_a <= 0.5)			//0.5�Ő؂�ւ��āA�N���b�N������alpha����
		{
			m_a_vec += 0.003f;	//�x�N�g���ɉ��Z
		}
		else
		{
			m_a_vec -= 0.003f;	//�x�N�g���Ɍ��Z
		}

		m_a += m_a_vec;	//�x�N�g���𔽉f
	}
}

//�h���[
void CObjFightOver::Draw()
{
	RECT_F src;//�؂���ʒu
	RECT_F dst;//�\���ʒu	


	//�N���b�N�Ń^�C�g���\��
	float c0[4] = { 1.0f,1.0f,1.0f,m_a };//char�̐F
	Font::StrDraw(L"�N���b�N�Ń^�C�g��", 350, 600, 50, c0);

	//�Q�[���I�[�o�[�t�H���g�\��
	float c[4] = { 0.7f,0.0f,0.0f,m_gameover_a };//char�̐F
	Font::StrDraw(L"G A M E", 220, 100, 200, c);
	Font::StrDraw(L"O V E R", 220, 300, 200, c);


	//����ʑS�̈Ó]�p�摜�\��
	//��blackout�̓��ߓx�̒l�Łu�\��/��\���v���؂�ւ�����
	float blackout[4] = { 1.0f,1.0f,1.0f,m_black_out_a };	//��ʑS�̈Ó]�摜�p
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1200.0f;
	src.m_bottom = 700.0f;

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 1200.0f;
	dst.m_bottom = 700.0f;
	Draw::Draw(20, &src, &dst, blackout, 0.0f);
}
