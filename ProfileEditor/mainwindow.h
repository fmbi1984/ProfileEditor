#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QTabWidget>
#include <QSettings>
#include <QDebug>
#include <QStringList>

#include <QMessageBox>
#include <QStandardItemModel>
#include <QDir>
#include <QTreeWidget>
#include <QHeaderView>
#include "comboboxdelegate.h"
#include "comboboxtime.h"
#include "timedelegate.h"
#include "spinboxdelegate.h"


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

    void jsonTable();
    void saveTable();

    void populateTree();
    void populateTable(int pgmIdx);

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_treeWidget_itemChanged(QTreeWidgetItem *item, int column);

    void on_tableWidget_cellChanged(int row, int column);

    void on_tableWidget_itemChanged(QTableWidgetItem *item);

    void on_tableWidget_itemClicked(QTableWidgetItem *item);

    void on_actionAgregar_Renglon_triggered();

    void on_actionBorrar_Renglon_triggered();

private:
    Ui::MainWindow *ui;

    void showEvent(QShowEvent *ev);
    void closeEvent(QCloseEvent *ev);

    void resizeEvent(QResizeEvent* resizeEvent);
    void keyPressEvent(QKeyEvent *event);

    QString m_sSettingsFile;
    QList <QStringList> programData;
    int m_cProgramIndex=0;

};

#endif // MAINWINDOW_H
