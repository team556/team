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

	bool  m_atk_f;	//���p(false = OFF, true = ON)
	bool  m_type;	//�^�C�v(false ���� , true �G)
};