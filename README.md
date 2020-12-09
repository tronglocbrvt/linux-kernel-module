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
- **Bước 2**: Biên dịch mã nguồn, tạo ra kernel module thông qua Makefile và Kbuild, bằng cách gõ lệnh
```terminal
make
```
- **Bước 3**: 
  - Kiểm tra danh sách các file có trong lúc thư mục lúc này, ta thấy có file ```random_gen.ko```:
  ```terminal
  ls
  ```
  - Để biết được các thông tin về module, ta sử dụng lệnh:
  ```terminal
  modinfo random_gen.ko
  ```
- **Bước 4**: 
  - Cấp quyền root:
  ```terminal
  sudo -s
  ```
  - Nhập mật khẩu để tiến hành xác thực và lấy quyền root.
 - **Bước 5**: Lắp module vào kernel
    - Ta sử dụng lệnh sau:
    ```terminal
    sudo insmod random_gen.ko
    ```
    - Ta có thể kiểm tra xem module đã được load thành công chưa bằng lệnh ```lsmod```.
    - Dùng lệnh ```dmesg``` để theo dõi quá trình hoạt động của module.
 - **Bước 6**: Thực hiện việc random số:
    - Ta sử dụng lệnh sau:
    ```terminal 
    ./random_gen_user
    ```
    - Nhập số từ 1-8 tương ứng với lựa chọn số byte mà người dùng mong muốn cho việc random số. Nếu muốn thoát nhập các số ngoài phạm vi 1 đến 8.
- **Bước 7**: Tháo module khỏi kernel:
```terminal
sudo rmmod random_gen.ko
```
- **Bước 8**: Dọn dẹp thư mục (dọn dẹp các file do Makefile và Kbuild tạo ra trước đó):
```terminal
make clean
```
