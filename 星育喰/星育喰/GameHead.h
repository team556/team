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
	OBJ_Rocket,
	OBJ_FIGHT_CLEAR,
	OBJ_FIGHT_OVER,
	OBJ_FIGHT_Rocket,
	OBJ_POD,
	OBJ_ENEMYPOD,

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
	ELEMENT_POD,
	ELEMENT_ENEMYPOD,
	ELEMENT_P_MIS,			//プレイヤーと
	ELEMENT_E_MIS,			//敵のミサイル

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
//▼セーブ必要性有り
extern int g_Stage_progress;		//現在のステージ進行度(1ステージ:1　2ステージ:2　3ステージ:3)
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
extern int g_Special_equipment;		//現在装備中のスペシャル技(0:未装備　1:敵に大ダメージ　2:一列殺し　3:一定時間無敵　4:生産性効率アップ　5:住民の士気がアップ)
extern bool g_Special_mastering[5];	//習得済みのスペシャル技[true:習得済  false:未習得](0:敵に大ダメージ　1:一列殺し　2:一定時間無敵　3:生産性効率アップ　4:住民の士気がアップ)
extern int g_Power_num;				//パワー住民数
extern int g_Defense_num;			//ディフェンス住民数
extern int g_Speed_num;				//スピード住民数
extern int g_Balance_num;			//バランス住民数
extern int g_Research_num;			//研究員住民数
extern int g_Remain_num;			//残り住民数

extern int g_Material_num_test;		//TEST用所持素材数

//▼セーブ必要性無し
extern int g_Challenge_enemy;		//戦闘を行う敵惑星識別番号(0:左から1番目の敵惑星　1:左から2番目の敵惑星　2:左から3番目の敵惑星　3:左から4番目の敵惑星　4:ボス惑星)

extern bool g_key_fg;//

//------------------------------------------------
//ゲーム内で使用するクラスヘッダ------------------


//------------------------------------------------

//ゲームシーンオブジェクトヘッダ------------------
#include "ObjTitle.h"
#include "ObjHome.h"
#include "ObjTest.h"
#include "ObjHuman.h"
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
#include "Pause.h"

//------------------------------------------------

//ゲームシーンクラスヘッダ------------------------
#include "SceneTitle.h"
#include "SceneHome.h"
#include "SceneTest.h"
#include "SceneTraining.h"
#include "ScenePreparation.h"
#include "SceneFight.h"

//-----------------------------------------------

//シーンスタートクラス---------------------------
//ゲーム開始時のシーンクラス登録
//#define SET_GAME_START CSceneTitle
//#define SET_GAME_START CSceneFight
//#define SET_GAME_START CSceneTraining
//#define SET_GAME_START CSceneTest
#define SET_GAME_START CScenePreparation
//-----------------------------------------------