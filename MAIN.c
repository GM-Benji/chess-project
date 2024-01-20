void main()
{
	char board[8][8] = { "rnbqkbnr","pppppppp","########","########","########","########","PPPPPPPP","RNBQKBNR"};
	//char board[8][8] = { "k#######","###P####","########","########","#Q####r#","########","########","######NK"};
	set game=setInit(board);

    move playersMove;
    bestReturn checkBlacksMat, algsMove;
    int d = 1; //glebokosc drzewa
    drawBoard(game.board);
	for(int i=0;i==0;)
    {
        //gracz
        playersMove = typeMove(game);

        checkBlacksMat = engine(game, 0, 0); //sprawdzanie przy pomocy engine czy jest koniec gry
        if(checkBlacksMat.x.pos1 == 1000)
        {
            drawBoard(game.board);
            printf("\n  WHITE WON VIA CHECKMATE\n");
            i=1;
        }
        else if(checkBlacksMat.x.pos1 == -1000)
        {
            drawBoard(game.board);
            printf("\n  BLACK WON VIA CHECKMATE\n");
            i=1;
        }
        else if(checkBlacksMat.x.pos1 == 100)
        {
            drawBoard(game.board);
            printf("\n  DRAW DUE TO STEALMATE\n");
            i=1;
        }
        else game=moveMaker(game, 1, playersMove);

        //komputer
        algsMove = engine(game, 0, d); // tez sprawdzanie czy koniec ale wykorzystane tez do wyszukania najlepszego ruchu z glebokoscia d
        if(algsMove.x.pos1 == 1000)
        {
            drawBoard(game.board);
            printf("\n  WHITE WON VIA CHECKMATE\n");
            i=1;
        }
        else if(algsMove.x.pos1 == -1000)
        {
            drawBoard(game.board);
            printf("\n  BLACK WON VIA CHECKMATE\n");
            i=1;
        }
        else if(algsMove.x.pos1 == 100)
        {
            drawBoard(game.board);
            printf("\n  DRAW DUE TO STEALMATE\n");
            i=1;
        }
        else game=moveMaker(game, 0, algsMove.x);
        drawBoard(game.board);
    }
}
