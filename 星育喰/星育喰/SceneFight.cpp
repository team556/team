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
	m_cnt = 0;
	m_speed = 0.12f;

	//背景を読み込み0番に登録
	Draw::LoadImage(L"TitleBackgroundTest.jpg", 0, TEX_SIZE_512);

	//外部グラフィックを読み込み0番に登録(512×512ピクセル)
	Draw::LoadImage(L"Human.png", 1, TEX_SIZE_512);

	//背景を読み込み0番に登録
	Draw::LoadImage(L"w.png", 2, TEX_SIZE_512);


	//出力させる文字のグラフィックを作成
	//Font::SetStrTex(L"");

	//テストオブジェクト作成
	CObjFight* obj = new CObjFight();		//タイトルオブジェクト作成
	Objs::InsertObj(obj, OBJ_FIGHT, 10);	//タイトルオブジェクト登録

	//星オブジェクト作成
	CObjPlanet* obj0 = new CObjPlanet(200, 300,false);	//オブジェクト作成
	Objs::InsertObj(obj0, OBJ_PLANET, 10);				//ブジェクト登録

	//自星オブジェクト作成
	CObjPlanet* obj1 = new CObjPlanet(900, 300, true);	//オブジェクト作成
	Objs::InsertObj(obj1, OBJ_PLANET, 10);				//オブジェクト登録

	//オブジェクト作成
	CObjPushUnit* obj2 = new CObjPushUnit(300, 600, 100, 100, 0);	//オブジェクト作成
	Objs::InsertObj(obj2, OBJ_PLANET, 10);				//オブジェクト登録

	//オブジェクト作成
	CObjPushUnit* obj3 = new CObjPushUnit(410, 600, 100, 100, 1);	//オブジェクト作成
	Objs::InsertObj(obj3, OBJ_PLANET, 10);				//オブジェクト登録

														//オブジェクト作成
	CObjPushUnit* obj4 = new CObjPushUnit(520, 600, 100, 100, 2);	//オブジェクト作成
	Objs::InsertObj(obj4, OBJ_PLANET, 10);				//オブジェクト登録
}

//ゲームメイン実行中メソッド
void CSceneFight::Scene()
{
	m_cnt += m_speed;
	if(m_speed > 0)
		m_speed -= 0.00005f;

	//描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	float d[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置


	//▼背景表示
	src.m_top   =  0.0f +(m_cnt * 4.5 / 6);
	src.m_left  =  0.0f + m_cnt;
	src.m_right =960.0f - m_cnt;
	src.m_bottom=638.0f -(m_cnt * 4.5 / 6);

	dst.m_top   =   0.0f;
	dst.m_left  =   0.0f;
	dst.m_right =1200.0f;
	dst.m_bottom= 700.0f;
	Draw::Draw(0, &src, &dst, d, 0.0f);
}