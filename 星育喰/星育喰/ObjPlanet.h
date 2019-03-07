#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：タイトル
class CObjPlanet :public CObj
{
public:
	CObjPlanet(float x, float y, bool type);//座標+タイプを受け取る
	~CObjPlanet() {};
	void Init();	//イニシャライズ
	void Action();  //アクション
	void Draw();    //ドロー
private:
	float m_px;		//星座標X
	float m_py;		//星座標Y
	float m_size;	//星サイズ
	float m_cnt;	//縮小用カウント
	
	int m_pnam;		//画像ナンバー
};