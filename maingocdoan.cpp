/*
    Mai Ngọc Đoàn: chào anh em.
    Bài này tôi làm cho vui với mục đích hỗ trợ ae mấy bài dễ này ( thầy khóa chế độ kéo thả trên excel ), lúc thi thì không kể đâu được,
    đang ma số tự nhiên bấm sai số thứ 6 sau dấu phẩy thôi cũng đủ sai rồi.
    Hoặc đang thi trục trặc hay quên công thức lại khổ.
    Những bài như nội suy, lagarang, xấp xỉ picard thì buộc làm bằng mathematica rồi, bạn nào siêu nhân thì làm tay^^
    Mấy bài xấp xỉ trung bình phương rời rạc, sai phân thầy có mở excel chế độ kéo thả nên làm luôn vào đấy đỡ phải chép.
    DÙNG EXCEL MẤY BÀI NÀY HOÀN TOÀN LÀM ĐƯỢC

    KHÔNG DÀNH CHO CÁC BẠN GIỎI^^ 
    Ai thích thì lên đây, tôi làm thêm cái Euler với RungeKutta nha:
        github : https://github.com/jkdoandeptrai/THTT_MAINGOCDOAN
*/
#include <iostream>
#include <valarray>
#include <vector>
#include <algorithm>
#include <math.h>
#include <iomanip>
using namespace std;
// viết dạng hàm vào chỗ return
double myfunction(double x) // x là ẩn số 
{
    return x*x*x -2*x*x + 2*x -100 ; // ví dụ ta có hàm số y = 2*x^3 - 2*x -2.1
    /*

    */
}
// đạo hàm hàm y
double myDerivation(double x) // x là ẩn số 
{
    return 3*x*x - 4*x + 2 ; // ví dụ ta có đạo hàm hàm số trên
}
double myEulerfunction(double x, double y){
    return x*y + 3*x -2*y;
}
double myEulerfunctionY(double x, double y, double z){
    return 1.97 * x*x + 2*x -5.08*y + 1.67*z;
}
double myEulerfunctionU(double x, double y, double z){
    return -2.44 *x*x -3*x +2.74*y +0.87*z;
}
// hàm dùng cho phương pháp chia đôi:
double ppChiaDoi( double(*functY)(double), double, double, int, double );
// hàm dùng cho phương pháp newton
double ppNewton( double(*functY)(double), double (*derived)(double), double, int);
// hàm dùng cho phương pháp lặp đơn
double ppLapDon( double(*functY)(double), double, int, double, double ssCanTinh = -1);
// tính đạo hàm cấp 1, độ chính xác cấp1
void   dhC1_1( const vector<double>&, const vector<double>& );
// tính đạo hàm cấp 1, độ chính xác cấp 2
void   dhC1_2(const vector<double>&, const vector<double>&, double );
// tính đạo hàm cấp 2 độ chính xác cấp 2
void   dhC2_2( const vector<double>&, const vector<double>& , double );
// tính gần đúng tích phân bằng công thức hình thang
void   ctHinhThang(  const vector<double>&,const vector<double>& );
// tính gần đúng tích phân bằng công thức hình thang
void   ctSimpson( const vector<double>&,const vector<double>& );
void   ppEuler( double(*functY)(double,double) ,const vector<double>& x, double );
void   ppEulerHePT( double(*functY)(double, double, double) , double(*functU)(double, double, double) ,const vector<double>& , double, double);
double RungeKutta4(double(*funct)(double, double), vector<double>, double);




/*             -------------------------------------------------------------------------------------------------------------------*/
// sẽ cập nhật thêm phần Euler và RungeKutta.
int main(){
    //phương pháp chia đôi
        // ppChiaDoi(myfunction,2,3,10,0.00001);
    // phương pháp newton
        // ppNewton(myfunction,myDerivation,6,9);
    // phương pháp lặp đơn
        // ppLapDon(myfunction,0,16,0.395997,0.000001);
    //***************************************************
    // đạo hàm cấp 1 với độ chính xác cấp 1:
    dhC1_1({4,4.2,4.4,4.6,4.8,5,5.2},
           {7,8.2,9.4,9.8,10.6,10.2,9.2});
    // //***************************************************
    //     dhC1_2({4,4.2,4.4,4.6,4.8,5,5,2},
    //     {7,8.2,9.4,9.8,10.6,10.2,9.2},0.2);
    // //***************************************************
    dhC2_2({4,4.2,4.4,4.6,4.8,5,5.2},
        {7,8.2,9.4,9.8,10.6,10.2,9.2},0.2);
    //***************************************************

    ctHinhThang({4,4.2,4.4,4.6,4.8,5,5.2},{7,8.2,9.4,9.8,10.6,10.2,9.2});
    //***************************************************

    ctSimpson({4,4.2,4.4,4.6,4.8,5,5.2},{7,8.2,9.4,9.8,10.6,10.2,9.2});
    //***************************************************

    // ppEuler(myEulerfunction,{2,2.1,2.3,2.6,2.7,2.9,3,3.3,3.4,3.8,4},0.4);
    //***************************************************
    // cout << endl;
    // ppEulerHePT(myEulerfunctionY,myEulerfunctionU,{0,0.1,0.3,0.4,0.7,0.8,1},4.11,1.7);
    //***************************************************

    // RungeKutta4(myEulerfunction,{2,2.1,2.3,2.6,2.7,2.9,3,3.3,3.4,3.8,4},0.4);
    // last modified: 10:39, thu 6.
    return 0;
}








/*---------------------------------------------------------------------------------------------------------------------------------------*/
double ppChiaDoi( double(*functY)(double),double a, double b, int n, double ssCanTinh = -1)
{   /*
        @param: 
            + functY : hàm số của đề các bạn
            + a,b là khoảng tách nghiệm (a,b)
            + n là số lần lặp
            + ssCanTinh: mỗi đề sẽ có câu hỏi như: cần lặp bao nhiêu lần để sai số là x..., nếu muốn 
            tính luôn thì thêm giá trị sai số vào
    */
    double ak = a;
    double bk = b;
    double saiso = abs((a-b)/pow(2,n));
    double k = ceil( log2( abs((b - a)) / ssCanTinh ) );
    cout << fixed << setprecision(6);
    for ( int i = 0; i <= n ; i ++){
        double ck = (ak+bk)/2;
        double mul = functY(ak)*functY(ck);
        cout << "i: ";
        cout << setw(4) << left << i + 1;
        cout << "ak: ";
        cout << setw(10) << left << ak;
        cout << "bk: ";
        cout << setw(10) << left << bk;
        cout << "ck: ";
        cout << setw(10) << left << ck;
        cout << "f(ak)*f(ck): ";
        cout << setw(10) << left << mul;
        if ( i < n )
            ( functY(ak)*functY(ck) < 0 ) ? bk = ck : ak = ck;
        cout<<endl;
    }
    cout << "Nghiem gan dung: " << (bk+ak)/2 << endl;
    cout << "Sai so sau " << n << " lan lap: "<< saiso << endl;
    if ( ssCanTinh != -1 )
        cout << "Can lap "<< setprecision(0) << k << " lan de co sai so "<< setprecision (10) << ssCanTinh << endl;
    return saiso;
}
double ppNewton( double(*functY)(double), double (*derived)(double) ,  double fourier, int n)
{
      /*
        @param: 
            + functY : hàm số của đề các bạn
            + derived : đạo hàm hàm functY
            + fourier : điểm x0 hay còn gọi là điểm fourier (  tìm điểm fourier: f(a)*f''(a) > 0 ? a : b; )
            + n là số lần lặp
            *** bài này các bạn tự tính sai số nhé
    */

    for ( int i = 0 ; i <= n ; i++ ){
        cout << "i: ";
        cout << left << setw(7) << i+1;
        cout << "X["<<i+1<<"] = " << setprecision(6) << fixed << fourier << endl;
        fourier = fourier - functY(fourier)/derived(fourier);
    }
    // phần này tự tính sai số nha
    return fourier;
}
double ppLapDon( double(*functY)(double), double x0, int n, double q, double ssCanTinh)
{
    /*
        @param: 
            + functY : hàm Phi(x)
            + xO    : điểm bắt đầu
            + n     : số lần lặp
            + q     : 0 <= q <= 1, max đạo hàm của hàm functY
            + ssCanTinh : tương tự đã giải thích trên. 
            *** bài này các bạn tự tính sai số nhé
    */
   
    double x1;
    double xn = x0;
    for ( int i = 0; i <=n ; i++){
        cout << "i: ";
        cout << left << setw(7) << i+1;
        cout << "x["<<i<<"]: ";
        cout << left << setw(10) << setprecision(6) << fixed << xn;
        cout << endl; 
        if ( i < n )
            xn = functY(xn);
        if ( i == 0)
            x1 = xn;
    }
    if ( ssCanTinh != -1){
        double k = ceil( log10( ssCanTinh*(1-q)/abs(x1-x0) )/log10(q) );
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
        cout << fixed << setprecision(6);
        for ( int i = 0; i < size - 1 ; i++){
            cout << "f'("<< x[i] << ") = "  << (y[i+1] - y[i])/(x[i+1] - x[i])<<endl;
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
        cout << setprecision(6) << fixed ;
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
        cout << fixed << setprecision(6) ;
        cout << "f''(x[0]) = " << (-y[3] +4*y[2] - 5*y[1] +2*y[0]) / (h*h) << endl;
        for ( int i = 1; i < size - 1; i++){
            cout << "f''(x["<<i<<"]) = " << (y[i+1] - 2*y[i] + y[i-1])/ (h*h) << endl;
        }
        cout << "f''(x["<<size-1<<"]) = " << abs((y[size - 4] - 4*y[size -3] + 5*y[size -2] -2*y[size -1]) / (h*h) ) << endl;
    } else {
        cout << "Nhap sai roi cac ban oi. "<<endl;
    }
    return;
}
void ctHinhThang( const vector<double>& x,const vector<double>& y)
{
    /*
        @param: 
            + y : list các điểm y(x), khi truyền vào hàm truyền theo dạng {5,6,7,8...};
            
    */
   
    double sum = 0;
    int  size = y.size();
    cout << fixed << setprecision(6);
    for ( int i = 0; i < size - 1; i++ ){
        sum += ((x[i+1]-x[i])/2)*(y[i+1]+y[i]);
    }
    cout << "Gia tri gan dung tich phan: " << sum <<endl;
    return;
}
void ctSimpson(const vector<double>& x ,const vector<double>& y)
{
    /*
        @param: 
            + y : list các điểm y(x), khi truyền vào hàm truyền theo dạng {5,6,7,8...};
            + h : khoảng cách giữa 2 điểm x: x[k+1] - x[k]
            
    */
    double sum = 0;
    int size = x.size();
    cout << fixed << setprecision(6);
    for ( int i = 1; i < size  ; i +=2 ){
        sum += ((x[i + 1] - x[i-1])/6)*(y[i-1] + 4*y[i] + y[i+1]);
        
    }
    cout << "Gia tri gan dung tich phan theo phuong phap Simpson: "<<sum<<endl;
    return;
}
void   ppEuler( double(*functY)(double, double) ,const vector<double>& x, double y0){
    int n = x.size() -1 ;
    double result[n+1][5];
    /////////////////////////////////////////////
    for ( int i = 0; i <= n; i++ ){
        result[i][0] = x[i];
    }
    for ( int i = 0; i < n ; i++){
        result[i][3] = x[i+1] - x[i];
    }
    result[0][1] = y0;
    result[0][2] = functY(x[0],y0);
    result[0][4] = result[0][2]*result[0][3];
    for ( int i = 1; i <= n; i++){
        result[i][1] = result[i-1][1] + result[i-1][4];
        result[i][2] = functY(result[i][0],result[i][1]);
        result[i][4] = result[i][3]*result[i][2];
    }
    ///////////////////////////////////////////////
    for( int i = 0; i <= n; i++){
        cout << "x[" << i+1 << "]: ";
        cout << setw(20 ) << left << setprecision(6) <<fixed << result[i][0];
        cout << "y[" << i+1 << "]: ";
        cout << setw(20 ) << left << setprecision(6) << result[i][1];
        if ( i!= n ){
            cout << "f[" << i+1 << "]: ";
            cout << setw(20 ) << left << setprecision(6) << result[i][2];
            cout << "h[" << i+1 << "]: ";
            cout << setw(20 ) << left << setprecision(6) << result[i][3];
            cout << "denta[" << i+1 << "]: ";
            cout << setw(20 ) << left << setprecision(6) << result[i][4];
            cout << endl;
        }

    }
    cout << endl;
    return;
}

void   ppEulerHePT(  double(*functY)(double, double, double) , double(*functU)(double, double, double) ,const vector<double>& x, double y0, double u0 )
{
    int n = x.size() -1 ;
    double result[n+2][8];
    /////////////////////////////////////////////
    // cột x:
    for ( int i = 0; i <= n; i++ ){
        result[i][0] = x[i];
    }
    // cột h:
    for ( int i = 0; i < n ; i++){
        result[i][5] = x[i+1] - x[i];
    }
    result[0][1] = y0;
    result[0][2] = u0;
    // f1
    result[0][3] = functY(x[0],y0,u0);
    // f2
    result[0][4] = functU(x[0],y0,u0);
    // h*f1
    result[0][6] = result[0][5]*result[0][3];
    // h*f2
    result[0][7] = result[0][5]*result[0][4];
    for ( int i = 1; i <= n; i++){
        result[i][1] = result[i-1][1] + result[i-1][6];
        result[i][2] = result[i-1][2] + result[i-1][7];
        result[i][3] = functY(result[i][0],result[i][1], result[i][2]);
        result[i][4] = functU(result[i][0],result[i][1], result[i][2]);
        result[i][6] = result[i][3]*result[i][5];
        result[i][7] = result[i][4]*result[i][5];
    }
    ///////////////////////////////////////////////
    for( int i = 0; i <= n; i++){
        int setWidth = 15;
        cout << "x[" << i+1 << "]: ";
        cout << setw(setWidth ) << left << setprecision(6) <<fixed << result[i][0];
        cout << "y[" << i+1 << "]: ";
        cout << setw(setWidth ) << left << setprecision(6) << result[i][1];
        cout << "u[" << i+1 << "]: ";
        cout << setw(setWidth ) << left << setprecision(6) << result[i][2];
        if ( i!= n ){
            cout << "f(y([" << i+1 << "])): ";
            cout << setw(setWidth ) << left << setprecision(6) << result[i][3];
            cout << "f(u([" << i+1 << "])): ";
            cout << setw(setWidth ) << left << setprecision(6) << result[i][4];
            cout << "h[" << i+1 << "]: ";
            cout << setw(setWidth ) << left << setprecision(6) << result[i][5];
            cout << "dentaY[" << i+1 << "]: ";
            cout << setw(setWidth ) << left << setprecision(6) << result[i][6];
            cout << "dentaU[" << i+1 << "]: ";
            cout << setw(setWidth ) << left << setprecision(6) << result[i][7];
            cout << endl;
        }

    }
    return;
}

double RungeKutta4(double(*funct)(double, double), vector<double> x, double y0)
{
    int index = x.size();
    if ( index >=2 ) {
        double h = x[1] - x[0];
        cout << "x = " << x[0] << " ,y = " << y0 << endl;
        cout << setw(20) << left << "x";
        cout << setw(20) << left << "y";
        cout << setw(20) << left << "f(x, y)";
        cout << setw(20) << left << "h*f(x, y)";
        cout << endl;
        // k11
        cout << setw(20) << left << fixed << setprecision(6) << x[0];
        cout << setw(20) << left << y0;
        double fy1 = funct(x[0],y0);
        cout << setw(20) << left << fy1;
        double k_11 = h*fy1;
        cout << setw(20) << left << k_11 ;
        cout << endl;
        /// k12
        cout << setw(20) << left << x[0] + h/2;
        cout << setw(20) << left << y0 + k_11/2 ;
        double fy2 = funct(x[0] + h/2 ,y0 + k_11/2);
        cout << setw(20) << left << fy2;
        double k_12 = h*fy2;
        cout << setw(20) << left << k_12 ;
        cout << endl;
        /// k13
        cout << setw(20) << left << x[0] + h/2;
        cout << setw(20) << left << y0 + k_12/2;
        double fy3 = funct(x[0] + h/2,y0 + k_12/2);
        cout << setw(20) << left << fy3;
        double k_13 = h*fy3;
        cout << setw(20) << left << k_13 ;
        cout << endl;
        /// k14
        cout << setw(20) << left << x[0] + h;
        cout << setw(20) << left << y0 + k_13;
        double fy4 = funct(x[0] + h,y0 + k_13);
        cout << setw(20) << left << fy4;
        double k_14 = h*fy4;
        cout << setw(20) << left << k_14 ;
        for ( int i = 0 ; i < index - 1 ; i++ ){
            x[i] = x[i + 1];
        }
        x.pop_back();
        float denta = (k_11 + 2*k_12 + 2*k_13 + k_14)/6;
        cout << endl;
        cout << " Yi = " << y0 << ", denta = " << denta <<endl;
        cout << endl << endl << "-------------------------------------" <<endl;
        return RungeKutta4(funct,x,y0 + denta);
    } else{
        return y0;
    }
}
