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
CObjMissile::CObjMissile(float x, float y, bool type,int n)
{
	m_x = x;
	m_y = y;
	m_type = type;
	ButtonU = n;
}

//イニシャライズ
void CObjMissile::Init()
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
		Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_E_MIS, OBJ_MISSILE, 1);
		m_x -= 100;
	}
	else {
		Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_P_MIS, OBJ_MISSILE, 1);
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

	if ((hit->CheckElementHit(ELEMENT_ENEMY) == true || 
		hit->CheckElementHit(ELEMENT_E_MIS) == true) && m_type == true)//敵の惑星かミサイルに当たった時かつ自弾
	{
		//位置を更新//惑星と接触しているかどうかを調べる
		this->SetStatus(false);		//当たった場合削除
		Hits::DeleteHitBox(this);
	}

	if ((hit->CheckElementHit(ELEMENT_PLAYER) == true ||
		hit->CheckElementHit(ELEMENT_P_MIS) == true) && m_type == false)//プレイヤーの惑星かミサイルに当たった時かつ敵弾
	{
		this->SetStatus(false);		//当たった場合削除
		Hits::DeleteHitBox(this);
	}
}

//ドロー
void CObjMissile::Draw()
{
	//描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	float d[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; //元の色
	float r[4] = { 1.0f, 0.0f, 0.0f, 1.0f }; //赤
	float g[4] = { 0.0f, 1.0f, 0.0f, 1.0f }; //緑
	float b[4] = { 0.0f, 0.2f, 2.0f, 1.0f }; //青


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
	if (m_type == false) { //-----------ボタン赤・青・緑を分ける判定
		m_r += 0.05 + m_mov_spd * 2;

		switch (Enemypod) {
		case 1:
			Draw::Draw(10, &src, &dst, r, m_r);  //赤ポッド
			break;
		case 2:
			Draw::Draw(10, &src, &dst, b, m_r);  //青ポッド
			break;
		case 3:
			Draw::Draw(10, &src, &dst, g, m_r);   //緑ポッド
			break;
		case 4:
			Draw::Draw(10, &src, &dst, d, m_r);   //灰色ポッド
			break;
		case 5:
			Draw::Draw(17, &src, &dst, d, m_r-145);   //ミサイル
			break;
		}
	}
}