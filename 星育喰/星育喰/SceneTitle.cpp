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
CSceneTitle::CSceneTitle()
{

}

//デストラクタ
CSceneTitle::~CSceneTitle()
{

}

//ゲーム初期化メソッド
void CSceneTitle::InitScene()
{
	//出力させる文字のグラフィックを作成
	//Font::SetStrTex(L"");

	//タイトルオブジェクト作成
	CObjTitle* obj = new CObjTitle();     //タイトルオブジェクト作成
	Objs::InsertObj(obj, OBJ_TITLE, 10);  //タイトルオブジェクト登録

	//背景を読み込み0番に登録
	Draw::LoadImage(L"背景.png", 0, TEX_SIZE_512);

	//タイトルロゴ
	Draw::LoadImage(L"タイトルロゴ.png", 1, TEX_SIZE_512);

	//ポーズ画面背景を読み込み2番に登録
	Draw::LoadImage(L"ポーズ画面背景.png", 2, TEX_SIZE_512);

	//20,22,24の番号は敵惑星描画で使用しているので使用しないように。

	//プレイヤー惑星Lv1を読み込み50番に登録
	Draw::LoadImage(L"P惑星_Lv1修正.png", 50, TEX_SIZE_512);

	//プレイヤー惑星Lv2を読み込み51番に登録
	//Draw::LoadImage(L"プレイヤー惑星.png", 51, TEX_SIZE_512);

	////プレイヤー惑星Lv3を読み込み52番に登録
	//Draw::LoadImage(L"プレイヤー惑星.png", 52, TEX_SIZE_512);

	//クリックでスタート文字画像を53番に登録
	Draw::LoadImage(L"クリックでスタート.png", 53, TEX_SIZE_512);

	//音楽読み込み
	Audio::LoadAudio(0, L"試練の山.wav", BACK_MUSIC);

	//SE読み込み
	//選択
	Audio::LoadAudio(1, L"選択＆振り分けアップ３.wav", EFFECT);

	////音楽スタート
	Audio::Start(0);

	//float v = Audio::VolumeMaster(0);
	//v = Audio::VolumeMaster((0.0 - v));


}

//ゲームメイン実行中メソッド
void CSceneTitle::Scene()
{

}