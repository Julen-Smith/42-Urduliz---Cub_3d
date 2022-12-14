#include "../../include/cub3d.h"

//funcion que chequea si el mapa es valido
int ft_ch_map(t_in *dt)
{
    int i;

    if (ft_ch_chars(dt) == -1)
        return (-1);
	dt->map = ft_add_columns(dt);
    if (ft_ch_personage(dt) == -1)
        return (-1);
    dt->map[dt->yo][dt->xo] = '0';//sustituyo el personaje por 0
    if (ft_ch_spaces(dt) == -1)
        return (-1);
    if (ft_ch_close(dt) == -1)
        return (-1);
/*    i = -1;
    while (dt->map[++i])
        printf ("El map %d: <%s>\n", i, dt->map[i]);
*/    return (0);
}

//chequeo el mapa por si tiene chars prohibidos o permitidos duplicados
//también guardo la posición del personaje
int ft_ch_chars(t_in *dt)
{
    int i;
    int j;
    int n;

    i = -1;
    n = 0;
    while (dt->map[++i])
    {
        j = -1;
        while (dt->map[i][++j])
        {
            if (dt->map[i][j] != '0' && dt->map[i][j] != '1' && dt->map[i][j] != ' ')
            {
                if (dt->map[i][j] != 'N' && dt->map[i][j] != 'S' && dt->map[i][j] != 'E' && dt->map[i][j] != 'O')
                {
                    printf ("Error\nBad char in map - ");
                    return (-1);
                }
                n++;
				if (ft_ch_chars_aux(i, j, n, dt) == -1)
					return (-1);
            }
        }
    }
	return (0);
}

//aux de la ft_ch_char
//funcion que guarda la posición del personaje en la estructura y lo substituye por un 0
int	ft_ch_chars_aux(int i, int j, int n, t_in *dt)
{
    if (n != 1)
    {
        if (n == 0)
            printf ("Error\nNo personage in map - ");
        else
            printf ("Error\nMore than one personage in map - ");
        return (-1);
    }
    dt->xo = j;
    dt->yo = i;
//	printf ("El personaje esta en:\ni: %d\nj: %d\n", dt->yo, dt->xo);
    return (0);
}

//cambia el map añadiendo espacios en los huecos vacios a la derecha y asi regularizar el map
char    **ft_add_columns(t_in *dt)
{
    char    **aux;
    int     i;
    int     j;

    aux = (char **) malloc (sizeof(char *) * (dt->maxy + 1));
    if (!aux)
        return (NULL);
    i = 0;
    while (dt->map[i])
    {
        aux[i] = (char *) malloc (sizeof(char) * (dt->maxx + 1));
        j = -1;
        while (dt->map[i][++j])
            aux[i][j] = dt->map[i][j];
        while (j < dt->maxx)
            aux[i][j++] = ' ';
        aux[i][j] = 00;
        free (dt->map[i++]);
    }
    aux[i] = NULL;
    free (dt->map);
    return (aux);
}

//chequeo si el personage esta tocando algun espacio o rodeado de 1
int ft_ch_personage(t_in *dt)
{
    int i;
    int j;
    int n;

    i = -1;
    n = 0;
    while (dt->map[++i])
    {
        j = -1;
        while (dt->map[i][++j])
        {
            if (dt->map[i][j] == 'N' || dt->map[i][j] == 'S' || dt->map[i][j] == 'E' || dt->map[i][j] == 'O')
            {
                n = ft_ch_personage_out(i, j, dt);
                if (n == 1)
                    printf ("Error\nPersonage inside limits - ");
                else if (n == 2)
                    printf ("Error\nPersonage in the air - ");
                else if (n == 3)
                    printf ("Error\nEncapsulated personage - ");
                if (n != 0)
                    return (-1);
            }
        }
    }
    return (0);
}

//aux de ft_ch_personage
int     ft_ch_personage_out(int i, int j, t_in *dt)
{
	dt->dir = dt->map[i][j];//guardo la direccion del personaje
    if (i == 0 || i == (dt->maxy - 1) || j == 0 || j == (dt->maxx - 1))
        return (1);//caso del personage en los limites del mapa
    else if (dt->map[i][j - 1] == ' ' || dt->map[i][j + 1] == ' ' || dt->map[i - 1][j] == ' ' || dt->map[i + 1][j] == ' ')
        return (2);
    else if (dt->map[i - 1][j] == '!' || dt->map[i + 1][j] == '!')
        return (2);
    else if (dt->map[i][j - 1] == '1' && dt->map[i][j + 1] == '1' && dt->map[i - 1][j] == '1' && dt->map[i + 1][j] == '1')
        return (3);
    return (0);
}

//funcion que comprueba en el char mandado
int	ft_ch(int i, int j, t_in *dt, int n)
{
	if (dt->map[i][j])
	{
		if (n == 0)//compruebo 1 o esp
		{
			if (dt->map[i][j] != '1' && dt->map[i][j] != ' ')
				return (-1);
		}
		if (n == 1)//compruebo 1 o 0
		{
			if (dt->map[i][j] != '1' && dt->map[i][j] != '0' && dt->map[i][j] != 'N')
				return (-1);
		}
	}
	return (0);
}

