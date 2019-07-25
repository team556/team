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
CSceneTitle::CSceneTitle()
{

}

//�f�X�g���N�^
CSceneTitle::~CSceneTitle()
{

}

//�Q�[�����������\�b�h
void CSceneTitle::InitScene()
{
	//�o�͂����镶���̃O���t�B�b�N���쐬
	//Font::SetStrTex(L"");

	//�^�C�g���I�u�W�F�N�g�쐬
	CObjTitle* obj = new CObjTitle();     //�^�C�g���I�u�W�F�N�g�쐬
	Objs::InsertObj(obj, OBJ_TITLE, 10);  //�^�C�g���I�u�W�F�N�g�o�^

	//�w�i��ǂݍ���0�Ԃɓo�^
	Draw::LoadImage(L"�w�i.png", 0, TEX_SIZE_512);

	//�^�C�g�����S
	Draw::LoadImage(L"�^�C�g�����S.png", 1, TEX_SIZE_512);

	//�|�[�Y��ʔw�i��ǂݍ���2�Ԃɓo�^
	Draw::LoadImage(L"�|�[�Y��ʔw�i.png", 2, TEX_SIZE_512);

	//20,22,24�̔ԍ��͓G�f���`��Ŏg�p���Ă���̂Ŏg�p���Ȃ��悤�ɁB

	//�v���C���[�f��Lv1��ǂݍ���50�Ԃɓo�^
	Draw::LoadImage(L"P�f��_Lv1�C��.png", 50, TEX_SIZE_512);

	//�v���C���[�f��Lv2��ǂݍ���51�Ԃɓo�^
	//Draw::LoadImage(L"�v���C���[�f��.png", 51, TEX_SIZE_512);

	////�v���C���[�f��Lv3��ǂݍ���52�Ԃɓo�^
	//Draw::LoadImage(L"�v���C���[�f��.png", 52, TEX_SIZE_512);

	//�N���b�N�ŃX�^�[�g�����摜��53�Ԃɓo�^
	Draw::LoadImage(L"�N���b�N�ŃX�^�[�g.png", 53, TEX_SIZE_512);

	//�f�[�^�����{�^���摜��54�Ԃɓo�^
	Draw::LoadImage(L"�f�[�^�����{�^��.png", 54, TEX_SIZE_512);

	//�͂������摜�ǂݍ���55�Ԃɓo�^
	Draw::LoadImage(L"�͂�.png", 55, TEX_SIZE_512);

	//�����������摜�ǂݍ���56�Ԃɓo�^
	Draw::LoadImage(L"������.png", 56, TEX_SIZE_512);

	//�E�C���h�E01��ǂݍ���57�Ԃɓo�^
	Draw::LoadImage(L"�E�C���h�E01.png", 57, TEX_SIZE_512);

	//�������W��ǂݍ���121�Ԃɓo�^
	Draw::LoadImage(L"�������W.png", 121, TEX_SIZE_512);



	//���y�ǂݍ���
	Audio::LoadAudio(0, L"�����̎R.wav", BACK_MUSIC);

	//SE�ǂݍ���
	//�I��
	Audio::LoadAudio(1, L"�I�����U�蕪���A�b�v�R.wav", EFFECT);

	//�߂�
	Audio::LoadAudio(2, L"�߂違�U�蕪���_�E���S.wav", EFFECT);

	//�f�[�^������
	Audio::LoadAudio(3, L"�H�ׂ鉹.wav", EFFECT);

	////���y�X�^�[�g
	Audio::Start(0);
}

//�Q�[�����C�����s�����\�b�h
void CSceneTitle::Scene()
{

}