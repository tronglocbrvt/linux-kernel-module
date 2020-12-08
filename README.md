# ĐỒ ÁN 02: TÌM HIỂU VÀ LẬP TRÌNH LINUX KERNEL MODULE - LỚP 18CNTN - FIT@HCMUS
## Thông tin thành viên
- 18120143: Nguyễn Đình Hoàng Phúc
- 18120151: Vũ Gia Tuệ
- 18120197: Trương Trọng Lộc
## Tóm tắt yêu cầu đồ án:
- Viết một module dùng để tạo ra số ngẫu nhiên. 
- Module này sẽ tạo một character device để cho phép các tiến trình ở userspace có thể open và read các số ngẫu nhiên.
## Hướng dẫn sử dụng chương trình: 
```Lưu ý: Trong đồ án này, nhóm sử dụng Termial của Ubuntu phiên bản 18.04.5 LTS để tiến hành thực hiện chương trình.```
- **Bước 1**: Di chuyển đến thư mục chứa ```source code``` đồ án bằng lệnh:
```terminal
cd random_generator
```
