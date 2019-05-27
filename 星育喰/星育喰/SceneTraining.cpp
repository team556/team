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
		CObjHuman* obj_human = new CObjHuman(m_ini_hx[i], m_ini_hy[i], i);	//�Z���I�u�W�F�N�g�쐬
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

	//�q�ɃI�u�W�F�N�g�쐬
	CObjWarehouse* warehouse = new CObjWarehouse();
	Objs::InsertObj(warehouse, OBJ_WAREHOUSE, 20);

	//�w���v�u�W�F�N�g
	CObjHelp* hlp = new CObjHelp();     //�w���v�u�W�F�N�g�쐬
	Objs::InsertObj(hlp, OBJ_HELP, 20);  //�w���v�u�W�F�N�g�o�^


	//�w�i��ǂݍ���0�Ԃɓo�^
	Draw::LoadImage(L"�n��TEST.gif", 0, TEX_SIZE_512);

	//�߂�A�C�R����ǂݍ���1�Ԃɓo�^
	Draw::LoadImage(L"�߂�.png", 1, TEX_SIZE_512);

	//����Lv1��ǂݍ���2�Ԃɓo�^
	Draw::LoadImage(L"����Lv1.png", 2, TEX_SIZE_512);

	//������Lv1��ǂݍ���3�Ԃɓo�^
	Draw::LoadImage(L"������Lv1.png", 3, TEX_SIZE_512);

	//�~�T�C��(��)��ǂݍ���4�Ԃɓo�^
	Draw::LoadImage(L"�~�T�C��.png", 4, TEX_SIZE_512);

	//����Lv2��ǂݍ���5�Ԃɓo�^
	Draw::LoadImage(L"����Lv2.png", 5, TEX_SIZE_512);

	//������Lv2��ǂݍ���6�Ԃɓo�^
	Draw::LoadImage(L"������Lv2.png", 6, TEX_SIZE_512);

	//����Lv3��ǂݍ���8�Ԃɓo�^
	Draw::LoadImage(L"����Lv3.png", 8, TEX_SIZE_512);

	//������Lv3��ǂݍ���9�Ԃɓo�^
	Draw::LoadImage(L"������Lv3.png", 9, TEX_SIZE_512);

	//�Z����ǂݍ���10�Ԃɓo�^
	Draw::LoadImage(L"Human.png", 10, TEX_SIZE_512);

	//�_��ǂݍ���15�Ԃɓo�^
	Draw::LoadImage(L"���߉_.png", 15, TEX_SIZE_512);

	//�v���C���[�f����ǂݍ���16�Ԃɓo�^
	Draw::LoadImage(L"�v���C���[�f��.png", 16, TEX_SIZE_512);

	//�D�F�E�C���h�E(��)��ǂݍ���20�Ԃɓo�^
	Draw::LoadImage(L"�D�F�E�C���h�E(��).png", 20, TEX_SIZE_512);

	//���b�Z�[�W�E�C���h�E��ǂݍ���21�Ԃɓo�^
	Draw::LoadImage(L"���b�Z�[�W�E�C���h�E(��).png", 21, TEX_SIZE_512);

	//�{��LVUP��ǂݍ���22�Ԃɓo�^
	Draw::LoadImage(L"�{��LVUP.png", 22, TEX_SIZE_512);

	//�Z���U�蕪��UP��ǂݍ���23�Ԃɓo�^
	Draw::LoadImage(L"���ɐU�蕪��UP.png", 23, TEX_SIZE_512);

	//�Z���U�蕪��DOWN��ǂݍ���24�Ԃɓo�^
	Draw::LoadImage(L"���ɐU�蕪��DOWN.png", 24, TEX_SIZE_512);

	//�~�T�C���{�^��(��)��ǂݍ���25�Ԃɓo�^
	Draw::LoadImage(L"�~�T�C���{�^��.png", 25, TEX_SIZE_512);

	//����|�b�h�{�^��(��)��ǂݍ���26�Ԃɓo�^
	Draw::LoadImage(L"����|�b�h�{�^��.png", 26, TEX_SIZE_512);

	//test�p�q�ɉ摜�ǂݍ���27�Ԃɓo�^
	Draw::LoadImage(L"�q��.png", 27, TEX_SIZE_512);

	//���ޑI���{�^���摜�ǂݍ���28�Ԃɓo�^
	Draw::LoadImage(L"���ޑI���{�^��.png", 28 , TEX_SIZE_512);

	//�Z���I���{�^���摜�ǂݍ���29�Ԃɓo�^
	Draw::LoadImage(L"�Z���I���{�^��.png", 29, TEX_SIZE_512);

	//�X�y�V�����Z�I���{�^���摜�ǂݍ���30�Ԃɓo�^
	Draw::LoadImage(L"�X�y�V�����Z�I���{�^��.png", 30, TEX_SIZE_512);

	//�����I���{�^���摜�ǂݍ���31�Ԃɓo�^
	Draw::LoadImage(L"�����I���{�^��.png", 31, TEX_SIZE_512);

	//���ރ{�^���I����̉�ʔw�i�摜32�Ԃɓo�^
	Draw::LoadImage(L"w.png", 32 , TEX_SIZE_512);

	//����(�؍�)�摜33�Ԃɓo�^
	Draw::LoadImage(L"�؍�.png", 33, TEX_SIZE_512);

	//����(�S)�摜34�Ԃɓo�^
	Draw::LoadImage(L"�S.png", 34, TEX_SIZE_512);

	//����(��)�摜35�Ԃɓo�^
	Draw::LoadImage(L"��.png", 35, TEX_SIZE_512);

	//����(�v���X�`�b�N)�摜36�Ԃɓo�^
	Draw::LoadImage(L"�v���X�`�b�N.png", 36, TEX_SIZE_512);

	//����(�A���~�j�E��)�摜37�Ԃɓo�^
	Draw::LoadImage(L"�A���~�j�E��.png", 37, TEX_SIZE_512);

	//����(�K�X)�摜38�Ԃɓo�^
	Draw::LoadImage(L"�K�X.png", 38, TEX_SIZE_512);

	//����(���A���^��)�摜39�Ԃɓo�^
	Draw::LoadImage(L"���A���^��.png", 39, TEX_SIZE_512);

	//�X�y�V�����Z1�摜40�Ԃɓo�^
	Draw::LoadImage(L"�X�y�V�����Z1.png", 40, TEX_SIZE_512);

	//�X�y�V�����Z2�摜41�Ԃɓo�^
	Draw::LoadImage(L"�X�y�V�����Z2.png", 41, TEX_SIZE_512);

	//�X�y�V�����Z3�摜42�Ԃɓo�^
	Draw::LoadImage(L"�X�y�V�����Z3.png", 42, TEX_SIZE_512);

	//�X�y�V�����Z4�摜43�Ԃɓo�^
	Draw::LoadImage(L"�X�y�V�����Z4.png", 43, TEX_SIZE_512);

	//�X�y�V�����Z5�摜44�Ԃɓo�^
	Draw::LoadImage(L"�X�y�V�����Z5.png", 44, TEX_SIZE_512);

	//�X�y�V�����Z���b�Z�[�W�E�B���h�E�摜45�Ԃɓo�^
	Draw::LoadImage(L"�X�y�V�����Z���b�Z�[�W�E�B���h�E.png", 45, TEX_SIZE_512);

	//�p���[����Lv.1�̉摜��ǂݍ���49�Ԃɓo�^
	Draw::LoadImage(L"�p���[Lv1.png", 49, TEX_SIZE_512);

	//�p���[����Lv.2�̉摜��ǂݍ���50�Ԃɓo�^
	Draw::LoadImage(L"�p���[Lv2.png", 50, TEX_SIZE_512);

	//�p���[����Lv.3�̉摜��ǂݍ���51�Ԃɓo�^
	Draw::LoadImage(L"�p���[Lv3.png", 51, TEX_SIZE_512);

	//�f�B�t�F���X����Lv.1�̉摜��ǂݍ���52�Ԃɓo�^
	Draw::LoadImage(L"�f�B�t�F���XLv1.png", 52, TEX_SIZE_512);

	//�f�B�t�F���X����Lv.2�̉摜��ǂݍ���53�Ԃɓo�^
	Draw::LoadImage(L"�f�B�t�F���XLv2.png", 53, TEX_SIZE_512);

	//�f�B�t�F���X����Lv.3�̉摜��ǂݍ���54�Ԃɓo�^
	Draw::LoadImage(L"�f�B�t�F���XLv3.png", 54, TEX_SIZE_512);

	//�X�s�[�h����Lv.1�̉摜��ǂݍ���55�Ԃɓo�^
	Draw::LoadImage(L"�X�s�[�hLv1.png", 55, TEX_SIZE_512);

	//�X�s�[�h����Lv.2�̉摜��ǂݍ���56�Ԃɓo�^
	Draw::LoadImage(L"�X�s�[�hLv2.png", 56, TEX_SIZE_512);

	//�X�s�[�h����Lv.3�̉摜��ǂݍ���57�Ԃɓo�^
	Draw::LoadImage(L"�X�s�[�hLv3.png", 57, TEX_SIZE_512);

	//�o�����X����Lv.1�̉摜��ǂݍ���58�Ԃɓo�^
	Draw::LoadImage(L"�o�����XLv1.png", 58, TEX_SIZE_512);

	//�o�����X����Lv.2�̉摜��ǂݍ���59�Ԃɓo�^
	Draw::LoadImage(L"�o�����XLv2.png", 59, TEX_SIZE_512);

	//�o�����X����Lv.3�̉摜��ǂݍ���60�Ԃɓo�^
	Draw::LoadImage(L"�o�����XLv3.png", 60, TEX_SIZE_512);

	//�|�b�hLv.1�̉摜��ǂݍ���61�Ԃɓo�^
	Draw::LoadImage(L"�|�b�hLv1.png", 61, TEX_SIZE_512);

	//�|�b�hLv.2�̉摜��ǂݍ���62�Ԃɓo�^
	Draw::LoadImage(L"�|�b�hLv2.png", 62, TEX_SIZE_512);

	//�|�b�hLv.3�̉摜��ǂݍ���63�Ԃɓo�^
	Draw::LoadImage(L"�|�b�hLv3.png", 63, TEX_SIZE_512);

	//�w���v�{�^����ǂݍ���64�Ԃɓo�^
	Draw::LoadImage(L"�w���v�{�^��.png", 64, TEX_SIZE_512);

	//�߂��ǂݍ���65�Ԃɓo�^
	Draw::LoadImage(L"�߂�.png", 65, TEX_SIZE_512);

	//�w���v�摜��ǂݍ���66�Ԃɓo�^
	Draw::LoadImage(L"�w���v�琬.png", 66, TEX_SIZE_512);

	//���y�ǂݍ���
	//Audio::LoadAudio(0, L"�����Ƃ�����.wav", BACK_MUSIC);
	//Audio::LoadAudio(0, L"���g���E�n�s�l�X.wav", BACK_MUSIC);
	//Audio::LoadAudio(0, L"���A���K.wav", BACK_MUSIC);

	//SE�ǂݍ���
	//Audio::LoadAudio(1, L"�I���{�^����", EFFECT);
	//Audio::LoadAudio(2, L"�߂�{�^����", EFFECT);
	//Audio::LoadAudio(3, L"�{�݃��x���A�b�v��", EFFECT);
	//Audio::LoadAudio(4, L"", EFFECT);
	//Audio::LoadAudio(5, L"", EFFECT);

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
void CSceneTraining::Scene()
{

}