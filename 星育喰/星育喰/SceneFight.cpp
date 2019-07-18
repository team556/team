//STLでバグ機能をOFFにする
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
	Draw::LoadImage(L"背景.png", 0, TEX_SIZE_512);

	//外部グラフィックを読み込み1番に登録(512×512ピクセル)
	Draw::LoadImage(L"Human.png", 1, TEX_SIZE_512);

	////2番にミサイル登録
	//Draw::LoadImage(L"w.png", 2, TEX_SIZE_512);

	//プレイヤー惑星Lv1を読み込み3番に登録
	Draw::LoadImage(L"P惑星_Lv1.png", 3, TEX_SIZE_512);

	//プレイヤー惑星Lv2を読み込み4番に登録
	Draw::LoadImage(L"P惑星_Lv2.png", 4, TEX_SIZE_512);

	//プレイヤー惑星Lv3を読み込み5番に登録
	Draw::LoadImage(L"P惑星_Lv3.png", 5, TEX_SIZE_512);

	//4番に登録惑星
	//Draw::LoadImage(L"プレイヤー惑星第二段階.png", 33, TEX_SIZE_512);

	//上レーン画像を5番に登録
	Draw::LoadImage(L"上レーン.png", 5, TEX_SIZE_512);

	//中央レーン画像を6番に登録
	Draw::LoadImage(L"中央レーン.png", 6, TEX_SIZE_512);

	//下レーン画像を7番に登録
	Draw::LoadImage(L"下レーン.png", 7, TEX_SIZE_512);

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
	Draw::LoadImage(L"スペシャル技ボタン.png", 19, TEX_SIZE_512);

	//ポーズ画面背景を読み込み20番に登録
	Draw::LoadImage(L"ポーズ画面背景.png", 20, TEX_SIZE_512);

	//スペシャル技[Explosion]画像を読み込み21番に登録
	Draw::LoadImage(L"エクスプロージョンビーム.png", 21, TEX_SIZE_512);

	//スペシャル技[Fracture_Ray]画像を読み込み22番に登録
	Draw::LoadImage(L"フラクチャーレイビーム.png", 22, TEX_SIZE_512);

	//スペシャル技[Immortality]画像を読み込み23番に登録
	Draw::LoadImage(L"スペシャル技インモータリティ.png", 23, TEX_SIZE_512);

	//スペシャル技[リミットブレイク]画像を読み込み24番に登録
	Draw::LoadImage(L"リミブレ.png", 24, TEX_SIZE_512);

	//スペシャル技[オーバーワーク]画像を読み込み25番に登録
	Draw::LoadImage(L"オーバーワーク.png", 25, TEX_SIZE_512);

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

	//スタート！文字画像を42番に登録
	Draw::LoadImage(L"スタート！.png", 42, TEX_SIZE_512);

	//プレイヤーを43番に登録
	Draw::LoadImage(L"プレイヤー.png", 43, TEX_SIZE_512);

	//エネミーを44番に登録
	Draw::LoadImage(L"エネミー.png", 44, TEX_SIZE_512);

	//エクスプロージョン文字画像を45番に登録
	Draw::LoadImage(L"エクスプロージョン.png", 45, TEX_SIZE_512);

	//フラクチャーレイ文字画像を46番に登録
	Draw::LoadImage(L"フラクチャーレイ.png", 46, TEX_SIZE_512);

	//イモータリティ文字画像を47番に登録
	Draw::LoadImage(L"イモータリティ.png", 47, TEX_SIZE_512);

	//オーバーワーク文字画像を48番に登録
	Draw::LoadImage(L"オーバーワーク.png", 48, TEX_SIZE_512);

	//リミットブレイク文字画像を49番に登録
	Draw::LoadImage(L"リミットブレイク.png", 49, TEX_SIZE_512);

	//発動！を50番に登録
	Draw::LoadImage(L"発動！.png", 50, TEX_SIZE_512);

	//クリックでタイトルに戻る文字画像を５１番に登録
	Draw::LoadImage(L"クリックでタイトルに戻る.png", 51, TEX_SIZE_512);

	//クリックでホーム画面文字画像を52番に登録
	Draw::LoadImage(L"クリックでホーム画面.png", 52, TEX_SIZE_512);

	//捕食成功！文字画像を53番に登録
	Draw::LoadImage(L"捕食成功！.png", 53, TEX_SIZE_512);

	//スペシャル技文字画像を54番に登録
	Draw::LoadImage(L"スペシャル技.png", 54, TEX_SIZE_512);

	//惑星HP文字画像を55番に登録
	Draw::LoadImage(L"惑星HP.png", 55, TEX_SIZE_512);

	//住民文字画像を56番に登録
	Draw::LoadImage(L"住民.png", 56, TEX_SIZE_512);

	//資材文字画像を57番に登録
	Draw::LoadImage(L"資材.png", 57, TEX_SIZE_512);

	//クリックでタイトルに戻る文字画像を５8番に登録
	Draw::LoadImage(L"GAME_OVER.png", 58, TEX_SIZE_512);

	//木材文字画像を59番に登録
	Draw::LoadImage(L"木材文字.png", 59, TEX_SIZE_512);

	//鉄文字画像を60番に登録
	Draw::LoadImage(L"鉄文字.png", 60, TEX_SIZE_512);

	//銀文字画像を61番に登録
	Draw::LoadImage(L"銀文字.png", 61, TEX_SIZE_512);

	//プラスチック文字画像を62番に登録
	Draw::LoadImage(L"プラスチック文字.png", 62, TEX_SIZE_512);

	//アルミ文字画像を63番に登録
	Draw::LoadImage(L"アルミ.png", 63, TEX_SIZE_512);

	//ガス文字画像を64番に登録
	Draw::LoadImage(L"ガス文字.png", 64, TEX_SIZE_512);

	//赤ポッドレベル1を65番目に登録
	Draw::LoadImage(L"ポッド赤Lv1.png", 65, TEX_SIZE_512);
	//赤ポッドレベル2を66番目に登録
	Draw::LoadImage(L"ポッド赤Lv2.png", 66, TEX_SIZE_512);
	//赤ポッドレベル3を67番目に登録
	Draw::LoadImage(L"ポッド赤Lv3.png", 67, TEX_SIZE_512);

	//青ポッドレベル1を68番目に登録
	Draw::LoadImage(L"ポッド青Lv1.png", 68, TEX_SIZE_512);
	//青ポッドレベル2を69番目に登録
	Draw::LoadImage(L"ポッド青Lv2.png", 69, TEX_SIZE_512);
	//青ポッドレベル3を70番目に登録
	Draw::LoadImage(L"ポッド青Lv3.png", 70, TEX_SIZE_512);

	//緑ポッドレベル1を71番目に登録
	Draw::LoadImage(L"ポッド緑Lv1.png", 71, TEX_SIZE_512);
	//緑ポッドレベル2を72番目に登録
	Draw::LoadImage(L"ポッド緑Lv2.png", 72, TEX_SIZE_512);
	//緑ポッドレベル3を73番目に登録
	Draw::LoadImage(L"ポッド緑Lv3.png", 73, TEX_SIZE_512);

	//白ポッドレベル1を74番目に登録
	Draw::LoadImage(L"ポッド白Lv1.png", 74, TEX_SIZE_512);
	//白ポッドレベル2を75番目に登録
	Draw::LoadImage(L"ポッド白Lv2.png", 75, TEX_SIZE_512);
	//白ポッドレベル3を76番目に登録
	Draw::LoadImage(L"ポッド白Lv3.png", 76, TEX_SIZE_512);

	//メッセージウインドウを読み込み78番に登録
	Draw::LoadImage(L"メッセージウィンドウ.png", 77, TEX_SIZE_512);

	//ポッドレーザーを読み込み78番に登録
	Draw::LoadImage(L"ポッドレーザー.png", 78, TEX_SIZE_512);

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