#include	"utils.hpp"

void	exitError(str_ message, str_ file, int line, str_ func)
{
	std::cout << \
		message << " : " \
		"[file] " << file << \
		" [line] " << line << \
		" [func] " << func << std::endl;
	std::exit(EXIT_FAILURE);
}

vec_str_	split(str_ str, str_ delim)
{
	vec_str_	vec_str;
	size_t		pos = 0;
	size_t		found;

	while (true)
	{
		found = str.find_first_not_of(delim, pos);
		if (found == str_::npos)
			break;
		pos = found;
		found = str.find_first_of(delim, pos);
		if (found == str_::npos)
			break;
		vec_str.push_back(str.substr(pos, found - pos));
		pos = found + 1;
	}
	vec_str.push_back(str.substr(pos));
	return (vec_str);
}

int	charLenByte(unsigned char c)
{
	if ((c & 0xF8) == 0xF0)
		return (4);
	else if ((c & 0xF0) == 0xE0)
		return (3);
	else if ((c & 0xE0) == 0xC0)
		return (2);
	else
		return (1);
}

void	calcTime(void)
{
	static bool	is_set = false;
	static std::chrono::system_clock::time_point	time_keep;

	std::chrono::system_clock::time_point	current_time = std::chrono::system_clock::now();

	if (!is_set) {
		time_keep = current_time;
		is_set = true;
	}
	else {
		auto	dur = current_time - time_keep;
		auto	msec = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
		std::cout << msec << " [msec]" << std::endl;
		is_set = false;
	}
}
