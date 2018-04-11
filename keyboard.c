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
#include "emp_type.h"
#include "keyboard.h"
#include "tm4c123gh6pm.h"
#include "glob_def.h"
#include "rtc.h"
#include "tmodel.h"
/*****************************    Defines    ********************************/
#define ast 0x41
#define has 0x11
#define zer 0x21
#define one 0x46
#define two 0x26
#define thr 0x16
#define fou 0x44
#define fiv 0x24
#define six 0x14
#define sev 0x42
#define eig 0x22
#define nin 0x12

/*****************************   Constants   ********************************/

/*****************************   Variables   ********************************/

/*****************************   Functions   *********************************
 *   Function : See General module specification (general.h-file).
 *****************************************************************************/
void keyboard_init()
{
#ifndef E_PORTA
#define E_PORTA
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0; // Clock gate port A
#endif

#ifndef E_PORTE
#define E_PORTE
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4; // Clock gate port E
#endif

    GPIO_PORTA_DIR_R |= 0x1C;               // Set A pins as output
    GPIO_PORTE_DIR_R &= 0x00;               // Set E pins as input
    GPIO_PORTA_DEN_R |= 0x1C;               // Enable digital function A2-4
    GPIO_PORTE_DEN_R |= 0x0F;               // Enable digital function E0-3
}

INT8U kp_scan(void)
{
    INT8U iter = 2, imask[3] = { 0x10, 0x20, 0x40 };
    INT8U mask[3] = { 0x04, 0x08, 0x10 };
    INT8U answer, data;
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
    }
    while (iter--);
    return answer;
}

void keyboard_read_task(INT8U my_id, INT8U my_state, INT8U event, INT8U data)
/*****************************************************************************
 *   Input    :
 *   Output   :
 *   Function : Task to read keyboard in put into queue.
 ******************************************************************************/
{
    static INT8U s_kp_value = 0, rep = 0, count = 0;
    INT8U kp_value = 0, ch;
    kp_value = kp_scan();
    if (rep)
    {
        if (kp_value == s_kp_value)
        {
            count++;
        }
        if (++rep == 4)
        {
            rep = 0;
            if (count >= 2)
            {
                switch (s_kp_value)
                {
                case ast:
                    ch = '*';
                    break;
                case has:
                    ch = '#';
                    break;
                case zer:
                    ch = '0';
                    break;
                case one:
                    ch = '1';
                    break;
                case two:
                    ch = '2';
                    break;
                case thr:
                    ch = '3';
                    break;
                case fou:
                    ch = '4';
                    break;
                case fiv:
                    ch = '5';
                    break;
                case six:
                    ch = '6';
                    break;
                case sev:
                    ch = '7';
                    break;
                case eig:
                    ch = '8';
                    break;
                case nin:
                    ch = '9';
                    break;
                default:
                    break;
                }
                put_queue(Q_KEYBOARD, ch, WAIT_FOREVER);
                signal(SEM_KEY_RECEIVED);
            }

        }
    }
    if ((kp_value) && !(rep))
    {
        rep++;
        count = 0;
        s_kp_value = kp_value;
    }

}

INT8U inbuff[2];

void keyboard_update_task(INT8U my_id, INT8U my_state, INT8U event, INT8U data)
/*****************************************************************************
 *   Input    :
 *   Output   :
 *   Function : Task to update RTC clock from keyboard input queues.
 ******************************************************************************/
{

    static INT8U state = STATE_IDLE;
    static INT8U read_count = 0;

    if (wait_sem(SEM_KEY_RECEIVED, WAIT_FOREVER))
    {
        INT8U ch;
        if (get_queue(Q_KEYBOARD, &ch, WAIT_FOREVER))
        {
            if (ch == '*' && state == STATE_IDLE)
            {
                state = STATE_READING;
                wait_sem(SEM_KEY_RTC_STOP, WAIT_FOREVER);
            }

            if (ch != '#' && state == STATE_READING && read_count < 7)
            {
                read_count++;

                switch (read_count)
                {
                case 1:
                    inbuff[0] = ch;
                    break;
                case 2:
                    inbuff[1] = ch;
                    set_hour((inbuff[0] - '0') * 10 + inbuff[1] - '0');
                    signal( SEM_RTC_UPDATED);
                    break;
                case 3:
                    inbuff[0] = ch;
                    break;
                case 4:
                    inbuff[1] = ch;
                    set_min((inbuff[0] - '0') * 10 + inbuff[1] - '0');
                    signal( SEM_RTC_UPDATED);
                    break;
                case 5:
                    inbuff[0] = ch;
                    break;
                case 6:
                    inbuff[1] = ch;
                    set_sec((inbuff[0] - '0') * 10 + inbuff[1] - '0');
                    signal( SEM_RTC_UPDATED);
                    break;
                default:
                    break;
                }

            }
            else
            {
                state = STATE_IDLE;
                read_count = 0;
                signal(SEM_KEY_RTC_STOP);
            }

        }
    }

}

/****************************** End Of Module *******************************/
