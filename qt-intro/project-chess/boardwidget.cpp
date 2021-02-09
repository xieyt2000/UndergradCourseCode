#include "boardwidget.h"
#include<QDebug>
#include<QMessageBox>
#include"promotedialog.h"
#include<QStringList>
#include<QChar>

boardWidget::boardWidget(QWidget *parent) : QWidget(parent)
{
    frontRects.resize(10);
    for(int i=0;i<10;i++)
    {
        frontRects[i].resize(10);
    }
    mySideTimer.setInterval(1000);
    //connect(&mySideTimer, &QTimer::timeout, this, &boardWidget::mySideOverTime);
    connect(&mySideTimer, &QTimer::timeout, this, [=](){
        curCountDownTime--;
        emit changeLCDTimer(curCountDownTime);
        if(curCountDownTime==0) mySideResign();
    });
}

QPixmap boardWidget::getPixMap(chessPieceType type, chessSide side)
{
    QPixmap pic;
    switch (type) {
    case pawn:
        if(side==blackSide) pic=QPixmap(":/pictures/pictures/black_pawn.png");
        else pic=QPixmap(":/pictures/pictures/white_pawn.png");
        break;
    case king:
        if(side==blackSide) pic=QPixmap(":/pictures/pictures/black_king.png");
        else pic=QPixmap(":/pictures/pictures/white_king.png");
        break;
    case knight:
        if(side==blackSide) pic=QPixmap(":/pictures/pictures/black_knight.png");
        else pic=QPixmap(":/pictures/pictures/white_knight.png");
        break;
    case bishop:
        if(side==blackSide) pic=QPixmap(":/pictures/pictures/black_bishop.png");
        else pic=QPixmap(":/pictures/pictures/white_bishop.png");
        break;
    case queen:
        if(side==blackSide) pic=QPixmap(":/pictures/pictures/black_queen.png");
        else pic=QPixmap(":/pictures/pictures/white_queen.png");
        break;
    case rook:
        if(side==blackSide) pic=QPixmap(":/pictures/pictures/black_rook.png");
        else pic=QPixmap(":/pictures/pictures/white_rook.png");
        break;
    }
    return pic;
}

void boardWidget::mousePressEvent(QMouseEvent *event)
{   
    if(curSide!=mySide) return;
    if(event->button()==Qt::LeftButton)
    {
        int X=event->pos().x(); int Y=event->pos().y();
        for(int i=1; i<=8; i++)
        {
            for(int j=1;j<=8;j++)
            {
                const QRectF& tmpRect=frontRects[i][j];
                if(X>tmpRect.left()&&X<tmpRect.right()&&Y>tmpRect.top()&&Y<tmpRect.bottom())
                {
                    //already select
                    if(selectAPiece)
                    {
                        if(board.squares[i][j].selectable)
                        {
                            if(chessPos(i,j)!=curSelectedPiecePos)  //move a piece
                            {
                                int tmpI=curSelectedPiecePos.first; int tmpJ=curSelectedPiecePos.second;
                                //judge game finish
                                if(board.squares[i][j].chessOnTheBoard.type==king&&board.squares[i][j].chessOnTheBoard.side!=curSide)
                                {
                                    board.squares[tmpI][tmpJ].hasChess=false;
                                    board.squares[i][j].hasChess=true;
                                    board.squares[i][j].chessOnTheBoard=board.squares[tmpI][tmpJ].chessOnTheBoard;
                                    update();
                                    //send message
                                    genBoardStrAndSend();
                                    oneSideWin(curSide);
                                    return;
                                }
                                board.squares[tmpI][tmpJ].hasChess=false;
                                board.squares[i][j].hasChess=true;
                                board.squares[i][j].chessOnTheBoard=board.squares[tmpI][tmpJ].chessOnTheBoard;
                                //change side
                                curSide=getOtherSide(curSide);


                                //try promote
                                if(curSelectedPiece.type==pawn)
                                {
                                    if(!promotePawn(chessPos(i,j)))
                                    {
                                        //send message
                                        genBoardStrAndSend();
                                        //check status
                                        checkBothSideCheckAndCursideStalement();
                                    }
                                }
                                else {
                                    //send message
                                    genBoardStrAndSend();
                                    //check status
                                    checkBothSideCheckAndCursideStalement();
                                }
                            }
                        }
                        //reset selet
                        resetSelect();
                        return;
                    }
                    //select a new
                    if(board.squares[i][j].hasChess&&board.squares[i][j].chessOnTheBoard.side==curSide)
                    {
                        board.squares[i][j].selectable=true;

                        curSelectedPiecePos=chessPos(i,j);
                        curSelectedPiece=board.squares[i][j].chessOnTheBoard;
                        selectAPiece=true;
                        genSelectAble(curSelectedPiece, curSelectedPiecePos);
                        board.squares[i][j].selectable=true;
                        update();
                        return;
                    }
                }
            }
        }
    }
}

void boardWidget::genSelectAble(const chessPiece& piece, const chessPos& pos)
{
    chessSide tmpPieceSide=piece.side;
    chessPieceType tmpPieceType=piece.type;
    int rank=pos.second;
    int file=pos.first;
    switch (tmpPieceType) {
    case pawn:
    {
        if(tmpPieceSide==whiteSide)
        {
            if(rank==2)
            {
                if(!board.squares[file][4].hasChess)
                {
                    if(!board.squares[file][3].hasChess)
                        board.squares[file][4].selectable=true;
                }
            }
            if(!board.squares[file][rank+1].hasChess)
                board.squares[file][rank+1].selectable=true;
            if(board.squares[file+1][rank+1].hasChess&&board.squares[file+1][rank+1].chessOnTheBoard.side!=tmpPieceSide)
                board.squares[file+1][rank+1].selectable=true;
            if(board.squares[file-1][rank+1].hasChess&&board.squares[file-1][rank+1].chessOnTheBoard.side!=tmpPieceSide)
                board.squares[file-1][rank+1].selectable=true;
        }
        if(tmpPieceSide==blackSide)
        {
            if(rank==7)
            {
                if(!board.squares[file][5].hasChess)
                {
                    if(!board.squares[file][6].hasChess)
                        board.squares[file][5].selectable=true;
                }
            }
            if(!board.squares[file][rank-1].hasChess)
                board.squares[file][rank-1].selectable=true;
            if(board.squares[file-1][rank-1].hasChess&&board.squares[file-1][rank-1].chessOnTheBoard.side!=tmpPieceSide)
                board.squares[file-1][rank-1].selectable=true;
            if(board.squares[file+1][rank-1].hasChess&&board.squares[file+1][rank-1].chessOnTheBoard.side!=tmpPieceSide)
                board.squares[file+1][rank-1].selectable=true;
        }
        break;
    }
    case rook:
    {
        for(int i=file+1;i<=8;i++)
        {
            if(!board.squares[i][rank].hasChess)
                board.squares[i][rank].selectable=true;
            else if(board.squares[i][rank].chessOnTheBoard.side!=tmpPieceSide)
            {
                board.squares[i][rank].selectable=true;
                break;
            }
            else break;
        }
        for(int i=file-1;i>=1;i--)
        {
            if(!board.squares[i][rank].hasChess)
                board.squares[i][rank].selectable=true;
            else if(board.squares[i][rank].chessOnTheBoard.side!=tmpPieceSide)
            {
                board.squares[i][rank].selectable=true;
                break;
            }
            else break;
        }
        for(int i=rank-1;i>=1;i--)
        {
            if(!board.squares[file][i].hasChess)
                board.squares[file][i].selectable=true;
            else if(board.squares[file][i].chessOnTheBoard.side!=tmpPieceSide)
            {
                board.squares[file][i].selectable=true;
                break;
            }
            else break;
        }
        for(int i=rank+1;i<=8;i++)
        {
            if(!board.squares[file][i].hasChess)
                board.squares[file][i].selectable=true;
            else if(board.squares[file][i].chessOnTheBoard.side!=tmpPieceSide)
            {
                board.squares[file][i].selectable=true;
                break;
            }
            else break;
        }
        break;
    }
    case king:
    {
        for(int i=file-1;i<=file+1;i++)
        {
            for(int j=rank-1;j<=rank+1;j++)
            {
                if(i<1||i>8||j<1||j>8) continue;
                if((!board.squares[i][j].hasChess)||board.squares[i][j].chessOnTheBoard.side!=tmpPieceSide)
                    board.squares[i][j].selectable=true;
            }
        }
        break;
    }
    case queen:
    {
        //rook
        for(int i=file+1;i<=8;i++)
        {
            if(!board.squares[i][rank].hasChess)
                board.squares[i][rank].selectable=true;
            else if(board.squares[i][rank].chessOnTheBoard.side!=tmpPieceSide)
            {
                board.squares[i][rank].selectable=true;
                break;
            }
            else break;
        }
        for(int i=file-1;i>=1;i--)
        {
            if(!board.squares[i][rank].hasChess)
                board.squares[i][rank].selectable=true;
            else if(board.squares[i][rank].chessOnTheBoard.side!=tmpPieceSide)
            {
                board.squares[i][rank].selectable=true;
                break;
            }
            else break;
        }
        for(int i=rank-1;i>=1;i--)
        {
            if(!board.squares[file][i].hasChess)
                board.squares[file][i].selectable=true;
            else if(board.squares[file][i].chessOnTheBoard.side!=tmpPieceSide)
            {
                board.squares[file][i].selectable=true;
                break;
            }
            else break;
        }
        for(int i=rank+1;i<=8;i++)
        {
            if(!board.squares[file][i].hasChess)
                board.squares[file][i].selectable=true;
            else if(board.squares[file][i].chessOnTheBoard.side!=tmpPieceSide)
            {
                board.squares[file][i].selectable=true;
                break;
            }
            else break;
        }
        //bishop
        for(int i=file+1;i<=8;i++)
        {
            int j=rank+i-file;
            if(j>8) break;
            if(!board.squares[i][j].hasChess)
                board.squares[i][j].selectable=true;
            else if(board.squares[i][j].chessOnTheBoard.side!=tmpPieceSide)
            {
                board.squares[i][j].selectable=true;
                break;
            }
            else break;
        }
        for(int i=file+1;i<=8;i++)
        {
            int j=rank+file-i;
            if(j<1) break;
            if(!board.squares[i][j].hasChess)
                board.squares[i][j].selectable=true;
            else if(board.squares[i][j].chessOnTheBoard.side!=tmpPieceSide)
            {
                board.squares[i][j].selectable=true;
                break;
            }
            else break;
        }
        for(int i=file-1;i>=1;i--)
        {
            int j=rank+file-i;
            if(j>8) break;
            if(!board.squares[i][j].hasChess)
                board.squares[i][j].selectable=true;
            else if(board.squares[i][j].chessOnTheBoard.side!=tmpPieceSide)
            {
                board.squares[i][j].selectable=true;
                break;
            }
            else break;
        }
        for(int i=file-1;i>=1;i--)
        {
            int j=rank+i-file;
            if(j<1) break;
            if(!board.squares[i][j].hasChess)
                board.squares[i][j].selectable=true;
            else if(board.squares[i][j].chessOnTheBoard.side!=tmpPieceSide)
            {
                board.squares[i][j].selectable=true;
                break;
            }
            else break;
        }
        break;
    }
    case bishop:
    {
        for(int i=file+1;i<=8;i++)
        {
            int j=rank+i-file;
            if(j>8) break;
            if(!board.squares[i][j].hasChess)
                board.squares[i][j].selectable=true;
            else if(board.squares[i][j].chessOnTheBoard.side!=tmpPieceSide)
            {
                board.squares[i][j].selectable=true;
                break;
            }
            else break;
        }
        for(int i=file+1;i<=8;i++)
        {
            int j=rank+file-i;
            if(j<1) break;
            if(!board.squares[i][j].hasChess)
                board.squares[i][j].selectable=true;
            else if(board.squares[i][j].chessOnTheBoard.side!=tmpPieceSide)
            {
                board.squares[i][j].selectable=true;
                break;
            }
            else break;
        }
        for(int i=file-1;i>=1;i--)
        {
            int j=rank+file-i;
            if(j>8) break;
            if(!board.squares[i][j].hasChess)
                board.squares[i][j].selectable=true;
            else if(board.squares[i][j].chessOnTheBoard.side!=tmpPieceSide)
            {
                board.squares[i][j].selectable=true;
                break;
            }
            else break;
        }
        for(int i=file-1;i>=1;i--)
        {
            int j=rank+i-file;
            if(j<1) break;
            if(!board.squares[i][j].hasChess)
                board.squares[i][j].selectable=true;
            else if(board.squares[i][j].chessOnTheBoard.side!=tmpPieceSide)
            {
                board.squares[i][j].selectable=true;
                break;
            }
            else break;
        }
        break;
    }
    case knight:
    {
        QVector<chessPos> possibalPos;
        possibalPos.append(chessPos(file-1, rank+2)); possibalPos.append(chessPos(file+1, rank+2));
        possibalPos.append(chessPos(file-1, rank-2)); possibalPos.append(chessPos(file+1, rank-2));
        possibalPos.append(chessPos(file-2, rank+1)); possibalPos.append(chessPos(file-2, rank-1));
        possibalPos.append(chessPos(file+2, rank+1)); possibalPos.append(chessPos(file+2, rank-1));
        for(auto it:possibalPos)
        {
            int i=it.first; int j=it.second;
            if(i<1||i>8||j<1||j>8) continue;
            if(!board.squares[i][j].hasChess||board.squares[i][j].chessOnTheBoard.side!=tmpPieceSide)
                board.squares[i][j].selectable=true;
        }
        break;
    }
    }
}

bool boardWidget::promotePawn(chessPos pos)
{
    int file=pos.first;int rank=pos.second;
    if(rank!=8&&rank!=1) return false;
    promoteDialog* prDialog = new promoteDialog(this);
    connect(prDialog, &promoteDialog::proType, this, [=](QString ty) mutable
    {
        chessPieceType prochessType=queen;
        if(ty=="Queen") prochessType=queen;
        if(ty=="Rook") prochessType=rook;
        if(ty=="Knight") prochessType=knight;
        if(ty=="Bishop") prochessType=bishop;
        board.squares[file][rank].chessOnTheBoard.type=prochessType;
        update();
        //send message
        genBoardStrAndSend();
        checkBothSideCheckAndCursideStalement();
    });
    prDialog->show();
    return  true;
}

void boardWidget::oneSideWin(chessSide winSide)
{
    update();
    QString winningSide;
    if(winSide==whiteSide) winningSide="White";
    else winningSide="Black";

    QMessageBox::information(this, "Game Ends",winningSide+" wins!");
    resetBoard();
}

chessSide boardWidget::getOtherSide(chessSide thisSide)
{
    if(thisSide==whiteSide) return blackSide;
    else return whiteSide;
}

chessPieceType boardWidget::getType(QString type)
{
    if(type=="king") return king;
    if(type=="rook") return  rook;
    if(type=="bishop") return bishop;
    if(type=="queen") return queen;
    if(type=="knight") return knight;
    return pawn;
}

void boardWidget::genBoardStrAndSend()
{
    QStringList Lines=generateCurBoard();
    QString ret;
    QTextStream textStream(&ret,QIODevice::WriteOnly);
    for(auto line : Lines)
    {
        if(line.length()==0) break;
        textStream<<line<<endl;
    }
    qDebug()<<ret;
    emit sendBoardMessage(ret);
    stopCountDown();
}

void boardWidget::checkStatus(chessSide sideToCheck)
{
    QString tocheckSide="black";
    if(sideToCheck==whiteSide) tocheckSide="white";
    if(checkCheck(sideToCheck))
        QMessageBox::information(this, "Check", tocheckSide+" king in check!");
    //only check curside stalement or not
    checkStalemate(curSide);
}

bool boardWidget::checkCheck(chessSide sideToCheck)
{
    chessSide otherSide=getOtherSide(sideToCheck);
    markAllTheSquresOneSideCanGo(otherSide);
    QString tocheckSide="black";
    if(sideToCheck==whiteSide) tocheckSide="white";
    //judge if check
    for(int i=1;i<=8;i++)
    {
        for(int j=1;j<=8;j++)
        {
            const chessBoardSquare& tmpCurSqure=board.squares[i][j];
            if(!tmpCurSqure.hasChess) continue;
            if(tmpCurSqure.chessOnTheBoard.side!=sideToCheck) continue;
            if(!tmpCurSqure.selectable) continue;
            if(tmpCurSqure.chessOnTheBoard.type==king)
            {

                resetSelect();
                return true;
            }
        }
    }
    resetSelect();
    return false;
}

bool boardWidget::checkStalemate(chessSide sideToCheck)
{
    chessSide otherSide=getOtherSide(sideToCheck);
    if(checkCheck(sideToCheck)) return false;
    resetSelect();
    //check king
    //find king
    chessPos kingPos;
    for(int i=1;i<=8;i++)
    {
        for(int j=1;j<=8;j++)
        {
            chessBoardSquare tmpCurSqure=board.squares[i][j];
            if(tmpCurSqure.hasChess&&tmpCurSqure.chessOnTheBoard.type==king&&tmpCurSqure.chessOnTheBoard.side==sideToCheck)
                kingPos=chessPos(i,j);
        }
    }
    //let all pieces go to all the selectable and in check
    for(int p=1;p<=8;p++)
    {
        for(int q=1;q<=8;q++)
        {
            if(!board.squares[p][q].hasChess) continue;
            chessPiece chessPieceToCheck=board.squares[p][q].chessOnTheBoard;
            if(chessPieceToCheck.side!=sideToCheck) continue;
            resetSelect();
            genSelectAble(chessPieceToCheck, chessPos(p,q));
            //keep a back up
            bool checkPieceCanGo[10][10];
            for(int i=1;i<=8;i++)
            {
                for(int j=1;j<=8;j++)
                {
                    checkPieceCanGo[i][j]=board.squares[i][j].selectable;
                }
            }
            resetSelect();
            checkPieceCanGo[p][q]=false;
            board.squares[p][q].hasChess=false;
            for(int i=1;i<=8;i++)
            {
                for(int j=1;j<=8;j++)
                {
                    if(checkPieceCanGo[i][j])
                    {
                        //keep ij
                        chessBoardSquare backupSquare=board.squares[i][j];
                        board.squares[i][j].hasChess=true;
                        board.squares[i][j].chessOnTheBoard=chessPieceToCheck;
                        if(!checkCheck(sideToCheck))
                        {
                            board.squares[i][j].hasChess=false;
                            board.squares[p][q].hasChess=true;
                            board.squares[p][q].chessOnTheBoard=chessPieceToCheck;
                            board.squares[i][j]=backupSquare;
                            return false;
                        }
                        //reset ij
                        board.squares[i][j]=backupSquare;
                    }
                }
            }
            board.squares[p][q].hasChess=true;
            board.squares[p][q].chessOnTheBoard=chessPieceToCheck;
        }
    }
    resetSelect();
    return true;
}

void boardWidget::markAllTheSquresOneSideCanGo(chessSide markSide)
{
    resetSelect();
    for(int i=1;i<=8;i++)
    {
        for(int j=1;j<=8;j++)
        {
            const chessBoardSquare& tmpCurSqure=board.squares[i][j];
            if(!tmpCurSqure.hasChess) continue;
            if(tmpCurSqure.chessOnTheBoard.side!=markSide) continue;
            genSelectAble(tmpCurSqure.chessOnTheBoard, chessPos(i,j));
        }
    }
}

void boardWidget::markAllTheSquresOneSideCanGoExceptKingAndExcludeThemSelves(chessSide markSide)
{
    resetSelect();
    for(int i=1;i<=8;i++)
    {
        for(int j=1;j<=8;j++)
        {
            const chessBoardSquare& tmpCurSqure=board.squares[i][j];
            if(!tmpCurSqure.hasChess) continue;
            if(tmpCurSqure.chessOnTheBoard.side!=markSide) continue;
            if(tmpCurSqure.chessOnTheBoard.type==king) continue;
            genSelectAble(tmpCurSqure.chessOnTheBoard, chessPos(i,j));
            board.squares[i][j].selectable=false;
        }
    }
}

bool boardWidget::checkBothSideCheckAndCursideStalement()
{
    //check check
    chessSide sideToCheck=whiteSide;
    QString tocheckSide="white";
    if(checkCheck(sideToCheck))
        QMessageBox::information(this, "Check", tocheckSide+" king in check!");
    sideToCheck=blackSide;
    tocheckSide="black";
    if(checkCheck(sideToCheck))
        QMessageBox::information(this, "Check", tocheckSide+" king in check!");
    //only check curside stalement or not
    if(checkStalemate(curSide))
    {
        stopCountDown();
        QMessageBox::information(this, "Game Ends", "Stalemate! Game ends as a draw.");
        resetBoard();
        return true;
    }
    resetSelect();
    return false;
}

void boardWidget::resetSelect()
{
    selectAPiece=false;
    for(int i=1;i<=8;i++)
    {
        for(int j=1;j<=8;j++)
        {
            board.squares[i][j].selectable=false;
        }
    }
    update();
}

void boardWidget::resetBoard()
{
    stopCountDown();
    board.SetBoardDefault();
    selectAPiece=false; resetSelect();
    curSide=whiteSide;
    if(mySide==whiteSide) startCountDown();
    update();
}

void boardWidget::countDown()
{
    curCountDownTime=60;
    emit changeLCDTimer(curCountDownTime);
    mySideTimer.start();
}

void boardWidget::startCountDown()
{
    countDown();
}

void boardWidget::stopCountDown()
{
    mySideTimer.stop();
    curCountDownTime=60;
    emit changeLCDTimer(60);
}



void boardWidget::mySideOverTime()
{
    mySideResign();
}

void boardWidget::castling(castleSide tarSide)
{
    int castleRank;
    if(curSide==whiteSide) castleRank=1;
    else castleRank=8;
    int castleKingTargetFile, castleRookOriFile, castleRookTargetFile;
    if(tarSide==kingside)
    {
        castleKingTargetFile=7;
        castleRookOriFile=8;
        castleRookTargetFile=6;
    }
    else
    {
        castleKingTargetFile=3;
        castleRookOriFile=1;
        castleRookTargetFile=4;
    }
    const chessBoardSquare& kingSquare=board.squares[5][castleRank];
    if(!(
                kingSquare.hasChess&&
                kingSquare.chessOnTheBoard.side==curSide&&
                kingSquare.chessOnTheBoard.type==king))
    {
        resetSelect();
        QMessageBox::information(this, "Can't Castle", "Your King is moved!");
        return;
    }
    const chessBoardSquare& rookSquare=board.squares[castleRookOriFile][castleRank];
    if(!(
                rookSquare.hasChess&&
                rookSquare.chessOnTheBoard.side==curSide&&
                rookSquare.chessOnTheBoard.type==rook))
    {
        resetSelect();
        QMessageBox::information(this, "Can't Castle", "Your Rook is moved!");

        return;
    }
    if(checkCheck(curSide))
    {
        resetSelect();
        QMessageBox::information(this, "Can't Castle", "Your King is in check!");
        return;
    }
    bool routeNotOccupied=true;
    for(int i=castleRookOriFile+1; i<5;i++)
    {
        if(board.squares[i][castleRank].hasChess) routeNotOccupied=false;
    }
    for(int i=castleRookOriFile-1; i>5;i--)
    {
        if(board.squares[i][castleRank].hasChess) routeNotOccupied=false;
    }
    if(!routeNotOccupied)
    {
        resetSelect();
        QMessageBox::information(this, "Can't Castle", "Chess piece between the king and the rook!");
        return;
    }
    bool castleIntoCheck=false;
    resetSelect();
    {
        for(int i=6;i<=castleKingTargetFile;i++)
        {
            board.squares[i][castleRank].hasChess=true;
            board.squares[i][castleRank].chessOnTheBoard=chessPiece(king,curSide);
            if(checkCheck(curSide)) castleIntoCheck=true;
            board.squares[i][castleRank].hasChess=false;
        }
        for(int i=4;i>=castleKingTargetFile;i--)
        {
            board.squares[i][castleRank].hasChess=true;
            board.squares[i][castleRank].chessOnTheBoard=chessPiece(king,curSide);
            if(checkCheck(curSide)) castleIntoCheck=true;
            board.squares[i][castleRank].hasChess=false;
        }
    }
    if(castleIntoCheck)
    {
        resetSelect();
        QMessageBox::information(this, "Can't Castle", "King castle into check!");
        return;
    }
    qDebug()<<"fuck";
    //castle
    board.squares[5][castleRank].hasChess=false;
    board.squares[castleRookOriFile][castleRank].hasChess=false;
    board.squares[castleKingTargetFile][castleRank].hasChess=true;
    board.squares[castleKingTargetFile][castleRank].chessOnTheBoard=chessPiece(king,curSide);
    board.squares[castleRookTargetFile][castleRank].hasChess=true;
    board.squares[castleRookTargetFile][castleRank].chessOnTheBoard=chessPiece(rook,curSide);
    resetSelect();
    update();
    //change side
    curSide=getOtherSide(curSide);

    //send message
    genBoardStrAndSend();
    //check status
    checkBothSideCheckAndCursideStalement();
    resetSelect();
}

QStringList boardWidget::generateCurBoard()
{
    QStringList ret;
    //get all the piece with type
    //board.whitePieces.clear(); board.blackPieces.clear();
    QVector<chessPos> whitekings, whitepawns, whiteknights, whitequeens, whiterooks, whitebishops;
    QVector<chessPos> blackkings, blackpawns, blackknights, blackqueens, blackrooks, blackbishops;
    for(int i=1;i<=8;i++)
    {
        for(int j=1;j<=8;j++)
        {
            const chessBoardSquare& tmpCurSqure=board.squares[i][j];
            if(tmpCurSqure.hasChess)
            {
                chessPos tmpCurPos(i,j);
                if(tmpCurSqure.chessOnTheBoard.side==whiteSide)
                {
                    switch (tmpCurSqure.chessOnTheBoard.type) {
                    case king:
                    {
                        whitekings.append(tmpCurPos);
                        break;
                    }
                    case bishop:
                    {
                        whitebishops.append(tmpCurPos);
                        break;
                    }
                    case pawn:
                    {
                        whitepawns.append(tmpCurPos);
                        break;
                    }
                    case knight:
                    {
                        whiteknights.append(tmpCurPos);
                        break;
                    }
                    case rook:
                    {
                        whiterooks.append(tmpCurPos);
                        break;
                    }
                    case queen:
                    {
                        whitequeens.append(tmpCurPos);
                        break;
                    }
                    }
                }
                else
                {
                    switch (tmpCurSqure.chessOnTheBoard.type) {
                    case king:
                    {
                        blackkings.append(tmpCurPos);
                        break;
                    }
                    case bishop:
                    {
                        blackbishops.append(tmpCurPos);
                        break;
                    }
                    case pawn:
                    {
                        blackpawns.append(tmpCurPos);
                        break;
                    }
                    case knight:
                    {
                        blackknights.append(tmpCurPos);
                        break;
                    }
                    case rook:
                    {
                        blackrooks.append(tmpCurPos);
                        break;
                    }
                    case queen:
                    {
                        blackqueens.append(tmpCurPos);
                        break;
                    }
                    }
                }
            }
        }
    }
    QStringList whiteret, blackret;
    //parse every line

    //white
    whiteret.append("white");
    if(whitekings.length()>0)
    {
        QString line;
        line.append("king ");
        line.append(QString::number(whitekings.length()));
        for(auto i : whitekings)
        {
            char file=char('a'+i.first-1);
            char rank=char('0'+i.second);
            QString tmp=' '+QChar(file)+QChar(rank);
            line.append(tmp);
        }
        whiteret.append(line);
    }
    if(whitepawns.length()>0)
    {
        QString line;
        line.append("pawn ");
        line.append(QString::number(whitepawns.length()));
        for(auto i : whitepawns)
        {
            char file=char('a'+i.first-1);

            char rank=char('0'+i.second);
            QString tmp=' '+QChar(file)+QChar(rank);
            line.append(tmp);
        }
        whiteret.append(line);
    }
    if(whiterooks.length()>0)
    {
        QString line;
        line.append("rook ");
        line.append(QString::number(whiterooks.length()));
        for(auto i : whiterooks)
        {
            char file=char('a'+i.first-1);

            char rank=char('0'+i.second);
            QString tmp=' '+QChar(file)+QChar(rank);
            line.append(tmp);
        }
        whiteret.append(line);
    }
    if(whiteknights.length()>0)
    {
        QString line;
        line.append("knight ");
        line.append(QString::number(whiteknights.length()));
        for(auto i : whiteknights)
        {
            char file=char('a'+i.first-1);

            char rank=char('0'+i.second);
            QString tmp=' '+QChar(file)+QChar(rank);
            line.append(tmp);
        }
        whiteret.append(line);
    }
    if(whitebishops.length()>0)
    {
        QString line;
        line.append("bishop ");
        line.append(QString::number(whitebishops.length()));
        for(auto i : whitebishops)
        {
            char file=char('a'+i.first-1);

            char rank=char('0'+i.second);
            QString tmp=' '+QChar(file)+QChar(rank);
            line.append(tmp);
        }
        whiteret.append(line);
    }
    if(whitequeens.length()>0)
    {
        QString line;
        line.append("queen ");
        line.append(QString::number(whitequeens.length()));
        for(auto i : whitequeens)
        {
            char file=char('a'+i.first-1);

            char rank=char('0'+i.second);
            QString tmp=' '+QChar(file)+QChar(rank);
            line.append(tmp);
        }
        whiteret.append(line);
    }

    //black
    blackret.append("black");
    if(blackkings.length()>0)
    {
        QString line;
        line.append("king ");
        line.append(QString::number(blackkings.length()));
        for(auto i : blackkings)
        {
            char file=char('a'+i.first-1);

            char rank=char('0'+i.second);
            QString tmp=' '+QChar(file)+QChar(rank);
            line.append(tmp);
        }
        blackret.append(line);
    }
    if(blackpawns.length()>0)
    {
        QString line;
        line.append("pawn ");
        line.append(QString::number(blackpawns.length()));
        for(auto i : blackpawns)
        {
            char file=char('a'+i.first-1);

            char rank=char('0'+i.second);
            QString tmp=' '+QChar(file)+QChar(rank);
            line.append(tmp);
        }
        blackret.append(line);
    }
    if(blackrooks.length()>0)
    {
        QString line;
        line.append("rook ");
        line.append(QString::number(blackrooks.length()));
        for(auto i : blackrooks)
        {
            char file=char('a'+i.first-1);

            char rank=char('0'+i.second);
            QString tmp=' '+QChar(file)+QChar(rank);
            line.append(tmp);
        }
        blackret.append(line);
    }
    if(blackknights.length()>0)
    {
        QString line;
        line.append("knight ");
        line.append(QString::number(blackknights.length()));
        for(auto i : blackknights)
        {
            char file=char('a'+i.first-1);

            char rank=char('0'+i.second);
            QString tmp=' '+QChar(file)+QChar(rank);
            line.append(tmp);
        }
        blackret.append(line);
    }
    if(blackbishops.length()>0)
    {
        QString line;
        line.append("bishop ");
        line.append(QString::number(blackbishops.length()));
        for(auto i : blackbishops)
        {
            char file=char('a'+i.first-1);

            char rank=char('0'+i.second);
            QString tmp=' '+QChar(file)+QChar(rank);
            line.append(tmp);
        }
        blackret.append(line);
    }
    if(blackqueens.length()>0)
    {
        QString line;
        line.append("queen ");
        line.append(QString::number(blackqueens.length()));
        for(auto i : blackqueens)
        {
            char file=char('a'+i.first-1);

            char rank=char('0'+i.second);
            QString tmp=' '+QChar(file)+QChar(rank);
            line.append(tmp);
        }
        blackret.append(line);
    }

    if(curSide==whiteSide)
    {
        ret.append(whiteret); ret.append(blackret);
    }
    else
    {
        ret.append(blackret); ret.append(whiteret);
    }
    return ret;
}

bool boardWidget::nowIsMySide()
{
    return (mySide==curSide);
}


void boardWidget::mySideResign()
{
    QString resignSide;
    if(mySide==whiteSide)
    {
        resignSide="white";
    }
    else
    {
        resignSide="black";
    }
    //send message
    emit sendBoardMessage(resignSide);
    oneSideWin(getOtherSide(mySide));
    //stopCountDown();
}

void boardWidget::loadABoard(QVector<QStringList> input)
{
    //game ends
    if(input.length()==1)
    {
        if(input[0][0]=="white") oneSideWin(blackSide);
        else oneSideWin(whiteSide);
        return;
    }
    //intialize
    board.whitePieces.clear();
    board.blackPieces.clear();
    for(int i=1; i<=8;i++)
    {
        for(int j=1;j<=8;j++)
        {
            board.squares[i][j].hasChess=false;
            board.squares[i][j].selectable=false;
        }
    }

    //normal input
    if(input[0][0]=="white")
        curSide=whiteSide;
    else
        curSide=blackSide;
    chessSide otherSide=getOtherSide(curSide);
    int i=1;
    bool curSideHasKing=false;
    for(;input[i].length()>1;i++)
    {
        chessPieceType tmpThisType=getType(input[i][0]);
        if(tmpThisType==king) curSideHasKing=true;
        for(int j=2;j<input[i].size();j++)
        {

            if(input[i][j].length()!=2) continue;
            int file=input[i][j][0].toLatin1()-'a'+1;
            int rank=input[i][j][1].digitValue();
            board.squares[file][rank].hasChess=true;
            board.squares[file][rank].chessOnTheBoard=chessPiece(tmpThisType, curSide);
        }
    }
    if(!curSideHasKing) oneSideWin(otherSide);
    bool otherSideHasKing=false;
    i++;
    for(;i<input.length();i++)
    {
        chessPieceType tmpThisType=getType(input[i][0]);
        if(tmpThisType==king) otherSideHasKing=true;
        for(int j=2;j<input[i].size();j++)
        {
            int file=input[i][j][0].toLatin1()-'a'+1;
            int rank=input[i][j][1].digitValue();
            board.squares[file][rank].hasChess=true;
            board.squares[file][rank].chessOnTheBoard=chessPiece(tmpThisType, otherSide);
        }
    }
    if(!otherSideHasKing) oneSideWin(curSide);
    update();
    checkBothSideCheckAndCursideStalement();
    if(curSide==mySide)
       startCountDown();
}


void boardWidget::paintEvent(QPaintEvent *)
{
    //if(width()<boardLength||height()<boardLength) return;
    int squareLength;
    int boardLength;
    if(width()>height()) squareLength=(height()-10)/8;
    else squareLength=(width()-10)/8;
    boardLength=8*squareLength;
    QPainter p(this);
    p.setPen(Qt::black);
    //start from bottom left
    int startX=(width()-boardLength)/2; int startY=height()-((height()-boardLength)/2);
    for(int i=1;i<=8;i++)//file
    {
        for(int j=1;j<=8;j++)//rank
        {
            const chessBoardSquare& curSquare=board.squares[i][j];
            if((i+j)%2==0) p.setBrush(Qt::gray);
            else p.setBrush(Qt::white);
            if(curSquare.selectable) p.setBrush(Qt::yellow);
            QRect tmpRect(startX+(i-1)*squareLength, startY-j*squareLength, squareLength, squareLength);
            frontRects[i][j]=tmpRect;
            p.drawRect(tmpRect);
            const chessPiece& curPiece=curSquare.chessOnTheBoard;
            if(curSquare.hasChess)
            {
                p.drawPixmap(tmpRect, getPixMap(curPiece.type,curPiece.side));
            }
        }
    }
}
