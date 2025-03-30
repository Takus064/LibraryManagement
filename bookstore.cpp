#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <limits>
#include <iomanip>
#include <conio.h>
#include <unordered_map>
using namespace std;

string truncate(const string& str, size_t width) {
    if (str.length() <= width) return str;
    return str.substr(0, width - 3) + "...";
}

void tachNgayThangNam(const string& ngayNhap, int& nam, int& thang, int& ngay) {
    nam = stoi(ngayNhap.substr(0, 4));
    thang = stoi(ngayNhap.substr(5, 2));
    ngay = stoi(ngayNhap.substr(8, 2));
}

class DMNhacungcap
{
private:
    string tenNhaCungCap;
    string maNhaCungCap;
    string diaChi;
    string soDienThoai;

public:
    // Constructor
    DMNhacungcap(string _tenNhaCungCap, string _maNhaCungCap, string _diaChi, string _soDienThoai)
        : tenNhaCungCap(_tenNhaCungCap), maNhaCungCap(_maNhaCungCap), diaChi(_diaChi), soDienThoai(_soDienThoai) {}
    DMNhacungcap(string _maNhaCungCap)
        : maNhaCungCap(_maNhaCungCap) {}

    // Getters
    string getTenNhaCungCap() const { return tenNhaCungCap; }
    string getMaNhaCungCap() const { return maNhaCungCap; }
    string getDiaChi() const { return diaChi; }
    string getSoDienThoai() const { return soDienThoai; }

    // Setters
    void setTenNhaCungCap(const string& _tenNhaCungCap) { this->tenNhaCungCap = _tenNhaCungCap; }
    void setMaNhaCungCap(const string& _maNhaCungCap) { this->maNhaCungCap = _maNhaCungCap; }
    void setDiaChi(const string& _diaChi) { this->diaChi = _diaChi; }
    void setSoDienThoai(const string& _soDienThoai) { this->soDienThoai = _soDienThoai; }
};

class DMSach
{
private:
    string tenSach;
    string maSach;
    string tacGia;
    string nhaXuatBan; // Changed from int to string
    string theloai;
    float giaSach;

public:
    // Constructor
    DMSach(string _tenSach, string _maSach, string _tacGia, string _nhaXuatBan, string _theloai, float _giaSach)
        : tenSach(_tenSach), maSach(_maSach), tacGia(_tacGia), nhaXuatBan(_nhaXuatBan), theloai(_theloai), giaSach(_giaSach) {}
    DMSach(string _maSach)
        : maSach(_maSach) {}

    // Getters
    string getTenSach() const { return tenSach; }
    string getMaSach() const { return maSach; }
    string getTacGia() const { return tacGia; }
    string getNhaXuatBan() const { return nhaXuatBan; } // Updated getter
    string getTheLoai() const { return theloai; }
    float getGiaSach() const { return giaSach; }

    // Setters
    void setTenSach(const string& _tenSach) { this->tenSach = _tenSach; }
    void setMaSach(const string& _maSach) { this->maSach = _maSach; }
    void setTacGia(const string& _tacGia) { this->tacGia = _tacGia; }
    void setNhaXuatBan(const string& _nhaXuatBan) { this->nhaXuatBan = _nhaXuatBan; } // Updated setter
    void setTheLoai(const string& _theloai) { this->theloai = _theloai; }
    void setGiaSach(float _giaSach) { this->giaSach = _giaSach; }
};

class PhieuNhapSach : public DMSach, public DMNhacungcap
{
protected:
    int soPhieu;
    string ngayNhap;
    int soLuong;
private:
    static int currentSoPhieu; // Static variable to track the current soPhieu
public:

    // Constructor
    PhieuNhapSach(string _ngayNhap, string _maNhaCungCap, string _maSach, int _soLuong)
        : DMSach(_maSach),
          DMNhacungcap(_maNhaCungCap),
          soPhieu(++currentSoPhieu), // Automatically increment soPhieu
          ngayNhap(_ngayNhap),
          soLuong(_soLuong) {}

    PhieuNhapSach(int _soPhieu, string _ngayNhap, string _maNhaCungCap, string _maSach, int _soLuong)
    : DMSach(_maSach), DMNhacungcap(_maNhaCungCap),
      soPhieu(_soPhieu), ngayNhap(_ngayNhap), soLuong(_soLuong) {}

    // Getters
    int getSoPhieu() const { return soPhieu; }
    string getNgayNhap() const { return ngayNhap; }
    int getSoLuong() const { return soLuong; }

    // Setters
    void setNgayNhap(const string& _ngayNhap) { this->ngayNhap = _ngayNhap; }
    void setSoLuong(int _soLuong) { this->soLuong = _soLuong; }

    static void setCurrentSoPhieu(int value) {
        currentSoPhieu = value;
    }
};

class BookStore {
    vector<DMNhacungcap> nccList; // Placeholder for the list of suppliers
    vector<DMSach> sachList; // Placeholder for the list of books
    vector<PhieuNhapSach> phieuList; // Placeholder for the list of import receipts
public:

    vector<PhieuNhapSach>& getPhieuList() {
    return phieuList;
    }

    vector<DMNhacungcap>& getNhaCungCapList() {
        return nccList;
    }

    // Function to read suppliers from a file
    void loadNhaCungCap(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error: Could not open file " << filename << endl;
            return;
        }

        string tenNhaCungCap, maNhaCungCap, diaChi, soDienThoai;

        // Read each line of the file
        while (file >> maNhaCungCap) {
            file.ignore(); // Ignore the space after maNhaCungCap
            getline(file, tenNhaCungCap, '\t'); // Read tenNhaCungCap until the tab character
            getline(file, diaChi, '\t'); // Read diaChi until the tab character
            getline(file, soDienThoai); // Read soDienThoai until the end of the line

            // Add the supplier to the list
            nccList.emplace_back(tenNhaCungCap, maNhaCungCap, diaChi, soDienThoai);
        }

        file.close();
    }

    // Function to read books from a file
    void loadSach(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error: Could not open file " << filename << endl;
            return;
        }

        string maSach, tenSach, tacGia, theloai, nhaXuatBan;
        float giaSach;

        // Read each line of the file
        while (file >> maSach) {
            file.ignore(); // Ignore the space after maSach
            getline(file, tenSach, '\t'); // Read tenSach until the tab character
            getline(file, tacGia, '\t'); // Read tacGia until the tab character
            getline(file, nhaXuatBan, '\t'); // Read nhaXuatBan until the tab character
            getline(file, theloai, '\t'); // Read theloai until the tab character
            file >> giaSach; // Read giaSach

            // Add the book to the list
            sachList.emplace_back(tenSach, maSach, tacGia, nhaXuatBan, theloai, giaSach);
        }

        file.close();
    }

    // Function to read receipts from a file
    void loadPhieuNhapSach(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error: Could not open file " << filename << endl;
            return;
        }
    
        int soPhieu, soLuong;
        string ngayNhap, maNhaCungCap, maSach;
        int maxSoPhieu = 0;
    
        while (file >> soPhieu >> ngayNhap >> maNhaCungCap >> maSach >> soLuong) {
            phieuList.emplace_back(soPhieu, ngayNhap, maNhaCungCap, maSach, soLuong);
            if (soPhieu > maxSoPhieu) maxSoPhieu = soPhieu;
        }
    
        // Đặt currentSoPhieu đúng với số lớn nhất đã load
        PhieuNhapSach::setCurrentSoPhieu(maxSoPhieu);
    
        file.close();
    }
    

    void addNhaCungCap(const DMNhacungcap& ncc) {
        nccList.push_back(ncc); // Assuming nccList is a vector of DMNhacungcap
        cout << "Da them nha cung cap " << ncc.getTenNhaCungCap() << endl;
    }

    void saveNhaCungCapToFile(const string& filename, const DMNhacungcap& ncc) {
        ofstream file(filename, ios::app); // mở ở chế độ append
        if (!file.is_open()) {
            cerr << "Khong mo duoc file de ghi: " << filename << endl;
            return;
        }
    
        // Ghi thông tin nhà cung cấp mới theo định dạng cũ (tách bằng tab)
        file << ncc.getMaNhaCungCap() << "\t"
             << ncc.getTenNhaCungCap() << "\t"
             << ncc.getDiaChi() << "\t"
             << ncc.getSoDienThoai() << "\n";
    
        file.close();
    }


    void addSach(const DMSach& sach) {
        sachList.push_back(sach); // Assuming sachList is a vector of DMSach
        cout << "Da them sach " << sach.getTenSach() << endl;
    }

    void saveSachToFile(const string& filename, const DMSach& sach) {
        ofstream file(filename, ios::app); // mở ở chế độ ghi tiếp (append)
        if (!file.is_open()) {
            cerr << "Khong mo duoc file de ghi: " << filename << endl;
            return;
        }
    
        file << sach.getMaSach() << "\t"
             << sach.getTenSach() << "\t"
             << sach.getTacGia() << "\t"
             << sach.getNhaXuatBan() << "\t"
             << sach.getTheLoai() << "\t"
             << sach.getGiaSach() << "\n";
    
        file.close();
    }

    void addPhieuNhapSach(const PhieuNhapSach& phieu) {
        phieuList.push_back(phieu); // Assuming phieuList is a vector of PhieuNhapSach
        cout << "Da them phieu nhap sach thanh cong. " << endl;
    }

    void saveAllPhieuNhapToFile(const string& filename) {
        ofstream file(filename); // mở ở chế độ ghi đè
        if (!file.is_open()) {
            cerr << "Khong mo duoc file de ghi: " << filename << endl;
            return;
        }
    
        for (const auto& phieu : phieuList) {
            file << phieu.getSoPhieu() << "\t"
                 << phieu.getNgayNhap() << "\t"
                 << phieu.getMaNhaCungCap() << "\t"
                 << phieu.getMaSach() << "\t"
                 << phieu.getSoLuong() << "\n";
        }
    
        file.close();
    }
    
    
    void showNhaCungCap()
    {
        cout << "+---------------+-----------------+----------------------------+---------------+\n";
        cout << "| Ma NCC        | Ten NCC         | Dia chi                    | SDT           |\n";
        cout << "+---------------+-----------------+----------------------------+---------------+\n";
        for (const auto& ncc : nccList)
        {
            cout << "| " << setw(14) << left << ncc.getMaNhaCungCap()
                << "| " << setw(16) << left << ncc.getTenNhaCungCap()
                << "| " << setw(27) << left << ncc.getDiaChi()
                << "| " << setw(14) << left << ncc.getSoDienThoai() << "|\n";
        }
        cout << "+---------------+-----------------+----------------------------+---------------+\n";
    }
    
    void showSach()
{
    cout << "+-----------+----------------------------+----------------------+-----------------+------------+----------+\n";
    cout << "| Ma sach   | Ten sach                   | Tac gia              | Nha xuat ban    | The loai   | Gia sach |\n";
    cout << "+-----------+----------------------------+----------------------+-----------------+------------+----------+\n";
    for (const auto& sach : sachList)
    {
        cout << "| " << setw(10) << left << sach.getMaSach()
             << "| " << setw(27) << left << truncate(sach.getTenSach(), 27)
             << "| " << setw(21) << left << truncate(sach.getTacGia(), 21)
             << "| " << setw(16) << left << truncate(sach.getNhaXuatBan(), 16)
             << "| " << setw(11) << left << truncate(sach.getTheLoai(), 11)
             << "| " << setw(8)  << left << sach.getGiaSach() << " |\n";
    }
    cout << "+-----------+----------------------------+----------------------+-----------------+------------+----------+\n";
}
    
    void showPhieuNhapSach()
    {
        // Sort the list by ngayNhap
        sort(phieuList.begin(), phieuList.end(), [](const PhieuNhapSach& a, const PhieuNhapSach& b) {
            return a.getNgayNhap() < b.getNgayNhap();
        });
    
        cout << "+-----------+------------+-----------------+-----------+----------+\n";
        cout << "| So phieu  | Ngay nhap  | Ma nha cung cap | Ma sach   | So luong |\n";
        cout << "+-----------+------------+-----------------+-----------+----------+\n";
        for (const auto& phieu : phieuList)
        {
            cout << "| " << setw(10) << left << phieu.getSoPhieu()
            << "| " << setw(11) << left << phieu.getNgayNhap()
            << "| " << setw(16) << left << phieu.getMaNhaCungCap()
            << "| " << setw(10) << left << phieu.getMaSach()
            << "| " << setw(8) << left << phieu.getSoLuong() << " |\n";
        }
        cout << "+-----------+------------+-----------------+-----------+----------+\n";
    }
    
    void searchPhieuNhapSach(int soPhieu)
    {
        auto it = find_if(phieuList.begin(), phieuList.end(), [soPhieu](const PhieuNhapSach& phieu) {
            return phieu.getSoPhieu() == soPhieu;
        });
    
        if (it != phieuList.end())
        {
            cout << "Tim thay Phieu Nhap Sach: " << endl;
            cout << "+-----------+------------+-----------------+-----------+----------+\n";
            cout << "| So phieu  | Ngay nhap  | Ma nha cung cap | Ma sach   | So luong |\n";
            cout << "+-----------+------------+-----------------+-----------+----------+\n";
            cout << "| " << setw(10) << left << it->getSoPhieu()
                << "| " << setw(11) << left << it->getNgayNhap()
                << "| " << setw(16) << left << it -> getMaNhaCungCap()
                << "| " << setw(10) << left << it -> getMaSach()
                << "| " << setw(8) << left << it -> getSoLuong() << " |\n";
            cout << "+-----------+------------+-----------------+-----------+----------+\n";
        }
        else
        {
            cout << "Khong tim thay phieu nhap tuong ung" << endl;
        }
    }

    void deletePhieuNhapBySoPhieu(int soPhieu) {
        auto it = remove_if(phieuList.begin(), phieuList.end(), [soPhieu](const PhieuNhapSach& p) {
            return p.getSoPhieu() == soPhieu;
        });
        if (it != phieuList.end()) {
            phieuList.erase(it, phieuList.end());
        }
    }
    
};

// Initialize the static variable
int PhieuNhapSach::currentSoPhieu = 0;

void thongKeTheoNam(const vector<PhieuNhapSach>& phieuList, int namTK) {
    int tongSoLuong = 0;
    for (const auto& phieu : phieuList) {
        int nam, thang, ngay;
        tachNgayThangNam(phieu.getNgayNhap(), nam, thang, ngay);
        if (nam == namTK) tongSoLuong += phieu.getSoLuong();
    }
    cout << "Tong so sach nhap trong nam " << namTK << ": " << tongSoLuong << " quyen.\n";
}

void thongKeTheoThangNam(const vector<PhieuNhapSach>& phieuList, int thangTK, int namTK) {
    int tongSoLuong = 0;
    for (const auto& phieu : phieuList) {
        int nam, thang, ngay;
        tachNgayThangNam(phieu.getNgayNhap(), nam, thang, ngay);
        if (nam == namTK && thang == thangTK) tongSoLuong += phieu.getSoLuong();
    }
    cout << "Tong so sach nhap trong thang " << thangTK << "/" << namTK << ": " << tongSoLuong << " quyen.\n";
}

void thongKeTheoNgay(const vector<PhieuNhapSach>& phieuList, int ngayTK, int thangTK, int namTK) {
    int tongSoLuong = 0;
    for (const auto& phieu : phieuList) {
        int nam, thang, ngay;
        tachNgayThangNam(phieu.getNgayNhap(), nam, thang, ngay);
        if (nam == namTK && thang == thangTK && ngay == ngayTK) tongSoLuong += phieu.getSoLuong();
    }
    cout << "Tong so sach nhap vao ngay " << ngayTK << "/" << thangTK << "/" << namTK << ": " << tongSoLuong << " quyen.\n";
}

void thongKeNhaCungCapNhieuNhat(const vector<PhieuNhapSach>& phieuList, const vector<DMNhacungcap>& nccList) {
    unordered_map<string, int> soLuongTheoNCC;

    // 1. Tính tổng số lượng sách theo mã nhà cung cấp
    for (const auto& phieu : phieuList) {
        string maNCC = phieu.getMaNhaCungCap();
        soLuongTheoNCC[maNCC] += phieu.getSoLuong();
    }

    // 2. Tìm mã NCC có số lượng lớn nhất
    string maNCCMax = "";
    int maxSoLuong = 0;

    for (const auto& pair : soLuongTheoNCC) {
        if (pair.second > maxSoLuong) {
            maxSoLuong = pair.second;
            maNCCMax = pair.first;
        }
    }

    // 3. Tìm tên NCC từ danh mục NCC
    string tenNCCMax = "Khong tim thay";
    for (const auto& ncc : nccList) {
        if (ncc.getMaNhaCungCap() == maNCCMax) {
            tenNCCMax = ncc.getTenNhaCungCap();
            break;
        }
    }

    // 4. Hiển thị kết quả
    cout << "Nha cung cap cung cap nhieu sach nhat:\n";
    cout << "- Ten: " << tenNCCMax << endl;
    cout << "- Ma: " << maNCCMax << endl;
    cout << "- Tong so luong sach da cung cap: " << maxSoLuong << " quyen\n";
}

void taoBaoCaoNhapSachTheoKhoangThoiGian(const vector<PhieuNhapSach>& phieuList, const string& ngayBatDau, const string& ngayKetThuc, const string& tenFile) {
    ofstream file(tenFile);
    if (!file.is_open()) {
        cerr << "Khong mo duoc file de ghi bao cao!\n";
        return;
    }
    
    // Tiêu đề báo cáo
    file << "===== BÁO CÁO NHẬP SÁCH =====\n\n";
    file << "Từ ngày: " << ngayBatDau << " đến ngày: " << ngayKetThuc << "\n\n";
    
    // Định nghĩa độ rộng cho từng cột
    const int colMaPhieu = 10;
    const int colMaSach = 10;
    const int colTenSach = 20;
    const int colNhaCungCap = 20;
    const int colSoLuong = 10;
    const int colNgayNhap = 12;
    
    // Tạo header với định dạng bảng có viền
    file << "+-" << string(colMaPhieu, '-') << "-+-" << string(colMaSach, '-') << "-+-" 
         << string(colTenSach, '-') << "-+-" << string(colNhaCungCap, '-') << "-+-" 
         << string(colSoLuong, '-') << "-+-" << string(colNgayNhap, '-') << "-+\n";
    
    file << "| " << setw(colMaPhieu) << left << "Mã phiếu" 
         << " | " << setw(colMaSach) << left << "Mã sách" 
         << " | " << setw(colTenSach) << left << "Tên sách" 
         << " | " << setw(colNhaCungCap) << left << "Nhà cung cấp" 
         << " | " << setw(colSoLuong) << left << "Số lượng" 
         << " | " << setw(colNgayNhap) << left << "Ngày nhập" << " |\n";
    
    file << "+-" << string(colMaPhieu, '-') << "-+-" << string(colMaSach, '-') << "-+-" 
         << string(colTenSach, '-') << "-+-" << string(colNhaCungCap, '-') << "-+-" 
         << string(colSoLuong, '-') << "-+-" << string(colNgayNhap, '-') << "-+\n";
    
    // Biến lưu tổng số sách nhập
    int tongSoLuong = 0;
    
    // Tạo một vector lưu các phiếu nhập và lọc theo ngày bắt đầu và kết thúc
    vector<PhieuNhapSach> phieuFiltered;
    for (const auto& phieu : phieuList) {
        string ngayNhap = phieu.getNgayNhap();
        if (ngayNhap >= ngayBatDau && ngayNhap <= ngayKetThuc) {
            phieuFiltered.push_back(phieu);
            tongSoLuong += phieu.getSoLuong();  // Cộng dồn số sách nhập
        }
    }
    
    // Sắp xếp phiếu nhập theo ngày nhập (ascending)
    sort(phieuFiltered.begin(), phieuFiltered.end(), [](const PhieuNhapSach& a, const PhieuNhapSach& b) {
        return a.getNgayNhap() < b.getNgayNhap(); // Sắp xếp theo ngày
    });
    
    // In thông tin các phiếu nhập đã lọc và sắp xếp với định dạng bảng
    for (const auto& phieu : phieuFiltered) {
        file << "| " << setw(colMaPhieu) << left << phieu.getSoPhieu() 
             << " | " << setw(colMaSach) << left << phieu.getMaSach() 
             << " | " << setw(colTenSach) << left << phieu.getTenSach() 
             << " | " << setw(colNhaCungCap) << left << phieu.getMaNhaCungCap() 
             << " | " << setw(colSoLuong) << left << phieu.getSoLuong() 
             << " | " << setw(colNgayNhap) << left << phieu.getNgayNhap() << " |\n";
    }
    
    // Đóng bảng
    file << "+-" << string(colMaPhieu, '-') << "-+-" << string(colMaSach, '-') << "-+-" 
         << string(colTenSach, '-') << "-+-" << string(colNhaCungCap, '-') << "-+-" 
         << string(colSoLuong, '-') << "-+-" << string(colNgayNhap, '-') << "-+\n";
    
    // Xuất tổng số sách nhập
    file << "\nTổng số sách nhập từ ngày " << ngayBatDau << " đến ngày " << ngayKetThuc << ": " << tongSoLuong << " quyển\n";
    file << "\n===== KẾT THÚC =====\n";
    file.close();
    
    cout << "Da xuat bao cao nhap sach tu " << ngayBatDau << " den " << ngayKetThuc << " ra file: " << tenFile << endl;
}

void printMenu() {
    cout << "\n========== MENU ==========\n";
    cout << "1. Them Nha Cung Cap\n";
    cout << "2. Them Sach\n";
    cout << "3. Them Phieu Nhap Sach\n";
    cout << "4. Xem Nha Cung Cap\n";
    cout << "5. Xem Sach\n";
    cout << "6. Xem Phieu Nhap Sach\n";
    cout << "7. Tim Kiem Phieu Nhap Sach\n";
    cout << "8. Thong ke so sach nhap theo ngay, thang, nam\n";
    cout << "9. Thong ke nha cung cap cung cap nhieu sach nhat\n";
    cout << "10. Bao cao nhap sach theo khoang thoi gian\n";
    cout << "11. Thoat\n";
    cout << "==========================\n";
    cout << "Chon mot tuy chon: ";
}

void pressAnyKeyToContinue() {
    cout << "\nNhan phim bat ky de quay lai menu...";
    _getch(); // Wait for a keypress without displaying the key
    system("cls");
}

int main() {
    BookStore store;

    // Load dữ liệu từ file
    store.loadNhaCungCap("DanhMucNhaCungCap.txt");
    store.loadSach("DanhMucSach.txt");
    store.loadPhieuNhapSach("PhieuNhapSach.txt"); 
    store.deletePhieuNhapBySoPhieu(9);
    store.deletePhieuNhapBySoPhieu(10);
    store.deletePhieuNhapBySoPhieu(11);

    int choice;
    do {
        printMenu();
        cin >> choice;
        if(choice < 1 || choice > 11) {
            cout << "Loi: Vui long chon tu 1 den 11.";
            cin.clear(); // Reset the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the line
        } else {
            switch (choice) {
                case 1: {
                    string tenNhaCungCap, maNhaCungCap, diaChi, soDienThoai;
                    cout << "Nhap ten nha cung cap: ";
                    cin.ignore(); // Xóa ký tự xuống dòng thừa để tránh lỗi getline()
                    getline(cin, tenNhaCungCap);
                    cout << "Nhap ma nha cung cap: ";
                    getline(cin, maNhaCungCap);
                    cout << "Nhap dia chi: ";
                    getline(cin, diaChi);
                    cout << "Nhap so dien thoai: ";
                    getline(cin, soDienThoai);
                    DMNhacungcap ncc(tenNhaCungCap, maNhaCungCap, diaChi, soDienThoai);
                    store.addNhaCungCap(ncc);
                    store.saveNhaCungCapToFile("DanhMucNhaCungCap.txt", ncc); // Save to file
                    pressAnyKeyToContinue(); // Wait for user input before returning to the menu
                    break;
                }
                case 2: {
                    string tenSach, maSachInput, tacGia, theloai, nhaXuatBan; // Changed nhaXuatBan to string
                    float giaSach;
    
                    cout << "Nhap ten sach: ";
                    cin.ignore(); // Xóa ký tự xuống dòng thừa để tránh lỗi getline()
                    getline(cin, tenSach);
                    cout << "Nhap ma sach: ";
                    getline(cin, maSachInput);
                    cout << "Nhap tac gia: ";
                    getline(cin, tacGia);
                    cout << "Nhap nha xuat ban: ";
                    getline(cin, nhaXuatBan); // Read nhaXuatBan as a string
                    cout << "Nhap the loai: ";
                    getline(cin, theloai);
    
                    cout << "Nhap gia sach: ";
                    while (!(cin >> giaSach)) {
                        cin.clear(); //
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Loi: Vui long nhap so thuc hop le.\nNhap lai: ";
                    }
    
                    DMSach sach(tenSach, maSachInput, tacGia, nhaXuatBan, theloai, giaSach);
                    store.addSach(sach);
                    store.saveSachToFile("DanhMucSach.txt", sach); // Save to file
                    pressAnyKeyToContinue(); // Wait for user input before returning to the menu
                    break;
                }
                case 3: {
                    string ngayNhap, maNhaCungCap, maSach;
                    int soLuong;
                    cout << "Nhap ngay nhap (Nhap theo format yyyy-mm-dd): ";
                    cin.ignore(); // Xóa ký tự xuống dòng thừa để tránh lỗi getline()
                    getline(cin, ngayNhap);
                    cout << "Nhap ma nha cung cap: ";
                    getline(cin, maNhaCungCap);
                    cout << "Nhap ma sach: ";
                    getline(cin, maSach);
    
                    cout << "Nhap so luong: ";
                    while (!(cin >> soLuong) || soLuong <= 0) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Loi: So luong phai la so nguyen duong.\nNhap lai: ";
                    }
    
                    PhieuNhapSach phieu(ngayNhap, maNhaCungCap, maSach, soLuong);
                    store.addPhieuNhapSach(phieu);
                    store.saveAllPhieuNhapToFile("PhieuNhapSach.txt"); // Save to file
                    pressAnyKeyToContinue(); // Wait for user input before returning to the menu
                    break;
                }
                case 4:
                    store.showNhaCungCap();
                    pressAnyKeyToContinue(); // Wait for user input before returning to the menu
                    break;
                case 5:
                    store.showSach();
                    pressAnyKeyToContinue(); // Wait for user input before returning to the menu
                    break;
                case 6:
                    store.showPhieuNhapSach();
                    pressAnyKeyToContinue(); // Wait for user input before returning to the menu
                    break;
                case 7: {
                    int soPhieu;
                    cout << "Nhap so phieu: ";
                    while (!(cin >> soPhieu) || soPhieu <= 0) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Loi: So phieu phai la so nguyen duong.\nNhap lai: ";
                    }
                    store.searchPhieuNhapSach(soPhieu);
                    pressAnyKeyToContinue(); // Wait for user input before returning to the menu
                    break;
                }
                case 8: {
                    // Thêm đoạn này:
                    int kieuThongKe;
                    cout << "Thong ke:\n1. Theo ngay\n2. Theo thang + nam\n3. Theo nam\nChon: ";
                    cin >> kieuThongKe;
                
                    if (kieuThongKe == 1) {
                        int d, m, y;
                        cout << "Nhap ngay: "; cin >> d;
                        cout << "Nhap thang: "; cin >> m;
                        cout << "Nhap nam: "; cin >> y;
                        thongKeTheoNgay(store.getPhieuList(), d, m, y);
                    } else if (kieuThongKe == 2) {
                        int m, y;
                        cout << "Nhap thang: "; cin >> m;
                        cout << "Nhap nam: "; cin >> y;
                        thongKeTheoThangNam(store.getPhieuList(), m, y);
                    } else if (kieuThongKe == 3) {
                        int y;
                        cout << "Nhap nam: "; cin >> y;
                        thongKeTheoNam(store.getPhieuList(), y);
                    } else {
                        cout << "Lua chon khong hop le.\n";
                    }
                    pressAnyKeyToContinue();
                    break;
                }
                case 9: {
                    thongKeNhaCungCapNhieuNhat(store.getPhieuList(), store.getNhaCungCapList());
                    pressAnyKeyToContinue();
                    break;
                }
                case 10: {
                    string ngayBatDau, ngayKetThuc;
                    cout << "Nhap ngay bat dau (yyyy-mm-dd): ";
                    cin >> ngayBatDau;
                    cout << "Nhap ngay ket thuc (yyyy-mm-dd): ";
                    cin >> ngayKetThuc;
                
                    taoBaoCaoNhapSachTheoKhoangThoiGian(store.getPhieuList(), ngayBatDau, ngayKetThuc, "BaoCaoNhapSach.txt");
                    pressAnyKeyToContinue();
                    break;
                }                           
                case 11:
                    cout << "Thoat chuong trinh. Tam biet!\n";
                    break;
            }
        }
    } while (choice != 11);

    return 0;
}


