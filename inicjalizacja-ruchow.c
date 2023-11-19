void init(int* moves[][32])
{
	//knight
	moves[0][0] = -21;
	moves[0][1] = +21;
	moves[0][2] = +19;
	moves[0][3] = -19;
	moves[0][4] = -12;
	moves[0][5] = +12;
	moves[0][6] = +8;
	moves[0][7] = -8;
	//Pawn(w)
	moves[1][0] = -10;
	moves[1][1] = -20;
	moves[1][2] = -11;
	moves[1][3] = -9;
	//pawn(b)
	moves[2][0] = 10;
	moves[2][1] = 20;
	moves[2][2] = 11;
	moves[2][3] = 9;
	//rook
	for (int i = 0; i < 32; i+=4)
	{
		moves[3][i] = i / 4;
		moves[3][i+1] = (i / 4)*10;
		moves[3][i+2] = -(i / 4)*10;
		moves[3][i+3] = -(i / 4);
	}
	//bishop
	for (int i = 0; i < 32; i += 4)
	{
		moves[4][i] = (i / 4) + (i / 4) * 10;
		moves[4][i+1] = -(i / 4) + (i / 4) * 10;
		moves[4][i+2] = (i / 4) - (i / 4) * 10;
		moves[4][i+3] = -(i / 4) - (i / 4) * 10;
	}
	//king
	moves[5][0] = 9;
	moves[5][1] = 10;
	moves[5][2] = 11;
	moves[5][3] = -1;
	moves[5][4] = 1;
	moves[5][5] = -11;
	moves[5][6] = -10;
	moves[5][7] = -9;



}
