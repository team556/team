#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�w���v�{�^��
class CObjHelp :public CObj
{
public:
	CObjHelp(int Scene_num) { m_Scene_num = Scene_num; }//�쐬���ɓn���ꂽ�l���Am_Scene_num�ɑ��
	~CObjHelp() {};
	void Init();     //�C�j�V�����C�Y
	void Action();   //�A�N�V����
	void Draw();     //�h���[

	bool GetHelpF() { return m_help_f; }//�w���v��ʕ\����Ԏ擾�p
	//void SetHelpF() { m_help_f = true; }//�w���v��ʕ\����Ԑݒ�p
	
	//�V�[���ڍs�����������̃w���v�I�u�W�F�N�g�ɓ`����ׂ̃Z�b�^�[���邩���B
private:
	float m_mou_x;		//�}�E�X�̈ʒuX
	float m_mou_y;		//�}�E�X�̈ʒuY
	bool  m_mou_r;		//�}�E�X�v�b�V���m�F(�E�N���b�N)
	bool  m_mou_l;		//�}�E�X�v�b�V���m�F(���N���b�N)
	bool  m_key_f;		//�}�E�X�̘A�Ő���(�L�[�t���O)

	float m_Help_Button_color;	//�w���v�{�^���̃J���[���x
	float m_Back_Button_color;	//�߂�{�^���̃J���[���x

	bool  m_help_f;		//�w���v��ʕ\���t���O(true:�w���v��ʕ\���@false:�w���v��ʔ�\��)

	int m_page_num;		//���ݕ\�����̃w���v�摜�ԍ�(�y�[�W)
	int m_page_max;		//���݃V�[���ŕ\������w���v�摜(�y�[�W)�̍ő吔
	int m_Img_num;		//�摜�̓o�^�ԍ�(�V�[�����Ƀw���v�摜�o�^�ԍ����Ⴄ����m_Scene_num���l�����Ēl������)[����g��Ȃ��Ƃ��o����悤�ɑS�摜�ԍ�(�w���v�Ŏg����)���ꂷ��H]

	int m_Scene_num;	//���ݕ\�����̃V�[���ԍ�(1:�z�[�� ,2:�琬 ,3:����)

	//static int  window_start_manage;//�{�݃E�C���h�E�̋N���Ǘ��t���O

	////���e�{�݃E�C���h�E(�߂�{�^���܂�)�ɗ񋓌^�Ŏ��ʔԍ�������U��
	//enum window_id
	//{
	//	Default,	//�f�t�H���g�B�ǂ̃E�C���h�E���J���Ă��Ȃ���ԁB
	//	BackButton,	//�߂�{�^���������āA�z�[����ʂɖ߂낤�Ƃ��Ă����ԁB
	//	Barracks,	//���ɃE�C���h�E���J���Ă����ԁB
	//	Institute,	//�������E�C���h�E���J���Ă����ԁB
	//	Warehouse,	//�q�ɃE�B���h�E���J���Ă����ԁB
	//	Help,		//�w���v�E�B���h�E���J���Ă����ԁB
	//};

};