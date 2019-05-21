//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"


#include "GameHead.h"
#include "UtilityModule.h"
#include "ObjRocket.h"

#include <time.h>

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjRocket::CObjRocket(float x, float y, bool type,int n)
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

	if (m_type == true) {
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
	//▼敵惑星攻撃パターン
	else if (m_type == false && battle_end == false)//惑星が敵の時のみ弾を発射し、戦闘終了時に弾を打たないようにする。
	{
		//▼敵行動パターン決め
		if (m_time <= 0)
		{
			int Enemy_Fight_line[5][6] =   //敵攻撃用の配列作成
			{
				//1=赤,2=青,3=緑,4=灰色,5=ミサイル
				{ 3,2,1,1,2,0 }, //0番目
				{ 3,3,2,3,1,0 }, //1番目
				{ 1,2,3,2,3,0 }, //2番目
				{ 2,1,1,2,3,0 }, //3番目
				{ 1,3,2,2,1,0 }, //4番目

				/*
				攻撃パターン追加する際は、上の配列の数字を変え
				下のコメントアウトを取って、出したい種類の数字をカンマごとに順番に入れてください。
				{,,,,,}, //5番目
				{,,,,,}, //6番目
				{,,,,,}, //7番目
				{,,,,,}, //8番目
				*/
			};

			m_get_line = Enemy_Fight_line[Enemy_Line_pattern_y][Enemy_Line_pattern_x];
			if (m_get_line == 0)//--------配列が最後に行ったとき(0の時)
			{
				Enemy_Line_pattern_x = 0;//配列一番左の状態に戻す
										   //↓行動パターンを決める,ランダムを割っている数字と配列の種類を増やすと攻撃パターンが増える	
				srand(time(NULL));
				Enemy_Line_pattern_x = rand() % 5;
				//↓m_attackに攻撃パターンを入れる処理
				m_get_line = Enemy_Fight_line[Enemy_Line_pattern_y][Enemy_Line_pattern_x];
				Enemy_Line_pattern_x++;
			}
			else
			{
				Enemy_Line_pattern_x++;
			}
		}
	}
	//else {
	//	CObjFight* obj = (CObjFight*)Objs::GetObj(OBJ_FIGHT);

	//	srand(time(NULL));
	//	m_get_line = rand() % 3 + 1;
	//	if (m_get_line == 1) { m_y = 310; }	//取得ナンバーで高さ変更
	//	else if (m_get_line == 2) { m_y = 420; }

	//	m_get_cnt = obj->GetCount();		//カウントを取得
	//	m_mov_spd = 1.0f / pla->GetX();

	//	srand(time(NULL));
	//	//敵のポッドの番号をランダムにする処理
	//	Enemypod = rand() % 5 + 1;	
	//}

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

	//当たり判定用HitBox作成
	if (m_type == true) 
	{
		m_x += 100;
		if (ButtonU == 1)
		{
			Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD, OBJ_PODP, 1);
		}
		else if (ButtonU == 2)
		{
			Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD, OBJ_PODS, 1);
		}
		else if (ButtonU == 3)
		{
			Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD, OBJ_PODD, 1);
		}
		else if (ButtonU == 4)
		{
			Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD, OBJ_PODB, 1);
		}
		else if (ButtonU == 5)
		{
			Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_POD, OBJ_Rocket, 1);
		}

	}
	else 
	{
		m_x -= 100;
		if (ButtonU == 1)
		{
			Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_ENEMYPOD, OBJ_PODP, 1);
		}
		else if (ButtonU == 2)
		{
			Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_ENEMYPOD, OBJ_PODD, 1);
		}
		else if (ButtonU == 3)
		{
			Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_ENEMYPOD, OBJ_PODS, 1);
		}
		else if (ButtonU == 4)
		{
			Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_ENEMYPOD, OBJ_PODB, 1);
		}
		else if (ButtonU == 5)
		{
			Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_ENEMYPOD, OBJ_Rocket, 1);
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

	m_podhp = 10;

	m_hp_cnt = 0;		//無敵タイム
	m_hp_f = false;		//無敵フラグ

	m_Enemy_damage = 10;
	m_Player_damage = 10;
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

	if (obj->GetCount() <= 60)
		m_del = true;

	if (m_mou_l == false && m_mou_f == false)
	{
		m_mou_f = true;
	}
	else
	{
		m_mou_f = false;
	}

	//爆発エフェクト回数処理
	if (m_del == true)
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

		//-----------------------座標更新
		if (m_type == true) {
			m_x += m_vx - m_mov_spd * 200;
			m_y += m_vy;
		}
		else {
			m_x -= m_vx - m_mov_spd * 200;
			m_y += m_vy;
		}
	}
	//-----------------------座標更新
	if (m_type == true) {
		m_x += m_vx;
		m_y += m_vy;
	}
	else {
		m_x -= m_vx;
		m_y += m_vy;
	}

	//爆発エフェクト
	m_eff = GetPodEffec(&m_ani, &m_ani_time, m_del, 5);	//敵とプレイヤーのポッド当たっているとき処理
	
	//ポッド消滅処理
	if (m_del == true)
	{
		if(m_bom != 5)	//５以外の場合
			m_bom = Rand(0, 4);//ランダムな爆発を起こす
		if (m_ani == 4 && m_bom == 5)
		{
			//[スペシャル技:ステロイド投与]発動中に実行
			//ポッドが破壊される度にその数をカウントする
			//※戦闘終了時は実行しない
			if (battle_end == false)
			{
				CObjSpecialButton* Special = (CObjSpecialButton*)Objs::GetObj(OBJ_SPECIAL);
				if (m_type == true && g_Special_equipment == 5 && Special->GetInvocating(0) == true && ButtonU != 5)
				{
					Special->SetBuff_count(0);//破壊された強化ポッド数をカウントする
				}
				if (m_type == false && Special->GetSpecial_equip() == 5 && Special->GetInvocating(1) == true && ButtonU != 5)
				{
					Special->SetBuff_count(1);//破壊された強化ポッド数をカウントする
				}
			}

			this->SetStatus(false);
			Hits::DeleteHitBox(this);
		}
		if (m_ani == 4)
		{
			m_ani = 0;
			m_bom = 5;
		}
		
	}
	
	//プレイヤーのミサイルポッドがエネミーのスペシャル技(FRACTURE_RAY)のオブジェクトHIT時、
	//HPの状態に関わらず消滅処理へと移行する
	if (hit->CheckObjNameHit(OBJ_FRACTURE_RAY, 1) != nullptr && //エネミーのスペシャル技にHITかつ、
		m_type == true)											//プレイヤーの射出したポッドである場合、実行
	{
		m_del = true;				//消滅処理フラグON
		hit->SetInvincibility(true);//当たり判定を無効化(無敵)
	}

	//エネミーのミサイルポッドがプレイヤーのスペシャル技(FRACTURE_RAY)のオブジェクトHIT時、
	//HPの状態に関わらず消滅処理へと移行する
	if (hit->CheckObjNameHit(OBJ_FRACTURE_RAY, 0) != nullptr && //プレイヤーのスペシャル技にHITかつ、
		m_type == false)										//エネミーの射出したポッドである場合、実行
	{
		m_del = true;				//消滅処理フラグON
		hit->SetInvincibility(true);//当たり判定を無効化(無敵)
	}


	if (hit->CheckElementHit(ELEMENT_PLAYER) == true && m_type == false)//惑星に当たった時かつ自弾
	{
		//位置を更新//惑星と接触しているかどうかを調べる
		m_del = true;
		hit->SetInvincibility(true);
	}
	else if (hit->CheckElementHit(ELEMENT_ENEMY) == true && m_type == true)//敵の惑星に当たった時かつ自弾
	{
		//位置を更新//惑星と接触しているかどうかを調べる
		m_del = true;
		hit->SetInvincibility(true);
	}

	//敵のポッドがプレイヤーのポッドにぶつかった時の判定
	//※エネミーがダメージを受ける時の処理
	if (hit->CheckElementHit(ELEMENT_POD) == true)
	{
		if (ButtonU == 1)//敵の種類１(パワー)がプレイヤーのポッドと当たった場合
		{
			if (hit->CheckObjNameHit(OBJ_PODD) != nullptr)	//プレイヤーのディフェンスポッド当たり時のHP
			{
				m_podhp -= m_Enemy_damage * damage_buff[0] * 0.8f;
			}
			else if (hit->CheckObjNameHit(OBJ_PODS) != nullptr)	//プレイヤーのスピードポッド当たり時のHP
			{
				m_podhp -= m_Enemy_damage * damage_buff[0] * 1.2f;
			}
			else											//プレイヤーのパワーポッド、バランスポッド、ミサイル当たり時のHP
			{
				m_podhp -= m_Enemy_damage * damage_buff[0];
			}
		}
		else if (ButtonU == 2)//敵の種類２(スピード)がプレイヤーのポッドと当たった場合
		{
			if (hit->CheckObjNameHit(OBJ_PODP) != nullptr)	//プレイヤーのパワーポッド当たり時のHP
			{
				m_podhp -= m_Enemy_damage * damage_buff[0] * 0.8f;
			}
			else if (hit->CheckObjNameHit(OBJ_PODD) != nullptr)	//プレイヤーのディフェンスポッド当たり時のHP
			{
				m_podhp -= m_Enemy_damage * damage_buff[0] * 1.2f;
			}
			else											//プレイヤーのスピードポッド、バランスポッド、ミサイル当たり時のHP
			{
				m_podhp -= m_Enemy_damage * damage_buff[0];
			}
		}
		else if (ButtonU == 3)//敵の種類３(ディフェンス)がプレイヤーのポッドと当たった場合
		{
			if (hit->CheckObjNameHit(OBJ_PODP) != nullptr)	//プレイヤーのパワーポッド当たり時のHP
			{
				m_podhp -= m_Enemy_damage * damage_buff[0] * 1.2f;
			}
			else if (hit->CheckObjNameHit(OBJ_PODS) != nullptr)	//プレイヤーのスピードポッド当たり時のHP
			{
				m_podhp -= m_Enemy_damage * damage_buff[0] * 0.8f;
			}
			else											//プレイヤーのディフェンスポッド、バランスポッド、ミサイルに当たり時のHP
			{
				m_podhp -= m_Enemy_damage * damage_buff[0];
			}
		}
		else if (ButtonU == 4)//敵の種類４(バランス)がプレイヤーのポッドとミサイルに当たった場合
		{
			m_podhp -= m_Enemy_damage * damage_buff[0];
		}
		else if (ButtonU == 5)//敵の種類５(ミサイル)がプレイヤーのポッドに当たった場合
		{
			m_podhp -= m_Enemy_damage;
		}
	}

	//プレイヤーのポッドが敵のポッドとぶつかった時の判定
	//※プレイヤーがダメージを受ける時の処理
	if (hit->CheckElementHit(ELEMENT_ENEMYPOD) == true)
	{
		if (ButtonU == 1)//自分の種類１(パワー)が敵のポッドと当たった場合
		{
			if (hit->CheckObjNameHit(OBJ_PODD) != nullptr)	//敵のディフェンスポッド当たり時のHP
			{
				m_podhp -= m_Player_damage * damage_buff[1] * 0.8f;
			}
			else if (hit->CheckObjNameHit(OBJ_PODS) != nullptr)	//敵のスピードポッド当たり時のHP
			{
				m_podhp -= m_Player_damage * damage_buff[1] * 1.2f;
			}
			else											//敵のパワーポッド、バランスポッド、ミサイル当たり時のHP
			{
				m_podhp -= m_Player_damage * damage_buff[1];
			}
		}
		else if (ButtonU == 2)//自分の種類２(スピード)が敵のポッドと当たった場合
		{
			if (hit->CheckObjNameHit(OBJ_PODP) != nullptr)	//敵のパワーポッド当たり時のHP
			{
				m_podhp -= m_Player_damage * damage_buff[1] * 0.8f;
			}
			else if (hit->CheckObjNameHit(OBJ_PODD) != nullptr)	//敵のディフェンスポッド当たり時のHP
			{
				m_podhp -= m_Player_damage * damage_buff[1] * 1.2f;
			}
			else											//敵のスピードポッド、バランスポッド、ミサイル当たり時のHP
			{
				m_podhp -= m_Player_damage * damage_buff[1];
			}
		}
		else if (ButtonU == 3)//自分の種類３(ディフェンス)が敵のポッドと当たった場合
		{
			if (hit->CheckObjNameHit(OBJ_PODP) != nullptr)	//敵のパワーポッド当たり時のHP
			{
				m_podhp -= m_Player_damage * damage_buff[1] * 1.2f;
			}
			else if (hit->CheckObjNameHit(OBJ_PODS) != nullptr)	//敵のスピードポッド当たり時のHP
			{
				m_podhp -= m_Player_damage * damage_buff[1] * 0.8f;
			}
			else											//敵のディフェンスポッド、バランスポッド、ミサイル当たり時のHP
			{
				m_podhp -= m_Player_damage * damage_buff[1];
			}

		}
		else if (ButtonU == 4)//自分の種類４(バランス)が敵のポッドとミサイルに当たった場合
		{
			m_podhp -= m_Player_damage * damage_buff[1];
		}
		else if (ButtonU == 5)//自分の種類５(ミサイル)が敵のポッドとミサイルに当たった場合
		{
			m_podhp -= m_Player_damage;
		}
	}
	
	if (m_podhp <= 0)//HP
	{
		m_del = true;
		hit->SetInvincibility(true);
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
	float c[4] = { 1.0f,1.0f,1.0f,m_a };


	RECT_F src;//切り取り位置
	RECT_F dst;//表示位置

	if (m_type == true) 
	{
		m_r += 0.05 + m_mov_spd * 2;
		if (ButtonU >= 1 && ButtonU <= 4)
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
		

		switch (ButtonU) {
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
			Draw::Draw(17, &src, &dst, d, m_r + 35);   //ミサイル
			break;
		}
		//Draw::Draw(10, &src, &dst, d, m_r - 15);
	}

	if(m_type==false)
	{
		//敵ポッドの1～4の番号(ポッド)の描画情報
		if (ButtonU >= 1 && ButtonU <= 4)
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

		if (m_type == false) { //-----------敵の赤・青・緑を分ける判定
			m_r += 0.05 + m_mov_spd * 2;

			switch (ButtonU) {
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
				Draw::Draw(17, &src, &dst, d, m_r-145);   //ミサイル
				break;
			}
		}
	}

	//エフェクト
	//左斜め上
	if (m_bom== 0) 
	{
		dst.m_top = 0.0f + m_y;
		dst.m_left = 0.0f + m_x;
		dst.m_right = 32.0f + m_x;
		dst.m_bottom = 29.0f + m_y;
	}

	//真ん中
	else if (m_bom == 1)
	{
		dst.m_top = 0.0f + m_y+10;
		dst.m_left = 0.0f + m_x+10;
		dst.m_right = 42.0f + m_x;
		dst.m_bottom = 39.0f + m_y;
	}

	//右斜め上
	else if (m_bom == 2)
	{
		dst.m_top = 0.0f + m_y;
		dst.m_left = 32.0f + m_x;
		dst.m_right = 64.0f + m_x;
		dst.m_bottom = 29.0f + m_y;
	}

	//左斜め下
	else if (m_bom == 3)
	{
		dst.m_top = 29.0f + m_y;
		dst.m_left = 0.0f + m_x;
		dst.m_right = 32.0f + m_x;
		dst.m_bottom = 58.0f + m_y;
	}

	//右斜め下
	else if (m_bom == 4)
	{
		dst.m_top = 29.0f + m_y;
		dst.m_left = 32.0f + m_x;
		dst.m_right = 64.0f + m_x;
		dst.m_bottom = 58.0f + m_y;
	}
	//大きいやつ
	else if (m_bom == 5)
	{
		dst.m_top = 0.0f + m_y;
		dst.m_left = 0.0f + m_x;
		dst.m_right = 50.0f + m_x;
		dst.m_bottom = 50.0f + m_y;
	}

	
	if (m_del == true) 
		Draw::Draw(16, &m_eff, &dst, c, 180.0f);
	



}