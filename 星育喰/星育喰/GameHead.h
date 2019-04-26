#pragma once

//�I�u�W�F�N�g�l�[��------------------------------
enum OBJ_NAME
{
	OBJ_NO_NAME,	//�I�u�W�F�N�g������(�֎~)
	//�Q�[���Ŏg���I�u�W�F�N�g�̖��O
	//OBJ_�����ƕ\�L

	OBJ_TITLE,
	OBJ_HOME,
	OBJ_TEST,
	OBJ_HUMAN,
	OBJ_PLANET,
	OBJ_ENEMY,
	OBJ_ENEMY2,
	OBJ_CLOUD,
	OBJ_TRAINING,
	OBJ_PREPARATION,
	OBJ_FIGHT,
	OBJ_WAREHOUSE,
	OBJ_INSTITUTE,
	OBJ_BARRACKS,
	OBJ_MISSILE,
	OBJ_FIGHT_CLEAR,
	OBJ_FIGHT_OVER,

};
//------------------------------------------------

//�����蔻�葮��----------------------------------
enum HIT_ELEMENTS
{
	ELEMENT_NULL,//�������� �S�Ă̑����Ɠ����蔻�肪���s�����
	//�ȉ��@�����������m�ł͓����蔻��͎��s����Ȃ�
	//�����͒ǉ��\�����A�f�o�b�N���̐F�͏����ݒ蕪��������
	ELEMENT_PLAYER,
	ELEMENT_ENEMY,
	ELEMENT_ITEM,
	ELEMENT_MAGIC,
	ELEMENT_FIELD,
	ELEMENT_RED,
	ELEMENT_GREEN,
	ELEMENT_BLUE,
	ELEMENT_BLACK,
	ELEMENT_WHITE,
	ELEMENT_FACILITY,
	ELEMENT_BUILD,
};
//------------------------------------------------

//------------------------------------------------
//�Z�[�u�����[�h�ƃV�[���Ԃ̂���肷��f�[�^
struct UserData
{
	int mSeveData;	//�T���v���Z�[�u�f�[�^
	
};
//------------------------------------------------


//�Q�[�����Ŏg�p�����O���[�o���ϐ��E�萔�E��--
extern int g_Stage_progress;		//���݂̃X�e�[�W�i�s�x(1�X�e�[�W:1�@2�X�e�[�W:2�@3�X�e�[�W:3)
extern int g_Bar_Level;				//���Ƀ��x��
extern int g_Ins_Level;				//���������x��
extern int g_Mis_Recast_Level;		//�~�T�C�����L���X�g���x��
extern int g_Pow_equip_Level;		//���݂̃p���[���탌�x��
extern int g_Pow_equip_Lv_achieve;	//�p���[���탌�x���̍ő哞�B�x
extern int g_Def_equip_Level;		//���݂̃f�B�t�F���X���탌�x��
extern int g_Def_equip_Lv_achieve;	//�f�B�t�F���X���탌�x���̍ő哞�B�x
extern int g_Spe_equip_Level;		//���݂̃X�s�[�h���탌�x��
extern int g_Spe_equip_Lv_achieve;	//�X�s�[�h���탌�x���̍ő哞�B�x
extern int g_Bal_equip_Level;		//���݂̃o�����X���탌�x��
extern int g_Bal_equip_Lv_achieve;	//�o�����X���탌�x���̍ő哞�B�x
extern int g_Pod_equip_Level;		//���݂̃|�b�h���x��
extern int g_Pod_equip_Lv_achieve;	//�|�b�h���x���̍ő哞�B�x
extern int g_Special_equipment;		//���ݑ������̃X�y�V�����Z(0:�������@1:�G�ɑ�_���[�W�@2:���E���@3:��莞�Ԗ��G�@4:���Y�������A�b�v�@5:�Z���̎m�C���A�b�v)
extern bool g_Special_mastering[5];	//�K���ς݂̃X�y�V�����Z			(0:�G�ɑ�_���[�W�@1:���E���@2:��莞�Ԗ��G�@3:���Y�������A�b�v�@4:�Z���̎m�C���A�b�v)
extern int g_Power_num;				//�p���[�Z����
extern int g_Defense_num;			//�f�B�t�F���X�Z����
extern int g_Speed_num;				//�X�s�[�h�Z����
extern int g_Balance_num;			//�o�����X�Z����
extern int g_Research_num;			//�������Z����
extern int g_Remain_num;			//�c��Z����

extern int g_Material_num_test;		//TEST�p�����f�ސ�

extern bool g_key_fg;//

//------------------------------------------------
//�Q�[�����Ŏg�p����N���X�w�b�_------------------


//------------------------------------------------

//�Q�[���V�[���I�u�W�F�N�g�w�b�_------------------
#include "ObjTitle.h"
#include "ObjHome.h"
#include "ObjTest.h"
#include "ObjHuman.h"
#include "ObjCloud_Effect.h"
#include "ObjBarracks.h"
#include "ObjPlanet.h"
#include "ObjTraining.h"
#include "ObjPreparation.h"
#include "ObjFight.h"
#include "ObjPushUnit.h"
#include "ObjMissile.h"
#include "ObjBarracks.h"
#include "ObjInstitute.h"
#include "ObjWarehouse.h"
#include "ObjMaterialBotton.h"
#include "ObjFightClear.h"
#include "ObjFightOver.h"

//------------------------------------------------

//�Q�[���V�[���N���X�w�b�_------------------------
#include "SceneTitle.h"
#include "SceneHome.h"
#include "SceneTest.h"
#include "SceneTraining.h"
#include "ScenePreparation.h"
#include "SceneFight.h"

//-----------------------------------------------

//�V�[���X�^�[�g�N���X---------------------------
//�Q�[���J�n���̃V�[���N���X�o�^
//#define SET_GAME_START CSceneTitle
//#define SET_GAME_START CSceneFight
#define SET_GAME_START CSceneTraining
//#define SET_GAME_START CSceneTest
//-----------------------------------------------