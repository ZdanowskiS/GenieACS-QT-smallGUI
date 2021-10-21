#ifndef CPE_H
#define CPE_H

#include <QString>
#include <QJsonObject>

class Cpe
{
public:

    QString nodeSSID24;
    QString nodeSSID24Pass;

    QString nodeSSID5;
    QString nodeSSID5Pass;

    QString nodePPPoELogin;
    QString nodePPPoEPass;
    QString nodePPPoEEnable;

    virtual QString getSSID24(QJsonObject item) =0;
    virtual QString getSSID24Pass(QJsonObject item) =0;

    virtual QString getSSID5(QJsonObject item) =0;
    virtual QString getSSID5Pass(QJsonObject item) =0;

    virtual QString getPPPoELogin(QJsonObject item) =0;
    virtual QString getPPPoEPass(QJsonObject item) =0;
    virtual QString getPPPoEEnable(QJsonObject item) =0;

    virtual QString getNodeSSID24()=0;
    virtual QString getNodeSSID24Pass()=0;

    virtual QString getNodeSSID5()=0;
    virtual QString getNodeSSID5Pass()=0;

    virtual QString getNodePPPoELogin()=0;
    virtual QString getNodePPPoEPass()=0;
    virtual QString getNodePPPoEEnable()=0;
};
#endif // CPE_H
