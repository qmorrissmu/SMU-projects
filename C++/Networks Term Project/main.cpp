#include <iostream>
#include <algorithm>
#include <fstream>
#include <nnode.h>
using namespace std;


float calcSlowDown(vector<NNode*> nodes, double nSize, int totalFlow)
{

    double totalSD;
    float SD;
    double fs;
    double wt;
    for(int i = 0; i < nSize; i++)
    {
        wt += static_cast<double>(nodes[i]->getWT());
    }
    SD = (totalFlow+wt)/totalFlow;
    return SD;

}

//distribution logic not quite right..was trying not to hardcode number of small vs large nodes
vector<NNode*> createNetwork(string type, double nSize, int seed)
{
    int smallCount = 0;
    int largeCount = 0;
    int smallTraffic = 0;
    int largeTraffic = 0;
    int totalTraffic = 0;
    vector<NNode*> nodes = vector<NNode*>();
    if(type == "pareto")
    {

        //create Pareto distribution of nodes
        for(int i = 0;i < nSize; i++)
        {
            double nPercent = static_cast<double>(i/nSize);
            NNode* node = new NNode();
            if(nPercent < 0.5)
            {
                node->setFS(1,seed);
                nodes.push_back(node);
                seed++;
                continue;
            }
            else if(nPercent > 0.5 && nPercent < 0.6)
            {
                node->setFS(2,seed);
                nodes.push_back(node);
                seed++;
                continue;
            }
            else if(nPercent > 0.6 && nPercent < 0.8)
            {
                node->setFS(3,seed);
                nodes.push_back(node);
                seed++;
                continue;
            }
            else if(nPercent > 0.8 && nPercent < 0.9)
            {
                node->setFS(4,seed);
                nodes.push_back(node);
                seed++;
                continue;
            }
            else if(nPercent > 0.9 && nPercent < 0.95)
            {
                node->setFS(5,seed);
                nodes.push_back(node);
                seed++;
                continue;
            }
            else
            {
                node->setFS(6,seed);
                nodes.push_back(node);
                seed++;
            }

        }

    }
    else if(type == "even")
    {
        //create even distribution of nodes
        for(int i = 0;i < nSize; i++)
        {
            double nPercent = static_cast<double>(i/nSize);
            NNode* node = new NNode();
            if(nPercent < 0.2)
            {
                node->setFS(1,seed);
                nodes.push_back(node);
                seed++;
                continue;
            }
            else if(nPercent > 0.2 && nPercent < 0.4)
            {
                node->setFS(2,seed);
                nodes.push_back(node);
                seed++;
                continue;
            }
            else if(nPercent > 0.4 && nPercent < 0.5)
            {
                node->setFS(3,seed);
                nodes.push_back(node);
                seed++;
                continue;
            }
            else if(nPercent > 0.5 && nPercent < 0.7)
            {
                node->setFS(4,seed);
                nodes.push_back(node);
                seed++;
                continue;
            }
            else if(nPercent > 0.7 && nPercent < 0.9)
            {
                node->setFS(5,seed);
                nodes.push_back(node);
                seed++;
                continue;
            }
            else
            {
                node->setFS(6,seed);
                nodes.push_back(node);
                seed++;
                continue;
            }

        }
    }
    else if(type == "normal")
    {
        //create Gaussian distribution of nodes
        for(int i = 0;i < nSize; i++)
        {
            NNode* node = new NNode();
            node->setFS(7,seed);
            nodes.push_back(node);
            seed++;
        }
    }

    //statistics of network
    for(int x = 0; x < nSize; x++)
    {
        if(nodes[x]->getFS() < 50)
        {
            smallCount += 1;
            smallTraffic += nodes[x]->getFS();
        }
        else
        {
            largeCount += 1;
            largeTraffic += nodes[x]->getFS();
        }

        totalTraffic += nodes[x]->getFS();
    }


    cout << "Percent of network w/ small FS: " << static_cast<double>(smallCount/nSize) << endl;
    cout << "Percent of network w/ large FS: " << static_cast<double>(largeCount/nSize) << endl;
    float pSmall = static_cast<float>(smallTraffic)/totalTraffic;
    float pLarge = static_cast<float>(largeTraffic)/totalTraffic;
    cout << "Percent of traffic from small FS: " << pSmall << endl;
    cout << "Percent of traffic from large FS: " << pLarge << endl;



    std::random_shuffle(nodes.begin(),nodes.end());
    return nodes;

}

//give each node a random destination node...issues here
void createDestination(double nSize, vector<NNode*> nodes, int num_collisions)
{
    int collisionCount = 0;
    int last_index = 0;
    int index = nSize-1;
    for(int i = 0; i < nSize; i++)
    {
        if(collisionCount < num_collisions)
        {
            collisionCount++;
        }
        else
        {
            index = rand() % static_cast<int>(nSize);
            while(last_index == index && index == i)
            {
                collisionCount = rand() % static_cast<int>(nSize);
            }
        }
        nodes[i]->setDestination(nodes[index]);
        last_index = index;
    }
}

//collision conditions
int checkCollision(NNode a, NNode b, int minLFS)
{
    if(a.getFS() < minLFS && b.getFS() < minLFS)
    {
        return 1;
    }
    else if(a.getFS() > minLFS && b.getFS() > minLFS)
    {
        return 2;
    }
    else if(a.getFS() < minLFS && b.getFS() > minLFS)
    {
        return 3;
    }
    else if(a.getFS() > minLFS && b.getFS() < minLFS)
    {
        return 4;
    }
    else
    {
        return 0;
    }
}

//retransmission
void retry(NNode*& a, NNode*& b, int exp)
{
    int aTry = rand() % a->getCW();
    int bTry = rand() % b->getCW();
    if(aTry == bTry)
    {
        exp += 1;
        a->setWT(exp);
        b->setWT(exp);
        a->setCW(a->backOff(exp,*a));
        b->setCW(b->backOff(exp,*b));
        retry(a,b,exp);
    }
    else
    {
        a->setWT(exp);
        b->setWT(exp);
    }

    return;
}

int tSlots_flow(int nSize, vector<NNode*> nodes)
{
    // gives all nodes a transmission spot and calculates total packets to be sent
    int totalFlow = 0;
    for (int i = 0; i < nSize; i++){
        nodes.at(i)->setTS(rand() % static_cast<int>(nodes.at(i)->getCW()));
        totalFlow += nodes.at(i)->getFS();
    }
    return totalFlow;
}

void backOff(NNode* node)
{
   int maxCW = 255;
   if((node->getCW()*node->getCW()) > maxCW)
   {
       node->setCW(maxCW);
   }
   else
   {
       node->setCW(node->getCW()*node->getCW());
   }

   node->setTS(node->getTS() + (rand() % static_cast<int>(node->getCW())));
}

int reTransmit(vector<NNode*> nodes,vector<pair<int,int>> vp, int totalFlow, bool intentional)
{
    if(vp.size()==1)
    {
        nodes[vp[0].second]->setWT(nodes[vp[0].second]->getWT());
        nodes[vp[0].second]->setFS(0);
        totalFlow = 0;
        return totalFlow;
    }

    if(intentional)
    {
        for(int x = 0; x < vp.size()-1; x++)
        {



                NNode* a = nodes[vp[x].second];
                NNode* b = nodes[vp[x+1].second];
                if(a->getFS() + a->getTS() <= b->getTS() && a!=b)
                {
                   totalFlow -= a->getFS();
                   a->setFS(0);
                   a->setWT(a->getWT() + a->getTS());

                }
                else if((a->getFS() + a->getTS() >= b->getTS()) && a!=b)
                {
                   if(a->getTS() > b->getTS())
                   {
                      continue;
                   }
                   a->setCW(5);
                   a->setFS(a->getFS()-(b->getTS()-a->getTS()));
                   totalFlow -= (b->getTS() - a->getTS());
                   if(a->getFS() <= b->getFS())
                   {
                       backOff(b);
                   }
                   else
                   {
                       backOff(a);
                   }
                }

            }

    }
    else
    {
        for(int x = 0; x < vp.size()-1; x++)
        {



                NNode* a = nodes[vp[x].second];
                NNode* b = nodes[vp[x+1].second];
                if(a->getFS() + a->getTS() <= b->getTS() && a!=b)
                {
                   totalFlow -= a->getFS();
                   a->setFS(0);
                   a->setWT(a->getWT() + a->getTS());

                }
                else if((a->getFS() + a->getTS() >= b->getTS()) && a!=b)
                {
                   if(a->getTS() > b->getTS())
                   {
                      continue;
                   }
                   a->setCW(5);
                   a->setFS(a->getFS()-(b->getTS()-a->getTS()));
                   totalFlow -= (b->getTS() - a->getTS());
                   backOff(a);
                   backOff(b);
                }



        }

    }



    vp.clear();
    return totalFlow;


}

//goes through nodes to check who they are trying to send to
void transmit(int nSize, vector<NNode*> nodes,int minLFS,bool intentional)
{
    int totalFlow = tSlots_flow(nSize,nodes);
    static int totalFlowCalc = totalFlow;
    //vector to hold elements with previous index
    vector<pair<int,int>> vp;
    //vector<NNode*> remainingNodes;
    for(int i = 0; i < nSize; i++)
    {
        if(nodes[i]->getFS()!=0)
        {
            vp.push_back(make_pair(nodes[i]->getTS(),i));
        }

    }

    //sort by TS
    sort(vp.begin(),vp.end());

    cout << "TS" << "\t" <<"FS" << "\t" <<"index" << endl;
    for(int i = 0; i < vp.size(); i++)
    {
        cout << vp[i].first << "\t" << nodes[vp[i].second]->getFS() << "\t" <<vp[i].second << endl;

    }
    cout << "-----------------------------------------"<<endl;


        if(intentional)
        {
            for(int i = 0; i < vp.size(); i++)
            {
                    for(int j = 0; j < vp.size(); j++)
                    {
                        int s1 = vp[i].first;
                        int s2 = vp[j].first;
                        int fs1 = nodes.at(vp[i].second)->getFS();
                        int fs2 = nodes.at(vp[j].second)->getFS();
                        if(s1 == s2 && i != j)
                        {
                            if(fs1 < fs2)
                            {
                                backOff(nodes.at(vp[j].second));
                            }
                            else if(fs1 > fs2)
                            {
                                backOff(nodes.at(vp[i].second));
                            }
                            else
                            {
                                backOff(nodes.at(vp[i].second));
                                backOff(nodes.at(vp[j].second));
                            }
                        }

                    }
            }

            //sort by TS
            sort(vp.begin(),vp.end());
            totalFlow = reTransmit(nodes,vp,totalFlow,intentional);
            if(totalFlow != 0)
            {
                transmit(nSize,nodes,minLFS,intentional);
            }
            else
            {
                float sd = calcSlowDown(nodes,nSize,totalFlowCalc);
                cout << "Avg Slowdown w/ intentional collisions: " << sd << endl;
                cout << "-----------------------------------------" << endl;

            }
        }
        else
        {
            for(int i = 0; i < nSize; i++)
                {
                    for(int j = 0; j < nSize; j++)
                    {
                        int s1 = vp[i].first;
                        int s2 = vp[j].first;
                        if(s1 == s2 && i != j)
                        {
                            backOff(nodes.at(vp[i].second));
                            backOff(nodes.at(vp[j].second));
                        }

                    }

                }


            //sort by TS
            sort(vp.begin(),vp.end());
            totalFlow = reTransmit(nodes,vp,totalFlow,intentional);
            if(totalFlow != 0)
            {
                transmit(nSize,nodes,minLFS,intentional);
            }
            else
            {
                float sd = calcSlowDown(nodes,nSize,totalFlowCalc);
                cout << "Avg Slowdown w/out intentional collisions: " << sd << endl;
                cout << "-----------------------------------------" << endl;

            }


            /*
            cout << "FS" << "\t" <<"index" << endl;
            for(int i = 0; i < nodes.size(); i++)
            {
                cout << nodes[i]->getFS() << "\t" << i << endl;
            }
            */


        }

    //transmit(nodes.size(),nodes,0,true);


    /*
    NNode* a;
    NNode* b;
    NNode* x;
    NNode* y;
    int intCollisions = 0;
    int regCollisions = 0;
    int exp = 1;

    //intentional collisions
    if(intentional == true)
    {
        for(int i = 0; i < nSize - 1; i++)
        {
            x = nodes[i];
            y = nodes[i+1];
            a = x->getDestination();
            b = y->getDestination();


            //if destinationos match, check collision conditions
            if(a == b)
            {
                int cc = checkCollision(*x,*y,minLFS);
                if(cc == 1 || cc == 2)
                {
                    //if both large or small flows
                    regCollisions += 1;
                    x->setCW(x->backOff(exp,*x));
                    y->setCW(y->backOff(exp,*y));
                    retry(*&x,*&y,exp);
                }
                else if(cc == 3)
                {
                    //if b is large and a is small
                    intCollisions += 1;
                    y->setCW(y->backOff(exp,*y));
                }
                else if(cc == 4)
                {
                    //if a is large and b is small
                    intCollisions += 1;
                    x->setCW(x->backOff(exp,*x));
                }
                else
                {
                    continue;
                }
            }
        }

        cout << "Intentional Collisions: " << intCollisions << endl;
        cout << "Regular Collisions: " << regCollisions << endl;
        cout << "Total Collisions: " << intCollisions+regCollisions << endl;

    }
    else
    {
        for(int i = 0; i < nSize - 1; i++)
        {
            x = nodes[i];
            y = nodes[i+1];
            a = x->getDestination();
            b = y->getDestination();

            if(a == b)
            {

                //come back to me
                regCollisions += 1;
                x->setCW(x->backOff(exp,*x));
                y->setCW(y->backOff(exp,*y));
                retry(*&x,*&y,exp);

            }
            else
            {
                continue;
            }
        }

        cout << "Total collisions: " << regCollisions << endl;
    }
    */


}


/*
void writeToFile(string type, double percentage){

    //Setting up a file writer to write to a file named fileName
    string fileName = "/home/student/Desktop/NetworkSimulator2" + to_string(percentage) + ".csv";
    ofstream myFile;
    myFile.open(fileName);

    //Creating vectors
    vector<NNode*> nodesT = vector<NNode*>();
    vector<NNode*> nodesF = vector<NNode*>();

    //Writing header
    myFile << "Nodes Transmitting" << "," << "Intentional Collision Slow Down" << "," << "No Intentional Collision Slow Down" << "," << "Change in Slow Down\n";

    for(int i = 1; i < 21; i++){

//--------transmitting with intentional collisions ---------------
        //setting variables to be changed for file writing
        double nSize = 5000*i;
        int numCollisions = percentage*nSize;

        //Setting network variables
        int minLFS = 50;
        int seed = time(nullptr) % 100;
        bool intentional = true;

        //creating network and transmitting
        nodesT = createNetwork(type,nSize,seed);
        createDestination(nSize,nodesT,numCollisions);
        transmit(nSize,nodesT,minLFS,intentional);

        //calculating slowdown
        double sdI = calcSlowDown(nodesT,nSize);

//--------transmitting with unintentional collisions -------------
        //Setting network variables
        intentional = false;

        //creating network and transmitting
        nodesF = createNetwork(type,nSize,seed);
        createDestination(nSize,nodesF,numCollisions);
        transmit(nSize,nodesF,minLFS,intentional);

        //calculating slowdown
        double sdNI = calcSlowDown(nodesF,nSize);

//------------end trasmission -----------------------------------
        double cip = ((sdNI-sdI)/sdNI)*100;

        nodesT.clear();
        nodesF.clear();

        //Writing info to file
        myFile << nSize << "," << sdI << "," << sdNI << "," << cip << "\n";
    }
    myFile.close();
}

*/

int main()
{
    //set up simulation with intentional collisions
    string type;
    type = "even";
    //writeToFile(type,0.7);

    bool intentional = true;
    vector<NNode*> nodesT = vector<NNode*>();
    double nSize = 9;
    int numCollisions = 0.5*nSize;
    int minLFS = 50;
    int seed = time(0);
    nodesT = createNetwork(type,nSize,seed);
    //createDestination(nSize,nodesT,numCollisions);
    transmit(nSize,nodesT,minLFS,intentional);
    //double sd1 = calcSlowDown(nodesT,nSize);


    //set up simulation without intentional collisions
    intentional = false;
    vector<NNode*> nodesF = vector<NNode*>();
    nodesF = createNetwork(type,nSize,seed);
    createDestination(nSize,nodesF,numCollisions);
    transmit(nSize,nodesF,minLFS,intentional);
    //double sd2 = calcSlowDown(nodesF,nSize);

   // cout << "Change in performance: " << ((sd2-sd1)/sd2)*100 << "%" << endl;


    return 0;
}
