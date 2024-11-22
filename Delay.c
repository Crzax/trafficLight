/**************************************************
 * Author:       Crzax
 * Date:         2024-10-29
 * Description:  软件延时实现
 **************************************************/

#include <intrins.h>

/**
  * @brief  延时n ms
  * @param  n，代表几ms
  * @retval 无
  */
void delay(unsigned int n)		//@11.0592MHz
{
	while (n)
	{
		unsigned char i, j;

		_nop_();
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
		--n;
	}
}