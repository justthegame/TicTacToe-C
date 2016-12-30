#include <stdio.h>
#include <string.h>
#include <time.h>//time_tt
#include <stdlib.h>

char board[3][3]; /* This array is responsible for storing current gamestate.*/
typedef enum { false, true } bool;


void printer(void);
int move(char, bool);
int win_condition(void);
int pvp(int choice);
int analyze();

int main()
{
	char small_buffer[3];
	int choice;
	printf("Tictactoe v0.1.0\n");
	printf("Would you like to play against PC(1) or human?(1/2)");
	do{
		fgets(small_buffer, sizeof small_buffer, stdin);
		choice = strtol(small_buffer,NULL,10);
	}	while(choice!=1 && choice!=2);
	/*Do-while loop presented above makes sure that end-user won't leave
	 *start menu unless he choses a valid option. strtol is used as a further
	 *security measure - since our strings are converted to valid numbers via
	 *function and not some gimmicky ASCII substraction there is certain level
	 *of comfort about malicious input from user.
	*/
	pvp(choice);
	return 0;
}



int pvp(int choice)
{
	int seed;//randomizer seed;
	int response=0;//value returned by move() function
	char buffer[20];
	char small_buffer[3];
	bool current_player=false;
	char p1[100]; //Player's name
	char p2[100];//Player's name
	time_t tt;//sprawdzamy czas od 01.01.1970
	int i,p;//loop controlers
	int new_game=0;
	int input=0;
	while(new_game<1){
		seed = time(&tt);
		srand(seed); /* Zmienna bez określonej wartości przyjmuje losowe wartości*/
		if(choice==1){
			strncpy(p2,"PC", sizeof(p2)-1);
		}
		for(i=0;i<3;i++){
			for(p=0;p<3;p++)
				board[i][p]='#';
		}
		printf("Hello! What is your name?\nName:");
		fgets(p1, sizeof p1, stdin);
		p1[strcspn(p1, "\n")] = 0;
		if(choice==2){
			printf("%s, how is your enemy called?\nName:", p1);
			fgets(p2, sizeof p2, stdin);
			p2[strcspn(p2, "\n")] = 0;
		}
		/*Above code block(starting at first printf) is responsile for getting the player's name into two variables, p1 and p2
		 *It accomplishes it's goal via fgets and strcspn functions. strcspn removes newline.*/
		printf("Here's the board! Familiarize yourself with it.\n\n");
		printer();
		if(seed%2==0){
			printf("%s starts!\n", p2);
			current_player=false;
		}else{
			printf("%s starts!\n", p1);
			current_player=true;
		}
		for(i=0;i<9;i++)/*Można wykonać maksymalnie 9 ruchów by zapełnić planszę, dlatego i<9*/
		{
			if(choice==2){
			printf("%s, which field would you like to fill?\n", current_player==true?p1:p2);
			fgets(buffer, sizeof buffer, stdin);
			input= strtol(buffer,NULL,10);
			response = move(input, current_player);/*Przechowujemy odpowiedź funkcji ruch w zmiennej response*/
			while(response == 0) { /*Funkcja response zwraca 0 jeśli wprowadzono znak spoza dozwolonego zakresu.
				Prosimy wtedy zawodnika o powtórzenie jego ruchu.*/
				printf("Field you have chosen doesn't exist or is already occupied!\n");
				fgets(buffer, sizeof buffer, stdin);
				input= strtol(buffer,NULL,10);
				response = move(input, current_player);
			}
		} else if(current_player==true && choice==1){
				printf("%s, which field would you like to fill?\n",p1);
				fgets(buffer, sizeof buffer, stdin);
				input= strtol(buffer,NULL,10);
				response = move(input, current_player);/*Przechowujemy odpowiedź funkcji ruch w zmiennej response*/
				while(response == 0) { /*Funkcja response zwraca 0 jeśli wprowadzono znak spoza dozwolonego zakresu.
					Prosimy wtedy zawodnika o powtórzenie jego ruchu.*/
					printf("Field you have chosen doesn't exist or is already occupied!\n");
					fgets(buffer, sizeof buffer, stdin);
					input= strtol(buffer,NULL,10);
					response = move(input, current_player);
				}
			} else if(current_player==false){
				input=analyze();
				printf("AI chose field no. %d!\n",input);
				response = move(input, current_player);/*Przechowujemy odpowiedź funkcji ruch w zmiennej response*/
				while(response == 0) { /*Funkcja response zwraca 0 jeśli wprowadzono znak spoza dozwolonego zakresu.
					Prosimy wtedy komputer o powtórzenie jego ruchu.*/
				input=analyze();
				response = move(input, current_player);}}
			printer();/*Pokaż planszę*/
			current_player = !current_player;/*Zmiana wartości ruc pozwala przeciwnikowi na ruch w następnej turze(następnym obrocie pętli)*/
			if(i>=4 && (win_condition()==1 || win_condition()==2)){
				printf("%s won!\n", win_condition()==1?p1:p2);
				break;
			}/*win_condition sprawdza warunek wygranej - jeśli któryś z graczy go spełni,
			zwraca identyfikator gracza i przerywa pętlę*/
		}
		if(win_condition()==0)
			printf("Draw!\n");/*Jeśli na końcu gry nikt nie wygrał, wyświetl odpowiedni komunikat*/

		printf("Would you like to play again?(Y/n)\n");
		fgets(small_buffer, sizeof small_buffer, stdin);
		small_buffer[strcspn(small_buffer, "\n")] = 0;
		if(small_buffer[0]=='Y'||small_buffer[0]=='y'){
			continue;
		}
		if(small_buffer[0]=='N'||small_buffer[0]=='n'){
			new_game++;
		} else {
			return 0;
		}
	}
	return 0;

}

int move(char pole, bool gracz){
	int i,p;
	for(i=0;i<3;i++){
		for(p=0;p<3;p++){
			if(pole-1==i*3+p)
				if (board[i][p] == '#'){
					board[i][p] = (gracz) ? 'X' : 'O'; return 3;
					}
	/*Jeśli pole jest wolne(wartość elementu tablicy to "#"), to wstaw znak. W przeciwnym wypadku zwróć komunikat błędu.*/
}}
	return 0;
}

void printer(void)
{
	printf("%c %c %c\n%c %c %c\n%c %c %c \n \n", board[0][0], board[0][1], board[0][2],board[1][0], board[1][1], board[1][2], board[2][0], board[2][1], board[2][2]);
	/*Pokaż na ekranie wszystkie elementy tablicy w odpowiedniej kolejności*/
}
int win_condition(){
	int i,p;
	for(i=0;i<3;i++){
		for(p=0;p<3;p++){
			if((board[i][p]=='X' && board[i][p+1]=='X' && board[i][p+2]=='X' && p==0) || (board[i][p]=='X' && board[i+1][p]=='X' && board[i+2][p]=='X')||
			(board[i][i]=='X' && board[i+1][i+1]=='X' && board[i+2][i+2]=='X') || (board[2][0]=='X' && board[1][1]=='X' && board[0][2]=='X')){
				return 1;
			}	else if((board[i][p]=='O' && board[i][p+1]=='O' && board[i][p+2]=='O' && p==0) || (board[i][p]=='O' && board[i+1][p]=='O' && board[i+2][p]=='O')||
						(board[i][i]=='O' && board[i+1][i+1]=='O' && board[i+2][i+2]=='O') ||  (board[2][0]=='O' && board[1][1]=='O' && board[0][2]=='O')){
							return 2;
						}
		}			/*Sprawdza, czy odpowiednie pola są zajęte. Jeśli któryś z graczy zapełni
					3 pola wymagane do wygranej to funkcja zwróci odpowiednią wartość, W przeciwnym wypadku
					zwraca wartość 0, świadczącą o remisie.*/
	}
				return 0;
}
int analyze(){
	int i,p,pole,x,d;
	x=0;
	d=0;
	pole=0;
	for(i=0;i<3;i++){
		for(p=0;p<3;p++){
			if((board[i][p-2]=='O' && board[i][p-1]=='O' && board[i][p]=='#' && p==2)||(board[i][p+1]=='O' && board[i][p+2]=='O' && board[i][p]=='#' && p==0)
			||(board[i][p-1]=='O' && board[i][p+1]=='O' && board[i][p]=='#' && p==1) || (board[i+1][p]=='O' && board[i+2][p]=='O' && board[i][p]=='#' && i==0)
			|| (board[i-1][p]=='O' && board[i+1][p]=='O' && board[i][p]=='#' && i==1) || (board[i-1][p]=='O' && board[i-2][p]=='O' && board[i][p]=='#' && i==2)
			|| (board[i][i]=='#' && board[i+1][i+1]=='O' && board[i+2][i+2]=='O' && p==i)	|| (board[i][i]=='#' && board[i-1][i-1]=='O' && board[i-2][i-2]=='O' && p==i)
			|| (board[i][i]=='#' && board[i-1][i-1]=='O' && board[i+1][i+1]=='O' && p==i)	|| (board[i][p]=='#' && board[i-1][p+1]=='O' && board[i-2][p+2]=='O' && i==2 && p==0)
			|| (board[i][p]=='#' && board[i+1][p-1]=='O' && board[i-1][p+1]=='O' && i==1 && p==1) || (board[i][p]=='#' && board[i+1][p-1]=='O' && board[i+2][p-2]=='O' && i==0 && p==2)	){
				pole=i*3+p+1;
				return pole;}
			}}
		for(i=0;i<3;i++){
			for(p=0;p<3;p++){
				if((board[i][p-2]=='X' && board[i][p-1]=='X' && board[i][p]=='#' && p==2)||(board[i][p+1]=='X' && board[i][p+2]=='X' && board[i][p]=='#' && p==0)
				||(board[i][p-1]=='X' && board[i][p+1]=='X' && board[i][p]=='#' && p==1) || (board[i+1][p]=='X' && board[i+2][p]=='X' && board[i][p]=='#' && i==0)
				|| (board[i-1][p]=='X' && board[i+1][p]=='X' && board[i][p]=='#' && i==1) || (board[i-1][p]=='X' && board[i-2][p]=='X' && board[i][p]=='#' && i==2)
				|| (board[i][i]=='#' && board[i+1][i+1]=='X' && board[i+2][i+2]=='X' && p==i)	|| (board[i][i]=='#' && board[i-1][i-1]=='X' && board[i-2][i-2]=='X' && p==i)
				|| (board[i][i]=='#' && board[i-1][i-1]=='X' && board[i+1][i+1]=='X' && p==i)	|| (board[i][p]=='#' && board[i-1][p+1]=='X' && board[i-2][p+2]=='X' && i==2 && p==0)
				|| (board[i][p]=='#' && board[i+1][p-1]=='X' && board[i-1][p+1]=='X' && i==1 && p==1) || (board[i][p]=='#' && board[i+1][p-1]=='X' && board[i+2][p-2]=='X' && i==0 && p==2)	 	){
					pole=i*3+p+1;
					return pole;}}}
		if(board[1][1]=='#'){
			return 5;}

		for(i=0;i<3;i++){
			for(p=0;p<3;p++){
				if(board[i][p]=='#'){
					x=rand();
					d=rand();
					d=d%3;
					x=x%3;
					if(board[x][d]=='#')
						return (3*x+d+1);
							}
						}}}
