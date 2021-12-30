#
# OMNeT++/OMNEST Makefile for $(LIB_PREFIX)leosatellitesExperiments
#
# This file was generated with the command:
#  opp_makemake --make-so -f --deep -KECMP_PROJ=../../ecmp -KINET4_PROJ=../../inet4 -KNDP_PROJ=../../ndp -KOS3_PROJ=../../os3 -KRAQSAC_PROJ=../../raqsac -KRDP_PROJ=../../rdp -DINET_IMPORT -I$$\(OS3_PROJ\)/src -I$$\(INET4_PROJ\)/src -I/usr/include/curl -L$$\(ECMP_PROJ\)/src -L$$\(INET4_PROJ\)/src -L$$\(NDP_PROJ\)/src -L$$\(OS3_PROJ\)/src -L$$\(RAQSAC_PROJ\)/src -L$$\(RDP_PROJ\)/src -lecmp$$\(D\) -lINET$$\(D\) -lndp$$\(D\) -los3$$\(D\) -lraqsac$$\(D\) -lrdp$$\(D\)
#

# Name of target to be created (-o option)
TARGET = $(LIB_PREFIX)leosatellitesExperiments$(D)$(SHARED_LIB_SUFFIX)
TARGET_DIR = .

# C++ include paths (with -I)
INCLUDE_PATH = -I$(OS3_PROJ)/src -I$(INET4_PROJ)/src -I/usr/include/curl

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS = $(LDFLAG_LIBPATH)$(ECMP_PROJ)/src $(LDFLAG_LIBPATH)$(INET4_PROJ)/src $(LDFLAG_LIBPATH)$(NDP_PROJ)/src $(LDFLAG_LIBPATH)$(OS3_PROJ)/src $(LDFLAG_LIBPATH)$(RAQSAC_PROJ)/src $(LDFLAG_LIBPATH)$(RDP_PROJ)/src  -lecmp$(D) -lINET$(D) -lndp$(D) -los3$(D) -lraqsac$(D) -lrdp$(D)

# Output directory
PROJECT_OUTPUT_DIR = ../out
PROJECTRELATIVE_PATH = src
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc, .msg and .sm files
OBJS = \
    $O/application/ResultFiltersThroughput.o \
    $O/application/TcpSinkAppGP.o \
    $O/application/UdpJitterSink.o \
    $O/common/CentralScheduler.o \
    $O/libnorad/cEcef.o \
    $O/libnorad/cNoradBaseA.o \
    $O/libnorad/cNoradSGP4A.o \
    $O/libnorad/cOrbitA.o \
    $O/mobility/GroundStationMobility.o \
    $O/mobility/INorad.o \
    $O/mobility/NoradA.o \
    $O/mobility/NoradTLE.o \
    $O/mobility/SatelliteMobility.o \
    $O/networklayer/configurator/ipv4/MatcherOS3.o \
    $O/networklayer/configurator/ipv4/SatelliteNetworkConfigurator.o \
    $O/physicallayer/apskradio/SatelliteApskScalarTransmission.o \
    $O/physicallayer/apskradio/SatelliteApskScalarTransmitter.o \
    $O/physicallayer/propagation/SatellitePropagation.o \
    $O/physicallayer/unitdisk/SatelliteUnitDiskTransmission.o \
    $O/physicallayer/unitdisk/SatelliteUnitDiskTransmitter.o

# Message files
MSGFILES =

# SM files
SMFILES =

# Other makefile variables (-K)
ECMP_PROJ=../../ecmp
INET4_PROJ=../../inet4
NDP_PROJ=../../ndp
OS3_PROJ=../../os3
RAQSAC_PROJ=../../raqsac
RDP_PROJ=../../rdp

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIBS = -loppenvir$D $(KERNEL_LIBS) $(SYS_LIBS)
ifneq ($(TOOLCHAIN_NAME),clangc2)
LIBS += -Wl,-rpath,$(abspath $(ECMP_PROJ)/src) -Wl,-rpath,$(abspath $(INET4_PROJ)/src) -Wl,-rpath,$(abspath $(NDP_PROJ)/src) -Wl,-rpath,$(abspath $(OS3_PROJ)/src) -Wl,-rpath,$(abspath $(RAQSAC_PROJ)/src) -Wl,-rpath,$(abspath $(RDP_PROJ)/src)
endif

COPTS = $(CFLAGS) $(IMPORT_DEFINES) -DINET_IMPORT $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)
SMCOPTS =

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE and have object
# files depend on it (except when "make depend" was called)
COPTS_FILE = $O/.last-copts
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
$(shell $(MKPATH) "$O" && echo "$(COPTS)" >$(COPTS_FILE))
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target
all: $(TARGET_DIR)/$(TARGET)

$(TARGET_DIR)/% :: $O/%
	@mkdir -p $(TARGET_DIR)
	$(Q)$(LN) $< $@
ifeq ($(TOOLCHAIN_NAME),clangc2)
	$(Q)-$(LN) $(<:%.dll=%.lib) $(@:%.dll=%.lib)
endif

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile $(CONFIGFILE)
	@$(MKPATH) $O
	@echo Creating shared library: $@
	$(Q)$(SHLIB_LD) -o $O/$(TARGET) $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS) $(LDFLAGS)
	$(Q)$(SHLIB_POSTPROCESS) $O/$(TARGET)

.PHONY: all clean cleanall depend msgheaders smheaders

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE) | msgheaders smheaders
	@$(MKPATH) $(dir $@)
	$(qecho) "$<"
	$(Q)$(CXX) -c $(CXXFLAGS) $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(qecho) MSGC: $<
	$(Q)$(MSGC) -s _m.cc -MD -MP -MF $O/$(basename $<)_m.h.d $(MSGCOPTS) $?

%_sm.cc %_sm.h: %.sm
	$(qecho) SMC: $<
	$(Q)$(SMC) -c++ -suffix cc $(SMCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

smheaders: $(SMFILES:.sm=_sm.h)

clean:
	$(qecho) Cleaning $(TARGET)
	$(Q)-rm -rf $O
	$(Q)-rm -f $(TARGET_DIR)/$(TARGET)
	$(Q)-rm -f $(TARGET_DIR)/$(TARGET:%.dll=%.lib)
	$(Q)-rm -f $(call opp_rwildcard, . , *_m.cc *_m.h *_sm.cc *_sm.h)

cleanall:
	$(Q)$(MAKE) -s clean MODE=release
	$(Q)$(MAKE) -s clean MODE=debug
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

# include all dependencies
-include $(OBJS:%=%.d) $(MSGFILES:%.msg=$O/%_m.h.d)
