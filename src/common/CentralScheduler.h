#ifndef __LEO_CentralScheduler_H
#define __LEO_CentralScheduler_H
#include <chrono>  // for high_resolution_clock

#include <map>
#include <set>
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <random>
#include <cmath>
#include <time.h>       /* time */

//IF DEF NDP
#include "../../../ndp/src/application/ndpapp/NdpBasicClientApp.h"
#include "../../../ndp/src/application/ndpapp/NdpSinkApp.h"

//IF DEF SCDP
#include "../../../scdp/src/application/scdpapp/ScdpBasicClientApp.h"
#include "../../../scdp/src/application/scdpapp/ScdpSinkApp.h"

#include "inet/common/INETDefs.h"
#include "inet/common/lifecycle/ILifecycle.h"

namespace inet {

enum TransportProtocol
{
    TCP,
    NDP
};

class INET_API CentralScheduler : public cSimpleModule, public ILifecycle
{
//private:
protected:

    bool isWebSearchWorkLoad;
    unsigned int indexWorkLoad;
    std::vector<unsigned int> flowSizeWebSeachWorkLoad;

    std::chrono::high_resolution_clock::time_point t1;
    std::chrono::high_resolution_clock::time_point t2;
    simtime_t totalSimTime;
    cOutVector permMapLongFlowsVec;
    cOutVector permMapShortFlowsVec;

    cOutVector randMapShortFlowsVec;
    cOutVector permMapShortFlowsVector;

    cOutVector numSessionAppsVec;
    cOutVector numSinkAppsVec;
    cOutVector nodes;
    cOutVector matSrc; // record all the source servers of the created short flows
    cOutVector matDest; // record all the dest servers of the created short flows

    cMessage *startManagerNode;
    unsigned int IW;
    unsigned int switchQueueLength;
    const char *trafficMatrixType; // either "permTM"  or "randTM"
    TransportProtocol transportProtocol;
    bool perFlowEcmp;
    bool perPacketEcmp;

    unsigned int test = 0;
    unsigned int arrivalRate; // lamda of an exponential distribution (Morteza uses 256 and 2560)
    unsigned int flowSize;
    unsigned int numOfNodes;
    unsigned int numShortFlows;
    unsigned int longFlowSize;
    double percentLongFlowNodes;
    unsigned int numCompletedShortFlows = 0;
    unsigned int numCompletedLongFlows = 0;
    unsigned int numRunningShortFlowsNow = 0;

    /////????????????????
    cMessage *stopSimulation;
    std::vector<unsigned int> permServers;

    std::vector<unsigned int> permLongFlowsServers;
    std::vector<unsigned int> permShortFlowsServers;

    unsigned int numlongflowsRunningServers; // 33% of nodes run long flows
    unsigned int numshortflowRunningServers;

    struct coreAggMap
    {
        unsigned int aggIndex;
        std::vector<int> associatedCores; // associated

    };

    typedef std::list<coreAggMap> CoreAggMapList;
    CoreAggMapList coreAggMapList;

    std::vector<int> tempNode;
    std::vector<int> tempCombination;
    std::list<std::vector<int> > combinations; // all possible combinations
    unsigned int numAllCombinations;
    std::set<int> alreadySelectedGroups; // contains index of the selected groups (set.insert does not add in order like in vector.pushback)

    virtual bool handleOperationStage(LifecycleOperation *operation, IDoneCallback *doneCallback) override
    {
        Enter_Method_Silent
        ();
        throw cRuntimeError("Unsupported lifecycle operation '%s'", operation->getClassName());
        return true;
    }

    //  <dest, src>
    std::map<unsigned int, unsigned int> permMapLongFlows;
    std::map<unsigned int, unsigned int> permMapShortFlows;

    double sumArrivalTimes = 0;
    double newArrivalTime;
    bool shuffle = false;
    bool randomGroup = true;

    struct NodeLocation
    {
        unsigned int index;
        unsigned int numSink;
        unsigned int numSession;
    };

    typedef std::list<NodeLocation> NodeLocationList;
    NodeLocationList nodeLocationList;
    unsigned int seedValue;
    std::mt19937 PRNG;
    std::exponential_distribution<double> expDistribution;
    std::exponential_distribution<double> expDistributionForRqDecdoing;

    struct RecordMat
    {
        unsigned int recordSrc;
        unsigned int recordDest;
    };
    typedef std::list<RecordMat> RecordMatList;
    RecordMatList recordMatList;

    unsigned int numTimesDecodingFailed = 0;
    unsigned int numTimesDecodingSucceeded = 0;

public:
    CentralScheduler()
    {
    }
    virtual ~CentralScheduler();
    double getNewValueFromExponentialDistribution();

protected:
    virtual void initialize(int stage) override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;
    virtual void handleParameterChange(const char *parname) override;
    void serversLocations();
    void generateTM();

    void getNewDestRandTM(std::string &itsSrc, std::string &newDest);
    void getNewDestPremTM(std::string &itsSrc, std::string &newDest);

    void findLocation(unsigned int nodeIndex, std::string &nodePodRackLoc);
    void scheduleLongFlows();
    void deleteAllSubModuleApp(const char *subModuleToBeRemoved);
    int findNumSumbodules(cModule *nodeModule, const char *subModuleType);
    void scheduleNewShortFlow(std::string itsSrc, std::string newDest);

    void permTM(const char *longOrShortFlows);

    void getWebSearchWorkLoad();
    unsigned int getNewFlowSizeFromWebSearchWorkLoad();
    unsigned int getPriorityValue(unsigned int flowSize);
    std::string getApplicationName(bool isClient);
    void setUpSrcModule(std::string itsSrc, std::string newDest, int newNumTpSinkAppsDest);
    int setUpDestModule(std::string itsSrc, std::string newDest, bool isLongFlow);
};

}

#endif // ifndef __INET_RQ_H
