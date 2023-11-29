element* generate(char board[8][8],int color)
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
			if ((board[i][j] == 'n'&& color==0) || (board[i][j] == 'N' && color==1))//skoczki
			{
				for (int k = 0; k < 8; k++)
				{
					ruch=(move){.pos1=i*10+j,.pos2=i*10+j+moves.arr[0][k]};
					if(ifLegal(color,ruch,board))
					{
						utworz(ruch,head);
					}
				}
			}
			if ((board[i][j] == 'P' && color))//biale pionki
			{
				for (int k = 0; k < 4; k++)
				{
					ruch=(move){.pos1=i*10+j,.pos2=i*10+j+moves.arr[1][k]};
					if(ifLegal(color,ruch,board))
					{
						utworz(ruch,head);
					}
				}
			}
			if ((board[i][j] == 'p' && !color))//czarne pionki
			{
				for (int k = 0; k < 4; k++)
				{
					ruch=(move){.pos1=i*10+j,.pos2=i*10+j+moves.arr[2][k]};
					if(ifLegal(color,ruch,board))
					{
						utworz(ruch,head);
					}
				}
			}
			if ((board[i][j] == 'r'&& color==0) || (board[i][j] == 'R' && color==1))//wieze
			{
				for (int k = 1; k <= 28; k++)
				{
					
					ruch=(move){.pos1=i*10+j,.pos2=i*10+j+moves.arr[3][k]};
					if(digi(ruch.pos1,0)!=digi(ruch.pos1+digi(moves.arr[3][k],1),0))continue;
					if(ifLegal(color,ruch,board))
					{
						utworz(ruch,head);
					}
				}
			}
			if ((board[i][j] == 'b' && color==0) || (board[i][j] == 'B' && color==1)) //gonce
            {
                for(int k=0; k < 32; k++)
                {
                    ruch=(move){.pos1=i*10+j,.pos2=i*10+j+moves.arr[4][k]};
					if(abs(digi(ruch.pos1,0)-digi(ruch.pos2,0))!=abs(digi(ruch.pos1,1)-digi(ruch.pos2,1)))continue;
                    if(ifLegal(color,ruch,board))
					{
						utworz(ruch,head);
					}
                }
            }
			if ((board[i][j] == 'q' && color==0) || (board[i][j] == 'Q' && color==1)) //hetmany
			{
				for (int k = 1; k <= 28; k++)
				{
					
					ruch=(move){.pos1=i*10+j,.pos2=i*10+j+moves.arr[3][k]};
					if(digi(ruch.pos1,0)!=digi(ruch.pos1+digi(moves.arr[3][k],1),0))continue;
					if(ifLegal(color,ruch,board))
					{
						utworz(ruch,head);
					}
				}
				for(int k=0; k < 32; k++)
                {
                    ruch=(move){.pos1=i*10+j,.pos2=i*10+j+moves.arr[4][k]};
					if(abs(digi(ruch.pos1,0)-digi(ruch.pos2,0))!=abs(digi(ruch.pos1,1)-digi(ruch.pos2,1)))continue;
                    if(ifLegal(color,ruch,board))
					{
						utworz(ruch,head);
					}
                }
			}
			if ((board[i][j] == 'k' && color==0) || (board[i][j] == 'K' && color==1)) //krole
            {
                for(int k=0; k < 8; k++)
                {
                    ruch=(move){.pos1=i*10+j,.pos2=i*10+j+moves.arr[5][k]};
                    if(ifLegal(color,ruch,board))
					{
						utworz(ruch,head);
					}
                }
            }
		}
	}
	return head;
}
