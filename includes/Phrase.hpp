#ifndef PHRASE_HPP
# define PHRASE_HPP

# include	<vector>
# include	<iostream>
# include	<exception>
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
		int			total_cost;

		Phrase() : total_cost(0) {}
		Phrase(vec_str_ split_line);
		Phrase(str_ phrase, int left_id, int right_id, int cost, str_ part_of_speech);
		~Phrase() {};

		str_		getPhrase(void) const;
		int			getLeftID(void) const;
		int			getRightID(void) const;
		int			getCost(void) const;
		str_		getPartOfSpeech(void) const;
		vec_str_	getInfo(void) const;
};

#endif
