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

	//背景を読み込み0番に登録
	Draw::LoadImage(L"TitleBackgroundTest.jpg", 0, TEX_SIZE_512);

	//育アイコンを読み込み1番に登録
	Draw::LoadImage(L"育TEST.png", 1, TEX_SIZE_512);

	//喰アイコンを読み込み2番に登録
	Draw::LoadImage(L"喰TEST.png", 2, TEX_SIZE_512);

	//雲を読み込み15番に登録
	Draw::LoadImage(L"透過雲.png", 15, TEX_SIZE_512);

	//プレイヤー惑星を読み込み50番に登録
	Draw::LoadImage(L"プレイヤー惑星.png", 50, TEX_SIZE_512);

	//音楽読み込み
	//Audio::LoadAudio(0, L"Blue.wav", BACK_MUSIC);
	//Audio::LoadAudio(0, L"Growing.wav", BACK_MUSIC);
	//Audio::LoadAudio(0, L"月夜の晩.wav", BACK_MUSIC);
	//Audio::LoadAudio(0, L"試練の山.wav", BACK_MUSIC);

	//▼5/20に起きた柏崎のパソコンがAudioの読み取り違反で動かなくなるバグ、
	//俺(後庵)のパソコンでも起きたので、以下の処理を一旦コメントアウトしました。
	//※コメントアウト後、正常動作を確認済み
	////バックミュージック
	//float v = Audio::VolumeMaster(0);
	//v = Audio::VolumeMaster((1.0 - v));

	////音楽スタート
	//Audio::Start(0);

}

//ゲームメイン実行中メソッド
void CSceneHome::Scene()
{

}