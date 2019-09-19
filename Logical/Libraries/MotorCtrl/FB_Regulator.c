#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
#include "MotorCtrl.h"
#ifdef __cplusplus
	};
#endif
/* TODO: Add your comment here */
void FB_Regulator(struct FB_Regulator* inst)
{
	//direct circuit
	inst->u += (inst->k_p * inst->e <= inst->max_abs_value ? inst->k_p * inst->e : inst->max_abs_value) + 
		inst->k_i * inst->dt * inst->e_prev - 
		(inst->k_p * inst->e_prev <= inst->max_abs_value ? inst->k_p * inst->e_prev : inst->max_abs_value);
	
	//feedback circuit
	/*if (inst->count == 0)
		inst->integrator.in = inst->e * inst->k_i;
	else
		inst->integrator.in = inst->e * inst->k_i + (inst->u - inst->u_raw) / inst->dt;
		
	FB_Integrator(&inst->integrator);
	inst->u_raw = (inst->k_p * inst->e <= inst->max_abs_value ? inst->k_p * inst->e : inst->max_abs_value) +
		inst->integrator.out;
	inst->u = inst->u_raw;*/
	
	//truncating output in case it exceeds max. voltage
	if (inst->u > inst->max_abs_value)
		inst->u = inst->max_abs_value;
}

