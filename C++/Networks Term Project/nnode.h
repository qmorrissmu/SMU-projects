#ifndef NNODE_H
#define NNODE_H
#include <string.h>
#include <random>
#include <cmath>
using namespace std;

class NNode
{
private:
    int fs;
    unsigned long long cw;
    NNode* destination;
    int waitTime;
    int transmit_slot;
public:
    NNode();
    void setTS(int);
    int getTS();
    void setWT(int);
    int getWT();
    void setFS(int,int);
    void setFS(int);
    int getFS();
    unsigned long long backOff(long long,NNode&);
    unsigned long long getCW();
    void setCW(int c);
    unsigned long long powInt(long long,long long);
    void setDestination(NNode*&);
    NNode* getDestination();
    bool operator==(NNode nnode_to_compare)
    {
        if(this->fs == nnode_to_compare.getFS() && this->cw == nnode_to_compare.getCW() && this->waitTime == nnode_to_compare.getWT())
        {
            return true;
        }
        return false;
    }
    NNode* operator= (NNode* nnode_to_equal)
    {
        this->cw = nnode_to_equal->getCW();
        this->fs = nnode_to_equal->getFS();
        this->waitTime = nnode_to_equal->getWT();
        this->destination = nnode_to_equal->getDestination();
        return this;
    }

};

#endif // NNODE_H
