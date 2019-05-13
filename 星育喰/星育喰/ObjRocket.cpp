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
	if (m_type == true) {
		CObjFight* obj = (CObjFight*)Objs::GetObj(OBJ_FIGHT);

		if (obj != nullptr) {					//情報が取得出来ていたら
			m_get_line = obj->GetLine();		//ラインナンバーを取得
			if (m_get_line == 1) { m_y = 310; }	//取得ナンバーで高さ変更
			else if (m_get_line == 2) { m_y = 420; }

			m_get_cnt = obj->GetCount();		//カウントを取得
			m_x += obj->GetCount() / 10;
			m_mov_spd = 1.0f / obj->GetCount();
		}
	}
	else {
		CObjFight* obj = (CObjFight*)Objs::GetObj(OBJ_FIGHT);

		srand(time(NULL));
		m_get_line = rand() % 3 + 1;
		if (m_get_line == 1) { m_y = 310; }	//取得ナンバーで高さ変更
		else if (m_get_line == 2) { m_y = 420; }

		m_get_cnt = obj->GetCount();		//カウントを取得
		m_mov_spd = 1.0f / obj->GetCount();

		srand(time(NULL));
		//敵のポッドの番号をランダムにする処理
		Enemypod = rand() % 5 + 1;	
	}

	m_size = 50.0f;//サイズ
	
	m_time = 100;

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
	if (m_type == false) {
		Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_E_MIS, OBJ_Rocket, 1);
		m_x -= 100;
	}
	else {
		Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_P_MIS, OBJ_Rocket, 1);
		m_x += 100;
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

}

//アクション
void CObjRocket::Action()
{
	m_vx = 0.0f;//ベクトル初期化
	m_vy = 0.0f;

	m_mov += m_mov_spd / 2;

	//マウスの位置を取得
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//マウスのボタンの状態
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	if (m_mou_l == false && m_mou_f == false)
	{
		m_mou_f = true;
	}
	else
	{
		m_mou_f = false;
	}

	//爆発エフェクト
	//m_eff = GetPodEffec(&m_ani, &m_ani_time, m_del, 10);

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
		m_x += m_vx - m_mov_spd * 200;
		m_y += m_vy;
	}
	else {
		m_x -= m_vx - m_mov_spd * 200;
		m_y += m_vy;
	}

	CHitBox* hit = Hits::GetHitBox(this);		//HitBox情報取得
	hit->SetPos(m_x, m_y, m_size, m_size);		//HitBox更新

	//敵とプレイヤーのポッド当たっているとき処理
	m_eff = GetPodEffec(&m_ani, &m_ani_time, m_del, 10);

	//ポッド消滅処理
	if (m_del == true)
	{
		if(m_bom != 5)	//５以外の場合
			m_bom = Rand(0, 4);//ランダムな爆発を起こす
		//m_ani_max == true;
		if (m_ani == 4 && m_bom == 5)
		{
			this->SetStatus(false);
			Hits::DeleteHitBox(this);
		}
		if (m_ani == 4)
		{
			m_ani = 0;
			m_bom = 5;
			//this->SetStatus(false);
			//Hits::DeleteHitBox(this);
		}
		
		return;
	}

	//if (m_ani_max == 0)
	//{
	//	this->SetStatus(false);
	//	Hits::DeleteHitBox(this);
	//}

	if ((hit->CheckElementHit(ELEMENT_ENEMY) == true || 
		hit->CheckElementHit(ELEMENT_E_MIS) == true) && m_type == true)//敵の惑星かミサイルに当たった時かつ自弾
	{
		//位置を更新//惑星と接触しているかどうかを調べる
		m_del = true;
		hit->SetInvincibility(true);
	}

	if ((hit->CheckElementHit(ELEMENT_PLAYER) == true ||
		hit->CheckElementHit(ELEMENT_P_MIS) == true) && m_type == false)//プレイヤーの惑星かミサイルに当たった時かつ敵弾
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

	if (ButtonU >= 1 && ButtonU <= 4)
	{
		//ポッドの描画情報
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 100.0f;
		src.m_bottom = 70.0f;

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

	if (m_type == true) { //-----------ボタン赤・青・緑を分ける判定
		m_r += 0.05 + m_mov_spd * 2;

		switch (ButtonU) {
		case 1:
			Draw::Draw(10, &src, &dst, r, m_r + 180);  //赤ポッド
			break;
		case 2:
			Draw::Draw(10, &src, &dst, b, m_r + 180);  //青ポッド
			break;
		case 3:
			Draw::Draw(10, &src, &dst, g, m_r + 180);   //緑ポッド
			break;
		case 4:
			Draw::Draw(10, &src, &dst, d, m_r + 180);   //灰色ポッド
			break;
		case 5:
			Draw::Draw(17, &src, &dst, d, m_r + 35);   //ミサイル
			break;

		}
		//Draw::Draw(10, &src, &dst, d, m_r - 15);
	}


	//敵ポッドの1～4の番号(ポッド)の描画情報
	if (Enemypod >= 1 && Enemypod <= 4)
	{
		//ポッドの描画情報
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 100.0f;
		src.m_bottom = 70.0f;

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

		switch (Enemypod) {
		case 1://---------ランダムの情報が1なら
			Draw::Draw(10, &src, &dst, r, m_r);  //赤ポッド
			break;
		case 2://---------ランダムの情報が2なら
			Draw::Draw(10, &src, &dst, b, m_r);  //青ポッド
			break;
		case 3://---------ランダムの情報が3なら
			Draw::Draw(10, &src, &dst, g, m_r);   //緑ポッド
			break;
		case 4://---------ランダムの情報が4なら
			Draw::Draw(10, &src, &dst, d, m_r);   //灰色ポッド
			break;
		case 5://---------ランダムの情報が5なら
			Draw::Draw(17, &src, &dst, d, m_r-145);   //ミサイル
			break;
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