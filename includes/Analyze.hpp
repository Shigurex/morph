#ifndef Analyze_HPP
# define Analyze_HPP

# include	<iostream>
# include	<algorithm>
# include	"Phrase.hpp"
# include	"utils.hpp"
# include	"Dict.hpp"
# include	"define.hpp"

typedef std::vector<Phrase> vec_phrase_;

class Analyze
{
	private:
		Dict&		_dict;
		str_		_sequence;
		vec_phrase_	*_node_prev;
		vec_phrase_	*_node_next;

		void		_connectNodeRecursive(size_t index, size_t index_multibyte);
		Phrase		_getLowestCostNode(size_t index_multibyte);
		void		_pushBackLowestCost(vec_phrase_& vec_phrase, Phrase phrase);
		vec_phrase_	_connectNodeBackward(void);

	public:
		Analyze(Dict& dict) : _dict(dict) {};
		~Analyze() {};

		void		setSequence(str_ sequence);
		vec_phrase_	getPhrases(size_t index);
		vec_phrase_	getLongestSequence(void);
		vec_phrase_	getLowestCostSequence(void);
		void		printSequence(vec_phrase_ sequence);
		int			calcTotalCost(vec_phrase_ sequence);
};

#endif
