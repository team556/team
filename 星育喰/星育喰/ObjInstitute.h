#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "ObjTraining.h"	//���N���X�Ƃ��Ē�`���邽�ߓǂݍ���
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F������
class CObjInstitute :public CObjTraining //CObjTraining���p������
{
public:
	CObjInstitute() {};
	~CObjInstitute() {};
	void Init();     //�C�j�V�����C�Y
	void Action();   //�A�N�V����
	void Draw();     //�h���[
private:
	float m_Ins_color;			//�������J���[���x
	float m_Ins_Lvup_color;		//���������x��UP�J���[���x
	float m_Human_up_color;		//�Z���U�蕪��UP�J���[���x
	float m_Human_down_color;	//�Z���U�蕪��DOWN�J���[���x
};