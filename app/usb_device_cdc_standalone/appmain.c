/*
 * Copyright (c) 2009 Sung Ho Park
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <ubinos.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <main.h>

static void root_func(void *arg);

static void cli_help_hook_func();
static int cli_hook_func(char *str, int len, void *arg);
static int cli_cmd_utup(char *str, int len, void *arg);
static int cli_cmd_utdn(char *str, int len, void *arg);

extern void usb_init();

int appmain(int argc, char *argv[])
{
    int r;
    (void) r;

    r = task_create(NULL, root_func, NULL, task_getmiddlepriority(), 0, "root");
    ubi_assert(r == 0);

    ubik_comp_start();

    return 0;
}

static void root_func(void *arg)
{
    int r;
    (void) r;

    printf("\n\n\n");
    printf("================================================================================\n");
    printf("usb_device_cdc_standalone (build time: %s %s)\n", __TIME__, __DATE__);
    printf("================================================================================\n");
    printf("\n");

    r = cli_sethookfunc(cli_hook_func, NULL);
    ubi_assert(r == 0);

    r = cli_sethelphookfunc(cli_help_hook_func);
    ubi_assert(r == 0);

    r = cli_setprompt("usb_device_cdc_standalone> ");
    ubi_assert(r == 0);

    r = task_create(NULL, cli_main, NULL, task_getmiddlepriority(), 0, "cli_main");
    ubi_assert(r == 0);

    /* Enable Power Clock*/
    __HAL_RCC_PWR_CLK_ENABLE();
    
    /* enable USB power on Pwrctrl CR2 register */
    HAL_PWREx_EnableVddUSB();

    r = semb_create(&usbd_write_sem);
    ubi_assert(r == 0);
    r = semb_create(&usbd_read_sem);
    ubi_assert(r == 0);

    usbd_write_need_restart = 1;

    /* Init Device Library */
    USBD_Init(&USBD_Device, &VCP_Desc, 0);
    
    /* Add Supported Class */
    USBD_RegisterClass(&USBD_Device, USBD_CDC_CLASS);
    
    /* Add CDC Interface Class */
    USBD_CDC_RegisterInterface(&USBD_Device, &USBD_CDC_fops);
    
    /* Start Device Process */
    USBD_Start(&USBD_Device);

    sem_give(usbd_write_sem);
}

static int cli_hook_func(char *str, int len, void *arg)
{
    int r = -1;
    char *tmpstr;
    int tmplen;
    char *cmd = NULL;
    int cmdlen;

    tmpstr = str;
    tmplen = len;

    cmd = "utup";
    cmdlen = strlen(cmd);
    if (tmplen == cmdlen && strncmp(tmpstr, cmd, cmdlen) == 0)
    {
        tmpstr = &tmpstr[cmdlen];
        tmplen -= cmdlen;

        r = cli_cmd_utup(tmpstr, tmplen, arg);
    }

    cmd = "utdn";
    cmdlen = strlen(cmd);
    if (tmplen == cmdlen && strncmp(tmpstr, cmd, cmdlen) == 0)
    {
        tmpstr = &tmpstr[cmdlen];
        tmplen -= cmdlen;

        r = cli_cmd_utdn(tmpstr, tmplen, arg);
    }

    return r;
}

static void cli_help_hook_func()
{
    printf("utup                                    : usbd upload test\n");
    printf("utdn                                    : usbd download test\n");
}

#define UTUP_BUF_SIZE 1024
uint8_t utup_buf[UTUP_BUF_SIZE];

static int cli_cmd_utup(char *str, int len, void *arg)
{
    srand((unsigned int)time(NULL));
    
    printf("\n");

    for (int i = 0; i < UTUP_BUF_SIZE; i++)
    {
        utup_buf[i] = i % 10 + 'a';
    }
    utup_buf[UTUP_BUF_SIZE - 2] = '\n';
    utup_buf[UTUP_BUF_SIZE - 1] = '\r';

    do
    {
        sem_take_timedms(usbd_write_sem, 1000);
        if (cbuf_get_empty_len(usbd_write_cbuf) >= 1)
        {
            break;
        }
    } while (1);
    cbuf_write(usbd_write_cbuf, utup_buf, 1, NULL);
    if (usbd_write_need_restart == 1 && cbuf_get_len(usbd_write_cbuf) > 0)
    {
        usbd_write_need_restart = 0;
        usbd_write_trying_size = 1;
        cbuf_view(usbd_write_cbuf, UserTxBuffer, usbd_write_trying_size, &usbd_write_trying_size);
        USBD_CDC_SetTxBuffer(&USBD_Device, UserTxBuffer, usbd_write_trying_size);
        if(USBD_CDC_TransmitPacket(&USBD_Device) != USBD_OK)
        {
            usbd_write_need_restart = 1;
            usbd_write_trying_size = 0;
        }
    }

    printf("start\n");

    for (int i = 0; i < 1000; )
    {
        do
        {
            sem_take_timedms(usbd_write_sem, 1000);
            if (cbuf_get_empty_len(usbd_write_cbuf) >= (UTUP_BUF_SIZE))
            {
                break;
            }
        } while (1);
        utup_buf[0] = '0' + (i % 10) ;
        cbuf_write(usbd_write_cbuf, utup_buf, UTUP_BUF_SIZE, NULL);
        if (usbd_write_need_restart == 1 && cbuf_get_len(usbd_write_cbuf) > 0)
        {
            usbd_write_need_restart = 0;
            usbd_write_trying_size = min(cbuf_get_len(usbd_write_cbuf), APP_TX_DATA_SIZE) - (rand() % 10);
            cbuf_view(usbd_write_cbuf, UserTxBuffer, usbd_write_trying_size, &usbd_write_trying_size);
            USBD_CDC_SetTxBuffer(&USBD_Device, UserTxBuffer, usbd_write_trying_size);
            if(USBD_CDC_TransmitPacket(&USBD_Device) != USBD_OK)
            {
                usbd_write_need_restart = 1;
                usbd_write_trying_size = 0;
            }
            else
            {
            }
        }
        i++;
        if (i % 100 == 0)
        {
            printf("%d\n", i);
        }
    }
    printf("ok\n");

    return 0;
}

static int cli_cmd_utdn(char *str, int len, void *arg)
{
    int count = 0;
    uint8_t data = 0;
    uint32_t read;
    ubi_err_t ubi_err;

    printf("\n");

    do
    {
        sem_take_timedms(usbd_read_sem, 1000);

        while (cbuf_get_len(usbd_read_cbuf) > 0)
        {
            ubi_err = cbuf_read(usbd_read_cbuf, &data, 1, &read);
            ubi_assert_ok(ubi_err);
            printf("%c", data);
            count ++;
            if (data == 'q')
            {
                break;
            }
        }
        if (data == 'q')
        {
            break;
        }
    } while(1);
    
    return 0;
}
