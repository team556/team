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
	m_speed = 0.12f;

	//�w�i��ǂݍ���0�Ԃɓo�^
	Draw::LoadImage(L"TitleBackgroundTest.jpg", 0, TEX_SIZE_512);

	//�O���O���t�B�b�N��ǂݍ���0�Ԃɓo�^(512�~512�s�N�Z��)
	Draw::LoadImage(L"Human.png", 1, TEX_SIZE_512);

	//�w�i��ǂݍ���0�Ԃɓo�^
	Draw::LoadImage(L"w.png", 2, TEX_SIZE_512);


	//�o�͂����镶���̃O���t�B�b�N���쐬
	//Font::SetStrTex(L"");

	//�e�X�g�I�u�W�F�N�g�쐬
	CObjFight* obj = new CObjFight();		//�^�C�g���I�u�W�F�N�g�쐬
	Objs::InsertObj(obj, OBJ_FIGHT, 10);	//�^�C�g���I�u�W�F�N�g�o�^

	//���I�u�W�F�N�g�쐬
	CObjPlanet* obj0 = new CObjPlanet(200, 300,false);	//�I�u�W�F�N�g�쐬
	Objs::InsertObj(obj0, OBJ_PLANET, 10);				//�u�W�F�N�g�o�^

	//�����I�u�W�F�N�g�쐬
	CObjPlanet* obj1 = new CObjPlanet(900, 300, true);	//�I�u�W�F�N�g�쐬
	Objs::InsertObj(obj1, OBJ_PLANET, 10);				//�I�u�W�F�N�g�o�^

	//�I�u�W�F�N�g�쐬
	CObjPushUnit* obj2 = new CObjPushUnit(300, 600, 100, 100, 0);	//�I�u�W�F�N�g�쐬
	Objs::InsertObj(obj2, OBJ_PLANET, 10);				//�I�u�W�F�N�g�o�^

	//�I�u�W�F�N�g�쐬
	CObjPushUnit* obj3 = new CObjPushUnit(410, 600, 100, 100, 1);	//�I�u�W�F�N�g�쐬
	Objs::InsertObj(obj3, OBJ_PLANET, 10);				//�I�u�W�F�N�g�o�^

														//�I�u�W�F�N�g�쐬
	CObjPushUnit* obj4 = new CObjPushUnit(520, 600, 100, 100, 2);	//�I�u�W�F�N�g�쐬
	Objs::InsertObj(obj4, OBJ_PLANET, 10);				//�I�u�W�F�N�g�o�^
}

//�Q�[�����C�����s�����\�b�h
void CSceneFight::Scene()
{
	m_cnt += m_speed;
	if(m_speed > 0)
		m_speed -= 0.00005f;

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
}