#include	"DoubleArray.hpp"

DoubleArray::DoubleArray()
{
	this->_base = vec_int_(1000000);
	this->_check = vec_int_(1000000);
}

void	DoubleArray::loadCharTable(str_ table_path)
{
	std::ifstream	ifs(table_path);
	str_			line;
	int				i = 1;

	if (ifs.fail())
		exitError("failed to open file", __FILE__, __LINE__, __FUNCTION__);

	// 終了文字 # の定義
	this->_char_table["#"] = i;
	i++;
	while (std::getline(ifs, line)) {
		this->_char_table[line] = i;
		i++;
	}

	ifs.close();

	std::cout << table_path << " loaded" << std::endl;
	std::cout << "[word size] " << this->_char_table.size() << std::endl;
}

int	DoubleArray::forward(int s, str_ c)
{
	int	t = this->_base[s] + this->_char_table[c];
	//if (this->_check[t])
	return (0);
}
