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
	//srand(time(NULL));//ランダム情報を初期化
	//
	////▼住民の初期X,Y座標をランダムで取得
	////今は3回ずつの繰り返し回数だが、
	////繰り返し回数は住民数を管理するグローバル変数を基に
	////描画する住民の数分行うように後に変更しておく。

	////Humanの初期X座標取得
	//for (int i = 0; i < 3; i++)
	//{
	//	m_ini_hx[i] = rand() % 401 + 400;//400〜800の値をランダム取得し、Humanの初期X座標とする。
	//}
	////Humanの初期Y座標取得
	//for (int i = 0; i < 3; i++)
	//{
	//	m_ini_hy[i] = rand() % 201 + 250;//250〜450の値をランダム取得し、Humanの初期Y座標とする。
	//}

	//住民オブジェクト
	//今は3回ずつの繰り返し回数だが、
	//繰り返し回数は住民数を管理するグローバル変数を基に
	//描画する住民の数分行うように後に変更しておく。
	//for (int i = 0; i < 3; i++)
	//{
	//	CObjHuman* obj_human = new CObjHuman(m_ini_hx[i], m_ini_hy[i], i);	//住民オブジェクト作成
	//	Objs::InsertObj(obj_human, OBJ_HUMAN, 15);						//住民オブジェクト登録
	//}

	
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

	//メッセージ表示(チュートリアル)オブジェクト作成
	if (g_tutorial_progress < 14)
	{
		CObjMessage* message = new CObjMessage(g_tutorial_progress);	//メッセージ表示オブジェクト作成
		Objs::InsertObj(message, OBJ_MESSAGE, 95);	//メッセージ表示オブジェクト登録
	}


	//背景Lv1(背景レベル＝プレイヤー惑星レベル)を読み込み0番に登録
	Draw::LoadImage(L"img\\背景\\育成画面Lv1.png", 0, TEX_SIZE_512);

	//戻るアイコンを読み込み1番に登録
	Draw::LoadImage(L"img\\ボタンUI\\戻る.png", 1, TEX_SIZE_512);

	//兵舎Lv1を読み込み2番に登録
	Draw::LoadImage(L"img\\育成画面\\兵舎Lv1.png", 2, TEX_SIZE_512);

	//研究所Lv1を読み込み3番に登録
	Draw::LoadImage(L"img\\育成画面\\研究所Lv.1.png", 3, TEX_SIZE_512);

	//ミサイル(仮)を読み込み4番に登録
	Draw::LoadImage(L"img\\ポッド\\ミサイル.png", 4, TEX_SIZE_512);

	//兵舎Lv2を読み込み5番に登録
	Draw::LoadImage(L"img\\育成画面\\兵舎Lv2.png", 5, TEX_SIZE_512);

	//研究所Lv.2を読み込み6番に登録
	Draw::LoadImage(L"img\\育成画面\\研究所Lv.2.png", 6, TEX_SIZE_512);

	//背景Lv2(背景レベル＝プレイヤー惑星レベル)を読み込み7番に登録
	Draw::LoadImage(L"img\\背景\\育成画面Lv2.png", 7, TEX_SIZE_512);

	//兵舎Lv3を読み込み8番に登録
	Draw::LoadImage(L"img\\育成画面\\兵舎Lv3.png", 8, TEX_SIZE_512);

	//研究所Lv.3を読み込み9番に登録
	Draw::LoadImage(L"img\\育成画面\\研究所Lv.3.png", 9, TEX_SIZE_512);

	////住民を読み込み10番に登録
	//Draw::LoadImage(L"Human.png", 10, TEX_SIZE_512);

	////ヘルプ画像を読み込み11番に登録
	//Draw::LoadImage(L"ヘルプ研究所.png", 11, TEX_SIZE_512);

	////ヘルプ画像を読み込み12番に登録
	//Draw::LoadImage(L"ヘルプ倉庫.png", 12, TEX_SIZE_512);

	////ヘルプ画像を読み込み13番に登録
	//Draw::LoadImage(L"ヘルプ兵舎.png", 13, TEX_SIZE_512);

	//背景Lv3(背景レベル＝プレイヤー惑星レベル)を読み込み14番に登録
	Draw::LoadImage(L"img\\背景\\育成画面Lv3.png", 14, TEX_SIZE_512);
	
	//雲を読み込み15番に登録
	Draw::LoadImage(L"img\\移行演出\\画面移行雲.png", 15, TEX_SIZE_512);

	//プレイヤー惑星Lv1を読み込み16番に登録
	Draw::LoadImage(L"img\\惑星\\P惑星_Lv1修正クチナシ.png", 16, TEX_SIZE_512);

	//プレイヤー惑星Lv2を読み込み17番に登録
	Draw::LoadImage(L"img\\惑星\\P惑星_Lv2new.png", 17, TEX_SIZE_512);

	//プレイヤー惑星Lv3を読み込み18番に登録
	Draw::LoadImage(L"img\\惑星\\P惑星_Lv3new.png", 18, TEX_SIZE_512);

	//ホワイトアウト演出画像を読み込み19番に登録
	Draw::LoadImage(L"img\\背景\\ホワイトアウト演出画像.png", 19, TEX_SIZE_512);

	//ウインドウ01を読み込み20番に登録
	Draw::LoadImage(L"img\\メッセージウィンドウ\\ウインドウ01.png", 20, TEX_SIZE_512);

	//メッセージウインドウを読み込み21番に登録
	Draw::LoadImage(L"img\\メッセージウィンドウ\\メッセージウィンドウ.png", 21, TEX_SIZE_512);

	//矢印を読み込み22番に登録
	Draw::LoadImage(L"img\\ボタンUI\\レベルアップ.png", 22, TEX_SIZE_512);

	//住民振り分けUPを読み込み23番に登録
	Draw::LoadImage(L"img\\ボタンUI\\戦上01.png", 23, TEX_SIZE_512);

	//住民振り分けDOWNを読み込み24番に登録
	Draw::LoadImage(L"img\\ボタンUI\\戦下.png", 24, TEX_SIZE_512);

	//ミサイルメニューボタンを読み込み25番に登録
	Draw::LoadImage(L"img\\ボタンUI\\ミサイルメニューボタン.png", 25, TEX_SIZE_512);

	//ポッドメニューボタンを読み込み26番に登録
	Draw::LoadImage(L"img\\ボタンUI\\ポッドメニューボタン.png", 26, TEX_SIZE_512);

	//倉庫画像読み込み27番に登録
	Draw::LoadImage(L"img\\育成画面\\倉庫.png", 27, TEX_SIZE_512);

	//資材ボタン画像読み込み28番に登録
	Draw::LoadImage(L"img\\ボタンUI\\資材ボタン.png", 28 , TEX_SIZE_512);

	//住民ボタン画像読み込み29番に登録
	Draw::LoadImage(L"img\\ボタンUI\\住民ボタン.png", 29, TEX_SIZE_512);

	//スペシャル技ボタン画像読み込み30番に登録
	Draw::LoadImage(L"img\\ボタンUI\\スペシャルボタン.png", 30, TEX_SIZE_512);

	//装備ボタン画像読み込み31番に登録
	Draw::LoadImage(L"img\\ボタンUI\\ポッドボタン.png", 31, TEX_SIZE_512);

	//資材ボタン後の画面背景画像32番に登録
	Draw::LoadImage(L"img\\背景\\w.png", 32 , TEX_SIZE_512);

	//資材(木材)画像33番に登録
	Draw::LoadImage(L"img\\資材\\木材.png", 33, TEX_SIZE_512);

	//資材(鉄)画像34番に登録
	Draw::LoadImage(L"img\\資材\\鉄.png", 34, TEX_SIZE_512);

	//資材(銀)画像35番に登録
	Draw::LoadImage(L"img\\資材\\銀.png", 35, TEX_SIZE_512);

	//資材(プラスチック)画像36番に登録
	Draw::LoadImage(L"img\\資材\\プラスチック.png", 36, TEX_SIZE_512);

	//資材(アルミニウム)画像37番に登録
	Draw::LoadImage(L"img\\資材\\アルミニウム.png", 37, TEX_SIZE_512);

	//資材(ガス)画像38番に登録
	Draw::LoadImage(L"img\\資材\\ガス.png", 38, TEX_SIZE_512);

	////資材(レアメタル)画像39番に登録
	//Draw::LoadImage(L"レアメタル.png", 39, TEX_SIZE_512);

	//スペシャル技1画像40番に登録
	Draw::LoadImage(L"img\\ボタンUI\\スペシャル技1.png", 40, TEX_SIZE_512);

	//スペシャル技2画像41番に登録
	Draw::LoadImage(L"img\\ボタンUI\\スペシャル技2.png", 41, TEX_SIZE_512);

	//スペシャル技3画像42番に登録
	Draw::LoadImage(L"img\\ボタンUI\\スペシャル技3.png", 42, TEX_SIZE_512);

	//スペシャル技4画像43番に登録
	Draw::LoadImage(L"img\\ボタンUI\\スペシャル技4.png", 43, TEX_SIZE_512);

	//スペシャル技5画像44番に登録
	Draw::LoadImage(L"img\\ボタンUI\\スペシャル技5.png", 44, TEX_SIZE_512);

	//スペシャル技メッセージウィンドウ画像45番に登録
	Draw::LoadImage(L"img\\メッセージウィンドウ\\スペシャル技メッセージウィンドウ.png", 45, TEX_SIZE_512);

	//ページを進めるボタンを読み込み46番に登録
	Draw::LoadImage(L"img\\ヘルプ\\ページを進めるボタン.png", 46, TEX_SIZE_512);

	////ヘルプボタンを読み込み47番に登録
	//Draw::LoadImage(L"ヘルプボタン.png", 47, TEX_SIZE_512);

	////ヘルプ画像を読み込み48番に登録
	//Draw::LoadImage(L"ヘルプ育成画面.png", 48, TEX_SIZE_512);

	//ポッドコア赤Lv1の画像を読み込み49番に登録
	Draw::LoadImage(L"img\\ポッド\\ポッドコア赤Lv1.png", 49, TEX_SIZE_512);

	//ポッドコア赤Lv2の画像を読み込み50番に登録ポッドコア赤Lv2
	Draw::LoadImage(L"img\\ポッド\\ポッドコア赤Lv2.png", 50, TEX_SIZE_512);

	//ポッドコア赤Lv3の画像を読み込み51番に登録
	Draw::LoadImage(L"img\\ポッド\\ポッドコア赤Lv3.png", 51, TEX_SIZE_512);

	//ポッドコア青Lv1の画像を読み込み52番に登録
	Draw::LoadImage(L"img\\ポッド\\ポッドコア青Lv1.png", 52, TEX_SIZE_512);

	//ポッドコア青Lv2の画像を読み込み53番に登録
	Draw::LoadImage(L"img\\ポッド\\ポッドコア青Lv2.png", 53, TEX_SIZE_512);

	//ポッドコア青Lv3の画像を読み込み54番に登録
	Draw::LoadImage(L"img\\ポッド\\ポッドコア青Lv3.png", 54, TEX_SIZE_512);

	//ポッドコア緑Lv1の画像を読み込み55番に登録
	Draw::LoadImage(L"img\\ポッド\\ポッドコア緑Lv1.png", 55, TEX_SIZE_512);

	//ポッドコア緑Lv2の画像を読み込み56番に登録
	Draw::LoadImage(L"img\\ポッド\\ポッドコア緑Lv2.png", 56, TEX_SIZE_512);

	//ポッドコア緑Lv3の画像を読み込み57番に登録
	Draw::LoadImage(L"img\\ポッド\\ポッドコア緑Lv3.png", 57, TEX_SIZE_512);

	//ポッドコア白Lv1の画像を読み込み58番に登録
	Draw::LoadImage(L"img\\ポッド\\ポッドコア白Lv1.png", 58, TEX_SIZE_512);

	//ポッドコア白Lv2の画像を読み込み59番に登録
	Draw::LoadImage(L"img\\ポッド\\ポッドコア白Lv2.png", 59, TEX_SIZE_512);

	//ポッドコア白Lv3の画像を読み込み60番に登録
	Draw::LoadImage(L"img\\ポッド\\ポッドコア白Lv3.png", 60, TEX_SIZE_512);

	//ポッド白Lv1の画像を読み込み61番に登録
	Draw::LoadImage(L"img\\ポッド\\ポッド白Lv1.png", 61, TEX_SIZE_512);

	//ポッド白Lv2の画像を読み込み62番に登録
	Draw::LoadImage(L"img\\ポッド\\ポッド白Lv2.png", 62, TEX_SIZE_512);

	//ポッド白Lv3の画像を読み込み63番に登録
	Draw::LoadImage(L"img\\ポッド\\ポッド白Lv3.png", 63, TEX_SIZE_512);

	//研究所 LV.文字画像を読み込み64番に登録
	Draw::LoadImage(L"img\\テキスト\\育成画面\\研究所 Lv.png",64,TEX_SIZE_512);

	//研究所レベルUP文字画像読み込み65番に登録
	Draw::LoadImage(L"img\\テキスト\\育成画面\\研究所レベルUP.png", 65, TEX_SIZE_512);

	//LvUP条件　所持必要文字画像読み込み66番に登録
	Draw::LoadImage(L"img\\テキスト\\育成画面\\LvUP条件　所持必要.png", 66, TEX_SIZE_512);

	//惑星HP文字画像を読み込み67番に登録
	Draw::LoadImage(L"img\\テキスト\\戦闘準備画面\\惑星HP.png", 67, TEX_SIZE_512);

	////50音文字画像読み込み68番に登録
	//Draw::LoadImage(L"", 68, TEX_SIZE_512);

	//鉄文字画像読み込み69番に登録
	Draw::LoadImage(L"img\\テキスト\\素材\\鉄文字.png", 69, TEX_SIZE_512);

	//LvUP可能!文字画像読み込み70番に登録
	Draw::LoadImage(L"img\\テキスト\\育成画面\\LvUP可能!.png", 70, TEX_SIZE_512);

	//LvUP不可文字画像読み込み71番に登録
	Draw::LoadImage(L"img\\テキスト\\育成画面\\LvUP不可.png", 71, TEX_SIZE_512);

	//素材消費してレベルアップしますか？文字画像読み込み72番に登録
	Draw::LoadImage(L"img\\テキスト\\育成画面\\素材消費してレベルアップしますか？.png", 72, TEX_SIZE_512);

	//はい文字画像読み込み73番に登録
	Draw::LoadImage(L"img\\テキスト\\よく使われる画像\\はい.png", 73, TEX_SIZE_512);

	//いいえ文字画像読み込み74番に登録
	Draw::LoadImage(L"img\\テキスト\\よく使われる画像\\いいえ.png", 74, TEX_SIZE_512);

	//研究員文字画像を読み込み75番に登録
	Draw::LoadImage(L"img\\テキスト\\育成画面\\研究員.png", 75, TEX_SIZE_512);

	//住民振り分け文字画像読み込み76番に登録
	Draw::LoadImage(L"img\\テキスト\\育成画面\\住民振り分け.png", 76, TEX_SIZE_512);

	//人文字画像読み込み77番に登録
	Draw::LoadImage(L"img\\テキスト\\育成画面\\人.png", 77, TEX_SIZE_512);

	//残り　　　人文字画像読み込み78番に登録
	Draw::LoadImage(L"img\\テキスト\\育成画面\\残り　　　人.png", 78, TEX_SIZE_512);

	//再生産スピード(リキャスト)文字画像読み込み79番に登録
	Draw::LoadImage(L"img\\テキスト\\育成画面\\再生産スピード(リキャスト).png", 79, TEX_SIZE_512);

	//NEXT LV UP文字画像読み込み80番に登録
	Draw::LoadImage(L"img\\テキスト\\育成画面\\NEXT LV UP.png", 80, TEX_SIZE_512);

	//LV. 文字画像読み込み81番に登録
	Draw::LoadImage(L"img\\テキスト\\育成画面\\Lv.png", 81, TEX_SIZE_512);

	//レッド文字画像読み込み82番に登録
	Draw::LoadImage(L"img\\テキスト\\育成画面\\レッド.png", 82, TEX_SIZE_512);

	//ブルー文字画像読み込み83番に登録
	Draw::LoadImage(L"img\\テキスト\\育成画面\\ブルー.png", 83, TEX_SIZE_512);

	//グリーン文字画像読み込み84番に登録
	Draw::LoadImage(L"img\\テキスト\\育成画面\\グリーン.png", 84, TEX_SIZE_512);

	//ホワイト文字画像読み込み85番に登録
	Draw::LoadImage(L"img\\テキスト\\育成画面\\ホワイト.png", 85, TEX_SIZE_512);

	//ポッド文字画像読み込み86番に登録
	Draw::LoadImage(L"img\\テキスト\\育成画面\\ポッド.png", 86, TEX_SIZE_512);

	//※研究員は失われません文字画像読み込み87番に登録
	Draw::LoadImage(L"img\\テキスト\\育成画面\\※研究員は失われません.png", 87, TEX_SIZE_512);

	//倉庫文字画像を読み込み88番に登録
	Draw::LoadImage(L"img\\テキスト\\育成画面\\倉庫文字.png", 88, TEX_SIZE_512);

	//木材文字画像を読み込み89番に登録
	Draw::LoadImage(L"img\\テキスト\\素材\\木材文字.png", 89, TEX_SIZE_512);

	//銀文字画像を読み込み90番に登録
	Draw::LoadImage(L"img\\テキスト\\素材\\銀文字.png", 90, TEX_SIZE_512);

	//プラスチック文字画像を読み込み91番に登録
	Draw::LoadImage(L"img\\テキスト\\素材\\プラスチック文字.png", 91, TEX_SIZE_512);

	//アルミニウム文字画像を読み込み92番に登録
	Draw::LoadImage(L"img\\テキスト\\素材\\アルミ.png", 92, TEX_SIZE_512);

	//ガス文字画像を読み込み93番に登録
	Draw::LoadImage(L"img\\テキスト\\素材\\ガス文字.png", 93, TEX_SIZE_512);

	//残り住民数がいません文字画像を読み込み94番に登録
	Draw::LoadImage(L"img\\テキスト\\育成画面\\残り住民数がいません.png", 94, TEX_SIZE_512);

	//相手の惑星に文字画像を読み込み95番に登録
	Draw::LoadImage(L"img\\テキスト\\育成画面\\相手の惑星に.png", 95, TEX_SIZE_512);

	//固定ダメージを与える文字画像を読み込み96番に登録
	Draw::LoadImage(L"img\\テキスト\\育成画面\\固定ダメージを与える.png", 96, TEX_SIZE_512);

	//選択ライン上の文字画像を読み込み96番に登録
	Draw::LoadImage(L"img\\テキスト\\育成画面\\選択ライン上の.png", 97, TEX_SIZE_512);

	//相手ポッド等を破壊する文字画像を読み込み98番に登録
	Draw::LoadImage(L"img\\テキスト\\スペシャル技\\相手ポッド等を破壊する.png", 98, TEX_SIZE_512);

	//約10秒間文字画像を読み込み99番に登録
	Draw::LoadImage(L"img\\テキスト\\スペシャル技\\約10秒間.png", 99, TEX_SIZE_512);

	//無敵となる文字画像を読み込み100番に登録10秒間ポッド生産速度
	Draw::LoadImage(L"img\\テキスト\\スペシャル技\\無敵となる.png", 100, TEX_SIZE_512);

	//10秒間ポッド生産速度文字画像を読み込み101番に登録
	Draw::LoadImage(L"img\\テキスト\\スペシャル技\\10秒間ポッド生産速度.png", 101, TEX_SIZE_512);

	//ミサイル生産速度UP文字画像を読み込み102番に登録出撃する
	Draw::LoadImage(L"img\\テキスト\\育成画面\\ミサイル生産速度UP.png", 102, TEX_SIZE_512);

	//出撃する文字画像を読み込み103番に登録
	Draw::LoadImage(L"img\\テキスト\\育成画面\\出撃する.png", 103, TEX_SIZE_512);

	//ポッド5機の攻撃力UP文字画像を読み込み104番に登録
	Draw::LoadImage(L"img\\テキスト\\育成画面\\ポッド5機の攻撃力UP.png", 104, TEX_SIZE_512);

	//未装備の文字画像(装備部分だけ)を読み込み105番に登録
	Draw::LoadImage(L"img\\テキスト\\スペシャル技\\未装備.png", 105, TEX_SIZE_512);

	//※惑星HPが0以下になる場合LvUPは出来ません文字画像を読み込み106番に登録
	Draw::LoadImage(L"img\\テキスト\\育成画面\\※惑星HPが0以下になる場合LvUPは出来ません.png", 106, TEX_SIZE_512);

	//最大Lv到達!文字画像を読み込み107番に登録
	Draw::LoadImage(L"img\\テキスト\\育成画面\\最大Lv到達!.png", 107, TEX_SIZE_512);

	//これ以上LVUP不可です。文字画像を読み込み108番に登録
	Draw::LoadImage(L"img\\テキスト\\育成画面\\これ以上LVUP不可です。.png", 108, TEX_SIZE_512);

	//兵舎 Lv文字画像を読み込み116番に登録
	Draw::LoadImage(L"img\\テキスト\\育成画面\\兵舎 Lv.png",116,TEX_SIZE_512);

	//兵舎レベルUP文字画像を読み込み117番に登録
	Draw::LoadImage(L"img\\テキスト\\育成画面\\兵舎レベルUP.png", 117, TEX_SIZE_512);

	//研究所住人UP文字画像を読み込み118番に登録
	Draw::LoadImage(L"img\\ボタンUI\\研下.png", 118, TEX_SIZE_512);

	//研究所住人UP文字画像を読み込み119番に登録
	Draw::LoadImage(L"img\\ボタンUI\\研上01.png", 119, TEX_SIZE_512);

	//黒文字画像を読み込み120番に登録
	Draw::LoadImage(L"img\\テキスト\\文字集\\黒文字集.png", 120, TEX_SIZE_512);

	//白文字画像を読み込み121番に登録
	Draw::LoadImage(L"img\\テキスト\\文字集\\白文字集.png", 121, TEX_SIZE_512);

	////Sを読み込み122番に登録
	//Draw::LoadImage(L"S.png", 122, TEX_SIZE_512);

	//Lv1を読み込み123番に登録
	Draw::LoadImage(L"img\\テキスト\\育成画面\\Lv1.png", 123, TEX_SIZE_512);

	//Lv2を読み込み124番に登録
	Draw::LoadImage(L"img\\テキスト\\育成画面\\Lv2.png", 124, TEX_SIZE_512);

	//Lv3を読み込み125番に登録
	Draw::LoadImage(L"img\\テキスト\\育成画面\\Lv3.png", 125, TEX_SIZE_512);

	//簡易メッセージ画像全てを読み込む為に、
	//読み込み番号127番を使用しているので使わないように！

	//ポッド強化ボタンLv1を128番に登録
	Draw::LoadImage(L"img\\ポッド\\ポッド強化ボタンLv1.png", 128, TEX_SIZE_512);

	//ポッド強化ボタンLv2を129番に登録
	Draw::LoadImage(L"img\\ポッド\\ポッド強化ボタンLv2.png", 129, TEX_SIZE_512);

	//ポッド強化ボタンLv3を130番に登録
	Draw::LoadImage(L"img\\ポッド\\ポッド強化ボタンLv3.png", 130, TEX_SIZE_512);

	//これ以上レベルUP出来ませんを131番に登録
	Draw::LoadImage(L"img\\テキスト\\育成画面\\これ以上レベルUP出来ません.png", 131, TEX_SIZE_512);

	//メッセージウィンドウ01を132番に登録
	Draw::LoadImage(L"img\\メッセージウィンドウ\\メッセージウィンドウ01.png", 132, TEX_SIZE_512);

	//惑星発展度UP!を133番に登録
	Draw::LoadImage(L"img\\テキスト\\育成画面\\惑星発展度UP！.png", 133, TEX_SIZE_512);

	//ウインドウ02を134番に登録
	Draw::LoadImage(L"img\\メッセージウィンドウ\\ウインドウ02.png", 134, TEX_SIZE_512);

	//ポーズ画面背景(画面暗転用)を読み込み135番に登録
	Draw::LoadImage(L"img\\背景\\ポーズ画面背景.png", 135, TEX_SIZE_512);

	////ヘルプボタンを読み込み136番に登録
	//Draw::LoadImage(L"img\\ボタンUI\\ヘルプボタン.png", 136, TEX_SIZE_512);

	////説明文育成画面を137番に登録
	//Draw::LoadImage(L"img\\ヘルプ\\説明文育成画面.png", 137, TEX_SIZE_512);

	////説明文研究所を138番に登録
	//Draw::LoadImage(L"img\\ヘルプ\\説明文研究所.png", 138, TEX_SIZE_512);

	////説明文ミサイル画面を139番に登録
	//Draw::LoadImage(L"img\\ヘルプ\\説明文ミサイル画面.png", 139, TEX_SIZE_512);

	////説明文コアについてを140番に登録
	//Draw::LoadImage(L"img\\ヘルプ\\説明文コアについて.png", 140, TEX_SIZE_512);

	////説明文ポッドについてを141番に登録
	//Draw::LoadImage(L"img\\ヘルプ\\説明文ポッドについて.png", 141, TEX_SIZE_512);

	////説明文三竦みを読み込み142番に登録
	//Draw::LoadImage(L"img\\ヘルプ\\説明文三竦み.png", 142, TEX_SIZE_512);

	////説明文兵舎を143番に登録
	//Draw::LoadImage(L"img\\ヘルプ\\説明文兵舎.png", 143, TEX_SIZE_512);

	////説明文倉庫を144番に登録
	//Draw::LoadImage(L"img\\ヘルプ\\説明文倉庫.png", 144, TEX_SIZE_512);

	////説明文倉庫を145番に登録
	//Draw::LoadImage(L"img\\ヘルプ\\説明文惑星発展度.png", 145, TEX_SIZE_512);

	//コア文字画像を読み込み146番に登録
	Draw::LoadImage(L"img\\テキスト\\育成画面\\コア文字画像.png", 146, TEX_SIZE_512);

	//資材文字画像を読み込み147番に登録
	Draw::LoadImage(L"img\\テキスト\\素材\\資材.png", 147, TEX_SIZE_512);

	//スペシャル技文字画像を読み込み148番に登録
	Draw::LoadImage(L"img\\テキスト\\スペシャル技\\スペシャル技.png", 148, TEX_SIZE_512);

	//ポッド文字画像を読み込み149番に登録
	Draw::LoadImage(L"img\\テキスト\\育成画面\\ポッド.png", 149, TEX_SIZE_512);

	//赤住民画像を読み込み150番に登録
	Draw::LoadImage(L"img\\住民\\赤住民.png", 150, TEX_SIZE_512);

	//青住民画像を読み込み151番に登録
	Draw::LoadImage(L"img\\住民\\青住民.png", 151, TEX_SIZE_512);

	//緑住民画像を読み込み152番に登録
	Draw::LoadImage(L"img\\住民\\緑住民.png", 152, TEX_SIZE_512);

	//白住民画像を読み込み153番に登録
	Draw::LoadImage(L"img\\住民\\白住民.png", 153, TEX_SIZE_512);

	//白研究員文字画像を読み込み154番に登録
	Draw::LoadImage(L"img\\ボタンUI\\白研究員.png", 154, TEX_SIZE_512);

	//メッセージウィンドウ白1画像を読み込み155番に登録
	Draw::LoadImage(L"img\\メッセージウィンドウ\\メッセージウィンドウ白1.png", 155, TEX_SIZE_512);

	//喰アイコンを読み込み156番に登録
	Draw::LoadImage(L"img\\ボタンUI\\喰２.png", 156, TEX_SIZE_512);

	//ヘルプボタンを読み込み166番に登録
	Draw::LoadImage(L"img\\ボタンUI\\ヘルプボタン.png", 166, TEX_SIZE_512);

	//説明文育成画面を167番に登録
	Draw::LoadImage(L"img\\ヘルプ\\説明文育成画面.png", 167, TEX_SIZE_512);

	//説明文研究所を168番に登録
	Draw::LoadImage(L"img\\ヘルプ\\説明文研究所.png", 168, TEX_SIZE_512);

	//説明文ミサイル画面を169番に登録
	Draw::LoadImage(L"img\\ヘルプ\\説明文ミサイル画面.png", 169, TEX_SIZE_512);

	//説明文コアについてを170番に登録
	Draw::LoadImage(L"img\\ヘルプ\\説明文コアについて.png", 170, TEX_SIZE_512);

	//説明文ポッドについてを171番に登録
	Draw::LoadImage(L"img\\ヘルプ\\説明文ポッドについて.png", 171, TEX_SIZE_512);

	//説明文三竦みを読み込み172番に登録
	Draw::LoadImage(L"img\\ヘルプ\\説明文三竦み.png", 172, TEX_SIZE_512);

	//説明文兵舎を173番に登録
	Draw::LoadImage(L"img\\ヘルプ\\説明文兵舎.png", 173, TEX_SIZE_512);

	//説明文倉庫を174番に登録
	Draw::LoadImage(L"img\\ヘルプ\\説明文倉庫.png", 174, TEX_SIZE_512);

	//説明文倉庫を175番に登録
	Draw::LoadImage(L"img\\ヘルプ\\説明文惑星発展度.png", 175, TEX_SIZE_512);

	//説明文倉庫を176番に登録
	Draw::LoadImage(L"img\\ヘルプ\\説明文移動について.png", 176, TEX_SIZE_512);

	//会話矢印を読み込み189番に登録
	Draw::LoadImage(L"img\\ボタンUI\\会話矢印.png", 189, TEX_SIZE_512);

	//戦闘員x10(山田)を読み込み190番に登録
	Draw::LoadImage(L"img\\住民\\戦闘員x10.png", 190, TEX_SIZE_512);

	//矢印画像を読み込み191番に登録
	Draw::LoadImage(L"img\\ボタンUI\\矢印.png", 191, TEX_SIZE_512);

	//float v = Audio::VolumeMaster(0);
	//v = Audio::VolumeMaster((0.0 - v));

	//音楽読み込み
	Audio::LoadAudio(0, L"BGM\\育成画面BGM\\きっといい日.wav", BACK_MUSIC);

	//SE読み込み
	//選択
	Audio::LoadAudio(1, L"BGM\\効果音育成\\選択＆振り分けアップ３.wav", EFFECT);

	//戻る
	Audio::LoadAudio(2, L"BGM\\効果音育成\\戻る＆振り分けダウン４.wav", EFFECT);

	//施設レベルアップの音
	Audio::LoadAudio(3, L"BGM\\効果音育成\\施設レベルアップ音.wav", EFFECT);

	//ホワイトアウトの音
	Audio::LoadAudio(4, L"BGM\\効果音育成\\ホワイトアウト音.wav", EFFECT);

	//選択
	Audio::LoadAudio(5, L"BGM\\効果音育成\\住民振り分けアップ用.wav", EFFECT);

	//音楽スタート
	Audio::Start(0);
}

//ゲームメイン実行中メソッド
void CSceneTraining::Scene()
{

}