#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.c"



typedef struct bestReturn {
    move x;
    double value;
}bestReturn;
bestReturn engine(set game,int color,int d)//d glebokosc
{
	bestReturn best;
	bestReturn current;
	current.value=0.0;
	best.value=0.0;
	element *head = malloc(sizeof(element));
	//printf("%d \n",d);
	head = generate(game,color);
	if(!head->nastepny)
	{
	    if(isCheck(game.board,!color))
	    {
	        if(color)//biale matuja czarnego
	        {
	            best.x.pos1=1000;
	            best.x.pos2=1000;
	            best.value=1000.0;
				zniszcz(head);
	            return best;
	        }
	    }
		else if(isCheck(game.board,color))//czarne matuja bialego
				{
					if(!color)
					{
					best.x.pos1=-1000;
	                best.x.pos2=-1000;
	                best.value=-1000.0;
					zniszcz(head);
	                return best;
					}
				}
	    else//pat
	    {
	        best.x.pos1=100;
	        best.x.pos2=100;
			best.value=0.0;
		    zniszcz(head);
	        return best;
	    }
	}
	head=head->nastepny;
	best.x=head->ruch;
	//showL(head);
	//printf("#######");
	for(;head;head=head->nastepny)
	{
		move temp=head->ruch;
		set copyGame=game;
		//char rev1=copyGame.board[digi(temp.pos2,0)][digi(temp.pos2,1)];

        // WYKONANIE RUCHOW
		if(temp.pos1 == temp.pos2) //promocja pionka
		{
		    if(digi(temp.pos1,0)>3)copyGame.board[6][digi(temp.pos1,1)] = '#';
		    else copyGame.board[1][digi(temp.pos1,1)] = '#';
            if(digi(temp.pos1,0) == 0 || digi(temp.pos1,0 == 7)) // na hetmana
            {
                if(color) copyGame.board[0][digi(temp.pos2,1)] = 'Q'; // biale
                else copyGame.board[7][digi(temp.pos1,1)] = 'q'; // czarne
            }
            else if(digi(temp.pos1,0) == 1 || digi(temp.pos1,0 == 6)) // na skoczka
            {
                if(color) copyGame.board[0][digi(temp.pos2,1)] = 'N'; // biale
                else copyGame.board[7][digi(temp.pos1,1)] = 'n'; // czarne
            }
            else if(digi(temp.pos1,0) == 2 || digi(temp.pos1,0 == 5)) // na gonca
            {
                if(color) copyGame.board[0][digi(temp.pos2,1)] = 'B'; // biale
                else copyGame.board[digi(temp.pos1,0)][digi(temp.pos1,1)] = 'b'; // czarne
            }
            else if(digi(temp.pos1,0) == 3 || digi(temp.pos1,0 == 4)) // na wieze
            {
                if(color) copyGame.board[0][digi(temp.pos2,1)] = 'R'; // biale
                else copyGame.board[7][digi(temp.pos1,1)] = 'r'; // czarne
            }
		}
		else if(digi(temp.pos1,1)-digi(temp.pos2,1)==-2 && 
		(copyGame.board[digi(temp.pos1,0)][digi(temp.pos1,1)] == 'K' || copyGame.board[digi(temp.pos1,0)][digi(temp.pos1,1)] == 'k'))//roszada krotka
        {
            if(color) // biale
            {
                copyGame.board[7][digi(temp.pos2,1)] = 'K';
                copyGame.board[7][digi(temp.pos2,1)-1] = 'R';
                copyGame.board[7][7]='#'; // czysci pole na ktorym stal krol
                copyGame.board[7][4]='#'; // czysci pole na ktorym stala wieza
				copyGame.movedWhiteCastle[1]=1;
            }
            else // czarne
            {
                copyGame.board[1][digi(temp.pos2,1)] = 'k';
                copyGame.board[1][digi(temp.pos2,1)-1] = 'r';
                copyGame.board[1][7]='#';
                copyGame.board[1][4]='#';
				copyGame.movedBlackCastle[1]=1;
            }
        }
        else if(digi(temp.pos1,1)-digi(temp.pos2,1)==2 && 
		(copyGame.board[digi(temp.pos1,0)][digi(temp.pos1,1)] == 'K' || copyGame.board[digi(temp.pos1,0)][digi(temp.pos1,1)] == 'k'))//roszada dluga
        {
            if(color) // biale
            {
                copyGame.board[7][digi(temp.pos2,1)] = 'K';
                copyGame.board[7][digi(temp.pos2,1)+1] = 'R';
                copyGame.board[7][0]='#';
                copyGame.board[7][4]='#';
				copyGame.movedWhiteCastle[1]=1;
            }
            else // czarne
            {
                copyGame.board[0][digi(temp.pos2,1)] = 'k';
                copyGame.board[0][digi(temp.pos2,1)+1] = 'r';
                copyGame.board[0][0]='#';
                copyGame.board[0][4]='#';
				copyGame.movedBlackCastle[1]=1;
            }
        }
        else if((copyGame.board[digi(temp.pos1,0)][digi(temp.pos1,1)] == 'P' || 
		copyGame.board[digi(temp.pos1,0)][digi(temp.pos1,1)] == 'p') 
		&& copyGame.board[digi(temp.pos2,0)][digi(temp.pos2,1)] == '#' && digi(temp.pos1,1)!=digi(temp.pos2,1)) // bicie w przelocie - rozpoznanie bicia w przelocie jest wtedy gdy na pos 2 jest # (puste)
        {
            copyGame.board[digi(temp.pos1,0)][digi(temp.pos1,1)] = '#'; // czysci pos1
            copyGame.board[digi(temp.pos1,0)][digi(temp.pos2,1)] = '#'; // juz wiadomo ze to bicie w przelocie wiec usuwa zbijanego pionka
            if(color) copyGame.board[digi(temp.pos2,0)][digi(temp.pos2,1)] = 'P';// bialy bije
            else copyGame.board[digi(temp.pos2,0)][digi(temp.pos2,1)] = 'p';// czarne
        }
		else // stadardowy ruch
        {
            copyGame.board[digi(temp.pos2,0)][digi(temp.pos2,1)] = copyGame.board[digi(temp.pos1,0)][digi(temp.pos1,1)];
            copyGame.board[digi(temp.pos1,0)][digi(temp.pos1,1)] = '#';
			if(temp.pos1==0 && copyGame.movedBlackCastle[0]==0 && brd(temp.pos1,copyGame.board)=='r')copyGame.movedBlackCastle[0]=1;//odbieranie praw do roszady
			else if(temp.pos1==7 && copyGame.movedBlackCastle[2]==0 && brd(temp.pos1,copyGame.board)=='r')copyGame.movedBlackCastle[2]=1;
			else if(temp.pos1==4 && copyGame.movedBlackCastle[1]==0 && brd(temp.pos1,copyGame.board)=='k')copyGame.movedBlackCastle[1]=1;
			else if(temp.pos1==70 && copyGame.movedWhiteCastle[0]==0 && brd(temp.pos1,copyGame.board)=='R')copyGame.movedWhiteCastle[0]=1;
			else if(temp.pos1==77 && copyGame.movedWhiteCastle[2]==0 && brd(temp.pos1,copyGame.board)=='R')copyGame.movedWhiteCastle[2]=1;
			else if(temp.pos1==74 && copyGame.movedWhiteCastle[1]==0 && brd(temp.pos1,copyGame.board)=='K')copyGame.movedWhiteCastle[1]=1;
			else if(brd(temp.pos1,copyGame.board)=='p' && abs(digi(temp.pos1,0)-digi(temp.pos2,0))==2)copyGame.movedBlackPawns=digi(temp.pos1,1);//pionki ruszają się o 2 pola
			else if(brd(temp.pos1,copyGame.board)=='P' && abs(digi(temp.pos1,0)-digi(temp.pos2,0))==2)copyGame.movedWhitePawns=digi(temp.pos1,1);//pionki ruszają się o 2 pola
        }
        element *head2 = malloc(sizeof(element));
	    head2 = generate(copyGame,!color);
		//showL(head2->nastepny);
		if(head2->nastepny==NULL)//nie ma ruchow w pozycji
	        {
				//printf("%d ",d);
	            if(isCheck(copyGame.board,!color))//jest mat
	            {
					best.x=temp;
	                if(color)//biale matuja czarnego
	                {
						best.value=1000.0;
					
	                }//czarne matuja bialego
					else{
						best.value=-1000.0;
					}
					zniszcz(head);
                    zniszcz(head2);
	                return best;
	            }
				else if(isCheck(copyGame.board,color))
				{
					best.x=temp;
	                if(color)//czarne matuja bialego
	                {
						best.value=-1000.0;
					
	                }//biale matuja czarnego
					else{
						best.value=1000.0;
					}
					zniszcz(head);
                    zniszcz(head2);
	                return best;
				}
	            else//pat
	            {
	                best.x=temp;
					best.value=0.0;
			    	zniszcz(head);
                    zniszcz(head2);
	                return best;
	            }
	        }
		head2=head2->nastepny;
		current.x=temp;
		int counter=0;
	    for(;head2;head2=head2->nastepny)
	    {
            move temp2=head2->ruch;
			set copyGame2=copyGame;
            //printf("%d %d\n",temp.pos1,temp.pos2);
            //char rev=copyGame2.board[digi(temp2.pos2,0)][digi(temp2.pos2,1)];
            if(temp2.pos1 == temp2.pos2) //promocja pionka
		{
		    if(digi(temp2.pos1,0)>3)copyGame2.board[6][digi(temp2.pos1,1)] = '#';
		    else copyGame2.board[1][digi(temp2.pos1,1)] = '#';
            if(digi(temp2.pos1,0) == 0 || digi(temp2.pos1,0 == 7)) // na hetmana
            {
                if(color) copyGame2.board[0][digi(temp2.pos2,1)] = 'Q'; // biale
                else copyGame2.board[7][digi(temp2.pos1,1)] = 'q'; // czarne
            }
            else if(digi(temp2.pos1,0) == 1 || digi(temp2.pos1,0 == 6)) // na skoczka
            {
                if(color) copyGame2.board[0][digi(temp2.pos2,1)] = 'N'; // biale
                else copyGame2.board[7][digi(temp2.pos1,1)] = 'n'; // czarne
            }
            else if(digi(temp2.pos1,0) == 2 || digi(temp2.pos1,0 == 5)) // na gonca
            {
                if(color) copyGame2.board[0][digi(temp2.pos2,1)] = 'B'; // biale
                else copyGame2.board[digi(temp2.pos1,0)][digi(temp2.pos1,1)] = 'b'; // czarne
            }
            else if(digi(temp2.pos1,0) == 3 || digi(temp2.pos1,0 == 4)) // na wieze
            {
                if(color) copyGame2.board[0][digi(temp2.pos2,1)] = 'R'; // biale
                else copyGame2.board[7][digi(temp2.pos1,1)] = 'r'; // czarne
            }
		}
		else if(digi(temp2.pos1,1)-digi(temp2.pos2,1)==-2 && 
		(copyGame2.board[digi(temp2.pos1,0)][digi(temp2.pos1,1)] == 'K' || copyGame2.board[digi(temp2.pos1,0)][digi(temp2.pos1,1)] == 'k'))//roszada krotka
        {
            if(color) // biale
            {
                copyGame2.board[7][digi(temp2.pos2,1)] = 'K';
                copyGame2.board[7][digi(temp2.pos2,1)-1] = 'R';
                copyGame2.board[7][7]='#'; // czysci pole na ktorym stal krol
                copyGame2.board[7][4]='#'; // czysci pole na ktorym stala wieza
				copyGame2.movedWhiteCastle[1]=1;
            }
            else // czarne
            {
                copyGame2.board[1][digi(temp2.pos2,1)] = 'k';
                copyGame2.board[1][digi(temp2.pos2,1)-1] = 'r';
                copyGame2.board[1][7]='#';
                copyGame2.board[1][4]='#';
				copyGame2.movedBlackCastle[1]=1;
            }
        }
        else if(digi(temp2.pos1,1)-digi(temp2.pos2,1)==2 && 
		(copyGame2.board[digi(temp2.pos1,0)][digi(temp2.pos1,1)] == 'K' || copyGame2.board[digi(temp2.pos1,0)][digi(temp2.pos1,1)] == 'k'))//roszada dluga
        {
            if(color) // biale
            {
                copyGame2.board[7][digi(temp2.pos2,1)] = 'K';
                copyGame2.board[7][digi(temp2.pos2,1)+1] = 'R';
                copyGame2.board[7][0]='#';
                copyGame2.board[7][4]='#';
				copyGame2.movedWhiteCastle[1]=1;
            }
            else // czarne
            {
                copyGame2.board[0][digi(temp2.pos2,1)] = 'k';
                copyGame2.board[0][digi(temp2.pos2,1)+1] = 'r';
                copyGame2.board[0][0]='#';
                copyGame2.board[0][4]='#';
				copyGame2.movedBlackCastle[1]=1;
            }
        }
        else if((copyGame2.board[digi(temp2.pos1,0)][digi(temp2.pos1,1)] == 'P' || 
		copyGame2.board[digi(temp2.pos1,0)][digi(temp2.pos1,1)] == 'p') 
		&& copyGame2.board[digi(temp2.pos2,0)][digi(temp2.pos2,1)] == '#') // bicie w przelocie - rozpoznanie bicia w przelocie jest wtedy gdy na pos 2 jest # (puste)
        {
            copyGame2.board[digi(temp2.pos1,0)][digi(temp2.pos1,1)] = '#'; // czysci pos1
            copyGame2.board[digi(temp2.pos1,0)][digi(temp2.pos2,1)] = '#'; // juz wiadomo ze to bicie w przelocie wiec usuwa zbijanego pionka
            if(color) copyGame2.board[digi(temp2.pos2,0)][digi(temp2.pos2,1)] = 'P';// bialy bije
            else copyGame2.board[digi(temp2.pos2,0)][digi(temp2.pos2,1)] = 'p';// czarne
        }
		else // stadardowy ruch
        {
            copyGame2.board[digi(temp2.pos2,0)][digi(temp2.pos2,1)] = copyGame2.board[digi(temp2.pos1,0)][digi(temp2.pos1,1)];
            copyGame2.board[digi(temp2.pos1,0)][digi(temp2.pos1,1)] = '#';
			if(temp2.pos1==0 && copyGame2.movedBlackCastle[0]==0 && brd(temp2.pos1,copyGame2.board)=='r')copyGame2.movedBlackCastle[0]=1;//odbieranie praw do roszady
			else if(temp2.pos1==7 && copyGame2.movedBlackCastle[2]==0 && brd(temp2.pos1,copyGame2.board)=='r')copyGame2.movedBlackCastle[2]=1;
			else if(temp2.pos1==4 && copyGame2.movedBlackCastle[1]==0 && brd(temp2.pos1,copyGame2.board)=='k')copyGame2.movedBlackCastle[1]=1;
			else if(temp2.pos1==70 && copyGame2.movedWhiteCastle[0]==0 && brd(temp2.pos1,copyGame2.board)=='R')copyGame2.movedWhiteCastle[0]=1;
			else if(temp2.pos1==77 && copyGame2.movedWhiteCastle[2]==0 && brd(temp2.pos1,copyGame2.board)=='R')copyGame2.movedWhiteCastle[2]=1;
			else if(temp2.pos1==74 && copyGame2.movedWhiteCastle[1]==0 && brd(temp2.pos1,copyGame2.board)=='K')copyGame2.movedWhiteCastle[1]=1;
			else if(brd(temp2.pos1,copyGame2.board)=='p' && abs(digi(temp2.pos1,0)-digi(temp2.pos2,0))==2)copyGame2.movedBlackPawns=digi(temp2.pos1,1);//pionki ruszają się o 2 pola
			else if(brd(temp2.pos1,copyGame2.board)=='P' && abs(digi(temp2.pos1,0)-digi(temp2.pos2,0))==2)copyGame2.movedWhitePawns=digi(temp2.pos1,1);//pionki ruszają się o 2 pola
        }
            //drawBoard(copyGame2.board);
            if(d)
            {
                bestReturn t=engine(copyGame2,color,d-1);
				/*if(t.x.pos1==1000)
				{
					current.x=temp;
					current.value=1000;
				}
				else if(t.x.pos1==-1000)
				{
					current.x=temp;
					current.value=-1000;
				}
				else if(t.x.pos1==100)
				{
					current.x=temp;
					current.value=0;
				}*/
                if(current.value<t.value && !color)
                {
                    current.value=t.value;
                }
				else if(current.value>t.value && color)
                {
                    current.value=t.value;
                }
				if(!counter)
				{
					t.x=temp;
					current=t;
				}
            }
            else
            {
                double tempValue=evaluate(copyGame2.board);
                if(current.value<tempValue && !color)
                {
                    current.value=tempValue;
                }
				else if(current.value>tempValue && color)
                {
                    current.value=tempValue;
                }
				if(!counter)current.value=tempValue;
			}
			//printf("%f \n",current.value);
			counter++;
		//copy.board[digi(temp2.pos1,0)][digi(temp2.pos1,1)] = game.board[digi(temp2.pos2,0)][digi(temp2.pos2,1)];//cofniecie posuniecia
		//game.board[digi(temp2.pos2,0)][digi(temp2.pos2,1)] = rev;
		}
		//game.board[digi(temp.pos1,0)][digi(temp.pos1,1)] = game.board[digi(temp.pos2,0)][digi(temp.pos2,1)];//cofniecie posuniecia
		//game.board[digi(temp.pos2,0)][digi(temp.pos2,1)] = rev1;
	
	   //if(d)printf("## %d %d %f\n",current.x.pos1,current.x.pos2,current.value);
	   if(current.value>best.value && color) best=current;
       else if(current.value<best.value && !color) best=current;
       zniszcz(head2);
	}
	zniszcz(head);
	//printf("##%d %d %f\n",best.x.pos1,best.x.pos2,best.value);
	return best;
}
int len(element *head)
{
	int d=0;
	while(head->nastepny)
	{
		head=head->nastepny;
		d++;
	}
	return d;
}
move typeMove2(set game)
{
	move conv;
	printf("    it's your turn to make a move\n");
	element *moveOptions=generate(game,1); //pobiera ruchy z generatora do porownania
    moveOptions=moveOptions->nastepny;
	int d=len(moveOptions);
    int isInputOk=0; //zmienna ktora pomoga sprawdzic czy input jest poprawnie wpisany
    int isInputOk2=0; 
	int i=0;
	int j=0;
	char promotion[1];
	do{
		if(i)printf("invalid move\n");
		char takeMove[5];
        printf("(np. g8-f6) >> ");
        scanf("%s", takeMove);
		//'a'-'h' = 97 - 104
		//'1'-'8' = 49 - 56
		conv.pos1=(takeMove[0]-97)+(takeMove[1]-42-2*(takeMove[1]-'1'))*10;
		conv.pos2=(takeMove[3]-97)+(takeMove[4]-42-2*(takeMove[4]-'1'))*10;
		if(digi(conv.pos2,0)==7 && brd(conv.pos1,game.board)=='p')
		{
			printf("choose a piece to promote to:q,n,r,b\n");
			do{
				if(j)printf("invalid piece\n");
				scanf("%c",promotion);
				if(promotion[0]=='q'||promotion[0]=='n'||promotion[0]=='r'||promotion[0]=='b')isInputOk2=1;
				j++;
			}while(!isInputOk2);
			conv.pos1=conv.pos2;
			if(promotion[0]=='n')
			{
				conv.pos1-=10;
				conv.pos2-=10;
			}
			else if(promotion[0]=='b')
			{
				conv.pos1-=20;
				conv.pos2-=20;
			}
			else if(promotion[0]=='r')
			{
				conv.pos1-=30;
				conv.pos2-=30;
			}
		}
		else if(digi(conv.pos2,0)==0 && brd(conv.pos1,game.board)=='P')
		{
			printf("choose a piece to promote to:Q,N,R,B\n");
			do{
				if(j)printf("invalid piece\n");
				scanf("%s",promotion);
				if(promotion[0]=='Q'||promotion[0]=='N'||promotion[0]=='R'||promotion[0]=='B')isInputOk2=1;
				j++;
			}while(!isInputOk2);
			conv.pos1=conv.pos2;
			if(promotion[0]=='N')
			{
				conv.pos1+=10;
				conv.pos2+=10;
			}
			else if(promotion[0]=='B')
			{
				conv.pos1+=20;
				conv.pos2+=20;
			}
			else if(promotion[0]=='R')
			{
				conv.pos1+=30;
				conv.pos2+=30;
			}
		}
		do{
			if(moveOptions->ruch.pos1==conv.pos1 && moveOptions->ruch.pos2==conv.pos2)isInputOk=1;
			moveOptions=moveOptions->nastepny;
		}while(moveOptions->nastepny);
		moveOptions-=d;
		i++;
	}while(!isInputOk);
	return conv;
}
move typeMove(set game) //trzeba jeszcze dorobiæ ¿eby pobiera³o info z funkcji sprawdzaj¹cej czy ruch jest mo¿liwy do wykonania
{// dopisac zeby sprawdzalo czy wpisany ruch jest w liscie z tych wygenerowanych, wtedy if else z iflegalem niepotrzebny
    char kolumny[8] = {'a','b','c','d','e','f','g','h'}; //tablice pomocnicze do porownania z inputem
    char wiersze[8] = {'8', '7', '6', '5', '4', '3', '2', '1'};

    move conv; //na to skonwertowane
    conv.pos1 = NULL;
    conv.pos2 = NULL;

    printf("    it's your turn to make a move\n");

    element *moveOptions=generate(game,1); //pobiera ruchy z generatora do porownania
    moveOptions=moveOptions->nastepny;

    int isInputOk; //zmienna ktora pomoga sprawdzic czy input jest poprawnie wpisany
    element *First=moveOptions;
    do
    {
        isInputOk = 1;
        conv.pos1 = NULL;
        conv.pos2 = NULL;
        char takeMove[5];
        printf("(np. g8-f6) >> ");
        scanf("%s", takeMove);
		//'a'-'h' = 97 - 104
		//'1'-'8' = 49 - 56
		

        int isOkey0=0, isOkey1=0, isOkey3=0, isOkey4=0;

        for(int i=0; i<8 && (isOkey0 == 0 || isOkey1 == 0 || isOkey3 == 0 || isOkey4 == 0); i++) //petla leci po calej kolumny i wiersze oraz jezeli wszystko zostalo przekonwertowane poprawnie to wszyskie isOkey zmieniaja sie na 1
        {
            if(isOkey0 == 0 && takeMove[0] == kolumny[i])
            {
                conv.pos1 += i;
                isOkey0=1;
            }
            if(isOkey1 == 0 && takeMove[1] == wiersze[i])
            {
                conv.pos1 += i*10;
                isOkey1=1;
            }
            if(isOkey3 == 0 && takeMove[3] == kolumny[i])
            {
                conv.pos2 += i;
                isOkey3=1;
            }
            if(isOkey4 == 0 && takeMove[4] == wiersze[i])
            {
                conv.pos2 += i*10;
                isOkey4=1;
            }
        }
        printf("ruch to: %d %d\n", conv.pos1, conv.pos2);

        if(isOkey0 == 0 || isOkey1 == 0 || isOkey3 == 0 || isOkey4 == 0) // jezeli cos nie zostalo zmienione to cos zostalo zle wpisane
        {
            printf("invalid input notation\n");
            isInputOk = 0;
        }
        else // jezeli zostalo wpisane dobrze to wypisuje ze teraz sie dzieje analiza planszy, zmienia isInputOk i nie robi petli jeszcze raz
        {
            int checker=0;
            if(digi(conv.pos1,0)==1 && digi(conv.pos2,0)==0 && game.board[digi(conv.pos1,0)][digi(conv.pos1,1)]=='P')//dla promocji osobno
            {
                for(; moveOptions; moveOptions=moveOptions->nastepny)
                if(moveOptions->ruch.pos1 == moveOptions->ruch.pos2 && digi(conv.pos1,1) == digi(moveOptions->ruch.pos1, 1)) checker=1; //czy z generatora jest ruch np z 10 na 10 i sprawdzic czy to pionek w teju kolumnie <<to chyba juz<<<<<<

                char newPiece[1];
                int isOkey=0;
                do //wpisanie nowej figury w promocji
                {
                    printf("choose piece: Q/N/B/R\n");
                    scanf("%s", newPiece);
                    /*if(newPiece[0] == 'Q' || newPiece[0] == 'R' || newPiece[0] == 'B' || newPiece[0] == 'N')
                    {
                        isOkey=1;
                        //game.board[digi(conv.pos2, 0)][digi(conv.pos2, 1)] = newPiece[0];
                    }*/
                    if(newPiece[0] == 'Q') conv.pos1=conv.pos2; //na hetmana np. 4 na 4
                    else if(newPiece[0] == 'N') //na skoczka np.14 na 14
                    {
                        conv.pos2+=10;
                        conv.pos1=conv.pos2;
                    }
                    else if(newPiece[0] == 'B') //na gonca np.24 na 24
                    {
                        conv.pos2+=20;
                        conv.pos1=conv.pos2;
                    }
                    else if(newPiece[0] == 'R') //na wieze np.34 na 34
                    {
                        conv.pos2+=30;
                        conv.pos1=conv.pos2;
                    }
                    else
                        printf("invalid new piece\n");
                }while(isOkey=0);
            }
            else
            {
                for(; moveOptions; moveOptions=moveOptions->nastepny)
                if(moveOptions->ruch.pos1 == conv.pos1 && moveOptions->ruch.pos2 == conv.pos2) checker=1;
            }

            if(checker==0) // tu musi byæ warunek ze jezeli ruch jest niemozliwy bo gracz jest szacha albo po drodze ruchu coœ stoi
            {
                if(takeMove=="cancel") printf("Move canceled\n");
                else printf("You cant make this move\n");
                isInputOk = 0;
            }
            else
            {
                printf("alg's move processing..\n");
                isInputOk = 1;
            }
        }
        moveOptions=First; //First jest po to zeby wrocic wskaźnik moveOptions do pierwszego elementu po wykonaniu pętli szukającej ruchu
    } while(isInputOk == 0); // jezeli cos nie zostalo zmienione to powtarza wpisywanie
    //printf("\n%d\n", isInputOk);
    printf("\n%d %d\n", conv.pos1, conv.pos2);
    //moveMaker(board, conv);
    moveOptions=First;
    return conv;
}
set moveMaker(set game, int color, move ruch)
{
    // WYKONANIE RUCHOW
		if(ruch.pos1 == ruch.pos2) //promocja pionka
		{
			if(digi(ruch.pos1,0)>3)game.board[6][digi(ruch.pos1,1)] = '#';
		    else game.board[1][digi(ruch.pos1,1)] = '#';
            if(digi(ruch.pos1,0) == 0 || digi(ruch.pos1,0 == 7)) // na hetmana
            {
                if(color) game.board[0][digi(ruch.pos2,1)] = 'Q'; // biale
                else game.board[7][digi(ruch.pos1,1)] = 'q'; // czarne
            }
            else if(digi(ruch.pos1,0) == 1 || digi(ruch.pos1,0 == 6)) // na skoczka
            {
                if(color) game.board[0][digi(ruch.pos2,1)] = 'N'; // biale
                else game.board[7][digi(ruch.pos1,1)] = 'n'; // czarne
            }
            else if(digi(ruch.pos1,0) == 2 || digi(ruch.pos1,0 == 5)) // na gonca
            {
                if(color) game.board[0][digi(ruch.pos2,1)] = 'B'; // biale
                else game.board[digi(ruch.pos1,0)][digi(ruch.pos1,1)] = 'b'; // czarne
            }
            else if(digi(ruch.pos1,0) == 3 || digi(ruch.pos1,0 == 4)) // na wieze
            {
                if(color) game.board[0][digi(ruch.pos2,1)] = 'R'; // biale
                else game.board[7][digi(ruch.pos1,1)] = 'r'; // czarne
            }
		}
		else if(digi(ruch.pos1,1)-digi(ruch.pos2,1)==-2 &&
		(game.board[digi(ruch.pos1,0)][digi(ruch.pos1,1)] == 'K' || game.board[digi(ruch.pos1,0)][digi(ruch.pos1,1)] == 'k'))//roszada krotka
        {
            if(color) // biale
            {
                game.board[7][digi(ruch.pos2,1)] = 'K';
                game.board[7][digi(ruch.pos2,1)-1] = 'R';
                game.board[7][7]='#'; // czysci pole na ktorym stal krol
                game.board[7][4]='#'; // czysci pole na ktorym stala wieza
				game.movedWhiteCastle[1]=1;
            }
            else // czarne
            {
                game.board[1][digi(ruch.pos2,1)] = 'k';
                game.board[1][digi(ruch.pos2,1)-1] = 'r';
                game.board[1][7]='#';
                game.board[1][4]='#';
				game.movedBlackCastle[1]=1;
            }
        }
        else if(digi(ruch.pos1,1)-digi(ruch.pos2,1)==2 &&
		(game.board[digi(ruch.pos1,0)][digi(ruch.pos1,1)] == 'K' || game.board[digi(ruch.pos1,0)][digi(ruch.pos1,1)] == 'k'))//roszada dluga
        {
            if(color) // biale
            {
                game.board[7][digi(ruch.pos2,1)] = 'K';
                game.board[7][digi(ruch.pos2,1)+1] = 'R';
                game.board[7][0]='#';
                game.board[7][4]='#';
				game.movedWhiteCastle[1]=1;
            }
            else // czarne
            {
                game.board[0][digi(ruch.pos2,1)] = 'k';
                game.board[0][digi(ruch.pos2,1)+1] = 'r';
                game.board[0][0]='#';
                game.board[0][4]='#';
				game.movedBlackCastle[1]=1;
            }
        }
        else if((game.board[digi(ruch.pos1,0)][digi(ruch.pos1,1)] == 'P' ||
		game.board[digi(ruch.pos1,0)][digi(ruch.pos1,1)] == 'p')
		&& game.board[digi(ruch.pos2,0)][digi(ruch.pos2,1)] == '#' && digi(ruch.pos1,1)!=digi(ruch.pos2,1)) // bicie w przelocie - rozpoznanie bicia w przelocie jest wtedy gdy na pos 2 jest # (puste)
        {
            game.board[digi(ruch.pos1,0)][digi(ruch.pos1,1)] = '#'; // czysci pos1
            game.board[digi(ruch.pos1,0)][digi(ruch.pos2,1)] = '#'; // juz wiadomo ze to bicie w przelocie wiec usuwa zbijanego pionka
            if(color) game.board[digi(ruch.pos2,0)][digi(ruch.pos2,1)] = 'P';// bialy bije
            else game.board[digi(ruch.pos2,0)][digi(ruch.pos2,1)] = 'p';// czarne
        }
		else // stadardowy ruch
        {
            game.board[digi(ruch.pos2,0)][digi(ruch.pos2,1)] = game.board[digi(ruch.pos1,0)][digi(ruch.pos1,1)];
            game.board[digi(ruch.pos1,0)][digi(ruch.pos1,1)] = '#';
			if(ruch.pos1==0 && game.movedBlackCastle[0]==0 && brd(ruch.pos1,game.board)=='r')game.movedBlackCastle[0]=1;//odbieranie praw do roszady
			else if(ruch.pos1==7 && game.movedBlackCastle[2]==0 && brd(ruch.pos1,game.board)=='r')game.movedBlackCastle[2]=1;
			else if(ruch.pos1==4 && game.movedBlackCastle[1]==0 && brd(ruch.pos1,game.board)=='k')game.movedBlackCastle[1]=1;
			else if(ruch.pos1==70 && game.movedWhiteCastle[0]==0 && brd(ruch.pos1,game.board)=='R')game.movedWhiteCastle[0]=1;
			else if(ruch.pos1==77 && game.movedWhiteCastle[2]==0 && brd(ruch.pos1,game.board)=='R')game.movedWhiteCastle[2]=1;
			else if(ruch.pos1==74 && game.movedWhiteCastle[1]==0 && brd(ruch.pos1,game.board)=='K')game.movedWhiteCastle[1]=1;
			else if(brd(ruch.pos1,game.board)=='p' && abs(digi(ruch.pos1,0)-digi(ruch.pos2,0))==2)game.movedBlackPawns=digi(ruch.pos1,1);//pionki ruszają się o 2 pola
			else if(brd(ruch.pos1,game.board)=='P' && abs(digi(ruch.pos1,0)-digi(ruch.pos2,0))==2)game.movedWhitePawns=digi(ruch.pos1,1);//pionki ruszają się o 2 pola
        }
        return game;
}
void main()
{
	char board[8][8] = { "rnbqkbnr","pppppppp","########","########","########","########","PPPPPPPP","RNBQKBNR"};
	//char board[8][8] = { "RR######","########","########","########","########","###ppp##","PP######","k###K##R"};
	set game=setInit(board);
	drawBoard(game.board);
	move x={.pos1=32,.pos2=21};
	bestReturn y=engine(game,0,1);
	//printf(" %d %d %f\n",y.x.pos1,y.x.pos2,y.value);
	element *head;
	while(1)
	{
		head=generate(game,0);
		if(!head->nastepny)break;
		y=engine(game,0,1);
		game = moveMaker(game,0,y.x);
		drawBoard(game.board);
		head=generate(game,1);
		if(!head->nastepny)break;
		y.x=typeMove(game);
		//y=engine(game,1,1);
		game = moveMaker(game,1,y.x);
		drawBoard(game.board);
	}
}
/*void main()
{
	char board[8][8] = { "rnbqkbnr","pppppppp","########","########","########","########","PPPPPPPP","RNBQKBNR"};
	//char board[8][8] = { "k#######","###P####","########","########","#Q####r#","########","########","######NK"};
	set game=setInit(board);
    move playersMove;
    bestReturn checkBlacksMate, algsMove;
    int d = 0; //glebokosc drzewa
    drawBoard(game.board);
	for(int i=0;i==0;)
    {
        //gracz
        playersMove = typeMove2(game);

        checkBlacksMate = engine(game, 0, 0); //sprawdzanie przy pomocy engine czy jest koniec gry
        if(checkBlacksMate.x.pos1 == 1000)
        {
            drawBoard(game.board);
            printf("\n  WHITE WON VIA CHECKMATE\n");
            i=1;
        }
        else if(checkBlacksMate.x.pos1 == -1000)
        {
            drawBoard(game.board);
            printf("\n  BLACK WON VIA CHECKMATE\n");
            i=1;
        }
        else if(checkBlacksMate.x.pos1 == 100)
        {
            drawBoard(game.board);
            printf("\n  DRAW DUE TO STEALMATE\n");
            i=1;
        }
        else game=moveMaker(game, 1, playersMove);

        //komputer
        algsMove = engine(game, 0, d); // tez sprawdzanie czy koniec ale wykorzystane tez do wyszukania najlepszego ruchu z glebokoscia d
		printf("%d %d %f\n",algsMove.x.pos1,algsMove.x.pos2,algsMove.value);
        if(algsMove.x.pos1 == 1000)
        {
            drawBoard(game.board);
            printf("\n  WHITE WON VIA CHECKMATE\n");
            i=1;
        }
        else if(algsMove.x.pos1 == -1000)
        {
            drawBoard(game.board);
            printf("\n  BLACK WON VIA CHECKMATE\n");
            i=1;
        }
        else if(algsMove.x.pos1 == 100)
        {
            drawBoard(game.board);
            printf("\n  DRAW DUE TO STEALMATE\n");
            i=1;
        }
        else game=moveMaker(game, 0, algsMove.x);
        drawBoard(game.board);
    }
}*/
