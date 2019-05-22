#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//#include "ObjTraining.h"//基底クラスとして定義するため読み込む
//使用するネームスペース
using namespace GameL;

//オブジェクト：タイトル
class CObjTutorial :public CObj
{
public:
	CObjTutorial() {};
	~CObjTutorial() {};
	void Init();     //イニシャライズ
	void Action();   //アクション
	void Draw();     //ドロー
private:
	float m_x;
	float m_y;
	bool  m_f;

	float m_mou_x;		//マウスの位置X
	float m_mou_y;		//マウスの位置Y
	bool  m_mou_r;		//マウスプッシュ確認(右クリック)
	bool  m_mou_l;		//マウスプッシュ確認(左クリック)
};