#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QSettings>
#include <QDebug>
#include <QStringList>

//#include <QComboBox>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QDir>
#include <QTreeWidget>
#include "comboboxdelegate.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNuevo_triggered();
    void on_actionGuardar_triggered();
    void on_actionRenombrar_triggered();
    void on_actionBorrar_triggered();
    void on_actionCancelar_triggered();
    void on_actionSalir_triggered();

    void saveSettings();
    void loadSettings();

    void populateTree();
    void populateTable(int pgmIdx);

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);
    void on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    //void on_tableWidget_doubleClicked(const QModelIndex &index);

    void on_tableWidget_viewportEntered();

    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_treeWidget_itemChanged(QTreeWidgetItem *item, int column);

    //void on_tableWidget_cellChanged(int row, int column);

    void on_tableWidget_itemChanged(QTableWidgetItem *item);

private:
    Ui::MainWindow *ui;

    void showEvent(QShowEvent *ev);
    void closeEvent(QCloseEvent *ev);

    void resizeEvent(QResizeEvent* resizeEvent);

    QString m_sSettingsFile;
    QList <QStringList> programData;
    int m_cProgramIndex=0;

};

#endif // MAINWINDOW_H
