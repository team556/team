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

	//戻るアイコンを読み込み56番に登録
	Draw::LoadImage(L"戻る.png", 56, TEX_SIZE_512);

	//スペシャル技アイコン(敵に大ダメージ)を読み込み57番に登録
	Draw::LoadImage(L"スペシャル技1.png", 57, TEX_SIZE_512);

	//スペシャル技アイコン(一列殺し)を読み込み58番に登録
	Draw::LoadImage(L"スペシャル技2.png", 58, TEX_SIZE_512);

	//スペシャル技アイコン(一定時間無敵)を読み込み59番に登録
	Draw::LoadImage(L"スペシャル技3.png", 59, TEX_SIZE_512);

	//スペシャル技アイコン(生産性効率アップ)を読み込み60番に登録
	Draw::LoadImage(L"スペシャル技4.png", 60, TEX_SIZE_512);

	//スペシャル技アイコン(住民の士気がアップ)を読み込み61番に登録
	Draw::LoadImage(L"スペシャル技5.png", 61, TEX_SIZE_512);

	//スペシャル技選択ウインドウを読み込み62番に登録
	Draw::LoadImage(L"スペシャル技選択ウインドウ(仮).png", 62, TEX_SIZE_512);

	//プレイヤー惑星を読み込み63番に登録
	Draw::LoadImage(L"プレイヤー惑星.png", 63, TEX_SIZE_512);
}

//ゲームメイン実行中メソッド
void CScenePreparation::Scene()
{

}