#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：育成画面
class CObjTraining :public CObj
{
public:
	CObjTraining() {};
	~CObjTraining() {};
	void Init();     //イニシャライズ
	void Action();   //アクション
	void Draw();     //ドロー
private:
	float m_size;		//プレイヤー惑星のサイズ

	float m_Back_Button_color;	//戻るボタンカラー明度
	bool  m_Back_Button_flag;	//戻るボタンクリック、もしくは右クリック時trueフラグ

	int m_Mig_time;		//ホーム画面にシーン移行する際の時間管理変数
protected:
	float m_mou_x;		//マウスの位置X
	float m_mou_y;		//マウスの位置Y
	bool  m_mou_r;		//マウスプッシュ確認(右クリック)
	bool  m_mou_l;		//マウスプッシュ確認(左クリック)
	bool  m_key_f;		//キーフラグ

	static int manage[4];
		
	//	enum window_start_manage	//施設ウインドウの起動管理フラグ
	//{
	//	Default,
	//	Barracks,
	//}manage;
	//↑メモ書き：int型、列挙で宣言。その数字のものだけ操作できるように各objで条件分岐。
	//ちなみにその際、objTrainingも操作出来ないようにしておく。(右クリックキャンセルをさせないために)
	static bool scene_change_start;//シーン切り替え演出開始を伝えるフラグ
};