/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <cmarteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 20:11:33 by marvin            #+#    #+#             */
/*   Updated: 2021/09/17 19:33:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include "../minilibx-linux/mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "get_next_line.h"

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;	
}				t_img;

typedef struct s_tex
{
	int		width;
	int		height;
	t_img	tex;
}			t_tex;

typedef struct s_rect
{
	int		x;
	int		y;
	int		width;
	int		height;
}				t_rect;

typedef struct s_sprite
{
	int				top;
	int				bottom;
	int				left;
	int				right;
	int				t_x;
	int				t_y;
	int				h;
	int				w;
	double			d;
	int				spritescreenx;
	t_tex			tex;
	int				x;
	int				y;
	char			y_n;
	struct s_sprite	*next;
}				t_sprite;

typedef struct s_list
{
	t_sprite	*first;
}			t_list;

typedef struct s_key
{
	int				keycode;
	struct s_key	*next;
}				t_key;

typedef struct s_key_list
{
	t_key	*first;
}				t_key_list;

typedef struct s_cub3d
{
	void		*img;
	int			*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	void		*mlx_ptr;
	void		*win_ptr;	
	double		x;
	double		y;
	double		dirvecx;
	double		dirvecy;
	double		camplanex;
	double		camplaney;
	double		camx;
	double		rayx;
	double		rayy;
	int			mapx;
	int			mapy;
	double		distox;
	double		distoy;
	double		deltadistx;
	double		deltadisty;
	double		distowall;
	int			stepx;
	int			stepy;
	int			wall;
	int			side;
	int			wallheight;
	int			walltop;
	int			wallbottom;
	double		speed;
	int			width;
	int			height;
	int			floor_color;
	int			ceiling_color;
	t_tex		no_tex;
	t_tex		so_tex;
	t_tex		we_tex;
	t_tex		ea_tex;
	t_tex		sp_tex;
	int			tex_pos;
	double		exact_x;
	int			tex_x;
	int			tex_y;
	char		**mapo;
	t_tex		tex ;
	int			tex_x_sprite;
	int			tex_y_sprite;
	t_sprite	sprite;
	double		*zbuffer;
	t_list		list;
	t_key_list	keys;
	int			flag;
	int			assigned;
	int			size_max;
}					t_cub3d;

void		ft_raycasting(t_cub3d *data);
void		ft_img_init(t_cub3d *data);
void		ft_key(t_cub3d *data);
void		ft_free_keys(t_cub3d *data);
void		ft_free_all(t_cub3d*data);
void		ft_key_delete(t_key_list *list, int keycode);
void		ft_key_addfront(t_key_list *list, t_key *new);
void		ft_forward(t_cub3d *data);
void		ft_backward(t_cub3d *data);
void		ft_right(t_cub3d *data);
void		ft_left(t_cub3d *data);
void		ft_lateral_right(t_cub3d *data);
void		ft_lateral_left(t_cub3d *data);
void		ft_definition(t_cub3d *data);
void		ft_raydef(t_cub3d *data);
void		ft_texture(char *line, t_cub3d *data, char c);
void		ft_textdef(int count_h, int count_w, t_cub3d *data);
void		ft_textsprite(t_cub3d *data, t_sprite *sprite);
void		ft_sprite_loop(t_cub3d *data);
void		ft_add_front(t_list *list, t_sprite *new);
void		ft_draw_sprite(t_cub3d *data);
void		ft_free_list(t_list *list);
void		ft_free_table(char **str);
void		ft_localize_sprite(t_cub3d *data);
void		ft_init_game(t_cub3d *data, char *map);
void		ft_parsing_map(t_cub3d *data, char *map);
void		ft_wall_limits(t_cub3d *data);
void		ft_sprite_limits(t_cub3d *data, t_sprite *new);
void		ft_minimap(t_cub3d *data);
void		ft_parsing_player(t_cub3d *data);
void		ft_parsing_dir(t_cub3d *data);
void		ft_parsing_cam(t_cub3d *data);
void		ft_pustr(char *str);
void		ft_error(int a);
void		ft_error_map1(t_cub3d *data);
void		ft_parsing_params(char *line, char c, t_cub3d *data);
void		ft_parsing(char *map, char c, t_cub3d *data);
void		ft_map_check(char *line, t_cub3d *data);
void		ft_nb_params(char *line, int j);
void		ft_error_params(t_cub3d *data);
void		ft_check_multiple_assignement(char *line, t_cub3d *data);
void		ft_replace_space(char *line, t_cub3d *data);
void		ft_error_map2(t_cub3d *data);
void		ft_def_tex(t_tex tex, char c, t_cub3d *data, char *str);
void		ft_parsing_tex(char *line, char c, t_cub3d *data);
void		ft_textdef_ns(int y, int x, t_cub3d *data, char c);
void		ft_textdef_ew(int y, int x, t_cub3d *data, char c);
void		ft_write_error(int a);
void		ft_error_assignment(char *line, int i, t_cub3d *data);
void		ft_error_tex(char *line, int a, t_cub3d *data);
void		ft_distowall(t_cub3d *data);
void		ft_new_sprite(t_cub3d *data, t_sprite *new);
void		ft_free_split(char *line, char *str, char **tab, t_cub3d *data);
void		ft_tex_err(char *str, char *line, t_cub3d *data);
void		ft_color_check(char *line);
void		ft_color_param(char *line, char *str);
void		ft_empty_line(char *line);

int			my_mlx_image(t_cub3d *data);
int			close_window(t_cub3d *data);
int			key_press(int keycode, t_cub3d *data);
int			ft_key_check(t_key_list *list, int keycode);
int			key_release(int keycode, t_cub3d *data);
int			ft_search_char(char *s, char c);
int			ft_width(char *line);
int			ft_height(char *line);
int			ft_color(char *line);
int			ft_colorred(char *line);
int			ft_colorgreen(char *line);
int			ft_colorblue(char *line);
int			ft_atoi(const char *str);
int			ft_truc(int i);
int			ft_check_split(char *str, int *i);
int			ft_skip_space(char *str, int i);
int			ft_parse_colors(char *line);

char		*ft_parsing_mapo(char *line, char c, int fd, char *tmp);
char		*ft_strdup(const char *s1);

t_key		*ft_new_key(int keycode);

double		ft_calcul_distowall(t_cub3d *data);

t_sprite	*ft_sprite(t_cub3d *data);

char		**ft_split(const char *str, char c, t_cub3d *data, char *line);

#endif
