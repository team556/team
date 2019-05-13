//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjPlanet.h"

#include <time.h>

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjPlanet::CObjPlanet(float x, float y, float hp, int type, float siz)
{
	//作成時に渡された値を、各ステータスに代入
	m_px = x;
	m_py = y;
	m_hp = hp;
	m_type = type;
	m_get_siz = siz;
}

//イニシャライズ
void CObjPlanet::Init()
{
	//各ステータス初期化
	m_size	 = 50.0f;//サイズ
	m_siz_max= 50.0f;
	m_siz_vec=  0.0f;

	m_cnt = 0;		//カウント

	m_get_hp = 0;	//取得HP

	m_time = 0; //タイムカウント初期化
	m_attackf = 0;

	i = 0;

	srand(time(NULL));
	j = rand() % 5;//初期行動パターンをランダムで決める(この処理ないと初期行動パターンが必ず0のものになる)

	CObjFight* fit = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
	m_mov_spd = 0.093f* 30 / (fit->GetCount() / 70);//動く速度
	///*m_siz_spd*/ = 0.07f * 30 / (fit->GetCount() / 40);//拡大速度

	if (m_type == 0)
		m_px += (fit->GetCount() / 30);
	else
		m_px -= (fit->GetCount() / 30);

	m_ani[0] = 0;//アニメーションデータの初期化
	m_ani[1] = 1;
	m_ani[2] = 2;
	m_ani[3] = 1;
	m_ani_frame = 0;
	m_ani_time = 0;
	m_cntf = 0;
	m_eat_f = false;	//喰うフラグ(true = 喰う)
	m_eat_spd = fit->GetCount();
	m_del_f = false;	//消すフラグ(true = 消す)
	
	//当たり判定用HitBoxを作成
	if(m_type == 0)
		Hits::SetHitBox(this, m_px, m_py, m_size, m_size, ELEMENT_PLAYER, OBJ_PLANET, 1);
	else
		Hits::SetHitBox(this, m_px, m_py, m_size, m_size, ELEMENT_ENEMY, OBJ_PLANET, 1);
}

//アクション
void CObjPlanet::Action()
{
	//▼戦闘開始前は戦闘処理(敵惑星の行動等)を実行しないようにする
	if (battle_start == false)
	{
		return;
	}

	CObjFight* fit = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
	if (fit->GetCount() != 0)		//対戦時間が0でない場合
		/*m_siz_vec += m_siz_spd*/; //拡大非をベクトルに加算


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
		if (m_ani_frame == 4) {			//最終初期フレームにする前
			m_eat_f = false;	//食べるフラグ★OFF
			m_ani_time = -1;							//ループ制御☆
			if (m_type == 0) {
				CObjFightClear* crer = new CObjFightClear();	//主人公の場合
				Objs::InsertObj(crer, OBJ_FIGHT_CLEAR, 15);	//クリア画面
			}
			else {
				CObjFightOver* over = new CObjFightOver();	//敵の場合
				Objs::InsertObj(over, OBJ_FIGHT_CLEAR, 15);	//ゲームオーバー画面
			}
		}
	}
				//2.5秒
	if (m_cnt < (2.5 * 60) * m_mov_spd)	//カウントし終わってない場合
		if (m_type == 0)				//(戦闘中)
			m_px -= m_mov_spd;	//自星の動き
		else
			m_px += m_mov_spd;	//敵星の動き
	else { 						//カウントし終わった後 (停止後)
		if (m_ani_time == 0) {					//timeでループ制御☆
			if (m_type == 0) {
				CObjPlanet* ene2 = (CObjPlanet*)Objs::GetObj(OBJ_ENEMY2);
				if(ene2 != nullptr)
					m_get_hp = ene2->GetHp();
			}
			else {
				CObjPlanet* pla = (CObjPlanet*)Objs::GetObj(OBJ_PLANET);
				if (pla != nullptr)
					m_get_hp = pla->GetHp();
			}
			if (m_type == 0) {
				if (m_hp >= m_get_hp) {
					m_eat_f = true;		//喰うフラグ有効
					fit->SetEndF(1);
				}
			}
			else {
				if (m_hp > m_get_hp) {
					m_eat_f = true;		//喰うフラグ有効
					fit->SetEndF(-1);
				}
			}
		}
	}

	if (m_eat_f == true) {	//食べるフラグ★処理
		m_ani_time++;		//ani_time 加算
		if ((m_ani_frame == 3) && (m_ani_time == 1)) {//口閉じた瞬間
			m_size = m_size*1.5f;					//サイズ変更(1.5倍)
			if (m_type == 0) {
				CObjPlanet* ene = (CObjPlanet*)Objs::GetObj(OBJ_ENEMY);
				ene->SetDelF();
			}
			else {
				CObjPlanet* pla = (CObjPlanet*)Objs::GetObj(OBJ_PLANET);
				pla->SetDelF();
			}	
		}
	}
	else
		m_ani_frame = 0;	//初期フレーム

	if (m_ani_frame == 2)		//喰うフレームの移動
	{
		if (m_type == 0)
		{
			CObjPlanet* ene = (CObjPlanet*)Objs::GetObj(OBJ_ENEMY);
			if (m_px > ene->GetX())		//敵のX座標より自惑星が大きくなると移動を止める
				m_px -= 4.0f;
		}
		else
		{
			CObjPlanet* pla = (CObjPlanet*)Objs::GetObj(OBJ_PLANET);
			if (m_px < pla->GetX())		//自分のX座標より敵惑星が小さくなると移動を止める
				m_px += 4.0f;
		}
	}

	//-------------------------------------------------------------

	
	hit->SetPos(m_px - m_siz_vec - m_size * 2,	//HitBox更新
				m_py - m_siz_vec - m_size * 2,		
				2 * m_siz_vec + m_size * 4,
				2 * m_siz_vec + m_size * 4);

	//▼ダメージ処理
	if ((hit->CheckElementHit(ELEMENT_E_MIS) == true) && (m_type == 0) && (m_hp > 0))
	{							//ミサイルに当たった場合
		m_hp -= 1;				//HP-1
		m_size -= m_size / 20;	//サイズ減少
	}
	else if ((hit->CheckElementHit(ELEMENT_P_MIS) == true) && (m_type != 0) && (m_hp > 0))
	{
		m_hp -= 1;				//HP-1
		m_size -= m_size / 20;	//サイズ減少
	}

	if (m_del_f == true) {				//消すフラグ判定＆処理
		this->SetStatus(false);	 //オブジェクト削除
		Hits::DeleteHitBox(this);//HitBox削除
	}

	//▼敵惑星攻撃パターン
	if (m_type == 1 && battle_end == false)//惑星が敵の時のみ弾を発射し、戦闘終了時に弾を打たないようにする。
	{
		//▼ミサイルポッド作成X位置を設定
		CObjFight* obj = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
		m_create_x = -(obj->GetCount() / 10 + 100);

		if (m_time <= 0)
		{
			int Enemy_Fight_type[5][6] =
			{
				//1=赤,2=青,3=緑,4=灰色,5=ミサイル
				{ 1,1,2,1,1,0 },
				{ 2,2,3,2,2,0 },
				{ 3,3,4,3,3,0 },
				{ 4,4,5,4,4,0 },
				{ 5,5,1,5,5,0 },
				//{ 2,2,3,4,5,0 },
				//{ 5,1,1,1,3,0 },
				//{ 4,2,2,2,1,0 },
				//{ 2,3,3,1,2,0 },
			};

			m_attackf = Enemy_Fight_type[j][i];

			if (m_attackf == 0)
			{
				i = 0;//配列一番左の状態に戻す
					
				srand(time(NULL));
				j = rand() % 5;//行動パターンを決める

				m_attackf = Enemy_Fight_type[j][i];
				i++;
			}
			else // (i < 5)
			{
				i++;
			}
		}


		
		if (m_attackf == 1 && m_time <= 0)
		{
			CObjRocket* M = new CObjRocket(575 + m_create_x, 200, false,1);//オブジェクト作成
			Objs::InsertObj(M, OBJ_Rocket, 20);		//オブジェクト登録
			m_time = 100;
		}
		else if (m_attackf == 2 && m_time <= 0)
		{
			CObjRocket* M = new CObjRocket(575 + m_create_x, 200, false,2);//オブジェクト作成
			Objs::InsertObj(M, OBJ_Rocket, 20);		//オブジェクト登録
			m_time = 100;
		}
		else if (m_attackf == 3 && m_time <= 0)
		{
			CObjRocket* M = new CObjRocket(575 + m_create_x, 200, false,3);//オブジェクト作成
			Objs::InsertObj(M, OBJ_Rocket, 20);		//オブジェクト登録
			m_time = 100;
		}
		else if (m_attackf == 4 && m_time <= 0)
		{
			CObjRocket* M = new CObjRocket(575 + m_create_x, 200, false,4);//オブジェクト作成
			Objs::InsertObj(M, OBJ_Rocket, 20);		//オブジェクト登録
			m_time = 100;
		}
		else if (m_attackf == 5 && m_time <= 0)
		{
			CObjRocket* M = new CObjRocket(575 + m_create_x, 200, false, 5);//オブジェクト作成
			Objs::InsertObj(M, OBJ_Rocket, 20);		//オブジェクト登録
			m_time = 100;
		}

		m_time--;
	}

	CObjFight* obj = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
	m_cntf = obj->GetCount();	//CObjFightのカウント数を持ってくる

	if (m_cntf <= 0)			//カウント数が0以下になったら
	{
		if (m_cnt < m_mov_spd)	//惑星同士が重なっていないとき
		{
			if (m_type == 0)
				m_px -= 1.0f;
				
			else
				m_px += 1.0f;
		}
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
	src.m_left  = m_ani[m_ani_frame] * 64.0f;
	src.m_right = m_ani[m_ani_frame] * 64.0f + 64.0f;
	src.m_bottom= 64.0f;
	//表示位置
	if(m_get_siz == 0){
		//dst.m_top   = m_py - m_siz_vec - m_size;//300
		//dst.m_left  = m_px - m_siz_vec - m_size;//800
		//dst.m_right = m_px + m_siz_vec + m_size;
		//dst.m_bottom= m_py + m_siz_vec + m_size;

		dst.m_top = m_py - m_size * 2;//300
		dst.m_left = m_px -m_size * 2;//800
		dst.m_right = m_px +m_size * 2;
		dst.m_bottom = m_py +m_size * 2;
	}
	else {
		dst.m_top   = m_py;//300
		dst.m_left  = m_px;//800
		dst.m_right = m_px + (m_get_siz * 2);
		dst.m_bottom= m_py + (m_get_siz * 2);
	}

	//0番目に登録したグラフィックをsrc,dst,c情報をもとに描画
	Draw::Draw(3, &src, &dst, c, 0.0f);
}
