#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class Polynomial
{
    private:
        vector< int > coefficients;

    public:
        Polynomial( int );
        Polynomial( Polynomial& );
        Polynomial& operator = ( Polynomial& );
        friend ostream& operator << ( ostream&, Polynomial& );
        friend Polynomial& operator + ( Polynomial&, Polynomial& );
        friend Polynomial& operator - ( Polynomial&, Polynomial& );
        friend Polynomial& operator * ( Polynomial&, Polynomial& );
        int operator [] ( int );
        int setCoeff( int, unsigned int );
};

Polynomial::Polynomial( int polyDegree = 0 )
{
    coefficients.resize( polyDegree + 1, 0 );
}

Polynomial::Polynomial( Polynomial& copyPoly )
{
    unsigned int i;

    coefficients.resize( copyPoly.coefficients.size( ), 0 );

    for( i = 0; i < coefficients.size( ); i++ )
        coefficients[ i ] = copyPoly.coefficients[ i ];
}

Polynomial& Polynomial::operator = ( Polynomial& Poly )
{
    if( this != &Poly )
        coefficients = Poly.coefficients;

    return *this;
}

ostream& operator << ( ostream& f, Polynomial& Poly )
{
    unsigned int i;

    if( Poly.coefficients.size( ) == 1 )
        f << Poly.coefficients[ 0 ];
    else
        f << Poly.coefficients[ 0 ] << " ";

    for( i = 1; i < Poly.coefficients.size( ); i++ )
    {
        if( Poly.coefficients[ i ] != 0 )
        {
            switch( i )
            {
                case 1:
                {
                    if( Poly.coefficients[ i ] > 0 )
                        f << "+ " << Poly.coefficients[ i ] << "X ";
                    else
                        f << "- " << Poly.coefficients[ i ] * ( -1 ) << "X ";

                    break;
                }

                default:
                {
                    if( Poly.coefficients[ i ] > 0 )
                        f << "+ " << Poly.coefficients[ i ] << "X^" << i << " ";
                    else
                        f << "- " << Poly.coefficients[ i ] * ( -1 ) << "X^" << i << " ";

                    break;
                }
            }
        }
    }

    return f;
}

Polynomial& operator + ( Polynomial& Poly1, Polynomial& Poly2 )
{
    unsigned int i;

    Polynomial* Poly = new Polynomial;

    Poly->coefficients.resize( max( Poly1.coefficients.size( ), Poly2.coefficients.size( ) ), 0 );

    for( i = 0; i < Poly1.coefficients.size( ); i++ )
        Poly->coefficients[ i ] += Poly1.coefficients[ i ];

    for( i = 0; i < Poly2.coefficients.size( ); i++ )
        Poly->coefficients[ i ] += Poly2.coefficients[ i ];

    for( i = Poly->coefficients.size( ) - 1; i > 0; i-- )
        if( Poly->coefficients[ i ] != 0 )
            break;

    Poly->coefficients.resize( i + 1 );

    return *Poly;
}

Polynomial& operator - ( Polynomial& Poly1, Polynomial& Poly2 )
{
    unsigned int i;

    Polynomial* Poly = new Polynomial;

    Poly->coefficients.resize( max( Poly1.coefficients.size( ), Poly2.coefficients.size( ) ), 0 );

    for( i = 0; i < Poly1.coefficients.size( ); i++ )
        Poly->coefficients[ i ] += Poly1.coefficients[ i ];

    for( i = 0; i < Poly2.coefficients.size( ); i++ )
        Poly->coefficients[ i ] -= Poly2.coefficients[ i ];

    for( i = Poly->coefficients.size( ) - 1; i > 0; i-- )
        if( Poly->coefficients[ i ] != 0 )
            break;

    Poly->coefficients.resize( i + 1 );

    return *Poly;
}

Polynomial& operator * ( Polynomial& Poly1, Polynomial& Poly2 )
{
    unsigned int i, j;

    Polynomial* Poly = new Polynomial;

    Poly->coefficients.resize( Poly1.coefficients.size( ) + Poly2.coefficients.size( ) - 1 );

    for( i = 0; i < Poly1.coefficients.size( ); i++ )
    {
        if( Poly1.coefficients[ i ] != 0 )
        {
            for( j = 0; j < Poly2.coefficients.size( ); j++ )
            {
                if( Poly2.coefficients[ j ] != 0 )
                    Poly->coefficients[ i + j ] = Poly1.coefficients[ i ] * Poly2.coefficients[ j ];
            }
        }
    }

    return *Poly;
}

int Polynomial::operator [] ( int point )
{
    int polyValue = 0;
    unsigned int i;

    for( i = 0; i < coefficients.size( ); i++ )
    {
        if( coefficients[ i ] != 0 )
        {
            if( i == 0 )
                polyValue += coefficients[ i ];
            else
                polyValue += coefficients[ i ] * pow( point, i );
        }
    }

    return polyValue;
}

int Polynomial::setCoeff( int coeffValue, unsigned int Index )
{
    if( Index > ( coefficients.size( ) - 1 ) )
        coefficients.resize( Index + 1, 0 );

    coefficients[ Index ] = coeffValue;

    return 1;
}

int main( )
{
    Polynomial p1, p2, p4;

    p1.setCoeff( 3, 0 );
    p1.setCoeff( 2, 3 );
    p1.setCoeff( 4, 5 );

    p2.setCoeff( 6, 0 );
    p2.setCoeff( 9, 1 );
    p2.setCoeff( 5, 3 );
    p2.setCoeff( 3, 4 );
    p2.setCoeff( 2, 6 );

    Polynomial p3( p1 - p2 );

    p4 = p1 * p2;

    cout << "First poly: " << p1 << endl;
    cout << "Second poly: " << p2 << endl;
    cout << "First poly evualted in 2 = " << p1[ 2 ] << endl;
    cout << "Sum of poly: " << p1 + p2 << endl;
    cout << "Difference of poly: " << p3 << endl;
    cout << "Product of poly: " << p4 << endl;

    return 0;
}
