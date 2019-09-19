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
void FB_Motor(struct FB_Motor* inst)
{
	inst->w = inst->w * inst->Tm / (inst->Tm + inst->dt) + 
		inst->u * inst->dt / (inst->ke * (inst->Tm + inst->dt));
	
	inst->integrator.in = inst->w;
	FB_Integrator(&inst->integrator);
	inst->phi = inst->integrator.out;
}