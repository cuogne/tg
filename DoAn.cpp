#include <iostream>
#include <fstream>
#include <string>
using namespace std ;

const double Pi = 3.14 ; // hang so Pi

// khai bao struct luu tru du lieu 3 hinh
struct ShapeType {
    char type[20];
    union {
        struct {
            double a; // canh hinh vuong
        } Square ;

        struct {
            double r; // ban kinh hinh tron
        } Circle;

        struct {
            double w,h; // rong va dai cua hcn
        } Rectangle ;
    };
};

void docFile (ShapeType st[], int &n){
    // doc file
    ifstream filein ;
    filein.open("input.txt", ios::in);

    filein >> n ; // doc dong dau tien la 1 so cua file
    filein.ignore(); // xuong dong
    
    for (int i = 0 ; i < n ; i++){
        filein.getline(st[i].type,20,':');
        // duyet tu dau toi dau : de xem do la hinh gi
        // neu la hinh vuong
        if (strcmp(st[i].type, "Square") == 0){
            filein.ignore(3); // bo qua 3 ki tu (space)a=
            filein >> st[i].Square.a ; // gan gia tri canh
            filein.ignore(); // xuong dong
        }

        // neu la hinh tron
        if (strcmp(st[i].type, "Circle") == 0){
            filein.ignore(3); // bo qua 3 ki tu (space)r=
            filein >> st[i].Circle.r; // gan ban kinh
            filein.ignore(); // xuong dong
        }

        // neu la hcn
        if (strcmp(st[i].type, "Rectangle") == 0){
            filein.ignore(3); // bo qua 3 ki tu (space)w=
            filein >> st[i].Rectangle.w ;
            filein.ignore(4); // bo qua 4 ki tu la ,(space)h=
            filein >> st[i].Rectangle.h ;
            filein.ignore();// xuong dong
        }
    }
    filein.close();
}

// ham tinh chu vi
double calcChuVi ( const ShapeType &st){
    if (strcmp(st.type, "Square") == 0){
        return st.Square.a * 4 ; // chu vi hinh vuong = canh * 4
    }
    else if (strcmp(st.type,"Rectangle") == 0){
        return (st.Rectangle.w + st.Rectangle.h)*2 ;
        // chuvi hcn = (dai + rong)*2
    }
    else if (strcmp(st.type, "Circle") == 0){
        return (st.Circle.r * 2 * Pi);
        // chuvi hinh tron = bankinh * 2 * pi
    }
    else return 0.0 ;
}

// ham tinh dien tich
double calcDienTich (const ShapeType &st){
    if (strcmp(st.type, "Square") == 0){
        return st.Square.a * st.Square.a ;
        // dt hv = canh * canh
    }
    else if (strcmp(st.type,"Rectangle") == 0){
        return st.Rectangle.w * st.Rectangle.h ;
        // dt hcn = dai * rong
    }
    else if (strcmp(st.type, "Circle") == 0){
        return (st.Circle.r * st.Circle.r * Pi);
        // dt hinh tron = ban kinh * ban kinh * pi
    }
    else return 0.0 ;
}

void output (ShapeType st[], int n){
    int tempCircle = 0 ; // dem so luong hinh tron
    int tempSquare = 0; // dem so luong hinh vuong
    int tempRectangle = 0; // dem so luong hcn
    double maxChuVi, maxDienTich = 0.0; // bien tim max chu vi va dt
    double minChuVi = INFINITY ; // bien min gan = vo cuc
    double minDienTich = INFINITY ; // nhu tren
    int maxChuViIndex, minChuViIndex, maxAreaIndex, minAreaIndex = -1 ;
    // bien nay se tim vi tri cua hinh lon nhat or nho nhat

    for (int i = 0 ; i < n ; i++){
        cout << st[i].type ; // in ra loai hinh

        if (strcmp(st[i].type, "Square") == 0){
            cout <<" "<<"a="<< st[i].Square.a <<" "<<"=> ";
            tempSquare++;
        }

        else if (strcmp(st[i].type, "Rectangle") == 0){
            cout <<" "<<"w="<< st[i].Rectangle.w <<" "<<"h="<<
            st[i].Rectangle.h <<" "<<"=> ";
            tempRectangle++;
        }

        else if (strcmp(st[i].type, "Circle") == 0){
            cout <<" "<<"r="<< st[i].Circle.r <<" "<<" =>";
            tempCircle++;
        }

        double chuvi = calcChuVi(st[i]); // tinh chuvi
        double dientich = calcDienTich(st[i]); // tinh dientich

        cout <<" Perimeter="<< chuvi <<" "<<"Area="<< dientich << endl ;

         if (chuvi > maxChuVi){
            maxChuVi = chuvi ;
            maxChuViIndex = i ; // gan vi tri max 
        }

        if (chuvi < minChuVi){
            minChuVi = chuvi ;
            minChuViIndex = i ;
        }

        if (dientich > maxDienTich){
            maxDienTich = dientich;
            maxAreaIndex = i ;
        }

        if (dientich < minDienTich){
            minDienTich = dientich ;
            minAreaIndex = i ;
        }
    }

    // chu vi lon nhat
    cout <<"Hinh co chu vi lon nhat: " << st[maxChuViIndex].type <<" ";
    if (strcmp(st[maxChuViIndex].type, "Square") == 0){
        cout <<"a = " << st[maxChuViIndex].Square.a ;
     }
    else if (strcmp(st[maxChuViIndex].type, "Rectangle") == 0){
         cout <<"w = " << st[maxChuViIndex].Rectangle.w <<" "<<"h = " 
         << st[maxChuViIndex].Rectangle.h ;
    }
    else if (strcmp(st[maxChuViIndex].type, "Circle") == 0){
        cout <<"r = " << st[maxChuViIndex].Circle.r ;
    }
    cout <<" => chuvi = " << maxChuVi << endl ;


    // chu vi nho nhat
    cout <<"Hinh co chu vi nho nhat: " << st[minChuViIndex].type <<" ";
    if (strcmp(st[minChuViIndex].type, "Square") == 0){
        cout <<"a = " << st[minChuViIndex].Square.a ;
    }
    else if (strcmp(st[minChuViIndex].type, "Rectangle") == 0){
        cout <<"w = " << st[minChuViIndex].Rectangle.w <<" "<<"h = " 
        << st[minChuViIndex].Rectangle.h ;
    }
    else if (strcmp(st[minChuViIndex].type, "Circle") == 0){
        cout <<"r = " << st[minChuViIndex].Circle.r ;
    }
    cout <<" => chuvi = " << minChuVi << endl ;        


    // max dien tich
    cout <<"Hinh co dien tich lon nhat: " << st[maxAreaIndex].type <<" ";
    if (strcmp(st[maxAreaIndex].type, "Square") == 0){
        cout <<"a = " << st[maxAreaIndex].Square.a ;
     }
    else if (strcmp(st[maxAreaIndex].type, "Rectangle") == 0){
        cout <<"w = " << st[maxAreaIndex].Rectangle.w <<" "<<"h = " 
        << st[maxAreaIndex].Rectangle.h ;
    }
    else if (strcmp(st[maxAreaIndex].type, "Circle") == 0){
        cout <<"r = " << st[maxAreaIndex].Circle.r ;
    }
    cout <<" => Dien tich = " << maxDienTich << endl ;


    // min dien tich 
    cout <<"Hinh co dien tich nho nhat: " << st[minAreaIndex].type <<" ";
    if (strcmp(st[minAreaIndex].type, "Square") == 0){
        cout <<"a = " << st[minAreaIndex].Square.a ;
     }
    else if (strcmp(st[minAreaIndex].type, "Rectangle") == 0){
        cout <<"w = " << st[minAreaIndex].Rectangle.w <<" "<<"h = " 
        << st[minAreaIndex].Rectangle.h ;
    }
    else if (strcmp(st[minAreaIndex].type, "Circle") == 0){
        cout <<"r = " << st[minAreaIndex].Circle.r ;
    }
    cout <<" => Dien tich = " << minDienTich << endl ;
        
    
    cout <<"Thong ke so luong hinh da doc: " << endl ;
    cout <<"So hinh vuong: " << tempSquare << endl ;
    cout <<"So hinh chu nhat: " << tempRectangle << endl ;
    cout <<"So hinh tron: " << tempCircle << endl ;
}

int main () {
    ShapeType st[100];
    int n = 0 ;
    docFile(st,n);
    output(st,n);
    return 0 ;
}