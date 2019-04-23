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

	//�G�f��1��ǂݍ���1�Ԃɓo�^
	Draw::LoadImage(L"Enemy_Planet_Test.jpg", 1, TEX_SIZE_512);

	//�G�f��2��ǂݍ���2�Ԃɓo�^
	Draw::LoadImage(L"Enemy_Planet_Test2.jpg", 2, TEX_SIZE_512);

	//�G�f��3��ǂݍ���3�Ԃɓo�^
	Draw::LoadImage(L"Enemy_Planet_Test3.jpg", 3, TEX_SIZE_512);

	//�G�f��4��ǂݍ���4�Ԃɓo�^
	Draw::LoadImage(L"Enemy_Planet_Test4.jpg", 4, TEX_SIZE_512);

	//�v���C���[�f����ǂݍ���63�Ԃɓo�^
	Draw::LoadImage(L"�v���C���[�f��.png", 63, TEX_SIZE_512);
}

//�Q�[�����C�����s�����\�b�h
void CScenePreparation::Scene()
{

}