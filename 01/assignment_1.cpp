#include <iostream>
using namespace std;

// class Complex that represents a complex number
class Complex {

private:
	// Variables that hold real and imaginary part
	float real ;
	float imgnry ;

public:

	// Default constructor -> initializes complex number to 0 + 0i
	Complex() : real(0.0f) , imgnry(0.0f) {}

	// Parameterized constructor -> initializes complex number to r + (img)i
	Complex( float r , float img ) : real( r ) , imgnry( img ) {}

	// function declaration
	void print() ;

	void read( string name ) ;

	void set_real( float r ) { real = r ;}

	void set_imgnry( float img ) { imgnry = img ;}

	float get_real() { return real; }

	float get_imgnry() {return imgnry ;}

 	Complex add( Complex other ) {
		float real_sum = real + other.get_real() ;
		float img_sum = imgnry + other.get_imgnry() ;
		Complex output( real_sum , img_sum ) ;
		return output ;
	}

	Complex subtract( Complex other ) {
		float real_diff = real - other.get_real() ;
		float img_diff = imgnry - other.get_imgnry() ;
		Complex output( real_diff , img_diff ) ;
		return output ;
	}

	Complex multiply( Complex other ) {
		float prod_real = ( real * other.get_real() ) - ( imgnry * other.get_imgnry() ) ;
		float prod_img = ( real * other.get_imgnry() ) + ( imgnry * other.get_real() ) ;
		Complex output( prod_real , prod_img ) ;
		return output ;
	}

	Complex conjugate() {
		float real_part = real ;
		float imgnry_part = ( -1 ) * imgnry ;
		Complex output( real_part , imgnry_part ) ;
		return output ;
	}

	Complex operator+( Complex other ) {
		return add( other ) ;
	}

	Complex operator-( Complex other ) {
		return subtract( other ) ;
	}

	Complex operator*( Complex other ) {
		return multiply( other ) ;
	}

	friend ostream& operator<< ( ostream& out , Complex& object ) {
		out << "( " << object.real << " )" << " + ( " <<  object.imgnry << "i )" << endl ;
		return out ; 
	}

	friend istream& operator>> ( istream& in , Complex& object ) {
		cout << "Enter real part for "  << endl ;
		in >> object.real ;
		cout << "Enter imaginary part " << endl ;
		in >> object.imgnry ;
		return in ; 
	}

};

void Complex::print() {
	cout << "( " << Complex::real << " )" << " + ( " << Complex::imgnry << "i )" << endl ;
}

void Complex::read( string name ) {
	cout << "Enter real part for " << name  << endl ;
	cin >> Complex::real ;
	cout << "Enter imaginary part " << name << endl ;
	cin >> Complex::imgnry ;
}

int main() {
	Complex c1;
	Complex c2( 1.0 , 2.0 ) ;

	Complex c3 ;
	cin >> c3 ; 

	cout << " Complex numbers " << endl ;

	c1.print() ;
	c2.print() ;
	c3.print() ;

	cout << " Sum " << endl ;

	Complex sum = c1.add( c2 );
	Complex sum2 = c1 + c2 ;
	sum.print() ;
	sum2.print() ;
	cout << sum2 ; 

	cout << " Difference " << endl ;

	Complex difference = c2.subtract( c3 ) ;
	Complex difference2 = c1 - c2 ;
	difference.print() ;
	difference2.print() ;

	cout << " Product " << endl ;

	Complex product = c2.multiply( c3 ) ;
	Complex product2 = c2 * c3 ;
	product.print() ;
	product2.print() ;

	return 0;
}
