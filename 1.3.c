#include<stdio.h> 
#include <stdlib.h>
#include <string.h>
#define N 5 
#define M 1000 
#define MAX 100

typedef struct{ 
 int data[N]; 
 int front; 
 int rear; 
 int count; 
} Node; 

typedef struct {
	int data[MAX];
	int count;
} stack;

void initialisasi(stack *s);
int kosong(stack *s);
int penuh(stack *s);
void push(int x, stack *s);
int pop(stack *s);

void tampil(int data[N][N]);
char pilihan;

void main(){ 
	int asal, tujuan;
	int beban[N][N];
	int TQ[N], R[N];
	stack sRute;
	Node q;
	 
	initialiseMatrik(&beban);
	
	do {
		inputCariRute(&asal, &tujuan);
		initialiseTQR(asal, TQ);
		
		tampilHasil(&beban);
		
		initialisasiQueue(&q);
		enqueue(asal-1, &q);
		
		printf("Hasil \n");
		
		dijkstra(asal, tujuan, &beban, &TQ, &R, &q);
		initialisasi(&sRute);
		cariRute(asal, tujuan, &R, &sRute);
		
		tampilAkhir(&TQ, &R);
		
		printf("Ulang program [y/t] : ");
		pilihan = getchar();
		fflush(stdin);
	} while(pilihan == 'y' || pilihan == 'Y');
}

int tampilAkhir(int TQ[N], int R[N]){
	printf("%-18s", "Beban Minimum");
	printf(": ");
	hitungBeban(TQ);
	printf("%-18s", "Matrik Beban");
	printf(": ");
	tampil2(TQ);
	printf("%-18s", "Matrik Rute");
	printf(": ");
	tampil2(R);
}

int initialiseMatrik(int beban[N][N]){
	int A[N][N] = {
		{M,1,3,M,M}, 
		{M,M,1,M,5}, 
		{3,M,M,2,M}, 
		{M,M,M,M,1}, 
		{M,M,M,M,M}
	}; 
	
	copyData(A, beban);
}

int copyData(int data2[N][N], int data[N][N]){
	int i, j;
	
	for(i=0; i<N; i++)
		for(j=0; j<N; j++)
			data[i][j] = data2[i][j];
}

int initialiseTQR(int a, int Q[N]){
	int i;
	
	for(i=0; i<N; i++) 
		if((i+1) == a) 
			Q[i]=0; 
		else 
			Q[i]=M;
}

int inputCariRute(int *asal, int *tujuan){
	printf("%-18s", "Masukkan Asal");
	printf(": ");
	scanf("%d", asal);
	fflush(stdin);
	printf("%-18s", "Masukkan Tujuan");
	printf(": ");
	scanf("%d", tujuan);
	fflush(stdin);
}

int tampilHasil(int beban[N][N]){
	printf("%-18s", "Matrix Beban (Q)");
	printf(": \n");
	tampil(beban);
	printf("\n"); 
}

void tampil(int data[N][N]){ 
int i, j;
	for(i=0; i<N; i++) { 
		for(j=0; j<N; j++){
			if(data[i][j] >= M)  
			printf("M "); 
			else 
			printf("%d ", data[i][j]); 
		}
		printf("\n"); 
	} 
} 

int tampil2(int data[N]){ 
int i;
	for(i=0; i<N; i++) { 
		if(data[i] >= M)  
			printf("M "); 
		else 
			printf("%d ", data[i]); 
	} 
	printf("\n"); 
} 

int initialisasiQueue(Node *q){
	q->front = 0;
	q->rear = 0;
	q->count = 0;
}

int qKosong(Node *q) {
	return q->count == 0; 
} 
 
int qPenuh(Node *q) { 
 	return q->count == N; 
} 

int enqueue(int x, Node *q){
	if(qPenuh(q)){ 
		printf("Queue Penuh !\n"); 
		exit(1); 
	} else { 
		q->data[q->rear] = x; 
		q->rear = (q->rear + 1) % N; 
		q->count++; 
	}
}

int dequeue(Node *q) {
	int temp; 
	if(qKosong(q)){ 
		printf("Queue kosong !\n"); 
		temp = -1; 
	} else{ 
		temp = q->data[q->front]; 
		q->front = (q->front + 1) % N; 
		q->count--; 
	} 
	return temp;
}

int dijkstra(int asal, int tujuan, int Q[N][N], int TQ[N], int R[N], Node *q){
	int currentNode;
	int i;
	
	while(!qKosong(q)){
		currentNode = dequeue(q);
		
		for(i=0; i<N; i++){
			if(Q[currentNode][i] != M){
				if(Q[currentNode][i] + TQ[currentNode] < TQ[i]){
					TQ[i] = Q[currentNode][i] + TQ[currentNode];
					R[i] = currentNode;
					if(i != asal-1 && i != tujuan-1 && !checkQ(i, q)){
						enqueue(i, q);
					}
				}
			}
		}
	}
//	tampil2(R);
}

int checkQ(int x, Node *q){
	int i = q->count - 1;
	while( !qKosong(q)){
		if(q->data[i] == x){
			return(1);
		} 
		i = i - 1;
	}
	return(0);	
}

int hitungBeban(int TQ[N]){
	int i, hasil = 0;
	for(i=0; i<N; i++){
		if(TQ[N] == M){
			break;
		}
		hasil = TQ[i];
	}
	printf("%d\n", hasil);
	return(hasil);
}

int cariRute(int asal, int tujuan, int R[N], stack *s){
	int i, j, r;
	
	for(i=N-1; i>=0; i--){
		r = R[i]+1;
		if(r == M)
			break;
		push(r, s);
	}
	
	printf("%-18s", "Rute Jalur");
	printf(": ");
	printf("%d", pop(s));
	while(!kosong(s)){
		printf(" - %d", pop(s));
	}
	printf("\n");
}

void initialisasi(stack *s) {
	s->count = 0;
}

int kosong(stack *s){
	if(s->count== 0)
		return(1);
	else
		return(0);
}

int penuh(stack *s) {
	if(s->count == MAX)
		return(1);
	else 
		return(0);
}

void push(int x, stack *s) {
	if(penuh(s))
		printf("Stack penuh, tidak bisa menyimpan data\n");
	else {
		s->data[s->count] = x;
		s->count++;
	}
}

int pop(stack *s) {
	int x;
	
	if(kosong(s)){
		printf("stack kosong, tidak ada data ");
		return(0);
	} else {
		x = s->data[--s->count];
		return(x);		
	}
}
