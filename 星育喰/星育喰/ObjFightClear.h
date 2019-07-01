#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：クリア画面
class CObjFightClear :public CObj
{
public:
	CObjFightClear(int people, int large, wchar_t Mat_nameA[20], int *Mat_typeA, int Mat_numA, int skill);
	CObjFightClear(int people, int large, wchar_t Mat_nameA[20], int *Mat_typeA, int Mat_numA, wchar_t Mat_nameB[20], int *Mat_typeB, int Mat_numB, int skill);
	~CObjFightClear() {};
	void Init();     //イニシャライズ
	void Action();   //アクション
	void Draw();     //ドロー
private:
	//float m_x;
	//float m_y;
	//bool  m_f;

	//float m_mou_x;		//マウスの位置X
	//float m_mou_y;		//マウスの位置Y
	//bool  m_mou_r;		//マウスプッシュ確認(右クリック)
	bool  m_mou_l;		//マウスプッシュ確認(左クリック)
	bool  m_key_f;		//キーフラグ

	float m_click_a;		//alpha 透明度(クリック催促フォント用)
	float m_click_a_vec;	//m_click_aベクトル
	bool m_click_a_f;		//不透明化フラグ
	float m_result_a;		//alpha(透過度)(戦闘結果フォント用)
	float m_black_out_a;	//画面暗転透過度
	float m_clear_a;		//alpha(透過度)(クリアメッセージのフォント用)

	bool  m_scene_migration_f;//シーン移行演出フラグ(true = ホーム画面にいる感じとなる。※実際にはこの時点ではまだ移行していない)

	int		m_people;		//獲得住民数
	int		m_large;		//獲得サイズ(HP)数
	wchar_t m_mat_name[2][20];//獲得資材名
	int		*m_mat_type[2];	//獲得資材種類 & 現在数
	int		m_mat_num[2];	//獲得資材数
	int		m_skill;		//獲得スペシャル技

	//int m_cnt;		//カウント
	//int m_cnt_max;	//カウントマックス

	//int m_page_nam;		//ページ数

	bool m_Stage_Clear_f;	//ステージクリアフラグ
	bool m_Game_Clear_f;	//ゲーム　クリアフラグ
};