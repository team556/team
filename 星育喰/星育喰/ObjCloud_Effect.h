#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�z�[��
class CObjCloud_Effect :public CObj
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
};