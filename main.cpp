#include <iostream>
#include <string>
#include "OrderManager.h"
#include "InputUtils.h"

using namespace std;

// ===== CAC HAM MENU =====

void displayMainMenu();
void displayCRUDMenu();
void displayProcessingMenu();
void displaySearchMenu();
void displayStatisticsMenu();

void CRUDMenu(OrderManager& manager);
void ProcessingMenu(OrderManager& manager);
void SearchMenu(OrderManager& manager);
void StatisticsMenu(OrderManager& manager);

// ===== KIEM TRA NGAY THANG =====

bool namNhuan(int nam) return (nam % 400 == 0) || (nam % 4 == 0 && nam % 100 != 0);

bool validateDate(int ngay, int thang, int nam) {
    if (nam < 1 || thang < 1 || thang > 12) return false;

    int soNgayTrongThang[] = {
        0, 31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    if (thang == 2 && namNhuan(nam)) soNgayTrongThang[2] = 29;
    return ngay >= 1 && ngay <= soNgayTrongThang[thang];
}

// ===== MAIN =====

int main() {
    OrderManager manager;
    int choice;

    do {
        displayMainMenu();
        choice = inputInt("Nhap lua chon: ");

        switch (choice) {
            case 1:
                CRUDMenu(manager);
                break;

            case 2:
                ProcessingMenu(manager);
                break;

            case 3:
                SearchMenu(manager);
                break;

            case 4:
                StatisticsMenu(manager);
                break;

            case 0:
                cout << "Ket thuc chuong trinh.\n";
                break;

            default:
                cout << "Lua chon khong hop le!\n";
        }

    } while (choice != 0);

    return 0;
}

// ===== MENU CHINH =====

void displayMainMenu() {
    cout << "\n";
    cout << "====================================\n";
    cout << "    QUAN LY DON DAT HANG ONLINE\n";
    cout << "====================================\n";
    cout << "1. Quan ly don hang (CRUD)\n";
    cout << "2. Xu ly don hang (Queue)\n";
    cout << "3. Tim kiem don hang\n";
    cout << "4. Thong ke don hang\n";
    cout << "0. Thoat\n";
    cout << "====================================\n";
}

// ===== MENU CRUD =====

void displayCRUDMenu() {
    cout << "\n";
    cout << "========== QUAN LY DON HANG ==========\n";
    cout << "1. Them don hang\n";
    cout << "2. Xoa don hang\n";
    cout << "3. Tim don hang theo ma\n";
    cout << "4. Hien thi tat ca don hang\n";
    cout << "0. Quay lai\n";
    cout << "======================================\n";
}

void CRUDMenu(OrderManager& manager) {
    int choice;
    string id;

    do {
        displayCRUDMenu();
        choice = inputInt("Nhap lua chon: ");

        switch (choice) {
            case 1: {
                id = inputString("Nhap ma don hang: ");
                string name = inputString("Nhap ten khach hang: ");
                int ngay, thang, nam;

                while (true) {
                    cout << "Nhap ngay thang nam (dd mm yyyy): ";

                    ngay = inputInt("Ngay: ");
                    thang = inputInt("Thang: ");
                    nam = inputInt("Nam: ");

                    if (validateDate(ngay, thang, nam)) break;

                    cout << "Ngay thang khong hop le! Nhap lai.\n";
                }

                double tien = inputDouble("Nhap tong tien: ");

                Order order(id, name, ngay, thang, nam, tien, ChoPheDuyet);

                if (manager.addOrder(order)) cout << "Them don hang thanh cong!\n";
                else cout << "Ma don hang da ton tai hoac them that bai!\n";

                break;
            }

            case 2:
                id = inputString("Nhap ma don hang can xoa: ");

                if (manager.deleteOrder(id)) cout << "Xoa don hang thanh cong!\n";
                else cout << "Khong tim thay don hang!\n";

                break;

            case 3:
                id = inputString("Nhap ma don hang can tim: ");
                manager.displayOrder(id);
                break;

            case 4:
                manager.displayAllOrders();
                break;

            case 0:
                break;

            default:
                cout << "Lua chon khong hop le!\n";
        }

    } while (choice != 0);
}

// ===== MENU PROCESSING =====

void displayProcessingMenu() {
    cout << "\n";
    cout << "========== XU LY DON HANG ==========\n";
    cout << "1. Xu ly don tiep theo trong Queue\n";
    cout << "2. Phe duyet don hang theo ma\n";
    cout << "3. Huy don hang theo ma\n";
    cout << "4. Huy don dau Queue\n";
    cout << "5. Hoan thanh don hang\n";
    cout << "0. Quay lai\n";
    cout << "===================================\n";
}

void ProcessingMenu(OrderManager& manager) {
    int choice;
    string id;

    do {
        displayProcessingMenu();
        choice = inputInt("Nhap lua chon: ");

        switch (choice) {
            case 1:
                manager.processNext();
                break;

            case 2:
                id = inputString("Nhap ma don can phe duyet: ");

                if (manager.approveOrder(id)) cout << "Phe duyet thanh cong!\n";
                else cout << "Khong the phe duyet don hang!\n";

                break;

            case 3:
                id = inputString("Nhap ma don can huy: ");

                if (manager.cancelOrder(id)) cout << "Huy don hang thanh cong!\n";
                else cout << "Khong the huy don hang!\n";

                break;

            case 4:
                if (manager.cancelFrontOrder()) cout << "Da huy don dau Queue!\n";
                else cout << "Queue dang rong!\n";

                break;

            case 5:
                id = inputString("Nhap ma don can hoan thanh: ");

                if (manager.completeOrder(id)) cout << "Hoan thanh don hang thanh cong!\n";
                else cout << "Khong the hoan thanh don hang!\n";

                break;

            case 0:
                break;

            default:
                cout << "Lua chon khong hop le!\n";
        }

    } while (choice != 0);
}

// ===== MENU SEARCH =====

void displaySearchMenu() {
    cout << "\n";
    cout << "========== TIM KIEM DON HANG ==========\n";
    cout << "1. Tim theo ngay tao\n";
    cout << "2. Loc theo trang thai\n";
    cout << "0. Quay lai\n";
    cout << "=======================================\n";
}

void SearchMenu(OrderManager& manager) {
    int choice;
    int status;
    string date;

    do {
        displaySearchMenu();
        choice = inputInt("Nhap lua chon: ");

        switch (choice) {
            case 1:
                date = inputString("Nhap ngay (dd/mm/yyyy): ");
                manager.displayByDate(date);
                break;

            case 2:
                cout << "\n0. Cho phe duyet\n";
                cout << "1. Da duyet\n";
                cout << "2. Huy\n";
                cout << "3. Hoan thanh\n";

                status = inputInt("Nhap trang thai: ");

                if (status >= 0 && status <= 3) {
                    manager.displayByStatus(
                        static_cast<Status>(status)
                    );
                } else cout << "Trang thai khong hop le!\n";

                break;

            case 0:
                break;

            default:
                cout << "Lua chon khong hop le!\n";
        }

    } while (choice != 0);
}

// ===== MENU STATISTICS =====

void displayStatisticsMenu() {
    cout << "\n";
    cout << "========== THONG KE DON HANG ==========\n";
    cout << "1. Xem thong ke\n";
    cout << "0. Quay lai\n";
    cout << "=======================================\n";
}

void StatisticsMenu(OrderManager& manager) {
    int choice;

    do {
        displayStatisticsMenu();
        choice = inputInt("Nhap lua chon: ");

        switch (choice) {
            case 1:
                manager.getStatistics();
                break;

            case 0:
                break;

            default:
                cout << "Lua chon khong hop le!\n";
        }

    } while (choice != 0);
}
