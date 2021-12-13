package leosatellites.simulations.ManhattanStatic;

import leosatellites.base.BasicSatellite;
import leosatellites.base.LaserSatellite;
import leosatellites.base.GroundStation;
import os3.base.MissionControlCenter;
import inet.physicallayer.contract.packetlevel.IRadioMedium;
import inet.physicallayer.apskradio.packetlevel.ApskScalarRadioMedium;
import os3.base.CNI_OS3;
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import ecmp.networklayer.configurator.ipv4.Ipv4NetworkConfiguratorEcmp;
import leosatellites.networklayer.configurator.ipv4.SatelliteNetworkConfigurator;
import inet.networklayer.configurator.ipv4.Ipv4FlatNetworkConfigurator;
import inet.visualizer.contract.IIntegratedVisualizer;
import inet.node.inet.StandardHost;
import ecmp.node.StandardHostEcmp;
import ndp.node.StandardHostNdp;
import raqsac.node.StandardHostRaqsac;
import inet.node.inet.INetworkNode;
import inet.common.geometry.common.SimpleGeographicCoordinateSystem;
import inet.common.geometry.common.OsgGeographicCoordinateSystem;
import inet.environment.objectcache.GridObjectCache;

import leosatellites.physicallayer.unitdisk.SatelliteUnitDiskTransmitter;
import leosatellites.physicallayer.propagation.SatellitePropagation;
import leosatellites.common.CentralScheduler;
import ned.DatarateChannel;
import leosatellites.base.StaticSatellite;
//
// Network SatSGP4 enables satellite movement on worldmap. This is the primary satellite network that
// is testing throughout the project by Aiden Valentine. The network has been largely adpated from the
// Initial OS3 implementation so that it works with the latest version of INET. The NED file below illustrates
// the new mdodels being used such as the SatelliteNetworkConfigurator which will periodically run Dijkstra's
// algorthm to re establish routes in a dynamic satellite network.
//
network ManhattanStatic
{
    parameters:
        int numOfSats; // Number of satellites
        int satPerLine = int(sqrt(numOfSats))
        @display("bgi=background_earth,s;bgb=2160,1080");
        //@statistic[rtt](source=count(MCC[0].app[0].rtt); record=figure; targetFigure=rttCounter; checkSignals=false);
        //@figure[rttCounter](type=plot; pos=600,50; label="Round Trip Time");
    types:
        channel laserlink extends DatarateChannel
        {
            //delay =  1ms;
            delay =  1ms;
            datarate = 1Gbps;
        } 
    submodules:
        visualizer: <default("IntegratedCanvasVisualizer")> like IIntegratedVisualizer if hasVisualizer() {
            @display("p=305.665,67.625`");
        }
        configurator: Ipv4NetworkConfiguratorEcmp {
            @display("p=183.94,67.625");
        }
        satellite[numOfSats]: StaticSatellite {   //LaserSatellite for using NoradA, Satellite for Ground-Relays using TLE
            parameters:
                @display("p=50,50.305,m,$satPerLine;i=satellit_blue");
        }
        centralScheduler: CentralScheduler {
            @display("p=704.06,601.0725;i=abstract/person,#17FF39;b=,,rect;is=vl;t=Central flow scheduler");
        }
    connections allowunconnected:
//        for i=0..satPerLine-1,for j=0..satPerLine-2{  
//            satellite[(i*satPerLine)+j].pppg++ <--> laserlink <--> satellite[(i*satPerLine)+j+1].pppg++;
//        }
//        for i=0..satPerLine-2,for j=0..satPerLine-1{  
//            satellite[(i*satPerLine)+j].pppg++ <--> laserlink <--> satellite[(i*satPerLine)+j+satPerLine].pppg++;
//        }
        for i=0..satPerLine-1,for j=0..satPerLine-2{  
            satellite[(i*satPerLine)+j].satGate++ <--> laserlink <--> satellite[(i*satPerLine)+j+1].satGate++;
        }
        for i=0..satPerLine-2,for j=0..satPerLine-1{  
            satellite[(i*satPerLine)+j].satGate++ <--> laserlink <--> satellite[(i*satPerLine)+j+satPerLine].satGate++;
        }
//		satellite[0].satGate++ <--> laserlink <--> satellite[1].satGate++;
//		satellite[0].satGate++ <--> laserlink <--> satellite[2].satGate++;
//		satellite[1].satGate++ <--> laserlink <--> satellite[3].satGate++;
//		satellite[2].satGate++ <--> laserlink <--> satellite[3].satGate++;
}