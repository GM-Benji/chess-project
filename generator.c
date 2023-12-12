element* generate(set game,int color)
{
	arrType moves=init();
	move r={.pos1=0,.pos2=0};
	element* head = malloc(sizeof(element));
	*head = (element){ .ruch = r,.nastepny = NULL };
	move ruch={.pos1=-1,.pos2=-1};
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
                for(int k=0; k < 8; k++)
                {
                    ruch=(move){.pos1=i*10+j,.pos2=i*10+j+moves.arr[5][k]};
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
