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
	//srand(time(NULL));//�����_������������
	//
	////���Z���̏���X,Y���W�������_���Ŏ擾
	////����3�񂸂̌J��Ԃ��񐔂����A
	////�J��Ԃ��񐔂͏Z�������Ǘ�����O���[�o���ϐ������
	////�`�悷��Z���̐����s���悤�Ɍ�ɕύX���Ă����B

	////Human�̏���X���W�擾
	//for (int i = 0; i < 3; i++)
	//{
	//	m_ini_hx[i] = rand() % 401 + 400;//400�`800�̒l�������_���擾���AHuman�̏���X���W�Ƃ���B
	//}
	////Human�̏���Y���W�擾
	//for (int i = 0; i < 3; i++)
	//{
	//	m_ini_hy[i] = rand() % 201 + 250;//250�`450�̒l�������_���擾���AHuman�̏���Y���W�Ƃ���B
	//}

	//�Z���I�u�W�F�N�g
	//����3�񂸂̌J��Ԃ��񐔂����A
	//�J��Ԃ��񐔂͏Z�������Ǘ�����O���[�o���ϐ������
	//�`�悷��Z���̐����s���悤�Ɍ�ɕύX���Ă����B
	//for (int i = 0; i < 3; i++)
	//{
	//	CObjHuman* obj_human = new CObjHuman(m_ini_hx[i], m_ini_hy[i], i);	//�Z���I�u�W�F�N�g�쐬
	//	Objs::InsertObj(obj_human, OBJ_HUMAN, 15);						//�Z���I�u�W�F�N�g�o�^
	//}

	
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

	//�w���v�I�u�W�F�N�g
	CObjHelp* help = new CObjHelp(2);     //�w���v�I�u�W�F�N�g�쐬
	Objs::InsertObj(help, OBJ_HELP, 90);  //�w���v�I�u�W�F�N�g�o�^

	//���b�Z�[�W�\��(�`���[�g���A��)�I�u�W�F�N�g�쐬
	if (g_tutorial_progress < 14)
	{
		CObjMessage* message = new CObjMessage(g_tutorial_progress);	//���b�Z�[�W�\���I�u�W�F�N�g�쐬
		Objs::InsertObj(message, OBJ_MESSAGE, 95);	//���b�Z�[�W�\���I�u�W�F�N�g�o�^
	}


	//�w�iLv1(�w�i���x�����v���C���[�f�����x��)��ǂݍ���0�Ԃɓo�^
	Draw::LoadImage(L"img\\�w�i\\�琬���Lv1.png", 0, TEX_SIZE_512);

	//�߂�A�C�R����ǂݍ���1�Ԃɓo�^
	Draw::LoadImage(L"img\\�{�^��UI\\�߂�.png", 1, TEX_SIZE_512);

	//����Lv1��ǂݍ���2�Ԃɓo�^
	Draw::LoadImage(L"img\\�琬���\\����Lv1.png", 2, TEX_SIZE_512);

	//������Lv1��ǂݍ���3�Ԃɓo�^
	Draw::LoadImage(L"img\\�琬���\\������Lv.1.png", 3, TEX_SIZE_512);

	//�~�T�C��(��)��ǂݍ���4�Ԃɓo�^
	Draw::LoadImage(L"img\\�|�b�h\\�~�T�C��.png", 4, TEX_SIZE_512);

	//����Lv2��ǂݍ���5�Ԃɓo�^
	Draw::LoadImage(L"img\\�琬���\\����Lv2.png", 5, TEX_SIZE_512);

	//������Lv.2��ǂݍ���6�Ԃɓo�^
	Draw::LoadImage(L"img\\�琬���\\������Lv.2.png", 6, TEX_SIZE_512);

	//�w�iLv2(�w�i���x�����v���C���[�f�����x��)��ǂݍ���7�Ԃɓo�^
	Draw::LoadImage(L"img\\�w�i\\�琬���Lv2.png", 7, TEX_SIZE_512);

	//����Lv3��ǂݍ���8�Ԃɓo�^
	Draw::LoadImage(L"img\\�琬���\\����Lv3.png", 8, TEX_SIZE_512);

	//������Lv.3��ǂݍ���9�Ԃɓo�^
	Draw::LoadImage(L"img\\�琬���\\������Lv.3.png", 9, TEX_SIZE_512);

	////�Z����ǂݍ���10�Ԃɓo�^
	//Draw::LoadImage(L"Human.png", 10, TEX_SIZE_512);

	////�w���v�摜��ǂݍ���11�Ԃɓo�^
	//Draw::LoadImage(L"�w���v������.png", 11, TEX_SIZE_512);

	////�w���v�摜��ǂݍ���12�Ԃɓo�^
	//Draw::LoadImage(L"�w���v�q��.png", 12, TEX_SIZE_512);

	////�w���v�摜��ǂݍ���13�Ԃɓo�^
	//Draw::LoadImage(L"�w���v����.png", 13, TEX_SIZE_512);

	//�w�iLv3(�w�i���x�����v���C���[�f�����x��)��ǂݍ���14�Ԃɓo�^
	Draw::LoadImage(L"img\\�w�i\\�琬���Lv3.png", 14, TEX_SIZE_512);
	
	//�_��ǂݍ���15�Ԃɓo�^
	Draw::LoadImage(L"img\\�ڍs���o\\��ʈڍs�_.png", 15, TEX_SIZE_512);

	//�v���C���[�f��Lv1��ǂݍ���16�Ԃɓo�^
	Draw::LoadImage(L"img\\�f��\\P�f��_Lv1�C���N�`�i�V.png", 16, TEX_SIZE_512);

	//�v���C���[�f��Lv2��ǂݍ���17�Ԃɓo�^
	Draw::LoadImage(L"img\\�f��\\P�f��_Lv2new.png", 17, TEX_SIZE_512);

	//�v���C���[�f��Lv3��ǂݍ���18�Ԃɓo�^
	Draw::LoadImage(L"img\\�f��\\P�f��_Lv3new.png", 18, TEX_SIZE_512);

	//�z���C�g�A�E�g���o�摜��ǂݍ���19�Ԃɓo�^
	Draw::LoadImage(L"img\\�w�i\\�z���C�g�A�E�g���o�摜.png", 19, TEX_SIZE_512);

	//�E�C���h�E01��ǂݍ���20�Ԃɓo�^
	Draw::LoadImage(L"img\\���b�Z�[�W�E�B���h�E\\�E�C���h�E01.png", 20, TEX_SIZE_512);

	//���b�Z�[�W�E�C���h�E��ǂݍ���21�Ԃɓo�^
	Draw::LoadImage(L"img\\���b�Z�[�W�E�B���h�E\\���b�Z�[�W�E�B���h�E.png", 21, TEX_SIZE_512);

	//����ǂݍ���22�Ԃɓo�^
	Draw::LoadImage(L"img\\�{�^��UI\\���x���A�b�v.png", 22, TEX_SIZE_512);

	//�Z���U�蕪��UP��ǂݍ���23�Ԃɓo�^
	Draw::LoadImage(L"img\\�{�^��UI\\���01.png", 23, TEX_SIZE_512);

	//�Z���U�蕪��DOWN��ǂݍ���24�Ԃɓo�^
	Draw::LoadImage(L"img\\�{�^��UI\\�퉺.png", 24, TEX_SIZE_512);

	//�~�T�C�����j���[�{�^����ǂݍ���25�Ԃɓo�^
	Draw::LoadImage(L"img\\�{�^��UI\\�~�T�C�����j���[�{�^��.png", 25, TEX_SIZE_512);

	//�|�b�h���j���[�{�^����ǂݍ���26�Ԃɓo�^
	Draw::LoadImage(L"img\\�{�^��UI\\�|�b�h���j���[�{�^��.png", 26, TEX_SIZE_512);

	//�q�ɉ摜�ǂݍ���27�Ԃɓo�^
	Draw::LoadImage(L"img\\�琬���\\�q��.png", 27, TEX_SIZE_512);

	//���ރ{�^���摜�ǂݍ���28�Ԃɓo�^
	Draw::LoadImage(L"img\\�{�^��UI\\���ރ{�^��.png", 28 , TEX_SIZE_512);

	//�Z���{�^���摜�ǂݍ���29�Ԃɓo�^
	Draw::LoadImage(L"img\\�{�^��UI\\�Z���{�^��.png", 29, TEX_SIZE_512);

	//�X�y�V�����Z�{�^���摜�ǂݍ���30�Ԃɓo�^
	Draw::LoadImage(L"img\\�{�^��UI\\�X�y�V�����{�^��.png", 30, TEX_SIZE_512);

	//�����{�^���摜�ǂݍ���31�Ԃɓo�^
	Draw::LoadImage(L"img\\�{�^��UI\\�|�b�h�{�^��.png", 31, TEX_SIZE_512);

	//���ރ{�^����̉�ʔw�i�摜32�Ԃɓo�^
	Draw::LoadImage(L"img\\�w�i\\w.png", 32 , TEX_SIZE_512);

	//����(�؍�)�摜33�Ԃɓo�^
	Draw::LoadImage(L"img\\����\\�؍�.png", 33, TEX_SIZE_512);

	//����(�S)�摜34�Ԃɓo�^
	Draw::LoadImage(L"img\\����\\�S.png", 34, TEX_SIZE_512);

	//����(��)�摜35�Ԃɓo�^
	Draw::LoadImage(L"img\\����\\��.png", 35, TEX_SIZE_512);

	//����(�v���X�`�b�N)�摜36�Ԃɓo�^
	Draw::LoadImage(L"img\\����\\�v���X�`�b�N.png", 36, TEX_SIZE_512);

	//����(�A���~�j�E��)�摜37�Ԃɓo�^
	Draw::LoadImage(L"img\\����\\�A���~�j�E��.png", 37, TEX_SIZE_512);

	//����(�K�X)�摜38�Ԃɓo�^
	Draw::LoadImage(L"img\\����\\�K�X.png", 38, TEX_SIZE_512);

	////����(���A���^��)�摜39�Ԃɓo�^
	//Draw::LoadImage(L"���A���^��.png", 39, TEX_SIZE_512);

	//�X�y�V�����Z1�摜40�Ԃɓo�^
	Draw::LoadImage(L"img\\�{�^��UI\\�X�y�V�����Z1.png", 40, TEX_SIZE_512);

	//�X�y�V�����Z2�摜41�Ԃɓo�^
	Draw::LoadImage(L"img\\�{�^��UI\\�X�y�V�����Z2.png", 41, TEX_SIZE_512);

	//�X�y�V�����Z3�摜42�Ԃɓo�^
	Draw::LoadImage(L"img\\�{�^��UI\\�X�y�V�����Z3.png", 42, TEX_SIZE_512);

	//�X�y�V�����Z4�摜43�Ԃɓo�^
	Draw::LoadImage(L"img\\�{�^��UI\\�X�y�V�����Z4.png", 43, TEX_SIZE_512);

	//�X�y�V�����Z5�摜44�Ԃɓo�^
	Draw::LoadImage(L"img\\�{�^��UI\\�X�y�V�����Z5.png", 44, TEX_SIZE_512);

	//�X�y�V�����Z���b�Z�[�W�E�B���h�E�摜45�Ԃɓo�^
	Draw::LoadImage(L"img\\���b�Z�[�W�E�B���h�E\\�X�y�V�����Z���b�Z�[�W�E�B���h�E.png", 45, TEX_SIZE_512);

	//�y�[�W��i�߂�{�^����ǂݍ���46�Ԃɓo�^
	Draw::LoadImage(L"img\\�w���v\\�y�[�W��i�߂�{�^��.png", 46, TEX_SIZE_512);

	////�w���v�{�^����ǂݍ���47�Ԃɓo�^
	//Draw::LoadImage(L"�w���v�{�^��.png", 47, TEX_SIZE_512);

	////�w���v�摜��ǂݍ���48�Ԃɓo�^
	//Draw::LoadImage(L"�w���v�琬���.png", 48, TEX_SIZE_512);

	//�|�b�h�R�A��Lv1�̉摜��ǂݍ���49�Ԃɓo�^
	Draw::LoadImage(L"img\\�|�b�h\\�|�b�h�R�A��Lv1.png", 49, TEX_SIZE_512);

	//�|�b�h�R�A��Lv2�̉摜��ǂݍ���50�Ԃɓo�^�|�b�h�R�A��Lv2
	Draw::LoadImage(L"img\\�|�b�h\\�|�b�h�R�A��Lv2.png", 50, TEX_SIZE_512);

	//�|�b�h�R�A��Lv3�̉摜��ǂݍ���51�Ԃɓo�^
	Draw::LoadImage(L"img\\�|�b�h\\�|�b�h�R�A��Lv3.png", 51, TEX_SIZE_512);

	//�|�b�h�R�A��Lv1�̉摜��ǂݍ���52�Ԃɓo�^
	Draw::LoadImage(L"img\\�|�b�h\\�|�b�h�R�A��Lv1.png", 52, TEX_SIZE_512);

	//�|�b�h�R�A��Lv2�̉摜��ǂݍ���53�Ԃɓo�^
	Draw::LoadImage(L"img\\�|�b�h\\�|�b�h�R�A��Lv2.png", 53, TEX_SIZE_512);

	//�|�b�h�R�A��Lv3�̉摜��ǂݍ���54�Ԃɓo�^
	Draw::LoadImage(L"img\\�|�b�h\\�|�b�h�R�A��Lv3.png", 54, TEX_SIZE_512);

	//�|�b�h�R�A��Lv1�̉摜��ǂݍ���55�Ԃɓo�^
	Draw::LoadImage(L"img\\�|�b�h\\�|�b�h�R�A��Lv1.png", 55, TEX_SIZE_512);

	//�|�b�h�R�A��Lv2�̉摜��ǂݍ���56�Ԃɓo�^
	Draw::LoadImage(L"img\\�|�b�h\\�|�b�h�R�A��Lv2.png", 56, TEX_SIZE_512);

	//�|�b�h�R�A��Lv3�̉摜��ǂݍ���57�Ԃɓo�^
	Draw::LoadImage(L"img\\�|�b�h\\�|�b�h�R�A��Lv3.png", 57, TEX_SIZE_512);

	//�|�b�h�R�A��Lv1�̉摜��ǂݍ���58�Ԃɓo�^
	Draw::LoadImage(L"img\\�|�b�h\\�|�b�h�R�A��Lv1.png", 58, TEX_SIZE_512);

	//�|�b�h�R�A��Lv2�̉摜��ǂݍ���59�Ԃɓo�^
	Draw::LoadImage(L"img\\�|�b�h\\�|�b�h�R�A��Lv2.png", 59, TEX_SIZE_512);

	//�|�b�h�R�A��Lv3�̉摜��ǂݍ���60�Ԃɓo�^
	Draw::LoadImage(L"img\\�|�b�h\\�|�b�h�R�A��Lv3.png", 60, TEX_SIZE_512);

	//�|�b�h��Lv1�̉摜��ǂݍ���61�Ԃɓo�^
	Draw::LoadImage(L"img\\�|�b�h\\�|�b�h��Lv1.png", 61, TEX_SIZE_512);

	//�|�b�h��Lv2�̉摜��ǂݍ���62�Ԃɓo�^
	Draw::LoadImage(L"img\\�|�b�h\\�|�b�h��Lv2.png", 62, TEX_SIZE_512);

	//�|�b�h��Lv3�̉摜��ǂݍ���63�Ԃɓo�^
	Draw::LoadImage(L"img\\�|�b�h\\�|�b�h��Lv3.png", 63, TEX_SIZE_512);

	//������ LV.�����摜��ǂݍ���64�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�琬���\\������ Lv.png",64,TEX_SIZE_512);

	//���������x��UP�����摜�ǂݍ���65�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�琬���\\���������x��UP.png", 65, TEX_SIZE_512);

	//LvUP�����@�����K�v�����摜�ǂݍ���66�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�琬���\\LvUP�����@�����K�v.png", 66, TEX_SIZE_512);

	//�f��HP�����摜��ǂݍ���67�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�퓬�������\\�f��HP.png", 67, TEX_SIZE_512);

	////50�������摜�ǂݍ���68�Ԃɓo�^
	//Draw::LoadImage(L"", 68, TEX_SIZE_512);

	//�S�����摜�ǂݍ���69�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�f��\\�S����.png", 69, TEX_SIZE_512);

	//LvUP�\!�����摜�ǂݍ���70�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�琬���\\LvUP�\!.png", 70, TEX_SIZE_512);

	//LvUP�s�����摜�ǂݍ���71�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�琬���\\LvUP�s��.png", 71, TEX_SIZE_512);

	//�f�ޏ���ă��x���A�b�v���܂����H�����摜�ǂݍ���72�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�琬���\\�f�ޏ���ă��x���A�b�v���܂����H.png", 72, TEX_SIZE_512);

	//�͂������摜�ǂݍ���73�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�悭�g����摜\\�͂�.png", 73, TEX_SIZE_512);

	//�����������摜�ǂݍ���74�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�悭�g����摜\\������.png", 74, TEX_SIZE_512);

	//�����������摜��ǂݍ���75�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�琬���\\������.png", 75, TEX_SIZE_512);

	//�Z���U�蕪�������摜�ǂݍ���76�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�琬���\\�Z���U�蕪��.png", 76, TEX_SIZE_512);

	//�l�����摜�ǂݍ���77�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�琬���\\�l.png", 77, TEX_SIZE_512);

	//�c��@�@�@�l�����摜�ǂݍ���78�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�琬���\\�c��@�@�@�l.png", 78, TEX_SIZE_512);

	//�Đ��Y�X�s�[�h(���L���X�g)�����摜�ǂݍ���79�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�琬���\\�Đ��Y�X�s�[�h(���L���X�g).png", 79, TEX_SIZE_512);

	//NEXT LV UP�����摜�ǂݍ���80�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�琬���\\NEXT LV UP.png", 80, TEX_SIZE_512);

	//LV. �����摜�ǂݍ���81�Ԃɓo�^
	Draw::LoadImage(L"LV.png", 81, TEX_SIZE_512);

	//���b�h�����摜�ǂݍ���82�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�琬���\\���b�h.png", 82, TEX_SIZE_512);

	//�u���[�����摜�ǂݍ���83�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�琬���\\�u���[.png", 83, TEX_SIZE_512);

	//�O���[�������摜�ǂݍ���84�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�琬���\\�O���[��.png", 84, TEX_SIZE_512);

	//�z���C�g�����摜�ǂݍ���85�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�琬���\\�z���C�g.png", 85, TEX_SIZE_512);

	//�|�b�h�����摜�ǂݍ���86�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�琬���\\�|�b�h.png", 86, TEX_SIZE_512);

	//���������͎����܂��񕶎��摜�ǂݍ���87�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�琬���\\���������͎����܂���.png", 87, TEX_SIZE_512);

	//�q�ɕ����摜��ǂݍ���88�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�琬���\\�q�ɕ���.png", 88, TEX_SIZE_512);

	//�؍ޕ����摜��ǂݍ���89�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�f��\\�؍ޕ���.png", 89, TEX_SIZE_512);

	//�╶���摜��ǂݍ���90�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�f��\\�╶��.png", 90, TEX_SIZE_512);

	//�v���X�`�b�N�����摜��ǂݍ���91�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�f��\\�v���X�`�b�N����.png", 91, TEX_SIZE_512);

	//�A���~�j�E�������摜��ǂݍ���92�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�f��\\�A���~.png", 92, TEX_SIZE_512);

	//�K�X�����摜��ǂݍ���93�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�f��\\�K�X����.png", 93, TEX_SIZE_512);

	//�c��Z���������܂��񕶎��摜��ǂݍ���94�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�琬���\\�c��Z���������܂���.png", 94, TEX_SIZE_512);

	//����̘f���ɕ����摜��ǂݍ���95�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�琬���\\����̘f����.png", 95, TEX_SIZE_512);

	//�Œ�_���[�W��^���镶���摜��ǂݍ���96�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�琬���\\�Œ�_���[�W��^����.png", 96, TEX_SIZE_512);

	//�I�����C����̕����摜��ǂݍ���96�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�琬���\\�I�����C�����.png", 97, TEX_SIZE_512);

	//����|�b�h����j�󂷂镶���摜��ǂݍ���98�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�X�y�V�����Z\\����|�b�h����j�󂷂�.png", 98, TEX_SIZE_512);

	//��10�b�ԕ����摜��ǂݍ���99�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�X�y�V�����Z\\��10�b��.png", 99, TEX_SIZE_512);

	//���G�ƂȂ镶���摜��ǂݍ���100�Ԃɓo�^10�b�ԃ|�b�h���Y���x
	Draw::LoadImage(L"img\\�e�L�X�g\\�X�y�V�����Z\\���G�ƂȂ�.png", 100, TEX_SIZE_512);

	//10�b�ԃ|�b�h���Y���x�����摜��ǂݍ���101�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�X�y�V�����Z\\10�b�ԃ|�b�h���Y���x.png", 101, TEX_SIZE_512);

	//�~�T�C�����Y���xUP�����摜��ǂݍ���102�Ԃɓo�^�o������
	Draw::LoadImage(L"img\\�e�L�X�g\\�琬���\\�~�T�C�����Y���xUP.png", 102, TEX_SIZE_512);

	//�o�����镶���摜��ǂݍ���103�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�琬���\\�o������.png", 103, TEX_SIZE_512);

	//�|�b�h5�@�̍U����UP�����摜��ǂݍ���104�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�琬���\\�|�b�h5�@�̍U����UP.png", 104, TEX_SIZE_512);

	//�������̕����摜(������������)��ǂݍ���105�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�X�y�V�����Z\\������.png", 105, TEX_SIZE_512);

	//���f��HP��0�ȉ��ɂȂ�ꍇLvUP�͏o���܂��񕶎��摜��ǂݍ���106�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�琬���\\���f��HP��0�ȉ��ɂȂ�ꍇLvUP�͏o���܂���.png", 106, TEX_SIZE_512);

	//�ő�Lv���B!�����摜��ǂݍ���107�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�琬���\\�ő�Lv���B!.png", 107, TEX_SIZE_512);

	//����ȏ�LVUP�s�ł��B�����摜��ǂݍ���108�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�琬���\\����ȏ�LVUP�s�ł��B.png", 108, TEX_SIZE_512);

	//���� Lv�����摜��ǂݍ���116�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�琬���\\���� Lv.png",116,TEX_SIZE_512);

	//���Ƀ��x��UP�����摜��ǂݍ���117�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�琬���\\���Ƀ��x��UP.png", 117, TEX_SIZE_512);

	//�������Z�lUP�����摜��ǂݍ���118�Ԃɓo�^
	Draw::LoadImage(L"img\\�{�^��UI\\����.png", 118, TEX_SIZE_512);

	//�������Z�lUP�����摜��ǂݍ���119�Ԃɓo�^
	Draw::LoadImage(L"img\\�{�^��UI\\����01.png", 119, TEX_SIZE_512);

	//�������摜��ǂݍ���120�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�����W\\�������W.png", 120, TEX_SIZE_512);

	//�������摜��ǂݍ���121�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�����W\\�������W.png", 121, TEX_SIZE_512);

	//S��ǂݍ���122�Ԃɓo�^
	Draw::LoadImage(L"S.png", 122, TEX_SIZE_512);

	//Lv1��ǂݍ���123�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�琬���\\Lv1.png", 123, TEX_SIZE_512);

	//Lv2��ǂݍ���124�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�琬���\\Lv2.png", 124, TEX_SIZE_512);

	//Lv3��ǂݍ���125�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�琬���\\Lv3.png", 125, TEX_SIZE_512);

	//�ȈՃ��b�Z�[�W�摜�S�Ă�ǂݍ��ވׂɁA
	//�ǂݍ��ݔԍ�127�Ԃ��g�p���Ă���̂Ŏg��Ȃ��悤�ɁI

	//�|�b�h�����{�^��Lv1��128�Ԃɓo�^
	Draw::LoadImage(L"img\\�|�b�h\\�|�b�h�����{�^��Lv1.png", 128, TEX_SIZE_512);

	//�|�b�h�����{�^��Lv2��129�Ԃɓo�^
	Draw::LoadImage(L"img\\�|�b�h\\�|�b�h�����{�^��Lv2.png", 129, TEX_SIZE_512);

	//�|�b�h�����{�^��Lv3��130�Ԃɓo�^
	Draw::LoadImage(L"img\\�|�b�h\\�|�b�h�����{�^��Lv3.png", 130, TEX_SIZE_512);

	//����ȏヌ�x��UP�o���܂����131�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�琬���\\����ȏヌ�x��UP�o���܂���.png", 131, TEX_SIZE_512);

	//���b�Z�[�W�E�B���h�E01��132�Ԃɓo�^
	Draw::LoadImage(L"img\\���b�Z�[�W�E�B���h�E\\���b�Z�[�W�E�B���h�E01.png", 132, TEX_SIZE_512);

	//�f�����W�xUP!��133�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�琬���\\�f�����W�xUP�I.png", 133, TEX_SIZE_512);

	//�E�C���h�E02��134�Ԃɓo�^
	Draw::LoadImage(L"img\\���b�Z�[�W�E�B���h�E\\�E�C���h�E02.png", 134, TEX_SIZE_512);

	//�|�[�Y��ʔw�i(��ʈÓ]�p)��ǂݍ���135�Ԃɓo�^
	Draw::LoadImage(L"img\\�w�i\\�|�[�Y��ʔw�i.png", 135, TEX_SIZE_512);

	//�w���v�{�^����ǂݍ���136�Ԃɓo�^
	Draw::LoadImage(L"img\\�{�^��UI\\�w���v�{�^��.png", 136, TEX_SIZE_512);

	//�������琬��ʂ�137�Ԃɓo�^
	Draw::LoadImage(L"img\\�w���v\\�������琬���.png", 137, TEX_SIZE_512);

	//��������������138�Ԃɓo�^
	Draw::LoadImage(L"img\\�w���v\\������������.png", 138, TEX_SIZE_512);

	//�������~�T�C����ʂ�139�Ԃɓo�^
	Draw::LoadImage(L"img\\�w���v\\�������~�T�C�����.png", 139, TEX_SIZE_512);

	//�������R�A�ɂ��Ă�140�Ԃɓo�^
	Draw::LoadImage(L"img\\�w���v\\�������R�A�ɂ���.png", 140, TEX_SIZE_512);

	//�������|�b�h�ɂ��Ă�141�Ԃɓo�^
	Draw::LoadImage(L"img\\�w���v\\�������|�b�h�ɂ���.png", 141, TEX_SIZE_512);

	//�������O␂݂�ǂݍ���142�Ԃɓo�^
	Draw::LoadImage(L"img\\�w���v\\�������O␂�.png", 142, TEX_SIZE_512);

	//���������ɂ�143�Ԃɓo�^
	Draw::LoadImage(L"img\\�w���v\\����������.png", 143, TEX_SIZE_512);

	//�������q�ɂ�144�Ԃɓo�^
	Draw::LoadImage(L"img\\�w���v\\�������q��.png", 144, TEX_SIZE_512);

	//�������q�ɂ�145�Ԃɓo�^
	Draw::LoadImage(L"img\\�w���v\\�������f�����W�x.png", 145, TEX_SIZE_512);

	//�R�A�����摜��ǂݍ���146�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�琬���\\�R�A�����摜.png", 146, TEX_SIZE_512);

	//���ޕ����摜��ǂݍ���147�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�f��\\����.png", 147, TEX_SIZE_512);

	//�X�y�V�����Z�����摜��ǂݍ���148�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�X�y�V�����Z\\�X�y�V�����Z.png", 148, TEX_SIZE_512);

	//�|�b�h�����摜��ǂݍ���149�Ԃɓo�^
	Draw::LoadImage(L"img\\�e�L�X�g\\�琬���\\�|�b�h.png", 149, TEX_SIZE_512);

	//�ԏZ���摜��ǂݍ���150�Ԃɓo�^
	Draw::LoadImage(L"img\\�Z��\\�ԏZ��.png", 150, TEX_SIZE_512);

	//�Z���摜��ǂݍ���151�Ԃɓo�^
	Draw::LoadImage(L"img\\�Z��\\�Z��.png", 151, TEX_SIZE_512);

	//�ΏZ���摜��ǂݍ���152�Ԃɓo�^
	Draw::LoadImage(L"img\\�Z��\\�ΏZ��.png", 152, TEX_SIZE_512);

	//���Z���摜��ǂݍ���153�Ԃɓo�^
	Draw::LoadImage(L"img\\�Z��\\���Z��.png", 153, TEX_SIZE_512);

	//�������������摜��ǂݍ���154�Ԃɓo�^
	Draw::LoadImage(L"img\\�{�^��UI\\��������.png", 154, TEX_SIZE_512);

	//���b�Z�[�W�E�B���h�E��1�摜��ǂݍ���155�Ԃɓo�^
	Draw::LoadImage(L"img\\���b�Z�[�W�E�B���h�E\\���b�Z�[�W�E�B���h�E��1.png", 155, TEX_SIZE_512);

	//��b����ǂݍ���189�Ԃɓo�^
	Draw::LoadImage(L"img\\�{�^��UI\\��b���.png", 189, TEX_SIZE_512);

	//�퓬��x10(�R�c)��ǂݍ���190�Ԃɓo�^
	Draw::LoadImage(L"img\\�Z��\\�퓬��x10.png", 190, TEX_SIZE_512);

	//���摜��ǂݍ���191�Ԃɓo�^
	Draw::LoadImage(L"img\\�{�^��UI\\���.png", 191, TEX_SIZE_512);

	//float v = Audio::VolumeMaster(0);
	//v = Audio::VolumeMaster((0.0 - v));

	//���y�ǂݍ���
	Audio::LoadAudio(0, L"�����Ƃ�����.wav", BACK_MUSIC);

	//SE�ǂݍ���
	//�I��
	Audio::LoadAudio(1, L"�I�����U�蕪���A�b�v�R.wav", EFFECT);

	//�߂�
	Audio::LoadAudio(2, L"�߂違�U�蕪���_�E���S.wav", EFFECT);

	//�{�݃��x���A�b�v�̉�
	Audio::LoadAudio(3, L"�{�݃��x���A�b�v��.wav", EFFECT);

	//�z���C�g�A�E�g�̉�
	Audio::LoadAudio(4, L"�z���C�g�A�E�g��.wav", EFFECT);

	//�I��
	Audio::LoadAudio(5, L"�Z���U�蕪���A�b�v�p.wav", EFFECT);

	//���y�X�^�[�g
	Audio::Start(0);
}

//�Q�[�����C�����s�����\�b�h
void CSceneTraining::Scene()
{

}