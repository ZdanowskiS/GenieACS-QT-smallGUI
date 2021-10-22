#include "cpewindow.h"
#include "ui_cpewindow.h"

#include "cpeigd.h"
#include "cpeac8.h"

Cpewindow::Cpewindow(rest *acs_rest, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Cpewindow)
{
    ui->setupUi(this);
    this->mrest=acs_rest;
    this->deviceID=this->mrest->selected;

    QString task= "devices/"+this->deviceID+"/tasks?timeout=3000&connection_request";

    std::string data="{\"name\":\"refreshObject\",\"objectName\":\"InternetGatewayDevice\"}";

    this->mrest->PostData(task, data);

    task="devices/?query=%7B%22_id%22%3A%22"+this->deviceID+"%22%7D";
    QString cpe=this->mrest->GetData(task);

    QJsonParseError jsonError;
    QJsonDocument doc = QJsonDocument::fromJson(cpe.toUtf8(),&jsonError);

    if(doc.isArray()){
        for(const auto& item : doc.array()){
            ui->lineEdit_id->setText(item.toObject().value("_id").toString());
            ui->lineEdit_productclass->setText(item.toObject().value("_deviceId").toObject().value("_ProductClass").toString());
            ui->lineEdit_serial->setText(item.toObject().value("_deviceId").toObject().value("_SerialNumber").toString());
            ui->lineEdit_softversion->setText(item.toObject().value("InternetGatewayDevice").toObject().value("DeviceInfo").toObject().value("SoftwareVersion").toObject().value("_value").toString());

            if(this->setPointer(item.toObject().value("_deviceId").toObject().value("_ProductClass").toString()))
            {
                this->displayCPE(item.toObject());
            }
        }
    }
}

Cpewindow::~Cpewindow()
{
    delete ui;
}

bool Cpewindow::setPointer(QString productclass){
    if(productclass=="IGD")
    {
        this->windowCPE= new CpeIGD();
        return true;
    }
    else if(productclass=="AC8")
    {
        this->windowCPE= new CpeAC8();
        return true;
    }
    return false;
}

void Cpewindow::sendReboot()
{
    QString task="devices/"+this->deviceID+"/tasks?connection_request";
    std::string data = "{\"name\":\"Reboot\"}";

    this->mrest->PostData(task, data);
}

void Cpewindow::sendFactoryReset()
{
    QString task="devices/"+this->deviceID+"/tasks?connection_request";
    std::string data = "{\"name\":\"factoryReset\"}";

    this->mrest->PostData(task, data);
}

void Cpewindow::sendSSID24()
{
    QString task="devices/"+this->deviceID+"/tasks?connection_request";
    std::string data = "{\"name\":\"setParameterValues\", \"parameterValues\": [[\""+this->windowCPE->getNodeSSID24().toStdString()+"\", \""+this->ssid24Line->text().toStdString()+"\", \"xsd:string\"]]}";

    this->mrest->PostData(task, data);
}

void Cpewindow::sendSSID24Pass()
{
    QString task="devices/"+this->deviceID+"/tasks?connection_request";
    std::string data = "{\"name\":\"setParameterValues\", \"parameterValues\": [[\""+this->windowCPE->getNodeSSID24Pass().toStdString()+"\", \""+this->ssid24PassLine->text().toStdString()+"\", \"xsd:string\"]]}";

    this->mrest->PostData(task, data);
}

void Cpewindow::sendSSID5()
{
    QString task="devices/"+this->deviceID+"/tasks?connection_request";
    std::string data = "{\"name\":\"setParameterValues\", \"parameterValues\": [[\""+this->windowCPE->getNodeSSID5().toStdString()+"\", \""+this->ssid5Line->text().toStdString()+"\", \"xsd:string\"]]}";

    this->mrest->PostData(task, data);
}

void Cpewindow::sendSSID5Pas()
{
    QString task="devices/"+this->deviceID+"/tasks?connection_request";
    std::string data = "{\"name\":\"setParameterValues\", \"parameterValues\": [[\""+this->windowCPE->getNodeSSID5Pass().toStdString()+"\", \""+this->ssid5PasLine->text().toStdString()+"\", \"xsd:string\"]]}";

    this->mrest->PostData(task, data);
}

void Cpewindow::sendPPPPoELogin()
{
    QString task="devices/"+this->deviceID+"/tasks?connection_request";
    std::string data = "{\"name\":\"setParameterValues\", \"parameterValues\": [[\""+this->windowCPE->getNodePPPoELogin().toStdString()+"\", \""+this->pppoeLoginLine->text().toStdString()+"\", \"xsd:string\"]]}";

    this->mrest->PostData(task, data);
}

void Cpewindow::sendPPPPoePas()
{
    QString task="devices/"+this->deviceID+"/tasks?connection_request";
    std::string data = "{\"name\":\"setParameterValues\", \"parameterValues\": [[\""+this->windowCPE->getNodePPPoEPass().toStdString()+"\", \""+this->pppoePLine->text().toStdString()+"\", \"xsd:string\"]]}";

    this->mrest->PostData(task, data);
}

void Cpewindow::sendPPPoEYesEnable(bool checked)
{
    std::string setting="false";
    if(checked){
        setting="true";
    }
    QString task="devices/"+this->deviceID+"/tasks?connection_request";
    std::string data = "{\"name\":\"setParameterValues\", \"parameterValues\": [[\""+this->windowCPE->getNodePPPoEEnable().toStdString()+"\", \""+setting+"\", \"xsd:string\"]]}";

    this->mrest->PostData(task, data);
}
void Cpewindow::displayCPE(QJsonObject item)
{
    const short int labelWidth = 85;
    QWidget* techAreaV = new QWidget;
    techAreaV->setLayout(new QVBoxLayout(techAreaV));
    /**/
    if(this->windowCPE->getNodeReboot()!="")
    {
        QLabel *rebootLabel = new QLabel();
        rebootLabel->setText("Reboot");
        rebootLabel->setMinimumWidth(labelWidth);

        QLineEdit *rebootLine = new QLineEdit();
        rebootLine->setText(this->windowCPE->getReboot(item));
        rebootLine->setMinimumWidth(100);
        rebootLine->setDisabled(true);

        QPushButton *rebootButton = new QPushButton();
        rebootButton->setText("Reboot");

        connect(rebootButton, SIGNAL(clicked()),this, SLOT(sendReboot()));

        QWidget* rebootArea = new QWidget;
        rebootArea->setLayout(new QHBoxLayout(rebootArea));

        rebootArea->layout()->setMargin(0);
        rebootArea->layout()->setSpacing(0);

        rebootArea->layout()->addWidget(rebootLabel);
        rebootArea->layout()->addWidget(rebootLine);
        rebootArea->layout()->addWidget(rebootButton);

        techAreaV->layout()->addWidget(rebootArea);
    }
    if(this->windowCPE->getNodeFactoryReset()!="")
    {
        QLabel *factoryResetLabel = new QLabel();
        factoryResetLabel->setText("Reset");
        factoryResetLabel->setMinimumWidth(labelWidth);

        QLineEdit *factoryResetLine = new QLineEdit();
        factoryResetLine->setText(this->windowCPE->getFactoryReset(item));
        factoryResetLine->setMinimumWidth(100);
        factoryResetLine->setDisabled(true);

        QPushButton *factoryResetButton = new QPushButton();
        factoryResetButton->setText("Reset");

        connect(factoryResetButton, SIGNAL(clicked()),this, SLOT(sendFactoryReset()));

        QWidget* factoryResetArea = new QWidget;
        factoryResetArea->setLayout(new QHBoxLayout(factoryResetArea));

        factoryResetArea->layout()->setMargin(0);
        factoryResetArea->layout()->setSpacing(0);

        factoryResetArea->layout()->addWidget(factoryResetLabel);
        factoryResetArea->layout()->addWidget(factoryResetLine);
        factoryResetArea->layout()->addWidget(factoryResetButton);

        techAreaV->layout()->addWidget(factoryResetArea);
    }
    if(this->windowCPE->getNodeSSID24()!="")
    {
        QLabel *ssid24Label = new QLabel();
        ssid24Label->setText("SSID 2.4GHz");
        ssid24Label->setMinimumWidth(labelWidth);

        this->ssid24Line->setText(this->windowCPE->getSSID24(item));

        //ssid24Line->setMinimumWidth(100);

        QPushButton *ssid24Button = new QPushButton();
        ssid24Button->setText("Save");

        connect(ssid24Button, SIGNAL(clicked()),this, SLOT(sendSSID24()));

        QWidget* ssid24Area = new QWidget;
        ssid24Area->setLayout(new QHBoxLayout(ssid24Area));

        ssid24Area->layout()->setMargin(0);
        ssid24Area->layout()->setSpacing(0);

        ssid24Area->layout()->addWidget(ssid24Label);
        ssid24Area->layout()->addWidget(this->ssid24Line);
        ssid24Area->layout()->addWidget(ssid24Button);

        techAreaV->layout()->addWidget(ssid24Area);
    }
    /**/
    if(this->windowCPE->getNodeSSID24Pass()!="")
    {
        QLabel *ssid24PassLabel = new QLabel();
        ssid24PassLabel->setText("2.4GHz Pass");
        ssid24PassLabel->setMinimumWidth(labelWidth);

        this->ssid24PassLine->setText(this->windowCPE->getSSID24Pass(item));
        QPushButton *ssid24PassButton = new QPushButton();
        ssid24PassButton->setText("Save");
        connect(ssid24PassButton, SIGNAL(clicked()),this, SLOT(sendSSID24Pass()));

        QWidget* ssid24PassArea = new QWidget;
        ssid24PassArea->setLayout(new QHBoxLayout(ssid24PassArea));

        ssid24PassArea->layout()->setMargin(0);
        ssid24PassArea->layout()->setSpacing(0);

        ssid24PassArea->layout()->addWidget(ssid24PassLabel);
        ssid24PassArea->layout()->addWidget(this->ssid24PassLine);
        ssid24PassArea->layout()->addWidget(ssid24PassButton);

        techAreaV->layout()->addWidget(ssid24PassArea);
    }
    /**/
    if(this->windowCPE->getNodeSSID5()!="")
    {
        QLabel *ssid5Label = new QLabel();
        ssid5Label->setText("SSID 5GHz");
        ssid5Label->setMinimumWidth(labelWidth);

        this->ssid5Line->setText(this->windowCPE->getSSID5(item));
        QPushButton *ssid5Button = new QPushButton();
        ssid5Button->setText("Save");
        connect(ssid5Button, SIGNAL(clicked()),this, SLOT(sendSSID5()));

        QWidget* ssid5Area = new QWidget;
        ssid5Area->setLayout(new QHBoxLayout(ssid5Area));

        ssid5Area->layout()->setMargin(0);
        ssid5Area->layout()->setSpacing(0);
        ssid5Area->layout()->addWidget(ssid5Label);
        ssid5Area->layout()->addWidget(this->ssid5Line);
        ssid5Area->layout()->addWidget(ssid5Button);

        techAreaV->layout()->addWidget(ssid5Area);
    }
    /**/
    if(this->windowCPE->getNodeSSID5Pass()!="")
    {
        QLabel *ssid5PasLabel = new QLabel();
        ssid5PasLabel->setText("5 GHz Pass");
        ssid5PasLabel->setMinimumWidth(labelWidth);

        this->ssid5PasLine->setText(this->windowCPE->getSSID5Pass(item));
        QPushButton *ssid5PasButton = new QPushButton();
        ssid5PasButton->setText("Save");
        connect(ssid5PasButton, SIGNAL(clicked()),this, SLOT(sendSSID5Pas()));

        QWidget* ssid5PasArea = new QWidget;
        ssid5PasArea->setLayout(new QHBoxLayout(ssid5PasArea));

        ssid5PasArea->layout()->setMargin(0);
        ssid5PasArea->layout()->setSpacing(0);

        ssid5PasArea->layout()->addWidget(ssid5PasLabel);
        ssid5PasArea->layout()->addWidget(this->ssid5PasLine);
        ssid5PasArea->layout()->addWidget(ssid5PasButton);
        techAreaV->layout()->addWidget(ssid5PasArea);
    }
    /**/
    if(this->windowCPE->getNodePPPoELogin()!="")
    {
        QLabel *pppoeLoginLabel = new QLabel();
        pppoeLoginLabel->setText("PPPoE Login");
        pppoeLoginLabel->setMinimumWidth(labelWidth);

        this->pppoeLoginLine->setText(this->windowCPE->getPPPoELogin(item));
        QPushButton *pppoeLoginButton = new QPushButton();
        pppoeLoginButton->setText("Save");
        connect(pppoeLoginButton, SIGNAL(clicked()),this, SLOT(sendPPPPoELogin()));

        QWidget* pppoeLoginArea = new QWidget;
        pppoeLoginArea->setLayout(new QHBoxLayout(pppoeLoginArea));

        pppoeLoginArea->layout()->setMargin(0);
        pppoeLoginArea->layout()->setSpacing(0);

        pppoeLoginArea->layout()->addWidget(pppoeLoginLabel);
        pppoeLoginArea->layout()->addWidget(this->pppoeLoginLine);
        pppoeLoginArea->layout()->addWidget(pppoeLoginButton);

        techAreaV->layout()->addWidget(pppoeLoginArea);
    }
    /**/
    if(this->windowCPE->getNodePPPoELogin()!="")
    {
        QLabel *pppoePLabel = new QLabel();
        pppoePLabel->setText("PPPoE Pass");
        pppoePLabel->setMinimumWidth(labelWidth);

        this->pppoePLine->setText(this->windowCPE->getPPPoEPass(item));
        QPushButton *pppoePButton = new QPushButton();
        pppoePButton->setText("Save");
        connect(pppoePButton, SIGNAL(clicked()),this, SLOT(sendPPPPoePas()));

        QWidget* pppoeArea = new QWidget;
        pppoeArea->setLayout(new QHBoxLayout(pppoeArea));

        pppoeArea->layout()->setMargin(0);
        pppoeArea->layout()->setSpacing(0);

        pppoeArea->layout()->addWidget(pppoePLabel);
        pppoeArea->layout()->addWidget(this->pppoePLine);
        pppoeArea->layout()->addWidget(pppoePButton);

        techAreaV->layout()->addWidget(pppoeArea);
    }
    if(this->windowCPE->getNodePPPoEEnable()!="")
    {
        QLabel *pppoeEnableLabel = new QLabel();
        pppoeEnableLabel->setText("PPPoE Enable");
        pppoeEnableLabel->setMinimumWidth(labelWidth);
        QRadioButton *pppoeYesEnable = new QRadioButton();
        pppoeYesEnable->setText("Yes");
        connect(pppoeYesEnable, SIGNAL(toggled(bool)),this, SLOT(sendPPPoEYesEnable(bool)));
        QRadioButton *pppoeNoEnable = new QRadioButton();
        pppoeNoEnable->setText("No");

        if(this->windowCPE->getNodePPPoEEnable()=='true')
        {
            pppoeYesEnable->setChecked(true);
            pppoeNoEnable->setChecked(false);
        }
        else{
            pppoeYesEnable->setChecked(false);
            pppoeNoEnable->setChecked(true);
        }
        QWidget* pppoeEnableArea = new QWidget;
        pppoeEnableArea->setLayout(new QHBoxLayout(pppoeEnableArea));

        pppoeEnableArea->layout()->setMargin(0);
        pppoeEnableArea->layout()->setSpacing(0);

        pppoeEnableArea->layout()->addWidget(pppoeEnableLabel);
        pppoeEnableArea->layout()->addWidget(pppoeYesEnable);
        pppoeEnableArea->layout()->addWidget(pppoeNoEnable);

        techAreaV->layout()->addWidget(pppoeEnableArea);
    }
    /**/

    ui->scrollArea->setWidget(techAreaV);
}
