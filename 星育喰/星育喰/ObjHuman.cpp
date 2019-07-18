////使用するヘッダーファイル
//#include "GameL\DrawTexture.h"
//#include "GameHead.h"
//#include "GameL\HitBoxManager.h"
//#include "ObjHuman.h"
//#include "UtilityModule.h"
//
//
////使用するネームスペース
//using namespace GameL;
//
////コンストラクタ
//CObjHuman::CObjHuman(float x, float y, int n)
//{
//	//作成時に渡された値を、座標の初期値に代入
//	m_hx = x;
//	m_hy = y;
//	m_nam = n;
//}
//
////イニシャライズ
//void CObjHuman::Init()
//{
//	m_size = 70.0f;
//	m_pos = 0;			//向き( 0← 1↑ 2→ 3↓ )
//	m_move = false;		//動きオフ
//	m_mov_spd = 4.0f;	//動く速さ
//	m_cnt = 0;			//カウント
//	m_turn = false;		//画面外処理
//	m_turn_count = 60;	//施設HIT時ターンカウント(1秒)
//
//	//当たり判定用HitBoxを作成
//	Hits::SetHitBox(this, m_hx, m_hy, m_size, m_size, ELEMENT_PLAYER, OBJ_HUMAN, 1);
//}
//
////アクション
//void CObjHuman::Action()
//{
//	m_cnt++;
//
//	if (m_cnt == 60 + (90 * m_nam)) {
//		m_pos = Rand(0, 3);	//向きをランダムに決める
//		m_move = true;		//動き状態
//	}
//	else if (m_cnt == 120 + 70 * m_nam) {
//		m_cnt = 0;
//		m_move = false;		//静止状態
//	}
//
//	bool check = CheckWindow(m_hx, m_hy, 0.0f, 0.0f, 1200.0f - m_size, 700.0f - m_size);
//	if (check == false)//画面外の場合
//	{
//		if (m_turn == false) {
//			CObjHuman::Turn(&m_pos);//向き反転関数
//			m_turn = true;
//		}
//	}
//	else {
//		m_turn = false;
//	}
//
//	if (m_move == true) {//動いてる時
//		switch (m_pos) {
//		case 0:m_hx -= m_mov_spd; break;//←
//		case 1:m_hy -= m_mov_spd; break;//↑
//		case 2:m_hx += m_mov_spd; break;//→
//		case 3:m_hy += m_mov_spd; break;//↓
//		default:break;
//		}
//		m_ani_time += 1;//アニメーションを進める
//	}
//	else{
//		m_ani_frame = 0;	//キー入力がない場合は静止フレームにする
//		m_ani_time = 0;		//アニメーションを止める
//	}
//
//	
//
//	if (m_ani_time > 6) {	//アニメーション動作間隔
//		m_ani_frame += 1;
//		m_ani_time = 0;
//	}
//
//	if (m_ani_frame == 4)	//フレーム4で0に戻す
//		m_ani_frame = 0;	//0～3をループ
//
//	CHitBox* hit = Hits::GetHitBox(this);	//CHitBoxポインタ取得
//	hit->SetPos(m_hx, m_hy);				//位置を更新
//
//	//ターンカウントが0以上の時、
//	//ターンカウントを徐々に0に近づける。
//	if (m_turn_count >= 0)
//	{
//		m_turn_count--;
//	}
//
//	//施設に当たったら向き反転させる
//	if (hit->CheckElementHit(ELEMENT_ENEMY) == true)
//	{
//		//ターンカウントが0の時のみ反転させる
//		if (m_turn_count <= 0) 
//		{
//			CObjHuman::Turn(&m_pos);//向き反転関数
//			m_turn_count= 60;//ターンカウントを60に戻す(1秒)
//		}
//	}
//}
//
////ドロー
//void CObjHuman::Draw()
//{
//	//▼シーン切り替え演出後に非表示にする処理
//	if (scene_change_start == true)
//	{
//		return;
//	}
//
//	int AniData[4] = { 1,0,1,2, };
//	int PosData[4] = { 0,2,0,1, };
//
//	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
//	RECT_F src;//切り取り位置
//	RECT_F dst;//表示位置
//	
//	src.m_top   =  0.0f + (PosData[m_pos] * 70.0f);
//	src.m_left  =  0.0f + (AniData[m_ani_frame] * 64.0f);
//	src.m_right = 64.0f + (AniData[m_ani_frame] * 64.0f);
//	src.m_bottom= 70.0f + (PosData[m_pos] * 70.0f);
//	
//	dst.m_top   = m_hy;
//	dst.m_left  = m_hx;
//	dst.m_right = m_hx + m_size;
//	dst.m_bottom= m_hy + m_size;
//
//	if (m_pos == 2){
//		dst.m_left  = m_hx + m_size;
//		dst.m_right = m_hx;
//	}
//
//	//10番目に登録したグラフィックをsrc,dst,c情報をもとに描画
//	Draw::Draw(10, &src, &dst, c, 0.0f);
//}
//
//void CObjHuman::Turn(int* pos)
//{//向きを反転させる
//	if (*pos == 0 || *pos == 1) { *pos += 2; }
//	else{ *pos -= 2; }
//	switch (*pos) {//反転方向に進む
//	case 0:m_hx -= m_mov_spd; break;//←
//	case 1:m_hy -= m_mov_spd; break;//↑
//	case 2:m_hx += m_mov_spd; break;//→
//	case 3:m_hy += m_mov_spd; break;//↓
//	}
//}