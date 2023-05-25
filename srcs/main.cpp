#include	"Morph.hpp"

void	stringSplit(str_ str)
{
	size_t	size = str.length();

	for (size_t i = 0; i < size; ) {
		char	c = str[i];
		int		len_c = charLenByte(c);
		std::string	character = str.substr(i, len_c);
		i += len_c;
		std::cout << character << std::endl;
	}
}

int	main(void)
{
	Dict	dict;

	// EUC-JPを変換する必要がある。
	//dict.loadDict("/Users/yamatohokari/Desktop/Keio University/3年春学期/自然言語処理/レポート/dict/mecab-ipadic-2.7.0-20070801/");

	DoubleArray	arr;

	arr.loadCharTable("./dict/jumandic/word.def");

	dict.loadDict("./dict/jumandic/");

	dict.findPhrase("すもも");
	dict.findPhrase("も");
	dict.getConnectionCost(1133, 1022);


	std::cout << "Starting infinite loop" << std::endl;

	str_	line;
	while (true) {
		std::cin >> line;
		dict.findPhrase(line);
	}
	return (0);
}
