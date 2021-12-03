//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 
#include "UdpJitterSink.h"

namespace inet {

Define_Module(UdpJitterSink);

simsignal_t UdpJitterSink::jitterSig = registerSignal("jitterSig");

void UdpJitterSink::initialize(int stage)
{
    UdpSink::initialize(stage);
}

void UdpJitterSink::processPacket(Packet *pk)
{
    EV_INFO << "Received packet: " << UdpSocket::getReceivedPacketInfo(pk) << endl;
    emit(packetReceivedSignal, pk);
    delete pk;
    numReceived++;
    if (firstDataReceived == false) {
        tEndPacketOne = simTime();
        firstDataReceived = true;
    }
    else{
        tEndPacketTwo = simTime();
        double jitter = (tEndPacketTwo - tEndPacketOne).dbl();
        emit(jitterSig, jitter);
        tEndPacketOne = tEndPacketTwo;
    }
}

}
