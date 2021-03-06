//使用するヘッダー
#include "GameL\DrawTexture.h"

//使用するネームスペース
using namespace GameL;

//---Call_Planet関数
//引数1　int group	:グループ決定
//引数2　int select	:惑星選択
//▼内容
//タイトル画面、ホーム画面の敵惑星(背景)を呼び出す関数。
//敵惑星(背景)は3つ存在するため、
//全ての敵惑星の画像を3グループに分け、
//そこから、それぞれ指定された(ランダムな)敵惑星データを返す。
void Call_Planet(int group, int select)
{
	if (group == 0)
	{
		if (select == 1)
		{
			//敵惑星1を読み込み20番に登録
			Draw::LoadImage(L"img\\惑星\\lv1x3クチナシ.png", 20, TEX_SIZE_512);	
		}
		else if (select == 2)
		{
			//敵惑星2を読み込み20番に登録
			Draw::LoadImage(L"img\\惑星\\lv1x3クチナシ.png", 20, TEX_SIZE_512);
		}
		else if (select == 3)
		{
			//敵惑星3を読み込み20番に登録
			Draw::LoadImage(L"img\\惑星\\lv1x3クチナシ.png", 20, TEX_SIZE_512);
		}
		else  //(select == 4)
		{
			//敵惑星4を読み込み20番に登録
			Draw::LoadImage(L"img\\惑星\\悪惑星修正.png", 20, TEX_SIZE_512);
		}
	}

	else if (group == 1)
	{
		if (select == 1)
		{
			//敵惑星1を読み込み22番に登録
			Draw::LoadImage(L"img\\惑星\\モアイ正面.png", 22, TEX_SIZE_512);
		}
		else if (select == 2)
		{
			//敵惑星2を読み込み22番に登録
			Draw::LoadImage(L"img\\惑星\\モアイ正面.png", 22, TEX_SIZE_512);
		}
		else if (select == 3)
		{
			//敵惑星3を読み込み22番に登録
			Draw::LoadImage(L"img\\惑星\\モアイ正面.png", 22, TEX_SIZE_512);
		}
		else  //(select == 4)
		{
			//敵惑星4を読み込み22番に登録
			Draw::LoadImage(L"img\\惑星\\悪惑星修正.png", 22, TEX_SIZE_512);
		}
	}

	else  //(group == 2)
	{
		if (select == 1)
		{
			//敵惑星1を読み込み24番に登録
			Draw::LoadImage(L"img\\惑星\\lv2x3修正.png", 24, TEX_SIZE_512);
		}
		else if (select == 2)
		{
			//敵惑星2を読み込み24番に登録
			Draw::LoadImage(L"img\\惑星\\lv2x3修正.png", 24, TEX_SIZE_512);
		}
		else if (select == 3)
		{
			//敵惑星3を読み込み24番に登録
			Draw::LoadImage(L"img\\惑星\\lv2x3修正.png", 24, TEX_SIZE_512);
		}
		else  //(select == 4)
		{
			//敵惑星4を読み込み24番に登録
			Draw::LoadImage(L"img\\惑星\\悪惑星修正.png", 24, TEX_SIZE_512);
		}
	}

}