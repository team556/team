#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�^�C�g��
class CObjTitle :public CObj
{
public:
	CObjTitle() {};
	~CObjTitle() {};
	void Init();     //�C�j�V�����C�Y
	void Action();   //�A�N�V����
	void Draw();     //�h���[
private:
	float m_Click_y;	//�N���b�N�ŃX�^�[�g�̈ʒu�x
	float m_Click_vy;	//�N���b�N�ŃX�^�[�g�̈ړ��p�x�N�g���x
	float m_r;			//�T�C���J�[�u�p�̊p�x(�N���b�N�ŃX�^�[�g�㉺�ӂ�ӂ�Ɏg�p)
	
	float m_mou_x;//�}�E�X�̈ʒuX(�f�o�b�N�p)
	float m_mou_y;//�}�E�X�̈ʒuY(�f�o�b�N�p)

	int m_time;
	int m_enemy_time;
	int m_Planet_Count;
	int m_enemy_y;
};