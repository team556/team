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

	int Allocation(int type_num, int up_down_check);//�U�蕪���֐�
private:
	float m_size;		//�v���C���[�f���̃T�C�Y

	int m_Mig_time;		//�z�[����ʂɃV�[���ڍs����ۂ̎��ԊǗ��ϐ�
protected:
	float m_mou_x;		 //�}�E�X�̈ʒuX
	float m_mou_y;		 //�}�E�X�̈ʒuY
	bool  m_mou_r;		 //�}�E�X�v�b�V���m�F(�E�N���b�N)
	bool  m_mou_l;		 //�}�E�X�v�b�V���m�F(���N���b�N)
	bool  m_introduce_f; //�{�ݏЉ�E�C���h�E�\���Ǘ��t���O(true:�\�� / false:��\��)
	bool  m_key_lf;		 //���N���b�N�p�L�[�t���O
	static bool m_key_rf;//�E�N���b�N�p�L�[�t���O

	float m_Back_Button_color;	//�߂�{�^���J���[���x

	wchar_t m_message[18];		//�}�E�X�J�[�\���㕔�ɕ`�悷��ȈՃ��b�Z�[�W(�G���[���b�Z�[�W�A���x��UP�\����)�̃t�H���g�p
	float	m_message_red_color;	//�ȈՃ��b�Z�[�W�J���[(Red)
	float	m_message_green_color;	//�ȈՃ��b�Z�[�W�J���[(Green)
	float	m_message_blue_color;	//�ȈՃ��b�Z�[�W�J���[(Blue)
	float	m_alpha;				//�}�E�X�J�[�\���㕔�ɕ`�悷��O���t�B�b�N�̓��ߓx(�A���t�@�l)

	static bool scene_change_start;	//�V�[���؂�ւ����o�J�n��`����t���O
	static int  window_start_manage;//�{�݃E�C���h�E�̋N���Ǘ��t���O

	//���e�{�݃E�C���h�E(�߂�{�^���܂�)�ɗ񋓌^�Ŏ��ʔԍ�������U��
	enum window_id	
	{
		Default,	//�f�t�H���g�B�ǂ̃E�C���h�E���J���Ă��Ȃ���ԁB
		BackButton,	//�߂�{�^���������āA�z�[����ʂɖ߂낤�Ƃ��Ă����ԁB
		Barracks,	//���ɃE�C���h�E���J���Ă����ԁB
		Institute,	//�������E�C���h�E���J���Ă����ԁB
		Missile,	//�~�T�C���E�C���h�E���J���Ă����ԁB
		Equipment,	//����|�b�h�E�C���h�E���J���Ă����ԁB
		Finalcheck,	//�ŏI�m�F�E�C���h�E���J���Ă����ԁB
		Warehouse,	//�q�ɃE�B���h�E���J���Ă����ԁB
		Materials,	//���ރE�B���h�E���J���Ă����ԁB
		Residents,	//�Z���E�B���h�E���J���Ă����ԁB
		Specialskill,//�X�y�V�����Z�E�B���h�E���J���Ă����ԁB
	};
};