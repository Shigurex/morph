#include	"Analyze.hpp"

void	Analyze::setSequence(str_ sequence)
{
	this->_sequence = sequence;
}

vec_phrase_	Analyze::getPhrases(size_t index)
{
	size_t		size = this->_sequence.length();
	vec_phrase_	vec_phrase;

	for (size_t i = 0; i <= size - index; i++) {
		try {vec_phrase.push_back(this->_dict.findPhrase(this->_sequence.substr(index, i)));}
		catch(const Dict::NoMorePhraseInDictException& e) {break ;}
		catch(const Dict::PhraseNotInDictException& e) {}
	}
	return (vec_phrase);
}

vec_phrase_	Analyze::getLongestSequence(void)
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
		} else {
			std::cout << "[file] " << __FILE__ << " [line] " << __LINE__ << " [func] " << __FUNCTION__ << std::endl;
			throw std::exception();
		}
	}

	final_sequence.push_back(Phrase("__EOS__", 0, -1, 0, "終了文字"));

	return (final_sequence);
}

Phrase	Analyze::_getLowestCostNode(size_t index_multibyte)
{
	vec_phrase_	phrase_current = this->_node_prev[index_multibyte];
	size_t		phrase_current_size = phrase_current.size();
	Phrase		lowest_cost_phrase = phrase_current[0];
	size_t		i;

	for (i = 1; i < phrase_current_size; i++) {
		if (phrase_current[i].total_cost < lowest_cost_phrase.total_cost)
			lowest_cost_phrase = phrase_current[i];
	}
	return (lowest_cost_phrase);
}

void	Analyze::_pushBackLowestCost(vec_phrase_& vec_phrase, Phrase phrase)
{
	size_t	vec_phrase_size = vec_phrase.size();

	for (size_t i = 0; i < vec_phrase_size; i++) {
		if (vec_phrase[i].getPhrase() == phrase.getPhrase()) {
			if (vec_phrase[i].total_cost > phrase.total_cost)
				vec_phrase[i].total_cost = phrase.total_cost;
			return ;
		}
	}

	vec_phrase.push_back(phrase);
}

void	Analyze::_connectNodeRecursive(size_t index, size_t index_multibyte)
{
	if (index_multibyte >= strLenMultibyte(this->_sequence)) {
		Phrase	eos("__EOS__", 0, -1, 0, "終了文字");

		Phrase	lowest_cost_node = this->_getLowestCostNode(index_multibyte);

		int	connection_cost = this->_dict.getConnectionCost(lowest_cost_node.getRightID(), eos.getLeftID());
		eos.total_cost = lowest_cost_node.total_cost + connection_cost + eos.getCost();

		this->_pushBackLowestCost(this->_node_next[index_multibyte], eos);
		return ;
	}

	vec_phrase_	phrase_option = this->getPhrases(index);
	size_t		phrase_num = phrase_option.size();

	if (phrase_num > 0) {
		for (size_t i = 0; i < phrase_num; i++) {
			str_	phrase = phrase_option[i].getPhrase();
			size_t	phrase_len = strLenMultibyte(phrase);

			Phrase	lowest_cost_node = this->_getLowestCostNode(index_multibyte);

			int	connection_cost = this->_dict.getConnectionCost(lowest_cost_node.getRightID(), phrase_option[i].getLeftID());
			phrase_option[i].total_cost = lowest_cost_node.total_cost + connection_cost + phrase_option[i].getCost();

			this->_pushBackLowestCost(this->_node_next[index_multibyte], phrase_option[i]);
			this->_pushBackLowestCost(this->_node_prev[index_multibyte + phrase_len], phrase_option[i]);

			//std::cout << "[" << index_multibyte << "] " << phrase << " (" << phrase_option[i].total_cost << ")" << std::endl;

			this->_connectNodeRecursive(index + phrase.length(), index_multibyte + phrase_len);
		}
	} else {
		std::cout << "[file] " << __FILE__ << " [line] " << __LINE__ << " [func] " << __FUNCTION__ << std::endl;
		throw std::exception();
	}
}

vec_phrase_	Analyze::_connectNodeBackward(void)
{
	vec_phrase_	final_sequence;
	size_t		index = strLenMultibyte(this->_sequence);

	final_sequence.insert(final_sequence.begin(), this->_node_next[index][0]);

	while (true) {
		Phrase	phrase = _getLowestCostNode(index);
		final_sequence.insert(final_sequence.begin(), phrase);

		if (phrase.getPartOfSpeech() == "開始文字")
			break ;

		index -= strLenMultibyte(phrase.getPhrase());
	}

	return (final_sequence);
}

vec_phrase_	Analyze::getLowestCostSequence(void)
{
	vec_phrase_	final_sequence;
	size_t		len_multibyte = strLenMultibyte(this->_sequence);

	this->_node_prev = new vec_phrase_[len_multibyte + 1];
	this->_node_next = new vec_phrase_[len_multibyte + 1];

	this->_node_prev[0].push_back(Phrase("__BOS__", -1, 0, 0, "開始文字"));
	_connectNodeRecursive(0, 0);

	final_sequence = _connectNodeBackward();

	delete []this->_node_prev;
	delete []this->_node_next;

	return (final_sequence);
}

void	Analyze::printSequence(vec_phrase_ sequence)
{
	size_t	size = sequence.size();

	for (size_t i = 0; i < size; i++) {
		std::cout << "[" << sequence[i].getPhrase() \
		<< "] : " << sequence[i].getPartOfSpeech() \
		<< ", " << sequence[i].getCost() << std::endl;
	}
	std::cout << "Total cost : " << calcTotalCost(sequence) << std::endl;
}

int	Analyze::calcTotalCost(vec_phrase_ sequence)
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
