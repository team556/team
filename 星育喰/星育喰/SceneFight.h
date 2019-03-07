#pragma once
//使用するヘッダーファイル
#include"GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//シーン：ゲームタイトル
class CSceneFight :public CScene
{
public:
	CSceneFight();
	~CSceneFight();
	void InitScene();  //ゲームタイトルの初期化メソッド
	void Scene();      //ゲームタイトルの実行中メソッド
private:
	float m_cnt;		//縮小比カウント
	float m_speed;		//縮小スピード
};