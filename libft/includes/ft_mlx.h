/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 05:06:14 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/20 05:06:14 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MLX_H
# define FT_MLX_H

# include <mlx.h>
# include "libft.h"
# include "ft_mlx.h"

typedef enum	e_mlx_keys
{
	KEY_ESC = 53,
	KEY_LEFT = 123,
	KEY_UP = 126,
	KEY_RIGHT = 124,
	KEY_DOWN = 125
}				t_mlx_keys;

typedef struct	s_mlx_init
{
	void	*to_free_data;
	void	*add_data;
	int		(*free_func)(void*);
	int		(*key_func)(int, void*);
	int		(*mouse_func)(int, int, int, void*);
	int		(*expose_func)(void*);
	int		(*loop_func)(void*);
}				t_mlx_init;

typedef struct	s_mlx
{
	void	*add_data;
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img;
	int		*img_data;
	void	*to_free_data;
	int		(*free_func)(void*);
	int		(*key_func)(int, void*);
	int		(*mouse_func)(int, int, int, void*);
	int		(*expose_func)(void*);
	int		(*loop_func)(void*);
	int		x;
	int		y;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}				t_mlx;

typedef struct	s_point
{
	int x;
	int y;
}				t_point;

typedef struct	s_hsv
{
	unsigned short	hue;
	unsigned char	sat;
	unsigned char	vol;
}				t_hsv;

/*
**	ft_hsv.c
*/
t_hsv			ft_rgb_to_hsv(unsigned int argb);
unsigned int	ft_hsv_to_rgb(t_hsv hsv);
/*
**	ft_hsv_grad.c
*/
unsigned int	ft_hsv_gradient(t_hsv from, t_hsv to,
				const double points[3], char dir);
/*
**	ft_mlx_destroy.c
*/
void			*ft_destroy_mlx(t_mlx *mlx, int ret);
int				ft_mlx_close(void *p);
/*
**	ft_mlx_hooks.c
*/
int				ft_mlx_main_key_hook(int key, void *data);
int				ft_mlx_main_mouse_hook(int button, int x, int y, void *param);
int				ft_mlx_main_expose_hook(void *param);
int				ft_mlx_main_loop_hook(void *param);
/*
**	ft_mlx_img.c
*/
void			ft_mlx_rectput(t_mlx *mlx, t_point size, t_point pos,
				int color);
void			ft_mlx_frameput(t_mlx *mlx, t_point size, t_point pos,
				int color);
void			ft_mlx_pixelput(t_mlx *mlx, int x, int y, int color);
void			ft_mlx_put_img(t_mlx *mlx);
void			ft_mlx_clear(t_mlx *mlx);
/*
**	ft_mlx_init.c
*/
void			ft_assign_mlx_data(t_mlx *mlx, int x, int y,
				t_mlx_init *init_data);
t_mlx			*ft_mlx_init(int x, int y, char *name,
				t_mlx_init tofree_data_freefunc_key_mouse_expose_loop);

#endif
