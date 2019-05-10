#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "ObjFight.h"	//基底クラスとして定義するため読み込む
//使用するネームスペース
using namespace GameL;

//オブジェクト：ミサイル
class CObjMissile :public CObjFight //CObjFightを継承する
{
public:
	CObjMissile(float x, float y,bool type,int n);
	~CObjMissile() {};
	void Init();     //イニシャライズ
	void Action();   //アクション
	void Draw();     //ドロー
private:
	float m_x;		//ミサイルの座標X
	float m_y;		//ミサイルの座標Y
	float m_vx;		//ベクトルX
	float m_vy;		//ベクトルY
	float m_size;	//ミサイルのサイズ
	bool  m_mou_f;	//マウスフラッグ

	float m_r;		//ミサイル角度
	float m_mov;	//
	float m_mov_spd;//動く速さ

	float m_mou_x;		//マウスの位置X
	float m_mou_y;		//マウスの位置Y
	bool  m_mou_r;		//マウスプッシュ確認(右クリック)
	bool  m_mou_l;		//マウスプッシュ確認(左クリック)

	int m_get_line;		//取得したラインナンバー
	int m_get_cnt;		//取得したカウント

	int ButtonU;		//プレイヤーが撃ったポッドの種類

	int m_time;
	int Enemypod;

	bool m_type;		//生成時のタイプ(true主人公)
};