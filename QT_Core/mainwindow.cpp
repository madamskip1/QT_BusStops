#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QItemSelectionModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->statusbar->showMessage(tr("Adamski Maciej, 300184, PAIN Qt"));

    PrepareModel();
    PrepareView();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete adapter;
    delete model;
    delete parser;
}

void MainWindow::PrepareModel()
{
    adapter = new BusStopAdapter();
    model = new TreeModel();
    parser = new BusStopParser();

    adapter->setModel(model);
    parser->setAdapter(adapter);
    parser->Parse();
}

void MainWindow::PrepareView()
{
    adapter->setModel(model);
    ui->BusView->setModel(model);

    ui->BusView->setColumnWidth(0, 110);
    ui->BusView->setColumnWidth(1, 170);
    ui->BusView->setColumnWidth(2, 170);
}


void MainWindow::on_findButton_clicked()
{
   QString text = ui->findText->text();
   lookForStop(text);
}


void MainWindow::on_findText_textChanged(const QString &arg1)
{
    lookForStop(arg1);
}

void MainWindow::lookForStop(const QString &id)
{
    QModelIndex index = model->getBusStartingWith(id.toInt());
    ui->BusView->scrollTo(index, QAbstractItemView::PositionAtCenter);
    selectRow(index);
}


void MainWindow::selectRow(QModelIndex index)
{
    QItemSelectionModel * selection = ui->BusView->selectionModel();
    selection->select(index, QItemSelectionModel::SelectCurrent);
}
