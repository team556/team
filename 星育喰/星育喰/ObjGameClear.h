#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//#include "ObjTraining.h"//���N���X�Ƃ��Ē�`���邽�ߓǂݍ���
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�^�C�g��
class CObjGameClear :public CObj
{
public:
	CObjGameClear() {};
	~CObjGameClear() {};
	void Init();     //�C�j�V�����C�Y
	void Action();   //�A�N�V����
	void Draw();     //�h���[
private:
	float m_x;
	float m_y;
	bool  m_f;

	float m_mou_x;		//�}�E�X�̈ʒuX
	float m_mou_y;		//�}�E�X�̈ʒuY
	bool  m_mou_r;		//�}�E�X�v�b�V���m�F(�E�N���b�N)
	bool  m_mou_l;		//�}�E�X�v�b�V���m�F(���N���b�N)

	float m_y_vec;	//y���x�N�g��
	float m_cy[20];	//char��y��
	int m_c_nam;		//char�̃i���o�[
};