//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"

//使用するネームスペース
using namespace GameL;

//マクロ
#define INI_BLACK_STAR_EFFECT_SIZE (1400.0f) //黒星の初期サイズ

//イニシャライズ
void CObjBefore_Fight_Effect::Init()
{
	m_black_star_effect_size = INI_BLACK_STAR_EFFECT_SIZE;
}

//アクション
void CObjBefore_Fight_Effect::Action()
{
	//▼戦闘前演出(黒星)の処理
	if (m_black_star_effect_size <= 0.0f)
	{
		//★の画像が見えなくなった後、
		//ObjFightの「戦闘開始カウント」を動作させる
		CObjFight* fight = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
		fight->SetStart_Count();

		this->SetStatus(false);		//役割を終えたのでこのオブジェクトを削除する
	}
	else if (m_black_star_effect_size > 0.0f)
	{
		//画面全体が★の画像で覆いつくされた状態で始まる。
		//★の画像を徐々に縮小していき、画面中央へと収束、
		//最終的に見えなくなる。
		m_black_star_effect_size -= 20.0f;
	}
}

//ドロー
void CObjBefore_Fight_Effect::Draw()
{
	//描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	//戦闘前演出画像用(黒星など)
	float d[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置


	//▼戦闘前演出(黒星)表示
	//※完全に縮小すると描画先表示位置の設定上、非表示状態になる。
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 256.0f;
	src.m_bottom = 256.0f;

	dst.m_top = 350.0f - m_black_star_effect_size;
	dst.m_left = 600.0f - m_black_star_effect_size;
	dst.m_right = 600.0f + m_black_star_effect_size;
	dst.m_bottom = 350.0f + m_black_star_effect_size;
	Draw::Draw(18, &src, &dst, d, 0.0f);
}
