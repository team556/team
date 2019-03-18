#pragma once
//使用するヘッダーファイル
#include"GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//シーン：育成画面
class CSceneTraining :public CScene
{
public:
	CSceneTraining();
	~CSceneTraining();
	void InitScene();  //ゲームタイトルの初期化メソッド
	void Scene();      //ゲームタイトルの実行中メソッド
private:
	//▼配列の[3]は後に住民数を管理するグローバル変数を基に決める為、
	//配置する事の出来る最大住民数の値に変えるように。
	float m_ini_hx[3];			//Humanの初期X座標
	float m_ini_hy[3];			//Humanの初期Y座標
};