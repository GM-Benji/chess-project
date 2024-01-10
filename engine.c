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
	for(;head;head=head->nastepny)
	{
		move temp=head->ruch;
		char rev1=game.board[digi(temp.pos2,0)][digi(temp.pos2,1)];

        // WYKONANIE RUCHOW
		if(temp.pos1 == temp.pos2) //promocja pionka
		{
		    game.board[digi(temp.pos1,0)][digi(temp.pos1,1)] = '#';
            if(digi(temp.pos1,0) == 0 || digi(temp.pos1,0 == 7)) // na hetmana
            {
                if(color) game.board[0][digi(temp.pos2,1)] = 'Q'; // biale
                else game.board[7][digi(temp.pos1,1)] = 'q'; // czarne
            }
            else if(digi(temp.pos1,0) == 1 || digi(temp.pos1,0 == 6)) // na skoczka
            {
                if(color) game.board[0][digi(temp.pos2,1)] = 'N'; // biale
                else game.board[7][digi(temp.pos1,1)] = 'n'; // czarne
            }
            else if(digi(temp.pos1,0) == 2 || digi(temp.pos1,0 == 5)) // na gonca
            {
                if(color) game.board[0][digi(temp.pos2,1)] = 'B'; // biale
                else game.board[digi(temp.pos1,0)][digi(temp.pos1,1)] = 'b'; // czarne
            }
            else if(digi(temp.pos1,0) == 3 || digi(temp.pos1,0 == 4)) // na wieze
            {
                if(color) game.board[0][digi(temp.pos2,1)] = 'R'; // biale
                else game.board[7][digi(temp.pos1,1)] = 'r'; // czarne
            }
		}
		else if(digi(temp.pos1,1)-digi(temp.pos2,1)==-2 && (game.board[digi(temp.pos1,0)][temp.pos1,1] == 'K' || game.board[digi(temp.pos1,0)][temp.pos1,1] == 'k')//roszada krotka
        {
            if(color) // biale
            {
                game.board[7][digi(temp.pos2,1)] = 'K';
                game.board[7][digi(temp.pos2,1)-1] = 'R';
                game.board[7][7]='#'; // czysci pole na ktorym stal krol
                game.board[7][4]='#'; // czysci pole na ktorym stala wieza
            }
            else // czarne
            {
                game.board[1][digi(temp.pos2,1)] = 'K';
                game.board[1][digi(temp.pos2,1)-1] = 'R';
                game.board[1][7]='#';
                game.board[1][4]='#';
            }
        }
        else if(digi(temp.pos1,1)-digi(temp.pos2,1)==2 && (game.board[digi(temp.pos1,0)][temp.pos1,1] == 'K' || game.board[digi(temp.pos1,0)][temp.pos1,1] == 'k')//roszada dluga
        {
            if(color) // biale
            {
                game.board[7][digi(temp.pos2,1)] = 'K';
                game.board[7][digi(temp.pos2,1)+1] = 'R';
                game.board[7][0]='#';
                game.board[7][4]='#';
            }
            else // czarne
            {
                game.board[0][digi(temp.pos2,1)] = 'k';
                game.board[0][digi(temp.pos2,1)+1] = 'r';
                game.board[0][0]='#';
                game.board[0][4]='#';
            }
        }
        else if((game.board[digi(temp.pos1,0)][temp.pos1,1] == 'P' || game.board[digi(temp.pos1,0)][temp.pos1,1] == 'p') && game.board[digi(temp.pos1,0)][temp.pos1,1] == '#') // bicie w przelocie - rozpoznanie bicia w przelocie jest wtedy gdy na pos 2 jest # (puste)
        {
            game.board[digi(temp.pos1,0)][digi(temp.pos1,1)] = '#'; // czysci pos1
            game.board[digi(temp.pos2,0)][digi(temp.pos1,1)] = '#'; // juz wiadomo ze to bicie w przelocie wiec usuwa zbijanego pionka
            if(color) game.board[digi(temp.pos2,0)][digi(temp.pos2,1)] = 'P';// bialy bije
            else game.board[digi(temp.pos2,0)][digi(temp.pos2,1)] = 'p'// czarne
        }
		else // stadardowy ruch
        {
            game.board[digi(temp.pos2,0)][digi(temp.pos2,1)] = game.board[digi(temp.pos1,0)][digi(temp.pos1,1)];
            game.board[digi(temp.pos1,0)][digi(temp.pos1,1)] = '#';
        }

        element *head2 = malloc(sizeof(element));
	    head2 = generate(game,!color);
		//showL(head2->nastepny);
		if(head2->nastepny==NULL)
	        {
				//printf("%d ",d);
	            if(isCheck(game.board,!color))
	            {
	                if(color)//biale matuja czarnego
	                {
	                    best.x.pos1=1000;
	                    best.x.pos2=1000;
					zniszcz(head);
                    zniszcz(head2);
	                    return best;
	                }//czarne matuja bialego
	            }
				else if(isCheck(game.board,color))
				{
					if(!color)
					{
					best.x.pos1=-1000;
	                best.x.pos2=-1000;
					zniszcz(head);
                    zniszcz(head2);
	                return best;
					}
				}
	            else//pat
	            {
	                best.x.pos1=100;
	                best.x.pos2=100;
					best.value=0;
			    	zniszcz(head);
                    zniszcz(head2);
	                return best;
	            }
	        }
		head2=head2->nastepny;
		current.x=temp;
	    for(;head2;head2=head2->nastepny)
	    {
            move temp2=head2->ruch;
            //printf("%d %d\n",temp.pos1,temp.pos2);
            char rev=game.board[digi(temp2.pos2,0)][digi(temp2.pos2,1)];
            game.board[digi(temp2.pos2,0)][digi(temp2.pos2,1)] = game.board[digi(temp2.pos1,0)][digi(temp2.pos1,1)]; // stadardowy ruch
            game.board[digi(temp2.pos1,0)][digi(temp2.pos1,1)] = '#';
            //drawBoard(game.board);
            if(d)
            {
                bestReturn t=engine(game,color,d-1);
                if(current.value<t.value && !color)
                {
                    current.value=t.value;
                }
                if(current.value>t.value && color)
                {
                    current.value=t.value;
                }
            }
            else
            {
                int tempValue=evaluate(game.board);
                if(current.value<tempValue && !color)
                {
                    current.value=tempValue;
                }
                if(current.value>tempValue && color)
                {
                    current.value=tempValue;
                }
		}
		game.board[digi(temp2.pos1,0)][digi(temp2.pos1,1)] = game.board[digi(temp2.pos2,0)][digi(temp2.pos2,1)];//cofniecie posuniecia
		game.board[digi(temp2.pos2,0)][digi(temp2.pos2,1)] = rev;
		}
		game.board[digi(temp.pos1,0)][digi(temp.pos1,1)] = game.board[digi(temp.pos2,0)][digi(temp.pos2,1)];//cofniecie posuniecia
		game.board[digi(temp.pos2,0)][digi(temp.pos2,1)] = rev1;
	   printf("## %d %d %d\n",current.x.pos1,current.x.pos2,current.value);
	   if(current.value>best.value && color) best=current;
       if(current.value<best.value && !color) best=current;
       zniszcz(head2);
	}
	zniszcz(head);
	printf("%d %d %d\n",best.x.pos1,best.x.pos2,best.value);
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
