#ifndef CPEIGD_H
#define CPEIGD_H

#include <QString>
#include <QJsonObject>
#include "cpe.h"

class CpeIGD : public Cpe
{
public:

    QString nodeSSID24="InternetGatewayDevice.LANDevice.1.WLANConfiguration.1.SSID";
    QString nodeSSID24Pass="InternetGatewayDevice.LANDevice.1.WLANConfiguration.1.X_TP_PreSharedKey";

    QString nodeSSID5="InternetGatewayDevice.LANDevice.1.WLANConfiguration.2.SSID";
    QString nodeSSID5Pass="InternetGatewayDevice.LANDevice.1.WLANConfiguration.2.X_TP_PreSharedKey";

    QString nodePPPoELogin="InternetGatewayDevice.WANDevice.1.WANConnectionDevice.1.WANPPPConnection.1.Username";
    QString nodePPPoEPass="InternetGatewayDevice.WANDevice.1.WANConnectionDevice.1.WANPPPConnection.1.Password";
    QString nodePPPoEEnable="";

    QString getSSID24(QJsonObject item);
    QString getSSID24Pass(QJsonObject item);

    QString getSSID5(QJsonObject item);
    QString getSSID5Pass(QJsonObject item);

    QString getPPPoELogin(QJsonObject item);
    QString getPPPoEPass(QJsonObject item);
    QString getPPPoEEnable(QJsonObject item);

    QString getNodeSSID24();
    QString getNodeSSID24Pass();

    QString getNodeSSID5();
    QString getNodeSSID5Pass();

    QString getNodePPPoELogin();
    QString getNodePPPoEPass();
    QString getNodePPPoEEnable();
};

#endif // CPEIGD_H
