#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


//#define DEBUG

#define MAX_PLEN 49

#define Y 7



#define GREEN_HOME_i 6
#define GREEN_HOME_j 3


int dx[]={-1,1,0,0};
int dy[]={0,0,-1,1};

struct Pair
{
	int i,j;
};

struct Maze
{
    int arr[Y][Y];
};

struct Graph
{
    _Bool adjmat[MAX_PLEN][MAX_PLEN];
};

struct Path
{
	int arr[MAX_PLEN];
};

typedef struct Path Path;
typedef struct Graph Graph;
typedef struct Maze Maze;
typedef struct Pair Pair;

Path init_path()
{
	Path P;
	for(int i = 0; i < MAX_PLEN; i++)
		P.arr[i] = -1;

	return P;
}

Maze init_maze()
{
		int arr[Y][Y]={
						{9,1,1,1,1,1,3},{8,0,0,0,0,0,2},{8,0,0,0,0,0,2},{8,0,0,0,0,0,2},{8,0,0,0,0,0,2},{8,0,0,0,0,0,2},{12,4,4,4,4,4,6}
					};



		Maze m;

		memcpy(m.arr,arr,sizeof(arr));
		return m;
}


 _Bool open(int N,int i)
 {
			return !(N&&i);
 }

 _Bool isvalid(int i,int j)
 {
				return (i<Y && i>=0 && j>=0 && j<Y);
 }

int CellNo(int x, int y)
{
    return x*Y + y;
}


struct Graph buildGraph(struct Maze maze)
{
    struct Graph G;

				for(int i=0;i<MAX_PLEN;i++)
    	memset(G.adjmat[i],0,sizeof G.adjmat[i]);

	for(int i=0;i<Y;i++)
	{
		for(int j=0;j<Y;j++)
		{

			int cn=CellNo(i,j);
			int up=cn-Y;
			int down=cn+Y;
			int left=cn-1;
			int right=cn+1;
			int x=maze.arr[i][j];

			if(open(x,x&1))
				if(isvalid(i-1,j))
					G.adjmat[cn][up]=1;

			if(open(x,x&4))
				if(isvalid(i+1,j))
                    G.adjmat[cn][down]=1;

			if(open(x,x&8))
				if(isvalid(i,j-1))
					G.adjmat[cn][left]=1;

			if(open(x,x&2))
				if(isvalid(i,j+1))
					G.adjmat[cn][right]=1;


		}
	}

    return G;
}

struct Node
{
    int i,j;
    struct Node *next;
};

struct Queue
{
    struct Node *front, *rear;

    int Size;
};

typedef struct Node Node;
typedef struct Queue Queue;

Node* GetNode(int i,int j)
{
    Node *temp = (struct Node*)malloc(sizeof(struct Node));
    (*temp).i=i;
    (*temp).j=j;

    (*temp).next=NULL;
    return temp;
}

Queue *GetQueue()
{
    struct Queue *q = (struct Queue*)malloc(sizeof(struct Queue));

    q->front =NULL;
	
				q->rear = NULL;
			
				q->Size=0;

    return q;
}

void Enqueue(Queue *q, Node *tempNode)
{
    if (q->rear==NULL)
    {
       q->front=q->rear=tempNode;
       q->Size++;
       return;
    }

    q->rear->next=tempNode;

    q->rear=tempNode;

				q->Size++;
}

Node* Dequeue(Queue *q)
{
    if (q->front == NULL)	//queue already empty , can't deque anymore
       return NULL;

				Node *temp=q->front;
    
				q->front=q->front->next;

    if (q->front==NULL) q->rear = NULL;

    q->Size--;

    return temp;
}


int visited[Y][Y];



Path findPath(struct Graph graph, int si,int sj, int di,int dj)
{
	//Doesn't implement the case where start =finish

	int start= 7*si+sj;
	int finish= 7*di+dj;

	Path P = init_path();

	for(int i=0;i<Y;i++) memset(visited[i],0,sizeof visited[i]);

    int predecessor[MAX_PLEN]; memset(predecessor,-1,sizeof predecessor);

	Queue * q=GetQueue();

	Enqueue(q,GetNode(si,sj));

	int flag=0; //flag 0 denotes ,we havn't reached destination vertex yet

	while(q->Size && (!flag))
	{
		Node * qfront=Dequeue(q);

		int i=	(*qfront).i;
		int j=	(*qfront).j;

		#ifdef DEBUG
			printf("<%d,%d> \n",i,j);
		#endif

        int v=CellNo(i,j);

   for(int k=0;k<4;k++)
   {
					int ni=i+dx[k];
					int nj=j+dy[k];

					if(isvalid(ni,nj))
					{
							int nv=CellNo(ni,nj);

							if(graph.adjmat[v][nv] && !visited[ni][nj])
							{
									visited[ni][nj]=1;

									predecessor[nv]=v;

									if(nv==finish)
									{
												flag=1;
												break;
									}	//finish is the destination vertex
	
									Enqueue(q,GetNode(ni,nj));
						}
			}
     

			}
        free(qfront);	//since the memory consumed at address qfront is of no use now, freeing it up
	}

    if(!flag)	// means we couldn't make it to finish cell
    {
							return P;
    }

    int tmpPath[MAX_PLEN]; memset(tmpPath,0,sizeof tmpPath);

    int v=finish,k=0;

    while(v!=start)
    {
							tmpPath[k++]=v;

							v=predecessor[v];
    }

    assert(v==start);

    tmpPath[k]=v;


    for(int i=k;i>=0;i--){
								P.arr[k-i]=tmpPath[i];
				}

	return P;
}

int si=GREEN_HOME_i;
int sj=GREEN_HOME_j;

Path GetPath(Maze maze, int di,int dj)
{
    Graph G = buildGraph(maze);

			#ifdef DEBUG
			for(int i=0;i<X;i++)
   {
						for(int j=0;j<X;j++){
						if(adjacency_matrix.mat[i][j])
            	printf("edge : (%d , %d)\n",i,j);
        }
    }
    #endif



    Path path = findPath(G, si,sj, di,dj);

    si=di;
    sj=dj;

				return path;
}

void block(Maze *M, int xi,int xj,char dir)
{

	switch(dir)
	{

		case 'R':
		{
			(*M).arr[xi][xj]+=2;
            break;
		}
		case 'L':
		{
			(*M).arr[xi][xj]+=8;
			break;
		}
		case 'U':
		{
			(*M).arr[xi][xj]+=1;
			break;
		}
		case 'D':
		{
			(*M).arr[xi][xj]+=4;
			break;
		}
		default:
		{
			printf("Error ! source : block function");
			break;
		}

	}
}

void Put_Obstacle_At(Maze * M , int i,int j)
{
    (*M).arr[i][j]=15;

	    if(isvalid(i,j-1))
								block(M,i,j-1,'R');

					if(isvalid(i,j+1))
								block(M,i,j+1,'L');

					if(isvalid(i-1,j))
								block(M,i-1,j,'U');

					if(isvalid(i+1,j))
								block(M,i+1,j,'D');

}



