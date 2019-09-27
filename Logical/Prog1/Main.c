
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

void _INIT ProgramInit(void)
{	
	//state variables
	enable = count = 0;
	
	//setting
	speed = 0;
	
	//regulator
	fb_regulator.k_p = 0.0064;
	fb_regulator.k_i = 0.16;
	fb_regulator.max_abs_value = 24;
	
	//1st motor
	fb_motor.dt = fb_regulator.dt = 0.002;
	fb_motor.Tm = fb_regulator.k_p / fb_regulator.k_i;
	fb_motor.ke = 3 * fb_motor.dt * fb_regulator.k_i;
	fb_motor.direct = fb_regulator.direct = 1;  //specifying motor's & regulator's structure
	
	//2nd motor
	fb_motor2.dt = fb_motor.dt;
	fb_motor2.Tm = fb_motor.Tm;
	fb_motor2.ke = fb_motor.ke;
	fb_motor2.direct = fb_motor.direct;
	
	fb_motor.integrator.dt = fb_regulator.integrator.dt = 0.002;
	fb_motor2.integrator.dt = fb_motor.integrator.dt;
	fb_motor.integrator.direct = fb_regulator.integrator.direct = fb_motor2.integrator.direct = 1;
}

void _CYCLIC ProgramCyclic(void)
{
	//delaying enabling
	if (count >= 25)
		enable = 1;
	
	if (enable)
	{
		//step function (5 secs period)
		if (count % 50 == 0)
			speed = speed == 0 ? 60 : 0;
		
		//motor without regulator
		fb_motor2.u = fb_motor2.direct ? mot2_prev : speed - fb_motor2.w;
		FB_Motor(&fb_motor2);
		
		mot2_prev = speed - fb_motor2.w;  //updating previous inputs
		
		//motor with regulator
		fb_regulator.e = speed - fb_motor.w;
		fb_regulator.e_prev = reg_prev;
		FB_Regulator(&fb_regulator);
		fb_motor.u = fb_motor.direct ? mot_prev : fb_regulator.u;
		FB_Motor(&fb_motor);
		
		reg_prev = fb_regulator.e;  //updating previous inputs
		mot_prev = fb_regulator.u;
	}

	//updating state
	count++;
}

void _EXIT ProgramExit(void)
{

}

