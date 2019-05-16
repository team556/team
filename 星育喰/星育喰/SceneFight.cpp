//STLでバグ機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERTOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL\DrawTexture.h"

//使用するネームスペース
using namespace GameL;

//使用ヘッダー
//#include "SceneMain.h"
#include "GameHead.h"

//コンストラクタ
CSceneFight::CSceneFight(int e_n)
{
	m_ene_nam = e_n;
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

	//外部グラフィックを読み込み0番に登録(512×512ピクセル)
	Draw::LoadImage(L"Human.png", 1, TEX_SIZE_512);

	//2番にミサイル登録
	Draw::LoadImage(L"w.png", 2, TEX_SIZE_512);

	//3番にプレイヤー登録
	Draw::LoadImage(L"プレイヤー惑星Lv1.png", 3, TEX_SIZE_512);

	//4番に登録惑星
	Draw::LoadImage(L"プレイヤー惑星第二段階.png", 33, TEX_SIZE_512);

	//5番に登録
	//Draw::LoadImage(L"プレイヤー捕食.png", 5, TEX_SIZE_512);

	//10番に登録赤色ポッド
	Draw::LoadImage(L"ポッド1.png", 10, TEX_SIZE_512);

	//11番に登録
	Draw::LoadImage(L"パワーボタン(仮).png", 11, TEX_SIZE_512);

	//12番に登録
	Draw::LoadImage(L"ディフェンスボタン(仮).png", 12, TEX_SIZE_512);

	//13番に登録
	Draw::LoadImage(L"スピードボタン(仮).png", 13, TEX_SIZE_512);

	//14番に登録
	Draw::LoadImage(L"バランスボタン(仮).png", 14, TEX_SIZE_512);

	//15番に登録
	Draw::LoadImage(L"ミサイルボタン(仮).png", 15, TEX_SIZE_512);

	//16番に爆発エフェクトを登録
	Draw::LoadImage(L"爆発エフェクト.png", 16, TEX_SIZE_512);

	//17番目に登録
	Draw::LoadImage(L"ミサイル.png", 17, TEX_SIZE_512);

	//戦闘画面移行演出(黒星)を読み込み18番に登録
	Draw::LoadImage(L"戦闘画面移行演出(黒星)(仮).png", 18, TEX_SIZE_512);

	//スペシャル技ボタンを読み込み19番に登録
	Draw::LoadImage(L"スペシャル技ボタン(仮).png", 19, TEX_SIZE_512);

	//▼調べた所、現状どこにも使われていなかった為、一旦コメントアウト中。
	//63番目に登録青色ポッド
	//Draw::LoadImage(L"ポッド2.png", 63, TEX_SIZE_512);
	

	//出力させる文字のグラフィックを作成
	//Font::SetStrTex(L"");

	//戦闘画面オブジェクト作成
	CObjFight* obj = new CObjFight(10, m_ene_nam);		//(戦闘時間, 敵ナンバー)
	Objs::InsertObj(obj, OBJ_FIGHT, 1);		//戦闘画面オブジェクト登録

	//敵星オブジェクト作成
	CObjPlanet* obj0 = new CObjPlanet(250, 350, 10, m_ene_nam);	//オブジェクト作成
	Objs::InsertObj(obj0, OBJ_ENEMY,  5);					//オブジェクト登録

	//自星オブジェクト作成
	CObjPlanet* obj1 = new CObjPlanet(950, 350, 10, 0);	//オブジェクト作成
	Objs::InsertObj(obj1, OBJ_PLANET, 10);					//オブジェクト登録

	//敵星クローン作成
	CObjPlanet* obj01 = new CObjPlanet(250, 350,10, m_ene_nam);	//オブジェクト作成
	Objs::InsertObj(obj01, OBJ_ENEMY2, 11);					//オブジェクト登録

	//民発射ボタン
	CObjRocketButton* obj2 = new CObjRocketButton(500, 600, 100, 100, 1);	//オブジェクト作成
	Objs::InsertObj(obj2, OBJ_PLANET, 10);						//オブジェクト登録

	CObjRocketButton* obj3 = new CObjRocketButton(650, 600, 100, 100, 2);	//オブジェクト作成
	Objs::InsertObj(obj3, OBJ_PLANET, 10);						//オブジェクト登録

	CObjRocketButton* obj4 = new CObjRocketButton(800, 600, 100, 100, 3);	//オブジェクト作成
	Objs::InsertObj(obj4, OBJ_PLANET, 10);						//オブジェクト登録

	CObjRocketButton* obj5 = new CObjRocketButton(950, 600, 100, 100, 4);	//オブジェクト作成
	Objs::InsertObj(obj5, OBJ_PLANET, 10);						//オブジェクト登録

	CObjRocketButton* obj6 = new CObjRocketButton(150, 600, 100, 200, 5);	//オブジェクト作成
	Objs::InsertObj(obj6, OBJ_PLANET, 10);						//オブジェクト登録

	//スペシャル技ボタン
	CObjSpecialButton* special = new CObjSpecialButton(1000.0f, 20.0f, 114.0f, 175.0f);	//オブジェクト作成
	Objs::InsertObj(special, OBJ_PLANET, 90);											//オブジェクト登録

	//戦闘前演出オブジェクト
	CObjBefore_Fight_Effect* before_fight_effect = new CObjBefore_Fight_Effect();	//戦闘前演出オブジェクト作成
	Objs::InsertObj(before_fight_effect, OBJ_BEFORE_FIGHT_EFFECT, 100);				//戦闘前演出オブジェクト登録
}

//ゲームメイン実行中メソッド
void CSceneFight::Scene()
{

}