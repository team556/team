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
	Draw::LoadImage(L"TitleBackgroundTest.jpg", 0, TEX_SIZE_512);

	//外部グラフィックを読み込み1番に登録(512×512ピクセル)
	Draw::LoadImage(L"Human.png", 1, TEX_SIZE_512);

	//2番にミサイル登録
	Draw::LoadImage(L"w.png", 2, TEX_SIZE_512);

	//3番にプレイヤー登録
	Draw::LoadImage(L"プレイヤー惑星Lv1.png", 3, TEX_SIZE_512);

	//4番に登録惑星
	Draw::LoadImage(L"プレイヤー惑星第二段階.png", 33, TEX_SIZE_512);

	//5番に登録
	//Draw::LoadImage(L"プレイヤー捕食.png", 5, TEX_SIZE_512);

	//ポッドLv.1を8番に登録
	Draw::LoadImage(L"ポッド1.png", 8, TEX_SIZE_512);

	//ポッドLv.2を9番に登録
	Draw::LoadImage(L"ポッド2.png", 9, TEX_SIZE_512);

	//ポッドLv.3を10番に登録
	Draw::LoadImage(L"ポッド3.png", 10, TEX_SIZE_512);

	//11番に登録
	Draw::LoadImage(L"パワーボタン.png", 11, TEX_SIZE_512);

	//12番に登録
	Draw::LoadImage(L"ディフェンスボタン.png", 12, TEX_SIZE_512);

	//13番に登録
	Draw::LoadImage(L"スピードボタン.png", 13, TEX_SIZE_512);

	//14番に登録
	Draw::LoadImage(L"バランスボタン.png", 14, TEX_SIZE_512);

	//15番に登録
	Draw::LoadImage(L"ミサイルボタン(新).png", 15, TEX_SIZE_512);

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

	//敵惑星1(1ステージ)を読み込み26番に登録
	Draw::LoadImage(L"Enemy_Planet_Test.jpg", 26, TEX_SIZE_512);

	//敵惑星2(1ステージ)を読み込み27番に登録
	Draw::LoadImage(L"Enemy_Planet_Test2.jpg", 27, TEX_SIZE_512);

	//敵惑星3(1ステージ)を読み込み28番に登録
	Draw::LoadImage(L"Enemy_Planet_Test3.jpg", 28, TEX_SIZE_512);

	//敵惑星4(1ステージ)を読み込み29番に登録
	Draw::LoadImage(L"Enemy_Planet_Test4.jpg", 29, TEX_SIZE_512);

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
	CObjRocketButton* obj2 = new CObjRocketButton(500, 600, 100, 100, 1);	//オブジェクト作成
	Objs::InsertObj(obj2, OBJ_POD_BUTTON1, 10);						//オブジェクト登録

	CObjRocketButton* obj3 = new CObjRocketButton(650, 600, 100, 100, 2);	//オブジェクト作成
	Objs::InsertObj(obj3, OBJ_POD_BUTTON2, 10);						//オブジェクト登録

	CObjRocketButton* obj4 = new CObjRocketButton(800, 600, 100, 100, 3);	//オブジェクト作成
	Objs::InsertObj(obj4, OBJ_POD_BUTTON3, 10);						//オブジェクト登録

	CObjRocketButton* obj5 = new CObjRocketButton(950, 600, 100, 100, 4);	//オブジェクト作成
	Objs::InsertObj(obj5, OBJ_POD_BUTTON4, 10);						//オブジェクト登録

	CObjRocketButton* obj6 = new CObjRocketButton(150, 600, 100, 200, 5);	//オブジェクト作成
	Objs::InsertObj(obj6, OBJ_MISSILE_BUTTON, 10);						//オブジェクト登録

	//スペシャル技ボタン
	CObjSpecialButton* special = new CObjSpecialButton(1000.0f, 20.0f, 114.0f, 175.0f);	//オブジェクト作成
	Objs::InsertObj(special, OBJ_SPECIAL, 90);											//オブジェクト登録

	//戦闘前演出オブジェクト
	CObjBefore_Fight_Effect* before_fight_effect = new CObjBefore_Fight_Effect();	//戦闘前演出オブジェクト作成
	Objs::InsertObj(before_fight_effect, OBJ_BEFORE_FIGHT_EFFECT, 100);				//戦闘前演出オブジェクト登録

	//音楽読み込み
	//Audio::LoadAudio(0, L"戦闘中.wav", BACK_MUSIC);
	//Audio::LoadAudio(1, L"勝利.wav", BACK_MUSIC);
	//Audio::LoadAudio(2, L"敗北.wav", BACK_MUSIC);

	//SE読み込み
	//Audio::LoadAudio(3, L"発射ボタン音", EFFECT);
	//Audio::LoadAudio(4, L"爆発音.wav", EFFECT);
	//Audio::LoadAudio(5, L"スペシャル技発動音.wav", EFFECT);


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
void CSceneFight::Scene()
{

}