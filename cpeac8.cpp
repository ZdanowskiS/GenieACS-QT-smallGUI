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
