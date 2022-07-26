/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 16:36:11 by seseo             #+#    #+#             */
/*   Updated: 2022/08/06 20:49:32 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <mlx.h>
# include <float.h>
# include "minirt_parsing.h"
# include "minirt_math.h"

# define _USE_MATH_DEFINES

# define SCRN_WIDTH			800
# define SCRN_HEIGHT		600

# define TRUE				1
# define FALSE				0

# define KEY_A				0
# define KEY_S				1
# define KEY_Z				6
# define KEY_X				7
# define KEY_C				8
# define KEY_Q				12
# define KEY_W				13
# define KEY_R				15
# define KEY_O				31
# define KEY_I				34
# define KEY_P				35

# define KEY_LEFT			123
# define KEY_RIGHT			124
# define KEY_DOWN			125
# define KEY_UP				126

# define KEY_1				18
# define KEY_2				19
# define KEY_3				20
# define KEY_4				21
# define KEY_5				23
# define KEY_6				22
# define KEY_7				26
# define KEY_8				28
# define KEY_9				25
# define KEY_0				29

# define KEY_ESC			53
# define KEY_EVENT_PRESS	2
# define KEY_EVENT_EXIT		17

// # define C_RED				0xFF0000
// # define C_GREEN			0xFF00
// # define C_BLUE				0xFF

enum	e_surface
{
	CHECKER_BOARD = 1,
	TEXTURE = 1 << 1,
	BUMP_MAP = 1 << 2
};

typedef struct s_data
{
	void	*mlx;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		w;
	int		h;
	int		endian;
}	t_data;

typedef struct s_uv_map
{
	double	u;
	double	v;
	t_vec	u_vec;
	t_vec	v_vec;
}	t_uv_map;

typedef struct s_phong
{
	double	ka;
	double	kd;
	double	ks;
	double	alpha;
	double	light_len;
	t_color	ambient;
	t_color	diffuse;
	t_color	specular;
	t_color	point_color;
}	t_phong;

typedef struct s_obj_info
{
	t_vec		pos;
	t_vec		orient;
	t_color		color;
	t_data		tx;
	t_data		bm;
	t_uv_map	uv_map;
	double		radius;
	double		r_sqare;
	double		rsq_div_hsq;
	double		rsq_div_h;
	double		map_scale;
	double		height;
	double		width;
	double		kd;
	double		ks;
	double		alpha;
	int			type;
	int			surface;
}	t_obj_info;

typedef struct s_ambi_light_info
{
	t_color	color;
	double	bright;
}	t_ambi_light_info;

typedef struct s_light_info
{
	t_vec	pos;
	t_color	color;
	double	bright;
}	t_light_info;

typedef struct s_cam_info
{
	t_vec	pos;
	t_vec	orient;
	t_vec	orient_neg;
	double	angle;
	t_vec	screen;
	t_vec	x_vec;
	t_vec	y_vec;
	double	focal_len;
}	t_cam_info;

typedef struct s_map_info
{
	t_ambi_light_info	ambi_light;
	t_light_info		*light;
	t_cam_info			*cam;
	t_obj_info			*obj;
	int					light_cnt;
	int					cam_cnt;
	int					obj_cnt;
	int					cam_idx;
}	t_map_info;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	t_map_info	*map;
	t_data		img;
}	t_vars;

// minirt_convert_data_obj.c
void	set_obj_info(t_map_info *map, t_obj *obj);

// minirt_convert_data.c
void	set_ambi_light_and_light_info(t_map_info *map_info, t_map *map, \
													t_ambi_light ambi_light);
void	set_cam_info(t_map_info *map, t_camera *cam);

// minirt_draw_img.c
void	draw_image(t_vars *vars, t_map_info *map, t_cam_info *cam);

// minirt_main_initialize.c
void	init_var_and_set_map_data(t_vars *vars, char *arg);

// minirt_main_mlx_hook.c
int		key_hook(int keycode, t_vars *vars);
int		exit_hook(t_vars *vars);

// minirt_utils_color_1.c
int		get_color(int color, int target_color);
int		convert_color_to_int(t_color color);

// minirt_utils_color_2.c
t_color	set_color(double red, double green, double blue);
t_color	color_mul(t_color color, double scale);
t_color	add_color(t_color c1, t_color c2);
t_color	set_color_from_int(int color_int);

// minirt_utils.c
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		get_mlx_pixel_color(t_data *data, int x, int y);
void	free_map(t_map *map);
void	free_map_info(t_map_info *map);
void	open_texture_img(t_data *img, char *file_name);

#endif
