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

	//メッセージ表示(チュートリアル)オブジェクト作成
	if (g_tutorial_progress < 8)
	{
		CObjMessage* message = new CObjMessage(g_tutorial_progress);	//メッセージ表示オブジェクト作成
		Objs::InsertObj(message, OBJ_MESSAGE, 90);	//メッセージ表示オブジェクト登録
	}
	
	////ヘルプオブジェクト
	//CObjHelp* help = new CObjHelp(1);     //ヘルプオブジェクト作成
	//Objs::InsertObj(help, OBJ_HELP, 20);  //ヘルプオブジェクト登録

	//背景を読み込み0番に登録
	Draw::LoadImage(L"img\\背景\\背景.png", 0, TEX_SIZE_512);

	//育アイコンを読み込み1番に登録
	Draw::LoadImage(L"img\\ボタンUI\\育２.png", 1, TEX_SIZE_512);

	//喰アイコンを読み込み2番に登録
	Draw::LoadImage(L"img\\ボタンUI\\喰２.png", 2, TEX_SIZE_512);

	//戻るを読み込み3番に登録
	Draw::LoadImage(L"img\\ボタンUI\\戻る.png", 3, TEX_SIZE_512);

	//ヘルプボタンを読み込み4番に登録
	Draw::LoadImage(L"img\\ボタンUI\\ヘルプボタン.png", 4, TEX_SIZE_512);

	////ヘルプ画像を読み込み5番に登録
	//Draw::LoadImage(L"ヘルプホーム.png", 5, TEX_SIZE_512);

	//メッセージウインドウを読み込み6番に登録
	Draw::LoadImage(L"img\\メッセージウィンドウ\\メッセージウィンドウ.png", 6, TEX_SIZE_512);

	//ウインドウ01を読み込み7番に登録
	Draw::LoadImage(L"img\\メッセージウィンドウ\\ウインドウ01.png", 7, TEX_SIZE_512);

	//ポーズ画面背景(画面暗転用)を読み込み8番に登録
	Draw::LoadImage(L"img\\背景\\ポーズ画面背景.png", 8, TEX_SIZE_512);

	//雲を読み込み15番に登録
	Draw::LoadImage(L"img\\移行演出\\画面移行雲.png", 15, TEX_SIZE_512);

	//20,22,24の番号は敵惑星描画で使用しているので使用しないように。

	//ページを進めるボタンを読み込み46番に登録
	Draw::LoadImage(L"img\\ヘルプ\\ページを進めるボタン.png", 46, TEX_SIZE_512);

	//プレイヤー惑星Lv1を読み込み50番に登録
	Draw::LoadImage(L"img\\惑星\\P惑星_Lv1修正クチナシ.png", 50, TEX_SIZE_512);

	//プレイヤー惑星Lv2を読み込み51番に登録
	Draw::LoadImage(L"img\\惑星\\P惑星_Lv2new.png", 51, TEX_SIZE_512);

	//プレイヤー惑星Lv3を読み込み52番に登録
	Draw::LoadImage(L"img\\惑星\\P惑星_Lv3new.png", 52, TEX_SIZE_512);

	//惑星HP文字画像を読み込み53番に登録
	Draw::LoadImage(L"img\\テキスト\\戦闘準備画面\\惑星HP.png", 53, TEX_SIZE_512);

	//装備中のスペシャル技文字画像を読み込み54番に登録
	Draw::LoadImage(L"img\\テキスト\\スペシャル技\\装備中のスペシャル技.png", 54, TEX_SIZE_512);

	//白文字画像を読み込み121番に登録
	Draw::LoadImage(L"img\\テキスト\\文字集\\白文字集.png", 121, TEX_SIZE_512);
	
	//現在装備中のスペシャル技文字画像全てを読み込む為に、
	//読み込み番号127番を使用しているので使わないように！

	//惑星名を読み込み128番に登録
	Draw::LoadImage(L"img\\テキスト\\戦闘準備画面\\惑星名.png", 128, TEX_SIZE_512);

	//会話矢印を読み込み189番に登録
	Draw::LoadImage(L"img\\ボタンUI\\会話矢印.png", 189, TEX_SIZE_512);

	//戦闘員x10(山田)を読み込み190番に登録
	Draw::LoadImage(L"img\\住民\\戦闘員x10.png", 190, TEX_SIZE_512);

	//矢印画像を読み込み191番に登録
	Draw::LoadImage(L"img\\ボタンUI\\矢印.png", 191, TEX_SIZE_512);

	//音楽読み込み
	Audio::LoadAudio(0, L"BGM\\Home&Title\\試練の山.wav", BACK_MUSIC);

	//SE読み込み
	//選択
	Audio::LoadAudio(1, L"BGM\\効果音育成\\選択＆振り分けアップ３.wav", EFFECT);

	//戻る
	Audio::LoadAudio(2, L"BGM\\効果音育成\\戻る＆振り分けダウン４.wav", EFFECT);

	//音楽スタート
	Audio::Start(0);

}

//ゲームメイン実行中メソッド
void CSceneHome::Scene()
{

}