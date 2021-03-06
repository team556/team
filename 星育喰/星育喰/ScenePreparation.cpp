﻿//STLでバグ機能をOFFにする
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

	//メッセージ表示(チュートリアル)オブジェクト作成
	if (g_tutorial_progress < 16)
	{
		CObjMessage* message = new CObjMessage(g_tutorial_progress);	//メッセージ表示オブジェクト作成
		Objs::InsertObj(message, OBJ_MESSAGE, 90);	//メッセージ表示オブジェクト登録
	}

	//背景を読み込み0番に登録
	Draw::LoadImage(L"img\\背景\\背景.png", 0, TEX_SIZE_512);

	//敵惑星1(1ステージ)を読み込み1番に登録
	Draw::LoadImage(L"img\\惑星\\lv1x3クチナシ.png", 1, TEX_SIZE_512);

	//敵惑星2(1ステージ)を読み込み2番に登録
	Draw::LoadImage(L"img\\惑星\\モアイ.png", 2, TEX_SIZE_512);

	//敵惑星3(1ステージ)を読み込み3番に登録
	Draw::LoadImage(L"img\\惑星\\悪惑星修正.png", 3, TEX_SIZE_512);

	//敵惑星4(1ステージ)を読み込み4番に登録
	Draw::LoadImage(L"img\\惑星\\lv2x3修正.png", 4, TEX_SIZE_512);

	//ボス惑星(1ステージ)を読み込み5番に登録
	Draw::LoadImage(L"img\\惑星\\lv4x3修正.png", 5, TEX_SIZE_512);

	//チュートリアル惑星を読み込み6番に登録
	Draw::LoadImage(L"img\\惑星\\ボロ.png", 6, TEX_SIZE_512);
	
	//敵惑星1(2ステージ)を読み込み6番に登録
	//Draw::LoadImage(L"Enemy_Planet_Test.jpg", 6, TEX_SIZE_512);

	//敵惑星2(2ステージ)を読み込み7番に登録
	//Draw::LoadImage(L"Enemy_Planet_Test2.jpg", 7, TEX_SIZE_512);

	////敵惑星3(2ステージ)を読み込み8番に登録
	//Draw::LoadImage(L"Enemy_Planet_Test3.jpg", 8, TEX_SIZE_512);

	////敵惑星4(2ステージ)を読み込み9番に登録
	//Draw::LoadImage(L"Enemy_Planet_Test4.jpg", 9, TEX_SIZE_512);

	////ボス惑星(2ステージ)を読み込み10番に登録
	//Draw::LoadImage(L"プレイヤー惑星Lv1.png", 10, TEX_SIZE_512);

	////敵惑星1(3ステージ)を読み込み11番に登録
	//Draw::LoadImage(L"Enemy_Planet_Test.jpg", 11, TEX_SIZE_512);

	////敵惑星2(3ステージ)を読み込み12番に登録
	//Draw::LoadImage(L"Enemy_Planet_Test2.jpg", 12, TEX_SIZE_512);

	////敵惑星3(3ステージ)を読み込み13番に登録
	//Draw::LoadImage(L"Enemy_Planet_Test3.jpg", 13, TEX_SIZE_512);

	////敵惑星4(3ステージ)を読み込み14番に登録
	//Draw::LoadImage(L"Enemy_Planet_Test4.jpg", 14, TEX_SIZE_512);

	////ボス惑星(3ステージ)を読み込み15番に登録
	//Draw::LoadImage(L"パンダ顔.png", 15, TEX_SIZE_512);

	//雲を読み込み15番に登録
	Draw::LoadImage(L"img\\移行演出\\画面移行雲.png", 15, TEX_SIZE_512);

	//戦闘画面移行演出(黒星)を読み込み18番に登録
	Draw::LoadImage(L"img\\戦闘画面\\戦闘画面移行演出(黒星)(仮).png", 18, TEX_SIZE_512);

	////ヘルプボタンを読み込み21番に登録
	//Draw::LoadImage(L"ヘルプボタン.png", 21, TEX_SIZE_512);

	////ヘルプ画像を読み込み22番に登録
	//Draw::LoadImage(L"ヘルプ戦闘準備.png", 22, TEX_SIZE_512);

	////ヘルプ画像を読み込み23番に登録
	//Draw::LoadImage(L"ヘルプ戦闘.png", 23, TEX_SIZE_512);
	
	//ページを進めるボタンを読み込み46番に登録
	Draw::LoadImage(L"img\\ヘルプ\\ページを進めるボタン.png", 46, TEX_SIZE_512);

	//プレイヤー惑星Lv1を読み込み47番に登録
	Draw::LoadImage(L"img\\惑星\\P惑星_Lv1修正クチナシ.png", 47, TEX_SIZE_512);

	//プレイヤー惑星Lv2を読み込み48番に登録
	Draw::LoadImage(L"img\\惑星\\P惑星_Lv2new.png", 48, TEX_SIZE_512);

	//プレイヤー惑星Lv3を読み込み49番に登録
	Draw::LoadImage(L"img\\惑星\\P惑星_Lv3new.png", 49, TEX_SIZE_512);

	//メッセージウインドウを読み込み55番に登録
	Draw::LoadImage(L"img\\メッセージウィンドウ\\メッセージウィンドウ.png", 55, TEX_SIZE_512);

	//戻るアイコンを読み込み56番に登録
	Draw::LoadImage(L"img\\ボタンUI\\戻る.png", 56, TEX_SIZE_512);

	//スペシャル技アイコン(Explosion)を読み込み57番に登録
	Draw::LoadImage(L"img\\ボタンUI\\スペシャル技1.png", 57, TEX_SIZE_512);

	//スペシャル技アイコン(Fracture_Ray)を読み込み58番に登録
	Draw::LoadImage(L"img\\ボタンUI\\スペシャル技2.png", 58, TEX_SIZE_512);

	//スペシャル技アイコン(Immortality)を読み込み59番に登録
	Draw::LoadImage(L"img\\ボタンUI\\スペシャル技3.png", 59, TEX_SIZE_512);

	//スペシャル技アイコン(リミットブレイク)を読み込み60番に登録
	Draw::LoadImage(L"img\\ボタンUI\\スペシャル技4.png", 60, TEX_SIZE_512);

	//スペシャル技アイコン(ステロイド投与)を読み込み61番に登録
	Draw::LoadImage(L"img\\ボタンUI\\スペシャル技5.png", 61, TEX_SIZE_512);

	//スペシャル技選択ウインドウを読み込み62番に登録
	Draw::LoadImage(L"img\\メッセージウィンドウ\\スペシャル技選択ウインドウ(仮).png", 62, TEX_SIZE_512);

	//強大な惑星出現中文字画像読み込み63番に登録
	Draw::LoadImage(L"img\\テキスト\\戦闘準備画面\\強大な惑星出現中.png", 63, TEX_SIZE_512);

	//強大な惑星接近まで文字画像読み込み64番に登録
	Draw::LoadImage(L"img\\テキスト\\戦闘準備画面\\強大な惑星接近まで.png", 64, TEX_SIZE_512);

	//喰う？文字画像読み込み65番に登録
	Draw::LoadImage(L"img\\テキスト\\戦闘準備画面\\喰う？.png", 65, TEX_SIZE_512);

	//はい文字画像読み込み66番に登録
	Draw::LoadImage(L"img\\テキスト\\よく使われる画像\\はい.png", 66, TEX_SIZE_512);

	//いいえ文字画像読み込み67番に登録
	Draw::LoadImage(L"img\\テキスト\\よく使われる画像\\いいえ.png", 67, TEX_SIZE_512);

	//スペシャル技選択文字画像読み込み68番に登録
	Draw::LoadImage(L"img\\テキスト\\戦闘準備画面\\スペシャル技選択.png", 68, TEX_SIZE_512);

	//あと3体文字画像読み込み69番に登録
	Draw::LoadImage(L"img\\テキスト\\戦闘準備画面\\あと3体.png", 69, TEX_SIZE_512);

	//あと2体文字画像読み込み70番に登録
	Draw::LoadImage(L"img\\テキスト\\戦闘準備画面\\あと2体.png", 70, TEX_SIZE_512);

	//あと1体文字画像読み込み71番に登録
	Draw::LoadImage(L"img\\テキスト\\戦闘準備画面\\あと1体.png", 71, TEX_SIZE_512);

	//あと0体文字画像読み込み72番に登録
	Draw::LoadImage(L"img\\テキスト\\戦闘準備画面\\あと0体.png", 72, TEX_SIZE_512);

	//★画像読み込み73番に登録
	Draw::LoadImage(L"img\\移行演出\\★.png", 73, TEX_SIZE_512);

	//測定不能文字画像74番に登録
	Draw::LoadImage(L"img\\テキスト\\戦闘準備画面\\測定不能.png", 74, TEX_SIZE_512);

	//ボロボロン文字画像75番に登録
	Draw::LoadImage(L"img\\テキスト\\惑星\\ボロボロン.png", 75, TEX_SIZE_512);

	//O阪魂文字画像76番に登録
	Draw::LoadImage(L"img\\テキスト\\惑星\\O阪魂.png", 76, TEX_SIZE_512);

	//再星文字画像77番に登録
	Draw::LoadImage(L"img\\テキスト\\惑星\\再星.png", 77, TEX_SIZE_512);

	//アモイ文字画像78番に登録
	Draw::LoadImage(L"img\\テキスト\\惑星\\アモイ.png", 78, TEX_SIZE_512);

	//コワモーテ文字画像79番に登録
	Draw::LoadImage(L"img\\テキスト\\惑星\\コワモーテ.png", 79, TEX_SIZE_512);

	//アマテラス文字画像80番に登録
	Draw::LoadImage(L"img\\テキスト\\惑星\\アマテラス.png", 80, TEX_SIZE_512);

	//ウィンドウ画像89番に登録
	Draw::LoadImage(L"img\\メッセージウィンドウ\\ウインドウ01.png", 89, TEX_SIZE_512);

	//メッセージウィンドウ01画像90番に登録
	Draw::LoadImage(L"img\\メッセージウィンドウ\\メッセージウィンドウ01.png", 90, TEX_SIZE_512);

	//ポーズ画面背景(画面暗転用)を読み込み91番に登録
	Draw::LoadImage(L"img\\背景\\ポーズ画面背景.png", 91, TEX_SIZE_512);

	//白文字画像を読み込み121番に登録
	Draw::LoadImage(L"img\\テキスト\\文字集\\白文字集.png", 121, TEX_SIZE_512);

	//詳細説明画像を読み込む為に、
	//読み込み番号122～127番を使用しているので
	//この番号は使わないように！

	//モアイ正面画像を読み込み128番に登録
	Draw::LoadImage(L"img\\惑星\\モアイ正面.png", 128, TEX_SIZE_512);

	//ヘルプボタンを読み込み129番に登録
	Draw::LoadImage(L"img\\ボタンUI\\ヘルプボタン.png", 129, TEX_SIZE_512);

	//説明文準備画面を読み込み130番に登録
	Draw::LoadImage(L"img\\ヘルプ\\説明文準備画面.png", 130, TEX_SIZE_512);

	//説明文戦闘1を読み込み131番に登録
	Draw::LoadImage(L"img\\ヘルプ\\説明文戦闘1.png", 131, TEX_SIZE_512);

	//説明文戦闘2を読み込み130番に登録
	Draw::LoadImage(L"img\\ヘルプ\\説明文戦闘2.png", 132, TEX_SIZE_512);

	//説明文スペシャル技を読み込み130番に登録
	Draw::LoadImage(L"img\\ヘルプ\\説明文スペシャル技.png", 133, TEX_SIZE_512);

	//説明文三竦みを読み込み130番に登録
	Draw::LoadImage(L"img\\ヘルプ\\説明文三竦み.png", 134, TEX_SIZE_512);

	//説明文戦闘デメリットを読み込み130番に登録
	Draw::LoadImage(L"img\\ヘルプ\\説明文戦闘デメリット.png", 135, TEX_SIZE_512);

	//説明文ポッドの爆発を読み込み130番に登録
	Draw::LoadImage(L"img\\ヘルプ\\説明文ポッドの爆発.png", 136, TEX_SIZE_512);

	//説明文惑星HPを読み込み130番に登録
	Draw::LoadImage(L"img\\ヘルプ\\説明文惑星HP.png", 137, TEX_SIZE_512);

	//ＥＸを読み込み187番に登録
	Draw::LoadImage(L"img\\テキスト\\戦闘準備画面\\EX.png", 187, TEX_SIZE_512);

	//育アイコンを読み込み188番に登録
	Draw::LoadImage(L"img\\ボタンUI\\育２.png", 188, TEX_SIZE_512);

	//会話矢印を読み込み189番に登録
	Draw::LoadImage(L"img\\ボタンUI\\会話矢印.png", 189, TEX_SIZE_512);

	//戦闘員x10(山田)を読み込み190番に登録
	Draw::LoadImage(L"img\\住民\\戦闘員x10.png", 190, TEX_SIZE_512);

	//矢印画像を読み込み191番に登録
	Draw::LoadImage(L"img\\ボタンUI\\矢印.png", 191, TEX_SIZE_512);

	//float v = Audio::VolumeMaster(0);
	//v = Audio::VolumeMaster((0.0 - v));

	//音楽読み込み
	Audio::LoadAudio(0, L"BGM\\Home&Title\\試練の山.wav", BACK_MUSIC);

	//SE読み込み
	//選択
	Audio::LoadAudio(1, L"BGM\\効果音育成\\選択＆振り分けアップ３.wav", EFFECT);

	//戻る
	Audio::LoadAudio(2, L"BGM\\効果音育成\\戻る＆振り分けダウン４.wav", EFFECT);

	////音楽スタート
	Audio::Start(0);
}

//ゲームメイン実行中メソッド
void CScenePreparation::Scene()
{

}