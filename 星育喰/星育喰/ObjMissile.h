#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�^�C�g��
class CObjMissile :public CObj
{
public:
	CObjMissile(float x, float y,bool type);
	~CObjMissile() {};
	void Init();     //�C�j�V�����C�Y
	void Action();   //�A�N�V����
	void Draw();     //�h���[
private:
	float m_x;		//�~�T�C���̍��WX
	float m_y;		//�~�T�C���̍��WY
	float m_vx;		//�x�N�g��X
	float m_vy;		//�x�N�g��Y
	float m_size;	//�~�T�C���̃T�C�Y
	bool  m_mou_f;	//�}�E�X�t���b�O

	float m_r;		//�~�T�C���p�x
	float m_mov;	//
	float m_mov_spd;//��������
	float m_psize;

	float m_mou_x;		//�}�E�X�̈ʒuX
	float m_mou_y;		//�}�E�X�̈ʒuY
	bool  m_mou_r;		//�}�E�X�v�b�V���m�F(�E�N���b�N)
	bool  m_mou_l;		//�}�E�X�v�b�V���m�F(���N���b�N)

	int m_get_line;		//�擾�������C���i���o�[
	int m_get_cnt;		//�擾�����J�E���g


	bool m_type;		//�������̃^�C�v
};