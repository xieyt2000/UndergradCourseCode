#include "liquiddrop.h"

int liquidDrop::colorIndexCount=0;
liquidDrop::liquidDrop():color(coloursRep[colorIndexCount])
{

    colorIndexCount++;
    if(colorIndexCount>8) colorIndexCount=0;
}

liquidDrop::liquidDrop(const QColor& first, const QColor& second):
color(QColor((first.red()+second.red())/2,
       (first.green()+second.green())/2,
        (first.blue()+second.blue())/2))
{

}
