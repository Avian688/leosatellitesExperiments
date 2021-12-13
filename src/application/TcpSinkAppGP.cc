#include "inet/applications/common/SocketTag_m.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/common/lifecycle/NodeStatus.h"
#include "inet/common/packet/Message.h"
#include "inet/networklayer/common/L3AddressResolver.h"

#include "TcpSinkAppGP.h"
namespace inet {

Define_Module(TcpSinkAppGP);
Define_Module(TcpSinkAppThreadGP);

simsignal_t goodputSig = NodeStatus::registerSignal("goodputSig");
simsignal_t fctRecordv3 = NodeStatus::registerSignal("fctRecordv3");
simsignal_t TcpSinkAppGP::jitterSig = registerSignal("jitterSig");

TcpSinkAppGP::TcpSinkAppGP()
{
}

TcpSinkAppGP::~TcpSinkAppGP()
{
}

void TcpSinkAppGP::initialize(int stage)
{
    TcpServerHostApp::initialize(stage);
    recordStatistics = par("recordStatistics");
    bytesNeeded = par("bytesNeeded");
    if (stage == INITSTAGE_LOCAL) {
        bytesRcvd = 0;
        WATCH(bytesRcvd);
    }
}

void TcpSinkAppGP::refreshDisplay() const
{
    ApplicationBase::refreshDisplay();

    char buf[160];
    sprintf(buf, "threads: %d\nrcvd: %ld bytes", socketMap.size(), bytesRcvd);
    getDisplayString().setTagArg("t", 0, buf);
}

void TcpSinkAppGP::finish()
{
    if(recordStatistics == true && bytesRcvd > 0){
        double throughput = 8 * (double) bytesRcvd / (tEndAdded - tStartAdded).dbl();
        double FCT = SIMTIME_DBL(tEndAdded - tStartAdded);
        TcpServerHostApp::finish();
        recordScalar("bytesRcvd", bytesRcvd);
        emit(fctRecordv3, FCT);
        emit(goodputSig, throughput);
    }
}


void TcpSinkAppThreadGP::initialize(int stage)
{
    TcpServerThreadBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        bytesRcvd = 0;
        WATCH(bytesRcvd);
    }
}

void TcpSinkAppThreadGP::established()
{
    bytesRcvd = 0;
}

void TcpSinkAppThreadGP::dataArrived(Packet *pk, bool urgent)
{
    sinkAppModule->bytesRcvd += pk->getByteLength();
    if (sinkAppModule->bytesNeeded <= sinkAppModule->bytesRcvd){
        sinkAppModule->tEndAdded = simTime();
        emit(packetReceivedSignal, pk);
        if(sinkAppModule->recordStatistics == true){
            cModule *centralMod =  sinkAppModule->getParentModule()->getModuleByPath("centralScheduler");
            std::cout << "Central Mod: " << centralMod->str() << endl;
            if (centralMod && sinkAppModule->recordStatistics == true) {
                int numFinishedFlows = centralMod->par("numCompletedShortFlows");
                int newNumFinishedFlows = numFinishedFlows + 1;
                centralMod->par("numCompletedShortFlows").setIntValue(newNumFinishedFlows);
                EV_INFO << "TcpSinkAppGP::handleMessage  numCompletedShortFlows " << newNumFinishedFlows << endl;
            }
        }
    }
    else if(pk->getKind() == TCP_I_DATA || pk->getKind() == TCP_I_URGENT_DATA){
        if(sinkAppModule->recordStatistics == true){
            long packetLength = pk->getByteLength();
            emit(packetReceivedSignal, pk);
            if (firstDataReceived == false) {
                auto data = pk->peekData(); // get all data from the packet
                sinkAppModule->tStartAdded = data->getTag<CreationTimeTag>()->getCreationTime();
                firstDataReceived = true;
                tEndPacketOne = simTime();
            }
            else{
                tEndPacketTwo = simTime();
                double jitter = (tEndPacketTwo - tEndPacketOne).dbl();
                sinkAppModule->emit(sinkAppModule->jitterSig, jitter);
                tEndPacketOne = tEndPacketTwo;
                auto data = pk->peekData();
                auto regions = data->getAllTags<CreationTimeTag>(); // get all tag regions
                for (auto& region : regions) { // for each region do
                    auto creationTime = region.getTag()->getCreationTime(); // original time
                    simtime_t startTime = creationTime;
                    if(startTime < sinkAppModule->tStartAdded){
                        sinkAppModule->tStartAdded = startTime;
                    }
                }
            }
        }
    }
    delete pk;
}

void TcpSinkAppThreadGP::refreshDisplay() const
{
    std::ostringstream os;
    os << (sock ? TcpSocket::stateName(sock->getState()) : "NULL_SOCKET") << "\nrcvd: " << bytesRcvd << " bytes";
    getDisplayString().setTagArg("t", 0, os.str().c_str());
}


} // namespace inet

