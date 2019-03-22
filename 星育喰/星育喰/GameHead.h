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
	OBJ_CLOUD,
	OBJ_TRAINING,
	OBJ_FIGHT,
	OBJ_BUILD,
	OBJ_WAREHOUSE,
	OBJ_INSTITUTE,
	OBJ_BARRACKS,
	OBJ_MATERIALBOTTON,
	OBJ_MISSILE,

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
extern int g_test;


//------------------------------------------------
//�Q�[�����Ŏg�p����N���X�w�b�_------------------


//------------------------------------------------

//�Q�[���V�[���I�u�W�F�N�g�w�b�_------------------
#include "ObjTitle.h"
#include "ObjHome.h"
#include "ObjTest.h"
#include "ObjHuman.h"
#include "ObjCloud_Effect.h"
#include "ObjBuild.h"
#include "ObjBarracks.h"
#include "ObjPlanet.h"
#include "ObjTraining.h"
#include "ObjFight.h"
#include "ObjPushUnit.h"
#include "ObjMissile.h"
#include "ObjBarracks.h"
#include "ObjInstitute.h"
#include "ObjWarehouse.h"
#include "ObjMaterialBotton.h"

//------------------------------------------------

//�Q�[���V�[���N���X�w�b�_------------------------
#include "SceneMain.h"
#include "SceneTitle.h"
#include "SceneHome.h"
#include "SceneTest.h"
#include "SceneFacility.h"
#include "SceneTraining.h"
#include "SceneFight.h"

//-----------------------------------------------

//�V�[���X�^�[�g�N���X---------------------------
//�Q�[���J�n���̃V�[���N���X�o�^
//#define SET_GAME_START CSceneTitle
//#define SET_GAME_START CSceneFight
//-----------------------------------------------