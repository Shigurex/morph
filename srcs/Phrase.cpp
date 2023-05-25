#include	"Phrase.hpp"

Phrase::Phrase(vec_str_ split_line)
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

vec_str_	Phrase::getInfo(void) const
{
	return (this->_info);
}
