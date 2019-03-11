//STLデバック機能をOFFにする
#define _SECURE_SCL_ (0)
#define _HAS_ITERATOR_DEBUGGINGb (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\Audio.h"

//使用するネームスペース
using namespace GameL;

//使用するヘッダー
#include "SceneFacility.h"
#include "GameHead.h"

//コンストラクタ
CSceneFacility::CSceneFacility()
{

}
//デストラクタ
CSceneFacility::~CSceneFacility()
{

}
//初期化メソッド
void CSceneFacility::InitScene()
{
	//test用外部グラフィック読み込み0番に登録
	Draw::LoadImage(L"背景.png", 0, TEX_SIZE_512);

}
//実行中メソッド
void CSceneFacility::Scene()
{
	//描画カラー情報 R=RED G=Green B=Blue A=alpha(透過情報) 
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;	//切り取り
	RECT_F dst;	//描画
	

	//切り取り
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 100.0f;
	src.m_bottom = 100.0f;

	//表示
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;

	//0番目に登録したグラフィックをsrc,dst,c情報をもとに描画
	Draw::Draw(0, &src, &dst, c, 0.0f);

}