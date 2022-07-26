/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_hit.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:02:31 by seseo             #+#    #+#             */
/*   Updated: 2022/08/06 17:09:53 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_HIT_H
# define MINIRT_HIT_H

# include "minirt.h"

# define LIGHT_LEN_LIMIT 4000
# define BM_TX_SCALE 25

// vec_dotprod(normal_vector, ray.direction);
// (orig + t * dir) hit object
typedef struct s_hit_info
{
	t_ray		ray;
	t_vec		hit_point;
	t_vec		norm_vec;
	double		distance;
	t_obj_info	*obj;
	t_phong		phong;
	t_uv_map	uv_map;
	t_color		color;
}	t_hit_info;

// minirt_is_hit_calc_coeff.c
void	calc_coeff(double coeff[3], t_ray ray, t_obj_info *obj);

// minirt_is_hit_main.c
int		is_hit(t_obj_info *obj, t_hit_info *info);

// minirt_is_hit_phong_and_shadow.c
t_phong	phong_reflection(t_map_info *map, t_hit_info *info, t_vec v);

// minirt_is_hit_update_hit_info_get_color.c
t_color	get_point_color(t_obj_info *obj, t_hit_info *info);
t_vec	get_normal_vector(t_vec dir, t_vec point, t_obj_info *obj);

// minirt_is_hit_update_hit_info_uv.c
void	get_uv_mapping(t_obj_info *obj, t_hit_info *info, t_uv_map *uv_map);

// minirt_is_hit_update_hit_info.c
int		update_hit_info(t_hit_info *info, t_obj_info *obj, double root);

#endif
