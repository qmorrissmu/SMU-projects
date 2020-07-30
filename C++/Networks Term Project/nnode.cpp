#include "nnode.h"

NNode::NNode()
{
    cw = 5;
    waitTime = 0;
}

void NNode::setTS(int ts)
{
    transmit_slot = ts;
}

int NNode::getTS()
{
    return transmit_slot;
}

void NNode::setWT(int t)
{
    waitTime += t;
}

int NNode::getWT()
{
    return waitTime;
}
void NNode::setFS(int size)
{
    fs = size;
}
void NNode::setFS(int size,int seed)
{
    srand(seed);
    if(size == 1)
    {
        //generate number between 1 and 10
        fs = (rand() % 10) + 1;
    }
    else if(size == 2)
    {
        //generate number between 11 and 20
        fs = 11 + (rand() % (20-11+1));
    }
    else if(size == 3)
    {
        //generate number between 21 and 50
        fs = 21 + (rand() % (50-21+1));
    }
    else if(size == 4)
    {
        //generate number between 51 and 100
        fs = 51 + (rand() % (100-51+1));
    }
    else if(size == 5)
    {
        //generate number between 101 and 500
        fs = 101 + (rand() % (500-101+1));
    }
    else if(size == 6)
    {
        //generate number between 501 and 1000
        fs = 501 + (rand() % (1000-501+1));
    }
    else if(size == 7)
    {
        //generate number between 1 and 1000
        fs = (rand() % 1000) + 1;
    }
}

int NNode::getFS()
{
    return fs;
}

unsigned long long NNode::powInt(long long base,long long exp)
{
    unsigned long long result = 1;
    for(int i = 0; i < exp; i++)
    {
        result *= base;
    }
    return result;

}

unsigned long long NNode::getCW()
{
    return cw;
}

void NNode::setCW(int c)
{
    cw = c;
}

unsigned long long NNode::backOff(long long i,NNode& n)
{
    return powInt(n.getCW(),i);
}

NNode* NNode::getDestination()
{
    return destination;
}

void NNode::setDestination(NNode*& n)
{
    destination = n;
}
