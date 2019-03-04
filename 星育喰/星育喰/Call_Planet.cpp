//g—p‚·‚éƒwƒbƒ_[
//#include "math.h" //”ŠwŒvZƒwƒbƒ_[
#include "GameL\DrawTexture.h"
#include <stdlib.h>
#include <time.h>

//g—p‚·‚éƒl[ƒ€ƒXƒy[ƒX
using namespace GameL;

//---Call_PlanetŠÖ”
//ˆø”1@int *progress	:ƒXƒe[ƒWis“x
//ˆø”2@int *select	:˜f¯‘I‘ğ
//“à—e
//ƒXƒe[ƒWis“x‚É‰‚¶‚½“G˜f¯(”wŒi)‚ğ•Ô‚·B
void Call_Planet(int progress, int select)
{
	if (progress == 1)
	{
		if (select == 1)
		{
			//“G˜f¯1‚ğ“Ç‚İ‚İ20”Ô‚É“o˜^
			Draw::LoadImage(L"Enemy_Planet_Test.jpg", 20, TEX_SIZE_512);	
		}
		else if (select == 2)
		{
			//“G˜f¯2‚ğ“Ç‚İ‚İ22”Ô‚É“o˜^
			Draw::LoadImage(L"Enemy_Planet_Test2.jpg", 22, TEX_SIZE_512);

			//“G˜f¯2•\¦
			//Draw::Draw(22, &src, &dst, d, 0.0f);
		}
		else if (select == 3)
		{
			//“G˜f¯3‚ğ“Ç‚İ‚İ24”Ô‚É“o˜^
			Draw::LoadImage(L"Enemy_Planet_Test3.jpg", 24, TEX_SIZE_512);

			//“G˜f¯3•\¦
			//Draw::Draw(24, &src, &dst, d, 0.0f);
		}
		else  //(select == 4)
		{
			//“G˜f¯4‚ğ“Ç‚İ‚İ26”Ô‚É“o˜^
			Draw::LoadImage(L"Enemy_Planet_Test4.jpg", 26, TEX_SIZE_512);

			//“G˜f¯4•\¦
			//Draw::Draw(26, &src, &dst, d, 0.0f);
		}
	}

	else if (progress == 2)
	{
		if (select == 1)
		{
			//“G˜f¯1‚ğ“Ç‚İ‚İ20”Ô‚É“o˜^
			Draw::LoadImage(L"Enemy_Planet_Test.jpg", 20, TEX_SIZE_512);

			//“G˜f¯1•\¦
			//Draw::Draw(20, &src, &dst, d, 0.0f);
		}
		else if (select == 2)
		{
			//“G˜f¯2‚ğ“Ç‚İ‚İ22”Ô‚É“o˜^
			Draw::LoadImage(L"Enemy_Planet_Test2.jpg", 22, TEX_SIZE_512);

			//“G˜f¯2•\¦
			//Draw::Draw(22, &src, &dst, d, 0.0f);
		}
		else if (select == 3)
		{
			//“G˜f¯3‚ğ“Ç‚İ‚İ24”Ô‚É“o˜^
			Draw::LoadImage(L"Enemy_Planet_Test3.jpg", 24, TEX_SIZE_512);

			//“G˜f¯3•\¦
			//Draw::Draw(24, &src, &dst, d, 0.0f);
		}
		else  //(select == 4)
		{
			//“G˜f¯4‚ğ“Ç‚İ‚İ26”Ô‚É“o˜^
			Draw::LoadImage(L"Enemy_Planet_Test4.jpg", 26, TEX_SIZE_512);

			//“G˜f¯4•\¦
			//Draw::Draw(26, &src, &dst, d, 0.0f);
		}
	}

	else  //(*progress == 3)
	{
		if (select == 1)
		{
			//“G˜f¯1‚ğ“Ç‚İ‚İ20”Ô‚É“o˜^
			Draw::LoadImage(L"Enemy_Planet_Test.jpg", 20, TEX_SIZE_512);

			//“G˜f¯1•\¦
			//Draw::Draw(20, &src, &dst, d, 0.0f);
		}
		else if (select == 2)
		{
			//“G˜f¯2‚ğ“Ç‚İ‚İ22”Ô‚É“o˜^
			Draw::LoadImage(L"Enemy_Planet_Test2.jpg", 22, TEX_SIZE_512);

			//“G˜f¯2•\¦
			//Draw::Draw(22, &src, &dst, d, 0.0f);
		}
		else if (select == 3)
		{
			//“G˜f¯3‚ğ“Ç‚İ‚İ24”Ô‚É“o˜^
			Draw::LoadImage(L"Enemy_Planet_Test3.jpg", 24, TEX_SIZE_512);

			//“G˜f¯3•\¦
			//Draw::Draw(24, &src, &dst, d, 0.0f);
		}
		else  //(select == 4)
		{
			//“G˜f¯4‚ğ“Ç‚İ‚İ26”Ô‚É“o˜^
			Draw::LoadImage(L"Enemy_Planet_Test4.jpg", 26, TEX_SIZE_512);

			//“G˜f¯4•\¦
			//Draw::Draw(26, &src, &dst, d, 0.0f);
		}
	}

}