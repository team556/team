//STL�Ńo�O�@�\��OFF�ɂ���
#define _SECURE_SCL (0)
#define _HAS_ITERTOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL\DrawTexture.h"
#include "GameL\Audio.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p�w�b�_�[
#include "SceneNameInput.h"
#include "GameHead.h"

//�R���X�g���N�^
CSceneNameInput::CSceneNameInput()
{}
//�f�X�g���N�^
CSceneNameInput::~CSceneNameInput()
{}
//�Q�[�����C�����������\�b�h
void CSceneNameInput::InitScene()
{
	//�O���t�B�b�N�o�^
	Draw::LoadImage(L"w.png", 0, TEX_SIZE_64);
	//���摜����Ԗڂɓo�^
	Draw::LoadImage(L"�Ȃ܂�.png", 1, TEX_SIZE_64);

	CObjNameInput*obj = new CObjNameInput();
	Objs::InsertObj(obj, OBJ_NAME_INPUT, 1);
}
//�Q�[�����C�����s�����\�b�h
void CSceneNameInput::Scene()
{}
