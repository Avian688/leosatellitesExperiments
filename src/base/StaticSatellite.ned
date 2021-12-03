
package leosatellites.base;

import inet.mobility.contract.IMobility;
import leosatellites.mobility.NoradA;
import inet.node.inet.WirelessHost;
import inet.node.inet.AdhocHost;
import inet.node.inet.StandardHost;
import ndp.node.StandardHostNdp;
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
        @display("p=50,50.305,m,$satPerLine;i=satellit_blue");  
    gates:
    	// As many ports as aggregation routers.
    	inout satGate[1]; 
    types:
        channel ethernetline extends DatarateChannel
        {
            delay = 1us;
            datarate = 1Gbps; 
        }

    submodules:
		sat: StandardHostNdp {
            // Reach value down.
            // position = index;
            @display("p=80,160,r,80");
            @display("i=device/device");
        }
        switch: RouterNdp { //no from type EdgeRouter.ned, because position is saved in Rack
            @display("p=300,80");
            @display("i=abstract/router");
          //  forwarding = default(true);
        }
    connections allowunconnected:
        sat.pppg++ <--> ethernetline <--> switch.pppg++;
    	switch.pppg++ <--> IdealChannel <--> satGate++;
}
