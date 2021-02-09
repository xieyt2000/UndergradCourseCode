#ifndef LIQUIDDROP_H
#define LIQUIDDROP_H
#include <QColor>
#include<QPair>
typedef QPair<int, int> posXY;

class liquidDrop
{
private:
    QColor coloursRep[9] = {QColor("cyan"), QColor("magenta"), QColor("red"),
                          QColor("darkRed"), QColor("darkCyan"), QColor("darkMagenta"),
                          QColor("green"), QColor("darkGreen"), QColor("yellow")};
public:
    static int colorIndexCount;
    liquidDrop();
    int id;
    QColor color;
    posXY dropCorr;
    liquidDrop(const QColor&, const QColor&);

};

#endif // LIQUIDDROP_H
