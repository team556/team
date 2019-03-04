#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：タイトル
class CObjTitle :public CObj
{
public:
	CObjTitle() {};
	~CObjTitle() {};
	void Init();     //イニシャライズ
	void Action();   //アクション
	void Draw();     //ドロー
private:
	float m_Click_y;	//クリックでスタートの位置Ｙ
	float m_Click_vy;	//クリックでスタートの移動用ベクトルＹ
	float m_r;			//サインカーブ用の角度(クリックでスタート上下ふわふわに使用)
	
	float m_mou_x;//マウスの位置X(デバック用)
	float m_mou_y;//マウスの位置Y(デバック用)

	int m_time;
	int m_enemy_time;
	int m_Planet_Count;
	int m_enemy_y;
};