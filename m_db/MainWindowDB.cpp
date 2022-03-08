#include "MainWindowDB.h"
#include "ui_MainWindowDB.h"

#include "ComboBoxDelegate.h"
#include "TablePrint.h"
#include "global.h"
#include "UnitNodeFactory.h"
#include "ServerSettingUtils.h"
#include "ServerTableModelJour.h"
#include "ContextArgMap.h"
#include "TypeUnitNode.h"

#include <IniFileService.h>
#include <QLineEdit>


QSharedPointer<GraphTerminal> MainWindowDB::graphTerminal = QSharedPointer<GraphTerminal>();

void MainWindowDB::applyStyleSheet()
{
    ui->dateEdit_From->setStyleSheet(deStyleSheet);

    ui->dateEdit_To->setStyleSheet(deStyleSheet);

    ui->comboBox_TypeSearch->setStyleSheet(cmbStyleSheet);
    ui->comboBox_TypeSearch->view()->setStyleSheet(lvStyleSheet);
    QPointer<QListView> view = new QListView(ui->comboBox_TypeSearch);
    view->setStyleSheet(lvStyleSheet);
    ui->comboBox_TypeSearch->setView(view);

    ui->comboBox_TypeUN->setStyleSheet(cmbStyleSheet);
    ui->comboBox_TypeUN->view()->setStyleSheet(lvStyleSheet);
    view = new QListView(ui->comboBox_TypeUN);
    view->setStyleSheet(lvStyleSheet);
    ui->comboBox_TypeUN->setView(view);

    ui->comboBox_Num1->setStyleSheet(cmbStyleSheet);
    ui->comboBox_Num1->view()->setStyleSheet(lvStyleSheet);
    view = new QListView(ui->comboBox_Num1);
    view->setStyleSheet(lvStyleSheet);
    ui->comboBox_Num1->setView(view);

    ui->comboBox_Num2->setStyleSheet(cmbStyleSheet);
    ui->comboBox_Num2->view()->setStyleSheet(lvStyleSheet);
    view = new QListView(ui->comboBox_Num2);
    view->setStyleSheet(lvStyleSheet);
    ui->comboBox_Num2->setView(view);

    ui->comboBox_Num3->setStyleSheet(cmbStyleSheet);
    ui->comboBox_Num3->view()->setStyleSheet(lvStyleSheet);
    view = new QListView(ui->comboBox_Num3);
    view->setStyleSheet(lvStyleSheet);
    ui->comboBox_Num3->setView(view);

    ui->comboBox_IPAddress->setStyleSheet(cmbStyleSheet);
    ui->comboBox_IPAddress->view()->setStyleSheet(lvStyleSheet);
    view = new QListView(ui->comboBox_IPAddress);
    view->setStyleSheet(lvStyleSheet);
    ui->comboBox_IPAddress->setView(view);

    ui->comboBox_TypeEvent->setStyleSheet(cmbStyleSheet);
    ui->comboBox_TypeEvent->view()->setStyleSheet(lvStyleSheet);
    view = new QListView(ui->comboBox_TypeEvent);
    view->setStyleSheet(lvStyleSheet);
    ui->comboBox_TypeEvent->setView(view);

    ui->comboBox_TypeOutUN->setStyleSheet(cmbStyleSheet);
    ui->comboBox_TypeOutUN->view()->setStyleSheet(lvStyleSheet);
    view = new QListView(ui->comboBox_TypeOutUN);
    view->setStyleSheet(lvStyleSheet);
    ui->comboBox_TypeOutUN->setView(view);

    ui->comboBox_AdamOff->setStyleSheet(cmbStyleSheet);
    ui->comboBox_AdamOff->view()->setStyleSheet(lvStyleSheet);
    view = new QListView(ui->comboBox_AdamOff);
    view->setStyleSheet(lvStyleSheet);
    ui->comboBox_AdamOff->setView(view);

    ui->comboBoxReason->setStyleSheet(cmbStyleSheet);
    ui->comboBoxReason->view()->setStyleSheet(lvStyleSheet);
    view = new QListView(ui->comboBoxReason);
    view->setStyleSheet(lvStyleSheet);
    ui->comboBoxReason->setView(view);

    ui->comboBoxTakenMeasures->setStyleSheet(cmbStyleSheet);
    ui->comboBoxTakenMeasures->view()->setStyleSheet(lvStyleSheet);
    view = new QListView(ui->comboBoxTakenMeasures);
    view->setStyleSheet(lvStyleSheet);
    ui->comboBoxTakenMeasures->setView(view);
}

void MainWindowDB::initialiseValidators()
{
    QRegExp regExpSSOIIU("(Все)|(ИУ[1-3])|(ВК[1-3])");
    regExpValidatorSSOIIU = QSharedPointer<QRegExpValidator>::create(regExpSSOIIU, this);

    QRegExp regExpIP("(Все)|(\\b(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|(Все)|2[0-4][0-9]|[01]?[0-9][0-9]?)(?::[0-9]{1,4})?\\b)");
    regExpValidatorIP = QSharedPointer<QRegExpValidator>::create(regExpIP, this);

    QRegExp regExp255("([0-9]?[0-9])|(1[0-9][0-9])|(2[0-4][0-9])|(25[0-5])|(Все)");
    regExpValidator255 = QSharedPointer<QRegExpValidator>::create(regExp255, this);

    QRegExp regExp0_255("([0-9])|([1-9][0-9])|(1[0-9][0-9])|(2[0-4][0-9])|(25[0-5])|(Все)");
    regExpValidator0_255 = QSharedPointer<QRegExpValidator>::create(regExp0_255, this);

    QRegExp regExp1_225("([1-9])|([1-9][0-9])|(1[0-9][0-9])|(2[0-2][0-9])|(22[0-5])|(Все)");
    regExpValidator1_225 = QSharedPointer<QRegExpValidator>::create(regExp1_225, this);

    QRegExp regExp1_255("([1-9])|([1-9][0-9])|(1[0-9][0-9])|(2[0-4][0-9])|(25[0-5])|(Все)");
    regExpValidator1_255 = QSharedPointer<QRegExpValidator>::create(regExp1_255, this);

    QRegExp regExp3("([1-3])|(Все)");
    regExpValidator1_3 = QSharedPointer<QRegExpValidator>::create(regExp3, this);

    QRegExp regExp4("([1-4])|(Все)");
    regExpValidator1_4 = QSharedPointer<QRegExpValidator>::create(regExp4, this);

    QRegExp regExp7("([0-7])|(Все)");
    regExpValidator0_7 = QSharedPointer<QRegExpValidator>::create(regExp7, this);

    QRegExp regExp8("([1-8])|(Все)");
    regExpValidator1_8 = QSharedPointer<QRegExpValidator>::create(regExp8, this);

    QRegExp regExp8v("([1-8])|(Все)|(вскрытие)");
    regExpValidator1_8v = QSharedPointer<QRegExpValidator>::create(regExp8v, this);

    QRegExp regExp26("([1-9])|(1[0-9])|(2[0-6])|(Все)");
    regExpValidator1_26 = QSharedPointer<QRegExpValidator>::create(regExp26, this);

    QRegExp regExp99("([1-9])|([1-9][0-9])|(Все)");
    regExpValidator1_99 = QSharedPointer<QRegExpValidator>::create(regExp99, this);

    QRegExp regExp100("([1-9])|([1-9][0-9])|(100)|(Все)");
    regExpValidator1_100 = QSharedPointer<QRegExpValidator>::create(regExp100, this);

}

void MainWindowDB::initialiseListCMB()
{
    listCmbData0_255.reserve(257);
    listCmbData0_255.append({"Все", -1});
    for(int i=0, n = 256; i < n; i++) {
        listCmbData0_255.append({QString::number(i), i});
    }

    listCmbData1_255.reserve(256);
    listCmbData1_255.append({"Все", -1});
    for(int i=1, n = 256; i < n; i++) {
        listCmbData1_255.append({QString::number(i), i});
    }

    listCmbData1_225.reserve(226);
    listCmbData1_225.append({"Все", -1});
    for(int i=1, n = 226; i < n; i++) {
        listCmbData1_225.append({QString::number(i), i});
    }


    listCmbData1_3.reserve(4);
    listCmbData1_3.append({"Все", -1});
    for(int i=1, n = 4; i < n; i++) {
        listCmbData1_3.append({QString::number(i), i});
    }

    listCmbData1_4.reserve(5);
    listCmbData1_4.append({"Все", -1});
    for(int i=1, n = 5; i < n; i++) {
        listCmbData1_4.append({QString::number(i), i});
    }

    listCmbData0_7.reserve(9);
    listCmbData0_7.append({"Все", -1});
    for(int i=0, n = 8; i < n; i++) {
        listCmbData0_7.append({QString::number(i), i});
    }

    listCmbData1_8.reserve(9);
    listCmbData1_8.append({"Все", -1});
    for(int i=1, n = 9; i < n; i++) {
        listCmbData1_8.append({QString::number(i), i});
    }

    listCmbData1_8v.reserve(10);
    listCmbData1_8v.append({"Все", -1});
    for(int i=1, n = 9; i < n; i++) {
        listCmbData1_8v.append({QString::number(i), i});
    }
    listCmbData1_8v.append({"вскрытие", 9});

    listCmbData1_26.reserve(27);
    listCmbData1_26.append({"Все", -1});
    for(int i=1, n = 27; i < n; i++) {
        listCmbData1_26.append({QString::number(i), i});
    }

    listCmbData1_99.reserve(100);
    listCmbData1_99.append({"Все", -1});
    for(int i=1, n = 100; i < n; i++) {
        listCmbData1_99.append({QString::number(i), i});
    }

    listCmbData1_100.reserve(101);
    listCmbData1_100.append({"Все", -1});
    for(int i=1, n = 101; i < n; i++) {
        listCmbData1_100.append({QString::number(i), i});
    }

    listCmbDataSSOIIU.reserve(7);
    listCmbDataSSOIIU.append({"Все", -1});
    listCmbDataSSOIIU.append({"ИУ1", 1});
    listCmbDataSSOIIU.append({"ИУ2", 2});
    listCmbDataSSOIIU.append({"ИУ3", 3});
    listCmbDataSSOIIU.append({"ВК1", 4});
    listCmbDataSSOIIU.append({"ВК2", 5});
    listCmbDataSSOIIU.append({"ВК3", 6});
}

void MainWindowDB::initilaseCmbList(QComboBox *cmb, const QList<QPair<QString, int>> &list) {
    cmb->clear();
    for(const auto& item : list) {
        cmb->addItem(item.first, item.second);
    }
}


void MainWindowDB::initilaseCmbValidator(QComboBox *cmb, const QSharedPointer<QValidator> &validator) {
    if(regExpValidator1_8.isNull())
        return;
    initilaseCmbValidator(cmb, validator.data());
}

void MainWindowDB::initilaseCmbValidator(QComboBox *cmb, QValidator const * validator) {
    cmb->setValidator(validator);
    if(cmb->isEditable())
        cmb->lineEdit()->setValidator(validator);
}

MainWindowDB::MainWindowDB(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindowDB)
{
    ui->setupUi(this);

    QString buildPrefix = "";

#ifdef QT_DEBUG
    buildPrefix = "b";
#else
    buildPrefix = "r";
#endif

    QDate date = QLocale(QLocale::C).toDate(QString(__DATE__).simplified(), QLatin1String("MMM d yyyy"));
    this->setWindowTitle(tr("База данных") + " - " + buildPrefix + "." + date.toString("dd.MM.yyyy"));


    qApp->setFont(qApp->font());

    setBlockSignal(true);

    applyStyleSheet();

    initialiseValidators();
    initialiseListCMB();

    ui->dateEdit_From->setDate(QDate::currentDate());
//    ui->dateEdit_From->setTime(QTime::fromString("00:00.00", "hh:MM.ms"));

    ui->dateEdit_To->setDate(QDate::currentDate());
//    ui->dateEdit_From->setTime(QTime::fromString("23:59.99", "hh:MM.ms"));


//    const auto& mapObject = JourEntity::getMapTypeObject(); // QMap<int, QString>
    auto&& inv = SetTypeUnitNode.toList();

    std::sort(std::begin(inv), std::end(inv),
      [](const TypeUnitNode* lhs, const TypeUnitNode* rhs) {
        return lhs->getStringTitle() < rhs->getStringTitle();
    });
    inv.move(inv.indexOf(&GroupTypeUnitNode::instance()), 0);
    inv.move(inv.indexOf(&SSOIIUTypeUnitNode::instance()),(inv.indexOf(&DDSOTATypeUnitNode::instance())+1));
    inv.move(inv.indexOf(&SSOISDTypeUnitNode::instance()),(inv.indexOf(&SSOIIUTypeUnitNode::instance())));
    inv.move(inv.indexOf(&DDSOTATypeUnitNode::instance()),(inv.indexOf(&Y4SOTATypeUnitNode::instance())));
    inv.move(inv.indexOf(&DDT4KMTypeUnitNode::instance()),(inv.indexOf(&Y4T4KMTypeUnitNode::instance())));
    inv.move(inv.indexOf(&BLIPSSOISDTypeUnitNode::instance()),(inv.indexOf(&BLIPSSOIIUTypeUnitNode::instance())));


    inv.move(inv.indexOf(&BLIPUZMonolitTypeUnitNode::instance()),(inv.indexOf(&BLIPSDTypeUnitNode::instance())+1));



    ui->comboBox_TypeUN->addItem(AllTypeUnitNode::instance().getStringTitle(), AllTypeUnitNode::instance().getIntTitle());
    for(const auto& key : qAsConst(inv)) {
        if(key->getInclusiveGroups()["ObjectGroup"])
            ui->comboBox_TypeUN->addItem(key->getStringTitle(), key->getIntTitle());
    }

    const auto& mapConnectObject = JourEntity::getMapTypeConnectObject(); // QMap<int, QString>
    ui->comboBox_TypeOutUN->addItem("Все", -1);
    for(auto it = mapConnectObject.begin(); it != mapConnectObject.end(); it++) {
        ui->comboBox_TypeOutUN->addItem(it.value(), it.key());
    }
    ui->comboBox_TypeOutUN->setCurrentIndex(1);

    {
        ui->comboBox_AdamOff->addItem("Все", -1);
        ui->comboBox_AdamOff->addItem("РИФ-РЛМ", 0);
        ui->comboBox_AdamOff->addItem("РИФ-РЛМ24", 1);
        ui->comboBox_AdamOff->addItem("РИФ-РЛМ(Б)", 2);
        ui->comboBox_AdamOff->addItem("РИФ-КРЛ", 3);
        ui->comboBox_AdamOff->addItem("Разрыв", 4);
        ui->comboBox_AdamOff->addItem("Трасса-1л", 5);
        ui->comboBox_AdamOff->setCurrentIndex(0);
    }


    ui->comboBox_TypeSearch->setCurrentIndex(0);

    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_cmbTypeUN->setVisible(false);
    ui->label_cmbTypeEvent->setVisible(false);
    ui->label_cmbTypeOutUN->setVisible(false);
    ui->label_cmbIPAddress->setVisible(false);
    ui->label_cmbNum1->setVisible(false);
    ui->label_cmbNum2->setVisible(false);
    ui->label_cmbNum3->setVisible(false);
    ui->label_cmbAdamOff->setVisible(false);


    ui->dateEdit_From->setVisible(false);
    ui->dateEdit_To->setVisible(false);

    ui->comboBox_TypeUN->setVisible(false);
    ui->comboBox_Num1->setVisible(false);
    ui->comboBox_Num2->setVisible(false);
    ui->comboBox_Num3->setVisible(false);
    ui->comboBox_TypeEvent->setVisible(false);
    ui->comboBox_TypeOutUN->setVisible(false);
    ui->comboBox_IPAddress->setVisible(false);
    ui->comboBox_AdamOff->setVisible(false);

//    ServerSettingUtils::loadTreeUnitNodes(UnitNodeFactory::makeShare(TypeUnitNodeEnum::SYSTEM));
//    TopologyService::

    m_dbManager = QSharedPointer<DataBaseManager>::create(this);

    modelJour = QSharedPointer<ServerTableModelJour>::create(this, false);

    modelJour->setFont(ui->tableView->font());
    modelJour->setForegroundRoleFlag(SwitchOffCondition::AlvaysOn);
    modelJour->setDecorationRoleFlag(SwitchOffCondition::RegularOff);

    ui->tableView->setModel(modelJour.data());    
    signalSotConnect();


    updComboBoxReason();
    updComboBoxTakenMeasures();

    {
        int visibleReasonMeasure = IniFileService::getValueBySectionKey("PostgresSQL", "allow_fix_data", "0").toInt();

        if(1 == visibleReasonMeasure) {
            ui->label_6->setVisible(false);
            ui->comboBoxReason->setVisible(false);
            ui->toolButtonAddReason->setVisible(false);
            ui->toolButtonRemoveReason->setVisible(false);

            ui->label_7->setVisible(false);
            ui->comboBoxTakenMeasures->setVisible(false);
            ui->toolButtonAddTakenMeasures->setVisible(false);
            ui->toolButtonRemoveTakenMeasures->setVisible(false);

            modelJour->setEnabledReasonMeasure(false);
        } else {
            ui->label_6->setVisible(true);
            ui->comboBoxReason->setVisible(true);
            ui->toolButtonAddReason->setVisible(true);
            ui->toolButtonRemoveReason->setVisible(true);

            ui->label_7->setVisible(true);
            ui->comboBoxTakenMeasures->setVisible(true);
            ui->toolButtonAddTakenMeasures->setVisible(true);
            ui->toolButtonRemoveTakenMeasures->setVisible(true);

            ui->tableView->setItemDelegateForColumn(4, new ComboBoxDelegate("reason", this));
            ui->tableView->setItemDelegateForColumn(5, new ComboBoxDelegate("measures", this));

            modelJour->setEnabledReasonMeasure(true);
        }
    }

    graphTerminal = loadPortsTcpGraphTerminal();

//    QRegExp regExpIP("localhost|((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])[\\.]){3}(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])");
//    QRegExp regExpNetPort("((6553[0-5])|[655[0-2][0-9]|65[0-4][0-9]{2}|6[0-4][0-9]{3}|[1-5][0-9]{4}|[1-9][0-9]{3}|[1-9][0-9]{2}|[1-9][0-9]|[0-9])");
    ui->comboBox_IPAddress->setValidator(regExpValidatorIP.data());

    ui->comboBox_Num1->setValidator(regExpValidator255.data());
    ui->comboBox_Num2->setValidator(regExpValidator255.data());
    ui->comboBox_Num3->setValidator(regExpValidator255.data());

    updComboBoxAddress();
//    updComboBoxNum1();
//    updComboBoxNum2();
//    updComboBoxNum3();

    connect(&beforeConstructotTimer, SIGNAL(timeout()), this, SLOT(beforeConstructot()));

    beforeConstructotTimer.setInterval(1000);
    beforeConstructotTimer.start();
}

void MainWindowDB::beforeConstructot() {
    beforeConstructotTimer.stop();

    setFromArgMap();

    setBlockSignal(false);

    setCurrentSqlQueryStr(createCompositFilter());
    modelJour->castomUpdateListRecords(getCurrentSqlQueryStr());


    if(!modelJour->getListJour().isEmpty()) {
        ui->tableView->resizeColumnToContents(1);
        ui->tableView->resizeColumnToContents(2);
        ui->tableView->resizeColumnToContents(3);
        ui->tableView->resizeColumnToContents(4);
        ui->tableView->resizeColumnToContents(5);
        ui->tableView->resizeColumnToContents(6);
    }

}


MainWindowDB::~MainWindowDB()
{
    delete ui;
}

void MainWindowDB::signalSotConnect() {
    connect(modelJour.data(),
            SIGNAL(needScrollToBottom()),
            ui->tableView,
            SLOT(scrollToBottom()));

    connect(ui->comboBox_TypeSearch,
            SIGNAL(currentIndexChanged(int)),
            this,
            SLOT(comboBox_TypeSearch_currentIndexChanged(int)));

    connect(ui->comboBox_TypeUN,
            SIGNAL(currentIndexChanged(int)),
            this,
            SLOT(comboBox_TypeUN_currentIndexChanged(int)));

    connect(ui->comboBox_IPAddress,
            SIGNAL(editTextChanged(QString)),
            this,
            SLOT(comboBox_IPAddress_editTextChanged(QString)));



    connect(ui->pushButton_UpdSelections,
            SIGNAL(clicked()),
            this,
            SLOT(pushButton_UpdSelections_clicked()));

//    connect(ui->comboBox_TypeSearch,
//            SIGNAL(currentIndexChanged(int)),
//            this,
//            SLOT(pushButton_UpdSelections_clicked()));

    connect(ui->dateEdit_From,
            SIGNAL(dateChanged(QDate)),
            this,
            SLOT(pushButton_UpdSelections_clicked()));

    connect(ui->dateEdit_To,
            SIGNAL(dateChanged(QDate)),
            this,
            SLOT(pushButton_UpdSelections_clicked()));

//    connect(ui->comboBox_TypeUN,
//            SIGNAL(currentIndexChanged(int)),
//            this,
//            SLOT(pushButton_UpdSelections_clicked()));

    connect(ui->comboBox_IPAddress,
            SIGNAL(editTextChanged(QString)),
            this,
            SLOT(pushButton_UpdSelections_clicked()));

    connect(ui->comboBox_Num1,
            SIGNAL(editTextChanged(QString)),
            this,
            SLOT(pushButton_UpdSelections_clicked()));

    connect(ui->comboBox_Num2,
            SIGNAL(editTextChanged(QString)),
            this,
            SLOT(pushButton_UpdSelections_clicked()));

    connect(ui->comboBox_Num3,
            SIGNAL(editTextChanged(QString)),
            this,
            SLOT(pushButton_UpdSelections_clicked()));

     connect(ui->comboBox_TypeEvent,
             SIGNAL(editTextChanged(QString)),
             this,
             SLOT(pushButton_UpdSelections_clicked()));

     connect(ui->comboBox_TypeOutUN,
             SIGNAL(currentIndexChanged(int)),
             this,
             SLOT(pushButton_UpdSelections_clicked()));

     connect(ui->comboBox_AdamOff,
             SIGNAL(currentIndexChanged(int)),
             this,
             SLOT(pushButton_UpdSelections_clicked()));

}


void MainWindowDB::setFromArgMap() {
    if(!ContextArgMap::argMap().contains("-type")
    || !ContextArgMap::argMap().contains("-num1")
    || !ContextArgMap::argMap().contains("-num2")
    || !ContextArgMap::argMap().contains("-num3")
    || !ContextArgMap::argMap().contains("-outType")
    || !ContextArgMap::argMap().contains("-adamOff")
    || !ContextArgMap::argMap().contains("-bazalt")
    || !ContextArgMap::argMap().contains("-ip")) {
        return;
    }

    /*if(ui->comboBox_TypeSearch->isVisible())*/ {
        ui->comboBox_TypeSearch->setCurrentIndex(1);
    }

    if(1 == QString(ContextArgMap::argMap().value("-bazalt")).toInt()
    && BLIPUZMonolitTypeUnitNode::instance().getIntTitle() == QString(ContextArgMap::argMap().value("-type")).toInt()) {
        auto index = ui->comboBox_TypeUN->findText("УЗ Монолит");
        ui->comboBox_TypeUN->setCurrentIndex(index);
    } else
    /*if(ui->comboBox_TypeUN->isVisible())*/ {
        auto index = ui->comboBox_TypeUN->findData(ContextArgMap::argMap().value("-type"));
        ui->comboBox_TypeUN->setCurrentIndex(index);
    }

    /*if(ui->comboBox_IPAddress->isVisible())*/ {
        auto index = ui->comboBox_IPAddress->findData(ContextArgMap::argMap().value("-ip"));
        if(-1 != index)
            ui->comboBox_IPAddress->setCurrentIndex(index);
        else
            ui->comboBox_IPAddress->setCurrentText(ContextArgMap::argMap().value("-ip"));
    }

    /*if(ui->comboBox_Num1->isVisible())*/ {
        auto index = ui->comboBox_Num1->findData(ContextArgMap::argMap().value("-num1"));
        if(-1 != index)
            ui->comboBox_Num1->setCurrentIndex(index);
        else
            ui->comboBox_Num1->setCurrentText(ContextArgMap::argMap().value("-num1"));
    }

    /*if(ui->comboBox_Num2->isVisible())*/ {
        auto index = ui->comboBox_Num2->findData(ContextArgMap::argMap().value("-num2"));
        if(-1 != index)
            ui->comboBox_Num2->setCurrentIndex(index);
        else
            ui->comboBox_Num2->setCurrentText(ContextArgMap::argMap().value("-num2"));
    }

    /*if(ui->comboBox_Num3->isVisible())*/ {
        auto index = ui->comboBox_Num3->findData(ContextArgMap::argMap().value("-num3"));
        if(-1 != index)
            ui->comboBox_Num3->setCurrentIndex(index);
        else
            ui->comboBox_Num3->setCurrentText(ContextArgMap::argMap().value("-num3"));
    }

    /*if(ui->comboBox_TypeOutUN->isVisible())*/ {
        auto index = ui->comboBox_TypeOutUN->findData(ContextArgMap::argMap().value("-outType"));
        if(-1 != index)
            ui->comboBox_TypeOutUN->setCurrentIndex(index);
        else
            ui->comboBox_TypeOutUN->setCurrentText(ContextArgMap::argMap().value("-outType"));
    }

    /*if(ui->comboBox_AdamOff->isVisible())*/ {
        auto index = ui->comboBox_AdamOff->findData(ContextArgMap::argMap().value("-adamOff"));
        if(-1 != index)
            ui->comboBox_AdamOff->setCurrentIndex(index);
        else
            ui->comboBox_AdamOff->setCurrentText(ContextArgMap::argMap().value("-adamOff"));
    }

    comboBox_TypeSearch_currentIndexChanged(ui->comboBox_TypeUN->currentIndex());
}

void MainWindowDB::currentBLIPSDTypeUnitNode() {
    //        "БЛ-IP СД"
    QMap<int, QString> mapEvent = JourEntity::getMapTypeEvent();

    ui->comboBox_TypeEvent->clear();
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eAllEvent), JourEntity::eAllEvent);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eAlarm), JourEntity::eAlarm);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eFault), JourEntity::eFault);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eCommand), JourEntity::eCommand);

    ui->label_cmbTypeOutUN->setVisible(true);
    ui->comboBox_TypeOutUN->setVisible(true);

    ui->label_cmbIPAddress->setVisible(true);
    ui->comboBox_IPAddress->setVisible(true);

    ui->label_cmbNum1->setVisible(false);
    ui->comboBox_Num1->setVisible(false);

    ui->label_cmbNum2->setVisible(true);
    ui->label_cmbNum2->setText("СД");
    ui->comboBox_Num2->setVisible(true);
    initilaseCmbList(ui->comboBox_Num2, listCmbData1_8);
    initilaseCmbValidator(ui->comboBox_Num2, regExpValidator1_8);

    ui->label_cmbNum3->setVisible(false);
    ui->comboBox_Num3->setVisible(false);

    ui->label_cmbAdamOff->setVisible(false);
    ui->comboBox_AdamOff->setVisible(false);
}

void MainWindowDB::currentBLIPUZMonolitTypeUnitNode() {
    //        "УЗ Монолит"
    QMap<int, QString> mapEvent = JourEntity::getMapTypeEvent();

    ui->comboBox_TypeEvent->clear();
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eAllEvent), JourEntity::eAllEvent);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eAlarm), JourEntity::eAlarm);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eFault), JourEntity::eFault);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eCommand), JourEntity::eCommand);

    ui->label_cmbTypeOutUN->setVisible(false);
    ui->comboBox_TypeOutUN->setVisible(false);

    ui->label_cmbIPAddress->setVisible(true);
    ui->comboBox_IPAddress->setVisible(true);

    ui->label_cmbNum1->setVisible(false);
    ui->comboBox_Num1->setVisible(false);

    ui->label_cmbNum2->setVisible(true);
    ui->label_cmbNum2->setText("СД");
    ui->comboBox_Num2->setVisible(true);
    initilaseCmbList(ui->comboBox_Num2, listCmbData1_3);
    initilaseCmbValidator(ui->comboBox_Num2, regExpValidator1_3);

    ui->label_cmbNum3->setVisible(false);
    ui->comboBox_Num3->setVisible(false);

    ui->label_cmbAdamOff->setVisible(false);
    ui->comboBox_AdamOff->setVisible(false);
}

void MainWindowDB::currentBLIPIUTypeUnitNode() {
    //        "БЛ-IP ИУ"
    QMap<int, QString> mapEvent = JourEntity::getMapTypeEvent();

    ui->comboBox_TypeEvent->clear();
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eAllEvent), JourEntity::eAllEvent);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eAlarm), JourEntity::eAlarm);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eFault), JourEntity::eFault);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eCommand), JourEntity::eCommand);

    ui->label_cmbTypeOutUN->setVisible(false);
    ui->comboBox_TypeOutUN->setVisible(false);

    ui->label_cmbIPAddress->setVisible(true);
    ui->comboBox_IPAddress->setVisible(true);

    ui->label_cmbNum1->setVisible(false);
    ui->comboBox_Num1->setVisible(false);

    ui->label_cmbNum2->setVisible(true);
    ui->label_cmbNum2->setText("ИУ");
    ui->comboBox_Num2->setVisible(true);
    initilaseCmbList(ui->comboBox_Num2, listCmbData1_4);
    initilaseCmbValidator(ui->comboBox_Num2, regExpValidator1_4);

    ui->label_cmbNum3->setVisible(false);
    ui->comboBox_Num3->setVisible(false);

    ui->label_cmbAdamOff->setVisible(false);
    ui->comboBox_AdamOff->setVisible(false);
}

void MainWindowDB::currentBLIPSSOISDTypeUnitNode() {
    //        "СД ССОИ-IP"
    QMap<int, QString> mapEvent = JourEntity::getMapTypeEvent();

    ui->comboBox_TypeEvent->clear();
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eAllEvent), JourEntity::eAllEvent);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eAlarm), JourEntity::eAlarm);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eFault), JourEntity::eFault);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eCommand), JourEntity::eCommand);

    ui->label_cmbTypeOutUN->setVisible(true);
    ui->comboBox_TypeOutUN->setVisible(true);

    ui->label_cmbIPAddress->setVisible(true);
    ui->comboBox_IPAddress->setVisible(true);

    ui->label_cmbNum1->setVisible(true);
    ui->label_cmbNum1->setText("Адрес");
    ui->comboBox_Num1->setVisible(true);
    initilaseCmbList(ui->comboBox_Num1, listCmbData1_99);
    initilaseCmbValidator(ui->comboBox_Num1, regExpValidator1_99);

    ui->label_cmbNum2->setVisible(true);
    ui->label_cmbNum2->setText("СД");
    ui->comboBox_Num2->setVisible(true);
    initilaseCmbList(ui->comboBox_Num2, listCmbData1_8v);
    initilaseCmbValidator(ui->comboBox_Num2, regExpValidator1_8v);

    ui->label_cmbNum3->setVisible(false);
    ui->comboBox_Num3->setVisible(false);

    ui->label_cmbAdamOff->setVisible(false);
    ui->comboBox_AdamOff->setVisible(false);
}

void MainWindowDB::currentBLIPSSOIIUTypeUnitNode() {
    //        "ИУ ССОИ-IP"
    QMap<int, QString> mapEvent = JourEntity::getMapTypeEvent();

    ui->comboBox_TypeEvent->clear();
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eAllEvent), JourEntity::eAllEvent);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eAlarm), JourEntity::eAlarm);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eFault), JourEntity::eFault);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eCommand), JourEntity::eCommand);

    ui->label_cmbTypeOutUN->setVisible(false);
    ui->comboBox_TypeOutUN->setVisible(false);

    ui->label_cmbIPAddress->setVisible(true);
    ui->comboBox_IPAddress->setVisible(true);

    ui->label_cmbNum1->setVisible(true);
    ui->label_cmbNum1->setText("Адрес");
    ui->comboBox_Num1->setVisible(true);
    initilaseCmbList(ui->comboBox_Num1, listCmbData1_99);
    initilaseCmbValidator(ui->comboBox_Num1, regExpValidator1_99);

    ui->label_cmbNum2->setVisible(true);
    ui->label_cmbNum2->setText("ИУ");
    ui->comboBox_Num2->setVisible(true);
    initilaseCmbList(ui->comboBox_Num2, listCmbData1_4);
    initilaseCmbValidator(ui->comboBox_Num2, regExpValidator1_4);

    ui->label_cmbNum3->setVisible(false);
    ui->comboBox_Num3->setVisible(false);

    ui->label_cmbAdamOff->setVisible(false);
    ui->comboBox_AdamOff->setVisible(false);
}


void MainWindowDB::currentKLTypeUnitNode() {
    //        "КЛ1 (концентратор) СД"
    QMap<int, QString> mapEvent = JourEntity::getMapTypeEvent();

    ui->comboBox_TypeEvent->clear();
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eAllEvent), JourEntity::eAllEvent);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eAlarm), JourEntity::eAlarm);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eFault), JourEntity::eFault);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eCommand), JourEntity::eCommand);

    ui->label_cmbTypeOutUN->setVisible(false);
    ui->comboBox_TypeOutUN->setVisible(false);

    ui->label_cmbIPAddress->setVisible(true);
    ui->comboBox_IPAddress->setVisible(true);

    ui->label_cmbNum1->setVisible(true);
    ui->label_cmbNum1->setText("Адрес");
    ui->comboBox_Num1->setVisible(true);
    initilaseCmbList(ui->comboBox_Num1, listCmbData1_99);
    initilaseCmbValidator(ui->comboBox_Num1, regExpValidator1_99);

    ui->label_cmbNum2->setVisible(true);
    ui->label_cmbNum2->setText("СД");
    ui->comboBox_Num2->setVisible(true);
    initilaseCmbList(ui->comboBox_Num2, listCmbData1_4);
    initilaseCmbValidator(ui->comboBox_Num2, regExpValidator1_4);

    ui->label_cmbNum3->setVisible(false);
    ui->comboBox_Num3->setVisible(false);

    ui->label_cmbAdamOff->setVisible(false);
    ui->comboBox_AdamOff->setVisible(false);
}

void MainWindowDB::currentTGTypeUnitNode() {
    //        "Точка/Гарда"
    QMap<int, QString> mapEvent = JourEntity::getMapTypeEvent();

    ui->comboBox_TypeEvent->clear();
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eAllEvent), JourEntity::eAllEvent);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eAlarm), JourEntity::eAlarm);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eFault), JourEntity::eFault);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eCommand), JourEntity::eCommand);

    ui->label_cmbTypeOutUN->setVisible(false);
    ui->comboBox_TypeOutUN->setVisible(false);

    ui->label_cmbIPAddress->setVisible(true);
    ui->comboBox_IPAddress->setVisible(true);

    ui->label_cmbNum1->setVisible(true);
    ui->label_cmbNum1->setText("Адрес");
    ui->comboBox_Num1->setVisible(true);
    initilaseCmbList(ui->comboBox_Num1, listCmbData1_99);
    initilaseCmbValidator(ui->comboBox_Num1, regExpValidator1_99);

    ui->label_cmbNum2->setVisible(true);
    ui->label_cmbNum2->setText("Участок-ЧЭ");
    ui->comboBox_Num2->setVisible(true);
    initilaseCmbList(ui->comboBox_Num2, listCmbData1_4);
    initilaseCmbValidator(ui->comboBox_Num2, regExpValidator1_4);

    ui->label_cmbNum3->setVisible(false);
    ui->comboBox_Num3->setVisible(false);

    ui->label_cmbAdamOff->setVisible(false);
    ui->comboBox_AdamOff->setVisible(false);
}

void MainWindowDB::currentRLMKRLTypeUnitNode() {
    //        "РИФ-РЛМ/КРЛ/Трасса"
    QMap<int, QString> mapEvent = JourEntity::getMapTypeEvent();

    ui->comboBox_TypeEvent->clear();
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eAllEvent), JourEntity::eAllEvent);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eAlarm), JourEntity::eAlarm);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eFault), JourEntity::eFault);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eCommand), JourEntity::eCommand);

    ui->label_cmbTypeOutUN->setVisible(false);
    ui->comboBox_TypeOutUN->setVisible(false);

    ui->label_cmbIPAddress->setVisible(true);
    ui->comboBox_IPAddress->setVisible(true);

    ui->label_cmbNum1->setVisible(true);
    ui->label_cmbNum1->setText("Адрес");
    ui->comboBox_Num1->setVisible(true);
    initilaseCmbList(ui->comboBox_Num1, listCmbData1_99);
    initilaseCmbValidator(ui->comboBox_Num1, regExpValidator1_99);

    ui->label_cmbNum2->setVisible(false);
    ui->comboBox_Num2->setVisible(false);

    ui->label_cmbNum3->setVisible(false);
    ui->comboBox_Num3->setVisible(false);

    ui->label_cmbAdamOff->setVisible(true);
    ui->label_cmbAdamOff->setText("Датчик");
    ui->comboBox_AdamOff->setVisible(true);
}

void MainWindowDB::currentRLMCTypeUnitNode() {
    //        "РИФ-РЛМ-С"
    QMap<int, QString> mapEvent = JourEntity::getMapTypeEvent();

    ui->comboBox_TypeEvent->clear();
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eAllEvent), JourEntity::eAllEvent);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eAlarm), JourEntity::eAlarm);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eFault), JourEntity::eFault);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eCommand), JourEntity::eCommand);

    ui->label_cmbTypeOutUN->setVisible(false);
    ui->comboBox_TypeOutUN->setVisible(false);

    ui->label_cmbIPAddress->setVisible(true);
    ui->comboBox_IPAddress->setVisible(true);

    ui->label_cmbNum1->setVisible(true);
    ui->label_cmbNum1->setText("Адрес");
    ui->comboBox_Num1->setVisible(true);
    initilaseCmbList(ui->comboBox_Num1, listCmbData1_99);
    initilaseCmbValidator(ui->comboBox_Num1, regExpValidator1_99);

    ui->label_cmbNum2->setVisible(false);
    ui->comboBox_Num2->setVisible(false);

    ui->label_cmbNum3->setVisible(false);
    ui->comboBox_Num3->setVisible(false);

    ui->label_cmbAdamOff->setVisible(false);
    ui->comboBox_AdamOff->setVisible(false);
}

void MainWindowDB::currentBODT4KMTypeUnitNode() {
    //        "Точка-М/Гарда БОД"
    QMap<int, QString> mapEvent = JourEntity::getMapTypeEvent();

    ui->comboBox_TypeEvent->clear();
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eAllEvent), JourEntity::eAllEvent);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eAlarm), JourEntity::eAlarm);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eFault), JourEntity::eFault);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eCommand), JourEntity::eCommand);

    ui->label_cmbTypeOutUN->setVisible(false);
    ui->comboBox_TypeOutUN->setVisible(false);

    ui->label_cmbIPAddress->setVisible(true);
    ui->comboBox_IPAddress->setVisible(true);

    ui->label_cmbNum1->setVisible(true);
    ui->label_cmbNum1->setText("Адрес");
    ui->comboBox_Num1->setVisible(true);
    initilaseCmbList(ui->comboBox_Num1, listCmbData1_99);
    initilaseCmbValidator(ui->comboBox_Num1, regExpValidator1_99);

    ui->label_cmbNum2->setVisible(false);
    ui->comboBox_Num2->setVisible(false);

    ui->label_cmbNum3->setVisible(false);
    ui->comboBox_Num3->setVisible(false);

    ui->label_cmbAdamOff->setVisible(false);
    ui->comboBox_AdamOff->setVisible(false);
}

void MainWindowDB::currentY4T4KMTypeUnitNode() {
    //        "Точка-М/Гарда Участок"
    QMap<int, QString> mapEvent = JourEntity::getMapTypeEvent();

    ui->comboBox_TypeEvent->clear();
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eAllEvent), JourEntity::eAllEvent);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eAlarm), JourEntity::eAlarm);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eFault), JourEntity::eFault);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eCommand), JourEntity::eCommand);

    ui->label_cmbTypeOutUN->setVisible(false);
    ui->comboBox_TypeOutUN->setVisible(false);

    ui->label_cmbIPAddress->setVisible(true);
    ui->comboBox_IPAddress->setVisible(true);

    ui->label_cmbNum1->setVisible(false);
    ui->comboBox_Num1->setVisible(false);

    ui->label_cmbNum2->setVisible(true);
    ui->label_cmbNum2->setText("Участок");
    ui->comboBox_Num2->setVisible(true);
    initilaseCmbList(ui->comboBox_Num2, listCmbData1_4);
    initilaseCmbValidator(ui->comboBox_Num2, regExpValidator1_4);

    ui->label_cmbNum3->setVisible(false);
    ui->comboBox_Num3->setVisible(false);

    ui->label_cmbAdamOff->setVisible(false);
    ui->comboBox_AdamOff->setVisible(false);
}

void MainWindowDB::currentDDT4KMTypeUnitNode() {
    //        "Точка-М/Гарда ДД"
    QMap<int, QString> mapEvent = JourEntity::getMapTypeEvent();

    ui->comboBox_TypeEvent->clear();
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eAllEvent), JourEntity::eAllEvent);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eAlarm), JourEntity::eAlarm);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eFault), JourEntity::eFault);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eCommand), JourEntity::eCommand);

    ui->label_cmbTypeOutUN->setVisible(false);
    ui->comboBox_TypeOutUN->setVisible(false);

    ui->label_cmbIPAddress->setVisible(true);
    ui->comboBox_IPAddress->setVisible(true);

    ui->label_cmbNum1->setVisible(false);
    ui->comboBox_Num1->setVisible(false);

    ui->label_cmbNum2->setVisible(true);
    ui->label_cmbNum2->setText("ДД");
    ui->comboBox_Num2->setVisible(true);
    initilaseCmbList(ui->comboBox_Num2, listCmbData1_26);
    initilaseCmbValidator(ui->comboBox_Num2, regExpValidator1_26);

    ui->label_cmbNum3->setVisible(false);
    ui->comboBox_Num3->setVisible(false);

    ui->label_cmbAdamOff->setVisible(false);
    ui->comboBox_AdamOff->setVisible(false);
}

void MainWindowDB::currentBODSOTATypeUnitNode() {
    //        "Сота/Сота-М БОД"
    QMap<int, QString> mapEvent = JourEntity::getMapTypeEvent();

    ui->comboBox_TypeEvent->clear();
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eAllEvent), JourEntity::eAllEvent);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eAlarm), JourEntity::eAlarm);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eFault), JourEntity::eFault);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eCommand), JourEntity::eCommand);

    ui->label_cmbTypeOutUN->setVisible(false);
    ui->comboBox_TypeOutUN->setVisible(false);

    ui->label_cmbIPAddress->setVisible(true);
    ui->comboBox_IPAddress->setVisible(true);

    ui->label_cmbNum1->setVisible(true);
    ui->label_cmbNum1->setText("Адрес");
    ui->comboBox_Num1->setVisible(true);
    initilaseCmbList(ui->comboBox_Num1, listCmbData1_99);
    initilaseCmbValidator(ui->comboBox_Num1, regExpValidator1_99);

    ui->label_cmbNum2->setVisible(false);
    ui->comboBox_Num2->setVisible(false);

    ui->label_cmbNum3->setVisible(false);
    ui->comboBox_Num3->setVisible(false);

    ui->label_cmbAdamOff->setVisible(false);
    ui->comboBox_AdamOff->setVisible(false);
}

void MainWindowDB::currentY4SOTATypeUnitNode() {
    //        "Сота/Сота-М Участок"
    QMap<int, QString> mapEvent = JourEntity::getMapTypeEvent();

    ui->comboBox_TypeEvent->clear();
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eAllEvent), JourEntity::eAllEvent);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eAlarm), JourEntity::eAlarm);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eFault), JourEntity::eFault);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eCommand), JourEntity::eCommand);

    ui->label_cmbTypeOutUN->setVisible(false);
    ui->comboBox_TypeOutUN->setVisible(false);

    ui->label_cmbIPAddress->setVisible(true);
    ui->comboBox_IPAddress->setVisible(true);

    ui->label_cmbNum1->setVisible(false);
    ui->comboBox_Num1->setVisible(false);

    ui->label_cmbNum2->setVisible(true);
    ui->label_cmbNum2->setText("Участок");
    ui->comboBox_Num2->setVisible(true);
    initilaseCmbList(ui->comboBox_Num2, listCmbData1_4);
    initilaseCmbValidator(ui->comboBox_Num2, regExpValidator1_4);

    ui->label_cmbNum3->setVisible(false);
    ui->comboBox_Num3->setVisible(false);

    ui->label_cmbAdamOff->setVisible(false);
    ui->comboBox_AdamOff->setVisible(false);
}

void MainWindowDB::currentDDSOTATypeUnitNode() {
    //        "Сота/Сота-М ДД"
    QMap<int, QString> mapEvent = JourEntity::getMapTypeEvent();

    ui->comboBox_TypeEvent->clear();
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eAllEvent), JourEntity::eAllEvent);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eAlarm), JourEntity::eAlarm);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eFault), JourEntity::eFault);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eCommand), JourEntity::eCommand);

    ui->label_cmbTypeOutUN->setVisible(false);
    ui->comboBox_TypeOutUN->setVisible(false);

    ui->label_cmbIPAddress->setVisible(true);
    ui->comboBox_IPAddress->setVisible(true);

    ui->label_cmbNum1->setVisible(false);
    ui->comboBox_Num1->setVisible(false);

    ui->label_cmbNum2->setVisible(true);
    ui->label_cmbNum2->setText("ДД");
    ui->comboBox_Num2->setVisible(true);
    initilaseCmbList(ui->comboBox_Num2, listCmbData1_100);
    initilaseCmbValidator(ui->comboBox_Num2, regExpValidator1_100);

    ui->label_cmbNum3->setVisible(false);
    ui->comboBox_Num3->setVisible(false);

    ui->label_cmbAdamOff->setVisible(false);
    ui->comboBox_AdamOff->setVisible(false);
}

void MainWindowDB::currentSSOISDTypeUnitNode() {
    //        "ССОИ СД"
    QMap<int, QString> mapEvent = JourEntity::getMapTypeEvent();

    ui->comboBox_TypeEvent->clear();
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eAllEvent), JourEntity::eAllEvent);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eAlarm), JourEntity::eAlarm);
    ui->comboBox_TypeEvent->addItem("- " + mapEvent.value(JourEntity::eAlarmWorked), JourEntity::eAlarmWorked);
    ui->comboBox_TypeEvent->addItem("- " + mapEvent.value(JourEntity::eAlarmOpening), JourEntity::eAlarmOpening);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eFault), JourEntity::eFault);
    ui->comboBox_TypeEvent->addItem("- " + mapEvent.value(JourEntity::eFaultNoConnect), JourEntity::eFaultNoConnect);
    ui->comboBox_TypeEvent->addItem("- " + mapEvent.value(JourEntity::eFaultDK), JourEntity::eFaultDK);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eCommand), JourEntity::eCommand);
    ui->comboBox_TypeEvent->addItem("- " + mapEvent.value(JourEntity::eCommandDK), JourEntity::eCommandDK);
    ui->comboBox_TypeEvent->addItem("- " + mapEvent.value(JourEntity::eCommandUZMonolit), JourEntity::eCommandUZMonolit);
    ui->comboBox_TypeEvent->addItem("- " + mapEvent.value(JourEntity::eCommandOperator), JourEntity::eCommandOperator);

    ui->label_cmbTypeOutUN->setVisible(true);
    ui->comboBox_TypeOutUN->setVisible(true);

    ui->label_cmbIPAddress->setVisible(true);
    ui->comboBox_IPAddress->setVisible(true);

    ui->label_cmbNum1->setVisible(true);
    ui->label_cmbNum1->setText("Канал");
    ui->comboBox_Num1->setVisible(true);
    initilaseCmbList(ui->comboBox_Num1, listCmbData1_4);
    initilaseCmbValidator(ui->comboBox_Num1, regExpValidator1_4);

    ui->label_cmbNum2->setVisible(true);
    ui->label_cmbNum2->setText("БЛ");
    ui->comboBox_Num2->setVisible(true);
    initilaseCmbList(ui->comboBox_Num2, listCmbData1_99);
    initilaseCmbValidator(ui->comboBox_Num2, regExpValidator1_99);

    ui->label_cmbNum3->setVisible(true);
    ui->label_cmbNum3->setText("СД");
    ui->comboBox_Num3->setVisible(true);
    initilaseCmbList(ui->comboBox_Num3, listCmbData1_8v);
    initilaseCmbValidator(ui->comboBox_Num3, regExpValidator1_8v);

    ui->label_cmbAdamOff->setVisible(false);
    ui->comboBox_AdamOff->setVisible(false);
}

void MainWindowDB::currentSSOIIUTypeUnitNode() {
    //        "ССОИ ИУ"
    QMap<int, QString> mapEvent = JourEntity::getMapTypeEvent();

    ui->comboBox_TypeEvent->clear();
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eAllEvent), JourEntity::eAllEvent);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eFault), JourEntity::eFault);
    ui->comboBox_TypeEvent->addItem("- " + mapEvent.value(JourEntity::eFaultNoConnect), JourEntity::eFaultNoConnect);
    ui->comboBox_TypeEvent->addItem("- " + mapEvent.value(JourEntity::eFaultCommand), JourEntity::eFaultCommand);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eCommand), JourEntity::eCommand);

    ui->label_cmbTypeOutUN->setVisible(true);
    ui->comboBox_TypeOutUN->setVisible(true);

    ui->label_cmbIPAddress->setVisible(true);
    ui->comboBox_IPAddress->setVisible(true);

    ui->label_cmbNum1->setVisible(true);
    ui->label_cmbNum1->setText("Канал");
    ui->comboBox_Num1->setVisible(true);
    initilaseCmbList(ui->comboBox_Num1, listCmbData1_4);
    initilaseCmbValidator(ui->comboBox_Num1, regExpValidator1_4);

    ui->label_cmbNum2->setVisible(true);
    ui->label_cmbNum2->setText("БЛ");
    ui->comboBox_Num2->setVisible(true);
    initilaseCmbList(ui->comboBox_Num2, listCmbData1_99);
    initilaseCmbValidator(ui->comboBox_Num2, regExpValidator1_99);

    ui->label_cmbNum3->setVisible(true);
    ui->label_cmbNum3->setText("ИУ");
    ui->comboBox_Num3->setVisible(true);
    initilaseCmbList(ui->comboBox_Num3, listCmbDataSSOIIU);
    initilaseCmbValidator(ui->comboBox_Num3, regExpValidatorSSOIIU);

    ui->label_cmbAdamOff->setVisible(false);
    ui->comboBox_AdamOff->setVisible(false);
}

void MainWindowDB::currentADAMTypeUnitNode() {
    //        "ADAM"
    QMap<int, QString> mapEvent = JourEntity::getMapTypeEvent();

    ui->comboBox_TypeEvent->clear();
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eAllEvent), JourEntity::eAllEvent);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eAlarm), JourEntity::eAlarm);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eFault), JourEntity::eFault);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eCommand), JourEntity::eCommand);

    ui->label_cmbTypeOutUN->setVisible(false);
    ui->comboBox_TypeOutUN->setVisible(false);

    ui->label_cmbIPAddress->setVisible(true);
    ui->comboBox_IPAddress->setVisible(true);

    ui->label_cmbNum1->setVisible(true);
    ui->label_cmbNum1->setText("Адрес");
    ui->comboBox_Num1->setVisible(true);
    initilaseCmbList(ui->comboBox_Num1, listCmbData1_255);
    initilaseCmbValidator(ui->comboBox_Num1, regExpValidator1_255);

    ui->label_cmbNum2->setVisible(true);
    ui->label_cmbNum2->setText("ИУ");
    ui->comboBox_Num2->setVisible(true);
    initilaseCmbList(ui->comboBox_Num2, listCmbData0_7);
    initilaseCmbValidator(ui->comboBox_Num2, regExpValidator0_7);

    ui->label_cmbNum3->setVisible(false);
    ui->comboBox_Num3->setVisible(false);

    ui->label_cmbAdamOff->setVisible(false);
    ui->comboBox_AdamOff->setVisible(false);
}

void MainWindowDB::currentTorosTypeUnitNode() {
    //        "Торос"
    QMap<int, QString> mapEvent = JourEntity::getMapTypeEvent();

    ui->comboBox_TypeEvent->clear();
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eAllEvent), JourEntity::eAllEvent);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eAlarm), JourEntity::eAlarm);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eFault), JourEntity::eFault);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eCommand), JourEntity::eCommand);

    ui->label_cmbTypeOutUN->setVisible(false);
    ui->comboBox_TypeOutUN->setVisible(false);

    ui->label_cmbIPAddress->setVisible(true);
    ui->comboBox_IPAddress->setVisible(true);

    ui->label_cmbNum1->setVisible(true);
    ui->label_cmbNum1->setText("Адрес");
    ui->comboBox_Num1->setVisible(true);
    initilaseCmbList(ui->comboBox_Num1, listCmbData1_99);
    initilaseCmbValidator(ui->comboBox_Num1, regExpValidator1_99);

    ui->label_cmbNum2->setVisible(false);
    ui->comboBox_Num2->setVisible(false);

    ui->label_cmbNum3->setVisible(false);
    ui->comboBox_Num3->setVisible(false);

    ui->label_cmbAdamOff->setVisible(false);
    ui->comboBox_AdamOff->setVisible(false);
}

void MainWindowDB::currentDefaultTypeUnitNode() {
    QMap<int, QString> mapEvent = JourEntity::getMapTypeEvent();

    ui->comboBox_TypeEvent->clear();
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eAllEvent), JourEntity::eAllEvent);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eAlarm), JourEntity::eAlarm);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eFault), JourEntity::eFault);
    ui->comboBox_TypeEvent->addItem(mapEvent.value(JourEntity::eCommand), JourEntity::eCommand);

    ui->label_cmbTypeOutUN->setVisible(false);
    ui->comboBox_TypeOutUN->setVisible(false);

    ui->label_cmbIPAddress->setVisible(true);
    ui->comboBox_IPAddress->setVisible(true);

    ui->label_cmbNum1->setVisible(false);
    ui->comboBox_Num1->setVisible(false);

    ui->label_cmbNum2->setVisible(false);
    ui->comboBox_Num2->setVisible(false);

    ui->label_cmbNum3->setVisible(false);
    ui->comboBox_Num3->setVisible(false);

    ui->label_cmbAdamOff->setVisible(false);
    ui->comboBox_AdamOff->setVisible(false);
}

void MainWindowDB::comboBox_TypeUN_currentIndexChanged(int index)
{
    const auto&  oldBlock = getBlockSignal();
    setBlockSignal(true);

    QString currentText = ui->comboBox_TypeUN->itemText(index);

    if(currentText == BLIPSDTypeUnitNode::instance().getStringTitle()) {
        currentBLIPSDTypeUnitNode();
    } else if(currentText == BLIPUZMonolitTypeUnitNode::instance().getStringTitle()) {
        currentBLIPUZMonolitTypeUnitNode();
    } else if(currentText == BLIPIUTypeUnitNode::instance().getStringTitle()) {
        currentBLIPIUTypeUnitNode();
    } else if(currentText == BLIPSSOISDTypeUnitNode::instance().getStringTitle()) {
        currentBLIPSSOISDTypeUnitNode();
    } else if(currentText == BLIPSSOIIUTypeUnitNode::instance().getStringTitle()) {
        currentBLIPSSOIIUTypeUnitNode();
    } else if(currentText == KLTypeUnitNode::instance().getStringTitle()) {
        currentKLTypeUnitNode();
    } else if(currentText == TGTypeUnitNode::instance().getStringTitle()) {
        currentTGTypeUnitNode();
    } else if(currentText == RLMKRLTypeUnitNode::instance().getStringTitle()) {
        currentRLMKRLTypeUnitNode();
    } else if(currentText == RLMCTypeUnitNode::instance().getStringTitle()) {
        currentRLMCTypeUnitNode();
    } else if(currentText == BODT4KMTypeUnitNode::instance().getStringTitle()) {
        currentBODT4KMTypeUnitNode();
    } else if(currentText == Y4T4KMTypeUnitNode::instance().getStringTitle()) {
        currentY4T4KMTypeUnitNode();
    } else if(currentText == DDT4KMTypeUnitNode::instance().getStringTitle()) {
        currentDDT4KMTypeUnitNode();
    } else if(currentText == BODSOTATypeUnitNode::instance().getStringTitle()) {
        currentBODSOTATypeUnitNode();
    } else if(currentText == Y4SOTATypeUnitNode::instance().getStringTitle()) {
        currentY4SOTATypeUnitNode();
    } else if(currentText == DDSOTATypeUnitNode::instance().getStringTitle()) {
        currentDDSOTATypeUnitNode();
    } else if(currentText == SSOISDTypeUnitNode::instance().getStringTitle()) {
        currentSSOISDTypeUnitNode();
    } else if(currentText == SSOIIUTypeUnitNode::instance().getStringTitle()) {
        currentSSOIIUTypeUnitNode();
    } else if(currentText == ADAMTypeUnitNode::instance().getStringTitle()) {
        currentADAMTypeUnitNode();
    } else if(currentText == TorosTypeUnitNode::instance().getStringTitle()) {
        currentTorosTypeUnitNode();
    } else {
        currentDefaultTypeUnitNode();
    }

    setBlockSignal(oldBlock);
    pushButton_UpdSelections_clicked();
}

void MainWindowDB::comboBox_TypeSearch_currentIndexChanged(int index)
{
    const auto&  oldBlock = getBlockSignal();
    setBlockSignal(true);

    switch (index) {
    case 0:{

        ui->label_2->setVisible(false);
        ui->label_3->setVisible(false);
        ui->label_cmbTypeUN->setVisible(false);
        ui->label_cmbTypeEvent->setVisible(false);
        ui->label_cmbTypeOutUN->setVisible(false);
        ui->label_cmbIPAddress->setVisible(false);
        ui->label_cmbNum1->setVisible(false);
        ui->label_cmbNum2->setVisible(false);
        ui->label_cmbNum3->setVisible(false);
        ui->label_cmbAdamOff->setVisible(false);

        ui->dateEdit_From->setVisible(false);
        ui->dateEdit_To->setVisible(false);

        ui->comboBox_TypeUN->setVisible(false);
        ui->comboBox_TypeEvent->setVisible(false);
        ui->comboBox_Num1->setVisible(false);
        ui->comboBox_Num2->setVisible(false);
        ui->comboBox_Num3->setVisible(false);
        ui->comboBox_TypeOutUN->setVisible(false);
        ui->comboBox_IPAddress->setVisible(false);
        ui->comboBox_AdamOff->setVisible(false);

        break;
    }
    case 1:{

        ui->label_2->setVisible(true);
        ui->label_3->setVisible(true);
        ui->label_cmbTypeUN->setVisible(true);
        ui->label_cmbTypeEvent->setVisible(true);
        ui->label_cmbNum1->setVisible(true);
        ui->label_cmbNum2->setVisible(true);
        ui->label_cmbNum3->setVisible(true);
        ui->label_cmbIPAddress->setVisible(true);


        ui->dateEdit_From->setDate(QDate::currentDate());
        ui->dateEdit_From->setVisible(true);
        ui->dateEdit_To->setDate(QDate::currentDate());
        ui->dateEdit_To->setVisible(true);

        ui->comboBox_TypeUN->setVisible(true);
        ui->comboBox_Num1->setVisible(true);
        ui->comboBox_Num2->setVisible(true);
        ui->comboBox_Num3->setVisible(true);
        ui->comboBox_TypeEvent->setVisible(true);
        ui->comboBox_IPAddress->setVisible(true);

        ui->comboBox_TypeUN->setCurrentIndex(0);
        ui->comboBox_TypeEvent->setCurrentIndex(0);

        comboBox_TypeUN_currentIndexChanged(ui->comboBox_TypeUN->currentIndex());
        break;
    }
    default:
        break;
    }

    setBlockSignal(oldBlock);

    pushButton_UpdSelections_clicked();
}

QString MainWindowDB::createEventFilter() {
    if(!ui->comboBox_TypeEvent->isVisible())
        return "";
    if("Все" == ui->comboBox_TypeEvent->currentText())
        return "";
    return DataBaseManager::eventFlt((JourEntity::TypeEvent)ui->comboBox_TypeEvent->currentData().toInt(),
                                     (JourEntity::TypeObject)ui->comboBox_TypeUN->currentData().toInt());
}

QString MainWindowDB::createDirectionFilter()
{
    if(!ui->comboBox_IPAddress->isVisible())
        return "";
    if("Все" == ui->comboBox_IPAddress->currentText())
        return "";
    return DataBaseManager::directionFlt(ui->comboBox_IPAddress->currentText());
}

QString MainWindowDB::createObjectFilter() {
    if(!ui->comboBox_TypeUN->isVisible())
        return "";
    if("Все" == ui->comboBox_TypeUN->currentText())
        return "";
    return "("
            + DataBaseManager::objectFlt((JourEntity::TypeObject)ui->comboBox_TypeUN->currentData().toInt()/*,
                                      ui->comboBox_6->currentIndex(),
                                      ui->comboBox_7->currentIndex(),
                                      ui->comboBox_8->currentIndex()*/)
            + ((BLIPUZMonolitTypeUnitNode::instance().getStringTitle() == ui->comboBox_TypeUN->currentText()) ? " AND ((params ->> 'Bazalt')::integer = 1) " : "")
            + ")";
}

QString MainWindowDB::createNum1Filter() {
    if(!ui->comboBox_Num1->isVisible())
        return "";
    if("Все" == ui->comboBox_Num1->currentText())
        return "";
    return DataBaseManager::num1Flt(ui->comboBox_Num1->currentText());
}

QString MainWindowDB::createNum2Filter() {
    if(!ui->comboBox_Num2->isVisible())
        return "";
    if("Все" == ui->comboBox_Num2->currentText())
        return "";
    return DataBaseManager::num2Flt(ui->comboBox_Num2->currentText());
}

QString MainWindowDB::createNum3Filter() {
    if(!ui->comboBox_Num3->isVisible())
        return "";
    if("Все" == ui->comboBox_Num3->currentText())
        return "";
    return DataBaseManager::num3Flt(ui->comboBox_Num3->currentText());
}

QString MainWindowDB::createOutFilter() {
    if(!ui->comboBox_TypeOutUN->isVisible())
        return "";
    if("Все" == ui->comboBox_TypeOutUN->currentText())
        return "";
    return DataBaseManager::outFlt(ui->comboBox_TypeOutUN->currentData().toInt());
}

QString MainWindowDB::createAdamOffFilter() {
    if(!ui->comboBox_AdamOff->isVisible())
        return "";
    if("Все" == ui->comboBox_AdamOff->currentText() || -1 == ui->comboBox_AdamOff->currentData().toInt())
        return "";
    return DataBaseManager::adamOff(ui->comboBox_AdamOff->currentData().toInt());
}

QString MainWindowDB::createDateFilter() {
    if(!ui->dateEdit_From->isVisible() || !ui->dateEdit_To->isVisible())
        return "";
    return DataBaseManager::dateFlt(ui->dateEdit_From->date(), ui->dateEdit_To->date());
}

QString MainWindowDB::createCompositFilter() {
    QString sqlFlt = "SELECT * FROM public.jour ";

    if(0 == ui->comboBox_TypeSearch->currentIndex()) {
        sqlFlt += " WHERE type = 902 ORDER BY id ";
        return sqlFlt;
    }

    QString sqlDateFlt = createDateFilter();
    QString sqlObjectFlt = createObjectFilter();
    QString sqlEventFlt = createEventFilter();
    QString sqlDirectionFlt = createDirectionFilter();
    QString sqlNum1Flt = createNum1Filter();
    QString sqlNum2Flt = createNum2Filter();
    QString sqlNum3Flt = createNum3Filter();
    QString sqlOutFlt = createOutFilter();
    QString sqlAdamOffFlt = createAdamOffFilter();

    if(!sqlDateFlt.isEmpty()
    || !sqlObjectFlt.isEmpty()
    || !sqlEventFlt.isEmpty()
    || !sqlNum1Flt.isEmpty()
    || !sqlNum2Flt.isEmpty()
    || !sqlNum3Flt.isEmpty()
    || !sqlOutFlt.isEmpty()
    || !sqlAdamOffFlt.isEmpty()) {
        sqlFlt += " WHERE ";

        QString sqlDopFlt;

        if(!sqlDopFlt.isEmpty() && !sqlDateFlt.isEmpty())
            sqlDopFlt += " AND ";
        sqlDopFlt += sqlDateFlt;

        if(!sqlDopFlt.isEmpty() && !sqlObjectFlt.isEmpty())
            sqlDopFlt += " AND ";
        sqlDopFlt += sqlObjectFlt;

        if(!sqlDopFlt.isEmpty() && !sqlEventFlt.isEmpty())
            sqlDopFlt += " AND ";
        sqlDopFlt += sqlEventFlt;

        if(!sqlDopFlt.isEmpty() && !sqlDirectionFlt.isEmpty())
            sqlDopFlt += " AND ";
        sqlDopFlt += sqlDirectionFlt;

        if(!sqlDopFlt.isEmpty() && !sqlNum1Flt.isEmpty())
            sqlDopFlt += " AND ";
        sqlDopFlt += sqlNum1Flt;

        if(!sqlDopFlt.isEmpty() && !sqlNum2Flt.isEmpty())
            sqlDopFlt += " AND ";
        sqlDopFlt += sqlNum2Flt;

        if(!sqlDopFlt.isEmpty() && !sqlNum3Flt.isEmpty())
            sqlDopFlt += " AND ";
        sqlDopFlt += sqlNum3Flt;

        if(!sqlDopFlt.isEmpty() && !sqlOutFlt.isEmpty())
            sqlDopFlt += " AND ";
        sqlDopFlt += sqlOutFlt;

        if(!sqlDopFlt.isEmpty() && !sqlAdamOffFlt.isEmpty())
            sqlDopFlt += " AND ";
        sqlDopFlt += sqlAdamOffFlt;

        sqlFlt += sqlDopFlt;
    } else {
        sqlFlt += " WHERE type = 902 ORDER BY id ";
        return sqlFlt;
    }

    if(!sqlFlt.isEmpty())
        sqlFlt += " ORDER BY id ";

    return sqlFlt;
}

void MainWindowDB::on_pushButton_3_clicked()
{
    TablePrint::prepareTmpFileHtmlTableFromModel(ui->tableView);
    TablePrint::print();
}

void MainWindowDB::on_pushButton_2_clicked()
{
    TablePrint::prepareTmpFileHtmlTableFromModel(ui->tableView);
    TablePrint tp;
    tp.printPreview();
}

void MainWindowDB::updateListRecords()
{
    if(getBlockSignal())
        return;
    //qDebug() << getCurrentSqlQueryStr();
    modelJour->castomUpdateListRecords(getCurrentSqlQueryStr());

    if(!modelJour->getListJour().isEmpty()) {
        ui->tableView->resizeColumnToContents(0);
        ui->tableView->resizeColumnToContents(1);
        ui->tableView->resizeColumnToContents(2);
        ui->tableView->resizeColumnToContents(3);
        ui->tableView->resizeColumnToContents(4);
        ui->tableView->resizeColumnToContents(5);
        ui->tableView->resizeColumnToContents(6);

    }

    ui->tableView->update();
}

void MainWindowDB::pushButton_UpdSelections_clicked()
{
    if(getBlockSignal())
        return;
    setCurrentSqlQueryStr(createCompositFilter());
    this->updateListRecords();
}

bool MainWindowDB::getBlockSignal() const
{
    return blockSignal;
}

void MainWindowDB::setBlockSignal(bool value)
{
    blockSignal = value;
}

void MainWindowDB::updComboBoxReason() {
    updComboBox(DataBaseManager::getReasonGroup(), ui->comboBoxReason);
}

void MainWindowDB::updComboBoxTakenMeasures() {
    updComboBox(DataBaseManager::getMeasuresGroup(), ui->comboBoxTakenMeasures);
}

void MainWindowDB::updComboBoxAddress()
{
    updComboBox(DataBaseManager::getDirectionGroup(), ui->comboBox_IPAddress);
    ui->comboBox_IPAddress->insertItem(0, "Все", -1);
    ui->comboBox_IPAddress->setCurrentIndex(0);
}

void MainWindowDB::updComboBoxNum1()
{
    updComboBox(DataBaseManager::getD1Group(), ui->comboBox_Num1);
    ui->comboBox_Num1->insertItem(0, "Все", -1);
    ui->comboBox_Num1->setCurrentIndex(0);
}
void MainWindowDB::updComboBoxNum2()
{
    updComboBox(DataBaseManager::getD2Group(), ui->comboBox_Num2);
    ui->comboBox_Num2->insertItem(0, "Все", -1);
    ui->comboBox_Num2->setCurrentIndex(0);
}
void MainWindowDB::updComboBoxNum3()
{
    updComboBox(DataBaseManager::getD3Group(), ui->comboBox_Num3);
    ui->comboBox_Num3->insertItem(0, "Все", -1);
    ui->comboBox_Num3->setCurrentIndex(0);
}

void MainWindowDB::updComboBox(QList<QString> lst, QComboBox * cmb) {
    cmb->clear();
    for(const auto&  itemData : lst) {
        cmb->addItem(itemData, itemData);
    }
    cmb->setCurrentIndex(-1);
}

void MainWindowDB::on_toolButtonAddReason_clicked()
{
    if(0 == selMsg.getId()) {
        return;
    }

    selMsg.setReason(ui->comboBoxReason->currentText());
    DataBaseManager::updateJourMsg_wS(selMsg);
    updComboBoxReason();
}

void MainWindowDB::on_toolButtonAddTakenMeasures_clicked()
{
    if(0 == selMsg.getId()) {
        return;
    }

    selMsg.setMeasures(ui->comboBoxTakenMeasures->currentText());
    DataBaseManager::updateJourMsg_wS(selMsg);
    updComboBoxTakenMeasures();
}

void MainWindowDB::on_tableView_clicked(const QModelIndex &index)
{
    JourEntity sel = this->modelJour->clickedMsg(index);

    if(0 == sel.getId()) {
        ui->comboBoxReason->setCurrentIndex(-1);
        ui->comboBoxTakenMeasures->setCurrentIndex(-1);
        return;
    }

    selMsg = sel;

    if(sel.getReason().isEmpty() ) {
        ui->comboBoxReason->setCurrentIndex(-1);
    } else {
        ui->comboBoxReason->setEditText(sel.getReason());
    }

    if(sel.getMeasures().isEmpty()) {
        ui->comboBoxTakenMeasures->setCurrentIndex(-1);
    } else {
        ui->comboBoxTakenMeasures->setEditText(sel.getMeasures());
    }

     GraphTerminal::sendAbonentEventBook(selMsg);
}

void MainWindowDB::on_toolButtonRemoveReason_clicked()
{
    if(0 == selMsg.getId()) {
        return;
    }

    selMsg.setReason("");
    DataBaseManager::updateJourMsg_wS(selMsg);
    updComboBoxReason();
}

void MainWindowDB::on_toolButtonRemoveTakenMeasures_clicked()
{
    if(0 == selMsg.getId()) {
        return;
    }

    selMsg.setMeasures("");
    DataBaseManager::updateJourMsg_wS(selMsg);
    updComboBoxTakenMeasures();
}

void MainWindowDB::on_action_triggered()
{
    this->close();
}

void MainWindowDB::on_pushButton_4_clicked()
{
    TablePrint::prepareTmpFileHtmlTableFromModel(ui->tableView);
    TablePrint::printPdf();
}

void MainWindowDB::on_tableView_doubleClicked(const QModelIndex &index)
{
    JourEntity sel = this->modelJour->clickedMsg(index);

    if(0 == sel.getId()) {
        return;
    }

    selMsg = sel;

    if(0 != ui->comboBox_TypeSearch->currentIndex() || 902 != selMsg.getType())
        return;

    const auto& oldBlockb = getBlockSignal();
    setBlockSignal(true);

    QString sqlFlt = "SELECT * FROM public.jour WHERE id >= %1";

    sqlFlt = sqlFlt.arg(selMsg.getId());

    QList<JourEntity> tmpLs = modelJour->getListJour();
    if(selMsg.getId() != tmpLs.last().getId()) {
        int indexCurrentMsg = -1;
        for(int i = 0, n = tmpLs.size(); i < n; i++) {
            if(selMsg.getId() == tmpLs.at(i).getId()) {
                indexCurrentMsg = i;
                break;
            }
        }
        if(-1 == indexCurrentMsg)
            return;
        JourEntity nextMsg = tmpLs.at(indexCurrentMsg + 1);
        if(0 != nextMsg.getId() && 902 == nextMsg.getType()) {
            sqlFlt += " AND id < %1 ";
            sqlFlt = sqlFlt.arg(nextMsg.getId());
        } else {
            ui->comboBox_TypeSearch->setCurrentIndex(0);
            sqlFlt = " SELECT * FROM public.jour WHERE type = 902 ";
        }
    }

    sqlFlt += " ORDER BY id ";

    setCurrentSqlQueryStr(sqlFlt);

    setBlockSignal(oldBlockb);

    this->updateListRecords();
}

QString MainWindowDB::getCurrentSqlQueryStr() const
{
    return currentSqlQueryStr;
}

void MainWindowDB::updSqlQueryStr(QString sql)
{
    const auto&  oldBlock = getBlockSignal();
    setBlockSignal(true);

    setCurrentSqlQueryStr(sql);

    setBlockSignal(oldBlock);

    this->updateListRecords();
}

void MainWindowDB::setCurrentSqlQueryStr(const QString &value)
{
    currentSqlQueryStr = value;
}

QSharedPointer<GraphTerminal> MainWindowDB::loadPortsTcpGraphTerminal(QString fileName) {

    QSettings settings(fileName, QSettings::IniFormat);
#if (defined (_WIN32) || defined (_WIN64))
    settings.setIniCodec( "Windows-1251" );
#else
    settings.setIniCodec( "UTF-8" );
#endif

    settings.beginGroup("INTEGRATION");
    int nPort = settings.value( "Port", -1 ).toInt();
    settings.endGroup();

    if(-1 != nPort)
        return QSharedPointer<GraphTerminal>::create(nPort);

    return QSharedPointer<GraphTerminal>();
}

void MainWindowDB::comboBox_IPAddress_editTextChanged(const QString &/*arg1*/)
{
    const auto&  oldBlock = getBlockSignal();
    setBlockSignal(true);

    setBlockSignal(oldBlock);
    pushButton_UpdSelections_clicked();
}
