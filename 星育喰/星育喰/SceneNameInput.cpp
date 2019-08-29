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
#include "SceneNameInput.h"
#include "GameHead.h"

//コンストラクタ
CSceneNameInput::CSceneNameInput()
{}
//デストラクタ
CSceneNameInput::~CSceneNameInput()
{}
//ゲームメイン初期化メソッド
void CSceneNameInput::InitScene()
{
	//グラフィック登録
	Draw::LoadImage(L"img\\背景\\w.png", 0, TEX_SIZE_64);
	//仮画像を一番目に登録
	Draw::LoadImage(L"img\\テキスト\\オープニング\\名前.png", 1, TEX_SIZE_64);

	//仮画像を一番目に登録
	Draw::LoadImage(L"img\\テキスト\\オープニング\\クリア.png", 2, TEX_SIZE_64);

	//仮画像を一番目に登録
	Draw::LoadImage(L"img\\テキスト\\オープニング\\決定.png", 3, TEX_SIZE_64);

	//仮画像を一番目に登録
	Draw::LoadImage(L"img\\テキスト\\オープニング\\惑星.png", 4, TEX_SIZE_64);

	//仮画像を一番目に登録
	Draw::LoadImage(L"img\\背景\\w.png", 5, TEX_SIZE_64);

	//白文字画像を読み込み121番に登録
	Draw::LoadImage(L"img\\テキスト\\文字集\\白文字集.png", 121, TEX_SIZE_512);
	//ウィンドウ画像89番に登録
	Draw::LoadImage(L"img\\メッセージウィンドウ\\ウインドウ01.png", 89, TEX_SIZE_512);
	//はい文字画像読み込み66番に登録
	Draw::LoadImage(L"img\\テキスト\\よく使われる画像\\はい.png", 66, TEX_SIZE_512);

	//いいえ文字画像読み込み67番に登録
	Draw::LoadImage(L"img\\テキスト\\よく使われる画像\\いいえ.png", 67, TEX_SIZE_512);

	//SE読み込み
	//選択
	Audio::LoadAudio(1, L"選択＆振り分けアップ３.wav", EFFECT);

	//戻る
	Audio::LoadAudio(2, L"戻る＆振り分けダウン４.wav", EFFECT);

	CObjNameInput*obj = new CObjNameInput();
	Objs::InsertObj(obj, OBJ_NAME_INPUT, 1);
}
//ゲームメイン実行中メソッド
void CSceneNameInput::Scene()
{}
