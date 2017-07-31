#include "include/matrix.h"

void Matrix4::RotateX( float angle ) {
    float cosA = cosf( angle * PI_OVER_180 );
    float sinA = sinf( angle * PI_OVER_180 );
    
    MakeIdentity();    
    m[ 5 ] = cosA; m[ 9 ] = -sinA;
    m[ 6 ] = sinA; m[ 10 ] = cosA;
}

void Matrix4::RotateY( float angle ) {
    float cosA = cosf( angle * PI_OVER_180 );
    float sinA = sinf( angle * PI_OVER_180 );

    MakeIdentity();
    m[ 0 ] = cosA; m[ 8 ] = sinA;
    m[ 2 ] = -sinA; m[ 10 ] = cosA;
}

void Matrix4::RotateZ( float angle ) {
    float cosA = cosf( angle * PI_OVER_180 );
    float sinA = sinf( angle * PI_OVER_180 );

    MakeIdentity();
    m[ 0 ] = cosA; m[ 4 ] = -sinA;
    m[ 1 ] = sinA; m[ 5 ] = cosA;
}

void Matrix4::Translate( float tx, float ty, float tz ) {
    MakeIdentity();
    m[ 12 ] = tx;
    m[ 13 ] = ty;
    m[ 14 ] = tz;
}

void Matrix4::Scale( float sx, float sy, float sz ) {
    MakeIdentity();
    m[ 0 ] = sx;
    m[ 5 ] = sy;
    m[ 10 ] = sz;
}

void Matrix4::MakeIdentity() {
    memset( m, 0, sizeof( float ) * 16 );
    m[ 0 ] = 1.0f; 
    m[ 5 ] = 1.0f; 
    m[ 10 ] = 1.0f; 
    m[ 15 ] = 1.0f;
}

void Matrix4::MakeZero() {
    memset( m, 0, sizeof( float ) * 16 );
}

