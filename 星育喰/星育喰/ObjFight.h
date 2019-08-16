#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//#include "GameL\DrawTexture.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：戦闘画面
class CObjFight :public CObj
{
public:
	CObjFight(int c = 0);	//c = cnt(戦闘時間),e_n = m_ene_nam(敵ナンバー)
	~CObjFight() {};
	void Init();     //イニシャライズ
	void Action();   //アクション
	void Draw();     //ドロー

	int GetLine() { return m_line_nam; }//選択ラインを返す
	int GetCount() { return m_cnt; }	//カウント数を返す
	void SetEndCount() { m_cnt = 60; }	//戦闘終了カウント数に設定する
	void SetStart_Count() { m_start_count_f = true; }//戦闘開始カウントを動作させる
	void SetEnd() { m_end_f = true; }	//クリア画面作成
	void SetBattle_start(bool start) { battle_start = start; }
	void SetExplosion_f(int id) { m_Explosion_f[id] = true; }
	void SetPrey_f(bool flag) { m_prey_f = flag; }
private:
	float m_mou_x;		//マウスの位置X
	float m_mou_y;		//マウスの位置Y
	bool  m_mou_r;		//マウスプッシュ確認(右クリック)
	bool  m_mou_l;		//マウスプッシュ確認(左クリック)
	
	float m_a;			//alpha(透明度)

	int m_line;			//選択前
	int m_line_nam;		//選択中ラインナンバー(上から0,1,2)

	int m_cnt;			//カウント用

	float m_ex;
	float m_ey;

	float m_scale_down_cnt;		//縮小比カウント(背景)
	float m_scale_down_speed;	//縮小スピード(背景)

	float m_font_a;				//透明度(戦闘開始時表示される"スタート"の文字用)

	int	  m_start_count;		//戦闘開始カウント用
	bool  m_start_count_f;		//「戦闘開始カウント」開始フラグ(trueの時、動作を開始する)

	bool m_line_dis;	//初期ライン選択表示用

	bool m_end_f;		//クリア画面作成用
	bool m_key_U_f;		//UP用キーフラグ
	bool m_key_D_f;		//DOWN用キーフラグ
	bool m_special_f;   //スペシャル技を打った時のフラグ

	int m_line_choice;	//ライン選択用

	int m_cuta;


	//▼背面表示させたい演出にて使用する変数等
	bool  m_Explosion_f[2];		//[スペシャル技:Explosion]発動管理フラグ(true:発動中　false:未発動)
	float m_Explosion_size[2];	//[スペシャル技:Explosion]エフェクト画像サイズ変更用
	float m_Explosion_width[2];	//[スペシャル技:Explosion]エフェクト画像の幅変更用

	bool  m_prey_f;				//捕食処理中かそうでないか確認用フラグ(true:捕食処理中　false:そうでない)
	int	  m_ani[4];				//口のアニメーション用
protected:
	static bool battle_start;	//戦闘開始フラグ(true:戦闘開始　false:戦闘前 or 一時停止中)
	static bool battle_end;		//戦闘終了フラグ(true:戦闘終了　false:戦闘中)

	static float Pla_One_pat_dem[3];	//プレイヤーのワンパターンデメリット値管理配列[0:上レーン　1:中レーン　2:下レーン][変動値は1.0～1.5の6段階。レーンで撃つ度に0.1ずつ増加。他のレーンを撃つ度に0.1ずつ減少。][この値が攻撃力と乗算され、最終的な受けるダメージとなる]
	static float Ene_One_pat_dem[3];	//エネミ－のワンパターンデメリット値管理配列[0:上レーン　1:中レーン　2:下レーン][変動値は1.0～1.5の6段階。レーンで撃つ度に0.1ずつ増加。他のレーンを撃つ度に0.1ずつ減少。][この値が攻撃力と乗算され、最終的な受けるダメージとなる]

	static int p_pnam;		//プレイヤーの排出したポッド数
	static int e_pnam;		//エネミーの排出したポッド数

	static float damage_buff[2];//ダメージのバフ倍率[スペシャル技:リミットブレイク用]
};