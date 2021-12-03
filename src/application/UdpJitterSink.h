//
// Copyright (C) 2004 Andras Varga
// Copyright (C) 2000 Institut fuer Telematik, Universitaet Karlsruhe
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

#ifndef __INET_UDPJITTERSINK_H
#define __INET_UDPJITTERSINK_H

#include <inet/common/TimeTag_m.h>
#include <inet/applications/udpapp/UdpSink.h>

namespace inet {

/**
 * Consumes and prints packets received from the Udp module. See NED for more info.
 */
class INET_API UdpJitterSink : public UdpSink
{
    public:
        UdpJitterSink() {}
        virtual ~UdpJitterSink() {}
    protected:
        static simsignal_t jitterSig;

        simtime_t tStartPacketOne;
        simtime_t tEndPacketOne;

        simtime_t tStartPacketTwo;
        simtime_t tEndPacketTwo;

        bool firstDataReceived = false;

        virtual void initialize(int stage) override;
        virtual void processPacket(Packet *msg) override;

};

} // namespace inet

#endif // ifndef __INET_UDPJITTERSINK_H

