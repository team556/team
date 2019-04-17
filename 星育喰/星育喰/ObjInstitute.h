#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "ObjTraining.h"	//���N���X�Ƃ��Ē�`���邽�ߓǂݍ���
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�}�N��
#define MIS_MAX_LV (5) //�~�T�C�����L���X�g��MAX���x��(�����߂�"5"�Ƃ��Ă���)
#define EQU_MAX_LV (3) //�e����|�b�h��MAX���x��

//�I�u�W�F�N�g�F������
class CObjInstitute :public CObjTraining //CObjTraining���p������
{
public:
	CObjInstitute() {};
	~CObjInstitute() {};
	void Init();     //�C�j�V�����C�Y
	void Action();   //�A�N�V����
	void Draw();     //�h���[

	int Equip_Lvup_check(int equip_id, int equip_Level, int equip_Lv_achieve);//����|�b�h���x��UP�`�F�b�N�֐�
	int Equip_Lvdown_check(int equip_id, int equip_Level);					//����|�b�h���x��DOWN�`�F�b�N�֐�
private:
	float m_Ins_color;				//�������J���[���x
	float m_Ins_Lvup_color;			//���������x��UP�J���[���x
	float m_Human_up_color;			//�Z���U�蕪��UP�J���[���x
	float m_Human_down_color;		//�Z���U�蕪��DOWN�J���[���x
	float m_Mis_Button_color;		//�~�T�C���{�^���J���[���x
	float m_Equ_Button_color;		//����|�b�h�{�^���J���[���x
	float m_Equ_pic_red_color[15];	//����|�b�h�摜�W�J���[(Red)
	float m_Equ_pic_green_color[15];//����|�b�h�摜�W�J���[(Green)
	float m_Equ_pic_blue_color[15];	//����|�b�h�摜�W�J���[(Blue)

	//wchar_t m_Wep_message[3(��3�s�����ɗp��)][100(�����镶����)];//����K�v�f��&�l�����b�Z�[�W�̃t�H���g�p

	float m_Mis_recast_time[MIS_MAX_LV];			//�~�T�C�����L���X�g�^�C��
	int m_Mis_recast_next_Ins_Lv[MIS_MAX_LV - 1];	//�~�T�C�����L���X�g�̎���LVUP�ɕK�v�Ȍ��������x���Ǘ��p
	int m_Mis_recast_next_Hum_num[MIS_MAX_LV - 1];	//�~�T�C�����L���X�g�̎���LVUP�ɕK�v�Ȍ������̏Z�����Ǘ��p
	
	int m_Equ_next_Hum_num[5][EQU_MAX_LV - 1];		//�e����A�|�b�h�̎���LVUP�ɕK�v�Ȍ������̏Z�����Ǘ��p
	int m_Equ_next_Mat_type[5][EQU_MAX_LV - 1];		//�e����A�|�b�h�̎���LVUP�ɕK�v�ȑf�ގ�ނƂ��̑f�ނ̏��������Ǘ�
	int m_Equ_next_Mat_num[5][EQU_MAX_LV - 1];		//�e����A�|�b�h�̎���LVUP�ɕK�v�ȑf�ސ��Ǘ��p(���ŕK�v�f��1��ނƂ��čl���Ă���B2��ވȏ�Ȃ炻�̕�Mat_type��Mat_num�𑝂₷�\��)
};