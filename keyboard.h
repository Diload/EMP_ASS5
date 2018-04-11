/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: keyboard.h
*
* PROJECT....: EMP_ASS5
*
* DESCRIPTION: Describe something.
*
* DEPENDENCIES: General.
*
* Change Log:
******************************************************************************
* Date    		Id    Change
* DD MMM, YYYY
* ----------------------------------------------------------------------------
* 11. apr. 2018	HLH   Module created.
*
*****************************************************************************/

#ifndef _KEYBOARD_H_
  #define _KEYBOARD_H_

/***************************** Include files ********************************/

/*****************************    Defines    ********************************/

/********************** External declaration of Variables *******************/

/*****************************   Constants   ********************************/

/*************************  Function interfaces *****************************/

void keyboard_init(void);

void keyboard_task(INT8U my_id, INT8U my_state, INT8U event, INT8U data);
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Task to be run.
*****************************************************************************/


/****************************** End Of Module *******************************/
#endif
