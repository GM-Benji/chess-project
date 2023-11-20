element* generate(char board[8][8],int color)
{
	int* moves[6][32];
	init(moves);
	move r={.pos1=0,.pos2=0};
	element* head = malloc(sizeof(element));
	*head = (element){ .ruch = r,.nastepny = NULL };
	
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if ((board[i][j] == 'n'&& color==0) || (board[i][j] == 'N' && color==1))
			{
				for (int k = 0; k < 8; k++)
				{
					int z=(int)(board[digi(i * 10 + j + *moves[0][k],0)][digi(i * 10 + j + *moves[0][k],1)]);//rzutowanie pola na int(czyli kod ascii)
					if (
						(i * 10 + j + *moves[0][k] >= 0 && i * 10 + j + *moves[0][k] <= 77 )//sprawdzanie czy nie wychodzi poza szachownice
						&&( (z<=90 &&color==0) || ((z>90 || z==35)&& color==1) ) //sprawdzanie czy nie stoi figura tego samego koloru(z kodu ascii)
						)
					{
						move ruch={.pos1=i * 10 + j,.pos2=i * 10 + j + *moves[0][k]};
						utworz(ruch,head);
					}
				}
			}
		}
	}
	return head;
}
