#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：タイトル
class CObjFacility :public CObj
{
	public:
		CObjFacility() {};
		~CObjFacility() {};
		void Init();     //イニシャライズ
		void Action();   //アクション
		void Draw();     //ドロー
	private:
};