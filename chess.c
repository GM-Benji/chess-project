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
    int counter2=0;
	for(;head;head=head->nastepny)
	{
		move temp=head->ruch;
		set copyGame=game;
        // WYKONANIE RUCHOW
		copyGame=moveMaker(copyGame,temp);
        element *head2 = malloc(sizeof(element));
	    head2 = generate(copyGame,!color);
		if(head2->nastepny==NULL)//nie ma ruchow w pozycji
	        {
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
			set copyGame2=moveMaker(copyGame,temp2);
            if(d)
            {
                bestReturn t=engine(copyGame2,color,d-1);
                if(!counter)
				{
					t.x=temp;
					current=t;
				}
                if(current.value<t.value && !color)
                {
                    current.value=t.value;
                }
				else if(current.value>t.value && color)
                {
                    current.value=t.value;
                }
            }
            else
            {
                double tempValue=evaluate(copyGame2);
                if(!counter)current.value=tempValue;
                if(current.value<tempValue && !color)
                {
                    current.value=tempValue;
                }
				else if(current.value>tempValue && color)
                {
                    current.value=tempValue;
                }
			}
			counter++;
		}
       if(!counter2)best=current;
	   if(current.value>best.value && color) best=current;
       else if(current.value<best.value && !color) best=current;
       zniszcz(head2);
       counter2++;
	}
	zniszcz(head);
	return best;
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
			conv.promotion=promotion[0];
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
			conv.promotion=promotion[0];
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

void main()
{
	char board[8][8] = { "rnbqkbnr","pppppppp","########","########","########","########","PPPPPPPP","RNBQKBNR"};
	//char board[8][8] = { "RR######","########","########","########","########","###ppp##","PP######","k###K##R"};
	set game=setInit(board);
	drawBoard(game.board);
	move x={.pos1=32,.pos2=21};
	bestReturn y=engine(game,0,1);
	bestReturn b=engine(game,0,1);
	//printf(" %d %d %f\n",y.x.pos1,y.x.pos2,y.value);
	element *head;
	while(1)
	{
		head=generate(game,0);
		if(!head->nastepny)break;
        b=engine(game,0,1);
		game = moveMaker(game,b.x);
		drawBoard(game.board);
		head=generate(game,1);
		if(!head->nastepny)break;
		y.x=typeMove2(game);
		//y=engine(game,1,1);
		game = moveMaker(game,y.x);
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
