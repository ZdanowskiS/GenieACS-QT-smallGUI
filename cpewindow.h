#ifndef CPEWINDOW_H
#define CPEWINDOW_H

#include <QWidget>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include <QStandardItemModel>
#include <QLabel>
#include <QString>
#include <QLineEdit>
#include <QPushButton>

#include <QDebug>

#include "rest.h"
#include "cpeigd.h"

namespace Ui {
class Cpewindow;
}

class Cpewindow : public QWidget
{
    Q_OBJECT

public:
    explicit Cpewindow(rest *acs_rest, QWidget *parent = nullptr);
    ~Cpewindow();

    void displayCPE(QJsonObject item);
    QString id;
    rest *mrest;
    Cpe *windowCPE;

    QString deviceID;

    bool setPointer(QString productclass);

    QLineEdit *ssid24Line = new QLineEdit();
    QLineEdit *ssid24PassLine = new QLineEdit();

    QLineEdit *ssid5Line = new QLineEdit();
    QLineEdit *ssid5PasLine = new QLineEdit();

    QLineEdit *pppoeLoginLine = new QLineEdit();
    QLineEdit *pppoePLine = new QLineEdit();

private slots:
    void sendSSID24();
    void sendSSID24Pass();
    void sendSSID5();
    void sendSSID5Pas();

    void sendPPPPoELogin();
    void sendPPPPoePas();

private:
    Ui::Cpewindow *ui;
};

#endif // CPEWINDOW_H
