#include "board.h"
#include<QMessageBox>
#include<QPointF>
#include<QColor>
#include<QFile>
#include<QTextStream>
#include<QtDebug>
#include<QTimer>
#include <QSound>
#include<QQueue>
#include<QEventLoop>
#include<QMediaPlayer>

board::board(QWidget *parent) : QWidget(parent)
{
    endBoards.resize(110);
    for(int i= 0; i<110;i++)
    {
        endBoards[i].resize(20);
        for(int j=0;j<20;j++)
        {
            endBoards[i][j].resize(20);
        }
    }
    for(auto i : endBoards)
    {
        endBoards.resize(110);
        i.resize(20);
        for(auto j : i)
        {
            j.resize(20);
        }
    }
    curEndBoard=endBoards[0];
}

void board::genRects(int r = 3, int c = 3 )
{
    if(r<3&&c<3)
    {
        dialogWarning("行列数同时小于3");
        return;
    }
    rectsToDraw.clear();
    rectsEdge.clear();
    row=r;column=c;
    int totalWidth=width()-10;
    int totalHeight=height()-10;
    wid=totalWidth/(column+2);
    hei=totalHeight/(row+2);
    for(int i=0; i<row+2; i++)
    {
        for(int j=0; j<column+2; j++)
        {
            QRectF tmpRec(j*wid,i*hei,wid,hei);
            if(i!=0&&j!=0&i!=row+1&j!=column+1) rectsToDraw.append(tmpRec);
            else rectsEdge.append(tmpRec);
        }
    }
}

void board::genInOut(QVector<posXY> in, posXY out)
{
    inputs.clear(); output=posXY(0,0);
    if(row==-1)
    {
        dialogWarning("请先设置行列数");
        return;
    }
    in.removeAll(posXY(0,0));
    if((out.first!=column&&out.first!=1)&&(out.second!=row&&out.second!=1))
    {
        dialogWarning("输出端口非法");
        return;
    }
    if(!posInBoardRange(out))
    {
        dialogWarning("输出端口非法");
        return;
    }
    bool validIn=true;
    for(auto i : in)
    {
        if((i.first!=column&&i.first!=1)&&(i.second!=row&&i.second!=1)) validIn=false;
        if(!posInBoardRange(i)) validIn=false;
        //else in.removeAll(i);
    }
    if(in.length()==0) validIn=false;
    if(!validIn)
    {
        dialogWarning("输入端口非法");
        return;
    }
    inputs=in;
    output=out;
}

void board::readFile(QString path)
{
    isRest=false;
    if(inputs.length()==0)
    {
        dialogWarning("请先设置输入输出");
        return;
    }
    cmdlist.clear();
    //initialize
    for(int i=0; i<=100; i++)
    {
        command ety; ety.type=Empty;
        QVector<command> ini;
        ini.append(ety);
        cmdlist.append(ini);
    }
    QFile f(path);
    if(!f.open(QIODevice::ReadOnly| QIODevice::Text))
    {
        dialogWarning("文件路径非法");
        return;
    }
    QTextStream input(&f);
    while (1) {
        QString line =input.readLine();
        if(line.size()==0) break;
        line.remove(";");
        QStringList lineSpace = line.split(" ");
        command tmp;
        QStringList numList=lineSpace[1].split(",");
        tmp.time=numList[0].toInt();
        if(tmp.time>totaltime) totaltime=tmp.time;
        for(int i=1; i<numList.size(); i+=2)
        {
            posXY tmpPos;
            tmpPos.first=numList[i].toInt();
            tmpPos.second=numList[i+1].toInt();
            if(!posInBoardRange(tmpPos))
            {
                dialogWarning("坐标越界");
                return;
            }
            tmp.corrs.append(tmpPos);
        }

        if(lineSpace[0]=="Input")
        {
            tmp.type=Input;
            bool flag=false;
            for(auto i : inputs)
            {
                if(i==tmp.corrs[0])
                {
                    flag=true;
                    break;
                }
            }
            if(!flag)
            {
                dialogWarning("非法Input于"+numList[0]+"步");
                //return;
            }
        }
        if(lineSpace[0]=="Move") tmp.type=Move;
        if(lineSpace[0]=="Merge") tmp.type=Merge;
        if(lineSpace[0]=="Split") tmp.type=Split;
        if(lineSpace[0]=="Mix") tmp.type=Mix;
        if(lineSpace[0]=="Output")
        {
            tmp.type=Output;
            if(tmp.corrs[0]!=output)
            {
                dialogWarning("非法Output于"+numList[0]+"步");
                //return;
            }
        }
        if(tmp.type==Mix)
        {
            for(int j=0;j<tmp.corrs.length()-1;j++)
            {
                command tmp2;
                tmp2.type=Move;
                tmp2.time=tmp.time+j;
                tmp2.corrs.append(tmp.corrs[j]);
                tmp2.corrs.append(tmp.corrs[j+1]);
                cmdlist[tmp2.time].append(tmp2);
            }
        }
        else if (tmp.type==Merge) {
            cmdlist[tmp.time].append(tmp);
            command tmp2=tmp;
            tmp2.type=Merge2;
            cmdlist[tmp.time+1].append(tmp2);
        }
        else if (tmp.type==Split) {
            cmdlist[tmp.time].append(tmp);
            command tmp2=tmp;
            tmp2.type=Split2;
            cmdlist[tmp.time+1].append(tmp2);
        }
        else {
            cmdlist[tmp.time].push_back(tmp);
        }
    }
    exeut(totaltime);
    //distanceCheck();
    f.close();
}

void board::exeut(int targetTime,int starttime)
{
    sounds.resize(110);
    //int liquidDropIdCount=0;
    //liquidDrops.clear();
    for(int tmpTime=starttime;tmpTime<=targetTime; tmpTime++)
    {
        QVector<command> cmdsThisTime=cmdlist[tmpTime];
        QVector<QVector<square>>& endBoard = endBoards[tmpTime];
        if(tmpTime>0) endBoard=endBoards[tmpTime-1];
        for(int k=0; k <cmdsThisTime.length(); k++)
        {
            command i=cmdsThisTime[k];
            switch (i.type) {
            case Input:
            {
                posXY cmdPos=i.corrs[0];
                if(endBoard[cmdPos.first][cmdPos.second].liquidId!=-1)
                {
                    dialogWarning("非法Input");
                    return;
                }
                liquidDrop tmp;
                tmp.id=liquidDropIdCount;
                tmp.dropCorr=cmdPos;
                liquidDropIdCount++;
                liquidDrops.append(tmp);
                endBoard[cmdPos.first][cmdPos.second].liquidId=tmp.id;
                endBoard[cmdPos.first][cmdPos.second].contaminateID.insert(tmp.id);
                endBoard[cmdPos.first][cmdPos.second].contaColor=tmp.color;
                break;
            }
            case Empty: break;
            case Output:
            {
                posXY cmdPos=i.corrs[0];
                int curLiquidId=endBoard[cmdPos.first][cmdPos.second].liquidId;
                if(endBoard[cmdPos.first][cmdPos.second].liquidId==-1)
                {
                    dialogWarning("非法Output");
                    return;
                }
                endBoard[cmdPos.first][cmdPos.second].liquidId=-1;
                break;
            }
            case Mix: break;
            case Merge:
            {
                posXY first=i.corrs[0]; posXY second = i.corrs[1];
                posXY mid;
                bool direction;//only mid one has this trait. false is left&right true is up&down
                if(first.first!=second.first)//leftright
                {
                    direction=false;
                    mid.first=(first.first+second.first)/2;
                    mid.second=first.second;
                }
                else
                {
                    direction=true;
                    mid.first=first.first;
                    mid.second=(first.second+second.second)/2;
                }
                int firstID=endBoard[first.first][first.second].liquidId;
                int secondID=endBoard[second.first][second.second].liquidId;
                liquidDrop toAdd(liquidDrops[firstID].color, liquidDrops[secondID].color);
                toAdd.id=liquidDropIdCount;
                liquidDropIdCount++;
                toAdd.dropCorr=mid;
                liquidDrops.push_back(toAdd);
                endBoard[mid.first][mid.second].liquidId=toAdd.id;
                endBoard[mid.first][mid.second].mergingOrSpliting=true;
                endBoard[mid.first][mid.second].mergeOrSlitingDirection=direction;
                endBoard[first.first][first.second].dontDraw=true;
                endBoard[second.first][second.second].dontDraw=true;
                endBoard[second.first][second.second].liquidId=toAdd.id;
                endBoard[first.first][first.second].liquidId=toAdd.id;
                endBoard[second.first][second.second].contaminateID.insert(toAdd.id);
                endBoard[first.first][first.second].contaminateID.insert(toAdd.id);
                endBoard[mid.first][mid.second].contaminateID.insert(toAdd.id);
                endBoard[second.first][second.second].contaColor=toAdd.color;
                endBoard[first.first][first.second].contaColor=toAdd.color;
                endBoard[mid.first][mid.second].contaColor=toAdd.color;
                break;
            }
            case Merge2:
            {
                sounds[tmpTime].insert(mergesuccessSound);
                posXY first=i.corrs[0]; posXY second = i.corrs[1];
                posXY mid;
                bool direction;//only mid one has this trait. false is left&right true is up&down
                if(first.first!=second.first)//leftright
                {
                    direction=false;
                    mid.first=(first.first+second.first)/2;
                    mid.second=first.second;
                }
                else
                {
                    direction=true;
                    mid.first=first.first;
                    mid.second=(first.second+second.second)/2;
                }
                endBoard[mid.first][mid.second].mergingOrSpliting=false;
                endBoard[second.first][second.second].liquidId=-1;
                endBoard[first.first][first.second].liquidId=-1;
                endBoard[first.first][first.second].dontDraw=false;
                endBoard[second.first][second.second].dontDraw=false;
                break;
            }
            case Split:
            {
                sounds[tmpTime].insert(split1Sound);
                posXY mid=i.corrs[0]; posXY first=i.corrs[1]; posXY second=i.corrs[2];
                bool direction;
                if(first.first!=second.first)//leftright
                {
                    direction=false;
                }
                else
                {
                    direction=true;
                }
                int midId=endBoard[mid.first][mid.second].liquidId;
                liquidDrop midDrop=liquidDrops[findLiquidIndexByID(midId)];
                endBoard[first.first][first.second].dontDraw=midId;
                endBoard[second.first][second.second].dontDraw=midId;
                endBoard[first.first][first.second].contaminateID.insert(midId);
                endBoard[second.first][second.second].contaminateID.insert(midId);
                endBoard[first.first][first.second].contaColor=midDrop.color;
                endBoard[second.first][second.second].contaColor=midDrop.color;
                endBoard[mid.first][mid.second].mergingOrSpliting=true;
                endBoard[mid.first][mid.second].mergeOrSlitingDirection=direction;
                endBoard[first.first][first.second].dontDraw=true;
                endBoard[second.first][second.second].dontDraw=true;
                break;
            }
            case Split2:
            {
                sounds[tmpTime].insert(split2Sound);
                posXY mid=i.corrs[0]; posXY first=i.corrs[1]; posXY second=i.corrs[2];
                bool direction;
                if(first.first!=second.first)//leftright
                {
                    direction=false;
                }
                else
                {
                    direction=true;
                }
                liquidDrop firstDrop; liquidDrop secondDrop;
                firstDrop.id=liquidDropIdCount; liquidDropIdCount++;
                secondDrop.id=liquidDropIdCount; liquidDropIdCount++;
                firstDrop.dropCorr=first; secondDrop.dropCorr=second;
                liquidDrops.push_back(firstDrop); liquidDrops.push_back(secondDrop);
                endBoard[first.first][first.second].liquidId=firstDrop.id;
                endBoard[first.first][first.second].contaminateID.insert(firstDrop.id);
                endBoard[first.first][first.second].contaColor=firstDrop.color;
                endBoard[first.first][first.second].immueContaAfterSplit=true;
                endBoard[second.first][second.second].liquidId=secondDrop.id;
                endBoard[second.first][second.second].contaminateID.insert(secondDrop.id);
                endBoard[second.first][second.second].contaColor=secondDrop.color;
                endBoard[second.first][second.second].immueContaAfterSplit=true;
                endBoard[mid.first][mid.second].liquidId=-1;
                endBoard[mid.first][mid.second].mergingOrSpliting=false;
                endBoard[first.first][first.second].dontDraw=false;
                endBoard[second.first][second.second].dontDraw=false;
                break;
            }
            case Move:
            {
                sounds[tmpTime].insert(movemixSound);
                posXY changingPos=i.corrs[0];
                if(endBoard[changingPos.first][changingPos.second].liquidId==-1)
                {
                    dialogWarning("非法Move");
                    break;
                }
                int tmpId=endBoard[changingPos.first][changingPos.second].liquidId;
                endBoard[changingPos.first][changingPos.second].liquidId=-1;
                changingPos=i.corrs[1];
                endBoard[changingPos.first][changingPos.second].liquidId=tmpId;
                endBoard[changingPos.first][changingPos.second].contaminateID.insert(tmpId);
                endBoard[changingPos.first][changingPos.second].contaColor=liquidDrops[findLiquidIndexByID(tmpId)].color;
                liquidDrops[findLiquidIndexByID(tmpId)].dropCorr=changingPos;
                break;
            }
            }
        }
        if(distanceCheck(tmpTime-1)) return;
    }
    endBoards[totaltime+1]=endBoards[totaltime];
    if(distanceCheck(targetTime)) return;
}

void board::defaultPlay()
{
    if(CurTime>totaltime) return;
    if(isPause) return;
    if(isRest) return;
    if(totaltime==0) return;
    //play music
    if(CurTime!=-1)
    {
        QSet<soundType> thistimeSounds = sounds[CurTime];
        for(auto i : thistimeSounds)
        {
            switch (i) {
            case movemixSound:
                QSound::play("move.wav");
                break;
            case mergesuccessSound:
                QSound::play("merge.wav");
                break;
            case split1Sound:
                QSound::play("split1.wav");
                break;
            case split2Sound:
                QSound::play("split2.wav");
                break;
            }
    }
    //show

    QEventLoop eventloop;
    QTimer::singleShot(playSpeed, &eventloop, SLOT(quit()));
    eventloop.exec();
    //show and do something
    CurTime++;
    curEndBoard=endBoards[CurTime];
    this->update();
    emit this->timeChange(CurTime+1);
    if(CurTime>1&&wash)
    {
        washShow();
        endBoards[CurTime]=curEndBoard;
        exeut(totaltime, CurTime+1);
    }
    defaultPlay();
    }
}

void board::playNext()
{
    if(totaltime==0) return;
    if(CurTime>totaltime) return;
    if(CurTime!=-1)
    {
        QSet<soundType> thistimeSounds = sounds[CurTime+1];
        for(auto i : thistimeSounds)
        {
            switch (i) {
            case movemixSound:
                QSound::play("move.wav");
                break;
            case mergesuccessSound:
                QSound::play("merge.wav");
                break;
            case split1Sound:
                QSound::play("split1.wav");
                break;
            case split2Sound:
                QSound::play("split2.wav");
                break;
            }
        }
    }
    CurTime++;
    curEndBoard=endBoards[CurTime];
    this->update();
    emit this->timeChange(CurTime+1);
    if(CurTime>1&&wash)
    {
        washShow();
        endBoards[CurTime]=curEndBoard;
        exeut(totaltime, CurTime+1);
    }
}

void board::playPrev()
{
    if(totaltime==0) return;
    if(wash)
    {
        dialogWarning("清洗开启时不能上一步");
        return;
    }
    if(CurTime<0) return;
    CurTime--;
    if(CurTime==-1) curEndBoard=endBoards[105];
    else curEndBoard=endBoards[CurTime];
    this->update();
    emit this->timeChange(CurTime+1);
}

void board::reset()
{
    /*
    endBoards[0].clear();
    endBoards[0].resize(20);
    for(int j=0;j<20;j++)
    {
        endBoards[0][j].resize(20);
    }
    exeut(totaltime);
    */
    CurTime=-1;
    curEndBoard=endBoards[105];
    this->update();
    emit this->timeChange(0);
}

void board::restart()
{
    emit this->timeChange(0);
    isPause=false;
    rectsToDraw.clear();
    rectsEdge.clear();
    row=-1; column=-1;
    output=posXY(0,0);
    inputs.clear();
    wid=0; hei=0;
    cmdlist.clear(); liquidDrops.clear();
    endBoards.clear(); CurTime=-1;
    curEndBoard.clear(); totaltime=0;
    update();
    sounds.clear();
    isRest=true;
}

void board::changePauseStatus()
{
    isPause=!isPause;
    defaultPlay();
}

void board::changeSpeed(int scrollPos)
{
    playSpeed=1000+10*(scrollPos-50);
}

void board::setWash(bool wa)
{
    wash=wa;
    if(wa)
    {
        if(inputs.size()==0)
        {
            dialogWarning("请先设置输入输出");
            return;
        }
        washIn=posXY(1,row);
        washOut=posXY(column,1);
        for(auto i : inputs)
        {
            if(i==washIn||i==washOut)
            {
                dialogWarning("输入端口与清洗冲突，请重置设置");
                return;
            }
        }
        if(output==washIn||output==washOut)
        {
            dialogWarning("输出端口与清洗冲突，请重置设置");
            return;
        }
    }
}

void board::washShow()
{
    //mark board
    bool squaresCanGo[20][20];
    for(int i=0;i<20; i++)
    {
        for(int j=0;j<20;j++)
        {
            squaresCanGo[i][j]=false;
        }
    }
    for(int i=1;i<=column;i++)
    {
        for(int j=1;j<=row;j++)
        {
            squaresCanGo[i][j]=true;
        }
    }
    for(int i=1;i<=column;i++)
    {
        for(int j=1;j<=row;j++)
        {
            if(curEndBoard[i][j].liquidId!=-1)
            {
                if(curEndBoard[i][j].testContaHappen())
                {
                    bool merOrSpl=curEndBoard[i-1][j].mergingOrSpliting
                            ||curEndBoard[i+1][j].mergingOrSpliting
                            ||curEndBoard[i][j-1].mergingOrSpliting
                            ||curEndBoard[i][j+1].mergingOrSpliting;
                    if(!merOrSpl) dialogWarning("发生无法清洗的污染");
                }
                for(int p=i-1;p<=i+1;p++)
                {
                    for(int q=j-1;q<=j+1;q++)
                    {
                        squaresCanGo[p][q]=false;
                    }
                }
            }
            if(curEndBoard[i][j].barred)
            {
                squaresCanGo[i][j]=false;
            }
        }
    }
    if(!squaresCanGo[washIn.first][washIn.second]) return;
    //find all the squres can reach from wash in
    QVector<QVector<posXY>> squaresCanReach; //record prev squre, if cannot reach recor 0
    squaresCanReach.resize(20);
    for(int i =0;i<20;i++)
    {
        squaresCanReach[i].resize(20);
    }
    bool visited[20][20];
    for(int i=0;i<20; i++)
    {
        for(int j=0;j<20;j++)
        {
            visited[i][j]=false;
            squaresCanReach[i][j]=posXY(0,0);
        }
    }
    QQueue<posXY> BFS;
    BFS.enqueue(washIn);
    while (!BFS.empty()) {
        posXY BFSstart= BFS.dequeue();
        int x=BFSstart.first; int y=BFSstart.second;
        if(squaresCanGo[x-1][y]&&!visited[x-1][y])
        {
            visited[x-1][y]=true;
            BFS.enqueue(posXY(x-1,y));
            squaresCanReach[x-1][y]=posXY(x,y);
        }
        if(squaresCanGo[x+1][y]&&!visited[x+1][y])
        {
            visited[x+1][y]=true;
            BFS.enqueue(posXY(x+1,y));
            squaresCanReach[x+1][y]=posXY(x,y);
        }
        if(squaresCanGo[x][y-1]&&!visited[x][y-1])
        {
            visited[x][y-1]=true;
            BFS.enqueue(posXY(x,y-1));
            squaresCanReach[x][y-1]=posXY(x,y);
        }
        if(squaresCanGo[x][y+1]&&!visited[x][y+1])
        {
            visited[x][y+1]=true;
            BFS.enqueue(posXY(x,y+1));
            squaresCanReach[x][y+1]=posXY(x,y);
        }
    }
    if(squaresCanReach[washOut.first][washOut.second]==posXY(0,0)) return;
    QVector<posXY> in2outRoute;//reverse
    for(posXY changing=washOut; changing!=washIn; changing=squaresCanReach[changing.first][changing.second])
    {
        in2outRoute.append(changing);
    }
    in2outRoute.append(washIn);
    for(int i=1;i<=column;i++)
    {
        for(int j=1;j<=row;j++)
        {
            if((curEndBoard[i][j].contaminateID.size())>0&&(squaresCanReach[i][j]!=posXY(0,0)))
            {
                //now we can wash this
                //find the route first
                QVector<posXY> route; posXY changing=posXY(i,j); //route reverse
                while (changing!=washIn) {
                    route.append(changing);
                    changing=squaresCanReach[changing.first][changing.second];
                }
                route.append(washIn);
                //show the process of wash this point and change the curEndboard
                for(int k=route.length()-1;k>=0;k--)
                {
                    square& oprSquare=curEndBoard[route[k].first][route[k].second];
                    if(k!=route.length()-1) curEndBoard[route[k+1].first][route[k+1].second].hasWash=false;
                    oprSquare.contaminateID.clear();
                    oprSquare.hasWash=true;
                    QEventLoop eventloop;
                    QTimer::singleShot(playSpeed/10, &eventloop, SLOT(quit()));
                    eventloop.exec();
                    this->update();
                }
                //go back to input
                for(int k=0;k<route.length();k++)
                {
                    square& oprSquare=curEndBoard[route[k].first][route[k].second];
                    if(k!=0) curEndBoard[route[k-1].first][route[k-1].second].hasWash=false;
                    oprSquare.hasWash=true;
                    QEventLoop eventloop;
                    QTimer::singleShot(playSpeed/10, &eventloop, SLOT(quit()));
                    eventloop.exec();
                    this->update();
                }
            }
        }
    }
    //go to output
    if(!curEndBoard[washIn.first][washIn.second].hasWash) return;
    for(int k=in2outRoute.length()-1;k>=0;k--)
    {
        square& oprSquare=curEndBoard[in2outRoute[k].first][in2outRoute[k].second];
        if(k!=in2outRoute.length()-1) curEndBoard[in2outRoute[k+1].first][in2outRoute[k+1].second].hasWash=false;
        oprSquare.contaminateID.clear();
        oprSquare.hasWash=true;
        QEventLoop eventloop;
        QTimer::singleShot(playSpeed/10, &eventloop, SLOT(quit()));
        eventloop.exec();
        this->update();
        if(k==0)
        {
            oprSquare.hasWash=false;
            QEventLoop eventloop;
            QTimer::singleShot(playSpeed/10, &eventloop, SLOT(quit()));
            eventloop.exec();
            this->update();
        }
    }
}

void board::paintEvent(QPaintEvent *ev)
{

    //draw squares
    if(row==-1) return;
    QPainter p(this);
    QPen pen(Qt::SolidLine);
    p.setPen(pen);
    p.drawRects(rectsToDraw);
    //draw barred
    for(int i=0; i<rectsToDraw.length();i++)
    {
        int y=i/column+1; int x=i%column+1;
        if(curEndBoard[x][y].barred)
        {
            p.setBrush(Qt::white);
            p.drawRect(rectsToDraw[i]);
        }
    }
    //draw out and in
    if(output.first==0) return;
    QRectF outRect=getEdgeRec(output.first, output.second);
    p.setBrush(QColor(115,115,255));
    p.drawRect(outRect);
    p.drawText(outRect,Qt::AlignCenter, "Output");
    if(inputs.length()==0) return;
    p.setBrush(QColor(255, 199, 161));
    for(auto i :inputs)
    {
        QRectF in=getEdgeRec(i.first,i.second);
        p.drawRect(in);
        p.drawText(in, Qt::AlignCenter, "Input");
    }
    //draw wash
    if(wash)
    {
        QRectF washOutRect=getEdgeRec(washOut.first, washOut.second);
        p.setBrush(QColor(166,155,103));
        p.drawRect(washOutRect);
        p.drawText(washOutRect, Qt::AlignCenter, "Waste");
        QRectF washInRect=getEdgeRec(washIn.first,washIn.second);
        p.setBrush(QColor(172,204,230));
        p.drawRect(washInRect);
        p.drawText(washInRect, Qt::AlignCenter, "Wash input");
    }
    //draw contaminate
    if(cmdlist.length()==0) return;
    for(int i=1; i<=column; i++)
    {
        for(int j=1; j<=row; j++)
        {
            square oprSquare=curEndBoard[i][j];
            QRectF tarRec=getSquareRec(i, j);
            int conNum=oprSquare.contaminateID.size();
            if(conNum<1) continue;
            p.setPen(oprSquare.contaColor);
            QString conNumstr=QString::number(conNum);
            p.drawText(tarRec, Qt::AlignCenter, conNumstr);
        }
    }
    p.setPen(pen);
    //draw liquid  wash included
    if(cmdlist.length()==0) return;
    for(int i=1; i<=column;i++)
    {
        for(int j=1; j<=row; j++)
        {
            square oprSquare=curEndBoard[i][j];
            if(oprSquare.hasWash)
            {
                p.setBrush(Qt::blue);
                p.drawEllipse(getSquareRec(i, j));
            }
            if(oprSquare.dontDraw) continue;
            if(oprSquare.liquidId==-1) continue;
            liquidDrop oprDrop=liquidDrops[findLiquidIndexByID(oprSquare.liquidId)];
            p.setBrush(oprDrop.color);
            if(oprSquare.mergingOrSpliting)
            {
                if(oprSquare.mergeOrSlitingDirection)//upanddown
                {
                    QRectF tmp(getSquareRec(i,j-1).topLeft(), getSquareRec(i,j+1).bottomRight());
                    p.drawEllipse(tmp);
                }
                else //left and right
                {
                    QRectF tmp(getSquareRec(i-1,j).topLeft(),getSquareRec(i+1, j).bottomRight());
                    p.drawEllipse(tmp);
                }
                continue;
            }
            p.drawEllipse(getSquareRec(i, j));
        }
    }
}

QRectF &board::getEdgeRec(int x, int y)
{
    if(y==1) return rectsEdge[x];
    if(y==row) return rectsEdge[column+2*row+x+2];
    if(x==1) return rectsEdge[column+2*y];
    return rectsEdge[column+2*y+1];
}

QRectF &board::getSquareRec(int x, int y)
{
    return rectsToDraw[column*(y-1)+x-1];
}

void board::dialogWarning(QString text)
{
    if(text=="") return;
    QMessageBox warDialog;
    warDialog.setText(text);
    warDialog.exec();
}

int board::findLiquidIndexByID(int id)
{
    for(int i=0;i< liquidDrops.length();i++)
    {
        if(liquidDrops[i].id==id) return i;
    }
}

int board::distanceCheck(int k)//k is time
{
        if(k<0) return 0;
        //static
        const QVector<QVector<square>>& bdThisTime=endBoards[k];
        for(int i=1;i<=column;i++)
        {
            for(int j=1; j<=row; j++)
            {
                if(bdThisTime[i][j].liquidId!=-1)
                {
                    for(int i_=i-1;i_<=i+1;i_++)
                    {
                        for(int j_=j-1; j_<=j+1; j_++)
                        {
                            if(bdThisTime[i_][j_].liquidId!=-1&&bdThisTime[i_][j_].liquidId!=bdThisTime[i][j].liquidId)
                            {
                                QString wrongTime=QString::number(k+1);
                                QString wrongX=QString::number(i); QString wrongY=QString::number(j);
                                dialogWarning("在第"+wrongTime+"步"+wrongX+" ,"+wrongY+"处违反静态约束，播放以检查");
                                return 1;
                            }
                        }
                    }
                }
            }
        }
        //dynamic
        if(k==totaltime) return 0;
        const QVector<QVector<square>>& bdNextTime=endBoards[k+1];
        for(int i=1;i<=column;i++)
        {
            for(int j=1; j<=row; j++)
            {
                if(bdThisTime[i][j].liquidId!=-1)
                {
                    posXY nextPos =findLiquidOnBoard(bdThisTime[i][j].liquidId, bdNextTime);
                    if(nextPos.first==i&&nextPos.second==j) continue;
                    if(nextPos.first==0&nextPos.second==0) continue;
                    int nextX=nextPos.first; int nextY=nextPos.second;
                    for(int i_=nextX-1;i_<=nextX+1;i_++)
                    {
                        for(int j_=nextY-1; j_<=nextY+1; j_++)
                        {
                            if(bdThisTime[i_][j_].liquidId!=-1&&bdThisTime[i_][j_].liquidId!=bdThisTime[i][j].liquidId)
                            {
                                QString wrongTime=QString::number(k+1);
                                QString wrongX=QString::number(i); QString wrongY=QString::number(j);
                                dialogWarning("在第"+wrongTime+"步"+wrongX+" ,"+wrongY+"处违反动态约束，播放以检查");
                                return 1;
                            }
                        }
                    }
                }
            }
        }
    return 0;
}

posXY board::findLiquidOnBoard(int id, const QVector<QVector<square>>& bdToFind)
{
    for(int i=1;i<=column;i++)
    {
        for(int j=1; j<=row; j++)
        {
            if(bdToFind[i][j].liquidId==id) return posXY(i,j);
        }
    }
    return posXY(0,0);
}

bool board::posInBoardRange(posXY test)
{
    if(test.first<1||test.first>column) return  false;
    if(test.second<1||test.second>row) return false;
    return true;
}

void board::mousePressEvent(QMouseEvent *event)
{
    if(!wash) return;
    if(event->button()==Qt::RightButton)
    {
        int X=event->pos().x(); int Y=event->pos().y();
        for(int i=0; i<rectsToDraw.size(); i++)
        {
            const QRectF& tmpRect=rectsToDraw[i];
            if(X>tmpRect.left()&&X<tmpRect.right()&&Y>tmpRect.top()&&Y<tmpRect.bottom())
            {
                int y=i/column+1; int x=i%column+1;
                curEndBoard[x][y].barred=!curEndBoard[x][y].barred;
                update();
                for(int j=0; j<endBoards.length(); j++)
                {
                    endBoards[j][x][y].barred=!endBoards[j][x][y].barred;
                }
            }
        }
    }
}

