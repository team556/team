//STL�Ńo�O�@�\��OFF�ɂ���
#define _SECURE_SCL (0)
#define _HAS_ITERTOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL\DrawTexture.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p�w�b�_�[
//#include "SceneMain.h"
#include "GameHead.h"

//�R���X�g���N�^
CSceneTest::CSceneTest()
{

}

//�f�X�g���N�^
CSceneTest::~CSceneTest()
{

}

//�Q�[�����������\�b�h
void CSceneTest::InitScene()
{
	//�O���O���t�B�b�N��ǂݍ���0�Ԃɓo�^(512�~512�s�N�Z��)
	Draw::LoadImage(L"Human.png", 0, TEX_SIZE_512);

	//�o�͂����镶���̃O���t�B�b�N���쐬
	//Font::SetStrTex(L"");

	//�e�X�g�I�u�W�F�N�g�쐬
	//CObjTest* obj = new CObjTest();		//�^�C�g���I�u�W�F�N�g�쐬
	//Objs::InsertObj(obj, OBJ_TEST, 10);	//�^�C�g���I�u�W�F�N�g�o�^

	//�Z���I�u�W�F�N�g�쐬
	CObjHuman* obj0 = new CObjHuman(100,100);	//�^�C�g���I�u�W�F�N�g�쐬
	Objs::InsertObj(obj0, OBJ_TEST, 10);		//�^�C�g���I�u�W�F�N�g�o�^
}

//�Q�[�����C�����s�����\�b�h
void CSceneTest::Scene()
{

}