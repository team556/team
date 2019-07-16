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
	//�w�i��ǂݍ���0�Ԃɓo�^
	Draw::LoadImage(L"TitleBackgroundTest.jpg", 0, TEX_SIZE_512);

	//�O���O���t�B�b�N��ǂݍ���1�Ԃɓo�^(512�~512�s�N�Z��)
	Draw::LoadImage(L"Human.png", 1, TEX_SIZE_512);

	//2�ԂɃ~�T�C���o�^
	Draw::LoadImage(L"w.png", 2, TEX_SIZE_512);

	//�v���C���[�f��Lv1��ǂݍ���3�Ԃɓo�^
	Draw::LoadImage(L"�v���C���[�f��Lv1 128x.png", 3, TEX_SIZE_512);

	//�v���C���[�f��Lv2��ǂݍ���4�Ԃɓo�^
	Draw::LoadImage(L"�v���C���[�f��Lv1 128x.png", 4, TEX_SIZE_512);

	//�v���C���[�f��Lv3��ǂݍ���5�Ԃɓo�^
	Draw::LoadImage(L"�v���C���[�f��Lv1 128x.png", 5, TEX_SIZE_512);

	//4�Ԃɓo�^�f��
	//Draw::LoadImage(L"�v���C���[�f�����i�K.png", 33, TEX_SIZE_512);

	//5�Ԃɓo�^
	//Draw::LoadImage(L"�v���C���[�ߐH.png", 5, TEX_SIZE_512);

	//�|�b�hLv.1��8�Ԃɓo�^
	Draw::LoadImage(L"�|�b�h1.png", 8, TEX_SIZE_512);

	//�|�b�hLv.2��9�Ԃɓo�^
	Draw::LoadImage(L"�|�b�h2.png", 9, TEX_SIZE_512);

	//�|�b�hLv.3��10�Ԃɓo�^
	Draw::LoadImage(L"�|�b�h3.png", 10, TEX_SIZE_512);

	//11�Ԃɓo�^
	Draw::LoadImage(L"�p���[�{�^��.png", 11, TEX_SIZE_512);

	//12�Ԃɓo�^
	Draw::LoadImage(L"�f�B�t�F���X�{�^��.png", 12, TEX_SIZE_512);

	//13�Ԃɓo�^
	Draw::LoadImage(L"�X�s�[�h�{�^��.png", 13, TEX_SIZE_512);

	//14�Ԃɓo�^
	Draw::LoadImage(L"�o�����X�{�^��.png", 14, TEX_SIZE_512);

	//15�Ԃɓo�^
	Draw::LoadImage(L"�~�T�C���{�^��(�V).png", 15, TEX_SIZE_512);

	//16�Ԃɔ����G�t�F�N�g��o�^
	Draw::LoadImage(L"�����G�t�F�N�g.png", 16, TEX_SIZE_512);

	//17�Ԗڂɓo�^
	Draw::LoadImage(L"�~�T�C��.png", 17, TEX_SIZE_512);

	//�퓬��ʈڍs���o(����)��ǂݍ���18�Ԃɓo�^
	Draw::LoadImage(L"�퓬��ʈڍs���o(����)(��).png", 18, TEX_SIZE_512);

	//�X�y�V�����Z�{�^����ǂݍ���19�Ԃɓo�^
	Draw::LoadImage(L"�X�y�V�����Z�{�^��(��).png", 19, TEX_SIZE_512);

	//�|�[�Y��ʔw�i��ǂݍ���20�Ԃɓo�^
	Draw::LoadImage(L"�|�[�Y��ʔw�i.png", 20, TEX_SIZE_512);

	//�X�y�V�����Z[Explosion]�摜��ǂݍ���21�Ԃɓo�^
	Draw::LoadImage(L"Explosion.png", 21, TEX_SIZE_512);

	//�X�y�V�����Z[Fracture_Ray]�摜��ǂݍ���22�Ԃɓo�^
	Draw::LoadImage(L"�X�y�V�����ZFracture_Ray.png", 22, TEX_SIZE_512);

	//�X�y�V�����Z[Immortality]�摜��ǂݍ���23�Ԃɓo�^
	Draw::LoadImage(L"�X�y�V�����Z�C�����[�^���e�B.png", 23, TEX_SIZE_512);

	//�X�y�V�����Z[���~�b�g�u���C�N]�摜��ǂݍ���24�Ԃɓo�^
	Draw::LoadImage(L"�U���̓A�b�v.png", 24, TEX_SIZE_512);

	//�X�y�V�����Z[�X�e���C�h���^]�摜��ǂݍ���25�Ԃɓo�^
	Draw::LoadImage(L"�X�e���C�h���^.png", 25, TEX_SIZE_512);

	Draw::LoadImage(L"���A�C.png", 26, TEX_SIZE_512);

	Draw::LoadImage(L"���C�h1 128x.png", 27, TEX_SIZE_512);

	Draw::LoadImage(L"����.png", 28, TEX_SIZE_512);

	//�G�f��4(1�X�e�[�W)��ǂݍ���29�Ԃɓo�^
	Draw::LoadImage(L"�ڂ₯����.png", 29, TEX_SIZE_512);

	//�{�X��(1�X�e�[�W)��ǂݍ���30�Ԃɓo�^
	Draw::LoadImage(L"�p���_�퓬.png", 30, TEX_SIZE_512);

	//�l���s���A�C�R����ǂݍ���31�Ԃɓo�^
	Draw::LoadImage(L"�l���s��.png", 31, TEX_SIZE_512);

	//HP�Q�[�W(���L���X�g�Q�[�W�ɂ��g�p)��ǂݍ���32�Ԃɓo�^
	Draw::LoadImage(L"HP�Q�[�W.png", 32, TEX_SIZE_512);

	//���b�Z�[�W�E�C���h�E��ǂݍ���33�Ԃɓo�^
	Draw::LoadImage(L"���b�Z�[�W�E�C���h�E(��).png", 33, TEX_SIZE_512);

	//����ǂݍ���34�Ԃɓo�^
	Draw::LoadImage(L"��.png", 34, TEX_SIZE_512);

	//�~�T�C���L�[�{�[�h�p�摜
	Draw::LoadImage(L"1�I���A�C�R��.png", 35, TEX_SIZE_512);

	//�ԃ|�b�h�L�[�{�[�h�p�摜
	Draw::LoadImage(L"2�I���A�C�R��.png", 36, TEX_SIZE_512);

	//�|�b�h�L�[�{�[�h�p�摜
	Draw::LoadImage(L"3�I���A�C�R��.png", 37, TEX_SIZE_512);

	//�΃L�[�{�[�h�p�摜
	Draw::LoadImage(L"4�I���A�C�R��.png", 38, TEX_SIZE_512);

	//�D�F�L�[�{�[�h�p�摜
	Draw::LoadImage(L"5�I���A�C�R��.png", 39, TEX_SIZE_512);

	//�X�y�V�����Z�L�[�{�[�h�p�摜
	Draw::LoadImage(L"s�I���A�C�R��.png", 40, TEX_SIZE_512);

	//�������̃t�H���g��41�Ԃɓo�^
	Draw::LoadImage(L"�������W.png", 41, TEX_SIZE_512);

	//�X�^�[�g�I��42�Ԃɓo�^
	Draw::LoadImage(L"�X�^�[�g�I.png", 42, TEX_SIZE_512);

	//�v���C���[��43�Ԃɓo�^
	Draw::LoadImage(L"�v���C���[.png", 43, TEX_SIZE_512);

	//�G�l�~�[��44�Ԃɓo�^
	Draw::LoadImage(L"�G�l�~�[.png", 44, TEX_SIZE_512);

	//�G�N�X�v���[�W������45�Ԃɓo�^
	Draw::LoadImage(L"�G�N�X�v���[�W����.png", 45, TEX_SIZE_512);

	//�t���N�`���[���C��46�Ԃɓo�^
	Draw::LoadImage(L"�t���N�`���[���C.png", 46, TEX_SIZE_512);

	//�C���[�^���e�B��47�Ԃɓo�^
	Draw::LoadImage(L"�C���[�^���e�B.png", 47, TEX_SIZE_512);

	//�I�[�o�[���[�N��48�Ԃɓo�^
	Draw::LoadImage(L"�I�[�o�[���[�N.png", 48, TEX_SIZE_512);

	//���~�b�g�u���C�N��49�Ԃɓo�^
	Draw::LoadImage(L"���~�b�g�u���C�N.png", 49, TEX_SIZE_512);

	//�����I��50�Ԃɓo�^
	Draw::LoadImage(L"�����I.png", 50, TEX_SIZE_512);

	//�N���b�N�Ń^�C�g���ɖ߂���T�P�Ԃɓo�^
	Draw::LoadImage(L"�N���b�N�Ń^�C�g���ɖ߂�.png", 51, TEX_SIZE_512);

	//�N���b�N�Ńz�[����ʂ�52�Ԃɓo�^
	Draw::LoadImage(L"�N���b�N�Ńz�[�����.png", 52, TEX_SIZE_512);

	//�ߐH�����I��53�Ԃɓo�^
	Draw::LoadImage(L"�ߐH�����I.png", 53, TEX_SIZE_512);

	//�X�y�V�����Z��54�Ԃɓo�^
	Draw::LoadImage(L"�X�y�V�����Z.png", 54, TEX_SIZE_512);

	//�f��HP��55�Ԃɓo�^
	Draw::LoadImage(L"�f��HP.png", 55, TEX_SIZE_512);

	//�Z����56�Ԃɓo�^
	Draw::LoadImage(L"�Z��.png", 56, TEX_SIZE_512);

	//��Ƃ�57�Ԃɓo�^
	Draw::LoadImage(L"����.png", 57, TEX_SIZE_512);

	//�N���b�N�Ń^�C�g���ɖ߂���T8�Ԃɓo�^
	Draw::LoadImage(L"GAME_OVER.png", 58, TEX_SIZE_512);

	//�؍ނ�59�Ԃɓo�^
	Draw::LoadImage(L"�؍ޕ���.png", 59, TEX_SIZE_512);

	//�S��60�Ԃɓo�^
	Draw::LoadImage(L"�S����.png", 60, TEX_SIZE_512);

	//���61�Ԃɓo�^
	Draw::LoadImage(L"�╶��.png", 61, TEX_SIZE_512);

	//�v���X�`�b�N��62�Ԃɓo�^
	Draw::LoadImage(L"�v���X�`�b�N����.png", 62, TEX_SIZE_512);

	//�A���~��63�Ԃɓo�^
	Draw::LoadImage(L"�A���~.png", 63, TEX_SIZE_512);

	//�K�X��64�Ԃɓo�^
	Draw::LoadImage(L"�K�X����.png", 64, TEX_SIZE_512);

	//�ԃ|�b�h���x��1��65�Ԗڂɓo�^
	Draw::LoadImage(L"�|�b�h��Lv1.png", 65, TEX_SIZE_512);
	//�ԃ|�b�h���x��2��66�Ԗڂɓo�^
	Draw::LoadImage(L"�|�b�h��Lv2.png", 66, TEX_SIZE_512);
	//�ԃ|�b�h���x��3��67�Ԗڂɓo�^
	Draw::LoadImage(L"�|�b�h��Lv3.png", 67, TEX_SIZE_512);

	//�|�b�h���x��1��68�Ԗڂɓo�^
	Draw::LoadImage(L"�|�b�h��Lv1.png", 68, TEX_SIZE_512);
	//�|�b�h���x��2��69�Ԗڂɓo�^
	Draw::LoadImage(L"�|�b�h��Lv2.png", 69, TEX_SIZE_512);
	//�|�b�h���x��3��70�Ԗڂɓo�^
	Draw::LoadImage(L"�|�b�h��Lv3.png", 70, TEX_SIZE_512);

	//�΃|�b�h���x��1��71�Ԗڂɓo�^
	Draw::LoadImage(L"�|�b�h��Lv1.png", 71, TEX_SIZE_512);
	//�΃|�b�h���x��2��72�Ԗڂɓo�^
	Draw::LoadImage(L"�|�b�h��Lv2.png", 72, TEX_SIZE_512);
	//�΃|�b�h���x��3��73�Ԗڂɓo�^
	Draw::LoadImage(L"�|�b�h��Lv3.png", 73, TEX_SIZE_512);

	//���|�b�h���x��1��74�Ԗڂɓo�^
	Draw::LoadImage(L"�|�b�h��Lv1.png", 74, TEX_SIZE_512);
	//���|�b�h���x��2��75�Ԗڂɓo�^
	Draw::LoadImage(L"�|�b�h��Lv2.png", 75, TEX_SIZE_512);
	//���|�b�h���x��3��76�Ԗڂɓo�^
	Draw::LoadImage(L"�|�b�h��Lv3.png", 76, TEX_SIZE_512);

	////�v���C���[�f��(�N���A��ʗp)��ǂݍ���34�Ԃɓo�^
	//Draw::LoadImage(L"�v���C���[�f��.png", 34, TEX_SIZE_512);

	//�o�͂����镶���̃O���t�B�b�N���쐬
	//Font::SetStrTex(L"");

	//�퓬��ʃI�u�W�F�N�g�쐬
	CObjFight* obj = new CObjFight(10);		//(�퓬����)
	Objs::InsertObj(obj, OBJ_FIGHT, 1);		//�퓬��ʃI�u�W�F�N�g�o�^

	//�G���I�u�W�F�N�g�쐬
	CObjPlanet* obj0 = new CObjPlanet(250, 350, 10);	//�I�u�W�F�N�g�쐬
	Objs::InsertObj(obj0, OBJ_ENEMY,  5);					//�I�u�W�F�N�g�o�^

	//�����I�u�W�F�N�g�쐬
	CObjPlanet* obj1 = new CObjPlanet(950, 350, g_Player_max_size, -1);	//�I�u�W�F�N�g�쐬
	Objs::InsertObj(obj1, OBJ_PLANET, 10);					//�I�u�W�F�N�g�o�^

	//�����˃{�^��
	CObjRocketButton* obj2 = new CObjRocketButton(500, 550, 100, 100, 1);	//�I�u�W�F�N�g�쐬
	Objs::InsertObj(obj2, OBJ_POD_BUTTON1, 10);						//�I�u�W�F�N�g�o�^

	CObjRocketButton* obj3 = new CObjRocketButton(650, 550, 100, 100, 2);	//�I�u�W�F�N�g�쐬
	Objs::InsertObj(obj3, OBJ_POD_BUTTON2, 10);						//�I�u�W�F�N�g�o�^

	CObjRocketButton* obj4 = new CObjRocketButton(800, 550, 100, 100, 3);	//�I�u�W�F�N�g�쐬
	Objs::InsertObj(obj4, OBJ_POD_BUTTON3, 10);						//�I�u�W�F�N�g�o�^

	CObjRocketButton* obj5 = new CObjRocketButton(950, 550, 100, 100, 4);	//�I�u�W�F�N�g�쐬
	Objs::InsertObj(obj5, OBJ_POD_BUTTON4, 10);						//�I�u�W�F�N�g�o�^

	CObjRocketButton* obj6 = new CObjRocketButton(150, 550, 100, 200, 5);	//�I�u�W�F�N�g�쐬
	Objs::InsertObj(obj6, OBJ_MISSILE_BUTTON, 10);						//�I�u�W�F�N�g�o�^

	//�X�y�V�����Z�{�^��
	CObjSpecialButton* special = new CObjSpecialButton(1000.0f, 20.0f, 114.0f, 175.0f);	//�I�u�W�F�N�g�쐬
	Objs::InsertObj(special, OBJ_SPECIAL, 90);											//�I�u�W�F�N�g�o�^

	//�퓬�O���o�I�u�W�F�N�g
	CObjBefore_Fight_Effect* before_fight_effect = new CObjBefore_Fight_Effect(false);	//�퓬�O���o�I�u�W�F�N�g�쐬
	Objs::InsertObj(before_fight_effect, OBJ_BEFORE_FIGHT_EFFECT, 100);					//�퓬�O���o�I�u�W�F�N�g�o�^

	//���y�ǂݍ���
	Audio::LoadAudio(0, L"�U�h��.wav", BACK_MUSIC);

	//����
	Audio::LoadAudio(1, L"Sunset.wav", BACK_MUSIC);

	//�s�k
	Audio::LoadAudio(2, L"�߂��s�����X.wav", BACK_MUSIC);

	//SE�ǂݍ���
	Audio::LoadAudio(3, L"�I�����U�蕪���A�b�v�R.wav", EFFECT);
	Audio::LoadAudio(5, L"�傫������.wav", EFFECT);

	Audio::LoadAudio(6, L"�r�[�����P.wav", EFFECT);//Explosion&FractureLay

	Audio::LoadAudio(7, L"�o���A�Q.wav", EFFECT);//Immortality

	Audio::LoadAudio(8, L"�|�b�h�A�b�v�P.wav", EFFECT);//���~�b�g�u���C�N���X�e���C�h���^

	Audio::LoadAudio(9, L"�H�ׂ鉹.wav", EFFECT);

	Audio::LoadAudio(10, L"�X�؃V�����Z������.wav", EFFECT);

	//���y�X�^�[�g
	Audio::Start(0);

}

//�Q�[�����C�����s�����\�b�h
void CSceneFight::Scene()
{

}