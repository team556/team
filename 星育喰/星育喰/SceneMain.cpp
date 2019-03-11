//STLデバック機能をOFFにする
#define _SECURE_SCL	(0)
#define _HAS_ITERATOR_DEBUGGING	(0)

//GameLで使用するヘッダー
#include "GameL\DrawTexture.h"

//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "SceneMain.h"
#include "GameHead.h"

//コンストラクタ
CSceneMain::CSceneMain()
{

}

//デストラクタ
CSceneMain::~CSceneMain()
{

}

//ゲームメイン初期化メソッド
void CSceneMain::InitScene()
{
	//test用外部グラフィック読み込み0番に登録
	Draw::LoadImage(L"背景.png", 1, TEX_SIZE_512);

	//test用建物グラフィック読み込み1番に登録
	Draw::LoadImage(L"建物.png", 2, TEX_SIZE_512);

	//背景オブジェクト作成
	CObjFacility* facility = new CObjFacility();
	Objs::InsertObj(facility, OBJ_FACILITY, 1);

	//建物オブジェクト作成
	CObjBuild* build = new CObjBuild();
	Objs::InsertObj(build, OBJ_BUILD, 2);
}

//ゲームメイン実行中メソッド
void CSceneMain::Scene()
{

}