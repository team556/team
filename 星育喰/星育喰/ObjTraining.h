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

	float m_mou_x;		//�}�E�X�̈ʒuX
	float m_mou_y;		//�}�E�X�̈ʒuY
	bool  m_mou_r;		//�}�E�X�v�b�V���m�F(�E�N���b�N)
	bool  m_mou_l;		//�}�E�X�v�b�V���m�F(���N���b�N)

	float m_Back_Button_color;	//�߂�{�^���J���[���x
	bool  m_Back_Button_flag;	//�߂�{�^���N���b�N�A�������͉E�N���b�N��true�t���O
	bool  m_Player_Display_flag;//�v���C���[�f���\���p�t���O

	int m_Mig_time;		//�z�[����ʂɃV�[���ڍs����ۂ̎��ԊǗ��ϐ�
	bool  m_key_f;		//�L�[�t���O

protected:
	static bool test_flag;//�{�݃E�C���h�E�̕����N���j�~�t���O(�ɂ���\��)
};