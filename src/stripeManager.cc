#include "stripeManager.hh"

stripeManager::stripeManager(config* c){
    _conf=c;
    _stripeQueue=NULL;
    _stripeCount=0;
    _repPlaPolicy=_conf->getRepPlaPolicy();
    _nodeNum=_conf->getNodeNum();
    _rackNum=_conf->getRackNum();
    _repFac=_conf->getReplicaNum();
    _ecN=_conf->getEcN();
    _ecK=_conf->getEcK();

    _blockCountInNode=(int*)calloc(_nodeNum,sizeof(int));
    _blockCountInRack=(int*)calloc(_rackNum,sizeof(int));

    _lGen=new layoutGen(_conf);
    _lGen->setRandomGen(new randomGen(12345));
    _striping=new striping(_conf);
}

int stripeManager::pushStripe(stripe* str){
    stripeNode* tmp=(stripeNode*)calloc(1,sizeof(stripeNode));
    tmp->_str=str;
    tmp->_next=NULL;
    if(_stripeQueue==NULL){
        _stripeQueue=tmp;
    }else{
        _sQueueTail->_next=tmp;
    }
    _sQueueTail=tmp;
    /* TODO: add striping time */

    _stripeCount++;
    return 0;
}

stripe* stripeManager::popStripe(){
    if(_stripeQueue==NULL){
        return NULL;
    }
    stripe* retVal=_stripeQueue->_str;
    stripeNode* tmp=_stripeQueue;
    _stripeQueue=_stripeQueue->_next;
    free(tmp);
    _stripeCount--;
    return retVal;
}

int stripeManager::strOp(){
    stripe* str;
    while((str=popStripe())!=NULL){
        //TODO: do striping ...
        int* loc=str->getLoc();
        //for(int i=0;i<_ecK*_repFac;i++){
        //    printf(i%3==0?"%4d":"%3d",loc[i]);
        //}
        //printf("\n");
        int* output=(int*)calloc(_ecN,sizeof(int));
        _striping->strOp(loc,output);
        str->setLoc(output);
        /* Numerical job */
        for(int i=0;i<_ecK*_repFac;i++){
            _blockCountInNode[loc[i]]--;
        }
        for(int i=0;i<_ecN;i++){
            //printf("%3d",output[i]);
            _blockCountInNode[output[i]]++;
        }
        free(loc);
    }
    return 0;
}

stripe* stripeManager::write(){
    stripe* retVal=new stripe(_conf);
    //puts("write(): before set loc");
    if(_repPlaPolicy==0){
        retVal->setLoc(_lGen->randomPla());
    }else{
        retVal->setLoc(_lGen->SOP());
    }
    //puts("write(): after set loc");
    addRepStripe(retVal->getLoc());
    pushStripe(retVal);
    return retVal;
}

int stripeManager::addRepStripe(int* loc){
    for(int i=0;i<_repFac*_ecK;i++){
        _blockCountInNode[loc[i]]++;
    }
    return 0;
}

int stripeManager::showNodeCapacity(){
    printf("stripeManager::showNodeCapacity():\n");
    for(int i=0;i<_nodeNum;i++){
        printf("Node %5d:%5d\n",i,_blockCountInNode[i]);
    }
    return 0;
}

int stripeManager::showRackCapacity(){
    //TODO: implement this
    return 0;
}




