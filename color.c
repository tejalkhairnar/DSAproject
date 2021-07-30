#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include "color.h"

void black(){
    printf("\033[0;30m");
    return ;
}

void red(){
    printf("\033[1;31m");
    return ;
}

void green(){
    printf("\033[1;32m");
    return ;
}

void yellow(){
    printf("\033[1;33m");
    return ;
}

void blue(){
    printf("\033[1;34m");
    return ;
}

void purple(){
    printf("\033[1;35m");
    return ;
}

void cyan(){
    printf("\033[1;36m");
    return ;
}

void white(){
    printf("\033[1;37m");
    return ;
}

void reset(){
    printf("\033[0m");
    return ;
}

void file_size( char *fname ){
    struct stat fileStat;
    if(stat( fname, &fileStat) < 0)    
        return ;
    printf("[ ");
    purple();
    printf("%ld bytes", fileStat.st_size );
    reset();
    printf(" ]");
    return ;
}

void file_permission( char *fname ){
    struct stat fileStat;
    if(stat( fname, &fileStat) < 0)    
        return ;
    printf("[ ") ;
    purple();
    printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
    reset();
    printf(" ]");
    return ;
}

void file_time( char *fname ){
    struct stat fileStat;
    if(stat( fname, &fileStat) < 0)    
        return ;
    char time[50];
    strftime(time, 50,"%Y-%m-%d %H:%M:%S", localtime(&fileStat.st_mtime));
    printf("[ ");
    purple();
    printf ("%s", time);
    reset();
    printf(" ]");
    return ;
}

void uid_num(){
    printf("[ ");
    purple();
    printf("%d", getuid());
    reset();
    printf(" ]");
}

void gid_num(){
    printf("[ ");
    purple();
    printf("%d", getgid());
    reset();
    printf(" ]");
}

int str_str(char *str, char *ch){
    int i = 0 ;
	char *p = str, *q = ch;
	while( *p != '\0' && *q != '\0' ){
		if( *p == *q )
			q++ ;
		else
			q = ch ;
		p++ ;
		i++ ;
	}
	if( *q == '\0' )
		return i -strlen( ch ) ;
	else
		return -1 ;
}