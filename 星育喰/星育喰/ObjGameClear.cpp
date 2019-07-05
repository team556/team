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
	m_right_alpha = 3.0f;

	m_flag = false;
	m_end_f = false;
}

//アクション
void CObjGameClear::Action()
{
	////マウスの位置を取得
	//m_mou_x = (float)Input::GetPosX();
	//m_mou_y = (float)Input::GetPosY();
	//マウスのボタンの状態
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	//下から上に移動させる処理
	for (int i = 0; i < 100; i++)
	{
		m_cy[i] -= m_y_vec + m_speed;
	}

	if (m_right_alpha >= 0.0f)
	{
		m_right_alpha -= 0.01f;
	}

	//右クリックを押している間、エンドロールの流れる速度が速くなる
	if (m_mou_r == true && m_end_f == false)
	{
		m_speed = 10;
		m_right_alpha -= 0.1f;//右クリックを押すと透過速度が早くなる
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
	//左クリックとエンドフラグがtrueになったら
	else if (m_mou_l == true && m_end_f == true)
	{
		m_flag = true;

		//選択音
		Audio::Start(1);
	}

	//23番目スクロールに登録された画像が下から上に流れてきたら
	if (m_cy[23] <= 0.0f)
	{
		m_y_vec = 0;	//スクロールを止める
		m_end_f = true;
	}
}
//ドロー
void CObjGameClear::Draw()
{
	//描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	float d[4] = { 0.0f,0.0f, 0.0f, 1.0f };

	//画像用[シーン移行時フェードアウト]
	float w[4] = { 1.0f,1.0f, 1.0f, m_alpha };

	//画像用[シーン移行時フェードアウト]
	float w2[4] = { 1.0f,1.0f, 1.0f, m_right_alpha };

	//文字の色(白)
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

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
	Draw::Draw(0, &src, &dst, d, 0.0f);


	//ここから下がスクロールするテキスト（画像）の描画
	//音人描画
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 893.0f;
	src.m_bottom = 193.0f;

	dst.m_top = 0.0f + m_cy[2];
	dst.m_left = 200.0f;
	dst.m_right = 900.0f;
	dst.m_bottom = 163.0f + m_cy[2];
	Draw::Draw(2, &src, &dst, w, m_alpha);

	//魔王魂描画
	src.m_top = 20.0f;
	src.m_left = 0.0f;
	src.m_right = 1065.0f;
	src.m_bottom = 200.0f;

	dst.m_top = 100.0f + m_cy[3];
	dst.m_left = 200.0f;
	dst.m_right = 900.0f;
	dst.m_bottom = 163.0f + m_cy[4];
	Draw::Draw(3, &src, &dst, w, m_alpha);

	//魔王魂2描画
	src.m_top = 15.0f;
	src.m_left = 0.0f;
	src.m_right = 893.0f;
	src.m_bottom = 95.0f;

	dst.m_top = 90.0f + m_cy[5];
	dst.m_left = 250.0f;
	dst.m_right = 843.0f;
	dst.m_bottom = 163.0f + m_cy[5];
	Draw::Draw(4, &src, &dst, w, m_alpha);

	//TAMM描画
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1364.0f;
	src.m_bottom = 202.0f;

	dst.m_top = 90.0f + m_cy[6];
	dst.m_left = 200.0f;
	dst.m_right = 893.0f;
	dst.m_bottom = 163.0f + m_cy[7];
	Draw::Draw(5, &src, &dst, w, m_alpha);

	//DOVA-SYN_DROME描画
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 995.0f;
	src.m_bottom = 196.0f;

	dst.m_top = 100.0f + m_cy[8];
	dst.m_left = 200.0f;
	dst.m_right = 893.0f;
	dst.m_bottom = 163.0f + m_cy[9];
	Draw::Draw(6, &src, &dst, w, m_alpha);

	//無料効果音で遊ぼう描画
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1866.0f;
	src.m_bottom = 212.0f;

	dst.m_top = 100.0f + m_cy[10];
	dst.m_left = 200.0f;
	dst.m_right = 893.0f;
	dst.m_bottom = 163.0f + m_cy[11];
	Draw::Draw(7, &src, &dst, w, m_alpha);

	//効果音ラボ描画
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1384.0f;
	src.m_bottom = 204.0f;

	dst.m_top = 100.0f + m_cy[12];
	dst.m_left = 200.0f;
	dst.m_right = 893.0f;
	dst.m_bottom = 163.0f + m_cy[13];
	Draw::Draw(8, &src, &dst, w, m_alpha);

	//OtoLogic描画
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 892.0f;
	src.m_bottom = 194.0f;

	dst.m_top = 100.0f + m_cy[14];
	dst.m_left = 200.0f;
	dst.m_right = 893.0f;
	dst.m_bottom = 163.0f + m_cy[15];
	Draw::Draw(9, &src, &dst, w, m_alpha);


	//タイトルロゴ描画
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1557.0f;
	src.m_bottom = 929.0f;

	dst.m_top = 0.0f + m_cy[24];
	dst.m_left = 300.0f;
	dst.m_right = 851.0f;
	dst.m_bottom = 350.0f + m_cy[24];
	Draw::Draw(1, &src, &dst, w, m_alpha);

	//END描画
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 274.0f;
	src.m_bottom = 117.0f;

	dst.m_top = 0.0f + m_cy[20];
	dst.m_left = 400.0f;
	dst.m_right = 574.0f;
	dst.m_bottom = 217.0f + m_cy[20];
	Draw::Draw(10, &src, &dst, w, m_alpha);

	//END描画
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 269.0f;
	src.m_bottom = 117.0f;

	dst.m_top = 0.0f + m_cy[20];
	dst.m_left = 400.0f;
	dst.m_right = 574.0f;
	dst.m_bottom = 217.0f + m_cy[20];
	Draw::Draw(10, &src, &dst, w, m_alpha);

	//右クリックをすると描画
	src.m_top = 3.0f;
	src.m_left = 3.0f;
	src.m_right = 1481.0f;
	src.m_bottom = 114.0f;

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 200.0f;
	dst.m_bottom = 32.0f;
	Draw::Draw(12, &src, &dst, w2, m_alpha);

	//エンドロールが早く流れます描画
	src.m_top = 3.0f;
	src.m_left = 3.0f;
	src.m_right = 1663.0f;
	src.m_bottom = 116.0f;

	dst.m_top = 40.0f;
	dst.m_left = 50.0f;
	dst.m_right = 300.0f;
	dst.m_bottom = 72.0f;
	Draw::Draw(13, &src, &dst, w2, m_alpha);




	//Font::StrDraw(L"右クリックを押し続けると", 0, 0, 20, w2);
	//Font::StrDraw(L"エンドロールが早く流れます。", 0,25, 20, w2);

	Font::StrDraw(L"使用した音楽、効果音サイト", 260, m_cy[0], 50, c);


	/*Font::StrDraw(L"End", 550, m_cy[20] , 60, c);*/

	//エンドフラグがtrueになったら
	if (m_end_f == true)
	{
		Font::StrDraw(L"クリックでタイトルに戻る", 250, 600, 60, w);
	}
}
