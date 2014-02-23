#ifndef _NODETREE_HH_
#define _NODETREE_HH_

#include <cstdio>
#include <cstdlib>
#include "Switch.hh"
#include "cpp.h"

typedef struct tNode{
    int _tNodeID;
    /* 
     * switch or host 
     * 0 for switch and 1 for host
     */
    int _type;
    int _childNum;
    Switch* _switch;
    tNode* _parent;
    tNode** _children;
    int _startHost;
    int _endHost;
}tNode;

/*
 * We use this class to simulate network traffic and run benchmark
 */
class NodeTree{
        tNode* _treeRoot;
        tNode** _hostList;
        tNode** _rackList;
        int _leafNum;
        int _nodeNum;
        int _maxDegree;
        int _rackNum;
        int _switchCount;

        int _maxLevel;

        /* 
         * Here is how we transfer our data:
         * Every time, we transfer the amount of _dataTransferOnce
         * until all the required data is transferred.
         */
        double _dataTransferOnce;
        double _bandwidth;

        int nameSwitches();
        int setSwitches(tNode*);
        int showSubTree(tNode*);
        /*
         * The returned array of getPath():
         * retVal[0] is the length of the array (not including itself)
         * the rest is the real array
         */
        int* getPath(int des,int src);
        tNode* getParent(tNode* node){return node->_parent;};
        Switch** _switchList;
        int setHostRange(tNode*);

        /* detect whether within the range of a switch */
        int isInSwitch(int node,tNode* tn);

    public:
        NodeTree(int leafNum,int maxChild);

        int showSwitches();
        int getRackNum(){return _rackNum;};
        //int* getRackList();
        int* getRackNodeList(int rackID);
        int dataTransfer(int des,int src,double size);
        /*
         * return a two elment array representing the range of hosts
         * sharing the same elments in some level
         */
        int* getNodeList(int nodeID,int level);
        int getMaxLevel(){return _maxLevel;}
        int* getRackRange(int rackID);
        int setBandwidth(double b){_bandwidth=b;return 0;};

        int getNearest(int,int,int*);
};

#endif

