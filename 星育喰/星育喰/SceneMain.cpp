//STL�f�o�b�N�@�\��OFF�ɂ���
#define _SECURE_SCL	(0)
#define _HAS_ITERATOR_DEBUGGING	(0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\DrawTexture.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p�w�b�_�[
#include "SceneMain.h"
#include "GameHead.h"

//�R���X�g���N�^
CSceneMain::CSceneMain()
{

}

//�f�X�g���N�^
CSceneMain::~CSceneMain()
{

}

//�Q�[�����C�����������\�b�h
void CSceneMain::InitScene()
{
	//test�p�O���O���t�B�b�N�ǂݍ���0�Ԃɓo�^
	Draw::LoadImage(L"�w�i.png", 1, TEX_SIZE_512);

	//test�p�����O���t�B�b�N�ǂݍ���1�Ԃɓo�^
	Draw::LoadImage(L"����.png", 2, TEX_SIZE_512);

	//�w�i�I�u�W�F�N�g�쐬
	CObjFacility* facility = new CObjFacility();
	Objs::InsertObj(facility, OBJ_FACILITY, 1);

	//�����I�u�W�F�N�g�쐬
	CObjBuild* build = new CObjBuild();
	Objs::InsertObj(build, OBJ_BUILD, 2);
}

//�Q�[�����C�����s�����\�b�h
void CSceneMain::Scene()
{

}