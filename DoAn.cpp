#include <iostream>
#include <string>
#include <fstream>

using namespace std ;

// thong tin trong file input.txt 

/* 
7
Square: a=12.3
Circle: r=12.5
Square: a=7.6
Rectangle: w=3.1, h=4.2
Rectangle: w=6.15, h=8.4
Circle: r=5.77
Square: a=8.913 
*/

const double Pi = 3.14 ; // hang so Pi

// khai bao struct luu tru du lieu 3 hinh
struct ShapeType {
    string type ;
    union {
        struct {
            float a; // canh hinh vuong
        } Square ;

        struct {
            float r; // ban kinh hinh tron
        } Circle;

        struct {
            float w,h; // rong va dai cua hcn
        } Rectangle ;
    };
};

// ham doc file input theo dinh dang dc cho truoc
void readFile (ShapeType st[], int &n){
    // mo file
    ifstream filein ; 
    filein.open("input.txt", ios::in);

    // check file xem file da mo chua
    if (!filein.is_open()){
        cout <<"Khong the mo file !!!";
        return;
    }

    filein >> n ; // doc dong dau tien 
    filein.ignore(); // xuong dong

    for (int i = 0 ; i < n ; i++){
        string line ; // tao bien line
        
        // dung getline de gan toan bo gia tri cua dong cho bien line (lay ca dau cach)
        getline (filein, line); 
        
        size_t spaceIndex = line.find(' '); // tim vi tri dau space
        size_t equalIndex = line.find('='); // tim vi tri dau =

        // lay tu 0 toi vi tri dau cach - 1 (de loai bo dau :)
        st[i].type = line.substr(0, spaceIndex - 1);  ;

        if (st[i].type == "Square"){
            // dung ham stof de bien string thanh float
           st[i].Square.a = stof(line.substr(equalIndex + 1)) ;
        }

        if(st[i].type == "Circle"){
            // dung ham stof de bien string thanh float
            st[i].Circle.r = stof(line.substr(equalIndex + 1)); 

        }

        if (st[i].type == "Rectangle"){
            // tim vi tri cua dau = thu 2 sau dau = thu 1
            // vi rectangle co 2 gia tri 
            size_t equalIndex2 = line.find('=', equalIndex + 1);

            // tim vi tri dau phay 
            size_t commaIndex = line.find(',');

            // tach lay chieu rong
            // dung stof de ep kieu string ve float 
            st[i].Rectangle.w = stof(line.substr(equalIndex + 1, commaIndex - equalIndex - 1)) ;

            // tach lay chieu dai 
            st[i].Rectangle.h = stof(line.substr(equalIndex2 + 1));
        }
    }

    filein.close(); // dong file ;
}

// ham tinh chu vi, calculator perimeter
float calcP (const ShapeType &st){
    if (st.type == "Square"){
        return st.Square.a * 4 ; // chu vi hinh vuong
    }
    else if (st.type == "Circle"){
        return st.Circle.r * 2 * Pi ; // chu vi hinh tron
    }
    else if (st.type == "Rectangle"){
        return (st.Rectangle.w + st.Rectangle.h)*2 ; // chu vi hcn
    }
    else return 0.0; // tra ve 0.0 neu khong co hinh
}

// ham tinh dien tich, calculator area
float calcA (const ShapeType &st){
    if (st.type == "Square"){
        return st.Square.a * st.Square.a ; // dien tich hinh vuong 
    }
    else if (st.type == "Circle"){
        return st.Circle.r * st.Circle.r * Pi ; // dien tich hinh tron
    }
    else if (st.type == "Rectangle"){
        return (st.Rectangle.w * st.Rectangle.h) ; // dien tich hcn
    }
    else return 0.0; // tra ve 0.0 neu khong co hinh
}

// ham in ra min max va dem so luong hinh
void output (ShapeType st[], int n){
    int countS = 0, countR = 0, countC = 0 ; // bien dem so luong hinh

    // bien luu tru gia tri max min
    float maxChuVi = 0.0, maxDT = 0.0, minChuVi = INFINITY, minDT = INFINITY;

    // bien luu tru vi tri max min
    int maxIndexDT = -1, maxIndexCV = -1, minIndexDT = -1, minIndexCV = -1 ;

    for (int i = 0 ; i < n ; i++){
        // duyet hinh
        cout << st[i].type <<": ";
        if (st[i].type == "Square"){
            countS++; // tang bien dem neu la hv
            cout <<"a="<< st[i].Square.a <<" =>";
        }

        if (st[i].type == "Circle"){
            countC++; // tang bien dem neu la ht
            cout <<"r=" << st[i].Circle.r <<" =>";
        }

        if (st[i].type == "Rectangle"){
            countR++; // in bien dem neu la hcn
            cout <<"w=" << st[i].Rectangle.w <<", h="<< st[i].Rectangle.h <<" =>";
        }

        double chuvi = calcP(st[i]) ; // ham tinh chu vi
        double dientich = calcA(st[i]); // ham tinh dien tich

        cout <<" area="<< dientich <<" perimeter="<< chuvi <<" "<< endl ;

        // tim chuvi lon nhat
        if (chuvi > maxChuVi){
            maxChuVi = chuvi ; // cap nhat lai bien maxchuvi
            maxIndexCV = i ; // luu tru vi tri cua bien maxchuvi
        }

        if (dientich > maxDT){
            maxDT = dientich; // tuong tu
            maxIndexDT = i ;
        }

        if (chuvi < minChuVi){
            minChuVi = chuvi ; // tuong tu
            minIndexCV = i ;
        }

        if (dientich < minDT){
            minDT = dientich ; // tuong tu
            minIndexDT = i ;
        }
    }

    cout << endl ;
    
    // in ra chu vi lon nhat
    cout <<"Hinh co chu vi lon nhat: " << st[maxIndexCV].type;
    if (st[maxIndexCV].type == "Circle"){
        cout <<" r=" << st[maxIndexCV].Circle.r <<" => perimeter="<< maxChuVi << endl ;
    }
    if(st[maxIndexCV].type == "Square"){
        cout <<" a="<< st[maxIndexCV].Square.a <<" => perimeter="<< maxChuVi << endl ;
    }
    if(st[maxIndexCV].type == "Rectangle"){
        cout <<" w="<< st[maxIndexCV].Rectangle.w <<", h="<< st[maxIndexCV].Rectangle.h <<" => perimeter="<< maxChuVi << endl ;
    }


    // in ra dien tich lon nhat
    cout <<"Hinh co dien tich lon nhat: " << st[maxIndexDT].type;
    if (st[maxIndexDT].type == "Circle"){
        cout <<" r=" << st[maxIndexDT].Circle.r <<" => area="<< maxDT << endl ;
    }
    if(st[maxIndexDT].type == "Square"){
        cout <<" a="<< st[maxIndexDT].Square.a <<" => area="<< maxDT << endl ;
    }
    if(st[maxIndexDT].type == "Rectangle"){
        cout <<" w="<< st[maxIndexDT].Rectangle.w <<", h="<< st[maxIndexDT].Rectangle.h <<" => area="<< maxDT << endl ;
    }

    // in ra chu vi nho nhat
    cout <<"Hinh co chu vi nho nhat: " << st[minIndexCV].type;
    if (st[minIndexCV].type == "Circle"){
        cout <<" r=" << st[minIndexCV].Circle.r <<" => perimeter="<< minChuVi << endl ;
    }
    if(st[minIndexCV].type == "Square"){
        cout <<" a="<< st[minIndexCV].Square.a <<" => perimeter="<< minChuVi << endl ;
    }
    if(st[minIndexCV].type == "Rectangle"){
        cout <<" w="<< st[minIndexCV].Rectangle.w <<", h="<< st[minIndexCV].Rectangle.h <<" => perimeter="<< minChuVi << endl ;
    }


    // in ra dien tich nho nhat
    cout <<"Hinh co dien tich nho nhat: " << st[minIndexDT].type;
    if (st[minIndexDT].type == "Circle"){
        cout <<" r=" << st[minIndexDT].Circle.r <<" => area="<< minDT << endl ;
    }
    if(st[minIndexDT].type == "Square"){
        cout <<" a="<< st[minIndexDT].Square.a <<" => area="<< minDT << endl ;
    }
    if(st[minIndexDT].type == "Rectangle"){
        cout <<" w="<< st[minIndexDT].Rectangle.w <<", h="<< st[minIndexDT].Rectangle.h <<" => area="<< minDT << endl ;
    }

    cout << endl;

    cout <<"Thong ke cac hinh da doc: "<< endl ;
    cout <<"+ Square: "<< countS << endl ;
    cout <<"+ Rectangle: "<< countR << endl ;
    cout <<"+ Circle: "<< countC << endl ;

}

int main() {
    ShapeType st[100];
    int n = 0;
    readFile(st, n);
    output(st, n);
    return 0;
}
