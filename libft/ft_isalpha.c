/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalpha.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 16:53:52 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/10/10 16:54:26 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
    The isalpha() function tests for any character for which isupper(3) or
    islower(3) is true.  The value of the argument must be representable as an
    unsigned char or the value of EOF.

    In the ASCII character set, this includes the following characters
    (preceded by their numeric values, in octal):

    101 ``A'' 102 ``B'' 103 ``C'' 104 ``D'' 105 ``E''
    106 ``F'' 107 ``G'' 110 ``H'' 111 ``I'' 112 ``J''
    113 ``K'' 114 ``L'' 115 ``M'' 116 ``N'' 117 ``O''
    120 ``P'' 121 ``Q'' 122 ``R'' 123 ``S'' 124 ``T''
    125 ``U'' 126 ``V'' 127 ``W'' 130 ``X'' 131 ``Y''
    132 ``Z'' 141 ``a'' 142 ``b'' 143 ``c'' 144 ``d''
    145 ``e'' 146 ``f'' 147 ``g'' 150 ``h'' 151 ``i''
    152 ``j'' 153 ``k'' 154 ``l'' 155 ``m'' 156 ``n''
    157 ``o'' 160 ``p'' 161 ``q'' 162 ``r'' 163 ``s''
    164 ``t'' 165 ``u'' 166 ``v'' 167 ``w'' 170 ``x''
    171 ``y'' 172 ``z''

PARAMETERS
	c: The char that will be checked.

RETURN VALUES
    The isalpha() function returns zero if the character tests false and
    returns non-zero if the character tests true.
*/

/*
int	ft_isalpha(int c)
{
	// Checks between 'A' and 'Z' (see ascii decimal).
	if (c >= 65 && c <= 90)
		// True.
		return (1);
	// Checks between 'a' and 'z' (see ascii decimal).
	if (c >= 97 && c <= 122)
		// True.
		return (2);
	// False.
	return (0);
}

*/

#include "libft.h"

int	ft_isalpha(int c)
{
	if (c >= 65 && c <= 90)
		return (1);
	if (c >= 97 && c <= 122)
		return (2);
	return (0);
}
