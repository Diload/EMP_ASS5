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

#define STATE_IDLE      1
#define STATE_READING   2

/********************** External declaration of Variables *******************/

/*****************************   Constants   ********************************/

/*************************  Function interfaces *****************************/

void keyboard_init(void);

void keyboard_read_task(INT8U my_id, INT8U my_state, INT8U event, INT8U data);
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Task to read keyboard in put into queue.
*****************************************************************************/

void keyboard_update_task(INT8U my_id, INT8U my_state, INT8U event, INT8U data);
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Task to update RTC clock from keyboard input queues.
*****************************************************************************/


/****************************** End Of Module *******************************/
#endif
