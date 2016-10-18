#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "wineProcess.h"
#include "ui_mainwindow.h"

#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    friend void dataProcessing::processProperListFile(vector<Wine> &wineList);

    static dataProcessing wineProcessor;
    static vector<Wine> wineList; //shared vector of wine objects


    void setUpTable(QTableWidget* table, unsigned int size);
    void clearTable(QTableWidget* table, unsigned int size);
    void populateTable(QTableWidget* table);

    void populateRow(QTableWidget* table, const QModelIndex &index);

    void saveTable();

    void reloadTable();

    void expandList();




private slots:
    void on_inputBtnAllWines_clicked();

    void on_inputBtnRateWines_clicked();

    void on_inputBtnPriceWines_clicked();

    void on_inputBtnSortRatingWines_clicked();

    void on_inputBtnSortPriceWines_clicked();

    void on_inputBtnAddWine_clicked();

    void on_inputBtnSaveWines_clicked();

    void on_inputBtnReloadWines_clicked();

    void on_tableWidget_clicked(const QModelIndex &index);

    void on_inputBtnEditWine_clicked();

    void on_inputBtnMysqlSearch_clicked();

    void on_inputBtnMysqlAll_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
