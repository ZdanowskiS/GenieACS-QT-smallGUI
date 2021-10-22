#include "cpeac8.h"

QString CpeAC8::getSSID24(QJsonObject item)
{
    return item.value("InternetGatewayDevice").toObject().value("LANDevice").toObject().value("1").toObject().value("WLANConfiguration").toObject().value("1").toObject().value("SSID").toObject().value("_value").toString();
}

QString CpeAC8::getSSID24Pass(QJsonObject item)
{
    return item.value("InternetGatewayDevice").toObject().value("LANDevice").toObject().value("1").toObject().value("WLANConfiguration").toObject().value("1").toObject().value("PreSharedKey").toObject().value("1").toObject().value("PreSharedKey").toObject().value("_value").toString();
}

QString CpeAC8::getSSID5(QJsonObject item)
{
   return item.value("InternetGatewayDevice").toObject().value("LANDevice").toObject().value("1").toObject().value("WLANConfiguration").toObject().value("2").toObject().value("SSID").toObject().value("_value").toString();
}

QString CpeAC8::getSSID5Pass(QJsonObject item)
{
    return item.value("InternetGatewayDevice").toObject().value("LANDevice").toObject().value("1").toObject().value("WLANConfiguration").toObject().value("2").toObject().value("PreSharedKey").toObject().value("1").toObject().value("PreSharedKey").toObject().value("_value").toString();
}

QString CpeAC8::getPPPoELogin(QJsonObject item)
{
   return item.value("InternetGatewayDevice").toObject().value("WANDevice").toObject().value("1").toObject().value("WANConnectionDevice").toObject().value("1").toObject().value("WANPPPConnection").toObject().value("1").toObject().value("Username").toObject().value("_value").toString();
}

QString CpeAC8::getPPPoEPass(QJsonObject item)
{
    return item.value("InternetGatewayDevice").toObject().value("WANDevice").toObject().value("1").toObject().value("WANConnectionDevice").toObject().value("1").toObject().value("WANPPPConnection").toObject().value("1").toObject().value("Password").toObject().value("_value").toString();
}

QString CpeAC8::getPPPoEEnable(QJsonObject item)
{
    return item.value("InternetGatewayDevice").toObject().value("WANDevice").toObject().value("1").toObject().value("WANConnectionDevice").toObject().value("1").toObject().value("WANPPPConnection").toObject().value("1").toObject().value("Enable").toObject().value("_value").toString();
}

QString CpeAC8::getReboot(QJsonObject item)
{
    QDateTime d = QDateTime::fromString(item.value("Reboot").toObject().value("_value").toString(), Qt::ISODate).toLocalTime();
    d.setTimeSpec(Qt::LocalTime);
    return d.toString("yyyy-MM-dd hh:mm:ss");
}

QString CpeAC8::getFactoryReset(QJsonObject item)
{
    QDateTime d = QDateTime::fromString(item.value("FactoryReset").toObject().value("_value").toString(), Qt::ISODate).toLocalTime();
    d.setTimeSpec(Qt::LocalTime);
    return d.toString("yyyy-MM-dd hh:mm:ss");
}

QString CpeAC8::getNodeSSID24()
{
    return this->nodeSSID24;
}

QString CpeAC8::getNodeSSID24Pass()
{
    return this->nodeSSID24Pass;
}

QString CpeAC8::getNodeSSID5()
{
    return this->nodeSSID5;
}

QString CpeAC8::getNodeSSID5Pass()
{
    return this->nodeSSID5Pass;
}

QString CpeAC8::getNodePPPoELogin()
{
    return this->nodePPPoELogin;
}

QString CpeAC8::getNodePPPoEPass()
{
    return this->nodePPPoEPass;
}

QString CpeAC8::getNodePPPoEEnable()
{
    return this->nodePPPoEEnable;
}

QString CpeAC8::getNodeReboot()
{
    return this->nodeReboot;
}

QString CpeAC8::getNodeFactoryReset()
{
    return this->nodeFactoryReset;
}
