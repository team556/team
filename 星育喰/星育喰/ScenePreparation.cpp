//STLでバグ機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERTOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"


//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "GameHead.h"

//コンストラクタ
CScenePreparation::CScenePreparation()
{

}

//デストラクタ
CScenePreparation::~CScenePreparation()
{

}

//ゲーム初期化メソッド
void CScenePreparation::InitScene()
{
	//ホームオブジェクト作成
	CObjPreparation* obj = new CObjPreparation();	//戦闘準備画面オブジェクト作成
	Objs::InsertObj(obj, OBJ_PREPARATION, 10);		//戦闘準備画面オブジェクト登録

	//背景を読み込み0番に登録
	Draw::LoadImage(L"TitleBackgroundTest.jpg", 0, TEX_SIZE_512);

	//敵惑星1を読み込み1番に登録
	Draw::LoadImage(L"Enemy_Planet_Test.jpg", 1, TEX_SIZE_512);

	//敵惑星2を読み込み2番に登録
	Draw::LoadImage(L"Enemy_Planet_Test2.jpg", 2, TEX_SIZE_512);

	//敵惑星3を読み込み3番に登録
	Draw::LoadImage(L"Enemy_Planet_Test3.jpg", 3, TEX_SIZE_512);

	//敵惑星4を読み込み4番に登録
	Draw::LoadImage(L"Enemy_Planet_Test4.jpg", 4, TEX_SIZE_512);

	//プレイヤー惑星を読み込み63番に登録
	Draw::LoadImage(L"プレイヤー惑星.png", 63, TEX_SIZE_512);
}

//ゲームメイン実行中メソッド
void CScenePreparation::Scene()
{

}