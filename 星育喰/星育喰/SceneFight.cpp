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
CSceneFight::CSceneFight()
{

}

//�f�X�g���N�^
CSceneFight::~CSceneFight()
{

}

//�Q�[�����������\�b�h
void CSceneFight::InitScene()
{
	m_cnt = 0;
	m_speed = 0.04f;
	m_a = 1.0f;

	//�w�i��ǂݍ���0�Ԃɓo�^
	Draw::LoadImage(L"TitleBackgroundTest.jpg", 0, TEX_SIZE_512);

	//�O���O���t�B�b�N��ǂݍ���0�Ԃɓo�^(512�~512�s�N�Z��)
	Draw::LoadImage(L"Human.png", 1, TEX_SIZE_512);

	//�~�T�C��2�Ԃɓo�^
	Draw::LoadImage(L"w.png", 2, TEX_SIZE_512);

	//3�Ԃɓo�^
	Draw::LoadImage(L"�v���C���[�f��Lv1.png", 3, TEX_SIZE_512);

	//4�Ԃɓo�^
	//Draw::LoadImage(L"�v���C���[���Ƃ�.png", 4, TEX_SIZE_512);

	//5�Ԃɓo�^
	//Draw::LoadImage(L"�v���C���[�ߐH.png", 5, TEX_SIZE_512);

	//10�Ԃɓo�^
	Draw::LoadImage(L"w.png", 10, TEX_SIZE_512);
	
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
	

	//�o�͂����镶���̃O���t�B�b�N���쐬
	//Font::SetStrTex(L"");

	//�e�X�g�I�u�W�F�N�g�쐬
	CObjFight* obj = new CObjFight();		//�^�C�g���I�u�W�F�N�g�쐬
	Objs::InsertObj(obj, OBJ_FIGHT, 10);	//�^�C�g���I�u�W�F�N�g�o�^

	//�G���I�u�W�F�N�g�쐬
	CObjPlanet* obj0 = new CObjPlanet(250, 350, 10, false);	//�I�u�W�F�N�g�쐬
	Objs::InsertObj(obj0, OBJ_ENEMY,  5);					//�u�W�F�N�g�o�^

	//�����I�u�W�F�N�g�쐬
	CObjPlanet* obj1 = new CObjPlanet(950, 350, 10, true);	//�I�u�W�F�N�g�쐬
	Objs::InsertObj(obj1, OBJ_PLANET, 10);					//�I�u�W�F�N�g�o�^

	//�G���I�u�W�F�N�g�쐬
	CObjPlanet* obj01 = new CObjPlanet(250, 350,10, false);	//�I�u�W�F�N�g�쐬
	Objs::InsertObj(obj01, OBJ_ENEMY2, 11);					//�u�W�F�N�g�o�^

	//�����˃{�^��
	CObjPushUnit* obj2 = new CObjPushUnit(500, 600, 100, 100, 1);	//�I�u�W�F�N�g�쐬
	Objs::InsertObj(obj2, OBJ_PLANET, 10);						//�I�u�W�F�N�g�o�^

	CObjPushUnit* obj3 = new CObjPushUnit(650, 600, 100, 100, 2);	//�I�u�W�F�N�g�쐬
	Objs::InsertObj(obj3, OBJ_PLANET, 10);						//�I�u�W�F�N�g�o�^

	CObjPushUnit* obj4 = new CObjPushUnit(800, 600, 100, 100, 3);	//�I�u�W�F�N�g�쐬
	Objs::InsertObj(obj4, OBJ_PLANET, 10);						//�I�u�W�F�N�g�o�^

	CObjPushUnit* obj5 = new CObjPushUnit(950, 600, 100, 100, 4);	//�I�u�W�F�N�g�쐬
	Objs::InsertObj(obj5, OBJ_PLANET, 10);						//�I�u�W�F�N�g�o�^

	//�~�T�C�����˃{�^��
	CObjPushMissile* obj6 = new CObjPushMissile(150, 600, 200, 100);	//�I�u�W�F�N�g�쐬
	Objs::InsertObj(obj6, OBJ_PLANET, 10);						//�I�u�W�F�N�g�o�^
}

//�Q�[�����C�����s�����\�b�h
void CSceneFight::Scene()
{
	m_cnt += m_speed;
	if(m_speed > 0)
		m_speed -= 0.00001f;

	//�`��J���[���  R=RED  G=Green  B=Blue A=alpha(���ߏ��)
	float d[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu


	//���w�i�\��
	src.m_top   =  0.0f +(m_cnt * 4.5 / 6);
	src.m_left  =  0.0f + m_cnt;
	src.m_right =960.0f - m_cnt;
	src.m_bottom=638.0f -(m_cnt * 4.5 / 6);

	dst.m_top   =   0.0f;
	dst.m_left  =   0.0f;
	dst.m_right =1200.0f;
	dst.m_bottom= 700.0f;
	Draw::Draw(0, &src, &dst, d, 0.0f);


	if (m_cnt >= 0.5 && m_a >=0 ) {
		m_a -= 0.01f;
	}
	
	float c[4] = { 1.0f,1.0f,1.0f,m_a };
	Font::StrDraw(L"�X�^�[�g�I", 420, 250, 80, c);
}