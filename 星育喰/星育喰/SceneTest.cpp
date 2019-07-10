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

	//外部グラフィックを読み込み1番に登録(512×512ピクセル)
	Draw::LoadImage(L"w.png", 1, TEX_SIZE_512);

	//メッセージウインドウを読み込み2番に登録
	Draw::LoadImage(L"メッセージウインドウ(仮).png", 2, TEX_SIZE_512);

	//白文字集を読み込み3番に登録
	Draw::LoadImage(L"白文字集.png", 3, TEX_SIZE_512);

	////10番に登録
	//Draw::LoadImage(L".png", 2, TEX_SIZE_512);

	//出力させる文字のグラフィックを作成
	//Font::SetStrTex(L"");

	//テストオブジェクト作成
	//CObjTest* obj = new CObjTest();		//タイトルオブジェクト作成
	//Objs::InsertObj(obj, OBJ_TEST, 10);	//タイトルオブジェクト登録

	////住民オブジェクト作成
	//CObjHuman* obj = new CObjHuman(100,600);	//タイトルオブジェクト作成
	//Objs::InsertObj(obj, OBJ_HUMAN, 10);		//タイトルオブジェクト登録

	////オブジェクト作成
	//CObjFightClear* obj = new CObjFightClear();	//タイトルオブジェクト作成
	//Objs::InsertObj(obj, OBJ_FIGHT_CLEAR, 10);		//タイトルオブジェクト登録

	////ヘルプオブジェクト作成
	//CObjHelp* help = new CObjHelp(1);		//ヘルプオブジェクト作成
	//Objs::InsertObj(help, OBJ_HELP, 10);	//ヘルプオブジェクト登録

	//メッセージ表示オブジェクト作成
	//CObjMessage* message = new CObjMessage(0);	//メッセージ表示オブジェクト作成
	//Objs::InsertObj(message, OBJ_MESSAGE, 90);	//メッセージ表示オブジェクト登録
}

//ゲームメイン実行中メソッド
void CSceneTest::Scene()
{
	//float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	//RECT_F src;
	//RECT_F dst;
	////切り取り位置
	//src.m_top   =  0.0f;
	//src.m_left  =  0.0f;
	//src.m_right =100.0f;
	//src.m_bottom=100.0f;
	////表示位置
	//dst.m_top   =   0.0f;
	//dst.m_left  =   0.0f;
	//dst.m_right =1200.0f;
	//dst.m_bottom= 700.0f;

	////0番目に登録したグラフィックをsrc,dst,c情報をもとに描画
	//Draw::Draw(1, &src, &dst, c, 0.0f);
}