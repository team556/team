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



	//�e�X�g��������������琬��ʂɔ�Ԃ悤�ɂ���
	if (m_mou_x > 500 && m_mou_l == true)
	{
		Scene::SetScene(new CSceneHome());//�琬��ʂփV�[���ڍs
	}

	if ((m_mou_x > 337 && m_mou_x<357)&&m_mou_l==true)
	{
		Scene::SetScene(new CSceneHome());//�琬��ʂփV�[���ڍs
	}



}
//�h���[
void CObjNameInput::Draw()
{
	//�����̐F(��)
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//�؂���ʒu
	RECT_F dst;//�\���ʒu


	//���摜�̓K�p
	src.m_top = 145.0f;
	src.m_left = 0.0f;
	src.m_right =1500.0f;
	src.m_bottom = 630.0f;

	dst.m_top = 200.0f;
	dst.m_left = 350.0f;
	dst.m_right = 850.0f;
	dst.m_bottom = 500.0f;
	Draw::Draw(1, &src, &dst, c, 0.0f);

	//�f�o�b�O�p���}�E�X�ʒu�\��
	wchar_t test_mou[256];
	swprintf_s(test_mou, L"x=%f,y=%f", m_mou_x, m_mou_y);
	Font::StrDraw(test_mou, 20.0f, 20.0f, 12.0f, c);
}
