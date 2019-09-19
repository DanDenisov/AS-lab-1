/* Automation Studio generated header file */
/* Do not edit ! */
/* MotorCtrl  */

#ifndef _MOTORCTRL_
#define _MOTORCTRL_
#ifdef __cplusplus
extern "C" 
{
#endif

#include <bur/plctypes.h>

#ifndef _BUR_PUBLIC
#define _BUR_PUBLIC
#endif
/* Datatypes and datatypes of function blocks */
typedef struct FB_Integrator
{
	/* VAR_INPUT (analog) */
	float in;
	/* VAR_OUTPUT (analog) */
	float out;
	/* VAR (analog) */
	float dt;
} FB_Integrator_typ;

typedef struct FB_Motor
{
	/* VAR_INPUT (analog) */
	float u;
	/* VAR_OUTPUT (analog) */
	float w;
	float phi;
	/* VAR (analog) */
	struct FB_Integrator integrator;
	float Tm;
	float ke;
	float dt;
} FB_Motor_typ;

typedef struct FB_Regulator
{
	/* VAR_INPUT (analog) */
	float e;
	float e_prev;
	/* VAR_OUTPUT (analog) */
	float u;
	/* VAR (analog) */
	unsigned char u_raw;
	unsigned char count;
	float k_p;
	float k_i;
	struct FB_Integrator integrator;
	float iyOld;
	float max_abs_value;
	float dt;
} FB_Regulator_typ;



/* Prototyping of functions and function blocks */
_BUR_PUBLIC void FB_Integrator(struct FB_Integrator* inst);
_BUR_PUBLIC void FB_Motor(struct FB_Motor* inst);
_BUR_PUBLIC void FB_Regulator(struct FB_Regulator* inst);


#ifdef __cplusplus
};
#endif
#endif /* _MOTORCTRL_ */

