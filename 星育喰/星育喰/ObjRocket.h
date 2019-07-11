#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "ObjFight.h"	//基底クラスとして定義するため読み込む
//使用するネームスペース
using namespace GameL;

//オブジェクト：ミサイル
class CObjRocket :public CObjFight //CObjFightを継承する
{
public:
	CObjRocket(float x, float y,int type,int n);
	~CObjRocket() {};
	void Init();     //イニシャライズ
	void Action();   //アクション
	void Draw();     //ドロー
	float GetX() { return m_vx; }
	float GetY() { return m_vy; }
private:
	float m_x;		//ミサイルの座標X
	float m_y;		//ミサイルの座標Y
	float m_vx;		//ベクトルX
	float m_vy;		//ベクトルY
	float m_size;	//ミサイルのサイズ

	float m_r;		//角度変更用(+で左回転)
	float m_mov;	//
	float m_mov_spd;//動く速さ

	int m_get_line;		//取得したラインナンバー
	int m_get_cnt;		//取得したカウント

	int ButtonU;		//ポッドの種類

	int ButtonUE;		//エネミーが撃ったポッドの種類
	int ButtonUP;		//プレイヤーが撃ったポッドの種類

	int m_atk_cnt;		//ダメージレートのカウント用
	int m_atk_cnt_max;	//ダメージレートのカウント最大値(1/3秒)

	int m_Enemy_Pod_Level;	//敵のポッドレベル情報(レベルに合わせたポット描画を行う)(1:レベル1　2:レベル2　3:レベル3)

	int m_type;		//生成時のタイプ(0主人公)
	int m_podhp;		//ポッド現在HP
	int m_pod_max_hp;	//ポッド最大HP
	int m_hp_cnt;		//無敵タイム
	bool m_hp_f;		//無敵フラグ

	int m_Player_damage;//プレイヤーが受けるダメージ量(エネミーの攻撃力)
	int m_Enemy_damage; //エネミーが受けるダメージ量(プレイヤーの攻撃力)

	int m_ani;			//着弾アニメーション
	int m_ani_max;
	int m_ani_time;		//着弾アニメーション間隔タイム
	bool m_del;			//削除チェック
	RECT_F m_eff;		//着弾エフェクト描画用

	float m_a;			//alpha(透明度)
	int m_bom;			//爆発エフェクトのランダム(0～3)
	bool m_fight;		//ポッド同士の衝突中フラグ(交戦時)
	int m_stop_cnt;		//止めるまでのカウント用
	bool m_stop_f;		//座標更新を止めるフラグ

	int Enemy_Line_pattern_x;	////敵攻撃パターンの横軸読み込む用
	int Enemy_Line_pattern_y;	////敵攻撃パターンの縦軸読み込む用

	int m_bomcount;		//爆発の回数カウント

	int m_level_comp[4];	//装備武器レベルの比較用
};