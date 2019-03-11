#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：タイトル
class CObjPushUnit :public CObj
{
public:
	CObjPushUnit(float x, float y, float h, float w, int t);
	~CObjPushUnit() {};
	void Init();     //イニシャライズ
	void Action();   //アクション
	void Draw();     //ドロー
private:
	float m_x;		//座標X
	float m_y;		//座標Y
	float m_h;		//height高
	float m_w;		//width幅
	float m_a;		//alpha

	int m_type;		//タイプ

	float m_mou_x;		//マウスの位置X
	float m_mou_y;		//マウスの位置Y
	bool  m_mou_r;		//マウスプッシュ確認(右クリック)
	bool  m_mou_l;		//マウスプッシュ確認(左クリック)

	
};