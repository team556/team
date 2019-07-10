#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "ObjTraining.h"	//基底クラスとして定義するため読み込む
//使用するネームスペース
using namespace GameL;

//オブジェクト：雲演出
class CObjCloud_Effect :public CObjTraining	//CObjTrainingを継承する
{
public:
	CObjCloud_Effect(bool check);
	~CObjCloud_Effect() {};
	void Init();     //イニシャライズ
	void Action();   //アクション
	void Draw();     //ドロー
	void SetCheck(bool check) { m_In_Out_Check = check; }//雲演出IN / OUT変更用
private:
	bool m_In_Out_Check;	//雲演出IN / OUTチェック(true=雲演出IN / false=雲演出OUT)
	float m_Cloud_move;		//雲の移動用ベクトル
	float m_white_out_a;	//ホワイトアウト演出画像透過度
	float m_white_out_a_vec;//ホワイトアウト演出画像透過度ベクトル

	int   m_time;	 //施設レベルアップ音を鳴らす時間管理用
	bool  m_level_se;//施設レベルアップ音フラグ
	bool  m_white_se;//ホワイトアウト音フラグ
};