//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"

//使用するネームスペース
using namespace GameL;

//マクロ
#define INI_ENEMY_X_POS (1250.0f)	//敵惑星4つ全体の初期X位置(敵惑星1基準)
#define INI_ENEMY_Y_POS (190.0f)	//敵惑星4つ全体の初期Y位置(敵惑星1基準)
#define INI_WARNING_MESSAGE_X_POS (125.0f)	//警告メッセージ全体の初期X位置
#define INI_WARNING_MESSAGE_Y_POS (250.0f)	//警告メッセージ全体の初期Y位置
#define INI_WARNING_MESSAGE_SIZE  (100.0f)	//警告メッセージ全体のサイズ
#define INI_SPEED (50.0f)//各演出で移動する各オブジェクトの初期移動速度
#define INI_ALPHA (0.0f) //透過度(アルファ値)の初期値
#define INI_COLOR (0.9f) //全カラー明度の初期値(アイコン未選択中のカラー)
#define INI_PLANET (300.0f)

//イニシャライズ
void CObjPreparation::Init()
{
	m_mou_x = 0.0f;
	m_mou_y = 0.0f;
	m_mou_r = false;
	m_mou_l = false;

	m_key_lf = false;
	m_key_rf = false;

	m_Pvx = 0.0f;
	m_Pvy = 0.0f;
	m_Pr = 0.0f;
	m_Psize = 0.0f;

	m_Svy = 0.0f;

	m_Bvx = 0.0f;
	m_Bvy = 0.0f;

	m_Evx = 0.0f;

	for (int i = 0; i < 2; i++)
	{
		m_warning_message_x[i] = INI_WARNING_MESSAGE_X_POS;
		m_warning_message_y[i] = INI_WARNING_MESSAGE_Y_POS;
	}

	m_warning_message_size = INI_WARNING_MESSAGE_SIZE;
	m_warning_message_alpha = INI_ALPHA;
	m_warning_message_skip_f = false;

	for (int i = 0; i < 3; i++)
	{
		m_Boss_vx[i] = 0.0f;
		m_Boss_vy[i] = 0.0f;
	}

	m_Boss_clip_pos_x = -1.0f;//0.0fだと意図してないタイミングで条件文に入る為、初期値を-1.0fにする事で現状対応。
	//m_Boss_clip_pos_y = 0.0f;

	m_speed = INI_SPEED;
	m_save_speed = 0.0f;

	m_black_star_effect_f = false;
	m_staging_time = 0;
	m_is_operatable = false;

	m_Back_Button_color = INI_COLOR;
	m_Yes_Button_color = 1.0f;
	m_No_Button_color = 1.0f;

	m_Back_flag = false;
	m_Go_flag = false;
	m_boss_emerge_staging_f = false;
	m_finalcheck_f = false;

	m_detail_message_window_top = 0.0f;
	m_detail_message_window_left = 0.0f;
	m_detail_message_window_right = 0.0f;
	m_detail_message_window_bottom = 0.0f;
	m_detail_message_draw_y = 0.0f;

	for (int i = 0; i < DETAIL_MES_MAX_FONT_LINE; i++)
	{
		m_detail_message_clip_right[i] = 0.0f;
		m_detail_message_clip_bottom[i] = 0.0f;
		m_detail_message_draw_right[i] = 0.0f;
	}

	m_detail_message_draw_left = 0.0f;
	m_detail_message_alpha = INI_ALPHA;
	m_level_star_num = 0;

	m_destroy_count = 0;

	//現在の撃破数をカウント
	for (int i = 0; i < 4; i++)
	{
		if (g_destroy_progress[i] == true)
		{
			m_destroy_count++;
		}
	}

	//チュートリアル時のみ特殊処理
	if (g_tutorial_progress == 1)
	{
		for (int i = 0; i < 4; i++)
		{
			g_destroy_progress[i] = true;
		}

		m_destroy_count = 4;
	}

	//▼現在のスペシャル技習得状況、装備状況に応じて
	//スペシャル技アイコンのカラー明度を以下のように設定していく。
	//「未習得」……………………………0.0f(黒色)
	//「クリックで装備可(習得済)」……0.4f(灰色)
	//「装備中」……………………………1.0f(白色)
	for (int i = 0; i < 5; i++)
	{
		//装備中の処理
		if (g_Special_equipment == i + 1)
		{
			m_Special_icon_color[i] = 1.0f;
		}
		//クリックで装備可(習得済)の処理
		else if (g_Special_mastering[i] == true)
		{
			m_Special_icon_color[i] = 0.4f;
		}
		//未習得の処理
		else
		{
			m_Special_icon_color[i] = 0.0f;
		}
	}

	//▼各敵惑星の詳細説明文設定
	//▽1ステージ　敵惑星1(左から1番目の敵惑星)
	//swprintf_s(m_Enemy_detail_message[0][0][0], L"難易度　★");//1行目
	//swprintf_s(m_Enemy_detail_message[0][0][1], L"取得可能な資材・技");//2行目
	//swprintf_s(m_Enemy_detail_message[0][0][2], L"木材50・鉄30");//3行目
	//swprintf_s(m_Enemy_detail_message[0][0][3], L"Fracture ray");//4行目
	//swprintf_s(m_Enemy_detail_message[0][0][4], L"ディフェンス重視");//5行目
	////▽1ステージ　敵惑星2(左から2番目の敵惑星)
	//swprintf_s(m_Enemy_detail_message[0][1][0], L"難易度　★★★");//1行目
	//swprintf_s(m_Enemy_detail_message[0][1][1], L"取得可能な資材・技");//2行目
	//swprintf_s(m_Enemy_detail_message[0][1][2], L"プラスチック40・ガス50");//3行目
	//swprintf_s(m_Enemy_detail_message[0][1][3], L"Expiosion");//4行目
	//swprintf_s(m_Enemy_detail_message[0][1][4], L"パワー重視");//5行目
	////▽1ステージ　敵惑星3(左から3番目の敵惑星)
	//swprintf_s(m_Enemy_detail_message[0][2][0], L"難易度　★★★★");//1行目
	//swprintf_s(m_Enemy_detail_message[0][2][1], L"取得可能な資材・技");//2行目
	//swprintf_s(m_Enemy_detail_message[0][2][2], L"銀65・レアメタル50");//3行目
	//swprintf_s(m_Enemy_detail_message[0][2][3], L"ステロイド投与");//4行目
	//swprintf_s(m_Enemy_detail_message[0][2][4], L"バランス重視");//5行目
	////▽1ステージ　敵惑星4(左から4番目の敵惑星)
	//swprintf_s(m_Enemy_detail_message[0][3][0], L"難易度　★★");//1行目
	//swprintf_s(m_Enemy_detail_message[0][3][1], L"取得可能な資材・技");//2行目
	//swprintf_s(m_Enemy_detail_message[0][3][2], L"鉄70・アルミ80");//3行目
	//swprintf_s(m_Enemy_detail_message[0][3][3], L"Immotality");//4行目
	//swprintf_s(m_Enemy_detail_message[0][3][4], L"スピード重視");//5行目
	////▽1ステージ　ボス惑星
	//swprintf_s(m_Enemy_detail_message[0][4][0], L"難易度　測定不能");//1行目
	//swprintf_s(m_Enemy_detail_message[0][4][1], L"取得可能な資材・技");//2行目
	//swprintf_s(m_Enemy_detail_message[0][4][2], L"無し");//3行目
	//swprintf_s(m_Enemy_detail_message[0][4][3], L"攻撃傾向");//4行目
	//swprintf_s(m_Enemy_detail_message[0][4][4], L"不明");//4行目
	////▽2ステージ　敵惑星1(左から1番目の敵惑星)
	//swprintf_s(m_Enemy_detail_message[1][0][0], L"テスト");//1行目
	//swprintf_s(m_Enemy_detail_message[1][0][1], L"テスト");//2行目
	//swprintf_s(m_Enemy_detail_message[1][0][2], L"テスト");//3行目
	//swprintf_s(m_Enemy_detail_message[1][0][3], L"テスト");//4行目
	////▽2ステージ　敵惑星2(左から2番目の敵惑星)
	//swprintf_s(m_Enemy_detail_message[1][1][0], L"テスト");//1行目
	//swprintf_s(m_Enemy_detail_message[1][1][1], L"テスト");//2行目
	//swprintf_s(m_Enemy_detail_message[1][1][2], L"テスト");//3行目
	//swprintf_s(m_Enemy_detail_message[1][1][3], L"テスト");//4行目
	////▽2ステージ　敵惑星3(左から3番目の敵惑星)
	//swprintf_s(m_Enemy_detail_message[1][2][0], L"テスト");//1行目
	//swprintf_s(m_Enemy_detail_message[1][2][1], L"テスト");//2行目
	//swprintf_s(m_Enemy_detail_message[1][2][2], L"テスト");//3行目
	//swprintf_s(m_Enemy_detail_message[1][2][3], L"テスト");//4行目
	////▽2ステージ　敵惑星4(左から4番目の敵惑星)
	//swprintf_s(m_Enemy_detail_message[1][3][0], L"テスト");//1行目
	//swprintf_s(m_Enemy_detail_message[1][3][1], L"テスト");//2行目
	//swprintf_s(m_Enemy_detail_message[1][3][2], L"テスト");//3行目
	//swprintf_s(m_Enemy_detail_message[1][3][3], L"テスト");//4行目
	////▽2ステージ　ボス惑星
	//swprintf_s(m_Enemy_detail_message[1][4][0], L"テスト");//1行目
	//swprintf_s(m_Enemy_detail_message[1][4][1], L"テスト");//2行目
	//swprintf_s(m_Enemy_detail_message[1][4][2], L"テスト");//3行目
	//swprintf_s(m_Enemy_detail_message[1][4][3], L"テスト");//4行目
	////▽3ステージ　敵惑星1(左から1番目の敵惑星)
	//swprintf_s(m_Enemy_detail_message[2][0][0], L"テスト");//1行目
	//swprintf_s(m_Enemy_detail_message[2][0][1], L"テスト");//2行目
	//swprintf_s(m_Enemy_detail_message[2][0][2], L"テスト");//3行目
	//swprintf_s(m_Enemy_detail_message[2][0][3], L"テスト");//4行目
	////▽3ステージ　敵惑星2(左から2番目の敵惑星)
	//swprintf_s(m_Enemy_detail_message[2][1][0], L"テスト");//1行目
	//swprintf_s(m_Enemy_detail_message[2][1][1], L"テスト");//2行目
	//swprintf_s(m_Enemy_detail_message[2][1][2], L"テスト");//3行目
	//swprintf_s(m_Enemy_detail_message[2][1][3], L"テスト");//4行目
	////▽3ステージ　敵惑星3(左から3番目の敵惑星)
	//swprintf_s(m_Enemy_detail_message[2][2][0], L"テスト");//1行目
	//swprintf_s(m_Enemy_detail_message[2][2][1], L"テスト");//2行目
	//swprintf_s(m_Enemy_detail_message[2][2][2], L"テスト");//3行目
	//swprintf_s(m_Enemy_detail_message[2][2][3], L"テスト");//4行目
	////▽3ステージ　敵惑星4(左から4番目の敵惑星)
	//swprintf_s(m_Enemy_detail_message[2][3][0], L"テスト");//1行目
	//swprintf_s(m_Enemy_detail_message[2][3][1], L"テスト");//2行目
	//swprintf_s(m_Enemy_detail_message[2][3][2], L"テスト");//3行目
	//swprintf_s(m_Enemy_detail_message[2][3][3], L"テスト");//4行目
	////▽3ステージ　ボス惑星
	//swprintf_s(m_Enemy_detail_message[2][4][0], L"テスト");//1行目
	//swprintf_s(m_Enemy_detail_message[2][4][1], L"テスト");//2行目
	//swprintf_s(m_Enemy_detail_message[2][4][2], L"テスト");//3行目
	//swprintf_s(m_Enemy_detail_message[2][4][3], L"テスト");//4行目
}

//アクション
void CObjPreparation::Action()
{
	//ヘルプ画面表示中は操作不能にする処理
	if (g_help_f == true)
	{
		//ヘルプ画面非表示時、
		//戦闘準備画面の各ボタンが同時にクリックされないように、
		//以下のようにキーフラグをfalseにする事で制御している。
		m_key_lf = false;
		m_key_rf = false;

		return;
	}

	//▼ホーム画面移行演出
	if (m_Back_flag == true)
	{
		if (m_Pvx >= 950.0f)
		{
			//プレイヤー惑星が画面中央に移動完了後、ホーム画面へ移行する。
			Scene::SetScene(new CSceneHome());//ホーム画面へシーン移行
		}
		else if (m_Psize == -150.0f)
		{
			//画面外(左側)から画面中央に向かってプレイヤー惑星を移動させる
			//▼プレイヤー惑星X移動処理
			m_Pvx += m_speed;

			//▼プレイヤー惑星Y移動処理
			//角度加算
			m_Pr += 1.0f;

			//360°で初期値に戻す
			if (m_Pr > 360.0f)
				m_Pr = 0.0f;

			//移動方向
			m_Pvy = sin(3.14f / 90 * m_Pr) - 550.0f;

			//速度付ける。
			m_Pvy -= m_speed;


			//徐々にプレイヤー惑星の移動速度を減少させる
			m_speed *= 0.948f;
		}
		else if(m_Evx >= 0.0f)
		{
			m_staging_time++;

			//約0.5秒後、以下の処理を実行。
			if (m_staging_time >= 30)
			{
				//プレイヤー惑星の位置を画面外(左側)に移動。
				//また、サイズをホーム画面のプレイヤー惑星と同じサイズにする。
				m_Pvx = 0.0f;
				m_Pvy = -550.0f;
				m_Psize = -150.0f;

				//移動速度を初期値に戻す。
				m_speed = INI_SPEED;
			}
		}
		else if (m_Evx < 0.0f)
		{
			//各惑星、スペシャル技アイコン、戻るボタン、
			//ボス出現警告メッセージ等をそれぞれ画面外に移動させる
			m_Evx += m_speed;			//移動速度は共通の変数を使い、敵惑星を基準に設定している。
			m_Pvx -= m_speed * 0.37;	//例えばプレイヤー惑星は敵惑星ほど大きく移動する訳ではない為、
			m_Pvy += m_speed * 0.37;	//0.37倍の値を移動速度に加算して、移動量を調節している。
			m_Svy += m_speed * 0.37;
			m_Bvx -= m_speed * 0.065;
			m_Bvy -= m_speed * 0.065;

			m_warning_message_y[0] -= m_speed * 0.1;
			m_warning_message_y[1] -= m_speed * 0.1;

			//ボス惑星出現時、以下の処理も行う
			if (m_destroy_count == 4)
			{
				m_Boss_vx[2] += m_speed * 0.91;
			}

			//徐々に上記オブジェクトの画面外移動速度を増加させる
			m_speed /= 0.956f;

			//敵惑星詳細説明を非表示(右クリックでホーム画面に戻る際、詳細説明が残らないようにするため)
			m_detail_message_alpha = 0.0f;

			//ObjHelpにシーン移行演出を伝える
			CObjHelp* help = (CObjHelp*)Objs::GetObj(OBJ_HELP);
			help->SetMig_stageF();
		}

		return;
	}
	//▼戦闘画面移行演出
	else if (m_Go_flag == true)
	{
		if (m_black_star_effect_f == true)
		{
			//★画像が画面全体を覆いつくした後、下記の撃破フラグ処理を実行
			//その後、戦闘画面へシーン移行する。

			//再度この戦闘準備画面に戻ってくる＝現在挑戦する敵惑星を撃破したという事。
			//その為、このタイミングで既に撃破フラグをtrueにしておく。
			//※ただし挑戦するのがボス惑星の場合、以下の処理を飛ばす。
			//ボス惑星撃破後、敵の撃破状態を元に戻したり、ステージを進める処理は
			//ObjFightClearで行っている。
			if (m_destroy_count != 4)
			{
				g_destroy_progress[g_Challenge_enemy] = true;
			}

			Scene::SetScene(new CSceneFight());//戦闘画面へシーン移行
		}
		
		return;
	}



	//▼操作可能時の処理
	if (m_is_operatable == true)
	{
		//チュートリアル中は操作を受け付けないようにする。
		if (g_is_operatable == false)
		{
			//チュートリアル進行度が2になると、戦闘画面へ強制移行させる
			if (g_tutorial_progress == 2)
			{
				//移行開始フラグ立て
				m_Go_flag = true;

				g_Challenge_enemy = 5;//戦闘相手をチュートリアル惑星に設定

				//戦闘前演出を行うオブジェクトを生成する
				CObjBefore_Fight_Effect* before_fight_effect = new CObjBefore_Fight_Effect(true);
				Objs::InsertObj(before_fight_effect, OBJ_BEFORE_FIGHT_EFFECT, 100);
			}
			
			return;
		}

		//マウスの位置を取得
		m_mou_x = (float)Input::GetPosX();
		m_mou_y = (float)Input::GetPosY();
		//マウスのボタンの状態
		m_mou_r = Input::GetMouButtonR();
		m_mou_l = Input::GetMouButtonL();

		//▼キーフラグ
		//※右クリックPush状態→右クリック未Push状態になるまで、
		//再度右クリックする事は出来ない処理。
		if (m_mou_r == false)	//右クリックOFF
		{
			m_key_rf = true;
		}

		//▼最終確認ウインドウ表示時の処理
		if (m_finalcheck_f == true)
		{
			//最終確認[はい]ボタン
			if (410 < m_mou_x && m_mou_x < 502 && 407 < m_mou_y && m_mou_y < 450)
			{
				m_Yes_Button_color = 0.0f;

				//▼クリックされたら移行開始フラグを立て、
				//演出を交えながら、戦闘画面にシーン移行する
				//左クリック入力時
				if (m_mou_l == true)
				{
					//左クリック押したままの状態では入力出来ないようにしている
					if (m_key_lf == true)
					{
						m_key_lf = false;

						m_Yes_Button_color = 1.0f;

						//移行開始フラグ立て
						m_Go_flag = true;

						//最終確認ウインドウを非表示にする
						m_finalcheck_f = false;

						//戦闘前演出を行うオブジェクトを生成する
						CObjBefore_Fight_Effect* before_fight_effect = new CObjBefore_Fight_Effect(true);
						Objs::InsertObj(before_fight_effect, OBJ_BEFORE_FIGHT_EFFECT, 100);

						//選択音
						Audio::Start(1);
					}
				}
				else
				{
					m_key_lf = true;
				}
			}
			else
			{
				m_Yes_Button_color = 1.0f;
			}

			//最終確認[いいえ]ボタン
			if (648 < m_mou_x && m_mou_x < 789 && 407 < m_mou_y && m_mou_y < 450 || m_mou_r == true)
			{
				m_No_Button_color = 0.0f;

				//▼クリックされたら、このウインドウを閉じる
				//右クリック入力時
				if (m_mou_r == true)
				{
					//ウインドウ閉じた後、続けて戻るボタンを入力出来ないようにする
					m_key_rf = false;

					m_No_Button_color = 1.0f;

					//最終確認ウインドウを非表示にする
					m_finalcheck_f = false;

					//戻るボタン音
					Audio::Start(2);
				}
				//左クリック入力時
				else if (m_mou_l == true)
				{
					//左クリック押したままの状態では入力出来ないようにしている
					if (m_key_lf == true)
					{
						m_key_lf = false;

						m_No_Button_color = 1.0f;

						//最終確認ウインドウを非表示にする
						m_finalcheck_f = false;

						//戻るボタン音
						Audio::Start(2);
					}
				}
				else
				{
					m_key_lf = true;
				}
			}
			else
			{
				m_No_Button_color = 1.0f;
			}


			return;
		}

		//戻るボタン左クリック、もしくは右クリックする事でホーム画面に戻る
		if (g_tutorial_progress != 1)
		{
			if (10 < m_mou_x && m_mou_x < 60 && 10 < m_mou_y && m_mou_y < 60 || m_mou_r == true)
			{
				m_Back_Button_color = 1.0f;

				//▼移行開始フラグを立て、ホーム画面へ演出を交えながらシーン移行
				//右クリック入力時
				if (m_mou_r == true)
				{
					//最終確認ウインドウから右クリック押したままの状態では入力出来ないようにしている
					if (m_key_rf == true)
					{
						//移行開始フラグ立て
						m_Back_flag = true;

						//戻るボタン音
						Audio::Start(2);
					}
				}
				//左クリック入力時
				else if (m_mou_l == true)
				{
					//左クリック押したままの状態では入力出来ないようにしている
					if (m_key_lf == true)
					{
						m_key_lf = false;

						//移行開始フラグ立て
						m_Back_flag = true;

						//戻るボタン音
						Audio::Start(2);
					}
				}
				else
				{
					m_key_lf = true;
				}
			}
			else
			{
				m_Back_Button_color = INI_COLOR;
			}
		}
		
		//敵惑星1(左から1番目の敵惑星)[未撃破時のみ選択可能]
		if (147 < m_mou_x && m_mou_x < 346 && 187 < m_mou_y && m_mou_y < 383 && g_destroy_progress[0] == false)
		{
			//▼敵惑星詳細説明を表示
			Enemy_message(0);//敵惑星詳細説明表示関数を呼び出す
		}

		//敵惑星2(左から2番目の敵惑星)[未撃破時のみ選択可能]
		else if (446 < m_mou_x && m_mou_x < 544 && 158 < m_mou_y && m_mou_y < 255 && g_destroy_progress[1] == false)
		{
			//▼敵惑星詳細説明を表示
			Enemy_message(1);//敵惑星詳細説明表示関数を呼び出す
		}

		//敵惑星3(左から3番目の敵惑星)[未撃破時のみ選択可能]
		else if (744 < m_mou_x && m_mou_x < 941 && 137 < m_mou_y && m_mou_y < 334 && g_destroy_progress[2] == false)
		{
			//▼敵惑星詳細説明を表示
			Enemy_message(2);//敵惑星詳細説明表示関数を呼び出す
		}

		//敵惑星4(左から4番目の敵惑星)[未撃破時のみ選択可能]
		else if (892 < m_mou_x && m_mou_x < 1139 && 433 < m_mou_y && m_mou_y < 679 && g_destroy_progress[3] == false)
		{
			//▼敵惑星詳細説明を表示
			Enemy_message(3);//敵惑星詳細説明表示関数を呼び出す
		}

		//ボス惑星[ボス惑星出現時のみ選択可能]
		else if (426 < m_mou_x && m_mou_x < 767 && 123 < m_mou_y && m_mou_y < 460 && m_destroy_count == 4 && g_tutorial_progress != 1)
		{
			//▼敵惑星詳細説明を表示
			Enemy_message(4);//敵惑星詳細説明表示関数を呼び出す
		}

		//チュートリアル惑星[チュートリアル惑星出現時のみ選択可能]
		else if (426 < m_mou_x && m_mou_x < 767 && 133 < m_mou_y && m_mou_y < 350 && m_destroy_count == 4 && g_tutorial_progress == 1)
		{
			//▼敵惑星詳細説明を表示
			Enemy_message(5);//敵惑星詳細説明表示関数を呼び出す

			//矢印を非表示にさせる
			CObjMessage* message = (CObjMessage*)Objs::GetObj(OBJ_MESSAGE);
			message->Setarrow(0);
		}

		//スペシャル技(エクスプロージョン)
		else if (377 < m_mou_x && m_mou_x < 455 && 579 < m_mou_y && m_mou_y < 637)
		{
			//▼スペシャル技詳細説明を表示
			Special_message(0);//スペシャル技詳細説明表示関数を呼び出す
		}

		//スペシャル技(フラクチャーレイ)
		else if (471 < m_mou_x && m_mou_x < 549 && 579 < m_mou_y && m_mou_y < 637)
		{
			//▼スペシャル技詳細説明を表示
			Special_message(1);//スペシャル技詳細説明表示関数を呼び出す
		}

		//スペシャル技(イモータリティ)
		else if (565 < m_mou_x && m_mou_x < 643 && 579 < m_mou_y && m_mou_y < 637)
		{
			//▼スペシャル技詳細説明を表示
			Special_message(2);//スペシャル技詳細説明表示関数を呼び出す
		}

		//スペシャル技(オーバーワーク)
		else if (660 < m_mou_x && m_mou_x < 737 && 579 < m_mou_y && m_mou_y < 637)
		{
			//▼スペシャル技詳細説明を表示
			Special_message(3);//スペシャル技詳細説明表示関数を呼び出す
		}

		//スペシャル技(リミットブレイク)
		else if (754 < m_mou_x && m_mou_x < 831 && 579 < m_mou_y && m_mou_y < 637)
		{
			//▼スペシャル技詳細説明を表示
			Special_message(4);//スペシャル技詳細説明表示関数を呼び出す
		}

		//上記の範囲外にマウスカーソルがある場合、
		//詳細説明(敵惑星、スペシャル技)を非表示にする
		else
		{
			m_detail_message_alpha = 0.0f;//詳細説明(敵惑星、スペシャル技)を非表示
		}


		return;
	}



	//▼警告メッセージスキップ処理
	if (m_warning_message_alpha != 0.0f && m_boss_emerge_staging_f == false || m_warning_message_skip_f == true)
	{
		//このスキップ処理は、警告メッセージ表示演出中に左クリックされると実行される。
		//スキップ処理という名の通り、実行されると警告メッセージの演出が素早く終了する。
		//※処理の流れは「if ～ else if」を駆使している為、基本的に下から上に実行されていく。

		//マウス左クリック状態を取得
		m_mou_l = Input::GetMouButtonL();

		if (m_warning_message_skip_f == true)
		{
			//警告メッセージ表示演出中に一度でも左クリックされるとこの処理に入る。

			if (m_warning_message_alpha >= 1.2f && m_warning_message_size == 55.0f)
			{
				//警告メッセージ完全表示後、
				//ボス惑星出現カウントが0であれば、ボス惑星出現演出に移行する。
				//そうでなければ、操作可能な状態にする。
				//※ボス演出を既に見ている場合も操作可能な状態にする。
				if (3 - m_destroy_count == 0)
				{
					m_boss_emerge_staging_f = true;
				}
				else
				{
					m_is_operatable = true;

					if (g_tutorial_progress != 15)
					{
						//ObjHelpに操作可能を伝える
						CObjHelp* help = (CObjHelp*)Objs::GetObj(OBJ_HELP);
						help->SetOperatable(true);
					}

					if (g_tutorial_progress <= 15)
					{
						g_is_operatable = false;//操作不可に

						//ObjMessageのメッセージ進行度を増加させる
						CObjMessage* message = (CObjMessage*)Objs::GetObj(OBJ_MESSAGE);
						message->Setprogress(1);
					}
				}

				m_warning_message_skip_f = false;//警告メッセージスキップフラグOFF(スキップ処理が終了した為)
			}
			else if (m_warning_message_alpha < 1.2f && m_warning_message_size == 55.0f)
			{
				//変更後、警告メッセージ透過度を素早く上げ、表示状態にする。
				m_warning_message_alpha += 0.1f;
			}
			else if (m_warning_message_alpha <= 0.0f)
			{
				//警告メッセージ完全非表示後、
				//警告メッセージサイズ、位置を
				//演出終了後のものに即座に変更する。
				
				//チュートリアル惑星時の処理
				if (g_tutorial_progress == 1)
				{
					m_warning_message_x[0] = 16.25f;
				}
				//ボス惑星出現時の処理
				else if (m_destroy_count == 4)
				{
					m_warning_message_x[0] = 97.2f;
				}
				//それ以外の時の処理
				else
				{
					m_warning_message_x[0] = 192.5f;
				}

				m_warning_message_y[0] = 25.0f;
				m_warning_message_x[1] = 507.5f;
				m_warning_message_y[1] = -105.4f;
				m_warning_message_size = 55.0f;
				m_warning_message_alpha = 0.0f;
			}
			else if (m_warning_message_alpha > 0.0f)
			{
				//警告メッセージ透過度を素早く下げ、非表示状態にする。
				m_warning_message_alpha -= 0.1f;
			}

			return;//ここでreturnする事で、通常処理に入らないようにする。
		}
		//警告メッセージ表示演出中に左クリックされたら、
		//警告メッセージスキップフラグを立てる。
		else if (m_mou_l == true)
		{
			m_warning_message_skip_f = true;//警告メッセージスキップフラグON
		}
	}

	//▼ボス惑星出現演出
	//ボス惑星出現カウントが0になった時、以下の処理を実行
	if (m_boss_emerge_staging_f == true)
	{
		if (m_destroy_count == 4)
		{
			//メッセージ内容を変更した為、
			//警告メッセージを徐々に表示させる
			//完全に表示後、操作可能な状態にする。
			if (m_warning_message_alpha >= 1.0f)
			{
				m_is_operatable = true;

				//ObjHelpに操作可能を伝える
				CObjHelp* help = (CObjHelp*)Objs::GetObj(OBJ_HELP);
				help->SetOperatable(true);
			}
			else if (m_warning_message_alpha < 1.0f)
			{
				m_warning_message_alpha += 0.02f;
			}
		}
		else if (m_Boss_vy[2] < 0.0f)
		{
			//画面中央まで移動完了後、以下の2つの処理を同時に行う。

			//警告メッセージを徐々に非表示にする
			//完全に非表示後、敵惑星撃破数を4に設定する事で
			//ボス出現警告メッセージ内容を変える。
			//また、移動速度を保存していたものに戻す
			if (m_warning_message_alpha <= 0.0f)
			{
				m_destroy_count = 4;
				m_warning_message_x[0] = 97.2f;
				m_speed = m_save_speed;
			}
			else if (m_warning_message_alpha > 0.0f)
			{
				m_warning_message_alpha -= 0.01f;
			}

			//ボス惑星描画元切り取り位置を徐々に変更し、最終的に口を閉じた状態にする
			//if (m_warning_message_alpha <= 0.0f)
			//{
			//	if (g_Stage_progress == 1)//ステージ1のパンダ惑星の時のみ、以下の処理を実行。
			//	{
			//		m_Boss_clip_pos_y = 128.0f;//正面を向かせる
			//	}
			//}
			if (m_warning_message_alpha <= 0.4f)
			{
				m_Boss_clip_pos_x = -600.0f;
			}
			else if (m_warning_message_alpha <= 0.8f)
			{
				m_Boss_clip_pos_x = -300.0f;
			}
			
		}
		else if (m_Boss_clip_pos_x == 0.0f)
		{
			//ボス惑星の準備完了後、
			//ボス惑星が画面外(右下)から画面中央へと敵惑星の上を通りながら通過。
			//通過タイミングで敵惑星を非表示にし、食べているように演出。

			//ボス惑星が敵惑星の上を通過し、
			//隠したタイミングで撃破フラグを立てる
			if (m_Boss_vy[2] <= 270.0f)
			{
				g_destroy_progress[3] = true;
			}

			//ボス惑星3移動
			m_Boss_vx[2] -= m_speed;
			m_Boss_vy[2] -= m_speed * 0.65;

			//徐々にボス惑星の移動速度を減少させる
			m_speed *= 0.951f;
		}
		else if (m_Boss_vx[1] >= 1520.0f)
		{
			//▽次の演出の準備
			//ボス惑星位置Yを適切な位置に移動させる
			m_Boss_vy[2] = 650.0f;

			//ボス惑星描画元切り取り位置を適切な位置に設定し、口を開けた状態にする
			m_Boss_clip_pos_x = 0.0f;

			//現在の移動速度を別変数に保存した後、移動速度を初期化する
			m_save_speed = m_speed;
			m_speed = INI_SPEED;
		}
		else if (m_Boss_vx[0] <= -1420.0f)
		{
			//演出用のボス惑星1が画面外(左)に移動完了後、
			//演出用のボス惑星2が画面外(左)から画面外(右)へと敵惑星2つの上を通りながら通過。
			//通過タイミングで敵惑星をそれぞれ非表示にし、食べているように演出。

			//ボス惑星が敵惑星の上を通過し、
			//隠したタイミングで撃破フラグを立てる
			if (m_Boss_vx[1] >= 1010.0f)
			{
				g_destroy_progress[2] = true;
			}
			else if (m_Boss_vx[1] >= 380.0f)
			{
				g_destroy_progress[0] = true;
			}

			//ボス惑星2移動
			m_Boss_vx[1] += 20.0f;
			m_Boss_vy[1] -= 2.0f;
		}
		else if (m_Boss_vx[0] > -1420.0f)
		{
			//演出用のボス惑星1が画面外(右)から画面外(左)へと敵惑星の上を通りながら通過。
			//通過タイミングで敵惑星を非表示にし、食べているように演出。

			//ボス惑星が敵惑星の上を通過し、
			//隠したタイミングで撃破フラグを立てる
			if (m_Boss_vx[0] <= -820.0f)
			{
				g_destroy_progress[1] = true;
			}

			//ボス惑星1移動
			m_Boss_vx[0] -= 20.0f;
			m_Boss_vy[0] -= 5.0f;
		}
	}

	//▼戦闘準備画面開始演出
	//戦闘準備画面に入ると、まず以下の処理が実行される
	else if (m_warning_message_y[0] < 30.0f)
	{
		//警告メッセージ移動完了後、
		//ボス惑星出現カウントが0であれば、ボス惑星出現演出に移行する。
		//そうでなければ、操作可能な状態にする。
		//※ボス演出を既に見ている場合も操作可能な状態にする。
		if (3 - m_destroy_count == 0)
		{
			m_boss_emerge_staging_f = true;
		}
		else
		{
			m_is_operatable = true;

			if (g_tutorial_progress != 15)
			{
				//ObjHelpに操作可能を伝える
				CObjHelp* help = (CObjHelp*)Objs::GetObj(OBJ_HELP);
				help->SetOperatable(true);
			}
			
			if (g_tutorial_progress <= 15)
			{
				g_is_operatable = false;//操作不可に

				//ObjMessageのメッセージ進行度を増加させる
				CObjMessage* message = (CObjMessage*)Objs::GetObj(OBJ_MESSAGE);
				message->Setprogress(1);
			}
		}
	}
	else if (m_warning_message_alpha >= 1.2f)
	{
		//警告メッセージ完全表示後、
		//警告メッセージサイズを徐々に小さくしながら、
		//画面上部へと警告メッセージを移動させる

		//チュートリアル惑星時の処理
		if (g_tutorial_progress == 1)
		{
			m_warning_message_x[0] += 3.25f;
		}
		//ボス惑星出現時の処理
		else if (m_destroy_count == 4)
		{
			m_warning_message_x[0] += 5.05f;
		}
		//それ以外の時の処理
		else
		{
			m_warning_message_x[0] += 1.5f;
		}
		m_warning_message_y[0] -= 5.0f;
		m_warning_message_x[1] += 8.5f;
		m_warning_message_y[1] -= 7.9f;
		m_warning_message_size -= 1.0f;
	}
	else if (m_Evx <= -1100.0f)
	{
		//画面内移動完了後、
		//警告メッセージを徐々に表示させる
		//1.0f以上にする意味は、フォント移動までの時間調節もついでに行っている為。
		if (m_warning_message_alpha < 1.2f)
		{
			m_warning_message_alpha += 0.01f;
		}
	}
	else if (m_Evx > -1100.0f)
	{
		//各惑星、スペシャル技アイコン、戻るボタン等を
		//それぞれ画面外→画面内に移動させる
		m_Evx -= m_speed;			//移動速度は共通の変数を使い、敵惑星を基準に設定している。
		m_Pvx += m_speed * 0.37;	//例えばプレイヤー惑星は敵惑星ほど大きく移動する訳ではない為、
		m_Pvy -= m_speed * 0.37;	//0.37倍の値を移動速度に加算して、移動量を調節している。
		m_Svy -= m_speed * 0.37;
		m_Bvx += m_speed * 0.065;
		m_Bvy += m_speed * 0.065;

		//ボス惑星出現時、以下の処理も行う
		if (m_destroy_count == 4)
		{
			if (g_tutorial_progress == 1)
			{
				m_Boss_vx[2] -= m_speed * 0.9f;
			}
			else
			{
				m_Boss_vx[2] -= m_speed * 0.955f;
			}
			m_warning_message_x[0] = -130.0f;//ボス出現警告メッセージの初期X位置を変更する
			m_Boss_clip_pos_x = -600.0f;

			//if (g_Stage_progress == 1)//ステージ1のパンダ惑星の時のみ、以下の処理を実行。
			//{
			//	//正面を向かせる
			//	m_Boss_clip_pos_x = 256.0f;
			//	m_Boss_clip_pos_y = 128.0f;
			//}
		}

		//徐々に上記オブジェクトの画面内移動速度を減少させる
		m_speed *= 0.956f;
	}
}

//ドロー
void CObjPreparation::Draw()
{
	//▽描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	//赤色
	float red[4] = { 1.0f,0.0f,0.0f,1.0f };

	//黒色
	float black[4] = { 0.0f,0.0f,0.0f,1.0f };

	//戻るボタン用
	float back[4] = { m_Back_Button_color,m_Back_Button_color,m_Back_Button_color,1.0f };

	//ボス出現警告メッセージ用
	float warning_message[4] = { 1.0f,0.0f,0.0f,m_warning_message_alpha };

	//スペシャル技アイコン用
	float Special_icon[5][4] =
	{
		{ m_Special_icon_color[0],m_Special_icon_color[0],m_Special_icon_color[0],1.0f },
		{ m_Special_icon_color[1],m_Special_icon_color[1],m_Special_icon_color[1],1.0f },
		{ m_Special_icon_color[2],m_Special_icon_color[2],m_Special_icon_color[2],1.0f },
		{ m_Special_icon_color[3],m_Special_icon_color[3],m_Special_icon_color[3],1.0f },
		{ m_Special_icon_color[4],m_Special_icon_color[4],m_Special_icon_color[4],1.0f },	
	};

	//詳細説明(敵惑星、スペシャル技)ウインドウ用
	float detail_message_window[4] = { 1.0f,1.0f,1.0f,m_detail_message_alpha };

	//詳細説明(敵惑星、スペシャル技)フォント用
	float detail_message_font[DETAIL_MES_MAX_FONT_LINE][4] =
	{
		{ 1.0f,1.0f,1.0f,m_detail_message_alpha },//1行目は白色
		{ 1.0f,0.0f,0.0f,m_detail_message_alpha },//2行目は赤色
		{ 1.0f,1.0f,1.0f,m_detail_message_alpha },//3行目は白色
		{ 1.0f,1.0f,1.0f,m_detail_message_alpha },//4行目は白色
		{ 1.0f,1.0f,1.0f,m_detail_message_alpha },//5行目は白色
		{ 1.0f,1.0f,0.0f,m_detail_message_alpha },//6行目は黄色
	};

	//最終確認[はい]ボタン用
	float Yes[4] = {1.0f,m_Yes_Button_color,m_Yes_Button_color,1.0f };

	//最終確認[いいえ]ボタン用
	float No[4] = { m_No_Button_color,m_No_Button_color,1.0f,1.0f };

	//その他画像用
	float d[4] = { 1.0f,1.0f,1.0f,1.0f };


	//▽フォント準備
	//▼ボス惑星出現カウント
	wchar_t Until_fight_boss_count[2][14];									//14文字分格納可能な文字配列を2つ宣言
	//ボス惑星出現時
	if (m_destroy_count == 4)
	{
		swprintf_s(Until_fight_boss_count[0], L"　　　強大な惑星 出現中!");	//その文字配列に文字データを入れる
		swprintf_s(Until_fight_boss_count[1], L"");							//文字データをクリアする
	}
	//それ以外の時
	else
	{
		swprintf_s(Until_fight_boss_count[0], L"強大な惑星 接近まで");			 //その文字配列に文字データを入れる
		swprintf_s(Until_fight_boss_count[1], L"あと %d体", 3 - m_destroy_count);//その文字配列に文字データを入れる
	}

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

	//▼背景表示
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1200.0f;
	src.m_bottom = 700.0f;

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 1200.0f;
	dst.m_bottom = 700.0f;
	Draw::Draw(0, &src, &dst, d, 0.0f);

	//チュートリアル中は表示しない
	if (!(g_tutorial_progress == 1 || g_tutorial_progress == 2))
	{
		//▼戻るボタン表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = -60.0f + m_Bvy;
		dst.m_left = -60.0f + m_Bvx;
		dst.m_right = -10.0f + m_Bvx;
		dst.m_bottom = -10.0f + m_Bvy;
		Draw::Draw(56, &src, &dst, back, 0.0f);
	}

	//未撃破時のみ表示
	if (g_destroy_progress[1] == false)
	{
		//▼敵惑星2(左から2番目の敵惑星)表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = INI_PLANET;
		src.m_bottom = INI_PLANET;

		dst.m_top = INI_ENEMY_Y_POS - 30.0f;
		dst.m_left = INI_ENEMY_X_POS + 300.0f + m_Evx;
		dst.m_right = INI_ENEMY_X_POS + 400.0f + m_Evx;
		dst.m_bottom = INI_ENEMY_Y_POS + 70.0f;
		Draw::Draw(128 + 5 * (g_Stage_progress - 1), &src, &dst, d, 0.0f);
	}

	//▼ボス惑星1表示(演出用)
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = -300.0f;
	src.m_bottom = 300.0f;

	dst.m_top = 360.0f + m_Boss_vy[0];
	dst.m_left = 1260.0f + m_Boss_vx[0];
	dst.m_right = 1410.0f + m_Boss_vx[0];
	dst.m_bottom = 510.0f + m_Boss_vy[0];
	Draw::Draw(5 + 5 * (g_Stage_progress - 1), &src, &dst, d, 0.0f);

	//未撃破時のみ表示
	if (g_destroy_progress[0] == false)
	{
		//▼敵惑星1(左から1番目の敵惑星)表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = INI_PLANET;
		src.m_bottom = INI_PLANET;

		dst.m_top = INI_ENEMY_Y_POS;
		dst.m_left = INI_ENEMY_X_POS + m_Evx;
		dst.m_right = INI_ENEMY_X_POS + 200.0f + m_Evx;
		dst.m_bottom = INI_ENEMY_Y_POS + 200.0f;
		Draw::Draw(1 + 5 * (g_Stage_progress - 1), &src, &dst, d, 0.0f);
	}

	//未撃破時のみ表示
	if (g_destroy_progress[2] == false)
	{
		//▼敵惑星3(左から3番目の敵惑星)表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = INI_PLANET;
		src.m_bottom = INI_PLANET;

		dst.m_top = INI_ENEMY_Y_POS - 50.0f;
		dst.m_left = INI_ENEMY_X_POS + 600.0f + m_Evx;
		dst.m_right = INI_ENEMY_X_POS + 800.0f + m_Evx;
		dst.m_bottom = INI_ENEMY_Y_POS + 150.0f;
		Draw::Draw(3 + 5 * (g_Stage_progress - 1), &src, &dst, d, 0.0f);
	}

	//▼ボス惑星2表示(演出用)
	src.m_top = 0.0f;
	src.m_left = 600.0f;
	src.m_right = 900.0f;
	src.m_bottom = 300.0f;

	dst.m_top = 200.0f + m_Boss_vy[1];
	dst.m_left = -310.0f + m_Boss_vx[1];
	dst.m_right = -10.0f + m_Boss_vx[1];
	dst.m_bottom = 500.0f + m_Boss_vy[1];
	Draw::Draw(5 + 5 * (g_Stage_progress - 1), &src, &dst, d, 0.0f);

	//未撃破時のみ表示
	if (g_destroy_progress[3] == false)
	{
		//▼敵惑星4(左から4番目の敵惑星)表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = INI_PLANET;
		src.m_bottom = INI_PLANET;

		dst.m_top = INI_ENEMY_Y_POS + 250.0f;
		dst.m_left = INI_ENEMY_X_POS + 750.0f + m_Evx;
		dst.m_right = INI_ENEMY_X_POS + 1000.0f + m_Evx;
		dst.m_bottom = INI_ENEMY_Y_POS + 500.0f;
		Draw::Draw(4 + 5 * (g_Stage_progress - 1), &src, &dst, d, 0.0f);
	}

	//▼ボス惑星3表示
	src.m_top = 0.0f;
	src.m_left = m_Boss_clip_pos_x;
	src.m_right = -(INI_PLANET) + m_Boss_clip_pos_x;
	src.m_bottom = INI_PLANET;

	dst.m_top = 100.0f + m_Boss_vy[2];
	dst.m_left = 1400.0f + m_Boss_vx[2];
	dst.m_right = 1800.0f + m_Boss_vx[2];
	dst.m_bottom = 500.0f + m_Boss_vy[2];
	
	if (g_tutorial_progress == 1 || g_tutorial_progress == 2)
	{
		src.m_right = INI_PLANET + m_Boss_clip_pos_x;

		Draw::Draw(6, &src, &dst, d, 0.0f);
	}
	else
	{
		Draw::Draw(5 + 5 * (g_Stage_progress - 1), &src, &dst, d, 0.0f);
	}
	

	//▼プレイヤー惑星表示
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 448.0f;
	src.m_bottom = 448.0f;

	dst.m_top = 800.0f + m_Pvy;
	dst.m_left = -500.0f + m_Pvx;
	dst.m_right = -50.0f + m_Pvx + m_Psize;
	dst.m_bottom = 1250.0f + m_Pvy + m_Psize;
	Draw::Draw(47 + ((int)((g_Bar_Level + g_Ins_Level) / 2)) - 1, &src, &dst, d, 0.0f);

	//チュートリアル中は表示しない
	if (!(g_tutorial_progress == 1 || g_tutorial_progress == 2))
	{

		//▽ウインドウ表示左上 
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 800.0f;
		src.m_bottom = 790.0f;

		dst.m_top = 940.0f + m_Svy;
		dst.m_left = 360.0f;
		dst.m_right = 440.0f;
		dst.m_bottom = 1020.0 + m_Svy;
		Draw::Draw(55, &src, &dst, d, 0.0f);

		//▽ウインドウ表示左下
		src.m_top = 0.0f;
		src.m_left = 800.0f;
		src.m_right = 1600.0f;
		src.m_bottom = 795.0f;

		dst.m_top = 1020.0f + m_Svy;
		dst.m_left = 360.0f;
		dst.m_right = 440.0f;
		dst.m_bottom = 1100.0 + m_Svy;
		Draw::Draw(55, &src, &dst, d, 0.0f);

		for (int i = 0; i < 5; i++)
		{
			//▽ウインドウ表示中央上 
			src.m_top = 0.0f;
			src.m_left = 1600.0f;
			src.m_right = 2400.0f;
			src.m_bottom = 795.0f;

			dst.m_top = 940.0f + m_Svy;
			dst.m_left = 440.0f + (i * 80);
			dst.m_right = 520.0f + (i * 80);
			dst.m_bottom = 1020.0f + m_Svy;
			Draw::Draw(55, &src, &dst, d, 0.0f);

			//▽ウインドウ表示中央下 
			src.m_top = 5.0f;
			src.m_left = 2400.0f;
			src.m_right = 3200.0f;
			src.m_bottom = 800.0f;

			dst.m_top = 1020.0f + m_Svy;
			dst.m_left = 440.0f + (i * 80);
			dst.m_right = 520.0f + (i * 80);
			dst.m_bottom = 1100.0f + m_Svy;
			Draw::Draw(55, &src, &dst, d, 0.0f);
		}

		//▼ウインドウ右上
		src.m_top = 0.0f;
		src.m_left = 4000.0f;
		src.m_right = 4800.0f;
		src.m_bottom = 795.0f;

		dst.m_top = 940.0f + m_Svy;
		dst.m_left = 780.0f;
		dst.m_right = 860.0f;
		dst.m_bottom = 1020.0 + m_Svy;
		Draw::Draw(55, &src, &dst, d, 0.0f);

		//▼ウインドウ右下
		src.m_top = 5.0f;
		src.m_left = 4800.0f;
		src.m_right = 5600.0f;
		src.m_bottom = 800.0f;

		dst.m_top = 1020.0f + m_Svy;
		dst.m_left = 780.0f;
		dst.m_right = 860.0f;
		dst.m_bottom = 1100.0 + m_Svy;
		Draw::Draw(55, &src, &dst, d, 0.0f);

		//▽ウインドウ表示左上 
		src.m_top = 0.0f;
		src.m_left = -10.0f;
		src.m_right = 800.0f;
		src.m_bottom = 790.0f;

		dst.m_top = 905.0f + m_Svy;
		dst.m_left = 420.0f;
		dst.m_right = 470.0f;
		dst.m_bottom = 955.0 + m_Svy;
		Draw::Draw(55, &src, &dst, d, 0.0f);

		//▽ウインドウ表示左下
		src.m_top = 30.0f;
		src.m_left = 780.0f;
		src.m_right = 1600.0f;
		src.m_bottom = 795.0f;

		dst.m_top = 920.0f + m_Svy;
		dst.m_left = 420.0f;
		dst.m_right = 470.0f;
		dst.m_bottom = 970.0 + m_Svy;
		Draw::Draw(55, &src, &dst, d, 0.0f);

		for (int i = 0; i < 6; i++)
		{
			//▽ウインドウ表示中央上 
			src.m_top = 0.0f;
			src.m_left = 1600.0f;
			src.m_right = 2400.0f;
			src.m_bottom = 795.0f;

			dst.m_top = 905.0f + m_Svy;
			dst.m_left = 470.0f + (i * 50);
			dst.m_right = 520.0f + (i * 50);
			dst.m_bottom = 955.0f + m_Svy;
			Draw::Draw(55, &src, &dst, d, 0.0f);

			//▽ウインドウ表示中央下 
			src.m_top = 5.0f;
			src.m_left = 2400.0f;
			src.m_right = 3200.0f;
			src.m_bottom = 800.0f;

			dst.m_top = 920.0f + m_Svy;
			dst.m_left = 470.0f + (i * 50);
			dst.m_right = 520.0f + (i * 50);
			dst.m_bottom = 970.0f + m_Svy;
			Draw::Draw(55, &src, &dst, d, 0.0f);
		}

		//▼ウインドウ右上
		src.m_top = 0.0f;
		src.m_left = 4000.0f;
		src.m_right = 4800.0f;
		src.m_bottom = 795.0f;

		dst.m_top = 905.0f + m_Svy;
		dst.m_left = 740.0f;
		dst.m_right = 790.0f;
		dst.m_bottom = 955.0 + m_Svy;
		Draw::Draw(55, &src, &dst, d, 0.0f);

		//▼ウインドウ右下
		src.m_top = 5.0f;
		src.m_left = 4800.0f;
		src.m_right = 5600.0f;
		src.m_bottom = 800.0f;

		dst.m_top = 920.0f + m_Svy;
		dst.m_left = 740.0f;
		dst.m_right = 790.0f;
		dst.m_bottom = 970.0 + m_Svy;
		Draw::Draw(55, &src, &dst, d, 0.0f);


		//▼スペシャル技アイコン集表示
		for (int i = 0; i < 5; i++)
		{
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 130.0f;
			src.m_bottom = 130.0f;

			dst.m_top = 985.0f + m_Svy;
			dst.m_left = 380.0f + i * 95.0f;
			dst.m_right = 460.0f + i * 95.0f;
			dst.m_bottom = 1065.0f + m_Svy;
			Draw::Draw(57 + i, &src, &dst, Special_icon[i], 0.0f);
		}

		//▼スペシャル技選択文字画像表示
		src.m_top = 0.0f;
		src.m_left = 1.0f;
		src.m_right = 952.0f;
		src.m_bottom = 111.0f;

		dst.m_top = 915.0f + m_Svy;
		dst.m_left = 445.0f;
		dst.m_right = 765.0f;
		dst.m_bottom = 955.0f + m_Svy;
		Draw::Draw(68, &src, &dst, d, 0.0f);
	}

	//ボス出現警告メッセージ
	//Font::StrDraw(文字列,X軸,Y軸,一文字当たりのサイズ,色);
	//Font::StrDraw(Until_fight_boss_count[0], m_warning_message_x[0], m_warning_message_y[0], m_warning_message_size, warning_message);
	//Font::StrDraw(Until_fight_boss_count[1], m_warning_message_x[1] + 250.0f, m_warning_message_y[1] + 130.0f, m_warning_message_size, warning_message);


	if (m_destroy_count == 0)
	{
		//▼強大な惑星 接近まで文字画像表示
		src.m_top = 0.0f;
		src.m_left = 2.0f;
		src.m_right = 1132.0f;
		src.m_bottom = 112.0f;

		dst.m_top = m_warning_message_y[0];
		dst.m_left = m_warning_message_x[0];
		dst.m_right = m_warning_message_x[0] + (m_warning_message_size*9.5);
		dst.m_bottom = m_warning_message_y[0] + (m_warning_message_size);
		Draw::Draw(64, &src, &dst, warning_message, 0.0);

		//▼あと3体文字画像表示
		src.m_top = 4.0f;
		src.m_left = 0.0f;
		src.m_right = 502.0f;
		src.m_bottom = 112.0f;

		dst.m_top = m_warning_message_y[1]+130.0f;
		dst.m_left = m_warning_message_x[1]+250.0f;
		dst.m_right = m_warning_message_x[1] + (m_warning_message_size*4)+250.0f;
		dst.m_bottom = m_warning_message_y[1] + (m_warning_message_size)+130.0f;
		Draw::Draw(69, &src, &dst, warning_message, 0.0);
	}

	else if (m_destroy_count == 1)
	{
		//▼強大な惑星 接近まで文字画像表示
		src.m_top = 0.0f;
		src.m_left = 2.0f;
		src.m_right = 1132.0f;
		src.m_bottom = 112.0f;

		dst.m_top = m_warning_message_y[0];
		dst.m_left = m_warning_message_x[0];
		dst.m_right = m_warning_message_x[0] + (m_warning_message_size*9.5);
		dst.m_bottom = m_warning_message_y[0] + (m_warning_message_size);
		Draw::Draw(64, &src, &dst, warning_message, 0.0);

		//▼あと2体文字画像表示
		src.m_top = 4.0f;
		src.m_left = 0.0f;
		src.m_right = 502.0f;
		src.m_bottom = 112.0f;

		dst.m_top = m_warning_message_y[1] + 130.0f;
		dst.m_left = m_warning_message_x[1] + 250.0f;
		dst.m_right = m_warning_message_x[1] + (m_warning_message_size * 4) + 250.0f;
		dst.m_bottom = m_warning_message_y[1] + (m_warning_message_size)+130.0f;
		Draw::Draw(70, &src, &dst, warning_message, 0.0);
	}

	else if (m_destroy_count == 2)
	{
		//▼強大な惑星 接近まで文字画像表示
		src.m_top = 0.0f;
		src.m_left = 2.0f;
		src.m_right = 1132.0f;
		src.m_bottom = 112.0f;

		dst.m_top = m_warning_message_y[0];
		dst.m_left = m_warning_message_x[0];
		dst.m_right = m_warning_message_x[0] + (m_warning_message_size*9.5);
		dst.m_bottom = m_warning_message_y[0] + (m_warning_message_size);
		Draw::Draw(64, &src, &dst, warning_message, 0.0);

		//▼あと1体文字画像表示
		src.m_top = 4.0f;
		src.m_left = 0.0f;
		src.m_right = 502.0f;
		src.m_bottom = 112.0f;

		dst.m_top = m_warning_message_y[1] + 130.0f;
		dst.m_left = m_warning_message_x[1] + 250.0f;
		dst.m_right = m_warning_message_x[1] + (m_warning_message_size * 4) + 250.0f;
		dst.m_bottom = m_warning_message_y[1] + (m_warning_message_size)+130.0f;
		Draw::Draw(71, &src, &dst, warning_message, 0.0);
	}

	else if (m_destroy_count == 3)
	{
		//▼強大な惑星 接近まで文字画像表示
		src.m_top = 0.0f;
		src.m_left = 2.0f;
		src.m_right = 1132.0f;
		src.m_bottom = 112.0f;

		dst.m_top = m_warning_message_y[0];
		dst.m_left = m_warning_message_x[0];
		dst.m_right = m_warning_message_x[0] + (m_warning_message_size*9.5);
		dst.m_bottom = m_warning_message_y[0] + (m_warning_message_size);
		Draw::Draw(64, &src, &dst, warning_message, 0.0);

		//▼あと0体文字画像表示
		src.m_top = 4.0f;
		src.m_left = 0.0f;
		src.m_right = 502.0f;
		src.m_bottom = 112.0f;

		dst.m_top = m_warning_message_y[1] + 130.0f;
		dst.m_left = m_warning_message_x[1] + 250.0f;
		dst.m_right = m_warning_message_x[1] + (m_warning_message_size * 4) + 250.0f;
		dst.m_bottom = m_warning_message_y[1] + (m_warning_message_size)+130.0f;
		Draw::Draw(72, &src, &dst, warning_message, 0.0);
	}

	else if (m_destroy_count = 4)
	{
		//▼強大な惑星出現中文字画像表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1012.0f;
		src.m_bottom = 112.0f;

		dst.m_top = m_warning_message_y[0];
		dst.m_left = m_warning_message_x[0] + (m_warning_message_size) + 240.0f - (m_warning_message_size - 45);
		dst.m_right = m_warning_message_x[0] + (m_warning_message_size * 8.5) + 240.0f + (m_warning_message_size - 45);
		dst.m_bottom = m_warning_message_y[0] + (m_warning_message_size);

		//チュートリアル惑星の時は「惑星　出現中」という風にしたいため、
		//切り取り位置、描画位置をそれ用に調整している。
		if (g_tutorial_progress == 1 || g_tutorial_progress == 2)
		{
			src.m_left = 360.0f;

			dst.m_left = m_warning_message_x[0] + (m_warning_message_size) + 415.0f - (m_warning_message_size - 45);
			dst.m_right = m_warning_message_x[0] + (m_warning_message_size * 5.5) + 415.0f + (m_warning_message_size - 45);
		}

		Draw::Draw(63, &src, &dst, warning_message, 0.0);
	}

	//Font::StrDraw(Until_fight_boss_count[0], m_warning_message_x[0], m_warning_message_y[0], m_warning_message_size, warning_message);

	//▼詳細説明(敵惑星、スペシャル技)メッセージ表示
	//▽ウインドウ表示 
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1200.0f;
	src.m_bottom = 700.0f;

	dst.m_top = m_mou_y + m_detail_message_window_top;
	dst.m_left = m_mou_x + m_detail_message_window_left;
	dst.m_right = m_mou_x + m_detail_message_window_right;
	dst.m_bottom = m_mou_y + m_detail_message_window_bottom;
	Draw::Draw(89, &src, &dst, detail_message_window, 0.0f);

	//▽詳細説明フォント画像表示
	for (int i = 0; i < DETAIL_MES_MAX_FONT_LINE; i++)
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = m_detail_message_clip_right[i];
		src.m_bottom = m_detail_message_clip_bottom[i];

		dst.m_top = m_mou_y + m_detail_message_draw_y + i * 38.0f;
		dst.m_left = m_mou_x + m_detail_message_draw_left;
		dst.m_right = m_mou_x + m_detail_message_draw_right[i];
		dst.m_bottom = m_mou_y + m_detail_message_draw_y + 25.0f + i * 38.0f;
		Draw::Draw(122 + i, &src, &dst, detail_message_font[i], 0.0f);


		//Font::StrDraw(m_detail_message[i], m_mou_x + m_detail_message_font_x, m_mou_y + m_detail_message_draw_y + i * 40.0f, 25.0f, detail_message_font[i]);

		////▼難易度文字画像表示
		//src.m_top = 0.0f;
		//src.m_left = 0.0f;
		//src.m_right = 367.0f;
		//src.m_bottom = 117.0f;

		//dst.m_top = m_mou_y + m_detail_message_draw_y + i;
		//dst.m_left = m_mou_x + m_detail_message_font_x;
		//dst.m_right = m_mou_x + m_detail_message_font_x;
		//dst.m_bottom = m_mou_y + m_detail_message_draw_y + i;
		//Draw::Draw(73, &src, &dst, d, 0.0f);

	}

	//▼難易度を表す★画像を表示
	//ボス惑星の場合
	if (m_level_star_num >= 5)
	{
		//▼測定不能文字画像表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 379.0f;
		src.m_bottom = 90.0f;

		dst.m_top = m_mou_y + m_detail_message_draw_y + 38.0f;
		dst.m_left = m_mou_x + m_detail_message_draw_left + 100.0f;
		dst.m_right = m_mou_x + m_detail_message_draw_left + 200.0f;
		dst.m_bottom = m_mou_y + m_detail_message_draw_y + 63.0f;
		Draw::Draw(74, &src, &dst, detail_message_font[1], 0.0f);
	}
	//その他のザコ惑星の場合
	else
	{
		for (int i = 0; i < m_level_star_num; i++)
		{
			//▼★画像表示
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 101.0f;
			src.m_bottom = 107.0f;

			dst.m_top = m_mou_y + m_detail_message_draw_y + 38.0f;
			dst.m_left = m_mou_x + m_detail_message_draw_left + 100.0f + (25.0f * i);
			dst.m_right = m_mou_x + m_detail_message_draw_left + 125.0f + (25.0f * i);
			dst.m_bottom = m_mou_y + m_detail_message_draw_y + 63.0f;
			Draw::Draw(73, &src, &dst, detail_message_font[1], 0.0f);
		}
	}

	//▼敵惑星名を表示　[難易度★数を基にどの惑星か判断する]
	//※チュートリアル惑星はm_level_star_num == 1の処理の中に、
	//チュートリアルのグローバルフラグ等で更に分岐させて判断させている。
	if (m_level_star_num == 1)
	{
		if (g_tutorial_progress == 1 || g_tutorial_progress == 2)
		{
			//▼「ボロボロン」表示
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 474.0f;
			src.m_bottom = 90.0f;

			dst.m_top = m_mou_y + m_detail_message_draw_y;
			dst.m_left = m_mou_x + m_detail_message_draw_left + 100.0f;
			dst.m_right = m_mou_x + m_detail_message_draw_left + 225.0f;
			dst.m_bottom = m_mou_y + m_detail_message_draw_y + 25.0f;
			Draw::Draw(75, &src, &dst, detail_message_font[0], 0.0f);
		}
		else
		{
			//▼「O阪魂」表示
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 258.0f;
			src.m_bottom = 90.0f;

			dst.m_top = m_mou_y + m_detail_message_draw_y;
			dst.m_left = m_mou_x + m_detail_message_draw_left + 100.0f;
			dst.m_right = m_mou_x + m_detail_message_draw_left + 175.0f;
			dst.m_bottom = m_mou_y + m_detail_message_draw_y + 25.0f;
			Draw::Draw(76, &src, &dst, detail_message_font[0], 0.0f);
		}
	}
	else if (m_level_star_num == 2)
	{
		//▼「再星」表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 186.0f;
		src.m_bottom = 90.0f;

		dst.m_top = m_mou_y + m_detail_message_draw_y;
		dst.m_left = m_mou_x + m_detail_message_draw_left + 100.0f;
		dst.m_right = m_mou_x + m_detail_message_draw_left + 150.0f;
		dst.m_bottom = m_mou_y + m_detail_message_draw_y + 25.0f;
		Draw::Draw(77, &src, &dst, detail_message_font[0], 0.0f);
	}
	else if (m_level_star_num == 3)
	{
		//▼「アモイ」表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 282.0f;
		src.m_bottom = 84.0f;

		dst.m_top = m_mou_y + m_detail_message_draw_y;
		dst.m_left = m_mou_x + m_detail_message_draw_left + 100.0f;
		dst.m_right = m_mou_x + m_detail_message_draw_left + 175.0f;
		dst.m_bottom = m_mou_y + m_detail_message_draw_y + 25.0f;
		Draw::Draw(78, &src, &dst, detail_message_font[0], 0.0f);
	}
	else if (m_level_star_num == 4)
	{
		//▼「コワモーテ」表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 474.0f;
		src.m_bottom = 84.0f;

		dst.m_top = m_mou_y + m_detail_message_draw_y;
		dst.m_left = m_mou_x + m_detail_message_draw_left + 100.0f;
		dst.m_right = m_mou_x + m_detail_message_draw_left + 225.0f;
		dst.m_bottom = m_mou_y + m_detail_message_draw_y + 25.0f;
		Draw::Draw(79, &src, &dst, detail_message_font[0], 0.0f);
	}
	else if (m_level_star_num == 5)
	{
		//▼「アマテラス」表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 474.0f;
		src.m_bottom = 84.0f;

		dst.m_top = m_mou_y + m_detail_message_draw_y;
		dst.m_left = m_mou_x + m_detail_message_draw_left + 100.0f;
		dst.m_right = m_mou_x + m_detail_message_draw_left + 225.0f;
		dst.m_bottom = m_mou_y + m_detail_message_draw_y + 25.0f;
		Draw::Draw(80, &src, &dst, detail_message_font[0], 0.0f);
	}


	//▼最終確認ウインドウ表示管理フラグがtrueの時、描画。
	if (m_finalcheck_f == true)
	{
		//▼最終確認ウインドウ表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1200.0f;
		src.m_bottom = 700.0f;

		dst.m_top = 220.0f;
		dst.m_left = 320.0f;
		dst.m_right = 880.0f;
		dst.m_bottom = 480.0f;
		Draw::Draw(89, &src, &dst, d, 0.0f);

		//▼喰う？文字画像表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 337.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 250.0f;
		dst.m_left = 460.0f;
		dst.m_right = 760.0f;
		dst.m_bottom = 350.0f;
		Draw::Draw(65, &src, &dst, d, 0.0f);

		//▼はい文字画像表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 232.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 410.0f;
		dst.m_left = 410.0f;
		dst.m_right = 510.0f;
		dst.m_bottom = 460.0f;
		Draw::Draw(66, &src, &dst, Yes, 0.0f);

		//▼いいえ文字画像表示
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 352.0f;
		src.m_bottom = 112.0f;

		dst.m_top    = 410.0f;
		dst.m_left   = 650.0f;
		dst.m_right  = 800.0f;
		dst.m_bottom = 460.0f;
		Draw::Draw(67, &src, &dst, No, 0.0f);
	}



	////デバッグ用仮マウス位置表示
	//wchar_t str[256];
	//swprintf_s(str, L"x=%f,y=%f", m_mou_x, m_mou_y);
	//Font::StrDraw(str, 20.0f, 20.0f, 12.0f, d);
}

//---Enemy_message関数
//引数1　int enemy_id	:敵惑星識別番号(0:左から1番目の敵惑星　1:左から2番目の敵惑星　2:左から3番目の敵惑星　3:左から4番目の敵惑星　4:ボス惑星　5:チュートリアル惑星)
//▼内容
//マウスで選択している敵惑星が何であるかを識別し、
//それに対応する敵惑星詳細説明を表示する。
void CObjPreparation::Enemy_message(int enemy_id)
{
	//▽以下は各敵惑星毎に異なる値を代入する個別処理
	//▼左から1番目の敵惑星
	if (enemy_id == 0)
	{
		//敵惑星詳細説明ウインドウのサイズを設定
		m_detail_message_window_top = -126.0f;
		m_detail_message_window_left = 20.0f;
		m_detail_message_window_right = 320.0f;
		m_detail_message_window_bottom = 120.0f;

		//敵惑星詳細説明画像の描画位置(right以外)を設定
		m_detail_message_draw_left = 33.0f;
		m_detail_message_draw_y = -108.0f;

		//▽4行目
		//敵惑星詳細説明画像を125番に登録
		Draw::LoadImage(L"img\\テキスト\\素材\\木材50・鉄30.png", 125, TEX_SIZE_512);

		//敵惑星詳細説明画像の切り取り位置を設定
		m_detail_message_clip_right[3] = 666.0f;
		m_detail_message_clip_bottom[3] = 90.0f;

		//敵惑星詳細説明画像の描画位置(right)を設定(全角一文字の大きさは25.0f)
		m_detail_message_draw_right[3] = m_detail_message_draw_left + 175.0f;


		//▽5行目
		//敵惑星詳細説明画像を126番に登録
		Draw::LoadImage(L"img\\テキスト\\スペシャル技\\フラクチャーレイ.png", 126, TEX_SIZE_512);

		//敵惑星詳細説明画像の切り取り位置を設定
		m_detail_message_clip_right[4] = 952.0f;
		m_detail_message_clip_bottom[4] = 112.0f;

		//敵惑星詳細説明画像の描画位置(right)を設定(全角一文字の大きさは25.0f)
		m_detail_message_draw_right[4] = m_detail_message_draw_left + 200.0f;


		//▽6行目
		//敵惑星詳細説明画像を127番に登録
		Draw::LoadImage(L"img\\テキスト\\戦闘準備画面\\ブルー重視.png", 127, TEX_SIZE_512);

		//敵惑星詳細説明画像の切り取り位置を設定
		m_detail_message_clip_right[5] = 474.0f;
		m_detail_message_clip_bottom[5] = 90.0f;

		//敵惑星詳細説明画像の描画位置(right)を設定(全角一文字の大きさは25.0f)
		m_detail_message_draw_right[5] = m_detail_message_draw_left + 125.0f;

		//難易度を表す★の数を設定
		m_level_star_num = 1;
	}
	//▼左から4番目の敵惑星
	else if (enemy_id == 3)
	{
		//敵惑星詳細説明ウインドウのサイズを設定
		m_detail_message_window_top = -126.0f;
		m_detail_message_window_left = -300.0f;
		m_detail_message_window_right = 0.0f;
		m_detail_message_window_bottom = 120.0f;

		//敵惑星詳細説明画像の描画位置(right以外)を設定
		m_detail_message_draw_left = -288.0f;
		m_detail_message_draw_y = -108.0f;

		//▽4行目
		//敵惑星詳細説明画像を125番に登録
		Draw::LoadImage(L"img\\テキスト\\素材\\鉄70・アルミ80.png", 125, TEX_SIZE_512);

		//敵惑星詳細説明画像の切り取り位置を設定
		m_detail_message_clip_right[3] = 762.0f;
		m_detail_message_clip_bottom[3] = 90.0f;

		//敵惑星詳細説明画像の描画位置(right)を設定(全角一文字の大きさは25.0f)
		m_detail_message_draw_right[3] = m_detail_message_draw_left + 200.0f;


		//▽5行目
		//敵惑星詳細説明画像を126番に登録
		Draw::LoadImage(L"img\\テキスト\\スペシャル技\\イモータリティ.png", 126, TEX_SIZE_512);

		//敵惑星詳細説明画像の切り取り位置を設定
		m_detail_message_clip_right[4] = 817.0f;
		m_detail_message_clip_bottom[4] = 112.0f;

		//敵惑星詳細説明画像の描画位置(right)を設定(全角一文字の大きさは25.0f)
		m_detail_message_draw_right[4] = m_detail_message_draw_left + 175.0f;


		//▽6行目
		//敵惑星詳細説明画像を127番に登録
		Draw::LoadImage(L"img\\テキスト\\戦闘準備画面\\グリーン重視.png", 127, TEX_SIZE_512);

		//敵惑星詳細説明画像の切り取り位置を設定
		m_detail_message_clip_right[5] = 570.0f;
		m_detail_message_clip_bottom[5] = 90.0f;

		//敵惑星詳細説明画像の描画位置(right)を設定(全角一文字の大きさは25.0f)
		m_detail_message_draw_right[5] = m_detail_message_draw_left + 150.0f;



		//難易度を表す★の数を設定
		m_level_star_num = 2;
	}
	//▼左から2、3番目の敵惑星 & ボス惑星 & チュートリアル惑星
	else  //(enemy_id == 1 || enemy_id == 2 || enemy_id == 4 || enemy_id == 5)
	{
		//敵惑星詳細説明ウインドウのサイズを設定
		m_detail_message_window_top = 20.0f;
		m_detail_message_window_left = -150.0f;
		m_detail_message_window_right = 150.0f;
		m_detail_message_window_bottom = 266.0f;

		//敵惑星詳細説明画像の描画位置(right以外)を設定
		m_detail_message_draw_left = -138.0f;
		m_detail_message_draw_y = 38.0f;

		
		//▼左から2番目の敵惑星
		if (enemy_id == 1)
		{
			//▽4行目
			//敵惑星詳細説明画像を125番に登録
			Draw::LoadImage(L"img\\テキスト\\素材\\プラスチック40・ガス50.png", 125, TEX_SIZE_512);

			//敵惑星詳細説明画像の切り取り位置を設定
			m_detail_message_clip_right[3] = 1147.0f;
			m_detail_message_clip_bottom[3] = 91.0f;

			//敵惑星詳細説明画像の描画位置(right)を設定(全角一文字の大きさは25.0f)
			m_detail_message_draw_right[3] = m_detail_message_draw_left + 275.0f;


			//▽5行目
			//敵惑星詳細説明画像を126番に登録
			Draw::LoadImage(L"img\\テキスト\\スペシャル技\\エクスプロージョン.png", 126, TEX_SIZE_512);

			//敵惑星詳細説明画像の切り取り位置を設定
			m_detail_message_clip_right[4] = 1072.0f;
			m_detail_message_clip_bottom[4] = 112.0f;

			//敵惑星詳細説明画像の描画位置(right)を設定(全角一文字の大きさは25.0f)
			m_detail_message_draw_right[4] = m_detail_message_draw_left + 225.0f;


			//▽6行目
			//敵惑星詳細説明画像を127番に登録
			Draw::LoadImage(L"img\\テキスト\\戦闘準備画面\\レッド重視.png", 127, TEX_SIZE_512);

			//敵惑星詳細説明画像の切り取り位置を設定
			m_detail_message_clip_right[5] = 467.0f;
			m_detail_message_clip_bottom[5] = 90.0f;

			//敵惑星詳細説明画像の描画位置(right)を設定(全角一文字の大きさは25.0f)
			m_detail_message_draw_right[5] = m_detail_message_draw_left + 125.0f;

			

			//難易度を表す★の数を設定
			m_level_star_num = 3;
		}
		//▼左から3番目の敵惑星
		else if (enemy_id == 2)
		{
			//▽4行目
			//敵惑星詳細説明画像を125番に登録	(画像がなかったため適用してない)
			Draw::LoadImage(L"img\\テキスト\\素材\\銀65・ガス50.png", 125, TEX_SIZE_512);

			//敵惑星詳細説明画像の切り取り位置を設定
			m_detail_message_clip_right[3] = 666.0f;
			m_detail_message_clip_bottom[3] = 90.0f;

			//敵惑星詳細説明画像の描画位置(right)を設定(全角一文字の大きさは25.0f)
			m_detail_message_draw_right[3] = m_detail_message_draw_left + 200.0f;


			//▽5行目
			//敵惑星詳細説明画像を126番に登録
			Draw::LoadImage(L"リミットブレイク.png", 126, TEX_SIZE_512);

			//敵惑星詳細説明画像の切り取り位置を設定
			m_detail_message_clip_right[4] = 952.0f;
			m_detail_message_clip_bottom[4] = 112.0f;

			//敵惑星詳細説明画像の描画位置(right)を設定(全角一文字の大きさは25.0f)
			m_detail_message_draw_right[4] = m_detail_message_draw_left + 200.0f;


			//▽6行目
			//敵惑星詳細説明画像を127番に登録
			Draw::LoadImage(L"img\\テキスト\\戦闘準備画面\\ホワイト重視.png", 127, TEX_SIZE_512);

			//敵惑星詳細説明画像の切り取り位置を設定
			m_detail_message_clip_right[5] = 570.0f;
			m_detail_message_clip_bottom[5] = 90.0f;

			//敵惑星詳細説明画像の描画位置(right)を設定(全角一文字の大きさは25.0f)
			m_detail_message_draw_right[5] = m_detail_message_draw_left + 150.0f;



			//難易度を表す★の数を設定
			m_level_star_num = 4;
		}
		//▼ボス惑星
		else if (enemy_id == 4)
		{
			//▽4行目
			//敵惑星詳細説明画像を125番に登録
			Draw::LoadImage(L"img\\テキスト\\戦闘準備画面\\無し.png", 125, TEX_SIZE_512);

			//敵惑星詳細説明画像の切り取り位置を設定
			m_detail_message_clip_right[3] = 180.0f;
			m_detail_message_clip_bottom[3] = 90.0f;

			//敵惑星詳細説明画像の描画位置(right)を設定(全角一文字の大きさは25.0f)
			m_detail_message_draw_right[3] = m_detail_message_draw_left + 50.0f;


			//▽5行目
			//敵惑星詳細説明画像を126番に登録
			Draw::LoadImage(L"img\\テキスト\\戦闘準備画面\\攻撃傾向.png", 126, TEX_SIZE_512);

			//敵惑星詳細説明画像の切り取り位置を設定
			m_detail_message_clip_right[4] = 378.0f;
			m_detail_message_clip_bottom[4] = 90.0f;

			//敵惑星詳細説明画像の描画位置(right)を設定(全角一文字の大きさは25.0f)
			m_detail_message_draw_right[4] = m_detail_message_draw_left + 100.0f;


			//▽6行目
			//敵惑星詳細説明画像を127番に登録
			Draw::LoadImage(L"img\\テキスト\\戦闘準備画面\\不明.png", 127, TEX_SIZE_512);

			//敵惑星詳細説明画像の切り取り位置を設定
			m_detail_message_clip_right[5] = 186.0f;
			m_detail_message_clip_bottom[5] = 90.0f;

			//敵惑星詳細説明画像の描画位置(right)を設定(全角一文字の大きさは25.0f)
			m_detail_message_draw_right[5] = m_detail_message_draw_left + 50.0f;



			//難易度を表す★の数を設定
			m_level_star_num = 5;
		}
		//▼チュートリアル惑星
		else if (enemy_id == 5)
		{
			//敵惑星詳細説明ウインドウのサイズを設定
			m_detail_message_window_top = -126.0f;
			m_detail_message_window_left = 20.0f;
			m_detail_message_window_right = 320.0f;
			m_detail_message_window_bottom = 120.0f;

			//敵惑星詳細説明画像の描画位置(right以外)を設定
			m_detail_message_draw_left = 33.0f;
			m_detail_message_draw_y = -108.0f;


			//▽4行目
			//敵惑星詳細説明画像を125番に登録
			Draw::LoadImage(L"img\\テキスト\\スペシャル技\\オーバーワーク.png", 125, TEX_SIZE_512);

			//敵惑星詳細説明画像の切り取り位置を設定
			m_detail_message_clip_right[3] = 832.0f;
			m_detail_message_clip_bottom[3] = 112.0f;

			//敵惑星詳細説明画像の描画位置(right)を設定(全角一文字の大きさは25.0f)
			m_detail_message_draw_right[3] = m_detail_message_draw_left + 175.0f;


			//▽5行目
			//敵惑星詳細説明画像を126番に登録	(そもそもチュートリアル惑星の5行目には何も表示しない)
			//Draw::LoadImage(L"", 126, TEX_SIZE_512);

			//敵惑星詳細説明画像の切り取り位置を設定
			m_detail_message_clip_right[4] = 0.0f;
			m_detail_message_clip_bottom[4] = 0.0f;

			//敵惑星詳細説明画像の描画位置(right)を設定(全角一文字の大きさは25.0f)
			m_detail_message_draw_right[4] = m_detail_message_draw_left + 0.0f;


			//▽6行目
			//敵惑星詳細説明画像を127番に登録
			Draw::LoadImage(L"img\\テキスト\\戦闘準備画面\\ホワイト重視.png", 127, TEX_SIZE_512);

			//敵惑星詳細説明画像の切り取り位置を設定
			m_detail_message_clip_right[5] = 570.0f;
			m_detail_message_clip_bottom[5] = 90.0f;

			//敵惑星詳細説明画像の描画位置(right)を設定(全角一文字の大きさは25.0f)
			m_detail_message_draw_right[5] = m_detail_message_draw_left + 150.0f;



			//難易度を表す★の数を設定
			m_level_star_num = 1;
		}
	}


	//▽以下は各敵惑星関係なく行う共通処理
	//▽1行目
	//敵惑星詳細説明画像を122番に登録
	Draw::LoadImage(L"img\\テキスト\\戦闘準備画面\\惑星名.png", 122, TEX_SIZE_512);

	//敵惑星詳細説明画像の切り取り位置を設定
	m_detail_message_clip_right[0] = 342.0f;
	m_detail_message_clip_bottom[0] = 90.0f;

	//敵惑星詳細説明画像の描画位置(right)を設定(全角一文字の大きさは25.0f)
	m_detail_message_draw_right[0] = m_detail_message_draw_left + 89.0f;


	//▽2行目
	//敵惑星詳細説明画像を123番に登録
	Draw::LoadImage(L"img\\テキスト\\戦闘準備画面\\難易度.png", 123, TEX_SIZE_512);

	//敵惑星詳細説明画像の切り取り位置を設定
	m_detail_message_clip_right[1] = 367.0f;
	m_detail_message_clip_bottom[1] = 117.0f;

	//敵惑星詳細説明画像の描画位置(right)を設定(全角一文字の大きさは25.0f)
	m_detail_message_draw_right[1] = m_detail_message_draw_left + 75.0f;


	//▽3行目
	//敵惑星詳細説明画像を124番に登録
	Draw::LoadImage(L"img\\テキスト\\戦闘準備画面\\取得可能な資材・技.png", 124, TEX_SIZE_512);

	//敵惑星詳細説明画像の切り取り位置を設定
	m_detail_message_clip_right[2] = 1117.0f;
	m_detail_message_clip_bottom[2] = 117.0f;

	//敵惑星詳細説明画像の描画位置(right)を設定(全角一文字の大きさは25.0f)
	m_detail_message_draw_right[2] = m_detail_message_draw_left + 225.0f;



	m_detail_message_alpha = 1.0f;//敵惑星詳細説明を表示

	//左クリックされたらフラグを立て、最終確認ウインドウを開く
	if (m_mou_l == true && g_tutorial_progress != 1)
	{
		//左クリック押したままの状態では入力出来ないようにしている
		if (m_key_lf == true)
		{
			m_key_lf = false;

			m_detail_message_alpha = 0.0f;//敵惑星詳細説明を非表示にする

			g_Challenge_enemy = enemy_id;//マウス選択中の敵惑星識別番号を取得

			m_finalcheck_f = true;//最終確認ウインドウを表示する

		    //選択音
			Audio::Start(1);
			return;
		}
	}
	else
	{
		m_key_lf = true;
	}
}

//---Special_message関数
//引数1　int special_id	:スペシャル技アイコン識別番号(0:エクスプロージョン　1:フラクチャーレイ　2:イモータリティ　3:オーバーワーク　4:リミットブレイク)
//▼内容
//マウスで選択しているスペシャル技アイコンが何であるかを識別し、
//それに対応するスペシャル技詳細説明を表示する。
void CObjPreparation::Special_message(int special_id)
{
	//チュートリアル中は実行しない
	if (g_tutorial_progress == 1 || g_tutorial_progress == 2)
	{
		return;
	}

	//▼スペシャル技アイコンが黒色(未習得)の時の処理
	if (m_Special_icon_color[special_id] == 0.0f)
	{
		//スペシャル技詳細説明ウインドウのサイズを設定
		m_detail_message_window_top = -50.0f;
		m_detail_message_window_left = -50.0f;
		m_detail_message_window_right = 50.0f;
		m_detail_message_window_bottom = 0.0f;

		//スペシャル技詳細説明画像の描画位置(right以外)を設定
		m_detail_message_draw_left = -38.0f;
		m_detail_message_draw_y = -113.0f;

		//▽3行目
		//スペシャル技詳細説明画像を124番に登録
		Draw::LoadImage(L"img\\テキスト\\スペシャル技\\未習得.png", 124, TEX_SIZE_512);

		//スペシャル技詳細説明画像の切り取り位置を設定
		m_detail_message_clip_right[2] = 352.0f;
		m_detail_message_clip_bottom[2] = 112.0f;

		//スペシャル技詳細説明画像の描画位置(right)を設定(全角一文字の大きさは25.0f)
		m_detail_message_draw_right[2] = m_detail_message_draw_left + 75.0f;

		//3行目以外の画像の描画位置rightをleftと同じにする事で表示しない処理
		for (int i = 0; i < DETAIL_MES_MAX_FONT_LINE; i++)
		{
			if (i != 2)
			{
				m_detail_message_draw_right[i] = m_detail_message_draw_left;
			}
		}

		//難易度★を表示しないようにする
		m_level_star_num = 0;
	}
	//▼スペシャル技アイコンが灰色(クリックで装備可)、もしくは白色(装備中)の時の処理
	else  //(m_Special_icon_color[special_id] == 0.4f || m_Special_icon_color[special_id] == 1.0f)
	{
		//スペシャル技詳細説明ウインドウのサイズを設定
		m_detail_message_window_top = -205.0f;
		m_detail_message_window_left = -150.0f;
		m_detail_message_window_right = 150.0f;
		m_detail_message_window_bottom = 0.0f;

		//スペシャル技詳細説明フォントの位置(right以外)を設定
		m_detail_message_draw_left = -138.0f;
		m_detail_message_draw_y = -225.0f;


		//▽以下は灰色、白色のどちらでも行う共通処理
		//スペシャル技詳細説明フォント設定
		if (special_id == 0)
		{
			//▽2行目
			//スペシャル技詳細説明画像を123番に登録
			Draw::LoadImage(L"img\\テキスト\\スペシャル技\\エクスプロージョン.png", 123, TEX_SIZE_512);

			//スペシャル技詳細説明画像の切り取り位置を設定
			m_detail_message_clip_right[1] = 1072.0f;
			m_detail_message_clip_bottom[1] = 112.0f;

			//スペシャル技詳細説明画像の描画位置(right)を設定(全角一文字の大きさは25.0f)
			m_detail_message_draw_right[1] = m_detail_message_draw_left + 225.0f;


			//▽3行目
			//スペシャル技詳細説明画像を124番に登録
			Draw::LoadImage(L"相手の惑星に.png", 124, TEX_SIZE_512);

			//スペシャル技詳細説明画像の切り取り位置を設定
			m_detail_message_clip_right[2] = 713.0f;
			m_detail_message_clip_bottom[2] = 112.0f;

			//スペシャル技詳細説明画像の描画位置(right)を設定(全角一文字の大きさは25.0f)
			m_detail_message_draw_right[2] = m_detail_message_draw_left + 150.0f;


			//▽4行目
			//スペシャル技詳細説明画像を125番に登録
			Draw::LoadImage(L"固定ダメージを与える.png", 125, TEX_SIZE_512);

			//スペシャル技詳細説明画像の切り取り位置を設定
			m_detail_message_clip_right[3] = 1182.0f;
			m_detail_message_clip_bottom[3] = 112.0f;

			//スペシャル技詳細説明画像の描画位置(right)を設定(全角一文字の大きさは25.0f)
			m_detail_message_draw_right[3] = m_detail_message_draw_left + 250.0f;
		}
		else if (special_id == 1)
		{
			//▽2行目
			//スペシャル技詳細説明画像を123番に登録
			Draw::LoadImage(L"img\\テキスト\\スペシャル技\\フラクチャーレイ.png", 123, TEX_SIZE_512);

			//スペシャル技詳細説明画像の切り取り位置を設定
			m_detail_message_clip_right[1] = 952.0f;
			m_detail_message_clip_bottom[1] = 112.0f;

			//スペシャル技詳細説明画像の描画位置(right)を設定(全角一文字の大きさは25.0f)
			m_detail_message_draw_right[1] = m_detail_message_draw_left + 200.0f;


			//▽3行目
			//スペシャル技詳細説明画像を124番に登録
			Draw::LoadImage(L"選択ライン上の.png", 124, TEX_SIZE_512);

			//スペシャル技詳細説明画像の切り取り位置を設定
			m_detail_message_clip_right[2] = 832.0f;
			m_detail_message_clip_bottom[2] = 112.0f;

			//スペシャル技詳細説明画像の描画位置(right)を設定(全角一文字の大きさは25.0f)
			m_detail_message_draw_right[2] = m_detail_message_draw_left + 175.0f;


			//▽4行目
			//スペシャル技詳細説明画像を125番に登録
			Draw::LoadImage(L"相手ポッド等を破壊する.png", 125, TEX_SIZE_512);

			//スペシャル技詳細説明画像の切り取り位置を設定
			m_detail_message_clip_right[3] = 1304.0f;
			m_detail_message_clip_bottom[3] = 112.0f;

			//スペシャル技詳細説明画像の描画位置(right)を設定(全角一文字の大きさは25.0f)
			m_detail_message_draw_right[3] = m_detail_message_draw_left + 275.0f;
		}
		else if (special_id == 2)
		{
			//▽2行目
			//スペシャル技詳細説明画像を123番に登録
			Draw::LoadImage(L"img\\テキスト\\スペシャル技\\イモータリティ.png", 123, TEX_SIZE_512);

			//スペシャル技詳細説明画像の切り取り位置を設定
			m_detail_message_clip_right[1] = 817.0f;
			m_detail_message_clip_bottom[1] = 112.0f;

			//スペシャル技詳細説明画像の描画位置(right)を設定(全角一文字の大きさは25.0f)
			m_detail_message_draw_right[1] = m_detail_message_draw_left + 175.0f;


			//▽3行目
			//スペシャル技詳細説明画像を124番に登録
			Draw::LoadImage(L"約10秒間.png", 124, TEX_SIZE_512);

			//スペシャル技詳細説明画像の切り取り位置を設定
			m_detail_message_clip_right[2] = 532.0f;
			m_detail_message_clip_bottom[2] = 112.0f;

			//スペシャル技詳細説明画像の描画位置(right)を設定(全角一文字の大きさは25.0f)
			m_detail_message_draw_right[2] = m_detail_message_draw_left + 100.0f;


			//▽4行目
			//スペシャル技詳細説明画像を125番に登録
			Draw::LoadImage(L"無敵となる.png", 125, TEX_SIZE_512);

			//スペシャル技詳細説明画像の切り取り位置を設定
			m_detail_message_clip_right[3] = 584.0f;
			m_detail_message_clip_bottom[3] = 112.0f;

			//スペシャル技詳細説明画像の描画位置(right)を設定(全角一文字の大きさは25.0f)
			m_detail_message_draw_right[3] = m_detail_message_draw_left + 125.0f;
		}
		else if (special_id == 3)
		{
			//▽2行目
			//スペシャル技詳細説明画像を123番に登録
			Draw::LoadImage(L"img\\テキスト\\スペシャル技\\オーバーワーク.png", 123, TEX_SIZE_512);

			//スペシャル技詳細説明画像の切り取り位置を設定
			m_detail_message_clip_right[1] = 832.0f;
			m_detail_message_clip_bottom[1] = 112.0f;

			//スペシャル技詳細説明画像の描画位置(right)を設定(全角一文字の大きさは25.0f)
			m_detail_message_draw_right[1] = m_detail_message_draw_left + 175.0f;


			//▽3行目
			//スペシャル技詳細説明画像を124番に登録
			Draw::LoadImage(L"10秒間ポッド生産速度.png", 124, TEX_SIZE_512);

			//スペシャル技詳細説明画像の切り取り位置を設定
			m_detail_message_clip_right[2] = 1252.0f;
			m_detail_message_clip_bottom[2] = 112.0f;

			//スペシャル技詳細説明画像の描画位置(right)を設定(全角一文字の大きさは25.0f)
			m_detail_message_draw_right[2] = m_detail_message_draw_left + 262.5f;


			//▽4行目
			//スペシャル技詳細説明画像を125番に登録
			Draw::LoadImage(L"ミサイル生産速度UP.png", 125, TEX_SIZE_512);

			//スペシャル技詳細説明画像の切り取り位置を設定
			m_detail_message_clip_right[3] = 1134.0f;
			m_detail_message_clip_bottom[3] = 112.0f;

			//スペシャル技詳細説明画像の描画位置(right)を設定(全角一文字の大きさは25.0f)
			m_detail_message_draw_right[3] = m_detail_message_draw_left + 237.5f;
		}
		else  //(special_id == 4)
		{
			//▽2行目
			//スペシャル技詳細説明画像を123番に登録
			Draw::LoadImage(L"リミットブレイク.png", 123, TEX_SIZE_512);

			//スペシャル技詳細説明画像の切り取り位置を設定
			m_detail_message_clip_right[1] = 952.0f;
			m_detail_message_clip_bottom[1] = 112.0f;

			//スペシャル技詳細説明画像の描画位置(right)を設定(全角一文字の大きさは25.0f)
			m_detail_message_draw_right[1] = m_detail_message_draw_left + 200.0f;


			//▽3行目
			//スペシャル技詳細説明画像を124番に登録
			Draw::LoadImage(L"出撃する.png", 124, TEX_SIZE_512);

			//スペシャル技詳細説明画像の切り取り位置を設定
			m_detail_message_clip_right[2] = 464.0f;
			m_detail_message_clip_bottom[2] = 112.0f;

			//スペシャル技詳細説明画像の描画位置(right)を設定(全角一文字の大きさは25.0f)
			m_detail_message_draw_right[2] = m_detail_message_draw_left + 100.0f;


			//▽4行目
			//スペシャル技詳細説明画像を125番に登録
			Draw::LoadImage(L"ポッド5機の攻撃力UP.png", 125, TEX_SIZE_512);

			//スペシャル技詳細説明画像の切り取り位置を設定
			m_detail_message_clip_right[3] = 1222.0f;
			m_detail_message_clip_bottom[3] = 112.0f;

			//スペシャル技詳細説明画像の描画位置(right)を設定(全角一文字の大きさは25.0f)
			m_detail_message_draw_right[3] = m_detail_message_draw_left + 262.5f;
		}
		

		//1行目と5行目は使用しないので、
		//その行の画像の描画位置rightをleftと同じにする事で表示しない処理
		m_detail_message_draw_right[0] = m_detail_message_draw_left;
		m_detail_message_draw_right[4] = m_detail_message_draw_left;

		//難易度★を表示しないようにする
		m_level_star_num = 0;


		//▽以下はスペシャル技アイコンが灰色(クリックで装備可)の時のみ行う処理
		if (m_Special_icon_color[special_id] == 0.4f)
		{
			//▽6行目
			//スペシャル技詳細説明画像を127番に登録
			Draw::LoadImage(L"クリックで装備可.png", 127, TEX_SIZE_512);

			//スペシャル技詳細説明画像の切り取り位置を設定
			m_detail_message_clip_right[5] = 952.0f;
			m_detail_message_clip_bottom[5] = 112.0f;

			//スペシャル技詳細説明画像の描画位置(right)を設定(全角一文字の大きさは25.0f)
			m_detail_message_draw_right[5] = m_detail_message_draw_left + 200.0f;

			//左クリックされたらマウスで選択中のスペシャル技を装備する
			if (m_mou_l == true)
			{
				//左クリック押したままの状態では入力出来ないようにしている
				if (m_key_lf == true)
				{
					m_key_lf = false;

					//未装備状態の時は以下の処理を飛ばす
					if (g_Special_equipment != 0)
					{
						//現在装備中のスペシャル技アイコンのカラーを灰色にする
						m_Special_icon_color[g_Special_equipment - 1] = 0.4f;
					}

					//マウス選択中のスペシャル技を装備する
					g_Special_equipment = special_id + 1;

					//マウス選択中のスペシャル技アイコンのカラーを白色にする
					m_Special_icon_color[g_Special_equipment - 1] = 1.0f;

					//選択音
					Audio::Start(1);
				}
			}
			else
			{
				m_key_lf = true;
			}
		}

		//▽以下はスペシャル技アイコンが白色(装備中)の時のみ行う処理
		else  //(m_Special_icon_color[special_id] == 1.0f)
		{
			//▽6行目
			//スペシャル技詳細説明画像を127番に登録
			Draw::LoadImage(L"img\\テキスト\\スペシャル技\\装備中.png", 127, TEX_SIZE_512);

			//スペシャル技詳細説明画像の切り取り位置を設定
			m_detail_message_clip_right[5] = 352.0f;
			m_detail_message_clip_bottom[5] = 112.0f;

			//スペシャル技詳細説明画像の描画位置(right)を設定(全角一文字の大きさは25.0f)
			m_detail_message_draw_right[5] = m_detail_message_draw_left + 75.0f;

			//左クリックされたら現在装備中のスペシャル技を外し、未装備状態にする
			if (m_mou_l == true)
			{
				//左クリック押したままの状態では入力出来ないようにしている
				if (m_key_lf == true)
				{
					m_key_lf = false;

					//現在装備中のスペシャル技アイコンのカラーを灰色にする
					m_Special_icon_color[g_Special_equipment - 1] = 0.4f;

					//未装備状態にする
					g_Special_equipment = 0;

					//戻るボタン音
					Audio::Start(2);
				}
			}
			else
			{
				m_key_lf = true;
			}
		}
	}


	m_detail_message_alpha = 1.0f;//スペシャル技詳細説明を表示
}
