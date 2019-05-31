//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjGameClear.h"


//使用するネームスペース
using namespace GameL;

//マクロ
#define INI_ALPHA (1.0f) //透過度(アルファ値)の初期値

////コンストラクタ
//CObjTest::CObjTest(float x, float y)
//{
//	//作成時に渡された値を、座標の初期値に代入
//	m_x = x;
//	m_y = y;
//}

//イニシャライズ
void CObjGameClear::Init()
{
	m_mou_x = 0.0f;	//マウスX座標
	m_mou_y = 0.0f; //マウスY座標
	m_mou_r = false;//右クリック
	m_mou_l = false;//左クリック

	m_f = false;
	m_y_vec = 1.0;

	for (int i = 0; i < 100; i++)//配列の初期化
		m_cy[i] = i * 80 + 700;	//行間の間隔を空けるのと、画面より下にする
	m_c_nam = 0;

	m_speed = 0;
	m_alpha = INI_ALPHA;

	m_flag = false;

}

//アクション
void CObjGameClear::Action()
{
	//マウスの位置を取得
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//マウスのボタンの状態
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	//Zキーを押している間、エンドロールの流れる速度が速くなる
	if (Input::GetVKey('Z') == true)
	{
		m_speed = 10;
	}
	else
	{
		m_speed = 0;
	}

	//左クリックでタイトル画面へシーン移行
	if (m_flag == true)
	{
		m_alpha -= 0.01f;

		if (m_alpha <= 0.0f)
		{
			Scene::SetScene(new CSceneTitle());//タイトル画面へシーン移行
		}

		return;
	}
	else if (m_mou_l == true)
	{
		if (m_key_f == true)
		{
			m_flag = true;
			//選択音
			Audio::Start(1);
		}
	}



}
//ドロー
void CObjGameClear::Draw()
{
	//描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	float d[4] = { 0.0f,0.0f, 0.0f, 1.0f };

	//白＆動く画像用(クリックでスタート、敵惑星)[シーン移行時フェードアウト]
	float w[4] = { 1.0f,1.0f,1.0f,m_alpha };

	RECT_F src;//切り取り位置
	RECT_F dst;//表示位置
	
	src.m_top   =  0.0f;
	src.m_left  =  0.0f;
	src.m_right =100.0f;
	src.m_bottom=100.0f;
	
	dst.m_top   =  0.0f;
	dst.m_left  =  0.0f;
	dst.m_right =1200.0f;
	dst.m_bottom= 700.0f;

	//0番目に登録したグラフィックをsrc,dst,c情報をもとに描画
	Draw::Draw(1, &src, &dst, d, 0.0f);

	for (int i = 0; i < 100; i++)
	{
		m_cy[i] -= m_y_vec + m_speed;
	}

	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	Font::StrDraw(L"使用した音楽、効果音サイト", 260, m_cy[0], 50, c);

	Font::StrDraw(L"音人",	550, m_cy[2], 45, c);
	Font::StrDraw(L"https://on-jin.com/",375, m_cy[3]-20, 45, c);

	Font::StrDraw(L"魔王魂",525, m_cy[4]+20, 45, c);
	Font::StrDraw(L"https://m aoudam ashii.jokersounds.com/",	160, m_cy[5], 45, c);

	Font::StrDraw(L"TA M M usic Factory",380, m_cy[6] + 20, 45, c);
	Font::StrDraw(L"https://w w w.tam - music.com/",300, m_cy[7], 45, c);

	Font::StrDraw(L"DOVA-SYN DROME", 450,m_cy[8] + 20, 45, c);
	Font::StrDraw(L"https://dova-s.jp/",400, m_cy[9], 45, c);

	Font::StrDraw(L"無料効果音で遊ぼう",400, m_cy[10] + 20, 45, c);
	Font::StrDraw(L"https://taira-ko m ori.jpn.org/in dex.htm l",160, m_cy[11], 45, c);

	Font::StrDraw(L"効果音ラボ",480, m_cy[12] + 20, 45, c);
	Font::StrDraw(L"https://soun deffect-lab.info/",300, m_cy[13], 45, c);

	Font::StrDraw(L"OtoLogic",500, m_cy[14] + 20, 45, c);
	Font::StrDraw(L"https://otologic.jp/",380, m_cy[15], 45, c);

	Font::StrDraw(L"End", 550, m_cy[20] , 60, c);

	//タイトルロゴ描画
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1557.0f;
	src.m_bottom = 929.0f;

	dst.m_top = 200.0f + m_cy[24];
	dst.m_left = 350.0f;
	dst.m_right = 851.0f;
	dst.m_bottom = 550.0f + m_cy[24];
	Draw::Draw(2, &src, &dst, w, m_alpha);

	if (m_cy[24] == true)
	{
		Font::StrDraw(L"クリックでタイトルに戻る", 350, 500, 60, c);
	}
}
