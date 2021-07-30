#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "tree.h"
#include "color.h"

int file_count = 0 ; //counts no of files
int dir_count = 0 ; //counts no of directories

//  -a = 0           All files are listed.
//  -f = 1           Print the full path prefix for each file.
//  -Q = 2           Quote filenames with double quotes.
void dir_a( char *dir_name, int no, int *arr, int mode ){
    DIR *dir;
    dir = opendir( dir_name ) ;
    if( dir == NULL )
        return ;

    if( no == 0 ){
        yellow();
        printf("%s \n", dir_name );
        reset();
    }

    struct dirent *de;
    int i, count = -2, j = 0 ;
    while( ( de = readdir(dir)) )
        count++ ;

    closedir(dir);
    dir = opendir( dir_name ) ;

    char fname[64], dname[64] ;
    strcpy( dname, dir_name );

    if( dir!=NULL ){
        while( ( de = readdir(dir)) ){
            if( de->d_type == DT_DIR ){
                if( strcmp( de->d_name, ".") == 0 || strcmp( de->d_name, "..") == 0 );
                else {
                    j++ ;
                    dir_count++ ;
                    for( i = 0 ; i < no ; i++ ){
                        if( *(arr+i) == 0 )
                            printf("│   ");
                        else
                            printf("    ");
                    }
                    if( j == count )
                        printf("└── ");
                    else
                        printf("├── ");
                    strcpy( dname, dir_name ) ;
                    strcat( dname, "/");
                    strcat( dname, de->d_name);

                    yellow();
                    if( mode == 0 )
                        printf("%s \n", de->d_name );
                    else if( mode == 1 )
                        printf("%s \n", dname );
                    else if( mode == 2 )
                        printf("\"%s\" \n", de->d_name );
                    reset();

                    if( j == count )
                        arr[no] = 1 ;
                    dir_a( dname, no +1, arr, mode );
                }
            }
            else{
                j++ ;
                file_count++ ;
                strcpy( fname, dir_name );
                strcat( fname, "/");
                strcat( fname, de->d_name );
                for( i = 0 ; i < no ; i++ ){
                    if( arr[i] == 0 )
                        printf("│   ");
                    else
                        printf("    ");
                }
                if( j == count )
                        printf("└── ");
                    else
                        printf("├── ");
                cyan();
                if( mode == 0 )
                    printf("%s \n", de->d_name );
                else if( mode == 1 )
                    printf("%s \n", fname );
                else if( mode == 2 )
                    printf("\"%s\" \n", de->d_name );

                reset();
            }
        }
        closedir(dir);
    }
    arr[no] = 0;
    if( no == 0 )
        printf("\n%d directories, %d files \n", dir_count, file_count );
    return ;
}

//  -d           List directories only.
void dir_d( char *dir_name, int no, int *arr ){
    DIR *dir;
    dir = opendir( dir_name ) ;
    if( dir == NULL )
        return ;

    if( no == 0 ){
        yellow();
        printf("%s \n", dir_name );
        reset();
    }

    struct dirent *de;
    int i, count = -2, j = 0 ;
    while( ( de = readdir(dir)) )
        if( de->d_type == DT_DIR )
            count++ ;

    closedir(dir);
    dir = opendir( dir_name ) ;

    char fname[64], dname[64] ;
    strcpy( dname, dir_name );

    if( dir!=NULL ){
        while( ( de = readdir(dir)) ){
            if( de->d_type == DT_DIR ){
                if( strcmp( de->d_name, ".") == 0 || strcmp( de->d_name, "..") == 0 );
                else {
                    j++ ;
                    dir_count++ ;
                    for( i = 0 ; i < no ; i++ ){
                        if( *(arr+i) == 0 )
                            printf("│   ");
                        else
                            printf("    ");
                    }
                    if( j == count )
                        printf("└── ");
                    else
                        printf("├── ");
                    strcpy( dname, dir_name ) ;
                    strcat( dname, "/");
                    strcat( dname, de->d_name);

                    yellow();
                    printf("%s \n", de->d_name );
                    reset();

                    if( j == count )
                        arr[no] = 1 ;
                    dir_d( dname, no +1, arr );
                }
            }
        }
        closedir(dir);
    }
    arr[no] = 0;
    if( no == 0 )
        printf("\n%d directories \n", dir_count );
    return ;
}

// L level           Max display depth of the directory tree
void dir_L( char *dir_name, int no, int *arr, int level ){
    if( level < 1 )
        return ;
    DIR *dir;
    dir = opendir( dir_name ) ;
    if( dir == NULL )
        return ;

    if( no == 0 ){
        yellow();
        printf("%s \n", dir_name );
        reset();
    }

    struct dirent *de;
    int i, count = -2, j = 0 ;
    while( ( de = readdir(dir)) )
        count++;
    closedir(dir);
    dir = opendir( dir_name ) ;

    char fname[64], dname[64] ;
    strcpy( dname, dir_name );

    if( dir!=NULL ){
        while( ( de = readdir(dir)) ){
            if( de->d_type == DT_DIR ){
                if( strcmp( de->d_name, ".") == 0 || strcmp( de->d_name, "..") == 0 );
                else {
                    j++ ;
                    dir_count++ ;
                    for( i = 0 ; i < no ; i++ ){
                        if( *(arr+i) == 0 )
                            printf("│   ");
                        else
                            printf("    ");
                    }
                    if( j == count )
                        printf("└── ");
                    else
                        printf("├── ");
                    strcpy( dname, dir_name ) ;
                    strcat( dname, "/");
                    strcat( dname, de->d_name);

                    yellow();    
                    printf("%s \n", de->d_name );
                    reset();

                    if( j == count )
                        arr[no] = 1 ;
                    dir_L( dname, no +1, arr, level -1 );
                }
            }
            else{
                j++ ;
                file_count++ ;
                for( i = 0 ; i < no ; i++ ){
                    if( arr[i] == 0 )
                        printf("│   ");
                    else
                        printf("    ");
                }
                if( j == count )
                        printf("└── ");
                    else
                        printf("├── ");
                cyan();
                printf("%s \n", de->d_name );
                reset();
            }
        }
        closedir(dir);
    }
    arr[no] = 0;
    if( no == 0 )
        printf("\n%d directories, %d files \n", dir_count, file_count );
    return ;
}

//  -p = 0           Print the protections for each file.
//  -s = 1           Print the size in bytes of each file.
//  -D = 2           Print the date of last modification or (-c) status change.
void dir_p( char *dir_name, int no, int *arr, int mode ){
    DIR *dir;
    dir = opendir( dir_name ) ;
    if( dir == NULL )
        return ;

    if( no == 0 ){
        yellow();
        printf("%s \n", dir_name );
        reset();
    }

    struct dirent *de;
    int i, count = -2, j = 0 ;
    while( ( de = readdir(dir)) )
        count++ ;

    closedir(dir);
    dir = opendir( dir_name ) ;

    char fname[64], dname[64] ;
    strcpy( dname, dir_name );

    if( dir!=NULL ){
        while( ( de = readdir(dir)) ){
            if( de->d_type == DT_DIR ){
                if( strcmp( de->d_name, ".") == 0 || strcmp( de->d_name, "..") == 0 );
                else {
                    j++ ;
                    dir_count++ ;
                    for( i = 0 ; i < no ; i++ ){
                        if( *(arr+i) == 0 )
                            printf("│   ");
                        else
                            printf("    ");
                    }
                    if( j == count )
                        printf("└── ");
                    else
                        printf("├── ");
                    strcpy( dname, dir_name ) ;
                    strcat( dname, "/");
                    strcat( dname, de->d_name);

                    yellow();
                    printf("%s \n", de->d_name );
                    reset();

                    if( j == count )
                        arr[no] = 1 ;
                    dir_p( dname, no +1, arr, mode );
                }
            }
            else{
                j++ ;
                file_count++ ;
                strcpy( fname, dir_name );
                strcat( fname, "/");
                strcat( fname, de->d_name );
                for( i = 0 ; i < no ; i++ ){
                    if( arr[i] == 0 )
                        printf("│   ");
                    else
                        printf("    ");
                }
                if( j == count )
                        printf("└── ");
                    else
                        printf("├── ");
                cyan();
                printf("%s ", de->d_name );
                reset();
                if( mode == 0 )
                    file_permission( fname );
                else if( mode == 1 )
                    file_size( fname );
                else if( mode == 2 )
                    file_time( fname );
                printf("\n");
            }
        }
        closedir(dir);
    }
    arr[no] = 0;
    if( no == 0 )
        printf("\n%d directories, %d files \n", dir_count, file_count );
    return ;
}

//  -u           Displays file owner or UID number.
//  -g           Displays file group owner or GID number.
void dir_u( char *dir_name, int no, int *arr, int mode ){
    DIR *dir;
    dir = opendir( dir_name ) ;
    if( dir == NULL )
        return ;

    if( no == 0 ){
        yellow();
        printf("%s \n", dir_name );
        reset();
    }

    struct dirent *de;
    int i, count = -2, j = 0 ;
    while( ( de = readdir(dir)) )
        count++ ;

    closedir(dir);
    dir = opendir( dir_name ) ;

    char fname[64], dname[64] ;
    strcpy( dname, dir_name );

    if( dir!=NULL ){
        while( ( de = readdir(dir)) ){
            if( de->d_type == DT_DIR ){
                if( strcmp( de->d_name, ".") == 0 || strcmp( de->d_name, "..") == 0 );
                else {
                    j++ ;
                    dir_count++ ;
                    for( i = 0 ; i < no ; i++ ){
                        if( *(arr+i) == 0 )
                            printf("│   ");
                        else
                            printf("    ");
                    }
                    if( j == count )
                        printf("└── ");
                    else
                        printf("├── ");
                    strcpy( dname, dir_name ) ;
                    strcat( dname, "/");
                    strcat( dname, de->d_name);

                    yellow();
                    printf("%s \n", de->d_name );
                    reset();

                    if( j == count )
                        arr[no] = 1 ;
                    dir_u( dname, no +1, arr, mode );
                }
            }
            else{
                j++ ;
                file_count++ ;
                for( i = 0 ; i < no ; i++ ){
                    if( arr[i] == 0 )
                        printf("│   ");
                    else
                        printf("    ");
                }
                if( j == count )
                        printf("└── ");
                    else
                        printf("├── ");
                cyan();
                printf("%s ", de->d_name );
                reset();
                if( mode == 0 )
                    uid_num();
                else if( mode == 1 )
                    gid_num();
                printf("\n");
            }
        }
        closedir(dir);
    }
    arr[no] = 0;
    if( no == 0 )
        printf("\n%d directories, %d files \n", dir_count, file_count );
    return ;
}

// i           Indentation lines will not be printed
void dir_i( char *dir_name, int no ){
    DIR *dir;
    dir = opendir( dir_name ) ;
    if( dir == NULL )
        return ;

    if( no == 0 ){
        yellow();
        printf("%s \n", dir_name );
        reset();
    }

    struct dirent *de;
    char fname[64], dname[64] ;
    strcpy( dname, dir_name );

    if( dir!=NULL ){
        while( ( de = readdir(dir)) ){
            if( de->d_type == DT_DIR ){
                if( strcmp( de->d_name, ".") == 0 || strcmp( de->d_name, "..") == 0 );
                else {
                    dir_count++ ;
                    strcpy( dname, dir_name ) ;
                    strcat( dname, "/");
                    strcat( dname, de->d_name);

                    yellow();
                    printf("%s \n", de->d_name );
                    reset();
                    dir_i( dname, no +1 );
                }
            }
            else{
                file_count++ ;
                cyan();
                printf("%s \n", de->d_name );
                reset();
            }
        }
        closedir(dir);
    }
    if( no == 0 )
        printf("\n%d directories, %d files \n", dir_count, file_count );
    return ;
}

//Graphics S           will turn on ASCII line graphics
void dir_S( char *dir_name, int no ){
    DIR *dir;
    dir = opendir( dir_name ) ;
    if( dir == NULL )
        return ;

    if( no == 0 ){
        yellow();
        printf("%s \n", dir_name );
        reset();
    }

    struct dirent *de;
    char fname[64], dname[64] ;
    strcpy( dname, dir_name );
    int i ;

    if( dir!=NULL ){
        while( ( de = readdir(dir)) ){
            if( de->d_type == DT_DIR ){
                if( strcmp( de->d_name, ".") == 0 || strcmp( de->d_name, "..") == 0 );
                else {
                    dir_count++ ;
                    for( i = 0 ; i < no ; i++ )
                        printf("    ");

                    strcpy( dname, dir_name ) ;
                    strcat( dname, "/");
                    strcat( dname, de->d_name);

                    yellow();
                    printf("%s \n", de->d_name );
                    reset();
                    dir_S( dname, no +1 );
                }
            }
            else{
                file_count++ ;
                for( i = 0 ; i < no ; i++ )
                    printf("    ");
                cyan();    
                printf("%s \n", de->d_name );
                reset();
            }
        }
        closedir(dir);
    }
    if( no == 0 )
        printf("\n%d directories, %d files \n", dir_count, file_count );
    return ;
}

// n           Turn colorization off always(without color)
void dir_n( char *dir_name, int no, int *arr ){
    DIR *dir;
    dir = opendir( dir_name ) ;
    if( dir == NULL )
        return ;
    if( no == 0 ){
        printf("%s \n", dir_name );
    }

    struct dirent *de;
    int i, count = -2, j = 0 ;
    while( ( de = readdir(dir)) )
        count++ ;

    closedir(dir);
    dir = opendir( dir_name ) ;

    char fname[64], dname[64] ;
    strcpy( dname, dir_name );

    if( dir!=NULL ){
        while( ( de = readdir(dir)) ){
            if( de->d_type == DT_DIR ){
                if( strcmp( de->d_name, ".") == 0 || strcmp( de->d_name, "..") == 0 );
                else {
                    j++ ;
                    dir_count++ ;
                    for( i = 0 ; i < no ; i++ ){
                        if( arr[i] == 0 )
                            printf("│   ");
                        else
                            printf("    ");
                    }
                    if( j == count )
                        printf("└── ");
                    else
                        printf("├── ");
                    strcpy( dname, dir_name ) ;
                    strcat( dname, "/");
                    strcat( dname, de->d_name);
    
                    printf("%s \n", de->d_name );
                    if( j == count )
                        arr[no] = 1 ;
                    dir_n( dname, no +1, arr );
                }
            }
            else{
                j++ ;
                file_count++ ;
                for( i = 0 ; i < no ; i++ ){
                    if( arr[i] == 0 )
                        printf("│   ");
                    else
                        printf("    ");
                }
                if( j == count )
                        printf("└── ");
                    else
                        printf("├── ");
                
                printf("%s \n", de->d_name );
                reset();
            }
        }
        closedir(dir);
    }
    arr[no] = 0;
    if( no == 0 )
        printf("\n%d directories, %d files \n", dir_count, file_count );
    return ;
}
//X           To display the directory in XML format
void dir_X( char *dir_name, int no ){
    DIR *dir;
    dir = opendir( dir_name ) ;
    if( dir == NULL )
        return ;

    if( no == 0 ){
        printf("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
        printf("<tree>\n");
        printf("    <directory name= \"%s\" > \n", dir_name);
    }

    struct dirent *de;
    char fname[64], dname[64] ;
    strcpy( dname, dir_name );
    int i ;

    if( dir!=NULL ){
        while( ( de = readdir(dir)) ){
            if( de->d_type == DT_DIR ){
                if( strcmp( de->d_name, ".") == 0 || strcmp( de->d_name, "..") == 0 );
                else {
                    dir_count++ ;
                    for( i = -1 ; i <= no ; i++ )
                        printf("    ");

                    strcpy( dname, dir_name ) ;
                    strcat( dname, "/");
                    strcat( dname, de->d_name);

                    printf("<directory name= \"%s\" > \n", de->d_name );
                    dir_X( dname, no +1 );
                    for( i = -1 ; i <= no ; i++ )
                        printf("    ");
                    printf("</directory> \n");
                }
            }
            else{
                file_count++ ;
                for( i = -1 ; i <= no ; i++ )
                    printf("    ");
                printf("<file name= \"%s\" ></file> \n", de->d_name );
            }
        }
        closedir(dir);
    }
    if( no == 0 ){
        printf("    </directory> \n");
        printf("    <report> \n");
        printf("        <directories> %d </directories> \n", dir_count );
        printf("        <files> %d </files> \n", file_count );
        printf("    </report> \n");
        printf("</tree> \n");
    }
    return ;
}
//J           To display the directory in JSON format(last file ends with a ,)
void dir_J( char *dir_name, int no ){
    DIR *dir;
    dir = opendir( dir_name ) ;
    if( dir == NULL )
        return ;

    if( no == 0 ){
        if( strcmp( dir_name, ".") == 0 )
            printf("[{\"type\":\"directory\",\"name\": \".\",\"contents\":[ \n");
        else
            printf("[ \n    {\"type\":\"directory\",\"name\": \"%s\",\"contents\":[ \n", dir_name );
    }

    struct dirent *de ;
    int i, count = -2, j = 0 ;
    while( ( de = readdir(dir)) )
        count++ ;

    closedir(dir);
    dir = opendir( dir_name ) ;
        
    char fname[64], dname[64] ;
    strcpy( dname, dir_name );

    if( dir!=NULL ){
        while( ( de = readdir(dir)) ){
            if( de->d_type == DT_DIR ){
                if( strcmp( de->d_name, ".") == 0 || strcmp( de->d_name, "..") == 0 );
                else {
                    j++ ;
                    dir_count++ ;
                    for( i = -1 ; i <= no ; i++ )
                        printf("    ");

                    printf("{\"type\":\"directory\",\"name\": \"%s\",\"contents\":[ \n", de->d_name );
                    strcpy( dname, dir_name ) ;
                    strcat( dname, "/");
                    strcat( dname, de->d_name);

                    dir_J( dname, no +1 );
                    for( i = -1 ; i <= no ; i++ )
                        printf("    ");
                    if( j == count )
                        printf("]} \n");
                    else
                        printf("]}, \n");
                }
            }
            else{
                j++ ;
                file_count++ ;
                for( i = -1 ; i <= no ; i++ )
                    printf("    ");
                printf("{\"type\":\"file\",\"name\":\"%s\"}", de->d_name );
                if( j == count )
                    printf(" \n");
                else
                    printf(", \n");
            }
        }
        closedir(dir);
    }
    if( no == 0 ){
        printf("    ]}, \n");
        printf("    {\"type\":\"report\",\"directories\": %d,\"files\": %d} \n", dir_count, file_count );
        printf("] \n");
    }
    return ;
}

// P = 0           Lists only those files that match the pattern    
// I = 1           Does'nt list files that match the pattern
void dir_P( char *dir_name, int no, int *arr, int mode, char *patt ){
    DIR *dir;
    dir = opendir( dir_name ) ;
    if( dir == NULL )
        return ;

    if( no == 0 ){
        yellow();
        printf("%s \n", dir_name );
        reset();
    }

    struct dirent *de;
    int i, count = -2, j = 0 ;
    while( ( de = readdir(dir)) )
        count++ ;

    closedir(dir);
    dir = opendir( dir_name ) ;

    char fname[64], dname[64] ;
    strcpy( dname, dir_name );

    if( dir!=NULL ){
        while( ( de = readdir(dir)) ){
            if( de->d_type == DT_DIR ){
                if( strcmp( de->d_name, ".") == 0 || strcmp( de->d_name, "..") == 0 );
                else {
                    j++ ;
                    dir_count++ ;
                    for( i = 0 ; i < no ; i++ ){
                        if( *(arr+i) == 0 )
                            printf("│   ");
                        else
                            printf("    ");
                    }
                    if( j == count )
                        printf("└── ");
                    else
                        printf("├── ");
                    strcpy( dname, dir_name ) ;
                    strcat( dname, "/");
                    strcat( dname, de->d_name);

                    yellow();
                    printf("%s \n", de->d_name );
                    reset();

                    if( j == count )
                        arr[no] = 1 ;
                    dir_P( dname, no +1, arr, mode, patt );
                }
            }
            else{
                j++ ;
                if( ( mode == 0 && str_str( de->d_name, patt ) != -1 ) || ( mode == 1 && str_str( de->d_name, patt ) == -1 ) ){
                    file_count++ ;
                    for( i = 0 ; i < no ; i++ ){
                        if( arr[i] == 0 )
                            printf("│   ");
                        else
                            printf("    ");
                    }
                    if( j == count )
                        printf("└── ");
                    else
                        printf("├── ");
                    cyan();
                    printf("%s \n", de->d_name );
                    reset();
                }
            }
        }
        closedir(dir);
    }
    arr[no] = 0;
    if( no == 0 )
        printf("\n%d directories, %d files \n", dir_count, file_count );
    return ;
}

//--help           Prints help

void help(){
    cyan();
    printf("usage : ./tree [option] folder name \n");
    printf(" ------- Listing options ------- \n");
    yellow();
    printf("-a            All files are listed. \n");
    printf("-d            List directories only. \n");
    printf("-f            Print the full path prefix for each file. \n");
    printf("-L level      Descend only level directories deep. \n");
    printf("-P pattern    List only those files that match the pattern given. \n");
    printf("-I pattern    Do not list files that match the given pattern. \n");
    cyan();
    printf(" ------- File options ------- \n");
    yellow();
    printf("-Q            Quote filenames with double quotes. \n");
    printf("-p            Print the protections for each file. \n");
    printf("-u            Displays file owner or UID number. \n");
    printf("-g            Displays file group owner or GID number. \n");
    printf("-s            Print the size in bytes of each file. \n");
    printf("-D            Print the date of last modification or (-c) status change. \n");
    cyan();
    printf("------- Graphics options ------- \n");
    yellow();
    printf("-i            Don't print indentation lines. \n");
    printf("-S            Print with CP437 (console) graphics indentation lines. \n");
    printf("-n            Turn colorization off always (-C overrides). \n");
    cyan();
    printf("------- XML/HTML options ------- \n");
    yellow();
    printf("-X            Prints out an XML representation of the tree. \n");
    printf("-J            Prints out an JSON representation of the tree. \n");
    cyan();
    printf("------- Miscellaneous options ------- \n");
    yellow();
    printf("--version     Print version and exit. \n");
    printf("--help        Print usage and this help message and exit. \n");
    return;
}

//--version           To get version   
void version(){
    cyan();
    printf("tree v1.4.6 (c) 2001 by Tejal Khairnar, MIS : 111903157, DSA Mini Project(4th Sem). \n");
    return;
}