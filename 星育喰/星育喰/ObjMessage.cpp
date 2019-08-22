//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"//�f�o�b�O�p
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "UtilityModule.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjMessage::Init()
{
	for (int i = 0; i < FONT_MAX; i++)
	{
		m_font_column[i] = 0;
		m_font_line[i] = 0;
		m_font_draw_x[i] = 0;
		m_font_draw_y[i] = 0;

		for (int j = 0; j < 4; j++)
		{
			m_font_color[i][j] = 1.0f;
		}
	}

	m_time = 0;
	m_font_count = 0;
	m_progress = 0;
	m_length = 0;
	m_fast_f = false;
	m_skip_f = false;

	m_mou_x = 0.0f;
	m_mou_y = 0.0f;
	m_mou_r = false;
	m_mou_l = false;
	m_key_f = false;

	m_count = 0;

	m_arrow_display_f = 0;
	m_arrow_angle_f = 0;
	m_arrow_x = 0.0f;
	m_arrow_y = 0.0f;
	
	m_swing_vec = 0.0f;
	m_swing_r = 0.0f;

	m_black_out_a = 0.0f;
	m_black_out_f = false;
	m_reminder_f = false;
	m_is_top_or_bottom = 0;

	m_ignore_alpha = 0.0f;

	m_message_window_num = 0;
	m_yamada_window_num = 0;
	m_black_out_num = 0;

	m_run_switch = false;


	//�t�H���g�f�[�^���
	//���z��ʒu�����̂܂ܐ؂���ʒu�ƂȂ�ׁA�t�H���g�摜�̔z�u�Ɠ����悤�ɕ����o�^����悤�ɁB
	wchar_t font_data[FONT_DATA_Y][FONT_DATA_X] =
	{
		{ L'��',L'��',L'��',L'��',L'��',L'�A',L'�C',L'�E',L'�G',L'�I',L'�~',L'��',L'�p',L'��',L'��',L'�e',L'�b',L'��',L'�R',L'��' },
		{ L'��',L'��',L'��',L'��',L'��',L'�J',L'�L',L'�N',L'�P',L'�R',L'��',L'��',L'��',L'��',L'��',L'�K',L'�M',L'�O',L'�Q',L'�S' },
		{ L'��',L'��',L'��',L'��',L'��',L'�T',L'�V',L'�X',L'�Z',L'�\',L'��',L'��',L'��',L'��',L'��',L'�U',L'�W',L'�Y',L'�[',L'�]' },
		{ L'��',L'��',L'��',L'��',L'��',L'�^',L'�`',L'�c',L'�e',L'�g',L'��',L'��',L'��',L'��',L'��',L'�_',L'�a',L'�d',L'�f',L'�h' },
		{ L'��',L'��',L'��',L'��',L'��',L'�i',L'�j',L'�k',L'�l',L'�m',L'��',L'��',L'��',L'��',L'�R',L'��',L'��',L'��',L'��',L'�Q' },
		{ L'��',L'��',L'��',L'��',L'��',L'�n',L'�q',L'�t',L'�w',L'�z',L'��',L'��',L'��',L'��',L'��',L'�o',L'�r',L'�u',L'�x',L'�{' },
		{ L'��',L'��',L'��',L'��',L'��',L'�}',L'�~',L'��',L'��',L'��',L'�M',L'�{',L'��',L'��',L'��',L'��',L'�b',L'��',L'�P',L'��' },
		{ L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'�s' },
		{ L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'�b',L'�s',L'�q',L'�k' },
		{ L'��',L'��',L'��',L'��',L'��',L'��',L'�v',L'�b',L'�m',L'�F' },
		{ L'�~',L'��',L'�F',L'�{',L'�|',L'�c',L'�B',L'�I',L'�H',L'�A',L'��',L'�D',L'��',L'�O',L'�P',L'�Q',L'�R',L'�S',L'�T',L'�U',L'�V',L'�W',L'�X',L'��',L'��',L'�O',L'�l',L'��',L'�Z',L'��',L'��',L'��',L'��' },
		{ L'��',L'��',L'�l',L'��',L'��',L'��',L'�R',L'�c',L'��',L'�G',L'�f',L'��',L'��',L'��',L'�s',L'��',L'��',L'��',L'�O',L'�s',L'�S',L'��',L'�^',L'�B',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��' },
		{ L'��',L'��',L'��',L'�v',L'��',L'��',L'�z',L'��',L'��',L'��',L'�U',L'��',L'�X',L'��',L'��',L'��',L'�K',L'�E',L'�Z',L'��',L'��',L'�H',L'�D',L'��',L'�g',L'�o',L'��',L'�|',L'��',L'�^' },
		{ L'��',L'��',L'��',L'��',L'�C',L'�d',L'��',L'��',L'�o',L'��',L'��',L'��',L'�Z',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'�~',L'�r',L'��',L'��' },
		{ L'�L',L'��',L'�s',L'��',L'��',L'��',L'��',L'�D',L'�F',L'��',L'��',L'�@',L'��',L'�P',L'��',L'�p',L'��',L'��',L'��',L'�^',L'��',L'��' },
		{ L'�z',L'��',L'�t',L'��',L'��',L'��',L'�m',L'��',L'��',L'��',L'��',L'��',L'��',L'�F',L'��',L'��',L'��',L'�o',L'�K',L'��',L'�l' },
		{ L'�f',L'��',L'��',L'��',L'�z',L'�u',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��' },
		{ L'��',L'�l',L'��',L'�W',L'��',L'�D',L'��',L'��',L'��',L'�e',L'��',L'��',L'�~',L'�c',L'��',L'�c',L'��',L'��',L'��',L'�f',L'�D',L'�n',L'��',L'��',L'�[',L'�y',L'�F',L'��' },
		{ L'��',L'�@',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'�p',L'��',L'�v',L'��',L'��',L'��',L'�U',L'��',L'�Y',L'��',L'��',L'��',L'��',L'�g',L'��',L'�E',L'��' },
		{ L'��',L'��',L'��',L'��',L'�x',L'��',L'��',L'�\',L'��',L'��',L'�x',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'�I',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��' },
		{ L'�Q',L'��',L'��',L'�U',L'��',L'��',L'�F',L'�o',L'��',L'�v',L'��',L'��',L'��',L'��',L'�q',L'��',L'��',L'��',L'��',L'�U',L'��',L'��',L'��',L'�I',L'��',L'��',L'��',L'��' },
		{ L'��',L'�W',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'�N',L'��',L'��',L'��',L'�S',L'�x',L'�V',L'��',L'�z',L'�s',L'��',L'�h',L'��',L'��',L'��',L'��',L'�\' },
	};

	//�t�H���g�f�[�^���R�s�[
	//���w�b�_�[��m_font_data�錾��A���ʂ�m_font_data���`���悤�Ƃ����
	//��L�̂悤�ɐ錾�Ɠ����ɒ�`����������ł��Ȃ��ׁA
	//������������邽�߂ɁA��U�C�j�V�����C�Y�݂̂ł����g���Ȃ��z���
	//�錾�Ɠ����ɒ�`���A���̃f�[�^��m_font_data�ɃR�s�[�����B
	memcpy(m_font_data, font_data, sizeof(wchar_t)*(FONT_DATA_Y * FONT_DATA_X));


	//-------------------------------------------------------------------------------
	//�����b�Z�[�W���ݒ�
	//�ȉ��̂悤�Ɂu�V�[��ID(if��)�ƃ��b�Z�[�W��(swprintf_s)�v�̂Q�łP�Z�b�g�Ƃ��Đݒ肷��B
	//���b�Z�[�W���͕K���S�p������p���鎖�B
	//���p�����A�t�H���g�f�[�^�ɓo�^����ĂȂ��������͎g�p�s�Ȃ̂Œ��ӁB(���͂���Ƌ󔒈����ƂȂ�)
	//�����ꏈ���ɂ���
	//�ȉ��̑S�p������ł����ނƁA���ꂼ����ꏈ�����s���܂��B
	//�u�q�v�c�c�ԕ�����
	//�u�f�v�c�c�Ε�����
	//�u�x�v�c�c��������
	//�u�v�v�c�c��������
	//�u�Q�v�c�c��
	//�u���v�c�c���s
	//�u�`�v�c�c���͓r���̃N���b�N�v��
	//�u�b�v�c�c���b�Z�[�W�\���@�\��~
	//���S�Ẵ��b�Z�[�W�I����A
	//�܂��̓��b�Z�[�W�r���Ƀv���C���[��
	//�������삳���������ɂ��̑S�p�����������ĉ������B

	//�����̘f����(�e�X�g�p)
	//wchar_t g_Player_Name[20] = L"�łӂ����";

	//������ʃ��b�Z�[�W���ݒ聕�摜�o�^�ԍ��ݒ�
	//if (m_Scene_id == 30)
	//{
	//	swprintf_s(m_font[1], L"");
	//	swprintf_s(m_font[2], L"", g_Player_Name);
	//	swprintf_s(m_font[3], L"");
	//	swprintf_s(m_font[4], L"");
	//	swprintf_s(m_font[5], L"");
	//	swprintf_s(m_font[6], L"");
	//	swprintf_s(m_font[7], L"");
	//	swprintf_s(m_font[8], L"");
	//	swprintf_s(m_font[9], L"");
	//	swprintf_s(m_font[10], L"");
	//	swprintf_s(m_font[11], L"");
	//	swprintf_s(m_font[12], L"");
	//	swprintf_s(m_font[13], L"");


	//	swprintf_s(m_font[0], L"�q���������a�����f�����Q�������`�������������������Ȃ��Ȃɂ����ɂ��܂ނ܂ށ��e�X�g�P�Q�R���Q�P�R�Q�R�P�Q���P�R�P�Q�P�R�Q");//���b�Z�[�W�P
	//	swprintf_s(m_font[1], L"�������������P�Q�R�����l�ޔ��W");	//���b�Z�[�W�Q
	//	swprintf_s(m_font[2], L"�e�X�g�F%s�F�e�X�g",g_Player_Name);		//���b�Z�[�W�R
	//	swprintf_s(m_font[3], L"�b");					//���b�Z�[�W�S
	//	swprintf_s(m_font[4], L"�����P�Q�Q�Q�R");		//���b�Z�[�W�T
	//	swprintf_s(m_font[5], L"�b");					//���b�Z�[�W�U

	//	m_message_window_num = 2;
	//	m_yamada_window_num = 3;
	//	m_black_out_num = 5;
	//}
	//�z�[�����1��ڃ��b�Z�[�W���ݒ聕�摜�o�^�ԍ��A�O���[�o���ϐ��ݒ�
	if (m_Scene_id == 0)
	{
		swprintf_s(m_font[0], L"�悤�B����������x%s���v�A�l�ޓ����ɂȂ����R�c���B", g_Player_Name);
		swprintf_s(m_font[1], L"�x%s�v�A���܂ꂽ�Ăł����Ȃ�Ȃ񂾂����G�f�����U�߂Ă�����ď�񂪓��������B", g_Player_Name);
		swprintf_s(m_font[2], L"�s�ӑł��H�炤�O�ɐ킢�ɍs�������I");
		swprintf_s(m_font[3], L"�b");

		m_message_window_num = 6;
		m_yamada_window_num = 7;
		m_black_out_num = 8;

		g_is_operatable = false;//����s�\��(ObjMessage���������Ȃ�)
		m_black_out_f = true;//���X�ɈÓ]
		m_ignore_alpha = 1.0f;//�R�c�����\��m�点��t�H���g�摜��\��
	}
	//�퓬�������1��ڃ��b�Z�[�W���ݒ聕�摜�o�^�ԍ��A�O���[�o���ϐ��ݒ�
	else if (m_Scene_id == 1)
	{
		swprintf_s(m_font[1], L"���ꂪ��̓G�f�����B�`���U�߂Ă�����ĕ���������A�������̂����邩�Ǝv�������ǁ��v���Ă����������Ԏセ�����ȁI");
		swprintf_s(m_font[2], L"�܂��セ�������Ǐ�������ɉz�������Ƃ͂˂��ȁI���x%s�v�I���G�f���Ƀ}�E�X�J�[�\�������킹�Ă݂ȁI", g_Player_Name);
		swprintf_s(m_font[3], L"�b");
		swprintf_s(m_font[4], L"�悵�A�J�[�\�������킹���ȁI�`���G�ɃJ�[�\�������킹��Ƃq�G�̏�񂪌����v���I����ɓ��鎑�ނ�G�̍U���X�����킩�邩�灏�키�O�ɂ�������`�F�b�N���Ă�����I");
		swprintf_s(m_font[5], L"���A���������B���G�̏��ɃI�[�o�[���[�N���ď����Ă��邾��H�`������͂q�X�y�V�����Z�v�Ƃ����āA���v�͓G�������Ă���q�K�E�Z�v�݂����Ȃ��񂾁B");
		swprintf_s(m_font[6], L"���x%s�v�̓X�y�V�����Z�������Ă͂��Ȃ������G��ߐH����Ƃq�G�������Ă���X�y�V�����Z�����D���Ďg����悤�ɂȂ�v����ȁB�`�����Ⴀ�퓬�ɂ����Ă݂邩�B",g_Player_Name);
		swprintf_s(m_font[7], L"�b");

		m_message_window_num = 55;
		m_yamada_window_num = 89;
		m_black_out_num = 91;

		g_is_operatable = true;//����\��
		m_black_out_f = false;//���]��Ԃ���n�߂�
	}
	//�퓬���1��ڃ��b�Z�[�W���ݒ聕�摜�o�^�ԍ��A�O���[�o���ϐ��ݒ�
	else if (m_Scene_id == 2)
	{
		swprintf_s(m_font[1], L"�퓬���n�܂����ȁB");
		swprintf_s(m_font[2], L"�E�����Ă킩��ʂ�x%s�v���ȁB",g_Player_Name);	
		swprintf_s(m_font[3], L"����ō����G�̘f�����B");
		swprintf_s(m_font[4], L"�����̘f���̉��ɗΐF�̃o�[�����邾��H�`�����̉��̃o�[���f���̂q�g�o�Q�[�W�v�ɂȂ��Ă邺�B");
		swprintf_s(m_font[5], L"�g�o�Q�[�W�͘f���̃T�C�Y�ɒ������Ă��āA���q���̃Q�[�W���[���ɂȂ�Ɓ��킢�ɕ����Ă��܂��v����ȁB�`���g�o�Q�[�W�������Ȃ�Ȃ��悤�ɋC�������B");
		swprintf_s(m_font[6], L"���͐퓬�̎d���ɂ��Ă��ȁB");
		swprintf_s(m_font[7], L"���Ɍ܂̃{�^�������邾��H");
		swprintf_s(m_font[8], L"���̓��̉E�̎l�̃{�^���̂ǂꂩ�������Ă݂�B");
		swprintf_s(m_font[9], L"�b");
		swprintf_s(m_font[10], L"�{�^�����������牽���o�Ă�����H�����ꂪ�q�|�b�h�v�����B�`���{�^���������ƂP�O�O�l�̏Z�������߂��󂯂āA���|�b�h�ɏ�荞�݁A�U�����ɍs���Ă���񂾁B");
		swprintf_s(m_font[11], L"��ŁA�����̐����́����ꂼ��̃|�b�h�̎c��Z������\���Ă�B�`���q���̐����O�ɂȂ�Ƃ��̃|�b�h�����o���ł��Ȃ��Ȃ�v����v���ӂ����B");
		swprintf_s(m_font[12], L"���ƁA�ŏ��͏������Ă��邩�灏�����Ƀ|�b�h���o�����邱�Ƃ��ł��邪�A���q���ڈȍ~�͏����Ɏ��Ԃ�������v���灏�������C�������B");
		swprintf_s(m_font[13], L"�|�b�h�ɂ͂q�����������ėL���s��������v�񂾁B�`���ԐF�͗ΐF�ɋ����΂͐ɋ��������Đ͐Ԃɋ����A���D�F�͂��ׂĂ̐F�ɑ΂��ď������������~�T�C���ɑ΂��Ă͂������ア�c�c���Ă��񂶂łȁB");
		swprintf_s(m_font[14], L"�|�b�h�͘f���ɓ�����ƃ_���[�W��^���āA���q�f���̃T�C�Y�����������ł���v���B�`�����Ȃ݂ɂq�������͍U�������̍��}�v�����灏�o���Ă����Ƃ������B");				
		swprintf_s(m_font[15], L"���͂q�~�T�C���v�ɂ��Ă̐������B");
		swprintf_s(m_font[16], L"���̃{�^���������Ă݂ȁB");
		swprintf_s(m_font[17], L"�b");
		swprintf_s(m_font[18], L"�@���̒ʂ�A�~�T�C�������˂���邺�B");
		swprintf_s(m_font[19], L"�~�T�C���͊ȒP�Ɍ����ƃW���u�݂����Ȃ��񂾁B�`���|�b�h�Ɠ����Ń_���[�W��^���邱�Ƃ��ł��邪���q�U���͂��Ⴂ�v�B");
		swprintf_s(m_font[20], L"�������̑���ɁA���q�|�b�h�����������鎞�Ԃ������v���灏���܂����Ɗ��p���Ă���I");
		swprintf_s(m_font[21], L"���Ȃ݂Ƀ|�b�h���~�T�C�������q�{�^���̉��ɏ����Ă���L�[�������Ă������߂ł���v���B");
		swprintf_s(m_font[22], L"�^�񒆂ɎO�̐������邾��H�`�����̐��̓|�b�h��~�T�C���́����ː��������������̂����B�`���I���B�͂��̐��̂��Ƃ��q���[���v���ČĂ�ł�B");
		swprintf_s(m_font[23], L"��ŁA���̃��[���̈�ԏ���N���b�N���Ă���B");
		swprintf_s(m_font[24], L"�b");
		swprintf_s(m_font[25], L"�N���b�N�������[���������������Ȃ��Ă��邾��H�`�����ꂪ�q���[���I�����ł�����Ԃv���B");
		swprintf_s(m_font[26], L"�������̃|�b�h��~�T�C���́��q�I�����[����Ɏˏo�����v���灏�󋵂ɉ����ă��[����I��Ő���Ă�����B");
		swprintf_s(m_font[27], L"�������������[���ŁA���~�T�C����|�b�h������������Ɓ��q�|�b�h�̖h��͂����������܂��f�����b�g�v������B");
		swprintf_s(m_font[28], L"�|�b�h��~�T�C�������x�Ɂ����[���̐F���Ԃ��Ȃ��Ă邾��H�`������͂��̃f�����b�g�x������\���Ă���Ă킯���B");
		swprintf_s(m_font[29], L"�v�͂q�Ԃ��Ȃ�΂Ȃ�قǁ��|�b�h�̖h��͂��������ă��o���v���Ă��Ƃ��ȁB");
		swprintf_s(m_font[30], L"���̃f�����b�g�́����̃��[���Ƀ|�b�h��~�T�C�����o�������Ă����΁�����ɂq���̃��[���ł́��|�b�h�h��͂����Ƃɖ߂�v���B");
		swprintf_s(m_font[31], L"�v�͂q�������[���Ɍ����Â���̂́���߂����������v���Ă��Ƃ����B");
		swprintf_s(m_font[32], L"���A���Ȃ݂Ƀ��[���I���́��q�����L�[�̏㉺�ł�����ł���v����ȁB");
		swprintf_s(m_font[33], L"���āA���ꂪ�퓬�Ō�̐������B");
		swprintf_s(m_font[34], L"��ʏ�Ɏ��Ԃ��\������Ă邾��H�`�����̎��Ԃ͘f�����m�����͂ň��������ā��Փ˂���܂ł̑�̂̎��Ԃ����B");
		swprintf_s(m_font[35], L"���Ԑ؂�ɂȂ��ďՓ˂�����A���q�f���̃T�C�Y���傫����������������ߐH����v���B�`�����ꂪ���̉F���̏펯������o���Ƃ���B");
		swprintf_s(m_font[36], L"�܂��K����芵��낾�ȁB�`����������͎����ōl���Đ���Ă݂ȁB���q���N���b�N�Ő퓬���n�܂�܂��B");
		swprintf_s(m_font[37], L"�b");
		swprintf_s(m_font[39], L"���Ԑ؂�ɂȂ�Ȃ��Ă����q�G�f���̗̑͂���肫��Ɓ��f�����z���񂹂��ĕߐH�ł���v���B�`���t�ɂq��肫����Ǝ������H��ꂿ�܂��v����ȁB");
		swprintf_s(m_font[40], L"�b");
		swprintf_s(m_font[43], L"�悵�I�킢�ɏ����ĕߐH���邱�Ƃ��ł����ȁB�`���ߐH����Ƃq�\�͂�f�ނ�D�����Ƃ��ł���v�񂾁B���ō�����H�`�����č���̐��ʂ����Ă��������B");
		swprintf_s(m_font[44], L"��ԏオ�x%s�v�ɈڏZ�����q�Z���v�̐����ȁB�`��������͂q���m�⌤�����ɂ�����Ɓ��F��ȏ��ɔz�u�ł���v����֗������B",g_Player_Name);
		swprintf_s(m_font[45], L"��Ԗڂɏ����Ă���̂͘f����H�ׂ����ƂŁ��ǂꂾ���x%s�v�̂q�ő�g�o�v�����㏸��������\���������ȁB",g_Player_Name);
		swprintf_s(m_font[46], L"�q�g�o������΂���قǁ��킢�͕����ɂ����Ȃ�v����A�������ɉz�������Ƃ͂˂��ȁB");
		swprintf_s(m_font[47], L"���̉��͊l�������q���ނv�̂��Ƃ������Ă��邺�B�`���܂�����͎��ނ��l���ł��Ȃ������݂��������ǂȁB�`�����̐킢����͂q�W�߂��鎑�ނv�̂��Ƃ��l�����B�����ނ͗L��������ȁB");
		swprintf_s(m_font[48], L"���ꂪ�Ōゾ�ȁB�����������������q�X�y�V�����Z�v���Ă���B");
		swprintf_s(m_font[49], L"����͂q�퓬�ɂ����Ă̐؂�D�v�݂����Ȃ���Ł��s���`�����؂����肷�邱�Ƃ��ł��邺�B�`���܂����Ƃŏڂ����������Ă���B");
		swprintf_s(m_font[50], L"�����͂���Ȃ��񂾂ȁB�`���q�����������~����������������c�����ā��ǂ̓G�Ɛ키�����l���Ă����v�̂������ꂩ�琶���c���Ă����錍�����B");
		swprintf_s(m_font[51], L"�b");

		m_message_window_num = 33;
		m_yamada_window_num = 79;
		m_black_out_num = 20;

		g_is_operatable = true;//����\��
		m_black_out_f = false;//���]��Ԃ���n�߂�
	}
	//�z�[�����2��ڃ��b�Z�[�W���ݒ聕�摜�o�^�ԍ��A�O���[�o���ϐ��ݒ�
	if (m_Scene_id == 7)
	{
		//swprintf_s(m_font[0], L"�킢�ɏ��ĂĂ悩�������B���c�c�����ǖ��f�͂���Ȃ�B�����̉F���͎ア�z�ɂ͗D�����Ȃ�����ȁB");
		//swprintf_s(m_font[1], L"���ꂩ����킢�ɏ����Ă������߂ɂ́A���������������邱�Ƃ���؂����I");
		//swprintf_s(m_font[2], L"��{�^���ň琬���āA��{�^���Ő퓬����c�c����������肩�����ā����̎�����H�̉F���Ő����c�낤���I");
		//swprintf_s(m_font[3], L"���A���������B��������Ȃ����Ƃ�����΁A���E��́H�{�^���������Ă���B");
		//swprintf_s(m_font[4], L"�I���������������Ƃ��A�������ĂȂ����Ƃ�����������ڂ��Ă邩��ȁI");
		//swprintf_s(m_font[5], L"�b");

		swprintf_s(m_font[0], L"�킢�ɏ��ĂĂ悩�������B���c�c�����ǖ��f�͂���Ȃ�B�����̉F���͎ア�z�ɂ͗D�����Ȃ�����ȁB");
		swprintf_s(m_font[1], L"���ꂩ����킢�ɏ����Ă������߂ɂ́A���q�������������邱�Ƃv����؂����I�`���c�c���Ă��Ƃŋ����Ȃ���@�������Ă�邺�I");
		swprintf_s(m_font[2], L"�b");

		m_message_window_num = 6;
		m_yamada_window_num = 7;
		m_black_out_num = 8;

		g_is_operatable = false;//����s�\��(ObjMessage���������Ȃ�)
		m_black_out_f = true;//���X�ɈÓ]
	}
	//�琬��ʃ��b�Z�[�W���ݒ聕�摜�o�^�ԍ��A�O���[�o���ϐ��ݒ�(��肩���B�F�X�o�O�L�B)
	else if (m_Scene_id == 8)
	{
		swprintf_s(m_font[0], L"�񂶂�A���������������Ă������B");
		swprintf_s(m_font[1], L"�܂��͂������N���b�N���Ă݂ȁB");
		swprintf_s(m_font[2], L"�b");
		swprintf_s(m_font[3], L"�����͂q�������v���B�`������������������ƏZ���̋Z�p���オ���ā��q�|�b�h�̑ϋv�͂������v���B");
		swprintf_s(m_font[4], L"�����̃{�^���������Ɓ����������������邱�Ƃ��ł��邼�B�`���������x%s�v�̂q�g�o�Ɓ����̐�����D�������ނ��K�v�v�����ǂȁB",g_Player_Name);
		swprintf_s(m_font[5], L"�E��̃{�^���ŏZ�����������Ɋ���U��邺�B�`������U��Ƃq�~�T�C���̍Đ��Y�𑁂߂��聏�R�A�𐻍삷�邱�Ƃ��ł���v���B");
		swprintf_s(m_font[6], L"�����ƁA�q�R�A�v�ɂ��Ă̐������܂��������ȁB");
		swprintf_s(m_font[7], L"�|�b�h�̓R�A�ɒ~�ς��ꂽ���q�R�X���p���[�v���Č����G�l���M�[�������͌��Ƃ��ē������聏�U������G�l���M�[�e�ɂȂ����肵�Ă�񂾁B");
		swprintf_s(m_font[8], L"�R�A���������邱�Ƃɂ���ā��~�ςł���R�X���p���[�������ā��q�U���͂��オ��v���B");
		swprintf_s(m_font[9], L"���Ȃ݂ɂ������̐퓬�Řb�������|�b�h���O�����݂ɂȂ��Ă��闝�R�⁏�퓬���ɓ������[���������Â���Ɓ��h��͂������闝�R�̓R�X���p���[�������Ȃ񂾂��B");
		swprintf_s(m_font[10], L"�Â��Č��Ɓ��R�X���p���[���̂̐��Y�ʂ��ǂ����Ȃ�������c���R�X���p���[���̂������������Ă��邩�灏�c�c���Ă��񂶂łȁB");
		swprintf_s(m_font[11], L"���F�̃|�b�h�͂������񂾂��B���������Ă��ׂẴR�X���p���[�����ߍ���ł邩��ȁB�`��������A���̃|�b�h��苭���񂾂��B");
		swprintf_s(m_font[12], L"����������ɑ΍R���邽�߂ɐ��܂ꂽ�̂����R�X���p���[�𗐂��遏�W���}�[���ڃ~�T�C�����Ă킯���I");
		swprintf_s(m_font[13], L"�R�X���p���[�����ׂĎ������F�|�b�h�ɂ͌��ʔ��Q�Ȃ񂾂��I");
		swprintf_s(m_font[14], L"�c�c���ƁA���M���b���Ă��܂����B���{��֖߂낤�B");
		swprintf_s(m_font[15], L"���͂��̃{�^�����N���b�N���Ă���B");
		swprintf_s(m_font[16], L"�b");
		swprintf_s(m_font[17], L"�����ł̓~�T�C���ɂ��Ă̏�񂪌���邺�B�`���~�T�C���̍Đ��Y�X�s�[�h�́��q�������𑝂₷�Ƒ����Ȃ��Ă����v���B�`���q���������̂̃��x�����グ�Ȃ��ƈӖ��͂Ȃ��v���ǂȁB");
		swprintf_s(m_font[18], L"�ڂ��������͈�ԉ��̃E�C���h�E�ɍڂ��Ă��邺�B");
		swprintf_s(m_font[19], L"���͂��̃{�^�����N���b�N���Ă���B");
		swprintf_s(m_font[20], L"�b");
		swprintf_s(m_font[21], L"�����ł̓R�A��|�b�h����邱�Ƃ��ł��邺�B�`�����͎��ނ������Ȃ����牽����邱�Ƃ͂ł��Ȃ����A�����Ƃ��ɂ͂q�������Ǝ��ނ��K�v�v�����B�`���q���쎞�Ɍ������͌���Ȃ��v������S���ȁB");
		swprintf_s(m_font[22], L"�R�A���쐬����ƁA���~�ςł���R�X���p���[�������ā��q�U���͂��オ��v���B");
		swprintf_s(m_font[23], L"�|�b�h���쐬����ƁA���|�b�h�̑��b����������ā��q�ϋv�͂�������v���B");
		swprintf_s(m_font[24], L"���͂������N���b�N���Ă݂ȁB");
		swprintf_s(m_font[25], L"�b");
		swprintf_s(m_font[26], L"�����͂q���ɂv���B�`�����ɂ���������Ǝ��̂����P���ɂȂ��ā��q�|�b�h�̍U���͂��グ�邱�Ƃ��ł���v���B");
		swprintf_s(m_font[27], L"�|�b�h�ɂ͏Z������荞��ōU�����邾��H�`���Z�����������邱�Ƃɂ���ā��|�b�h�̍U���͂����ΓI�ɏオ����Ă��Ƃ��ȁB");
		swprintf_s(m_font[28], L"�����̃{�^���������Ɓ����ɂ��������邱�Ƃ��ł��邼�B�`�����������ɂ��x%s�v�̂q�g�o�Ɓ����̐�����D�������ނ��K�v�v�����ǂȁB",g_Player_Name);
		swprintf_s(m_font[29], L"�E��̃{�^���ŏZ���𕺎m�Ɋ���U��邺�B�`���|�b�h��ɂ����P�O�O�l�悹�Ĕ��ł����񂾁B");
		swprintf_s(m_font[30], L"�������Z���̐U�蕪�������s���Ă��Ȃ��F�̃|�b�h�́��q�퓬���ɏo�����邱�Ƃ́��ł��Ȃ��v���炻���͗v���ӂ����B");
		swprintf_s(m_font[31], L"���͂������N���b�N���Ă݂ȁB");
		swprintf_s(m_font[32], L"�b");
		swprintf_s(m_font[33], L"�����͂q�q�ɂv���B�`���F��ȏ�������邺�B");
		swprintf_s(m_font[34], L"����̎��ރE�C���h�E�́����ݎ����Ă��鎑�ނ����ꂽ��c�c");
		swprintf_s(m_font[35], L"�E��̏Z���E�C���h�E�́����ɂƌ������Ŋ���U�����Z���Ɓ�����U���Ă��Ȃ��Z���̐����m�F�ł�����c�c");
		swprintf_s(m_font[36], L"�����̃X�y�V�����Z�E�C���h�E�́����ݎ擾���Ă���X�y�V�����Z�̌��ʂ����ڂ����m�F�ł�����c�c�B");
		swprintf_s(m_font[37], L"�E���̃|�b�h�E�C���h�E�́����ݑ������Ă���R�A�⁏���݂̃|�b�h���m�F�ł�����c�c�����Ă��񂶂łȁB");
		swprintf_s(m_font[38], L"�悵�A���ꂶ�Ⴀ�������N���b�N���邩�A���E�N���b�N�������đq�ɂ���o�Ă���B");
		swprintf_s(m_font[39], L"�b");
		swprintf_s(m_font[40], L"�Ō�ɕ⑫�Ȃ񂾂��A���������╺�ɂ��������Ă����Ɓ��q�f�������W���Ă����v���I�`��������ǂ�ǂ񋭉����Ă����I");
		swprintf_s(m_font[41], L"�悵�A����Ő����͈ȏゾ�B�`���܂��͍������������Ƃ���Ɂ������Ȃ悤�ɏZ����������U���Ă݂�̂����������ȁB");
		swprintf_s(m_font[42], L"����ŏ������o������A�����͂��������瑼�̘f�����U�߂ɂ��������I�`�������Ȃ邽�߂ɂ͎��ނ��K�v�����A�����͂��̎��ނ��܂������Ȃ�����ȁB");
		swprintf_s(m_font[43], L"�U�߂ɂ������@�́A������̖߂�{�^�����������A�E�N���b�N�������ā����̌�ɋ�{�^�������I");
		swprintf_s(m_font[44], L"�b");

		m_message_window_num = 21;
		m_yamada_window_num = 20;
		m_black_out_num = 135;

		g_is_operatable = false;//����s�\��(ObjMessage���������Ȃ�)
		m_black_out_f = false;//���]��Ԃ���n�߂�

		//���b�Z�[�W�E�C���h�E�ʒu�ύX
		m_is_top_or_bottom = 1;
	}
	//�퓬�������2��ڃ��b�Z�[�W���ݒ聕�摜�o�^�ԍ��A�O���[�o���ϐ��ݒ�
	else if (m_Scene_id == 15)
	{
		swprintf_s(m_font[1], L"�悤�A���̂Ƃ�������Ă݂ȁB�`���������܂łȂ��������̂������Ă��邾��B");
		swprintf_s(m_font[2], L"�����łq�X�y�V�����Z�̑������ł���v���B�`�����͂܂�������X�y�V�����Z���Ȃ������G��H�ׂ邱�Ƃő����Ă�������ȁB");
		swprintf_s(m_font[3], L"���āA��������͂x%s�v�����킢�����f����I��Ő키�񂾁B�`���킢�����f�����N���b�N����Ɓ��키���ǂ����I�ׂ邩��ȁB",g_Player_Name);
		swprintf_s(m_font[4], L"�b");

		m_message_window_num = 55;
		m_yamada_window_num = 89;
		m_black_out_num = 91;

		g_is_operatable = true;//����\��
		m_black_out_f = false;//���]��Ԃ���n�߂�

		//���b�Z�[�W�E�C���h�E�ʒu�ύX
		m_is_top_or_bottom = 1;
	}
	//�퓬���2��ڃ��b�Z�[�W���ݒ聕�摜�o�^�ԍ��A�O���[�o���ϐ��ݒ�
	else if (m_Scene_id == 16)
	{
		swprintf_s(m_font[0], L"�����ƁA���X�y�V�����Z�̔����̎d���������ĂȂ������ȁB");
		swprintf_s(m_font[1], L"�����͊ȒP�����B���q�E��̃{�^���������΂��������v������ȁB");
		swprintf_s(m_font[2], L"�������q�퓬���Ɉ�񂵂����������邱�Ƃ��ł��˂��v���灏�����^�C�~���O�����ɂ߂ȁB");
		swprintf_s(m_font[3], L"���Ȃ݂ɃX�y�V�����Z�́��q�G���^�[�L�[�ł������ł���v����ȁB");
		swprintf_s(m_font[4], L"�b");

		m_message_window_num = 33;
		m_yamada_window_num = 79;
		m_black_out_num = 20;

		g_is_operatable = false;//����s�\��
		m_black_out_f = true;//���X�ɈÓ]
	}
	//�G���f�B���O���b�Z�[�W���ݒ�
	else if (m_Scene_id == 30)
	{
		swprintf_s(m_font[0], L"�您�A�v���Ԃ肾�ȁB�`������̓G�͕��������������ȁB");
		
		//�X�y�V�����Z����؎g��Ȃ������ꍇ�A�Z���t���኱�ς��B
		if (g_tutorial_progress == 16 || g_tutorial_progress == 17)
		{
			swprintf_s(m_font[1], L"�����������ƃX�y�V�����Z���g�킸�Ɂ������Â���Ƃ́c�c�B�`���x%s�v�A���܂��z���g�ɐ��܂ꂽ�Ă��H�������v�����炢��������B", g_Player_Name);
		}
		else
		{
			swprintf_s(m_font[1], L"���������Ƃ͂����A�����ŋ߂܂Ő��܂ꂽ�Ă��������x%s�v���悭���Ă����񂾁B�`�����Ă����Ƃ��{���Ɋ�Ղ����B", g_Player_Name);
		}
		
		swprintf_s(m_font[2], L"�c�c�B�`�������A�N�񂾂��B�`���ǂ����x%s�v�Ƃ������̋����f�������������т̘f����H���s�������݂������B", g_Player_Name);
		swprintf_s(m_font[3], L"�����獡�͈��S���ċx�݂ȁB�`���Ȃ񂽂��č��͂��O����͍ŋ��Ȃ񂾂���ȁB");
		swprintf_s(m_font[4], L"�b");

		m_message_window_num = 33;
		m_yamada_window_num = 79;
		m_black_out_num = 20;

		g_is_operatable = false;//����s�\��(ObjMessage���������Ȃ�)
		m_black_out_f = true;//���X�ɈÓ]
	}
}

//�A�N�V����
void CObjMessage::Action()
{
	//�}�E�X�̈ʒu���擾
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//�}�E�X�̃{�^���̏��
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	//���L�[�t���O
	//�����N���b�NPush��ԁ����N���b�N��Push��ԂɂȂ�܂ŁA
	//�ēx���N���b�N���鎖�͏o���Ȃ������B
	if (m_mou_l == false)
	{
		m_key_f = false;
	}

	//���b�Z�[�W�\���@�\���쒆�̏���
	if (m_run_switch == true)
	{
		//���z�[�����1���
		if (m_Scene_id == 0 && 0 <= m_progress && m_progress <= 2)
		{
			//���S��\����͉��̏������s��Ȃ��悤�ɂ���B
			if (m_ignore_alpha <= 0.0f)
			{
				;//�����s��Ȃ�
			}
			//5�b��A�R�c�����\��m�点��t�H���g�摜�����X�ɔ�\���ɂ���
			else if (m_count >= 60 * 5 || m_ignore_alpha != 1.0f)
			{
				m_count = 0;//m_count��������
				m_ignore_alpha -= 0.01f;//�R�c�����\��m�点��t�H���g�摜�����X�ɔ�\���ɂ���
			}
			else
			{
				m_count++;//���Ԍv���J�n	
			}
		}


		//���퓬���1���
		if (m_Scene_id == 2 && m_progress == 2)
		{
			m_black_out_f = false;//���X�ɖ��]

			//�퓬�������ꎞ��~������
			CObjFight* fight = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
			fight->SetBattle_start(false);

			//���\��
			m_arrow_display_f = 1;
			m_arrow_angle_f = 1;
			m_arrow_x = 915.0f;
			m_arrow_y = 120.0f;
		}
		else if (m_Scene_id == 2 && m_progress == 3)
		{
			//���\��
			m_arrow_display_f = 1;
			m_arrow_angle_f = 1;
			m_arrow_x = 225.0f;
			m_arrow_y = 120.0f;
		}
		else if (m_Scene_id == 2 && (m_progress == 4 || m_progress == 5))
		{
			//���b�Z�[�W�E�C���h�E�ʒu�ύX
			m_is_top_or_bottom = 1;

			//���\��
			m_arrow_display_f = 1;
			m_arrow_angle_f = 0;
			m_arrow_y = 480.0f;

			m_count++;//���Ԍv��

			if (m_count >= 240)
			{
				m_count = 0;//m_count��������
			}
			else if (m_count >= 120)
			{
				m_arrow_x = 225.0f;
			}
			else
			{
				m_arrow_x = 915.0f;
			}
		}
		else if (m_Scene_id == 2 && m_progress == 6)
		{
			m_black_out_f = true;//���X�ɈÓ]

			//����\��
			m_arrow_display_f = 0;
			m_arrow_angle_f = 0;
			m_arrow_x = 0.0f;
			m_arrow_y = 0.0f;
			
			m_count = 0;//m_count��������
		}
		else if (m_Scene_id == 2 && m_progress == 8)
		{
			m_black_out_f = false;//���X�ɖ��]

			//���\��
			m_arrow_display_f = 1;
			m_arrow_angle_f = 1;
			m_arrow_x = 470.0f + m_swing_r * 1.5;
			m_arrow_y = 410.0f;
		}
		else if (m_Scene_id == 2 && m_progress == 11)
		{
			m_black_out_f = false;//���X�ɖ��]

			//���\��
			m_arrow_display_f = 1;
			m_arrow_angle_f = 2;
			m_arrow_x = 265.0f;
			m_arrow_y = 528.0f;
		}
		else if (m_Scene_id == 2 && m_progress == 12)
		{
			m_black_out_f = true;//���X�ɈÓ]

			//����\��
			m_arrow_display_f = 0;
		}
		else if (m_Scene_id == 2 && m_progress == 13)
		{
			m_black_out_f = false;//���X�ɖ��]

			//���b�Z�[�W�E�C���h�E�ʒu�ύX
			m_is_top_or_bottom = 0;

			//���\��
			m_arrow_display_f = 1;
			m_arrow_angle_f = 2;
			m_arrow_x = 250.0f;
			m_arrow_y = 50.0f;
		}
		else if (m_Scene_id == 2 && m_progress == 14)
		{
			m_black_out_f = true;//���X�ɈÓ]

			//����\��
			m_arrow_display_f = 0;
		}
		else if (m_Scene_id == 2 && m_progress == 15)
		{
			//���b�Z�[�W�E�C���h�E�ʒu�ύX
			m_is_top_or_bottom = 1;
		}
		else if (m_Scene_id == 2 && m_progress == 16)
		{
			m_black_out_f = false;//���X�ɖ��]

			//���\��
			m_arrow_display_f = 1;
			m_arrow_angle_f = 1;
			m_arrow_x = 368.5f;
			m_arrow_y = 410.0f;

			g_is_operatable = true;//����\�ɂ���
		}
		else if (m_Scene_id == 2 && m_progress == 22)
		{
			//���b�Z�[�W�E�C���h�E�ʒu�ύX
			m_is_top_or_bottom = 0;
		}
		else if (m_Scene_id == 2 && m_progress == 23)
		{
			m_black_out_f = false;//���X�ɖ��]

			//���\��
			m_arrow_display_f = 1;
			m_arrow_angle_f = 1;
			m_arrow_x = 557.5f;
			m_arrow_y = 80.0f;

			g_is_operatable = true;//����\�ɂ���
		}
		else if (m_Scene_id == 2 && m_progress == 34)
		{
			m_black_out_f = false;//���X�ɖ��]

			//���\��
			m_arrow_display_f = 1;
			m_arrow_angle_f = 0;
			m_arrow_x = 553.5f;
			m_arrow_y = 100.0f;
		}
		else if (m_Scene_id == 2 && m_progress == 35)
		{
			m_black_out_f = true;//���X�ɈÓ]

			//����\��
			m_arrow_display_f = 0;
		}
		else if (m_Scene_id == 2 && m_progress == 44)
		{
			m_black_out_f = false;//���X�ɖ��]

			//���\��
			m_arrow_display_f = 1;
			m_arrow_angle_f = 2;
			m_arrow_x = 880.0f;
			m_arrow_y = 185.0f;
		}
		else if (m_Scene_id == 2 && (m_progress == 45 || m_progress == 46))
		{
			//���\��
			m_arrow_y = 235.0f;
		}
		else if (m_Scene_id == 2 && m_progress == 47)
		{
			//���\��
			m_arrow_x = 550.0f;
			m_arrow_y = 310.0f;
		}
		else if (m_Scene_id == 2 && (m_progress == 48 || m_progress == 49))
		{
			//���b�Z�[�W�E�C���h�E�ʒu�ύX
			m_is_top_or_bottom = 1;

			//���\��
			m_arrow_x = 1030.0f;
			m_arrow_y = 435.0f;
		}
		else if (m_Scene_id == 2 && m_progress == 50)
		{
			m_black_out_f = true;//���X�ɈÓ]

			//����\��
			m_arrow_display_f = 0;
		}


		//���琬���
		else if (m_Scene_id == 8 && m_progress == 1)
		{
			m_black_out_f = false;//���X�ɖ��]

			//���\��
			m_arrow_display_f = 1;
			m_arrow_angle_f = 0;
			m_arrow_x = 140.0f;
			m_arrow_y = 520.0f;
		}
		else if (m_Scene_id == 8 && m_progress == 4)
		{
			m_black_out_f = false;//���X�ɖ��]

			//���\��
			m_arrow_display_f = 1;
			m_arrow_angle_f = 1;
			m_arrow_x = 70.0f;
			m_arrow_y = 340.0f;
		}
		else if (m_Scene_id == 8 && m_progress == 5)
		{
			//���b�Z�[�W�E�C���h�E�ʒu�ύX
			m_is_top_or_bottom = 0;

			m_black_out_f = false;//���X�ɖ��]

			//���\��
			m_arrow_display_f = 1;
			m_arrow_angle_f = 3;
			m_arrow_x = 510.0f;
			m_arrow_y = 15.0f;
		}
		else if (m_Scene_id == 8 && m_progress == 6)
		{
			m_black_out_f = true;//���X�ɈÓ]

			//����\��
			m_arrow_display_f = 0;
		}
		else if (m_Scene_id == 8 && m_progress == 15)
		{
			m_black_out_f = false;//���X�ɖ��]

			//���\��
			m_arrow_display_f = 1;
			m_arrow_angle_f = 3;
			m_arrow_x = 450.0f;
			m_arrow_y = 340.0f;	
		}
		else if (m_Scene_id == 8 && m_progress == 18)
		{
			//���b�Z�[�W�E�C���h�E�ʒu�ύX
			m_is_top_or_bottom = 1;

			m_black_out_f = false;//���X�ɖ��]

			//���\��
			m_arrow_display_f = 1;
			m_arrow_angle_f = 3;
			m_arrow_x = 640.0f;
			m_arrow_y = 440.0f;
		}
		else if (m_Scene_id == 8 && m_progress == 19)
		{
			//���b�Z�[�W�E�C���h�E�ʒu�ύX
			m_is_top_or_bottom = 0;

			m_black_out_f = false;//���X�ɖ��]

			//���\��
			m_arrow_display_f = 1;
			m_arrow_angle_f = 0;
			m_arrow_x = 75.0f;
			m_arrow_y = 130.0f;
		}
		else if (m_Scene_id == 8 && m_progress == 24)
		{
			m_black_out_f = false;//���X�ɖ��]

			//���\��
			m_arrow_display_f = 1;
			m_arrow_angle_f = 0;
			m_arrow_x = 75.0f;
			m_arrow_y = 130.0f;
		}
		else if (m_Scene_id == 8 && m_progress == 28)
		{
			//���b�Z�[�W�E�C���h�E�ʒu�ύX
			m_is_top_or_bottom = 1;

			m_black_out_f = false;//���X�ɖ��]
			
			//���\��
			m_arrow_display_f = 1;
			m_arrow_angle_f = 1;
			m_arrow_x = 70.0f;
			m_arrow_y = 340.0f;
		}
		else if (m_Scene_id == 8 && m_progress == 29)
		{
			//���b�Z�[�W�E�C���h�E�ʒu�ύX
			m_is_top_or_bottom = 0;

			m_black_out_f = false;//���X�ɖ��]

			//���\��
			m_arrow_display_f = 1;
			m_arrow_angle_f = 3;
			m_arrow_x = 510.0f;
			m_arrow_y = 15.0f;
		}
		else if (m_Scene_id == 8 && m_progress == 31)
		{
			m_black_out_f = false;//���X�ɖ��]

			//���\��
			m_arrow_display_f = 1;
			m_arrow_angle_f = 0;
			m_arrow_x = 65.0f;
			m_arrow_y = 120.0f;
		}
		else if (m_Scene_id == 8 && m_progress == 34)
		{
			//���b�Z�[�W�E�C���h�E�ʒu�ύX
			m_is_top_or_bottom = 0;

			m_black_out_f = false;//���X�ɖ��]

			//���\��
			m_arrow_display_f = 1;
			m_arrow_angle_f = 0;
			m_arrow_x = 325.0f;
			m_arrow_y = 350.0f;
		}
		else if (m_Scene_id == 8 && m_progress == 35)
		{
			//���\��
			m_arrow_display_f = 1;
			m_arrow_angle_f = 0;
			m_arrow_x = 850.0f;
			m_arrow_y = 350.0f;
		}
		else if (m_Scene_id == 8 && m_progress == 36)
		{
			//���b�Z�[�W�E�C���h�E�ʒu�ύX
			m_is_top_or_bottom = 1;

			//���\��
			m_arrow_display_f = 1;
			m_arrow_angle_f = 1;
			m_arrow_x = 325.0f;
			m_arrow_y = 270.0f;
		}
		else if (m_Scene_id == 8 && m_progress == 37)
		{
			//���\��
			m_arrow_display_f = 1;
			m_arrow_angle_f = 1;
			m_arrow_x = 850.0f;
			m_arrow_y = 270.0f;
		}
		else if (m_Scene_id == 8 && m_progress == 38)
		{
			//���b�Z�[�W�E�C���h�E�ʒu�ύX
			m_is_top_or_bottom = 0;

			m_black_out_f = false;//���X�ɖ��]

			//���\��
			m_arrow_display_f = 1;
			m_arrow_angle_f = 0;
			m_arrow_x = 65.0f;
			m_arrow_y = 120.0f;
		}
		else if (m_Scene_id == 8 && m_progress == 43)
		{
			//���b�Z�[�W�E�C���h�E�ʒu�ύX
			m_is_top_or_bottom = 0;

			m_black_out_f = false;//���X�ɖ��]

			//���\��
			m_arrow_display_f = 1;
			m_arrow_angle_f = 0;
			m_arrow_x = 5.0f;
			m_arrow_y = 60.0f;
		}


		//���퓬�������2���
		else if (m_Scene_id == 15 && m_progress == 2)
		{
			m_black_out_f = false;//���X�ɖ��]

			//���\��
			m_arrow_display_f = 1;
			m_arrow_angle_f = 1;
			m_arrow_x = 570.0f;
			m_arrow_y = 370.0f;
		}
		else if (m_Scene_id == 15 && m_progress == 3)
		{
			m_black_out_f = true;//���X�ɈÓ]

			//����\��
			m_arrow_display_f = 0;
		}


		//���퓬���2���
		else if (m_Scene_id == 16 && m_progress == 1)
		{
			m_black_out_f = false;//���X�ɖ��]

			//���\��
			m_arrow_display_f = 1;
			m_arrow_angle_f = 0;
			m_arrow_x = 1060.0f;
			m_arrow_y = 140.0f;
		}
		else if (m_Scene_id == 16 && m_progress == 2)
		{
			m_black_out_f = true;//���X�ɈÓ]

			//����\��
			m_arrow_display_f = 0;
		}
	}
	//�����b�Z�[�W�\���@�\����~�������̏���
	//�����b�Z�[�W�\���@�\��~���͂��̏����̒��ɓ���A
	//���̏����ȍ~�̏����͎��s����Ȃ��B
	//���ɂ��̏����̒��ɉ����������܂Ȃ���΁A
	//���b�Z�[�W�\���@�\���Ăѓ����ԂɂȂ鎖�͂Ȃ��B
	//�Ăѓ����Ԃɂ������ꍇ�A�����𖞂���������
	//�um_progress++�v�um_run_switch = true�v���鎖�œ��삳���鎖���o����B
	//���um_progress++�v����Ӗ��́A���b�Z�[�W�i�s�x�����ɐi�߂Ȃ��ƁA
	//�܂��u�b�v���ǂݍ��܂�Ă��܂����߁B
	else if (m_run_switch == false)
	{
		//���z�[�����1���
		if (m_Scene_id == 0 && m_progress == 0)
		{
			//���S�Ó]��A���b�Z�[�W�����J�n
			if (m_black_out_a >= 0.5f)
			{
				m_run_switch = true;//���b�Z�[�W�\���@�\����J�n
			}
		}
		else if (m_Scene_id == 0 && m_progress == 3)
		{
			if (m_arrow_display_f == 0 && m_arrow_angle_f == 1)
			{
				m_progress = 4;//�i�s�x�㏸�����Ă��̏������甲����

				return;
			}

			//���\��
			m_arrow_display_f = 1;
			m_arrow_angle_f = 1;
			m_arrow_x = 1050.0f;
			m_arrow_y = 340.0f;

			g_is_operatable = true;//����\��
			m_black_out_f = false;//��ʖ��]
			g_tutorial_progress = 1;//�`���[�g���A���i�s�x��1�ɂ���
		}


		//���퓬�������1���
		else if (m_Scene_id == 1 && m_progress == 1)
		{
			m_black_out_f = true;//���X�ɈÓ]
			
			//���S�Ó]��A���b�Z�[�W�����J�n
			if (m_black_out_a >= 0.5f)
			{
				m_run_switch = true;//���b�Z�[�W�\���@�\����J�n
			}
		}
		else if (m_Scene_id == 1 && m_progress == 3)
		{
			if (m_arrow_display_f == 0 && m_arrow_angle_f == 2)
			{
				g_is_operatable = false;//����s��
				m_black_out_f = true;//��ʈÓ]

				//���S�Ó]��A���b�Z�[�W�����J�n
				if (m_black_out_a >= 0.5f)
				{
					m_run_switch = true;//���b�Z�[�W�\���@�\����J�n
					m_progress = 4;//�i�s�x�㏸�����Ă��̏������甲����
				}

				return;
			}

			//���\��
			m_arrow_display_f = 1;
			m_arrow_angle_f = 2;
			m_arrow_x = 800.0f;
			m_arrow_y = 250.0f;

			g_is_operatable = true;//����\��
			m_black_out_f = false;//��ʖ��]
		}
		else if (m_Scene_id == 1 && m_progress == 7)
		{
			g_tutorial_progress = 2;//�`���[�g���A���i�s�x��2�ɂ���
		}


		//���퓬���1���
		else if (m_Scene_id == 2 && m_progress == 1)
		{
			m_count++;//���Ԍv���J�n

			//���S�Ó]��A���b�Z�[�W�����J�n
			if (m_black_out_a >= 0.5f)
			{
				m_run_switch = true;//���b�Z�[�W�\���@�\����J�n
				m_count = 0;//m_count��������
			}
			//�퓬�J�n1�b��A��ʈÓ]�����J�n
			else if (m_count >= 60 * 1)
			{
				m_black_out_f = true;//��ʈÓ]
			}
		}
		else if (m_Scene_id == 2 && m_progress == 9)
		{			
			//�|�b�h����������P�o��΁A���̏����ɓ���
			if (m_arrow_display_f == 0)
			{
				m_count++;//���Ԍv���J�n

				g_is_operatable = false;//����s�\�ɂ���

				//���S�Ó]��A���b�Z�[�W�����J�n
				if (m_black_out_a >= 0.5f)
				{
					//�퓬�������ꎞ��~������
					CObjFight* fight = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
					fight->SetBattle_start(false);

					m_run_switch = true;//���b�Z�[�W�\���@�\����J�n
					m_count = 0;//m_count��������
					m_progress = 10;//�i�s�x�㏸�����Ă��̏������甲����
				}
				//1�b��A��ʈÓ]�����J�n
				else if (m_count >= 60 * 1)
				{
					m_black_out_f = true;//��ʈÓ]
				}

				return;
			}

			//���\��
			m_arrow_x = 470.0f + m_swing_r * 1.5;
			m_arrow_y = 410.0f;

			//�퓬�������ĊJ������
			CObjFight* fight = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
			fight->SetBattle_start(true);

			g_tutorial_progress = 3;//�`���[�g���A���i�s�x��3�ɐݒ�	
		}
		else if (m_Scene_id == 2 && m_progress == 17)
		{
			//�~�T�C�����P�o��΁A���̏����ɓ���
			if (m_arrow_display_f == 0)
			{
				m_count++;//���Ԍv���J�n

				g_is_operatable = false;//����s�\�ɂ���

				//���S�Ó]��A���b�Z�[�W�����J�n
				if (m_black_out_a >= 0.5f)
				{
					//�퓬�������ꎞ��~������
					CObjFight* fight = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
					fight->SetBattle_start(false);

					m_run_switch = true;//���b�Z�[�W�\���@�\����J�n
					m_count = 0;//m_count��������
					m_progress = 18;//�i�s�x�㏸�����Ă��̏������甲����
				}
				//1�b��A��ʈÓ]�����J�n
				else if (m_count >= 60 * 1)
				{
					m_black_out_f = true;//��ʈÓ]
				}

				return;
			}

			//���\��
			m_arrow_x = 368.5f;
			m_arrow_y = 410.0f;

			//�퓬�������ĊJ������
			CObjFight* fight = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
			fight->SetBattle_start(true);

			g_tutorial_progress = 4;//�`���[�g���A���i�s�x��4�ɐݒ�	
		}
		else if (m_Scene_id == 2 && m_progress == 24)
		{
			//���[���I���o����΁A���̏����ɓ���
			if (m_arrow_display_f == 0)
			{
				m_count++;//���Ԍv���J�n

				g_is_operatable = false;//����s�\�ɂ���

				//���S�Ó]��A���b�Z�[�W�����J�n
				if (m_black_out_a >= 0.5f)
				{
					//�퓬�������ꎞ��~������
					CObjFight* fight = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
					fight->SetBattle_start(false);

					m_run_switch = true;//���b�Z�[�W�\���@�\����J�n
					m_count = 0;//m_count��������
					m_progress = 25;//�i�s�x�㏸�����Ă��̏������甲����
				}
				//1�b��A��ʈÓ]�����J�n
				else if (m_count >= 60 * 1)
				{
					m_black_out_f = true;//��ʈÓ]
				}

				return;
			}

			//���\��
			m_arrow_x = 557.5f;
			m_arrow_y = 80.0f;

			//�퓬�������ĊJ������
			CObjFight* fight = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
			fight->SetBattle_start(true);

			g_tutorial_progress = 5;//�`���[�g���A���i�s�x��5�ɐݒ�	
		}
		else if (m_Scene_id == 2 && m_progress == 37)
		{
			m_black_out_f = false;//��ʖ��]

			g_is_operatable = true;//����\�ɂ���

			//�퓬�������ĊJ������
			CObjFight* fight = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
			fight->SetBattle_start(true);

			g_tutorial_progress = 6;//�`���[�g���A���i�s�x��6�ɐݒ�	
		}
		else if (m_Scene_id == 2 && m_progress == 38)
		{
			m_black_out_f = true;//���X�ɈÓ]

			//���S�Ó]��A���b�Z�[�W�����J�n
			if (m_black_out_a >= 0.5f)
			{
				m_run_switch = true;//���b�Z�[�W�\���@�\����J�n
				m_progress = 39;//�i�s�x�㏸�����Ă��̏������甲����
			}
		}
		else if (m_Scene_id == 2 && m_progress == 40)
		{
			m_black_out_f = false;//��ʖ��]

			//�N���A��ʕ\��
			CObjFight* fight = (CObjFight*)Objs::GetObj(OBJ_FIGHT);
			fight->SetEnd();

			//�퓬���y��j�����������y�Đ�
			Audio::Stop(0);
			Audio::Start(4);

			m_progress = 41;//�i�s�x�㏸�����Ă��̏������甲����
		}
		else if (m_Scene_id == 2 && m_progress == 42)
		{
			m_black_out_f = true;//���X�ɈÓ]

			//���S�Ó]��A���b�Z�[�W�����J�n
			if (m_black_out_a >= 0.5f)
			{
				m_run_switch = true;//���b�Z�[�W�\���@�\����J�n
				m_progress = 43;//�i�s�x�㏸�����Ă��̏������甲����
			}
		}
		else if (m_Scene_id == 2 && m_progress == 51)
		{
			m_black_out_f = false;//���X�ɖ��]

			g_tutorial_progress = 7;//�`���[�g���A���i�s�x��7�ɂ���B
		}


		//���z�[�����2���
		else if (m_Scene_id == 7 && m_progress == 0)
		{
			//���S�Ó]��A���b�Z�[�W�����J�n
			if (m_black_out_a >= 0.5f)
			{
				m_run_switch = true;//���b�Z�[�W�\���@�\����J�n
			}
		}
		else if (m_Scene_id == 7 && m_progress == 2)
		{
			if (m_arrow_display_f == 0 && m_arrow_angle_f == 1)
			{
				m_progress = 3;//�i�s�x�㏸�����Ă��̏������甲����

				return;
			}

			//���\��
			m_arrow_display_f = 1;
			m_arrow_angle_f = 1;
			m_arrow_x = 90.0f;
			m_arrow_y = 340.0f;

			g_is_operatable = true;//����\��
			m_black_out_f = false;//��ʖ��]
			g_tutorial_progress = 8;//�`���[�g���A���i�s�x��8�ɂ���
		}


		//���琬���
		else if (m_Scene_id == 8 && m_progress == 0)
		{
			m_count++;//���Ԍv���J�n

			 //���S�Ó]��A���b�Z�[�W�����J�n
			if (m_black_out_a >= 0.5f)
			{
				m_run_switch = true;//���b�Z�[�W�\���@�\����J�n
				m_count = 0;//m_count��������
			}
			//1�b��A��ʈÓ]�����J�n
			else if (m_count >= 60 * 1)
			{
				m_black_out_f = true;//��ʈÓ]
			}
		}
		else if (m_Scene_id == 8 && m_progress == 2)
		{
			if (m_arrow_display_f == 0)
			{
				m_count++;//���Ԍv���J�n

				g_is_operatable = false;//����s�\��

				//���S�Ó]��A���b�Z�[�W�����J�n
				if (m_black_out_a >= 0.5f)
				{
					m_run_switch = true;//���b�Z�[�W�\���@�\����J�n
					m_count = 0;//m_count��������
					m_progress = 3;//�i�s�x�㏸�����Ă��̏������甲����
				}
				//0.5�b��A��ʈÓ]�����J�n
				else if (m_count >= 60 * 0.5)
				{
					m_black_out_f = true;//��ʈÓ]
				}

				return;
			}

			g_tutorial_progress = 9;//�`���[�g���A���i�s�x��9�ɂ���

			g_is_operatable = true;//����\��
		}
		else if (m_Scene_id == 8 && m_progress == 16)
		{
			if (m_arrow_display_f == 0)
			{
				m_count++;//���Ԍv���J�n

				g_is_operatable = false;//����s�\��
				
				//���S�Ó]��A���b�Z�[�W�����J�n
				if (m_black_out_a >= 0.5f)
				{
					m_run_switch = true;//���b�Z�[�W�\���@�\����J�n
					m_count = 0;//m_count��������
					m_progress = 17;//�i�s�x�㏸�����Ă��̏������甲����
				}
				//0.5�b��A��ʈÓ]�����J�n
				else if (m_count >= 60 * 0.5)
				{
					m_black_out_f = true;//��ʈÓ]
				}

				return;
			}

			g_tutorial_progress = 10;//�`���[�g���A���i�s�x��10�ɂ���

			g_is_operatable = true;//����\��
		}
		else if (m_Scene_id == 8 && m_progress == 20)
		{
			if (m_arrow_display_f == 0)
			{
				m_count++;//���Ԍv���J�n

				g_is_operatable = false;//����s�\��

				//���S�Ó]��A���b�Z�[�W�����J�n
				if (m_black_out_a >= 0.5f)
				{
					m_run_switch = true;//���b�Z�[�W�\���@�\����J�n
					m_count = 0;//m_count��������
					m_progress = 21;//�i�s�x�㏸�����Ă��̏������甲����
				}
				//0.5�b��A��ʈÓ]�����J�n
				else if (m_count >= 60 * 0.5)
				{
					m_black_out_f = true;//��ʈÓ]
				}

				return;
			}

			g_tutorial_progress = 11;//�`���[�g���A���i�s�x��11�ɂ���

			g_is_operatable = true;//����\��
		}
		else if (m_Scene_id == 8 && m_progress == 25)
		{
			if (m_arrow_display_f == 0)
			{
				m_count++;//���Ԍv���J�n

				g_is_operatable = false;//����s�\��
				
				//���S�Ó]��A���b�Z�[�W�����J�n
				if (m_black_out_a >= 0.5f)
				{
					m_run_switch = true;//���b�Z�[�W�\���@�\����J�n
					m_count = 0;//m_count��������
					m_progress = 26;//�i�s�x�㏸�����Ă��̏������甲����
				}
				//0.5�b��A��ʈÓ]�����J�n
				else if (m_count >= 60 * 0.5)
				{
					m_black_out_f = true;//��ʈÓ]
				}

				return;
			}

			g_is_operatable = true;//����\��

			g_tutorial_progress = 12;//�`���[�g���A���i�s�x��12�ɂ���
		}
		else if (m_Scene_id == 8 && m_progress == 32)
		{
			if (m_arrow_display_f == 0)
			{
				m_count++;//���Ԍv���J�n

				g_is_operatable = false;//����s�\��

				//���S�Ó]��A���b�Z�[�W�����J�n
				if (m_black_out_a >= 0.5f)
				{
					m_run_switch = true;//���b�Z�[�W�\���@�\����J�n
					m_count = 0;//m_count��������
					m_progress = 33;//�i�s�x�㏸�����Ă��̏������甲����
				}
				//0.5�b��A��ʈÓ]�����J�n
				else if (m_count >= 60 * 0.5)
				{
					m_black_out_f = true;//��ʈÓ]
				}

				return;
			}

			g_is_operatable = true;//����\��

			g_tutorial_progress = 13;//�`���[�g���A���i�s�x��13�ɂ���
		}
		else if (m_Scene_id == 8 && m_progress == 39)
		{
			if (m_arrow_display_f == 0)
			{
				m_count++;//���Ԍv���J�n

				g_is_operatable = false;//����s�\��

				//���b�Z�[�W�E�C���h�E�ʒu�ύX
				m_is_top_or_bottom = 1;

				//���S�Ó]��A���b�Z�[�W�����J�n
				if (m_black_out_a >= 0.5f)
				{
					m_run_switch = true;//���b�Z�[�W�\���@�\����J�n
					m_count = 0;//m_count��������
					m_progress = 40;//�i�s�x�㏸�����Ă��̏������甲����
				}
				//0.5�b��A��ʈÓ]�����J�n
				else if (m_count >= 60 * 0.5)
				{
					m_black_out_f = true;//��ʈÓ]
				}

				return;
			}

			g_is_operatable = true;//����\��

			g_tutorial_progress = 14;//�`���[�g���A���i�s�x��14�ɂ���
		}
		else if (m_Scene_id == 8 && m_progress == 44)
		{
			m_black_out_f = false;//���X�ɖ��]

			g_tutorial_progress = 15;//�`���[�g���A���i�s�x��15�ɂ���

			m_arrow_display_f = 0;//����\��

			g_is_operatable = true;//����\��
		}


		//���퓬�������2���
		else if (m_Scene_id == 15 && m_progress == 1)
		{
			m_black_out_f = true;//���X�ɈÓ]

			//���S�Ó]��A���b�Z�[�W�����J�n
			if (m_black_out_a >= 0.5f)
			{
				m_run_switch = true;//���b�Z�[�W�\���@�\����J�n
			}
		}
		else if (m_Scene_id == 15 && m_progress == 4)
		{
			m_black_out_f = false;//���X�ɖ��]

			g_tutorial_progress = 16;//�`���[�g���A���i�s�x��16�ɂ���

			g_is_operatable = true;//����\��
		}


		//�퓬���2���
		else if (m_Scene_id == 16 && m_progress == 0 && g_tutorial_progress != 31)
		{
			//���S�Ó]��A���b�Z�[�W�����J�n
			if (m_black_out_a >= 0.5f)
			{
				m_run_switch = true;//���b�Z�[�W�\���@�\����J�n
			}
		}
		else if (m_Scene_id == 16 && m_progress == 4 && g_tutorial_progress != 31)
		{
			m_black_out_f = false;//���X�ɖ��]

			g_tutorial_progress = 18;//�`���[�g���A���i�s�x��18(�ő�l)�ɂ���

			g_is_operatable = true;//����\��
		}


		//���G���f�B���O���
		else if (m_Scene_id == 30 && m_progress == 0)
		{
			//���S�Ó]��A���b�Z�[�W�����J�n
			if (m_black_out_a >= 0.5f)
			{
				m_run_switch = true;//���b�Z�[�W�\���@�\����J�n
			}
		}
		else if (m_Scene_id == 30 && m_progress == 4)
		{
			g_is_operatable = true;//����\��
			m_black_out_f = false;//��ʖ��]

			g_tutorial_progress = 31;//�G���f�B���O�ցB
		}

		return;
	}

	//�����b�Z�[�W�\���@�\��~����
	//���u�b(���b�Z�[�W�\���@�\��~)�v��������Ă���΁A
	//���̏��������s�����B
	if (m_font[m_progress][m_font_count] == L'�b')
	{
		m_run_switch = false;
		m_skip_f = false;//�X�L�b�v�t���OOFF(�Ăѓ����ԂƂȂ������A�X�L�b�v�����̂�h������)

		return;
	}


	//�����݃��b�Z�[�W�̕�����̒������擾
	//���V���ȃ��b�Z�[�W�擾���ɂP�񂾂����s�����B
	if (m_length == 0)
	{
		//�������̏I��蕔���Ɉ�(�G)������
		swprintf_s(m_font[m_progress], L"%s�G", m_font[m_progress]);

		for (int i = 0; m_font[m_progress][i] != L'�G'; i++)
		{
			m_length = i;
		}
	}

	//�����͓r���̃N���b�N�v������
	if (m_font[m_progress][m_font_count] == L'�`')
	{
		m_reminder_f = true;//�N���b�N�Ñ��摜�\��

		//���݂̃��b�Z�[�W���Ō�܂ŕ\������Ă��Ȃ��Ƃ��A
		//'�`'�������΃N���b�N����܂Ń��b�Z�[�W���~�߂鎖���o����B
		//���̏����ɓ����Ă��鎞�ɁA���N���b�N���鎖�Ń��b�Z�[�W�̑����������B
		//���X�L�b�v�t���OON���̓N���b�N�����Ƃ��A����ɏ������i�ށB
		if (m_mou_l == true && m_key_f == false || m_skip_f == true)
		{
			//���݂̃t�H���g�`��ʒuX�����̂܂܎��̃t�H���g�`��ʒuX�ɓ����
			//��'�q'���̕����͓��������̖��ߕ��ł���A�`�悷���ł͂Ȃ����߁B
			m_font_draw_x[m_font_count + 1] = m_font_draw_x[m_font_count];

			m_font_count++;	//�\�����悤�Ƃ��Ă��镶�������̃t�H���g���֕ύX����


			m_fast_f = false;//�`�摬�x��������~
			m_key_f = true;//�L�[�t���O�𗧂Ă�
			m_reminder_f = false;//�N���b�N�Ñ��摜��\��

			//�I����
			Audio::Start(1);
		}

		return;
	}

	//�����b�Z�[�W�J���[�ύX����
	if (m_font[m_progress][m_font_count] == L'�q' || m_font[m_progress][m_font_count] == L'�f' ||
		m_font[m_progress][m_font_count] == L'�x' || m_font[m_progress][m_font_count] == L'�v')
	{
		if (m_font[m_progress][m_font_count] == L'�q')
		{
			//�q�錾�̌��ɂ���t�H���g�S�Ă�ԐF�ɕύX����
			for (int i = m_font_count; i <= m_length; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (j != 0)
					{
						m_font_color[i][j] = 0.25f;
					}
					else
					{
						m_font_color[i][j] = 1.0f;
					}
				}
			}
		}
		else if (m_font[m_progress][m_font_count] == L'�f')
		{
			//�f�錾�̌��ɂ���t�H���g�S�Ă�ΐF�ɕύX����
			for (int i = m_font_count; i <= m_length; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (j != 1)
					{
						m_font_color[i][j] = 0.0f;
					}
					else
					{
						m_font_color[i][j] = 1.0f;
					}
				}
			}
		}
		else if (m_font[m_progress][m_font_count] == L'�x')
		{
			//�x�錾�̌��ɂ���t�H���g�S�Ă�F�ɕύX����
			for (int i = m_font_count; i <= m_length; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (j != 2)
					{
						m_font_color[i][j] = 1.0f;
					}
					else
					{
						m_font_color[i][j] = 0.0f;
					}
				}
			}
		}
		else  //(m_font[m_progress][m_font_count] == L'�v')
		{
			//�v�錾�̌��ɂ���t�H���g�S�Ă𔒐F�ɕύX����
			for (int i = m_font_count; i <= m_length; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					m_font_color[i][j] = 1.0f;
				}
			}
		}

		//���݂̃t�H���g�`��ʒuX�����̂܂܎��̃t�H���g�`��ʒuX�ɓ����
		//��'�q'���̕����͓��������̖��ߕ��ł���A�`�悷���ł͂Ȃ����߁B
		m_font_draw_x[m_font_count + 1] = m_font_draw_x[m_font_count];

		m_font_count++;	//�\�����悤�Ƃ��Ă��镶�������̃t�H���g���֕ύX����

		return;
	}
	
	//�����b�Z�[�W�\�����I������
	if (m_font[m_progress][m_font_count] == L'�G' || m_skip_f == true)
	{
		m_reminder_f = true;//�N���b�N�Ñ��摜�\��

		//�����b�Z�[�W�I���̏���
		//���݂̃��b�Z�[�W���Ō�܂ŕ\�������ƁA���̏��������s�����B
		//���̏�Ԃ̎��ɁA���N���b�N���鎖�Ŏ��̃��b�Z�[�W�ւƈڍs����B
		//���X�L�b�v�t���OON���̓��b�Z�[�W�I�����ĂȂ��Ă����̏����ɓ���B
		if (m_mou_l == true && m_key_f == false || m_skip_f == true)
		{
			//���̃��b�Z�[�W�ֈڍs����O�ɁA
			//���b�Z�[�W�\���ɕK�v�ȕϐ��������ɖ߂�
			for (int i = 0; i < FONT_MAX; i++)
			{
				m_font_column[i] = 0;
				m_font_line[i] = 0;
				m_font_draw_x[i] = 0;
				m_font_draw_y[i] = 0;

				for (int j = 0; j < 4; j++)
				{
					m_font_color[i][j] = 1.0f;
				}
			}

			m_time = 0;
			m_font_count = 0;
			m_length = 0;
			m_fast_f = false;

			m_key_f = true;//�L�[�t���O�𗧂Ă�
			m_reminder_f = false;//�N���b�N�Ñ��摜��\��
			m_progress++;//���b�Z�[�W�i�s�x�𑝉������A���̃��b�Z�[�W�ւƈڍs�B

			//�I����
			Audio::Start(1);
		}
	}
	else if (m_time <= 0 || m_fast_f == true)
	{
		//�����b�Z�[�W�\������
		//���݂̃��b�Z�[�W���Ō�܂ŕ\������Ă��Ȃ��ꍇ�A
		//m_time�ɂ��A0.08�b���ɂ��̏��������s�����B
		//�t�H���g�f�[�^�ɓo�^���ꂽ�������猻�ݕ\�����悤�Ƃ��Ă��镶����
		//���Ă͂܂���̂�T���A������΁A�K�؂Ȑ؂���ʒu��Ԃ��B
		//��������Ȃ���΋󔒂�Ԃ��B
		//���V���ɕ�����o�^�������ꍇ�A
		//�t�H���g�摜���X�V���A����ɓK������悤�Ƀt�H���g�f�[�^���X�V�����OK�B
		//���`�摬�x�������t���OON����m_time�֌W�Ȃ��ɂ��̏����ɓ���B


		//�󔒂̏���
		if (m_font[m_progress][m_font_count] == L'�Q')
		{
			m_font_column[m_font_count] = 0;
			m_font_line[m_font_count] = 0;
		}
		//���s�̏���
		else if (m_font[m_progress][m_font_count] == L'��')
		{
			m_font_column[m_font_count] = 0;
			m_font_line[m_font_count] = 0;

			m_font_draw_x[m_font_count + 1] = 0;//�t�H���g�`��ʒuX�������n�_�ɖ߂�
			m_font_count++;	//�\�����悤�Ƃ��Ă��镶�������̃t�H���g���֕ύX����

			//���s�ȍ~�̃t�H���g�`��ʒuY�����ɂ��炷
			//��m_length + 1�̗��R�́A�N���b�N�Ñ��摜�����ɂ��炵�������߁B
			for (int i = m_font_count; i <= m_length + 1; i++)
			{
				m_font_draw_y[i]++;
			}

			return;
		}
		//�t�H���g�f�[�^�ǂݍ��ݏ���
		//���󔒂ł����s�ł��Ȃ��ꍇ�A�t�H���g�f�[�^����̌������J�n����
		else
		{
			for (int i = 0; i < FONT_DATA_Y; i++)
			{
				for (int j = 0; j < FONT_DATA_X; j++)
				{
					//�t�H���g�f�[�^�̒[���ɓ��B����ƁA���̍s�Ɉڂ鏈��
					if (m_font_data[i][j] == NULL)
					{
						break;
					}
					//����HIT������A���̐؂���ʒu��������
					else if (m_font[m_progress][m_font_count] == m_font_data[i][j])
					{
						m_font_column[m_font_count] = j + 1;
						m_font_line[m_font_count] = i + 1;

						break;
					}
				}

				//�����I�����Ă���΁A�t�H���g�f�[�^�ǂݍ��ݏ������甲����
				if (m_font_column[m_font_count] != 0 || m_font_line[m_font_count] != 0)
				{
					break;
				}
			}
		}

		//���̃t�H���g�`��ʒuX�����݂̃t�H���g�`��ʒuX����ɉE�ɂ��炷
		m_font_draw_x[m_font_count + 1] = m_font_draw_x[m_font_count] + 1;

		m_font_count++;//�\�����悤�Ƃ��Ă��镶�������̃t�H���g���֕ύX����
		m_time = 5;//���̃t�H���g�`��܂ł̎��Ԃ�0.08�b�ɐݒ�
	}
	else
	{
		//�����̃t�H���g�`��܂ł̎��Ԍ�������
		m_time--;
	}


	//���b�Z�[�W�\�����ɍ��N���b�N���ꂽ��
	//���b�Z�[�W�`�摬�x������������t���O�𗧂Ă�
	if (m_mou_l == true && m_key_f == false)
	{
		m_fast_f = true;
		m_key_f = true;//�L�[�t���O�𗧂Ă�
	}
	//���b�Z�[�W�\������CTRL�L�[�����͂��ꂽ��
	//���b�Z�[�W�\���@�\��~�܂ł̃��b�Z�[�W��S�Ĕ�΂��t���O�𗧂Ă�
	else if (Input::GetVKey(VK_CONTROL) == true)
	{
		m_skip_f = true;
	}
}

//�h���[
void CObjMessage::Draw()
{
	//���b�Z�[�W�E�C���h�E�`��ʒu���z��
	float window_pos_y[2] = { 480.0f,20.0f };
	
	//���T�C�Y���Ǘ��z��
	float arrow_size[2] = { 0.0f,64.0f };
	
	//���p�x���Ǘ��z��
	float arrow_angle[4] = { 0.0f,180.0f,90.0f,270.0f };


	//���`��J���[���  R=RED  G=Green  B=Blue A=alpha(���ߏ��)
	float d[4] = { 1.0f,1.0f,1.0f,1.0f };//�t�H���g�摜�p
	float blackout[4] = { 1.0f,1.0f,1.0f,m_black_out_a };//��ʑS�̂��Ó]�摜�p
	float orange[4] = { 1.0f,0.5f,0.0f,1.0f };//�R�c�����摜�p
	float ignore[4] = { 1.0f,1.0f,0.0f,m_ignore_alpha };//�R�c�����\�m�点�镶���摜�p

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu


	//����ʏ��X�ɈÓ]�����X�ɖ��]����
	if (m_black_out_f == true)
	{
		if (m_black_out_a < 0.5f)
		{
			m_black_out_a += 0.01f;
		}
	}
	else
	{
		if (m_black_out_a > 0.0f)
		{
			m_black_out_a -= 0.01f;
		}
	}

	//��m_swing_vec�̒l�𑝌������鏈��
	//����ɂ��̏����͎��s����Ă���B
	//���ׁ̈A���̕ϐ���`��ʒu���ɑg�ݍ��ނ�
	//�����A�j���[�V���������鎖���o����Ƃ�����ł���B

	//�p�x���Z
	m_swing_r += 2.0f;

	//360���ŏ����l�ɖ߂�
	if (m_swing_r > 360.0f)
	{
		m_swing_r = 0.0f;
	}

	//�ړ�����
	m_swing_vec = sin(3.14f / 90 * m_swing_r);

	//���x�t����
	m_swing_vec *= 10.0f;



	//����ʑS�̂��Ó]�摜
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1200.0f;
	src.m_bottom = 700.0f;

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 1200.0f;
	dst.m_bottom = 700.0f;
	Draw::Draw(m_black_out_num, &src, &dst, blackout, 0.0f);

	//�����\��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 32.0f;
	src.m_bottom = 64.0f;

	if (m_arrow_angle_f <= 1)//��A������
	{
		dst.m_top = m_arrow_y + m_swing_vec;
		dst.m_left = m_arrow_x;
		dst.m_right = arrow_size[m_arrow_display_f] + m_arrow_x;
		dst.m_bottom = arrow_size[m_arrow_display_f] * 2.0f + m_arrow_y + m_swing_vec;
	}
	else					 //���A�E����
	{
		dst.m_top = m_arrow_y;
		dst.m_left = m_arrow_x + m_swing_vec;
		dst.m_right = arrow_size[m_arrow_display_f] + m_arrow_x + m_swing_vec;
		dst.m_bottom = arrow_size[m_arrow_display_f] * 2.0f + m_arrow_y;
	}
	Draw::Draw(191, &src, &dst, d, arrow_angle[m_arrow_angle_f]);


	//�����b�Z�[�W�\���@�\OFF���͈ȉ��̃h���[���������s���Ȃ�����
	if (m_run_switch == false)
	{
		return;
	}

	//���E�C���h�E�\������ 
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 800.0f;
	src.m_bottom = 790.0f;

	dst.m_top = window_pos_y[m_is_top_or_bottom];
	dst.m_left = 230.0f;
	dst.m_right = 540.0f;
	dst.m_bottom = window_pos_y[m_is_top_or_bottom] + 100.0f;
	Draw::Draw(m_message_window_num, &src, &dst, d, 0.0f);

	//���E�C���h�E�\������
	src.m_top = 30.0f;
	src.m_left = 800.0f;
	src.m_right = 1600.0f;
	src.m_bottom = 795.0f;

	dst.m_top = window_pos_y[m_is_top_or_bottom] + 100.0f;
	dst.m_left = 230.0f;
	dst.m_right = 540.0f;
	dst.m_bottom = window_pos_y[m_is_top_or_bottom] + 200.0f;
	Draw::Draw(m_message_window_num, &src, &dst, d, 0.0f);

	//���E�C���h�E�\�������� 
	src.m_top = 0.0f;
	src.m_left = 1600.0f;
	src.m_right = 2400.0f;
	src.m_bottom = 795.0f;

	dst.m_top = window_pos_y[m_is_top_or_bottom];
	dst.m_left = 530.0f;
	dst.m_right = 860.0f;
	dst.m_bottom = window_pos_y[m_is_top_or_bottom] + 100.0f;
	Draw::Draw(m_message_window_num, &src, &dst, d, 0.0f);

	//���E�C���h�E�\�������� 
	src.m_top = 5.0f;
	src.m_left = 2400.0f;
	src.m_right = 3200.0f;
	src.m_bottom = 800.0f;

	dst.m_top = window_pos_y[m_is_top_or_bottom] + 100.0f;
	dst.m_left = 540.0f;
	dst.m_right = 860.0f;
	dst.m_bottom = window_pos_y[m_is_top_or_bottom] + 200.0f;
	Draw::Draw(m_message_window_num, &src, &dst, d, 0.0f);

	//���E�C���h�E�E��
	src.m_top = 0.0f;
	src.m_left = 4000.0f;
	src.m_right = 4800.0f;
	src.m_bottom = 795.0f;

	dst.m_top = window_pos_y[m_is_top_or_bottom];
	dst.m_left = 860.0f;
	dst.m_right = 1180.0f;
	dst.m_bottom = window_pos_y[m_is_top_or_bottom] + 100.0f;
	Draw::Draw(m_message_window_num, &src, &dst, d, 0.0f);

	//���E�C���h�E�E��
	src.m_top = 5.0f;
	src.m_left = 4801.0f;
	src.m_right = 5600.0f;
	src.m_bottom = 800.0f;

	dst.m_top = window_pos_y[m_is_top_or_bottom] + 100.0f;
	dst.m_left = 850.0f;
	dst.m_right = 1180.0f;
	dst.m_bottom = window_pos_y[m_is_top_or_bottom] + 200.0f;
	Draw::Draw(m_message_window_num, &src, &dst, d, 0.0f);

	//���R�c�E�C���h�E�\��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1200.0f;
	src.m_bottom = 700.0f;

	dst.m_top = window_pos_y[m_is_top_or_bottom];
	dst.m_left = 20.0f;
	dst.m_right = 220.0f;
	dst.m_bottom = window_pos_y[m_is_top_or_bottom] + 200.0f;
	Draw::Draw(m_yamada_window_num, &src, &dst, d, 0.0f);

	//���R�c�\��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 160.0f;
	src.m_bottom = 240.0f;

	dst.m_top = window_pos_y[m_is_top_or_bottom] + 20.0f;
	dst.m_left = 40.0f;
	dst.m_right = 200.0f;
	dst.m_bottom = window_pos_y[m_is_top_or_bottom] + 180.0f;
	Draw::Draw(190, &src, &dst, d, 0.0f);

	//���R�c�����摜�\��
	FontDraw(L"�R�c", 255.0f, window_pos_y[m_is_top_or_bottom] + 8.0f, 36.0f, 36.0f, orange, false);

	//���N���b�N�Ñ��摜
	if (m_reminder_f == true)
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 36.0f;
		src.m_bottom = 35.0f;

		dst.m_top = window_pos_y[m_is_top_or_bottom] + 57.0f + (FONT_DRAW_SIZE * m_font_draw_y[m_font_count]) + m_swing_vec;
		dst.m_left = 264.0f + (FONT_DRAW_SIZE * m_font_draw_x[m_font_count]);
		dst.m_right = 246.0f + (FONT_DRAW_SIZE * (m_font_draw_x[m_font_count] + 1));
		dst.m_bottom = window_pos_y[m_is_top_or_bottom] + 39.0f + (FONT_DRAW_SIZE * (m_font_draw_y[m_font_count] + 1)) + m_swing_vec;
		Draw::Draw(189, &src, &dst, d, 0.0f);
	}

	//���R�c�����\��m�点��t�H���g�摜
	FontDraw(L"�b�s�q�k�L�[�ŎR�c�̘b�𖳎�����", 670.0f, 430.0f + m_swing_vec, 30.0f, 30.0f, ignore, false);



	//���݃��b�Z�[�W�̕�����̒������擾�o���Ă���Ύ��s�����
	if (m_length != 0)
	{
		//������̒���(�����̐�)���A�t�H���g�\���������s��
		//���t�H���g�P�P��for���ŕ����̑������񂵂āA�\�����Ă���B
		for (int i = 0; i <= m_length; i++)
		{
			//���t�H���g�\��
			src.m_top = FONT_CLIP_SIZE * (m_font_line[i] - 1);
			src.m_left = FONT_CLIP_SIZE * (m_font_column[i] - 1);
			src.m_right = FONT_CLIP_SIZE * m_font_column[i];
			src.m_bottom = FONT_CLIP_SIZE * m_font_line[i];

			dst.m_top = window_pos_y[m_is_top_or_bottom] + 48.0f + (FONT_DRAW_SIZE * m_font_draw_y[i]);
			dst.m_left = 255.0f + (FONT_DRAW_SIZE * m_font_draw_x[i]);
			dst.m_right = 255.0f + (FONT_DRAW_SIZE * (m_font_draw_x[i] + 1));
			dst.m_bottom = window_pos_y[m_is_top_or_bottom] + 48.0f + (FONT_DRAW_SIZE * (m_font_draw_y[i] + 1));

			//�ȉ��̓t�H���g�؂���ʒu(��A�s)�̂ǂ��炩��0�����͂���Ă����ꍇ�A
			//���̃t�H���g��\�����Ȃ������B
			if (src.m_right == 0.0f || src.m_bottom == 0.0f)
			{
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 0.0f;
				src.m_bottom = 0.0f;

				dst.m_top = 0.0f;
				dst.m_left = 0.0f;
				dst.m_right = 0.0f;
				dst.m_bottom = 0.0f;
			}

			Draw::Draw(121, &src, &dst, m_font_color[i], 0.0f);
		}
	}

	//�f�o�b�O�p���}�E�X�ʒu�\��
	//wchar_t mou[256];
	//swprintf_s(mou, L"x=%f,y=%f", m_mou_x, m_mou_y);
	//Font::StrDraw(mou, 20.0f, 20.0f, 12.0f, d);
}
