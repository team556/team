#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "ObjTraining.h"	//基底クラスとして定義するため読み込む
//使用するネームスペース
using namespace GameL;

//オブジェクト：住民
class CObjHuman :public CObjTraining	//CObjTrainingを継承する
{
public:
	CObjHuman(float x, float y, int n);//作成時の座標用引数
	~CObjHuman() {};
	void Init();		//イニシャライズ
	void Action();		//アクション
	void Draw();		//ドロー
	
	void Turn(int* pos);		//向き反転
private:
	float m_hx;			//HumanのX座標
	float m_hy;			//HumanのY座標
	float m_mov_spd;	//動きの速さ
	float m_size;		//Humanのサイズ

	int m_pos;			//Humanの向き(0～3で四方向)
	int m_ani_time;		//アニメーションフレーム動作間隔
	int m_ani_frame;	//描画フレーム
	int m_nam;			//住民ナンバー
	int m_cnt;			//カウント

	bool m_move;		//true動いている,false動いてない
	bool m_turn;		//ターンフラグ,ture領域外
};