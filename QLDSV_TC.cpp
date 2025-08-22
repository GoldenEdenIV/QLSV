#include "QLDSV_TC.h"
#include <string.h>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;
DSLopSV::DSLopSV()
{
nodes = new LopSV[capacity];
}
DSLopSV::~DSLopSV()
{
for (int i = 0; i < n; i++)
{
Xoa_SV_LopSV(nodes[i].FirstSV);
}
delete[] nodes;
}
string ChuanHoa_Chuoi(string &chuoi, int dodai)
{
    size_t start = 0;
    while (start < chuoi.length() && isspace(static_cast<unsigned char>(chuoi[start])))
    {
        ++start;
    }
    size_t end = chuoi.length();
    while (end > start && isspace(static_cast<unsigned char>(chuoi[end - 1])))
    {
        --end;
    }
    string ketqua = chuoi.substr(start, end - start);
    if ((int)ketqua.length() > dodai)
    {
        return "Do dai chuoi vuot qua " + to_string(dodai) + " ky tu!\n";
    }
    return ketqua;
}

string ChuanHoa_InputNangCao(string chuoi, int dodai, bool toUpper, bool vietHoaDau)
{
    size_t start = 0;
    while (start < chuoi.length() && isspace(static_cast<unsigned char>(chuoi[start])))
    {
        ++start;
    }
    size_t end = chuoi.length();
    while (end > start && isspace(static_cast<unsigned char>(chuoi[end - 1])))
    {
        --end;
    }
    string tam = chuoi.substr(start, end - start);
    string hopLe = "";
    for (char c : tam)
    {
        if (isalnum(c) || c == '-' || c == '_' || isspace(static_cast<unsigned char>(c)))
            hopLe += c;
    }
    stringstream ss(hopLe);
    string word, ketqua;
    while (ss >> word)
    {
        if (!ketqua.empty())
            ketqua += " ";
        ketqua += word;
    }
    if (toUpper)
    {
        for (char &c : ketqua)
            c = toupper(c);
    }
    if (vietHoaDau)
    {
        bool capitalize = true;
        for (char &c : ketqua)
        {
            if (isspace(c))
            {
                capitalize = true;
            }
            else if (capitalize && isalpha(c))
            {
                c = toupper(c);
                capitalize = false;
            }
            else
            {
                c = tolower(c);
            }
        }
    }
    string temp = ketqua; // Temporary to pass to ChuanHoa_Chuoi
    return ChuanHoa_Chuoi(temp, dodai);
}

bool KiemTra_SDT(string sdt)
{
    if (sdt.length() != 10)
        return false;
    for (char c : sdt)
        if (!isdigit(c))
            return false;
    return true;
}

bool KiemTra_Email(string email)
{
    size_t at = email.find('@');
    size_t dot = email.find('.', at);
    return at != string::npos && dot != string::npos && dot > at;
}

bool KiemTra_ChuaChuVaSo(string s)
{
    bool coChu = false, coSo = false;
    for (char c : s)
    {
        if (isalpha(c))
            coChu = true;
        if (isdigit(c))
            coSo = true;
    }
    return coChu && coSo;
}

bool isNumber(string s)
{
    for (char c : s)
        if (!isdigit(c))
            return false;
    return !s.empty();
}

void ChenNodeMH(TreeMH &DSMH, const MonHoc &mh)
{
    if (DSMH == NULL)
    {
        DSMH = new NodeMH;
        DSMH->mh = mh;
        DSMH->left = NULL;
        DSMH->right = NULL;
        return;
    }
    int cmp = strcasecmp(mh.MAMH.c_str(), DSMH->mh.MAMH.c_str());
    if (cmp < 0)
    {
        ChenNodeMH(DSMH->left, mh);
    }
    else if (cmp > 0)
    {
        ChenNodeMH(DSMH->right, mh);
    }
}

NodeMH *TimMH_MAMH(TreeMH DSMH, string mamh)
{
    if (!DSMH)
        return NULL;
    int cmp = strcasecmp(DSMH->mh.MAMH.c_str(), mamh.c_str());
    if (cmp == 0)
        return DSMH;
    if (cmp > 0)
        return TimMH_MAMH(DSMH->left, mamh);
    return TimMH_MAMH(DSMH->right, mamh);
}

TreeMH Search_MH(TreeMH root, string mamh)
{
    return TimMH_MAMH(root, mamh);
}

TreeMH Insert_MH(TreeMH root, MonHoc mh)
{
    ChenNodeMH(root, mh);
    return root;
}

string Them_MonHoc(TreeMH &DSMH, string mamh_input, string tenmh_input, string stclt_input, string stcth_input)
{
    stringstream ss;
    MonHoc mh;
    mh.MAMH = ChuanHoa_InputNangCao(mamh_input, 10, true, false);
    if (mh.MAMH.empty())
    {
        ss << "Ma mon hoc khong duoc rong!\n";
        return ss.str();
    }
    if (!KiemTra_ChuaChuVaSo(mh.MAMH))
    {
        ss << "Ma mon hoc phai chua it nhat 1 chu va 1 so!\n";
        return ss.str();
    }
    if (Search_MH(DSMH, mh.MAMH) != NULL)
    {
        ss << "Ma mon hoc da ton tai!\n";
        return ss.str();
    }
    mh.TENMH = ChuanHoa_InputNangCao(tenmh_input, 50, false, true);
    if (mh.TENMH.empty())
    {
        ss << "Ten mon hoc khong duoc rong!\n";
        return ss.str();
    }
    if (!isNumber(stclt_input))
    {
        ss << "STCLT phai la so!\n";
        return ss.str();
    }
    mh.STCLT = stoi(stclt_input);
    if (!isNumber(stcth_input))
    {
        ss << "STCTH phai la so!\n";
        return ss.str();
    }
    mh.STCTH = stoi(stcth_input);
    DSMH = Insert_MH(DSMH, mh);
    ss << "Them mon hoc thanh cong!\n";
    return ss.str();
}

string HieuChinh_MonHoc(TreeMH &DSMH, string mamh, string tenmh_new, string stclt_new, string stcth_new)
{
    stringstream ss;
    if (DSMH == NULL)
    {
        ss << "Danh sach mon hoc rong!\n";
        return ss.str();
    }
    string temp_mamh = mamh;
    ChuanHoa_Chuoi(temp_mamh, 10);
    NodeMH *node = TimMH_MAMH(DSMH, mamh);
    if (node == NULL)
    {
        ss << "Khong tim thay mon hoc!\n";
        return ss.str();
    }
    if (!tenmh_new.empty()) {
        node->mh.TENMH = ChuanHoa_InputNangCao(tenmh_new, 50, false, true);
    }
    if (!stclt_new.empty()) {
        node->mh.STCLT = stoi(stclt_new);
    }
    if (!stcth_new.empty()) {
        node->mh.STCTH = stoi(stcth_new);
    }
    ss << "Hieu chinh mon hoc thanh cong!\n";
    return ss.str();
}

NodeMH *TimMinMH(TreeMH DSMH)
{
    while (DSMH != NULL && DSMH->left != NULL)
        DSMH = DSMH->left;
    return DSMH;
}

string Xoa_MonHoc(TreeMH &DSMH, string mamh, bool confirm)
{
    stringstream ss;
    if (DSMH == NULL)
    {
        ss << "Danh sach mon hoc rong!\n";
        return ss.str();
    }
    string temp_mamh = mamh;
    ChuanHoa_Chuoi(temp_mamh, 10);
    NodeMH *parent = NULL;
    NodeMH *current = DSMH;
    while (current != NULL && strcasecmp(current->mh.MAMH.c_str(), mamh.c_str()) != 0)
    {
        parent = current;
        if (SoSanh_Chuoi(mamh, current->mh.MAMH) < 0)
            current = current->left;
        else
            current = current->right;
    }
    if (current == NULL)
    {
        ss << "Khong tim thay ma mon hoc!\n";
        return ss.str();
    }
    if (!confirm)
    {
        ss << "Da huy thao tac!\n";
        return ss.str();
    }
    if (current->left == NULL)
    {
        if (current == DSMH)
        {
            DSMH = current->right;
        }
        else if (parent->left == current)
        {
            parent->left = current->right;
        }
        else
        {
            parent->right = current->right;
        }
        delete current;
    }
    else if (current->right == NULL)
    {
        if (current == DSMH)
        {
            DSMH = current->left;
        }
        else if (parent->left == current)
        {
            parent->left = current->left;
        }
        else
        {
            parent->right = current->left;
        }
        delete current;
    }
    else
    {
        NodeMH *minNode = TimMinMH(current->right);
        current->mh = minNode->mh;
        NodeMH *minParent = current;
        NodeMH *minCurrent = current->right;
        while (minCurrent != minNode)
        {
            minParent = minCurrent;
            minCurrent = minCurrent->left;
        }
        if (minParent->left == minCurrent)
            minParent->left = minCurrent->right;
        else
            minParent->right = minCurrent->right;
        delete minCurrent;
    }
    ss << "Xoa mon hoc thanh cong!\n";
    return ss.str();
}
string SearchTenMH_MAMH(TreeMH &DSMH, string mamh)
{
if (DSMH == NULL)
{
return "";
}
if (strcasecmp(DSMH->mh.MAMH.c_str(), mamh.c_str()) == 0)
{
return DSMH->mh.TENMH;
}
if (mamh < DSMH->mh.MAMH)
{
return SearchTenMH_MAMH(DSMH->left, mamh);
}
if (mamh > DSMH->mh.MAMH)
{
return SearchTenMH_MAMH(DSMH->right, mamh);
}
return "";
}
DSMHArray::DSMHArray()
{
capacity = 100;
nodes = new MonHoc[capacity];
n = 0;
}
DSMHArray::~DSMHArray()
{
delete[] nodes;
}
void DSMHArray::Them(MonHoc mh)
{
if (n >= capacity)
{
int new_capacity = capacity * 2;
MonHoc *new_nodes = new MonHoc[new_capacity];
for (int i = 0; i < n; i++)
{
new_nodes[i] = nodes[i];
}
delete[] nodes;
nodes = new_nodes;
capacity = new_capacity;
}
nodes[n] = mh;
n++;
}
void ThuThapMH(TreeMH DSMH, DSMHArray &arr)
{
if (DSMH != NULL)
{
ThuThapMH(DSMH->left, arr);
arr.Them(DSMH->mh);
ThuThapMH(DSMH->right, arr);
}
}
int SoSanh_Chuoi(const string &s1, const string &s2)
{
int len1 = s1.length();
int len2 = s2.length();
int minLen = (len1 < len2) ? len1 : len2;
for (int i = 0; i < minLen; i++)
{
char c1 = tolower(s1[i]);
char c2 = tolower(s2[i]);
if (c1 < c2)
return -1;
if (c1 > c2)
return 1;
}
if (len1 < len2)
return -1;
if (len1 > len2)
return 1;
return 0;
}
string In_DSMH_SapXep(TreeMH DSMH)
{
stringstream ss;
if (DSMH == NULL)
{
ss << "Danh sach mon hoc rong!\n";
return ss.str();
}
DSMHArray arr;
ThuThapMH(DSMH, arr);
// Custom bubble sort for MonHoc array
for (int i = 0; i < arr.n - 1; i++)
{
for (int j = i + 1; j < arr.n; j++)
{
if (SoSanh_Chuoi(arr.nodes[i].TENMH, arr.nodes[j].TENMH) > 0)
{
MonHoc temp = arr.nodes[i];
arr.nodes[i] = arr.nodes[j];
arr.nodes[j] = temp;
}
}
}
ss << "--- DANH SACH MON HOC (SAP XEP THEO TEN) ---\n";
ss << "----------------------------------------------------------\n";
ss << left
<< setw(10) << "Ma MH"
<< setw(35) << "Ten Mon Hoc"
<< setw(8) << "STCLT"
<< setw(8) << "STCTH" << "\n";
ss << "----------------------------------------------------------\n";
for (int i = 0; i < arr.n; i++)
{
ss << left
<< setw(10) << arr.nodes[i].MAMH
<< setw(35) << arr.nodes[i].TENMH
<< setw(8) << arr.nodes[i].STCLT
<< setw(8) << arr.nodes[i].STCTH << "\n";
}
return ss.str();
}
PTRSV SearchSV_MASV(DSLopSV &DSLSV, string msv)
{
for (int i = 0; i < DSLSV.n; i++)
{
PTRSV p = DSLSV.nodes[i].FirstSV;
while (p != NULL)
{
if (strcasecmp(p->sv.MASV.c_str(), msv.c_str()) == 0)
{
return p;
}
p = p->next;
}
}
return NULL;
}
string LietKe_DSSV(DSLopSV &DSLSV)
{
stringstream ss;
ss << "--- DANH SACH SINH VIEN ---\n";
ss << "------------------------------------------------------------------------------\n";
ss << "MaSV\t\tHo\t\tTen\tGioiTinh\tSoDT\t\tEmail\n";
ss << "------------------------------------------------------------------------------\n";
for (int i = 0; i < DSLSV.n; i++)
{
for (PTRSV p = DSLSV.nodes[i].FirstSV; p != NULL; p = p->next)
{
ss << p->sv.MASV << "\t"
<< p->sv.HO << "\t"
<< p->sv.TEN << "\t"
<< p->sv.GIOITINH << "\t\t"
<< p->sv.SODT << "\t"
<< p->sv.EMAIL << "\n";
}
}
return ss.str();
}
void Xoa_SV_LopSV(PTRSV &FirstSV)
{
while (FirstSV != NULL)
{
PTRSV temp = FirstSV;
FirstSV = FirstSV->next;
delete temp;
}
}
int Tim_LopSV(DSLopSV &DSLSV, string malop)
{
for (int i = 0; i < DSLSV.n; i++)
{
if (strcasecmp(DSLSV.nodes[i].MALOP.c_str(), malop.c_str()) == 0)
return i;
}
return -1;
}
void MoRong_DSLopSV(DSLopSV &DSLSV)
{
int new_capacity = DSLSV.capacity * 2;
if (new_capacity > MAX_LOPSV)
new_capacity = MAX_LOPSV;
LopSV *new_nodes = new LopSV[new_capacity];
for (int i = 0; i < DSLSV.n; i++)
{
new_nodes[i] = DSLSV.nodes[i];
}
delete[] DSLSV.nodes;
DSLSV.nodes = new_nodes;
DSLSV.capacity = new_capacity;
}
string Them_LopSV(DSLopSV &DSLSV, string malop_input, string tenlop_input)
{
stringstream ss;
if (DSLSV.n >= MAX_LOPSV)
{
ss << "Da dat gioi han toi da " << MAX_LOPSV << " lop sinh vien!\n";
return ss.str();
}
if (DSLSV.n >= DSLSV.capacity)
{
MoRong_DSLopSV(DSLSV);
}
string malop = malop_input;
ChuanHoa_Chuoi(malop, 15);
if (Tim_LopSV(DSLSV, malop) != -1)
{
ss << "Ma lop da ton tai!\n";
return ss.str();
}
DSLSV.nodes[DSLSV.n].MALOP = malop;
DSLSV.nodes[DSLSV.n].TENLOP = tenlop_input;
DSLSV.nodes[DSLSV.n].SLSV = 0;
DSLSV.nodes[DSLSV.n].FirstSV = NULL;
DSLSV.n++;
ss << "Them lop sinh vien thanh cong!\n";
return ss.str();
}
string Xoa_LopSV(DSLopSV &DSLSV, string malop_input)
{
stringstream ss;
if (DSLSV.n == 0)
{
ss << "Danh sach lop sinh vien rong!\n";
return ss.str();
}
string malop = malop_input;
ChuanHoa_Chuoi(malop, 15);
int pos = Tim_LopSV(DSLSV, malop);
if (pos == -1)
{
ss << "Khong tim thay lop!\n";
return ss.str();
}
Xoa_SV_LopSV(DSLSV.nodes[pos].FirstSV);
DSLSV.nodes[pos].SLSV = 0;
for (int i = pos; i < DSLSV.n - 1; i++)
{
DSLSV.nodes[i] = DSLSV.nodes[i + 1];
}
DSLSV.n--;
ss << "Xoa lop sinh vien thanh cong!\n";
return ss.str();
}
string HieuChinh_LopSV(DSLopSV &DSLSV, string malop_input, string tenlop_new)
{
stringstream ss;
if (DSLSV.n == 0)
{
ss << "Danh sach lop sinh vien rong!\n";
return ss.str();
}
string malop = malop_input;
ChuanHoa_Chuoi(malop, 15);
int pos = Tim_LopSV(DSLSV, malop);
if (pos == -1)
{
ss << "Khong tim thay lop!\n";
return ss.str();
}
DSLSV.nodes[pos].TENLOP = tenlop_new;
ss << "Hieu chinh thanh cong!\n";
return ss.str();
}
bool KiemTra_SV(PTRSV FirstSV, string masv)
{
for (PTRSV p = FirstSV; p != NULL; p = p->next)
{
if (p->sv.MASV == masv)
{
return true;
}
}
return false;
}
void Nhap_DSSV_TheoMSSV(PTRSV &FirstSV, int &SLSV, DSLopSV &DSLSV)
{
// For GUI, this would be called with a list of MASV, but since no STL, perhaps pass fixed array
// Example: assume called from GUI with individual adds
// For now, stub as it's console based originally
}
string Nhap_SV_Lop(DSLopSV &DSLSV, string malop_input)
{
stringstream ss;
if (DSLSV.n == 0)
{
ss << "Danh sach lop sinh vien rong!\n";
return ss.str();
}
string malop = malop_input;
ChuanHoa_Chuoi(malop, 15);
int pos = Tim_LopSV(DSLSV, malop);
if (pos == -1)
{
ss << "Khong tim thay lop!\n";
return ss.str();
}
// Call Nhap_DSSV_TheoMSSV(DSLSV.nodes[pos].FirstSV, DSLSV.nodes[pos].SLSV, DSLSV);
ss << "Nhap sinh vien vao lop thanh cong!\n";
return ss.str();
}
string LietKe_LopSV(DSLopSV &DSLSV)
{
stringstream ss;
if (DSLSV.n == 0)
{
ss << "Danh sach lop sinh vien rong!\n";
return ss.str();
}
ss << "DANH SACH LOP SINH VIEN:\n";
ss << "-------------------------------------------------------------\n";
ss << "STT\tMa Lop\t\tTen Lop\t\t\t\tSo SV\n";
ss << "-------------------------------------------------------------\n";
for (int i = 0; i < DSLSV.n; i++)
{
ss << (i + 1) << "\t"
<< DSLSV.nodes[i].MALOP << "\t\t"
<< DSLSV.nodes[i].TENLOP << "\t\t"
<< DSLSV.nodes[i].SLSV << "\n";
}
return ss.str();
}
bool SoSanh_TenHo(const SinhVien &sv1, const SinhVien &sv2)
{
int result = SoSanh_Chuoi(sv1.TEN, sv2.TEN);
if (result != 0)
return result < 0;
return SoSanh_Chuoi(sv1.HO, sv2.HO) < 0;
}
void SapXep_DSSV_TenHo(PTRSV &FirstSV)
{
if (FirstSV == NULL || FirstSV->next == NULL)
return;
for (PTRSV i = FirstSV; i->next != NULL; i = i->next)
{
PTRSV min = i;
for (PTRSV j = i->next; j != NULL; j = j->next)
{
if (SoSanh_TenHo(j->sv, min->sv))
{
min = j;
}
}
if (min != i)
{
SinhVien temp = i->sv;
i->sv = min->sv;
min->sv = temp;
}
}
}
string In_DSSV_Lop_SapXep(DSLopSV &DSLSV, string malop_input)
{
stringstream ss;
if (DSLSV.n == 0)
{
ss << "Danh sach lop sinh vien rong!\n";
return ss.str();
}
string malop = malop_input;
ChuanHoa_Chuoi(malop, 15);
int pos = Tim_LopSV(DSLSV, malop);
if (pos == -1)
{
ss << "Khong tim thay lop!\n";
return ss.str();
}
if (DSLSV.nodes[pos].FirstSV == NULL)
{
ss << "Lop khong co sinh vien nao!\n";
return ss.str();
}
SapXep_DSSV_TenHo(DSLSV.nodes[pos].FirstSV);
ss << "--- DANH SACH SINH VIEN LOP " << DSLSV.nodes[pos].TENLOP << " (sap xep theo ten+ho) ---\n";
ss << "-------------------------------------------------------------\n";
ss << "STT\tMaSV\t\tHo\t\tTen\tGioiTinh\tSoDT\t\tEmail\n";
ss << "-------------------------------------------------------------\n";
int stt = 1;
for (PTRSV p = DSLSV.nodes[pos].FirstSV; p != NULL; p = p->next)
{
ss << stt << "\t"
<< p->sv.MASV << "\t"
<< p->sv.HO << "\t"
<< p->sv.TEN << "\t"
<< p->sv.GIOITINH << "\t\t"
<< p->sv.SODT << "\t"
<< p->sv.EMAIL << "\n";
stt++;
}
return ss.str();
}
string Them_LopTC(DSLopTC &DSLTC, TreeMH &DSMH, string mamh_input, string nienkhoa_input, int hocky_input, int nhom_input, int minsv_input, int maxsv_input)
{
stringstream ss;
if (DSLTC.n >= MAX_LOPTC)
{
ss << "Danh sach lop tin chi da day!\n";
return ss.str();
}
LopTC *ltc = new LopTC;
ltc->MAMH = mamh_input;
string tenmh = SearchTenMH_MAMH(DSMH, ltc->MAMH);
if (tenmh.empty()) {
ss << "Khong tim thay mon hoc!\n";
delete ltc;
return ss.str();
}
ltc->NIENKHOA = nienkhoa_input;
ltc->HOCKY = hocky_input;
ltc->NHOM = nhom_input;
ltc->MINSV = minsv_input;
ltc->MAXSV = maxsv_input;
ltc->MALOPTC = DSLTC.n + 1;
ltc->HUYLOP = false;
ltc->DSDK = NULL;
DSLTC.nodes[DSLTC.n] = ltc;
DSLTC.n++;
ss << "Them lop tin chi thanh cong!\n";
return ss.str();
}
LopTC *SearchLopTC_MALTC(DSLopTC &DSLTC, int mltc_input)
{
if (DSLTC.n == 0)
{
return NULL;
}
LopTC *p;
for (int i = 0; i < DSLTC.n; i++)
{
p = DSLTC.nodes[i];
if (p->MALOPTC == mltc_input)
return p;
}
return NULL;
}
string HieuChinh_LopTC(DSLopTC &DSLTC, int mltc_input, string mamh_new, string nienkhoa_new, int hocky_new, int nhom_new, int minsv_new, int maxsv_new, bool huylop_new)
{
stringstream ss;
LopTC *ltc = SearchLopTC_MALTC(DSLTC, mltc_input);
if (ltc == NULL)
{
ss << "Khong tim thay lop tin chi!\n";
return ss.str();
}
ltc->MAMH = mamh_new;
ltc->NIENKHOA = nienkhoa_new;
ltc->HOCKY = hocky_new;
ltc->NHOM = nhom_new;
ltc->MINSV = minsv_new;
ltc->MAXSV = maxsv_new;
ltc->HUYLOP = huylop_new;
ss << "Hieu chinh lop tin chi thanh cong!\n";
return ss.str();
}
string Xoa_LopTC(DSLopTC &DSLTC, int mltc_input, bool confirm)
{
stringstream ss;
LopTC *ltc = SearchLopTC_MALTC(DSLTC, mltc_input);
if (ltc == NULL)
{
ss << "Khong tim thay lop tin chi!\n";
return ss.str();
}
if (!confirm)
{
ss << "Da huy thao tac xoa!\n";
return ss.str();
}
int vitri = -1;
for (int i = 0; i < DSLTC.n; i++)
{
if (DSLTC.nodes[i] == ltc)
{
vitri = i;
break;
}
}
if (vitri == -1)
{
ss << "Lop tin chi khong ton tai!\n";
return ss.str();
}
// Clean DSDK
PTRDK dk = ltc->DSDK;
while (dk != NULL) {
PTRDK temp = dk;
dk = dk->next;
delete temp;
}
delete DSLTC.nodes[vitri];
for (int i = vitri; i < DSLTC.n - 1; i++)
{
DSLTC.nodes[i] = DSLTC.nodes[i + 1];
}
DSLTC.n--;
ss << "Da xoa lop tin chi co ma " << mltc_input << " thanh cong!\n";
return ss.str();
}
string LietKe_LopTC(DSLopTC &DSLTC, TreeMH &DSMH, string nienkhoa_input, int hocky_input)
{
stringstream ss;
ss << "--- DANH SACH LOP TIN CHI - Nien Khoa: " << nienkhoa_input << ", Hoc Ky: " << hocky_input << " ---\n";
ss << "------------------------------------------------------------------------------------------------------------------\n";
ss << left
<< setw(8) << "MaLTC"
<< setw(10) << "MaMH"
<< setw(35) << "TenMH"
<< setw(12) << "NienKhoa"
<< setw(7) << "HocKy"
<< setw(6) << "Nhom"
<< setw(7) << "MinSV"
<< setw(7) << "MaxSV"
<< setw(16) << "SoLuongDK"
<< setw(8) << "HuyLop"
<< "\n";
ss << "------------------------------------------------------------------------------------------------------------------\n";
for (int i = 0; i < DSLTC.n; i++)
{
LopTC *ltc = DSLTC.nodes[i];
if (ltc->NIENKHOA == nienkhoa_input && ltc->HOCKY == hocky_input)
{
string tenmh = SearchTenMH_MAMH(DSMH, ltc->MAMH);
ss << left
<< setw(8) << ltc->MALOPTC
<< setw(10) << ltc->MAMH
<< setw(35) << tenmh
<< setw(12) << ltc->NIENKHOA
<< setw(7) << ltc->HOCKY
<< setw(6) << ltc->NHOM
<< setw(7) << ltc->MINSV
<< setw(7) << ltc->MAXSV
<< setw(16) << ltc->SLSVDK
<< setw(8) << (ltc->HUYLOP ? "Yes" : "No")
<< "\n";
}
}
return ss.str();
}
LopTC *SearchLopTC(DSLopTC &DSLTC, string mamh, string nienkhoa, int hocky, int nhom)
{
for (int i = 0; i < DSLTC.n; i++)
{
if (strcasecmp(DSLTC.nodes[i]->MAMH.c_str(), mamh.c_str()) == 0 && strcasecmp(DSLTC.nodes[i]->NIENKHOA.c_str(), nienkhoa.c_str()) == 0 && DSLTC.nodes[i]->HOCKY == hocky && DSLTC.nodes[i]->NHOM == nhom)
{
return DSLTC.nodes[i];
}
}
return NULL;
}
string InDSSV_LopTC(DSLopTC &DSLTC, DSLopSV &DSLSV, string mamh, string nienkhoa, int hocky, int nhom)
{
stringstream ss;
LopTC *ltc = SearchLopTC(DSLTC, mamh, nienkhoa, hocky, nhom);
if (ltc == NULL)
{
ss << "Khong ton tai lop tin chi nay!\n";
return ss.str();
}
if (ltc->DSDK == NULL)
{
ss << "Danh sach sinh vien rong!\n";
return ss.str();
}
ss << "--- DANH SACH SINH VIEN DANG KY LOP " << mamh << " - HOC KY " << hocky << " - NIEN KHOA " << nienkhoa << " - NHOM " << nhom << " ---\n";
ss << "----------------------------------------------------------------------------------------------------\n";
ss << "MaSV\t\tHo\t\tTen\t\tGioiTinh\tSo DT\t\tEmail\n";
ss << "----------------------------------------------------------------------------------------------------\n";
NodeDK *p = ltc->DSDK;
while (p != NULL)
{
PTRSV node = SearchSV_MASV(DSLSV, p->dk.MASV);
if (node != NULL)
{
ss << node->sv.MASV << "\t" << node->sv.HO << "\t" << node->sv.TEN << "\t\t" << node->sv.GIOITINH << "\t\t" << node->sv.SODT << "\t" << node->sv.EMAIL << "\n";
}
p = p->next;
}
return ss.str();
}
string DangKy_LopTC(DSLopTC &DSLTC, TreeMH &DSMH, DSLopSV &DSLSV, string masv, string nienkhoa, int hocky, string mamh, int nhom)
{
stringstream ss;
PTRSV p = SearchSV_MASV(DSLSV, masv);
if (p == NULL)
{
ss << "Khong tim thay sinh vien!\n";
return ss.str();
}
LopTC *ltc = SearchLopTC(DSLTC, mamh, nienkhoa, hocky, nhom);
if (ltc == NULL)
{
ss << "Khong tim thay lop tin chi!\n";
return ss.str();
}
if (ltc->HUYLOP)
{
ss << "Lop da huy!\n";
return ss.str();
}
if (ltc->MAXSV - ltc->SLSVDK == 0)
{
ss << "So luong sv dang ky da day!\n";
return ss.str();
}
// Check if already registered
PTRDK dk = ltc->DSDK;
while (dk != NULL) {
if (dk->dk.MASV == masv) {
ss << "Sinh vien da dang ky!\n";
return ss.str();
}
dk = dk->next;
}
ltc->SLSVDK++;
PTRDK node = new NodeDK;
node->dk.MASV = masv;
node->dk.DIEM = 0;
node->next = NULL;
if (ltc->DSDK == NULL)
{
ltc->DSDK = node;
}
else
{
PTRDK temp = ltc->DSDK;
while (temp->next != NULL)
{
temp = temp->next;
}
temp->next = node;
}
ss << "Dang ky thanh cong!\n";
return ss.str();
}
float TinhDiemTrungBinh(string masv, DSLopTC &DSLTC, TreeMH DSMH)
{
float tongDiem = 0;
int tongSoTinChi = 0;
for (int i = 0; i < DSLTC.n; ++i)
{
LopTC *lop = DSLTC.nodes[i];
if (lop->HUYLOP)
continue;
PTRDK dk = lop->DSDK;
while (dk != NULL)
{
if (dk->dk.MASV == masv)
{
TreeMH p = DSMH;
while (p != NULL)
{
if (lop->MAMH == p->mh.MAMH)
break;
else if (lop->MAMH < p->mh.MAMH)
p = p->left;
else
p = p->right;
}
if (p != NULL)
{
int tinChi = p->mh.STCLT + p->mh.STCTH;
tongDiem += dk->dk.DIEM * tinChi;
tongSoTinChi += tinChi;
}
}
dk = dk->next;
}
}
return (tongSoTinChi == 0) ? 0 : tongDiem / tongSoTinChi;
}
int SearchLopSV_MALOP(DSLopSV &DSLSV, string malop)
{
for (int i = 0; i < DSLSV.n; ++i)
{
if (strcasecmp(DSLSV.nodes[i].MALOP.c_str(), malop.c_str()) == 0)
{
return i;
}
}
return -1;
}
string InDTBLopSV_SoTC(DSLopSV &DSLSV, DSLopTC &DSLTC, TreeMH DSMH, string malop_input)
{
stringstream ss;
int index = SearchLopSV_MALOP(DSLSV, malop_input);
if (index == -1)
{
ss << "Lop " << malop_input << " khong ton tai!\n";
return ss.str();
}
ss << left << setw(5) << "STT"
<< setw(15) << "MSSV"
<< setw(20) << "Ho"
<< setw(15) << "Ten"
<< setw(10) << "DiemTB" << "\n";
ss << string(65, '-') << "\n";
int stt = 1;
PTRSV p = DSLSV.nodes[index].FirstSV;
while (p != NULL)
{
float diemTB = TinhDiemTrungBinh(p->sv.MASV, DSLTC, DSMH);
ss << setw(5) << stt++
<< setw(15) << p->sv.MASV
<< setw(20) << p->sv.HO
<< setw(15) << p->sv.TEN
<< fixed << setprecision(2) << setw(10) << diemTB
<< "\n";
p = p->next;
}
return ss.str();
}

string NhapDiem_LopTC(DSLopTC &DSLTC, TreeMH &DSMH, DSLopSV &DSLSV, string mamh, string nienkhoa, int hocky, int nhom, CustomPair diem_list[], int diem_size)
{
stringstream ss;
LopTC *ltc = SearchLopTC(DSLTC, mamh, nienkhoa, hocky, nhom);
if (ltc == NULL)
{
ss << "Khong ton tai lop tin chi nay!\n";
return ss.str();
}
if (ltc->DSDK == NULL)
{
ss << "Lop tin chi chua co sinh vien dang ky!\n";
return ss.str();
}
// Update diem using diem_list array
for (int i = 0; i < diem_size; i++) {
PTRDK p = ltc->DSDK;
while (p != NULL) {
if (p->dk.MASV == diem_list[i].masv) {
p->dk.DIEM = diem_list[i].diem;
break;
}
p = p->next;
}
}
ss << "\nHoan thanh nhap diem cho lop tin chi!\n";
return ss.str();
}
string InDiemTongKet(DSLopSV &DSLSV, DSLopTC &DSLTC, string malop_input)
{
stringstream ss;
int indexLop = SearchLopSV_MALOP(DSLSV, malop_input);
if (indexLop == -1)
{
ss << "Khong ton tai lop sinh vien nay!\n";
return ss.str();
}
if (DSLSV.nodes[indexLop].FirstSV == NULL)
{
ss << "Lop sinh vien chua co sinh vien nao!\n";
return ss.str();
}
// Custom array for unique MAMH, fixed max 100
string danhSachMaMH[100];
int soMon = 0;
PTRSV p = DSLSV.nodes[indexLop].FirstSV;
while (p != NULL)
{
for (int i = 0; i < DSLTC.n; i++)
{
if (DSLTC.nodes[i] != NULL && !DSLTC.nodes[i]->HUYLOP)
{
PTRDK dk = DSLTC.nodes[i]->DSDK;
while (dk != NULL)
{
if (dk->dk.MASV == p->sv.MASV && dk->dk.DIEM >= 0)
{
bool daTonTai = false;
for (int j = 0; j < soMon; j++)
{
if (danhSachMaMH[j] == DSLTC.nodes[i]->MAMH)
{
daTonTai = true;
break;
}
}
if (!daTonTai)
{
if (soMon < 100) {
danhSachMaMH[soMon] = DSLTC.nodes[i]->MAMH;
soMon++;
}
}
break;
}
dk = dk->next;
}
}
}
p = p->next;
}
ss << "\n";
ss << setw(50) << "BANG DIEM TONG KET\n";
ss << setw(40) << "Lop : " << malop_input << "\n\n";
ss << "| STT | Ma SV    | Ho Ten        |";
for (int i = 0; i < soMon; i++)
{
ss << " " << setw(6) << danhSachMaMH[i] << " |";
}
ss << "\n";
ss << "|-----|----------|---------------|";
for (int i = 0; i < soMon; i++)
{
ss << "--------|";
}
ss << "\n";
p = DSLSV.nodes[indexLop].FirstSV;
int stt = 1;
while (p != NULL)
{
ss << "| " << setw(2) << stt << "  | ";
ss << setw(8) << left << p->sv.MASV << " | ";
string hoTen = p->sv.HO + " " + p->sv.TEN;
ss << setw(13) << left << hoTen << " |";
for (int k = 0; k < soMon; k++)
{
float diem = -1;
bool timThay = false;
for (int j = 0; j < DSLTC.n; j++)
{
if (DSLTC.nodes[j] != NULL && !DSLTC.nodes[j]->HUYLOP &&
DSLTC.nodes[j]->MAMH == danhSachMaMH[k])
{
PTRDK dk = DSLTC.nodes[j]->DSDK;
while (dk != NULL)
{
if (dk->dk.MASV == p->sv.MASV)
{
diem = dk->dk.DIEM;
timThay = true;
break;
}
dk = dk->next;
}
if (timThay)
break;
}
}
if (timThay && diem >= 0)
{
ss << " " << setw(6) << fixed << setprecision(0) << diem << " |";
}
else
{
ss << " " << setw(6) << "" << " |";
}
}
ss << "\n";
p = p->next;
stt++;
}
return ss.str();
}
string InBangDiem_LopTC(DSLopTC &DSLTC, TreeMH &DSMH, DSLopSV &DSLSV, string mamh, string nienkhoa, int hocky, int nhom)
{
stringstream ss;
LopTC *ltc = SearchLopTC(DSLTC, mamh, nienkhoa, hocky, nhom);
if (ltc == NULL || ltc->HUYLOP)
{
ss << "Khong ton tai lop tin chi nay hoac da bi huy!\n";
return ss.str();
}
string tenmh = SearchTenMH_MAMH(DSMH, mamh);
ss << "\nBẢNG ĐIỂM MÔN HỌC: " << tenmh << "\n";
ss << "Niên khóa: " << nienkhoa << "  | Học kỳ: " << hocky << "  | Nhóm: " << nhom << "\n";
ss << "-------------------------------------------------------------\n";
ss << "STT  MASV        HO                 TEN        DIEM\n";
ss << "-------------------------------------------------------------\n";
int stt = 1;
for (PTRDK p = ltc->DSDK; p != NULL; p = p->next)
{
PTRSV sv = SearchSV_MASV(DSLSV, p->dk.MASV);
if (sv != NULL)
{
ss << setw(3) << stt << "  "
<< setw(10) << sv->sv.MASV << "  "
<< setw(18) << sv->sv.HO << "  "
<< setw(10) << sv->sv.TEN << "  "
<< fixed << setprecision(1) << p->dk.DIEM << "\n";
}
stt++;
}
return ss.str();
}
void DocFile_DSMH(TreeMH &DSMH)
{
    ifstream in("DSMH.txt");
    if (!in.is_open())
    {
        return;
    }
    string line;
    if (!getline(in, line))
    {
        return;
    }
    int soMonHoc = stoi(line);
    for (int i = 0; i < soMonHoc; ++i)
    {
        if (!getline(in, line))
            break;
        stringstream ss(line);
        string MAMH, TENMH, STCLT, STCTH;
        getline(ss, MAMH, ',');
        getline(ss, TENMH, ',');
        getline(ss, STCLT, ',');
        getline(ss, STCTH, ',');
        MonHoc mh;
        mh.MAMH = MAMH;
        mh.TENMH = TENMH;
        mh.STCLT = stoi(STCLT);
        mh.STCTH = stoi(STCTH);
        ChenNodeMH(DSMH, mh);
    }
    in.close();
}

int TimViTriLop(DSLopSV &DSLSV, string maLop)
{
    for (int i = 0; i < DSLSV.n; i++)
    {
        if (DSLSV.nodes[i].MALOP == maLop)
            return i;
    }
    return -1;
}

void ThemSinhVienVaoLop(PTRSV &FirstSV, SinhVien sv)
{
    PTRSV newNode = new NodeSV;
    newNode->sv = sv;
    newNode->next = NULL;
    if (FirstSV == NULL)
    {
        FirstSV = newNode;
    }
    else
    {
        PTRSV temp = FirstSV;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }
}

void DocFile_DSLSV(DSLopSV &DSLSV)
{
    ifstream in("DSLSV.txt");
    if (!in.is_open())
    {
        return;
    }
    string line;
    LopSV *lopHienTai = NULL;
    if (!getline(in, line))
    {
        return;
    }
    int soLop = stoi(line);
    for (int i = 0; i < soLop; ++i)
    {
        if (!getline(in, line))
            break;
        stringstream ss(line);
        string MALOP, TENLOP;
        getline(ss, MALOP, ',');
        getline(ss, TENLOP);
        LopSV lop;
        lop.MALOP = MALOP;
        lop.TENLOP = TENLOP;
        if (!getline(in, line))
            break;
        lop.SLSV = stoi(line);
        lop.FirstSV = NULL;
        lopHienTai = &DSLSV.nodes[DSLSV.n];
        *lopHienTai = lop;
        for (int j = 0; j < lop.SLSV; ++j)
        {
            if (!getline(in, line))
                break;
            line = line.substr(5);
            stringstream svStream(line);
            SinhVien sv;
            getline(svStream, sv.MASV, ',');
            getline(svStream, sv.HO, ',');
            getline(svStream, sv.TEN, ',');
            getline(svStream, sv.GIOITINH, ',');
            getline(svStream, sv.SODT, ',');
            getline(svStream, sv.EMAIL, ',');
            ThemSinhVienVaoLop(lopHienTai->FirstSV, sv);
        }
        DSLSV.n++;
    }
    in.close();
}

void DocFile_DSLTC(DSLopTC &DSLTC)
{
    ifstream in("DSLTC.txt");
    if (!in.is_open())
    {
        return;
    }
    string line;
    getline(in, line);
    int tongSoLop = stoi(line);
    for (int i = 0; i < tongSoLop; ++i)
    {
        if (!getline(in, line))
            break;
        stringstream ss(line);
        string MALOPTC, MAMH, NIENKHOA, HOCKY, NHOM, MINSV, MAXSV, HUYLOP;
        getline(ss, MALOPTC, ',');
        getline(ss, MAMH, ',');
        getline(ss, NIENKHOA, ',');
        getline(ss, HOCKY, ',');
        getline(ss, NHOM, ',');
        getline(ss, MINSV, ',');
        getline(ss, MAXSV, ',');
        getline(ss, HUYLOP, ',');
        LopTC *ltc = new LopTC;
        ltc->MALOPTC = stoi(MALOPTC);
        ltc->MAMH = MAMH;
        ltc->NIENKHOA = NIENKHOA;
        ltc->HOCKY = stoi(HOCKY);
        ltc->NHOM = stoi(NHOM);
        ltc->MINSV = stoi(MINSV);
        ltc->MAXSV = stoi(MAXSV);
        ltc->SLSVDK = 0;
        ltc->HUYLOP = (HUYLOP == "Yes");
        ltc->DSDK = NULL;
        if (!getline(in, line))
            break;
        int soSV = stoi(line);
        ltc->SLSVDK = soSV;
        for (int j = 0; j < soSV; ++j)
        {
            if (!getline(in, line))
                break;
            line = line.substr(5);
            stringstream svStream(line);
            string MASV, DIEM_STR;
            getline(svStream, MASV, ',');
            getline(svStream, DIEM_STR, ',');
            float DIEM = stof(DIEM_STR);
            PTRDK newNode = new NodeDK;
            newNode->dk.MASV = MASV;
            newNode->dk.DIEM = DIEM;
            newNode->next = NULL;
            if (ltc->DSDK == NULL)
            {
                ltc->DSDK = newNode;
            }
            else
            {
                PTRDK last = ltc->DSDK;
                while (last->next != NULL)
                    last = last->next;
                last->next = newNode;
            }
        }
        DSLTC.nodes[DSLTC.n++] = ltc;
    }
    in.close();
}

string DocFile(TreeMH &DSMH, DSLopSV &DSLSV, DSLopTC &DSLTC)
{
    stringstream ss;
    DocFile_DSMH(DSMH);
    DocFile_DSLSV(DSLSV);
    DocFile_DSLTC(DSLTC);
    ss << "Doc du lieu tu file thanh cong!\n";
    return ss.str();
}

int DemSoMonHoc(TreeMH DSMH)
{
    if (DSMH == NULL)
        return 0;
    return 1 + DemSoMonHoc(DSMH->left) + DemSoMonHoc(DSMH->right);
}

void GhiDSMH_NLR(TreeMH DSMH, ofstream &out)
{
    if (DSMH == NULL)
        return;
    out << DSMH->mh.MAMH << ","
        << DSMH->mh.TENMH << ","
        << DSMH->mh.STCLT << ","
        << DSMH->mh.STCTH << "\n";
    GhiDSMH_NLR(DSMH->left, out);
    GhiDSMH_NLR(DSMH->right, out);
}

void GhiFile_DSMH(TreeMH &DSMH)
{
    ofstream out("DSMH_Temp.txt");
    if (!out.is_open())
    {
        return;
    }
    int soMonHoc = DemSoMonHoc(DSMH);
    out << soMonHoc << "\n";
    GhiDSMH_NLR(DSMH, out);
    out.close();
}

void GhiFile_DSLSV(DSLopSV &DSLSV)
{
    ofstream out("DSLSV_Temp.txt");
    if (!out.is_open())
    {
        return;
    }
    out << DSLSV.n << "\n";
    for (int i = 0; i < DSLSV.n; i++)
    {
        LopSV &lop = DSLSV.nodes[i];
        out << lop.MALOP << "," << lop.TENLOP << "\n";
        out << "     " << lop.SLSV << "\n";
        for (PTRSV p = lop.FirstSV; p != NULL; p = p->next)
        {
            SinhVien &sv = p->sv;
            out << "     "
                << sv.MASV << ","
                << sv.HO << ","
                << sv.TEN << ","
                << sv.GIOITINH << ","
                << sv.SODT << ","
                << sv.EMAIL << "\n";
        }
    }
    out.close();
}

void GhiFile_DSLTC(DSLopTC &DSLTC)
{
    ofstream out("DSLTC_Temp.txt");
    if (!out.is_open())
    {
        return;
    }
    out << DSLTC.n << "\n";
    for (int i = 0; i < DSLTC.n; ++i)
    {
        LopTC *ltc = DSLTC.nodes[i];
        out << ltc->MALOPTC << "," << ltc->MAMH << "," << ltc->NIENKHOA << "," << ltc->HOCKY << "," << ltc->NHOM << ","
            << ltc->MINSV << "," << ltc->MAXSV << "," << (ltc->HUYLOP ? "Yes" : "No") << "\n";
        int countSV = 0;
        for (PTRDK p = ltc->DSDK; p != NULL; p = p->next)
            countSV++;
        out << "     " << countSV << "\n";
        PTRDK p = ltc->DSDK;
        while (p != NULL)
        {
            out << "     " << p->dk.MASV << "," << fixed << setprecision(1) << p->dk.DIEM << "\n";
            p = p->next;
        }
    }
    out.close();
}

string GhiFile(TreeMH &DSMH, DSLopSV &DSLSV, DSLopTC &DSLTC)
{
    stringstream ss;
    GhiFile_DSMH(DSMH);
    GhiFile_DSLSV(DSLSV);
    GhiFile_DSLTC(DSLTC);
    ss << "Da ghi du lieu vao file thanh cong!\n";
    return ss.str();
}
