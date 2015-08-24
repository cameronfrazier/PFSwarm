/* 
 * File:   vector3.h
 * Author: c_frazier
 *
 * Created on August 21, 2015, 2:15 PM
 */

#ifndef VECTOR3_H
#define	VECTOR3_H

#include <math.h>
#include <iostream>

template<class T>
class Vector3
{
public:
    T x, y, z;
    
    Vector3<T>(T _x = 0, T _y = 0, T _z = 0)
    {
        this->x = _x;
        this->y = _y;
        this->z = _z;
    }
    Vector3<T>(const Vector3<T> & vec){
        this->x = (T) vec.x;
        this->y = (T) vec.y;
        this->z = (T) vec.z;
    }
    ~Vector3(){}
    
    T mag()
    {
        return pow(pow(x,2) + pow(y,2) + pow(z,2),0.5);
    }
    
    void normalize()
    {
        this->scale(1/mag());
    }
    
    void scale(T factor)
    {
        x *= factor;
        y *= factor;
        z *= factor;
    }
    
    T unit()
    {
        Vector3<T> temp = Vector3<T>(this->x,this->y,this->z);
        temp.normalize();
        return temp;
    }
    void operator+= (const Vector3& param)
    {
        x += param.x;
        y += param.y;
        z += param.z;
    }
    void operator-= (const Vector3& param)
    {
        x -= param.x;
        y -= param.y;
        z -= param.z;
    }  
    void operator*= (const Vector3& param)
    {
        x *= param.x;
        y *= param.y;
        z *= param.z;
    }  
    void operator/= (const Vector3& param)
    {
        x /= param.x;
        y /= param.y;
        z /= param.z;
    }
    
    void operator+= (double param)
    {
        x += param;
        y += param;
        z += param;
    }
    void operator-= (double param)
    {
        x -= param;
        y -= param;
        z -= param;
    }  
    void operator*= (double param)
    {
        x *= param;
        y *= param;
        z *= param;
    }  
    void operator/= (double param)
    {
        x /= param;
        y /= param;
        z /= param;
    }  
    
    Vector3<T> operator+ (const Vector3& param)
    {
        Vector3<T> temp;
        temp.x = x + param.x;
        temp.y = y + param.y;
        temp.z = z + param.z;
        return temp;
    }
    Vector3<T> operator- (const Vector3& param)
    {
        Vector3<T> temp;
        temp.x = x - param.x;
        temp.y = y - param.y;
        temp.z = z - param.z;
        return temp;
    }
    Vector3<T> operator* (const Vector3& param)
    {
        Vector3<T> temp;
        temp.x = x * param.x;
        temp.y = y * param.y;
        temp.z = z * param.z;
        return temp;
    }
    Vector3<T> operator/ (const Vector3& param)
    {
        Vector3<T> temp;
        temp.x = x / param.x;
        temp.y = y / param.y;
        temp.z = z / param.z;
        return temp;
    }
    Vector3<T> operator+ (double param)
    {
        Vector3<T> temp;
        temp.x = x + param;
        temp.y = y + param;
        temp.z = z + param;
        return temp;
    }
    Vector3<T> operator- (double param)
    {
        Vector3<T> temp;
        temp.x = x - param;
        temp.y = y - param;
        temp.z = z - param;
        return temp;
    }
    Vector3<T> operator* (double param)
    {
        Vector3<T> temp;
        temp.x = x * param;
        temp.y = y * param;
        temp.z = z * param;
        return temp;
    }
    Vector3<T> operator/ (double param)
    {
        Vector3<T> temp;
        temp.x = x / param;
        temp.y = y / param;
        temp.z = z / param;
        return temp;
    }
    
    Vector3<T> leastOf(const Vector3& param)
    {
        Vector3<T> temp;
        temp.x = (x < param.x) ? x : param.x;
        temp.y = (y < param.y) ? y : param.y;
        temp.z = (z < param.z) ? z : param.z;
        return temp;
    }
    Vector3<T> greatestOf(const Vector3& param)
    {
        Vector3<T> temp;
        temp.x = (x > param.x) ? x : param.x;
        temp.y = (y > param.y) ? y : param.y;
        temp.z = (z > param.z) ? z : param.z;
        return temp;
    }
    
    void print(bool withCR = true)
    {
	std::cout << std::fixed << std::setprecision(3);
        std::cout << "[ " << x << ", " << y << ", " << z << " ]";
        if (withCR) std::cout << std::endl;
    }
};

#endif	/* VECTOR3_H */

