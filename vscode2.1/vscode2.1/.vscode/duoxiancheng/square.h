#include <stdio.h>
#include <time.h>
#include <memory.h>
#include <string.h>
#include <thread>
#include <algorithm>

#define MAXN 10
#define MAXNN 100

#ifdef WIN32
#include <conio.h>
#endif

typedef struct squarelist {
    int     i[MAXNN];
    int     time;                                          
    int     resultCount, partResultCount, totalCount;       
    struct squarelist  *next;
} SQUARENODE;

typedef struct square
{
    int working;                    
    int scope_start, scope_end;     
    int i[MAXNN];                   
    int remain[MAXNN];             
    int totalCount, resultCount, partResultCount;
    int t_start, time;
    int stdsum;
    int rsum[MAXN], csum[MAXN];           // 0~N-1
    SQUARENODE  head, *tail;
    int threshold_max[MAXN], threshold_min[MAXN];
} SQUARE;

void    beginWorker(SQUARE *ps);
int exam(SQUARE *ps);
void msquare(SQUARE *ps, int no);

int     exam(SQUARE *ps);
void    msquare( SQUARE *ps, int no);
void    fileWrite( char *filename, SQUARE *ps, int count) ;
void    initSquare( SQUARE  *ps, int start, int end);

SQUARENODE *sl_append(SQUARE *ps); 
void    sl_free( SQUARENODE *head);
void    calcThreshold( SQUARE *ps );