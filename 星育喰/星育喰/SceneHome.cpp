//STL�Ńo�O�@�\��OFF�ɂ���
#define _SECURE_SCL (0)
#define _HAS_ITERTOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\Audio.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p�w�b�_�[
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
	//�z�[���I�u�W�F�N�g�쐬
	CObjHome* obj = new CObjHome();     //�z�[���I�u�W�F�N�g�쐬
	Objs::InsertObj(obj, OBJ_HOME, 10);  //�z�[���I�u�W�F�N�g�o�^

	//�w�i��ǂݍ���0�Ԃɓo�^
	Draw::LoadImage(L"TitleBackgroundTest.jpg", 0, TEX_SIZE_512);

	//��A�C�R����ǂݍ���1�Ԃɓo�^
	Draw::LoadImage(L"��TEST.png", 1, TEX_SIZE_512);

	//��A�C�R����ǂݍ���2�Ԃɓo�^
	Draw::LoadImage(L"��TEST.png", 2, TEX_SIZE_512);

	//�_��ǂݍ���15�Ԃɓo�^
	Draw::LoadImage(L"���߉_.png", 15, TEX_SIZE_512);

	//�v���C���[�f����ǂݍ���50�Ԃɓo�^
	Draw::LoadImage(L"�v���C���[�f��.png", 50, TEX_SIZE_512);

	//���y�ǂݍ���
	//Audio::LoadAudio(0, L"Blue.wav", BACK_MUSIC);
	//Audio::LoadAudio(0, L"Growing.wav", BACK_MUSIC);
	//Audio::LoadAudio(0, L"����̔�.wav", BACK_MUSIC);
	//Audio::LoadAudio(0, L"�����̎R.wav", BACK_MUSIC);

	//��5/20�ɋN��������̃p�\�R����Audio�̓ǂݎ��ᔽ�œ����Ȃ��Ȃ�o�O�A
	//��(���)�̃p�\�R���ł��N�����̂ŁA�ȉ��̏�������U�R�����g�A�E�g���܂����B
	//���R�����g�A�E�g��A���퓮����m�F�ς�
	////�o�b�N�~���[�W�b�N
	//float v = Audio::VolumeMaster(0);
	//v = Audio::VolumeMaster((1.0 - v));

	////���y�X�^�[�g
	//Audio::Start(0);

}

//�Q�[�����C�����s�����\�b�h
void CSceneHome::Scene()
{

}