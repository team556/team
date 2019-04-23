#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：タイトル
class CObjFightClear :public CObj
{
public:
	CObjFightClear() {};
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

	int m_people;	//住民
	int m_mrl;		//マテリアルズ(資材)
	char m_skill;	//スペシャル技
};