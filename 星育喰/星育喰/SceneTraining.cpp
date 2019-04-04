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

#include <stdlib.h>
#include <time.h>

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

	srand(time(NULL));//�����_������������
	
	//���Z���̏���X,Y���W�������_���Ŏ擾
	//����3�񂸂̌J��Ԃ��񐔂����A
	//�J��Ԃ��񐔂͏Z�������Ǘ�����O���[�o���ϐ������
	//�`�悷��Z���̐����s���悤�Ɍ�ɕύX���Ă����B

	//Human�̏���X���W�擾
	for (int i = 0; i < 3; i++)
	{
		m_ini_hx[i] = rand() % 401 + 400;//400�`800�̒l�������_���擾���AHuman�̏���X���W�Ƃ���B
	}
	//Human�̏���Y���W�擾
	for (int i = 0; i < 3; i++)
	{
		m_ini_hy[i] = rand() % 201 + 250;//250�`450�̒l�������_���擾���AHuman�̏���Y���W�Ƃ���B
	}

	//�Z���I�u�W�F�N�g
	//����3�񂸂̌J��Ԃ��񐔂����A
	//�J��Ԃ��񐔂͏Z�������Ǘ�����O���[�o���ϐ������
	//�`�悷��Z���̐����s���悤�Ɍ�ɕύX���Ă����B
	for (int i = 0; i < 3; i++)
	{
		CObjHuman* obj_human = new CObjHuman(m_ini_hx[i], m_ini_hy[i]);	//�Z���I�u�W�F�N�g�쐬
		Objs::InsertObj(obj_human, OBJ_HUMAN, 15);						//�Z���I�u�W�F�N�g�o�^
	}

	
	//�琬��ʃI�u�W�F�N�g
	CObjTraining* obj = new CObjTraining();     //�琬��ʃI�u�W�F�N�g�쐬
	Objs::InsertObj(obj, OBJ_TRAINING, 10);		//�琬��ʃI�u�W�F�N�g�o�^

	//���ɃI�u�W�F�N�g							
	CObjBarracks* obj1 = new CObjBarracks();	//���ɃI�u�W�F�N�g�쐬
	Objs::InsertObj(obj1, OBJ_BARRACKS, 20);	//���ɃI�u�W�F�N�g�o�^

	//�������I�u�W�F�N�g							
	CObjInstitute* obj2 = new CObjInstitute();	//�������I�u�W�F�N�g�쐬
	Objs::InsertObj(obj2, OBJ_INSTITUTE, 20);	//�������I�u�W�F�N�g�o�^

	//�_���o�I�u�W�F�N�g(�_���oOUT)
	CObjCloud_Effect* obj_cloud = new CObjCloud_Effect(false);	//�_���o�I�u�W�F�N�g�쐬
	Objs::InsertObj(obj_cloud, OBJ_CLOUD, 100);					//�_���o�I�u�W�F�N�g�o�^


	//�w�i��ǂݍ���0�Ԃɓo�^
	Draw::LoadImage(L"�n��TEST.gif", 0, TEX_SIZE_512);

	//�߂�A�C�R����ǂݍ���1�Ԃɓo�^
	Draw::LoadImage(L"�߂�.png", 1, TEX_SIZE_512);

	//���ɂ�ǂݍ���2�Ԃɓo�^
	Draw::LoadImage(L"����(��).jfif", 2, TEX_SIZE_512);

	//��������ǂݍ���3�Ԃɓo�^
	Draw::LoadImage(L"������.png", 3, TEX_SIZE_512);

	//�~�T�C��(��)��ǂݍ���4�Ԃɓo�^
	Draw::LoadImage(L"�~�T�C��(��).png", 4, TEX_SIZE_512);

	//�Z����ǂݍ���10�Ԃɓo�^
	Draw::LoadImage(L"Human.png", 10, TEX_SIZE_512);

	//�_��ǂݍ���15�Ԃɓo�^
	Draw::LoadImage(L"���߉_.png", 15, TEX_SIZE_512);

	//�D�F�E�C���h�E(��)��ǂݍ���20�Ԃɓo�^
	Draw::LoadImage(L"�D�F�E�C���h�E(��).png", 20, TEX_SIZE_512);

	//���b�Z�[�W�E�C���h�E(��)��ǂݍ���21�Ԃɓo�^
	Draw::LoadImage(L"���b�Z�[�W�E�C���h�E(��).png", 21, TEX_SIZE_512);

	//�{��LVUP��ǂݍ���22�Ԃɓo�^
	Draw::LoadImage(L"�{��LVUP.png", 22, TEX_SIZE_512);

	//�Z���U�蕪��UP��ǂݍ���23�Ԃɓo�^
	Draw::LoadImage(L"���ɐU�蕪��UP.png", 23, TEX_SIZE_512);

	//�Z���U�蕪��DOWN��ǂݍ���24�Ԃɓo�^
	Draw::LoadImage(L"���ɐU�蕪��DOWN.png", 24, TEX_SIZE_512);

	//�~�T�C���{�^��(��)��ǂݍ���25�Ԃɓo�^
	Draw::LoadImage(L"�~�T�C���{�^��(��).png", 25, TEX_SIZE_512);

	//����|�b�h�{�^��(��)��ǂݍ���26�Ԃɓo�^
	Draw::LoadImage(L"����|�b�h�{�^��(��).png", 26, TEX_SIZE_512);

	//�v���C���[�f����ǂݍ���50�Ԃɓo�^
	Draw::LoadImage(L"�v���C���[�f��.png", 50, TEX_SIZE_512);
}

//�Q�[�����C�����s�����\�b�h
void CSceneTraining::Scene()
{

}