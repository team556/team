//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"


#include "GameHead.h"
#include "UtilityModule.h"
#include "ObjMissile.h"

#include <time.h>

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjMissile::CObjMissile(float x, float y, bool type)
{
	m_x = x;
	m_y = y;
	m_type = type;
}

//イニシャライズ
void CObjMissile::Init()
{
	if (m_type == true) {
		CObjFight* obj = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
		CObjPlanet * obj2 = (CObjPlanet*)Objs::GetObj(OBJ_PLANET);

		if (obj != nullptr) {					//情報が取得出来ていたら
			m_get_line = obj->GetLine();		//ラインナンバーを取得
			if (m_get_line == 1) { m_y = 310; }	//取得ナンバーで高さ変更
			else if (m_get_line == 2) { m_y = 420; }

			m_get_cnt = obj->GetCount();		//カウントを取得
			//m_psize = obj2->GetSiz();			//サイズを取得
			//m_x +=obj2->GetX() - m_psize;
			m_x += obj->GetCount() / 10;
			m_mov_spd = 1.0f / obj->GetCount();
		}
	}
	else {
		CObjFight* obj = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
		CObjPlanet * obj2 = (CObjPlanet*)Objs::GetObj(OBJ_PLANET);

		srand(time(NULL));
		m_get_line = rand() % 3 + 1;
		if (m_get_line == 1) { m_y = 310; }	//取得ナンバーで高さ変更
		else if (m_get_line == 2) { m_y = 420; }

		m_get_cnt = obj->GetCount();		//カウントを取得
		m_x -= obj->GetCount() / 10;
		m_mov_spd = 1.0f / obj->GetCount();
	}

	m_size = 50.0f;//サイズ
	
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
		Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_RED, OBJ_MISSILE, 1);
		m_x -= 100;
	}
	else {
		Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_MAGIC, OBJ_MISSILE, 1);
		m_x += 100;
	}

}

//アクション
void CObjMissile::Action()
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


	CHitBox* hit = Hits::GetHitBox(this);		//HitBox情報取得
	hit->SetPos(m_x, m_y, m_size, m_size);		//HitBox更新

	if (m_type == true) {
		if (hit->CheckElementHit(ELEMENT_ENEMY) == true)
		{//位置を更新//惑星と接触しているかどうかを調べる
			this->SetStatus(false);		//当たった場合削除
			Hits::DeleteHitBox(this);
		}
	}
	else {
		if (hit->CheckElementHit(ELEMENT_PLAYER) == true)
		{//位置を更新//惑星と接触しているかどうかを調べる
			this->SetStatus(false);		//当たった場合削除
			Hits::DeleteHitBox(this);
		}
	}
}

//ドロー
void CObjMissile::Draw()
{
	//描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	float d[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	RECT_F src;//切り取り位置
	RECT_F dst;//表示位置
	
	src.m_top   =  0.0f;
	src.m_left  =  0.0f;
	src.m_right =100.0f;
	src.m_bottom=100.0f;
	
	dst.m_top   = m_y;
	dst.m_left  = m_x;
	dst.m_right = m_x + m_size;
	dst.m_bottom= m_y + m_size;
	
	if (m_type == true) {
		m_r += 0.05 + m_mov_spd * 2;
		Draw::Draw(2, &src, &dst, d, m_r - 15);
	}
	else {
		m_r -= 0.05 - m_mov_spd * 2;
		Draw::Draw(2, &src, &dst, d, m_r + 15);
	}
	
}