# Demo: Mã vòng C(n,k)

File này hướng dẫn cách biên dịch, chạy và kiểm tra `Demo.cpp` — chương trình minh họa mã vòng trên GF(2).

## Tóm tắt

- File nguồn: `Demo.cpp`
- Ngôn ngữ: C++ (C++11/17)

## Biên dịch

Mở terminal trong thư mục dự án và chạy:

```bash
g++ -std=c++17 Demo.cpp -O2 -o demo
```

Hoặc (mặc định):

```bash
g++ -std=c++17 Demo.cpp -O2 -o a.out
```

## Định dạng đầu vào

Chương trình đọc 4 giá trị từ `stdin`:

1. `n` — chiều dài từ mã (integer)
2. `k` — chiều dài bản tin (integer)
3. `g` — đa thức sinh dưới dạng chuỗi nhị phân (ví dụ `1011` cho x^3 + x + 1)
4. `opt` — chế độ in: `1` = tự luận chi tiết, `2` = trắc nghiệm nhanh

Ví dụ:

```bash
echo "7 4 1011 2" | ./demo
```

## Thư mục `tests/`

Trong repository có thư mục `tests/` chứa các bộ test. Mỗi bộ test gồm hai file:

- `tests/testNN.in` — input mẫu
- `tests/testNN.out` — output mẫu

Để chạy tất cả test và sinh các file `.out` (nếu chưa có), dùng:

```bash
for f in tests/*.in; do ./demo < "$f" > "${f%.in}.out"; done
```

Hoặc chạy một test cụ thể:

```bash
./demo < tests/test01.in > tests/test01.out
```
