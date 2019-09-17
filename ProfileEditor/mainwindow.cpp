#include "mainwindow.h"
#include "ui_mainwindow.h"

//Carpertas FormationDataFiles -reportes  //configFiles settings

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowMaximizeButtonHint);

    setWindowTitle("Profile Editor");

    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setColumnWidth(3,30);
    //ui->tableWidget->setRowCount(1);
    //ui->tableWidget->setSpan(0,3,1,2);

    QStringList tableTitles({"Modo Operación","Valor Nominal","Termino","","Stand-By"});
    ui->tableWidget->setHorizontalHeaderLabels(tableTitles);



    //ui->tableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);

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

    programData.append({"124-SGL","-,-,-,-,-"});
}

void MainWindow::on_actionGuardar_triggered()
{
    qDebug()<<"Guardar";
    saveTable();
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
     qDebug()<<"saveSettings";
     qRegisterMetaTypeStreamOperators<QList<QStringList>>("Stuff");

     QSettings settings("archivo.ini", QSettings::NativeFormat);
     settings.setValue("programData", QVariant::fromValue(programData));

     qDebug()<<programData;
     //qDebug()<<settings.fileName();
}

void MainWindow::loadSettings()
{
    qDebug()<<"loadSettings";

    qRegisterMetaTypeStreamOperators<QList<QStringList>>("Stuff");
    QSettings settings("archivo.ini", QSettings::NativeFormat);
    QList<QStringList> myList = settings.value("programData").value<QList<QStringList> >();
    programData = myList;
}

void MainWindow::populateTree()
{
    qDebug()<<"populateTree";
    for (const auto& i : programData)
    {
       qDebug()<<"i";
       qDebug() << i;
       QTreeWidgetItem * topLevel = new QTreeWidgetItem();
       topLevel->setText(0,QVariant(i[0]).toString());
       ui->treeWidget->addTopLevelItem(topLevel);
    }
}

void MainWindow::populateTable(int pgmIdx)
{
    qDebug()<<"populateTable";
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
        ui->tableWidget->setItem(nstep, 4, new QTableWidgetItem(query[4]));
    }
}

void MainWindow::jsonTable()
{
    //Modo operacion,valor nominal, termino, stand-by

    qDebug()<<programData.size();

    for (int j=1;j<programData.size();++j) {
        QStringList list1 = {programData[0][j]};
        //QStringList list1 = {"Carga,15,5,-"};
        qDebug()<<"list1";
        qDebug()<<list1;

        QStringList list3;

        QString temp0;
        QString temp1;
        QString temp2;
        QString temp3;
        QString stepCount[list1.size()];

        for (int i = 0; i < list1.size(); ++i){
            QString list2 = list1.at(i).toLocal8Bit().constData();
            for(int x = 0; x < 4; ++x)
            {
                list3 = list2.split(',');
                temp0 = list3[0];
                temp1 = list3[1];
                temp2 = list3[2];
                temp3 = list3[3];
            }

            if(temp0 == "Carga") {
                stepCount[i] = {"{Type:"+temp0+",Current:"+temp1+",Time:"+temp2+",Temp:"+temp3+"}"};
                stepCount[i].replace("-","0.0");
                qDebug()<<"stepCount0";
                qDebug()<<stepCount[i];
            }
            else {
                stepCount[i] = {"{Type:"+temp0+",Time:"+temp2+"}"};
                qDebug()<<"stepCount1";
                qDebug()<<stepCount[i];

                /*QTableWidgetItem *item = new QTableWidgetItem("-");
                item->setFlags(item->flags() & ~Qt::ItemIsEditable); //non editable
                ui->tableWidget->setItem(0,1,item);*/
            }
        }

        //qDebug()<<"[{Type:Begin},";
        //for (int j=0;j<list1.size();++j) {
            //QStringList stepTotal = {"[{Type:Begin},"+stepCount[0]+","+stepCount[1]+","+stepCount[2]+",{Type:End}]"};
            //QStringList stepTotal = {"[{Type:Begin},"+stepCount[0]+",{Type:End}]"};
            //QStringList stepTotal = {","+stepCount[j]+","};
            //qDebug()<<stepTotal;
        //}
        //qDebug()<<"[{Type:End}]";
    }
}
void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(item);
    Q_UNUSED(column);

    qDebug()<<"Item Clicked";

    try {
        this->m_cProgramIndex = ui->treeWidget->currentIndex().row();
        qDebug()<<"indice"<<this->m_cProgramIndex;
        populateTable(this->m_cProgramIndex);
    } catch(...) {
        //ui->tableWidget->clear();
    }
}

void MainWindow::on_pushButton_clicked()
{
    qDebug()<<"Agregar";
    programData[this->m_cProgramIndex].append("-,-,-,-,-");
    ui->tableWidget->setRowCount(programData[0].count()-1);

    populateTable(this->m_cProgramIndex);
}

void MainWindow::on_pushButton_2_clicked()
{
    qDebug()<<"Eliminar";

    programData[this->m_cProgramIndex].removeLast();
    ui->tableWidget->setRowCount(programData[0].count()-1);
    populateTable(this->m_cProgramIndex);
}

void MainWindow::showEvent(QShowEvent *ev)
{
    Q_UNUSED(ev);
    qDebug()<<"showEvent";

    int treeWidgetLeftMargin = 5;
    int treeWidgetTopMargin = 5;
    int treeWidgetWidth = 120;
    int tableWidgetLeftMargin = 5;
    int tableWidgetRightMargin = 5;
    int tableWidgetTopMargin = 5;

    int statusBarHeight = ui->statusBar->height();
    int mainToolbarHeight = ui->mainToolBar->height();
    int bothControlsHeight = statusBarHeight + mainToolbarHeight;

    MainWindow::setGeometry(308,187,616,372);

    ui->tableWidget->setColumnWidth(0,112);
    ui->tableWidget->setColumnWidth(1,112);
    ui->tableWidget->setColumnWidth(2,112);
    ui->tableWidget->setColumnWidth(3,30);
    ui->tableWidget->setColumnWidth(4,112);

    ui->treeWidget->setGeometry(treeWidgetLeftMargin, treeWidgetTopMargin, treeWidgetWidth, MainWindow::height()-(bothControlsHeight+tableWidgetLeftMargin+tableWidgetRightMargin));
    ui->tableWidget->setGeometry(tableWidgetLeftMargin+ui->treeWidget->width()+tableWidgetRightMargin, tableWidgetTopMargin, MainWindow::width()-ui->treeWidget->width()-15, MainWindow::height()-(bothControlsHeight+tableWidgetLeftMargin+tableWidgetRightMargin));

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
    //qDebug()<<"ResizeWidth"<<MainWindow::width();
    //qDebug()<<"ResizeHeight"<<MainWindow::height();

    int mainWidht = MainWindow::width();
    int mainHeight = MainWindow::height();
    int tableSize = ui->tableWidget->size().width();

    int treeWidgetLeftMargin = 5;
    int treeWidgetTopMargin = 5;
    int treeWidgetWidth = 120;
    int tableWidgetLeftMargin = 5;
    int tableWidgetRightMargin = 5;
    int tableWidgetTopMargin = 5;

    int statusBarHeight = ui->statusBar->height();
    int mainToolbarHeight = ui->mainToolBar->height();
    int bothControlsHeight = statusBarHeight + mainToolbarHeight;
    int tableWidth = (tableSize - 30) / 4;

    //qDebug()<<"tableWidth"<<tableWidth;

    if(mainWidht<617 || mainHeight<188) {
        MainWindow::setGeometry(308,187,616,372);
        ui->tableWidget->setColumnWidth(0,112);
        ui->tableWidget->setColumnWidth(1,112);
        ui->tableWidget->setColumnWidth(2,112);
        ui->tableWidget->setColumnWidth(3,30);
        ui->tableWidget->setColumnWidth(4,112);
    }
    else {
        ui->treeWidget->setGeometry(treeWidgetLeftMargin, treeWidgetTopMargin, treeWidgetWidth, MainWindow::height()-(bothControlsHeight+tableWidgetLeftMargin+tableWidgetRightMargin));
        ui->tableWidget->setGeometry(tableWidgetLeftMargin+ui->treeWidget->width()+tableWidgetRightMargin, tableWidgetTopMargin, MainWindow::width()-ui->treeWidget->width()-15, MainWindow::height()-(bothControlsHeight+tableWidgetLeftMargin+tableWidgetRightMargin));
        ui->tableWidget->setColumnWidth(0,tableWidth);
        ui->tableWidget->setColumnWidth(1,tableWidth);
        ui->tableWidget->setColumnWidth(2,tableWidth);
        //ui->tableWidget->setColumnWidth(3,30);
        ui->tableWidget->setColumnWidth(4,tableWidth);
    }
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


void MainWindow::on_tableWidget_cellChanged(int row, int column)
{
    qDebug()<<"cell changed";
    QRegExp rx("(\\ |\\,|\\.|\\:|\\t)"); //RegEx for ' ' or ',' or '.' or ':' or '\t'
    QString stringToSplit = programData[m_cProgramIndex][row+1];
    QStringList query = stringToSplit.split(rx);
    query[column] = ui->tableWidget->item(row, column)->text();
    //qDebug()<<query;

    programData[m_cProgramIndex][row+1] = query[0]+","+query[1]+","+query[2]+","+query[3]+","+query[4];
    qDebug()<<query;
}


void MainWindow::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    qDebug()<<"tableWidget item";
    ComboBoxDelegate* cbid = new ComboBoxDelegate();
    ui->tableWidget->setItemDelegateForColumn(0,cbid);

    ComboBoxTime* cbtime = new ComboBoxTime();
    ui->tableWidget->setItemDelegateForColumn(3,cbtime);
}

void MainWindow::saveTable()
{
    qDebug()<<"saveTable";
    QString itabtext[5];

    //qDebug()<<programData[m_cProgramIndex].count()-1;

    for (int j = 0;j<programData[m_cProgramIndex].count()-1;++j) {
        for (int i = 0;i<5;++i) {
            QTableWidgetItem *itab = ui->tableWidget->item(j,i);
            //ui->tableWidget->
            itabtext[i] = itab->text();
            //qDebug()<<itabtext[i];
        }
        QString text={itabtext[0]+","+itabtext[1]+","+itabtext[2]+","+itabtext[3]+","+itabtext[4]};
        qDebug()<<"text";
        qDebug()<<text;

        qDebug()<<m_cProgramIndex;

        programData[m_cProgramIndex][j+1] = text;

        //programData.append({"124-SGL",text});
        qDebug()<<programData[m_cProgramIndex][j+1];
    }
}

//[{"Type": "Begin"}, {"Type": "Pause", "Time": "25000"}, {"Type": "Charge", "Time": "30000", "Current": "30.0"}, {"Type": "Charge", "Time": "1800000", "Current": "27.4", "Maxtemp": "31.0", "Mintemp": "20.0"}, {"Type": "Charge", "Time": "1200000", "Current": "18.6", "Maxtemp": "31.0", "Mintemp": "20.5"}, {"Type": "Pause", "Time": "180000"}, {"Type": "Charge", "Time": "1200000", "Current": "9.0"}, {"Type": "Pause", "Time": "60000"}, {"Type": "Charge", "Time": "900000", "Current": "12.4", "Maxtemp": "29.0", "Mintemp": "20.1"}, {"Type": "Charge", "Time": "1200000", "Current": "8.2", "Maxtemp": "30.3", "Mintemp": "20.0"}, {"Type": "Charge", "Time": "1500000", "Current": "25.6", "Maxtemp": "30.3", "Mintemp": "20.0"}, {"Type": "Pause", "Time": "180000"}, {"Type": "Charge", "Time": "1200000", "Current": "17.6"}, {"Type": "End"}]


void MainWindow::on_tableWidget_itemClicked(QTableWidgetItem *item)
{
    qDebug()<<"itemClicked";

    qDebug()<<"text";
    QTableWidgetItem *itab = ui->tableWidget->item(programData[m_cProgramIndex].count()-2,0);
    itab->setTextAlignment(Qt::AlignCenter);

    QString itabtext = itab->text();
    qDebug()<<itabtext;

    item = new QTableWidgetItem("-");

    if(itabtext == "Carga"){
        //QColor colorLive(Qt::white);  //flag
        item->setFlags(item->flags() | Qt::ItemIsEditable);
        //ui->tableWidget->setItem(programData[m_cProgramIndex].count()-2,1,item);
        //ui->tableWidget->item(programData[m_cProgramIndex].count()-2,1)->setBackgroundColor(colorLive);

    }
    if(itabtext == "Pausa"){
        QColor colorLive(Qt::lightGray);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        ui->tableWidget->setItem(programData[m_cProgramIndex].count()-2,1,item);
        ui->tableWidget->item(programData[m_cProgramIndex].count()-2,1)->setBackgroundColor(colorLive);
    }
}
