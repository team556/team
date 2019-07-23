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
	Draw::LoadImage(L"w.png", 0, TEX_SIZE_64);
	//仮画像を一番目に登録
	Draw::LoadImage(L"名前.png", 1, TEX_SIZE_64);

	//白文字画像を読み込み121番に登録
	Draw::LoadImage(L"白文字集.png", 121, TEX_SIZE_512);

	CObjNameInput*obj = new CObjNameInput();
	Objs::InsertObj(obj, OBJ_NAME_INPUT, 1);
}
//ゲームメイン実行中メソッド
void CSceneNameInput::Scene()
{}
