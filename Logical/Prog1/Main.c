
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

void _INIT ProgramInit(void)
{	
	speed = count = 0;
	
	fb_motor.dt = fb_regulator.dt = 0.002;
	
	fb_regulator.k_p = 0.0064;
	fb_regulator.k_i = 0.16;
	fb_regulator.max_abs_value = 24;
	
	fb_motor.Tm = fb_regulator.k_p / fb_regulator.k_i;
	fb_motor.ke = 3 * fb_motor.dt * fb_regulator.k_i;
}

void _CYCLIC ProgramCyclic(void)
{
	//step function
	if (speed < 7000)
		speed += 50;
	
	if (count == 0)
	{
		fb_regulator.e = speed;
		FB_Regulator(&fb_regulator);
		fb_motor.u = fb_regulator.u;
		FB_Motor(&fb_motor);
	}
	else
	{
		fb_regulator.e = speed - fb_motor.w;
		FB_Regulator(&fb_regulator);
		fb_motor.u = fb_regulator.u;
		FB_Motor(&fb_motor);
	}
	
	count++;
}

void _EXIT ProgramExit(void)
{

}

