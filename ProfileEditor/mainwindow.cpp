#include "mainwindow.h"
#include "ui_mainwindow.h"

//Carpertas FormationDataFiles -reportes  //configFiles settings

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Profile Editor");

    ui->tableWidget->setColumnCount(4);

    QStringList tableTitles({"Modo Operación", "Valor Nominal", "Termino", "Stand-By"});
    ui->tableWidget->setHorizontalHeaderLabels(tableTitles);

    QString treeTitle = "Programa";
    ui->treeWidget->setHeaderLabel(treeTitle);

    ui->treeWidget->header()->setDefaultAlignment(Qt::AlignCenter);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNuevo_triggered()
{
    qDebug()<<"Nuevo";

    QTreeWidget * tree = ui->treeWidget;

    QTreeWidgetItem * topLevel = new QTreeWidgetItem();
    topLevel->setText(0, "124-SGL");

    tree->addTopLevelItem(topLevel);

    programData.append({"124-SGL","Carga,15,5,-"});
}

void MainWindow::on_actionGuardar_triggered()
{
    qDebug()<<"Guardar";
    saveSettings();
}

void MainWindow::on_actionRenombrar_triggered()
{
     qDebug()<<"Renombrar";
     loadSettings();
}

void MainWindow::on_actionBorrar_triggered()
{
     qDebug()<<"Borrar";
     qDebug()<<programData.count();
     programData.removeAt(this->m_cProgramIndex);
     qDebug()<<programData.count();
     ui->tableWidget->clear();
     ui->treeWidget->takeTopLevelItem(this->m_cProgramIndex);
     //populateTable(this->m_cProgramIndex);

}

void MainWindow::on_actionCancelar_triggered()
{
    qDebug()<<"Cancelar";
    loadSettings();
    populateTable(this->m_cProgramIndex);
}

void MainWindow::on_actionSalir_triggered()
{
    QMessageBox msg;
    msg.setWindowTitle("Warning");
    msg.setText("Desea guardar cambios");
    msg.setStandardButtons(QMessageBox::Yes);
    msg.addButton(QMessageBox::No);
    msg.setDefaultButton(QMessageBox::No);
    if(msg.exec() == QMessageBox::Yes){
      // do something
       qDebug()<<"SaveSettings";
       saveSettings();
       QApplication::quit();
    }else {
      // do something else
        qDebug()<<"close";
        QApplication::quit();
    }
}

void MainWindow::saveSettings()
{
     qRegisterMetaTypeStreamOperators<QList<QStringList>>("Stuff");

     QSettings settings("archivo.ini", QSettings::NativeFormat);
     settings.setValue("programData", QVariant::fromValue(programData));

     qDebug()<<programData;
     //qDebug()<<settings.fileName();
}

void MainWindow::loadSettings()
{
    qRegisterMetaTypeStreamOperators<QList<QStringList>>("Stuff");
    QSettings settings("archivo.ini", QSettings::NativeFormat);
    QList<QStringList> myList = settings.value("programData").value<QList<QStringList> >();
    programData = myList;
}

void MainWindow::populateTree()
{
    for (const auto& i : programData)
    {
       qDebug() << i;
       QTreeWidgetItem * topLevel = new QTreeWidgetItem();
       topLevel->setText(0,QVariant(i[0]).toString());
       ui->treeWidget->addTopLevelItem(topLevel);
    }
}

void MainWindow::populateTable(int pgmIdx)
{
    ui->tableWidget->setRowCount(programData[pgmIdx].count()-1);
    for(int nstep=0;nstep<programData[pgmIdx].count()-1;nstep++)
    {
        QRegExp rx("(\\ |\\,|\\.|\\:|\\t)"); //RegEx for ' ' or ',' or '.' or ':' or '\t'

        QString stringToSplit = programData[pgmIdx][nstep+1];
        QStringList query = stringToSplit.split(rx);
        //qDebug()<<query;
        //qDebug()<<programData[pgmIdx][nstep+1];
        ui->tableWidget->setItem(nstep, 0, new QTableWidgetItem(query[0]));
        ui->tableWidget->setItem(nstep, 1, new QTableWidgetItem(query[1]));
        ui->tableWidget->setItem(nstep, 2, new QTableWidgetItem(query[2]));
        ui->tableWidget->setItem(nstep, 3, new QTableWidgetItem(query[3]));
    }
}

void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(item);
    Q_UNUSED(column);

    qDebug()<<"Item Clicked";

    try {
        this->m_cProgramIndex = ui->treeWidget->currentIndex().row();
        qDebug()<<this->m_cProgramIndex;
        populateTable(this->m_cProgramIndex);
    } catch(...) {
        //ui->tableWidget->clear();
    }
}

void MainWindow::on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    Q_UNUSED(current);
    Q_UNUSED(previous);

    qDebug()<<"Item Changed";
}

void MainWindow::on_pushButton_clicked()
{
    qDebug()<<"Agregar";
    programData[this->m_cProgramIndex].append("Carga,15,5,-");
    ui->tableWidget->setRowCount(programData[0].count()-1);

    populateTable(this->m_cProgramIndex);
}

void MainWindow::on_pushButton_2_clicked()
{
    qDebug()<<"Eliminar";
    programData[0].removeLast();
    ui->tableWidget->setRowCount(programData[0].count()-1);

    populateTable(this->m_cProgramIndex);
}

void MainWindow::showEvent(QShowEvent *ev)
{
    Q_UNUSED(ev);

    loadSettings();
    populateTree();
}

void MainWindow::closeEvent(QCloseEvent *ev)
{
    Q_UNUSED(ev);

    qDebug()<<"closeEvent";
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    //qDebug()<<"Resize"<<ui->tableWidget->size();
    //qDebug()<<"Resize"<<MainWindow::width();
    //qDebug()<<"Resize"<<MainWindow::height();

    int treeWidgetLeftMargin = 5;
    int treeWidgetTopMargin = 5;
    int treeWidgetWidth = 100;
    int tableWidgetLeftMargin = 5;
    int tableWidgetRightMargin = 5;
    int tableWidgetTopMargin = 5;

    int statusBarHeight = ui->statusBar->height();
    int mainToolbarHeight = ui->mainToolBar->height();
    int bothControlsHeight = statusBarHeight + mainToolbarHeight;

    ui->treeWidget->setGeometry(treeWidgetLeftMargin, treeWidgetTopMargin, treeWidgetWidth, MainWindow::height()-(bothControlsHeight+tableWidgetLeftMargin+tableWidgetRightMargin));

    ui->tableWidget->setGeometry(tableWidgetLeftMargin+ui->treeWidget->width()+tableWidgetRightMargin, tableWidgetTopMargin, MainWindow::width()-ui->treeWidget->width()-15, MainWindow::height()-(bothControlsHeight+tableWidgetLeftMargin+tableWidgetRightMargin));
}

/*void MainWindow::on_tableWidget_doubleClicked(const QModelIndex &index)
{
    Q_UNUSED(index);
    qDebug()<<"double click";

    ComboBoxDelegate* cbid = new ComboBoxDelegate();
    ui->tableWidget->setItemDelegateForColumn(0,cbid);

    //ui->tableWidget->itemDelegate();


    //qDebug()<<t;
    //programData[m_cProgramIndex][0] = y;
}*/

void MainWindow::on_tableWidget_viewportEntered()
{
    qDebug()<<"viewport";
}

void MainWindow::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    qDebug()<<"edit item";
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    ui->treeWidget->editItem(item, column);
}

void MainWindow::on_treeWidget_itemChanged(QTreeWidgetItem *item, int column)
{
    qDebug()<<"item changed";
    QString d = item->text(column);
    qDebug()<<d;
    programData[m_cProgramIndex][0] = d;
}

/*
void MainWindow::on_tableWidget_cellChanged(int row, int column)
{
    qDebug()<<"cell changed";
    QRegExp rx("(\\ |\\,|\\.|\\:|\\t)"); //RegEx for ' ' or ',' or '.' or ':' or '\t'
    QString stringToSplit = programData[m_cProgramIndex][row+1];
    QStringList query = stringToSplit.split(rx);
    query[column] = ui->tableWidget->item(row, column)->text();
    qDebug()<<query;
    programData[m_cProgramIndex][row+1] = query[0]+","+query[1]+","+query[2]+","+query[3];
}
*/

void MainWindow::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    qDebug()<<"tableWidget item";

    ComboBoxDelegate* cbid = new ComboBoxDelegate();
    ui->tableWidget->setItemDelegateForColumn(0,cbid);

    //ui->tableWidget->item(0,0);
    //cbid->item
    //QStringList y = ui->tableWidget->ite
    //ui->tableWidget->itemDelegate();

    //qDebug()<<y;
    //qDebug()<< programData[m_cProgramIndex][1];
    //programData[m_cProgramIndex][0] = y;
}
