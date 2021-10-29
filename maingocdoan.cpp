/*
    Mai Ngọc Đoàn: chào anh em.
    Bài này tôi làm cho vui với mục đích hỗ trợ ae mấy bài dễ này ( thầy khóa chế độ kéo thả trên excel ), lúc thi thì không kể đâu được,
    đang ma số tự nhiên bấm sai số thứ 6 sau dấu phẩy thôi cũng đủ sai rồi.
    Hoặc đang thi trục trặc hay quên công thức lại khổ.
    Những bài như nội suy, lagarang, xấp xỉ picard thì buộc làm bằng mathematica rồi, bạn nào siêu nhân thì làm tay^^
    Mấy bài xấp xỉ trung bình phương rời rạc, sai phân thầy có mở excel chế độ kéo thả nên làm luôn vào đấy đỡ phải chép.
    DÙNG EXCEL MẤY BÀI NÀY HOÀN TOÀN LÀM ĐƯỢC

    KHÔNG DÀNH CHO CÁC BẠN GIỎI^^ 
*/
#include <iostream>
#include <valarray>
#include <vector>
#include <algorithm>
#include <math.h>
#include <iomanip>
using namespace std;
// viết dạng hàm vào chỗ return
double myFunction(double x) // x là ẩn số 
{
    return 2*pow(x,3) - 2*x - 2.1 ; // ví dụ ta có hàm số y = 2*x^3 - 2*x -2.1
    /*

    */
}
// đạo hàm hàm y
double myDerivation(double x) // x là ẩn số 
{
    return 6*x*x - 2 ; // ví dụ ta có đạo hàm hàm số trên
}
// hàm dùng cho phương pháp chia đôi:
double ppChiaDoi( double(*funct)(double), double, double, int, double );
// hàm dùng cho phương pháp newton
double ppNewton( double(*funct)(double), double (*derived)(double), double, int);
// hàm dùng cho phương pháp lặp đơn
double ppLapDon( double(*funct)(double), double, int, double, double ssCanTinh = -1);
// tính đạo hàm cấp 1, độ chính xác cấp1
void   dhC1_1( const vector<double>&, const vector<double>& );
// tính đạo hàm cấp 1, độ chính xác cấp 2
void   dhC1_2(const vector<double>&, const vector<double>&, double );
// tính đạo hàm cấp 2 độ chính xác cấp 2
void   dhC2_2( const vector<double>&, const vector<double>& , double );
// tính gần đúng tích phân bằng công thức hình thang
void   ctHinhThang( const vector<double>& , double );
// tính gần đúng tích phân bằng công thức hình thang
void   ctSimpson( const vector<double>& , double );
// sẽ cập nhật thêm phần Euler và RungeKutta.
int main(){
    // ppChiaDoi(myFunction,1,3,10,0.000001);
    // ppNewton(myFunction,myDerivation,3,10);
    // ppLapDon(myFunction,0,10,0.5,0.0000002);
    // dhC2_2({0.6, 0.8, 1, 1.2, 1.4, 1.6},{0.65, 1.74, 3, 4.7, 6.8, 9.3},0.2);
    // ctHinhThang({7, 8.2, 9.4, 9.8, 10.6, 10.2, 9.2},0.2);
    // ctSimpson({7, 8.2, 9.4, 9.8, 10.6, 10.2, 9.2},0.2);


    return 0;
}
// hàm y = f(x)

double ppChiaDoi( double(*funct)(double),double a, double b, int n, double ssCanTinh = -1)
{   /*
        @param: 
            + funct : hàm số của đề các bạn
            + a,b là khoảng tách nghiệm (a,b)
            + n là số lần lặp
            + ssCanTinh: mỗi đề sẽ có câu hỏi như: cần lặp bao nhiêu lần để sai số là x..., nếu muốn 
            tính luôn thì thêm giá trị sai số vào
    */
    double ak = a;
    double bk = b;
    double saiso = abs((a-b)/pow(2,n));
    double k = ceil( log2( abs((b - a)) / ssCanTinh ) );
    for ( int i = 0; i <= n ; i ++){
        double ck = (ak+bk)/2;
        double mul = funct(ak)*funct(ck);
        cout << "i: ";
        cout << setw(4) << left << i + 1;
        cout << "ak: ";
        cout << setw(10) << left <<  setprecision(6) << ak;
        cout << "bk: ";
        cout << setw(10) << left << setprecision(6) << bk;
        cout << "ck: ";
        cout << setw(10) << left <<  setprecision(6) << ck;
        cout << "f(ak)*f(ck): ";
        cout << setw(10) << left << setprecision(6) << fixed << mul;
        if ( i < n )
            ( funct(ak)*funct(ck) < 0 ) ? bk = ck : ak = ck;
        cout<<endl;
    }
    cout << "Nghiem gan dung: " << (bk+ak)/2 << endl;
    cout << "Sai so sau " << n << " lan lap: "<< saiso << endl;
    if ( ssCanTinh != -1 )
        cout << "Can lap "<< k << " lan de co sai so "<< fixed << ssCanTinh << endl;
    return saiso;
}
double ppNewton( double(*funct)(double), double (*derived)(double) ,  double fourier, int n)
{
      /*
        @param: 
            + funct : hàm số của đề các bạn
            + derived : đạo hàm hàm funct
            + fourier : điểm x0 hay còn gọi là điểm fourier (  tìm điểm fourier: f(a)*f''(a) > 0 ? a : b; )
            + n là số lần lặp
            *** bài này các bạn tự tính sai số nhé
    */

    for ( int i = 0 ; i <= n ; i++ ){
        cout << "i: ";
        cout << left << setw(7) << i+1;
        cout << "X["<<i+1<<"] = " << setprecision(6) << fixed << fourier << endl;
        fourier = fourier - funct(fourier)/derived(fourier);
    }
    // phần này tự tính sai số nha
    return fourier;
}
double ppLapDon( double(*funct)(double), double x0, int n, double q, double ssCanTinh)
{
    /*
        @param: 
            + funct : hàm Phi(x)
            + xO    : điểm bắt đầu
            + n     : số lần lặp
            + q     : 0 <= q <= 1, max đạo hàm của hàm funct
            + ssCanTinh : tương tự đã giải thích trên. 
            *** bài này các bạn tự tính sai số nhé
    */
   
    float x1;
    float xn = x0;
    for ( int i = 0; i <=n ; i++){
        cout << "i: ";
        cout << left << setw(7) << i+1;
        cout << "x["<<i<<"]: ";
        cout << left << setw(10) << setprecision(6) << fixed << xn;
        cout << endl; 
        if ( i < n )
            xn = funct(xn);
        if ( i == 0)
            x1 = xn;
    }
    if ( ssCanTinh != -1){
        float k = ceil( log10( ssCanTinh*(1-q)/abs(x1-x0) )/log10(q) );
        cout << "Can phai lap "<< setprecision(0) << k << " lan de co sai so "<< setprecision(10) <<ssCanTinh << endl;
    }
    return x0;
}
// Đạo hàm cấp 1 với độ chính xác cấp 1:
void dhC1_1  (const vector<double>& x, const vector<double>& y )
{
    /*
        @param: 
            + x : list các điểm trên đề bài, khi truyền vào hàm truyền theo dạng {1,2,32,3.....};
            + y : list các điểm y(x), khi truyền vào hàm truyền theo dạng {5,6,7,8...};
            
    */
   
    const int size = x.size();
    if ( size == y.size() ){
        for ( int i = 0; i < size - 1 ; i++){
            cout << "f'("<< x[i] << ") = " << (y[i+1] - y[i])/(x[i+1] - x[i])<<endl;
        }
    } else {
        cout << "x,y sai roi ban e!"<<endl;
    }
    return;
}
void dhC1_2   ( const vector<double>& x, const vector<double>& y , double h)
{
    /*
        @param: 
            + x : list các điểm trên đề bài, khi truyền vào hàm truyền theo dạng {1,2,32,3.....};
            + y : list các điểm y(x), khi truyền vào hàm truyền theo dạng {5,6,7,8...};
            + h : khoảng cách giữa 2 điểm x: x[k+1] - x[k]
            
    */
   
    const int size = x.size();
    if ( size == y.size() ){
        cout << "f'(x[0]) = " << (-y[2] + 4*y[1] - 3*y[0]) / (2*h) << endl;
        for ( int i = 1; i < size - 1; i++){
            cout << "f'(x["<<i<<"]) = " << (y[i+1] - y[i-1])/ (2*h) << endl;
        }
        cout << "f'(x["<<size-1<<"]) = " << (y[size - 3] - 4*y[size - 2] + 3*y[size-1]) / (2*h) << endl;
    } else {
        cout << "Nhap sai roi cac ban oi. "<<endl;
    }
    return;
}
void dhC2_2   ( const vector<double>& x, const vector<double>& y , double h)
{
    
    /*
        @param: 
            + x : list các điểm trên đề bài, khi truyền vào hàm truyền theo dạng {1,2,32,3.....};
            + y : list các điểm y(x), khi truyền vào hàm truyền theo dạng {5,6,7,8...};
            + h : khoảng cách giữa 2 điểm x: x[k+1] - x[k]
            
    */
   
    const int size = x.size();
    if ( size == y.size() ){
        cout << "f'(x[0]) = " << (-2*y[1] + y[2] + y[0]) / (h*h) << endl;
        for ( int i = 1; i < size - 1; i++){
            cout << "f'(x["<<i<<"]) = " << (y[i+1] - 2*y[i] + y[i-1])/ (h*h) << endl;
        }
        cout << "f'(x["<<size-1<<"]) = " << (y[size-1] - 2*y[size - 2] + y[size-3]) / (h*h) << endl;
    } else {
        cout << "Nhap sai roi cac ban oi. "<<endl;
    }
    return;
}
void ctHinhThang( const vector<double>& y, double h )
{
    /*
        @param: 
            + y : list các điểm y(x), khi truyền vào hàm truyền theo dạng {5,6,7,8...};
            + h : khoảng cách giữa 2 điểm x: x[k+1] - x[k]
            
    */
   
    float sum = 0;
    int  size = y.size();
    for ( int i = 1; i < size - 1; i++ ){
        sum += 2*y[i];
    }
    cout << "Gia tri gan dung tich phan: " << (h/2)*(y[0] + y[size -1] + sum )<<endl;
    return;
}
void ctSimpson( const vector<double>& y , double h)
{
    /*
        @param: 
            + y : list các điểm y(x), khi truyền vào hàm truyền theo dạng {5,6,7,8...};
            + h : khoảng cách giữa 2 điểm x: x[k+1] - x[k]
            
    */
    float sumOdd = 0, sumEven = 0;
    int size = y.size();
    for ( int i = 1; i < size - 1; i++){
        // cộng các y có chỉ số chẵn
        if ( i%2 == 0 ){
            sumEven += 2*y[i];
        } else {
            // cộng các y có chỉ số lẻ
            sumOdd += 4*y[i];
        }
    }
    cout << "Gia tri gan dung tich phan theo phuong phap Simpson: "<<(h/3)*( y[0] + y[size-1] + sumOdd + sumEven)<<endl;
    return;
}


