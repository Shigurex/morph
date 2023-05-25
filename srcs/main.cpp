#include	"Morph.hpp"

int	main(void)
{
	Dict	dict;

	//calculateTime();
	dict.loadDict("./dict/jumandic/");
	//calculateTime();

	Viterbi	viterbi(dict);

	std::cout << "Starting infinite loop" << std::endl;

	str_	line;

	while (true) {
		std::cin >> line;
		try
		{
			viterbi.setSequence(line);
			vec_phrase_	vec_phrase = viterbi.getLongestSequence();
			for (size_t i = 0; i < vec_phrase.size(); i++)
				std::cout << vec_phrase[i].getPhrase() << " -> ";
			std::cout << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
	return (0);
}
