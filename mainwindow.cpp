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
    isShowingStudentList = false;
    refreshLopSVTable();
}


void MainWindow::on_listSortedStudentsButton_clicked()
{
    bool ok;
    QString maLop = QInputDialog::getText(this, "Danh Sách SV Sắp Xếp", "Nhập mã lớp:", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    int idx = Tim_LopSV(DSLSV, maLop.toStdString());
    if (idx == -1) {
        QMessageBox::warning(this, "Lỗi", "Không tìm thấy lớp");
        return;
    }
    SapXep_DSSV_TenHo(DSLSV.nodes[idx].FirstSV);
    ui->lopSVTableView->clear();
    ui->lopSVTableView->setRowCount(0);
    ui->lopSVTableView->setColumnCount(7);
    QStringList headers = {"Mã Lớp", "MASV", "Họ", "Tên", "Giới Tính", "SĐT", "Email"};
    ui->lopSVTableView->setHorizontalHeaderLabels(headers);

    // Set flag to indicate we're showing student list
    isShowingStudentList = true;

    int row = 0;
    PTRSV p = DSLSV.nodes[idx].FirstSV;
    string malop = DSLSV.nodes[idx].MALOP;
    while (p) {
        ui->lopSVTableView->insertRow(row);
        ui->lopSVTableView->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(malop)));
        ui->lopSVTableView->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(p->sv.MASV)));
        ui->lopSVTableView->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(p->sv.HO)));
        ui->lopSVTableView->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(p->sv.TEN)));
        ui->lopSVTableView->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(p->sv.GIOITINH)));
        ui->lopSVTableView->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(p->sv.SODT)));
        ui->lopSVTableView->setItem(row, 6, new QTableWidgetItem(QString::fromStdString(p->sv.EMAIL)));
        row++;
        p = p->next;
    }
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
    bool ok;
    QString mamh = QInputDialog::getText(this, "Thêm Môn Học", "Nhập mã MH:", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    QString tenmh = QInputDialog::getText(this, "Thêm Môn Học", "Nhập tên MH:", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    QString stclt = QInputDialog::getText(this, "Thêm Môn Học", "Nhập STCLT:", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    QString stcth = QInputDialog::getText(this, "Thêm Môn Học", "Nhập STCTH:", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    string result = Them_MonHoc(DSMH, mamh.toStdString(), tenmh.toStdString(), stclt.toStdString(), stcth.toStdString());
    QMessageBox::information(this, "Kết Quả", QString::fromStdString(result));
    refreshMonHocTable();
}

void MainWindow::on_editSubjectButton_clicked()
{
    bool ok;
    QString mamh = QInputDialog::getText(this, "Sửa Môn Học", "Nhập mã MH cần sửa:", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    QString tenmh_new = QInputDialog::getText(this, "Sửa Môn Học", "Nhập tên MH mới (bỏ trống nếu không đổi):", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    QString stclt_new = QInputDialog::getText(this, "Sửa Môn Học", "Nhập STCLT mới (bỏ trống nếu không đổi):", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    QString stcth_new = QInputDialog::getText(this, "Sửa Môn Học", "Nhập STCTH mới (bỏ trống nếu không đổi):", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    string result = HieuChinh_MonHoc(DSMH, mamh.toStdString(), tenmh_new.toStdString(), stclt_new.toStdString(), stcth_new.toStdString());
    QMessageBox::information(this, "Kết Quả", QString::fromStdString(result));
    refreshMonHocTable();
}

void MainWindow::on_deleteSubjectButton_clicked()
{
    bool ok;
    QString mamh = QInputDialog::getText(this, "Xóa Môn Học", "Nhập mã MH cần xóa:", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    int confirm = QMessageBox::question(this, "Xác Nhận", "Bạn có chắc muốn xóa môn học này?");
    if (confirm != QMessageBox::Yes) return;
    string result = Xoa_MonHoc(DSMH, mamh.toStdString(), true);
    QMessageBox::information(this, "Kết Quả", QString::fromStdString(result));
    refreshMonHocTable();
}

void MainWindow::on_listSubjectsButton_clicked()
{
    refreshMonHocTable();
}

//Tab Sinh viên =======================================================================

void MainWindow::on_addStudentButton_clicked()
{
    bool ok;
    QString maLop = QInputDialog::getText(this, "Thêm Sinh Viên", "Nhập mã lớp:", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    int idx = Tim_LopSV(DSLSV, maLop.toStdString());
    if (idx == -1) {
        QMessageBox::warning(this, "Lỗi", "Không tìm thấy lớp");
        return;
    }
    QString masv = QInputDialog::getText(this, "Thêm Sinh Viên", "Nhập MASV:", QLineEdit::Normal, "", &ok);
    if (!ok || masv.isEmpty()) return;
    if (SearchSV_MASV(DSLSV, masv.toStdString()) != NULL) {
        QMessageBox::warning(this, "Lỗi", "MASV đã tồn tại");
        return;
    }
    QString ho = QInputDialog::getText(this, "Thêm Sinh Viên", "Nhập họ:", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    QString ten = QInputDialog::getText(this, "Thêm Sinh Viên", "Nhập tên:", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    QString gioitinh = QInputDialog::getText(this, "Thêm Sinh Viên", "Nhập giới tính:", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    QString sdt = QInputDialog::getText(this, "Thêm Sinh Viên", "Nhập SĐT:", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    QString email = QInputDialog::getText(this, "Thêm Sinh Viên", "Nhập email:", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    PTRSV newNode = new NodeSV;
    newNode->sv.MASV = masv.toStdString();
    newNode->sv.HO = ho.toStdString();
    newNode->sv.TEN = ten.toStdString();
    newNode->sv.GIOITINH = gioitinh.toStdString();
    newNode->sv.SODT = sdt.toStdString();
    newNode->sv.EMAIL = email.toStdString();
    newNode->next = NULL;
    if (DSLSV.nodes[idx].FirstSV == NULL) {
        DSLSV.nodes[idx].FirstSV = newNode;
    } else {
        PTRSV p = DSLSV.nodes[idx].FirstSV;
        while (p->next) p = p->next;
        p->next = newNode;
    }
    DSLSV.nodes[idx].SLSV++;
    QMessageBox::information(this, "Kết Quả", "Thêm sinh viên thành công");
    refreshLopSVTable();
    on_listAllStudentsButton_clicked();
}


void MainWindow::on_editStudentButton_clicked()
{
    bool ok;
    QString masv = QInputDialog::getText(this, "Sửa Sinh Viên", "Nhập MASV cần sửa:", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    PTRSV p = SearchSV_MASV(DSLSV, masv.toStdString());
    if (p == NULL) {
        QMessageBox::warning(this, "Lỗi", "Không tìm thấy sinh viên");
        return;
    }
    QString ho_new = QInputDialog::getText(this, "Sửa Sinh Viên", "Nhập họ mới (bỏ trống nếu không đổi):", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    if (!ho_new.isEmpty()) p->sv.HO = ho_new.toStdString();
    QString ten_new = QInputDialog::getText(this, "Sửa Sinh Viên", "Nhập tên mới (bỏ trống nếu không đổi):", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    if (!ten_new.isEmpty()) p->sv.TEN = ten_new.toStdString();
    QString gioitinh_new = QInputDialog::getText(this, "Sửa Sinh Viên", "Nhập giới tính mới (bỏ trống nếu không đổi):", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    if (!gioitinh_new.isEmpty()) p->sv.GIOITINH = gioitinh_new.toStdString();
    QString sdt_new = QInputDialog::getText(this, "Sửa Sinh Viên", "Nhập SĐT mới (bỏ trống nếu không đổi):", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    if (!sdt_new.isEmpty()) p->sv.SODT = sdt_new.toStdString();
    QString email_new = QInputDialog::getText(this, "Sửa Sinh Viên", "Nhập email mới (bỏ trống nếu không đổi):", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    if (!email_new.isEmpty()) p->sv.EMAIL = email_new.toStdString();
    QMessageBox::information(this, "Kết Quả", "Sửa sinh viên thành công");
    on_listAllStudentsButton_clicked();
}


void MainWindow::on_deleteStudentButton_clicked()
{
    bool ok;
    QString masv = QInputDialog::getText(this, "Xóa Sinh Viên", "Nhập MASV cần xóa:", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    int confirm = QMessageBox::question(this, "Xác Nhận", "Bạn có chắc muốn xóa sinh viên này?");
    if (confirm != QMessageBox::Yes) return;
    bool found = false;
    for (int i = 0; i < DSLSV.n; i++) {
        PTRSV prev = NULL;
        PTRSV p = DSLSV.nodes[i].FirstSV;
        while (p) {
            if (p->sv.MASV == masv.toStdString()) {
                if (prev == NULL) {
                    DSLSV.nodes[i].FirstSV = p->next;
                } else {
                    prev->next = p->next;
                }
                delete p;
                DSLSV.nodes[i].SLSV--;
                found = true;
                break;
            }
            prev = p;
            p = p->next;
        }
        if (found) break;
    }
    if (found) {
        QMessageBox::information(this, "Kết Quả", "Xóa sinh viên thành công");
        refreshLopSVTable();
        on_listAllStudentsButton_clicked();
    } else {
        QMessageBox::warning(this, "Lỗi", "Không tìm thấy sinh viên");
    }
}

void MainWindow::on_listAllStudentsButton_clicked()
{
    refreshSinhVienTable();
}

//Tab Lớp TC =======================================================================

void MainWindow::on_addCreditClassButton_clicked()
{
    bool ok;
    QString mamh = QInputDialog::getText(this, "Thêm Lớp TC", "Nhập mã MH:", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    QString nienkhoa = QInputDialog::getText(this, "Thêm Lớp TC", "Nhập niên khóa:", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    int hocky = QInputDialog::getInt(this, "Thêm Lớp TC", "Nhập học kỳ:", 1, 1, 10, 1, &ok);
    if (!ok) return;
    int nhom = QInputDialog::getInt(this, "Thêm Lớp TC", "Nhập nhóm:", 1, 1, 10, 1, &ok);
    if (!ok) return;
    int minsv = QInputDialog::getInt(this, "Thêm Lớp TC", "Nhập min SV:", 10, 1, 100, 1, &ok);
    if (!ok) return;
    int maxsv = QInputDialog::getInt(this, "Thêm Lớp TC", "Nhập max SV:", 50, 1, 100, 1, &ok);
    if (!ok) return;
    string result = Them_LopTC(DSLTC, DSMH, mamh.toStdString(), nienkhoa.toStdString(), hocky, nhom, minsv, maxsv);
    QMessageBox::information(this, "Kết Quả", QString::fromStdString(result));
    refreshLopTCTable();
}

void MainWindow::on_editCreditClassButton_clicked()
{
    bool ok;
    int mltc = QInputDialog::getInt(this, "Sửa Lớp TC", "Nhập mã LTC cần sửa:", 0, 0, 100000, 1, &ok);
    if (!ok) return;
    LopTC *ltc = SearchLopTC_MALTC(DSLTC, mltc);
    if (!ltc) {
        QMessageBox::warning(this, "Lỗi", "Không tìm thấy lớp TC");
        return;
    }
    QString mamh_new = QInputDialog::getText(this, "Sửa Lớp TC", "Nhập mã MH mới (bỏ trống nếu không đổi):", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    QString nienkhoa_new = QInputDialog::getText(this, "Sửa Lớp TC", "Nhập niên khóa mới (bỏ trống nếu không đổi):", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    QString hocky_new_str = QInputDialog::getText(this, "Sửa Lớp TC", "Nhập học kỳ mới (bỏ trống nếu không đổi):", QLineEdit::Normal, "", &ok);
    int hocky_new = hocky_new_str.isEmpty() ? ltc->HOCKY : hocky_new_str.toInt();
    if (!ok) return;
    QString nhom_new_str = QInputDialog::getText(this, "Sửa Lớp TC", "Nhập nhóm mới (bỏ trống nếu không đổi):", QLineEdit::Normal, "", &ok);
    int nhom_new = nhom_new_str.isEmpty() ? ltc->NHOM : nhom_new_str.toInt();
    if (!ok) return;
    QString minsv_new_str = QInputDialog::getText(this, "Sửa Lớp TC", "Nhập min SV mới (bỏ trống nếu không đổi):", QLineEdit::Normal, "", &ok);
    int minsv_new = minsv_new_str.isEmpty() ? ltc->MINSV : minsv_new_str.toInt();
    if (!ok) return;
    QString maxsv_new_str = QInputDialog::getText(this, "Sửa Lớp TC", "Nhập max SV mới (bỏ trống nếu không đổi):", QLineEdit::Normal, "", &ok);
    int maxsv_new = maxsv_new_str.isEmpty() ? ltc->MAXSV : maxsv_new_str.toInt();
    if (!ok) return;
    QString huylop_new_str = QInputDialog::getText(this, "Sửa Lớp TC", "Hủy lớp? (yes/no, bỏ trống nếu không đổi):", QLineEdit::Normal, "", &ok);
    bool huylop_new = huylop_new_str.isEmpty() ? ltc->HUYLOP : (huylop_new_str.toLower() == "yes");
    if (!ok) return;
    string result = HieuChinh_LopTC(DSLTC, mltc, mamh_new.toStdString(), nienkhoa_new.toStdString(), hocky_new, nhom_new, minsv_new, maxsv_new, huylop_new);
    QMessageBox::information(this, "Kết Quả", QString::fromStdString(result));
    refreshLopTCTable();
}

void MainWindow::on_deleteCreditClassButton_clicked()
{
    bool ok;
    int mltc = QInputDialog::getInt(this, "Xóa Lớp TC", "Nhập mã LTC cần xóa:", 0, 0, 100000, 1, &ok);
    if (!ok) return;
    int confirm = QMessageBox::question(this, "Xác Nhận", "Bạn có chắc muốn xóa lớp TC này?");
    if (confirm != QMessageBox::Yes) return;
    string result = Xoa_LopTC(DSLTC, mltc, true);
    QMessageBox::information(this, "Kết Quả", QString::fromStdString(result));
    refreshLopTCTable();
}

void MainWindow::on_registerStudentButton_clicked()
{
    bool ok;
    QString masv = QInputDialog::getText(this, "Đăng Ký Lớp TC", "Nhập MASV:", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    QString nienkhoa = QInputDialog::getText(this, "Đăng Ký Lớp TC", "Nhập niên khóa:", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    int hocky = QInputDialog::getInt(this, "Đăng Ký Lớp TC", "Nhập học kỳ:", 1, 1, 10, 1, &ok);
    if (!ok) return;
    QString mamh = QInputDialog::getText(this, "Đăng Ký Lớp TC", "Nhập mã MH:", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    int nhom = QInputDialog::getInt(this, "Đăng Ký Lớp TC", "Nhập nhóm:", 1, 1, 10, 1, &ok);
    if (!ok) return;
    string result = DangKy_LopTC(DSLTC, DSMH, DSLSV, masv.toStdString(), nienkhoa.toStdString(), hocky, mamh.toStdString(), nhom);
    QMessageBox::information(this, "Kết Quả", QString::fromStdString(result));
    refreshLopTCTable();
}

void MainWindow::on_enterScoresButton_clicked()
{
    bool ok;
    QString mamh = QInputDialog::getText(this, "Nhập Điểm Lớp TC", "Nhập mã MH:", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    QString nienkhoa = QInputDialog::getText(this, "Nhập Điểm Lớp TC", "Nhập niên khóa:", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    int hocky = QInputDialog::getInt(this, "Nhập Điểm Lớp TC", "Nhập học kỳ:", 1, 1, 10, 1, &ok);
    if (!ok) return;
    int nhom = QInputDialog::getInt(this, "Nhập Điểm Lớp TC", "Nhập nhóm:", 1, 1, 10, 1, &ok);
    if (!ok) return;

    LopTC *ltc = SearchLopTC(DSLTC, mamh.toStdString(), nienkhoa.toStdString(), hocky, nhom);
    if (!ltc) {
        QMessageBox::warning(this, "Lỗi", "Không tìm thấy lớp TC");
        return;
    }

    // Count the number of students to determine array size
    int diem_size = 0;
    PTRDK p = ltc->DSDK;
    while (p) {
        diem_size++;
        p = p->next;
    }

    // Create CustomPair array
    CustomPair* diem_list = new CustomPair[diem_size];
    int index = 0;

    p = ltc->DSDK;
    while (p) {
        QString masv_qs = QString::fromStdString(p->dk.MASV);
        float diem = QInputDialog::getDouble(this, "Nhập Điểm", "Nhập điểm cho SV " + masv_qs + ":", p->dk.DIEM, 0, 10, 1, &ok);
        if (!ok) {
            delete[] diem_list; // Clean up memory
            return;
        }

        diem_list[index].masv = p->dk.MASV;
        diem_list[index].diem = diem;
        index++;
        p = p->next;
    }

    string result = NhapDiem_LopTC(DSLTC, DSMH, DSLSV, mamh.toStdString(), nienkhoa.toStdString(), hocky, nhom, diem_list, diem_size);

    // Clean up memory
    delete[] diem_list;

    QMessageBox::information(this, "Kết Quả", QString::fromStdString(result));
}

void MainWindow::on_listRegisteredStudentsButton_clicked()
{
    bool ok;
    QString mamh = QInputDialog::getText(this, "Danh Sách SV ĐK Lớp TC", "Nhập mã MH:", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    QString nienkhoa = QInputDialog::getText(this, "Danh Sách SV ĐK Lớp TC", "Nhập niên khóa:", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    int hocky = QInputDialog::getInt(this, "Danh Sách SV ĐK Lớp TC", "Nhập học kỳ:", 1, 1, 10, 1, &ok);
    if (!ok) return;
    int nhom = QInputDialog::getInt(this, "Danh Sách SV ĐK Lớp TC", "Nhập nhóm:", 1, 1, 10, 1, &ok);
    if (!ok) return;
    LopTC *ltc = SearchLopTC(DSLTC, mamh.toStdString(), nienkhoa.toStdString(), hocky, nhom);
    if (!ltc) {
        QMessageBox::warning(this, "Lỗi", "Không tìm thấy lớp TC");
        return;
    }
    ui->sinhVienTableView->clear();
    ui->sinhVienTableView->setRowCount(0);
    ui->sinhVienTableView->setColumnCount(6);
    QStringList headers = {"MASV", "Họ", "Tên", "Giới Tính", "SĐT", "Email"};
    ui->sinhVienTableView->setHorizontalHeaderLabels(headers);
    int row = 0;
    PTRDK p = ltc->DSDK;
    while (p) {
        PTRSV sv = SearchSV_MASV(DSLSV, p->dk.MASV);
        if (sv) {
            ui->sinhVienTableView->insertRow(row);
            ui->sinhVienTableView->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(sv->sv.MASV)));
            ui->sinhVienTableView->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(sv->sv.HO)));
            ui->sinhVienTableView->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(sv->sv.TEN)));
            ui->sinhVienTableView->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(sv->sv.GIOITINH)));
            ui->sinhVienTableView->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(sv->sv.SODT)));
            ui->sinhVienTableView->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(sv->sv.EMAIL)));
            row++;
        }
        p = p->next;
    }
}

void MainWindow::on_printScoresButton_clicked()
{
    bool ok;
    QString mamh = QInputDialog::getText(this, "In Bảng Điểm Lớp TC", "Nhập mã MH:", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    QString nienkhoa = QInputDialog::getText(this, "In Bảng Điểm Lớp TC", "Nhập niên khóa:", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    int hocky = QInputDialog::getInt(this, "In Bảng Điểm Lớp TC", "Nhập học kỳ:", 1, 1, 10, 1, &ok);
    if (!ok) return;
    int nhom = QInputDialog::getInt(this, "In Bảng Điểm Lớp TC", "Nhập nhóm:", 1, 1, 10, 1, &ok);
    if (!ok) return;
    LopTC *ltc = SearchLopTC(DSLTC, mamh.toStdString(), nienkhoa.toStdString(), hocky, nhom);
    if (!ltc) {
        QMessageBox::warning(this, "Lỗi", "Không tìm thấy lớp TC");
        return;
    }
    ui->sinhVienTableView->clear();
    ui->sinhVienTableView->setRowCount(0);
    ui->sinhVienTableView->setColumnCount(4);
    QStringList headers = {"MASV", "Họ Tên", "Điểm"};
    ui->sinhVienTableView->setHorizontalHeaderLabels(headers);
    int row = 0;
    PTRDK p = ltc->DSDK;
    while (p) {
        PTRSV sv = SearchSV_MASV(DSLSV, p->dk.MASV);
        if (sv) {
            ui->sinhVienTableView->insertRow(row);
            ui->sinhVienTableView->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(sv->sv.MASV)));
            QString hoten = QString::fromStdString(sv->sv.HO) + " " + QString::fromStdString(sv->sv.TEN);
            ui->sinhVienTableView->setItem(row, 1, new QTableWidgetItem(hoten));
            ui->sinhVienTableView->setItem(row, 2, new QTableWidgetItem(QString::number(p->dk.DIEM, 'f', 1)));
            row++;
        }
        p = p->next;
    }
}

void MainWindow::on_printAvgScoresButton_clicked()
{
    bool ok;
    QString malop = QInputDialog::getText(this, "In ĐTB Lớp SV", "Nhập mã lớp:", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    int idx = Tim_LopSV(DSLSV, malop.toStdString());
    if (idx == -1) {
        QMessageBox::warning(this, "Lỗi", "Không tìm thấy lớp");
        return;
    }
    ui->sinhVienTableView->clear();
    ui->sinhVienTableView->setRowCount(0);
    ui->sinhVienTableView->setColumnCount(4);
    QStringList headers = {"MASV", "Họ", "Tên", "ĐTB"};
    ui->sinhVienTableView->setHorizontalHeaderLabels(headers);
    int row = 0;
    PTRSV p = DSLSV.nodes[idx].FirstSV;
    while (p) {
        float dtb = TinhDiemTrungBinh(p->sv.MASV, DSLTC, DSMH);
        ui->sinhVienTableView->insertRow(row);
        ui->sinhVienTableView->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(p->sv.MASV)));
        ui->sinhVienTableView->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(p->sv.HO)));
        ui->sinhVienTableView->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(p->sv.TEN)));
        ui->sinhVienTableView->setItem(row, 3, new QTableWidgetItem(QString::number(dtb, 'f', 2)));
        row++;
        p = p->next;
    }
}

void MainWindow::on_printTotalScoresButton_clicked()
{
    bool ok;
    QString malop = QInputDialog::getText(this, "In Điểm Tổng Kết Lớp SV", "Nhập mã lớp:", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    string result = InDiemTongKet(DSLSV, DSLTC, malop.toStdString());
    QMessageBox::information(this, "Điểm Tổng Kết", QString::fromStdString(result));
}


void MainWindow::on_lopSVSearchLineEdit_textChanged(const QString &arg1)
{
    QString search = arg1.toLower();
    for (int row = 0; row < ui->lopSVTableView->rowCount(); row++) {
        bool match = false;

        if (isShowingStudentList) {
            // When showing student list: search in MASV (col 1), Họ (col 2), and Tên (col 3)
            for (int col = 1; col <= 3; col++) {
                if (ui->lopSVTableView->item(row, col) &&
                    ui->lopSVTableView->item(row, col)->text().toLower().contains(search)) {
                    match = true;
                    break;
                }
            }
        } else {
            // When showing class list: search in Mã Lớp (col 0) and Tên Lớp (col 1)
            for (int col = 0; col <= 1; col++) {
                if (ui->lopSVTableView->item(row, col) &&
                    ui->lopSVTableView->item(row, col)->text().toLower().contains(search)) {
                    match = true;
                    break;
                }
            }
        }
        ui->lopSVTableView->setRowHidden(row, !match);
    }
}

void MainWindow::on_monHocSearchLineEdit_textChanged(const QString &arg1)
{
    QString search = arg1.toLower();
    for (int row = 0; row < ui->monHocTableView->rowCount(); row++) {
        bool match = false;

        // Search only in: Mã MH (col 0), Tên MH (col 1)
        for (int col = 0; col <= 1; col++) {
            if (ui->monHocTableView->item(row, col) &&
                ui->monHocTableView->item(row, col)->text().toLower().contains(search)) {
                match = true;
                break;
            }
        }

        ui->monHocTableView->setRowHidden(row, !match);
    }
}

void MainWindow::on_sinhVienSearchLineEdit_textChanged(const QString &arg1)
{
    QString search = arg1.toLower();
    for (int row = 0; row < ui->sinhVienTableView->rowCount(); row++) {
        bool match = false;

        // Search only in: Mã SV (col 0), Họ (col 1), Tên (col 2)
        for (int col = 0; col <= 2; col++) {
            if (ui->sinhVienTableView->item(row, col) &&
                ui->sinhVienTableView->item(row, col)->text().toLower().contains(search)) {
                match = true;
                break;
            }
        }
        ui->sinhVienTableView->setRowHidden(row, !match);
    }
}

void MainWindow::on_lopTCSearchLineEdit_textChanged(const QString &arg1)
{
    QString search = arg1.toLower();
    for (int row = 0; row < ui->lopTCTableView->rowCount(); row++) {
        bool match = false;

        // Search in: Mã LTC (col 0), Mã MH (col 1), Tên MH (col 2)
        for (int col = 0; col <= 2; col++) {
            if (ui->lopTCTableView->item(row, col) &&
                ui->lopTCTableView->item(row, col)->text().toLower().contains(search)) {
                match = true;
                break;
            }
        }

        ui->lopTCTableView->setRowHidden(row, !match);
    }
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




