#include "command.h"

command::~command()
{

}

bool command::operator<(const command &cmp)
{
    return (time<cmp.time);
}
