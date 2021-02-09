#include "chessboard.h"

chessBoard::chessBoard()
{
    squares.resize(10);
    for(int i=0;i<10;i++)
    {
        squares[i].resize(10);
    }
    //lay pawn
    for(int i=1;i<=8;i++)
    {
        whitePieces.append(chessPiece(pawn,whiteSide,chessPos(i,2)));
        squares[i][2].chessOnTheBoard=whitePieces.last();
        blackPieces.append(chessPiece(pawn, blackSide, chessPos(i,7)));
        squares[i][7].chessOnTheBoard=blackPieces.last();
        squares[i][1].hasChess=true;squares[i][2].hasChess=true;
        squares[i][7].hasChess=true;squares[i][8].hasChess=true;
    }
    //lay others
    whitePieces.append(chessPiece(rook, whiteSide, chessPos(1,1)));
    squares[1][1].chessOnTheBoard=whitePieces[8];
    whitePieces.append(chessPiece(rook, whiteSide, chessPos(8,1)));
    squares[8][1].chessOnTheBoard=whitePieces.last();
    whitePieces.append(chessPiece(knight, whiteSide, chessPos(2,1)));
    squares[2][1].chessOnTheBoard=whitePieces.last();
    whitePieces.append(chessPiece(knight, whiteSide, chessPos(7,1)));
    squares[7][1].chessOnTheBoard=whitePieces.last();
    whitePieces.append(chessPiece(bishop, whiteSide, chessPos(3,1)));
    squares[3][1].chessOnTheBoard=whitePieces.last();
    whitePieces.append(chessPiece(bishop, whiteSide, chessPos(6,1)));
    squares[6][1].chessOnTheBoard=whitePieces.last();
    whitePieces.append(chessPiece(queen,whiteSide,chessPos(4,1)));
    squares[4][1].chessOnTheBoard=whitePieces.last();
    whitePieces.append(chessPiece(king, whiteSide, chessPos(5,1)));
    squares[5][1].chessOnTheBoard=whitePieces.last();
    blackPieces.append(chessPiece(rook, blackSide, chessPos(1,8)));
    squares[1][8].chessOnTheBoard=blackPieces.last();
    blackPieces.append(chessPiece(rook, blackSide, chessPos(8,8)));
    squares[8][8].chessOnTheBoard=blackPieces.last();
    blackPieces.append(chessPiece(knight, blackSide, chessPos(2,8)));
    squares[2][8].chessOnTheBoard=blackPieces.last();
    blackPieces.append(chessPiece(knight, blackSide, chessPos(7,8)));
    squares[7][8].chessOnTheBoard=blackPieces.last();
    blackPieces.append(chessPiece(bishop, blackSide, chessPos(3,8)));
    squares[3][8].chessOnTheBoard=blackPieces.last();
    blackPieces.append(chessPiece(bishop, blackSide, chessPos(6,8)));
    squares[6][8].chessOnTheBoard=blackPieces.last();
    blackPieces.append(chessPiece(queen,blackSide,chessPos(4,8)));
    squares[4][8].chessOnTheBoard=blackPieces.last();
    blackPieces.append(chessPiece(king, blackSide, chessPos(5,8)));
    squares[5][8].chessOnTheBoard=blackPieces.last();
}

void chessBoard::SetBoardDefault()
{
    for(int i=0;i<10;i++)
    {
        squares[i].clear();
    }
    squares.clear();
    whitePieces.clear();
    blackPieces.clear();
    squares.resize(10);
    for(int i=0;i<10;i++)
    {
        squares[i].resize(10);
    }
    //lay pawn
    for(int i=1;i<=8;i++)
    {
        whitePieces.append(chessPiece(pawn,whiteSide,chessPos(i,2)));
        squares[i][2].chessOnTheBoard=whitePieces.last();
        blackPieces.append(chessPiece(pawn, blackSide, chessPos(i,7)));
        squares[i][7].chessOnTheBoard=blackPieces.last();
        squares[i][1].hasChess=true;squares[i][2].hasChess=true;
        squares[i][7].hasChess=true;squares[i][8].hasChess=true;
    }
    //lay others
    whitePieces.append(chessPiece(rook, whiteSide, chessPos(1,1)));
    squares[1][1].chessOnTheBoard=whitePieces[8];
    whitePieces.append(chessPiece(rook, whiteSide, chessPos(8,1)));
    squares[8][1].chessOnTheBoard=whitePieces.last();
    whitePieces.append(chessPiece(knight, whiteSide, chessPos(2,1)));
    squares[2][1].chessOnTheBoard=whitePieces.last();
    whitePieces.append(chessPiece(knight, whiteSide, chessPos(7,1)));
    squares[7][1].chessOnTheBoard=whitePieces.last();
    whitePieces.append(chessPiece(bishop, whiteSide, chessPos(3,1)));
    squares[3][1].chessOnTheBoard=whitePieces.last();
    whitePieces.append(chessPiece(bishop, whiteSide, chessPos(6,1)));
    squares[6][1].chessOnTheBoard=whitePieces.last();
    whitePieces.append(chessPiece(queen,whiteSide,chessPos(4,1)));
    squares[4][1].chessOnTheBoard=whitePieces.last();
    whitePieces.append(chessPiece(king, whiteSide, chessPos(5,1)));
    squares[5][1].chessOnTheBoard=whitePieces.last();
    blackPieces.append(chessPiece(rook, blackSide, chessPos(1,8)));
    squares[1][8].chessOnTheBoard=blackPieces.last();
    blackPieces.append(chessPiece(rook, blackSide, chessPos(8,8)));
    squares[8][8].chessOnTheBoard=blackPieces.last();
    blackPieces.append(chessPiece(knight, blackSide, chessPos(2,8)));
    squares[2][8].chessOnTheBoard=blackPieces.last();
    blackPieces.append(chessPiece(knight, blackSide, chessPos(7,8)));
    squares[7][8].chessOnTheBoard=blackPieces.last();
    blackPieces.append(chessPiece(bishop, blackSide, chessPos(3,8)));
    squares[3][8].chessOnTheBoard=blackPieces.last();
    blackPieces.append(chessPiece(bishop, blackSide, chessPos(6,8)));
    squares[6][8].chessOnTheBoard=blackPieces.last();
    blackPieces.append(chessPiece(queen,blackSide,chessPos(4,8)));
    squares[4][8].chessOnTheBoard=blackPieces.last();
    blackPieces.append(chessPiece(king, blackSide, chessPos(5,8)));
    squares[5][8].chessOnTheBoard=blackPieces.last();
}
