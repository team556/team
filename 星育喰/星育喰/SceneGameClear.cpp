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
CSceneGameClear::CSceneGameClear()
{

}

//デストラクタ
CSceneGameClear::~CSceneGameClear()
{

}

//ゲーム初期化メソッド
void CSceneGameClear::InitScene()
{
	//外部グラフィックを読み込み1番に登録(512×512ピクセル)
	Draw::LoadImage(L"w.png", 1, TEX_SIZE_512);

	//オブジェクト作成
	CObjGameClear* obj = new CObjGameClear();	//オブジェクト作成
	Objs::InsertObj(obj, OBJ_GAME_CLEAR, 10);	//オブジェクト登録

	//音楽読み込み
	Audio::LoadAudio(0, L"エンドロール.wav", BACK_MUSIC);

	//クリック音
	Audio::LoadAudio(1, L"選択＆振り分けアップ３.wav", EFFECT);

	//音楽スタート
	Audio::Start(0);

}

//ゲームメイン実行中メソッド
void CSceneGameClear::Scene()
{
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	RECT_F src;
	RECT_F dst;
	//切り取り位置
	src.m_top   =  0.0f;
	src.m_left  =  0.0f;
	src.m_right =100.0f;
	src.m_bottom=100.0f;
	//表示位置
	dst.m_top   =   0.0f;
	dst.m_left  =   0.0f;
	dst.m_right =1200.0f;
	dst.m_bottom= 700.0f;

	//0番目に登録したグラフィックをsrc,dst,c情報をもとに描画
	Draw::Draw(1, &src, &dst, c, 0.0f);
}