#pragma once

//�I�u�W�F�N�g�l�[��------------------------------
enum OBJ_NAME
{
	OBJ_NO_NAME,	//�I�u�W�F�N�g������(�֎~)
	//�Q�[���Ŏg���I�u�W�F�N�g�̖��O
	//OBJ_�����ƕ\�L
	OBJ_TEST,
	OBJ_TITLE,
	OBJ_HOME,
	//OBJ_HUMAN,
	OBJ_PLANET,
	OBJ_ENEMY,
	OBJ_POD_BUTTON1,
	OBJ_POD_BUTTON2,
	OBJ_POD_BUTTON3,
	OBJ_POD_BUTTON4,
	OBJ_MISSILE_BUTTON,
	OBJ_SPECIAL,
	OBJ_CLOUD,
	OBJ_BEFORE_FIGHT_EFFECT,
	OBJ_TRAINING,
	OBJ_PREPARATION,
	OBJ_FIGHT,
	OBJ_WAREHOUSE,
	OBJ_INSTITUTE,
	OBJ_BARRACKS,
	OBJ_ROCKET,
	OBJ_FRACTURE_RAY,
	OBJ_FIGHT_CLEAR,
	OBJ_FIGHT_OVER,
	OBJ_FIGHT_Rocket,
	OBJ_PODP,
	OBJ_PODD,
	OBJ_PODS,
	OBJ_PODB,
	OBJ_HELP,
	OBJ_GAME_CLEAR,
	OBJ_MESSAGE,
	OBJ_RKTHIT,
	OBJ_RKTHIT1,
	OBJ_RKTHIT2,
	OBJ_RKTHIT3,
	OBJ_RKTHIT4,
	OBJ_RKTHIT5,
	OBJ_RKTHIT6,
	OBJ_RKTHIT7,
	OBJ_RKTHIT8,
	OBJ_RKTHIT9,
	OBJ_eRKTHIT,
	OBJ_eRKTHIT1,
	OBJ_eRKTHIT2,
	OBJ_eRKTHIT3,
	OBJ_eRKTHIT4,
	OBJ_eRKTHIT5,
	OBJ_eRKTHIT6,
	OBJ_eRKTHIT7,
	OBJ_eRKTHIT8,
	OBJ_eRKTHIT9,
	OBJ_NAME_INPUT,

};
//------------------------------------------------

//�����蔻�葮��----------------------------------
enum HIT_ELEMENTS
{
	ELEMENT_NULL,//�������� �S�Ă̑����Ɠ����蔻�肪���s�����
	//�ȉ��@�����������m�ł͓����蔻��͎��s����Ȃ�
	//�����͒ǉ��\�����A�f�o�b�N���̐F�͏����ݒ蕪��������
	ELEMENT_PLAYER,		//�v���C���[�f���̓����蔻�葮��
	ELEMENT_ENEMY,		//�G�l�~�[�f���̓����蔻�葮��
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
	ELEMENT_POD,
	ELEMENT_POD1,
	ELEMENT_POD2,
	ELEMENT_POD3,
	ELEMENT_POD4,
	ELEMENT_POD5,
	ELEMENT_POD6,
	ELEMENT_POD7,
	ELEMENT_POD8,
	ELEMENT_POD9,
	ELEMENT_ENEMYPOD,
	ELEMENT_ENEMYPOD1,
	ELEMENT_ENEMYPOD2,
	ELEMENT_ENEMYPOD3,
	ELEMENT_ENEMYPOD4,
	ELEMENT_ENEMYPOD5,
	ELEMENT_ENEMYPOD6,
	ELEMENT_ENEMYPOD7,
	ELEMENT_ENEMYPOD8,
	ELEMENT_ENEMYPOD9,
	ELEMENT_P_MIS,		//�v���C���[��
	ELEMENT_E_MIS,		//�G�̃~�T�C��
	ELEMENT_LINE,

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
//���Z�[�u�K�v���L��
extern int g_Stage_progress;		//���݂̃X�e�[�W�i�s�x(1�X�e�[�W:1�@2�X�e�[�W:2�@3�X�e�[�W:3)
extern bool g_destroy_progress[4];	//0~3�̓G(�{�X�f���ȊO�̓G�f��)�̌��j���(false:���� , true:���j)
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
extern float g_Player_max_size;		//���݂̃v���C���[�f���̃T�C�Y(�ő�HP)
extern int g_Special_equipment;		//���ݑ������̃X�y�V�����Z(0:�������@1:Explosion�@2:Fracture_Ray�@3:Immortality�@4:���~�b�g�u���C�N�@5:�X�e���C�h���^)
extern bool g_Special_mastering[5];	//�K���ς݂̃X�y�V�����Z[true:�K����  false:���K��](0:Explosion�@1:Fracture_Ray�@2:Immortality�@3:���~�b�g�u���C�N�@4:�X�e���C�h���^)
extern int g_Power_num;				//�p���[�Z����
extern int g_Defense_num;			//�f�B�t�F���X�Z����
extern int g_Speed_num;				//�X�s�[�h�Z����
extern int g_Balance_num;			//�o�����X�Z����
extern int g_Research_num;			//�������Z����
extern int g_Remain_num;			//�c��Z����
extern float g_Recast_time;			//�~�T�C���̃��L���X�g�^�C���p
//extern float g_Missile_pow;			//�~�T�C���̉Η͗p
//extern int g_E_Planet_damage;					//
extern float g_P_Planet_damage;					//�G�|�b�h���f���ɗ^����_���[�W�ۑ��p
//extern int g_Enemy_Pod_LV;			//�e�X�g�p�G�|�b�h���x��
//--------------------------------------------------����----
extern int g_Iron_num;				//�S�̏�����
extern int g_Wood_num;				//�؂̏�����
extern int g_Silver_num;        //��
extern int g_Plastic_num;		//�v���X�`�b�N
extern int g_Aluminum_num;		//�A���~�j�E��
extern int g_gus_num;			//�K�X

//���Z�[�u�K�v������
extern int g_Challenge_enemy;		//�퓬���s���G�f�����ʔԍ�(0:������1�Ԗڂ̓G�f���@1:������2�Ԗڂ̓G�f���@2:������3�Ԗڂ̓G�f���@3:������4�Ԗڂ̓G�f���@4:�{�X�f���@5:�`���[�g���A���f��)
extern bool g_help_f;				//�w���v��ʕ\���t���O(true:�w���v��ʕ\���@false:�w���v��ʔ�\��)
extern int  g_tutorial_progress;	//���݂̃`���[�g���A���i�s�x
extern bool g_is_operatable;		//�`���[�g���A���ɂđ���\���m�F�t���O(true:����\�@false;����s��)[���b�Z�[�W��ǂݐi�߂鎞�Ɍ��̃{�^�������������Ȃ��悤�ɂ���ׂɎg�p]

//���萔
#define CUT_ZERO 1625		//�����W�Ő�����؂���Ƃ���0�̈ʒu
#define END_ZERO 1750		//�����W�Ő�����؂���Ƃ���0�̈ʒu

//------------------------------------------------
//�Q�[�����Ŏg�p����N���X�w�b�_------------------


//------------------------------------------------

//�Q�[���V�[���I�u�W�F�N�g�w�b�_------------------
#include "ObjTitle.h"
#include "ObjHome.h"
#include "ObjTest.h"
//#include "ObjHuman.h"
#include "ObjCloud_Effect.h"
#include "ObjBefore_Fight_Effect.h"
#include "ObjBarracks.h"
#include "ObjPlanet.h"
#include "ObjTraining.h"
#include "ObjPreparation.h"
#include "ObjFight.h"
#include "ObjRocketButton.h"
#include "ObjRocket.h"
#include "ObjSpecialButton.h"
#include "ObjBarracks.h"
#include "ObjInstitute.h"
#include "ObjWarehouse.h"
#include "ObjMaterialBotton.h"
#include "ObjFightClear.h"
#include "ObjFightOver.h"
#include "ObjHelp.h"
#include "ObjGameClear.h"
#include "ObjMessage.h"
#include "ObjRktHit.h"
#include "ObjNameInput.h"

//------------------------------------------------

//�Q�[���V�[���N���X�w�b�_------------------------
#include "SceneTitle.h"
#include "SceneHome.h"
#include "SceneTest.h"
#include "SceneTraining.h"
#include "ScenePreparation.h"
#include "SceneFight.h"
#include "SceneGameClear.h"
#include "SceneNameInput.h"

//-----------------------------------------------

//�V�[���X�^�[�g�N���X---------------------------
//�Q�[���J�n���̃V�[���N���X�o�^
//#define SET_GAME_START CSceneTitle
//#define SET_GAME_START CSceneHome
//#define SET_GAME_START CSceneFight
//#define SET_GAME_START CSceneTraining
//#define SET_GAME_START CSceneGameClear
#define SET_GAME_START CScenePreparation
//#define SET_GAME_START CSceneNameInput
//----------------------------------------------