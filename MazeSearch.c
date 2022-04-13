#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <windows.h>

#define MAX 128

struct Node {
	int node[2];
	struct Node *next;	
};

struct Queue {
	int n;
	Node *front;
	Node *end;
};

int **map;
int **visit;

int n, m;

int pX, pY;

int re[2];

void init(Queue *q) {
	q->front = q->end = NULL;
	q->n = 0;
}

void push(Queue *q, int data[2]) {
	if( MAX < q->n ) {
		printf("큐의 최대 크기를 넘었습니다.");
		return;
	}
	
	Node *node = (Node *)malloc(sizeof(Node));
	node->node[0] = data[0];
	node->node[1] = data[1];
	node->next = NULL;
	
	if( q->n == 0 ){
		q->front = node;
	} else{
		q->end->next = node;
	}
	
	q->end = node;
	q->n += 1;
} 

int *pop(Queue *q) {
	Node *node;
	
	if( q->n == 0 )
		return 0;
	
	node = q->front;
	
	re[0] = node->node[0];
	re[1] = node->node[1];
	
	q->front = node->next;
	
	free(node);
	q->n -= 1;
	
	return re;
}

void print(Queue *q){
	system("cls");
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++) {
			if( visit[i][j] == 1) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
				printf("%d ", map[i][j]);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			} else {
				printf("%d ", map[i][j]);
			}
			
		}
		printf("\n");
	}
	
	printf("queue : [ ");
	printf("%d ", q->n);
	printf("]\n");
}


int bfs(Queue *q, int x, int y) {
	
	int vector2[2] = {x, y}; //push 할 배열  
	int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1}; // 상 하 좌 우 방향 정의 
	visit[x][y] = 1; // 방문 처리 
	
	push(q, vector2);
	
	while( q->n ) {
		printf("빼기전 큐의 갯수 : %d\n", q->n);
		int *que = pop(q);
		x = que[0], y = que[1];
		printf("큐의 갯수 : %d\n", q->n);
		
		printf(" 현재 위치 : %d, %d \n", x, y);
		
		for(int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			
			if( nx >= 0 && ny >= 0 && nx < n && ny < m)
			if( map[nx][ny] == 1 && visit[nx][ny] == 0) { //1 이고 방문 표시가 0 인곳을 방문 
				map[nx][ny] = map[x][y] + 1;
				visit[nx][ny] = 1;
				int result[2] = {nx, ny};
				push(q, result);
				Sleep(300);
				//printf("(%d , %d)\n", nx, ny);
				print(q);
				
			}
			
		}
		
	}
	
	return map[pX - 1][pY -1];
} 

int main() {
	Queue *q = (Queue *) malloc(sizeof(Queue));
	
	init(q); // 큐의 초기회 
	
	scanf("%d %d", &n, &m);
	map = (int **) malloc(sizeof(int*) * n);
	visit = (int **) malloc(sizeof(int*) * n);
	
	for(int i = 0; i < n; i++) {
		map[i] = (int*)malloc(sizeof(int) *m); // 맵 초기화 
		visit[i] = (int*)malloc(sizeof(int) *m);
	}
		
	
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			int data;
			scanf("%d", &data);
			map[i][j] = data;
			visit[i][j] = 0;
		}
		
	}
	
	scanf("%d %d", &pX, &pY);	

	printf("\n[result || vector(%d, %d)] : %d", pX - 1, pY - 1, bfs(q, 0, 0));
	
	
	free(q);
	
	return 0;
}
