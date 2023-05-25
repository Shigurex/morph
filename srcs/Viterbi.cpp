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

	while (index < size) {
		vec_phrase_	vec_phrase = this->getPhrases(index);
		std::cout << "vector size: " << vec_phrase.size() << std::endl;

		if (vec_phrase.size() > 0) {
			Phrase	phrase = vec_phrase.back();
			index += phrase.getPhrase().length();
			final_sequence.push_back(phrase);
		}
		else {
			std::cout << "[file] " << __FILE__ << " [line] " << __LINE__ << " [func] " << __FUNCTION__ << std::endl;
			throw std::exception();
		}
	}
	return (final_sequence);
}
