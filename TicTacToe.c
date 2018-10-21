#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<dos.h>
#include<dir.h>
int P;
int draw=0;

struct node{
    char val;
    struct node *next;
    struct node *down;
};

void SetColor(int ForgC)
 {
     WORD wColor;

      HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
      CONSOLE_SCREEN_BUFFER_INFO csbi;
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
 }

void initializeBoard(struct node *arr[], int n) {
    int i, j;
    struct node *newNode, *ptr;
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            newNode = (struct node*)malloc(sizeof(struct node));
            newNode->next = NULL;
            newNode->down = NULL;
            newNode->val = ' ';
            if(j==0) {
                arr[i] = newNode;
                ptr = arr[i];
            }
            else{
                ptr->next = newNode;
                ptr = ptr->next;
            }
        } 
    }
    //down pointer
    for(j=0; j<n-1; j++) {
        ptr = arr[j];
        newNode = arr[j+1];
        for(i=0; i<n; i++) {
            ptr->down = newNode;
            ptr = ptr->next;
            newNode = newNode->next;
        }
    }
}

void reInitialize(struct node *arr[], int n) {
	int i,j;
	struct node *ptr;
	for(i=0; i<n; i++) {
		ptr = arr[i];
		for(j=0; j<n; j++) {
			ptr->val = ' ';
			ptr = ptr->next;
		}
	}
}

void printBoard(struct node *arr[], int n) {
    int i, j, k;
    struct node *ptr;
    for(k=0;k<n;k++){
   		printf(" ---------------");
    }
    printf("\n");
    for(i=0; i<n; i++) {


   		printf("|");
   		for(k=0;k<n;k++){
   			printf("               |");
   		}
   		printf("\n");       
   		printf("|");
   		for(k=0;k<n;k++){
   			printf("               |");
   		}
   		printf("\n");


        ptr = arr[i];
        for(j=1; j<=n; j++) {
            if(ptr->val == ' '){
                printf("|\t%d\t", i*n+j);
            }
            else{
            	if(ptr->val=='X'){
            		printf("|");
            		SetColor(12);
               		printf("\t%c\t", ptr->val);
               		SetColor(15);
           		}
           		else{
            		printf("|");           			
           			SetColor(11);
           			printf("\t%c\t", ptr->val);
           			SetColor(15);
           		}
            }
            ptr=ptr->next;
        }
        printf("|");
        printf("\n");


        printf("|");
   		for(k=0;k<n;k++){
   			printf("               |");
   		}
   		printf("\n");       
   		printf("|");
   		for(k=0;k<n;k++){
   			printf("               |");
   		}
   		printf("\n");       
        for(k=0;k<n;k++){
   			printf(" ---------------");
    	}
    	printf("\n");


    }
}

int input(struct node *arr[], int pl, int n){
    int pos, row, col;
    struct node *ptr;
    printf("Enter a number to place your symbol there: ");
    scanf("%d", &pos);
    row = (pos-1)/n;    
    col = (pos-1)%n;    
    ptr =arr[row];
    if(pos<1 || pos>n*n){
    	SetColor(2);
    	printf("Invalid position\n");
    	SetColor(15);
	    input(arr, pl, n);
    }
    else{
	    for(pos=0; pos!=col; pos++) {
	        ptr = ptr->next;
	    }
	    if(ptr->val != ' ') {
	    	SetColor(2);
	        printf("Invalid position\n");
	        SetColor(15);
	        input(arr, pl, n);
	    }
	    else{
	        if(pl % 2 == 1 ) {
	            ptr->val = 'X';
	        }
	        else {
	            ptr->val = 'O';
	        }
	        draw++;
	    }
    }
    return draw;
}

void playerWins(char c){
	if(c=='X'){
		P=1;
	}
	else{
		P=2;
	}
}

int isGameOver(struct node *arr[], int n){
	int gameOver,i,j;
    struct node *ptr;
    char values[n];
    //Horizontal Check
    for (i = 0; i < n; i++)
    {
    	gameOver = 1;
    	ptr = arr[i];
    	for(j=0; j<n; j++) {
    		values[j] = ptr->val;
    		ptr= ptr->next;
	   	}
        //checing if row is equal
    	for(j=0; j<n-1; j++){
    		if(values[j]==' ' || values[j+1] == ' '){
    			gameOver = 0;
    			break;
    		}
    		else if(values[j] != values[j+1]){
    			gameOver = 0;
    			break;
    		}
    	}
    	if(gameOver == 1){
    		playerWins(values[j]);
    		return gameOver;
		}    		    	
    }
    //Vertical Check
    for(i=0; i<n; i++){
        ptr = arr[0];
        for(j=0; j<i; j++) {
            ptr = ptr->next;
        }
        gameOver = 1;
        for(j=0; j<n; j++){
            values[j] = ptr->val;
            ptr = ptr->down;
        }
        //checking if column is equal
        for(j=0; j<n-1; j++) {
            if(values[j]==' ' || values[j+1] == ' '){
    			gameOver = 0;
    			break;
    		}
            if(values[j] != values[j+1]) {
                gameOver = 0;
                break;
            }
        }
        if(gameOver == 1){
        	playerWins(values[j]);
    		return gameOver;
		}
    }
    //leading Diagonal
    for(i=0; i<n; i++){
        gameOver = 1;
        ptr = arr[i];
        for(j=0; j<i; j++){
            ptr = ptr->next;
        }
        values[i] = ptr->val;
        //checking if leading diagonal is equal
        for(j=0; j<n-1; j++) {
            if(values[j]==' ' || values[j+1] == ' '){
    			gameOver = 0;
    			break;
    		}
            if(values[j] != values[j+1]) {
                gameOver = 0;
                break;
            }
        }
        if(gameOver == 1){
        	playerWins(values[j]);
    		return gameOver;
		}
    }
    //other Diagonal
    for(i=n-1; i>=0; i--){
        gameOver = 1;
        ptr = arr[n-i-1];
        for(j=0; j<i; j++){
            ptr = ptr->next;
        }
        values[n-i-1] = ptr->val;
        //checking if non-leading diagonal is equal
        for(j=0; j<n-1; j++) {
            if(values[j]==' ' || values[j+1] == ' '){
    			gameOver = 0;
    			break;
    		}
            if(values[j] != values[j+1]) {
                gameOver = 0;
                break;
            }
        }
        if(gameOver == 1){
        	playerWins(values[j]);
    		return gameOver;
		}
    }
    return gameOver;
}



int main() {
	system("cls");
	char player1[25], player2[25];
    int pl=1, n=4, d, ch,e;	//n is size of matrix
    struct node *arr[n];
    while(ch!=2){
    	P=0;
    	system("cls");
    	SetColor(2);
	    printf(" -------------------------------------------------------------------------\n");
		printf("|                                                                         |\n");
		printf("|                               TIC TAC TOE                               |\n");
		printf("|                                                                         |\n");
		printf(" -------------------------------------------------------------------------\n");
		printf("|                                                                         |\n");
		printf("|                                1. PLAY                                  |\n");
		printf("|                                2. QUIT                                  |\n");
		printf("|                                                                         |\n");
		printf(" -------------------------------------------------------------------------\n");
		printf("|  Select a choice:                                                       |\n");
		printf(" -------------------------------------------------------------------------\n");
		scanf("%d",&ch);
		SetColor(15);
		switch(ch){
			case 1:
		    	system("cls");
			    printf("Player 1 Enter your name: ");
			    SetColor(12);  
			    scanf("%s", &player1);
			    printf("%s your symbol is X\n\n\n",player1);
			    SetColor(15);
			    printf("Player 2 Enter your name: ");
			    SetColor(11);  
			    scanf("%s", &player2);
			    printf("%s your symbol is O\n\n\n",player2);
			    SetColor(15);
			    printf("Press any key to continue.\n");
			    getch();
			    initializeBoard(arr, n);
			    do{
			    	system("cls");
			    	if(d==(n*n)){
			    		break;
			    	}
			    	else{
				    	printBoard(arr, n);
				    	if(pl % 2 != 0){	 
				    		SetColor(12);   		
				            printf("\nYour move %s.\n", player1);
				    		d = input(arr, pl, n);	
				    		SetColor(15);    		
						}
						else{
				    		SetColor(11);   
							printf("\nYour move %s.\n", player2);
							d = input(arr, pl, n);
				    		SetColor(15);   		
						}
						pl ++;
					}	
				}while(isGameOver(arr,n) != 1);
				system("cls");
				printBoard(arr, n);
				if(P==1){
					SetColor(12);   		
					printf("\n\t\t%s Wins!!\n",player1);
					SetColor(15);   		
				}
				else if(P==2){
					SetColor(11);   		
					printf("\n\t\t%s Wins!!\n",player2);
					SetColor(15);   		
				}
				else{
					SetColor(2);   		
					printf("\n\t\tIt's a Draw!\n\n");
					SetColor(15);   		
				}
				printf("\n\n");
				printf("Press any key to continue.\n");
			    getch();
				reInitialize(arr, n);		
				draw = 0;
				d=0;
				break;
			case 2:
				break;
			default:
				SetColor(2);
				printf("Enter a valid choice");	
				SetColor(15);
		}				
	}while(ch!=2);
	system("cls");	
    return 0;
}
