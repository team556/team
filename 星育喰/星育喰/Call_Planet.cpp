//�g�p����w�b�_�[
//#include "math.h" //���w�v�Z�w�b�_�[
#include "GameL\DrawTexture.h"
#include <stdlib.h>
#include <time.h>

//�g�p����l�[���X�y�[�X
using namespace GameL;

//---Call_Planet�֐�
//����1�@int *progress	:�X�e�[�W�i�s�x
//����2�@int *select	:�f���I��
//���e
//�X�e�[�W�i�s�x�ɉ������G�f��(�w�i)��Ԃ��B
void Call_Planet(int progress, int select)
{
	if (progress == 1)
	{
		if (select == 1)
		{
			//�G�f��1��ǂݍ���20�Ԃɓo�^
			Draw::LoadImage(L"Enemy_Planet_Test.jpg", 20, TEX_SIZE_512);	
		}
		else if (select == 2)
		{
			//�G�f��2��ǂݍ���22�Ԃɓo�^
			Draw::LoadImage(L"Enemy_Planet_Test2.jpg", 22, TEX_SIZE_512);

			//�G�f��2�\��
			//Draw::Draw(22, &src, &dst, d, 0.0f);
		}
		else if (select == 3)
		{
			//�G�f��3��ǂݍ���24�Ԃɓo�^
			Draw::LoadImage(L"Enemy_Planet_Test3.jpg", 24, TEX_SIZE_512);

			//�G�f��3�\��
			//Draw::Draw(24, &src, &dst, d, 0.0f);
		}
		else  //(select == 4)
		{
			//�G�f��4��ǂݍ���26�Ԃɓo�^
			Draw::LoadImage(L"Enemy_Planet_Test4.jpg", 26, TEX_SIZE_512);

			//�G�f��4�\��
			//Draw::Draw(26, &src, &dst, d, 0.0f);
		}
	}

	else if (progress == 2)
	{
		if (select == 1)
		{
			//�G�f��1��ǂݍ���20�Ԃɓo�^
			Draw::LoadImage(L"Enemy_Planet_Test.jpg", 20, TEX_SIZE_512);

			//�G�f��1�\��
			//Draw::Draw(20, &src, &dst, d, 0.0f);
		}
		else if (select == 2)
		{
			//�G�f��2��ǂݍ���22�Ԃɓo�^
			Draw::LoadImage(L"Enemy_Planet_Test2.jpg", 22, TEX_SIZE_512);

			//�G�f��2�\��
			//Draw::Draw(22, &src, &dst, d, 0.0f);
		}
		else if (select == 3)
		{
			//�G�f��3��ǂݍ���24�Ԃɓo�^
			Draw::LoadImage(L"Enemy_Planet_Test3.jpg", 24, TEX_SIZE_512);

			//�G�f��3�\��
			//Draw::Draw(24, &src, &dst, d, 0.0f);
		}
		else  //(select == 4)
		{
			//�G�f��4��ǂݍ���26�Ԃɓo�^
			Draw::LoadImage(L"Enemy_Planet_Test4.jpg", 26, TEX_SIZE_512);

			//�G�f��4�\��
			//Draw::Draw(26, &src, &dst, d, 0.0f);
		}
	}

	else  //(*progress == 3)
	{
		if (select == 1)
		{
			//�G�f��1��ǂݍ���20�Ԃɓo�^
			Draw::LoadImage(L"Enemy_Planet_Test.jpg", 20, TEX_SIZE_512);

			//�G�f��1�\��
			//Draw::Draw(20, &src, &dst, d, 0.0f);
		}
		else if (select == 2)
		{
			//�G�f��2��ǂݍ���22�Ԃɓo�^
			Draw::LoadImage(L"Enemy_Planet_Test2.jpg", 22, TEX_SIZE_512);

			//�G�f��2�\��
			//Draw::Draw(22, &src, &dst, d, 0.0f);
		}
		else if (select == 3)
		{
			//�G�f��3��ǂݍ���24�Ԃɓo�^
			Draw::LoadImage(L"Enemy_Planet_Test3.jpg", 24, TEX_SIZE_512);

			//�G�f��3�\��
			//Draw::Draw(24, &src, &dst, d, 0.0f);
		}
		else  //(select == 4)
		{
			//�G�f��4��ǂݍ���26�Ԃɓo�^
			Draw::LoadImage(L"Enemy_Planet_Test4.jpg", 26, TEX_SIZE_512);

			//�G�f��4�\��
			//Draw::Draw(26, &src, &dst, d, 0.0f);
		}
	}

}