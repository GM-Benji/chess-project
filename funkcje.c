int digi(int x, int i)//zwraca pierwszą współrzędną dla i=0 i drugą dla i=1 np digi(54,0)=5 i digi(54,1)=4
{
	int t1 = x % 10;
	int t2 = x - t1;
	if (i)return t1;
	return t2 / 10;
}
char brd(int x, char board[8][8])
{
	if(x>77||x<0)return ' ';
	return board[digi(x,0)][digi(x,1)];
}

char *substr(move x,char board[8][8])
{
	int temp=abs(digi(x.pos1,0)-digi(x.pos2,0));//przesuniecie na wierszach
	if(abs(digi(x.pos1,1)-digi(x.pos2,1))>temp)temp=abs(digi(x.pos1,1)-digi(x.pos2,1));//przesuniecie na kolumnach
	char *str=calloc(8,sizeof(char));
	
	if(digi(x.pos1,0)==digi(x.pos2,0))//ruch w ramach jednego wiersza
	{
		
		int pos=x.pos1;
		if(digi(x.pos1,1)>digi(x.pos2,1))pos=x.pos2;
		for(int i=0;i<temp;i++)
		{
			*str=brd(pos+i,board);
			
			str++;
		}
		str-=temp;
		return str;
	}
	if(digi(x.pos1,1)==digi(x.pos2,1))//ruch w ramach jednej kolumny
	{
		int pos=x.pos1;
		if(digi(x.pos1,0)>digi(x.pos2,0))pos=x.pos2;
		for(int i=0;i<temp;i++)
		{
			*str=brd(pos+i*10,board);
			str++;
		}
		str-=temp;
		return str;
	}
	if(digi(x.pos1,1)!=digi(x.pos2,1) && digi(x.pos1,0)!=digi(x.pos2,0))//ruch po diagonali
	{
		int pos=x.pos1;
		if(digi(x.pos1,0)>digi(x.pos2,0))pos=x.pos2;
		for(int i=0;i<temp;i++)
		{
			*str=brd(pos+i*10+i,board);
			str++;
		}
		str-=temp;
		return str;
	}

	return str;
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
