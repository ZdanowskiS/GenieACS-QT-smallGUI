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

#include "rest.h"
namespace Ui {
class Cpewindow;
}

class Cpewindow : public QWidget
{
    Q_OBJECT

public:
    explicit Cpewindow(rest *acs_rest, QWidget *parent = nullptr);
    ~Cpewindow();

    void displayIGD(QJsonObject item);
    QString id;
    rest *mrest;

    QLineEdit *ssidLine = new QLineEdit();
    QLineEdit *ssidPasLine = new QLineEdit();

    QLineEdit *ssidBLine = new QLineEdit();
    QLineEdit *ssidBPasLine = new QLineEdit();

    QLineEdit *pppoeLLine = new QLineEdit();
    QLineEdit *pppoePLine = new QLineEdit();

private slots:
    void sendSSID();
    void sendSSIDPas();
    void sendSSIDB();
    void sendSSIDBPas();

    void sendPPPPoeL();
    void sendPPPPoePas();

private:
    Ui::Cpewindow *ui;
};

#endif // CPEWINDOW_H
