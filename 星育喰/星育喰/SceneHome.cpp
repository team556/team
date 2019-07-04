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
	//ホームオブジェクト作成
	CObjHome* obj = new CObjHome();     //ホームオブジェクト作成
	Objs::InsertObj(obj, OBJ_HOME, 10);  //ホームオブジェクト登録

	////ヘルプブジェクト
	//CObjHelp* hlp = new CObjHelp(1);     //ヘルプブジェクト作成
	//Objs::InsertObj(hlp, OBJ_HELP, 20);  //ヘルプブジェクト登録

	//背景を読み込み0番に登録
	Draw::LoadImage(L"TitleBackgroundTest.jpg", 0, TEX_SIZE_512);

	//育アイコンを読み込み1番に登録
	Draw::LoadImage(L"育ボタン.png", 1, TEX_SIZE_512);

	//喰アイコンを読み込み2番に登録
	Draw::LoadImage(L"喰ボタン.png", 2, TEX_SIZE_512);

	//ヘルプボタンを読み込み3番に登録
	Draw::LoadImage(L"ヘルプボタン.png", 3, TEX_SIZE_512);

	//戻るを読み込み4番に登録
	Draw::LoadImage(L"戻る.png", 4, TEX_SIZE_512);

	//ヘルプ画像を読み込み5番に登録
	Draw::LoadImage(L"ヘルプホーム.png", 5, TEX_SIZE_512);

	//メッセージウインドウを読み込み6番に登録
	Draw::LoadImage(L"メッセージウインドウ(仮).png", 6, TEX_SIZE_512);

	//雲を読み込み15番に登録
	Draw::LoadImage(L"透過雲.png", 15, TEX_SIZE_512);

	//プレイヤー惑星Lv1を読み込み50番に登録
	Draw::LoadImage(L"プレイヤー惑星.png", 50, TEX_SIZE_512);

	//プレイヤー惑星Lv2を読み込み51番に登録
	Draw::LoadImage(L"プレイヤー惑星.png", 51, TEX_SIZE_512);

	//プレイヤー惑星Lv3を読み込み52番に登録
	Draw::LoadImage(L"プレイヤー惑星.png", 52, TEX_SIZE_512);

	//惑星HP文字画像を読み込み53番に登録
	Draw::LoadImage(L"惑星HP.png", 53, TEX_SIZE_512);

	//装備中のスペシャル技文字画像を読み込み54番に登録
	Draw::LoadImage(L"ミサイル生産速度UP.png", 54, TEX_SIZE_512);//名前を変更してください

	//未装備文字画像を読み込み55番に登録
	Draw::LoadImage(L"装備中.png", 55, TEX_SIZE_512);//名前を変更してください


	//音楽読み込み
	Audio::LoadAudio(0, L"試練の山.wav", BACK_MUSIC);

	//SE読み込み
	//選択
	Audio::LoadAudio(1, L"選択＆振り分けアップ３.wav", EFFECT);

	//戻る
	Audio::LoadAudio(2, L"戻る＆振り分けダウン４.wav", EFFECT);

	//音楽スタート
	Audio::Start(0);

}

//ゲームメイン実行中メソッド
void CSceneHome::Scene()
{

}