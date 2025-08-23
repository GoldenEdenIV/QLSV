#ifndef QLDSV_TC_H
#define QLDSV_TC_H

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <conio.h>

using namespace std;

const int MAX_LOPSV = 500;
const int MAX_LOPTC = 10000;

struct MonHoc
{
    string MAMH;
    string TENMH;
    int STCLT;
    int STCTH;
};

struct NodeMH
{
    MonHoc mh;
    NodeMH *left;
    NodeMH *right;
};
typedef NodeMH *TreeMH;

struct SinhVien
{
    string MASV;
    string HO;
    string TEN;
    string GIOITINH;
    string SODT;
    string EMAIL;
};

struct NodeSV
{
    SinhVien sv;
    NodeSV *next;
};
typedef NodeSV *PTRSV;

struct LopSV
{
    string MALOP;
    string TENLOP;
    int SLSV = 0;
    PTRSV FirstSV = NULL;
};

struct DSLopSV
{
    int n = 0;
    int capacity = 100;
    LopSV *nodes;
    DSLopSV();
    ~DSLopSV();
};

struct DangKy
{
    string MASV;
    float DIEM = 0;
};

struct NodeDK
{
    DangKy dk;
    NodeDK *next;
};
typedef NodeDK *PTRDK;

struct LopTC
{
    int MALOPTC;
    string MAMH;
    string NIENKHOA;
    int HOCKY;
    int NHOM;
    int MINSV;
    int MAXSV;
    int SLSVDK = 0;
    bool HUYLOP = false;
    PTRDK DSDK = NULL;
};

struct DSLopTC
{
    int n = 0;
    LopTC *nodes[MAX_LOPTC];
};

struct CustomPair {
    string masv;
    float diem;
};

// Utility functions
string ChuanHoa_Chuoi(const string &chuoi, int dodai);
string ChuanHoa_InputNangCao(string chuoi, int dodai, bool toUpper = false, bool vietHoaDau = false);
bool KiemTra_SDT(string sdt);
bool KiemTra_Email(string email);
bool KiemTra_ChuaChuVaSo(string s);
bool isNumber(string s);

// MonHoc functions
void ChenNodeMH(TreeMH &DSMH, const MonHoc &mh);
NodeMH *TimMH_MAMH(TreeMH DSMH, string mamh);
TreeMH Search_MH(TreeMH root, string mamh);
TreeMH Insert_MH(TreeMH root, MonHoc mh);
string Them_MonHoc(TreeMH &DSMH, string mamh, string tenmh, string stclt, string stcth);
string HieuChinh_MonHoc(TreeMH &DSMH, string mamh, string tenmh_new, string stclt_new, string stcth_new);
NodeMH *TimMinMH(TreeMH DSMH);
string Xoa_MonHoc(TreeMH &DSMH, string mamh, bool confirm);
string SearchTenMH_MAMH(TreeMH &DSMH, string mamh);
struct DSMHArray {
    MonHoc *nodes;
    int n;
    int capacity;
    DSMHArray();
    ~DSMHArray();
    void Them(MonHoc mh);
};
void ThuThapMH(TreeMH DSMH, DSMHArray &arr);
string In_DSMH_SapXep(TreeMH DSMH);

// SinhVien functions
PTRSV SearchSV_MASV(DSLopSV &DSLSV, string msv);
string LietKe_DSSV(DSLopSV &DSLSV);

// LopSV functions
void Xoa_SV_LopSV(PTRSV &FirstSV);
int Tim_LopSV(DSLopSV &DSLSV, string malop);
void MoRong_DSLopSV(DSLopSV &DSLSV);
string Them_LopSV(DSLopSV &DSLSV, string malop, string tenlop);
string Xoa_LopSV(DSLopSV &DSLSV, string malop);
string HieuChinh_LopSV(DSLopSV &DSLSV, string malop, string tenlop_new);
bool KiemTra_SV(PTRSV FirstSV, string masv);
void Nhap_DSSV_TheoMSSV(PTRSV &FirstSV, int &SLSV, DSLopSV &DSLSV);
string Nhap_SV_Lop(DSLopSV &DSLSV, string malop);
string LietKe_LopSV(DSLopSV &DSLSV);
int SoSanh_Chuoi(const string &s1, const string &s2);
bool SoSanh_TenHo(const SinhVien &sv1, const SinhVien &sv2);
void SapXep_DSSV_TenHo(PTRSV &FirstSV);
string In_DSSV_Lop_SapXep(DSLopSV &DSLSV, string malop);

// LopTC functions
string Them_LopTC(DSLopTC &DSLTC, TreeMH &DSMH, string mamh, string nienkhoa, int hocky, int nhom, int minsv, int maxsv);
LopTC *SearchLopTC_MALTC(DSLopTC &DSLTC, int mltc);
string HieuChinh_LopTC(DSLopTC &DSLTC, int mltc, string mamh_new, string nienkhoa_new, int hocky_new, int nhom_new, int minsv_new, int maxsv_new, bool huylop_new);
string Xoa_LopTC(DSLopTC &DSLTC, int mltc, bool confirm);
string LietKe_LopTC(DSLopTC &DSLTC, TreeMH &DSMH, string nienkhoa, int hocky);
LopTC *SearchLopTC(DSLopTC &DSLTC, string mamh, string nienkhoa, int hocky, int nhom);
string InDSSV_LopTC(DSLopTC &DSLTC, DSLopSV &DSLSV, string mamh, string nienkhoa, int hocky, int nhom);
string DangKy_LopTC(DSLopTC &DSLTC, TreeMH &DSMH, DSLopSV &DSLSV, string masv, string nienkhoa, int hocky, string mamh, int nhom);
float TinhDiemTrungBinh(string masv, DSLopTC &DSLTC, TreeMH DSMH);
int SearchLopSV_MALOP(DSLopSV &DSLSV, string malop);
string InDTBLopSV_SoTC(DSLopSV &DSLSV, DSLopTC &DSLTC, TreeMH DSMH, string malop);
string NhapDiem_LopTC(DSLopTC &DSLTC, TreeMH &DSMH, DSLopSV &DSLSV, string mamh, string nienkhoa, int hocky, int nhom, CustomPair diem_list[], int diem_size);
string InDiemTongKet(DSLopSV &DSLSV, DSLopTC &DSLTC, string malop);
string InBangDiem_LopTC(DSLopTC &DSLTC, TreeMH &DSMH, DSLopSV &DSLSV, string mamh, string nienkhoa, int hocky, int nhom);

// File I/O functions
void DocFile_DSMH(TreeMH &DSMH);
void DocFile_DSLSV(DSLopSV &DSLSV);
void DocFile_DSLTC(DSLopTC &DSLTC);
string DocFile(TreeMH &DSMH, DSLopSV &DSLSV, DSLopTC &DSLTC);
int DemSoMonHoc(TreeMH DSMH);
void GhiDSMH_NLR(TreeMH DSMH, ofstream &out);
void GhiFile_DSMH(TreeMH &DSMH);
void GhiFile_DSLSV(DSLopSV &DSLSV);
void GhiFile_DSLTC(DSLopTC &DSLTC);
string GhiFile(TreeMH &DSMH, DSLopSV &DSLSV, DSLopTC &DSLTC);

#endif // QLDSV_TC_H
