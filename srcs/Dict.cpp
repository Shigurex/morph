#include	"Dict.hpp"

void	Dict::loadDict(str_ dir_path)
{
	regex_	target_file(".*.csv$");

	for (const std::filesystem::directory_entry& file : std::filesystem::directory_iterator(dir_path)) {
		str_	file_path = file.path();
		if (std::regex_match(file_path, target_file))
			this->loadCSV(file_path);
		else if (file_path == dir_path + "matrix.def")
			this->loadMatrix(file_path);
	}

	std::cout << "[dict size] " << this->_dict.size() << std::endl;
	std::cout << "[matrix size] " << this->_matrix.size() << std::endl;
}

void	Dict::loadCSV(str_ csv_path)
{
	std::ifstream	ifs(csv_path);
	str_			line;
	vec_str_		split_line;

	if (ifs.fail())
		exitError("failed to open file", __FILE__, __LINE__, __FUNCTION__);

	while (std::getline(ifs, line)) {
		split_line = split(line, ",");
		Phrase		phrase(split_line);
		_dict[split_line[0]] = phrase;
	}

	ifs.close();

	std::cout << csv_path << " loaded" << std::endl;
}

void	Dict::loadMatrix(str_ matrix_path)
{
	std::ifstream	ifs(matrix_path);
	str_			line;
	vec_str_		split_line;

	if (ifs.fail())
		exitError("failed to open file", __FILE__, __LINE__, __FUNCTION__);

	std::getline(ifs, line);
	split_line = split(line, " ");
	this->_num_id_types = std::stoi(split_line[0]);
	this->_matrix = vec_int_(this->_num_id_types * this->_num_id_types);

	while (std::getline(ifs, line)) {
		split_line = split(line, " ");
		int	right_id = std::stoi(split_line[0]);
		int	left_id = std::stoi(split_line[1]);
		int	connection_cost = std::stoi(split_line[2]);
		this->_matrix[right_id * this->_num_id_types + left_id] = connection_cost;
	}

	std::cout << matrix_path << " loaded" << std::endl;
}

Phrase	Dict::findPhrase(str_ phrase)
{
	if (!this->_dict.contains(phrase)) {
		map_str_phrase_::const_iterator	iter = this->_dict.lower_bound(phrase);
		if (iter != this->_dict.end()) {
			const str_&	key = iter->first;
			if (key.compare(0, phrase.size(), phrase) == 0)
				throw Dict::PhraseNotInDictException();
		}
		throw Dict::NoMorePhraseInDictException();
	}

	std::cout << "[file] " << __FILE__ << " [line] " << __LINE__ << " [func] " << __FUNCTION__ << std::endl;
	std::cout << "Phrase [ " << this->_dict[phrase].getPhrase() << " ] : cost [" << this->_dict[phrase].getCost() << "]" << std::endl;
	return (this->_dict[phrase]);
}

int	Dict::getConnectionCost(int right_id, int left_id)
{
	int	pos = right_id * this->_num_id_types + left_id;

	if (pos < 0 || this->_num_id_types * this->_num_id_types <= pos)
		exitError("matrix out of range", __FILE__, __LINE__, __FUNCTION__);
	return (this->_matrix[right_id * _num_id_types + left_id]);
}
