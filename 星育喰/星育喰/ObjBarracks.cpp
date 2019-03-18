//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"

#include "GameHead.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjBarracks::Init()
{

}

//アクション
void CObjBarracks::Action()
{

}

//ドロー
void CObjBarracks::Draw()
{
	//▼シーン切り替え演出後に非表示にする処理
	if (scene_change_start == true)
	{
		return;
	}

	//それ以外の画像用
	float d[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

	//▼兵舎表示
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 245.0f;
	src.m_bottom = 206.0f;

	dst.m_top = 460.0f;
	dst.m_left = 810.0f;
	dst.m_right = 1190.0f;
	dst.m_bottom = 690.0f;
	Draw::Draw(2, &src, &dst, d, 0.0f);
}