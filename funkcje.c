int digi(int x, int i)//zwraca pierwszą współrzędną dla i=0 i drugą dla i=1 np digi(54,0)=5 i digi(54,1)=4
{
	int t1 = x % 10;
	int t2 = x - t1;
	if (i)return t1;
	return t2 / 10;
}
char brd(int x, char board[8][8])
{
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
int helper(char x)
{
	char tab[13]={'p','r','n','b','q','k','P','R','N','B','Q','K','#'};
	for(int i=0;i<13;i++)
	{
		if(x==tab[i])return 1;
	}
	return 0;
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
#include <string.h>
int isLane(char *str)
{
    for(int i=1; i < strlen(str)-1; i++)
    {
        if(str[i] != '#') return 0;
    }
    return 1;
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
	char *tempStr;
	int d=0;//kierunek po liniach
	for(int i=0;i<8;i++)
	{
		tempStr=calloc(8,sizeof(char));
		tempStr=substr(X[i],board);
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
	}
	free(tempStr);
	
	return 0;
}

int checkStrForCheck(char *strCheck, int direction) //(1 szach na bialym (-1 szach na czarnym) \ 0-straight 1-diagonal \ color k-czarny K-bialy // funkcja na podstawie tego czy nma pierwszym miejscu jest k czy K okreœla czy sprawdza szach bia³ego czy czarnego!
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

    for(int i=1; strCheck[0] == 'k' && i < size; i++) //na pierwszym miejscu string zawsze jest król, wiêc jego pomijamy ale najpierw trzeba sprawdzic ktory to stad pierwszy warunek w forze
    {
        if(strCheck[i] != '#')
        {
            if(direction == 0 && (strCheck[i] == 'Q' || strCheck[i] == 'R')) return -1;
            if(direction == 1 && (strCheck[i] == 'Q' || strCheck[i] == 'B')) return -1;
            return 0;
        }
    }
    for(int i=1; strCheck[0] == 'K' && i < size; i++)
    {
        if(strCheck[i] != '#')
        {
            if(direction == 0 && (strCheck[i] == 'q' || strCheck[i] == 'r')) return 1;
            if(direction == 1 && (strCheck[i] == 'q' || strCheck[i] == 'b')) return 1;
            return 0;
        }
    }
	return 0;
}
int ifLegal(int color, move x, char board[8][8])//color: 0-czarny, 1-bialy
{
	if(brd(x.pos2,board)=='k' || brd(x.pos2,board)=='K')return 0;//bicie krola
	if(x.pos1<0 || x.pos1>77 || digi(x.pos1,2)>7)return 0;//czy jest w szachownicy
	if(x.pos2<0 || x.pos2>77 || digi(x.pos2,2)>7)return 0;
	if((brd(x.pos1,board)=='p' && (x.pos2-x.pos1)==20) && (digi(x.pos1,0)!=1))return 0;//pionki ruszaja sie o 2 tylko jak sie nie ruszyly wczesniej
	if((brd(x.pos1,board)=='P' && (x.pos1-x.pos2)==20) && (digi(x.pos1,0)!=6))return 0;
	if(( brd(x.pos1,board)=='p' || brd(x.pos1,board)=='P') && digi(x.pos1,1)!=digi(x.pos2,1) && brd(x.pos2,board)=='#')return 0;//pionek bije tylko kiedy ma co bic
	int t=(int)brd(x.pos2,board);//czy bije kolor przeciwnika
	if((t<=90 && t!=35) && color)return 0;
	if(t>90 && !color)return 0;
	if(brd(x.pos1,board)!='n' && brd(x.pos1,board)!='N')
	{
		char *str=calloc(8,sizeof(char));//sprawdzanie czy nie ma nic pomiedzy
		str=substr(x,board);
		if(!isWay(str))
		{
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
void moveMaker(char board[8][8], move thisMove) //funkcja to wykonania ruchu ze sprawdzaniem czy jest mozliwy NIEKOMPLETNA
{
    //if(isLegal(board, thisMove));

            board[digi(thisMove.pos2, 0)][digi(thisMove.pos2, 1)] = board[digi(thisMove.pos1, 0)][digi(thisMove.pos1, 1)];
            char placedPiece = board[digi(thisMove.pos2, 0)][digi(thisMove.pos2, 1)];
            board[digi(thisMove.pos1, 0)][digi(thisMove.pos1, 1)] = '#';

    if(placedPiece == 'P') // dla gracza wraz z pobraniem wyboru figuty
    {
        char newPiece[1];
        int isOkey = 1;
        do
        {
            printf("choose piece: Q/R/B/N\n");
            scanf("%s", newPiece);
            if(newPiece[0] == 'Q' || newPiece[0] == 'R' || newPiece[0] == 'B' || newPiece[0] == 'N')
            {
                isOkey=1;
                board[digi(thisMove.pos2, 0)][digi(thisMove.pos2, 1)] = newPiece[0];
            }
            else
            {
                isOkey = 0;
                printf("invalid new piece\n");
            }
        } while(isOkey == 0);
    }
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
