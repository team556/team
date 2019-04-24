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
	m_speed = 0.04f;
	m_a = 1.0f;

	//背景を読み込み0番に登録
	Draw::LoadImage(L"TitleBackgroundTest.jpg", 0, TEX_SIZE_512);

	//外部グラフィックを読み込み0番に登録(512×512ピクセル)
	Draw::LoadImage(L"Human.png", 1, TEX_SIZE_512);

	//ミサイル2番に登録
	Draw::LoadImage(L"w.png", 2, TEX_SIZE_512);

	//3番に登録
	Draw::LoadImage(L"プレイヤー惑星.png", 3, TEX_SIZE_512);

	//4番に登録
	Draw::LoadImage(L"口綴じプレイヤー.png", 4, TEX_SIZE_512);

	//5番に登録
	Draw::LoadImage(L"プレイヤー捕食.png", 5, TEX_SIZE_512);

	//10番に登録
	Draw::LoadImage(L"w.png", 10, TEX_SIZE_512);
	


	//出力させる文字のグラフィックを作成
	//Font::SetStrTex(L"");

	//テストオブジェクト作成
	CObjFight* obj = new CObjFight();		//タイトルオブジェクト作成
	Objs::InsertObj(obj, OBJ_FIGHT, 10);	//タイトルオブジェクト登録

	//敵星オブジェクト作成
	CObjPlanet* obj0 = new CObjPlanet(250, 350, 10, false);	//オブジェクト作成
	Objs::InsertObj(obj0, OBJ_ENEMY,  5);				//ブジェクト登録

	//自星オブジェクト作成
	CObjPlanet* obj1 = new CObjPlanet(950, 350, 10, true);	//オブジェクト作成
	Objs::InsertObj(obj1, OBJ_PLANET, 10);				//オブジェクト登録

	//民発射ボタン
	CObjPushUnit* obj2 = new CObjPushUnit(400, 600, 100, 100);	//オブジェクト作成
	Objs::InsertObj(obj2, OBJ_PLANET, 10);						//オブジェクト登録

	CObjPushUnit* obj3 = new CObjPushUnit(550, 600, 100, 100);	//オブジェクト作成
	Objs::InsertObj(obj3, OBJ_PLANET, 10);						//オブジェクト登録

	CObjPushUnit* obj4 = new CObjPushUnit(700, 600, 100, 100);	//オブジェクト作成
	Objs::InsertObj(obj4, OBJ_PLANET, 10);						//オブジェクト登録
}

//ゲームメイン実行中メソッド
void CSceneFight::Scene()
{
	m_cnt += m_speed;
	if(m_speed > 0)
		m_speed -= 0.00001f;

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


	if (m_cnt >= 0.5 && m_a >=0 ) {
		m_a -= 0.01f;
	}
	
	float c[4] = { 1.0f,1.0f,1.0f,m_a };
	Font::StrDraw(L"スタート！", 420, 250, 80, c);
}