#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "ObjFight.h"	//基底クラスとして定義するため読み込む
//使用するネームスペース
using namespace GameL;

//オブジェクト：スペシャル技ボタン
class CObjSpecialButton :public CObjFight //CObjFightを継承する
{
public:
	CObjSpecialButton(float x, float y, float h, float w);
	~CObjSpecialButton() {};
	void Init();     //イニシャライズ
	void Action();   //アクション
	void Draw();     //ドロー

	bool GetEnemy_Used_Special() { return m_is_used_special[1]; }//敵がスペシャル技を使用したかどうかを返す
	int  GetSpecial_equip() { return m_enemy_special_equipment; }//敵が装備中のスペシャル技を返す
	bool GetInvocating(int Planet_id) { return m_is_invocating[Planet_id]; }//[プレイヤー or 敵]が現在スペシャル技発動中であるかを返す
	void SetBuff_count(int Planet_id) { m_count[Planet_id] += 1; }//ポッドの射出回数カウント用[スペシャル技:ステロイド投与用]
	void SetSpecial_Equip(int equip) { m_enemy_special_equipment = equip; }//敵の発動するスペシャル技を決める用
	void SetSpecial_Start() { m_enemy_special_button = true; }	//敵のスペシャル技を発動させる用
private:
	void Special_staging_message(int Planet_id, int Special_equip);	//スペシャル技発動演出メッセージ設定関数
	void Special_process(int Planet_id, int Opponent_id, int Special_equip);	//スペシャル技処理関数(スペシャル技発動演出、スペシャル技効果の処理等を行う)
	void Special_effect(int Planet_id, int Special_equip);	//スペシャル技エフェクト描画関数

	float m_x;		//スペシャル技ボタンの座標X
	float m_y;		//スペシャル技ボタンの座標Y
	float m_h;		//スペシャル技ボタンのheight(高さ)
	float m_w;		//スペシャル技ボタンのwidth(幅)
	float m_a;		//スペシャル技ボタンのalpha(透過度)

	float m_mou_x;		//マウスの位置X
	float m_mou_y;		//マウスの位置Y
	bool  m_mou_r;		//マウスプッシュ確認(右クリック)
	bool  m_mou_l;		//マウスプッシュ確認(左クリック)

	wchar_t m_staging_message[2][15];	//スペシャル技発動演出フォント用([フォント行数][文字データ格納可能数])
	float m_staging_font_color;			//スペシャル技発動演出フォントカラー変更用

	int m_pla_type;		//惑星がプレイヤーか否かの判別用

	//▼配列数字の意味は以下の通り
	//0:プレイヤー惑星　1:敵惑星
	int m_count[2];				//スペシャル技効果時間、効果回数、発動演出時間管理用
	bool m_is_used_special[2];	//スペシャル技が使用されたか[スペシャル技発動演出終了時点で使用したとみなされる](true:使用済　false:未使用)
	bool m_is_invocating[2];	//現在スペシャル技が発動中であるか(true:発動中　false:発動済 or 未発動)
	bool  m_special_staging_f[2];//スペシャル技発動演出フラグ[true:演出中　false:演出してない]

	float m_Explosion_size[2];	//[スペシャル技:Explosion]エフェクト画像サイズ変更用
	float m_Explosion_width[2];	//[スペシャル技:Explosion]エフェクト画像の幅変更用
	float m_Explosion_pos[2];	//[スペシャル技:Explosion]エフェクト画像の位置変更用
	int   m_Explosion_target[2];//[スペシャル技:Explosion]エフェクト対象変更用
	float m_Explosion_angle[2];	//[スペシャル技:Explosion]エフェクト角度変更用

	float m_Fracture_Ray_pos[2];	//[スペシャル技:Fracture_Ray]エフェクト画像の位置変更用
	float m_Fracture_Ray_width[2];	//[スペシャル技:Fracture_Ray]エフェクト画像の幅変更用

	float m_Immortality_size[2];	//[スペシャル技:Immortality]エフェクト画像サイズ変更用

	bool  m_sptime[2];	//Immortality & ステロイド投与SE鳴らすフラグ
	bool  m_sp_invocation_SE[2];//スペシャル技発動SE用

	float m_Special_effect_alpha[2];	//スペシャル技エフェクト画像のalpha(透過度)
	float m_Special_effect_alpha_vec[2];//スペシャル技エフェクト画像の透過度ベクトル

	//▼以下は敵が[スペシャル技:Fracture_Ray]使用時、
	//どのライン上に発射するか決定する為に必要な変数・配列
	int	  m_Enemy_line;	//発射するライン(0:未決定状態　1:中ライン　2:下ライン　3:上ライン)
	int   m_PodMissile_count[3];//当たり判定内に存在するプレイヤーのポッドミサイルカウント用[0:中ライン用　1:下ライン用　2:上ライン用]

	//▼以下はObjPlanet(Enemy)から送られてくる情報を取得する用
	int  m_enemy_special_equipment;//敵装備中のスペシャル技(0:未装備　1:Explosion　2:Fracture_Ray　3:Immortality　4:リミットブレイク　5:ステロイド投与)
	bool m_enemy_special_button;//敵用スペシャル技発動ボタン(true:発動　false:発動してない)


	//▼オブジェクト情報取得用のポインタをそれぞれ宣言
	//※スペシャル技ボタンの処理を各オブジェクトに送ったり、逆に取得したりする為のもの。
	CObjFight *FightScene;
	CObjPlanet *Planet[2];
	CObjRocketButton *PodMissile[5];
};