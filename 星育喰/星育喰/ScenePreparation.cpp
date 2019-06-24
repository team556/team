//STLでバグ機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERTOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\Audio.h"


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

	////ヘルプブジェクト
	//CObjHelp* hlp = new CObjHelp(3);     //ヘルプブジェクト作成
	//Objs::InsertObj(hlp, OBJ_HELP, 20);  //ヘルプブジェクト登録

	//背景を読み込み0番に登録
	Draw::LoadImage(L"TitleBackgroundTest.jpg", 0, TEX_SIZE_512);

	//敵惑星1(1ステージ)を読み込み1番に登録
	Draw::LoadImage(L"水惑星.png", 1, TEX_SIZE_512);

	//敵惑星2(1ステージ)を読み込み2番に登録
	Draw::LoadImage(L"レイド1 128x.png", 2, TEX_SIZE_512);

	//敵惑星3(1ステージ)を読み込み3番に登録
	Draw::LoadImage(L"悪☆.png", 3, TEX_SIZE_512);

	//敵惑星4(1ステージ)を読み込み4番に登録
	Draw::LoadImage(L"ぼやけた星.png", 4, TEX_SIZE_512);

	//ボス惑星(1ステージ)を読み込み5番に登録
	Draw::LoadImage(L"パンダ戦闘.png", 5, TEX_SIZE_512);

	//敵惑星1(2ステージ)を読み込み6番に登録
	Draw::LoadImage(L"Enemy_Planet_Test.jpg", 6, TEX_SIZE_512);

	//敵惑星2(2ステージ)を読み込み7番に登録
	Draw::LoadImage(L"Enemy_Planet_Test2.jpg", 7, TEX_SIZE_512);

	//敵惑星3(2ステージ)を読み込み8番に登録
	Draw::LoadImage(L"Enemy_Planet_Test3.jpg", 8, TEX_SIZE_512);

	//敵惑星4(2ステージ)を読み込み9番に登録
	Draw::LoadImage(L"Enemy_Planet_Test4.jpg", 9, TEX_SIZE_512);

	//ボス惑星(2ステージ)を読み込み10番に登録
	Draw::LoadImage(L"プレイヤー惑星Lv1.png", 10, TEX_SIZE_512);

	//敵惑星1(3ステージ)を読み込み11番に登録
	Draw::LoadImage(L"Enemy_Planet_Test.jpg", 11, TEX_SIZE_512);

	//敵惑星2(3ステージ)を読み込み12番に登録
	Draw::LoadImage(L"Enemy_Planet_Test2.jpg", 12, TEX_SIZE_512);

	//敵惑星3(3ステージ)を読み込み13番に登録
	Draw::LoadImage(L"Enemy_Planet_Test3.jpg", 13, TEX_SIZE_512);

	//敵惑星4(3ステージ)を読み込み14番に登録
	Draw::LoadImage(L"Enemy_Planet_Test4.jpg", 14, TEX_SIZE_512);

	//ボス惑星(3ステージ)を読み込み15番に登録
	Draw::LoadImage(L"パンダ顔.png", 15, TEX_SIZE_512);

	//ヘルプボタンを読み込み20番に登録
	Draw::LoadImage(L"ヘルプボタン.png", 20, TEX_SIZE_512);

	//戻るを読み込み21番に登録
	Draw::LoadImage(L"戻る.png", 21, TEX_SIZE_512);

	//ヘルプ画像を読み込み22番に登録
	Draw::LoadImage(L"ヘルプ戦闘準備.png", 22, TEX_SIZE_512);

	//ヘルプ画像を読み込み23番に登録
	Draw::LoadImage(L"ヘルプ戦闘.png", 23, TEX_SIZE_512);
	
	//プレイヤー惑星Lv1を読み込み47番に登録
	Draw::LoadImage(L"プレイヤー惑星.png", 47, TEX_SIZE_512);

	//プレイヤー惑星Lv2を読み込み48番に登録
	Draw::LoadImage(L"プレイヤー惑星.png", 48, TEX_SIZE_512);

	//プレイヤー惑星Lv3を読み込み49番に登録
	Draw::LoadImage(L"プレイヤー惑星.png", 49, TEX_SIZE_512);

	//戦闘画面移行演出(黒星)を読み込み50番に登録
	Draw::LoadImage(L"戦闘画面移行演出(黒星)(仮).png", 50, TEX_SIZE_512);

	//メッセージウインドウを読み込み55番に登録
	Draw::LoadImage(L"メッセージウインドウ(仮).png", 55, TEX_SIZE_512);

	//戻るアイコンを読み込み56番に登録
	Draw::LoadImage(L"戻る.png", 56, TEX_SIZE_512);

	//スペシャル技アイコン(Explosion)を読み込み57番に登録
	Draw::LoadImage(L"スペシャル技1.png", 57, TEX_SIZE_512);

	//スペシャル技アイコン(Fracture_Ray)を読み込み58番に登録
	Draw::LoadImage(L"スペシャル技2.png", 58, TEX_SIZE_512);

	//スペシャル技アイコン(Immortality)を読み込み59番に登録
	Draw::LoadImage(L"スペシャル技3.png", 59, TEX_SIZE_512);

	//スペシャル技アイコン(リミットブレイク)を読み込み60番に登録
	Draw::LoadImage(L"スペシャル技4.png", 60, TEX_SIZE_512);

	//スペシャル技アイコン(ステロイド投与)を読み込み61番に登録
	Draw::LoadImage(L"スペシャル技5.png", 61, TEX_SIZE_512);

	//スペシャル技選択ウインドウを読み込み62番に登録
	Draw::LoadImage(L"スペシャル技選択ウインドウ(仮).png", 62, TEX_SIZE_512);

	//音楽読み込み
	Audio::LoadAudio(0, L"試練の山.wav", BACK_MUSIC);

	//SE読み込み
	//選択
	Audio::LoadAudio(1, L"選択＆振り分けアップ３.wav", EFFECT);

	//戻る
	Audio::LoadAudio(2, L"戻る＆振り分けダウン４.wav", EFFECT);

	////音楽スタート
	Audio::Start(0);
}

//ゲームメイン実行中メソッド
void CScenePreparation::Scene()
{

}