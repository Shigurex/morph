#ifndef DOUBLEARRAY_HPP
# define DOUBLEARRAY_HPP

# include	<fstream>
# include	<iostream>
# include	"utils.hpp"
# include	"define.hpp"

class DoubleArray
{
	private:
		vec_int_	_base;
		vec_int_	_check;
		map_str_int	_char_table;
		int			_char_table_max;

	public:
		DoubleArray();
		~DoubleArray() {};

		void	loadCharTable(str_ table_path);
		int	forward(int s, str_ c);
};

#endif