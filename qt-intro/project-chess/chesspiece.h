#ifndef CHESSPIECE_H
#define CHESSPIECE_H
#include<QPair>

enum chessPieceType{bishop, king ,knight, pawn, queen, rook};

enum chessSide{whiteSide, blackSide};

typedef QPair<int,int> chessPos; //<rank, file>  rank a is 1...h is 8

class chessPiece
{
public:
    chessPiece();
    chessPiece(chessPieceType, chessSide, chessPos);
    chessPiece(chessPieceType, chessSide);
    chessPieceType type=pawn;
    //int id;//from 0 == index in the vector
    chessSide side=whiteSide;
    chessPos curPos;
    //bool isValid=false;
};

#endif // CHESSPIECE_H
