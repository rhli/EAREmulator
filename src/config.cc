#include <cstring>
#include "config.hh"

using namespace tinyxml2;

/**
 * Config reads settings from configure file
 */
config::config(){
  XMLDocument doc;
  doc.LoadFile("config/sysSetting.xml");
  XMLElement* element;
  for(element = doc.FirstChildElement("sysSetting")->FirstChildElement("attribute");
      element!=NULL;
      element=element->NextSiblingElement("attribute")){
    XMLElement* ele = element->FirstChildElement("name");
    if(strcmp(ele->GetText(),"nodePerRack")==0){
      _nodePerRack=atoi(ele->NextSiblingElement("value")->GetText());
    }else if(strcmp(ele->GetText(),"rackNum")==0){
      _rackNum=atoi(ele->NextSiblingElement("value")->GetText());
    }else if(strcmp(ele->GetText(),"ecN")==0){
      _ecN=atoi(ele->NextSiblingElement("value")->GetText());
    }else if(strcmp(ele->GetText(),"ecK")==0){
      _ecK=atoi(ele->NextSiblingElement("value")->GetText());
    }else if(strcmp(ele->GetText(),"replicaNum")==0){
      _replicaNum=atoi(ele->NextSiblingElement("value")->GetText());
    }else if(strcmp(ele->GetText(),"repPlaPolicy")==0){
      _repPlaPolicy=atoi(ele->NextSiblingElement("value")->GetText());
    }else if(strcmp(ele->GetText(),"blockSize")==0){
      _blockSize=atoi(ele->NextSiblingElement("value")->GetText());
    }else if(strcmp(ele->GetText(),"bandwidth")==0){
      _bandwidth=atof(ele->NextSiblingElement("value")->GetText())*72/125;
    }else if(strcmp(ele->GetText(),"writeInterval")==0){
      _writeInterval=atof(ele->NextSiblingElement("value")->GetText());
    }else if(strcmp(ele->GetText(),"inClusWriteProportion")==0){
      _inClusWritePercent=atof(ele->NextSiblingElement("value")->GetText());
    }else if(strcmp(ele->GetText(),"bgTrafficInterval")==0){
      _bgTrafficInterval=atof(ele->NextSiblingElement("value")->GetText());
    }else if(strcmp(ele->GetText(),"inRackTrafficProportion")==0){
      _inRackTrafficPercent=atof(ele->NextSiblingElement("value")->GetText());
    }else if(strcmp(ele->GetText(),"encodingStripeCount")==0){
      _encodingStripeCount=atof(ele->NextSiblingElement("value")->GetText());
    }else if(strcmp(ele->GetText(),"randSeed")==0){
      _randSeed=atof(ele->NextSiblingElement("value")->GetText());
    }else if(strcmp(ele->GetText(),"maxInRack")==0){
      _maxInRack=atof(ele->NextSiblingElement("value")->GetText());
    }else if(strcmp(ele->GetText(),"runTime")==0){
      _runTime=atoi(ele->NextSiblingElement("value")->GetText());
    }
  }
  _nodeNum=_rackNum*_nodePerRack;
}


