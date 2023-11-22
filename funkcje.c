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
		str-=temp+1;
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
		str-=temp+1;
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
		str-=temp+1;
		return str;
	}

	return str;
}
int isWay(char *str)
{
	str++;
	while(*str!=NULL)
	{
		if(*(++str)==NULL)return 1;
		str--;
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
int isCheck(char board[8][8],int color)
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
	//ruchy proste
	move x1={.pos1=digi(posK,0)*10,.pos2=posK};//od lewej do krola
	move x2={.pos1=posK,.pos2=digi(posK,0)*10+7};//od krola do prawej
	move x3={.pos1=digi(posK,1),.pos2=posK};//od góry do króla
	move x4={.pos1=posK,.pos2=digi(posK,1)+70};//od krola do dolu
	//ruchy diagonalne
	int r=posK%11;
	//powyzej albo na glownej diagonali
	move x5={.pos1=r,.pos2=posK};//od lewego gornego do krola
	move x6={.pos1=posK,.pos2=(7-r)*11+r};//od krola do prawgo dolnego
	if(digi(posK,0)>digi(posK,1))//ponizej glownej diagonali
	{
		r-=11;
		x5=(move){.pos1=abs(r*10),.pos2=posK};//od lewego gornego do krola
		x6=(move){.pos1=posK,.pos2=77+r};//od krola do prawgo dolnego
	}
	
	char *str1=calloc(8,sizeof(char));
	char *str2=calloc(8,sizeof(char));
	char *str3=calloc(8,sizeof(char));
	char *str4=calloc(8,sizeof(char));
	char *str5=calloc(8,sizeof(char));
	char *str6=calloc(8,sizeof(char));
	char *str7=calloc(8,sizeof(char));
	char *str8=calloc(8,sizeof(char));
	str1=substr(x1,board);
	str2=substr(x2,board);
	str3=substr(x3,board);
	str4=substr(x4,board);
	str5=substr(x5,board);
	str6=substr(x6,board);
	printf("%s\n",str1);
	printf("%s\n",str2);
	printf("%s\n",str3);
	printf("%s\n",str4);
	printf("%s\n",str5);
	printf("%s\n",str6);
	return 0;
}
