#ifndef DICT_HPP
# define DICT_HPP

# include	<iostream>
# include	<map>
# include	<fstream>
# include	<filesystem>
# include	<regex>
# include	"define.hpp"
# include	"utils.hpp"
# include	"Phrase.hpp"

typedef std::map<str_, Phrase>	map_str_phrase_;

class Dict
{
	private:
		map_str_phrase_	_dict;
		vec_int_		_matrix;
		int				_num_id_types;

	public:
		Dict() {};
		~Dict() {};

		void	loadDict(str_ dir_path);
		void	loadCSV(str_ csv_path);
		void	loadMatrix(str_ matrix_path);
		Phrase	findPhrase(str_ phrase);
		int		getConnectionCost(int left_id, int right_id);

		class PhraseNotInDictException : public std::exception
		{
			virtual const char	*what() const throw() {return ("cannot find phrase in dictionary");};
		};

		class NoMorePhraseInDictException : public std::exception
		{
			virtual const char	*what() const throw() {return ("no more matching phrase in dictionary");};
		};
};

#endif
