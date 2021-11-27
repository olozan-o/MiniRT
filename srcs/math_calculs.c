/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_calculs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olozano- <olozano-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 19:57:14 by oscarlo           #+#    #+#             */
/*   Updated: 2021/11/27 22:58:11 by olozano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double      *cross_product(double *one, double *other)
{
    double  *result;
    
    result = ft_calloc(3, sizeof(double));
    result[0] = one[1] * other[2] - one[2] * other[1];
    result[1] = one[2] * other[0] - one[0] * other[2];
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

double		dot_product(double *one, double *other)
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
    int     i;

    i = 0;
    max = 1;
    while (i < 3)
    {
        if (fabs(these3[i]) > max)
            max = fabs(these3[i]);
        i++;
    }
    these3[0] = these3[0] / max;
    these3[1] = these3[1] / max;
    these3[2] = these3[2] / max;
    return (these3);
}

double  *rotate_cam(double *origin, double *trans, double *up_v)
{
    double  *x_axis;
    double  *y_axis;
    double  *z_axis;
    double *result;

    result = ft_calloc(4, sizeof(double));
    z_axis = trans;
    if (trans[1] != 1 && trans[1] != -1)
        x_axis = cross_product(up_v, z_axis);
    else
    {
        x_axis = ft_calloc(4, sizeof(double));
        x_axis[0] = trans[1];
    }
    y_axis = cross_product(z_axis, x_axis);
    result[0] = origin[0] * x_axis[0] + origin[1] * y_axis[0] + origin[2] * z_axis[0];
    result[1] = origin[0] * x_axis[1] + origin[1] * y_axis[1] + origin[2] * z_axis[1];
    result[2] = origin[0] * x_axis[2] + origin[1] * y_axis[2] + origin[2] * z_axis[2];
    free(origin);
    free(x_axis);
    free(y_axis);
    return(result);
}

double  **compute_rotation(double *orig, double *dir, double *up_v)
{
    double  *xaxis;
    double  *yaxis;
    double  *zaxis;
    int     i;
    double  **rot_m;

    printf("--  Starting with: %f,%f,%f\n", up_v[0], up_v[1], up_v[2]);
    zaxis = normalize(dir);
    printf("--  Here is the data: %f,%f,%f\n", zaxis[0], zaxis[1], zaxis[2]);
    usleep(1000);
    xaxis = normalize(cross_product(up_v, zaxis));
        printf("--  Here is the data: %f,%f,%f\n", xaxis[0], xaxis[1], xaxis[2]);
    usleep(1000);
    yaxis = normalize(cross_product(zaxis, xaxis));
        printf("--  Here is the data: %f,%f,%f\n", yaxis[0], yaxis[1], yaxis[2]);
    usleep(1000);
    rot_m = ft_calloc(4, sizeof(double*));
    i = 0;
    while (i < 3)
    {
        rot_m[i] = ft_calloc(4, sizeof(double));
        rot_m[i][0] = xaxis[i];
        rot_m[i][1] = yaxis[i];
        rot_m[i][2] = zaxis[i];
        rot_m[i][3] = 0;
        i++;
    }
    rot_m[3] = ft_calloc(4, sizeof(double));
    rot_m[3][0] = dot_product(xaxis, orig);
    rot_m[3][1] = dot_product(yaxis, orig);
    rot_m[3][2] = dot_product(zaxis, orig);
    printf("--  Here is the data: %f,%f,%f\n", rot_m[3][0], rot_m[3][1], rot_m[3][2]);
    rot_m[3][3] = 1;
    free(zaxis);
    free(xaxis);
    free(yaxis);
    return(rot_m);
}

void      *world_to_cam(double *vec, double **rot_m)
{
    vec[0] = vec[0] * rot_m[0][0] + vec[1] * rot_m[0][1] + vec[2] * rot_m[0][2]; //+ rot_m[3][0];
    vec[1] = vec[0] * rot_m[0][1] + vec[1] * rot_m[1][1] + vec[2] * rot_m[1][2]; //+ rot_m[3][1];
    vec[2] = vec[0] * rot_m[0][2] + vec[1] * rot_m[2][1] + vec[2] * rot_m[2][2]; //+ rot_m[3][2];
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




double  *cam_here(rt_scene *sc, int i, int j)
{
    double  aspect_ratio;
    double  *res;
    double  fov;

    res = ft_calloc(4, sizeof(double));
    fov = sc->camera->params[0];
    aspect_ratio = sc->width / sc->height;
    res[0] = (2 * (i / sc->width) - 1) * aspect_ratio * fov;
    res[1] = (1 - (2 * j / sc->height)) * fov;
    res[0] *= -1;
    res[2] = 1;
    normalize(res);
    return (res);
}

*/