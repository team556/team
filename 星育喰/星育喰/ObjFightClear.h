#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�N���A���
class CObjFightClear :public CObj
{
public:
	CObjFightClear(int p, int m, int s, int l);
	~CObjFightClear() {};
	void Init();     //�C�j�V�����C�Y
	void Action();   //�A�N�V����
	void Draw();     //�h���[
private:
	//float m_x;
	//float m_y;
	//bool  m_f;

	//float m_mou_x;		//�}�E�X�̈ʒuX
	//float m_mou_y;		//�}�E�X�̈ʒuY
	//bool  m_mou_r;		//�}�E�X�v�b�V���m�F(�E�N���b�N)
	bool  m_mou_l;		//�}�E�X�v�b�V���m�F(���N���b�N)

	float m_a;		//alpha �����x
	float m_a_vec;	//m_a�x�N�g��
	bool m_a_f;		//�s�������t���O

	int m_people;	//�Z��
	int m_mrl;		//�}�e���A���Y(����)
	int m_skill;	//�X�y�V�����Z
	int m_large;		//�T�C�Y

	int m_cnt;		//�J�E���g
};