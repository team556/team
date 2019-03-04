#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：住民
class CObjHuman :public CObj
{
public:
	CObjHuman(float x,float y);//作成時の座標用引数
	~CObjHuman() {};
	void Init();		//イニシャライズ
	void Action();		//アクション
	void Draw();		//ドロー
private:
	float m_hx;			//HumanのX座標
	float m_hy;			//HumanのY座標

	int m_pos;			//Humanの向き(0～3で四方向)
	int m_ani_time;		//アニメーションフレーム動作間隔
	int m_ani_frame;	//描画フレーム
	int m_cnt;			//カウント

	bool m_move;		//true動いている,false動いてない
};