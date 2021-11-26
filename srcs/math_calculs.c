/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_calculs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olozano- <olozano-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 19:57:14 by oscarlo           #+#    #+#             */
/*   Updated: 2021/05/12 11:20:34 by olozano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double      *cross_product(double *one, double *other)
{
    double  *result;
    
    result = ft_calloc(3, sizeof(double));
    result[0] = one[1] * other[2] - one[2] * other[1];
    result[1] = one[2] * other[2] - one[0] * other[2];
    result[2] = one[0] * other[1] - one[1] * other[0];
    return (result);
}

double      *scalar_product(double *one, double *other)
{
    double  *result;
    
    result = ft_calloc(3, sizeof(double));
    result[0] = one[1] * other[2] - one[2] * other[0];
    result[1] = one[2] * other[0] - one[0] * other[2];
    result[2] = one[0] * other[1] - one[1] * other[0];
    return (result);
}

double		single_product(double *one, double *other)
{
    return (one[0]*other[0] + one[1]*other[1] + one[2]*other[2]);
}

double      *substract(double *one, double *other)
{
    double  *result;
    
    result = ft_calloc(3, sizeof(double));
    result[0] = one[0] - other[0];
    result[1] = one[1] - other[1];
    result[2] = one[2] - other[2];
    return (result);
}

// Pre-multiply a vector by a matrix on the right. 
// ****** ENTENC que només calen els 3 primers resultats, que lo altre és la magnitud! no?
// ****** ENTENC que és "matrix on the right" i no on the left, no? https://www.3dgep.com/understanding-the-view-matrix/

double      *normalize(double *these3)
{
    double  max;

    if (these3[0] >= these3 [1] && these3[0] >= these3[2])
        max = these3[0];
    else if (these3[1] >= these3 [0] && these3[1] >= these3[2])
        max = these3[1];
    else
        max = these3[2];
    these3[0] = these3[0] / max;
    these3[1] = these3[1] / max;
    these3[2] = these3[2] / max;
    return (these3);
}

void      compute_rotation(double *orig, double *dir)
{
    double  *xaxis;
    double  *yaxis;
    double  *zaxis;
    int     i;

    zaxis = normalize(substract(orig, dir));
    xaxis = normalize(cross_product(g_up_vector, zaxis));
    yaxis = cross_product(zaxis, xaxis);
    g_rot_m = ft_calloc(4, sizeof(double*));
    i = 0;
    while (i < 3)
    {
        g_rot_m[i] = ft_calloc(4, sizeof(double));
        g_rot_m[i][0] = xaxis[i];
        g_rot_m[i][1] = yaxis[i];
        g_rot_m[i][2] = zaxis[i];
        g_rot_m[i][3] = 0;
    }
    g_rot_m[3][0] = single_product(xaxis, orig);
    g_rot_m[3][1] = single_product(yaxis, orig);
    g_rot_m[3][2] = single_product(zaxis, orig);
    g_rot_m[3][3] = 1;
}

void      *world_to_cam(double *vec)
{
    vec[0] = vec[0] * g_rot_m[0][0] + vec[1] * g_rot_m[0][1] + vec[2] * g_rot_m[0][0] + g_rot_m[0][3];
    vec[1] = vec[0] * g_rot_m[1][0] + vec[1] * g_rot_m[1][1] + vec[2] * g_rot_m[1][0] + g_rot_m[1][3];
    vec[2] = vec[0] * g_rot_m[2][0] + vec[1] * g_rot_m[2][1] + vec[2] * g_rot_m[2][0] + g_rot_m[2][3];
    // result[3] =  v[0] * m[3][0] + v[1] * m[3][1] + v[2] * m[3][2] + v[3] * m[3][3];
}


/*
Matrix44f lookAt(const Vec3f& from, const Vec3f& to, const Vec3f& tmp = Vec3f(0, 1, 0)) 
{ 
    Vec3f forward = normalize(from - to); 
    Vec3f right = crossProduct(normalize(tmp), forward); 
    Vec3f up = crossProduct(forward, right); 
 
    Matrix44f camToWorld; 
 
    camToWorld[0][0] = right.x; 
    camToWorld[0][1] = right.y; 
    camToWorld[0][2] = right.z; 
    camToWorld[1][0] = up.x; 
    camToWorld[1][1] = up.y; 
    camToWorld[1][2] = up.z; 
    camToWorld[2][0] = forward.x; 
    camToWorld[2][1] = forward.y; 
    camToWorld[2][2] = forward.z; 
 
    camToWorld[3][0] = from.x; 
    camToWorld[3][1] = from.y; 
    camToWorld[3][2] = from.z; 
 
    return camToWorld; 
} 

*/