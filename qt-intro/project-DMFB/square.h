#ifndef SQUARE_H
#define SQUARE_H
#include<QPair>
#include<QSet>
#include<QColor>

typedef QPair<int, int> posXY;

class square
{
public:
    QSet<int> contaminateID; //to liquid ID
    QColor contaColor=Qt::black;
    int liquidId=-1;
    bool mergingOrSpliting = false;
    bool mergeOrSlitingDirection = false; //only mid one has this trait. false is left&right true is up&down
    bool dontDraw=false;
    bool barred=false; //click to set bar
    bool hasWash=false;
    bool testContaHappen();
    bool immueContaAfterSplit=false;
};

#endif // SQUARE_H
