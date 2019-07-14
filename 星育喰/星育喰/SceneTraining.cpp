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

#include <stdlib.h>
#include <time.h>

//コンストラクタ
CSceneTraining::CSceneTraining()
{

}

//デストラクタ
CSceneTraining::~CSceneTraining()
{

}

//ゲーム初期化メソッド
void CSceneTraining::InitScene()
{
	srand(time(NULL));//ランダム情報を初期化
	
	//▼住民の初期X,Y座標をランダムで取得
	//今は3回ずつの繰り返し回数だが、
	//繰り返し回数は住民数を管理するグローバル変数を基に
	//描画する住民の数分行うように後に変更しておく。

	//Humanの初期X座標取得
	for (int i = 0; i < 3; i++)
	{
		m_ini_hx[i] = rand() % 401 + 400;//400～800の値をランダム取得し、Humanの初期X座標とする。
	}
	//Humanの初期Y座標取得
	for (int i = 0; i < 3; i++)
	{
		m_ini_hy[i] = rand() % 201 + 250;//250～450の値をランダム取得し、Humanの初期Y座標とする。
	}

	//住民オブジェクト
	//今は3回ずつの繰り返し回数だが、
	//繰り返し回数は住民数を管理するグローバル変数を基に
	//描画する住民の数分行うように後に変更しておく。
	for (int i = 0; i < 3; i++)
	{
		CObjHuman* obj_human = new CObjHuman(m_ini_hx[i], m_ini_hy[i], i);	//住民オブジェクト作成
		Objs::InsertObj(obj_human, OBJ_HUMAN, 15);						//住民オブジェクト登録
	}

	
	//育成画面オブジェクト
	CObjTraining* obj = new CObjTraining();     //育成画面オブジェクト作成
	Objs::InsertObj(obj, OBJ_TRAINING, 10);		//育成画面オブジェクト登録

	//兵舎オブジェクト							
	CObjBarracks* obj1 = new CObjBarracks();	//兵舎オブジェクト作成
	Objs::InsertObj(obj1, OBJ_BARRACKS, 20);	//兵舎オブジェクト登録

	//研究所オブジェクト							
	CObjInstitute* obj2 = new CObjInstitute();	//研究所オブジェクト作成
	Objs::InsertObj(obj2, OBJ_INSTITUTE, 20);	//研究所オブジェクト登録

	//雲演出オブジェクト(雲演出OUT)
	CObjCloud_Effect* obj_cloud = new CObjCloud_Effect(false);	//雲演出オブジェクト作成
	Objs::InsertObj(obj_cloud, OBJ_CLOUD, 100);					//雲演出オブジェクト登録

	//倉庫オブジェクト作成
	CObjWarehouse* warehouse = new CObjWarehouse();
	Objs::InsertObj(warehouse, OBJ_WAREHOUSE, 20);

	//ヘルプオブジェクト
	CObjHelp* help = new CObjHelp(2);     //ヘルプオブジェクト作成
	Objs::InsertObj(help, OBJ_HELP, 90);  //ヘルプオブジェクト登録


	//背景Lv1(背景レベル＝プレイヤー惑星レベル)を読み込み0番に登録
	Draw::LoadImage(L"育成画面Lv1.png", 0, TEX_SIZE_512);

	//戻るアイコンを読み込み1番に登録
	Draw::LoadImage(L"戻る.png", 1, TEX_SIZE_512);

	//兵舎Lv1を読み込み2番に登録
	Draw::LoadImage(L"兵舎Lv1.png", 2, TEX_SIZE_512);

	//研究所Lv1を読み込み3番に登録
	Draw::LoadImage(L"研究所Lv.1.png", 3, TEX_SIZE_512);

	//ミサイル(仮)を読み込み4番に登録
	Draw::LoadImage(L"ミサイル.png", 4, TEX_SIZE_512);

	//兵舎Lv2を読み込み5番に登録
	Draw::LoadImage(L"兵舎Lv2.png", 5, TEX_SIZE_512);

	//研究所Lv.2を読み込み6番に登録
	Draw::LoadImage(L"研究所Lv.2.png", 6, TEX_SIZE_512);

	//背景Lv2(背景レベル＝プレイヤー惑星レベル)を読み込み7番に登録
	Draw::LoadImage(L"育成画面Lv2.png", 7, TEX_SIZE_512);

	//兵舎Lv3を読み込み8番に登録
	Draw::LoadImage(L"兵舎Lv3.png", 8, TEX_SIZE_512);

	//研究所Lv.3を読み込み9番に登録
	Draw::LoadImage(L"研究所Lv.3.png", 9, TEX_SIZE_512);

	//住民を読み込み10番に登録
	Draw::LoadImage(L"Human.png", 10, TEX_SIZE_512);

	//ヘルプ画像を読み込み11番に登録
	Draw::LoadImage(L"ヘルプ研究所.png", 11, TEX_SIZE_512);

	//ヘルプ画像を読み込み12番に登録
	Draw::LoadImage(L"ヘルプ倉庫.png", 12, TEX_SIZE_512);

	//ヘルプ画像を読み込み13番に登録
	Draw::LoadImage(L"ヘルプ兵舎.png", 13, TEX_SIZE_512);

	//背景Lv3(背景レベル＝プレイヤー惑星レベル)を読み込み14番に登録
	Draw::LoadImage(L"育成画面Lv3.png", 14, TEX_SIZE_512);
	
	//雲を読み込み15番に登録
	Draw::LoadImage(L"画面移行雲.png", 15, TEX_SIZE_512);

	//プレイヤー惑星Lv1を読み込み16番に登録
	Draw::LoadImage(L"P惑星_Lv1.png", 16, TEX_SIZE_512);

	//プレイヤー惑星Lv2を読み込み17番に登録
	Draw::LoadImage(L"P惑星_Lv2.png", 17, TEX_SIZE_512);

	//プレイヤー惑星Lv3を読み込み18番に登録
	Draw::LoadImage(L"P惑星_Lv3.png", 18, TEX_SIZE_512);

	//ホワイトアウト演出画像を読み込み19番に登録
	Draw::LoadImage(L"ホワイトアウト演出画像.png", 19, TEX_SIZE_512);

	//ウインドウ01を読み込み20番に登録
	Draw::LoadImage(L"ウインドウ01.png", 20, TEX_SIZE_512);

	//メッセージウインドウを読み込み21番に登録
	Draw::LoadImage(L"メッセージウィンドウ.png", 21, TEX_SIZE_512);

	//矢印を読み込み22番に登録
	Draw::LoadImage(L"矢印.png", 22, TEX_SIZE_512);

	//住民振り分けUPを読み込み23番に登録
	Draw::LoadImage(L"戦上01.png", 23, TEX_SIZE_512);

	//住民振り分けDOWNを読み込み24番に登録
	Draw::LoadImage(L"戦下.png", 24, TEX_SIZE_512);

	//ミサイルメニューボタンを読み込み25番に登録
	Draw::LoadImage(L"ミサイルメニューボタン.png", 25, TEX_SIZE_512);

	//ポッドメニューボタンを読み込み26番に登録
	Draw::LoadImage(L"ポッドメニューボタン.png", 26, TEX_SIZE_512);

	//倉庫画像読み込み27番に登録
	Draw::LoadImage(L"倉庫.png", 27, TEX_SIZE_512);

	//資材選択ボタン画像読み込み28番に登録
	Draw::LoadImage(L"資材選択ボタン.png", 28 , TEX_SIZE_512);

	//住民選択ボタン画像読み込み29番に登録
	Draw::LoadImage(L"住民選択ボタン.png", 29, TEX_SIZE_512);

	//スペシャル技選択ボタン画像読み込み30番に登録
	Draw::LoadImage(L"スペシャル技選択ボタン.png", 30, TEX_SIZE_512);

	//装備選択ボタン画像読み込み31番に登録
	Draw::LoadImage(L"装備選択ボタン.png", 31, TEX_SIZE_512);

	//資材ボタン選択後の画面背景画像32番に登録
	Draw::LoadImage(L"w.png", 32 , TEX_SIZE_512);

	//資材(木材)画像33番に登録
	Draw::LoadImage(L"木材.png", 33, TEX_SIZE_512);

	//資材(鉄)画像34番に登録
	Draw::LoadImage(L"鉄.png", 34, TEX_SIZE_512);

	//資材(銀)画像35番に登録
	Draw::LoadImage(L"銀.png", 35, TEX_SIZE_512);

	//資材(プラスチック)画像36番に登録
	Draw::LoadImage(L"プラスチック.png", 36, TEX_SIZE_512);

	//資材(アルミニウム)画像37番に登録
	Draw::LoadImage(L"アルミニウム.png", 37, TEX_SIZE_512);

	//資材(ガス)画像38番に登録
	Draw::LoadImage(L"ガス.png", 38, TEX_SIZE_512);

	////資材(レアメタル)画像39番に登録
	//Draw::LoadImage(L"レアメタル.png", 39, TEX_SIZE_512);

	//スペシャル技1画像40番に登録
	Draw::LoadImage(L"スペシャル技1.png", 40, TEX_SIZE_512);

	//スペシャル技2画像41番に登録
	Draw::LoadImage(L"スペシャル技2.png", 41, TEX_SIZE_512);

	//スペシャル技3画像42番に登録
	Draw::LoadImage(L"スペシャル技3.png", 42, TEX_SIZE_512);

	//スペシャル技4画像43番に登録
	Draw::LoadImage(L"スペシャル技4.png", 43, TEX_SIZE_512);

	//スペシャル技5画像44番に登録
	Draw::LoadImage(L"スペシャル技5.png", 44, TEX_SIZE_512);

	//スペシャル技メッセージウィンドウ画像45番に登録
	Draw::LoadImage(L"スペシャル技メッセージウィンドウ.png", 45, TEX_SIZE_512);

	//ページを進めるボタンを読み込み46番に登録
	Draw::LoadImage(L"ページを進めるボタン(仮).png", 46, TEX_SIZE_512);

	//ヘルプボタンを読み込み47番に登録
	Draw::LoadImage(L"ヘルプボタン.png", 47, TEX_SIZE_512);

	//ヘルプ画像を読み込み48番に登録
	Draw::LoadImage(L"ヘルプ育成画面.png", 48, TEX_SIZE_512);

	//ポッドコア赤Lv1の画像を読み込み49番に登録
	Draw::LoadImage(L"ポッドコア赤Lv1.png", 49, TEX_SIZE_512);

	//ポッドコア赤Lv2の画像を読み込み50番に登録ポッドコア赤Lv2
	Draw::LoadImage(L"ポッドコア赤Lv2.png", 50, TEX_SIZE_512);

	//ポッドコア赤Lv3の画像を読み込み51番に登録
	Draw::LoadImage(L"ポッドコア赤Lv3.png", 51, TEX_SIZE_512);

	//ポッドコア青Lv1の画像を読み込み52番に登録
	Draw::LoadImage(L"ポッドコア青Lv1.png", 52, TEX_SIZE_512);

	//ポッドコア青Lv2の画像を読み込み53番に登録
	Draw::LoadImage(L"ポッドコア青Lv2.png", 53, TEX_SIZE_512);

	//ポッドコア青Lv3の画像を読み込み54番に登録
	Draw::LoadImage(L"ポッドコア青Lv3.png", 54, TEX_SIZE_512);

	//ポッドコア緑Lv1の画像を読み込み55番に登録
	Draw::LoadImage(L"ポッドコア緑Lv1.png", 55, TEX_SIZE_512);

	//ポッドコア緑Lv2の画像を読み込み56番に登録
	Draw::LoadImage(L"ポッドコア緑Lv2.png", 56, TEX_SIZE_512);

	//ポッドコア緑Lv3の画像を読み込み57番に登録
	Draw::LoadImage(L"ポッドコア緑Lv3.png", 57, TEX_SIZE_512);

	//ポッドコア白Lv1の画像を読み込み58番に登録
	Draw::LoadImage(L"ポッドコア白Lv1.png", 58, TEX_SIZE_512);

	//ポッドコア白Lv2の画像を読み込み59番に登録
	Draw::LoadImage(L"ポッドコア白Lv2.png", 59, TEX_SIZE_512);

	//ポッドコア白Lv2の画像を読み込み60番に登録
	Draw::LoadImage(L"ポッドコア白Lv2.png", 60, TEX_SIZE_512);

	//ポッド白Lv1の画像を読み込み61番に登録
	Draw::LoadImage(L"ポッド白Lv1.png", 61, TEX_SIZE_512);

	//ポッド白Lv2の画像を読み込み62番に登録
	Draw::LoadImage(L"ポッド白Lv2.png", 62, TEX_SIZE_512);

	//ポッド白Lv3の画像を読み込み63番に登録
	Draw::LoadImage(L"ポッド白Lv3.png", 63, TEX_SIZE_512);

	//研究所 LV.文字画像を読み込み64番に登録
	Draw::LoadImage(L"研究所 Lv.png",64,TEX_SIZE_512);

	//研究所レベルUP文字画像読み込み65番に登録
	Draw::LoadImage(L"研究所レベルUP.png", 65, TEX_SIZE_512);

	//LvUP条件　所持必要文字画像読み込み66番に登録
	Draw::LoadImage(L"LvUP条件　所持必要.png", 66, TEX_SIZE_512);

	//惑星HP文字画像を読み込み67番に登録
	Draw::LoadImage(L"惑星HP.png", 67, TEX_SIZE_512);

	////50音文字画像読み込み68番に登録
	//Draw::LoadImage(L"", 68, TEX_SIZE_512);

	//鉄文字画像読み込み69番に登録
	Draw::LoadImage(L"鉄文字.png", 69, TEX_SIZE_512);

	//LvUP可能!文字画像読み込み70番に登録
	Draw::LoadImage(L"LvUP可能!.png", 70, TEX_SIZE_512);

	//LvUP不可文字画像読み込み71番に登録
	Draw::LoadImage(L"LvUP不可.png", 71, TEX_SIZE_512);

	//素材消費してレベルアップしますか？文字画像読み込み72番に登録
	Draw::LoadImage(L"素材消費してレベルアップしますか？.png", 72, TEX_SIZE_512);

	//はい文字画像読み込み73番に登録
	Draw::LoadImage(L"はい.png", 73, TEX_SIZE_512);

	//いいえ文字画像読み込み74番に登録
	Draw::LoadImage(L"いいえ.png", 74, TEX_SIZE_512);

	//研究員文字画像を読み込み75番に登録
	Draw::LoadImage(L"研究員.png", 75, TEX_SIZE_512);

	//住民振り分け文字画像読み込み76番に登録
	Draw::LoadImage(L"住民振り分け.png", 76, TEX_SIZE_512);

	//人文字画像読み込み77番に登録
	Draw::LoadImage(L"人.png", 77, TEX_SIZE_512);

	//残り　　　人文字画像読み込み78番に登録
	Draw::LoadImage(L"残り　　　人.png", 78, TEX_SIZE_512);

	//再生産スピード(リキャスト)文字画像読み込み79番に登録
	Draw::LoadImage(L"再生産スピード(リキャスト).png", 79, TEX_SIZE_512);

	//NEXT LV UP文字画像読み込み80番に登録
	Draw::LoadImage(L"NEXT LV UP.png", 80, TEX_SIZE_512);

	//LV. 文字画像読み込み81番に登録
	Draw::LoadImage(L"LV.png", 81, TEX_SIZE_512);

	//レッド文字画像読み込み82番に登録
	Draw::LoadImage(L"レッド.png", 82, TEX_SIZE_512);

	//ブルー文字画像読み込み83番に登録
	Draw::LoadImage(L"ブルー.png", 83, TEX_SIZE_512);

	//グリーン文字画像読み込み84番に登録
	Draw::LoadImage(L"グリーン.png", 84, TEX_SIZE_512);

	//ホワイト文字画像読み込み85番に登録
	Draw::LoadImage(L"ホワイト.png", 85, TEX_SIZE_512);

	//ポッド文字画像読み込み86番に登録
	Draw::LoadImage(L"ポッド.png", 86, TEX_SIZE_512);

	//※研究員は失われません文字画像読み込み87番に登録
	Draw::LoadImage(L"※研究員は失われません.png", 87, TEX_SIZE_512);

	//倉庫文字画像を読み込み88番に登録
	Draw::LoadImage(L"倉庫文字.png", 88, TEX_SIZE_512);

	//木材文字画像を読み込み89番に登録
	Draw::LoadImage(L"木材文字.png", 89, TEX_SIZE_512);

	//銀文字画像を読み込み90番に登録
	Draw::LoadImage(L"銀文字.png", 90, TEX_SIZE_512);

	//プラスチック文字画像を読み込み91番に登録
	Draw::LoadImage(L"プラスチック文字.png", 91, TEX_SIZE_512);

	//アルミニウム文字画像を読み込み92番に登録
	Draw::LoadImage(L"アルミ.png", 92, TEX_SIZE_512);

	//ガス文字画像を読み込み93番に登録
	Draw::LoadImage(L"ガス文字.png", 93, TEX_SIZE_512);

	//残り住民数がいません文字画像を読み込み94番に登録
	Draw::LoadImage(L"残り住民数がいません.png", 94, TEX_SIZE_512);

	//相手の惑星に文字画像を読み込み95番に登録
	Draw::LoadImage(L"相手の惑星に.png", 95, TEX_SIZE_512);

	//固定ダメージを与える文字画像を読み込み96番に登録
	Draw::LoadImage(L"固定ダメージを与える.png", 96, TEX_SIZE_512);

	//選択ライン上の文字画像を読み込み96番に登録
	Draw::LoadImage(L"選択ライン上の.png", 97, TEX_SIZE_512);

	//相手ポッド等を破壊する文字画像を読み込み98番に登録
	Draw::LoadImage(L"相手ポッド等を破壊する.png", 98, TEX_SIZE_512);

	//約10秒間文字画像を読み込み99番に登録
	Draw::LoadImage(L"約10秒間.png", 99, TEX_SIZE_512);

	//無敵となる文字画像を読み込み100番に登録10秒間ポッド生産速度
	Draw::LoadImage(L"無敵となる.png", 100, TEX_SIZE_512);

	//10秒間ポッド生産速度文字画像を読み込み101番に登録
	Draw::LoadImage(L"10秒間ポッド生産速度.png", 101, TEX_SIZE_512);

	//ミサイル生産速度UP文字画像を読み込み102番に登録出撃する
	Draw::LoadImage(L"ミサイル生産速度UP.png", 102, TEX_SIZE_512);

	//出撃する文字画像を読み込み103番に登録
	Draw::LoadImage(L"出撃する.png", 103, TEX_SIZE_512);

	//ポッド5機の攻撃力UP文字画像を読み込み104番に登録
	Draw::LoadImage(L"ポッド5機の攻撃力UP.png", 104, TEX_SIZE_512);

	//未装備の文字画像(装備部分だけ)を読み込み105番に登録
	Draw::LoadImage(L"未装備.png", 105, TEX_SIZE_512);

	//兵舎 Lv文字画像を読み込み116番に登録
	Draw::LoadImage(L"兵舎 Lv.png",116,TEX_SIZE_512);

	//兵舎レベルUP文字画像を読み込み117番に登録
	Draw::LoadImage(L"兵舎レベルUP.png", 117, TEX_SIZE_512);

	//研究所住人UP文字画像を読み込み118番に登録
	Draw::LoadImage(L"研下.png", 118, TEX_SIZE_512);

	//研究所住人UP文字画像を読み込み119番に登録
	Draw::LoadImage(L"研上01.png", 119, TEX_SIZE_512);

	//黒文字画像を読み込み120番に登録
	Draw::LoadImage(L"黒文字集.png", 120, TEX_SIZE_512);

	//白文字画像を読み込み121番に登録
	Draw::LoadImage(L"白文字集.png", 121, TEX_SIZE_512);

	//Sを読み込み122番に登録
	Draw::LoadImage(L"S.png", 122, TEX_SIZE_512);


	


	//簡易メッセージ画像全てを読み込む為に、
	//読み込み番号127番を使用しているので使わないように！


	//音楽読み込み
	Audio::LoadAudio(0, L"きっといい日.wav", BACK_MUSIC);

	//SE読み込み
	//選択
	Audio::LoadAudio(1, L"選択＆振り分けアップ３.wav", EFFECT);

	//戻る
	Audio::LoadAudio(2, L"戻る＆振り分けダウン４.wav", EFFECT);

	//施設レベルアップの音
	Audio::LoadAudio(3, L"施設レベルアップ音.wav", EFFECT);

	//ホワイトアウトの音
	Audio::LoadAudio(4, L"ホワイトアウト音.wav", EFFECT);

	//音楽スタート
	Audio::Start(0);
}

//ゲームメイン実行中メソッド
void CSceneTraining::Scene()
{

}