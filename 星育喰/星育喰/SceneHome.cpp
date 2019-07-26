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

	//���b�Z�[�W�\��(�`���[�g���A��)�I�u�W�F�N�g�쐬
	if (g_tutorial_progress < 20)
	{
		CObjMessage* message = new CObjMessage(g_tutorial_progress);	//���b�Z�[�W�\���I�u�W�F�N�g�쐬
		Objs::InsertObj(message, OBJ_MESSAGE, 90);	//���b�Z�[�W�\���I�u�W�F�N�g�o�^
	}
	
	////�w���v�I�u�W�F�N�g
	//CObjHelp* help = new CObjHelp(1);     //�w���v�I�u�W�F�N�g�쐬
	//Objs::InsertObj(help, OBJ_HELP, 20);  //�w���v�I�u�W�F�N�g�o�^

	//�w�i��ǂݍ���0�Ԃɓo�^
	Draw::LoadImage(L"�w�i.png", 0, TEX_SIZE_512);

	//��A�C�R����ǂݍ���1�Ԃɓo�^
	Draw::LoadImage(L"��Q.png", 1, TEX_SIZE_512);

	//��A�C�R����ǂݍ���2�Ԃɓo�^
	Draw::LoadImage(L"��Q.png", 2, TEX_SIZE_512);

	//�߂��ǂݍ���3�Ԃɓo�^
	Draw::LoadImage(L"�߂�.png", 3, TEX_SIZE_512);

	//�w���v�{�^����ǂݍ���4�Ԃɓo�^
	Draw::LoadImage(L"�w���v�{�^��.png", 4, TEX_SIZE_512);

	//�w���v�摜��ǂݍ���5�Ԃɓo�^
	Draw::LoadImage(L"�w���v�z�[��.png", 5, TEX_SIZE_512);

	//���b�Z�[�W�E�C���h�E��ǂݍ���6�Ԃɓo�^
	Draw::LoadImage(L"���b�Z�[�W�E�B���h�E.png", 6, TEX_SIZE_512);

	//�E�C���h�E01��ǂݍ���7�Ԃɓo�^
	Draw::LoadImage(L"�E�C���h�E01.png", 7, TEX_SIZE_512);

	//�|�[�Y��ʔw�i(��ʈÓ]�p)��ǂݍ���8�Ԃɓo�^
	Draw::LoadImage(L"�|�[�Y��ʔw�i.png", 8, TEX_SIZE_512);

	//�_��ǂݍ���15�Ԃɓo�^
	Draw::LoadImage(L"��ʈڍs�_.png", 15, TEX_SIZE_512);

	//20,22,24�̔ԍ��͓G�f���`��Ŏg�p���Ă���̂Ŏg�p���Ȃ��悤�ɁB

	//�y�[�W��i�߂�{�^����ǂݍ���46�Ԃɓo�^
	Draw::LoadImage(L"�y�[�W��i�߂�{�^��.png", 46, TEX_SIZE_512);

	//�v���C���[�f��Lv1��ǂݍ���50�Ԃɓo�^
	Draw::LoadImage(L"P�f��_Lv1�C��.png", 50, TEX_SIZE_512);

	//�v���C���[�f��Lv2��ǂݍ���51�Ԃɓo�^
	Draw::LoadImage(L"P�f��_Lv2�C��.png", 51, TEX_SIZE_512);

	//�v���C���[�f��Lv3��ǂݍ���52�Ԃɓo�^
	Draw::LoadImage(L"P�f��_Lv3�C��.png", 52, TEX_SIZE_512);

	//�f��HP�����摜��ǂݍ���53�Ԃɓo�^
	Draw::LoadImage(L"�f��HP.png", 53, TEX_SIZE_512);

	//�������̃X�y�V�����Z�����摜��ǂݍ���54�Ԃɓo�^
	Draw::LoadImage(L"�������̃X�y�V�����Z.png", 54, TEX_SIZE_512);

	//�������摜��ǂݍ���121�Ԃɓo�^
	Draw::LoadImage(L"�������W.png", 121, TEX_SIZE_512);
	
	//���ݑ������̃X�y�V�����Z�����摜�S�Ă�ǂݍ��ވׂɁA
	//�ǂݍ��ݔԍ�127�Ԃ��g�p���Ă���̂Ŏg��Ȃ��悤�ɁI

	//��b����ǂݍ���189�Ԃɓo�^
	Draw::LoadImage(L"��b���.png", 189, TEX_SIZE_512);

	//�퓬��x10(�R�c)��ǂݍ���190�Ԃɓo�^
	Draw::LoadImage(L"�퓬��x10.png", 190, TEX_SIZE_512);

	//���摜��ǂݍ���191�Ԃɓo�^
	Draw::LoadImage(L"���.png", 191, TEX_SIZE_512);

	//float v = Audio::VolumeMaster(0);
	//v = Audio::VolumeMaster((0.0 - v));

	//���y�ǂݍ���
	Audio::LoadAudio(0, L"�����̎R.wav", BACK_MUSIC);

	//SE�ǂݍ���
	//�I��
	Audio::LoadAudio(1, L"�I�����U�蕪���A�b�v�R.wav", EFFECT);

	//�߂�
	Audio::LoadAudio(2, L"�߂違�U�蕪���_�E���S.wav", EFFECT);

	//���y�X�^�[�g
	Audio::Start(0);

}

//�Q�[�����C�����s�����\�b�h
void CSceneHome::Scene()
{

}