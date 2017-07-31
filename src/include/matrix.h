#ifndef MATRIX_H
#define	MATRIX_H

#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING

#include <cstdio>
#include <cstring>
#include <cmath>
#include "types.h"
#include "vector.h"

using namespace std;

// 4x4 matrix, column-major
class Matrix4 {
public:
    float m[16];    

    Matrix4() { }
    
    Matrix4( float *n ) { 
        if ( n ) {
            memcpy (m, n, sizeof( float ) * 16 ); 
        }
    }
    
    Matrix4( const Matrix4& n ) { 
        memcpy( m, n.m, sizeof( float ) * 16 ); 
    }
    
    Matrix4& operator=( const Matrix4& n ) {
        memcpy( m, n.m, sizeof(float) * 16 );

        return ( *this );
    }

    bool operator==( const Matrix4& n ) const {
        return ( memcmp( m, n.m, sizeof( float ) * 16 ) == 0 );
    }

    bool operator!=( const Matrix4& n ) const {
        return ( !( *this == n ) );
    }

    Matrix4 operator+( const Matrix4& n ) const {
        float temp[ 16 ];

        for ( int i = 0; i < 16; i++ ) {
            temp[ i ] = m[ i ] + n.m[ i ];
        }

        return Matrix4(temp);
    }

    Matrix4 & operator+=( const Matrix4& n ) {
        for ( int i = 0; i < 16; i++ ) {
            m[ i ] += n.m[ i ];
        }

        return ( *this );
    }

    Matrix4 operator-( const Matrix4& n ) const {
        float temp[ 16 ];

        for ( int i = 0; i < 16; i++ ) {
            temp[ i ] = m[ i ] - n.m[ i ];
        }

        return Matrix4( temp );
    }

    Matrix4& operator-=( const Matrix4& n ) {       
        for ( int i = 0; i < 16; i++ ) {
            m[ i ] -= n.m[ i ];
        }

        return ( *this );
    }

    Matrix4 operator-() const {
        float temp[ 16 ];

        for ( int i = 0; i < 16; i++ ) {
            temp[ i ] = m[ i ] * -1.0f;
        }

        return Matrix4( temp );
    }

    Matrix4 operator*( float s ) const {
        float temp[ 16 ];

        for ( int i = 0; i < 16; i++ )
            temp[ i ] = m[ i ] * s;

        return Matrix4( temp );
    }

    Vector3 operator*( const Vector3& v ) const {
        float temp[ 3 ];

        temp[ 0 ] = m[ 0 ] * v.v[ 0 ] + m[ 4 ] * v.v[ 1 ] + m[ 8 ] * v.v[ 2 ] + m[ 12 ];
        temp[ 1 ] = m[ 1 ] * v.v[ 0 ] + m[ 5 ] * v.v[ 1 ] + m[ 9 ] * v.v[ 2 ] + m[ 13 ];
        temp[ 2 ] = m[ 2 ] * v.v[ 0 ] + m[ 6 ] * v.v[ 1 ] + m[ 10 ] * v.v[ 2 ] + m[ 14 ];

        return Vector3( temp[ 0 ], temp[ 1 ], temp[ 2 ] );
    }

    Matrix4 operator*( const Matrix4& n ) const {
        float temp[ 16 ];

        for ( int row = 0; row < 4; row++ ) {
            for ( int col = 0; col < 4; col++ ) {
                temp[ col * 4 + row ] = 
                    m[ 0 + row ] * n.m[ 0 + col * 4 ] +
                    m[ 4 + row ] * n.m[ 1 + col * 4 ] +
                    m[ 8 + row ] * n.m[ 2 + col * 4 ] +
                    m[ 12 + row ] * n.m[ 3 + col * 4 ];
            }
        }

        return Matrix4( temp );
    }

    Matrix4 & operator*=( float s ) {
        for ( int i = 0; i < 16; i++ ) {
            m[ i ] *= s;
        }

        return ( *this );
    }

    Matrix4 & operator*=( const Matrix4& n ) {
        float temp[ 16 ];

        for ( int row = 0; row < 4; row++ ) {
            for ( int col = 0; col < 4; col++ ) {
                temp[col * 4 + row] = 
                    m[ 0 + row ] * n.m[ 0 + col * 4 ] +
                    m[ 4 + row ] * n.m[ 1 + col * 4 ] +
                    m[ 8 + row ] * n.m[ 2 + col * 4 ] +
                    m[ 12 + row ] * n.m[ 3 + col * 4 ];
            }
        }

        memcpy( m, temp, sizeof( float ) * 16 );

        return ( *this );
    }

    Matrix4 operator/( float s ) const { 
        float temp[ 16 ];

        if ( s != 0.0f )  {
            for ( int i = 0; i < 16; i++ ) {
                temp[ i ] = m[ i ] / s;
            }

            return Matrix4( temp );
        }
        else {
            // Divide by zero
            return ( Matrix4() );
        }
    }

    Matrix4& operator/=( float s ) {
        float temp[ 16 ];

        if ( s != 0.0f )  {
            for ( int i = 0; i < 16; i++ ) {
                temp[ i ] = m[ i ] / s;
            }

            memcpy( m, temp, sizeof( float ) * 16 );
        }
        else {
            // Divide by zero
        }

        return ( *this );
    }

    Matrix4& Transpose() {
        swap( m[ 1 ],  m[ 4 ] );
        swap( m[ 2 ],  m[ 8 ] );
        swap( m[ 3 ],  m[ 12 ] );
        swap( m[ 6 ],  m[ 9 ] );
        swap( m[ 7 ],  m[ 13 ] );
        swap( m[ 11 ], m[ 14 ] );

        return ( *this );
    }

    void RotateX( float angle );
    void RotateY( float angle );
    void RotateZ( float angle );
    void Translate( float tx, float ty, float tz );
    void Scale( float sx, float sy, float sz );
    void MakeIdentity();
    void MakeZero();    
    inline void swap( float& a, float& b ) {
        static float temp;
        temp = a;
        a = b;
        b = temp;
    }
        
};

#endif

