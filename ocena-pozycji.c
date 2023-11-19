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
