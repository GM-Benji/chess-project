element* generate(char board[][],int color)
{
	int* moves[6][32];
	init(moves);
	element *head={.nastepny=NULL,.ruch={.poz1=0,.poz2=0}};
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if ((board[i][j] == 'n'&& color==0) || (board[i][j] == 'N' && color==1))
			{
				for (int k = 0; k < 8; k++)
				{
					int z=int(board[digi(i * 10 + j + moves[0][k],0)][digi(i * 10 + j + moves[0][k],1)]);//rzutowanie pola na int(czyli kod ascii)
					if (
						(i * 10 + j + moves[0][k] >= 0 && i * 10 + j + moves[0][k] <= 77 )//sprawdzanie czy nie wychodzi poza szachownice
						&&( (z<=90 &&color==0) || ((z>90 || z==35)&& color==1) ) //sprawdzanie czy nie stoi figura tego samego koloru(z kodu ascii)
						)
					{
						
					}
				}
			}
		}
	}
}
