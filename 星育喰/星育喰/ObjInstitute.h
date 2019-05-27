#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "ObjTraining.h"	//基底クラスとして定義するため読み込む
//使用するネームスペース
using namespace GameL;

//マクロ
#define MIS_MAX_LV (5) //ミサイルリキャストのMAXレベル(仮決めで"5"としている)
#define EQU_MAX_LV (3) //各武器ポッドのMAXレベル
#define EQU_MES_MAX_FONT_LINE (3) //武器ポッド必要素材&人数メッセージの最大フォント行数

//オブジェクト：研究所
class CObjInstitute :public CObjTraining //CObjTrainingを継承する
{
public:
	CObjInstitute() {};
	~CObjInstitute() {};
	void Init();     //イニシャライズ
	void Action();   //アクション
	void Draw();     //ドロー

	void Missile_Lvup_check();//ミサイルリキャストレベルUPチェック関数
	int  Equip_Lvup_check(int equip_id, int equip_Level, int equip_Lv_achieve);//武器ポッドレベルUPチェック関数
	int  Equip_Lvdown_check(int equip_id, int equip_Level);					   //武器ポッドレベルDOWNチェック関数
	void Equip_Lvup_possible_check();						//武器ポッドレベルUP可能チェック関数
	void Equip_message(int equip_id, int Lv_id);			//武器ポッド必要素材&人数メッセージ表示関数
private:
	float m_Ins_color;				//研究所カラー明度
	float m_Ins_Lvup_color;			//研究所レベルUPカラー明度
	float m_Human_up_color;			//住民振り分けUPカラー明度
	float m_Human_down_color;		//住民振り分けDOWNカラー明度
	float m_Mis_Button_color;		//ミサイルボタンカラー明度
	float m_Equ_Button_color;		//武器ポッドボタンカラー明度
	float m_Equ_pic_red_color[15];	//武器ポッド画像集カラー(Red)
	float m_Equ_pic_green_color[15];//武器ポッド画像集カラー(Green)
	float m_Equ_pic_blue_color[15];	//武器ポッド画像集カラー(Blue)

	wchar_t m_Equ_message[EQU_MES_MAX_FONT_LINE][22];	//武器ポッド必要素材&人数メッセージのフォント用(素材名除く)
	float	m_Equ_message_window_x_size;				//武器ポッド必要素材&人数ウインドウのサイズX
	float	m_Equ_message_window_y_size;				//武器ポッド必要素材&人数ウインドウのサイズY

	int   finalcheck_Lvup_type;		//最終確認ウインドウでLvUPさせる武器ポッドのタイプを管理
	int  *finalcheck_Lvup_Level;	//最終確認ウインドウでLvUPさせる武器レベルを管理するポインタ
	int  *finalcheck_Lvup_achieve;	//最終確認ウインドウでLvUPさせる武器レベル最大到達度を管理するポインタ

	float m_Mis_recast_time[MIS_MAX_LV];				//ミサイルリキャストタイム
	int	  m_Mis_recast_next_Ins_Lv[MIS_MAX_LV - 1];		//ミサイルリキャストの次のLVUPに必要な研究所レベル管理用
	int   m_Mis_recast_next_Hum_num[MIS_MAX_LV - 1];	//ミサイルリキャストの次のLVUPに必要な研究員の住民数管理用
	
	int  m_Equ_next_Hum_num[5][EQU_MAX_LV - 1];			//各武器、ポッドの次のLVUPに必要な研究員の住民数管理用
	wchar_t m_Equ_next_Mat_name[5][EQU_MAX_LV - 1][MAT_NAME_CHAR_DATA_STORE_NUM];//各武器、ポッドの次のLVUPに必要な素材の名前管理用
	int *m_Equ_next_Mat_type[5][EQU_MAX_LV - 1];		//各武器、ポッドの次のLVUPに必要な素材種類とその素材の所持数を管理するポインタ
	int  m_Equ_next_Mat_num[5][EQU_MAX_LV - 1];			//各武器、ポッドの次のLVUPに必要な素材数管理用(仮で必要素材1種類として考えている。2種類以上ならその分Mat_typeとMat_numを配列構造体に入れて増やす予定)
};