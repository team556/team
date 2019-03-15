#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：ホーム
class CObjCloud_Effect :public CObj
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
};