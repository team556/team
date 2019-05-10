#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "ObjFight.h"	//���N���X�Ƃ��Ē�`���邽�ߓǂݍ���
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�f��(�v���C���[ & �G)
class CObjPlanet :public CObjFight //CObjFight���p������
{
public:
	CObjPlanet(float x, float y, float hp, bool type, float siz = 0);//���W+HP+�^�C�v+�T�C�Y
	~CObjPlanet() {};
	void Init();	//�C�j�V�����C�Y
	void Action();  //�A�N�V����
	void Draw();    //�h���[

	//float GetX() { return m_px; }
	//float GetY() { return m_py; }
	float GetHp() { return m_hp; }	//�J�E���g����Ԃ�
	//float GetSiz() { return (m_siz_vec + m_size); }
	void SetEeatF() { m_eat_f = true; }//�Z�b�g�򂤃t���O

	void SetDelF() { m_del_f = true; }//�Z�b�g�����t���O
private:

	float m_px;			//�����WX
	float m_py;			//�����WY
	float m_size;		//���T�C�Y
	float m_siz_max;	//�T�C�Y�}�b�N�X
	float m_siz_vec;	//�T�C�Y�ύX�x�N�g��
	float m_siz_spd;	//�T�C�Y�ύX�X�s�[�h
	float m_get_siz;	//�Q�b�g�T�C�Y
	float m_mov_spd;	//�f���ړ��X�s�[�h

	float m_hp;			//�q�b�g�|�C���g
	float m_get_hp;		//�Q�b�gHP
	int m_cnt;			//�J�E���g
	bool m_type;		//�f���^�C�v(true��l��)

	int m_time;
	int m_attackf;

	float m_create_x;	//�G�f���~�T�C���|�b�h�쐬X�ʒu�����p
	
	int m_ani[4];
	int m_ani_time;
	int m_ani_frame;

	bool m_eat_f;		//�򂤃t���O(true = ��)
	float m_eat_spd;
	bool m_del_f;		//�����t���O(true = ����)

	int m_cntf;
};