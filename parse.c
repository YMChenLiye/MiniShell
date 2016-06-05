#include "parse.h"
#include <stdio.h>
#include "init.h"
#include "externs.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


void get_command(int i);
int check(const char* str);
void getname(char* name);

//shell主循环
void shell_loop(void)
{
	while(1){
		printf("[MiniShell]$ ");
		fflush(stdout);
		init();
		if(read_command() == -1){
			break;
		}
		parse_command();
		execute_command();
	}
	printf("\nexit\n");
}

//读取命令
//成功返回0，失败或者读取到文件结束符(EOF)返回-1
int read_command(void)
{
	if(fgets(cmdline,MAXLINE,stdin) == NULL){
		return -1;
	}
	return 0;
}

//解析命令
//成功返回解析到的命令个数，失败返回-1
int parse_command(void)
{
	//cat < test.txt | grep -n public > test2.txt &
	//1、解析第一条简单命令
	get_command(0);
	//2、判断是否有输入重定向符
	if(check("<")){
		getname(infile);
	}
	//3、判断是否有管道
	int i;
	for(i = 1; i<PIPELINE;++i){
		if(check("|")){
			get_command(i);
		}else {
			break;
		}
	}
	//4、判断是否有输出重定向符
	if(check(">")){
		getname(outfile);
	}
	//5、判断是否后台作业
	if(check("&")){
		backgnd = 1;
	}
	//6、判断命令结束 '\n'
	if(check("\n")){
		cmd_count = i;
		return cmd_count;
	}else {
		fprintf(stderr,"Command line syntax error\n");
		return -1;
	}

	return 0;

}

//执行命令
//成功返回0，失败返回-1
int execute_command(void)
{
	/*
	pid_t pid = fork();
	if(pid == -1){
		ERR_EXIT("fork");
	}

	int ret;
	if(pid == 0){	//child
		ret = execvp(cmd.args[0],cmd.args);
		
	}

	wait(NULL);
	*/
	return 0;

}

//解析简单命令至cmd[i]
//提取cmdline中的命令参数到avline数组中，
//并且将COMMAND结构中的args[]中的每个指针指向这些字符串
void get_command(int i)
{
	int j = 0;
	int inword;
	while(*lineptr != '\0'){
		//去除空格
		while(*lineptr == ' ' || *lineptr == '\t'){
			*lineptr++;
		}
		cmd[i].args[j] = avptr;
		while(*lineptr != '\0' && *lineptr != ' ' && *lineptr != '\t'
				&& *lineptr != '>' && *lineptr != '<' && *lineptr != '|'
				&& *lineptr != '&' && *lineptr != '\n'){
			*avptr++ = *lineptr++;
			inword = 1;
		}
		*avptr++ = '\0';
		
		switch(*lineptr){
			case ' ':
			case '\t':
				inword = 0;
				j++;
				break;
			case '<':
			case '>':
			case '|':
			case '&':
			case '\n':
				if(inword == 0){
					cmd[i].args[j] = NULL;
				}
				return ;
			default:	//for '\0'
				return;
		}
	}

}
int check(const char* str)
{

}

void getname(char* name)
{

}
