//STL�Ńo�O�@�\��OFF�ɂ���
#define _SECURE_SCL (0)
#define _HAS_ITERTOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p�w�b�_�[
//#include "SceneMain.h"
#include "GameHead.h"

//�R���X�g���N�^
CSceneTraining::CSceneTraining()
{

}

//�f�X�g���N�^
CSceneTraining::~CSceneTraining()
{

}

//�Q�[�����������\�b�h
void CSceneTraining::InitScene()
{
	//�o�͂����镶���̃O���t�B�b�N���쐬
	//Font::SetStrTex(L"");

	//�琬��ʃI�u�W�F�N�g�쐬
	CObjTraining* obj = new CObjTraining();     //�琬��ʃI�u�W�F�N�g�쐬
	Objs::InsertObj(obj, OBJ_TRAINING, 10);  //�琬��ʃI�u�W�F�N�g�o�^

	 //�w�i��ǂݍ���0�Ԃɓo�^
	Draw::LoadImage(L"�n��TEST.gif", 0, TEX_SIZE_512);

	//�_��ǂݍ���1�Ԃɓo�^
	Draw::LoadImage(L"�_TEST.png", 1, TEX_SIZE_512);

	//�v���C���[�f����ǂݍ���50�Ԃɓo�^
	Draw::LoadImage(L"Player_Planet_Test.png", 50, TEX_SIZE_512);
}

//�Q�[�����C�����s�����\�b�h
void CSceneTraining::Scene()
{

}