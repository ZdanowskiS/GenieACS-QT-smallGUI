#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSettings settings(SETTINGS_ORG, SETTINGS_APP);

   if(settings.value("settings/url", false).toBool()){
       ui->urlEdit->setText(settings.value("settings/url").toString());
   }
   if(settings.value("settings/guiurl", false).toBool()){
       ui->guiurlEdit->setText(settings.value("settings/guiurl").toString());
   }
   if(settings.value("settings/guitoken", false).toBool()){
       ui->guitokenEdit->setText(settings.value("settings/guitoken").toString());
   }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    this->acs_rest->selected=ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toString();
    Cpewindow *cpewindow = new Cpewindow(this->acs_rest,this->lightCSV_rest);

    cpewindow->show();
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    QSettings settings(SETTINGS_ORG, SETTINGS_APP);
    if(index==1){
        QString url=ui->urlEdit->text();
        settings.setValue("settings/url", url);
        QString guiurl=ui->guiurlEdit->text();
        settings.setValue("settings/guiurl", guiurl);

        QString guitoken=ui->guitokenEdit->text();
        settings.setValue("settings/guitoken", guitoken);
        settings.sync();

        acs_rest->SetUrl(url);
        lightCSV_rest->SetUrl(guiurl);
        lightCSV_rest->SetToken(guitoken);

        acs_rest->cpeVector=acs_rest->getCPEList();

        this->fill_tableView(acs_rest->cpeVector);
    }
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    QVector<cpeListItem> searchVector;
    for (int row = 0; row < acs_rest->cpeVector.count(); ++row)
    {
        if(acs_rest->cpeVector[row].serial.contains(arg1,Qt::CaseInsensitive))
        {
            searchVector.push_back(cpeListItem());
            searchVector[searchVector.size()-1]=acs_rest->cpeVector[row];
        }
    }
    this->fill_tableView(searchVector);
}

void MainWindow::fill_tableView(QVector<cpeListItem> fillVector)
{
    QStandardItemModel *tableDevices;
    tableDevices = new QStandardItemModel(fillVector.count(),4,this);
    for (int row = 0; row < fillVector.count(); ++row)
    {
        QModelIndex index = tableDevices->index(row,0,QModelIndex());
        tableDevices->setData(index,fillVector[row].id);
        index = tableDevices->index(row,1,QModelIndex());
        tableDevices->setData(index,fillVector[row].productclass);
        index = tableDevices->index(row,2,QModelIndex());
        tableDevices->setData(index,fillVector[row].serial);
        index = tableDevices->index(row,3,QModelIndex());
        tableDevices->setData(index,fillVector[row].softversion);
    }
    tableDevices->setHeaderData(0, Qt::Horizontal, tr("Device Id"), Qt::DisplayRole);
    tableDevices->setHeaderData(1, Qt::Horizontal, tr("Class"), Qt::DisplayRole);
    tableDevices->setHeaderData(2, Qt::Horizontal, tr("Serial"), Qt::DisplayRole);
    tableDevices->setHeaderData(3, Qt::Horizontal, tr("Soft. version"), Qt::DisplayRole);

    ui->tableView->setModel(tableDevices);

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}
