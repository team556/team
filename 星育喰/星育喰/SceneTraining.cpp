//STLでバグ機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERTOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"


//使用するネームスペース
using namespace GameL;

//使用ヘッダー
//#include "SceneMain.h"
#include "GameHead.h"

#include <stdlib.h>
#include <time.h>

//コンストラクタ
CSceneTraining::CSceneTraining()
{

}

//デストラクタ
CSceneTraining::~CSceneTraining()
{

}

//ゲーム初期化メソッド
void CSceneTraining::InitScene()
{
	//出力させる文字のグラフィックを作成
	//Font::SetStrTex(L"");

	srand(time(NULL));//ランダム情報を初期化
	
	//▼住民の初期X,Y座標をランダムで取得
	//今は3回ずつの繰り返し回数だが、
	//繰り返し回数は住民数を管理するグローバル変数を基に
	//描画する住民の数分行うように後に変更しておく。

	//Humanの初期X座標取得
	for (int i = 0; i < 3; i++)
	{
		m_ini_hx[i] = rand() % 401 + 400;//400～800の値をランダム取得し、Humanの初期X座標とする。
	}
	//Humanの初期Y座標取得
	for (int i = 0; i < 3; i++)
	{
		m_ini_hy[i] = rand() % 301 + 200;//200～500の値をランダム取得し、Humanの初期Y座標とする。
	}

	//住民オブジェクト
	//今は3回ずつの繰り返し回数だが、
	//繰り返し回数は住民数を管理するグローバル変数を基に
	//描画する住民の数分行うように後に変更しておく。
	for (int i = 0; i < 3; i++)
	{
		CObjHuman* obj_human = new CObjHuman(m_ini_hx[i], m_ini_hy[i]);	//住民オブジェクト作成
		Objs::InsertObj(obj_human, OBJ_HUMAN, 15);						//住民オブジェクト登録
	}

	
	//育成画面オブジェクト
	CObjTraining* obj = new CObjTraining();     //育成画面オブジェクト作成
	Objs::InsertObj(obj, OBJ_TRAINING, 10);		//育成画面オブジェクト登録

	//施設(仮)オブジェクト							
	//CObjTest* obj1 = new CObjTest(700,300);	//施設(仮)オブジェクト作成
	//Objs::InsertObj(obj1, OBJ_TEST, 20);		//施設(仮)オブジェクト登録

	//雲演出オブジェクト(雲演出OUT)
	CObjCloud_Effect* obj_cloud = new CObjCloud_Effect(false);	//雲演出オブジェクト作成
	Objs::InsertObj(obj_cloud, OBJ_CLOUD, 100);					//雲演出オブジェクト登録

	//背景を読み込み0番に登録
	Draw::LoadImage(L"地面TEST.gif", 0, TEX_SIZE_512);

	//(仮)戻るアイコンを読み込み1番に登録
	Draw::LoadImage(L"戻るアイコンTEST.png", 1, TEX_SIZE_512);

	//住民を読み込み10番に登録
	Draw::LoadImage(L"Human.png", 10, TEX_SIZE_512);

	//雲を読み込み15番に登録
	Draw::LoadImage(L"透過雲.png", 15, TEX_SIZE_512);

	//プレイヤー惑星を読み込み50番に登録
	Draw::LoadImage(L"Player_Planet_Test.png", 50, TEX_SIZE_512);
}

//ゲームメイン実行中メソッド
void CSceneTraining::Scene()
{

}