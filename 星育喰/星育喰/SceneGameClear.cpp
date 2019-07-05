//STL�Ńo�O�@�\��OFF�ɂ���
#define _SECURE_SCL (0)
#define _HAS_ITERTOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL\DrawTexture.h"
#include "GameL\Audio.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p�w�b�_�[
//#include "SceneMain.h"
#include "GameHead.h"

//�R���X�g���N�^
CSceneGameClear::CSceneGameClear()
{

}

//�f�X�g���N�^
CSceneGameClear::~CSceneGameClear()
{

}

//�Q�[�����������\�b�h
void CSceneGameClear::InitScene()
{
	//�O���O���t�B�b�N��ǂݍ���1�Ԃɓo�^(512�~512�s�N�Z��)
	Draw::LoadImage(L"w.png", 0, TEX_SIZE_512);

	//�^�C�g�����S
	Draw::LoadImage(L"�^�C�g�����S.png", 1, TEX_SIZE_512);

	//���G���f�B���O�̃e�L�X�g�p
	//���lURL
	Draw::LoadImage(L"���l.png", 2,TEX_SIZE_512);

	//������URL�`��o�^
	Draw::LoadImage(L"����������.png", 3, TEX_SIZE_512);
	Draw::LoadImage(L"�����������Q.png", 4, TEX_SIZE_512);

	//TAMMURL�`��o�^
	Draw::LoadImage(L"TAM_Music_Factory.png", 5, TEX_SIZE_512);

	//DOVA-SYN DROME�`��o�^
	Draw::LoadImage(L"DOVA-SYN_DROME.png", 6, TEX_SIZE_512);

	//�������ʉ��ŗV�ڂ��`��o�^
	Draw::LoadImage(L"�������ʉ��ŗV�ڂ�.png", 7, TEX_SIZE_512);

	//���ʉ����{�`��o�^
	Draw::LoadImage(L"���ʉ����{.png", 8, TEX_SIZE_512);

	//OtoLogic
	Draw::LoadImage(L"OtoLogic.png", 9, TEX_SIZE_512);

	//END�`��o�^
	Draw::LoadImage(L"END.png", 10, TEX_SIZE_512);

	//�g�p�������y�`��o�^
	Draw::LoadImage(L"�g�p�������y�E���ʉ��T�C�g.png", 11, TEX_SIZE_512);

	//�G���h���[������������܂��B�`��o�^
	Draw::LoadImage(L"�E�N���b�N�������������.png", 12, TEX_SIZE_512);

	//�E�N���b�N�������������
	Draw::LoadImage(L"�G���h���[������������܂��B.png", 13, TEX_SIZE_512);

	//�I�u�W�F�N�g�쐬
	CObjGameClear* obj = new CObjGameClear();	//�I�u�W�F�N�g�쐬
	Objs::InsertObj(obj, OBJ_GAME_CLEAR, 10);	//�I�u�W�F�N�g�o�^

	//���y�ǂݍ���
	Audio::LoadAudio(0, L"�G���h���[��.wav", BACK_MUSIC);

	//�N���b�N��
	Audio::LoadAudio(1, L"�I�����U�蕪���A�b�v�R.wav", EFFECT);

	//���y�X�^�[�g
	Audio::Start(0);

}

//�Q�[�����C�����s�����\�b�h
void CSceneGameClear::Scene()
{
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	RECT_F src;
	RECT_F dst;
	//�؂���ʒu
	src.m_top   =  0.0f;
	src.m_left  =  0.0f;
	src.m_right =100.0f;
	src.m_bottom=100.0f;
	//�\���ʒu
	dst.m_top   =   0.0f;
	dst.m_left  =   0.0f;
	dst.m_right =1200.0f;
	dst.m_bottom= 700.0f;

	//0�Ԗڂɓo�^�����O���t�B�b�N��src,dst,c�������Ƃɕ`��
	Draw::Draw(1, &src, &dst, c, 0.0f);
}