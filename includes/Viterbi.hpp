#ifndef VITERBI_HPP
# define VITERBI_HPP

# include	<iostream>
# include	"Phrase.hpp"
# include	"utils.hpp"
# include	"Dict.hpp"
# include	"define.hpp"

typedef std::vector<Phrase> vec_phrase_;

class Viterbi
{
	private:
		Dict&	_dict;
		str_	_sequence;

	public:
		Viterbi(Dict& dict);
		~Viterbi() {};

		void		setSequence(str_ sequence);
		vec_phrase_	getPhrases(size_t index);
		vec_phrase_	getLongestSequence();
		void		printSequence(vec_phrase_ sequence);
		//int			calcCost(vec_str_ vec_str);
};

#endif
