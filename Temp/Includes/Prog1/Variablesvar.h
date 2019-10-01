/* Automation Studio generated header file */
/* Do not edit ! */

#ifndef _BUR_1569962960_1_
#define _BUR_1569962960_1_

#include <bur/plctypes.h>

/* Constants */
#ifdef _REPLACE_CONST
#else
#endif


/* Variables */
_BUR_LOCAL float mot_prevs[2];
_BUR_LOCAL float reg_prevs[2];
_BUR_LOCAL struct FB_Regulator regulators[2];
_BUR_LOCAL struct FB_Motor motors[2];
_BUR_LOCAL plcbit enable;
_BUR_LOCAL float speed;





__asm__(".section \".plc\"");

/* Used IEC files */
__asm__(".ascii \"iecfile \\\"Logical/Prog1/Variables.var\\\" scope \\\"local\\\"\\n\"");
__asm__(".ascii \"iecfile \\\"Logical/Libraries/MotorCtrl/MotorCtrl.fun\\\" scope \\\"global\\\"\\n\"");

/* Exported library functions and function blocks */

__asm__(".previous");


#endif /* _BUR_1569962960_1_ */

