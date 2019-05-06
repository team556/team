//STL�Ńo�O�@�\��OFF�ɂ���
#define _SECURE_SCL (0)
#define _HAS_ITERTOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p�w�b�_�[
#include "GameHead.h"

//�R���X�g���N�^
CScenePreparation::CScenePreparation()
{

}

//�f�X�g���N�^
CScenePreparation::~CScenePreparation()
{

}

//�Q�[�����������\�b�h
void CScenePreparation::InitScene()
{
	//�z�[���I�u�W�F�N�g�쐬
	CObjPreparation* obj = new CObjPreparation();	//�퓬������ʃI�u�W�F�N�g�쐬
	Objs::InsertObj(obj, OBJ_PREPARATION, 10);		//�퓬������ʃI�u�W�F�N�g�o�^

	//�w�i��ǂݍ���0�Ԃɓo�^
	Draw::LoadImage(L"TitleBackgroundTest.jpg", 0, TEX_SIZE_512);

	//�G�f��1(1�X�e�[�W)��ǂݍ���1�Ԃɓo�^
	Draw::LoadImage(L"Enemy_Planet_Test.jpg", 1, TEX_SIZE_512);

	//�G�f��2(1�X�e�[�W)��ǂݍ���2�Ԃɓo�^
	Draw::LoadImage(L"Enemy_Planet_Test2.jpg", 2, TEX_SIZE_512);

	//�G�f��3(1�X�e�[�W)��ǂݍ���3�Ԃɓo�^
	Draw::LoadImage(L"Enemy_Planet_Test3.jpg", 3, TEX_SIZE_512);

	//�G�f��4(1�X�e�[�W)��ǂݍ���4�Ԃɓo�^
	Draw::LoadImage(L"Enemy_Planet_Test4.jpg", 4, TEX_SIZE_512);

	//�{�X�f��(1�X�e�[�W)��ǂݍ���5�Ԃɓo�^
	Draw::LoadImage(L"�v���C���[�f��Lv1.png", 5, TEX_SIZE_512);

	//�G�f��1(2�X�e�[�W)��ǂݍ���6�Ԃɓo�^
	Draw::LoadImage(L"Enemy_Planet_Test.jpg", 6, TEX_SIZE_512);

	//�G�f��2(2�X�e�[�W)��ǂݍ���7�Ԃɓo�^
	Draw::LoadImage(L"Enemy_Planet_Test2.jpg", 7, TEX_SIZE_512);

	//�G�f��3(2�X�e�[�W)��ǂݍ���8�Ԃɓo�^
	Draw::LoadImage(L"Enemy_Planet_Test3.jpg", 8, TEX_SIZE_512);

	//�G�f��4(2�X�e�[�W)��ǂݍ���9�Ԃɓo�^
	Draw::LoadImage(L"Enemy_Planet_Test4.jpg", 9, TEX_SIZE_512);

	//�{�X�f��(2�X�e�[�W)��ǂݍ���10�Ԃɓo�^
	Draw::LoadImage(L"�v���C���[�f��Lv1.png", 10, TEX_SIZE_512);

	//�G�f��1(3�X�e�[�W)��ǂݍ���11�Ԃɓo�^
	Draw::LoadImage(L"Enemy_Planet_Test.jpg", 11, TEX_SIZE_512);

	//�G�f��2(3�X�e�[�W)��ǂݍ���12�Ԃɓo�^
	Draw::LoadImage(L"Enemy_Planet_Test2.jpg", 12, TEX_SIZE_512);

	//�G�f��3(3�X�e�[�W)��ǂݍ���13�Ԃɓo�^
	Draw::LoadImage(L"Enemy_Planet_Test3.jpg", 13, TEX_SIZE_512);

	//�G�f��4(3�X�e�[�W)��ǂݍ���14�Ԃɓo�^
	Draw::LoadImage(L"Enemy_Planet_Test4.jpg", 14, TEX_SIZE_512);

	//�{�X�f��(3�X�e�[�W)��ǂݍ���15�Ԃɓo�^
	Draw::LoadImage(L"�v���C���[�f��Lv1.png", 15, TEX_SIZE_512);

	//�퓬��ʈڍs���o(����)��ǂݍ���50�Ԃɓo�^
	Draw::LoadImage(L"�퓬��ʈڍs���o(����)(��).png", 50, TEX_SIZE_512);

	//���b�Z�[�W�E�C���h�E��ǂݍ���55�Ԃɓo�^
	Draw::LoadImage(L"���b�Z�[�W�E�C���h�E(��).png", 55, TEX_SIZE_512);

	//�߂�A�C�R����ǂݍ���56�Ԃɓo�^
	Draw::LoadImage(L"�߂�.png", 56, TEX_SIZE_512);

	//�X�y�V�����Z�A�C�R��(�G�ɑ�_���[�W)��ǂݍ���57�Ԃɓo�^
	Draw::LoadImage(L"�X�y�V�����Z1.png", 57, TEX_SIZE_512);

	//�X�y�V�����Z�A�C�R��(���E��)��ǂݍ���58�Ԃɓo�^
	Draw::LoadImage(L"�X�y�V�����Z2.png", 58, TEX_SIZE_512);

	//�X�y�V�����Z�A�C�R��(��莞�Ԗ��G)��ǂݍ���59�Ԃɓo�^
	Draw::LoadImage(L"�X�y�V�����Z3.png", 59, TEX_SIZE_512);

	//�X�y�V�����Z�A�C�R��(���Y�������A�b�v)��ǂݍ���60�Ԃɓo�^
	Draw::LoadImage(L"�X�y�V�����Z4.png", 60, TEX_SIZE_512);

	//�X�y�V�����Z�A�C�R��(�Z���̎m�C���A�b�v)��ǂݍ���61�Ԃɓo�^
	Draw::LoadImage(L"�X�y�V�����Z5.png", 61, TEX_SIZE_512);

	//�X�y�V�����Z�I���E�C���h�E��ǂݍ���62�Ԃɓo�^
	Draw::LoadImage(L"�X�y�V�����Z�I���E�C���h�E(��).png", 62, TEX_SIZE_512);

	//�v���C���[�f����ǂݍ���63�Ԃɓo�^
	Draw::LoadImage(L"�v���C���[�f��.png", 63, TEX_SIZE_512);
}

//�Q�[�����C�����s�����\�b�h
void CScenePreparation::Scene()
{

}