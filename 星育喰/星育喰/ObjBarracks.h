#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "ObjTraining.h"	//���N���X�Ƃ��Ē�`���邽�ߓǂݍ���
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F����
class CObjBarracks :public CObjTraining	//CObjTraining���p������
{
public:
	CObjBarracks() {};
	~CObjBarracks() {};
	void Init();		//�C�j�V�����C�Y
	void Action();		//�A�N�V����
	void Draw();		//�h���[
private:
	float m_Bar_color;	//���ɃJ���[���x
	bool m_f;
};