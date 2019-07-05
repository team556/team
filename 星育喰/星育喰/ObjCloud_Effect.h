#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "ObjTraining.h"	//���N���X�Ƃ��Ē�`���邽�ߓǂݍ���
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�_���o
class CObjCloud_Effect :public CObjTraining	//CObjTraining���p������
{
public:
	CObjCloud_Effect(bool check);
	~CObjCloud_Effect() {};
	void Init();     //�C�j�V�����C�Y
	void Action();   //�A�N�V����
	void Draw();     //�h���[
	void SetCheck(bool check) { m_In_Out_Check = check; }//�_���oIN / OUT�ύX�p
private:
	bool m_In_Out_Check;	//�_���oIN / OUT�`�F�b�N(true=�_���oIN / false=�_���oOUT)
	float m_Cloud_move;		//�_�̈ړ��p�x�N�g��
	float m_white_out_a;	//�z���C�g�A�E�g���o�摜���ߓx
	float m_white_out_a_vec;//�z���C�g�A�E�g���o�摜���ߓx�x�N�g��

	int   m_time;	 //�{�݃��x���A�b�v����炷���ԊǗ��p
	bool  m_level_se;//�{�݃��x���A�b�v���t���O
	bool  m_white_se;//�z���C�g�A�E�g���t���O
};