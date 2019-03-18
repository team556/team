#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�琬���
class CObjTraining :public CObj
{
public:
	CObjTraining() {};
	~CObjTraining() {};
	void Init();     //�C�j�V�����C�Y
	void Action();   //�A�N�V����
	void Draw();     //�h���[
private:
	float m_size;		//�v���C���[�f���̃T�C�Y

	float m_Back_Button_color;	//�߂�{�^���J���[���x

	int m_Mig_time;		//�z�[����ʂɃV�[���ڍs����ۂ̎��ԊǗ��ϐ�
protected:
	float m_mou_x;		//�}�E�X�̈ʒuX
	float m_mou_y;		//�}�E�X�̈ʒuY
	bool  m_mou_r;		//�}�E�X�v�b�V���m�F(�E�N���b�N)
	bool  m_mou_l;		//�}�E�X�v�b�V���m�F(���N���b�N)
	bool  m_key_f;		//�L�[�t���O

	static bool scene_change_start;	//�V�[���؂�ւ����o�J�n��`����t���O
	static int  window_start_manage;//�{�݃E�C���h�E�̋N���Ǘ��t���O
	//�����������Fint�^�A�񋓂Ő錾�B���̐����̂��̂�������ł���悤�Ɋeobj�ŏ�������B
	//���Ȃ݂ɂ��̍ہAobjTraining������o���Ȃ��悤�ɂ��Ă����B(�E�N���b�N�L�����Z���������Ȃ����߂�)

	//���e�{�݃E�C���h�E(�߂�{�^���܂�)�ɗ񋓌^�Ŏ��ʔԍ�������U��
	enum window_id	
	{
		Default,	//�f�t�H���g�B�ǂ̃E�C���h�E���J���Ă��Ȃ���ԁB
		BackButton,	//�߂�{�^���������āA�z�[����ʂɖ߂낤�Ƃ��Ă����ԁB
		Barracks,	//���ɃE�C���h�E���J���Ă����ԁB
	};
};