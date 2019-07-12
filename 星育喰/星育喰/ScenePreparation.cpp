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

	//ヘルプオブジェクト
	CObjHelp* help = new CObjHelp(3);     //ヘルプオブジェクト作成
	Objs::InsertObj(help, OBJ_HELP, 20);  //ヘルプオブジェクト登録

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

	//戦闘画面移行演出(黒星)を読み込み18番に登録
	Draw::LoadImage(L"戦闘画面移行演出(黒星)(仮).png", 18, TEX_SIZE_512);

	//ヘルプボタンを読み込み21番に登録
	Draw::LoadImage(L"ヘルプボタン.png", 21, TEX_SIZE_512);

	//ヘルプ画像を読み込み22番に登録
	Draw::LoadImage(L"ヘルプ戦闘準備.png", 22, TEX_SIZE_512);

	//ヘルプ画像を読み込み23番に登録
	Draw::LoadImage(L"ヘルプ戦闘.png", 23, TEX_SIZE_512);
	
	//ページを進めるボタンを読み込み46番に登録
	Draw::LoadImage(L"ページを進めるボタン(仮).png", 46, TEX_SIZE_512);

	//プレイヤー惑星Lv1を読み込み47番に登録
	Draw::LoadImage(L"プレイヤー惑星.png", 47, TEX_SIZE_512);

	//プレイヤー惑星Lv2を読み込み48番に登録
	Draw::LoadImage(L"プレイヤー惑星.png", 48, TEX_SIZE_512);

	//プレイヤー惑星Lv3を読み込み49番に登録
	Draw::LoadImage(L"プレイヤー惑星.png", 49, TEX_SIZE_512);

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

	//強大な惑星出現中文字画像読み込み63番に登録
	Draw::LoadImage(L"強大な惑星出現中.png", 63, TEX_SIZE_512);

	//強大な惑星接近まで文字画像読み込み64番に登録
	Draw::LoadImage(L"強大な惑星接近まで.png", 64, TEX_SIZE_512);

	//喰う？文字画像読み込み65番に登録
	Draw::LoadImage(L"喰う？.png", 65, TEX_SIZE_512);

	//はい文字画像読み込み66番に登録
	Draw::LoadImage(L"はい.png", 66, TEX_SIZE_512);

	//いいえ文字画像読み込み67番に登録
	Draw::LoadImage(L"いいえ.png", 67, TEX_SIZE_512);

	//スペシャル技選択文字画像読み込み68番に登録
	Draw::LoadImage(L"スペシャル技選択.png", 68, TEX_SIZE_512);

	//あと3体文字画像読み込み69番に登録
	Draw::LoadImage(L"あと3体.png", 69, TEX_SIZE_512);

	//あと2体文字画像読み込み70番に登録
	Draw::LoadImage(L"あと2体.png", 70, TEX_SIZE_512);

	//あと1体文字画像読み込み71番に登録
	Draw::LoadImage(L"あと1体.png", 71, TEX_SIZE_512);

	//あと0体文字画像読み込み72番に登録
	Draw::LoadImage(L"あと0体.png", 72, TEX_SIZE_512);

	//難易度文字画像読み込み73番に登録367*117
	Draw::LoadImage(L"難易度.png", 73, TEX_SIZE_512);

	//★画像読み込み74番に登録101*107
	Draw::LoadImage(L"★.png", 74, TEX_SIZE_512);

	//取得可能な資材・技文字画像読み込み75番に登録
	Draw::LoadImage(L"取得可能な資材・技文字.png", 75, TEX_SIZE_512);

	//木材50・鉄30文字画像文字画像読み込み76番に登録
	Draw::LoadImage(L"木材50・鉄30文字画像.png", 76, TEX_SIZE_512);

	//フラクチャーレイ文字画像読み込み77番に登録
	Draw::LoadImage(L"取得可能な資材・技文字.png", 77, TEX_SIZE_512);

	//ディフェンス重視文字画像読み込み78番に登録
	Draw::LoadImage(L"ディフェンス重視文字.png", 78, TEX_SIZE_512);

	//鉄70・アルミ80文字画像読み込み79番に登録
	Draw::LoadImage(L"鉄70・アルミ80.png", 79, TEX_SIZE_512);

	//イモータリティ文字画像読み込み80番に登録
	Draw::LoadImage(L"イモータリティ.png", 80, TEX_SIZE_512);

	//スピード重視文字画像読み込み81番に登録
	Draw::LoadImage(L"スピード重視文字.png", 81, TEX_SIZE_512);

	//プラスチック40・ガス50文字画像読み込み82番に登録
	Draw::LoadImage(L"プラスチック40・ガス50.png", 82, TEX_SIZE_512);

	//エクスプロージョン文字画像読み込み83番に登録
	Draw::LoadImage(L"エクスプロージョン.png", 83, TEX_SIZE_512);

	//パワー重視文字画像読み込み84番に登録
	Draw::LoadImage(L"パワー重視文字.png", 84, TEX_SIZE_512);

	////文字画像読み込み85番に登録
	//Draw::LoadImage(L".png", 85, TEX_SIZE_512);

	//リミットブレイク文字画像読み込み86番に登録
	Draw::LoadImage(L"リミットブレイク.png", 86, TEX_SIZE_512);

	//バランス重視文字読み込み87番に登録
	Draw::LoadImage(L"バランス重視文字.png", 87, TEX_SIZE_512);

	//オーバーワーク画像読み込み88番に登録
	Draw::LoadImage(L"パワー重視文字.png", 88, TEX_SIZE_512);

	//音楽読み込み
	Audio::LoadAudio(0, L"試練の山.wav", BACK_MUSIC);

	//▼音楽消したい時はここのコメントアウト外せば音量0の命令となり、消せる。
	//ただし、最後のプッシュ前には必ずコメントアウトし直して音楽流れる状態に戻すように！
	//float v = Audio::VolumeMaster(0);
	//v = Audio::VolumeMaster((0.0 - v));

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