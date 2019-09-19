
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

void _INIT ProgramInit(void)
{	
	enable = 0;
	
	speed = count = 0;
	
	fb_motor.dt = fb_regulator.dt = 0.002;
	
	fb_regulator.k_p = 0.0064;
	fb_regulator.k_i = 0.16;
	fb_regulator.max_abs_value = 24;
	
	fb_motor.Tm = fb_regulator.k_p / fb_regulator.k_i;
	fb_motor.ke = 5 * fb_motor.dt * fb_regulator.k_i;
}

void _CYCLIC ProgramCyclic(void)
{
	//delaying enabling
	if (count >= 25)
		enable = 1;
	
	if (enable)
	{
		//step function (10 secs period)
		if (count % 50 == 0)
			speed = speed == 0 ? 2000 : 0;
	
		//processing system's output (integrator link in direct circuit)
		fb_regulator.e = speed - fb_motor.w;
		fb_regulator.e_prev = reg_prev;
		FB_Regulator(&fb_regulator);
		fb_motor.u = mot_prev;
		FB_Motor(&fb_motor);
		
		//processing system's output (integrator link in feedback circuit)
		/*fb_regulator.e = speed - fb_motor.w;
		fb_regulator.e_prev = 0;
		fb_regulator.count = count;
		FB_Regulator(&fb_regulator);
		fb_motor.u = fb_regulator.u;
		FB_Motor(&fb_motor);*/
	
		//updating blocks' "previous" inputs
		//(current input on step [k] equals previous input on step [k + 1])
		reg_prev = fb_regulator.e;
		mot_prev = fb_regulator.u;
	}

	//updating state
	count++;
}

void _EXIT ProgramExit(void)
{

}

