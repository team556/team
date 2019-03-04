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
CSceneTest::CSceneTest()
{

}

//デストラクタ
CSceneTest::~CSceneTest()
{

}

//ゲーム初期化メソッド
void CSceneTest::InitScene()
{
	//外部グラフィックを読み込み0番に登録(512×512ピクセル)
	Draw::LoadImage(L"Human.png", 0, TEX_SIZE_512);

	//出力させる文字のグラフィックを作成
	//Font::SetStrTex(L"");

	//テストオブジェクト作成
	//CObjTest* obj = new CObjTest();		//タイトルオブジェクト作成
	//Objs::InsertObj(obj, OBJ_TEST, 10);	//タイトルオブジェクト登録

	//住民オブジェクト作成
	CObjHuman* obj0 = new CObjHuman(100,100);	//タイトルオブジェクト作成
	Objs::InsertObj(obj0, OBJ_TEST, 10);		//タイトルオブジェクト登録
}

//ゲームメイン実行中メソッド
void CSceneTest::Scene()
{

}