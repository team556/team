//STLでバグ機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERTOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"


//使用するネームスペース
using namespace GameL;

//使用ヘッダー
//#include "SceneMain.h"
#include "GameHead.h"

//コンストラクタ
CSceneHome::CSceneHome()
{

}

//デストラクタ
CSceneHome::~CSceneHome()
{

}

//ゲーム初期化メソッド
void CSceneHome::InitScene()
{
	//出力させる文字のグラフィックを作成
	//Font::SetStrTex(L"");

	//タイトルオブジェクト作成
	CObjHome* obj = new CObjHome();     //ホームオブジェクト作成
	Objs::InsertObj(obj, OBJ_HOME, 10);  //ホームオブジェクト登録

	//背景を読み込み0番に登録
	Draw::LoadImage(L"TitleBackgroundTest.jpg", 0, TEX_SIZE_512);

	//育アイコンを読み込み1番に登録
	Draw::LoadImage(L"育TEST.png", 1, TEX_SIZE_512);

	//喰アイコンを読み込み2番に登録
	Draw::LoadImage(L"喰TEST.png", 2, TEX_SIZE_512);

	//プレイヤー惑星を読み込み50番に登録
	Draw::LoadImage(L"Player_Planet_Test.png", 50, TEX_SIZE_512);
}

//ゲームメイン実行中メソッド
void CSceneHome::Scene()
{

}