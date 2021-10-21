#ifndef CPEAC8_H
#define CPEAC8_H

#include <QString>
#include <QJsonObject>
#include "cpe.h"

class CpeAC8 : public Cpe
{
public:
    //cpeAC8();
    QString nodeSSID24="InternetGatewayDevice.LANDevice.1.WLANConfiguration.1.SSID";
    QString nodeSSID24Pass="InternetGatewayDevice.LANDevice.1.WLANConfiguration.1.PreSharedKey.1.PreSharedKey";

    QString nodeSSID5="InternetGatewayDevice.LANDevice.1.WLANConfiguration.2.SSID";
    QString nodeSSID5Pass="InternetGatewayDevice.LANDevice.1.WLANConfiguration.2.PreSharedKey.1.PreSharedKey";

    QString nodePPPoELogin="InternetGatewayDevice.WANDevice.1.WANConnectionDevice.1.WANPPPConnection.1.Username";
    QString nodePPPoEPass="InternetGatewayDevice.WANDevice.1.WANConnectionDevice.1.WANPPPConnection.1.Password";

    QString getSSID24(QJsonObject item);
    QString getSSID24Pass(QJsonObject item);

    QString getSSID5(QJsonObject item);
    QString getSSID5Pass(QJsonObject item);

    QString getPPPoELogin(QJsonObject item);
    QString getPPPoEPass(QJsonObject item);

    QString getNodeSSID24();
    QString getNodeSSID24Pass();

    QString getNodeSSID5();
    QString getNodeSSID5Pass();

    QString getNodePPPoELogin();
    QString getNodePPPoEPass();
};

#endif // CPEAC8_H
