#ifndef UTILS_HPP
# define UTILS_HPP

# include	<iostream>
# include	<cstdlib>
# include	<vector>
# include	<chrono>
# include	"define.hpp"

void		exitError(str_ message, str_ file, int line, str_ func);
vec_str_	split(str_ str, str_ delim);
int			charLenByte(unsigned char c);
void		calculateTime(void);

#endif
