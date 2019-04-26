#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
//使用するネームスペース
using namespace GameL;

//マクロ
#define WARE_MES_MAX_FONT_LINE (3) //倉庫資材、技名、住民数、装備名最大フォント桁数

//オブジェクト：タイトル
class CObjWarehouse :public CObjTraining//CObjTrainingを継承する
{
	public:
		CObjWarehouse() {};
		~CObjWarehouse() {};
		void Init();     //イニシャライズ
		void Action();   //アクション
		void Draw();     //ドロー

		float m_mou_x;		//マウスx座標
		float m_mou_y;		//マウスy座標

		bool m_mou_r;		//右クリックフラグ
		bool m_mou_l;		//左クリックフラグ

	private:
		int m_x;
		int m_y;

		bool m_key_lf;  //左クリック用キーフラグ

		wchar_t m_Ware_message[WARE_MES_MAX_FONT_LINE][100];	//武器ポッド必要素材&人数メッセージのフォント用

		float m_Ware_color;			//倉庫カラー明度
		float m_Back_Button_color;	//戻るボタンカラー明度
		float m_object_ma;			//資材ボタンカラー明度
		float m_object_re;			//住民ボタンカラー明度
		float m_object_sp;			//スペシャル技ボタンカラー明度
		float m_object_eq;			//装備ボタンカラー明度

		int k;	//資材の所持している数

		//住民
		int p;	//住民パワーの値
		int s;	//住民スピードの値
		int d;	//住民ディフェンスの値
		int b;	//住民バランスの値
		int r;	//研究員の値

		//住民補正値
		int crvp;//補正値パワー
		int crp;

		int crvs;//補正値スピード
		int crs;

		int crvd;//補正値ディフェンス
		int crd;

		int crvbh;//補正値バランス	体力
		int crbh;

		int crvbp;//補正値バランス	パワー
		int crbp;

		int crvbs;//補正値バランス	スピード
		int crbs;

		int crvr;//補正値研究員
		int crr;

		//装備
		int eqpp;	//装備補正値パワープラス
		int epp;
		int eqpm;	//装備補正値パワーマイナス
		int epm;

		int eqsp;	//装備補正値スピードプラス
		int esp;
		int eqsm;	//装備補正値スピードマイナス
		int esm;

		int eqdp;	//装備補正値ディフェンスプラス
		int edp;
		int eqdm;	//装備補正値ディフェンスマイナス
		int edm;

		int eqbp;	//装備補正値バランスプラス
		int ebp;

		int epdp;	//装備補正値ポッドプラス
		int edpp;
		int m_time;
};