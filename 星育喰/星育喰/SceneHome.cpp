//STL�Ńo�O�@�\��OFF�ɂ���
#define _SECURE_SCL (0)
#define _HAS_ITERTOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p�w�b�_�[
//#include "SceneMain.h"
#include "GameHead.h"

//�R���X�g���N�^
CSceneHome::CSceneHome()
{

}

//�f�X�g���N�^
CSceneHome::~CSceneHome()
{

}

//�Q�[�����������\�b�h
void CSceneHome::InitScene()
{
	//�o�͂����镶���̃O���t�B�b�N���쐬
	//Font::SetStrTex(L"");

	//�^�C�g���I�u�W�F�N�g�쐬
	CObjHome* obj = new CObjHome();     //�z�[���I�u�W�F�N�g�쐬
	Objs::InsertObj(obj, OBJ_HOME, 10);  //�z�[���I�u�W�F�N�g�o�^

	//�w�i��ǂݍ���0�Ԃɓo�^
	Draw::LoadImage(L"TitleBackgroundTest.jpg", 0, TEX_SIZE_512);

	//��A�C�R����ǂݍ���1�Ԃɓo�^
	Draw::LoadImage(L"��TEST.png", 1, TEX_SIZE_512);

	//��A�C�R����ǂݍ���2�Ԃɓo�^
	Draw::LoadImage(L"��TEST.png", 2, TEX_SIZE_512);

	//�v���C���[�f����ǂݍ���50�Ԃɓo�^
	Draw::LoadImage(L"Player_Planet_Test.png", 50, TEX_SIZE_512);
}

//�Q�[�����C�����s�����\�b�h
void CSceneHome::Scene()
{

}