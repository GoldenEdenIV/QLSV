#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QLDSV_TC.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QTextStream>
#include <QSpinBox>
#include <QFormLayout>
#include <sstream>
#include <iomanip>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lopSVTableView->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->monHocTableView->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->sinhVienTableView->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->lopTCTableView->setEditTriggers(QAbstractItemView::DoubleClicked);
}



MainWindow::~MainWindow()
{
    delete ui;
}

class SingleInputDialog : public QDialog {
public:
    QLineEdit *inputEdit;

    SingleInputDialog(const QString &title, const QString &label, QWidget *parent = nullptr) : QDialog(parent) {
        setWindowTitle(title);
        QFormLayout *layout = new QFormLayout(this);

        inputEdit = new QLineEdit(this);
        layout->addRow(label, inputEdit);

        QPushButton *okButton = new QPushButton("OK", this);
        QPushButton *cancelButton = new QPushButton("Cancel", this);
        QHBoxLayout *buttonLayout = new QHBoxLayout();
        buttonLayout->addWidget(okButton);
        buttonLayout->addWidget(cancelButton);
        layout->addRow(buttonLayout);

        connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
        connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    }

    QString getInput() { return inputEdit->text(); }
};

class LopSVAddEditDialog : public QDialog {
public:
    QLineEdit *maLopEdit;
    QLineEdit *tenLopEdit;

    LopSVAddEditDialog(const QString &title, QWidget *parent = nullptr) : QDialog(parent) {
        setWindowTitle(title);
        QFormLayout *layout = new QFormLayout(this);

        maLopEdit = new QLineEdit(this);
        tenLopEdit = new QLineEdit(this);

        layout->addRow("Mã lớp:", maLopEdit);
        layout->addRow("Tên lớp:", tenLopEdit);

        QPushButton *okButton = new QPushButton("OK", this);
        QPushButton *cancelButton = new QPushButton("Cancel", this);
        QHBoxLayout *buttonLayout = new QHBoxLayout();
        buttonLayout->addWidget(okButton);
        buttonLayout->addWidget(cancelButton);
        layout->addRow(buttonLayout);

        connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
        connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    }

    QString getMaLop() { return maLopEdit->text(); }
    QString getTenLop() { return tenLopEdit->text(); }
};

class MonHocAddEditDialog : public QDialog {
public:
    QLineEdit *mamhEdit;
    QLineEdit *tenmhEdit;
    QLineEdit *stcltEdit;
    QLineEdit *stcthEdit;

    MonHocAddEditDialog(const QString &title, QWidget *parent = nullptr) : QDialog(parent) {
        setWindowTitle(title);
        QFormLayout *layout = new QFormLayout(this);

        mamhEdit = new QLineEdit(this);
        tenmhEdit = new QLineEdit(this);
        stcltEdit = new QLineEdit(this);
        stcthEdit = new QLineEdit(this);

        layout->addRow("Mã MH:", mamhEdit);
        layout->addRow("Tên MH:", tenmhEdit);
        layout->addRow("STCLT:", stcltEdit);
        layout->addRow("STCTH:", stcthEdit);

        QPushButton *okButton = new QPushButton("OK", this);
        QPushButton *cancelButton = new QPushButton("Cancel", this);
        QHBoxLayout *buttonLayout = new QHBoxLayout();
        buttonLayout->addWidget(okButton);
        buttonLayout->addWidget(cancelButton);
        layout->addRow(buttonLayout);

        connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
        connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    }

    QString getMaMH() { return mamhEdit->text(); }
    QString getTenMH() { return tenmhEdit->text(); }
    QString getSTCLT() { return stcltEdit->text(); }
    QString getSTCTH() { return stcthEdit->text(); }
};

class StudentAddEditDialog : public QDialog {
public:
    QLineEdit *maLopEdit;
    QLineEdit *masvEdit;
    QLineEdit *hoEdit;
    QLineEdit *tenEdit;
    QLineEdit *gioitinhEdit;
    QLineEdit *sodtEdit;
    QLineEdit *emailEdit;

    StudentAddEditDialog(const QString &title, QWidget *parent = nullptr) : QDialog(parent) {
        setWindowTitle(title);
        QFormLayout *layout = new QFormLayout(this);

        maLopEdit = new QLineEdit(this);
        masvEdit = new QLineEdit(this);
        hoEdit = new QLineEdit(this);
        tenEdit = new QLineEdit(this);
        gioitinhEdit = new QLineEdit(this);
        sodtEdit = new QLineEdit(this);
        emailEdit = new QLineEdit(this);

        layout->addRow("Mã lớp:", maLopEdit);
        layout->addRow("Mã SV:", masvEdit);
        layout->addRow("Họ:", hoEdit);
        layout->addRow("Tên:", tenEdit);
        layout->addRow("Giới tính:", gioitinhEdit);
        layout->addRow("SĐT:", sodtEdit);
        layout->addRow("Email:", emailEdit);

        QPushButton *okButton = new QPushButton("OK", this);
        QPushButton *cancelButton = new QPushButton("Cancel", this);
        QHBoxLayout *buttonLayout = new QHBoxLayout();
        buttonLayout->addWidget(okButton);
        buttonLayout->addWidget(cancelButton);
        layout->addRow(buttonLayout);

        connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
        connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    }

    QString getMaLop() { return maLopEdit->text(); }
    QString getMaSV() { return masvEdit->text(); }
    QString getHo() { return hoEdit->text(); }
    QString getTen() { return tenEdit->text(); }
    QString getGioiTinh() { return gioitinhEdit->text(); }
    QString getSoDT() { return sodtEdit->text(); }
    QString getEmail() { return emailEdit->text(); }
};

class LopTCAddDialog : public QDialog {
public:
    QLineEdit *mamhEdit;
    QLineEdit *nienkhoaEdit;
    QLineEdit *hockyEdit;
    QLineEdit *nhomEdit;
    QLineEdit *minsvEdit;
    QLineEdit *maxsvEdit;

    LopTCAddDialog(const QString &title, QWidget *parent = nullptr) : QDialog(parent) {
        setWindowTitle(title);
        QFormLayout *layout = new QFormLayout(this);

        mamhEdit = new QLineEdit(this);
        nienkhoaEdit = new QLineEdit(this);
        hockyEdit = new QLineEdit(this);
        nhomEdit = new QLineEdit(this);
        minsvEdit = new QLineEdit(this);
        maxsvEdit = new QLineEdit(this);

        layout->addRow("Mã MH:", mamhEdit);
        layout->addRow("Niên khóa:", nienkhoaEdit);
        layout->addRow("Học kỳ:", hockyEdit);
        layout->addRow("Nhóm:", nhomEdit);
        layout->addRow("Min SV:", minsvEdit);
        layout->addRow("Max SV:", maxsvEdit);

        QPushButton *okButton = new QPushButton("OK", this);
        QPushButton *cancelButton = new QPushButton("Cancel", this);
        QHBoxLayout *buttonLayout = new QHBoxLayout();
        buttonLayout->addWidget(okButton);
        buttonLayout->addWidget(cancelButton);
        layout->addRow(buttonLayout);

        connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
        connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    }

    QString getMaMH() { return mamhEdit->text(); }
    QString getNienKhoa() { return nienkhoaEdit->text(); }
    QString getHocKy() { return hockyEdit->text(); }
    QString getNhom() { return nhomEdit->text(); }
    QString getMinSV() { return minsvEdit->text(); }
    QString getMaxSV() { return maxsvEdit->text(); }
};

class LopTCEditDialog : public QDialog {
public:
    QLineEdit *mltcEdit;
    QLineEdit *mamhEdit;
    QLineEdit *nienkhoaEdit;
    QLineEdit *hockyEdit;
    QLineEdit *nhomEdit;
    QLineEdit *minsvEdit;
    QLineEdit *maxsvEdit;
    QLineEdit *huylopEdit;

    LopTCEditDialog(const QString &title, QWidget *parent = nullptr) : QDialog(parent) {
        setWindowTitle(title);
        QFormLayout *layout = new QFormLayout(this);

        mltcEdit = new QLineEdit(this);
        mamhEdit = new QLineEdit(this);
        nienkhoaEdit = new QLineEdit(this);
        hockyEdit = new QLineEdit(this);
        nhomEdit = new QLineEdit(this);
        minsvEdit = new QLineEdit(this);
        maxsvEdit = new QLineEdit(this);
        huylopEdit = new QLineEdit(this);

        layout->addRow("Mã LTC:", mltcEdit);
        layout->addRow("Mã MH mới:", mamhEdit);
        layout->addRow("Niên khóa mới:", nienkhoaEdit);
        layout->addRow("Học kỳ mới:", hockyEdit);
        layout->addRow("Nhóm mới:", nhomEdit);
        layout->addRow("Min SV mới:", minsvEdit);
        layout->addRow("Max SV mới:", maxsvEdit);
        layout->addRow("Hủy lớp (yes/no):", huylopEdit);

        mamhEdit->setPlaceholderText("Bỏ trống nếu không đổi");
        nienkhoaEdit->setPlaceholderText("Bỏ trống nếu không đổi");
        hockyEdit->setPlaceholderText("Bỏ trống nếu không đổi");
        nhomEdit->setPlaceholderText("Bỏ trống nếu không đổi");
        minsvEdit->setPlaceholderText("Bỏ trống nếu không đổi");
        maxsvEdit->setPlaceholderText("Bỏ trống nếu không đổi");
        huylopEdit->setPlaceholderText("Bỏ trống nếu không đổi");

        QPushButton *okButton = new QPushButton("OK", this);
        QPushButton *cancelButton = new QPushButton("Cancel", this);
        QHBoxLayout *buttonLayout = new QHBoxLayout();
        buttonLayout->addWidget(okButton);
        buttonLayout->addWidget(cancelButton);
        layout->addRow(buttonLayout);

        connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
        connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    }

    QString getMaLTC() { return mltcEdit->text(); }
    QString getMaMH() { return mamhEdit->text(); }
    QString getNienKhoa() { return nienkhoaEdit->text(); }
    QString getHocKy() { return hockyEdit->text(); }
    QString getNhom() { return nhomEdit->text(); }
    QString getMinSV() { return minsvEdit->text(); }
    QString getMaxSV() { return maxsvEdit->text(); }
    QString getHuyLop() { return huylopEdit->text(); }
};

class LopTCInputDialog : public QDialog {
public:
    QLineEdit *mamhEdit;
    QLineEdit *nienkhoaEdit;
    QSpinBox *hockySpin;
    QSpinBox *nhomSpin;

    LopTCInputDialog(const QString &title, QWidget *parent = nullptr) : QDialog(parent) {
        setWindowTitle(title);
        QFormLayout *layout = new QFormLayout(this);

        mamhEdit = new QLineEdit(this);
        nienkhoaEdit = new QLineEdit(this);
        hockySpin = new QSpinBox(this);
        hockySpin->setRange(1, 10);
        nhomSpin = new QSpinBox(this);
        nhomSpin->setRange(1, 10);

        layout->addRow("Mã MH:", mamhEdit);
        layout->addRow("Niên khóa:", nienkhoaEdit);
        layout->addRow("Học kỳ:", hockySpin);
        layout->addRow("Nhóm:", nhomSpin);

        QPushButton *okButton = new QPushButton("OK", this);
        QPushButton *cancelButton = new QPushButton("Cancel", this);
        QHBoxLayout *buttonLayout = new QHBoxLayout();
        buttonLayout->addWidget(okButton);
        buttonLayout->addWidget(cancelButton);
        layout->addRow(buttonLayout);

        connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
        connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    }

    QString getMaMH() { return mamhEdit->text(); }
    QString getNienKhoa() { return nienkhoaEdit->text(); }
    int getHocKy() { return hockySpin->value(); }
    int getNhom() { return nhomSpin->value(); }
};

// Custom dialog for class input (malop)
class MalopInputDialog : public QDialog {
public:
    QLineEdit *malopEdit;

    MalopInputDialog(const QString &title, QWidget *parent = nullptr) : QDialog(parent) {
        setWindowTitle(title);
        QFormLayout *layout = new QFormLayout(this);

        malopEdit = new QLineEdit(this);
        layout->addRow("Mã lớp:", malopEdit);

        QPushButton *okButton = new QPushButton("OK", this);
        QPushButton *cancelButton = new QPushButton("Cancel", this);
        QHBoxLayout *buttonLayout = new QHBoxLayout();
        buttonLayout->addWidget(okButton);
        buttonLayout->addWidget(cancelButton);
        layout->addRow(buttonLayout);

        connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
        connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    }

    QString getMaLop() { return malopEdit->text(); }
};



void MainWindow::refreshLopSVTable()
{
    ui->lopSVTableView->clear();
    ui->lopSVTableView->setRowCount(DSLSV.n);
    ui->lopSVTableView->setColumnCount(3);

    QStringList headers;
    headers << "Mã Lớp" << "Tên Lớp" << "SLSV";
    ui->lopSVTableView->setHorizontalHeaderLabels(headers);

    for (int i = 0; i < DSLSV.n; i++) {
        // Column 0 and 1 - editable
        ui->lopSVTableView->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(DSLSV.nodes[i].MALOP)));
        ui->lopSVTableView->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(DSLSV.nodes[i].TENLOP)));

        // Column 2 (SLSV) - read-only
        QTableWidgetItem *slsvItem = new QTableWidgetItem(QString::number(DSLSV.nodes[i].SLSV));
        slsvItem->setFlags(slsvItem->flags() & ~Qt::ItemIsEditable);
        ui->lopSVTableView->setItem(i, 2, slsvItem);
    }

    ui->lopSVTableView->resizeColumnsToContents();
    ui->lopSVTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->lopSVTableView->setEditTriggers(QAbstractItemView::DoubleClicked |
                                        QAbstractItemView::EditKeyPressed |
                                        QAbstractItemView::AnyKeyPressed);
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
    ui->monHocTableView->resizeColumnsToContents();
    ui->monHocTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
}

void MainWindow::refreshLopTCTable()
{
    isShowingScores = false;
    ui->editCreditClassButton->setEnabled(true);
    ui->enterScoresButton->setEnabled(false);
    ui->lopTCTableView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed | QAbstractItemView::AnyKeyPressed);
    ui->lopTCTableView->clear();
    ui->lopTCTableView->setRowCount(DSLTC.n);
    ui->lopTCTableView->setColumnCount(10);
    QStringList headers;
    headers << "Mã LTC" << "Mã MH" << "Tên MH" << "Niên Khóa" << "Học Kỳ" << "Nhóm" << "Min SV" << "Max SV" << "SLDK" << "Hủy";
    ui->lopTCTableView->setHorizontalHeaderLabels(headers);

    for (int i = 0; i < DSLTC.n; i++) {
        LopTC *ltc = DSLTC.nodes[i];

        // Editable columns
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

        // Column 8 (SLDK) - read-only
        QTableWidgetItem *sldkItem = new QTableWidgetItem(QString::number(ltc->SLSVDK));
        sldkItem->setFlags(sldkItem->flags() & ~Qt::ItemIsEditable);
        ui->lopTCTableView->setItem(i, 8, sldkItem);

        ui->lopTCTableView->setItem(i, 9, new QTableWidgetItem(ltc->HUYLOP ? "Yes" : "No"));
    }

    ui->lopTCTableView->resizeColumnsToContents();
    ui->lopTCTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
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
    ui->sinhVienTableView->resizeColumnsToContents();
    ui->sinhVienTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
}

// Tab lớp sinh viên  =======================================================================

void MainWindow::on_addClassButton_clicked()
{
    LopSVAddEditDialog dialog("Thêm Lớp SV", this);
    if (dialog.exec() != QDialog::Accepted) return;
    QString maLop = dialog.getMaLop();
    QString tenLop = dialog.getTenLop();
    std::string result = Them_LopSV(DSLSV, maLop.toStdString(), tenLop.toStdString());
    QMessageBox::information(this, "Kết Quả", QString::fromStdString(result));
    refreshLopSVTable();
}

void MainWindow::on_editClassButton_clicked() {
    if (isShowingStudentList) {
        QMessageBox::information(this, "Info", "Switch to class list view to edit classes.");
        return;
    }
    bool hasError = false;
    for (int row = 0; row < ui->lopSVTableView->rowCount(); ++row) {
        QString malopQ = ui->lopSVTableView->item(row, 0)->text();
        std::string malop = malopQ.toStdString();
        int idx = Tim_LopSV(DSLSV, malop);
        if (idx == -1) continue;
        QString newTenQ = ui->lopSVTableView->item(row, 1)->text().trimmed();
        std::string newTen = ChuanHoa_InputNangCao(newTenQ.toStdString(), 50, false, true);
        std::string error;
        if (newTen.empty()) {
            error = "Ten lop khong duoc rong cho lop " + malop;
        }
        if (!error.empty()) {
            hasError = true;
            ui->lopSVTableView->item(row, 1)->setText(QString::fromStdString(DSLSV.nodes[idx].TENLOP));
            QMessageBox::warning(this, "Loi", QString::fromStdString(error));
            continue;
        }
        DSLSV.nodes[idx].TENLOP = newTen;
    }
    if (!hasError) {
        QMessageBox::information(this, "Thanh cong", "Da luu thay doi cho cac lop!");
    }
    refreshLopSVTable(); // Refresh to show updated if needed
}

void MainWindow::on_deleteClassButton_clicked()
{
    SingleInputDialog dialog("Xóa Lớp SV", "Nhập mã lớp cần xóa:", this);
    if (dialog.exec() != QDialog::Accepted) return;
    QString maLop = dialog.getInput();
    int confirm = QMessageBox::question(this, "Xác Nhận", "Bạn có chắc muốn xóa lớp này?");
    if (confirm != QMessageBox::Yes) return;
    std::string result = Xoa_LopSV(DSLSV, maLop.toStdString());
    QMessageBox::information(this, "Kết Quả", QString::fromStdString(result));
    refreshLopSVTable();
}

void MainWindow::on_listSortedStudentsButton_clicked()
{
    MalopInputDialog dialog("Danh Sách SV Sắp Xếp", this);
    if (dialog.exec() != QDialog::Accepted) return;
    QString maLop = dialog.getMaLop();
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
    ui->lopSVTableView->resizeColumnsToContents();
    ui->lopSVTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->lopSVTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}


void MainWindow::on_listClassesButton_clicked()
{
    isShowingStudentList = false;
    refreshLopSVTable();
}

void MainWindow::on_addStudentsButton_clicked()
{
    MalopInputDialog dialog("Thêm SV Vào Lớp", this);
    if (dialog.exec() != QDialog::Accepted) return;
    QString maLop = dialog.getMaLop();
    int idx = Tim_LopSV(DSLSV, maLop.toStdString());
    if (idx == -1) {
        QMessageBox::warning(this, "Lỗi", "Không tìm thấy lớp");
        return;
    }
    bool ok;
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
    MonHocAddEditDialog dialog("Thêm Môn Học", this);
    if (dialog.exec() != QDialog::Accepted) return;
    QString mamh = dialog.getMaMH();
    QString tenmh = dialog.getTenMH();
    QString stclt = dialog.getSTCLT();
    QString stcth = dialog.getSTCTH();
    string result = Them_MonHoc(DSMH, mamh.toStdString(), tenmh.toStdString(), stclt.toStdString(), stcth.toStdString());
    QMessageBox::information(this, "Kết Quả", QString::fromStdString(result));
    refreshMonHocTable();
}

void MainWindow::on_editSubjectButton_clicked() {
    bool hasError = false;
    for (int row = 0; row < ui->monHocTableView->rowCount(); ++row) {
        QString mamhQ = ui->monHocTableView->item(row, 0)->text();
        std::string mamh = mamhQ.toStdString();
        NodeMH *node = TimMH_MAMH(DSMH, mamh);
        if (!node) continue;
        QString newTenQ = ui->monHocTableView->item(row, 1)->text().trimmed();
        QString newSTCLTQ = ui->monHocTableView->item(row, 2)->text().trimmed();
        QString newSTCTHQ = ui->monHocTableView->item(row, 3)->text().trimmed();
        std::string newTen = ChuanHoa_InputNangCao(newTenQ.toStdString(), 50, false, true);
        std::string stcltS = newSTCLTQ.toStdString();
        std::string stcthS = newSTCTHQ.toStdString();
        std::string error;
        if (newTen.empty()) error += "Ten MH khong duoc rong! ";
        if (!isNumber(stcltS)) error += "STCLT phai la so! ";
        if (!isNumber(stcthS)) error += "STCTH phai la so! ";
        if (!error.empty()) {
            hasError = true;
            ui->monHocTableView->item(row, 1)->setText(QString::fromStdString(node->mh.TENMH));
            ui->monHocTableView->item(row, 2)->setText(QString::number(node->mh.STCLT));
            ui->monHocTableView->item(row, 3)->setText(QString::number(node->mh.STCTH));
            QMessageBox::warning(this, "Loi", QString::fromStdString(error + " cho MH " + mamh));
            continue;
        }
        node->mh.TENMH = newTen;
        node->mh.STCLT = std::stoi(stcltS);
        node->mh.STCTH = std::stoi(stcthS);
    }
    if (!hasError) {
        QMessageBox::information(this, "Thanh cong", "Da luu thay doi cho cac mon hoc!");
    }
    refreshMonHocTable();
    refreshLopTCTable(); // Since TENMH may change
}

void MainWindow::on_deleteSubjectButton_clicked()
{
    SingleInputDialog dialog("Xóa Môn Học", "Nhập mã MH cần xóa:", this);
    if (dialog.exec() != QDialog::Accepted) return;
    QString mamh = dialog.getInput();
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
    StudentAddEditDialog dialog("Thêm Sinh Viên", this);
    if (dialog.exec() != QDialog::Accepted) return;
    QString maLop = dialog.getMaLop();
    int idx = Tim_LopSV(DSLSV, maLop.toStdString());
    if (idx == -1) {
        QMessageBox::warning(this, "Lỗi", "Không tìm thấy lớp");
        return;
    }
    QString masv = dialog.getMaSV();
    if (masv.isEmpty()) return;
    if (SearchSV_MASV(DSLSV, masv.toStdString()) != NULL) {
        QMessageBox::warning(this, "Lỗi", "MASV đã tồn tại");
        return;
    }
    QString ho = dialog.getHo();
    QString ten = dialog.getTen();
    QString gioitinh = dialog.getGioiTinh();
    QString sdt = dialog.getSoDT();
    QString email = dialog.getEmail();
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
    bool hasError = false;
    for (int row = 0; row < ui->sinhVienTableView->rowCount(); ++row) {
        QString masvQ = ui->sinhVienTableView->item(row, 0)->text();
        std::string masv = masvQ.toStdString();
        PTRSV sv = SearchSV_MASV(DSLSV, masv);
        if (!sv) continue;
        QString newHoQ = ui->sinhVienTableView->item(row, 1)->text().trimmed();
        QString newTenQ = ui->sinhVienTableView->item(row, 2)->text().trimmed();
        QString newGtQ = ui->sinhVienTableView->item(row, 3)->text().trimmed();
        QString newSdtQ = ui->sinhVienTableView->item(row, 4)->text().trimmed();
        QString newEmailQ = ui->sinhVienTableView->item(row, 5)->text().trimmed();
        std::string newHo = ChuanHoa_InputNangCao(newHoQ.toStdString(), 50, false, true);
        std::string newTen = ChuanHoa_InputNangCao(newTenQ.toStdString(), 10, false, true);
        std::string newGt = ChuanHoa_InputNangCao(newGtQ.toStdString(), 3, false, true);
        std::string newSdt = ChuanHoa_Chuoi(newSdtQ.toStdString(), 10);
        std::string newEmail = ChuanHoa_Chuoi(newEmailQ.toStdString(), 50);
        std::string error;
        if (newHo.empty()) error += "Ho khong duoc rong! ";
        if (newTen.empty()) error += "Ten khong duoc rong! ";
        if (newGt != "Nam" && newGt != "Nu") error += "Gioi tinh phai la Nam hoac Nu! ";
        if (!KiemTra_SDT(newSdt)) error += "So dien thoai khong hop le! ";
        if (!KiemTra_Email(newEmail)) error += "Email khong hop le! ";
        if (!error.empty()) {
            hasError = true;
            ui->sinhVienTableView->item(row, 1)->setText(QString::fromStdString(sv->sv.HO));
            ui->sinhVienTableView->item(row, 2)->setText(QString::fromStdString(sv->sv.TEN));
            ui->sinhVienTableView->item(row, 3)->setText(QString::fromStdString(sv->sv.GIOITINH));
            ui->sinhVienTableView->item(row, 4)->setText(QString::fromStdString(sv->sv.SODT));
            ui->sinhVienTableView->item(row, 5)->setText(QString::fromStdString(sv->sv.EMAIL));
            QMessageBox::warning(this, "Loi", QString::fromStdString(error + " cho SV " + masv));
            continue;
        }
        sv->sv.HO = newHo;
        sv->sv.TEN = newTen;
        sv->sv.GIOITINH = newGt;
        sv->sv.SODT = newSdt;
        sv->sv.EMAIL = newEmail;
    }
    if (!hasError) {
        QMessageBox::information(this, "Thanh cong", "Da luu thay doi cho cac sinh vien!");
    }
    refreshSinhVienTable();
    // Optionally refresh lopSVTableView if isShowingStudentList
    if (isShowingStudentList) refreshLopSVTable();
}

void MainWindow::on_deleteStudentButton_clicked()
{
    SingleInputDialog dialog("Xóa Sinh Viên", "Nhập MASV cần xóa:", this);
    if (dialog.exec() != QDialog::Accepted) return;
    QString masv = dialog.getInput();
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
    LopTCAddDialog dialog("Thêm Lớp TC", this);
    if (dialog.exec() != QDialog::Accepted) return;
    QString mamh = dialog.getMaMH();
    QString nienkhoa = dialog.getNienKhoa();
    QString hocky_str = dialog.getHocKy();
    int hocky = hocky_str.toInt();
    QString nhom_str = dialog.getNhom();
    int nhom = nhom_str.toInt();
    QString minsv_str = dialog.getMinSV();
    int minsv = minsv_str.toInt();
    QString maxsv_str = dialog.getMaxSV();
    int maxsv = maxsv_str.toInt();
    string result = Them_LopTC(DSLTC, DSMH, mamh.toStdString(), nienkhoa.toStdString(), hocky, nhom, minsv, maxsv);
    QMessageBox::information(this, "Kết Quả", QString::fromStdString(result));
    refreshLopTCTable();
}

void MainWindow::on_editCreditClassButton_clicked()
{
    bool hasError = false;
    for (int row = 0; row < ui->lopTCTableView->rowCount(); ++row) {
        QString mltcQ = ui->lopTCTableView->item(row, 0)->text();
        int mltc = mltcQ.toInt();
        LopTC *ltc = SearchLopTC_MALTC(DSLTC, mltc);
        if (!ltc) continue;

        // Get all field values from the table
        QString newMamhQ = ui->lopTCTableView->item(row, 1)->text().trimmed();
        QString newNkQ = ui->lopTCTableView->item(row, 3)->text().trimmed();
        QString newHkQ = ui->lopTCTableView->item(row, 4)->text().trimmed();
        QString newNhomQ = ui->lopTCTableView->item(row, 5)->text().trimmed();
        QString newMinQ = ui->lopTCTableView->item(row, 6)->text().trimmed();
        QString newMaxQ = ui->lopTCTableView->item(row, 7)->text().trimmed();
        QString newHuyQ = ui->lopTCTableView->item(row, 9)->text().trimmed();

        // Process the values
        std::string newMamh = ChuanHoa_InputNangCao(newMamhQ.toStdString(), 10, true, false);
        std::string newNk = ChuanHoa_Chuoi(newNkQ.toStdString(), 9);
        std::string newHkS = newHkQ.toStdString();
        std::string newNhomS = newNhomQ.toStdString();
        std::string newMinS = newMinQ.toStdString();
        std::string newMaxS = newMaxQ.toStdString();
        std::string newHuyLow = newHuyQ.toLower().toStdString();
        bool newHuy = (newHuyLow == "yes");

        std::string error;

        // Validate MAMH
        if (newMamh.empty() || !KiemTra_ChuaChuVaSo(newMamh)) {
            error += "Ma MH khong hop le! ";
        } else if (Search_MH(DSMH, newMamh) == NULL) {
            error += "Mon hoc khong ton tai! ";
        }

        // Validate HOCKY
        if (!isNumber(newHkS)) {
            error += "Hoc ky phai la so! ";
        } else {
            int val = std::stoi(newHkS);
            if (val < 1 || val > 10) error += "Hoc ky tu 1 den 10! ";
        }

        // Validate NHOM
        if (!isNumber(newNhomS)) {
            error += "Nhom phai la so! ";
        } else {
            int val = std::stoi(newNhomS);
            if (val < 1) error += "Nhom phai lon hon 0! ";
        }

        // Validate MinSV
        int minValue = 0;
        if (!isNumber(newMinS)) {
            error += "MinSV phai la so! ";
        } else {
            minValue = std::stoi(newMinS);
            if (minValue < 1) error += "MinSV phai lon hon 0! ";
        }

        // Validate MaxSV
        if (!isNumber(newMaxS)) {
            error += "MaxSV phai la so! ";
        } else {
            int maxValue = std::stoi(newMaxS);
            // Only check MinSV vs MaxSV if MinSV is valid
            if (isNumber(newMinS) && maxValue < minValue) {
                error += "MaxSV phai >= MinSV! ";
            }
        }

        // Validate HUYLOP
        if (newHuyLow != "yes" && newHuyLow != "no") {
            error += "Huy lop phai la Yes hoac No! ";
        }

        // If there's an error, revert to original values and show error
        if (!error.empty()) {
            hasError = true;
            ui->lopTCTableView->item(row, 1)->setText(QString::fromStdString(ltc->MAMH));
            ui->lopTCTableView->item(row, 3)->setText(QString::fromStdString(ltc->NIENKHOA));
            ui->lopTCTableView->item(row, 4)->setText(QString::number(ltc->HOCKY));
            ui->lopTCTableView->item(row, 5)->setText(QString::number(ltc->NHOM));
            ui->lopTCTableView->item(row, 6)->setText(QString::number(ltc->MINSV));
            ui->lopTCTableView->item(row, 7)->setText(QString::number(ltc->MAXSV));
            ui->lopTCTableView->item(row, 9)->setText(ltc->HUYLOP ? "Yes" : "No");
            QMessageBox::warning(this, "Loi", QString::fromStdString(error + " cho LTC " + std::to_string(mltc)));
            continue;
        }

        // Update the LopTC object with new values
        ltc->MAMH = newMamh;
        ltc->NIENKHOA = newNk;
        ltc->HOCKY = std::stoi(newHkS);
        ltc->NHOM = std::stoi(newNhomS);
        ltc->MINSV = std::stoi(newMinS);
        ltc->MAXSV = std::stoi(newMaxS);
        ltc->HUYLOP = newHuy;
    }

    if (!hasError) {
        QMessageBox::information(this, "Thanh cong", "Da luu thay doi cho cac lop TC!");
    }

    refreshLopTCTable();
}

void MainWindow::on_deleteCreditClassButton_clicked()
{
    SingleInputDialog dialog("Xóa Lớp TC", "Nhập mã LTC cần xóa:", this);
    if (dialog.exec() != QDialog::Accepted) return;
    QString mltc_str = dialog.getInput();
    int mltc = mltc_str.toInt();
    int confirm = QMessageBox::question(this, "Xác Nhận", "Bạn có chắc muốn xóa lớp TC này?");
    if (confirm != QMessageBox::Yes) return;
    string result = Xoa_LopTC(DSLTC, mltc, true);
    QMessageBox::information(this, "Kết Quả", QString::fromStdString(result));
    refreshLopTCTable();
}

class RegisterDialog : public QDialog {
public:
    QLineEdit *masvEdit;
    QLabel *studentInfoLabel;
    QLineEdit *nienkhoaEdit;
    QSpinBox *hockySpin;
    QLineEdit *mamhEdit;
    QSpinBox *nhomSpin;

    RegisterDialog(DSLopSV &DSLSV, QWidget *parent = nullptr) : QDialog(parent), m_DSLSV(DSLSV) {
        setWindowTitle("Đăng Ký Lớp TC");
        QFormLayout *layout = new QFormLayout(this);

        masvEdit = new QLineEdit(this);
        studentInfoLabel = new QLabel(this);
        studentInfoLabel->setWordWrap(true);
        nienkhoaEdit = new QLineEdit(this);
        hockySpin = new QSpinBox(this);
        hockySpin->setRange(1, 10);
        mamhEdit = new QLineEdit(this);
        nhomSpin = new QSpinBox(this);
        nhomSpin->setRange(1, 10);

        layout->addRow("Mã SV:", masvEdit);
        layout->addRow("Thông tin SV:", studentInfoLabel);
        layout->addRow("Niên khóa:", nienkhoaEdit);
        layout->addRow("Học kỳ:", hockySpin);
        layout->addRow("Mã MH:", mamhEdit);
        layout->addRow("Nhóm:", nhomSpin);

        QPushButton *okButton = new QPushButton("OK", this);
        QPushButton *cancelButton = new QPushButton("Cancel", this);
        QHBoxLayout *buttonLayout = new QHBoxLayout();
        buttonLayout->addWidget(okButton);
        buttonLayout->addWidget(cancelButton);
        layout->addRow(buttonLayout);

        connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
        connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
        connect(masvEdit, &QLineEdit::textChanged, this, &RegisterDialog::updateStudentInfo);
    }

    QString getMaSV() { return masvEdit->text(); }
    QString getNienKhoa() { return nienkhoaEdit->text(); }
    int getHocKy() { return hockySpin->value(); }
    QString getMaMH() { return mamhEdit->text(); }
    int getNhom() { return nhomSpin->value(); }

private:
    DSLopSV &m_DSLSV;

    void updateStudentInfo(const QString &masv) {
        PTRSV sv = SearchSV_MASV(m_DSLSV, masv.toStdString());
        if (sv) {
            QString info = QString("Họ: %1\nTên: %2\nGiới tính: %3\nSĐT: %4\nEmail: %5")
                               .arg(QString::fromStdString(sv->sv.HO))
                               .arg(QString::fromStdString(sv->sv.TEN))
                               .arg(QString::fromStdString(sv->sv.GIOITINH))
                               .arg(QString::fromStdString(sv->sv.SODT))
                               .arg(QString::fromStdString(sv->sv.EMAIL));
            studentInfoLabel->setText(info);
        } else {
            studentInfoLabel->setText("Không tìm thấy sinh viên");
        }
    }
};

void MainWindow::on_registerStudentButton_clicked()
{
    RegisterDialog dialog(DSLSV, this);
    if (dialog.exec() != QDialog::Accepted) return;

    QString masv = dialog.getMaSV();
    QString nienkhoa = dialog.getNienKhoa();
    int hocky = dialog.getHocKy();
    QString mamh = dialog.getMaMH();
    int nhom = dialog.getNhom();

    std::string result = DangKy_LopTC(DSLTC, DSMH, DSLSV, masv.toStdString(), nienkhoa.toStdString(), hocky, mamh.toStdString(), nhom);
    QMessageBox::information(this, "Kết Quả", QString::fromStdString(result));
    refreshLopTCTable(); // Refresh to update SLSVDK if needed
}

void MainWindow::on_enterScoresButton_clicked()
{
    if (!isShowingScores) {
        QMessageBox::warning(this, "Lỗi", "Vui lòng chọn lớp TC trước để nhập điểm.");
        return;
    }

    // Collect scores from the table
    int rowCount = ui->lopTCTableView->rowCount();
    CustomPair *diem_list = new CustomPair[rowCount];
    int diem_size = 0;
    bool valid = true;

    for (int row = 0; row < rowCount; ++row) {
        QTableWidgetItem *masvItem = ui->lopTCTableView->item(row, 0); // column 0 for MASV
        QTableWidgetItem *diemItem = ui->lopTCTableView->item(row, 6); // column 6 for DIEM (now last column)

        if (masvItem && diemItem) {
            std::string masv = masvItem->text().toStdString();
            QString diemStr = diemItem->text();
            bool ok;
            float diem = diemStr.toFloat(&ok);

            if (!ok || diem < 0 || diem > 10) {
                QMessageBox::warning(this, "Lỗi", QString("Điểm không hợp lệ tại dòng %1 (MASV: %2). Điểm phải từ 0-10.")
                                                      .arg(row + 1).arg(QString::fromStdString(masv)));
                valid = false;
                break;
            }

            diem_list[diem_size].masv = masv;
            diem_list[diem_size].diem = diem;
            diem_size++;
        }
    }

    if (!valid) {
        delete[] diem_list;
        return;
    }

    // Save to database using NhapDiem_LopTC
    std::string result = NhapDiem_LopTC(DSLTC, DSMH, DSLSV, current_mamh, current_nienkhoa, current_hocky, current_nhom, diem_list, diem_size);
    QMessageBox::information(this, "Kết Quả", QString::fromStdString(result));
    delete[] diem_list;

    // Refresh the table after saving - just update the scores column
    refreshScoresInTable();
}

void MainWindow::on_listRegisteredStudentsButton_clicked()
{
    ui->editCreditClassButton->setEnabled(false);
    ui->enterScoresButton->setEnabled(false);

    LopTCInputDialog dialog("Danh Sách SV ĐK Lớp TC", this);
    if (dialog.exec() != QDialog::Accepted) return;

    QString mamh = dialog.getMaMH();
    QString nienkhoa = dialog.getNienKhoa();
    int hocky = dialog.getHocKy();
    int nhom = dialog.getNhom();

    LopTC *ltc = SearchLopTC(DSLTC, mamh.toStdString(), nienkhoa.toStdString(), hocky, nhom);
    if (!ltc) {
        QMessageBox::warning(this, "Lỗi", "Không tìm thấy lớp TC");
        return;
    }

    // Store current identifiers for later use in saving scores
    current_mamh = mamh.toStdString();
    current_nienkhoa = nienkhoa.toStdString();
    current_hocky = hocky;
    current_nhom = nhom;

    // Set flag to enable score entry
    isShowingScores = true;
    ui->enterScoresButton->setEnabled(true);

    // Clear and set up lopTCTableView for registered students with scores
    ui->lopTCTableView->clear();
    ui->lopTCTableView->setRowCount(0);
    ui->lopTCTableView->setColumnCount(7); // Added one more column for DIEM
    QStringList headers = {"MASV", "Họ", "Tên", "Giới Tính", "SĐT", "Email", "ĐIỂM"};
    ui->lopTCTableView->setHorizontalHeaderLabels(headers);

    // Get existing scores for this class
    CustomPair *existingScores = nullptr;
    int existingScoresSize = 0;

    std::string scoresResult = InBangDiem_LopTC(DSLTC, DSMH, DSLSV, current_mamh, current_nienkhoa, current_hocky, current_nhom);

    // Parse existing scores if available
    if (scoresResult.find("Khong ton tai") == std::string::npos) {
        QStringList lines = QString::fromStdString(scoresResult).split("\n");
        bool dataStarted = false;

        // Count valid score lines first
        int scoreCount = 0;
        for (const QString &line : lines) {
            if (line.contains("STT")) {
                dataStarted = true;
                continue;
            }
            if (dataStarted && !line.trimmed().isEmpty() && !line.contains("---")) {
                QStringList parts = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
                if (parts.size() >= 4) {
                    scoreCount++;
                }
            }
        }

        // Allocate array for existing scores
        if (scoreCount > 0) {
            existingScores = new CustomPair[scoreCount];
            existingScoresSize = 0;
            dataStarted = false;

            for (const QString &line : lines) {
                if (line.contains("STT")) {
                    dataStarted = true;
                    continue;
                }

                if (dataStarted && !line.trimmed().isEmpty() && !line.contains("---")) {
                    QStringList parts = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
                    if (parts.size() >= 4) {
                        std::string masv = parts[1].toStdString();
                        QString diemStr = parts.last();
                        bool ok;
                        float diem = diemStr.toFloat(&ok);
                        if (ok) {
                            existingScores[existingScoresSize].masv = masv;
                            existingScores[existingScoresSize].diem = diem;
                            existingScoresSize++;
                        }
                    }
                }
            }
        }
    }

    // Helper function to find score by MASV
    auto findScore = [existingScores, existingScoresSize](const std::string& masv) -> float {
        for (int i = 0; i < existingScoresSize; i++) {
            if (existingScores[i].masv == masv) {
                return existingScores[i].diem;
            }
        }
        return -1.0f; // Not found
    };

    // Populate table with student info and scores
    int row = 0;
    PTRDK p = ltc->DSDK;
    while (p) {
        PTRSV sv = SearchSV_MASV(DSLSV, p->dk.MASV);
        if (sv) {
            ui->lopTCTableView->insertRow(row);

            // MASV (non-editable)
            QTableWidgetItem *masvItem = new QTableWidgetItem(QString::fromStdString(sv->sv.MASV));
            masvItem->setFlags(masvItem->flags() & ~Qt::ItemIsEditable);
            ui->lopTCTableView->setItem(row, 0, masvItem);

            // HO (non-editable)
            QTableWidgetItem *hoItem = new QTableWidgetItem(QString::fromStdString(sv->sv.HO));
            hoItem->setFlags(hoItem->flags() & ~Qt::ItemIsEditable);
            ui->lopTCTableView->setItem(row, 1, hoItem);

            // TEN (non-editable)
            QTableWidgetItem *tenItem = new QTableWidgetItem(QString::fromStdString(sv->sv.TEN));
            tenItem->setFlags(tenItem->flags() & ~Qt::ItemIsEditable);
            ui->lopTCTableView->setItem(row, 2, tenItem);

            // GIOITINH (non-editable)
            QTableWidgetItem *gioitinhItem = new QTableWidgetItem(QString::fromStdString(sv->sv.GIOITINH));
            gioitinhItem->setFlags(gioitinhItem->flags() & ~Qt::ItemIsEditable);
            ui->lopTCTableView->setItem(row, 3, gioitinhItem);

            // SODT (non-editable)
            QTableWidgetItem *sodtItem = new QTableWidgetItem(QString::fromStdString(sv->sv.SODT));
            sodtItem->setFlags(sodtItem->flags() & ~Qt::ItemIsEditable);
            ui->lopTCTableView->setItem(row, 4, sodtItem);

            // EMAIL (non-editable)
            QTableWidgetItem *emailItem = new QTableWidgetItem(QString::fromStdString(sv->sv.EMAIL));
            emailItem->setFlags(emailItem->flags() & ~Qt::ItemIsEditable);
            ui->lopTCTableView->setItem(row, 5, emailItem);

            // DIEM (editable)
            QString diemText = "";
            float existingScore = findScore(sv->sv.MASV);
            if (existingScore >= 0) {
                diemText = QString::number(existingScore);
            }
            QTableWidgetItem *diemItem = new QTableWidgetItem(diemText);
            diemItem->setFlags(diemItem->flags() | Qt::ItemIsEditable);
            ui->lopTCTableView->setItem(row, 6, diemItem);

            row++;
        }
        p = p->next;
    }

    // Clean up allocated memory
    if (existingScores) {
        delete[] existingScores;
    }

    // Set table properties
    ui->lopTCTableView->resizeColumnsToContents();
    ui->lopTCTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->lopTCTableView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed | QAbstractItemView::AnyKeyPressed);
}

void MainWindow::refreshScoresInTable()
{
    // Get updated scores
    std::string scoresResult = InBangDiem_LopTC(DSLTC, DSMH, DSLSV, current_mamh, current_nienkhoa, current_hocky, current_nhom);

    if (scoresResult.find("Khong ton tai") != std::string::npos) {
        return; // No scores to update
    }

    // Parse updated scores
    QStringList lines = QString::fromStdString(scoresResult).split("\n");
    bool dataStarted = false;

    // Count valid score lines first
    int scoreCount = 0;
    for (const QString &line : lines) {
        if (line.contains("STT")) {
            dataStarted = true;
            continue;
        }
        if (dataStarted && !line.trimmed().isEmpty() && !line.contains("---")) {
            QStringList parts = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
            if (parts.size() >= 4) {
                scoreCount++;
            }
        }
    }

    // Allocate array for updated scores
    CustomPair *updatedScores = nullptr;
    int updatedScoresSize = 0;

    if (scoreCount > 0) {
        updatedScores = new CustomPair[scoreCount];
        updatedScoresSize = 0;
        dataStarted = false;

        for (const QString &line : lines) {
            if (line.contains("STT")) {
                dataStarted = true;
                continue;
            }

            if (dataStarted && !line.trimmed().isEmpty() && !line.contains("---")) {
                QStringList parts = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
                if (parts.size() >= 4) {
                    std::string masv = parts[1].toStdString();
                    QString diemStr = parts.last();
                    bool ok;
                    float diem = diemStr.toFloat(&ok);
                    if (ok) {
                        updatedScores[updatedScoresSize].masv = masv;
                        updatedScores[updatedScoresSize].diem = diem;
                        updatedScoresSize++;
                    }
                }
            }
        }
    }

    // Helper function to find score by MASV
    auto findUpdatedScore = [updatedScores, updatedScoresSize](const std::string& masv) -> float {
        for (int i = 0; i < updatedScoresSize; i++) {
            if (updatedScores[i].masv == masv) {
                return updatedScores[i].diem;
            }
        }
        return -1.0f; // Not found
    };

    // Update the DIEM column in the table
    int rowCount = ui->lopTCTableView->rowCount();
    for (int row = 0; row < rowCount; ++row) {
        QTableWidgetItem *masvItem = ui->lopTCTableView->item(row, 0);
        if (masvItem) {
            std::string masv = masvItem->text().toStdString();
            float updatedScore = findUpdatedScore(masv);
            if (updatedScore >= 0) {
                QTableWidgetItem *diemItem = ui->lopTCTableView->item(row, 6);
                if (diemItem) {
                    diemItem->setText(QString::number(updatedScore));
                }
            }
        }
    }

    // Clean up allocated memory
    if (updatedScores) {
        delete[] updatedScores;
    }
}

// void MainWindow::on_printScoresButton_clicked()
// {
//     ui->editCreditClassButton->setEnabled(false);
//     ui->enterScoresButton->setEnabled(true);

//     LopTCInputDialog dialog("In Bảng Điểm Lớp TC", this);
//     if (dialog.exec() != QDialog::Accepted) return;

//     std::string mamh = dialog.getMaMH().toStdString();
//     std::string nienkhoa = dialog.getNienKhoa().toStdString();
//     int hocky = dialog.getHocKy();
//     int nhom = dialog.getNhom();

//     // Store current identifiers for later use in saving
//     current_mamh = mamh;
//     current_nienkhoa = nienkhoa;
//     current_hocky = hocky;
//     current_nhom = nhom;

//     // Set flag
//     isShowingScores = true;

//     // Populate the table
//     populateScoresTable();
// }

void MainWindow::on_printAvgScoresButton_clicked()
{
    MalopInputDialog dialog("In ĐTB Lớp SV", this);
    if (dialog.exec() != QDialog::Accepted) return;

    QString malop = dialog.getMaLop();
    int idx = Tim_LopSV(DSLSV, malop.toStdString());
    if (idx == -1) {
        QMessageBox::warning(this, "Lỗi", "Không tìm thấy lớp");
        return;
    }

    // Clear and set up lopTCTableView for avg scores
    ui->lopTCTableView->clear();
    ui->lopTCTableView->setRowCount(0);
    ui->lopTCTableView->setColumnCount(4);
    QStringList headers = {"MASV", "Họ", "Tên", "ĐTB"};
    ui->lopTCTableView->setHorizontalHeaderLabels(headers);

    int row = 0;
    PTRSV p = DSLSV.nodes[idx].FirstSV;
    while (p) {
        float dtb = TinhDiemTrungBinh(p->sv.MASV, DSLTC, DSMH);
        ui->lopTCTableView->insertRow(row);
        ui->lopTCTableView->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(p->sv.MASV)));
        ui->lopTCTableView->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(p->sv.HO)));
        ui->lopTCTableView->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(p->sv.TEN)));
        ui->lopTCTableView->setItem(row, 3, new QTableWidgetItem(QString::number(dtb, 'f', 2)));
        row++;
        p = p->next;
    }
    ui->lopTCTableView->resizeColumnsToContents();
    ui->lopTCTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->lopTCTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

// For on_printTotalScoresButton_clicked (Điểm Tổng Kết Lớp SV)
void MainWindow::on_printTotalScoresButton_clicked()
{
    MalopInputDialog dialog("In Điểm Tổng Kết Lớp SV", this);
    if (dialog.exec() != QDialog::Accepted) return;
    QString malop = dialog.getMaLop();
    int idx = Tim_LopSV(DSLSV, malop.toStdString());
    if (idx == -1) {
        QMessageBox::warning(this, "Lỗi", "Không tìm thấy lớp");
        return;
    }
    string danhSachMaMH[MAX_LOPTC];
    int numMH = 0;
    for (int j = 0; j < DSLTC.n; j++) {
        if (DSLTC.nodes[j] && !DSLTC.nodes[j]->HUYLOP) {
            string mamh = DSLTC.nodes[j]->MAMH;
            bool exists = false;
            for (int k = 0; k < numMH; k++) {
                if (danhSachMaMH[k] == mamh) {
                    exists = true;
                    break;
                }
            }
            if (!exists) {
                danhSachMaMH[numMH++] = mamh;
            }
        }
    }
    ui->lopTCTableView->clear();
    ui->lopTCTableView->setRowCount(0);
    int colCount = 3 + numMH; // MASV, HO, TEN + each MH
    ui->lopTCTableView->setColumnCount(colCount);
    QStringList headers = {"MASV", "Họ", "Tên"};
    for (int k = 0; k < numMH; k++) {
        headers << QString::fromStdString(danhSachMaMH[k]);
    }
    ui->lopTCTableView->setHorizontalHeaderLabels(headers);
    int row = 0;
    PTRSV p = DSLSV.nodes[idx].FirstSV;
    while (p) {
        ui->lopTCTableView->insertRow(row);
        ui->lopTCTableView->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(p->sv.MASV)));
        ui->lopTCTableView->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(p->sv.HO)));
        ui->lopTCTableView->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(p->sv.TEN)));
        for (int k = 0; k < numMH; ++k) {
            float diem = -1;
            bool timThay = false;
            for (int j = 0; j < DSLTC.n; j++) {
                if (DSLTC.nodes[j] && !DSLTC.nodes[j]->HUYLOP && DSLTC.nodes[j]->MAMH == danhSachMaMH[k]) {
                    PTRDK dk = DSLTC.nodes[j]->DSDK;
                    while (dk) {
                        if (dk->dk.MASV == p->sv.MASV) {
                            diem = dk->dk.DIEM;
                            timThay = true;
                            break;
                        }
                        dk = dk->next;
                    }
                    if (timThay) break;
                }
            }
            QString diemStr = (timThay && diem >= 0) ? QString::number(diem, 'f', 0) : "";
            ui->lopTCTableView->setItem(row, 3 + k, new QTableWidgetItem(diemStr));
        }
        row++;
        p = p->next;
    }
    ui->lopTCTableView->resizeColumnsToContents();
    ui->lopTCTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->lopTCTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}


void MainWindow::on_lopSVSearchLineEdit_textChanged(const QString &arg1)
{
    // Set placeholder text based on current view
    if (isShowingStudentList) {
        ui->lopSVSearchLineEdit->setPlaceholderText("Tìm kiếm theo MASV, Họ, Tên hoặc Họ Tên...");
    } else {
        ui->lopSVSearchLineEdit->setPlaceholderText("Tìm kiếm theo Mã Lớp, Tên Lớp...");
    }

    QString search = arg1.toLower().trimmed();
    for (int row = 0; row < ui->lopSVTableView->rowCount(); row++) {
        bool match = false;
        if (isShowingStudentList) {
            // When showing student list: search in MASV (col 1), Họ (col 2), and Tên (col 3)

            // Check MASV first
            if (ui->lopSVTableView->item(row, 1) &&
                ui->lopSVTableView->item(row, 1)->text().toLower().contains(search)) {
                match = true;
            }

            // Check individual columns (Họ, Tên)
            if (!match) {
                for (int col = 2; col <= 3; col++) {
                    if (ui->lopSVTableView->item(row, col) &&
                        ui->lopSVTableView->item(row, col)->text().toLower().contains(search)) {
                        match = true;
                        break;
                    }
                }
            }

            // Check combined full name (Họ + Tên)
            if (!match && ui->lopSVTableView->item(row, 2) && ui->lopSVTableView->item(row, 3)) {
                QString fullName = (ui->lopSVTableView->item(row, 2)->text() + " " +
                                    ui->lopSVTableView->item(row, 3)->text()).toLower();
                if (fullName.contains(search)) {
                    match = true;
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
    ui->monHocSearchLineEdit->setPlaceholderText("Tìm kiếm theo Mã MH, Tên MH...");

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
    ui->sinhVienSearchLineEdit->setPlaceholderText("Tìm kiếm theo Mã SV, Họ, Tên hoặc Họ Tên...");

    QString search = arg1.toLower().trimmed();
    for (int row = 0; row < ui->sinhVienTableView->rowCount(); row++) {
        bool match = false;

        // Check Mã SV first
        if (ui->sinhVienTableView->item(row, 0) &&
            ui->sinhVienTableView->item(row, 0)->text().toLower().contains(search)) {
            match = true;
        }

        // Check individual columns (Họ, Tên)
        if (!match) {
            for (int col = 1; col <= 2; col++) {
                if (ui->sinhVienTableView->item(row, col) &&
                    ui->sinhVienTableView->item(row, col)->text().toLower().contains(search)) {
                    match = true;
                    break;
                }
            }
        }

        // Check combined full name (Họ + Tên)
        if (!match && ui->sinhVienTableView->item(row, 1) && ui->sinhVienTableView->item(row, 2)) {
            QString fullName = (ui->sinhVienTableView->item(row, 1)->text() + " " +
                                ui->sinhVienTableView->item(row, 2)->text()).toLower();
            if (fullName.contains(search)) {
                match = true;
            }
        }

        ui->sinhVienTableView->setRowHidden(row, !match);
    }
}

void MainWindow::on_lopTCSearchLineEdit_textChanged(const QString &arg1)
{
    ui->lopTCSearchLineEdit->setPlaceholderText("Tìm kiếm theo Mã LTC, Mã MH, Tên MH...");

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










void MainWindow::on_disableCreditClassButton_clicked()
{
    LopTCInputDialog dialog("Hủy Lớp TC", this);
    if (dialog.exec() != QDialog::Accepted) return;
    QString mamh = dialog.getMaMH();
    QString nienkhoa = dialog.getNienKhoa();
    int hocky = dialog.getHocKy();
    int nhom = dialog.getNhom();
    LopTC *ltc = SearchLopTC(DSLTC, mamh.toStdString(), nienkhoa.toStdString(), hocky, nhom);
    if (!ltc) {
        QMessageBox::warning(this, "Lỗi", "Không tìm thấy lớp TC");
        return;
    }
    int confirm = QMessageBox::question(this, "Xác Nhận", "Bạn có chắc muốn hủy lớp này?");
    if (confirm != QMessageBox::Yes) return;
    ltc->HUYLOP = true;
    refreshLopTCTable();
    QMessageBox::information(this, "Kết Quả", "Đã hủy lớp thành công");
}


void MainWindow::on_printCreditClassButton_clicked()
{
    refreshLopTCTable();
}


