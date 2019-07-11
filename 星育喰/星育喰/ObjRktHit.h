#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//#include "ObjTraining.h"//���N���X�Ƃ��Ē�`���邽�ߓǂݍ���
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�^�C�g��
class CObjRktHit :public CObj

{
public:
	CObjRktHit(float x, float y, bool t);//���W�A�^�C�v�A
	~CObjRktHit() {};
	void Init();     //�C�j�V�����C�Y
	void Action();   //�A�N�V����
	void Draw();     //�h���[
private:
	float m_x;		//���WX
	float m_y;		//���WY
	float m_vx;		//X�ړ��pvec
	float m_vy;		//Y�ړ��pvec
	float m_mov;	//Y�ϑ��ړ��p
	float m_mov_spd;//�����X�s�[�h
	float m_size;	//�c���T�C�Y(50)

	int m_get_line;	//�퓬�V�[������Get����line
	int m_del_cnt;	//�폜�܂ł̃J�E���g�p

	bool m_atk_f;	//���p(true = �퓬��)
	bool m_type;	//�^�C�v(true = �G)
	bool m_del_f;	//�폜�t���O(true = �폜)
	bool m_ppod_f;	//�v���C���[�|�b�h�ƐڐG���t���O(true = �ڐG��)
	bool m_epod_f;	//�G�l�~�[�|�b�h�ƐڐG���t���O(true = �ڐG��)
};