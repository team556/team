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
	float m_Bar_color;			//���ɃJ���[���x
	float m_Bar_Lvup_color;		//���Ƀ��x��UP�J���[���x
	float m_Human_up_color[4];	//�Z���U�蕪��UP�J���[���x
	float m_Human_down_color[4];//�Z���U�蕪��DOWN�J���[���x

	int m_Warrior[4];	//���ɂɊ���U���Ă���Z���ۑ��p
};