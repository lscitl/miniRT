/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_is_hit_calc_coeff.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:28:31 by chanhpar          #+#    #+#             */
/*   Updated: 2022/08/05 23:51:05 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_hit.h"

static void	calc_coeff_sphere(double coeff[3], t_ray ray, t_obj_info *obj);
static void	calc_coeff_cylinder(double coeff[3], t_ray ray, t_obj_info *obj);
static void	calc_coeff_cone(double coeff[3], t_ray ray, t_obj_info *obj);
static void	calc_coeff_plane(double coeff[3], t_ray ray, t_obj_info *obj);

void	calc_coeff(double coeff[3], t_ray ray, t_obj_info *obj)
{
	static void (*const	func_array[5])(double *, t_ray, t_obj_info *) = {
		calc_coeff_sphere, \
		calc_coeff_cylinder, \
		calc_coeff_cone, \
		calc_coeff_plane, \
		calc_coeff_plane, \
	};

	func_array[obj->type](coeff, ray, obj);
}

static void	calc_coeff_sphere(double coeff[3], t_ray ray, t_obj_info *obj)
{
	t_vec	w;

	w = vec_minus(ray.orig, obj->pos);
	coeff[0] = vec_dotprod(ray.direction, ray.direction);
	coeff[1] = (double)2 * vec_dotprod(ray.direction, w);
	coeff[2] = vec_dotprod(w, w) - (obj->r_sqare);
}

static void	calc_coeff_cylinder(double coeff[3], t_ray ray, t_obj_info *obj)
{
	t_vec	v;
	t_vec	w;
	t_vec	h;
	double	v_dot_h;
	double	w_dot_h;

	h = obj->orient;
	v = ray.direction;
	w = vec_minus(ray.orig, obj->pos);
	v_dot_h = vec_dotprod(v, h);
	w_dot_h = vec_dotprod(w, h);
	coeff[0] = 1.0 - v_dot_h * v_dot_h;
	coeff[1] = 2.0 * (vec_dotprod(v, w) - v_dot_h * w_dot_h);
	coeff[2] = vec_dotprod(w, w) - w_dot_h * w_dot_h - obj->r_sqare;
}

static void	calc_coeff_cone(double coeff[3], t_ray ray, t_obj_info *obj)
{
	t_vec	v;
	t_vec	w;
	t_vec	h;
	double	v_dot_h;
	double	w_dot_h;

	h = obj->orient;
	v = ray.direction;
	w = vec_minus(ray.orig, obj->pos);
	v_dot_h = vec_dotprod(v, h);
	w_dot_h = vec_dotprod(w, h);
	coeff[0] = 1.0 - (1.0 + obj->rsq_div_hsq) * v_dot_h * v_dot_h;
	coeff[1] = 2.0 * (vec_dotprod(w, v) + obj->rsq_div_h * v_dot_h \
							- (1.0 + obj->rsq_div_hsq) * w_dot_h * v_dot_h);
	coeff[2] = vec_dotprod(w, w) \
				- (1.0 + obj->rsq_div_hsq) * w_dot_h * w_dot_h \
						- obj->r_sqare + 2.0 * obj->rsq_div_h * w_dot_h;
}

static void	calc_coeff_plane(double coeff[3], t_ray ray, t_obj_info *obj)
{
	coeff[0] = vec_dotprod(ray.direction, obj->orient);
	coeff[1] = vec_dotprod(vec_minus(ray.orig, obj->pos), obj->orient);
}
