#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "ObjFight.h"	//基底クラスとして定義するため読み込む
//使用するネームスペース
using namespace GameL;

//オブジェクト：惑星(プレイヤー & 敵)
class CObjPlanet :public CObjFight //CObjFightを継承する
{
public:
	CObjPlanet(float x, float y, float size, int type/*, float siz = 0*/);//座標+サイズ(HP)+タイプ
	~CObjPlanet() {};
	void Init();	//イニシャライズ
	void Action();  //アクション
	void Draw();    //ドロー

	float GetX() { return m_px; }
	float GetY() { return m_py; }
	//float GetHp() { return m_hp; }	//HP取得関数
	float GetSiz() { return m_size; }
	int  GetType() { return m_type; }
	bool GetInvincible() { return m_invincible_f; }//無敵であるかどうか返す
	void SetDamage() { m_size -= 1; }//呼び出すとダメージ処理を行う[スペシャル技:Explosion用]
	void SetScale_down_move(int Planet_id) //呼び出すとサイズ縮小分、X座標の移動を行う(Planet_id:プレイヤー or エネミー判別用)[スペシャル技:Explosion用]
	{
		Planet_id = Planet_id == 0 ? -1 : 1;//Planet_idが0なら-1を、それ以外なら1をPlanet_idに代入する
		m_scale_down_move = ((1 - (m_size / m_siz_max)) * 60) * Planet_id; 
	}
	void SetInvincible(bool is_Invincible) { m_invincible_f = is_Invincible; }//無敵フラグ設定用[スペシャル技:Immortality用]
	void SetRecastBuff(float buff) { m_enemy_recast_buff = buff; }//バフ倍率設定用[スペシャル技:リミットブレイク用]
	void SetEeatF() { m_eat_f = true; }//セット喰うフラグ

	void SetDelF() { m_del_f = true; }//セット消すフラグ
private:

	float m_px;			//星座標X
	float m_py;			//星座標Y
	float m_size;		//星サイズ(現在HP)
	float m_siz_max;	//サイズマックス(最大HP)
	//float m_siz_vec;	//サイズ変更ベクトル
	//float m_siz_spd;	//サイズ変更スピード
	float m_get_siz;	//ゲットサイズ
	float m_mov_spd;	//惑星移動スピード
	float m_scale_down_move;	//サイズ縮小分、X座標移動用(プレイヤーなら左に、エネミーなら右に移動)

	//float m_hp;			//ヒットポイント(m_sizeでHPも管理する事に変更。size = hp)
	//float m_get_hp;		//ゲットHP
	int m_cnt;			//カウント
	int m_type;		//惑星タイプ(主人公 == 0 != 敵)
	int m_img_nam;	//画像(image)ナンバー

	bool m_invincible_f;	//無敵フラグ(true:無敵　false:無敵ではない)[スペシャル技:Immortality用]
	float m_enemy_recast_buff;//エネミーミサイルポッドリキャストタイムのバフ倍率[スペシャル技:リミットブレイク用]	


	int m_time;
	int m_attackf;		//敵の攻撃タイプ

	int m_ani[4];
	int m_ani_time;
	int m_ani_frame;

	bool m_eat_f;		//喰うフラグ(true = 喰う)
	float m_eat_spd;
	bool m_del_f;		//消すフラグ(true = 消す)

	bool m_win;			//敵惑星に勝利した時に流れる音楽のフラグ	
	bool m_failed;		//敵惑星に敗北した時に流れる音楽のフラグ

	int m_cntf;			//fightのm_cnt変数の値を格納する用
	int m_mov_stop;		//

	int Enemy_Attack_pattern_x;  //敵攻撃パターンの横軸読み込む用
	int Enemy_Attack_pattern_y;  //敵攻撃パターンの縦軸読み込む用
};