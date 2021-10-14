#include "cpewindow.h"
#include "ui_cpewindow.h"

Cpewindow::Cpewindow(rest *acs_rest, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Cpewindow)
{
    ui->setupUi(this);
    this->mrest=acs_rest;

    QString task= "devices/"+this->mrest->selected+"/tasks?timeout=3000&connection_request";

    std::string data="{\"name\":\"refreshObject\",\"objectName\":\"InternetGatewayDevice\"}";

    this->mrest->PostData(task, data);

    task="devices/?query=%7B%22_id%22%3A%22"+this->mrest->selected+"%22%7D";
    QString cpe=this->mrest->GetData(task);

    QJsonParseError jsonError;
    QJsonDocument doc = QJsonDocument::fromJson(cpe.toUtf8(),&jsonError);

    if(doc.isArray()){
        for(const auto& item : doc.array()){
            ui->lineEdit_id->setText(item.toObject().value("_id").toString());
            ui->lineEdit_productclass->setText(item.toObject().value("_deviceId").toObject().value("_ProductClass").toString());
            ui->lineEdit_serial->setText(item.toObject().value("_deviceId").toObject().value("_SerialNumber").toString());
            ui->lineEdit_softversion->setText(item.toObject().value("InternetGatewayDevice").toObject().value("DeviceInfo").toObject().value("SoftwareVersion").toObject().value("_value").toString());

            if(item.toObject().value("_deviceId").toObject().value("_ProductClass").toString()=="IGD"){
                this->displayIGD(item.toObject());
            }
        }
    }
}

Cpewindow::~Cpewindow()
{
    delete ui;
}

void Cpewindow::sendSSID()
{
    QString task="devices/"+this->mrest->selected+"/tasks?connection_request";
    std::string data = "{\"name\":\"setParameterValues\", \"parameterValues\": [[\"InternetGatewayDevice.LANDevice.1.WLANConfiguration.1.SSID\", \""+this->ssidLine->text().toStdString()+"\", \"xsd:string\"]]}";

    this->mrest->PostData(task, data);
}

void Cpewindow::sendSSIDPas()
{
    QString task="devices/"+this->mrest->selected+"/tasks?connection_request";
    std::string data = "{\"name\":\"setParameterValues\", \"parameterValues\": [[\"InternetGatewayDevice.LANDevice.1.WLANConfiguration.1.X_TP_PreSharedKey\", \""+this->ssidPasLine->text().toStdString()+"\", \"xsd:string\"]]}";

    this->mrest->PostData(task, data);
}

void Cpewindow::sendSSIDB()
{
    QString task="devices/"+this->mrest->selected+"/tasks?connection_request";
    std::string data = "{\"name\":\"setParameterValues\", \"parameterValues\": [[\"InternetGatewayDevice.LANDevice.1.WLANConfiguration.2.SSID\", \""+this->ssidBLine->text().toStdString()+"\", \"xsd:string\"]]}";

    this->mrest->PostData(task, data);
}

void Cpewindow::sendSSIDBPas()
{
    QString task="devices/"+this->mrest->selected+"/tasks?connection_request";
    std::string data = "{\"name\":\"setParameterValues\", \"parameterValues\": [[\"InternetGatewayDevice.LANDevice.1.WLANConfiguration.2.X_TP_PreSharedKey\", \""+this->ssidBPasLine->text().toStdString()+"\", \"xsd:string\"]]}";

    this->mrest->PostData(task, data);
}

void Cpewindow::sendPPPPoeL()
{
    QString task="devices/"+this->mrest->selected+"/tasks?connection_request";
    std::string data = "{\"name\":\"setParameterValues\", \"parameterValues\": [[\"InternetGatewayDevice.WANDevice.1.WANConnectionDevice.1.WANPPPConnection.1.Username\", \""+this->pppoeLLine->text().toStdString()+"\", \"xsd:string\"]]}";

    this->mrest->PostData(task, data);
}

void Cpewindow::sendPPPPoePas()
{
    QString task="devices/"+this->mrest->selected+"/tasks?connection_request";
    std::string data = "{\"name\":\"setParameterValues\", \"parameterValues\": [[\"InternetGatewayDevice.WANDevice.1.WANConnectionDevice.1.WANPPPConnection.1.Password\", \""+this->pppoePLine->text().toStdString()+"\", \"xsd:string\"]]}";

    this->mrest->PostData(task, data);
}

void Cpewindow::displayIGD(QJsonObject item)
{
    const short int labelWidth = 70;
    /**/
    QLabel *ssidLabel = new QLabel();
    ssidLabel->setText("SSID 1");
    ssidLabel->setMinimumWidth(labelWidth);

    this->ssidLine->setText(item.value("InternetGatewayDevice").toObject().value("LANDevice").toObject().value("1").toObject().value("WLANConfiguration").toObject().value("1").toObject().value("SSID").toObject().value("_value").toString());
    ssidLine->setMinimumWidth(100);

    QPushButton *ssidButton = new QPushButton();
    ssidButton->setText("Save");
    connect(ssidButton, SIGNAL(clicked()),this, SLOT(sendSSID()));

    QWidget* ssidArea = new QWidget;
    ssidArea->setLayout(new QHBoxLayout(ssidArea));

    ssidArea->layout()->setMargin(0);
    ssidArea->layout()->setSpacing(0);

    ssidArea->layout()->addWidget(ssidLabel);
    ssidArea->layout()->addWidget(this->ssidLine);
    ssidArea->layout()->addWidget(ssidButton);
    /**/
    QLabel *ssidPasLabel = new QLabel();
    ssidPasLabel->setText("Pass");
    ssidPasLabel->setMinimumWidth(labelWidth);

    this->ssidPasLine->setText(item.value("InternetGatewayDevice").toObject().value("LANDevice").toObject().value("1").toObject().value("WLANConfiguration").toObject().value("1").toObject().value("X_TP_PreSharedKey").toObject().value("_value").toString());
    QPushButton *ssidPasButton = new QPushButton();
    ssidPasButton->setText("Save");
    connect(ssidPasButton, SIGNAL(clicked()),this, SLOT(sendSSIDPas()));

    QWidget* ssidPasArea = new QWidget;
    ssidPasArea->setLayout(new QHBoxLayout(ssidPasArea));

    ssidPasArea->layout()->setMargin(0);
    ssidPasArea->layout()->setSpacing(0);

    ssidPasArea->layout()->addWidget(ssidPasLabel);
    ssidPasArea->layout()->addWidget(this->ssidPasLine);
    ssidPasArea->layout()->addWidget(ssidPasButton);
    /**/
    QLabel *ssidBLabel = new QLabel();
    ssidBLabel->setText("SSID 2");
    ssidBLabel->setMinimumWidth(labelWidth);

    this->ssidBLine->setText(item.value("InternetGatewayDevice").toObject().value("LANDevice").toObject().value("1").toObject().value("WLANConfiguration").toObject().value("2").toObject().value("SSID").toObject().value("_value").toString());

    QPushButton *ssidBButton = new QPushButton();
    ssidBButton->setText("Save");
    connect(ssidBButton, SIGNAL(clicked()),this, SLOT(sendSSIDB()));

    QWidget* ssidBArea = new QWidget;
    ssidBArea->setLayout(new QHBoxLayout(ssidBArea));

    ssidBArea->layout()->setMargin(0);
    ssidBArea->layout()->setSpacing(0);
    ssidBArea->layout()->addWidget(ssidBLabel);
    ssidBArea->layout()->addWidget(this->ssidBLine);
    ssidBArea->layout()->addWidget(ssidBButton);
    /**/
    QLabel *ssidBPasLabel = new QLabel();
    ssidBPasLabel->setText("Pass");
    ssidBPasLabel->setMinimumWidth(labelWidth);

    this->ssidBPasLine->setText(item.value("InternetGatewayDevice").toObject().value("LANDevice").toObject().value("1").toObject().value("WLANConfiguration").toObject().value("1").toObject().value("X_TP_PreSharedKey").toObject().value("_value").toString());
    QPushButton *ssidBPasButton = new QPushButton();
    ssidBPasButton->setText("Save");
    connect(ssidBPasButton, SIGNAL(clicked()),this, SLOT(sendSSIDBPas()));

    QWidget* ssidBPasArea = new QWidget;
    ssidBPasArea->setLayout(new QHBoxLayout(ssidBPasArea));

    ssidBPasArea->layout()->setMargin(0);
    ssidBPasArea->layout()->setSpacing(0);

    ssidBPasArea->layout()->addWidget(ssidBPasLabel);
    ssidBPasArea->layout()->addWidget(this->ssidBPasLine);
    ssidBPasArea->layout()->addWidget(ssidBPasButton);
    /**/
    QLabel *pppoeLLabel = new QLabel();
    pppoeLLabel->setText("PPPoE L");
    pppoeLLabel->setMinimumWidth(labelWidth);

    this->pppoeLLine->setText(item.value("InternetGatewayDevice").toObject().value("WANDevice").toObject().value("1").toObject().value("WANConnectionDevice").toObject().value("1").toObject().value("WANPPPConnection").toObject().value("1").toObject().value("Username").toObject().value("_value").toString());
    QPushButton *pppoeLButton = new QPushButton();
    pppoeLButton->setText("Save");
    connect(pppoeLButton, SIGNAL(clicked()),this, SLOT(sendPPPPoeL()));

    QWidget* pppoeLArea = new QWidget;
    pppoeLArea->setLayout(new QHBoxLayout(pppoeLArea));

    pppoeLArea->layout()->setMargin(0);
    pppoeLArea->layout()->setSpacing(0);

    pppoeLArea->layout()->addWidget(pppoeLLabel);
    pppoeLArea->layout()->addWidget(this->pppoeLLine);
    pppoeLArea->layout()->addWidget(pppoeLButton);
    /**/
    QLabel *pppoePLabel = new QLabel();
    pppoePLabel->setText("PPPoE P");
    pppoePLabel->setMinimumWidth(labelWidth);

    this->pppoePLine->setText(item.value("InternetGatewayDevice").toObject().value("WANDevice").toObject().value("1").toObject().value("WANConnectionDevice").toObject().value("1").toObject().value("WANPPPConnection").toObject().value("1").toObject().value("Password").toObject().value("_value").toString());
    QPushButton *pppoePButton = new QPushButton();
    pppoePButton->setText("Save");
    connect(pppoePButton, SIGNAL(clicked()),this, SLOT(sendPPPPoePas()));

    QWidget* pppoePArea = new QWidget;
    pppoePArea->setLayout(new QHBoxLayout(pppoePArea));

    pppoePArea->layout()->setMargin(0);
    pppoePArea->layout()->setSpacing(0);

    pppoePArea->layout()->addWidget(pppoePLabel);
    pppoePArea->layout()->addWidget(this->pppoePLine);
    pppoePArea->layout()->addWidget(pppoePButton);
    /**/
    QWidget* techAreaV = new QWidget;
    techAreaV->setLayout(new QVBoxLayout(techAreaV));
    techAreaV->layout()->addWidget(ssidArea);
    techAreaV->layout()->addWidget(ssidPasArea);
    techAreaV->layout()->addWidget(ssidBArea);
    techAreaV->layout()->addWidget(ssidBPasArea);
    techAreaV->layout()->addWidget(pppoeLArea);
    techAreaV->layout()->addWidget(pppoePArea);

    ui->scrollArea->setWidget(techAreaV);
}
