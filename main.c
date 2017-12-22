#include<stdio.h>
#include<stdlib.h>
#include "src.c"


#define DONT_DEBUG




void ReachDestinationAvoidingNode(unsigned char Xd,unsigned char Yd,unsigned char Xn,unsigned char Yn)
{

				int di=Xd-1,dj=Yd-'A';

    int oi=Xn-1,oj=Yn-'A';

    Maze M=init_maze();

    Put_Obstacle_At(&M,oi,oj);

    Path P = GetPath(M,di,dj);

    int i=0;

    while(i+1<MAX_PLEN)
    {
 						printf("%d ",P.arr[i]);
				
						if(P.arr[i+1]==-1) break;
						
						i++;
				}


				printf("\n");
 }




int main()
{
       ReachDestinationAvoidingNode(5,'D',6,'D');

	   			ReachDestinationAvoidingNode(2,'F',2,'D');

	   			ReachDestinationAvoidingNode(2,'A',2,'C');

}

