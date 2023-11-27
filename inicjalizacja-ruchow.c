typedef struct arrType
{
	int arr[6][32];
}arrType;

arrType init()
{
	arrType moves;
	//knight
	moves.arr[0][0] = -21;
	moves.arr[0][1] = +21;
	moves.arr[0][2] = +19;
	moves.arr[0][3] = -19;
	moves.arr[0][4] = -12;
	moves.arr[0][5] = +12;
	moves.arr[0][6] = +8;
	moves.arr[0][7] = -8;
	//Pawn(w)
	moves.arr[1][0] = -10;
	moves.arr[1][1] = -20;
	moves.arr[1][2] = -11;
	moves.arr[1][3] = -9;
	//pawn(b)
	moves.arr[2][0] = 10;
	moves.arr[2][1] = 20;
	moves.arr[2][2] = 11;
	moves.arr[2][3] = 9;
	//rook
	for (int i = 0; i < 32; i+=4)
	{
		moves.arr[3][i] = i / 4;
		moves.arr[3][i+1] = (i / 4)*10;
		moves.arr[3][i+2] = -(i / 4)*10;
		moves.arr[3][i+3] = -(i / 4);
	}
	//bishop
	for (int i = 0; i < 32; i += 4)
	{
		moves.arr[4][i] = (i / 4) + (i / 4) * 10;
		moves.arr[4][i+1] = -(i / 4) + (i / 4) * 10;
		moves.arr[4][i+2] = (i / 4) - (i / 4) * 10;
		moves.arr[4][i+3] = -(i / 4) - (i / 4) * 10;
	}
	//king
	moves.arr[5][0] = 9;
	moves.arr[5][1] = 10;
	moves.arr[5][2] = 11;
	moves.arr[5][3] = -1;
	moves.arr[5][4] = 1;
	moves.arr[5][5] = -11;
	moves.arr[5][6] = -10;
	moves.arr[5][7] = -9;
	return moves;
}
