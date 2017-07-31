#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>

class Vector2 {
public:
    float v[ 2 ];

    Vector2() { }
    
    Vector2( float x, float y ) { 
        v[ 0 ] = x;
        v[ 1 ] = y; 
    }
    
    Vector2( const Vector2& vv ) { 
        v[ 0 ] = vv.v[ 0 ]; 
        v[ 1 ] = vv.v[ 1 ]; 
    }

    Vector2& operator=( const Vector2&vv ) {
        v[ 0 ] = vv.v[0];
        v[ 1 ] = vv.v[1];

        return ( *this );
    }

    bool operator==( const Vector2& vv ) const {
        return ( ( v[ 0 ] == vv.v[ 0 ] ) && (v[ 1 ] == vv.v[ 1 ] ) );
    }

    bool operator!=( const Vector2& vv ) const {
        return ( ( v[ 0 ] != vv.v[ 0 ] ) || ( v[ 1 ] != vv.v[ 1 ] ) );
    }

    Vector2 operator+( const Vector2& vv ) const {
        return Vector2( v[ 0 ] + vv.v[ 0 ], v[ 1 ] + vv.v[ 1 ] );
    }

    Vector2& operator+=( const Vector2& vv ) {
        v[ 0 ] += vv.v[ 0 ];
        v[ 1 ] += vv.v[ 1 ];

        return ( *this );
    }

    Vector2 operator-( const Vector2& vv ) const {
        return Vector2( v[ 0 ] - vv.v[ 0 ], v[ 1 ] - vv.v[ 1 ] );
    }

    Vector2 operator-() const {
        return Vector2( -v[ 0 ], -v[ 1 ] );
    }

    Vector2& operator-=( const Vector2& vv ) {
        v[ 0 ] -= vv.v[ 0 ];
        v[ 1 ] -= vv.v[ 1 ];

        return ( *this );
    }

    Vector2& operator*=( float s ) {
        v[ 0 ] *= s;
        v[ 1 ] *= s;

        return ( *this );
    }

    Vector2& operator/=( float s ) {
        float r = 1 / s;

        v[ 0 ] *= r;
        v[ 1 ] *= r;

        return ( *this );
    }

    Vector2 operator*( float s ) const {
        return Vector2( v[ 0 ] * s, v[ 1 ] * s );
    }

    Vector2 operator/( float s ) const {
        if ( s != 0.0f ) {
            float r = 1 / s;
            return Vector2( v[ 0 ] * r, v[ 1 ] * r );
        } 
        else {
            // Divide by zero
        }
            
    }

    float Dot( const Vector2& vv ) const {
        return ( v[ 0 ] * vv.v[ 0 ] + v[ 1 ] * vv.v[ 1 ] );
    }

    float Length() const {
        return sqrtf( v[ 0 ] * v[ 0 ] + v[ 1 ] * v[ 1 ] );
    }

    float LengthSqr() const {
        return ( v[ 0 ] * v[ 0 ] + v[ 1 ] * v[ 1 ] );
    }

    void Norm() {
        ( *this ) /= Length();
    }
};

class Vector3 {
public:
    float v[ 3 ];

    Vector3() { }
    
    Vector3( float x, float y, float z ) { 
        v[ 0 ] = x; 
        v[ 1 ] = y; 
        v[ 2 ] = z; 
    }
    
    Vector3( float* vv )  {
        v[ 0 ] = vv[ 0 ]; 
        v[ 1 ] = vv[ 1 ]; 
        v[ 2 ] = vv[ 2 ]; 
    }
    
    Vector3( const Vector3& vv ) { 
        v[ 0 ] = vv.v[ 0 ]; 
        v[ 1 ] = vv.v[ 1 ]; 
        v[ 2 ] = vv.v[ 2 ]; 
    }

    Vector3 & operator=( const Vector3& vv ) {
        v[ 0 ] = vv.v[ 0 ];
        v[ 1 ] = vv.v[ 1 ];
        v[ 2 ] = vv.v[ 2 ];

        return ( *this );
    }

    bool operator==( const Vector3& vv ) const {
        return ( ( v[ 0 ] == vv.v[ 0 ] ) && ( v[ 1 ] == vv.v[ 1 ] ) && ( v[ 2 ] == vv.v[ 2 ] ) );
    }

    bool operator!=( const Vector3& vv ) const {
        return ( ( v[ 0 ] != vv.v[ 0 ] ) || ( v[ 1 ] != vv.v[ 1 ] ) || ( v[ 2 ] != vv.v[ 2 ] ) );
    }

    Vector3 operator+( const Vector3& vv ) const {
        return Vector3( v[ 0 ] + vv.v[ 0 ], v[ 1 ] + vv.v[ 1 ], v[ 2 ] + vv.v[ 2 ] );
    }

    Vector3& operator+=( const Vector3& vv ) {
        v[ 0 ] += vv.v[ 0 ];
        v[ 1 ] += vv.v[ 1 ];
        v[ 2 ] += vv.v[ 2 ];

        return ( *this );
    }

    Vector3 operator-( const Vector3& vv ) const {
        return Vector3( v[ 0 ] - vv.v[ 0 ], v[ 1 ] - vv.v[ 1 ], v[ 2 ] - vv.v[ 2 ] );
    }

    Vector3 operator-() const {
        return Vector3( -v[ 0 ], -v[ 1 ], -v[ 2 ] );
    }

    Vector3& operator-=( const Vector3& vv ) {
        v[ 0 ] -= vv.v[ 0 ];
        v[ 1 ] -= vv.v[ 1 ];
        v[ 2 ] -= vv.v[ 2 ];

        return ( *this );
    }

    Vector3& operator*=( float s ) {
        v[ 0 ] *= s;
        v[ 1 ] *= s;
        v[ 2 ] *= s;

        return ( *this );
    }

    Vector3& operator/=( float s ) {
        float r = 1 / s;

        v[ 0 ] *= r;
        v[ 1 ] *= r;
        v[ 2 ] *= r;

        return ( *this );
    }

    Vector3 operator*( float s ) const {
        return Vector3( v[ 0 ] * s, v[ 1 ] * s, v[ 2 ] * s );
    }

    Vector3 operator/( float s ) const {
        float r = 1 / s;

        return Vector3( v[ 0 ] * r, v[ 1 ] * r, v[ 2 ] * r );
    }

    float Dot( const Vector3& vv ) const {
        return ( v[ 0 ] * vv.v[ 0 ] + v[ 1 ] * vv.v[ 1 ] + v[ 2 ] * vv.v[ 2 ] );
    }

    float Dot( const float* vv ) const {
        return ( v[ 0 ] * vv[ 0 ] + v[ 1 ] * vv[ 1 ] + v[ 2 ] * vv[ 2 ] );
    }

    Vector3 Cross( const Vector3& vv ) const {
        return Vector3( 
                v[ 1 ] * vv.v[ 2 ] - v[ 2 ] * vv.v[ 1 ],
                v[ 2 ] * vv.v[ 0 ] - v[ 0 ] * vv.v[ 2 ],
                v[ 0 ] * vv.v[ 1 ] - v[ 1 ] * vv.v[ 0 ] );
    }

    float Length() const {
        return ( sqrtf( v[ 0 ] * v[ 0 ] + v[ 1 ] * v[ 1 ] + v[ 2 ] * v[ 2 ] ) );
    }

    float LengthSqr() const {
        return ( v[ 0 ] * v[ 0 ] + v[ 1 ] * v[ 1 ] + v[ 2 ] * v[ 2 ] );
    }

    void Norm() {
        static float magSqr;
        static float i;

        magSqr = v[ 0 ] * v[ 0 ] + v[ 1 ] * v[ 1 ] + v[ 2 ] * v[ 2 ];

        if ( magSqr > 0.0f ) {
            i = 1.0f / sqrtf( magSqr );
            v[ 0 ] /= i;
            v[ 1 ] /= i;
            v[ 2 ] /= i;
        }
    }
};


#endif
