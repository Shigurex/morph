#include	"Morph.hpp"

int	main(void)
{
	Dict	dict;

	dict.loadDict("./dict/jumandic/");

	Viterbi	viterbi(dict);

	std::cout << "Starting infinite loop" << std::endl;

	str_	line;

	while (true) {
		std::cin >> line;
		try
		{
			viterbi.setSequence(line);
			vec_phrase_	vec_phrase = viterbi.getLongestSequence();
			viterbi.printSequence(vec_phrase);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
	return (0);
}
