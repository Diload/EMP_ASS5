/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: keyboard.c
*
* PROJECT....: EMP_ASS5
*
* DESCRIPTION: See module specification file (.h-file).
*
* Change Log:
******************************************************************************
* Date			Id	  Change
* DD MMM, YYYY
* ----------------------------------------------------------------------------
* 11. apr. 2018	HLH   Module created.
*
*****************************************************************************/

/***************************** Include files ********************************/
#include <stdint.h>
#include "keyboard.h"
#include "tm4c123gh6pm.h"
#include "emp_type.h"
#include "glob_def.h"
#include "tmodel.h"
/*****************************    Defines    ********************************/

/*****************************   Constants   ********************************/

/*****************************   Variables   ********************************/

/*****************************   Functions   *********************************
*   Function : See General module specification (general.h-file).
*****************************************************************************/
void keyboard_init()
{
    #ifndef E_PORTA
    #define E_PORTA
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA;                 // Enable clock for Port A
    #endif

    #ifndef E_PORTE
    #define E_PORTE
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA;                 // Enable clock for Port E
    #endif

    GPIO_PORTA_DIR_R |= 0x1C;
    GPIO_PORTE_DIR_R &= ~(0x0F);
    GPIO_PORTA_DEN_R |= 0x1C;               // Enable digital function A2-4
    GPIO_PORTE_DEN_R |= 0x0F;               // Enable digital function E0-3



}

uint8_t kp_scan(void)
{
    uint8_t iter = 2, imask[3] = { 0x10, 0x20, 0x40 };
    uint8_t mask[3] = { 0x04, 0x08, 0x10 };
    uint8_t answer, data;
    do
    {
        GPIO_PORTA_DATA_R |= mask[iter];
        data = GPIO_PORTE_DATA_R;
        if (data)
        {
            answer += imask[iter];
            answer += data;
            iter = 0;
        }
    } while (iter--);
    return answer;
}


void keyboard_read_task(INT8U my_id, INT8U my_state, INT8U event, INT8U data)
/*****************************************************************************
*   Input    :
*   Output   :
*   Function : Task to be run.
******************************************************************************/
{


}

/****************************** End Of Module *******************************/
