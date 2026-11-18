#include <iostream>
#include <queue>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

class Order {
private:
    struct Date {
        int ngay, thang, nam;
    };

    enum Status {
        ChoPheDuyet,
        DaDuyet,
        Huy,
        HoanThanh
    };

    string orderId;
    string customerName;
    Date createDate;
    double tongtien;
    Status trangthai;

public:
    Order(string id, string name, int ngay, int thang, int nam,
          double tien, Status status)
        : orderId(id), customerName(name),
          createDate{ngay, thang, nam},
          tongtien(tien), trangthai(status) {}

    string getOrderId() const { return orderId; }
    string getCustomerName() const { return customerName; }
    int getNgay() const { return createDate.ngay; }
    int getThang() const { return createDate.thang; }
    int getNam() const { return createDate.nam; }
    double getTongTien() const { return tongtien; }

    int getTrangThai() const { return static_cast<int>(trangthai); }

    string getTrangThaiText() const {
        switch (trangthai) {
            case ChoPheDuyet: return "Cho phe duyet";
            case DaDuyet:     return "Da duyet";
            case Huy:         return "Huy";
            case HoanThanh:   return "Hoan thanh";
        }
        return "Khong xac dinh";
    }

    static Order taoDon(string id, string name, int ngay, int thang,
                        int nam, double tien, int status) {
        Status s = ChoPheDuyet;
        if (status == 1) s = DaDuyet;
        else if (status == 2) s = Huy;
        else if (status == 3) s = HoanThanh;

        return Order(id, name, ngay, thang, nam, tien, s);
    }
};

bool namNhuan(int nam) {
    return (nam % 400 == 0) || (nam % 4 == 0 && nam % 100 != 0);
}

bool validateDate(int ngay, int thang, int nam) {
    if (nam < 1 || thang < 1 || thang > 12)
        return false;

    int soNgayTrongThang[] = {
        0, 31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    if (thang == 2 && namNhuan(nam))
        soNgayTrongThang[2] = 29;

    return ngay >= 1 && ngay <= soNgayTrongThang[thang];
}

string dateToString(int ngay, int thang, int nam) {
    string s = "";
    if (ngay < 10) s += "0";
    s += to_string(ngay) + "/";
    if (thang < 10) s += "0";
    s += to_string(thang) + "/" + to_string(nam);
    return s;
}

void displayOrders(queue<Order> ds) {
    if (ds.empty()) {
        cout << "Khong tim thay don hang phu hop!\n";
        return;
    }

    cout << left << setw(13) << "Ngay tao"
         << setw(12) << "Ma don"
         << setw(16) << "Tong tien"
         << setw(22) << "Khach hang"
         << "Trang thai\n";
    cout << string(78, '-') << '\n';

    while (!ds.empty()) {
        Order don = ds.front();
        ds.pop();

        cout << left
             << setw(13) << dateToString(don.getNgay(), don.getThang(), don.getNam())
             << setw(12) << don.getOrderId()
             << setw(16) << fixed << setprecision(0) << don.getTongTien()
             << setw(22) << don.getCustomerName()
             << don.getTrangThaiText() << '\n';
    }
}

void searchByDate(queue<Order> ds, int ngay, int thang, int nam) {
    if (!validateDate(ngay, thang, nam)) {
        cout << "Ngay thang khong hop le!\n";
        return;
    }

    queue<Order> ketQua;

    while (!ds.empty()) {
        Order don = ds.front();
        ds.pop();

        if (don.getNgay() == ngay &&
            don.getThang() == thang &&
            don.getNam() == nam) {
            ketQua.push(don);
        }
    }

    displayOrders(ketQua);
}

void filterByStatus(queue<Order> ds, int trangThaiCanTim) {
    if (trangThaiCanTim < 0 || trangThaiCanTim > 3) {
        cout << "Trang thai khong hop le!\n";
        return;
    }

    queue<Order> ketQua;

    while (!ds.empty()) {
        Order don = ds.front();
        ds.pop();

        if (don.getTrangThai() == trangThaiCanTim)
            ketQua.push(don);
    }

    displayOrders(ketQua);
}

queue<Order> taoDuLieuMau() {
    queue<Order> ds;

    ds.push(Order::taoDon("DH001", "Nguyen An", 10, 11, 2026, 500000, 0));
    ds.push(Order::taoDon("DH002", "Tran Binh", 10, 11, 2026, 750000, 1));
    ds.push(Order::taoDon("DH003", "Le Hoa", 11, 11, 2026, 300000, 2));
    ds.push(Order::taoDon("DH004", "Pham Minh", 11, 11, 2026, 900000, 3));
    ds.push(Order::taoDon("DH005", "Do Lan", 12, 11, 2026, 650000, 0));

    return ds;
}

int main() {
    queue<Order> dsDonHang = taoDuLieuMau();
    int chon;

    do {
        cout << "\n===== TIM KIEM VA LOC DON HANG =====\n";
        cout << "1. Xem tat ca don hang\n";
        cout << "2. Tim don hang theo ngay tao\n";
        cout << "3. Loc don hang theo trang thai\n";
        cout << "0. Thoat\n";
        cout << "Nhap lua chon: ";

        if (!(cin >> chon)) {
            cout << "Lua chon khong hop le!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            chon = -1;
            continue;
        }

        if (chon == 1) {
            displayOrders(dsDonHang);
        }
        else if (chon == 2) {
            int ngay, thang, nam;
            cout << "Nhap ngay thang nam (dd mm yyyy): ";
            if (!(cin >> ngay >> thang >> nam)) {
                cout << "Du lieu ngay thang khong hop le!\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                searchByDate(dsDonHang, ngay, thang, nam);
            }
        }
        else if (chon == 3) {
            int status;
            cout << "0. Cho phe duyet\n";
            cout << "1. Da duyet\n";
            cout << "2. Huy\n";
            cout << "3. Hoan thanh\n";
            cout << "Chon trang thai: ";

            if (!(cin >> status)) {
                cout << "Trang thai khong hop le!\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                filterByStatus(dsDonHang, status);
            }
        }
        else if (chon != 0) {
            cout << "Vui long chon lai!\n";
        }

    } while (chon != 0);

    cout << "Ket thuc chuong trinh.\n";
    return 0;
}
