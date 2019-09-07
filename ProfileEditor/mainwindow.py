# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'mainwindow.ui'
#
# Created by: PyQt5 UI code generator 5.12.2
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(400, 300)
        self.centralWidget = QtWidgets.QWidget(MainWindow)
        self.centralWidget.setObjectName("centralWidget")
        self.label_2 = QtWidgets.QLabel(self.centralWidget)
        self.label_2.setGeometry(QtCore.QRect(70, 10, 111, 16))
        self.label_2.setObjectName("label_2")
        self.spinBox = QtWidgets.QSpinBox(self.centralWidget)
        self.spinBox.setGeometry(QtCore.QRect(50, 40, 71, 22))
        self.spinBox.setAlignment(QtCore.Qt.AlignCenter)
        self.spinBox.setButtonSymbols(QtWidgets.QAbstractSpinBox.PlusMinus)
        self.spinBox.setMinimum(1)
        self.spinBox.setMaximum(15)
        self.spinBox.setProperty("value", 1)
        self.spinBox.setObjectName("spinBox")
        self.pushButton = QtWidgets.QPushButton(self.centralWidget)
        self.pushButton.setEnabled(True)
        self.pushButton.setGeometry(QtCore.QRect(130, 40, 71, 32))
        self.pushButton.setCheckable(False)
        self.pushButton.setObjectName("pushButton")
        self.tableWidget = QtWidgets.QTableWidget(self.centralWidget)
        self.tableWidget.setGeometry(QtCore.QRect(20, 90, 256, 131))
        self.tableWidget.setShowGrid(True)
        self.tableWidget.setRowCount(0)
        self.tableWidget.setColumnCount(0)
        self.tableWidget.setObjectName("tableWidget")
        MainWindow.setCentralWidget(self.centralWidget)
        self.menuBar = QtWidgets.QMenuBar(MainWindow)
        self.menuBar.setGeometry(QtCore.QRect(0, 0, 400, 22))
        self.menuBar.setObjectName("menuBar")
        MainWindow.setMenuBar(self.menuBar)
        self.mainToolBar = QtWidgets.QToolBar(MainWindow)
        self.mainToolBar.setObjectName("mainToolBar")
        MainWindow.addToolBar(QtCore.Qt.TopToolBarArea, self.mainToolBar)
        self.statusBar = QtWidgets.QStatusBar(MainWindow)
        self.statusBar.setObjectName("statusBar")
        MainWindow.setStatusBar(self.statusBar)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

        self.MainWindow = MainWindow

        self.pushButton.clicked.connect(self.on_pushButton_clicked)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.label_2.setText(_translate("MainWindow", "Numero de Pasos"))
        self.pushButton.setText(_translate("MainWindow", "Crear"))

    
    def on_pushButton_clicked(self):    
        rows = self.spinBox.value()
        self.tableWidget.setRowCount(rows)
        self.tableWidget.setColumnCount(4)
    


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())
