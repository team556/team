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
	Draw::LoadImage(L"w.png", 0, TEX_SIZE_512);

	//タイトルロゴ
	Draw::LoadImage(L"タイトルロゴ.png", 1, TEX_SIZE_512);

	//↓エンディングのテキスト用
	//END描画登録
	Draw::LoadImage(L"img\\テキスト\\Ending\\END.png", 2, TEX_SIZE_512);

	//使用した音楽描画登録
	Draw::LoadImage(L"img\\テキスト\\Ending\\使用した音楽・効果音サイト.png", 3, TEX_SIZE_512);

	//エンドロールが早く流れます。描画登録
	Draw::LoadImage(L"img\\テキスト\\Ending\\右クリックを押し続けると.png", 4, TEX_SIZE_512);

	//右クリックを押し続けると
	Draw::LoadImage(L"img\\テキスト\\Ending\\エンドロールが早く流れます。.png", 5, TEX_SIZE_512);

	//クリックでタイトルに戻る
	Draw::LoadImage(L"img\\テキスト\\Ending\\クリックでタイトルに戻る.png", 6, TEX_SIZE_512);

	//音人
	Draw::LoadImage(L"img\\テキスト\\Ending\\音人.png", 7,TEX_SIZE_512);
	Draw::LoadImage(L"img\\テキスト\\Ending\\音人_URL.png", 8, TEX_SIZE_512);

	//魔王魂描画登録
	Draw::LoadImage(L"img\\テキスト\\Ending\\魔王魂.png", 9, TEX_SIZE_512);
	Draw::LoadImage(L"img\\テキスト\\Ending\\魔王魂_URL_1.png", 10, TEX_SIZE_512);
	Draw::LoadImage(L"img\\テキスト\\Ending\\魔王魂_URL_2.png", 11, TEX_SIZE_512);

	//TAMM描画登録
	Draw::LoadImage(L"img\\テキスト\\Ending\\TAM_Music_Factory.png", 12, TEX_SIZE_512);
	Draw::LoadImage(L"img\\テキスト\\Ending\\TAM_Music_Factory_URL.png", 13, TEX_SIZE_512);

	//DOVA-SYN DROME描画登録
	Draw::LoadImage(L"img\\テキスト\\Ending\\DOVA-SYN_DROME.png", 14, TEX_SIZE_512);
	Draw::LoadImage(L"img\\テキスト\\Ending\\DOVA-SYN_DROME_URL.png", 15, TEX_SIZE_512);

	//無料効果音で遊ぼう描画登録
	Draw::LoadImage(L"img\\テキスト\\Ending\\無料効果音で遊ぼう.png", 16, TEX_SIZE_512);
	Draw::LoadImage(L"img\\テキスト\\Ending\\無料効果音で遊ぼう_URL.png", 17, TEX_SIZE_512);

	//効果音ラボ描画登録
	Draw::LoadImage(L"img\\テキスト\\Ending\\効果音ラボ.png", 18, TEX_SIZE_512);
	Draw::LoadImage(L"img\\テキスト\\Ending\\効果音ラボ_URL.png", 19, TEX_SIZE_512);

	//OtoLogic
	Draw::LoadImage(L"img\\テキスト\\Ending\\OtoLogic.png", 20, TEX_SIZE_512);
	Draw::LoadImage(L"img\\テキスト\\Ending\\OtoLogic_URL.png", 21, TEX_SIZE_512);

	//メンバーの名前描画登録
	Draw::LoadImage(L"img\\テキスト\\Ending\\池田.png", 22, TEX_SIZE_512);
	Draw::LoadImage(L"img\\テキスト\\Ending\\後庵.png", 23, TEX_SIZE_512);
	Draw::LoadImage(L"img\\テキスト\\Ending\\木村.png", 24, TEX_SIZE_512);
	Draw::LoadImage(L"img\\テキスト\\Ending\\脇田.png", 25, TEX_SIZE_512);
	Draw::LoadImage(L"img\\テキスト\\Ending\\柏崎.png", 26, TEX_SIZE_512);
	Draw::LoadImage(L"img\\テキスト\\Ending\\坂田.png", 27, TEX_SIZE_512);
	Draw::LoadImage(L"img\\テキスト\\Ending\\諏訪.png", 28, TEX_SIZE_512);

	//使用グラフィック紹介
	Draw::LoadImage(L"img\\テキスト\\Ending\\弊社サイト.png", 29, TEX_SIZE_512);//
	Draw::LoadImage(L"img\\テキスト\\Ending\\よく飛ばない鳥.png", 30, TEX_SIZE_512);//
	Draw::LoadImage(L"img\\テキスト\\Ending\\ピリオドフォントURL.png", 31, TEX_SIZE_512);//
	Draw::LoadImage(L"img\\テキスト\\Ending\\フォント.png", 32, TEX_SIZE_512);//
	Draw::LoadImage(L"img\\テキスト\\Ending\\ピリオドフォント.png", 33, TEX_SIZE_512);//
	Draw::LoadImage(L"img\\テキスト\\Ending\\作者.png", 34, TEX_SIZE_512);//
	Draw::LoadImage(L"img\\テキスト\\Ending\\作者名.png", 35, TEX_SIZE_512);//

	//制作メンバーの役割紹介
	Draw::LoadImage(L"img\\テキスト\\Ending\\総合.png", 36, TEX_SIZE_512);
	Draw::LoadImage(L"img\\テキスト\\Ending\\プログラマ.png", 37, TEX_SIZE_512);
	Draw::LoadImage(L"img\\テキスト\\Ending\\グラフィッカー.png", 38, TEX_SIZE_512);
	Draw::LoadImage(L"img\\テキスト\\Ending\\プランナ.png", 39, TEX_SIZE_512);






	

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