#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//#include "ObjTraining.h"//���N���X�Ƃ��Ē�`���邽�ߓǂݍ���
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�^�C�g��
class CObjHelp :public CObj
{
public:
	CObjHelp(int Scene_num) { m_Scene_nam = Scene_num; }//�쐬���ɓn���ꂽ�l���Am_Scene_nam�ɑ��
	~CObjHelp() {};
	void Init();     //�C�j�V�����C�Y
	void Action();   //�A�N�V����
	void Draw();     //�h���[
private:
	float m_x;
	float m_y;
	bool  m_help_f;		//�w���v�\���t���O
	
	int m_page_nam;		//�y�[�W��
	float m_a;			//alpha(�����x)
	float m_a2;			//alpha2(�߂�{�^��)

	int m_Scene_nam;	//���ݕ\�����̃V�[���ԍ�(1:�z�[�� ,2:�琬 ,3:���� ,4:�퓬)
	int m_Img_nam;		//�摜�̓o�^�ԍ�

	float m_mou_x;		//�}�E�X�̈ʒuX
	float m_mou_y;		//�}�E�X�̈ʒuY
	bool  m_mou_r;		//�}�E�X�v�b�V���m�F(�E�N���b�N)
	bool  m_mou_l;		//�}�E�X�v�b�V���m�F(���N���b�N)

	bool m_key_f;		//�}�E�X�̘A�Ő���

	static int  window_start_manage;//�{�݃E�C���h�E�̋N���Ǘ��t���O

	//���e�{�݃E�C���h�E(�߂�{�^���܂�)�ɗ񋓌^�Ŏ��ʔԍ�������U��
	enum window_id
	{
		Default,	//�f�t�H���g�B�ǂ̃E�C���h�E���J���Ă��Ȃ���ԁB
		BackButton,	//�߂�{�^���������āA�z�[����ʂɖ߂낤�Ƃ��Ă����ԁB
		Barracks,	//���ɃE�C���h�E���J���Ă����ԁB
		Institute,	//�������E�C���h�E���J���Ă����ԁB
		Warehouse,	//�q�ɃE�B���h�E���J���Ă����ԁB
		Help,		//�w���v�E�B���h�E���J���Ă����ԁB
	};

};