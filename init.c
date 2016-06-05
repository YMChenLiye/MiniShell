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
	int i;
	for(i = 0; i<PIPELINE; ++i){
		cmd[i].infd = 0;
		cmd[i].outfd = 1;
	}
	memset(cmdline,0,sizeof(cmdline));
	memset(avline,0,sizeof(avline));
	lineptr = cmdline;
	avptr = avline;
	memset(infile,0,sizeof(infile));
	memset(outfile,0,sizeof(outfile));
	cmd_count = 0;
	backgnd = 0;
	append = 0;
	lastpid = 0;
	printf("[MiniShell]$ ");
	fflush(stdout);
}
