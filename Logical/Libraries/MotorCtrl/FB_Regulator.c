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
	inst->u += (inst->k_p * inst->e <= inst->max_abs_value ? inst->k_p * inst->e : inst->max_abs_value) + 
		inst->k_i * inst->dt * inst->e_prev - 
		(inst->k_p * inst->e_prev <= inst->max_abs_value ? inst->k_p * inst->e_prev : inst->max_abs_value);
	
	if (inst->u > inst->max_abs_value)
		inst->u = inst->max_abs_value;
}