//使用するヘッダーファイル
//#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
//#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjSpecialButton::CObjSpecialButton(float x, float y, float h, float w)
{
	//作成時に渡された値を、座標の初期値に代入
	m_x = x;
	m_y = y;
	m_h = h;
	m_w = w;
}

//イニシャライズ
void CObjSpecialButton::Init()
{
	m_mou_x = 0.0f;	
	m_mou_y = 0.0f;
	m_mou_r = false;
	m_mou_l = false;

	m_a = 1.0f;	

	//▼テスト用
	//CObjPlanet* pla = (CObjPlanet*)Objs::GetObj(OBJ_PLANET);
	//m_invincible_f[PLAYER] = pla->GetInvincible_sp(PLAYER);
}

//アクション
void CObjSpecialButton::Action()
{
	//▼戦闘開始前は操作不能にする処理
	if (battle_start == false)
	{
		return;
	}

	//マウスの位置を取得
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//マウスのボタンの状態
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();


	//▼プレイヤー惑星スペシャル技処理(↓の敵惑星verとほとんど被るようであれば後で関数化)
	if ((m_x <= m_mou_x && m_mou_x <= (m_x + m_w)) && 	//X軸範囲
		(m_y <= m_mou_y && m_mou_y <= (m_y + m_h)) &&	//Y軸範囲
		 m_mou_l == true &&								//クリック
		 m_is_used_special[PLAYER] == false)			//スペシャル技未使用かチェック
	{
		//▼スペシャル技発動演出(敵惑星でも使うので関数化必須)


		//現在装備中のスペシャル技を判別後、
		//そのスペシャル技の効果を実際に発動する


		//▼テスト用
		//*m_invincible_f[PLAYER] = true;



		m_is_used_special[PLAYER] = true;	//スペシャル技使用済フラグ立て
		m_a = 0.3f;		//透明化
	}

	//▼敵惑星スペシャル技処理
	//if (*m_enemy_special_button == true &&				//敵スペシャル技発動チェック
	//	m_is_used_special[ENEMY] == false)				//スペシャル技未使用かチェック
	//{
	//	m_is_used_special[ENEMY] == true;	//スペシャル技使用済フラグ立て
	//}

	//▼時間切れの時の処理
	CObjFight* obj = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
	if (obj->GetCount() <= 60) 
	{	
		m_is_used_special[PLAYER] = true;	//時間切れでスペシャル技発動不可にする
		m_is_used_special[ENEMY]  = true;	//同じく敵もスペシャル技発動不可にする
		m_a -= 0.03f;				//徐々に透明化する
		if (m_a > 0.0f)
			this->SetStatus(false);	//完全透明になった時点で消滅
	}
}

//ドロー
void CObjSpecialButton::Draw()
{
	//描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	float c[4] = { 1.0f,1.0f, 1.0f, m_a };

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置


	//▼スペシャル技ボタン表示
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 175.0f;
	src.m_bottom = 114.0f;

	dst.m_top = m_y;
	dst.m_left = m_x;
	dst.m_right = m_x + m_w;
	dst.m_bottom = m_y + m_h;
	Draw::Draw(19, &src, &dst, c, 0.0f);
}