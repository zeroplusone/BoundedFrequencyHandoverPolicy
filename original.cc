/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Vikas Pushkar (Adapted from third.cc)
 */


#include "ns3/core-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/csma-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/wifi-module.h"
#include "ns3/mobility-module.h"
#include "ns3/internet-module.h"
#include "ns3/netanim-module.h"
#include "ns3/basic-energy-source.h"
#include "ns3/simple-device-energy-model.h"
#include "ns3/lte-helper.h"
#include "ns3/ptr.h"
#include "ns3/epc-helper.h"
#include "ns3/point-to-point-epc-helper.h"
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace ns3;
using namespace std;
NS_LOG_COMPONENT_DEFINE ("Original");

#define MAXLTEGRID 2
#define MAXWIFIGRID 10
#define MAXWIFIUSER 10
#define MAXLTEUSER 100
#define POLLINGTIME 10

#define NO 0
#define UMTS 1
#define LTE 2
#define WIFI 3

#pragma clang diagnostic ignored "-Wunused-variable"

#define Debug(x) cout << #x" = " << x <<endl;

struct eNb{
    int id;
    double x, y;
    int userNum;
    int failNum;
};
typedef struct eNb eNb;

struct wifiAp{
    int id;
    double x, y;
    int userNum;
    int failNum;
};
typedef struct wifiAp wifiAp;

struct user{
    int id;
    int handoverTime;
    int bsType;
    int bsId;
};
typedef struct user user;

vector<eNb> eNbList;
vector<wifiAp> wifiApList;
vector<user> userList;
// bool isENbPoiFill[MAXLTEGRID*MAXLTEGRID];
// bool isWifiApPoiFill[MAXWIFIGRID*MAXWIFIGRID];
double simTime;
uint16_t numberOfUes;
uint16_t numberOfEnbs; 
uint16_t numberOfWifi; 
uint16_t lteRadius;
uint16_t wifiRadius;
uint16_t maxHandoverTime;

Ptr<MobilityModel> mob;
NodeContainer wifiNodes;
NodeContainer wifiApNode;

double checkDistance(int ap_index, double posx, double posy,int type)
{
    double tmp;
    double ap_X=0, ap_Y=0;
    if(type==WIFI){
        ap_X=wifiApList[ap_index].x;
        ap_Y=wifiApList[ap_index].y;
    }else if(type==LTE){
        ap_X=eNbList[ap_index].x;
        ap_Y=eNbList[ap_index].y;        
    }
    // cout << "checkDistance ap" << ap_index << " ap_X:" << ap_X << " ap_Y:" << ap_Y << endl;
    //cout << "PosX:" << posx << " PosY:" << posy << endl;
    tmp=sqrt(pow(ap_X-posx,2)+pow(ap_Y-posy,2));
    return tmp;
}

void requestHandover(int userindex, int type, int id)
{
    user u=userList[userindex];
    if(u.bsType==WIFI){
        wifiApList[u.bsId].userNum--;
    }else if(u.bsType==LTE){
        eNbList[u.bsId].userNum--;
    }
    if(type==WIFI){
        wifiApList[id].userNum++;
    }else if(type==LTE){
        eNbList[id].userNum++;
    }
    userList[userindex].bsType=type;
    userList[userindex].bsId=id;
    //if(userindex==1)cout<<u.bsType<<" "<<type<<endl;
    if(u.bsType!=type) {
        //cout<<userList[userindex].bsType<<" "<<userList[userindex].bsId<<" => "<<type<<" "<<id<<endl;
        userList[userindex].handoverTime++;
        
    }
}

void UpdateState()
{
    //cout << Simulator::Now().GetSeconds()<< " UpdateState" << endl ;
    for(int i = 0; i < userList.size() ; i++)
    {
        //BFHP
        user u=userList[i];
        // if(u.handoverTime>=maxHandoverTime){
        //     u.bsType=UMTS;
        //     continue;
        // }
        mob = wifiNodes.Get(i)->GetObject<MobilityModel>();
        Vector pos = mob->GetPosition ();
        //cout << "node "<<i<<"( "<<pos.x<<", "<<pos.y<<"), curAP: " << u.bsType << u.bsId<<endl;

        double min_wifi_dis = wifiRadius*2*MAXWIFIGRID+100;
        int min_wifi_ap = 0;
        for(int x=0;x<numberOfWifi;++x){
            double temp = checkDistance(x,pos.x, pos.y, WIFI);
            if( temp < wifiRadius && temp < min_wifi_dis){
                min_wifi_dis = temp;
                min_wifi_ap = x;
            }
        }

        float min_enb_dis = lteRadius*2*MAXLTEGRID+100;
        int min_enb_ap = 0;
        for(int x=0;x<numberOfEnbs;++x){
            double temp = checkDistance(x,pos.x, pos.y, LTE);
            if( temp < lteRadius && temp < min_enb_dis){
                min_enb_dis = temp;
                min_enb_ap = x;
            }
        }
        //if(i==1)cout<<"node "<<i<<" ,wifi "<<min_wifi_dis<<" ,lte "<<min_enb_dis<<endl;
        bool isConnectWiFi=true, isConnectLte=true;
        if(min_wifi_dis == wifiRadius*2*MAXWIFIGRID+100)
            isConnectWiFi=false;
        if(min_enb_dis == lteRadius*2*MAXLTEGRID+100)
            isConnectLte=false;

        int newBsType=UMTS, newId=0;
        if(isConnectWiFi==false && isConnectLte==false){
            newBsType=UMTS;
            newId=0;
        }else if(isConnectWiFi==false && isConnectLte==true){
            newBsType=LTE;
            newId=min_enb_ap;
        }else if(isConnectWiFi==true && isConnectLte==false){
            newBsType=WIFI;
            newId=min_wifi_ap;
        }else if(isConnectWiFi==true && isConnectLte==true){
            newBsType=LTE;
            newId=min_enb_ap;
        }
        //if(i==1)cout<<userList[i].bsType<<" => ";
        requestHandover(i, newBsType, newId);
        //if(i==1)cout<<userList[i].bsType<<endl;
    }

    for(int i=0;i<eNbList.size();++i){
        //cout<<i<<" (enb): "<<eNbList[i].userNum<<endl;
        int overNum=eNbList[i].userNum-MAXLTEUSER;
        eNbList[i].failNum+=overNum>0?overNum:0;
    }

    for(int i=0;i<wifiApList.size();++i){
        //cout<<i<<" (wifi): "<<wifiApList[i].userNum<<endl;
        int overNum=wifiApList[i].userNum-MAXLTEUSER;
        wifiApList[i].failNum+=overNum>0?overNum:0;
    }
}

void Reload(){
    UpdateState();
    Simulator::Schedule(Seconds(POLLINGTIME), &Reload);
}

void Result(){
    long long int sum=0;
    cout<<"---average handover time---"<<endl;
    for(int i=0;i<userList.size();++i){
        sum+=userList[i].handoverTime;
        //cout<<"node "<<i<<" "<<userList[i].handoverTime<<endl;
    }
    cout<<(double)sum/(double)userList.size()<<endl;
    cout<<"---overall fail rate---"<<endl;
    sum=0;
    for(int i=0;i<eNbList.size();++i){
        sum+=eNbList[i].failNum;
        //cout<<"node "<<i<<" "<<userList[i].handoverTime<<endl;
    }
    for(int i=0;i<wifiApList.size();++i){
        sum+=wifiApList[i].failNum;
        //cout<<"node "<<i<<" "<<userList[i].handoverTime<<endl;
    }
    //cout<<sum<<endl;
    cout<<(double)sum/(double)(userList.size()*simTime/POLLINGTIME)<<endl;

}

int main (int argc, char *argv[])
{
    std::string traceFile="scratch/RW_n200t2500.ns_movements";
    /** environment parameters setting **/
    numberOfUes = 200;
    numberOfEnbs = 3; //75%
    numberOfWifi = 300; //75%
    lteRadius = 1250;
    wifiRadius = 125;
    maxHandoverTime = 10;
    simTime = 1000;
    double UmtsLteHoTime = 0.7;
    double LteWifiHoTime = 0.3;
    double UmtsWifiTime = LteWifiHoTime+UmtsLteHoTime;

    CommandLine cmd;
    cmd.AddValue ("numberOfUes", "Number of UEs", numberOfUes);
    cmd.AddValue ("numberOfEnbs", "Number of eNodeBs", numberOfEnbs);
    cmd.AddValue ("numberOfWifi", "Number of WiFi", numberOfWifi);
    cmd.AddValue ("", "Total duration of the simulation (in seconds)", simTime);
    cmd.AddValue ("UmtsLteHoTime", "srvcc handover time", UmtsLteHoTime);
    cmd.AddValue ("LteWifiHoTime", "vowifi handover time", LteWifiHoTime);
    cmd.AddValue ("maxHandoverTime", "vowifi handover time", maxHandoverTime);
    cmd.AddValue ("traceFile", "path of trace file", traceFile);
    cmd.Parse (argc, argv);

    cout<<traceFile<<endl;
    //Initialize
    eNbList.clear();
    wifiApList.clear();
    userList.clear();
    srand (time(NULL));
    // memset(isENbPoiFill, false, sizeof(isENbPoiFill))
    // memset(isWifiApPoiFill, false, sizeof(isWifiApPoiFill))
    int cnt=numberOfEnbs;
    int id, index;
    vector<int> allId;
    allId.clear();
    for(int i=0;i<MAXLTEGRID*MAXLTEGRID;++i){
        allId.push_back(i);
    }
    while(cnt--){
        index=rand()%allId.size();
        id=allId[index];
        eNb newENb;
        newENb.id=id;
        newENb.x=lteRadius+id/MAXLTEGRID*lteRadius*2;
        newENb.y=lteRadius+id%MAXLTEGRID*lteRadius*2;
        newENb.userNum=0;
        newENb.failNum=0;
        eNbList.push_back(newENb);
        allId.erase(allId.begin()+index);
    }
    allId.clear();
    for(int i=0;i<MAXWIFIGRID*MAXWIFIGRID*MAXLTEGRID*MAXLTEGRID;++i){
        allId.push_back(i);
    }
    cnt=numberOfWifi;
    while(cnt--){
        index=rand()%allId.size();
        id=allId[index];
        wifiAp newWifiAp;
        newWifiAp.id=id;
        newWifiAp.x=wifiRadius+id/(MAXWIFIGRID*MAXLTEGRID)*wifiRadius*2;
        newWifiAp.y=wifiRadius+id%(MAXWIFIGRID*MAXLTEGRID)*wifiRadius*2;
        newWifiAp.userNum=0;
        wifiApList.push_back(newWifiAp);
        allId.erase(allId.begin()+index);
    }

    for(int i=0;i<numberOfUes;++i){
        user u;
        u.id=i;
        u.handoverTime=0;
        u.bsType=NO;
        u.bsId=0;
        userList.push_back(u);
    }

    //Create nodes
    Ns2MobilityHelper ns2 = Ns2MobilityHelper (traceFile);
    wifiNodes.Create (numberOfUes);
    ns2.Install ();

    wifiApNode.Create (numberOfWifi);

    MobilityHelper mobility;
    mobility.SetPositionAllocator ("ns3::GridPositionAllocator",
            "MinX", DoubleValue (75.0),
            "MinY", DoubleValue (75.0),
            "DeltaX", DoubleValue (100.0),
            "DeltaY", DoubleValue (100.0),
            "GridWidth", UintegerValue (5000),
            "LayoutType", StringValue ("RowFirst"));
    mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
    mobility.Install (wifiApNode);

    // MobilityHelper mobility;
    // mobility.SetPositionAllocator ("ns3::GridPositionAllocator",
    //                                  "MinX", DoubleValue (0.0),
    //                                  "MinY", DoubleValue (0.0),
    //                                  "DeltaX", DoubleValue (5.0),
    //                                  "DeltaY", DoubleValue (10.0),
    //                                  "GridWidth", UintegerValue (5000),
    //                                  "LayoutType", StringValue ("RowFirst"));

    // mobility.SetMobilityModel ("ns3::RandomWalk2dMobilityModel",
    //                              "Bounds", RectangleValue (Rectangle (-50, 50, -50, 50)));
    // mobility.Install (wifiNodes);
    AnimationInterface anim ("animation.xml");
    Simulator::Schedule(Seconds(0.0), &Reload);
    Simulator::Stop (Seconds (simTime));
    Simulator::Run ();
    Simulator::Destroy ();
    Result();
    return 0;
}