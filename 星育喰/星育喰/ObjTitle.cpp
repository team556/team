//使用するヘッダーファイ
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"
#include "ObjTitle.h"
#include "Call_Planet.h"

#include <stdlib.h>
#include <time.h>

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjTitle::Init()
{
	m_Click_vy = 0.0f;	
	m_r = 0.0f;			

	m_mou_x = 0.0f;
	m_mou_y = 0.0f;

	m_time = 0;
	m_enemy_time = 0;
	m_Planet_Count = 0;
	m_enemy_y = 0;

	srand(time(NULL));//ランダム情報を初期化
}

//アクション
void CObjTitle::Action()
{
	//マウスの位置を取得(デバック用)
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
}

//ドロー
void CObjTitle::Draw()
{
	//描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	float d[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

	//背景表示
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 960.0f;
	src.m_bottom = 638.0f;

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 1200.0f;
	dst.m_bottom = 800.0f;
	Draw::Draw(0, &src, &dst, d, 0.0f);

	//プレイヤー惑星表示
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 300.0f;
	src.m_bottom = 168.0f;

	dst.m_top = 220.0f;
	dst.m_left = 250.0f;
	dst.m_right = 950.0f;
	dst.m_bottom = 620.0f;
	Draw::Draw(10, &src, &dst, d, 0.0f);


	//白
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	//黄色
	float y[4] = { 1.0f,1.0f,0.0f,1.0f };
	//Font::StrDraw(L"", 230, 250, 32, c);

	//▼"☆育喰"というタイトルを表示
	Font::StrDraw(L"☆育喰", 425, 100, 120, y);

	//▼上下ふわふわする"クリックでスタート"を表示
	//角度加算
	m_r += 2.0f;

	//360°で初期値に戻す
	if (m_r > 360.0f)
		m_r = 0.0f;

	//移動方向
	m_Click_vy = sin(3.14f / 90 * m_r);

	//速度付ける。
	m_Click_vy *= 10.0f;

	Font::StrDraw(L"クリックでスタート", 460, 700 + m_Click_vy, 32, c);


	//敵惑星
	m_time++;
	m_enemy_time+= 5;

	if (m_enemy_time >= 1500.0f)
	{
		m_enemy_time = 0;
		Call_Planet(1, 1);
		m_enemy_y = rand() % 601 + 100;
	}

	//if (rand() % 101 + 150 == m_time)
	//{
		m_time = 0;
		
	/*	if (m_Planet_Count == 0)
		{
			m_Planet_Count++;
			m_enemy_time = 0;
			Call_Planet(1, 1);
			m_enemy_y = rand () % 601 + 100;

			
		}*/

		//敵惑星1表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 384.0f;
		src.m_bottom = 384.0f;

		dst.m_top = m_enemy_y;
		dst.m_left = 1199.0f - m_enemy_time;
		dst.m_right = 1249.0f - m_enemy_time;
		dst.m_bottom = m_enemy_y + 50.0f;
		Draw::Draw(20, &src, &dst, d, 0.0f);



	//}


	//デバック用仮マウス位置表示
	wchar_t str[256];
	swprintf_s(str, L"x=%f,y=%f", m_mou_x, m_mou_y);
	Font::StrDraw(str, 20, 20, 12, c);
}
