#ifndef COMMAND_H
#define COMMAND_H

#include<QVector>
typedef QPair<int, int> posXY;
enum commandType{Input,Move,Split,Mix,Merge,Output, Merge2, Split2, Empty};

class command
{
public:
    int time;
    commandType type;
    QVector<posXY> corrs;
    ~command();
    bool operator< (const command& cmp);
};

#endif // COMMAND_H
