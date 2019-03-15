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

	//育成画面オブジェクト
	CObjTraining* obj = new CObjTraining();     //育成画面オブジェクト作成
	Objs::InsertObj(obj, OBJ_TRAINING, 10);  //育成画面オブジェクト登録

	//住民オブジェクト
	//for文の中で3~5程度の値をランダムで取得、
	//その値をfor文繰り返しにぶち込み、その数分の住人を生成。
	//ついでに、初期位置もランダムにしたい。
	CObjHuman* obj0 = new CObjHuman(100, 100);	//住民オブジェクト作成
	Objs::InsertObj(obj0, OBJ_HUMAN, 15);		//住民オブジェクト登録

	//施設(仮)オブジェクト							
	//CObjTest* obj1 = new CObjTest(700,300);	//施設(仮)オブジェクト作成
	//Objs::InsertObj(obj1, OBJ_TEST, 20);		//施設(仮)オブジェクト登録

	//雲演出オブジェクト
	CObjCloud_Effect* obj_cloud = new CObjCloud_Effect(false);	//雲演出オブジェクト作成
	Objs::InsertObj(obj_cloud, OBJ_CLOUD, 100);					//雲演出オブジェクト登録

	//背景を読み込み0番に登録
	Draw::LoadImage(L"地面TEST.gif", 0, TEX_SIZE_512);

	//住民を読み込み10番に登録
	Draw::LoadImage(L"Human.png", 10, TEX_SIZE_512);

	//雲を読み込み15番に登録
	Draw::LoadImage(L"雲TEST.png", 15, TEX_SIZE_512);

	//プレイヤー惑星を読み込み50番に登録
	Draw::LoadImage(L"Player_Planet_Test.png", 50, TEX_SIZE_512);
}

//ゲームメイン実行中メソッド
void CSceneTraining::Scene()
{

}