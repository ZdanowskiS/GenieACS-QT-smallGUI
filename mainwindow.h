#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QSettings>

#include "rest.h"
#include "cpewindow.h"

#define SETTINGS_ORG "SZ"
#define SETTINGS_APP "GenieACSQTsmallGUI"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    rest *acs_rest = new rest();
    rest *lightCSV_rest = new rest();

    void fill_tableView(QVector<cpeListItem> fillVector);
private slots:
    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_tabWidget_currentChanged(int index);

    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
