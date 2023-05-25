#ifndef PHRASE_HPP
# define PHRASE_HPP

# include	<vector>
# include	<iostream>
# include	"define.hpp"

class Phrase
{
	private:
		str_		_phrase;
		int			_left_id;
		int			_right_id;
		int			_cost;
		str_		_part_of_speech;
		vec_str_	_info;

	public:
		Phrase() {}
		Phrase(vec_str_ split_line);
		~Phrase() {};

		str_		getPhrase(void) const;
		int			getLeftID(void) const;
		int			getRightID(void) const;
		int			getCost(void) const;
		vec_str_	getInfo(void) const;
};

#endif
