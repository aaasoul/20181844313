#include <stdio.h>
#define N   4  
#define MAX   (N*N) 
#define ROW_END  1 
#define COL_END  2  
#define LEFT_DOWN 3  
#define RIGHT_DOWN 4 
#define OTHER  0  

struct _ngg
{
 int num[MAX];  
 int val;   
 int count;   
};


void init(struct _ngg *pngg);

void fill(struct _ngg * pngg,int pos);

int getFlag(int pos);

int isFilled(struct _ngg * pngg,int pos,int i);

int sumRow(struct _ngg * pngg,int pos);

int sumCol(struct _ngg * pngg, int pos);

int sumLU_RD(struct _ngg * pngg);

int sumRU_LD(struct _ngg * pngg);

void prt(struct _ngg * pngg);
 

int main(void)
{

 struct _ngg ngg = {0};
 
 init(&ngg);
 printf("N = %d, MAX = %d, val = %d\n",N,MAX,ngg.val);
 
 fill(&ngg,0);
 return 0;
}

void init(struct _ngg *pngg)
{
 
 pngg->val = MAX * (MAX + 1) / 2 / N;
}

void fill(struct _ngg * pngg,int pos)
{
 
 int flag = getFlag(pos);  
 int i;
 
 for(i = 1; i <=MAX; i++)
 {
  //判断 i 在前面有没有填过，填过则填下一个数
  if(isFilled(pngg,pos,i))
  {
   continue;
  }
  //填入 i 到 pos 位置
  pngg->num[pos] = i;
  //根据 flag 分情况进行处理
  switch(flag)
  {
  //行结束
  case ROW_END:
   //如果行和相等则继续填下一个位置
   if(pngg->val == sumRow(pngg,pos))
   {
    fill(pngg,pos+1);
   }
   break;
  //列结束
  case COL_END:
   //如果列和相等则继续填下一个位置
   if(pngg->val == sumCol(pngg,pos))
   {
    fill(pngg,pos+1);
   }
   break;
  //左下角
  case LEFT_DOWN:
   //如果列和、右上-左下对角和相等则填下一个位置
   if(pngg->val == sumCol(pngg,pos) && 
    pngg->val == sumRU_LD(pngg))
   {
    fill(pngg,pos+1);
   }
   break;
  //右下角
  case RIGHT_DOWN:
   //如果行和、列和、左上-右下对角和相等则打印数组
   if(pngg->val == sumRow(pngg,pos) &&
    pngg->val == sumCol(pngg,pos) &&
    pngg->val == sumLU_RD(pngg) )
   {
    prt(pngg);
   }
   break;
  
  
  default:
   //其它情况填下一个位置
   fill(pngg,pos+1);
  }
 }
}

int getFlag(int pos)
{
 //如果到了行尾，但不是最后一个元素则为行结束
 if(0 == (pos + 1) % N && MAX - 1 != pos)
 {
  return ROW_END;
 }
 //如果到了列尾，但不是第 0 列，也不是最后一个元素，则为列结束
 if(pos > N * (N - 1) && MAX - 1 != pos)
 {
  return COL_END;
 }
 //如果是最后一行，并且是第 0 列，则为左下角
 if(pos == N * (N - 1))
 {
  return LEFT_DOWN;
 }
 //如果是最后一个元素，则是右下角
 if(MAX - 1 == pos)
 {
  return RIGHT_DOWN;
 }
 
 return OTHER;
}

int isFilled(struct _ngg * pngg,int pos,int i)
{
 int j;
 for(j = 0; j < pos;j++)
 {
  if(pngg->num[j] == i)
  {
   return 1;
  }
 }
 return 0;
}
//计算行和
int sumRow(struct _ngg * pngg,int pos)
{
 int i,sum = 0;
 //从第 pos 个元素往回加
 for(i = pos; i > pos - N; i--)
 {
  sum += pngg->num[i];
 }
 return sum;
}
//计算列和
int sumCol(struct _ngg * pngg, int pos)
{
 int i,sum = 0;
 //从第 pos 个元素往上加
 for(i = pos; i >= 0; i -= N)
 {
  sum += pngg->num[i];
 }
 return sum;
}
//计算右上-左下对角和
int sumRU_LD(struct _ngg * pngg)
{
 int i,sum = 0;
 //从第 N - 1 个元素开始每次跳过 N - 1 个元素累加
 for(i = N - 1; i < MAX -1; i += N - 1)
 {
  sum += pngg->num[i];
 }
 return sum;
}
//计算左上-右下对角和
int sumLU_RD(struct _ngg * pngg)
{
 int i,sum = 0;
 //从第 0 个元素开始每次跳过 N + 1个元素累加
 for(i = 0; i < MAX; i += N + 1)
 {
  sum += pngg->num[i];
 }
 return sum;
}
//打印数组
void prt(struct _ngg * pngg)
{
 int i;
 printf("-----------------------------------------%d\n",++pngg->count);
 for(i = 0; i < MAX; i++)
 {
  printf("\t%d",pngg->num[i]);
  if(0 == (i + 1) % N)
  {
   printf("\n");
  }
 }
}