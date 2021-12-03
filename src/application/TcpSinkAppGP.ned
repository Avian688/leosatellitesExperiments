//
// Copyright (C) 2004 Andras Varga
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

package leosatellites.application;

import inet.applications.contract.IApp;
import inet.applications.tcpapp.TcpSinkApp;
import inet.applications.tcpapp.TcpSinkAppThread;
//
// Accepts any number of incoming TCP connections, and discards whatever
// arrives on them. Compatible with both ~Ipv4 and ~Ipv6.
//"
module TcpSinkAppGP extends TcpSinkApp
{
    parameters:
        serverThreadModuleType = default("leosatellites.application.TcpSinkAppThreadGP");
        bool recordStatistics = default(true);
        @class("inet::TcpSinkAppGP");
        @display("i=block/sink");
        @statistic[packetReceived](title="packets received"; source=packetReceived; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none; checkSignals=false);
        @statistic[endToEndDelay](title="end-to-end delay"; source="dataAge(packetReceived)"; unit=s; record=histogram,weightedHistogram,vector; interpolationmode=none; checkSignals=false);
        
        @signal[fctRecordv3](type=double);
        @statistic[fctRecordv3](title="TCP Session's flow completion time"; source=fctRecordv3; unit=s; record=last);
        
        @signal[goodputSig](type=double);
        @statistic[goodput](title="goodput"; source=goodputSig; unit=bps; record=last);
		@statistic[instThroughput](title="instThroughput"; source="throughputA(packetReceived)"; unit=bps; record=mean,vector); //ResultsFilter.cc
		
		@signal[jitterSig](type=double);
        @statistic[jitterSig](title="Inter-Packet Latency"; source=jitterSig; record=vector; interpolationmode=none);
}

simple TcpSinkAppThreadGP extends TcpSinkAppThread
{
    parameters:
        @class("inet::TcpSinkAppThreadGP");
        @display("i=block/sink");
        @signal[packetReceived](type=inet::Packet);
        @statistic[packetReceived](title="packets received"; source=packetReceived; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
        @statistic[endToEndDelay](title="end-to-end delay"; source="dataAge(packetReceived)"; unit=s; record=histogram,weightedHistogram,vector; interpolationmode=none);
        
        @signal[fctRecordv3](type=double);
        @statistic[fctRecordv3](title="TCP Session's flow completion time"; source=fctRecordv3; unit=s; record=last);
        
        @signal[goodputSig](type=double);
        @statistic[goodput](title="goodput"; source=goodputSig; unit=bps; record=last);

}	

