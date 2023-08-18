/*
 * Copyright (c) 2009 Sung Ho Park
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <ubinos.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <main.h>

static void root_func(void *arg);

static void cli_help_hook_func();
static int cli_hook_func(char *str, int len, void *arg);
static int my_command(char *str, int len, void *arg);

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
    printf("command line interface tester (build time: %s %s)\n", __TIME__, __DATE__);
    printf("================================================================================\n");
    printf("\n");

    r = cli_sethookfunc(cli_hook_func, NULL);
    ubi_assert(r == 0);

    r = cli_sethelphookfunc(cli_help_hook_func);
    ubi_assert(r == 0);

    r = cli_setprompt("cli_tester> ");
    ubi_assert(r == 0);

    r = task_create(NULL, cli_main, NULL, task_getmiddlepriority(), 0, "cli_main");
    ubi_assert(r == 0);

  /* Enable Power Clock*/
  __HAL_RCC_PWR_CLK_ENABLE();
  
  /* enable USB power on Pwrctrl CR2 register */
  HAL_PWREx_EnableVddUSB();

  /* Init Device Library */
  USBD_Init(&USBD_Device, &VCP_Desc, 0);
  
  /* Add Supported Class */
  USBD_RegisterClass(&USBD_Device, USBD_CDC_CLASS);
  
  /* Add CDC Interface Class */
  USBD_CDC_RegisterInterface(&USBD_Device, &USBD_CDC_fops);
  
  /* Start Device Process */
  USBD_Start(&USBD_Device);

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

    cmd = "mc";
    cmdlen = strlen(cmd);
    if (tmplen == cmdlen && strncmp(tmpstr, cmd, cmdlen) == 0)
    {
        tmpstr = &tmpstr[cmdlen];
        tmplen -= cmdlen;

        r = my_command(tmpstr, tmplen, arg);
    }

    return r;
}

static void cli_help_hook_func()
{
    printf("mc                                      : my command\n");
}

static int my_command(char *str, int len, void *arg)
{
    printf("\n");
    printf("done\n");

    return 0;
}

