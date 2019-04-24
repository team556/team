#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�^�C�g��
class CObjPlanet :public CObj
{
public:
	CObjPlanet(float x, float y, float hp,bool type);//���W+�^�C�v���󂯎��
	~CObjPlanet() {};
	void Init();	//�C�j�V�����C�Y
	void Action();  //�A�N�V����
	void Draw();    //�h���[

	float GetX() { return m_px; }
	float GetY() { return m_px; }
	float GetHp() { return m_hp; }	//�J�E���g����Ԃ�
	void SetEeatF() { m_eat_f = true; }
private:

	float m_px;			//�����WX
	float m_py;			//�����WY
	float m_size;		//���T�C�Y
	float m_siz_max;	//�T�C�Y�}�b�N�X
	float m_siz_vec;	//�T�C�Y�ύX�x�N�g��
	float m_siz_spd;	//�T�C�Y�ύX�X�s�[�h
	float m_mov_spd;	//�f���ړ��X�s�[�h

	float m_hp;			//�q�b�g�|�C���g
	float m_get_hp;		//�Q�b�gHP
	int m_cnt;			//�J�E���g
	bool m_type;		//�f���^�C�v(true��l��)
	
	int m_ani[4];
	int m_ani_time;
	int m_ani_frame;

	bool m_eat_f;
};