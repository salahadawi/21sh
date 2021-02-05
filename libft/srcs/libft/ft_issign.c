#include "libft.h"

int		ft_issign(int c)
{
	return ((33 <= c && c < 39) || (40 <= c && c < 47) || (c == 58) ||
    (c == 61) || (63 <= c && c <= 64) || (c == 96) || (123 <= c && c < 127));
}