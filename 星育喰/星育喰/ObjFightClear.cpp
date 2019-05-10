//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"
#include "ObjFightClear.h"

//使用するネームスペース
using namespace GameL;

////コンストラクタ
//CObjTest::CObjTest(float x, float y)
//{
//	//作成時に渡された値を、座標の初期値に代入
//	m_x = x;
//	m_y = y;
//}

//イニシャライズ
void CObjFightClear::Init()
{
	//m_mou_x = 0.0f;	//マウスX座標
	//m_mou_y = 0.0f; //マウスY座標
	//m_mou_r = false;//右クリック
	m_mou_l = false;//左クリック

	m_a = 0.0f;
	m_a_vec = 0.0f;
	m_a_f = false;

	m_people = 0;	//住民
	m_mrl = 0;		//マテリアルズ(資材)
	m_skill = 0;	//スペシャル技

	m_cnt = 3 * 60;	//3秒カウント
}

//アクション
void CObjFightClear::Action()
{
	////マウスの位置を取得
	//m_mou_x = (float)Input::GetPosX();
	//m_mou_y = (float)Input::GetPosY();
	////マウスのボタンの状態
	//m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	if (m_cnt == 0) {							//カウント終了後
		if (m_mou_l == true)					//クリックした場合
			Scene::SetScene(new CSceneHome());	//シーン移行
		m_a_f = true;			//フラグ有効
	}
	else
		m_cnt--;	//0でない場合カウントダウン

	if (m_a_f == true)			//フラグ有効の場合
		if (m_a <= 0.5)						//0.5で切り替え
			m_a_vec += 0.003f;	//ベクトルに加算
		else
			m_a_vec -= 0.003f;	//ベクトルに減算

	m_a += m_a_vec;	//ベクトルを反映
}

//ドロー
void CObjFightClear::Draw()
{
	//描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	float d[4] = { 1.0f,1.0f, 1.0f, 1.0f };//画像の色

	RECT_F src;//切り取り位置
	RECT_F dst;//表示位置
	
	src.m_top   =  0.0f;
	src.m_left  =  0.0f;
	src.m_right =100.0f;
	src.m_bottom=100.0f;
	
	dst.m_top   =  50.0f;
	dst.m_left  = 650.0f;
	dst.m_right =1100.0f;
	dst.m_bottom= 600.0f;
	//0番目に登録したグラフィックをsrc,dst,c情報をもとに描画
	Draw::Draw(2, &src, &dst, d, 0.0f);

	float c0[4] = { 1.0f,1.0f,1.0f,m_a };//charの色
	Font::StrDraw(L"クリックでホーム画面", 350, 600, 50, c0);

	float c[4] = { 0.0f,0.0f,0.0f,1.0f };//charの色
	Font::StrDraw(L"住民", 700, 100, 50, c);

	Font::StrDraw(L"資材", 700, 250, 50, c);

	Font::StrDraw(L"技", 700, 400, 50, c);

	//Font::StrDraw(L"大きさ", 0, 300, 32, c);

	wchar_t str[256];
	swprintf_s(str, L"＋%d人",m_people);		//住民
	Font::StrDraw(str, 900, 100, 50, c);

	swprintf_s(str, L"＋%d個", m_mrl);			//資材
	Font::StrDraw(str, 900, 250, 50, c);

	swprintf_s(str, L"Get %c", m_skill);		//スペシャル技
	Font::StrDraw(str, 900, 400, 50, c);
}
