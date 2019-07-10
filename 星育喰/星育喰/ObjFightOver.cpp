//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"

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
void CObjFightOver::Init()
{
	//m_mou_x = 0.0f;	//マウスX座標
	//m_mou_y = 0.0f; //マウスY座標
	//m_mou_r = false;//右クリック
	m_mou_l = false;//左クリック

	m_a = 0.0f;
	m_a_vec = 0.0f;
	m_a_f = false;
	m_black_out_a = 0.0f;
	m_gameover_a = 0.0f;

	//m_cnt = 3 * 60;	//3秒カウント
}

//アクション
void CObjFightOver::Action()
{
	//ゲームオーバーメッセージ表示後の処理
	if (m_gameover_a >= 1.0f)
	{
		////マウスの位置を取得
		//m_mou_x = (float)Input::GetPosX();
		//m_mou_y = (float)Input::GetPosY();
		////マウスのボタンの状態
		//m_mou_r = Input::GetMouButtonR();
		m_mou_l = Input::GetMouButtonL();

		m_a_f = true;			//フラグ有効

		//左クリックした場合、実行(一度クリックすると以後、クリックせずともこの処理に入る)
		if (m_mou_l == true || m_black_out_a != 0.0f)
		{
			//クリック音を鳴らす(1度のみしか実行されない)
			if (m_black_out_a == 0.0f)
			{
				Audio::Start(3);
			}

			//画面暗転透過度を徐々に増加させ、画面全体を暗転させた後、
			//フラグを立て、タイトル画面に移行する
			if (m_black_out_a >= 1.0f)
			{
				Scene::SetScene(new CSceneTitle());	//シーン移行
			}
			else
			{
				m_black_out_a += 0.01f;	//画面暗転
				m_a -= 0.03f;			//クリック催促フォントを徐々に非表示に。
			}

			m_a_f = false;//フラグ無効
		}
	}
	//ゲームオーバーメッセージ表示前の処理
	else
	{
		//ゲームオーバーメッセージの透過度増加し、
		//ゲームオーバーメッセージを表示していく。
		//※表示後、このelse文を抜ける。
		m_gameover_a += 0.01f;
	}

	//▼「クリックでタイトル」の文字点滅処理
	//フラグ有効の場合
	if (m_a_f == true)
	{
		if (m_a <= 0.5)			//0.5で切り替えて、クリック文字のalpha調整
		{
			m_a_vec += 0.003f;	//ベクトルに加算
		}
		else
		{
			m_a_vec -= 0.003f;	//ベクトルに減算
		}

		m_a += m_a_vec;	//ベクトルを反映
	}
}

//ドロー
void CObjFightOver::Draw()
{
	RECT_F src;//切り取り位置
	RECT_F dst;//表示位置	


	//クリックでタイトル表示
	float c0[4] = { 1.0f,1.0f,1.0f,m_a };//charの色

	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1484.0f;
	src.m_bottom = 117.0f;

	dst.m_top = 600.0f;
	dst.m_left = 275.0f;
	dst.m_right = 975.0f;
	dst.m_bottom = 650.0f;
	Draw::Draw(51, &src, &dst, c0, 0.0f);




	//Font::StrDraw(L"クリックでタイトル", 350, 600, 50, c0);

	//ゲームオーバーフォント表示
	float c[4] = { 0.7f,0.0f,0.0f,m_gameover_a };//charの色
	//Font::StrDraw(L"G A M E", 220, 100, 200, c);
	//Font::StrDraw(L"O V E R", 220, 300, 200, c);

	src.m_top = 60.0f;
	src.m_left = 0.0f;
	src.m_right = 900.0f;
	src.m_bottom = 400.0f;

	dst.m_top = 150.0f;
	dst.m_left = 220.0f;
	dst.m_right = 975.0f;
	dst.m_bottom = 495.0f;
	Draw::Draw(52, &src, &dst, c, 0.0f);


	//▼画面全体暗転用画像表示
	//※blackoutの透過度の値で「表示/非表示」が切り替えられる
	float blackout[4] = { 1.0f,1.0f,1.0f,m_black_out_a };	//画面全体暗転画像用
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1200.0f;
	src.m_bottom = 700.0f;

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 1200.0f;
	dst.m_bottom = 700.0f;
	Draw::Draw(20, &src, &dst, blackout, 0.0f);
}
