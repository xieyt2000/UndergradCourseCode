#include "chesspiece.h"

chessPiece::chessPiece()
{

}

chessPiece::chessPiece(chessPieceType t, chessSide s, chessPos p)
{
    type=t;side=s;curPos=p;
}

chessPiece::chessPiece(chessPieceType t, chessSide s)
{
    type=t;side=s;
}
