//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjFight.h"
#include "UtilityModule.h"

//使用するネームスペース
using namespace GameL;

//static変数の定義
bool CObjFight::battle_start = false;
bool CObjFight::battle_end = false;
float CObjFight::Pla_One_pat_dem[3] = { 1.0f,1.0f,1.0f };
float CObjFight::Ene_One_pat_dem[3] = { 1.0f,1.0f,1.0f };
int CObjFight::p_pnam = 0;
int CObjFight::e_pnam = 0;
float CObjFight::damage_buff[2] = { 1.0f,1.0f };

#define INI_COLOR (0.5f) //全カラー明度の初期値(アイコン未選択中のカラー)

//c = cnt(戦闘時間),e_n = m_ene_nam(敵ナンバー)
CObjFight::CObjFight(int c)
{
	m_cnt = c * 60;
}

//イニシャライズ
void CObjFight::Init()
{
	m_mou_x = 0.0f;	//マウスX座標
	m_mou_y = 0.0f; //マウスY座標
	m_mou_r = false;//右クリック
	m_mou_l = false;//左クリック
	
	m_line = 1;		//初期値、
	m_line_nam = 1; //初期値、真ん中選択

	m_cnt = 60 * 300;//戦闘時間(60 * X = X秒)
	m_a = 1;		//初期値、不透明

	m_ex = 0;
	m_ey = 0;

	m_scale_down_cnt = 0;
	m_scale_down_speed = 0.04f;
	m_font_a = 1.0f;

	m_start_count = 60 * 3;	//3秒経過後、戦闘開始
	m_start_count_f = false;

	m_end_f = false;

	//m_line_dis = false;

	m_key_U_f = false;
	m_key_D_f = false;

	m_special_f = false;

	//m_line_choice = 1;

	m_cuta =0;

	//▼以下のstatic変数は他シーンから戦闘画面に入る度に初期化を行う
	battle_start = false;
	battle_end = false;
	
	for (int i = 0; i < 3; i++)
	{
		Pla_One_pat_dem[i] = 1.0f;
		Ene_One_pat_dem[i] = 1.0f;
	}
	
	p_pnam = 0;
	e_pnam = 0;

	for (int i = 0; i < 2; i++)
	{
		damage_buff[i] = 1.0f;
	}

	Hits::SetHitBox(this, 400, 310, 400, 60, ELEMENT_LINE, OBJ_FIGHT, 1);


	//▼背面表示させたい演出にて使用する変数の初期化
	for (int i = 0; i < 2; i++)
	{
		m_Explosion_f[i] = false;
		m_Explosion_size[i] = 0.0f;
		m_Explosion_width[i] = 200.0f;
	}

	m_prey_f = -1;
	m_ani[0] = 0;//アニメーションデータの初期化
	m_ani[1] = 1;
	m_ani[2] = 2;
	m_ani[3] = 1;
}

//アクション
void CObjFight::Action()
{
	//▼戦闘開始前は戦闘処理を実行しないようにする＆
	//戦闘開始カウントの処理
	if (battle_start == false)
	{
		//戦闘前演出オブジェクトから「戦闘開始カウント」開始フラグをtrueにした時に実行
		//戦闘開始カウントを徐々に減らしていき、0になった時、戦闘開始フラグ等を立てる。
		if (m_start_count <= 60 * 0)
		{
			//ポーズ画面等で戦闘を一時停止する際、
			//battle_startの[true / false]で一時停止を行うが、
			//再度この戦闘開始カウントの処理が行われると厄介である為、
			//[m_start_count_f]をfalseに、[m_start_count]を初期値に戻す事で、
			//この処理が行われないようにする。
			m_start_count_f = false;
			m_start_count = 60 * 3;

			battle_start = true;//戦闘開始フラグを立てる

			if (g_tutorial_progress == 2)
			{
				//ObjMessageのメッセージ進行度を増加させる
				CObjMessage* message = (CObjMessage*)Objs::GetObj(OBJ_MESSAGE);
				message->Setprogress(1);
			}
		}
		else if (m_start_count_f == true && g_is_operatable == true)
		{
			m_start_count--;//戦闘開始カウントダウン
		}
		
		return;
	}

	//戦闘開始のカウントが終わった時にラインを表示させる
	//※一度しか動かない
	//if (m_line_dis == false) {
	//	m_line_nam = 1;
	//	m_line_dis = true;
	//}

	//▼戦闘終了間際(残り1秒)のタイミングで戦闘終了フラグを立てる
	if (m_cnt <= 60)
	{
		battle_end = true;	//戦闘終了フラグを立てる
	}

	//チュートリアル中は戦闘時間が減少しない
	if (!(2 <= g_tutorial_progress && g_tutorial_progress <= 5))
	{
		if (m_cnt > 0)	//0より大きい時
			m_cnt--;	//カウントダウン
	}

	//背景拡大処理
	//※戦闘終了後は実際されない。
	if (battle_end == false)
	{
		m_scale_down_cnt += m_scale_down_speed;
		if (m_scale_down_speed > 0)
			m_scale_down_speed -= 0.00001f;
	}

	//戦闘開始時表示される"スタート"の文字を徐々に透明化
	if (m_scale_down_cnt >= 0.5 && m_font_a >= 0) {
		m_font_a -= 0.01f;
	}

	//マウスの位置を取得
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//マウスのボタンの状態
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	m_line = 6;//常に選択前ラインを初期化


	//チュートリアル中は操作出来ないようにする条件文
	if (g_tutorial_progress >= 6)
	{
		//ラインを矢印キーで選択するときの処理
		if (m_key_U_f == false && Input::GetVKey(VK_UP) == true) {

			//選択中のラインが一番上に来た時に下に移動させる
			if (m_line_nam <= 0) {
				m_line_nam = 2;
			}
			else {
				m_line_nam--;
			}
			m_key_U_f = true;
		}

		if (m_key_D_f == false && Input::GetVKey(VK_DOWN) == true) {

			//選択中のラインが一番下に来た時に上に移動させる
			if (m_line_nam >= 2) {
				m_line_nam = 0;
			}
			else {
				m_line_nam++;
			}
			m_key_D_f = true;
		}

		//選択ラインのX軸幅内にマウスカーソルがある且つ、上下のキーが入力されていないとき
		//※キーを押してる間はマウスに反応させないため
		if (400 <= m_mou_x && m_mou_x <= 800 && m_key_U_f == false && m_key_D_f == false) {

			if (200 <= m_mou_y && m_mou_y <= 250) {
				if (m_mou_l == true) { m_line_nam = 0; }//上ライン------
				else { m_line = 0; }
			}
			else if (310 <= m_mou_y && m_mou_y <= 360) {
				if (m_mou_l == true) { m_line_nam = 1; }//中ライン------
				else { m_line = 1; }
			}
			else if (420 <= m_mou_y && m_mou_y <= 470) {
				if (m_mou_l == true) { m_line_nam = 2; }//下ライン------
				else { m_line = 2; }
			}
			else {};//ライン外何もしない

		}
		//else if (m_key_U_f == true || m_key_D_f == true) {
		//	if (m_line_nam == 0) {
		//		m_line_nam = 0;
		//	}
		//	else if (m_line_nam == 1) {
		//		m_line_nam = 1;
		//	}
		//	else if (m_line_nam == 2) {
		//		m_line_nam = 2;
		//	}
		//}


		//キーフラグ制御---------------
		if (Input::GetVKey(VK_UP) == false) {

			m_key_U_f = false;

		}

		if (Input::GetVKey(VK_DOWN) == false) {

			m_key_D_f = false;

		}
	}
	//以下の処理はチュートリアル中のみ実行される。
	else if (g_tutorial_progress == 5)
	{
		if (400 <= m_mou_x && m_mou_x <= 800) 
		{
			if (200 <= m_mou_y && m_mou_y <= 250) 
			{	
				//上ライン------
				if (m_mou_l == true) 
				{ 
					//矢印を非表示にさせる
					CObjMessage* message = (CObjMessage*)Objs::GetObj(OBJ_MESSAGE);
					message->Setarrow(0);

					m_line_nam = 0; 
				}
				else 
				{ 
					m_line = 0; 
				}
			}
		}
	}
	


	//▼クリア処理
	//エネミー毎に取得出来る資源等は違うため、
	//以下でそれぞれ引数を設定し、ObjFightClearを作成する。
	if (m_end_f == true)
	{
		m_end_f = false;

		//▽引数メモ
		//以下の順番で引数を入れて下さい。
		//(住人数, サイズ(HP), 資材A名前, 資材Aアドレス, 資材数A, 資材B名前, 資材Bアドレス, 資材数B, スペシャル技)
		//▽詳細説明
		// 住人数:		　獲得できる住人数。この値分、住人数が増加する。
		// サイズ(HP):	  獲得できるサイズ(HP)。この値分、サイズ(HP)が上昇する。
		// 資材A名前:	　獲得出来る資材(1つ目)の名前を入力してください。
		// 資材Aアドレス: 獲得出来る資材(1つ目)のグローバル変数アドレスを入力してください。
		// 資材数A:		  獲得出来る資材(1つ目)の数。この値分、資材数が増加する。
		// 資材B名前:	　獲得出来る資材(2つ目)の名前。※2つ目がない場合、入力しないでください。
		// 資材Bアドレス: 獲得出来る資材(2つ目)のアドレス。※2つ目がない場合、入力しないでください。
		// 資材数B:		  獲得出来る資材(2つ目)の数。※2つ目がない場合、入力しないでください。
		// スペシャル技:  獲得できるスペシャル技。以下の数字を入力すると、その値に対応するスペシャル技を取得出来ます。※獲得できない場合は0を入力してください。
		//	(1:Explosion　2:Fracture_Ray　3:Immortality　4:リミットブレイク　5:ステロイド投与)

		//左から１番目(たこ焼き)
		if (g_Challenge_enemy == 0)									
		{				
			CObjFightClear* crer = new CObjFightClear(5500, 240, L"木材", &g_Wood_num, 50, L"鉄", &g_Iron_num, 70, 2);
			Objs::InsertObj(crer, OBJ_FIGHT_CLEAR, 15);
		}
		//左から２番目(モアイ)
		if (g_Challenge_enemy == 1)									
		{				
			CObjFightClear* crer = new CObjFightClear(10000, 430, L"プラスチック",  &g_Plastic_num, 40, L"ガス", &g_gus_num, 50, 1);
			Objs::InsertObj(crer, OBJ_FIGHT_CLEAR, 15);
		}
		//左から３番目(コワモーテ)
		if (g_Challenge_enemy == 2)									
		{
			//全素材獲得処理は急遽追加されたものであり、
			//このクリア処理では対応出来ないため、
			//とりあえずここでは木材の獲得処理のみを行い、
			//それ以外の素材取得の処理は、
			//ObjFightClearのコンストラクタで対応している。
			//※ちなみにリザルト画面の「全素材」の表記は直接ドロー処理を書き換えた。
			CObjFightClear* crer = new CObjFightClear(12000, 500, L"木材", &g_Wood_num, 100, 5);
			Objs::InsertObj(crer, OBJ_FIGHT_CLEAR, 15);
		}
		//左から４番目(再星)
		if (g_Challenge_enemy == 3)									
		{
			CObjFightClear* crer = new CObjFightClear(8000, 340, L"鉄", &g_Iron_num, 30, L"アルミ", &g_Aluminum_num, 80, 3);
			Objs::InsertObj(crer, OBJ_FIGHT_CLEAR, 15);
		}
		//ボス(アマテラス)
		if (g_Challenge_enemy == 4)									
		{
			CObjFightClear* crer = new CObjFightClear(1000, 20, L"木材", &g_Wood_num, 0, 0);
			Objs::InsertObj(crer, OBJ_FIGHT_CLEAR, 15);
		}
		//チュートリアル(チュートリアル惑星)
		if (g_Challenge_enemy == 5)
		{
			//エラーを回避するために木材を0個獲得するようにしている
			CObjFightClear* crer = new CObjFightClear(10000 - (g_Power_num + g_Defense_num + g_Speed_num + g_Balance_num), 20, L"なし", &g_Wood_num, 0, 4);
			Objs::InsertObj(crer, OBJ_FIGHT_CLEAR, 15);
		}
	}



	//▼以下の処理は演出上、
	//各オブジェクトの背面に表示したいものであり、
	//このObjFightの中で処理する事で、
	//背面に表示するというのを実現している。
	
	//プレイヤーの[Explosion]の演出処理(下からの上の順番で徐々に実行される)
	if (m_Explosion_f[0] == true)
	{
		if (m_Explosion_width[1] >= 860.0f)
		{
			//▽エフェクト画像の幅が狭まり、画面から非表示になると実行。
			m_Explosion_f[0] = false;
		}
		else if (m_Explosion_size[1] <= -860.0f)
		{
			//サイズ変更(下発射)をやめて、エフェクト画像の幅を徐々に狭めていく。
			m_Explosion_width[1] += 10.0f;//エフェクト画像の幅を狭める
		}
		else
		{
			//エフェクト画像が画面外(相手惑星の真上)を起点に下へと発射し、相手惑星を貫く。
			m_Explosion_size[1] -= 20.0f;//エフェクト画像サイズを変更し、下方向に画像を伸ばす
			m_Explosion_width[1] += 10.0f;//エフェクト画像の幅を狭める
		}
	}

	//エネミーの[Explosion]の演出処理(下からの上の順番で徐々に実行される)
	if (m_Explosion_f[1] == true)
	{
		if (m_Explosion_width[0] >= 860.0f)
		{
			//▽エフェクト画像の幅が狭まり、画面から非表示になると実行。
			m_Explosion_f[1] = false;
		}
		else if (m_Explosion_size[0] <= -860.0f)
		{
			//▽エフェクト画像サイズが画面外(下)に到達すると実行。
			//サイズ変更(下発射)をやめて、エフェクト画像の幅を徐々に狭めていく。
			m_Explosion_width[0] += 10.0f;//エフェクト画像の幅を狭める
		}
		else
		{
			//エフェクト画像が画面外(相手惑星の真上)を起点に下へと発射し、相手惑星を貫く。
			m_Explosion_size[0] -= 20.0f;//エフェクト画像サイズを変更し、下方向に画像を伸ばす
			m_Explosion_width[0] += 10.0f;//エフェクト画像の幅を狭める
		}
	}
}

//ドロー
void CObjFight::Draw()
{	
	//描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	float c[4] = { 1.0f,1.0f,1.0f,m_a };
	float d[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

	//▼背景表示
	src.m_top = 0.0f + (m_scale_down_cnt * 4.5 / 6);
	src.m_left = 0.0f + m_scale_down_cnt;
	src.m_right = 1200.0f - m_scale_down_cnt;
	src.m_bottom = 700.0f - (m_scale_down_cnt * 4.5 / 6);

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 1200.0f;
	dst.m_bottom = 700.0f;
	Draw::Draw(0, &src, &dst, d, 0.0f);

	//▼戦闘時間表示
	if (battle_end == false) {
		int s = (m_cnt / 60), m = 0;	//ミニッツ,セコンドを宣言＆初期化
		if (s >= 60) {						//60秒以上の場合
			m += (s / 60); int n = (s / 60); s -= (n * 60);	//分に秒÷60を足して、秒はその分減らす。
		}													//nはその減らす分。

		//▼残り時間表示(十の位の分数)
		//している動作は残り分数の10の位をとるために
		//分数/10をして小数点以下切り捨てをして
		//その値によって切り取り位置を変えている
		src.m_top = 1250.0f;
		src.m_left =  CUT_ZERO + (floor(m / 10) * 125);	//実質動くことはないが10分以上に設定したときも
		src.m_right = END_ZERO + (floor(m / 10) * 125);	//動作するようになっている
		src.m_bottom = 1375.0f;

		dst.m_top = 50.0f;
		dst.m_left = 525.0f;
		dst.m_right = 550.0f;
		dst.m_bottom = 100.0f;
		Draw::Draw(41, &src, &dst, d, 0.0f);

		//▼残り時間表示(一の位の分数)
		//している動作は残り分数の1の位をとるために
		//分数/10の余りを出して
		//その値によって切り取り位置を変えている
		src.m_top = 1250.0f;
		src.m_left =  CUT_ZERO + ((m % 10) * 125);
		src.m_right = END_ZERO + ((m % 10) * 125);
		src.m_bottom = 1375.0f;

		dst.m_top = 50.0f;
		dst.m_left = 550.0f;
		dst.m_right = 575.0f;
		dst.m_bottom = 100.0f;
		Draw::Draw(41, &src, &dst, d, 0.0f);

		//▼残り時間表示(コロン)
		src.m_top = 1250.0f;
		src.m_left = 250.0f;
		src.m_right = 375.0f;
		src.m_bottom = 1375.0f;

		dst.m_top = 50.0f;
		dst.m_left = 575.0f;
		dst.m_right = 600.0f;
		dst.m_bottom = 100.0f;
		Draw::Draw(41, &src, &dst, d, 0.0f);

		//▼残り時間表示(十の位の秒数)
		//している動作は残り秒数の10の位をとるために
		//秒数/10をして小数点以下切り捨てをして
		//その値によって切り取り位置を変えている
		src.m_top = 1250.0f;
		src.m_left =  CUT_ZERO + (floor(s / 10) * 125);
		src.m_right = END_ZERO + (floor(s / 10) * 125);
		src.m_bottom = 1375.0f;

		dst.m_top = 50.0f;
		dst.m_left = 600.0f;
		dst.m_right = 625.0f;
		dst.m_bottom = 100.0f;
		Draw::Draw(41, &src, &dst, d, 0.0f);

		//▼残り時間表示(一の位の秒数)
		//している動作は残り秒数の1の位をとるために
		//秒数/10の余りを出して
		//その値によって切り取り位置を変えている
		src.m_top = 1250.0f;
		src.m_left =  CUT_ZERO + ((s % 10) * 125);
		src.m_right = END_ZERO + ((s % 10) * 125);
		src.m_bottom = 1375.0f;

		dst.m_top = 50.0f;
		dst.m_left = 625.0f;
		dst.m_right = 650.0f;
		dst.m_bottom = 100.0f;
		Draw::Draw(41, &src, &dst, d, 0.0f);
	}

	//wchar_t str[256];
	//swprintf_s(str, L"%02d :%02d", m, s);		//2桁、0詰め表示
	//Font::StrDraw(str,500 ,60 ,50 , c);


	//▼攻撃用ライン描画処理
	CObjFight* obj = (CObjFight*)Objs::GetObj(OBJ_FIGHT);

	//描画カラー情報  R=RED  G=Green  B=Blue A=alpha(透過情報)
	float d0[4] = { 1.0f,1.0f - (Pla_One_pat_dem[0] - 1.0f) * 2,1.0f - (Pla_One_pat_dem[0] - 1.0f) * 2,0.2f };
	float d1[4] = { 1.0f,1.0f - (Pla_One_pat_dem[1] - 1.0f) * 2,1.0f - (Pla_One_pat_dem[1] - 1.0f) * 2,0.2f };
	float d2[4] = { 1.0f,1.0f - (Pla_One_pat_dem[2] - 1.0f) * 2,1.0f - (Pla_One_pat_dem[2] - 1.0f) * 2,0.2f };

	if (obj->GetCount() == 0) {//-------------------------時間切れの場合----
		if (m_a > 0.0f) {
			m_a -= 0.03f;				//透明化
		}
		d0[3] = { m_a };//個別に初期化
		d1[3] = { m_a };
		d2[3] = { m_a };
	}
	else {//------------------------------------------対戦時間中のみ動作-----
		if (m_line == 0)		//選択時に各ラインを不透明化
			d0[3] = INI_COLOR;
		else if (m_line == 1)
			d1[3] = INI_COLOR;
		else if (m_line == 2)
			d2[3] = INI_COLOR;

		if (m_line_nam == 0)	//カーソル時に半不透明化
			d0[3] = 1.0f;
		else if (m_line_nam == 1)
			d1[3] = 1.0f;
		else if (m_line_nam == 2)
			d2[3] = 1.0f;
	}

	//攻撃用ライン画像
	src.m_top   =  0.0f;
	src.m_left  =  0.0f;
	src.m_right =400.0f;
	src.m_bottom=60.0f;

	dst.m_top   =200.0f;
	dst.m_left  =400.0f;
	dst.m_right =800.0f;
	dst.m_bottom=260.0f;
	Draw::Draw(118, &src, &dst, d0, 0.0f);

	dst.m_top   =310.0f;
	dst.m_left  =400.0f;
	dst.m_right =800.0f;
	dst.m_bottom=370.0f;
	Draw::Draw(119, &src, &dst, d1, 0.0f);

	dst.m_top   =420.0f;
	dst.m_left  =400.0f;
	dst.m_right =800.0f;
	dst.m_bottom=480.0f;
	Draw::Draw(120, &src, &dst, d2, 0.0f);

	if (battle_end == false) {
		//ポッドやミサイルのキーボード選択用画像
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 96.0f;
		src.m_bottom = 96.0f;

		//ミサイルキー描画
		dst.m_top = 655.0f;
		dst.m_left = 385.0f;
		dst.m_right = 415.0f;
		dst.m_bottom = 685.0f;
		Draw::Draw(35, &src, &dst, d, 0.0f);

		//赤ポッドキー描画
		dst.m_top = 655.0f;
		dst.m_left = 535.0f;
		dst.m_right = 565.0f;
		dst.m_bottom = 685.0f;
		Draw::Draw(36, &src, &dst, d, 0.0f);

		//青ポッドキー描画
		dst.m_top = 655.0f;
		dst.m_left = 685.0f;
		dst.m_right = 715.0f;
		dst.m_bottom = 685.0f;
		Draw::Draw(37, &src, &dst, d, 0.0f);

		//緑ポッドキー描画
		dst.m_top = 655.0f;
		dst.m_left = 837.0f;
		dst.m_right = 867.0f;
		dst.m_bottom = 685.0f;
		Draw::Draw(38, &src, &dst, d, 0.0f);

		//灰ポッドキー描画
		dst.m_top = 655.0f;
		dst.m_left = 985.0f;
		dst.m_right = 1015.0f;
		dst.m_bottom = 685.0f;
		Draw::Draw(39, &src, &dst, d, 0.0f);

		//スペシャル技を装備しているときはアイコンを出す
		if (g_Special_equipment != 0 && m_special_f==false)
		{
			//ポッドやミサイルのキーボード選択用画像
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 288.0f;
			src.m_bottom = 96.0f;


			dst.m_top = 60.0f;
			dst.m_left = 940.0f;
			dst.m_right = 990.0f;
			dst.m_bottom = 100.0f;
			Draw::Draw(40, &src, &dst, d, 0.0f);
			/*m_special_f = true;*/
		}

		//三すくみ説明画像描画
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1353.0f;
		src.m_bottom = 1050.0f;

		dst.m_top = 25.0f;
		dst.m_left = 25.0f;
		dst.m_right = 225.0f;
		dst.m_bottom = 200.0f;
		Draw::Draw(80, &src, &dst, d, 0.0f);


		FontDraw(L"残り住民数", 20, 455, 25, 25, c, false);

		//ポッド描画の切り取り位置
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		//赤ポッドの表示位置
		dst.m_top = 490.0f;
		dst.m_left = 45.0f;
		dst.m_right = 95.0f;
		dst.m_bottom = 535.0f;
		Draw::Draw(65, &src, &dst, d, 0.0f);
		//残り住人数表示用
		FontDraw(NumConversion(g_Power_num), 100, 495, 30, 30, c, false);
		
		//青ポッドの表示位置
		dst.m_top = 545.0f;
		dst.m_left = 45.0f;
		dst.m_right = 95.0f;
		dst.m_bottom = 590.0f;
		Draw::Draw(68, &src, &dst, d, 0.0f);
		//残り住人数表示用
		FontDraw(NumConversion(g_Defense_num), 100, 550, 30, 30, c, false); 

		//緑ポッドの表示位置
		dst.m_top = 600.0f;
		dst.m_left = 45.0f;
		dst.m_right = 95.0f;
		dst.m_bottom = 645.0f;
		Draw::Draw(71, &src, &dst, d, 0.0f);
		//残り住人数表示用
		FontDraw(NumConversion(g_Speed_num), 100, 605, 30, 30, c, false);

		//白ポッドの表示位置
		dst.m_top = 655.0f;
		dst.m_left = 45.0f;
		dst.m_right = 95.0f;
		dst.m_bottom = 701.0f;
		Draw::Draw(74, &src, &dst, d, 0.0f);
		//残り住人数表示用
		FontDraw(NumConversion(g_Balance_num), 100, 660, 30, 30, c, false);


	}



	//▼戦闘開始カウント
	//戦闘開始カウントの値に合わせて、
	//３→２→１と徐々にカウントダウンしていき、
	//０になると「スタート！」と表示。
	//その後「スタート！」の文字は徐々に透明化していき、
	//最終的に見えなくなる。
	float start_font[4] = { 1.0f,1.0f,1.0f,m_font_a };
	
	if (battle_start == true)
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 547.0f;
		src.m_bottom = 112.0f;

		dst.m_top = 225.0f;
		dst.m_left = 400.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 325.0f;
		Draw::Draw(42, &src, &dst, start_font, 0.0f);
	}
	else if (m_start_count <= 60 * 1)
	{
		src.m_top = 1250.0f;
		src.m_left = CUT_ZERO + 125;
		src.m_right = END_ZERO + 125;
		src.m_bottom = 1375.0f;

		dst.m_top = 250.0f;
		dst.m_left = 550.0f;
		dst.m_right = 650.0f;
		dst.m_bottom = 350.0f;
		Draw::Draw(41, &src, &dst, start_font, 0.0f);
	}
	else if (m_start_count <= 60 * 2)
	{
		src.m_top = 1250.0f;
		src.m_left = CUT_ZERO + 250;
		src.m_right = END_ZERO + 250;
		src.m_bottom = 1375.0f;

		dst.m_top = 250.0f;
		dst.m_left = 550.0f;
		dst.m_right = 650.0f;
		dst.m_bottom = 350.0f;
		Draw::Draw(41, &src, &dst, start_font, 0.0f);
	}
	else if (m_start_count_f == true)
	{
		src.m_top = 1250.0f;
		src.m_left = CUT_ZERO + 375;
		src.m_right = END_ZERO + 375;
		src.m_bottom = 1375.0f;

		dst.m_top = 250.0f;
		dst.m_left = 550.0f;
		dst.m_right = 650.0f;
		dst.m_bottom = 350.0f;
		Draw::Draw(41, &src, &dst, start_font, 0.0f);
	}

	//if (battle_start == true)
	//{
	//	Font::StrDraw(L"スタート！", 420, 250, 80, start_font);
	//}
	//else if (m_start_count <= 60 * 1)
	//{
	//	Font::StrDraw(L"１", 495, 260, 160, start_font);
	//}
	//else if (m_start_count <= 60 * 2)
	//{
	//	Font::StrDraw(L"２", 495, 260, 160, start_font);
	//}
	//else if (m_start_count_f == true)
	//{
	//	Font::StrDraw(L"３", 495, 260, 160, start_font);
	//}



	//▼以下の処理は演出上、
	//各オブジェクトの背面に表示したいものであり、
	//このObjFightの中で処理する事で、
	//背面に表示するというのを実現している。

	//▽プレイヤーExplosion表示(敵に直撃している演出)
	if (m_Explosion_f[0] == true)
	{
		CObjPlanet* Enemy = (CObjPlanet*)Objs::GetObj(OBJ_ENEMY);

		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1200.0f;
		src.m_bottom = 400.0f;

		//▽メモ1：
		//画像を拡大縮小等と変形する際、
		//均等にtopとleftとrightとbottomを伸ばさなければ、
		//その誤差分、画像が引き伸ばされ、
		//欲しい画像とならないので
		//基本的にどんな状況でも均等に伸ばさないといけない。
		//ただ今回はtop方向に画像を伸ばし、bottomの位置は固定としたい為、
		//bottomを動かさない分、topを2倍動かす事でこれに対応している。
		//▽メモ2:
		//今回の画像は90度&270度回転させて使用している為、
		//topとbottomの値の差を変動させる事で、
		//欲しい画像である"左右から徐々に消えていく演出"を行っている。
		dst.m_top = Enemy->GetY() - m_Explosion_size[1] * 2 - m_Explosion_width[1] - 1000.0f;
		dst.m_left = Enemy->GetX() - m_Explosion_size[1] + Enemy->GetScale_down_move();
		dst.m_right = Enemy->GetX() + m_Explosion_size[1] + Enemy->GetScale_down_move();
		dst.m_bottom = Enemy->GetY() + m_Explosion_width[1] - 1000.0f;
		Draw::Draw(21, &src, &dst, d, 270.0f);
	}
	
	//▽エネミーExplosion表示(敵に直撃している演出)
	if (m_Explosion_f[1] == true)
	{
		CObjPlanet* Player = (CObjPlanet*)Objs::GetObj(OBJ_PLANET);

		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1200.0f;
		src.m_bottom = 400.0f;

		//▽メモ1：
		//画像を拡大縮小等と変形する際、
		//均等にtopとleftとrightとbottomを伸ばさなければ、
		//その誤差分、画像が引き伸ばされ、
		//欲しい画像とならないので
		//基本的にどんな状況でも均等に伸ばさないといけない。
		//ただ今回はtop方向に画像を伸ばし、bottomの位置は固定としたい為、
		//bottomを動かさない分、topを2倍動かす事でこれに対応している。
		//▽メモ2:
		//今回の画像は90度&270度回転させて使用している為、
		//topとbottomの値の差を変動させる事で、
		//欲しい画像である"左右から徐々に消えていく演出"を行っている。
		dst.m_top = Player->GetY() - m_Explosion_size[0] * 2 - m_Explosion_width[0] - 1000.0f;
		dst.m_left = Player->GetX() - m_Explosion_size[0] + Player->GetScale_down_move();
		dst.m_right = Player->GetX() + m_Explosion_size[0] + Player->GetScale_down_move();
		dst.m_bottom = Player->GetY() + m_Explosion_width[0] - 1000.0f;
		Draw::Draw(21, &src, &dst, d, 270.0f);
	}


	//▽捕食処理時、勝利惑星の口だけを背面に描画
	if (m_prey_f >= 0)
	{
		//▼プレイヤー惑星
		if (m_prey_f == 0)
		{
			CObjPlanet* Player = (CObjPlanet*)Objs::GetObj(OBJ_PLANET);

			//▽切り取り位置
			src.m_top = 0.0f;
			src.m_left = m_ani[Player->GetAni_frame()] * 448.0f * 2;
			src.m_right = m_ani[Player->GetAni_frame()] * 448.0f * 2 + 448.0f;
			src.m_bottom = 448.0f;

			//▽表示位置
			dst.m_top = Player->GetY() - 60.0f - ((Player->GetSiz() / Player->GetMaxSiz()) * Player->GetSiz_change_range());
			dst.m_left = Player->GetX() - 60.0f - ((Player->GetSiz() / Player->GetMaxSiz()) * Player->GetSiz_change_range()) + Player->GetScale_down_move();
			dst.m_right = Player->GetX() + 60.0f + ((Player->GetSiz() / Player->GetMaxSiz()) * Player->GetSiz_change_range()) + Player->GetScale_down_move();
			dst.m_bottom = Player->GetY() + 60.0f + ((Player->GetSiz() / Player->GetMaxSiz()) * Player->GetSiz_change_range());
		}
		//▼敵惑星
		else
		{
			CObjPlanet* Enemy = (CObjPlanet*)Objs::GetObj(OBJ_ENEMY);

			//▽切り取り位置
			src.m_top = 0.0f;
			src.m_left = m_ani[Enemy->GetAni_frame()] * 300.0f;
			src.m_right = m_ani[Enemy->GetAni_frame()] * 300.0f + 300.0f;
			src.m_bottom = 300.0f;

			//▽表示位置
			dst.m_top = Enemy->GetY() - 60.0f - ((Enemy->GetSiz() / Enemy->GetMaxSiz()) * Enemy->GetSiz_change_range());
			dst.m_left = Enemy->GetX() - 60.0f - ((Enemy->GetSiz() / Enemy->GetMaxSiz()) * Enemy->GetSiz_change_range()) + Enemy->GetScale_down_move();
			dst.m_right = Enemy->GetX() + 60.0f + ((Enemy->GetSiz() / Enemy->GetMaxSiz()) * Enemy->GetSiz_change_range()) + Enemy->GetScale_down_move();
			dst.m_bottom = Enemy->GetY() + 60.0f + ((Enemy->GetSiz() / Enemy->GetMaxSiz()) * Enemy->GetSiz_change_range());
		}

		//▽実際に描画
		//▼プレイヤー惑星
		if (m_prey_f == 0)
		{
			Draw::Draw(6, &src, &dst, d, 0.0f);
		}
		//▼Ｏ阪魂
		else if (m_prey_f == 1)
		{
			Draw::Draw(81, &src, &dst, d, 0.0f);
		}
		//▼アマテラス
		else if (m_prey_f == 5)
		{
			Draw::Draw(82, &src, &dst, d, 0.0f);
		}
	}



	//デバッグ用仮マウス位置表示
	//wchar_t test_mou[256];
	//swprintf_s(test_mou, L"x=%f,y=%f", m_mou_x, m_mou_y);
	//Font::StrDraw(test_mou, 20.0f, 20.0f, 12.0f, d);
}
