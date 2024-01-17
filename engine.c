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
		(copyGame.board[digi(temp.pos1,0)][temp.pos1,1] == 'K' || copyGame.board[digi(temp.pos1,0)][temp.pos1,1] == 'k'))//roszada krotka
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
		(copyGame.board[digi(temp.pos1,0)][temp.pos1,1] == 'K' || copyGame.board[digi(temp.pos1,0)][temp.pos1,1] == 'k'))//roszada dluga
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
        else if((copyGame.board[digi(temp.pos1,0)][temp.pos1,1] == 'P' || 
		copyGame.board[digi(temp.pos1,0)][temp.pos1,1] == 'p') 
		&& copyGame.board[digi(temp.pos1,0)][temp.pos1,1] == '#') // bicie w przelocie - rozpoznanie bicia w przelocie jest wtedy gdy na pos 2 jest # (puste)
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
		(copyGame2.board[digi(temp2.pos1,0)][temp2.pos1,1] == 'K' || copyGame2.board[digi(temp2.pos1,0)][temp2.pos1,1] == 'k'))//roszada krotka
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
		(copyGame2.board[digi(temp2.pos1,0)][temp2.pos1,1] == 'K' || copyGame2.board[digi(temp2.pos1,0)][temp2.pos1,1] == 'k'))//roszada dluga
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
        else if((copyGame2.board[digi(temp2.pos1,0)][temp2.pos1,1] == 'P' || 
		copyGame2.board[digi(temp2.pos1,0)][temp2.pos1,1] == 'p') 
		&& copyGame2.board[digi(temp2.pos1,0)][temp2.pos1,1] == '#') // bicie w przelocie - rozpoznanie bicia w przelocie jest wtedy gdy na pos 2 jest # (puste)
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
            drawBoard(copyGame2.board);
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
void main()
{
	//char board[8][8] = { "rnbqkbnr","pppppppp","########","########","########","########","PPPPPPPP","RNBQKBNR"};
	char board[8][8] = { "##b#k###","########","R#######","########","########","########","########","#######K"};
	move x={.pos1=74,.pos2=72};
	set game=setInit(board);
	drawBoard(game.board);
	printf("helloworld");
	bestReturn y=engine(game,0,2);
	printf("%d %d\n",y.x.pos1,y.x.pos2);
	//printf("%d\n",ifCastle(game.board,1,x));
	//drawBoard(game.board);
	/*element *head = malloc(sizeof(element));
	head = generate(game,1);
	showL(head->nastepny);
	zniszcz(head);*/
}
