#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void drawBoard(char board[8][8])
{
    for(int i=0; i < 8; i++)
    {
        printf(" +---+---+---+---+---+---+---+---+\n");
        printf("%d", 8-i);
        for(int j=0; j<8; j++)
        {
            if(j!=0)
                printf(" ");
            printf("| ");
            if(board[i][j] != '#')
                printf("%c", board[i][j]);
            else
                printf(" ");
        }

        printf(" | \n");
    }
    printf(" +---+---+---+---+---+---+---+---+\n");
    printf("   A   B   C   D   E   F   G   H\n");
}
typedef struct move {
	int pos1;
	int pos2;
}move;
typedef struct element {
	move ruch;
	struct element* nastepny;
}element;
element* utworz(move ruch, element* head)
{
	if (head)
	{
		if (head->nastepny)
		{
			return utworz(ruch, head->nastepny);
		}
		else
		{
			head->nastepny = malloc(sizeof(element));
			*(head->nastepny) = (element){ .ruch = ruch,.nastepny = NULL };
			return head->nastepny;
		}
	}
	else
	{
		element* ptr = malloc(sizeof(element));
		*ptr = (element){ .ruch = ruch,.nastepny = NULL };
		return ptr;
	}
}
/*void zniszcz(element** head)
{
	if(!*head)return;
	zniszcz(&((*head)->nastepny));
	free(*head);
	free(head);
}*/
void zniszcz(element* head)
{
    if (head)
    {
        zniszcz(head->nastepny);
        free(head);
    }
}

void showL(element* head)
{
	while(head!=NULL)
	{
		printf("z %d na %d\n",head->ruch.pos1,head->ruch.pos2);
		head=head->nastepny;
	}
}
typedef struct arrType
{
	int arr[6][32];
}arrType;

arrType init()
{
	arrType moves;
	//knight
	moves.arr[0][0] = -21;
	moves.arr[0][1] = +21;
	moves.arr[0][2] = +19;
	moves.arr[0][3] = -19;
	moves.arr[0][4] = -12;
	moves.arr[0][5] = +12;
	moves.arr[0][6] = +8;
	moves.arr[0][7] = -8;
	//Pawn(w)
	moves.arr[1][0] = -10;
	moves.arr[1][1] = -20;
	moves.arr[1][2] = -11;
	moves.arr[1][3] = -9;
	//pawn(b)
	moves.arr[2][0] = 10;
	moves.arr[2][1] = 20;
	moves.arr[2][2] = 11;
	moves.arr[2][3] = 9;
	//rook
	for (int i = 4; i < 32; i+=4)
	{
		moves.arr[3][i-3] = (int)(i / 4);
		moves.arr[3][i-2] = (int)((i / 4)*10);
		moves.arr[3][i-1] = (int)(-(i / 4)*10);
		moves.arr[3][i] = (int)(-(i / 4));
	}
	//bishop
	for (int i = 4; i < 32; i += 4)
	{
		moves.arr[4][i-3] = (i / 4) + (i / 4) * 10;
		moves.arr[4][i-2] = -(i / 4) + (i / 4) * 10;
		moves.arr[4][i-1] = (i / 4) - (i / 4) * 10;
		moves.arr[4][i] = -(i / 4) - (i / 4) * 10;
	}
	//king
	moves.arr[5][0] = 9;
	moves.arr[5][1] = 10;
	moves.arr[5][2] = 11;
	moves.arr[5][3] = -1;
	moves.arr[5][4] = 1;
	moves.arr[5][5] = -11;
	moves.arr[5][6] = -10;
	moves.arr[5][7] = -9;
	moves.arr[5][8] = -2;
	moves.arr[5][9] = 2;
	return moves;
}

int evaluate(char board[8][8])
{
	int value = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			switch (board[i][j])
			{
			case 'N':
				value += 3;
				break;
			case 'Q':
				value += 9;
				break;
			case 'P':
				value += 1;
				break;
			case 'B':
				value += 3;
				break;
			case 'R':
				value += 5;
				break;
			case 'n':
				value -= 3;
				break;
			case 'q':
				value -= 9;
				break;
			case 'p':
				value -= 1;
				break;
			case 'b':
				value -= 3;
				break;
			case 'r':
				value -= 5;
				break;
			}
		}
	}
	return value;
}
int digi(int x, int i)//zwraca pierwszą współrzędną dla i=0 i drugą dla i=1 np digi(54,0)=5 i digi(54,1)=4
{
	int t1 = x % 10;
	int t2 = x - t1;
	if (i)return t1;
	return t2 / 10;
}
int helper(char x)
{
	char tab[13]={'p','r','n','b','q','k','P','R','N','B','Q','K','#'};
	for(int i=0;i<13;i++)
	{
		if(x==tab[i])return 1;
	}
	return 0;
}
char brd(int x, char board[8][8])
{
	//printf("%d:%c ",x,board[digi(x,0)][digi(x,1)]);
	if(x>77||x<0)return '\0';
	return board[digi(x,0)][digi(x,1)];
}
char *substr(move x,char board[8][8])
{

	int temp=abs(digi(x.pos1,0)-digi(x.pos2,0));//przesuniecie na wierszach
	if(abs(digi(x.pos1,1)-digi(x.pos2,1))>temp)temp=abs(digi(x.pos1,1)-digi(x.pos2,1));//przesuniecie na kolumnach
	char *str=calloc(9,sizeof(char));
	if(digi(x.pos1,0)==digi(x.pos2,0))//ruch w ramach jednego wiersza
	{
		int pos=x.pos1;
		if(digi(x.pos1,1)>digi(x.pos2,1))pos=x.pos2;
		for(int i=0;i<=temp;i++)
		{
			*str=brd(pos+i,board);
			str++;
		}
		*str='\0';
		str-=temp+1;
		return str;
	}
	if(digi(x.pos1,1)==digi(x.pos2,1))//ruch w ramach jednej kolumny
	{
		int pos=x.pos1;
		if(digi(x.pos1,0)>digi(x.pos2,0))pos=x.pos2;
		for(int i=0;i<=temp;i++)
		{
			*str=brd(pos+i*10,board);
			str++;
		}
		*str='\0';
		str-=temp+1;
		return str;
	}
	if(digi(x.pos1,1)!=digi(x.pos2,1) && digi(x.pos1,0)!=digi(x.pos2,0))//ruch po diagonali
	{
		int pos=x.pos1;
		int pos2=x.pos2;
		if(digi(x.pos1,0)>digi(x.pos2,0))
		{
			pos=x.pos2;
			pos2=x.pos1;
		}
		if(digi(pos,1)<digi(pos2,1))//ruch od lewego gornego do prawego dolnego
		{
			for(int i=0;i<=temp;i++)
			{
				*str=brd(pos+i*10+i,board);
				str++;
			}
			*str='\0';
			str-=temp+1;
			return str;
		}
		else{//ruch od prawego gornego do lewego dolnego
			for(int i=0;i<=temp;i++)
			{
				*str=brd(pos+i*10-i,board);
				str++;
			}
			*str='\0';
			str-=temp+1;
			return str;
		}
	}

	return str;
}

int isWay(char *str)
{
	int l=strlen(str);
	if(*str=='#')//jezeli str jest odwrocony to wstawia # na koniec
	{
		int counter=0;
		while(helper(*str))
		{
			str++;
			counter++;
		}
		str--;
		*str='#';
		str-=(counter-1);
	}
	str++;
	for(int i=0;i<l-2;i++)
	{
		if(*str!='#')return 0;
		str++;
	}
	return 1;
}
int checkStrForCheck(char *strCheck, int direction) //(1 szach na bialym (-1 szach na czarnym) \ 0-straight 1-diagonal \ color k-czarny K-bialy // funkcja na podstawie tego czy nma pierwszym miejscu jest k czy K określa czy sprawdza szach białego czy czarnego!
{
    int size = strlen(strCheck);

    if(strCheck[size-1] == 'k' || strCheck[size-1] == 'K') //odwracanie stringa jezeli król nie jest na pierwszym msc tylko ostatnim
    {
        for(int i = 0, j = size-1; i < j ; i++, j--)
        {
            char bufor = strCheck[i];
            strCheck[i] = strCheck[j];
            strCheck[j] = bufor;
        }
    }

    for(int i=1; strCheck[0] == 'k' && i < size; i++) //na pierwszym miejscu string zawsze jest król, więc jego pomijamy ale najpierw trzeba sprawdzic ktory to stad pierwszy warunek w forze
    {
        if(strCheck[i] != '#' )
        {
            if(direction == 0 && (strCheck[i] == 'Q' || strCheck[i] == 'R')) return -1;
            if(direction == 1 && (strCheck[i] == 'Q' || strCheck[i] == 'B')) return -1;
            return 0;
        }
    }
    for(int i=1; strCheck[0] == 'K' && i < size; i++)
    {
        if(strCheck[i] != '#' )
        {
            if(direction == 0 && (strCheck[i] == 'q' || strCheck[i] == 'r')) return 1;
            if(direction == 1 && (strCheck[i] == 'q' || strCheck[i] == 'b')) return 1;
            return 0;
        }
    }
	return 0;
}
int isCheck(char board[8][8],int color)//1- jest szach, 0- nie ma szacha
{
	int posK=0;
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			if(board[i][j]=='K' && color)posK=i*10+j;
			if(board[i][j]=='k' && !color)posK=i*10+j;
		}
	}
	//ruchy skoczka
	int Nmoves[8]={-21,-19,-12,-8,8,12,19,21};
	for(int i=0;i<8;i++)
	{
		if((posK+Nmoves[i]>=0 && posK+Nmoves[i]<=77) && (brd(posK+Nmoves[i],board)=='N' && !color))return 1;
		if((posK+Nmoves[i]>=0 && posK+Nmoves[i]<=77) && (brd(posK+Nmoves[i],board)=='n' && color))return 1;
	}
	//ruchy pionkow
	if(color)
	{
		if((posK-11>=0 && posK-11<=77) && brd(posK-11,board)=='p')return 1;
		if((posK-9>=0 && posK-9<=77) && brd(posK-9,board)=='p')return 1;
	}
	else{
		if((posK+11>=0 && posK+11<=77) && brd(posK+11,board)=='P')return 1;
		if((posK+9>=0 && posK+9<=77) && brd(posK+9,board)=='P')return 1;
	}

	//ruchy proste
	move x1={.pos1=digi(posK,0)*10,.pos2=posK};//od lewej do krola
	move x2={.pos1=posK,.pos2=digi(posK,0)*10+7};//od krola do prawej
	move x3={.pos1=digi(posK,1),.pos2=posK};//od góry do króla
	move x4={.pos1=posK,.pos2=digi(posK,1)+70};//od krola do dolu
	//ruchy diagonalne
	int r=posK%11;
	//powyzej albo na glownej diagonali 0-77
	move x5={.pos1=r,.pos2=posK};//od lewego gornego do krola
	move x6={.pos1=posK,.pos2=(7-r)*11+r};//od krola do prawgo dolnego
	if(digi(posK,0)>digi(posK,1))//ponizej glownej diagonali 0-77
	{
		r-=11;
		x5=(move){.pos1=abs(r*10),.pos2=posK};//od lewego gornego do krola
		x6=(move){.pos1=posK,.pos2=77+r};//od krola do prawgo dolnego
	}
	//powyzej albo na glownej diagonali 7-70
	int r2=posK%9;
	move x7={.pos1=r2,.pos2=posK};//od prawego gornego do krola
	move x8={.pos1=posK,.pos2=r2*10};//od krola do lewego dolnego
	if((digi(posK,0)+digi(posK,1))>7)//ponizej glownej diagonali 7-70
	{
		if(r2==8)r2=-1;
		x7=(move){.pos1=(r2+2)*10+7,.pos2=posK};//od prawego gornego do krola
		x8=(move){.pos1=posK,.pos2=72+r2};//od krola do lewego dolnego
	}
	move X[8]={x1,x2,x3,x4,x5,x6,x7,x8};
	//char *tempStr=substr(X[i],board);
	int d=0;//kierunek po liniach
	for(int i=0;i<8;i++)
	{
		//printf("%d %d\n",X[i].pos1,X[i].pos2);
		//tempStr=calloc(9,sizeof(char));
		//tempStr=substr(X[i],board);
		char *tempStr=substr(X[i],board);
		if(i>3)d=1;//kierunek po diagonalach
		if(checkStrForCheck(tempStr,d)==1 && color)
		{
			free(tempStr);
			return 1;
		}
		if(checkStrForCheck(tempStr,d)==-1 && !color)
		{
			free(tempStr);
			return 1;
		}
		free(tempStr);
	}


	return 0;
}

int ifLegal(int color, move x, char board[8][8])//color: 0-czarny, 1-bialy
{
	if(brd(x.pos2,board)=='k' || brd(x.pos2,board)=='K')return 0;//bicie krola
	if(x.pos1<0 || x.pos1>77 || digi(x.pos1,2)>7)return 0;//czy jest w szachownicy
	if(x.pos2<0 || x.pos2>77 || digi(x.pos2,2)>7)return 0;
	if((brd(x.pos1,board)=='k' || brd(x.pos1,board)=='K')&& abs(digi(x.pos2,1)-digi(x.pos1,1))==2)return 0;
	if((brd(x.pos1,board)=='p' && (x.pos2-x.pos1)==20) && (digi(x.pos1,0)!=1))return 0;//pionki ruszaja sie o 2 tylko jak sie nie ruszyly wczesniej
	if((brd(x.pos1,board)=='P' && (x.pos1-x.pos2)==20) && (digi(x.pos1,0)!=6))return 0;
	if(( brd(x.pos1,board)=='p' || brd(x.pos1,board)=='P') && digi(x.pos1,1)!=digi(x.pos2,1) && brd(x.pos2,board)=='#')return 0;//pionek bije tylko kiedy ma co bic
	if(( brd(x.pos1,board)=='p' || brd(x.pos1,board)=='P') && digi(x.pos1,1)==digi(x.pos2,1) && brd(x.pos2,board)!='#')return 0;
	int t=(int)brd(x.pos2,board);//czy bije kolor przeciwnika
	if((t<=90 && t!=35) && color)return 0;
	if(t>90 && !color)return 0;
	//printf("rncj");
	if(brd(x.pos1,board)!='n' && brd(x.pos1,board)!='N')
	{
		char *str=calloc(8,sizeof(char));//sprawdzanie czy nie ma nic pomiedzy
		str=substr(x,board);
		if(!isWay(str))
		{
			//printf("%s",str);
			free(str);
			return 0;
		}
		free(str);
	}

	char copyBoard[8][8];
	strcpy(copyBoard,board);
	copyBoard[digi(x.pos2,0)][digi(x.pos2,1)]=copyBoard[digi(x.pos1,0)][digi(x.pos1,1)];//sprawdzanie czy nie ma szacha po wykonaniu posuniecia
	copyBoard[digi(x.pos1,0)][digi(x.pos1,1)]='#';
	if(isCheck(copyBoard,color))
	{
		return 0;
	}
	return 1;
}
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
        game.movedWhiteCastle[i] = 1;//0 nie ruszone, 1 ruszone
        game.movedBlackCastle[i] = 1;
    }
	return game;
}
int ifCastle(char board[8][8],int color,move x)//0 nie mozna roszady, 1- mozna roszade
{
	if(x.pos1<x.pos2)//krotka roszada
	{
		char *str=calloc(8,sizeof(char));
		str=substr(x,board);
		if(!isWay(str))
		{
		    free(str);
		    return 0;
		}
		if(isCheck(board,color))
        {
		    free(str);
		    return 0;
		}
		char copyBoard[8][8];
		strcpy(copyBoard,board);
		copyBoard[digi(x.pos1,0)][digi(x.pos1,1)+1]=copyBoard[digi(x.pos1,0)][digi(x.pos1,1)];
		copyBoard[digi(x.pos1,0)][digi(x.pos1,1)]='#';
		if(isCheck(copyBoard,color))
		{
		    free(str);
		    return 0;
		}
		copyBoard[digi(x.pos2,0)][digi(x.pos2,1)]=copyBoard[digi(x.pos1,0)][digi(x.pos1,1)+1];
		copyBoard[digi(x.pos1,0)][digi(x.pos1,1)+1]='#';
		if(isCheck(copyBoard,color))
		{
		    free(str);
		    return 0;
		}
		free(str);
		return 1;
	}
	else//dluga roszada
	{
		char *str=calloc(8,sizeof(char));
		x.pos2--;
		str=substr(x,board);
		if(!isWay(str))
        {
		    free(str);
		    return 0;
		}
		if(isCheck(board,color))
		{
		    free(str);
		    return 0;
		}
		char copyBoard[8][8];
		strcpy(copyBoard,board);
		copyBoard[digi(x.pos1,0)][digi(x.pos1,1)-1]=copyBoard[digi(x.pos1,0)][digi(x.pos1,1)];
		copyBoard[digi(x.pos1,0)][digi(x.pos1,1)]='#';
		if(isCheck(copyBoard,color))
		{
		    free(str);
		    return 0;
		}
		copyBoard[digi(x.pos1,0)][digi(x.pos1,1)-2]=copyBoard[digi(x.pos1,0)][digi(x.pos1,1)-1];
		copyBoard[digi(x.pos1,0)][digi(x.pos1,1)-1]='#';
		if(isCheck(copyBoard,color))
		{
		    free(str);
		    return 0;
		}
		free(str);
		return 1;
	}
}
int ifEnPassant(set game, int color, move ruch)
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
        if(isCheck(copyBoard, color)) return 0;//czy nie ma szacha
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
        if(isCheck(copyBoard, color)) return 0;//czy nie ma szacha
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

    // zerowanie zmiennych do bicia w przelocie z poprzedniego ruchu -1 oznacza ze zaden pionek danego koloru nie ruszyl sie w poprzednim ruchu o 2 pola
    if(color) game.movedWhitePawns = -1;
    if(!color) game.movedBlackPawns = -1;
    game.movedBlackPawns = 6;

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
					if((k==2 || k==3) && brd(ruch.pos2,game.board) == '#' && ifEnPassant(game, color, ruch))  // bicie w przelocie
					{
						utworz(ruch,head);
						continue;
					}

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

                    if((k==2 || k==3) && brd(ruch.pos2,game.board) == '#' && ifEnPassant(game, color, ruch))  // bicie w przelocie
					{
						utworz(ruch,head);
						continue;
					}

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

typedef struct bestReturn {
    move x;
    int value;
}bestReturn;
bestReturn engine(set game,int color,int d)//d glebokosc
{
	bestReturn best;
	bestReturn current;
	current.value=0;
	best.value=0;
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
	            best.value=1000;
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
					zniszcz(head);
	                return best;
					}
				}
	    else//pat
	    {
	        best.x.pos1=100;
	        best.x.pos2=100;
			best.value=0;
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
		    copyGame.board[digi(temp.pos1,0)][digi(temp.pos1,1)] = '#';
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
						best.value=1000;

	                }//czarne matuja bialego
					else{
						best.value=-1000;
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
						best.value=-1000;

	                }//biale matuja czarnego
					else{
						best.value=1000;
					}
					zniszcz(head);
                    zniszcz(head2);
	                return best;
				}
	            else//pat
	            {
	                best.x=temp;
					best.value=0;
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
		    copyGame2.board[digi(temp2.pos1,0)][digi(temp2.pos1,1)] = '#';
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
				if(!counter)current=t;
            }
            else
            {
                int tempValue=evaluate(copyGame2.board);
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
			//printf("%d \n",current.value);
			counter++;
		//copy.board[digi(temp2.pos1,0)][digi(temp2.pos1,1)] = game.board[digi(temp2.pos2,0)][digi(temp2.pos2,1)];//cofniecie posuniecia
		//game.board[digi(temp2.pos2,0)][digi(temp2.pos2,1)] = rev;
		}
		//game.board[digi(temp.pos1,0)][digi(temp.pos1,1)] = game.board[digi(temp.pos2,0)][digi(temp.pos2,1)];//cofniecie posuniecia
		//game.board[digi(temp.pos2,0)][digi(temp.pos2,1)] = rev1;

	   //printf("## %d %d %d\n",current.x.pos1,current.x.pos2,current.value);
	   if(current.value>best.value && color) best=current;
       if(current.value<best.value && !color) best=current;
       zniszcz(head2);
	}
	zniszcz(head);
	//printf("%d %d %d\n",best.x.pos1,best.x.pos2,best.value);
	return best;
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
		    game.board[digi(ruch.pos1,0)][digi(ruch.pos1,1)] = '#';
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
	//char board[8][8] = { "k#######","###P####","########","########","#Q####r#","########","########","######NK"};
	set game=setInit(board);

    move playersMove;
    bestReturn checkBlacksMat, algsMove;
    int d = 1; //glebokosc drzewa
    drawBoard(game.board);
	for(int i=0;i==0;)
    {
        //gracz
        playersMove = typeMove(game);

        checkBlacksMat = engine(game, 0, 0); //sprawdzanie przy pomocy engine czy jest koniec gry
        if(checkBlacksMat.x.pos1 == 1000)
        {
            drawBoard(game.board);
            printf("\n  WHITE WON VIA CHECKMATE\n");
            i=1;
        }
        else if(checkBlacksMat.x.pos1 == -1000)
        {
            drawBoard(game.board);
            printf("\n  BLACK WON VIA CHECKMATE\n");
            i=1;
        }
        else if(checkBlacksMat.x.pos1 == 100)
        {
            drawBoard(game.board);
            printf("\n  DRAW DUE TO STEALMATE\n");
            i=1;
        }
        else game=moveMaker(game, 1, playersMove);

        //komputer
        algsMove = engine(game, 0, d); // tez sprawdzanie czy koniec ale wykorzystane tez do wyszukania najlepszego ruchu z glebokoscia d
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
}
