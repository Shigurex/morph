#include	"Phrase.hpp"

Phrase::Phrase(str_ phrase, int left_id, int right_id, int cost, str_ part_of_speech) : total_cost(0)
{
	this->_phrase = phrase;
	this->_left_id = left_id;
	this->_right_id = right_id;
	this->_cost = cost;
	this->_part_of_speech = part_of_speech;
}

Phrase::Phrase(vec_str_ split_line) : total_cost(0)
{
	this->_phrase = split_line[0];
	this->_left_id = std::stoi(split_line[1]);
	this->_right_id = std::stoi(split_line[2]);
	this->_cost = std::stoi(split_line[3]);
	this->_part_of_speech = split_line[4];
	this->_info = split_line;
}

str_	Phrase::getPhrase(void) const
{
	return (this->_phrase);
}

int	Phrase::getLeftID(void) const
{
	return (this->_left_id);
}

int	Phrase::getRightID(void) const
{
	return (this->_right_id);
}

int	Phrase::getCost(void) const
{
	return (this->_cost);
}

str_	Phrase::getPartOfSpeech(void) const
{
	return (this->_part_of_speech);
}

vec_str_	Phrase::getInfo(void) const
{
	return (this->_info);
}
