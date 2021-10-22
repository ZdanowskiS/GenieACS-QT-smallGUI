#include "cpeigd.h"

QString CpeIGD::getSSID24(QJsonObject item)
{
    return item.value("InternetGatewayDevice").toObject().value("LANDevice").toObject().value("1").toObject().value("WLANConfiguration").toObject().value("1").toObject().value("SSID").toObject().value("_value").toString();
}

QString CpeIGD::getSSID24Pass(QJsonObject item)
{
    return item.value("InternetGatewayDevice").toObject().value("LANDevice").toObject().value("1").toObject().value("WLANConfiguration").toObject().value("1").toObject().value("X_TP_PreSharedKey").toObject().value("_value").toString();
}

QString CpeIGD::getSSID5(QJsonObject item)
{
   return item.value("InternetGatewayDevice").toObject().value("LANDevice").toObject().value("1").toObject().value("WLANConfiguration").toObject().value("2").toObject().value("SSID").toObject().value("_value").toString();
}

QString CpeIGD::getSSID5Pass(QJsonObject item)
{
    return item.value("InternetGatewayDevice").toObject().value("LANDevice").toObject().value("1").toObject().value("WLANConfiguration").toObject().value("2").toObject().value("X_TP_PreSharedKey").toObject().value("_value").toString();
}

QString CpeIGD::getPPPoELogin(QJsonObject item)
{
   return item.value("InternetGatewayDevice").toObject().value("WANDevice").toObject().value("1").toObject().value("WANConnectionDevice").toObject().value("1").toObject().value("WANPPPConnection").toObject().value("1").toObject().value("Username").toObject().value("_value").toString();
}

QString CpeIGD::getPPPoEPass(QJsonObject item)
{
    return item.value("InternetGatewayDevice").toObject().value("WANDevice").toObject().value("1").toObject().value("WANConnectionDevice").toObject().value("1").toObject().value("WANPPPConnection").toObject().value("1").toObject().value("Password").toObject().value("_value").toString();
}

QString CpeIGD::getPPPoEEnable(QJsonObject item)
{
    QString result="";
    return result;
}

QString CpeIGD::getReboot(QJsonObject item)
{
    QDateTime d = QDateTime::fromString(item.value("Reboot").toObject().value("_value").toString(), Qt::ISODate).toLocalTime();
    d.setTimeSpec(Qt::LocalTime);
    return d.toString("yyyy-MM-dd hh:mm:ss");
}

QString CpeIGD::getFactoryReset(QJsonObject item)
{
    QDateTime d = QDateTime::fromString(item.value("FactoryReset").toObject().value("_value").toString(), Qt::ISODate).toLocalTime();
    d.setTimeSpec(Qt::LocalTime);
    return d.toString("yyyy-MM-dd hh:mm:ss");
}

QString CpeIGD::getNodeSSID24()
{
    return this->nodeSSID24;
}

QString CpeIGD::getNodeSSID24Pass()
{
    return this->nodeSSID24Pass;
}

QString CpeIGD::getNodeSSID5()
{
    return this->nodeSSID5;
}

QString CpeIGD::getNodeSSID5Pass()
{
    return this->nodeSSID5Pass;
}

QString CpeIGD::getNodePPPoELogin()
{
    return this->nodePPPoELogin;
}

QString CpeIGD::getNodePPPoEPass()
{
    return this->nodePPPoEPass;
}
QString CpeIGD::getNodePPPoEEnable()
{
    return this->nodePPPoEEnable;
}

QString CpeIGD::getNodeReboot()
{
    return this->nodeReboot;
}

QString CpeIGD::getNodeFactoryReset()
{
    return this->nodeFactoryReset;
}
