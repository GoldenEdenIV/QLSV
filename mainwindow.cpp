#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QLDSV_TC.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QTextStream>
#include <sstream>
#include <iomanip>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshLopSVTable()
{
    ui->lopSVTableView->clear();
    ui->lopSVTableView->setRowCount(DSLSV.n);
    ui->lopSVTableView->setColumnCount(3);
    QStringList headers;
    headers << "Mã Lớp" << "Tên Lớp" << "SLSV";
    ui->lopSVTableView->setHorizontalHeaderLabels(headers);
    for (int i = 0; i < DSLSV.n; i++) {
        ui->lopSVTableView->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(DSLSV.nodes[i].MALOP)));
        ui->lopSVTableView->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(DSLSV.nodes[i].TENLOP)));
        ui->lopSVTableView->setItem(i, 2, new QTableWidgetItem(QString::number(DSLSV.nodes[i].SLSV)));
    }
}

void MainWindow::refreshMonHocTable()
{
    DSMHArray arr;
    ThuThapMH(DSMH, arr);
    ui->monHocTableView->clear();
    ui->monHocTableView->setRowCount(arr.n);
    ui->monHocTableView->setColumnCount(4);
    QStringList headers;
    headers << "Mã MH" << "Tên MH" << "STCLT" << "STCTH";
    ui->monHocTableView->setHorizontalHeaderLabels(headers);
    for (int i = 0; i < arr.n; i++) {
        ui->monHocTableView->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(arr.nodes[i].MAMH)));
        ui->monHocTableView->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(arr.nodes[i].TENMH)));
        ui->monHocTableView->setItem(i, 2, new QTableWidgetItem(QString::number(arr.nodes[i].STCLT)));
        ui->monHocTableView->setItem(i, 3, new QTableWidgetItem(QString::number(arr.nodes[i].STCTH)));
    }
}

void MainWindow::refreshLopTCTable()
{
    ui->lopTCTableView->clear();
    ui->lopTCTableView->setRowCount(DSLTC.n);
    ui->lopTCTableView->setColumnCount(10);
    QStringList headers;
    headers << "Mã LTC" << "Mã MH" << "Tên MH" << "Niên Khóa" << "Học Kỳ" << "Nhóm" << "Min SV" << "Max SV" << "SLDK" << "Hủy";
    ui->lopTCTableView->setHorizontalHeaderLabels(headers);
    for (int i = 0; i < DSLTC.n; i++) {
        LopTC *ltc = DSLTC.nodes[i];
        ui->lopTCTableView->setItem(i, 0, new QTableWidgetItem(QString::number(ltc->MALOPTC)));
        ui->lopTCTableView->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(ltc->MAMH)));
        NodeMH *node = TimMH_MAMH(DSMH, ltc->MAMH);
        string tenmh = node ? node->mh.TENMH : "";
        ui->lopTCTableView->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(tenmh)));
        ui->lopTCTableView->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(ltc->NIENKHOA)));
        ui->lopTCTableView->setItem(i, 4, new QTableWidgetItem(QString::number(ltc->HOCKY)));
        ui->lopTCTableView->setItem(i, 5, new QTableWidgetItem(QString::number(ltc->NHOM)));
        ui->lopTCTableView->setItem(i, 6, new QTableWidgetItem(QString::number(ltc->MINSV)));
        ui->lopTCTableView->setItem(i, 7, new QTableWidgetItem(QString::number(ltc->MAXSV)));
        ui->lopTCTableView->setItem(i, 8, new QTableWidgetItem(QString::number(ltc->SLSVDK)));
        ui->lopTCTableView->setItem(i, 9, new QTableWidgetItem(ltc->HUYLOP ? "Yes" : "No"));
    }
}

void MainWindow::refreshSinhVienTable()
{
    ui->sinhVienTableView->clear();

    // Count total number of students across all classes
    int count = 0;
    for (int i = 0; i < DSLSV.n; i++) {
        for (PTRSV p = DSLSV.nodes[i].FirstSV; p != NULL; p = p->next) {
            count++;
        }
    }

    // Set up table structure
    ui->sinhVienTableView->setRowCount(count);
    ui->sinhVienTableView->setColumnCount(6);
    QStringList headers;
    headers << "Mã SV" << "Họ" << "Tên" << "Giới Tính" << "Số ĐT" << "Email";
    ui->sinhVienTableView->setHorizontalHeaderLabels(headers);

    // Populate the table with students from all classes
    int row = 0;
    for (int i = 0; i < DSLSV.n; i++) {
        for (PTRSV p = DSLSV.nodes[i].FirstSV; p != NULL; p = p->next) {
            ui->sinhVienTableView->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(p->sv.MASV)));
            ui->sinhVienTableView->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(p->sv.HO)));
            ui->sinhVienTableView->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(p->sv.TEN)));
            ui->sinhVienTableView->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(p->sv.GIOITINH)));
            ui->sinhVienTableView->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(p->sv.SODT)));
            ui->sinhVienTableView->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(p->sv.EMAIL)));
            row++;
        }
    }
}

// Tab lớp sinh viên  =======================================================================

void MainWindow::on_addClassButton_clicked()
{
    bool ok;
    QString maLop = QInputDialog::getText(this, "Thêm Lớp SV", "Nhập mã lớp:", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    QString tenLop = QInputDialog::getText(this, "Thêm Lớp SV", "Nhập tên lớp:", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    std::string result = Them_LopSV(DSLSV, maLop.toStdString(), tenLop.toStdString());
    QMessageBox::information(this, "Kết Quả", QString::fromStdString(result));
    refreshLopSVTable();
}


void MainWindow::on_editClassButton_clicked()
{
    bool ok;
    QString maLop = QInputDialog::getText(this, "Sửa Lớp SV", "Nhập mã lớp cần sửa:", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    QString tenLopNew = QInputDialog::getText(this, "Sửa Lớp SV", "Nhập tên lớp mới (nếu không thay đổi thì bỏ trống):", QLineEdit::Normal, "", &ok);
    if (!ok) return;

    std::string result = HieuChinh_LopSV(DSLSV, maLop.toStdString(), tenLopNew.toStdString());
    QMessageBox::information(this, "Kết Quả", QString::fromStdString(result));
    refreshLopSVTable();
}


void MainWindow::on_deleteClassButton_clicked()
{
    bool ok;
    QString maLop = QInputDialog::getText(this, "Xóa Lớp SV", "Nhập mã lớp cần xóa:", QLineEdit::Normal, "", &ok);
    if (!ok) return;

    int confirm = QMessageBox::question(this, "Xác Nhận", "Bạn có chắc muốn xóa lớp này?");
    if (confirm != QMessageBox::Yes) return;

    std::string result = Xoa_LopSV(DSLSV, maLop.toStdString());
    QMessageBox::information(this, "Kết Quả", QString::fromStdString(result));
    refreshLopSVTable();
}


void MainWindow::on_listClassesButton_clicked()
{
    refreshLopSVTable();
}


void MainWindow::on_listSortedStudentsButton_clicked()
{

}


void MainWindow::on_addStudentsButton_clicked()
{
    bool ok;
    QString maLop = QInputDialog::getText(this, "Thêm SV Vào Lớp", "Nhập mã lớp:", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    int idx = Tim_LopSV(DSLSV, maLop.toStdString());
    if (idx == -1) {
        QMessageBox::warning(this, "Lỗi", "Không tìm thấy lớp");
        return;
    }
    while (true) {
        QString masv = QInputDialog::getText(this, "Thêm SV", "Nhập MASV (bỏ trống để dừng):", QLineEdit::Normal, "", &ok);
        if (!ok || masv.isEmpty()) break;
        PTRSV sv = SearchSV_MASV(DSLSV, masv.toStdString());
        if (sv == NULL) {
            QMessageBox::warning(this, "Lỗi", "Không tìm thấy sinh viên trong hệ thống");
            continue;
        }
        if (KiemTra_SV(DSLSV.nodes[idx].FirstSV, masv.toStdString())) {
            QMessageBox::warning(this, "Lỗi", "Sinh viên đã có trong lớp này");
            continue;
        }
        // Find the original class and remove from there
        int orig_idx = -1;
        PTRSV prev = NULL;
        PTRSV p = NULL;
        for (int i = 0; i < DSLSV.n; i++) {
            prev = NULL;
            p = DSLSV.nodes[i].FirstSV;
            while (p) {
                if (p->sv.MASV == masv.toStdString()) {
                    orig_idx = i;
                    break;
                }
                prev = p;
                p = p->next;
            }
            if (orig_idx != -1) break;
        }
        if (orig_idx != -1) {
            if (prev == NULL) {
                DSLSV.nodes[orig_idx].FirstSV = p->next;
            } else {
                prev->next = p->next;
            }
            DSLSV.nodes[orig_idx].SLSV--;
            // Add to new class
            p->next = NULL;
            if (DSLSV.nodes[idx].FirstSV == NULL) {
                DSLSV.nodes[idx].FirstSV = p;
            } else {
                PTRSV q = DSLSV.nodes[idx].FirstSV;
                while (q->next) q = q->next;
                q->next = p;
            }
            DSLSV.nodes[idx].SLSV++;
        }
    }
    QMessageBox::information(this, "Kết Quả", "Thêm SV vào lớp thành công");
    refreshLopSVTable();
}

//Tab môn học  =======================================================================


void MainWindow::on_addSubjectButton_clicked()
{

}


void MainWindow::on_editSubjectButton_clicked()
{

}


void MainWindow::on_deleteSubjectButton_clicked()
{

}


void MainWindow::on_listSubjectsButton_clicked()
{

}

//Tab Sinh viên =======================================================================

void MainWindow::on_addStudentButton_clicked()
{

}


void MainWindow::on_editStudentButton_clicked()
{

}


void MainWindow::on_deleteStudentButton_clicked()
{

}

void MainWindow::on_listAllStudentsButton_clicked()
{

}

//Tab Lớp TC =======================================================================

void MainWindow::on_addCreditClassButton_clicked()
{

}


void MainWindow::on_editCreditClassButton_clicked()
{

}


void MainWindow::on_deleteCreditClassButton_clicked()
{

}


void MainWindow::on_registerStudentButton_clicked()
{

}


void MainWindow::on_enterScoresButton_clicked()
{

}


void MainWindow::on_listRegisteredStudentsButton_clicked()
{

}


void MainWindow::on_printScoresButton_clicked()
{

}


void MainWindow::on_printAvgScoresButton_clicked()
{

}


void MainWindow::on_printTotalScoresButton_clicked()
{

}


void MainWindow::on_lopSVSearchLineEdit_textChanged(const QString &arg1)
{

}


void MainWindow::on_monHocSearchLineEdit_textChanged(const QString &arg1)
{

}


void MainWindow::on_sinhVienSearchLineEdit_textChanged(const QString &arg1)
{

}


void MainWindow::on_lopTCSearchLineEdit_textChanged(const QString &arg1)
{

}


void MainWindow::on_readFileButton_clicked()
{
    std::string result = DocFile(DSMH, DSLSV, DSLTC);
    QMessageBox::information(this, "Kết Quả", QString::fromStdString(result));
    refreshLopSVTable();
    refreshMonHocTable();
    refreshLopTCTable();
    refreshSinhVienTable();
}


void MainWindow::on_writeFileButton_clicked()
{
    std::string result = GhiFile(DSMH, DSLSV, DSLTC);
    QMessageBox::information(this, "Kết Quả", QString::fromStdString(result));
}




