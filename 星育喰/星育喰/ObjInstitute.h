#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "ObjTraining.h"	//���N���X�Ƃ��Ē�`���邽�ߓǂݍ���
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�}�N��
#define MIS_MAX_LV (5) //�~�T�C�����L���X�g��MAX���x��(�����߂�"5"�Ƃ��Ă���)

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
	float m_Mis_Button_color;	//�~�T�C���{�^���J���[���x
	float m_Equ_Button_color;	//����|�b�h�{�^���J���[���x

	float m_Mis_recast_time[MIS_MAX_LV];			//�~�T�C�����L���X�g�^�C��
	int m_Mis_recast_next_Ins_Lv[MIS_MAX_LV - 1];	//�~�T�C�����L���X�g�̎���LVUP�ɕK�v�Ȍ��������x���Ǘ��p
	int m_Mis_recast_next_Hum_num[MIS_MAX_LV - 1];	//�~�T�C�����L���X�g�̎���LVUP�ɕK�v�Ȍ������̏Z�����Ǘ��p
};