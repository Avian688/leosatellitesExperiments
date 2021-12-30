
package leosatellites.base;

import inet.mobility.contract.IMobility;
import leosatellites.mobility.NoradA;
import inet.node.inet.WirelessHost;
import inet.node.inet.AdhocHost;
import inet.node.inet.StandardHost;
import ndp.node.StandardHostNdp;
import rdp.node.StandardHostRdp;
import raqsac.node.StandardHostRaqsac;
import ndp.base.RouterNdp;
import ned.DatarateChannel;
import ned.IdealChannel;
// Static Satellite model that uses the NoradA implementation, which therefore allows the use of inter-satellite links.
//
//
module StaticSatellite
{
    parameters:
        @Sat;
        int numOfGS;
        @display("p=50,50.305,m,$satPerLine;i=satellit_blue");  
    gates:
    	// As many connected satellites.
    	inout satGate[4]; 
    types:
        channel radioIdeal extends DatarateChannel
        {
            //delay = 1ms; //max is range is 1123 km - 0.0033 seconds
            delay = 1ms;
            datarate = 1Gbps; 
        }

    submodules:
		groundStation[numOfGS]: StandardHostRdp {
            // Reach value down.
            // position = index;
            @display("p=238.04,343.535;r=10;i=device/receiverdish");
            @display("p=80,160,r,80");
            @display("i=device/device");
        }
        switch: RouterNdp { //no from type EdgeRouter.ned, because position is saved in Rack
            @display("p=300,80");
            @display("i=abstract/router");
          //  forwarding = default(true);
        }
    connections allowunconnected:
        for i=0..sizeof(groundStation)-1 {
            groundStation[i].pppg++ <--> radioIdeal <--> switch.pppg++;
        }
    	for i=0..3 {
            switch.pppg++ <--> IdealChannel <--> satGate++; 
        }
}
