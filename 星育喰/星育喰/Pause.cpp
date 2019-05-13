#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameHead.h"
#include "Pause.h"

CObjPause::CObjPause(float x, float y)
{
	m_x = x;
	m_y = y;
}

//�C�j�V�����C�Y
void CObjPause::Init()
{
	Pause = 0;
}

//�A�N�V����
void CObjPause::Action()
{
	if (Input::GetVKey('M') == true)
	{
		if (Pause == 0)
		{
			Pause++;
		}
	}

	if (Pause == 1)
	{
		if (Input::GetVKey(VK_RETURN))
		{
			Pause--;
		}
	}
}

//�h���[
void CObjPause::Draw()
{

}