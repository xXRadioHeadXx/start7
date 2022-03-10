QT += core
CONFIG += c++14 -std=gnu++14 -std=c++14

INCLUDEPATH += $$PWD/

SOURCES += \
    $$PWD/SWP.cpp \
    $$PWD/swpblip/SWPBLIPType0x41.cpp \
    $$PWD/swpblip/SWPBLIPType0x42.cpp \
    $$PWD/swpblip/SWPIUBLIPType0x41.cpp \
    $$PWD/swprlmc/SWPRLMCType0x31.cpp \
    $$PWD/swprlm/SWPRLMType0x31.cpp \
    $$PWD/swpblip/SWPSDBLIPType0x41.cpp \
    $$PWD/swpblip/SWPSDBLIPType0x42.cpp \
    $$PWD/swpssoiblip/SWPSSOIBLIPType0x41.cpp \
    $$PWD/swpssoiblip/SWPSSOIBLIPType0x42.cpp \
    $$PWD/swpssoiblip/SWPSSOIIUBLIPType0x41.cpp \
    $$PWD/swpssoiblip/SWPSSOISDBLIPType0x41.cpp \
    $$PWD/swpssoiblip/SWPSSOISDBLIPType0x42.cpp \
    $$PWD/swpt4k/SWPT4KBODType0x32.cpp \
    $$PWD/swpt4k/SWPT4KBODType0x33.cpp \
    $$PWD/swpt4k/SWPT4KBODType0x34.cpp \
    $$PWD/swpt4k/SWPT4KDDCFType0x33.cpp \
    $$PWD/swpt4k/SWPT4KDDCFType0x34.cpp \
    $$PWD/swpt4k/SWPT4KDDCType0x32.cpp \
    $$PWD/swpt4k/SWPT4KDDCType0x33.cpp \
    $$PWD/swpt4k/SWPT4KDDCType0x34.cpp \
    $$PWD/swpt4k/SWPT4KDDType0x32.cpp \
    $$PWD/swpt4k/SWPT4KDDType0x33.cpp \
    $$PWD/swpt4k/SWPT4KDDType0x34.cpp \
    $$PWD/swpt4k/SWPT4KY4Type0x32.cpp \
    $$PWD/swpt4k/SWPT4KY4Type0x33.cpp \
    $$PWD/swptg/SWPTGSubType0x32.cpp \
    $$PWD/swptg/SWPTGSubType0x33.cpp \
    $$PWD/swptg/SWPTGSubType0x34.cpp \
    $$PWD/swptg/SWPTGType0x31.cpp \
    $$PWD/swptg/SWPTGType0x32.cpp \
    $$PWD/swptg/SWPTGType0x33.cpp \
    $$PWD/swptg/SWPTGType0x34.cpp


HEADERS += \
    $$PWD/SWP.h \
    $$PWD/SWPAlarm.h \
    $$PWD/SWPCliff.h \
    $$PWD/SWPClockPeriod.h \
    $$PWD/SWPClosure.h \
    $$PWD/SWPCountImpact.h \
    $$PWD/SWPDurationOvercoming.h \
    $$PWD/SWPExistDK.h \
    $$PWD/SWPFault.h \
    $$PWD/SWPInAlarm.h \
    $$PWD/SWPInCommunicationBreak.h \
    $$PWD/SWPInNorm.h \
    $$PWD/SWPInOpened.h \
    $$PWD/SWPInterrogation.h \
    $$PWD/SWPLevel.h \
    $$PWD/SWPLineBreak.h \
    $$PWD/SWPModeProcessing.h \
    $$PWD/SWPNorm.h \
    $$PWD/SWPOff.h \
    $$PWD/SWPOn.h \
    $$PWD/SWPOpened.h \
    $$PWD/SWPOutAlarm.h \
    $$PWD/SWPOutNorm.h \
    $$PWD/SWPReady.h \
    $$PWD/SWPShortCircuit.h \
    $$PWD/SWPSynchronization.h \
    $$PWD/SWPThreshold.h \
    $$PWD/SWPTimeImpact.h \
    $$PWD/SWPTimeImpact.h \
    $$PWD/SWPVoltage.h \
    $$PWD/SWPWasAlarm.h \
    $$PWD/SWPWasDK.h \
    $$PWD/SWPWasOpened.h \
    $$PWD/SWPWeakening.h \
    $$PWD/swpblip/SWPBLIPType0x41.h \
    $$PWD/swpblip/SWPBLIPType0x42.h \
    $$PWD/swpblip/SWPIUBLIPType0x41.h \
    $$PWD/swprlmc/SWPRLMCType0x31.h \
    $$PWD/swprlm/SWPRLMType0x31.h \
    $$PWD/swpblip/SWPSDBLIPType0x41.h \
    $$PWD/swpblip/SWPSDBLIPType0x42.h \
    $$PWD/swpssoiblip/SWPSSOIBLIPType0x41.h \
    $$PWD/swpssoiblip/SWPSSOIBLIPType0x42.h \
    $$PWD/swpssoiblip/SWPSSOIIUBLIPType0x41.h \
    $$PWD/swpssoiblip/SWPSSOISDBLIPType0x41.h \
    $$PWD/swpssoiblip/SWPSSOISDBLIPType0x42.h \
    $$PWD/swpt4k/SWPT4KBODType0x32.h \
    $$PWD/swpt4k/SWPT4KBODType0x33.h \
    $$PWD/swpt4k/SWPT4KBODType0x34.h \
    $$PWD/swpt4k/SWPT4KDDCFType0x33.h \
    $$PWD/swpt4k/SWPT4KDDCFType0x34.h \
    $$PWD/swpt4k/SWPT4KDDCType0x32.h \
    $$PWD/swpt4k/SWPT4KDDCType0x33.h \
    $$PWD/swpt4k/SWPT4KDDCType0x34.h \
    $$PWD/swpt4k/SWPT4KDDType0x32.h \
    $$PWD/swpt4k/SWPT4KDDType0x33.h \
    $$PWD/swpt4k/SWPT4KDDType0x34.h \
    $$PWD/swpt4k/SWPT4KY4Type0x32.h \
    $$PWD/swpt4k/SWPT4KY4Type0x33.h \
    $$PWD/swptg/SWPTGSubType0x32.h \
    $$PWD/swptg/SWPTGSubType0x33.h \
    $$PWD/swptg/SWPTGSubType0x34.h \
    $$PWD/swptg/SWPTGType0x31.h \
    $$PWD/swptg/SWPTGType0x32.h \
    $$PWD/swptg/SWPTGType0x33.h \
    $$PWD/swptg/SWPTGType0x34.h \
    $$PWD/SWPWasCommunicationBreak.h



HEADERS += \
    $$PWD/SWP.h \
    $$PWD/SWPAlarm.h \
    $$PWD/SWPCliff.h \
    $$PWD/SWPClockPeriod.h \
    $$PWD/SWPClosure.h \
    $$PWD/SWPExistDK.h \
    $$PWD/SWPFault.h \
    $$PWD/SWPInAlarm.h \
    $$PWD/SWPInCommunicationBreak.h \
    $$PWD/SWPInNorm.h \
    $$PWD/SWPInOpened.h \
    $$PWD/SWPInterrogation.h \
    $$PWD/SWPLevel.h \
    $$PWD/SWPLineBreak.h \
    $$PWD/SWPModeProcessing.h \
    $$PWD/SWPNorm.h \
    $$PWD/SWPOff.h \
    $$PWD/SWPOn.h \
    $$PWD/SWPOpened.h \
    $$PWD/SWPOutAlarm.h \
    $$PWD/SWPOutNorm.h \
    $$PWD/SWPReady.h \
    $$PWD/SWPShortCircuit.h \
    $$PWD/SWPSynchronization.h \
    $$PWD/SWPThreshold.h \
    $$PWD/SWPTimeImpact.h \
    $$PWD/SWPVoltage.h \
    $$PWD/SWPWasAlarm.h \
    $$PWD/SWPWasDK.h \
    $$PWD/SWPWasOpened.h \
    $$PWD/SWPWeakening.h \
    $$PWD/swpblip/SWPBLIPType0x41.h \
    $$PWD/swpblip/SWPBLIPType0x42.h \
    $$PWD/swpblip/SWPIUBLIPType0x41.h \
    $$PWD/swprlmc/SWPRLMCType0x31.h \
    $$PWD/swprlm/SWPRLMType0x31.h \
    $$PWD/swpblip/SWPSDBLIPType0x41.h \
    $$PWD/swpblip/SWPSDBLIPType0x42.h \
    $$PWD/swpssoiblip/SWPSSOIBLIPType0x41.h \
    $$PWD/swpssoiblip/SWPSSOIBLIPType0x42.h \
    $$PWD/swpssoiblip/SWPSSOIIUBLIPType0x41.h \
    $$PWD/swpssoiblip/SWPSSOISDBLIPType0x41.h \
    $$PWD/swpssoiblip/SWPSSOISDBLIPType0x42.h \
    $$PWD/swpt4k/SWPT4KBODType0x32.h \
    $$PWD/swpt4k/SWPT4KBODType0x33.h \
    $$PWD/swpt4k/SWPT4KBODType0x34.h \
    $$PWD/swpt4k/SWPT4KDDCFType0x33.h \
    $$PWD/swpt4k/SWPT4KDDCFType0x34.h \
    $$PWD/swpt4k/SWPT4KDDCType0x32.h \
    $$PWD/swpt4k/SWPT4KDDCType0x33.h \
    $$PWD/swpt4k/SWPT4KDDCType0x34.h \
    $$PWD/swpt4k/SWPT4KDDType0x32.h \
    $$PWD/swpt4k/SWPT4KDDType0x33.h \
    $$PWD/swpt4k/SWPT4KDDType0x34.h \
    $$PWD/swpt4k/SWPT4KY4Type0x32.h \
    $$PWD/swpt4k/SWPT4KY4Type0x33.h \
    $$PWD/swptg/SWPTGSubType0x32.h \
    $$PWD/swptg/SWPTGSubType0x33.h \
    $$PWD/swptg/SWPTGSubType0x34.h \
    $$PWD/swptg/SWPTGType0x31.h \
    $$PWD/swptg/SWPTGType0x32.h \
    $$PWD/swptg/SWPTGType0x33.h \
    $$PWD/swptg/SWPTGType0x34.h \
    $$PWD/SWPWasCommunicationBreak.h

