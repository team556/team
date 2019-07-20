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

	//�w���v�I�u�W�F�N�g
	CObjHelp* help = new CObjHelp(3);     //�w���v�I�u�W�F�N�g�쐬
	Objs::InsertObj(help, OBJ_HELP, 20);  //�w���v�I�u�W�F�N�g�o�^

	//�w�i��ǂݍ���0�Ԃɓo�^
	Draw::LoadImage(L"�w�i.png", 0, TEX_SIZE_512);

	//�G�f��1(1�X�e�[�W)��ǂݍ���1�Ԃɓo�^
	Draw::LoadImage(L"lv1x3.png", 1, TEX_SIZE_512);

	//�G�f��2(1�X�e�[�W)��ǂݍ���2�Ԃɓo�^
	Draw::LoadImage(L"���A�C.png", 2, TEX_SIZE_512);

	//�G�f��3(1�X�e�[�W)��ǂݍ���3�Ԃɓo�^
	Draw::LoadImage(L"���f��.png", 3, TEX_SIZE_512);

	//�G�f��4(1�X�e�[�W)��ǂݍ���4�Ԃɓo�^
	Draw::LoadImage(L"lv2x3.png", 4, TEX_SIZE_512);

	//�{�X�f��(1�X�e�[�W)��ǂݍ���5�Ԃɓo�^
	Draw::LoadImage(L"lv4x3.png", 5, TEX_SIZE_512);

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
	Draw::LoadImage(L"�p���_��.png", 15, TEX_SIZE_512);

	//�퓬��ʈڍs���o(����)��ǂݍ���18�Ԃɓo�^
	Draw::LoadImage(L"�퓬��ʈڍs���o(����)(��).png", 18, TEX_SIZE_512);

	//�w���v�{�^����ǂݍ���21�Ԃɓo�^
	Draw::LoadImage(L"�w���v�{�^��.png", 21, TEX_SIZE_512);

	//�w���v�摜��ǂݍ���22�Ԃɓo�^
	Draw::LoadImage(L"�w���v�퓬����.png", 22, TEX_SIZE_512);

	//�w���v�摜��ǂݍ���23�Ԃɓo�^
	Draw::LoadImage(L"�w���v�퓬.png", 23, TEX_SIZE_512);
	
	//�y�[�W��i�߂�{�^����ǂݍ���46�Ԃɓo�^
	Draw::LoadImage(L"�y�[�W��i�߂�{�^��(��).png", 46, TEX_SIZE_512);

	//�v���C���[�f��Lv1��ǂݍ���47�Ԃɓo�^
	Draw::LoadImage(L"P�f��_Lv1.png", 47, TEX_SIZE_512);

	//�v���C���[�f��Lv2��ǂݍ���48�Ԃɓo�^
	Draw::LoadImage(L"P�f��_Lv2.png", 48, TEX_SIZE_512);

	//�v���C���[�f��Lv3��ǂݍ���49�Ԃɓo�^
	Draw::LoadImage(L"P�f��_Lv3.png", 49, TEX_SIZE_512);

	//���b�Z�[�W�E�C���h�E��ǂݍ���55�Ԃɓo�^
	Draw::LoadImage(L"���b�Z�[�W�E�C���h�E(��).png", 55, TEX_SIZE_512);

	//�߂�A�C�R����ǂݍ���56�Ԃɓo�^
	Draw::LoadImage(L"�߂�.png", 56, TEX_SIZE_512);

	//�X�y�V�����Z�A�C�R��(Explosion)��ǂݍ���57�Ԃɓo�^
	Draw::LoadImage(L"�X�y�V�����Z1.png", 57, TEX_SIZE_512);

	//�X�y�V�����Z�A�C�R��(Fracture_Ray)��ǂݍ���58�Ԃɓo�^
	Draw::LoadImage(L"�X�y�V�����Z2.png", 58, TEX_SIZE_512);

	//�X�y�V�����Z�A�C�R��(Immortality)��ǂݍ���59�Ԃɓo�^
	Draw::LoadImage(L"�X�y�V�����Z3.png", 59, TEX_SIZE_512);

	//�X�y�V�����Z�A�C�R��(���~�b�g�u���C�N)��ǂݍ���60�Ԃɓo�^
	Draw::LoadImage(L"�X�y�V�����Z4.png", 60, TEX_SIZE_512);

	//�X�y�V�����Z�A�C�R��(�X�e���C�h���^)��ǂݍ���61�Ԃɓo�^
	Draw::LoadImage(L"�X�y�V�����Z5.png", 61, TEX_SIZE_512);

	//�X�y�V�����Z�I���E�C���h�E��ǂݍ���62�Ԃɓo�^
	Draw::LoadImage(L"�X�y�V�����Z�I���E�C���h�E(��).png", 62, TEX_SIZE_512);

	//����Șf���o���������摜�ǂݍ���63�Ԃɓo�^
	Draw::LoadImage(L"����Șf���o����.png", 63, TEX_SIZE_512);

	//����Șf���ڋ߂܂ŕ����摜�ǂݍ���64�Ԃɓo�^
	Draw::LoadImage(L"����Șf���ڋ߂܂�.png", 64, TEX_SIZE_512);

	//�򂤁H�����摜�ǂݍ���65�Ԃɓo�^
	Draw::LoadImage(L"�򂤁H.png", 65, TEX_SIZE_512);

	//�͂������摜�ǂݍ���66�Ԃɓo�^
	Draw::LoadImage(L"�͂�.png", 66, TEX_SIZE_512);

	//�����������摜�ǂݍ���67�Ԃɓo�^
	Draw::LoadImage(L"������.png", 67, TEX_SIZE_512);

	//�X�y�V�����Z�I�𕶎��摜�ǂݍ���68�Ԃɓo�^
	Draw::LoadImage(L"�X�y�V�����Z�I��.png", 68, TEX_SIZE_512);

	//����3�̕����摜�ǂݍ���69�Ԃɓo�^
	Draw::LoadImage(L"����3��.png", 69, TEX_SIZE_512);

	//����2�̕����摜�ǂݍ���70�Ԃɓo�^
	Draw::LoadImage(L"����2��.png", 70, TEX_SIZE_512);

	//����1�̕����摜�ǂݍ���71�Ԃɓo�^
	Draw::LoadImage(L"����1��.png", 71, TEX_SIZE_512);

	//����0�̕����摜�ǂݍ���72�Ԃɓo�^
	Draw::LoadImage(L"����0��.png", 72, TEX_SIZE_512);

	//���摜�ǂݍ���73�Ԃɓo�^(���m�ȁ��摜�ɕύX�\��)
	//Draw::LoadImage(L"��ʈڍs��.png", 73, TEX_SIZE_512);

	//����s�\�����摜74�Ԃɓo�^
	Draw::LoadImage(L"����s�\.png", 74, TEX_SIZE_512);

	//���b�Z�[�W�E�B���h�E�摜89�Ԃɓo�^
	Draw::LoadImage(L"�E�C���h�E01.png", 89, TEX_SIZE_512);

	//�������摜��ǂݍ���121�Ԃɓo�^
	Draw::LoadImage(L"�������W.png", 121, TEX_SIZE_512);

	//�ڍא����摜��ǂݍ��ވׂɁA
	//�ǂݍ��ݔԍ�122�`127�Ԃ��g�p���Ă���̂�
	//���̔ԍ��͎g��Ȃ��悤�ɁI





	//�f���F�����摜94�Ԃɓo�^
	Draw::LoadImage(L"�f���F.png", 94, TEX_SIZE_512);

	//�{���{���������摜95�Ԃɓo�^
	Draw::LoadImage(L"�{���{����.png", 95, TEX_SIZE_512);

	//O�㍰�����摜96�Ԃɓo�^
	Draw::LoadImage(L"O�㍰.png", 96, TEX_SIZE_512);

	//�Đ������摜97�Ԃɓo�^
	Draw::LoadImage(L"�Đ�.png", 97, TEX_SIZE_512);

	//�A���C�����摜98�Ԃɓo�^
	Draw::LoadImage(L"�A���C.png", 98, TEX_SIZE_512);

	//�R�����[�e�����摜99�Ԃɓo�^
	Draw::LoadImage(L"�R�����[�e.png", 99, TEX_SIZE_512);

	//�A�}�e���X�����摜100�Ԃɓo�^
	Draw::LoadImage(L"�A�}�e���X.png", 100, TEX_SIZE_512);

	//���y�ǂݍ���
	Audio::LoadAudio(0, L"�����̎R.wav", BACK_MUSIC);

	//�����y�����������͂����̃R�����g�A�E�g�O���Ή���0�̖��߂ƂȂ�A������B
	//�������A�Ō�̃v�b�V���O�ɂ͕K���R�����g�A�E�g�������ĉ��y������Ԃɖ߂��悤�ɁI
	//float v = Audio::VolumeMaster(0);
	//v = Audio::VolumeMaster((0.0 - v));

	//SE�ǂݍ���
	//�I��
	Audio::LoadAudio(1, L"�I�����U�蕪���A�b�v�R.wav", EFFECT);

	//�߂�
	Audio::LoadAudio(2, L"�߂違�U�蕪���_�E���S.wav", EFFECT);

	////���y�X�^�[�g
	Audio::Start(0);
}

//�Q�[�����C�����s�����\�b�h
void CScenePreparation::Scene()
{

}