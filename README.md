# BÀI TẬP LỚN – CẤU TRÚC DỮ LIỆU VÀ GIẢI THUẬT

## ĐỀ TÀI: QUẢN LÝ ĐƠN HÀNG TRỰC TUYẾN

## 1. Giới thiệu

Dự án xây dựng chương trình quản lý đơn hàng trực tuyến bằng ngôn ngữ C++, vận dụng kiến thức lập trình hướng đối tượng và cấu trúc dữ liệu trong môn Cấu trúc dữ liệu và Giải thuật.

Chương trình hỗ trợ quản lý thông tin đơn hàng, tìm kiếm, xử lý đơn hàng theo nguyên tắc FIFO và thống kê dữ liệu.

## 2. Công nghệ sử dụng

- Ngôn ngữ lập trình: C++.
- Chuẩn C++: C++17.
- Trình biên dịch: GCC (g++).
- Môi trường phát triển: Visual Studio Code.

## 3. Cấu trúc dữ liệu

Dự án sử dụng các cấu trúc dữ liệu chính:

- **Class Order:** Biểu diễn và quản lý thông tin của một đơn hàng.
- **Vector:** Lưu trữ và quản lý danh sách đơn hàng.
- **Queue:** Quản lý thứ tự xử lý đơn hàng theo nguyên tắc FIFO.
- **Singly Linked List:** Cài đặt cấu trúc Queue thông qua danh sách liên kết đơn.

## 4. Các chức năng chính

- Quản lý đơn hàng: Thêm, xóa và hiển thị đơn hàng.
- Tìm kiếm đơn hàng theo ngày tạo hoặc trạng thái.
- Xử lý đơn hàng theo nguyên tắc FIFO.
- Phê duyệt, hủy và hoàn thành đơn hàng.
- Thống kê tổng số đơn hàng, tổng giá trị và số lượng đơn theo từng trạng thái.

## 5. Cấu trúc source code

| Tệp tin | Chức năng |
|---|---|
| main.cpp | Khởi tạo chương trình và điều hướng menu |
| order.h / order.cpp | Quản lý thông tin đơn hàng |
| orderqueue.h / orderqueue.cpp | Cài đặt cấu trúc hàng đợi |
| orderManager.h / orderManager.cpp | Quản lý dữ liệu và điều phối nghiệp vụ |
| orderCRUD.cpp | Các thao tác thêm, xóa và hiển thị |
| orderProcessing.cpp | Xử lý đơn hàng và cập nhật trạng thái |
| orderSearch.cpp | Tìm kiếm đơn hàng |
| orderStatistics.cpp | Thống kê đơn hàng |

## 6. Hướng dẫn biên dịch và chạy chương trình

### Yêu cầu
- Đã cài đặt trình biên dịch GCC (g++).
- Hỗ trợ chuẩn C++17 trở lên.

### Bước 1: Clone repository

```bash
git clone https://github.com/ChrisCatspher/BaiTapLon_CauTrucDuLieu-GiaiThuat_QuanLiDonHangTrucTuyen.git
cd BaiTapLon_CauTrucDuLieu-GiaiThuat_QuanLiDonHangTrucTuyen
```

### Bước 2: Biên dịch chương trình

```bash
g++ -std=c++17 -g main.cpp order.cpp orderqueue.cpp orderManager.cpp orderCRUD.cpp orderProcessing.cpp OrderSearch.cpp orderStatistics.cpp InputUtils.cpp -o program
```

### Bước 3: Chạy chương trình

Trên Linux:

```bash
./program
```

Trên Windows:

```bash
program.exe
```

## 7. Mục đích thực hiện

Dự án giúp nhóm vận dụng kiến thức về lập trình hướng đối tượng, quản
