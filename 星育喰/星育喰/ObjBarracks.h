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
	
	int Allocation(int human_num, int updown_flag);//
private:
	float m_Bar_color;			//���ɃJ���[���x
	float m_Human_up_color[4];	//�Z���U�蕪��UP�J���[���x
	float m_Human_down_color[4];//�Z���U�蕪��DOWN�J���[���x

	int m_Bar_Level_test;	//���Ƀ��x���Ǘ��ϐ�(��ɃO���[�o���ϐ��ɂ���\��)
	int m_power_num;	//�p���[�Z����(��ɃO���[�o���ϐ��ɂ���\��)
	int m_defense_num;	//�f�B�t�F���X�Z����(��ɃO���[�o���ϐ��ɂ���\��)
	int m_speed_num;	//�X�s�[�h�Z����(��ɃO���[�o���ϐ��ɂ���\��)
	int m_balance_num;	//�o�����X�Z����(��ɃO���[�o���ϐ��ɂ���\��)
	int m_remain_num;	//�c��Z����(��ɃO���[�o���ϐ��ɂ���\��)
};