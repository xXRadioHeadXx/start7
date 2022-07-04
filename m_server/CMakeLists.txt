cmake_minimum_required(VERSION 3.5)

project(m_server VERSION 0.1 LANGUAGES CXX)


set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 CONFIG REQUIRED COMPONENTS Core Gui Widgets LinguistTools Network Sql Multimedia Xml PrintSupport)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets LinguistTools Network Sql Multimedia Xml PrintSupport)

set(TS_FILES app_ru.ts)


set(PROJECT_SOURCES
  main.cpp
  MainWindowServer.cpp
  AuthenticationDialog.cpp

  #global
  ../src/global.h

  #template
  ../src/template/AfterConstructInitialization.h
  ../src/template/SingletonTemplate.h

  #ctpl
  ../src/ctpl/ThreadPool.cpp
  ../src/ctpl/ThreadPool.h
  ../src/ctpl/ctpl_stl.h

  #database
  ../src/database/DataBaseManager.cpp
  ../src/database/DataBaseManager.h

  #utils
  ../src/utils/AlarmSwitchOffLogger.h
  ../src/utils/ContextArgMap.h
  ../src/utils/ConvertUTF.h
  ../src/utils/Icons.h
  ../src/utils/Icons_cfg.h
  ../src/utils/IniFileService.h
  ../src/utils/IniFileServiceImpl.h
  ../src/utils/IntervalSheduler.h
  ../src/utils/MessageBoxServer.h
  ../src/utils/RunGuard.h
  ../src/utils/ServerSettingUtils.h
  ../src/utils/Sheduler.h
  ../src/utils/ShedulerDK.h
  ../src/utils/ShedulerNewDuty.h
  ../src/utils/SignalSlotCommutator.h
  ../src/utils/SimpleIni.h
  ../src/utils/SoundAdjuster.h
  ../src/utils/TopologyService.h
  ../src/utils/TopologyServiceImpl.h
  ../src/utils/Utils.h
  ../src/utils/AlarmSwitchOffLogger.cpp
  ../src/utils/ContextArgMap.cpp
  ../src/utils/ConvertUTF.c
  ../src/utils/Icons.cpp
  ../src/utils/Icons_cfg.cpp
  ../src/utils/IniFileService.cpp
  ../src/utils/IniFileServiceImpl.cpp
  ../src/utils/IntervalSheduler.cpp
  ../src/utils/MessageBoxServer.cpp
  ../src/utils/RunGuard.cpp
  ../src/utils/ServerSettingUtils.cpp
  ../src/utils/Sheduler.cpp
  ../src/utils/ShedulerDK.cpp
  ../src/utils/ShedulerNewDuty.cpp
  ../src/utils/SignalSlotCommutator.cpp
  ../src/utils/SoundAdjuster.cpp
  ../src/utils/TopologyService.cpp
  ../src/utils/TopologyServiceImpl.cpp
  ../src/utils/Utils.cpp

  #tablemodel
  ../src/tablemodel/ComboBoxDelegate.h
  ../src/tablemodel/ServerTableModelJour.h
  ../src/tablemodel/ServerTreeModelUnitNode.h
  ../src/tablemodel/ComboBoxDelegate.cpp
  ../src/tablemodel/ServerTableModelJour.cpp
  ../src/tablemodel/ServerTreeModelUnitNode.cpp

  #port
  ../src/port/AbstractPort.h
  ../src/port/AbstractPortFactory.h
  ../src/port/ContainerRequesters.h
  ../src/port/DataQueueItem.h
  ../src/port/GraphTerminal.h
  ../src/port/Port.h
  ../src/port/PortFactory.h
  ../src/port/PortManager.h
  ../src/port/TcpServer.h
  ../src/port/ContainerRequesters.cpp
  ../src/port/DataQueueItem.cpp
  ../src/port/GraphTerminal.cpp
  ../src/port/Port.cpp
  ../src/port/PortFactory.cpp
  ../src/port/PortManager.cpp
  ../src/port/TcpServer.cpp

  #port
    #hendlerstateword
    ../src/handlerstateword/HandlerStateWordAbstract.h
    ../src/handlerstateword/ProcessingStateWordAbstract.h
    ../src/handlerstateword/HandlerStateWordAbstract.cpp
    ../src/handlerstateword/ProcessingStateWordAbstract.cpp
  #port
    #hendlerstateword
        #31
        ../src/handlerstateword/31/HandlerStateWord0x31.h
        ../src/handlerstateword/31/ProcessingStateWord0x31DK.h
        ../src/handlerstateword/31/HandlerStateWord0x31.cpp
        ../src/handlerstateword/31/ProcessingStateWord0x31DK.cpp
  #port
    #hendlerstateword
        #31
            #rlm
            ../src/handlerstateword/31/rlm/ProcessingStateWord0x31RLM.h
            ../src/handlerstateword/31/rlm/ProcessingStateWord0x31RLM.cpp

  #port
    #hendlerstateword
        #31
            #rlmc
            ../src/handlerstateword/31/rlmc/ProcessingStateWord0x31RLMC.h
            ../src/handlerstateword/31/rlmc/ProcessingStateWord0x31RLMC.cpp


  #port
    #hendlerstateword
        #31
            #tg
            ../src/handlerstateword/31/tg/ProcessingStateWord0x31TG.h
            ../src/handlerstateword/31/tg/ProcessingStateWord0x31TG.cpp
  #port
    #hendlerstateword
        #32
        ../src/handlerstateword/32/HandlerStateWord0x32.h
        ../src/handlerstateword/32/HandlerStateWord0x32.cpp
  #port
    #hendlerstateword
        #32
            #sota
            ../src/handlerstateword/32/sota/ProcessingStateWord0x32SOTABOD.h
            ../src/handlerstateword/32/sota/ProcessingStateWord0x32SOTADD.h
            ../src/handlerstateword/32/sota/ProcessingStateWord0x32SOTADK.h
            ../src/handlerstateword/32/sota/ProcessingStateWord0x32SOTAY4.h
            ../src/handlerstateword/32/sota/ProcessingStateWord0x32SOTABOD.cpp
            ../src/handlerstateword/32/sota/ProcessingStateWord0x32SOTADD.cpp
            ../src/handlerstateword/32/sota/ProcessingStateWord0x32SOTADK.cpp
            ../src/handlerstateword/32/sota/ProcessingStateWord0x32SOTAY4.cpp
  #port
    #hendlerstateword
        #32
            #t4k
            ../src/handlerstateword/32/t4k/ProcessingStateWord0x32T4KBOD.h
            ../src/handlerstateword/32/t4k/ProcessingStateWord0x32T4KDD.h
            ../src/handlerstateword/32/t4k/ProcessingStateWord0x32T4KDK.h
            ../src/handlerstateword/32/t4k/ProcessingStateWord0x32T4KY4.h
            ../src/handlerstateword/32/t4k/ProcessingStateWord0x32T4KBOD.cpp
            ../src/handlerstateword/32/t4k/ProcessingStateWord0x32T4KDD.cpp
            ../src/handlerstateword/32/t4k/ProcessingStateWord0x32T4KDK.cpp
            ../src/handlerstateword/32/t4k/ProcessingStateWord0x32T4KY4.cpp
  #port
    #hendlerstateword
        #32
            #tg
            ../src/handlerstateword/32/tg/ProcessingStateWord0x32TG.h
            ../src/handlerstateword/32/tg/ProcessingStateWord0x32TGDK.h
            ../src/handlerstateword/32/tg/ProcessingStateWord0x32TG.cpp
            ../src/handlerstateword/32/tg/ProcessingStateWord0x32TGDK.cpp
  #port
    #hendlerstateword
        #33
        ../src/handlerstateword/33/HandlerStateWord0x33.h
        ../src/handlerstateword/33/HandlerStateWord0x33.cpp
  #port
    #hendlerstateword
        #33
            #sota
            ../src/handlerstateword/33/sota/ProcessingStateWord0x33SOTABOD.h
            ../src/handlerstateword/33/sota/ProcessingStateWord0x33SOTADD.h
            ../src/handlerstateword/33/sota/ProcessingStateWord0x33SOTADK.h
            ../src/handlerstateword/33/sota/ProcessingStateWord0x33SOTAY4.h
            ../src/handlerstateword/33/sota/ProcessingStateWord0x33SOTABOD.cpp
            ../src/handlerstateword/33/sota/ProcessingStateWord0x33SOTADD.cpp
            ../src/handlerstateword/33/sota/ProcessingStateWord0x33SOTADK.cpp
            ../src/handlerstateword/33/sota/ProcessingStateWord0x33SOTAY4.cpp

  #port
    #hendlerstateword
        #33
            #t4k
            ../src/handlerstateword/33/t4k/ProcessingStateWord0x33T4KBOD.h
            ../src/handlerstateword/33/t4k/ProcessingStateWord0x33T4KDD.h
            ../src/handlerstateword/33/t4k/ProcessingStateWord0x33T4KDK.h
            ../src/handlerstateword/33/t4k/ProcessingStateWord0x33T4KY4.h
            ../src/handlerstateword/33/t4k/ProcessingStateWord0x33T4KBOD.cpp
            ../src/handlerstateword/33/t4k/ProcessingStateWord0x33T4KDD.cpp
            ../src/handlerstateword/33/t4k/ProcessingStateWord0x33T4KDK.cpp
            ../src/handlerstateword/33/t4k/ProcessingStateWord0x33T4KY4.cpp

  #port
    #hendlerstateword
        #33
            #tg
            ../src/handlerstateword/33/tg/ProcessingStateWord0x33TG.h
            ../src/handlerstateword/33/tg/ProcessingStateWord0x33TGDK.h
            ../src/handlerstateword/33/tg/ProcessingStateWord0x33TG.cpp
            ../src/handlerstateword/33/tg/ProcessingStateWord0x33TGDK.cpp
  #port
    #hendlerstateword
        #34
        ../src/handlerstateword/34/HandlerStateWord0x34.h
        ../src/handlerstateword/34/HandlerStateWord0x34.cpp
  #port
    #hendlerstateword
        #34
            #sota
            ../src/handlerstateword/34/sota/ProcessingStateWord0x34SOTADD.h
            ../src/handlerstateword/34/sota/ProcessingStateWord0x34SOTADD.cpp
  #port
    #hendlerstateword
        #34
            #t4k
            ../src/handlerstateword/34/t4k/ProcessingStateWord0x34T4KDD.h
            ../src/handlerstateword/34/t4k/ProcessingStateWord0x34T4KDD.cpp
  #port
    #hendlerstateword
        #34
            #tg
            ../src/handlerstateword/34/tg/ProcessingStateWord0x34TG.h
            ../src/handlerstateword/34/tg/ProcessingStateWord0x34TGDK.h
            ../src/handlerstateword/34/tg/ProcessingStateWord0x34TG.cpp
            ../src/handlerstateword/34/tg/ProcessingStateWord0x34TGDK.cpp
  #port
    #hendlerstateword
        #41
        ../src/handlerstateword/41/HandlerStateWord0x41.h
        ../src/handlerstateword/41/HandlerStateWord0x41.cpp
  #port
    #hendlerstateword
        #41
            #blip
            ../src/handlerstateword/41/blip/ProcessingStateWord0x41BLIPDK.h
            ../src/handlerstateword/41/blip/ProcessingStateWord0x41BLIPUzo.h
            ../src/handlerstateword/41/blip/ProcessingStateWord0x41BLIPSD.h
            ../src/handlerstateword/41/blip/ProcessingStateWord0x41BLIPIU.h
            ../src/handlerstateword/41/blip/ProcessingStateWord0x41BLIPDK.cpp
            ../src/handlerstateword/41/blip/ProcessingStateWord0x41BLIPUzo.cpp
            ../src/handlerstateword/41/blip/ProcessingStateWord0x41BLIPSD.cpp
            ../src/handlerstateword/41/blip/ProcessingStateWord0x41BLIPIU.cpp
  #port
    #hendlerstateword
        #41
            #ssoiblip
            ../src/handlerstateword/41/ssoiblip/ProcessingStateWord0x41SSOIBLIPUzo.h
            ../src/handlerstateword/41/ssoiblip/ProcessingStateWord0x41SSOIBLIPIU.h
            ../src/handlerstateword/41/ssoiblip/ProcessingStateWord0x41SSOIBLIPSD.h
            ../src/handlerstateword/41/ssoiblip/ProcessingStateWord0x41SSOIBLIPDK.h
            ../src/handlerstateword/41/ssoiblip/ProcessingStateWord0x41SSOIBLIPUzo.cpp
            ../src/handlerstateword/41/ssoiblip/ProcessingStateWord0x41SSOIBLIPIU.cpp
            ../src/handlerstateword/41/ssoiblip/ProcessingStateWord0x41SSOIBLIPSD.cpp
            ../src/handlerstateword/41/ssoiblip/ProcessingStateWord0x41SSOIBLIPDK.cpp
  #port
    #hendlerstateword
        #42
        ../src/handlerstateword/42/HandlerStateWord0x42.h
        ../src/handlerstateword/42/HandlerStateWord0x42.cpp
  #port
    #hendlerstateword
        #42
            #blip
            ../src/handlerstateword/42/blip/ProcessingStateWord0x42BLIPDK.h
            ../src/handlerstateword/42/blip/ProcessingStateWord0x42BLIPSD.h
            ../src/handlerstateword/42/blip/ProcessingStateWord0x42BLIPDK.cpp
            ../src/handlerstateword/42/blip/ProcessingStateWord0x42BLIPSD.cpp
  #port
    #hendlerstateword
        #42
            #ssoiblip
            ../src/handlerstateword/42/ssoiblip/ProcessingStateWord0x42SSOIBLIPSD.h
            ../src/handlerstateword/42/ssoiblip/ProcessingStateWord0x42SSOIBLIPDK.h
            ../src/handlerstateword/42/ssoiblip/ProcessingStateWord0x42SSOIBLIPSD.cpp
            ../src/handlerstateword/42/ssoiblip/ProcessingStateWord0x42SSOIBLIPDK.cpp

  #entity
  ../src/entity/JourEntity.h
  ../src/entity/KeyGroup.h
  ../src/entity/Operator.h
  ../src/entity/TreeItem.h
  ../src/entity/TypeUnitNode.h
  ../src/entity/UnitNode.h
  ../src/entity/UnitNodeCFG.h
  ../src/entity/UnitNodeFactory.h
  ../src/entity/UnitNodeTreeItem.h
  ../src/entity/JourEntity.cpp
  ../src/entity/KeyGroup.cpp
  ../src/entity/Operator.cpp
  ../src/entity/TreeItem.cpp
  ../src/entity/TypeUnitNode.cpp
  ../src/entity/UnitNode.cpp
  ../src/entity/UnitNodeCFG.cpp
  ../src/entity/UnitNodeFactory.cpp
  ../src/entity/UnitNodeTreeItem.cpp
  #entity
    #statewordparsers
    ../src/statewordparsers/SWP.h
    ../src/statewordparsers/SWPAlarm.h
    ../src/statewordparsers/SWPCliff.h
    ../src/statewordparsers/SWPClockPeriod.h
    ../src/statewordparsers/SWPClosure.h
    ../src/statewordparsers/SWPCountImpact.h
    ../src/statewordparsers/SWPDurationOvercoming.h
    ../src/statewordparsers/SWPExistDK.h
    ../src/statewordparsers/SWPFault.h
    ../src/statewordparsers/SWPInAlarm.h
    ../src/statewordparsers/SWPInCommunicationBreak.h
    ../src/statewordparsers/SWPInNorm.h
    ../src/statewordparsers/SWPInOpened.h
    ../src/statewordparsers/SWPInterrogation.h
    ../src/statewordparsers/SWPLevel.h
    ../src/statewordparsers/SWPLineBreak.h
    ../src/statewordparsers/SWPModeProcessing.h
    ../src/statewordparsers/SWPNorm.h
    ../src/statewordparsers/SWPOff.h
    ../src/statewordparsers/SWPOn.h
    ../src/statewordparsers/SWPOpened.h
    ../src/statewordparsers/SWPOutAlarm.h
    ../src/statewordparsers/SWPOutNorm.h
    ../src/statewordparsers/SWPReady.h
    ../src/statewordparsers/SWPShortCircuit.h
    ../src/statewordparsers/SWPSynchronization.h
    ../src/statewordparsers/SWPThreshold.h
    ../src/statewordparsers/SWPTimeImpact.h
    ../src/statewordparsers/SWPTimeImpact.h
    ../src/statewordparsers/SWPVoltage.h
    ../src/statewordparsers/SWPWasAlarm.h
    ../src/statewordparsers/SWPWasDK.h
    ../src/statewordparsers/SWPWasOpened.h
    ../src/statewordparsers/SWPWeakening.h
    ../src/statewordparsers/SWPWasCommunicationBreak.h
    ../src/statewordparsers/SWP.cpp
  #entity
    #statewordparsers
        #swpblip
        ../src/statewordparsers/swpblip/SWPBLIPType0x41.h
        ../src/statewordparsers/swpblip/SWPBLIPType0x42.h
        ../src/statewordparsers/swpblip/SWPIUBLIPType0x41.h
        ../src/statewordparsers/swpblip/SWPSDBLIPType0x41.h
        ../src/statewordparsers/swpblip/SWPSDBLIPType0x42.h
        ../src/statewordparsers/swpblip/SWPBLIPType0x41.cpp
        ../src/statewordparsers/swpblip/SWPBLIPType0x42.cpp
        ../src/statewordparsers/swpblip/SWPIUBLIPType0x41.cpp
        ../src/statewordparsers/swpblip/SWPSDBLIPType0x41.cpp
        ../src/statewordparsers/swpblip/SWPSDBLIPType0x42.cpp
  #entity
    #statewordparsers
        #swprlmc
        ../src/statewordparsers/swprlmc/SWPRLMCType0x31.h
        ../src/statewordparsers/swprlmc/SWPRLMCType0x31.cpp
  #entity
    #statewordparsers
        #swprlm
        ../src/statewordparsers/swprlm/SWPRLMType0x31.h
        ../src/statewordparsers/swprlm/SWPRLMType0x31.cpp
  #entity
    #statewordparsers
        #swpssoiblip
        ../src/statewordparsers/swpssoiblip/SWPSSOIBLIPType0x41.h
        ../src/statewordparsers/swpssoiblip/SWPSSOIBLIPType0x42.h
        ../src/statewordparsers/swpssoiblip/SWPSSOIIUBLIPType0x41.h
        ../src/statewordparsers/swpssoiblip/SWPSSOISDBLIPType0x41.h
        ../src/statewordparsers/swpssoiblip/SWPSSOISDBLIPType0x42.h
        ../src/statewordparsers/swpssoiblip/SWPSSOIBLIPType0x41.cpp
        ../src/statewordparsers/swpssoiblip/SWPSSOIBLIPType0x42.cpp
        ../src/statewordparsers/swpssoiblip/SWPSSOIIUBLIPType0x41.cpp
        ../src/statewordparsers/swpssoiblip/SWPSSOISDBLIPType0x41.cpp
        ../src/statewordparsers/swpssoiblip/SWPSSOISDBLIPType0x42.cpp
  #entity
    #statewordparsers
        #swpt4k
        ../src/statewordparsers/swpt4k/SWPT4KBODType0x32.h
        ../src/statewordparsers/swpt4k/SWPT4KBODType0x33.h
        ../src/statewordparsers/swpt4k/SWPT4KBODType0x34.h
        ../src/statewordparsers/swpt4k/SWPT4KDDCFType0x33.h
        ../src/statewordparsers/swpt4k/SWPT4KDDCFType0x34.h
        ../src/statewordparsers/swpt4k/SWPT4KDDCType0x32.h
        ../src/statewordparsers/swpt4k/SWPT4KDDCType0x33.h
        ../src/statewordparsers/swpt4k/SWPT4KDDCType0x34.h
        ../src/statewordparsers/swpt4k/SWPT4KDDType0x32.h
        ../src/statewordparsers/swpt4k/SWPT4KDDType0x33.h
        ../src/statewordparsers/swpt4k/SWPT4KDDType0x34.h
        ../src/statewordparsers/swpt4k/SWPT4KY4Type0x32.h
        ../src/statewordparsers/swpt4k/SWPT4KY4Type0x33.h
        ../src/statewordparsers/swpt4k/SWPT4KBODType0x32.cpp
        ../src/statewordparsers/swpt4k/SWPT4KBODType0x33.cpp
        ../src/statewordparsers/swpt4k/SWPT4KBODType0x34.cpp
        ../src/statewordparsers/swpt4k/SWPT4KDDCFType0x33.cpp
        ../src/statewordparsers/swpt4k/SWPT4KDDCFType0x34.cpp
        ../src/statewordparsers/swpt4k/SWPT4KDDCType0x32.cpp
        ../src/statewordparsers/swpt4k/SWPT4KDDCType0x33.cpp
        ../src/statewordparsers/swpt4k/SWPT4KDDCType0x34.cpp
        ../src/statewordparsers/swpt4k/SWPT4KDDType0x32.cpp
        ../src/statewordparsers/swpt4k/SWPT4KDDType0x33.cpp
        ../src/statewordparsers/swpt4k/SWPT4KDDType0x34.cpp
        ../src/statewordparsers/swpt4k/SWPT4KY4Type0x32.cpp
        ../src/statewordparsers/swpt4k/SWPT4KY4Type0x33.cpp
  #entity
    #statewordparsers
        #swptg
        ../src/statewordparsers/swptg/SWPTGSubType0x32.h
        ../src/statewordparsers/swptg/SWPTGSubType0x33.h
        ../src/statewordparsers/swptg/SWPTGSubType0x34.h
        ../src/statewordparsers/swptg/SWPTGType0x31.h
        ../src/statewordparsers/swptg/SWPTGType0x32.h
        ../src/statewordparsers/swptg/SWPTGType0x33.h
        ../src/statewordparsers/swptg/SWPTGType0x34.h
        ../src/statewordparsers/swptg/SWPTGSubType0x32.cpp
        ../src/statewordparsers/swptg/SWPTGSubType0x33.cpp
        ../src/statewordparsers/swptg/SWPTGSubType0x34.cpp
        ../src/statewordparsers/swptg/SWPTGType0x31.cpp
        ../src/statewordparsers/swptg/SWPTGType0x32.cpp
        ../src/statewordparsers/swptg/SWPTGType0x33.cpp
        ../src/statewordparsers/swptg/SWPTGType0x34.cpp
  #entity
    #statewordparsers
        #swsota
        ../src/statewordparsers/swpsota/SWPSOTABODType0x32.h
        ../src/statewordparsers/swpsota/SWPSOTABODType0x33.h
        ../src/statewordparsers/swpsota/SWPSOTABODType0x34.h
        ../src/statewordparsers/swpsota/SWPSOTADDFType0x33.h
        ../src/statewordparsers/swpsota/SWPSOTADDFType0x34.h
        ../src/statewordparsers/swpsota/SWPSOTADDType0x32.h
        ../src/statewordparsers/swpsota/SWPSOTADDType0x33.h
        ../src/statewordparsers/swpsota/SWPSOTADDType0x34.h
        ../src/statewordparsers/swpsota/SWPSOTAY4Type0x32.h
        ../src/statewordparsers/swpsota/SWPSOTAY4Type0x33.h
        ../src/statewordparsers/swpsota/SWPSOTABODType0x32.cpp
        ../src/statewordparsers/swpsota/SWPSOTABODType0x33.cpp
        ../src/statewordparsers/swpsota/SWPSOTABODType0x34.cpp
        ../src/statewordparsers/swpsota/SWPSOTADDFType0x33.cpp
        ../src/statewordparsers/swpsota/SWPSOTADDFType0x34.cpp
        ../src/statewordparsers/swpsota/SWPSOTADDType0x32.cpp
        ../src/statewordparsers/swpsota/SWPSOTADDType0x33.cpp
        ../src/statewordparsers/swpsota/SWPSOTADDType0x34.cpp
        ../src/statewordparsers/swpsota/SWPSOTAY4Type0x32.cpp
        ../src/statewordparsers/swpsota/SWPSOTAY4Type0x33.cpp


  #requester
  ../src/requester/AbstractRequester.h
  ../src/requester/ManagerSingleMsg.h
  ../src/requester/MultiUNStatusConnectRequester.h
  ../src/requester/ProcessDKWaiter.h
  ../src/requester/ConfirmationAdmissionWaiter.h
  ../src/requester/LockWaiter.h
  ../src/requester/OnOffIUWaiter.h  ../src/requester/AbstractRequester.cpp
  ../src/requester/ManagerSingleMsg.cpp
  ../src/requester/MultiUNStatusConnectRequester.cpp
  ../src/requester/ProcessDKWaiter.cpp
  ../src/requester/ConfirmationAdmissionWaiter.cpp
  ../src/requester/LockWaiter.cpp
  ../src/requester/OnOffIUWaiter.cpp

  AuthenticationDialog.ui
  MainWindowServer.ui
  resource.qrc
  ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(m_server
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET m_server APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(m_server SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(m_server
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(m_server PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Network Qt${QT_VERSION_MAJOR}::Sql Qt${QT_VERSION_MAJOR}::Multimedia Qt${QT_VERSION_MAJOR}::Xml Qt${QT_VERSION_MAJOR}::PrintSupport)

set_target_properties(m_server PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(m_server)
endif()
