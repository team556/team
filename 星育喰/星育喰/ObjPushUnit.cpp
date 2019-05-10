//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"
#include "ObjPushUnit.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjPushUnit::CObjPushUnit(float x, float y, float h, float w, int n)
{
	//作成時に渡された値を、座標の初期値に代入
	m_x = x;
	m_y = y;
	m_h = h;
	m_w = w;

	Button_num = n;
}

//イニシャライズ
void CObjPushUnit::Init()
{
	m_mou_x = 0.0f;	//マウスX座標
	m_mou_y = 0.0f; //マウスY座標
	m_mou_r = false;//右クリック
	m_mou_l = false;//左クリック
	m_mou_f = false;//マウスフラグ

	m_a = 1.0f;		//透明度

	m_cnt = 0;		//カウント
}

//アクション
void CObjPushUnit::Action()
{

	//マウスの位置を取得
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//マウスのボタンの状態
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();


	if ((m_x <= m_mou_x && m_mou_x <= (m_x + m_w))		//X軸範囲
		&& (m_y <= m_mou_y && m_mou_y <= (m_y + m_h))	//Y軸範囲
		&& m_mou_l == true) {							//クリック
		if (m_mou_f == false) {
			//▼ポッド作成X位置を設定
			CObjFight* obj = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
			m_create_x = obj->GetCount() / 10 + 100;

			g_Power_num;				//パワー住民数
			g_Defense_num;			//ディフェンス住民数
			g_Speed_num;				//スピード住民数
			g_Balance_num;			//バランス住民数

			if (Button_num == 1 && g_Power_num != 0)//パワーボタンかつ、パワーユニット数がある場合
			{
				//オブジェクト作成
				CObjMissile* M = new CObjMissile(575 + m_create_x, 200, true,1);//オブジェクト作成
				Objs::InsertObj(M, OBJ_MISSILE, 15);		//オブジェクト登録

			}
			else if (Button_num == 2 && g_Defense_num != 0)
			{
				//オブジェクト作成
				CObjMissile* M = new CObjMissile(575 + m_create_x, 200, true, 2);//オブジェクト作成
				Objs::InsertObj(M, OBJ_MISSILE, 15);		//オブジェクト登録

			}
			else if (Button_num == 3 && g_Speed_num != 0)
			{
				//オブジェクト作成
				CObjMissile* M = new CObjMissile(575 + m_create_x, 200, true, 3);//オブジェクト作成
				Objs::InsertObj(M, OBJ_MISSILE, 15);		//オブジェクト登録

			}

			else if (Button_num == 4 && g_Balance_num != 0)
			{
				//オブジェクト作成
				CObjMissile* M = new CObjMissile(575 + m_create_x , 200, true, 4);//オブジェクト作成
				Objs::InsertObj(M, OBJ_MISSILE, 15);		//オブジェクト登録
			}

			else if (Button_num == 5)
			{
				CObjMissile* M = new CObjMissile(575 + m_create_x , 200, true, 5);//オブジェクト作成
				Objs::InsertObj(M, OBJ_MISSILE, 15);		//オブジェクト登録
			}

			m_mou_f = true;
			m_a = 0.3f;		//透明化
		}
	}

	else{}

	if (m_mou_f == true) {	//クリックした後の処理
		m_cnt++;			//カウントする
		if (m_cnt == 60 * 5) {	//5秒間数えたら
			m_mou_f = false;	//クリックできるようにする。
			m_cnt = 0;
			m_a = 1.0f;		//不透明化
		}
	}

	CObjFight* obj = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
	if (obj->GetCount() <= 60) {	//時間切れで
		m_mou_f = true;			//マウス無効
		m_a -= 0.03f;				//透明化
		if (m_a > 0.0f) 
			this->SetStatus(false);	//消滅
	}
}

//ドロー
void CObjPushUnit::Draw()
{
	//描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	float c[4] = { 1.0f,1.0f, 1.0f, m_a };

	RECT_F src;//切り取り位置
	RECT_F dst;//表示位置
	
	//ボタン入力が1～4の時の切り取り位置
	if (Button_num >= 1 && Button_num <= 4)
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 156.0f;
		src.m_bottom = 156.0f;
	}
	//それ以外ならミサイルの切り取り位置
	else
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 300.0f;
		src.m_bottom = 180.0f;
	}
		dst.m_top = m_y;
		dst.m_left = m_x;
		dst.m_right = m_x + m_w;
		dst.m_bottom = m_y + m_h;

	//ポッド・ミサイルの表示するためのswitch文
	switch (Button_num){
	case 1:                 //-------------------------赤色ボタン
		//11番目に登録したグラフィックをsrc,dst,c情報をもとに描画
		Draw::Draw(11, &src, &dst, c, 0.0f);
		break;
	case 2:                 //-------------------------青色ボタン
		//12番目に登録したグラフィックをsrc,dst,c情報をもとに描画
		Draw::Draw(12, &src, &dst, c, 0.0f);
		break;
	case 3:                 //-------------------------緑色ボタン
		//13番目に登録したグラフィックをsrc,dst,c情報をもとに描画
		Draw::Draw(13, &src, &dst, c, 0.0f);
		break;
	case 4:                 //-------------------------灰色ボタン
		//14番目に登録したグラフィックをsrc,dst,c情報をもとに描画
		Draw::Draw(14, &src, &dst, c, 0.0f);
		break;
	case 5:                 //-------------------------ミサイルボタン
		//15番目に登録したグラフィックをsrc,dst,c情報をもとに描画
		Draw::Draw(15, &src, &dst, c, 0.0f);
		break;
	}
}