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
	//END�`��o�^
	Draw::LoadImage(L"img\\�e�L�X�g\\Ending\\END.png", 2, TEX_SIZE_512);

	//�g�p�������y�`��o�^
	Draw::LoadImage(L"img\\�e�L�X�g\\Ending\\�g�p�������y�E���ʉ��T�C�g.png", 3, TEX_SIZE_512);

	//�G���h���[������������܂��B�`��o�^
	Draw::LoadImage(L"img\\�e�L�X�g\\Ending\\�E�N���b�N�������������.png", 4, TEX_SIZE_512);

	//�E�N���b�N�������������
	Draw::LoadImage(L"img\\�e�L�X�g\\Ending\\�G���h���[������������܂��B.png", 5, TEX_SIZE_512);

	//�N���b�N�Ń^�C�g���ɖ߂�
	Draw::LoadImage(L"img\\�e�L�X�g\\Ending\\�N���b�N�Ń^�C�g���ɖ߂�.png", 6, TEX_SIZE_512);

	//���l
	Draw::LoadImage(L"img\\�e�L�X�g\\Ending\\���l.png", 7,TEX_SIZE_512);
	Draw::LoadImage(L"img\\�e�L�X�g\\Ending\\���l_URL.png", 8, TEX_SIZE_512);

	//�������`��o�^
	Draw::LoadImage(L"img\\�e�L�X�g\\Ending\\������.png", 9, TEX_SIZE_512);
	Draw::LoadImage(L"img\\�e�L�X�g\\Ending\\������_URL_1.png", 10, TEX_SIZE_512);
	Draw::LoadImage(L"img\\�e�L�X�g\\Ending\\������_URL_2.png", 11, TEX_SIZE_512);

	//TAMM�`��o�^
	Draw::LoadImage(L"img\\�e�L�X�g\\Ending\\TAM_Music_Factory.png", 12, TEX_SIZE_512);
	Draw::LoadImage(L"img\\�e�L�X�g\\Ending\\TAM_Music_Factory_URL.png", 13, TEX_SIZE_512);

	//DOVA-SYN DROME�`��o�^
	Draw::LoadImage(L"img\\�e�L�X�g\\Ending\\DOVA-SYN_DROME.png", 14, TEX_SIZE_512);
	Draw::LoadImage(L"img\\�e�L�X�g\\Ending\\DOVA-SYN_DROME_URL.png", 15, TEX_SIZE_512);

	//�������ʉ��ŗV�ڂ��`��o�^
	Draw::LoadImage(L"img\\�e�L�X�g\\Ending\\�������ʉ��ŗV�ڂ�.png", 16, TEX_SIZE_512);
	Draw::LoadImage(L"img\\�e�L�X�g\\Ending\\�������ʉ��ŗV�ڂ�_URL.png", 17, TEX_SIZE_512);

	//���ʉ����{�`��o�^
	Draw::LoadImage(L"img\\�e�L�X�g\\Ending\\���ʉ����{.png", 18, TEX_SIZE_512);
	Draw::LoadImage(L"img\\�e�L�X�g\\Ending\\���ʉ����{_URL.png", 19, TEX_SIZE_512);

	//OtoLogic
	Draw::LoadImage(L"img\\�e�L�X�g\\Ending\\OtoLogic.png", 20, TEX_SIZE_512);
	Draw::LoadImage(L"img\\�e�L�X�g\\Ending\\OtoLogic_URL.png", 21, TEX_SIZE_512);

	//�����o�[�̖��O�`��o�^
	Draw::LoadImage(L"img\\�e�L�X�g\\Ending\\�r�c.png", 22, TEX_SIZE_512);
	Draw::LoadImage(L"img\\�e�L�X�g\\Ending\\���.png", 23, TEX_SIZE_512);
	Draw::LoadImage(L"img\\�e�L�X�g\\Ending\\�ؑ�.png", 24, TEX_SIZE_512);
	Draw::LoadImage(L"img\\�e�L�X�g\\Ending\\�e�c.png", 25, TEX_SIZE_512);
	Draw::LoadImage(L"img\\�e�L�X�g\\Ending\\����.png", 26, TEX_SIZE_512);
	Draw::LoadImage(L"img\\�e�L�X�g\\Ending\\��c.png", 27, TEX_SIZE_512);
	Draw::LoadImage(L"img\\�e�L�X�g\\Ending\\�z�K.png", 28, TEX_SIZE_512);

	//�g�p�O���t�B�b�N�Љ�
	Draw::LoadImage(L"img\\�e�L�X�g\\Ending\\���ЃT�C�g.png", 29, TEX_SIZE_512);//
	Draw::LoadImage(L"img\\�e�L�X�g\\Ending\\�悭��΂Ȃ���.png", 30, TEX_SIZE_512);//
	Draw::LoadImage(L"img\\�e�L�X�g\\Ending\\�s���I�h�t�H���gURL.png", 31, TEX_SIZE_512);//
	Draw::LoadImage(L"img\\�e�L�X�g\\Ending\\�t�H���g.png", 32, TEX_SIZE_512);//
	Draw::LoadImage(L"img\\�e�L�X�g\\Ending\\�s���I�h�t�H���g.png", 33, TEX_SIZE_512);//
	Draw::LoadImage(L"img\\�e�L�X�g\\Ending\\���.png", 34, TEX_SIZE_512);//
	Draw::LoadImage(L"img\\�e�L�X�g\\Ending\\��Җ�.png", 35, TEX_SIZE_512);//

	//���상���o�[�̖����Љ�
	Draw::LoadImage(L"img\\�e�L�X�g\\Ending\\����.png", 36, TEX_SIZE_512);
	Draw::LoadImage(L"img\\�e�L�X�g\\Ending\\�v���O���}.png", 37, TEX_SIZE_512);
	Draw::LoadImage(L"img\\�e�L�X�g\\Ending\\�O���t�B�b�J�[.png", 38, TEX_SIZE_512);
	Draw::LoadImage(L"img\\�e�L�X�g\\Ending\\�v�����i.png", 39, TEX_SIZE_512);






	

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