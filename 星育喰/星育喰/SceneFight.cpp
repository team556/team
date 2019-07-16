﻿//STLでバグ機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERTOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL\DrawTexture.h"
#include "GameL\Audio.h"

//使用するネームスペース
using namespace GameL;

//使用ヘッダー
//#include "SceneMain.h"
#include "GameHead.h"



//コンストラクタ
CSceneFight::CSceneFight()
{
	
}

//デストラクタ
CSceneFight::~CSceneFight()
{

}

//ゲーム初期化メソッド
void CSceneFight::InitScene()
{
	//背景を読み込み0番に登録
	Draw::LoadImage(L"TitleBackgroundTest.jpg", 0, TEX_SIZE_512);

	//外部グラフィックを読み込み1番に登録(512×512ピクセル)
	Draw::LoadImage(L"Human.png", 1, TEX_SIZE_512);

	//2番にミサイル登録
	Draw::LoadImage(L"w.png", 2, TEX_SIZE_512);

	//プレイヤー惑星Lv1を読み込み3番に登録
	Draw::LoadImage(L"プレイヤー惑星Lv1 128x.png", 3, TEX_SIZE_512);

	//プレイヤー惑星Lv2を読み込み4番に登録
	Draw::LoadImage(L"プレイヤー惑星Lv1 128x.png", 4, TEX_SIZE_512);

	//プレイヤー惑星Lv3を読み込み5番に登録
	Draw::LoadImage(L"プレイヤー惑星Lv1 128x.png", 5, TEX_SIZE_512);

	//4番に登録惑星
	//Draw::LoadImage(L"プレイヤー惑星第二段階.png", 33, TEX_SIZE_512);

	//5番に登録
	//Draw::LoadImage(L"プレイヤー捕食.png", 5, TEX_SIZE_512);

	//ポッドLv.1を8番に登録
	Draw::LoadImage(L"ポッド1.png", 8, TEX_SIZE_512);

	//ポッドLv.2を9番に登録
	Draw::LoadImage(L"ポッド2.png", 9, TEX_SIZE_512);

	//ポッドLv.3を10番に登録
	Draw::LoadImage(L"ポッド3.png", 10, TEX_SIZE_512);

	//11番に登録
	Draw::LoadImage(L"ポッドボタン赤.png", 11, TEX_SIZE_512);

	//12番に登録
	Draw::LoadImage(L"ポッドボタン青.png", 12, TEX_SIZE_512);

	//13番に登録
	Draw::LoadImage(L"ポッドボタン緑.png", 13, TEX_SIZE_512);

	//14番に登録
	Draw::LoadImage(L"ポッドボタン白.png", 14, TEX_SIZE_512);

	//15番に登録
	Draw::LoadImage(L"ミサイルボタン.png", 15, TEX_SIZE_512);

	//16番に爆発エフェクトを登録
	Draw::LoadImage(L"爆発エフェクト.png", 16, TEX_SIZE_512);

	//17番目に登録
	Draw::LoadImage(L"ミサイル.png", 17, TEX_SIZE_512);

	//戦闘画面移行演出(黒星)を読み込み18番に登録
	Draw::LoadImage(L"戦闘画面移行演出(黒星)(仮).png", 18, TEX_SIZE_512);

	//スペシャル技ボタンを読み込み19番に登録
	Draw::LoadImage(L"スペシャル技ボタン(仮).png", 19, TEX_SIZE_512);

	//ポーズ画面背景を読み込み20番に登録
	Draw::LoadImage(L"ポーズ画面背景.png", 20, TEX_SIZE_512);

	//スペシャル技[Explosion]画像を読み込み21番に登録
	Draw::LoadImage(L"Explosion.png", 21, TEX_SIZE_512);

	//スペシャル技[Fracture_Ray]画像を読み込み22番に登録
	Draw::LoadImage(L"スペシャル技Fracture_Ray.png", 22, TEX_SIZE_512);

	//スペシャル技[Immortality]画像を読み込み23番に登録
	Draw::LoadImage(L"スペシャル技インモータリティ.png", 23, TEX_SIZE_512);

	//スペシャル技[リミットブレイク]画像を読み込み24番に登録
	Draw::LoadImage(L"攻撃力アップ.png", 24, TEX_SIZE_512);

	//スペシャル技[ステロイド投与]画像を読み込み25番に登録
	Draw::LoadImage(L"ステロイド投与.png", 25, TEX_SIZE_512);

	Draw::LoadImage(L"モアイ.png", 26, TEX_SIZE_512);

	Draw::LoadImage(L"レイド1 128x.png", 27, TEX_SIZE_512);

	Draw::LoadImage(L"悪☆.png", 28, TEX_SIZE_512);

	//敵惑星4(1ステージ)を読み込み29番に登録
	Draw::LoadImage(L"ぼやけた星.png", 29, TEX_SIZE_512);

	//ボス星(1ステージ)を読み込み30番に登録
	Draw::LoadImage(L"パンダ戦闘.png", 30, TEX_SIZE_512);

	//人数不足アイコンを読み込み31番に登録
	Draw::LoadImage(L"人数不足.png", 31, TEX_SIZE_512);

	//HPゲージ(リキャストゲージにも使用)を読み込み32番に登録
	Draw::LoadImage(L"HPゲージ.png", 32, TEX_SIZE_512);

	//メッセージウインドウを読み込み33番に登録
	Draw::LoadImage(L"メッセージウインドウ(仮).png", 33, TEX_SIZE_512);

	//汗を読み込み34番に登録
	Draw::LoadImage(L"汗.png", 34, TEX_SIZE_512);

	//ミサイルキーボード用画像
	Draw::LoadImage(L"1選択アイコン.png", 35, TEX_SIZE_512);

	//赤ポッドキーボード用画像
	Draw::LoadImage(L"2選択アイコン.png", 36, TEX_SIZE_512);

	//青ポッドキーボード用画像
	Draw::LoadImage(L"3選択アイコン.png", 37, TEX_SIZE_512);

	//緑キーボード用画像
	Draw::LoadImage(L"4選択アイコン.png", 38, TEX_SIZE_512);

	//灰色キーボード用画像
	Draw::LoadImage(L"5選択アイコン.png", 39, TEX_SIZE_512);

	//スペシャル技キーボード用画像
	Draw::LoadImage(L"s選択アイコン.png", 40, TEX_SIZE_512);

	//白文字のフォントを41番に登録
	Draw::LoadImage(L"白文字集.png", 41, TEX_SIZE_512);

	//スタート！を42番に登録
	Draw::LoadImage(L"スタート！.png", 42, TEX_SIZE_512);

	//プレイヤーを43番に登録
	Draw::LoadImage(L"プレイヤー.png", 43, TEX_SIZE_512);

	//エネミーを44番に登録
	Draw::LoadImage(L"エネミー.png", 44, TEX_SIZE_512);

	//エクスプロージョンを45番に登録
	Draw::LoadImage(L"エクスプロージョン.png", 45, TEX_SIZE_512);

	//フラクチャーレイを46番に登録
	Draw::LoadImage(L"フラクチャーレイ.png", 46, TEX_SIZE_512);

	//イモータリティを47番に登録
	Draw::LoadImage(L"イモータリティ.png", 47, TEX_SIZE_512);

	//オーバーワークを48番に登録
	Draw::LoadImage(L"オーバーワーク.png", 48, TEX_SIZE_512);

	//リミットブレイクを49番に登録
	Draw::LoadImage(L"リミットブレイク.png", 49, TEX_SIZE_512);

	//発動！を50番に登録
	Draw::LoadImage(L"発動！.png", 50, TEX_SIZE_512);

	//クリックでタイトルに戻るを５１番に登録
	Draw::LoadImage(L"クリックでタイトルに戻る.png", 51, TEX_SIZE_512);

	//クリックでホーム画面を52番に登録
	Draw::LoadImage(L"クリックでホーム画面.png", 52, TEX_SIZE_512);

	//捕食成功！を53番に登録
	Draw::LoadImage(L"捕食成功！.png", 53, TEX_SIZE_512);

	//スペシャル技を54番に登録
	Draw::LoadImage(L"スペシャル技.png", 54, TEX_SIZE_512);

	//惑星HPを55番に登録
	Draw::LoadImage(L"惑星HP.png", 55, TEX_SIZE_512);

	//住民を56番に登録
	Draw::LoadImage(L"住民.png", 56, TEX_SIZE_512);

	//作業を57番に登録
	Draw::LoadImage(L"資材.png", 57, TEX_SIZE_512);

	//クリックでタイトルに戻るを５8番に登録
	Draw::LoadImage(L"GAME_OVER.png", 58, TEX_SIZE_512);

	//木材を59番に登録
	Draw::LoadImage(L"木材文字.png", 59, TEX_SIZE_512);

	//鉄を60番に登録
	Draw::LoadImage(L"鉄文字.png", 60, TEX_SIZE_512);

	//銀を61番に登録
	Draw::LoadImage(L"銀文字.png", 61, TEX_SIZE_512);

	//プラスチックを62番に登録
	Draw::LoadImage(L"プラスチック文字.png", 62, TEX_SIZE_512);

	//アルミを63番に登録
	Draw::LoadImage(L"アルミ.png", 63, TEX_SIZE_512);

	//ガスを64番に登録
	Draw::LoadImage(L"ガス文字.png", 64, TEX_SIZE_512);

	////プレイヤー惑星(クリア画面用)を読み込み34番に登録
	//Draw::LoadImage(L"プレイヤー惑星.png", 34, TEX_SIZE_512);

	//出力させる文字のグラフィックを作成
	//Font::SetStrTex(L"");

	//戦闘画面オブジェクト作成
	CObjFight* obj = new CObjFight(10);		//(戦闘時間)
	Objs::InsertObj(obj, OBJ_FIGHT, 1);		//戦闘画面オブジェクト登録

	//敵星オブジェクト作成
	CObjPlanet* obj0 = new CObjPlanet(250, 350, 10);	//オブジェクト作成
	Objs::InsertObj(obj0, OBJ_ENEMY,  5);					//オブジェクト登録

	//自星オブジェクト作成
	CObjPlanet* obj1 = new CObjPlanet(950, 350, g_Player_max_size, -1);	//オブジェクト作成
	Objs::InsertObj(obj1, OBJ_PLANET, 10);					//オブジェクト登録

	//民発射ボタン
	CObjRocketButton* obj2 = new CObjRocketButton(500, 550, 100, 100, 1);	//オブジェクト作成
	Objs::InsertObj(obj2, OBJ_POD_BUTTON1, 10);						//オブジェクト登録

	CObjRocketButton* obj3 = new CObjRocketButton(650, 550, 100, 100, 2);	//オブジェクト作成
	Objs::InsertObj(obj3, OBJ_POD_BUTTON2, 10);						//オブジェクト登録

	CObjRocketButton* obj4 = new CObjRocketButton(800, 550, 100, 100, 3);	//オブジェクト作成
	Objs::InsertObj(obj4, OBJ_POD_BUTTON3, 10);						//オブジェクト登録

	CObjRocketButton* obj5 = new CObjRocketButton(950, 550, 100, 100, 4);	//オブジェクト作成
	Objs::InsertObj(obj5, OBJ_POD_BUTTON4, 10);						//オブジェクト登録

	CObjRocketButton* obj6 = new CObjRocketButton(150, 550, 100, 200, 5);	//オブジェクト作成
	Objs::InsertObj(obj6, OBJ_MISSILE_BUTTON, 10);						//オブジェクト登録

	//スペシャル技ボタン
	CObjSpecialButton* special = new CObjSpecialButton(1000.0f, 20.0f, 114.0f, 175.0f);	//オブジェクト作成
	Objs::InsertObj(special, OBJ_SPECIAL, 90);											//オブジェクト登録

	//戦闘前演出オブジェクト
	CObjBefore_Fight_Effect* before_fight_effect = new CObjBefore_Fight_Effect(false);	//戦闘前演出オブジェクト作成
	Objs::InsertObj(before_fight_effect, OBJ_BEFORE_FIGHT_EFFECT, 100);					//戦闘前演出オブジェクト登録

	//音楽読み込み
	Audio::LoadAudio(0, L"攻防戦.wav", BACK_MUSIC);

	//勝利
	Audio::LoadAudio(1, L"Sunset.wav", BACK_MUSIC);

	//敗北
	Audio::LoadAudio(2, L"過ぎ行く日々.wav", BACK_MUSIC);

	//SE読み込み
	Audio::LoadAudio(3, L"選択＆振り分けアップ３.wav", EFFECT);
	Audio::LoadAudio(5, L"大きい爆発.wav", EFFECT);

	Audio::LoadAudio(6, L"ビーム音１.wav", EFFECT);//Explosion&FractureLay

	Audio::LoadAudio(7, L"バリア２.wav", EFFECT);//Immortality

	Audio::LoadAudio(8, L"ポッドアップ１.wav", EFFECT);//リミットブレイク＆ステロイド投与

	Audio::LoadAudio(9, L"食べる音.wav", EFFECT);

	Audio::LoadAudio(10, L"スぺシャル技発動音.wav", EFFECT);

	//音楽スタート
	Audio::Start(0);

}

//ゲームメイン実行中メソッド
void CSceneFight::Scene()
{

}