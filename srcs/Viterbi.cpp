#include	"Viterbi.hpp"

Viterbi::Viterbi(Dict& dict) : _dict(dict)
{
	;
}

void	Viterbi::setSequence(str_ sequence)
{
	this->_sequence = sequence;
}

vec_phrase_	Viterbi::getPhrases(size_t index)
{
	size_t		size = this->_sequence.length();
	vec_phrase_	vec_phrase;

	for (size_t i = 0; i <= size - index; i++) {
		try
		{
			vec_phrase.push_back(this->_dict.findPhrase(this->_sequence.substr(index, i)));
		}
		catch(const Dict::NoMorePhraseInDictException& e)
		{
			break ;
		}
		catch(const Dict::PhraseNotInDictException& e)
		{
			;
		}
	}
	return (vec_phrase);
}

vec_phrase_	Viterbi::getLongestSequence()
{
	size_t		size = this->_sequence.length();
	size_t		index = 0;
	vec_phrase_	final_sequence;

	final_sequence.push_back(Phrase("__BOS__", -1, 0, 0, "開始文字"));

	while (index < size) {
		vec_phrase_	phrase_option = this->getPhrases(index);

		if (phrase_option.size() > 0) {
			Phrase	longest_phrase = phrase_option.back();
			index += longest_phrase.getPhrase().length();
			final_sequence.push_back(longest_phrase);
		}
		else {
			std::cout << "[file] " << __FILE__ << " [line] " << __LINE__ << " [func] " << __FUNCTION__ << std::endl;
			throw std::exception();
		}
	}

	final_sequence.push_back(Phrase("__EOS__", 0, -1, 0, "終了文字"));

	return (final_sequence);
}

void	Viterbi::printSequence(vec_phrase_ sequence)
{
	size_t	size = sequence.size();

	for (size_t i = 0; i < size; i++) {
		std::cout << "[" << sequence[i].getPhrase() \
		<< "] : " << sequence[i].getPartOfSpeech() \
		<< ", " << sequence[i].getCost() << std::endl;
	}
	std::cout << "Total cost : " << calcTotalCost(sequence) << std::endl;
}

int	Viterbi::calcTotalCost(vec_phrase_ sequence)
{
	size_t	size = sequence.size();
	int		cost = 0;

	for (size_t i = 0; i < size; i++) {
		cost += sequence[i].getCost();
		if (sequence[i].getPartOfSpeech() == "終了文字")
			break ;
		cost += this->_dict.getConnectionCost(sequence[i].getRightID(), sequence[i + 1].getLeftID());
	}
	return (cost);
}

