
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

void _INIT ProgramInit(void)
{	
	//state variables
	enable = count = 0;
	
	//setting
	speed = 60;
	
	//regulator
	regulators[0].integrator.dt = 0.002;
	regulators[0].k_p = 0.0064;
	regulators[0].k_i = 0.16;
	regulators[0].max_abs_value = 24;
	
	//1st motor
	motors[0].integrator.dt = motors[0].integrator_phi.dt = regulators[0].integrator.dt;
	motors[0].Tm = regulators[0].k_p / regulators[0].k_i;
	motors[0].ke = 3 * motors[0].integrator.dt * regulators[0].k_i;
	motors[0].enable_reg = 1;
	
	//2nd motor
	motors[1].integrator.dt = motors[1].integrator_phi.dt = motors[0].integrator.dt;
	motors[1].Tm = motors[0].Tm;
	motors[1].ke = motors[0].ke;
	motors[1].enable_reg = 0;
	
	//integrators' structure
	motors[0].integrator.direct = motors[0].integrator_phi.direct = regulators[0].integrator.direct = 
		motors[1].integrator.direct = motors[1].integrator_phi.direct = 1;
}

void _CYCLIC ProgramCyclic(void)
{
	//switching system state
	if (count % 100 == 0)
		enable = !enable;
	
	//switching input
	if (enable)
		speed = 60;
	else
		speed = 0;
	
	//updating system states
	int i;
	for (i = 0; i < 2; i++)
	{
		if (motors[i].enable_reg)
		{
			//motor with regulator
			regulators[i].e = speed - motors[i].w;
			regulators[i].e_prev = reg_prevs[i];
			FB_Regulator(&regulators[i]);
			motors[i].u = motors[i].integrator.direct ? mot_prevs[i] : regulators[i].u;
			FB_Motor(&motors[i]);
		
			reg_prevs[i] = regulators[i].e;  //updating previous inputs
			mot_prevs[i] = regulators[i].u;
		}
		else
		{
			//motor without regulator
			motors[i].u = motors[i].integrator.direct ? mot_prevs[i] : speed * motors[i].ke;
			FB_Motor(&motors[i]);
			
			mot_prevs[i] = speed * motors[i].ke;  //updating previous inputs
		}
	}

	//updating state
	count++;
}

void _EXIT ProgramExit(void)
{

}

