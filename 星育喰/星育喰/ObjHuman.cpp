//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameHead.h"
#include "ObjHuman.h"
#include "UtilityModule.h"


//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjHuman::CObjHuman(float x, float y)
{
	//作成時に渡された値を、座標の初期値に代入
	m_hx = x;
	m_hy = y;
}

//イニシャライズ
void CObjHuman::Init()
{
	m_pos = 0;
	m_move = false;
	m_cnt = 0;
}

//アクション
void CObjHuman::Action()
{
	m_cnt++;

	if (m_cnt == 60) {
		m_pos = Rand(0, 3);
		m_move = true;
	}
	else if (m_cnt == 120) {
		m_cnt = 0;
		m_move = false;
	}

	if (m_move == true) {//動いてる時
		switch (m_pos) {
		case 0:m_hx -= 1.0f; break;
		case 1:m_hy -= 1.0f; break;
		case 2:m_hy += 1.0f; break;
		case 3:m_hx += 1.0f; break;
		}
		m_ani_time += 1;//アニメーションを進める
	}
	else{
		m_ani_frame = 1;	//キー入力がない場合は静止フレームにする
		m_ani_time = 0;		//アニメーションを止める
	}

	if (m_ani_time > 6) {	//アニメーション動作間隔
		m_ani_frame += 1;
		m_ani_time = 0;
	}

	if (m_ani_frame == 4)
		m_ani_frame = 0;	//フレーム4で0に戻す
}

//ドロー
void CObjHuman::Draw()
{
	int AniData[4] = { 0,1,2,1, };

	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	RECT_F src;
	RECT_F dst;

	src.m_top   =  0.0f;
	src.m_left  =  0.0f;
	src.m_right =100.0f;
	src.m_bottom=100.0f;

	dst.m_top   = m_hy +  0.0f;
	dst.m_left  = m_hx +  0.0f;
	dst.m_right = m_hx + 50.0f;
	dst.m_bottom= m_hy + 50.0f;

	//0番目に登録したグラフィックをsrc,dst,c情報をもとに描画
	Draw::Draw(0, &src, &dst, c, 0.0f);
}