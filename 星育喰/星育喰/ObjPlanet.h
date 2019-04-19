#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�^�C�g��
class CObjPlanet :public CObj
{
public:
	CObjPlanet(float x, float y, bool type);//���W+�^�C�v���󂯎��
	~CObjPlanet() {};
	void Init();	//�C�j�V�����C�Y
	void Action();  //�A�N�V����
	void Draw();    //�h���[
private:

	float m_px;			//�����WX
	float m_py;			//�����WY
	float m_size;		//���T�C�Y
	float m_siz_vec;	//�T�C�Y�ύX�x�N�g��
	float m_mov_spd;	//�f���ړ��X�s�[�h
	float m_siz_spd;	//�T�C�Y�ύX�X�s�[�h

	float m_hp;			//�q�b�g�|�C���g

	bool m_type;		//�f���^�C�v(true��l��)
	bool m_cnt_f;		//�J�E���g�t���O
	
};