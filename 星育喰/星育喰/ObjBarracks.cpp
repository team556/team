//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjBarracks.h"


//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjBarracks::Init()
{

}

//アクション
void CObjBarracks::Action()
{
	//マウスの位置を取得
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//マウスのボタンの状態
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	if (m_x <= m_mou_x && m_mou_x <= m_x + 250.0f) {//X軸の範囲
		if (m_y <= m_mou_y && m_mou_y <= m_y + 268.0f) {//Y軸の範囲
			if (m_mou_l == true) {//クリック時
				if (m_key_f == true && m_turn == true) {
					Draw::LoadImage(L"オブジェクト.png", 1, TEX_SIZE_512);
					m_key_f = false;
					m_turn = false;
				}
				else if (m_key_f == true && m_turn == false)//2回目のクリック
				{
					//キャンセル時の範囲
					if (m_x <= m_mou_x && m_mou_x <= m_x + 100.0f && m_y <= m_mou_y && m_mou_y <= m_y + 100.0f)
					{
						Draw::LoadImage(L"建物.jpg", 1, TEX_SIZE_512);
						m_key_f = false;
						m_turn0 = false;
					}
				}
			}
			else {//クリック離した時
				m_key_f = true;
				if (m_turn0 == false) {
					m_turn = true;
					m_turn0 = true;
				}
			}
		}
	}


}

////初期化メソッド
//void CObjBarracks::InitScene()
//{
//	//
//}
//


//ドロー
void CObjBarracks::Draw()
{

}

