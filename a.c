#include <stdio.h>
#include <stdlib.h>
#include "game.c"

typedef struct set {
	char board[8][8];
    int movedWhitePawns; // pamiec czy pionki sie ruszylu o dwa pola oraz krole i wieze sie ruszyly
    int movedBlackPawns;
    int movedWhiteCastle[3]; // lewa wieza, krol, prawa wieza
    int movedBlackCastle[3];
}set;
set setInit(char board[8][8])
{
	set game;
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			game.board[i][j]=board[i][j];
		}
	}

    game.movedWhitePawns = 0;
    game.movedBlackPawns = 0;
    for(int i=0; i<3; i++)
    {
        game.movedWhiteCastle[i] = 0;
        game.movedBlackCastle[i] = 0;
    }
	return game;
}

int ifEnPassant(set game, int color, move ruch) // usunac te elementy z generatora wszystko ma byc tu
{
    if(color)
    {
        if(game.movedBlackPawns == -1 || game.movedBlackPawns == -1) return 0;
        if(digi(ruch.pos1,0) != 3) return 0;
        if(game.movedBlackPawns != digi(ruch.pos2,1)) return 0; // zlamany if sprawdza czy jest niemozliwe bicie w przelocie

        char copyBoard[8][8];
        strcpy(copyBoard,game.board);
        copyBoard[digi(ruch.pos2,0)][digi(ruch.pos2,1)] = game.board[digi(ruch.pos1,0)][digi(ruch.pos1,1)]; // przesuniecie pionka ktory bije
        copyBoard[digi(ruch.pos1,0)][digi(ruch.pos1,1)] = '#';
        copyBoard[digi(ruch.pos2,0)+1][digi(ruch.pos2,1)] = '#'; // usuniecie pionka zbijanego

        drawBoard(copyBoard);

        if(isCheck(copyBoard, color)) return 0;
    }
    if(!color)
    {
        if(game.movedWhitePawns == -1 || game.movedWhitePawns == -1) return 0;
        if(digi(ruch.pos1,0) != 4) return 0;
        if(game.movedWhitePawns != digi(ruch.pos2,1)) return 0; // zlamany if sprawdza czy jest niemozliwe bicie w przelocie

        char copyBoard[8][8];
        strcpy(copyBoard,game.board);
        copyBoard[digi(ruch.pos2,0)][digi(ruch.pos2,1)] = game.board[digi(ruch.pos1,0)][digi(ruch.pos1,1)]; // przesuniecie pionka ktory bije
        copyBoard[digi(ruch.pos1,0)][digi(ruch.pos1,1)] = '#';
        copyBoard[digi(ruch.pos2,0)-1][digi(ruch.pos2,1)] = '#'; // usuniecie pionka zbijanego

        drawBoard(copyBoard);

        if(isCheck(copyBoard, color)) return 0;
    }
    return 1;
}

element* generate(set game,int color)
{
	arrType moves=init();
	move r={.pos1=0,.pos2=0};
	element* head = malloc(sizeof(element));
	*head = (element){ .ruch = r,.nastepny = NULL };
	move ruch={.pos1=-1,.pos2=-1};

    // zerowanie zmiennych do bicia w przelocie z poprzedniego ruchu -1 oznacza ze dany pionek nie ruszyl sie w poprzednim ruchu o 2 pola
    if(color) game.movedWhitePawns = -1;
    if(!color) game.movedBlackPawns = -1;
    game.movedWhitePawns = 6;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if ((game.board[i][j] == 'n'&& color==0) || (game.board[i][j] == 'N' && color==1))//skoczki
			{
				for (int k = 0; k < 8; k++)
				{
					ruch=(move){.pos1=i*10+j,.pos2=i*10+j+moves.arr[0][k]};
					if(ifLegal(color,ruch,game.board))
					{
						utworz(ruch,head);
					}
				}
			}
			if ((game.board[i][j] == 'P' && color))//biale pionki
			{
				for (int k = 0; k < 4; k++)
				{
					ruch=(move){.pos1=i*10+j,.pos2=i*10+j+moves.arr[1][k]};

					if((k==2 || k==3) && ifEnPassant(game, color, ruch)) utworz(ruch,head); // bicie w przelocie

					if(ifLegal(color,ruch,game.board))
					{
					    if(digi(ruch.pos1, 0) == 1)
						{
						    int temp = ruch.pos1;
                            ruch.pos1 = ruch.pos2;
                            utworz(ruch, head); //promocja na hetmana np. 4 do 4
                            ruch.pos1 = temp;
                            ruch.pos2 = temp;
                            utworz(ruch, head); //promocja na skoczka np. 14 do 14
							ruch.pos1 += 10;
                            ruch.pos2 += 10;
							utworz(ruch, head); //promocja na gonca np. 24 do 24
							ruch.pos1 += 10;
                            ruch.pos2 += 10;
							utworz(ruch, head); //promocja na wieze 34 do 34
						}
						else utworz(ruch,head);
                    }
				}
			}
			if ((game.board[i][j] == 'p' && !color))//czarne pionki
			{
				for (int k = 0; k < 4; k++)
				{
					ruch=(move){.pos1=i*10+j,.pos2=i*10+j+moves.arr[2][k]};

                    if((k==2 || k==3) && ifEnPassant(game, color, ruch)) utworz(ruch,head); // bicie w przelocie

					if(ifLegal(color,ruch,game.board))
					{
						if(digi(ruch.pos2, 0) == 7)
						{
						    int temp = ruch.pos1;
                            ruch.pos1 = ruch.pos2;
                            utworz(ruch, head); //promocja na hetmana np. 74 do 74
                            ruch.pos1 = temp;
                            ruch.pos2 = temp;
                            utworz(ruch, head); //promocja na skoczka np. 64 do 64
							ruch.pos1-=10;
							ruch.pos2-=10;
							utworz(ruch, head); //promocja na gonca np. 54 do 54
							ruch.pos1-=10;
							ruch.pos2-=10;
							utworz(ruch, head); //promocja na wieze np. 44 do 44
						}
						else utworz(ruch,head);
					}
				}
			}
			if ((game.board[i][j] == 'r'&& color==0) || (game.board[i][j] == 'R' && color==1))//wieze
			{
				for (int k = 1; k <= 28; k++)
				{

					ruch=(move){.pos1=i*10+j,.pos2=i*10+j+moves.arr[3][k]};
					if(digi(ruch.pos1,0)!=digi(ruch.pos1+digi(moves.arr[3][k],1),0))continue;
					if(ifLegal(color,ruch,game.board))
					{
						utworz(ruch,head);
					}
				}
			}
			if ((game.board[i][j] == 'b' && color==0) || (game.board[i][j] == 'B' && color==1)) //gonce
            {
                for(int k=1; k < 32; k++)
                {
                    ruch=(move){.pos1=i*10+j,.pos2=i*10+j+moves.arr[4][k]};
					if(abs(digi(ruch.pos1,0)-digi(ruch.pos2,0))!=abs(digi(ruch.pos1,1)-digi(ruch.pos2,1)))continue;
                    if(ifLegal(color,ruch,game.board))
					{
						utworz(ruch,head);
					}
                }
            }
			if ((game.board[i][j] == 'q' && color==0) || (game.board[i][j] == 'Q' && color==1)) //hetmany
			{
				for (int k = 1; k <= 28; k++)
				{

					ruch=(move){.pos1=i*10+j,.pos2=i*10+j+moves.arr[3][k]};
					if(digi(ruch.pos1,0)!=digi(ruch.pos1+digi(moves.arr[3][k],1),0))continue;
					if(ifLegal(color,ruch,game.board))
					{
						utworz(ruch,head);
					}
				}
				for(int k=0; k < 32; k++)
                {
                    ruch=(move){.pos1=i*10+j,.pos2=i*10+j+moves.arr[4][k]};
					if(abs(digi(ruch.pos1,0)-digi(ruch.pos2,0))!=abs(digi(ruch.pos1,1)-digi(ruch.pos2,1)))continue;
                    if(ifLegal(color,ruch,game.board))
					{
						utworz(ruch,head);
					}
                }
			}
			if ((game.board[i][j] == 'k' && color==0) || (game.board[i][j] == 'K' && color==1)) //krole
            {
                for(int k=0; k < 10; k++)
                {
                    ruch=(move){.pos1=i*10+j,.pos2=i*10+j+moves.arr[5][k]};
					if(digi(ruch.pos1,1)-digi(ruch.pos2,1)==-2)//roszada krotka
					{
						if(color && game.movedWhiteCastle[1]==0 && game.movedWhiteCastle[2]==0 && ifCastle(game.board,color,ruch))
						{
							utworz(ruch,head);
							continue;
						}
						if(!color && game.movedBlackCastle[1]==0 && game.movedBlackCastle[2]==0 && ifCastle(game.board,!color,ruch))
						{
							utworz(ruch,head);
							continue;
						}
					}
					if(digi(ruch.pos1,1)-digi(ruch.pos2,1)==2)//roszada dluga
					{
						if(color && game.movedWhiteCastle[0]==0 && game.movedWhiteCastle[1]==0 && ifCastle(game.board,color,ruch))
						{
							utworz(ruch,head);
							continue;
						}
						if(!color && game.movedBlackCastle[0]==0 && game.movedBlackCastle[1]==0 && ifCastle(game.board,!color,ruch))
						{
							utworz(ruch,head);
							continue;
						}
					}
                    if(ifLegal(color,ruch,game.board))
					{
						utworz(ruch,head);
					}
                }
            }
		}
	}
	return head;
}

char board[8][8] = {
    { '#', '#', '#', '#', '#', 'k', '#', '#' },
    { '#', '#', '#', '#', '#', '#', '#', '#' },
    { '#', '#', '#', '#', '#', '#', '#', '#' },
    { '#', '#', '#', '#', '#', '#', '#', '#' },
    { '#', '#', '#', '#', 'P', 'p', 'P', '#' },
    { '#', '#', '#', '#', '#', '#', '#', '#' },
    { '#', '#', '#', '#', '#', '#', '#', '#' },
    { '#', 'K', '#', '#', '#', 'Q', '#', '#' }
};

int gameOver(char board[8][8]) //do zrobienia w innym pliku bo z tego beda korzystac inne funkcje
{
    return 0;
}

move typeMove() //trzeba jeszcze dorobiæ ¿eby pobiera³o info z funkcji sprawdzaj¹cej czy ruch jest mo¿liwy do wykonania
{// dopisac zeby sprawdzalo czy wpisany ruch jest w liscie z tych wygenerowanych, wtedy if else z iflegalem niepotrzebny
    char kolumny[8] = {'a','b','c','d','e','f','g','h'}; //tablice pomocnicze do porownania z inputem
    char wiersze[8] = {'8', '7', '6', '5', '4', '3', '2', '1'};

    move conv; //na to skonwertowane
    conv.pos1 = NULL;
    conv.pos2 = NULL;

    printf("    it's your turn to make a move\n");

    int isInputOk; //zmienna ktora pomoga sprawdzic czy input jest poprawnie wpisany
    do
    {
        isInputOk = 1;
        conv.pos1 = NULL;
        conv.pos2 = NULL;
        char takeMove[5];
        printf("(np. g8-f6) >> ");
        scanf("%s", takeMove);

        int isOkey0=0, isOkey1=0, isOkey3=0, isOkey4=0;

        for(int i=0; i<=8 && (isOkey0 == 0 || isOkey1 == 0 || isOkey3 == 0 || isOkey4 == 0); i++) //petla leci po calej kolumny i wiersze oraz jezeli wszystko zostalo przekonwertowane poprawnie to wszyskie isOkey zmieniaja sie na 1
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

        if(isOkey0 == 0 || isOkey1 == 0 || isOkey3 == 0 || isOkey4 == 0) // jezeli cos nie zostalo zmienione to cos zostalo zle wpisane
        {
            printf("invalid input notation\n");
            isInputOk = 0;
        }
        else // jezeli zostalo wpisane dobrze to wypisuje ze teraz sie dzieje analiza planszy, zmienia isInputOk i nie robi petli jeszcze raz
        {
            if(!(ifLegal(1,conv,board))) // tu musi byæ warunek ze jezeli ruch jest niemozliwy bo gracz jest szacha albo po drodze ruchu coœ stoi
            {
                printf("You cant make this move\n");
                isInputOk = 0;
            }
            else
            {
                printf("pricessing the move..\n");
                isInputOk = 1;
            }
        }

        //printf("%d | %d\n", conv.pos1, conv.pos2);
    } while(isInputOk == 0); // jezeli cos nie zostalo zmienione to powtarza wpisywanie
    //printf("\n%d\n", isInputOk);

    moveMaker(board, conv);

    return conv;
}

void main()
{
	//char board[8][8] = { "rnbqkbnr","pppppppp","########","########","########","########","PPPPPPPP","RNBQKBNR"};
	//char board[8][8] = { "########","######B#","########","K#######","########","##b#####","########","k#######"};
	move x={.pos1=31,.pos2=20};
	drawBoard(board);

    //isCheck(board, 0);
	//zniszcz(head);
	printf("%d\n",ifLegal(0,x,board));
    printf("%d\n",isCheck(board, 0));

    set game = setInit(board);
    //drawBoard(game.board);
    printf("to tyle \n");

    element *head = malloc(sizeof(element));
	head = generate(game,0);

	showL(head->nastepny);

/*
	for(int i=0; i<8; i++) //sprawdzacz - to jest niepotrzebne póŸniej
    {
        for(int j=0; j<8; j++)
            printf(" %2d", i*10+j);
        printf("\n");
    }

    while(gameOver(board)==0)
    {
        drawBoard(board);
        move playersMove = typeMove();
    }

    if(gameOver(board) == 1) //win
        printf("white wins");
    else if(gameOver(board) == 2) //lose
        printf("black wins");
    else if(gameOver(board) == 3)
        printf("pat / draw"); //draw
*/
}
