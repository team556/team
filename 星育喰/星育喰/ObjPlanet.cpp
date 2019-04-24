//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjPlanet.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjPlanet::CObjPlanet(float x, float y, bool type)
{
	//作成時に渡された値を、座標の初期値に代入
	m_px = x;
	m_py = y;
	m_type = type;
}

//イニシャライズ
void CObjPlanet::Init()
{
	m_size	 = 50.0f;
	m_siz_max= 50.0f;
	m_siz_vec=  0.0f;

	m_cnt = 0;

	m_hp = 10;

	CObjFight* obj = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
	m_mov_spd = 0.093f* 30 / (obj->GetCount() / 60);
	m_siz_spd = 0.07f * 30 / (obj->GetCount() / 60);

	m_ani[0] = 3;
	m_ani[1] = 4;
	m_ani[2] = 5;
	m_ani[3] = 4;
	m_ani_frame = 0;
	m_ani_time = 0;

	m_eat_f = false;
	
	//当たり判定用HitBoxを作成
	if(m_type == true)
		Hits::SetHitBox(this, m_px, m_py, m_size, m_size, ELEMENT_PLAYER, OBJ_PLANET, 1);
	else
		Hits::SetHitBox(this, m_px, m_py, m_size, m_size, ELEMENT_ENEMY, OBJ_PLANET, 1);
}

//アクション
void CObjPlanet::Action()
{
	CObjFight* obj = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
	if (obj->GetCount() != 0)	//対戦時間が0でない場合
		m_siz_vec += m_siz_spd; //拡大非をベクトルに加算


	CHitBox* hit = Hits::GetHitBox(this);	//CHitBoxポインタ取得
	if (((hit->CheckElementHit(ELEMENT_ENEMY) == true)
		|| (hit->CheckElementHit(ELEMENT_PLAYER) == true))	//お互い当たっているかつ
		&& (m_cnt < (2.5 * 60) * m_mov_spd)) {		//2.5秒カウントしてない場合
		m_cnt++;
	}


	//-------------------------------------------------アニメーション、星の動き
	if (m_ani_time == 60) {	//フレーム切り替え時間
		m_ani_time = 0;		//タイムリセット
		m_ani_frame++;		//フレーム切り替え
		if (m_ani_frame == 4) {	//最終初期フレームにする前
			m_eat_f = false;	//食べるフラグ★OFF
			m_ani_time = -1;							//ループ制御☆
			//オブジェクト作成
			CObjFightClear* obj = new CObjFightClear();	//オブジェクト作成
			Objs::InsertObj(obj, OBJ_FIGHT_CLEAR, 10);	//オブジェクト登録
		}
	}
				//2.5秒
	if (m_cnt < (2.5 * 60) * m_mov_spd)//カウントし終わってない場合
		if (m_type == true)
			m_px -= m_mov_spd;	//それぞれ移動させる
		else
			m_px += m_mov_spd;
	else { 						//カウントし終わった後 (停止後)
		if((m_type == true) && (m_ani_time == 0))	//timeでループ制御☆
			m_eat_f = true;	//食べるフラグ★ON
	}

	if (m_eat_f == true) {	//食べるフラグ★処理
		m_ani_time++;		//ani_time 加算
		if((m_ani_frame == 3)&&(m_ani_time == 1))//口閉じた瞬間
			m_size += m_size;					//サイズ変更
	}
	else
		m_ani_frame = 0;	//初期フレーム

	if (m_ani_frame == 2)		//喰うフレームの移動
		m_px -= m_mov_spd * 20;	//スピード×20加算
		
	//-------------------------------------------------------------

	
	hit->SetPos(m_px - m_siz_vec - m_size,	//HitBox更新
				m_py - m_siz_vec - m_size,		
				2 * m_siz_vec + m_size * 2,
				2 * m_siz_vec + m_size * 2);

	if ((hit->CheckElementHit(ELEMENT_MAGIC) == true) && (m_type == false) && (m_hp > 0))
	{							//敵のミサイルに当たった場合
		m_hp -= 1;				//HP-1
		m_size -= m_size / 10;	//サイズ減少
	}
	
}

//ドロー
void CObjPlanet::Draw()
{
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	RECT_F src;
	RECT_F dst;
	//切り取り位置
	src.m_top   =  0.0f;
	src.m_left  =  0.0f;
	src.m_right = 62.0f;
	src.m_bottom= 62.0f;
	//表示位置
	dst.m_top   = m_py - m_siz_vec - m_size;//300
	dst.m_left  = m_px - m_siz_vec - m_size;//800
	dst.m_right = m_px + m_siz_vec + m_size;
	dst.m_bottom= m_py + m_siz_vec + m_size;

	//0番目に登録したグラフィックをsrc,dst,c情報をもとに描画
	Draw::Draw(m_ani[m_ani_frame], &src, &dst, c, 0.0f);
}
