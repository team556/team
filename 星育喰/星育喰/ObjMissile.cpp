//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjMissile.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjMissile::CObjMissile(float x, float y)
{
	//作成時に渡された値を、座標の初期値に代入
	m_x = x;
	m_y = y;
}

//イニシャライズ
void CObjMissile::Init()
{
	m_size = 50.0f;//サイズ
	
	m_vx = 0.0f;//ベクトル
	m_vy = 0.0f;
	
	m_mou_x = 0.0f;	//マウス情報
	m_mou_y = 0.0f;
	m_mou_r = false;
	m_mou_l = false;
	
	m_get_line = 0;//ライン取得用

	m_mou_f = false;//マウスフラグ

	//当たり判定用HitBox作成
	Hits::SetHitBox(this, m_x, m_y, m_size, m_size, ELEMENT_BLUE, OBJ_MISSILE, 1);
}

//アクション
void CObjMissile::Action()
{
	m_vx = 0.0f;//ベクトル初期化
	m_vy = 0.0f;

	//マウスの位置を取得
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//マウスのボタンの状態
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	if (m_mou_l == false)
	{
		m_mou_f = true;
	}
	else
	{
		m_mou_f = false;
	}

	CObjFight* obj = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
	if (obj != nullptr) {					//情報が取得出来ていたら
		m_get_line = obj->GetLine();		//ラインナンバーを取得
	}

	if (m_get_line == 0)
	{

	}
	else if (m_get_line == 1)
	{

	}
	else//if(m_get_line == 2)
	{

	}

	//座標更新
	m_x += m_vx;
	m_y += m_vy;

	CHitBox* hit = Hits::GetHitBox(this);	//CHitBoxポインタ取得
	hit->SetPos(m_x, m_y, m_size, m_size);	//位置を更新
}

//ドロー
void CObjMissile::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	Font::StrDraw(L"", 230, 250, 32, c);
	
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

	//2番目に登録したグラフィックをsrc,dst,c情報をもとに描画
	Draw::Draw(2, &src, &dst, d, 0.0f);
}