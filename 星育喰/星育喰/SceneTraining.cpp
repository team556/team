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
		m_ini_hy[i] = rand() % 201 + 250;//250～450の値をランダム取得し、Humanの初期Y座標とする。
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

	//兵舎オブジェクト							
	CObjBarracks* obj1 = new CObjBarracks();	//兵舎オブジェクト作成
	Objs::InsertObj(obj1, OBJ_BARRACKS, 20);	//兵舎オブジェクト登録

	//研究所オブジェクト							
	CObjInstitute* obj2 = new CObjInstitute();	//研究所オブジェクト作成
	Objs::InsertObj(obj2, OBJ_INSTITUTE, 20);	//研究所オブジェクト登録

	//雲演出オブジェクト(雲演出OUT)
	CObjCloud_Effect* obj_cloud = new CObjCloud_Effect(false);	//雲演出オブジェクト作成
	Objs::InsertObj(obj_cloud, OBJ_CLOUD, 100);					//雲演出オブジェクト登録


	//背景を読み込み0番に登録
	Draw::LoadImage(L"地面TEST.gif", 0, TEX_SIZE_512);

	//戻るアイコンを読み込み1番に登録
	Draw::LoadImage(L"戻る.png", 1, TEX_SIZE_512);

	//兵舎を読み込み2番に登録
	Draw::LoadImage(L"兵舎(仮).jfif", 2, TEX_SIZE_512);

	//研究所を読み込み3番に登録
	Draw::LoadImage(L"研究所.png", 3, TEX_SIZE_512);

	//ミサイル(仮)を読み込み4番に登録
	Draw::LoadImage(L"ミサイル(仮).png", 4, TEX_SIZE_512);

	//住民を読み込み10番に登録
	Draw::LoadImage(L"Human.png", 10, TEX_SIZE_512);

	//雲を読み込み15番に登録
	Draw::LoadImage(L"透過雲.png", 15, TEX_SIZE_512);

	//灰色ウインドウ(仮)を読み込み20番に登録
	Draw::LoadImage(L"灰色ウインドウ(仮).png", 20, TEX_SIZE_512);

	//メッセージウインドウ(仮)を読み込み21番に登録
	Draw::LoadImage(L"メッセージウインドウ(仮).png", 21, TEX_SIZE_512);

	//施設LVUPを読み込み22番に登録
	Draw::LoadImage(L"施設LVUP.png", 22, TEX_SIZE_512);

	//住民振り分けUPを読み込み23番に登録
	Draw::LoadImage(L"兵舎振り分けUP.png", 23, TEX_SIZE_512);

	//住民振り分けDOWNを読み込み24番に登録
	Draw::LoadImage(L"兵舎振り分けDOWN.png", 24, TEX_SIZE_512);

	//ミサイルボタン(仮)を読み込み25番に登録
	Draw::LoadImage(L"ミサイルボタン(仮).png", 25, TEX_SIZE_512);

	//武器ポッドボタン(仮)を読み込み26番に登録
	Draw::LoadImage(L"武器ポッドボタン(仮).png", 26, TEX_SIZE_512);

	//プレイヤー惑星を読み込み50番に登録
	Draw::LoadImage(L"プレイヤー惑星.png", 50, TEX_SIZE_512);
}

//ゲームメイン実行中メソッド
void CSceneTraining::Scene()
{

}