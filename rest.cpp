#include "rest.h"

rest::rest()
{

}

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void rest::SetUrl(QString url)
{
    this->url=url;
}

void rest::SetToken(QString token)
{
    this->token=token;
}

QString rest::GetData(QString task)
{
    CURL* easyhandle = curl_easy_init();
    std::string readBuffer;
    QString url=this->url+task;

    struct curl_slist *slist=NULL;
    if(this->token!="")
    {
        QString auth="Authorization: "+this->token;
        slist = curl_slist_append(slist, auth.toStdString().c_str());
        curl_easy_setopt(easyhandle, CURLOPT_HTTPHEADER, slist);
    }
    curl_easy_setopt(easyhandle, CURLOPT_URL, url.toStdString().c_str());
    curl_easy_setopt(easyhandle, CURLOPT_SSL_VERIFYPEER, false);
    curl_easy_setopt(easyhandle, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(easyhandle, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_perform(easyhandle);
    curl_easy_cleanup(easyhandle);
    curl_slist_free_all(slist);

    QString result = QString::fromUtf8(readBuffer.c_str());

    return result;
}

QString rest::PostData(QString task, std::string data)
{
    CURL* easyhandle = curl_easy_init();
    std::string readBuffer;
    QString url=this->url+task;

    struct curl_slist *slist=NULL;
    if(this->token!="")
    {
        QString auth="Authorization: "+this->token;
        slist = curl_slist_append(slist, auth.toStdString().c_str());
        curl_easy_setopt(easyhandle, CURLOPT_HTTPHEADER, slist);
    }
    curl_easy_setopt(easyhandle, CURLOPT_URL, url.toStdString().c_str());
    curl_easy_setopt(easyhandle, CURLOPT_POST, 1);
    curl_easy_setopt(easyhandle, CURLOPT_POSTFIELDS,data.c_str());
    curl_easy_setopt(easyhandle, CURLOPT_SSL_VERIFYPEER, false);
    curl_easy_setopt(easyhandle, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(easyhandle, CURLOPT_WRITEDATA, &readBuffer);

    curl_easy_perform(easyhandle);
    curl_easy_cleanup(easyhandle);
    curl_slist_free_all(slist);
    QString result = QString::fromUtf8(readBuffer.c_str());

    return result;
}

QVector<cpeListItem> rest::getCPEList()
{
    QString devices=this->GetData("devices");

    QVector<cpeListItem> cpeVector;

    QJsonParseError jsonError;
    QJsonDocument doc = QJsonDocument::fromJson(devices.toUtf8(),&jsonError);
    if(doc.isArray())
    {
        for(const auto& item : doc.array()){
            if(item.isObject()){
                cpeVector.push_back(cpeListItem());

                cpeVector[cpeVector.size()-1].id=item.toObject().value("_id").toString();
                cpeVector[cpeVector.size()-1].productclass=item.toObject().value("_deviceId").toObject().value("_ProductClass").toString();
                cpeVector[cpeVector.size()-1].serial=item.toObject().value("_deviceId").toObject().value("_SerialNumber").toString();
                cpeVector[cpeVector.size()-1].softversion=item.toObject().value("InternetGatewayDevice").toObject().value("DeviceInfo").toObject().value("SoftwareVersion").toObject().value("_value").toString();
            }
        }
    }

    return cpeVector;
}
