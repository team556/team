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
CSceneFight::CSceneFight(int e_n)
{
	m_ene_nam = e_n;
}

//�f�X�g���N�^
CSceneFight::~CSceneFight()
{

}

//�Q�[�����������\�b�h
void CSceneFight::InitScene()
{
	//�w�i��ǂݍ���0�Ԃɓo�^
	Draw::LoadImage(L"TitleBackgroundTest.jpg", 0, TEX_SIZE_512);

	//�O���O���t�B�b�N��ǂݍ���0�Ԃɓo�^(512�~512�s�N�Z��)
	Draw::LoadImage(L"Human.png", 1, TEX_SIZE_512);

	//2�ԂɃ~�T�C���o�^
	Draw::LoadImage(L"w.png", 2, TEX_SIZE_512);

	//3�ԂɃv���C���[�o�^
	Draw::LoadImage(L"�v���C���[�f��Lv1.png", 3, TEX_SIZE_512);

	//4�Ԃɓo�^�f��
	Draw::LoadImage(L"�v���C���[�f�����i�K.png", 33, TEX_SIZE_512);

	//5�Ԃɓo�^
	//Draw::LoadImage(L"�v���C���[�ߐH.png", 5, TEX_SIZE_512);

	//10�Ԃɓo�^�ԐF�|�b�h
	Draw::LoadImage(L"�|�b�h1.png", 10, TEX_SIZE_512);

	//11�Ԃɓo�^
	Draw::LoadImage(L"�p���[�{�^��(��).png", 11, TEX_SIZE_512);

	//12�Ԃɓo�^
	Draw::LoadImage(L"�f�B�t�F���X�{�^��(��).png", 12, TEX_SIZE_512);

	//13�Ԃɓo�^
	Draw::LoadImage(L"�X�s�[�h�{�^��(��).png", 13, TEX_SIZE_512);

	//14�Ԃɓo�^
	Draw::LoadImage(L"�o�����X�{�^��(��).png", 14, TEX_SIZE_512);

	//15�Ԃɓo�^
	Draw::LoadImage(L"�~�T�C���{�^��(��).png", 15, TEX_SIZE_512);

	//16�Ԃɔ����G�t�F�N�g��o�^
	Draw::LoadImage(L"�����G�t�F�N�g.png", 16, TEX_SIZE_512);

	//17�Ԗڂɓo�^
	Draw::LoadImage(L"�~�T�C��.png", 17, TEX_SIZE_512);

	//�퓬��ʈڍs���o(����)��ǂݍ���18�Ԃɓo�^
	Draw::LoadImage(L"�퓬��ʈڍs���o(����)(��).png", 18, TEX_SIZE_512);

	//�X�y�V�����Z�{�^����ǂݍ���19�Ԃɓo�^
	Draw::LoadImage(L"�X�y�V�����Z�{�^��(��).png", 19, TEX_SIZE_512);

	//�����ׂ����A����ǂ��ɂ��g���Ă��Ȃ������ׁA��U�R�����g�A�E�g���B
	//63�Ԗڂɓo�^�F�|�b�h
	//Draw::LoadImage(L"�|�b�h2.png", 63, TEX_SIZE_512);
	

	//�o�͂����镶���̃O���t�B�b�N���쐬
	//Font::SetStrTex(L"");

	//�퓬��ʃI�u�W�F�N�g�쐬
	CObjFight* obj = new CObjFight(10, m_ene_nam);		//(�퓬����, �G�i���o�[)
	Objs::InsertObj(obj, OBJ_FIGHT, 1);		//�퓬��ʃI�u�W�F�N�g�o�^

	//�G���I�u�W�F�N�g�쐬
	CObjPlanet* obj0 = new CObjPlanet(250, 350, 10, m_ene_nam);	//�I�u�W�F�N�g�쐬
	Objs::InsertObj(obj0, OBJ_ENEMY,  5);					//�I�u�W�F�N�g�o�^

	//�����I�u�W�F�N�g�쐬
	CObjPlanet* obj1 = new CObjPlanet(950, 350, 10, 0);	//�I�u�W�F�N�g�쐬
	Objs::InsertObj(obj1, OBJ_PLANET, 10);					//�I�u�W�F�N�g�o�^

	//�G���N���[���쐬
	CObjPlanet* obj01 = new CObjPlanet(250, 350,10, m_ene_nam);	//�I�u�W�F�N�g�쐬
	Objs::InsertObj(obj01, OBJ_ENEMY2, 11);					//�I�u�W�F�N�g�o�^

	//�����˃{�^��
	CObjRocketButton* obj2 = new CObjRocketButton(500, 600, 100, 100, 1);	//�I�u�W�F�N�g�쐬
	Objs::InsertObj(obj2, OBJ_PLANET, 10);						//�I�u�W�F�N�g�o�^

	CObjRocketButton* obj3 = new CObjRocketButton(650, 600, 100, 100, 2);	//�I�u�W�F�N�g�쐬
	Objs::InsertObj(obj3, OBJ_PLANET, 10);						//�I�u�W�F�N�g�o�^

	CObjRocketButton* obj4 = new CObjRocketButton(800, 600, 100, 100, 3);	//�I�u�W�F�N�g�쐬
	Objs::InsertObj(obj4, OBJ_PLANET, 10);						//�I�u�W�F�N�g�o�^

	CObjRocketButton* obj5 = new CObjRocketButton(950, 600, 100, 100, 4);	//�I�u�W�F�N�g�쐬
	Objs::InsertObj(obj5, OBJ_PLANET, 10);						//�I�u�W�F�N�g�o�^

	CObjRocketButton* obj6 = new CObjRocketButton(150, 600, 100, 200, 5);	//�I�u�W�F�N�g�쐬
	Objs::InsertObj(obj6, OBJ_PLANET, 10);						//�I�u�W�F�N�g�o�^

	//�X�y�V�����Z�{�^��
	CObjSpecialButton* special = new CObjSpecialButton(1000.0f, 20.0f, 114.0f, 175.0f);	//�I�u�W�F�N�g�쐬
	Objs::InsertObj(special, OBJ_PLANET, 90);											//�I�u�W�F�N�g�o�^

	//�퓬�O���o�I�u�W�F�N�g
	CObjBefore_Fight_Effect* before_fight_effect = new CObjBefore_Fight_Effect();	//�퓬�O���o�I�u�W�F�N�g�쐬
	Objs::InsertObj(before_fight_effect, OBJ_BEFORE_FIGHT_EFFECT, 100);				//�퓬�O���o�I�u�W�F�N�g�o�^
}

//�Q�[�����C�����s�����\�b�h
void CSceneFight::Scene()
{

}