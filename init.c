#include "init.h"
#include <signal.h>
#include <stdio.h>
#include "externs.h"
#include <string.h>

void sigint_handler(int signo);

void setup(void)
{
	signal(SIGINT,sigint_handler);
	signal(SIGQUIT,SIG_IGN);
}

void sigint_handler(int signo)
{
	printf("\n[MiniShell]$ ");
	fflush(stdout);
}

void init(void)
{
	memset(cmd,0,sizeof(cmd));
	memset(&cmdline,0,sizeof(cmdline));
	lineptr = cmdline;
	avptr = avline;
}
