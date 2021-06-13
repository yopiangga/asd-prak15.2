#include<stdio.h> 
#include <stdlib.h>
#include <string.h>
#define N 5 
#define M 1000 
#define MAX 100

typedef struct element Node;
struct element {
	int data;
	Node *next;
};

typedef struct {
	int data[MAX];
	int count;
} stack;

void initialisasi(stack *s);
int kosong(stack *s);
int penuh(stack *s);
void push(int x, stack *s);
int pop(stack *s);

Node *rear, *front, *p;

void tampil(int data[N][N]);

char pilihan;

void main(){ 
	int asal, tujuan;
	int beban[N][N];
	int TQ[N], R[N];
	stack sRute;
	 
	initialiseMatrik(&beban);
	
	do {
		inputCariRute(&asal, &tujuan);
		initialiseTQR(&TQ, &R, asal);
		
		tampilHasil(&beban);
		
		initialisasiQueue();
		tambah(asal-1);
		
		printf("Hasil \n");
		
		dijkstra(asal, tujuan, &beban, &TQ, &R);
		initialisasi(&sRute);
		cariRute(asal, tujuan, &R, &sRute);
		
		tampilAkhir(&TQ, &R, tujuan);
		printf("%-18s", "Ulang program");
		printf(": ");
		pilihan = getchar();
		fflush(stdin);
		printf("\n");
	} while(pilihan == 'y' || pilihan == 'Y');
}

int tampilAkhir(int TQ[N], int R[N], int tujuan){
	printf("%-18s", "Beban Minimum");
	printf(": ");
	hitungBeban(TQ, tujuan);
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

int initialiseTQR(int TQ[N], int R[N], int asal){
	int A[N] = {M,M,M,M,M}; 
	A[asal-1] = 0;
	int B[N] = {-1,-1,-1,-1,-1};
	 
	copyData2(A, TQ);
	copyData2(B, R);
}

int copyData2(int data2[N], int data[N]){
	int i, j;
	
	for(i=0; i<N; i++)
		data[i] = data2[i];
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

int initialisasiQueue(){
	front = NULL;
	rear = NULL;
}

int alokasi(int asal){
	
	p = (Node *) malloc(sizeof(Node));
	
	if(p == NULL){
		printf("Alokasi memori gagal");
		exit(0);
	}
	
	p->data = asal;
	p->next = NULL;
}

int tambah(int asal){
	alokasi(asal);
	
	enqueue();
}

int enqueue(){
	Node *jalan;
	jalan = front;
	
	if(front == NULL){
		front = p;
	} else {
		while(jalan->next != NULL){
			jalan = jalan->next;
		}
		jalan->next = p;
	}
}

int dequeue() {
	int x;
	
	if(front == NULL){
		printf("stack kosong, tidak ada data ");
		return(0);
	} else {
		x = front->data;
		front = front->next;
		return(x);	
	}
}

int dijkstra(int asal, int tujuan, int Q[N][N], int TQ[N], int R[N]){
	int currentNode;
	int i;
	
	while(front != NULL){
		currentNode = dequeue();
		
		for(i=0; i<N; i++){
			if(Q[currentNode][i] != M){
				if(Q[currentNode][i] + TQ[currentNode] < TQ[i]){
					TQ[i] = Q[currentNode][i] + TQ[currentNode];
					R[i] = currentNode;
					if(i != asal-1 && i != tujuan-1 && !checkQ(i)){
						tambah(i);
					}
				}
			}
		}
	}
}

int checkQ(int x){
	Node *jalan;
	jalan = front;
	
	if(front == NULL){
		return(0);
	} else {
		while(jalan != NULL){
			if(jalan->data == x){
				return(1);
			} 
			jalan = jalan->next;
		}
		return(0);	
	}
}

int hitungBeban(int TQ[N], int tujuan){
	int i, hasil = 0;
	for(i=0; i<N; i++){
		if(i == tujuan){
			break;
		}
		hasil = TQ[i];
	}
	printf("%d\n", hasil);
	return(hasil);
}

int cariRute(int asal, int tujuan, int R[N], stack *s){
	int i, j, r;
	
	for(i=tujuan-1; i>=0; i--){
		if(R[i] == -1){
			break;
		}
		r = R[i]+2;
		push(r, s);
	}
	
	printf("%-18s", "Rute Jalur");
	printf(": ");
	printf("%d", asal);
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
