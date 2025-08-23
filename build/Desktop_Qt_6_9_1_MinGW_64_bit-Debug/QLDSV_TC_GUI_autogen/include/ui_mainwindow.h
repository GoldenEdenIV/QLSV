/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionRead;
    QAction *actionWrite;
    QWidget *centralwidget;
    QTabWidget *TabWidget;
    QWidget *tab;
    QPushButton *listClassesButton;
    QPushButton *deleteClassButton;
    QPushButton *editClassButton;
    QPushButton *addClassButton;
    QPushButton *listSortedStudentsButton;
    QLineEdit *lopSVSearchLineEdit;
    QPushButton *addStudentsButton;
    QTableWidget *lopSVTableView;
    QWidget *tab_2;
    QPushButton *addSubjectButton;
    QPushButton *editSubjectButton;
    QPushButton *deleteSubjectButton;
    QLineEdit *monHocSearchLineEdit;
    QTableWidget *monHocTableView;
    QWidget *tab_3;
    QLineEdit *sinhVienSearchLineEdit;
    QPushButton *editStudentButton;
    QPushButton *deleteStudentButton;
    QPushButton *addStudentButton;
    QTableWidget *sinhVienTableView;
    QWidget *tab_4;
    QPushButton *editCreditClassButton;
    QPushButton *deleteCreditClassButton;
    QPushButton *enterScoresButton;
    QPushButton *addCreditClassButton;
    QPushButton *registerStudentButton;
    QLineEdit *lopTCSearchLineEdit;
    QPushButton *listRegisteredStudentsButton;
    QPushButton *printAvgScoresButton;
    QPushButton *printTotalScoresButton;
    QTableWidget *lopTCTableView;
    QPushButton *printCreditClassButton;
    QLabel *label;
    QPushButton *writeFileButton;
    QPushButton *readFileButton;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1532, 920);
        actionRead = new QAction(MainWindow);
        actionRead->setObjectName("actionRead");
        actionWrite = new QAction(MainWindow);
        actionWrite->setObjectName("actionWrite");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        TabWidget = new QTabWidget(centralwidget);
        TabWidget->setObjectName("TabWidget");
        TabWidget->setGeometry(QRect(20, 80, 1881, 761));
        TabWidget->setMaximumSize(QSize(2000, 1500));
        QFont font;
        font.setPointSize(12);
        TabWidget->setFont(font);
        TabWidget->setTabPosition(QTabWidget::TabPosition::North);
        TabWidget->setElideMode(Qt::TextElideMode::ElideNone);
        tab = new QWidget();
        tab->setObjectName("tab");
        listClassesButton = new QPushButton(tab);
        listClassesButton->setObjectName("listClassesButton");
        listClassesButton->setGeometry(QRect(0, 380, 161, 41));
        deleteClassButton = new QPushButton(tab);
        deleteClassButton->setObjectName("deleteClassButton");
        deleteClassButton->setGeometry(QRect(0, 170, 161, 41));
        editClassButton = new QPushButton(tab);
        editClassButton->setObjectName("editClassButton");
        editClassButton->setGeometry(QRect(0, 30, 161, 41));
        addClassButton = new QPushButton(tab);
        addClassButton->setObjectName("addClassButton");
        addClassButton->setGeometry(QRect(0, 100, 161, 41));
        listSortedStudentsButton = new QPushButton(tab);
        listSortedStudentsButton->setObjectName("listSortedStudentsButton");
        listSortedStudentsButton->setGeometry(QRect(0, 240, 161, 41));
        lopSVSearchLineEdit = new QLineEdit(tab);
        lopSVSearchLineEdit->setObjectName("lopSVSearchLineEdit");
        lopSVSearchLineEdit->setGeometry(QRect(190, 30, 591, 41));
        addStudentsButton = new QPushButton(tab);
        addStudentsButton->setObjectName("addStudentsButton");
        addStudentsButton->setGeometry(QRect(0, 310, 161, 41));
        lopSVTableView = new QTableWidget(tab);
        lopSVTableView->setObjectName("lopSVTableView");
        lopSVTableView->setGeometry(QRect(190, 100, 1301, 551));
        TabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        addSubjectButton = new QPushButton(tab_2);
        addSubjectButton->setObjectName("addSubjectButton");
        addSubjectButton->setGeometry(QRect(0, 100, 161, 41));
        editSubjectButton = new QPushButton(tab_2);
        editSubjectButton->setObjectName("editSubjectButton");
        editSubjectButton->setGeometry(QRect(0, 30, 161, 41));
        deleteSubjectButton = new QPushButton(tab_2);
        deleteSubjectButton->setObjectName("deleteSubjectButton");
        deleteSubjectButton->setGeometry(QRect(0, 170, 161, 41));
        monHocSearchLineEdit = new QLineEdit(tab_2);
        monHocSearchLineEdit->setObjectName("monHocSearchLineEdit");
        monHocSearchLineEdit->setGeometry(QRect(190, 30, 481, 41));
        monHocTableView = new QTableWidget(tab_2);
        monHocTableView->setObjectName("monHocTableView");
        monHocTableView->setGeometry(QRect(190, 100, 1301, 551));
        TabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        sinhVienSearchLineEdit = new QLineEdit(tab_3);
        sinhVienSearchLineEdit->setObjectName("sinhVienSearchLineEdit");
        sinhVienSearchLineEdit->setGeometry(QRect(190, 30, 481, 41));
        editStudentButton = new QPushButton(tab_3);
        editStudentButton->setObjectName("editStudentButton");
        editStudentButton->setGeometry(QRect(0, 30, 161, 41));
        deleteStudentButton = new QPushButton(tab_3);
        deleteStudentButton->setObjectName("deleteStudentButton");
        deleteStudentButton->setGeometry(QRect(0, 170, 161, 41));
        addStudentButton = new QPushButton(tab_3);
        addStudentButton->setObjectName("addStudentButton");
        addStudentButton->setGeometry(QRect(0, 100, 161, 41));
        sinhVienTableView = new QTableWidget(tab_3);
        sinhVienTableView->setObjectName("sinhVienTableView");
        sinhVienTableView->setGeometry(QRect(190, 100, 1301, 551));
        TabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        editCreditClassButton = new QPushButton(tab_4);
        editCreditClassButton->setObjectName("editCreditClassButton");
        editCreditClassButton->setGeometry(QRect(0, 30, 161, 41));
        deleteCreditClassButton = new QPushButton(tab_4);
        deleteCreditClassButton->setObjectName("deleteCreditClassButton");
        deleteCreditClassButton->setGeometry(QRect(0, 170, 161, 41));
        enterScoresButton = new QPushButton(tab_4);
        enterScoresButton->setObjectName("enterScoresButton");
        enterScoresButton->setEnabled(false);
        enterScoresButton->setGeometry(QRect(190, 30, 161, 41));
        addCreditClassButton = new QPushButton(tab_4);
        addCreditClassButton->setObjectName("addCreditClassButton");
        addCreditClassButton->setGeometry(QRect(0, 100, 161, 41));
        registerStudentButton = new QPushButton(tab_4);
        registerStudentButton->setObjectName("registerStudentButton");
        registerStudentButton->setGeometry(QRect(0, 240, 161, 41));
        lopTCSearchLineEdit = new QLineEdit(tab_4);
        lopTCSearchLineEdit->setObjectName("lopTCSearchLineEdit");
        lopTCSearchLineEdit->setGeometry(QRect(380, 30, 481, 41));
        listRegisteredStudentsButton = new QPushButton(tab_4);
        listRegisteredStudentsButton->setObjectName("listRegisteredStudentsButton");
        listRegisteredStudentsButton->setGeometry(QRect(0, 380, 161, 41));
        printAvgScoresButton = new QPushButton(tab_4);
        printAvgScoresButton->setObjectName("printAvgScoresButton");
        printAvgScoresButton->setGeometry(QRect(0, 520, 161, 41));
        printTotalScoresButton = new QPushButton(tab_4);
        printTotalScoresButton->setObjectName("printTotalScoresButton");
        printTotalScoresButton->setGeometry(QRect(0, 450, 161, 41));
        lopTCTableView = new QTableWidget(tab_4);
        lopTCTableView->setObjectName("lopTCTableView");
        lopTCTableView->setGeometry(QRect(380, 100, 1111, 551));
        printCreditClassButton = new QPushButton(tab_4);
        printCreditClassButton->setObjectName("printCreditClassButton");
        printCreditClassButton->setGeometry(QRect(0, 310, 161, 41));
        TabWidget->addTab(tab_4, QString());
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 1531, 81));
        QFont font1;
        font1.setPointSize(30);
        label->setFont(font1);
        label->setScaledContents(false);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label->setMargin(-3);
        writeFileButton = new QPushButton(centralwidget);
        writeFileButton->setObjectName("writeFileButton");
        writeFileButton->setGeometry(QRect(20, 20, 91, 41));
        readFileButton = new QPushButton(centralwidget);
        readFileButton->setObjectName("readFileButton");
        readFileButton->setGeometry(QRect(120, 20, 91, 41));
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        TabWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionRead->setText(QCoreApplication::translate("MainWindow", "Read", nullptr));
        actionWrite->setText(QCoreApplication::translate("MainWindow", "Write", nullptr));
        listClassesButton->setText(QCoreApplication::translate("MainWindow", "In danh s\303\241ch", nullptr));
        deleteClassButton->setText(QCoreApplication::translate("MainWindow", "X\303\263a l\341\273\233p SV", nullptr));
        editClassButton->setText(QCoreApplication::translate("MainWindow", "C\341\272\255p nh\341\272\255t l\341\273\233p SV", nullptr));
        addClassButton->setText(QCoreApplication::translate("MainWindow", "Th\303\252m l\341\273\233p SV", nullptr));
        listSortedStudentsButton->setText(QCoreApplication::translate("MainWindow", "S\341\272\257p x\341\272\277p", nullptr));
        lopSVSearchLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "L\341\273\233p SV: T\303\254m theo m\303\243 l\341\273\233p, t\303\252n l\341\273\233p. DSSV: T\303\254m theo m\303\243 SV, h\341\273\215 t\303\252n.", nullptr));
        addStudentsButton->setText(QCoreApplication::translate("MainWindow", "Th\303\252m sinh vi\303\252n", nullptr));
        TabWidget->setTabText(TabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "L\341\273\233p SV", nullptr));
        addSubjectButton->setText(QCoreApplication::translate("MainWindow", "Th\303\252m m\303\264n h\341\273\215c", nullptr));
        editSubjectButton->setText(QCoreApplication::translate("MainWindow", "C\341\272\255p nh\341\272\255t MH", nullptr));
        deleteSubjectButton->setText(QCoreApplication::translate("MainWindow", "X\303\263a m\303\264n h\341\273\215c", nullptr));
        monHocSearchLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "T\303\254m theo m\303\243 m\303\264n h\341\273\215c, t\303\252n m\303\264n h\341\273\215c", nullptr));
        TabWidget->setTabText(TabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "M\303\264n h\341\273\215c", nullptr));
        sinhVienSearchLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "T\303\254m theo m\303\243 sinh vi\303\252n, h\341\273\215, t\303\252n", nullptr));
        editStudentButton->setText(QCoreApplication::translate("MainWindow", "C\341\272\255p nh\341\272\255t SV", nullptr));
        deleteStudentButton->setText(QCoreApplication::translate("MainWindow", "Xo\303\241 SV", nullptr));
        addStudentButton->setText(QCoreApplication::translate("MainWindow", "Th\303\252m SV", nullptr));
        TabWidget->setTabText(TabWidget->indexOf(tab_3), QCoreApplication::translate("MainWindow", "Sinh vi\303\252n", nullptr));
        editCreditClassButton->setText(QCoreApplication::translate("MainWindow", "C\341\272\255p nh\341\272\255t l\341\273\233p TC", nullptr));
        deleteCreditClassButton->setText(QCoreApplication::translate("MainWindow", "X\303\263a l\341\273\233p TC", nullptr));
        enterScoresButton->setText(QCoreApplication::translate("MainWindow", "C\341\272\255p nh\341\272\255t \304\221i\341\273\203m", nullptr));
        addCreditClassButton->setText(QCoreApplication::translate("MainWindow", "Th\303\252m l\341\273\233p TC", nullptr));
        registerStudentButton->setText(QCoreApplication::translate("MainWindow", "\304\220\304\203ng k\303\255 SV", nullptr));
        lopTCSearchLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "T\303\254m theo m\303\243 l\341\273\233p TC, m\303\243 MH, t\303\252n MH.", nullptr));
        listRegisteredStudentsButton->setText(QCoreApplication::translate("MainWindow", "Xem SV \304\221\304\203ng k\303\255", nullptr));
        printAvgScoresButton->setText(QCoreApplication::translate("MainWindow", "In \304\221i\341\273\203m TB", nullptr));
        printTotalScoresButton->setText(QCoreApplication::translate("MainWindow", "In \304\221i\341\273\203m t\341\273\225ng", nullptr));
        printCreditClassButton->setText(QCoreApplication::translate("MainWindow", "In l\341\273\233p TC", nullptr));
        TabWidget->setTabText(TabWidget->indexOf(tab_4), QCoreApplication::translate("MainWindow", "L\341\273\233p t\303\255n ch\341\273\211", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "QU\341\272\242N L\303\215 SINH VI\303\212N", nullptr));
        writeFileButton->setText(QCoreApplication::translate("MainWindow", "Ghi file", nullptr));
        readFileButton->setText(QCoreApplication::translate("MainWindow", "\304\220\341\273\215c file", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
