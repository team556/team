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

	//ヘルプブジェクト
	CObjHelp* hlp = new CObjHelp();     //ヘルプブジェクト作成
	Objs::InsertObj(hlp, OBJ_HELP, 20);  //ヘルプブジェクト登録


	//背景を読み込み0番に登録
	Draw::LoadImage(L"地面TEST.gif", 0, TEX_SIZE_512);

	//戻るアイコンを読み込み1番に登録
	Draw::LoadImage(L"戻る.png", 1, TEX_SIZE_512);

	//兵舎Lv1を読み込み2番に登録
	Draw::LoadImage(L"兵舎Lv1.png", 2, TEX_SIZE_512);

	//研究所Lv1を読み込み3番に登録
	Draw::LoadImage(L"研究所Lv1.png", 3, TEX_SIZE_512);

	//ミサイル(仮)を読み込み4番に登録
	Draw::LoadImage(L"ミサイル.png", 4, TEX_SIZE_512);

	//兵舎Lv2を読み込み5番に登録
	Draw::LoadImage(L"兵舎Lv2.png", 5, TEX_SIZE_512);

	//研究所Lv2を読み込み6番に登録
	Draw::LoadImage(L"研究所Lv2.png", 6, TEX_SIZE_512);

	//兵舎Lv3を読み込み8番に登録
	Draw::LoadImage(L"兵舎Lv3.png", 8, TEX_SIZE_512);

	//研究所Lv3を読み込み9番に登録
	Draw::LoadImage(L"研究所Lv3.png", 9, TEX_SIZE_512);

	//住民を読み込み10番に登録
	Draw::LoadImage(L"Human.png", 10, TEX_SIZE_512);

	//雲を読み込み15番に登録
	Draw::LoadImage(L"透過雲.png", 15, TEX_SIZE_512);

	//プレイヤー惑星を読み込み16番に登録
	Draw::LoadImage(L"プレイヤー惑星.png", 16, TEX_SIZE_512);

	//灰色ウインドウ(仮)を読み込み20番に登録
	Draw::LoadImage(L"灰色ウインドウ(仮).png", 20, TEX_SIZE_512);

	//メッセージウインドウを読み込み21番に登録
	Draw::LoadImage(L"メッセージウインドウ(仮).png", 21, TEX_SIZE_512);

	//施設LVUPを読み込み22番に登録
	Draw::LoadImage(L"施設LVUP.png", 22, TEX_SIZE_512);

	//住民振り分けUPを読み込み23番に登録
	Draw::LoadImage(L"兵舎振り分けUP.png", 23, TEX_SIZE_512);

	//住民振り分けDOWNを読み込み24番に登録
	Draw::LoadImage(L"兵舎振り分けDOWN.png", 24, TEX_SIZE_512);

	//ミサイルボタン(仮)を読み込み25番に登録
	Draw::LoadImage(L"ミサイルボタン.png", 25, TEX_SIZE_512);

	//武器ポッドボタン(仮)を読み込み26番に登録
	Draw::LoadImage(L"武器ポッドボタン.png", 26, TEX_SIZE_512);

	//test用倉庫画像読み込み27番に登録
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

	//資材(レアメタル)画像39番に登録
	Draw::LoadImage(L"レアメタル.png", 39, TEX_SIZE_512);

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

	//パワー武器Lv.1の画像を読み込み49番に登録
	Draw::LoadImage(L"パワーLv1.png", 49, TEX_SIZE_512);

	//パワー武器Lv.2の画像を読み込み50番に登録
	Draw::LoadImage(L"パワーLv2.png", 50, TEX_SIZE_512);

	//パワー武器Lv.3の画像を読み込み51番に登録
	Draw::LoadImage(L"パワーLv3.png", 51, TEX_SIZE_512);

	//ディフェンス武器Lv.1の画像を読み込み52番に登録
	Draw::LoadImage(L"ディフェンスLv1.png", 52, TEX_SIZE_512);

	//ディフェンス武器Lv.2の画像を読み込み53番に登録
	Draw::LoadImage(L"ディフェンスLv2.png", 53, TEX_SIZE_512);

	//ディフェンス武器Lv.3の画像を読み込み54番に登録
	Draw::LoadImage(L"ディフェンスLv3.png", 54, TEX_SIZE_512);

	//スピード武器Lv.1の画像を読み込み55番に登録
	Draw::LoadImage(L"スピードLv1.png", 55, TEX_SIZE_512);

	//スピード武器Lv.2の画像を読み込み56番に登録
	Draw::LoadImage(L"スピードLv2.png", 56, TEX_SIZE_512);

	//スピード武器Lv.3の画像を読み込み57番に登録
	Draw::LoadImage(L"スピードLv3.png", 57, TEX_SIZE_512);

	//バランス武器Lv.1の画像を読み込み58番に登録
	Draw::LoadImage(L"バランスLv1.png", 58, TEX_SIZE_512);

	//バランス武器Lv.2の画像を読み込み59番に登録
	Draw::LoadImage(L"バランスLv2.png", 59, TEX_SIZE_512);

	//バランス武器Lv.3の画像を読み込み60番に登録
	Draw::LoadImage(L"バランスLv3.png", 60, TEX_SIZE_512);

	//ポッドLv.1の画像を読み込み61番に登録
	Draw::LoadImage(L"ポッドLv1.png", 61, TEX_SIZE_512);

	//ポッドLv.2の画像を読み込み62番に登録
	Draw::LoadImage(L"ポッドLv2.png", 62, TEX_SIZE_512);

	//ポッドLv.3の画像を読み込み63番に登録
	Draw::LoadImage(L"ポッドLv3.png", 63, TEX_SIZE_512);

	//ヘルプボタンを読み込み64番に登録
	Draw::LoadImage(L"ヘルプボタン.png", 64, TEX_SIZE_512);

	//戻るを読み込み65番に登録
	Draw::LoadImage(L"戻る.png", 65, TEX_SIZE_512);

	//ヘルプ画像を読み込み66番に登録
	Draw::LoadImage(L"ヘルプ育成.png", 66, TEX_SIZE_512);

	//音楽読み込み
	//Audio::LoadAudio(0, L"きっといい日.wav", BACK_MUSIC);
	//Audio::LoadAudio(0, L"リトル・ハピネス.wav", BACK_MUSIC);
	//Audio::LoadAudio(0, L"洞窟の祠.wav", BACK_MUSIC);

	//SE読み込み
	//Audio::LoadAudio(1, L"選択ボタン音", EFFECT);
	//Audio::LoadAudio(2, L"戻るボタン音", EFFECT);
	//Audio::LoadAudio(3, L"施設レベルアップ音", EFFECT);
	//Audio::LoadAudio(4, L"", EFFECT);
	//Audio::LoadAudio(5, L"", EFFECT);

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
void CSceneTraining::Scene()
{

}