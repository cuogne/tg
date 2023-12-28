/*Khai báo cấu trúc diểm trong hệ tọa độ 2D, với tung độ và hoành độ là số thực
Sinh viên hãy viết hàm để thực hiện các yêu cầu sau:
a) (1 điểm) Khai báo (các) cấu trúc (struct) cần thiết để thể hiện các thông tin liên quan.
b) (1 điểm) Nhập danh sách các điểm từ bàn phím.
c) (1 điểm) Tìm tất cả các bộ 3 điểm tạo thành tam giác hợp lệ trong danh sách (b) 
và in ra màn hình tọa độ 3 điểm.
d) (1 điểm) Viết hàm tính diện tích tam giác.
e) (1 điểm) Xuất danh sách các tam giác hợp lệ dưới dạng tọa độ các điểm và diện tích 
tương ứng được sắp xếp theo diện tích tăng dần ra output. txt (tập tin văn bản).
*/

#include <iostream>
#include <cmath>
#include <fstream>

using namespace std ;

// khai bao struct diem 
struct Point {
    float x,y ;
};

struct Triangle {
    Point a,b,c ;
    double dt ;
};


// ham nhap toa do diem
void inputPoint (Point pt[], int &n){
    cout <<"Nhap so luong diem: "; cin >> n ;
    for (int i = 0 ; i < n ; i++){
        cout <<"Nhap toa do diem " << i + 1 <<": "; 
        cin >> pt[i].x >> pt[i].y ;
    }
}

// ham ktra xem 3 diem co thang hang kh
bool ThangHang (const Point &a, const Point &b, const Point &c){
    return ((a.x - b.x) * (c.y - b.y) != (a.y - b.y) * (c.x - b.x));
}


// ham tinh dien tich tam giac = cong thuc heron
double areaTriangle(const Point &a, const Point &b, const Point &c){
    return std::abs((a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y)) / 2.0);
}

// ham sap xep dien tich tam giac tang dan deu
void BBS_Triangle(Triangle tg[], int n){
    for (int i = 0 ; i < n ; i++){
        for (int j = 0 ; j < n - i - 1 ; j++){
            if (tg[j].dt > tg[j+1].dt){
                swap(tg[j], tg[j+1]);
            }
        }
    }
}

// ham xuat cac danh sach hop le va dien tich tuong ung 
void outputTrianglesToFile (Triangle tg[], int n, const char* fileName){
    ofstream outputFile (fileName);
    if (outputFile.is_open()){
        outputFile <<"Danh sach cac tam giac hop le " << endl ;

        for (int i = 0 ; i < n ; i++){
            outputFile << "Tam giac thu " << i + 1 << ": (" << tg[i].a.x << ", " << tg[i].a.y << "), (" << tg[i].b.x << ", " << tg[i].b.y << "), (" << tg[i].c.x << ", " << tg[i].c.y << ")" <<" ";
            outputFile << "Dien tich: " << tg[i].dt << endl;
        }

        outputFile.close();
        cout <<"Da ghi vao tep !!!";
    }
    else {
        cout <<"Ghi that bai" << endl ;
    }

}

int main () {
    int n ; 
    Point pt[100];
    Triangle tg[100];
    inputPoint(pt,n);

    int numTriangles = 0 ;
    for (int i = 0 ; i < n - 2 ; i++){
        for (int j = i + 1 ; j < n - 1 ; j++){
            for (int k = j + 1 ; k < n ; k++){
                if(ThangHang(pt[i], pt[j], pt[k])){
                    tg[numTriangles].a = pt[i];
                    tg[numTriangles].b = pt[j];
                    tg[numTriangles].c = pt[k];
                    tg[numTriangles].dt = areaTriangle(pt[i],pt[j],pt[k]);
                    numTriangles++;
                }
            }
        }
    }


    BBS_Triangle(tg,n);
    outputTrianglesToFile(tg,n,"output.txt");
    return 0 ;
}