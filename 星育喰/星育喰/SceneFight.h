#pragma once
//使用するヘッダーファイル
#include"GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//シーン：戦闘画面
class CSceneFight :public CScene
{
public:
	CSceneFight();
	~CSceneFight();
	void InitScene();  //ゲームタイトルの初期化メソッド
	void Scene();      //ゲームタイトルの実行中メソッド
private:
	int m_time;		//シーンのタイム(クリック音後にシーン以降)

};