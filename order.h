#include <iostream>
using namespace std;

class Order {
private:
    struct Date
    {
        int ngay, thang, nam;
    };
    
    enum Status 
    {
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
};