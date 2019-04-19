#pragma once

//オブジェクトネーム------------------------------
enum OBJ_NAME
{
	OBJ_NO_NAME,	//オブジェクト名無し(禁止)
	//ゲームで使うオブジェクトの名前
	//OBJ_○○と表記

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

//当たり判定属性----------------------------------
enum HIT_ELEMENTS
{
	ELEMENT_NULL,//属性無し 全ての属性と当たり判定が実行される
	//以下　同じ属性同士では当たり判定は実行されない
	//属性は追加可能だが、デバック時の色は初期設定分しか無い
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
//セーブ＆ロードとシーン間のやり取りするデータ
struct UserData
{
	int mSeveData;	//サンプルセーブデータ
	
};
//------------------------------------------------


//ゲーム内で使用されるグローバル変数・定数・列挙--
extern int g_Bar_Level;				//兵舎レベル
extern int g_Ins_Level;				//研究所レベル
extern int g_Mis_Recast_Level;		//ミサイルリキャストレベル
extern int g_Pow_equip_Level;		//現在のパワー武器レベル
extern int g_Pow_equip_Lv_achieve;	//パワー武器レベルの最大到達度
extern int g_Def_equip_Level;		//現在のディフェンス武器レベル
extern int g_Def_equip_Lv_achieve;	//ディフェンス武器レベルの最大到達度
extern int g_Spe_equip_Level;		//現在のスピード武器レベル
extern int g_Spe_equip_Lv_achieve;	//スピード武器レベルの最大到達度
extern int g_Bal_equip_Level;		//現在のバランス武器レベル
extern int g_Bal_equip_Lv_achieve;	//バランス武器レベルの最大到達度
extern int g_Pod_equip_Level;		//現在のポッドレベル
extern int g_Pod_equip_Lv_achieve;	//ポッドレベルの最大到達度
extern int g_Power_num;				//パワー住民数
extern int g_Defense_num;			//ディフェンス住民数
extern int g_Speed_num;				//スピード住民数
extern int g_Balance_num;			//バランス住民数
extern int g_Research_num;			//研究員住民数
extern int g_Remain_num;			//残り住民数

extern int g_Material_num_test;		//TEST用所持素材数


//------------------------------------------------
//ゲーム内で使用するクラスヘッダ------------------


//------------------------------------------------

//ゲームシーンオブジェクトヘッダ------------------
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

//ゲームシーンクラスヘッダ------------------------
#include "SceneMain.h"
#include "SceneTitle.h"
#include "SceneHome.h"
#include "SceneTest.h"
#include "SceneFacility.h"
#include "SceneTraining.h"
#include "SceneFight.h"

//-----------------------------------------------

//シーンスタートクラス---------------------------
//ゲーム開始時のシーンクラス登録
//#define SET_GAME_START CSceneTitle
#define SET_GAME_START CSceneFight
//#define SET_GAME_START CSceneFacility
//-----------------------------------------------