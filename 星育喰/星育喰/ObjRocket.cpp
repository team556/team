//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"


#include "GameHead.h"
#include "UtilityModule.h"
#include "ObjRocket.h"

#include <time.h>

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjRocket::CObjRocket(float x, float y, int type,int n)
{
	m_x = x;
	m_y = y;
	m_type = type;
	ButtonU = n;

}

//イニシャライズ
void CObjRocket::Init()
{
	Enemy_Line_pattern_x = 0;

	srand(time(NULL));
	Enemy_Line_pattern_y = rand() % 5;//初期行動パターンをランダムで決める(この処理ないと初期行動パターンが必ず0のものになる)

	CObjPlanet* pla = (CObjPlanet*)Objs::GetObj(OBJ_PLANET);

	if (m_type == 0) {
		CObjFight* obj = (CObjFight*)Objs::GetObj(OBJ_FIGHT);

		if (obj != nullptr) {					//情報が取得出来ていたら
			m_get_line = obj->GetLine();		//ラインナンバーを取得
			if (m_get_line == 1) { m_y = 310; }	//取得ナンバーで高さ変更
			else if (m_get_line == 2) { m_y = 420; }

			m_get_cnt = obj->GetCount();		//カウントを取得
			//m_x += obj->GetCount() / 10;
			m_x += 0.0f;
			m_mov_spd = 1.0f / pla->GetX();
		}
	}
	else if (m_type != 0 && battle_end == false)
	{
		CObjPlanet* ene = (CObjPlanet*)Objs::GetObj(OBJ_ENEMY);

		m_get_line = ene->GetLine();
	}

	CObjFight* obj = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
	if (m_get_line == 1) { m_y = 310; }	//取得ナンバーで高さ変更
	else if (m_get_line == 2) { m_y = 420; }

	m_get_cnt = obj->GetCount();		//カウントを取得
	m_mov_spd = 1.0f / pla->GetX();

	m_size = 50.0f;//サイズ
	
	m_time = 100;

	m_Enemy_Pod_Level = g_Stage_progress;	//現状、現在のステージ進行度に合わせて敵のポッドレベルを設定している

	m_vx = 0.0f;//ベクトル
	m_vy = 0.0f;
	m_mov = 0;
	
	m_r = 0.0f;

	m_mou_x = 0.0f;	//マウス情報
	m_mou_y = 0.0f;
	m_mou_r = false;
	m_mou_l = false;
	
	m_mou_f = false;//マウスフラグ

	if (m_type == 0)
		ButtonUP = ButtonU;
	else
		ButtonUE = ButtonU;

	//当たり判定用HitBox作成
	if (m_type == 0) 
	{
		m_x += 100;
		if (ButtonUP == 1)
		{
			Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD, OBJ_PODP, 1);
		}
		else if (ButtonUP == 2)
		{
			Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD, OBJ_PODD, 1);
		}
		else if (ButtonUP == 3)
		{
			Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD, OBJ_PODS, 1);
		}
		else if (ButtonUP == 4)
		{
			Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD, OBJ_PODB, 1);
		}
		else if (ButtonUP == 5)
		{
			Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD, OBJ_ROCKET, 1);
		}

	}
	else if(m_type != 0)
	{
		m_x -= 100;
		if (ButtonUE == 1)
		{
			Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_ENEMYPOD, OBJ_PODP, 1);
		}
		else if (ButtonUE == 2)
		{
			Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_ENEMYPOD, OBJ_PODD, 1);
		}
		else if (ButtonUE == 3)
		{
			Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_ENEMYPOD, OBJ_PODS, 1);
		}
		else if (ButtonUE == 4)
		{
			Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_ENEMYPOD, OBJ_PODB, 1);
		}
		else if (ButtonUE == 5)
		{
			Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_ENEMYPOD, OBJ_ROCKET, 1);
		}

	}

	m_eff.m_top = 0;
	m_eff.m_left = 0;
	m_eff.m_right = 32;
	m_eff.m_bottom = 29;
	m_ani = 0;
	m_ani_max = 1;
	m_ani_time = 0;
	m_del = false;
	m_vx = 0.0f;

	m_a = 1.0f;
	m_bom = 0.3f;

	//ポッドのHPを決める
	if (ButtonU == 5)			//ポッドがミサイルの時のみHPを1にする
	{
		m_pod_max_hp = 1;
	}
	else if (m_type == 0) {		//自惑星の時に(ポッドのLv*10)+(研究所のLv*5)をHPに代入する
		m_pod_max_hp = (g_Pod_equip_Level * 10) + ((g_Ins_Level - 1)* 5);
	}
	else if (m_type == 1) {		//敵惑星の時は固定値
		m_pod_max_hp = 10;
	}
	else if (m_type == 2) {
		m_pod_max_hp = 20;
	}
	else if (m_type == 3) {
		m_pod_max_hp = 20;
	}
	else if (m_type == 4) {
		m_pod_max_hp = 10;
	}
	else if (m_type == 5) {
		m_pod_max_hp = 30;
	}

	m_podhp = m_pod_max_hp;

	m_hp_cnt = 0;		//無敵タイム
	m_hp_f = false;		//無敵フラグ
	m_fight = false;	//衝突中フラグ
	m_bomcount = 0;		//爆発カウント

	////ミサイルの火力を決めるための準備
	////（使わない可能性大）
	//for (int i = 0; i < 4; i++)
	//{
	//	switch (i) {
	//	case 0:
	//		m_level_comp[i] = g_Pow_equip_Level;
	//		break;
	//	case 1:
	//		m_level_comp[i] = g_Def_equip_Level;
	//		break;
	//	case 2:
	//		m_level_comp[i] = g_Spe_equip_Level;
	//		break;
	//	case 3:
	//		m_level_comp[i] = g_Bal_equip_Level;
	//		break;
	//	}
	//}

	//for (int i = 1; i<4; ++i)
	//{
	//	if (m_level_comp[0] > m_level_comp[i])
	//	{
	//		g_Missile_pow = m_level_comp[i];
	//	}
	//}

	//g_Missile_pow = g_Missile_pow * (10 / 2);

	m_Enemy_damage = 10;//エネミーが受けるダメージ量(プレイヤーの攻撃力)
	m_Player_damage = 10;//プレイヤーが受けるダメージ量(エネミーの攻撃力)

	if (m_type == 0)
	{
		//プレイヤーの火力を装備レベルによって変える(ポッドレベル * 10)
		switch (ButtonUP) {
		case 1:
			m_Enemy_damage = g_Pow_equip_Level * 10;
			break;
		case 2:
			m_Enemy_damage = g_Def_equip_Level * 10;
			break;
		case 3:
			m_Enemy_damage = g_Spe_equip_Level * 10;
			break;
		case 4:
			m_Enemy_damage = g_Bal_equip_Level * 10;
			break;
		case 5:					//ミサイルの時は火力3固定
			m_Enemy_damage = 3;
			break;
		}
		
		if (ButtonU != 5)						//ミサイルは火力固定のため省く
			m_Enemy_damage += (g_Bar_Level - 1) * 5;	//決まった火力+兵舎のLv*5する

	}

	else if (m_type != 0)
	{
			//敵の火力を敵によって変える
			switch (m_type) {
			case 1:
				m_Enemy_Pod_Level = 1;		//ポッドレベル設定
				m_Player_damage = 3;		//いったんミサイルの攻撃力(3)を代入
				if (ButtonUE != 5)			//ミサイル以外かどうか判定
					m_Player_damage = 10;	//ミサイル以外なら本来のダメージを代入
				g_P_Planet_damage = m_Player_damage;
				break;
			case 2:
				m_Enemy_Pod_Level = 2;		//ポッドレベル設定
				m_Player_damage = 3;
				if (ButtonUE != 5)
					m_Player_damage = 20;
				g_P_Planet_damage = m_Player_damage;
				break;
			case 3:
				m_Enemy_Pod_Level = 2;		//ポッドレベル設定
				m_Player_damage = 3;
				if (ButtonUE != 5)
					m_Player_damage = 20;
				g_P_Planet_damage = m_Player_damage;
				break;
			case 4:
				m_Enemy_Pod_Level = 1;		//ポッドレベル設定
				m_Player_damage = 3;
				if (ButtonUE != 5)
					m_Player_damage = 10;
				g_P_Planet_damage = m_Player_damage;
				break;
			case 5:
				m_Enemy_Pod_Level = 3;		//ポッドレベル設定
				m_Player_damage = 3;
				if (ButtonUE != 5)
					m_Player_damage = 30;
				g_P_Planet_damage = m_Player_damage;
				break;
			}
	}
}

//アクション
void CObjRocket::Action()
{
	//▼ポーズ画面等による一時停止中にミサイルポッドが動かないようにする処理
	if (battle_start == false)
	{
		return;
	}

	m_vx = 0.0f;//ベクトル初期化
	m_vy = 0.0f;

	CObjFight* obj = (CObjFight*)Objs::GetObj(OBJ_FIGHT);

	m_mov += m_mov_spd / 2;

	//マウスの位置を取得
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//マウスのボタンの状態
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	CHitBox* hit = Hits::GetHitBox(this);		//HitBox情報取得
	hit->SetPos(m_x, m_y, m_size, m_size);		//HitBox更新

	if (battle_end == true)	//バトル終了時、存在している全てのポッドを破壊する
	{
		Audio::Start(5);
		m_del = true;
	}
		

	if (m_mou_l == false && m_mou_f == false)
	{
		m_mou_f = true;
	}
	else
	{
		m_mou_f = false;
	}

	//爆発エフェクト回数処理
	if (m_fight == true)//衝突中フラグＯＮ時
	{
		;
	}
	else//ポッド同士が当たると動きを止め勝敗を決める処理
	{
		//各ライン毎の動き方
		if (m_get_line == 0 || m_get_line == 3)//------上ライン----
		{
			m_vx -= 0.3f;
			m_vy += (-0.15 + m_mov);
		}
		else if (m_get_line == 1)//---------------中ライン-----
		{
			m_vx -= 0.5f;
		}
		else//if(m_get_line == 2)---------------下ライン------
		{
			m_vx -= 0.3f;
			m_vy -= (-0.15 + m_mov);
		}

		//-----------------------------座標更新
		if (m_type == 0) {
			m_x += m_vx - m_mov_spd * 200;
			m_y += m_vy;
		}
		else {
			m_x -= m_vx - m_mov_spd * 200;
			m_y += m_vy;
		}
	}
	////---------------------------------座標更新
	//if (m_fight == false) {//戦闘フラグＯＦＦ時
	//	if (m_type == 0) {
	//		m_x += m_vx;
	//		m_y += m_vy;
	//	}
	//	else {
	//		m_x -= m_vx;
	//		m_y += m_vy;
	//	}
	//}

	//爆発エフェクト
	m_eff = GetPodEffec(&m_ani, &m_ani_time, m_del, 5);	//敵とプレイヤーのポッド当たっているとき処理
	
	//ポッド消滅処理
	if (m_del == true)
	{
		if (m_ani == 3 && m_bom == 0)
		{
			//[スペシャル技:ステロイド投与]発動中に実行
			//ポッドが破壊される度にその数をカウントする
			//※戦闘終了時は実行しない
			if (battle_end == false)
			{
				CObjSpecialButton* Special = (CObjSpecialButton*)Objs::GetObj(OBJ_SPECIAL);
				if (m_type == 0 && g_Special_equipment == 5 && Special->GetInvocating(0) == true && ButtonUP != 5)
				{
					Special->SetBuff_count(0);//破壊された強化ポッド数をカウントする
				}
				if (m_type != 0 && Special->GetSpecial_equip() == 5 && Special->GetInvocating(1) == true && ButtonUE != 5)
				{
					Special->SetBuff_count(1);//破壊された強化ポッド数をカウントする
				}
			}
				this->SetStatus(false);
				Hits::DeleteHitBox(this);
		}
	}
	
	//▼ポッドのダメージ処理
	//※戦闘終了後は以下のポッドのダメージ処理は行わない
	if (battle_end == false)
	{
		//プレイヤーのミサイルポッドがエネミーのスペシャル技(FRACTURE_RAY)のオブジェクトHIT時、
		//HPの状態に関わらず消滅処理へと移行する
		if (hit->CheckObjNameHit(OBJ_FRACTURE_RAY, 1) != nullptr && //エネミーのスペシャル技にHITかつ、
			m_type == 0)											//プレイヤーの射出したポッドである場合、実行
		{
			m_del = true;				//消滅処理フラグON
			hit->SetInvincibility(true);//当たり判定を無効化(無敵)
			Audio::Start(5);
		}

		//エネミーのミサイルポッドがプレイヤーのスペシャル技(FRACTURE_RAY)のオブジェクトHIT時、
		//HPの状態に関わらず消滅処理へと移行する
		if (hit->CheckObjNameHit(OBJ_FRACTURE_RAY, 0) != nullptr && //プレイヤーのスペシャル技にHITかつ、
			m_type != 0)										//エネミーの射出したポッドである場合、実行
		{
			m_del = true;				//消滅処理フラグON
			hit->SetInvincibility(true);//当たり判定を無効化(無敵)
			Audio::Start(5);
		}


		if (hit->CheckElementHit(ELEMENT_PLAYER) == true && m_type != 0)		//惑星に当たった時かつ敵弾
		{
			//惑星と接触しているかどうかを調べる
			m_del = true;
			hit->SetInvincibility(true);
			Audio::Start(5);
		}
		else if (hit->CheckElementHit(ELEMENT_ENEMY) == true && m_type == 0)	//敵の惑星に当たった時かつ自弾
		{
			//惑星と接触しているかどうかを調べる
			m_del = true;
			hit->SetInvincibility(true);
			Audio::Start(5);
		}

		//敵のポッドがプレイヤーのポッドにぶつかった時の判定
		//※エネミーがダメージを受ける時の処理
		if (hit->CheckElementHit(ELEMENT_POD) == true)
		{
			m_fight = true;	//衝突中フラグＯＮ
			
			if (ButtonUE == 1)		//敵の種類１(パワー)がプレイヤーのポッドと当たった場合
			{
				if (hit->CheckObjNameHit(OBJ_PODS) != nullptr)			//プレイヤーのスピードポッド当たり時のHP
				{
					m_podhp -= m_Enemy_damage * damage_buff[0] * 0.8f;
				}
				else if (hit->CheckObjNameHit(OBJ_PODD) != nullptr)		//プレイヤーのディフェンスポッド当たり時のHP
				{
					m_podhp -= m_Enemy_damage * damage_buff[0] * 1.2f;
				}
				else if (hit->CheckObjNameHit(OBJ_ROCKET) != nullptr)	//敵のミサイルに当たった時のHP処理
				{
					m_podhp -= 3;
				}
				else											//プレイヤーのパワーポッド、バランスポッド、ミサイル当たり時のHP
				{
					m_podhp -= m_Enemy_damage * damage_buff[0];
				}
			}
			else if (ButtonUE == 2)	//敵の種類２(ディフェンス)がプレイヤーのポッドと当たった場合
			{
				if (hit->CheckObjNameHit(OBJ_PODP) != nullptr)			//プレイヤーのパワーポッド当たり時のHP
				{
					m_podhp -= m_Enemy_damage * damage_buff[0] * 0.8f;
				}
				else if (hit->CheckObjNameHit(OBJ_PODS) != nullptr)		//プレイヤーのスピードポッド当たり時のHP
				{
					m_podhp -= m_Enemy_damage * damage_buff[0] * 1.2f;
				}
				else if (hit->CheckObjNameHit(OBJ_ROCKET) != nullptr)	//敵のミサイルに当たった時のHP処理
				{
					m_podhp -= 3;
				}
				else											//プレイヤーのディフェンスポッド、バランスポッド、ミサイル当たり時のHP
				{
					m_podhp -= m_Enemy_damage * damage_buff[0];
				}
			}
			else if (ButtonUE == 3)	//敵の種類３(スピード)がプレイヤーのポッドと当たった場合
			{
				if (hit->CheckObjNameHit(OBJ_PODP) != nullptr)			//プレイヤーのパワーポッド当たり時のHP
				{
					m_podhp -= m_Enemy_damage * damage_buff[0] * 1.2f;
				}
				else if (hit->CheckObjNameHit(OBJ_PODD) != nullptr)		//プレイヤーのディフェンスポッド当たり時のHP
				{
					m_podhp -= m_Enemy_damage * damage_buff[0] * 0.8f;
				}
				else if (hit->CheckObjNameHit(OBJ_ROCKET) != nullptr)	//敵のミサイルに当たった時のHP処理
				{
					m_podhp -= 3;
				}
				else											//プレイヤーのスピードポッド、バランスポッド、ミサイルに当たり時のHP
				{
					m_podhp -= m_Enemy_damage * damage_buff[0];
				}
			}
			else if (ButtonUE == 4)	//敵の種類４(バランス)がプレイヤーのポッドとミサイルに当たった場合
			{
				m_podhp -= m_Enemy_damage * damage_buff[0];
			}
			else if (ButtonUE == 5)	//敵の種類５(ミサイル)がプレイヤーのポッドに当たった場合
			{
				m_podhp -= m_Enemy_damage;
				m_fight = false;	//衝突中フラグを戻す
			}
		}
		else if(m_type != 0){	//当たってないかつ、自分が敵タイプ時
			m_fight = false;	//衝突中フラグＯＦＦ
		}

		//プレイヤーのポッドが敵のポッドとぶつかった時の判定
		//※プレイヤーがダメージを受ける時の処理
		if (hit->CheckElementHit(ELEMENT_ENEMYPOD) == true)
		{
			m_fight = true;	//衝突中フラグＯＮ
			Audio::Start(5);
			
			if (ButtonUP == 1)		//自分の種類１(パワー)が敵のポッドと当たった場合
			{
				if (hit->CheckObjNameHit(OBJ_PODS) != nullptr)			//敵のスピードポッド当たり時のHP
				{
					m_podhp -= m_Player_damage * damage_buff[1] * 0.8f;
				}
				else if (hit->CheckObjNameHit(OBJ_PODD) != nullptr)		//敵のディフェンスポッド当たり時のHP
				{
					m_podhp -= m_Player_damage * damage_buff[1] * 1.2f;
				}
				else if (hit->CheckObjNameHit(OBJ_ROCKET) != nullptr)	//敵のミサイルに当たった時のHP処理
				{
					m_podhp -= 3;
				}
				else											//敵のパワーポッド、バランスポッド、ミサイル当たり時のHP
				{
					m_podhp -= m_Player_damage * damage_buff[1];
				}
			}
			else if (ButtonUP == 2)	//自分の種類２(ディフェンス)が敵のポッドと当たった場合
			{
				if (hit->CheckObjNameHit(OBJ_PODP) != nullptr)			//敵のパワーポッド当たり時のHP
				{
					m_podhp -= m_Player_damage * damage_buff[1] * 0.8f;
				}
				else if (hit->CheckObjNameHit(OBJ_PODS) != nullptr)		//敵のスピードポッド当たり時のHP
				{
					m_podhp -= m_Player_damage * damage_buff[1] * 1.2f;
				}
				else if (hit->CheckObjNameHit(OBJ_ROCKET) != nullptr)	//敵のミサイルに当たった時のHP処理
				{
					m_podhp -= 3;
				}
				else											//敵のディフェンスポッド、バランスポッド、ミサイル当たり時のHP
				{
					m_podhp -= m_Player_damage * damage_buff[1];
				}
			}
			else if (ButtonUP == 3)//自分の種類３(スピード)が敵のポッドと当たった場合
			{
				if (hit->CheckObjNameHit(OBJ_PODP) != nullptr)			//敵のパワーポッド当たり時のHP
				{
					m_podhp -= m_Player_damage * damage_buff[1] * 1.2f;
				}
				else if (hit->CheckObjNameHit(OBJ_PODD) != nullptr)		//敵のディフェンスポッド当たり時のHP
				{
					m_podhp -= m_Player_damage * damage_buff[1] * 0.8f;
				}
				else if (hit->CheckObjNameHit(OBJ_ROCKET) != nullptr)	//敵のミサイルに当たった時のHP処理
				{
					m_podhp -= 3;
				}
				else											//敵のスピードポッド、バランスポッド、ミサイル当たり時のHP
				{
					m_podhp -= m_Player_damage * damage_buff[1];
				}

			}
			else if (ButtonUP == 4)//自分の種類４(バランス)が敵のポッドとミサイルに当たった場合
			{
				m_podhp -= m_Player_damage * damage_buff[1];
			}
			else if (ButtonUP == 5)//自分の種類５(ミサイル)が敵のポッドとミサイルに当たった場合
			{
				m_podhp -= m_Player_damage;
				m_fight = false;	//衝突中フラグを戻す
			}
			
		}
		else if(m_type == 0){	//当たってないかつ、自分が味方のタイプ時
			m_fight = false;	//衝突中フラグＯＦＦ
		}

		if (m_podhp <= 0)//HP
		{
			m_del = true;
			hit->SetInvincibility(true);
		}
	}
}

//ドロー
void CObjRocket::Draw()
{
	//描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	float d[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; //元の色
	float r[4] = { 1.0f, 0.0f, 0.0f, 1.0f }; //赤
	float g[4] = { 0.0f, 1.0f, 0.0f, 1.0f }; //緑
	float b[4] = { 0.0f, 0.2f, 2.0f, 1.0f }; //青
	float black[4] = { 0.0f, 0.0f, 0.0f, 1.0f };//黒(HPゲージ最大値で使用)
	float c[4] = { 1.0f,1.0f,1.0f,m_a };


	RECT_F src;//切り取り位置
	RECT_F dst;//表示位置

	if (m_type == 0)
	{
		switch (m_get_line) {
		case 0:m_r += 0.05 + m_mov_spd * 2; break;//ミサイル角度加算
		case 2:m_r -= 0.05 + m_mov_spd * 2; break;
		}
		
		if (ButtonUP >= 1 && ButtonUP <= 4)
		{
			//ポッドの描画情報
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 128.0f;
			src.m_bottom = 64.0f;

			dst.m_top = m_y + m_size;
			dst.m_left = m_x;
			dst.m_right = m_x + m_size;
			dst.m_bottom = m_y;
		}
		else
		{
			//ミサイルの描画情報
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 64.0f;
			src.m_bottom = 64.0f;

			dst.m_top = m_y;
			dst.m_left = m_x;
			dst.m_right = m_x + m_size;
			dst.m_bottom = m_y + m_size;
		}

		 //-----------ボタン赤・青・緑を分ける判定
		

		switch (ButtonUP) {
		case 1:
			Draw::Draw(8 + (g_Pod_equip_Level - 1), &src, &dst, r, m_r + 180);  //赤ポッド
			break;
		case 2:
			Draw::Draw(8 + (g_Pod_equip_Level - 1), &src, &dst, b, m_r + 180);  //青ポッド
			break;
		case 3:
			Draw::Draw(8 + (g_Pod_equip_Level - 1), &src, &dst, g, m_r + 180);   //緑ポッド
			break;
		case 4:
			Draw::Draw(8 + (g_Pod_equip_Level - 1), &src, &dst, d, m_r + 180);   //灰色ポッド
			break;
		case 5:
			if (m_get_line == 0)		{ Draw::Draw(17, &src, &dst, d, m_r + 35); }//ミサイルの
			else if (m_get_line == 2)	{ Draw::Draw(17, &src, &dst, d, m_r + 55); }//各ラインの角度調整
			else						{ Draw::Draw(17, &src, &dst, d, m_r + 45); }
			//else if ();
			break;
		}
		//Draw::Draw(10, &src, &dst, d, m_r - 15);
	}

	if(m_type != 0)
	{
		//敵ポッドの1〜4の番号(ポッド)の描画情報
		if (ButtonUE >= 1 && ButtonUE <= 4)
		{
			//ポッドの描画情報
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 128.0f;
			src.m_bottom = 64.0f;

			dst.m_top = m_y;
			dst.m_left = m_x;
			dst.m_right = m_x + m_size;
			dst.m_bottom = m_y + m_size;
		}
		else  //------------敵ミサイルの描画用
		{
			switch (m_get_line) {
			case 0:m_r -= 0.05 + m_mov_spd * 2; break;//ミサイル角度加算
			case 2:m_r += 0.05 + m_mov_spd * 2; break;
			case 3:m_r -= 0.05 + m_mov_spd * 2; break;
			}

			//ミサイルの描画情報
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 64.0f;
			src.m_bottom = 64.0f;

			dst.m_top = m_y;
			dst.m_left = m_x;
			dst.m_right = m_x + m_size;
			dst.m_bottom = m_y + m_size;
		}

		switch (ButtonUE) {
		case 1://---------ランダムの情報が1なら
			Draw::Draw(8 + (m_Enemy_Pod_Level - 1), &src, &dst, r, m_r);  //赤ポッド
			break;
		case 2://---------ランダムの情報が2なら
			Draw::Draw(8 + (m_Enemy_Pod_Level - 1), &src, &dst, b, m_r);  //青ポッド
			break;
		case 3://---------ランダムの情報が3なら
			Draw::Draw(8 + (m_Enemy_Pod_Level - 1), &src, &dst, g, m_r);   //緑ポッド
			break;
		case 4://---------ランダムの情報が4なら
			Draw::Draw(8 + (m_Enemy_Pod_Level - 1), &src, &dst, d, m_r);   //灰色ポッド
			break;
		case 5://---------ランダムの情報が5なら
			if (m_get_line == 1)		{ Draw::Draw(17, &src, &dst, d, m_r - 135); }//ミサイルの
			else if (m_get_line == 2)	{ Draw::Draw(17, &src, &dst, d, m_r - 145); }//各ラインの角度調整
			else						{ Draw::Draw(17, &src, &dst, d, m_r - 125); }
			break;
		}
	}

	//HPゲージ表示(ミサイル以外かつ破壊されていない時に表示される)
	if (ButtonU != 5 && m_del == false)
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 128.0f;
		src.m_bottom = 10.0f;

		dst.m_top = m_y + m_size;
		dst.m_left = m_x;
		dst.m_bottom = m_y + m_size + 5.0f;

		//▼最大値表示
		dst.m_right = m_x + m_size;
		Draw::Draw(32, &src, &dst, black, 0.0f);

		//▼現在値表示		
		dst.m_right = m_x + (m_size * ((float)m_podhp / (float)m_pod_max_hp));
		Draw::Draw(32, &src, &dst, d, 0.0f);
	}
	

	//爆発エフェクト
	//左斜め上
	if (m_bom== 0) 
	{
		dst.m_top = 0.0f + m_y;
		dst.m_left = 0.0f + m_x;
		dst.m_right = 50.0f + m_x;
		dst.m_bottom = 50.0f + m_y;
	}

	if (m_del == true) 
		Draw::Draw(16, &m_eff, &dst, c, 180.0f);

	//敵PODの体力とHPを表示する(デバッグ用)
	//wchar_t test_mou[256];
	//if (m_type != 0)
	//{
	//	swprintf_s(test_mou, L"HP%d,攻撃%d", m_podhp, m_Player_damage);
	//	Font::StrDraw(test_mou, 20.0f, 20.0f, 12.0f, d);
	//}
	//else
	//{
	//	swprintf_s(test_mou, L"HP%d,攻撃%d", m_podhp, m_Enemy_damage);
	//	Font::StrDraw(test_mou, 1100.0f, 20.0f, 12.0f, d);
	//}
	
}