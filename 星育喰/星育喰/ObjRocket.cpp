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
	if (ButtonU != 5) {
		
	}

	//▼ワンパターンデメリット処理
	//▽プレイヤーの処理
	if (m_type == 0)
	{
		CObjFight* obj = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
		
		//発射されたレーンのワンパターンデメリット値を受け取る
		m_One_pat_dem = Pla_One_pat_dem[obj->GetLine()];

		//発射されたレーンでのワンパターンデメリット値を減少させる(次回以降のミサイルポッドの攻撃力を減少させる)
		//※最低値の0.5の場合、実行されない。
		if (Pla_One_pat_dem[obj->GetLine()] < 1.5f)
		{
			Pla_One_pat_dem[obj->GetLine()] += 0.1f;
		}

		//発射されたレーン以外のレーンのワンパターンデメリット値を回復させる(次回以降のミサイルポッドの攻撃力が元の攻撃力に近づく)
		//※最高値の1.0の場合、実行されない。
		for (int i = 0; i < 3; i++)
		{
			if (Pla_One_pat_dem[i] > 1.0f && obj->GetLine() != i)
			{
				Pla_One_pat_dem[i] -= 0.1f;
			}
		}
	}
	//▽エネミーの処理
	else
	{
		CObjPlanet* ene = (CObjPlanet*)Objs::GetObj(OBJ_ENEMY);

		//発射されたレーンのワンパターンデメリット値を受け取る
		m_One_pat_dem = Ene_One_pat_dem[ene->GetLine() - 1];

		//発射されたレーンでのワンパターンデメリット値を減少させる(次回以降のミサイルポッドの攻撃力を減少させる)
		//※最低値の0.5の場合、実行されない。
		if (Ene_One_pat_dem[ene->GetLine() - 1] < 1.5f)
		{
			Ene_One_pat_dem[ene->GetLine() - 1] += 0.1f;
		}

		//発射されたレーン以外のレーンのワンパターンデメリット値を回復させる(次回以降のミサイルポッドの攻撃力が元の攻撃力に近づく)
		//※最高値の1.0の場合、実行されない。
		for (int i = 0; i < 3; i++)
		{
			if (Ene_One_pat_dem[i] > 1.0f && ene->GetLine() - 1 != i)
			{
				Ene_One_pat_dem[i] -= 0.1f;
			}
		}
	}

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

			//m_get_cnt = obj->GetCount();		//カウントを取得
			////m_x += obj->GetCount() / 10;
			//m_x += 0.0f;
			//m_mov_spd = 1.0f / pla->GetX();
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

	m_size = 50.0f;	//サイズ
	
	m_atk_cnt = 0;
	m_atk_cnt_max = 20;//(1/3秒)

	m_Enemy_Pod_Level = g_Stage_progress;	//現状、現在のステージ進行度に合わせて敵のポッドレベルを設定している
	m_pod_nam = (g_Power_num + g_Defense_num + g_Speed_num + g_Balance_num) / 1200;//各ポッドの住民総数

	m_vx = 0.0f;	//ベクトル
	m_vy = 0.0f;
	m_schange = 3.0f;
	m_mov = 0;
	
	m_r = 0.0f;		//角度

	if (m_type == 0)
		ButtonUP = ButtonU;
	else
		ButtonUE = ButtonU;

	m_pnam = p_pnam;//ポッドを排出した回数
	m_enam = e_pnam;

	//当たり判定用HitBox作成
	if (m_type == 0) 
	{
		m_x += 100;
		if (ButtonUP == 1)
		{
			switch (p_pnam) {
			case 0:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD, OBJ_PODP, 1); break;
			case 1:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD1, OBJ_PODP, 1); break;
			case 2:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD2, OBJ_PODP, 1); break;
			case 3:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD3, OBJ_PODP, 1); break;
			case 4:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD4, OBJ_PODP, 1); break;
			case 5:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD5, OBJ_PODP, 1); break;
			case 6:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD6, OBJ_PODP, 1); break;
			case 7:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD7, OBJ_PODP, 1); break;
			case 8:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD8, OBJ_PODP, 1); break;
			case 9:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD9, OBJ_PODP, 1); break;
			}
		}
		else if (ButtonUP == 2)
		{
			switch (p_pnam) {
			case 0:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD, OBJ_PODD, 1); break;
			case 1:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD1, OBJ_PODD, 1); break;
			case 2:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD2, OBJ_PODD, 1); break;
			case 3:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD3, OBJ_PODD, 1); break;
			case 4:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD4, OBJ_PODD, 1); break;
			case 5:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD5, OBJ_PODP, 1); break;
			case 6:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD6, OBJ_PODP, 1); break;
			case 7:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD7, OBJ_PODP, 1); break;
			case 8:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD8, OBJ_PODP, 1); break;
			case 9:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD9, OBJ_PODP, 1); break;
			}
		}
		else if (ButtonUP == 3)
		{
			switch (p_pnam) {
			case 0:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD, OBJ_PODS, 1); break;
			case 1:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD1, OBJ_PODS, 1); break;
			case 2:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD2, OBJ_PODS, 1); break;
			case 3:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD3, OBJ_PODS, 1); break;
			case 4:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD4, OBJ_PODS, 1); break;
			case 5:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD5, OBJ_PODP, 1); break;
			case 6:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD6, OBJ_PODP, 1); break;
			case 7:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD7, OBJ_PODP, 1); break;
			case 8:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD8, OBJ_PODP, 1); break;
			case 9:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD9, OBJ_PODP, 1); break;
			}
		}
		else if (ButtonUP == 4)
		{
			switch (p_pnam) {
			case 0:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD, OBJ_PODB, 1); break;
			case 1:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD1, OBJ_PODB, 1); break;
			case 2:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD2, OBJ_PODB, 1); break;
			case 3:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD3, OBJ_PODB, 1); break;
			case 4:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD4, OBJ_PODB, 1); break;
			case 5:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD5, OBJ_PODP, 1); break;
			case 6:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD6, OBJ_PODP, 1); break;
			case 7:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD7, OBJ_PODP, 1); break;
			case 8:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD8, OBJ_PODP, 1); break;
			case 9:Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD9, OBJ_PODP, 1); break;
			}
		}
		else if (ButtonUP == 5)
		{
			Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD, OBJ_ROCKET, 1);
		}
		if (ButtonUP != 5) {
			CObjRktHit* RH = new CObjRktHit(m_x, m_y, m_type);	//ヒットボックス用Obj作成
			Objs::InsertObj(RH, OBJ_RKTHIT, 15);				//オブジェクト登録
			p_pnam++;
		}
		if (p_pnam == 9)
			p_pnam = 0;
	}
	else if(m_type != 0)
	{
		m_x -= 100;
		if (ButtonUE == 1)
		{
			Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_ENEMYPOD, OBJ_PODP, 1);
			CObjRktHit* RH = new CObjRktHit(m_x, m_y, m_type);	//ヒットボックス用Obj作成
			Objs::InsertObj(RH, OBJ_RKTHIT, 15);				//オブジェクト登録
		}
		else if (ButtonUE == 2)
		{
			Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_ENEMYPOD, OBJ_PODD, 1);
			CObjRktHit* RH = new CObjRktHit(m_x, m_y, m_type);	//ヒットボックス用Obj作成
			Objs::InsertObj(RH, OBJ_RKTHIT, 15);				//オブジェクト登録
		}
		else if (ButtonUE == 3)
		{
			Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_ENEMYPOD, OBJ_PODS, 1);
			CObjRktHit* RH = new CObjRktHit(m_x, m_y, m_type);	//ヒットボックス用Obj作成
			Objs::InsertObj(RH, OBJ_RKTHIT, 15);				//オブジェクト登録
		}
		else if (ButtonUE == 4)
		{
			Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_ENEMYPOD, OBJ_PODB, 1);
			CObjRktHit* RH = new CObjRktHit(m_x, m_y, m_type);	//ヒットボックス用Obj作成
			Objs::InsertObj(RH, OBJ_RKTHIT, 15);				//オブジェクト登録
		}
		else if (ButtonUE == 5)
		{
			Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_ENEMYPOD, OBJ_ROCKET, 1);
		}
		if (ButtonUP != 5) {
			e_pnam++;
		}
		if (e_pnam == 9)
			e_pnam = 0;
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
		m_pod_max_hp = 1.0f;
	}
	else if (m_type == 0) {		//自惑星の時に(ポッドのLv*10)+(研究所のLv*5)をHPに代入する
		m_pod_max_hp = (float)((g_Pod_equip_Level * 10) + ((g_Ins_Level - 1)* 5));
	}
	else if (m_type == 1) {		//敵惑星の時は固定値
		m_pod_max_hp = 10.0f;
	}
	else if (m_type == 2) {
		m_pod_max_hp = 20.0f;
	}
	else if (m_type == 3) {
		m_pod_max_hp = 20.0f;
	}
	else if (m_type == 4) {
		m_pod_max_hp = 17.0f;
	}
	else if (m_type == 5) {
		m_pod_max_hp = 30.0f;
	}
	else if (m_type == 6) {
		m_pod_max_hp = 10.0f;
	}

	m_podhp = m_pod_max_hp;

	m_hp_cnt = 0;		//無敵タイム
	m_hp_f = false;		//無敵フラグ
	m_fight = false;	//衝突中フラグ
	m_stop_f = false;	//停止フラグ
	//m_pstop = false;	//ポッドでの停止フラグ
	m_stop_cnt = 0;		//止めるまでのカウント
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

	m_Enemy_damage = 2.0f;//エネミーが受けるダメージ量(プレイヤーの基礎攻撃力)
	m_Player_damage = 2.0f;//プレイヤーが受けるダメージ量(エネミーの基礎攻撃力)
	

	//敵の火力を敵によって変える
	switch (g_Challenge_enemy + 1) {
	case 1:
		m_Enemy_Pod_Level = 1;		//ポッドレベル設定
		m_Player_damage = 3.0f;		//プレイヤーへのポッドによる攻撃力決定
		g_P_Planet_damage = m_Player_damage;//ObjPlanetに渡す用
		break;
	case 2:
		m_Enemy_Pod_Level = 2;		//ポッドレベル設定
		m_Player_damage = 10.0f;
		g_P_Planet_damage = m_Player_damage;
		break;
	case 3:
		m_Enemy_Pod_Level = 2;		//ポッドレベル設定
		m_Player_damage = 15.0f;
		g_P_Planet_damage = m_Player_damage;
		break;
	case 4:
		m_Enemy_Pod_Level = 1;		//ポッドレベル設定
		m_Player_damage = 6.0f;
		g_P_Planet_damage = m_Player_damage;
		break;
	case 5:
		m_Enemy_Pod_Level = 3;		//ポッドレベル設定
		m_Player_damage = 17.0f;
		g_P_Planet_damage = m_Player_damage;
		break;
	case 6:
		m_Enemy_Pod_Level = 1;		//ポッドレベル設定
		m_Player_damage = 2.0f;
		g_P_Planet_damage = m_Player_damage;
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

	CObjFight* obj = (CObjFight*)Objs::GetObj(OBJ_FIGHT);	//戦闘画面の情報
	CHitBox* hit = Hits::GetHitBox(this);					//HitBox情報取得

	if (battle_end == true)
	{					//バトル終了時、存在している全てのポッドを破壊する
		Audio::Start(5);
		m_del = true;
	}

	//ポッド同士の戦闘時にHitBox位置とサイズを変更する
	if (m_type == 0)
		if (ButtonU == 5) {//ロケットのみ通常で更新
			hit->SetPos(m_x, m_y,m_size, m_size);		//HitBox更新
		}
		else
		{
			hit->SetPos(m_x, m_y, m_size, m_size);		//HitBox更新
			if (m_fight == true)		
				hit->SetPos(m_x - m_size * (m_schange - 1),m_y,m_size,m_size * m_schange);//戦闘時変更
		}
	else
	{
		hit->SetPos(m_x, m_y, m_size, m_size);			//HitBox更新
		if(m_fight == true)				
			hit->SetPos(m_x, m_y, m_size, m_size * m_schange);				//戦闘時変更
	}

	if (m_fight == true)
	{
		if (m_atk_cnt > m_atk_cnt_max)//maxを超えた時
		{
			m_atk_cnt = 0;//0にリセット
		}
		else//maxを超えてない時
		{
			m_atk_cnt++;//カウント
		}
	}

	//if (m_pstop == true)		//ポッド停止フラグON時
	//{
	//	m_stop_cnt+=0.5;
	//	if (m_stop_cnt == m_pod_nam)
	//	{
	//		hit->SetInvincibility(true);		//HitBoxの判定無効
	//		m_schange = 4.0f;
	//		m_fight = true;
	//	}
	//	else if (m_stop_cnt == m_pod_nam + 10)
	//	{
	//		hit->SetInvincibility(false);		//HitBoxの判定有効
	//		m_stop_cnt = 0;
	//	}
	//}
	//else
	//	m_schange = 3.0f;

	//if (m_pstop == false) {
		if (m_stop_f == true)	//停止フラグON時
		{
			m_stop_cnt++;
			if (m_stop_cnt == 8) {
				m_fight = true;
			}
			else if (m_stop_cnt == 11) {
				m_stop_cnt = 0;
			}
		}
		else if(m_del == false)//停止時以外、移動ベクトル加算
		{
			m_fight = false;
			m_mov += m_mov_spd / 2;

			//各ライン毎の動き方
			if (m_get_line == 0 || m_get_line == 3)//------上ライン----
			{
				m_vx -= 0.3f;
				m_vy += (-0.15 + m_mov);
			}
			else if (m_get_line == 1)//---------------中ライン-----
			{
				m_vx -= 0.3f;
			}
			else//if(m_get_line == 2)---------------下ライン------
			{
				m_vx -= 0.3f;
				m_vy -= (-0.15 + m_mov);
			}

			//-----------------------------座標更新
			if (m_type == 0) {
				m_x += m_vx * 2 - m_mov_spd * 200;
				m_y += m_vy * 2;
			}
			else {
				m_x -= m_vx * 2 - m_mov_spd * 200;
				m_y += m_vy * 2;
			}
		}
	//}
	

	//爆発エフェクト
	m_eff = GetPodEffec(&m_ani, &m_ani_time, m_del, 4);	//敵とプレイヤーのポッド当たっているとき処理
	
	//---------------------------------------ポッド消滅処理
	if (m_del == true)
	{
		hit->SetInvincibility(true);		//HitBoxの判定無効
		if (m_ani == 20 && m_bom == 0)
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
	
	//▼ポッドの当たり判定処理
	//※戦闘終了後は以下のポッドの処理は行わない
	if (battle_end == false)
	{
		if (ButtonU != 5) {		//ミサイル以外のストップ処理
			if (hit->CheckElementHit(ELEMENT_NULL) == true && m_type == 0)//Hit用OBJに当たった場合
				if ((hit->CheckObjNameHit(OBJ_RKTHIT) != nullptr && m_pnam == 0)||
					(hit->CheckObjNameHit(OBJ_RKTHIT1) != nullptr && m_pnam == 1) ||
					(hit->CheckObjNameHit(OBJ_RKTHIT2) != nullptr && m_pnam == 2) ||
					(hit->CheckObjNameHit(OBJ_RKTHIT3) != nullptr && m_pnam == 3) ||
					(hit->CheckObjNameHit(OBJ_RKTHIT4) != nullptr && m_pnam == 4) ||
					(hit->CheckObjNameHit(OBJ_RKTHIT5) != nullptr && m_pnam == 5) ||
					(hit->CheckObjNameHit(OBJ_RKTHIT6) != nullptr && m_pnam == 6) ||
					(hit->CheckObjNameHit(OBJ_RKTHIT7) != nullptr && m_pnam == 7) ||
					(hit->CheckObjNameHit(OBJ_RKTHIT8) != nullptr && m_pnam == 8) ||
					(hit->CheckObjNameHit(OBJ_RKTHIT9) != nullptr && m_pnam == 9))
					m_fight = true;
				else if ((hit->CheckObjNameHit(OBJ_eRKTHIT) != nullptr && m_pnam == 0) ||
					(hit->CheckObjNameHit(OBJ_eRKTHIT1) != nullptr && m_pnam == 1) ||
					(hit->CheckObjNameHit(OBJ_eRKTHIT2) != nullptr && m_pnam == 2) ||
					(hit->CheckObjNameHit(OBJ_eRKTHIT3) != nullptr && m_pnam == 3) ||
					(hit->CheckObjNameHit(OBJ_eRKTHIT4) != nullptr && m_pnam == 4) ||
					(hit->CheckObjNameHit(OBJ_eRKTHIT5) != nullptr && m_pnam == 5) ||
					(hit->CheckObjNameHit(OBJ_eRKTHIT6) != nullptr && m_pnam == 6) ||
					(hit->CheckObjNameHit(OBJ_eRKTHIT7) != nullptr && m_pnam == 7) ||
					(hit->CheckObjNameHit(OBJ_eRKTHIT8) != nullptr && m_pnam == 8) ||
					(hit->CheckObjNameHit(OBJ_eRKTHIT9) != nullptr && m_pnam == 9))
					m_fight = true;
				else
					m_fight = false;
			else
				m_fight = false;		//進める
		}

		if (m_type == 0) {	//同じタイプ同士での、衝突ストップ判定
			if (hit->CheckElementHit(ELEMENT_POD) == true && (m_pnam >= 1 && m_pnam <= 3))
				m_stop_f = true;
			else if (hit->CheckElementHit(ELEMENT_POD1) == true && (m_pnam >= 2 && m_pnam <= 4))
				m_stop_f = true;
			else if (hit->CheckElementHit(ELEMENT_POD2) == true && (m_pnam >= 3 && m_pnam <= 5))
				m_stop_f = true;
			else if (hit->CheckElementHit(ELEMENT_POD3) == true && (m_pnam >= 4 && m_pnam <= 6))
				m_stop_f = true;
			else if (hit->CheckElementHit(ELEMENT_POD4) == true && (m_pnam >= 5 && m_pnam <= 7))
				m_stop_f = true;
			else if (hit->CheckElementHit(ELEMENT_POD5) == true && (m_pnam >= 6 && m_pnam <= 8))
				m_stop_f = true;
			else if (hit->CheckElementHit(ELEMENT_POD6) == true && (m_pnam >= 7 && m_pnam <= 9))
				m_stop_f = true;
			else if (hit->CheckElementHit(ELEMENT_POD7) == true && (m_pnam >= 8 || m_pnam <= 0))
				m_stop_f = true;
			else if (hit->CheckElementHit(ELEMENT_POD8) == true && (m_pnam >= 9 || m_pnam <= 1))
				m_stop_f = true;
			else if (hit->CheckElementHit(ELEMENT_POD9) == true && (m_pnam >= 0 || m_pnam <= 2))
				m_stop_f = true;
			else if(m_fight == false)
				m_stop_f = false;
		}
		else {
			if (hit->CheckElementHit(ELEMENT_ENEMYPOD) == true && (m_pnam >= 1 && m_pnam <= 3))
				m_stop_f = true;
			else if (hit->CheckElementHit(ELEMENT_ENEMYPOD1) == true && (m_pnam >= 2 && m_pnam <= 4))
				m_stop_f = true;
			else if (hit->CheckElementHit(ELEMENT_ENEMYPOD2) == true && (m_pnam >= 3 && m_pnam <= 5))
				m_stop_f = true;
			else if (hit->CheckElementHit(ELEMENT_ENEMYPOD3) == true && (m_pnam >= 4 && m_pnam <= 6))
				m_stop_f = true;
			else if (hit->CheckElementHit(ELEMENT_ENEMYPOD4) == true && (m_pnam >= 5 && m_pnam <= 7))
				m_stop_f = true;
			else if (hit->CheckElementHit(ELEMENT_ENEMYPOD5) == true && (m_pnam >= 6 && m_pnam <= 8))
				m_stop_f = true;
			else if (hit->CheckElementHit(ELEMENT_ENEMYPOD6) == true && (m_pnam >= 7 && m_pnam <= 9))
				m_stop_f = true;
			else if (hit->CheckElementHit(ELEMENT_ENEMYPOD7) == true && (m_pnam >= 8 || m_pnam <= 0))
				m_stop_f = true;
			else if (hit->CheckElementHit(ELEMENT_ENEMYPOD8) == true && (m_pnam >= 9 || m_pnam <= 1))
				m_stop_f = true;
			else if (hit->CheckElementHit(ELEMENT_ENEMYPOD9) == true && (m_pnam >= 0 || m_pnam <= 2))
				m_stop_f = true;
			else if (m_fight == false)
				m_stop_f = false;
		}

		//プレイヤーのミサイルポッドがエネミーのスペシャル技(FRACTURE_RAY)のオブジェクトHIT時、
		//HPの状態に関わらず消滅処理へと移行する
		if (hit->CheckObjNameHit(OBJ_FRACTURE_RAY, 1) != nullptr && //エネミーのスペシャル技にHITかつ、
			m_type == 0)											//プレイヤーの射出したポッドである場合、実行
		{
			m_del = true;				//消滅処理フラグON
			Audio::Start(5);
		}

		//エネミーのミサイルポッドがプレイヤーのスペシャル技(FRACTURE_RAY)のオブジェクトHIT時、
		//HPの状態に関わらず消滅処理へと移行する
		if (hit->CheckObjNameHit(OBJ_FRACTURE_RAY, 0) != nullptr && //プレイヤーのスペシャル技にHITかつ、
			m_type != 0)										//エネミーの射出したポッドである場合、実行
		{
			m_del = true;				//消滅処理フラグON
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
		if ((hit->CheckElementHit(ELEMENT_POD) == true ||
			hit->CheckElementHit(ELEMENT_POD1) == true ||
			hit->CheckElementHit(ELEMENT_POD2) == true ||
			hit->CheckElementHit(ELEMENT_POD3) == true ||
			hit->CheckElementHit(ELEMENT_POD4) == true ||
			hit->CheckElementHit(ELEMENT_POD5) == true || 
			hit->CheckElementHit(ELEMENT_POD6) == true || 
			hit->CheckElementHit(ELEMENT_POD7) == true || 
			hit->CheckElementHit(ELEMENT_POD8) == true || 
			hit->CheckElementHit(ELEMENT_POD9) == true )&& m_type != 0)
		{
			m_fight = true;	//衝突中フラグＯＮ
			m_stop_f = true;
			
			if (ButtonUE == 1)		//敵の種類１(パワー)がプレイヤーのポッドと当たった場合
			{
				if (m_atk_cnt == 0)	//0の時のみ、各ダメージを受ける
				{
					if (hit->CheckObjNameHit(OBJ_PODS) != nullptr)			//プレイヤーのスピードポッド当たり時のHP
					{
						//m_Enemy_damage += (float)g_Spe_equip_Level;//プレイヤーの火力を装備レベルによって変える(+ポッドレベル)
						//m_Enemy_damage += (float)(g_Bar_Level - 1);//決まった火力+兵舎Lv

						//m_Enemy_damage *= m_One_pat_dem;//ワンパターンデメリット値の乗算を行う

						m_podhp -= m_Enemy_damage * damage_buff[0] * 0.8f * m_One_pat_dem + (float)g_Spe_equip_Level + (float)(g_Bar_Level - 1);
					}
					else if (hit->CheckObjNameHit(OBJ_PODD) != nullptr)		//プレイヤーのディフェンスポッド当たり時のHP
					{
						//m_Enemy_damage += (float)g_Def_equip_Level;//プレイヤーの火力を装備レベルによって変える(+ポッドレベル)
						//m_Enemy_damage += (float)(g_Bar_Level - 1);//決まった火力+兵舎Lv

						//m_Enemy_damage *= m_One_pat_dem;//ワンパターンデメリット値の乗算を行う

						m_podhp -= m_Enemy_damage * damage_buff[0] * 1.2f * m_One_pat_dem + (float)g_Def_equip_Level + (float)(g_Bar_Level - 1);
					}
					else if (hit->CheckObjNameHit(OBJ_PODP) != nullptr)		//プレイヤーのパワーポッド当たり時のHP
					{
						//m_Enemy_damage += (float)g_Pow_equip_Level;//プレイヤーの火力を装備レベルによって変える(+ポッドレベル)
						//m_Enemy_damage += (float)(g_Bar_Level - 1);//決まった火力+兵舎Lv

						//m_Enemy_damage *= m_One_pat_dem;//ワンパターンデメリット値の乗算を行う

						m_podhp -= m_Enemy_damage * damage_buff[0] * m_One_pat_dem + (float)g_Pow_equip_Level + (float)(g_Bar_Level - 1);
					}
					else if (hit->CheckObjNameHit(OBJ_PODB) != nullptr)//プレイヤーのバランスポッド当たり時のHP
					{
						//m_Enemy_damage += (float)g_Bal_equip_Level;//プレイヤーの火力を装備レベルによって変える(+ポッドレベル)
						//m_Enemy_damage += (float)(g_Bar_Level - 1);//決まった火力+兵舎Lv

						//m_Enemy_damage *= m_One_pat_dem;//ワンパターンデメリット値の乗算を行う

						m_podhp -= m_Enemy_damage * damage_buff[0] * 1.1f * m_One_pat_dem + (float)g_Bal_equip_Level + (float)(g_Bar_Level - 1);
					}
				}
				if (hit->CheckObjNameHit(OBJ_ROCKET) != nullptr)//敵のミサイルに当たった時のHP処理
				{
					//m_Enemy_damage = 3.0f;//ミサイルの時は火力3固定
					//m_Enemy_damage *= m_One_pat_dem;//ワンパターンデメリット値の乗算を行う

					m_podhp -= (m_Enemy_damage + 1.0f) * m_One_pat_dem;
				}
			}
			else if (ButtonUE == 2)	//敵の種類２(ディフェンス)がプレイヤーのポッドと当たった場合
			{
				if (m_atk_cnt == 0)	//0の時のみ、各ダメージを受ける
				{
					if (hit->CheckObjNameHit(OBJ_PODP) != nullptr)			//プレイヤーのパワーポッド当たり時のHP
					{
						//m_Enemy_damage += (float)g_Pow_equip_Level;//プレイヤーの火力を装備レベルによって変える(+ポッドレベル)
						//m_Enemy_damage += (float)(g_Bar_Level - 1);//決まった火力+兵舎Lv

						//m_Enemy_damage *= m_One_pat_dem;//ワンパターンデメリット値の乗算を行う

						m_podhp -= m_Enemy_damage * damage_buff[0] * 0.8f * m_One_pat_dem + (float)g_Pow_equip_Level + (float)(g_Bar_Level - 1);
					}
					else if (hit->CheckObjNameHit(OBJ_PODS) != nullptr)		//プレイヤーのスピードポッド当たり時のHP
					{
						//m_Enemy_damage += (float)g_Spe_equip_Level;//プレイヤーの火力を装備レベルによって変える(+ポッドレベル)
						//m_Enemy_damage += (float)(g_Bar_Level - 1);//決まった火力+兵舎Lv

						//m_Enemy_damage *= m_One_pat_dem;//ワンパターンデメリット値の乗算を行う

						m_podhp -= m_Enemy_damage * damage_buff[0] * 1.2f * m_One_pat_dem + (float)g_Spe_equip_Level + (float)(g_Bar_Level - 1);
					}
					else if (hit->CheckObjNameHit(OBJ_PODD) != nullptr)		//プレイヤーのディフェンスポッド当たり時のHP
					{
						//m_Enemy_damage += (float)g_Def_equip_Level;//プレイヤーの火力を装備レベルによって変える(+ポッドレベル)
						//m_Enemy_damage += (float)(g_Bar_Level - 1);//決まった火力+兵舎Lv

						//m_Enemy_damage *= m_One_pat_dem;//ワンパターンデメリット値の乗算を行う

						m_podhp -= m_Enemy_damage * damage_buff[0] * m_One_pat_dem + (float)g_Def_equip_Level + (float)(g_Bar_Level - 1);
					}
					else if (hit->CheckObjNameHit(OBJ_PODB) != nullptr)	//プレイヤーのバランスポッド当たり時のHP
					{
						//m_Enemy_damage += (float)g_Bal_equip_Level;//プレイヤーの火力を装備レベルによって変える(+ポッドレベル)
						//m_Enemy_damage += (float)(g_Bar_Level - 1);//決まった火力+兵舎Lv

						//m_Enemy_damage *= m_One_pat_dem;//ワンパターンデメリット値の乗算を行う

						m_podhp -= m_Enemy_damage * damage_buff[0] * 1.1f * m_One_pat_dem + (float)g_Bal_equip_Level + (float)(g_Bar_Level - 1);
					}
				}
				if (hit->CheckObjNameHit(OBJ_ROCKET) != nullptr)//敵のミサイルに当たった時のHP処理
				{
					//m_Enemy_damage = 3.0f;//ミサイルの時は火力3固定
					//m_Enemy_damage *= m_One_pat_dem;//ワンパターンデメリット値の乗算を行う

					m_podhp -= (m_Enemy_damage + 1.0f) * m_One_pat_dem;
				}
			}
			else if (ButtonUE == 3)	//敵の種類３(スピード)がプレイヤーのポッドと当たった場合
			{
				if (m_atk_cnt == 0)	//0の時のみ、各ダメージを受ける
				{
					if (hit->CheckObjNameHit(OBJ_PODP) != nullptr)			//プレイヤーのパワーポッド当たり時のHP
					{
						//m_Enemy_damage += (float)g_Pow_equip_Level;//プレイヤーの火力を装備レベルによって変える(+ポッドレベル)
						//m_Enemy_damage += (float)(g_Bar_Level - 1);//決まった火力+兵舎Lv

						//m_Enemy_damage *= m_One_pat_dem;//ワンパターンデメリット値の乗算を行う

						m_podhp -= m_Enemy_damage * damage_buff[0] * 1.2f * m_One_pat_dem + (float)g_Pow_equip_Level + (float)(g_Bar_Level - 1);
					}
					else if (hit->CheckObjNameHit(OBJ_PODD) != nullptr)		//プレイヤーのディフェンスポッド当たり時のHP
					{
						//m_Enemy_damage += (float)g_Def_equip_Level;//プレイヤーの火力を装備レベルによって変える(+ポッドレベル)
						//m_Enemy_damage += (float)(g_Bar_Level - 1);//決まった火力+兵舎Lv

						//m_Enemy_damage *= m_One_pat_dem;//ワンパターンデメリット値の乗算を行う

						m_podhp -= m_Enemy_damage * damage_buff[0] * 0.8f * m_One_pat_dem + (float)g_Def_equip_Level + (float)(g_Bar_Level - 1);
					}
					else if (hit->CheckObjNameHit(OBJ_PODS) != nullptr)		//プレイヤーのスピードポッド当たり時のHP
					{
						//m_Enemy_damage += (float)g_Spe_equip_Level;//プレイヤーの火力を装備レベルによって変える(+ポッドレベル)
						//m_Enemy_damage += (float)(g_Bar_Level - 1);//決まった火力+兵舎Lv

						//m_Enemy_damage *= m_One_pat_dem;//ワンパターンデメリット値の乗算を行う

						m_podhp -= m_Enemy_damage * damage_buff[0] * m_One_pat_dem + (float)g_Spe_equip_Level + (float)(g_Bar_Level - 1);
					}
					else if (hit->CheckObjNameHit(OBJ_PODB) != nullptr)	//プレイヤーのバランスポッド当たり時のHP
					{
						//m_Enemy_damage += (float)g_Bal_equip_Level;//プレイヤーの火力を装備レベルによって変える(+ポッドレベル)
						//m_Enemy_damage += (float)(g_Bar_Level - 1);//決まった火力+兵舎Lv

						//m_Enemy_damage *= m_One_pat_dem;//ワンパターンデメリット値の乗算を行う

						m_podhp -= m_Enemy_damage * damage_buff[0] * 1.1f * m_One_pat_dem + (float)g_Bal_equip_Level + (float)(g_Bar_Level - 1);
					}
				}
				if (hit->CheckObjNameHit(OBJ_ROCKET) != nullptr)//敵のミサイルに当たった時のHP処理
				{
					//m_Enemy_damage = 3.0f;//ミサイルの時は火力3固定
					//m_Enemy_damage *= m_One_pat_dem;//ワンパターンデメリット値の乗算を行う

					m_podhp -= (m_Enemy_damage + 1.0f) * m_One_pat_dem;
				}
			}
			else if (ButtonUE == 4)	//敵の種類４(バランス)がプレイヤーのポッドとミサイルに当たった場合
			{
				if (m_atk_cnt == 0)	//0の時のみ、ダメージを受ける
				{
					if (hit->CheckObjNameHit(OBJ_PODP) != nullptr)			//プレイヤーのパワーポッド当たり時のHP
					{
						//m_Enemy_damage += (float)g_Pow_equip_Level;//プレイヤーの火力を装備レベルによって変える(+ポッドレベル)
						//m_Enemy_damage += (float)(g_Bar_Level - 1);//決まった火力+兵舎Lv

						//m_Enemy_damage *= m_One_pat_dem;//ワンパターンデメリット値の乗算を行う

						m_podhp -= m_Enemy_damage * damage_buff[0] * 0.9f * m_One_pat_dem + (float)g_Pow_equip_Level + (float)(g_Bar_Level - 1);
					}
					else if (hit->CheckObjNameHit(OBJ_PODD) != nullptr)		//プレイヤーのディフェンスポッド当たり時のHP
					{
						//m_Enemy_damage += (float)g_Def_equip_Level;//プレイヤーの火力を装備レベルによって変える(+ポッドレベル)
						//m_Enemy_damage += (float)(g_Bar_Level - 1);//決まった火力+兵舎Lv

						//m_Enemy_damage *= m_One_pat_dem;//ワンパターンデメリット値の乗算を行う

						m_podhp -= m_Enemy_damage * damage_buff[0] * 0.9f * m_One_pat_dem + (float)g_Def_equip_Level + (float)(g_Bar_Level - 1);
					}
					else if (hit->CheckObjNameHit(OBJ_PODS) != nullptr)		//プレイヤーのスピードポッド当たり時のHP
					{
						//m_Enemy_damage += (float)g_Spe_equip_Level;//プレイヤーの火力を装備レベルによって変える(+ポッドレベル)
						//m_Enemy_damage += (float)(g_Bar_Level - 1);//決まった火力+兵舎Lv

						//m_Enemy_damage *= m_One_pat_dem;//ワンパターンデメリット値の乗算を行う

						m_podhp -= m_Enemy_damage * damage_buff[0] * 0.9f * m_One_pat_dem + (float)g_Spe_equip_Level + (float)(g_Bar_Level - 1);
					}
					else if (hit->CheckObjNameHit(OBJ_PODB) != nullptr)	//プレイヤーのバランスポッド当たり時のHP
					{
						//m_Enemy_damage += (float)g_Bal_equip_Level;//プレイヤーの火力を装備レベルによって変える(+ポッドレベル)
						//m_Enemy_damage += (float)(g_Bar_Level - 1);//決まった火力+兵舎Lv

						//m_Enemy_damage *= m_One_pat_dem;//ワンパターンデメリット値の乗算を行う

						m_podhp -= m_Enemy_damage * damage_buff[0] * m_One_pat_dem + (float)g_Bal_equip_Level + (float)(g_Bar_Level - 1);
					}
				}
				if (hit->CheckObjNameHit(OBJ_ROCKET) != nullptr)//敵のミサイルに当たった時のHP処理
				{
					//m_Enemy_damage = 3.0f;//ミサイルの時は火力3固定
					//m_Enemy_damage *= m_One_pat_dem;//ワンパターンデメリット値の乗算を行う
					
					m_podhp -= (m_pod_max_hp * 0.85) * m_One_pat_dem;//最大HP*0.85倍のダメージを与える
				}
			}
			else if (ButtonUE == 5)	//敵の種類５(ミサイル)がプレイヤーのポッドに当たった場合
			{
				m_del = true;				//消滅処理フラグON
				Audio::Start(5);
			}
		}
		else if (m_type != 0 && m_stop_cnt == 10) {	//敵かつ、停止時
			m_fight = false;
			m_stop_cnt = 0;
		}
		

		//プレイヤーのポッドが敵のポッドとぶつかった時の判定
		//※プレイヤーがダメージを受ける時の処理
		if (hit->CheckElementHit(ELEMENT_ENEMYPOD) == true && m_type == 0)
		{
			m_fight = true;	//衝突中フラグＯＮ
			m_stop_f = true;
			Audio::Start(5);
			
			if (ButtonUP == 1)		//自分の種類１(パワー)が敵のポッドと当たった場合
			{
				if (m_atk_cnt == 0)	//0の時のみ、各ダメージを受ける
				{
					if (hit->CheckObjNameHit(OBJ_PODS) != nullptr)			//敵のスピードポッド当たり時のHP
					{
						//m_Player_damage *= m_One_pat_dem;//ワンパターンデメリット値の乗算を行う

						m_podhp -= m_Player_damage * damage_buff[1] * 0.8f * m_One_pat_dem;
					}
					else if (hit->CheckObjNameHit(OBJ_PODD) != nullptr)		//敵のディフェンスポッド当たり時のHP
					{
						//m_Player_damage *= m_One_pat_dem;//ワンパターンデメリット値の乗算を行う

						m_podhp -= m_Player_damage * damage_buff[1] * 1.2f * m_One_pat_dem;
					}
					else if (hit->CheckObjNameHit(OBJ_PODP) != nullptr)		//敵のパワーポッド当たり時のHP
					{
						// * m_One_pat_demm_Player_damage *= m_One_pat_dem;//ワンパターンデメリット値の乗算を行う

						m_podhp -= m_Player_damage * damage_buff[1] * m_One_pat_dem;
					}
					else if (hit->CheckObjNameHit(OBJ_PODB) != nullptr)	//敵のバランスポッド当たり時のHP
					{
						//m_Player_damage *= m_One_pat_dem;//ワンパターンデメリット値の乗算を行う

						m_podhp -= m_Player_damage * damage_buff[1] * 1.1f * m_One_pat_dem;
					}
				}
				if (hit->CheckObjNameHit(OBJ_ROCKET) != nullptr)//敵のミサイルに当たった時のHP処理
				{
					//m_Player_damage = 3.0f;//ミサイルの時は火力3固定

					//m_Player_damage *= m_One_pat_dem;//ワンパターンデメリット値の乗算を行う

					m_podhp -= (m_Player_damage + 1.0f) * m_One_pat_dem;
				}
			}
			else if (ButtonUP == 2)	//自分の種類２(ディフェンス)が敵のポッドと当たった場合
			{
				if (m_atk_cnt == 0)	//0の時のみ、各ダメージを受ける
				{
					if (hit->CheckObjNameHit(OBJ_PODP) != nullptr)			//敵のパワーポッド当たり時のHP
					{
						//m_Player_damage *= m_One_pat_dem;//ワンパターンデメリット値の乗算を行う

						m_podhp -= m_Player_damage * damage_buff[1] * 0.8f * m_One_pat_dem;
					}
					else if (hit->CheckObjNameHit(OBJ_PODS) != nullptr)		//敵のスピードポッド当たり時のHP
					{
						//m_Player_damage *= m_One_pat_dem;//ワンパターンデメリット値の乗算を行う

						m_podhp -= m_Player_damage * damage_buff[1] * 1.2f * m_One_pat_dem;
					}
					else if (hit->CheckObjNameHit(OBJ_PODD) != nullptr)		//敵のディフェンスポッド当たり時のHP
					{
						//m_Player_damage *= m_One_pat_dem;//ワンパターンデメリット値の乗算を行う

						m_podhp -= m_Player_damage * damage_buff[1] * m_One_pat_dem;
					}
					else if (hit->CheckObjNameHit(OBJ_PODB) != nullptr)	//敵のバランスポッド当たり時のHP
					{
						//m_Player_damage *= m_One_pat_dem;//ワンパターンデメリット値の乗算を行う

						m_podhp -= m_Player_damage * damage_buff[1] * 1.1f * m_One_pat_dem;
					}
				}
				if (hit->CheckObjNameHit(OBJ_ROCKET) != nullptr)//敵のミサイルに当たった時のHP処理
				{
					//m_Player_damage = 3.0f;//ミサイルの時は火力3固定

					//m_Player_damage *= m_One_pat_dem;//ワンパターンデメリット値の乗算を行う
					
					m_podhp -= (m_Player_damage + 1.0f) * m_One_pat_dem;
				}
			}
			else if (ButtonUP == 3)//自分の種類３(スピード)が敵のポッドと当たった場合
			{
				if (m_atk_cnt == 0)	//0の時のみ、各ダメージを受ける
				{
					if (hit->CheckObjNameHit(OBJ_PODP) != nullptr)			//敵のパワーポッド当たり時のHP
					{
						//m_Player_damage *= m_One_pat_dem;//ワンパターンデメリット値の乗算を行う

						m_podhp -= m_Player_damage * damage_buff[1] * 1.2f * m_One_pat_dem;
					}
					else if (hit->CheckObjNameHit(OBJ_PODD) != nullptr)		//敵のディフェンスポッド当たり時のHP
					{
						//m_Player_damage *= m_One_pat_dem;//ワンパターンデメリット値の乗算を行う

						m_podhp -= m_Player_damage * damage_buff[1] * 0.8f * m_One_pat_dem;
					}
					else if (hit->CheckObjNameHit(OBJ_PODS) != nullptr)		//敵のスピードポッド当たり時のHP
					{
						//m_Player_damage *= m_One_pat_dem;//ワンパターンデメリット値の乗算を行う

						m_podhp -= m_Player_damage * damage_buff[1] * m_One_pat_dem;
					}
					else if (hit->CheckObjNameHit(OBJ_PODB) != nullptr)	//敵のバランスポッド当たり時のHP
					{
						//m_Player_damage *= m_One_pat_dem;//ワンパターンデメリット値の乗算を行う

						m_podhp -= m_Player_damage * damage_buff[1] * 1.1f * m_One_pat_dem;
					}
				}
				if (hit->CheckObjNameHit(OBJ_ROCKET) != nullptr)//敵のミサイルに当たった時のHP処理
				{
					//m_Player_damage = 3.0f;//ミサイルの時は火力3固定
					//m_Player_damage *= m_One_pat_dem;//ワンパターンデメリット値の乗算を行う

					m_podhp -= (m_Player_damage + 1.0f) * m_One_pat_dem;
				}
			}
			else if (ButtonUP == 4)//自分の種類４(バランス)が敵のポッドとミサイルに当たった場合
			{
				if (m_atk_cnt == 0)	//0の時のみ、ダメージを受ける
				{
					if (hit->CheckObjNameHit(OBJ_PODP) != nullptr)			//敵のパワーポッド当たり時のHP
					{
						//m_Player_damage *= m_One_pat_dem;//ワンパターンデメリット値の乗算を行う

						m_podhp -= m_Player_damage * damage_buff[1] * 0.9f * m_One_pat_dem;
					}
					else if (hit->CheckObjNameHit(OBJ_PODD) != nullptr)		//敵のディフェンスポッド当たり時のHP
					{
						//m_Player_damage *= m_One_pat_dem;//ワンパターンデメリット値の乗算を行う

						m_podhp -= m_Player_damage * damage_buff[1] * 0.9f * m_One_pat_dem;
					}
					else if (hit->CheckObjNameHit(OBJ_PODS) != nullptr)		//敵のスピードポッド当たり時のHP
					{
						//m_Player_damage *= m_One_pat_dem;//ワンパターンデメリット値の乗算を行う

						m_podhp -= m_Player_damage * damage_buff[1] * 0.9f * m_One_pat_dem;
					}
					else if (hit->CheckObjNameHit(OBJ_PODB) != nullptr)	//敵のバランスポッド当たり時のHP
					{
						//m_Player_damage *= m_One_pat_dem;//ワンパターンデメリット値の乗算を行う

						m_podhp -= m_Player_damage * damage_buff[1] * m_One_pat_dem;
					}
				}
				if (hit->CheckObjNameHit(OBJ_ROCKET) != nullptr)//敵のミサイルに当たった時のHP処理
				{
					//m_Player_damage = 3.0f;//ミサイルの時は火力3固定

					//m_Player_damage *= m_One_pat_dem;//ワンパターンデメリット値の乗算を行う
					
					m_podhp -= (m_pod_max_hp * 0.85) * m_One_pat_dem;//最大HP*0.85倍のダメージを与える
				}
			}
			else if (ButtonUP == 5)//自分の種類５(ミサイル)が敵のポッドとミサイルに当たった場合
			{
				m_del = true;				//消滅処理フラグON
				Audio::Start(5);
			}
			
		}
		else if (m_type == 0 && m_stop_cnt == 10) {	//味方かつ、止まってる時
			m_fight = false;
			m_stop_cnt = 0;
		
		}


		if (m_podhp <= 0)//両ポッドHPでの削除
		{
			m_del = true;
		}
	}

	
}

//ドロー
void CObjRocket::Draw()
{
	//描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	float d[4] =	{ 1.0f, 1.0f, 1.0f, 1.0f }; //元の色
	float r[4] =	{ 1.0f, 0.0f, 0.0f, 1.0f }; //赤
	float g[4] =	{ 0.0f, 1.0f, 0.0f, 1.0f }; //緑
	float b[4] =	{ 0.0f, 0.2f, 2.0f, 1.0f }; //青
	float black[4]=	{ 0.0f, 0.0f, 0.0f, 1.0f };	//黒(HPゲージ最大値で使用)
	float c[4] =	{ 1.0f,1.0f,1.0f,m_a };


	RECT_F src;//切り取り位置
	RECT_F dst;//表示位置
	if (m_ani < 10) {		//着弾アニメーションの途中まで描画
		if (m_type == 0)
		{
			if (m_stop_f == false /*&& m_pstop == false*/)
			{
				switch (m_get_line) {
				case 0:m_r += 0.08 + m_mov_spd * 2; break;//ミサイル角度加算
				case 2:m_r -= 0.08 + m_mov_spd * 2; break;
				}
			}

			if (ButtonUP >= 1 && ButtonUP <= 4)
			{
				//ポッドの描画情報
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = -64.0f;
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
				if (m_get_line == 1) { Draw::Draw(65 + (g_Pod_equip_Level - 1), &src, &dst, d, m_r - 180); }//赤色ポッドの
				else if (m_get_line == 2) { Draw::Draw(65 + (g_Pod_equip_Level - 1), &src, &dst, d, m_r - 160); }//各ラインの角度調整
				else { Draw::Draw(65 + (g_Pod_equip_Level - 1), &src, &dst, d, m_r - 200); }
				break;
			case 2:
				if (m_get_line == 1) { Draw::Draw(68 + (g_Pod_equip_Level - 1), &src, &dst, d, m_r - 180); }//青色ポッドの
				else if (m_get_line == 2) { Draw::Draw(68 + (g_Pod_equip_Level - 1), &src, &dst, d, m_r - 160); }//各ラインの角度調整
				else { Draw::Draw(68 + (g_Pod_equip_Level - 1), &src, &dst, d, m_r - 200); }
				break;
			case 3:
				if (m_get_line == 1) { Draw::Draw(71 + (g_Pod_equip_Level - 1), &src, &dst, d, m_r - 180); }//緑色ポッドの
				else if (m_get_line == 2) { Draw::Draw(71 + (g_Pod_equip_Level - 1), &src, &dst, d, m_r - 160); }//各ラインの角度調整
				else { Draw::Draw(71 + (g_Pod_equip_Level - 1), &src, &dst, d, m_r - 200); }
				break;
			case 4:
				if (m_get_line == 1) { Draw::Draw(74 + (g_Pod_equip_Level - 1), &src, &dst, d, m_r - 180); }//原色ポッドの
				else if (m_get_line == 2) { Draw::Draw(74 + (g_Pod_equip_Level - 1), &src, &dst, d, m_r - 160); }//各ラインの角度調整
				else { Draw::Draw(74 + (g_Pod_equip_Level - 1), &src, &dst, d, m_r - 200); }
				break;
			case 5:
				if (m_get_line == 1) { Draw::Draw(17, &src, &dst, d, m_r + 45); }//ミサイルの
				else if (m_get_line == 2) { Draw::Draw(17, &src, &dst, d, m_r + 65); }//各ラインの角度調整
				else { Draw::Draw(17, &src, &dst, d, m_r + 25); }
				//else if ();
				break;
			}
			//Draw::Draw(10, &src, &dst, d, m_r - 15);
		}

		if (m_type != 0)
		{
			if (m_stop_f == false/* && m_pstop == false*/)
			{
				switch (m_get_line) {
				case 0:m_r -= 0.08 + m_mov_spd * 2; break;//ミサイル角度加算
				case 2:m_r += 0.08 + m_mov_spd * 2; break;
				case 3:m_r -= 0.08 + m_mov_spd * 2; break;
				}
			}

			//敵ポッドの1～4の番号(ポッド)の描画情報
			if (ButtonUE >= 1 && ButtonUE <= 4)
			{
				//ポッドの描画情報
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = -64.0f;
				src.m_bottom = 64.0f;

				dst.m_top = m_y;
				dst.m_left = m_x;
				dst.m_right = m_x + m_size;
				dst.m_bottom = m_y + m_size;
			}
			else  //------------敵ミサイルの描画用
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

			switch (ButtonUE) {
			case 1://---------ランダムの情報が1なら
				if (m_get_line == 1) { Draw::Draw(65 + (m_Enemy_Pod_Level - 1), &src, &dst, d, m_r); }//赤色ポッドの
				else if (m_get_line == 2) { Draw::Draw(65 + (m_Enemy_Pod_Level - 1), &src, &dst, d, m_r - 20); }//各ラインの角度調整
				else { Draw::Draw(65 + (m_Enemy_Pod_Level - 1), &src, &dst, d, m_r + 20); }
				break;
			case 2://---------ランダムの情報が2なら
				if (m_get_line == 1) { Draw::Draw(68 + (m_Enemy_Pod_Level - 1), &src, &dst, d, m_r); }//青色ポッドの
				else if (m_get_line == 2) { Draw::Draw(68 + (m_Enemy_Pod_Level - 1), &src, &dst, d, m_r - 20); }//各ラインの角度調整
				else { Draw::Draw(68 + (m_Enemy_Pod_Level - 1), &src, &dst, d, m_r + 20); }
				break;
			case 3://---------ランダムの情報が3なら
				if (m_get_line == 1) { Draw::Draw(71 + (m_Enemy_Pod_Level - 1), &src, &dst, d, m_r); }//緑色ポッドの
				else if (m_get_line == 2) { Draw::Draw(71 + (m_Enemy_Pod_Level - 1), &src, &dst, d, m_r - 20); }//各ラインの角度調整
				else { Draw::Draw(71 + (m_Enemy_Pod_Level - 1), &src, &dst, d, m_r + 20); }
				break;
			case 4://---------ランダムの情報が4なら
				if (m_get_line == 1) { Draw::Draw(74 + (m_Enemy_Pod_Level - 1), &src, &dst, d, m_r); }//原色ポッドの
				else if (m_get_line == 2) { Draw::Draw(74 + (m_Enemy_Pod_Level - 1), &src, &dst, d, m_r - 20); }//各ラインの角度調整
				else { Draw::Draw(74 + (m_Enemy_Pod_Level - 1), &src, &dst, d, m_r + 20); }
				break;
			case 5://---------ランダムの情報が5なら
				if (m_get_line == 1) { Draw::Draw(17, &src, &dst, d, m_r - 135); }//各ラインの角度調整
				else if (m_get_line == 2) { Draw::Draw(17, &src, &dst, d, m_r - 155); }//ミサイルの
				else { Draw::Draw(17, &src, &dst, d, m_r - 115); }
				break;
			}
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
		Draw::Draw(32, &src, &dst, g, 0.0f);
	}
	

	//爆発エフェクト
	if (m_del == 1)
	{
		dst.m_top = -48.0f + m_y;
		dst.m_left = -48.0f + m_x;
		dst.m_right = 80.0f + m_x;
		dst.m_bottom = 80.0f + m_y;
		Draw::Draw(16, &m_eff, &dst, c, 0.0f);
	}

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
