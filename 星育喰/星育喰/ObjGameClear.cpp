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
		m_cy[i] = i * 25 + 700;	//行間の間隔を空けるのと、画面より下にする
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
	//else if (m_mou_l == true && m_end_f == false)
	//{
	//	m_speed = -10;
	//	m_right_alpha -= 0.1f;//右クリックを押すと透過速度が早くなる
	//}
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
	if (m_cy[79]+125.0f <= 0.0f)
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

	//使用した音楽、効果音サイト描画
	src.m_top = 3.0f;
	src.m_left = 3.0f;
	src.m_right = 1606.0f;
	src.m_bottom = 114.0f;

	dst.m_top = 0.0f + m_cy[0];
	dst.m_left = 350.0f;
	dst.m_right = 850.0f;
	dst.m_bottom = 0.0f + m_cy[1];
	Draw::Draw(3, &src, &dst, w, 0.0);

	//音人描画
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 185.0f;
	src.m_bottom = 90.0f;

	dst.m_top = 0.0f + m_cy[2];
	dst.m_left = 575.0f;
	dst.m_right = 625.0f;
	dst.m_bottom = 0.0f + m_cy[3];
	Draw::Draw(7, &src, &dst, w, 0.0);

	//音人URL描画
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 870.0f;
	src.m_bottom = 84.0f;

	dst.m_top = 10.0f + m_cy[3];
	dst.m_left = 475.0f;
	dst.m_right = 725.0f;
	dst.m_bottom = 10.0f + m_cy[4];
	Draw::Draw(8, &src, &dst, w, 0.0);

	//魔王魂描画
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 282.0f;
	src.m_bottom = 90.0f;

	dst.m_top = 20.0f + m_cy[6];
	dst.m_left = 565.0f;
	dst.m_right = 635.0f;
	dst.m_bottom = 20.0f + m_cy[7];
	Draw::Draw(9, &src, &dst, w, 0.0);

	//魔王魂URL1描画
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1060.0f;
	src.m_bottom = 84.0f;

	dst.m_top = 30.0f + m_cy[7];
	dst.m_left = 425.0f;
	dst.m_right = 775.0f;
	dst.m_bottom = 30.0f + m_cy[8];
	Draw::Draw(10, &src, &dst, w, 0.0);

	//魔王魂URL2描画
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 876.0f;
	src.m_bottom = 84.0f;

	dst.m_top = 30.0f + m_cy[8];
	dst.m_left = 475.0f;
	dst.m_right = 725.0f;
	dst.m_bottom = 30.0f + m_cy[9];
	Draw::Draw(11, &src, &dst, w, 0.0);

	//TAMM描画
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1005.0f;
	src.m_bottom = 84.0f;

	dst.m_top = 30.0f + m_cy[11];
	dst.m_left = 505.0f;
	dst.m_right = 690.0f;
	dst.m_bottom = 30.0f + m_cy[12];
	Draw::Draw(12, &src, &dst, w, 0.0);

	//TAMMURL描画
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1341.0f;
	src.m_bottom = 84.0f;

	dst.m_top = 40.0f + m_cy[12];
	dst.m_left = 400.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 40.0f + m_cy[13];
	Draw::Draw(13, &src, &dst, w, 0.0);

	//DOVA-SYN_DROME描画
	src.m_top = 2.0f;
	src.m_left = 0.0f;
	src.m_right = 945.0f;
	src.m_bottom = 77.0f;

	dst.m_top = 40.0f + m_cy[15];
	dst.m_left = 505.0f;
	dst.m_right = 690.0f;
	dst.m_bottom = 40.0f + m_cy[16];
	Draw::Draw(14, &src, &dst, w, 0.0);

	//DOVA-SYN_DROMEURL描画
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 819.0f;
	src.m_bottom = 84.0f;

	dst.m_top = 50.0f + m_cy[16];
	dst.m_left = 480.0f;
	dst.m_right = 720.0f;
	dst.m_bottom = 50.0f + m_cy[17];
	Draw::Draw(15, &src, &dst, w, 0.0);

	//無料効果音で遊ぼう描画
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 852.0f;
	src.m_bottom = 90.0f;

	dst.m_top = 50.0f + m_cy[19];
	dst.m_left = 495.0f;
	dst.m_right = 705.0f;
	dst.m_bottom = 50.0f + m_cy[20];
	Draw::Draw(16, &src, &dst, w, 0.0);

	//無料効果音で遊ぼうURL描画
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1842.0f;
	src.m_bottom = 84.0f;

	dst.m_top = 60.0f + m_cy[20];
	dst.m_left = 400.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 60.0f + m_cy[21];
	Draw::Draw(17, &src, &dst, w, 0.0);

	//効果音ラボ描画
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 474.0f;
	src.m_bottom = 90.0f;

	dst.m_top = 70.0f + m_cy[23];
	dst.m_left = 542.0f;
	dst.m_right = 658.0f;
	dst.m_bottom = 70.0f + m_cy[24];
	Draw::Draw(18, &src, &dst, w, 0.0);

	//効果音ラボurl描画
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1364.0f;
	src.m_bottom = 84.0f;

	dst.m_top = 80.0f + m_cy[24];
	dst.m_left = 400.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 80.0f + m_cy[25];
	Draw::Draw(19, &src, &dst, w, 0.0);

	//OtoLogic描画
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 444.0f;
	src.m_bottom = 84.0f;

	dst.m_top = 90.0f + m_cy[27];
	dst.m_left = 550.0f;
	dst.m_right = 650.0f;
	dst.m_bottom = 90.0f + m_cy[28];
	Draw::Draw(20, &src, &dst, w, 0.0);

	//OtoLogic描画
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 882.0f;
	src.m_bottom = 84.0f;

	dst.m_top = 100.0f + m_cy[28];
	dst.m_left = 450.0f;
	dst.m_right = 750.0f;
	dst.m_bottom = 100.0f + m_cy[29];
	Draw::Draw(21, &src, &dst, w, 0.0);

	//使用フォント描画
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 672.0f;
	src.m_bottom = 105.0f;

	dst.m_top = 110.0f + m_cy[33];
	dst.m_left = 500.0f;
	dst.m_right = 700.0f;
	dst.m_bottom = 110.0f + m_cy[34];
	Draw::Draw(32, &src, &dst, w, 0.0);

	//使用フォントピリオド描画
	src.m_top = 1.0f;
	src.m_left = 1444.0f;
	src.m_right = 0.0f;
	src.m_bottom = 101.0f;

	dst.m_top = 120.0f + m_cy[34];
	dst.m_left = 750.0f;
	dst.m_right = 450.0f;
	dst.m_bottom = 120.0f + m_cy[35];
	Draw::Draw(33, &src, &dst, w, 0.0);

	//作者紹介
	src.m_top = 1.0f;
	src.m_left = 290.0f;
	src.m_right = 10.0f;
	src.m_bottom = 100.0f;

	dst.m_top = 130.0f + m_cy[36];
	dst.m_left = 650.0f;
	dst.m_right = 550.0f;
	dst.m_bottom = 130.0f + m_cy[37];
	Draw::Draw(35, &src, &dst, w, 0.0);

	//作者名紹介
	src.m_top = 1.0f;
	src.m_left = 290.0f;
	src.m_right = 30.0f;
	src.m_bottom = 100.0f;

	dst.m_top =140.0f + m_cy[37];
	dst.m_left = 650.0f;
	dst.m_right = 550.0f;
	dst.m_bottom = 140.0f + m_cy[38];
	Draw::Draw(34, &src, &dst, w, 0.0);

	//サイト紹介
	src.m_top =2.0f;
	src.m_left = 486.0f;
	src.m_right = 105.0f;
	src.m_bottom = 100.0f;

	dst.m_top = 150.0f + m_cy[39];
	dst.m_left = 650.0f;
	dst.m_right = 550.0f;
	dst.m_bottom = 150.0f + m_cy[40];
	Draw::Draw(29, &src, &dst, w, 0.0);

	//飛べない鳥紹介
	src.m_top = 1.0f;
	src.m_left = 0.0f;
	src.m_right = 716.0f;
	src.m_bottom = 93.0f;

	dst.m_top = 160.0f + m_cy[40];
	dst.m_left = 500.0f;
	dst.m_right = 700.0f;
	dst.m_bottom = 160.0f + m_cy[41];
	Draw::Draw(30, &src, &dst, w, 0.0);

	//使用フォントURL
	src.m_top		= 1.0f;
	src.m_left		= 0.0f;
	src.m_right		= 1649.0f;
	src.m_bottom	= 94.0f;

	dst.m_top = 170.0f + m_cy[41];
	dst.m_left = 400.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 170.0f + m_cy[42];
	Draw::Draw(31, &src, &dst, w, 0.0);

	//総合ディレクタ
	src.m_top = 1.0f;
	src.m_left = 0.0f;
	src.m_right = 795.0f;
	src.m_bottom = 129.0f;

	dst.m_top = 180.0f + m_cy[46];
	dst.m_left = 450.0f;
	dst.m_right = 750.0f;
	dst.m_bottom = 180.0f + m_cy[47];
	Draw::Draw(36, &src, &dst, w, 0.0);

	//池田描画
	src.m_top = 5.0f;
	src.m_left = 0.0f;
	src.m_right = 497.0f;
	src.m_bottom = 99.0f;

	dst.m_top = 190.0f + m_cy[47];
	dst.m_left = 550.0f;
	dst.m_right = 650.0f;
	dst.m_bottom = 190.0f + m_cy[48];
	Draw::Draw(22, &src, &dst, w, 0.0);

	//プログラマ
	src.m_top = 1.0f;
	src.m_left = 0.0f;
	src.m_right = 490.0f;
	src.m_bottom = 100.0f;

	dst.m_top = 200.0f + m_cy[50];
	dst.m_left = 500.0f;
	dst.m_right = 700.0f;
	dst.m_bottom = 200.0f + m_cy[51];
	Draw::Draw(37, &src, &dst, w, 0.0);

	//後庵描画
	src.m_top = 1.0f;
	src.m_left = 0.0f;
	src.m_right = 398.0f;
	src.m_bottom = 99.0f;

	dst.m_top = 210.0f + m_cy[51];
	dst.m_left = 550.0f;
	dst.m_right = 650.0f;
	dst.m_bottom = 210.0f + m_cy[52];
	Draw::Draw(23, &src, &dst, w, 0.0);

	//木村描画
	src.m_top = 1.0f;
	src.m_left = 0.0f;
	src.m_right = 393.0f;
	src.m_bottom = 100.0f;

	dst.m_top = 220.0f + m_cy[52];
	dst.m_left = 550.0f;
	dst.m_right = 650.0f;
	dst.m_bottom = 220.0f + m_cy[53];
	Draw::Draw(24, &src, &dst, w, 0.0);

	//柏崎描画
	src.m_top = 1.0f;
	src.m_left = 0.0f;
	src.m_right = 392.0f;
	src.m_bottom = 100.0f;

	dst.m_top = 230.0f + m_cy[53];
	dst.m_left = 550.0f;
	dst.m_right = 650.0f;
	dst.m_bottom = 230.0f + m_cy[54];
	Draw::Draw(26, &src, &dst, w, 0.0);

	//グラフィッカー
	src.m_top = 1.0f;
	src.m_left = 0.0f;
	src.m_right = 674.0f;
	src.m_bottom = 125.0f;

	dst.m_top = 240.0f + m_cy[56];
	dst.m_left = 500.0f;
	dst.m_right = 700.0f;
	dst.m_bottom = 240.0f + m_cy[57];
	Draw::Draw(38, &src, &dst, w, 0.0);

	//諏訪描画
	src.m_top = 1.0f;
	src.m_left = 0.0f;
	src.m_right = 488.0f;
	src.m_bottom = 100.0f;

	dst.m_top = 250.0f + m_cy[57];
	dst.m_left = 550.0f;
	dst.m_right = 650.0f;
	dst.m_bottom = 250.0f + m_cy[58];
	Draw::Draw(28, &src, &dst, w, 0.0);

	//坂田描画
	src.m_top = 1.0f;
	src.m_left = 0.0f;
	src.m_right = 484.0f;
	src.m_bottom = 90.0f;

	dst.m_top = 260.0f + m_cy[58];
	dst.m_left = 550.0f;
	dst.m_right = 650.0f;
	dst.m_bottom = 260.0f + m_cy[59];
	Draw::Draw(27, &src, &dst, w, 0.0);

	//プランナー描画
	src.m_top = 1.0f;
	src.m_left = 0.0f;
	src.m_right = 497.0f;
	src.m_bottom = 100.0f;

	dst.m_top = 270.0f + m_cy[61];
	dst.m_left = 500.0f;
	dst.m_right = 700.0f;
	dst.m_bottom = 270.0f + m_cy[62];
	Draw::Draw(39, &src, &dst, w, 0.0);

	//脇田描画
	src.m_top = 1.0f;
	src.m_left = 0.0f;
	src.m_right = 490.0f;
	src.m_bottom = 100.0f;

	dst.m_top = 280.0f + m_cy[62];
	dst.m_left = 550.0f;
	dst.m_right = 650.0f;
	dst.m_bottom = 280.0f + m_cy[63];
	Draw::Draw(25, &src, &dst, w, 0.0);

	//END描画
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 269.0f;
	src.m_bottom = 117.0f;

	dst.m_top = 290.0f + m_cy[71];
	dst.m_left = 525.0f;
	dst.m_right = 675.0f;
	dst.m_bottom = 290.0f + m_cy[72];
	Draw::Draw(2, &src, &dst, w, 0.0);

	//タイトルロゴ描画
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1557.0f;
	src.m_bottom = 929.0f;

	dst.m_top = 300.0f + m_cy[78];
	dst.m_left = 300.0f;
	dst.m_right = 851.0f;
	dst.m_bottom = 650.0f + m_cy[79];
	Draw::Draw(1, &src, &dst, w, 0.0);
	


	//右クリックをすると描画
	src.m_top = 3.0f;
	src.m_left = 3.0f;
	src.m_right = 1481.0f;
	src.m_bottom = 114.0f;

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 200.0f;
	dst.m_bottom = 32.0f;
	Draw::Draw(4, &src, &dst, w2, 0.0);

	//エンドロールが早く流れます描画
	src.m_top = 3.0f;
	src.m_left = 3.0f;
	src.m_right = 1663.0f;
	src.m_bottom = 116.0f;

	dst.m_top = 40.0f;
	dst.m_left = 50.0f;
	dst.m_right = 300.0f;
	dst.m_bottom = 72.0f;
	Draw::Draw(5, &src, &dst, w2, 0.0);

	//Font::StrDraw(L"右クリックを押し続けると", 0, 0, 20, w2);
	//Font::StrDraw(L"エンドロールが早く流れます。", 0,25, 20, w2);

	//Font::StrDraw(L"使用した音楽、効果音サイト", 260, m_cy[0], 50, c);


	/*Font::StrDraw(L"End", 550, m_cy[20] , 60, c);*/

	//エンドフラグがtrueになったら
	if (m_end_f == true)
	{
		src.m_top = 3.0f;
		src.m_left = 3.0f;
		src.m_right = 1483.0f;
		src.m_bottom = 116.0f;

		dst.m_top = 630.0f;
		dst.m_left = 400.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 660.0f;
		Draw::Draw(6, &src, &dst, w, 0.0);
	}
}
