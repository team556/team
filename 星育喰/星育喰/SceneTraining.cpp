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

	//育成画面オブジェクト作成
	CObjTraining* obj = new CObjTraining();     //育成画面オブジェクト作成
	Objs::InsertObj(obj, OBJ_TRAINING, 10);  //育成画面オブジェクト登録

	 //背景を読み込み0番に登録
	Draw::LoadImage(L"地面TEST.gif", 0, TEX_SIZE_512);

	//雲を読み込み1番に登録
	Draw::LoadImage(L"雲TEST.png", 1, TEX_SIZE_512);

	//プレイヤー惑星を読み込み50番に登録
	Draw::LoadImage(L"Player_Planet_Test.png", 50, TEX_SIZE_512);
}

//ゲームメイン実行中メソッド
void CSceneTraining::Scene()
{

}