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
	else {
		CObjFight* obj = (CObjFight*)Objs::GetObj(OBJ_FIGHT);

		srand(time(NULL));
		m_get_line = rand() % 3 + 1;
		if (m_get_line == 1) { m_y = 310; }	//取得ナンバーで高さ変更
		else if (m_get_line == 2) { m_y = 420; }

		m_get_cnt = obj->GetCount();		//カウントを取得
		m_mov_spd = 1.0f / pla->GetX();

		srand(time(NULL));
		//敵のポッドの番号をランダムにする処理
		Enemypod = rand() % 5 + 1;	
	}

	m_size = 50.0f;//サイズ
	
	m_time = 100;

	m_Enemy_Pod_Level = 1;

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
			Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_ENEMYPOD, OBJ_PODS, 1);
		}
		else if (ButtonU == 3)
		{
			Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_ENEMYPOD, OBJ_PODD, 1);
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
}

//アクション
void CObjRocket::Action()
{
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
		/*if (m_ani == 4)
		{
			m_ani = 0;
			m_ani_max++;
		}*/
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

	CHitBox* hit = Hits::GetHitBox(this);		//HitBox情報取得
	hit->SetPos(m_x, m_y, m_size, m_size);		//HitBox更新

	

	//爆発エフェクト
	m_eff = GetPodEffec(&m_ani, &m_ani_time, m_del, 10);	//敵とプレイヤーのポッド当たっているとき処理
	
	//ポッド消滅処理
	if (m_del == true)
	{
		if(m_bom != 5)	//５以外の場合
			m_bom = Rand(0, 4);//ランダムな爆発を起こす
		if (m_ani == 4 && m_bom == 5)
		{
			this->SetStatus(false);
			Hits::DeleteHitBox(this);
		}
		if (m_ani == 4)
		{
			m_ani = 0;
			m_bom = 5;
		}
		
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
	if (hit->CheckElementHit(ELEMENT_POD) == true)
	{
		if (ButtonU == 1)//敵の種類１(パワー)がプレイヤーのポッドと当たった場合
		{
			if (hit->CheckObjNameHit(OBJ_PODD) != nullptr)	//プレイヤーのディフェンスポッド当たり時のHP
			{
				m_podhp -= 8;
			}
			else if (hit->CheckObjNameHit(OBJ_PODS) != nullptr)	//プレイヤーのスピードポッド当たり時のHP
			{
				m_podhp -= 12;
			}
			else											//プレイヤーのパワーポッド、バランスポッド、ミサイル当たり時のHP
			{
				m_podhp -= 10;
			}
		}
		else if (ButtonU == 2)//敵の種類２(スピード)がプレイヤーのポッドと当たった場合
		{
			if (hit->CheckObjNameHit(OBJ_PODP) != nullptr)	//プレイヤーのパワーポッド当たり時のHP
			{
				m_podhp -= 8;
			}
			else if (hit->CheckObjNameHit(OBJ_PODD) != nullptr)	//プレイヤーのディフェンスポッド当たり時のHP
			{
				m_podhp -= 12;
			}
			else											//プレイヤーのスピードポッド、バランスポッド、ミサイル当たり時のHP
			{
				m_podhp -= 10;
			}
		}
		else if (ButtonU == 3)//敵の種類３(ディフェンス)がプレイヤーのポッドと当たった場合
		{
			if (hit->CheckObjNameHit(OBJ_PODP) != nullptr)	//プレイヤーのパワーポッド当たり時のHP
			{
				m_podhp -= 12;
			}
			else if (hit->CheckObjNameHit(OBJ_PODS) != nullptr)	//プレイヤーのスピードポッド当たり時のHP
			{
				m_podhp -= 8;
			}
			else											//プレイヤーのディフェンスポッド、バランスポッド、ミサイルに当たり時のHP
			{
				m_podhp -= 10;
			}
		}
		else if (ButtonU == 4)//敵の種類４(バランス)がプレイヤーのポッドとミサイルに当たった場合
		{
			m_podhp -= 10;
		}
		else if (ButtonU == 5)//敵の種類５(ミサイル)がプレイヤーのポッドに当たった場合
		{
			;
		}
	}

	//プレイヤーのポッドが敵のポッドとぶつかった時の判定
	if (hit->CheckElementHit(ELEMENT_ENEMYPOD) == true)
	{
		if (ButtonU == 1)//自分の種類１(パワー)が敵のポッドと当たった場合
		{
			if (hit->CheckObjNameHit(OBJ_PODD) != nullptr)	//敵のディフェンスポッド当たり時のHP
			{
				m_podhp -= 8;
			}
			else if (hit->CheckObjNameHit(OBJ_PODS) != nullptr)	//敵のスピードポッド当たり時のHP
			{
				m_podhp -= 12;
			}
			else											//敵のパワーポッド、バランスポッド、ミサイル当たり時のHP
			{
				m_podhp -= 10;
			}
		}
		else if (ButtonU == 2)//自分の種類２(スピード)が敵のポッドと当たった場合
		{
			if (hit->CheckObjNameHit(OBJ_PODP) != nullptr)	//敵のパワーポッド当たり時のHP
			{
				m_podhp -= 8;
			}
			else if (hit->CheckObjNameHit(OBJ_PODD) != nullptr)	//敵のディフェンスポッド当たり時のHP
			{
				m_podhp -= 12;
			}
			else											//敵のスピードポッド、バランスポッド、ミサイル当たり時のHP
			{
				m_podhp -= 10;
			}
		}
		else if (ButtonU == 3)//自分の種類３(ディフェンス)が敵のポッドと当たった場合
		{
			if (hit->CheckObjNameHit(OBJ_PODP) != nullptr)	//敵のパワーポッド当たり時のHP
			{
				m_podhp -= 12;
			}
			else if (hit->CheckObjNameHit(OBJ_PODS) != nullptr)	//敵のスピードポッド当たり時のHP
			{
				m_podhp -= 8;
			}
			else											//敵のディフェンスポッド、バランスポッド、ミサイル当たり時のHP
			{
				m_podhp -= 10;
			}

		}
		else if (ButtonU == 4)//自分の種類４(バランス)が敵のポッドとミサイルに当たった場合
		{
			m_podhp -= 10;
		}
		else if (ButtonU == 5)//自分の種類５(ミサイル)が敵のポッドとミサイルに当たった場合
		{
			;
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
	if (m_bom == 3)
	{
		dst.m_top = 29.0f + m_y;
		dst.m_left = 0.0f + m_x;
		dst.m_right = 32.0f + m_x;
		dst.m_bottom = 58.0f + m_y;
	}

	//右斜め下
	if (m_bom == 4)
	{
		dst.m_top = 29.0f + m_y;
		dst.m_left = 32.0f + m_x;
		dst.m_right = 64.0f + m_x;
		dst.m_bottom = 58.0f + m_y;
	}
	//大きいやつ
	if (m_bom == 5)
	{
		dst.m_top = 0.0f + m_y;
		dst.m_left = 0.0f + m_x;
		dst.m_right = 50.0f + m_x;
		dst.m_bottom = 50.0f + m_y;
	}

	
	if (m_del == true) 
		Draw::Draw(16, &m_eff, &dst, c, 180.0f);
	



}