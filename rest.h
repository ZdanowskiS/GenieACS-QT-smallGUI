#ifndef REST_H
#define REST_H

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QString>
#include <QVector>

#include "curl/curl.h"

struct cpeListItem
{
    QString id;
    QString productclass;
    QString serial;
    QString softversion;
};

class rest
{
public:
    rest();

    QString url;
    QString token;
    QString selected;

    void SetUrl(QString url);
    void SetToken(QString token);

    QString GetData(QString task);
    QString PostData(QString task, std::string data);

    QVector<cpeListItem> cpeVector;
    QVector<cpeListItem> getCPEList();
};

#endif // REST_H
