#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QLDSV_TC.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void refreshLopSVTable();

    void refreshMonHocTable();

    void refreshLopTCTable();

    void refreshSinhVienTable();

    void on_addClassButton_clicked();

    void on_editClassButton_clicked();

    void on_deleteClassButton_clicked();

    void on_listClassesButton_clicked();

    void on_listSortedStudentsButton_clicked();

    void on_addStudentsButton_clicked();

    void on_addSubjectButton_clicked();

    void on_editSubjectButton_clicked();

    void on_deleteSubjectButton_clicked();

    void on_listSubjectsButton_clicked();

    void on_listAllStudentsButton_clicked();

    void on_addCreditClassButton_clicked();

    void on_editCreditClassButton_clicked();

    void on_deleteCreditClassButton_clicked();

    void on_registerStudentButton_clicked();

    void on_enterScoresButton_clicked();

    void on_listRegisteredStudentsButton_clicked();

    void on_printScoresButton_clicked();

    void on_printAvgScoresButton_clicked();

    void on_printTotalScoresButton_clicked();

    void on_lopSVSearchLineEdit_textChanged(const QString &arg1);

    void on_monHocSearchLineEdit_textChanged(const QString &arg1);

    void on_sinhVienSearchLineEdit_textChanged(const QString &arg1);

    void on_lopTCSearchLineEdit_textChanged(const QString &arg1);

    void on_readFileButton_clicked();

    void on_writeFileButton_clicked();

    void on_addStudentButton_clicked();

    void on_editStudentButton_clicked();

    void on_deleteStudentButton_clicked();

private:
    Ui::MainWindow *ui;
    DSLopTC DSLTC;
    TreeMH DSMH = NULL;
    DSLopSV DSLSV;
    PTRSV FirstSV = NULL;
    bool isShowingStudentList = false;
};
#endif // MAINWINDOW_H
