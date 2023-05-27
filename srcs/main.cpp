#include	"Morph.hpp"

int	main(void)
{
	Dict	dict;

	dict.loadDict("./dict/jumandic/");
	Analyze	analyze(dict);

	std::cout << "input sequence" << std::endl;

	str_		line;

	while (true) {
		std::cout << "> ";
		std::cin >> line;
		try
		{
			std::cout << "最長一致法" << std::endl;
			analyze.setSequence(line);
			vec_phrase_	vec_phrase = analyze.getLongestSequence();
			analyze.printSequence(vec_phrase);

			std::cout << std::endl;

			std::cout << "最小コスト法" << std::endl;
			analyze.setSequence(line);
			vec_phrase_	vec_phrase2 = analyze.getLowestCostSequence();
			analyze.printSequence(vec_phrase2);
		}
		catch(const std::exception& e)
		{
			std::cerr << "word not in map used" << std::endl;
		}
	}
	return (0);
}
