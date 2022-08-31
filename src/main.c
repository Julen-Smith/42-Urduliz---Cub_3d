#include "../include/cub3d.h"

int	main(int argc, char *argv[])
{
	int		fd;
	t_in	dt;//inicio estructura de datos inicial

	if (argc != 2)
	{
		printf("Error in arguments\n");
		return (0);
	}
	fd = open(argv[1], O_RDWR);
	if (fd == -1)
	{
		perror("Open error\n");
		return (0);
	}
	ft_traspas(fd, argv[1], &dt);
	close(fd);
	ft_free(&dt);
//	system("leaks cub");
	return (0);
}

//funcion inicial que empieza a analizar el mapa
int	ft_traspas(int fd, char *argv, t_in *dt)
{
	t_hook	*hk;

	hk = ft_memset(dt);
	if (ft_create_bid(fd, dt, argv) == -1)
		return (-1);
	if (ft_ch_map(dt) == -1)
	{
		printf ("Map error\n");
		return (-1);
	}
	if (ft_draw_map (hk) == -1)
	{
		printf ("Draw map error\n");
		return (-1);
	}
	if (ft_rayc_init(hk) == -1)
	{
		printf ("Calculs error\n");
		return (-1);
	}
	return (0);
}

//resetea los valores iniciales
t_hook	*ft_memset(t_in *dt)
{
	t_mlx	*gr;//creo la libreria grafica
	t_hook	*hk;//creo la estructura unica para trabajar con las funciones de la mlx

	dt->map = NULL;
	dt->xo = 0;
	dt->yo = 0;
	gr = NULL;
	hk = NULL;
	gr = (t_mlx *)malloc(sizeof(t_mlx) * 1);
	hk = (t_hook *)malloc(sizeof(t_hook) * 1);
	if (!gr || !hk)
		return (NULL);
	hk->dt = dt;
	hk->gr = gr;
	gr->mlx = mlx_init();//inicio la libreria gráfica 
	return (hk);
}

void	ft_free(t_in *dt)
{
	int	i;

	if (dt->map)
	{
		i = -1;
		while (dt->map[++i])
			free (dt->map[i]);
		free (dt->map);
	}
}

void	ft_free_hk(t_hook *hk)
{
	int	i;

	if (hk->dt->map)
	{
		i = -1;
		while (hk->dt->map[++i])
			free (hk->dt->map[i]);
		free (hk->dt->map);
	}
	free (hk->gr);
	free (hk);
}
