#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：戦闘前演出
class CObjBefore_Fight_Effect :public CObj
{
public:
	CObjBefore_Fight_Effect(bool check) { m_In_Out_Check = check; }
	~CObjBefore_Fight_Effect() {};
	void Init();     //イニシャライズ
	void Action();   //アクション
	void Draw();     //ドロー
private:
	bool  m_In_Out_Check;	//黒星演出IN / OUTチェック(true=黒星演出IN / false=黒星演出OUT)
	float m_black_star_effect_size;	//戦闘前演出(黒星)のサイズ
};