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
CSceneTest::CSceneTest()
{

}

//�f�X�g���N�^
CSceneTest::~CSceneTest()
{

}

//�Q�[�����������\�b�h
void CSceneTest::InitScene()
{
	//�O���O���t�B�b�N��ǂݍ���0�Ԃɓo�^(512�~512�s�N�Z��)
	Draw::LoadImage(L"Human.png", 0, TEX_SIZE_512);

	//�O���O���t�B�b�N��ǂݍ���1�Ԃɓo�^(512�~512�s�N�Z��)
	Draw::LoadImage(L"w.png", 1, TEX_SIZE_512);

	//���b�Z�[�W�E�C���h�E��ǂݍ���2�Ԃɓo�^
	Draw::LoadImage(L"���b�Z�[�W�E�C���h�E(��).png", 2, TEX_SIZE_512);

	//�������W��ǂݍ���3�Ԃɓo�^
	Draw::LoadImage(L"�������W.png", 3, TEX_SIZE_512);

	////10�Ԃɓo�^
	//Draw::LoadImage(L".png", 2, TEX_SIZE_512);

	//�o�͂����镶���̃O���t�B�b�N���쐬
	//Font::SetStrTex(L"");

	//�e�X�g�I�u�W�F�N�g�쐬
	//CObjTest* obj = new CObjTest();		//�^�C�g���I�u�W�F�N�g�쐬
	//Objs::InsertObj(obj, OBJ_TEST, 10);	//�^�C�g���I�u�W�F�N�g�o�^

	////�Z���I�u�W�F�N�g�쐬
	//CObjHuman* obj = new CObjHuman(100,600);	//�^�C�g���I�u�W�F�N�g�쐬
	//Objs::InsertObj(obj, OBJ_HUMAN, 10);		//�^�C�g���I�u�W�F�N�g�o�^

	////�I�u�W�F�N�g�쐬
	//CObjFightClear* obj = new CObjFightClear();	//�^�C�g���I�u�W�F�N�g�쐬
	//Objs::InsertObj(obj, OBJ_FIGHT_CLEAR, 10);		//�^�C�g���I�u�W�F�N�g�o�^

	////�w���v�I�u�W�F�N�g�쐬
	//CObjHelp* help = new CObjHelp(1);		//�w���v�I�u�W�F�N�g�쐬
	//Objs::InsertObj(help, OBJ_HELP, 10);	//�w���v�I�u�W�F�N�g�o�^

	//���b�Z�[�W�\���I�u�W�F�N�g�쐬
	//CObjMessage* message = new CObjMessage(0);	//���b�Z�[�W�\���I�u�W�F�N�g�쐬
	//Objs::InsertObj(message, OBJ_MESSAGE, 90);	//���b�Z�[�W�\���I�u�W�F�N�g�o�^
}

//�Q�[�����C�����s�����\�b�h
void CSceneTest::Scene()
{
	//float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	//RECT_F src;
	//RECT_F dst;
	////�؂���ʒu
	//src.m_top   =  0.0f;
	//src.m_left  =  0.0f;
	//src.m_right =100.0f;
	//src.m_bottom=100.0f;
	////�\���ʒu
	//dst.m_top   =   0.0f;
	//dst.m_left  =   0.0f;
	//dst.m_right =1200.0f;
	//dst.m_bottom= 700.0f;

	////0�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
	//Draw::Draw(1, &src, &dst, c, 0.0f);
}