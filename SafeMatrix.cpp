#include<iostream>
#include<cstdlib>
#include<cmath>
#include<cassert>
using namespace std;

// implement templates

template <class T> class SA {

private:

 int low, high;
 T* p;

 //pointer is now of the template, not the integer

public:

 // default constructor
 // allows for writing things like SA a;

 SA(){low = 0; high = -1; p = NULL;}


 // 2 parameter constructor lets us write
 // SA x(10,20);


 // single parameter constructor lets us
 // create a SA almost like a "standard" one by writing
 // SA x(10); and getting an array x indexed from 0 to 9

 SA(int i) {//one param consructor
    low = 0; high = i-1;
    p = new T[i];
    //remember that p now holds a template
 }
 SA(int l, int h){ //2 param constructor
    if ((h - l + 1) <= 0) {
        cout<<"constructor error in bounds definition"<<endl;
        exit(1);
    }

    low = l;
    high = h;
    p = new T[h - l+1];
 } 

 // copy constructor for pass by value and
 // initialization

 SA(const SA & s) {
    int size = s.high - s.low + 1;
    p = new T[size];
    for (int i = 0; i < size; i++)
        p[i] = s.p[i];
    low = s.low;
    high = s.high;
 }

 // destructor

 ~SA(){
    delete [] p;
 }

 //overloaded [] lets us write
 //SA x(10,20); x[15]= 100;

// implement template
 T& operator[](int i) {
   //  if (i < low || i > high) {
   //      cout<< "index "<<i<<" out of range"<<endl;
   //      cout<<"shutting down :(\n";//
   //      exit(1);
   //   }

   //*****i don't see why this case should be left when implementing a 2d SA approach
   //leaving this forces all matrixes to have elements such that the element can't exceed the number of cols...



    return p[i-low];
 }
 // overloaded assignment lets us assign
 // one SA to another

 SA & operator=(const SA & s) {
   if (this == &s) return *this;

   delete [] p;
   int size = s.high - s.low + 1;
   p = new T[size];

   for (int i = 0; i < size; i++)
      p[i]=s.p[i];

   low=s.low;
   high=s.high;
   return *this;
 }

 // overloads << so we can directly print SAs
 // overloaded with Safe arrays of template <class T>
 
 friend ostream& operator<<(ostream& os, SA<T> s) {
   int size = s.high - s.low + 1;
   for (int i = 0; i < size; i++)
      cout<< s.p[i] << endl;
   return os;
 }

};

// class for 2d safearray/matrix
template<class U> class Matrix {
   // declared private by default within class
   SA<U>** matrix;
   // not sure as to why double pointers are needed here but seems to be suggested by compiler
   int row, col;

   public: 

      Matrix() {//default constructor - initializes matrix with one row and one col
         row = 1;
         col = 1;
         matrix = new SA<U>*[1];
         for (int i = 0; i<1; i++){
            matrix[i] = new SA<U>;//the element is a SA, of the type of the matrix
         }
      }

      Matrix(int r, int c){//2 param constructor given rows and cols
         row = r;
         col = c;
         matrix = new SA<U>*[r];
         for (int i = 0; i < r; i++){
            matrix[i] = new SA<U>(col);//arrays in each row are of # of col
         }
      }

      // overloading operator[] to return indexes
      SA<U> &operator[](int i) {
            return *matrix[i];//point to the address being returned
      }

      // overload * operator for matrix multiplication
      Matrix<U> operator*(Matrix<U> b){//where b is the matrix on the right side of the operator
         if (col != b.row){
            cout<<"Matrix dimensions aren't capable for multiplication\n";
         }
         //case where matrix dimensions cannot be multiplied
         // occurs when:
         //given matrix a has dimensions m1 x n1 and b has dimensions m2 x n2
         //n1 must equal to m2
        
         

         int rowC = row;
         int colC = b.col;
         //obviously can be omitted for right side values in implementation

         //declare new returning matrix to hold the product
         Matrix<U> product(rowC, colC);

         //after multiplication the new matrix will be of size m1 x n2
         //where m1 is row of leftside and n2 is the col of rightside
         
         for (int i = 0; i < rowC; i++){
            for (int j = 0; j < colC ; j++){
               int sum = 0;
               //this sum keeps the sum per column available for the next iteration

               for (int k = 0; k < col; k++){

                  int temp = (*this)[i][k];
                  sum += temp * b[k][j];

               }
               product[i][j] = sum;
            }
         }
         return product;
      }

};



int main(){
   SA<int> a(10), b(3,5);
//    b[3] = 3; b[4] = 4; b[5] = 5;
//    int i;
//    for(i = 0; i<10; i++)
//       a[i] = 10 - i;
//    cout<<"printing a the first time"<<endl;
//    cout<<a<<endl;
//    cout<<b<<endl;

//    cout<<"printing using []"<<endl;
//    for( i=0;i<10;i++)
//       cout<<a[i]<<endl;
//    //can be assumed this works for safe array b

// // write your own sort
// // Sort(a,10);

//    cout<<"printing a the second time" <<endl;
//    cout<<a<<endl;
//    b[4]=12;
//    //4th index will refer to the (4-3)rd index as b is a safearray from (3,5)
//    cout<<"printing b " <<endl;
//    cout<<b<<endl;
//    a[10]=12; 
// should print an OOB error message and exit
// the above code was tested with initial SA template implementation


   int rowA, colA;
   int rowB, colB;


   // initialize the matrices first
   // A
   cout << "Enter the # of rows for matrix A:\n";
   cin >> rowA;

   cout << "Enter the # of cols for matrix A:\n";
   cin >> colA;
   Matrix<int> A(rowA, colA);

   // B
   cout << "Enter the # of rows for matrix B:\n";
   cin >> rowB;

   cout << "Enter the # of cols for matrix B:\n";
   cin >> colB;
   Matrix<int> B(rowB, colB);

  

   // now allow user to input all values of matrices A and B:
   // A:
   cout << "Enter values for Matrix A:\n";
   for (int i = 0; i < rowA; i++){
      for (int j = 0 ; j < colA; j++){
         cin >> A[i][j];
      }
   }
   B:
   cout << "Enter values for Matrix B:\n";
   for (int i = 0; i < rowB; i++){
      for (int j = 0 ; j < colB; j++){
         cin >> B[i][j];
      }
   }
   // declare matrix to hold the product:
   Matrix<int> C;
   C = A*B;

   // print matrix A:
   cout<<"Matrix A:\n";
   for(int i = 0; i < rowA; i++){
      for(int j = 0; j < colA; j++){
         cout << " " << A[i][j];
      }
      cout << endl;
   }

   cout << "------------------------------------\n";
     // print matrix B:
   cout<<"Matrix B:\n";
   for(int i = 0; i < rowB; i++){
      for(int j = 0; j < colB; j++){
         cout << " " << B[i][j];
      }
      cout << endl;
   }

   cout << "------------------------------------\n";
   // print matrix C:
   cout<<"Matrix C:\n";

   for(int i = 0; i < rowA; i++){
      for(int j = 0; j < colB; j++){
         cout << " " << C[i][j];
      }
      cout << endl;
   }
   // try to implement a length function for safe arrays and matrixes...

   return 0;
} 
