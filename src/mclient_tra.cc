#include <algorithm>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

const unsigned int __debug = -1;
const char* __whitespace = " \t\n\r\f\v";

inline std::string& rtrim(std::string& s, const char* t = __whitespace)
{
	s.erase(s.find_last_not_of(t) + 1);
	return s;
}

inline std::string& ltrim(std::string& s, const char* t = __whitespace)
{
	s.erase(0, s.find_first_not_of(t));
	return s;
}

inline std::string& trim(std::string& s, const char* t = __whitespace)
{
	return ltrim(rtrim(s, t), t);
}

inline std::string& clean(std::string& s)
{
	std::replace(s.begin(), s.end(), '\n', ' ');
	std::regex line("  *");
	s = std::regex_replace(s, line, " ");
	return s;
}

std::string join_lines(std::string text)
{
	std::replace(text.begin(), text.end(), '\n', ',');
	std::regex line("([^,]*)(.)");
	text = std::regex_replace(text, line, "\"$1\"$2");
	text.pop_back();
	return text;
}

std::string evaluate_query(std::string query, std::string opt = "")
{
	std::array<char, 1024> buffer;
	std::string result;
	std::string command = "mclient " + opt + " -s'" + query + "'";
	std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);

	if (!pipe)
	{
		throw std::runtime_error("popen() failed!");
	}

	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
	{
		result += buffer.data();
	}

	return result;
}

std::string::iterator get_symbol(std::string::iterator& i, std::string::iterator b, std::string::iterator e)
{
	for (; i != b && *(i-1) != '(' && *(i-1) != ' '; --i);
	auto j = i;

	size_t parens = (*j == '(') ? 1 : 0;

	if (parens == 0)
	{
		for (++j; j != e && *j != ' ' && *j != ')'; ++j);
		return j;
	}

	for (++j; parens > 0 && j != e; ++j)
	{
		if (*j == '(')
		{
			++parens;
		}
		else if (*j == ')')
		{
			--parens;
		}
	}

	return j;
}

std::string get_phase1_query(std::string rel, std::string order)
{
	return "SELECT " + order + " FROM " + rel
		+ " AS tmp ORDER BY " + order + ";";
}

std::string get_phase2_query(std::string query, std::smatch match, std::string attributes)
{
	auto i = query.begin() + match.position() + match.length();
	auto j = get_symbol(i, query.begin(), query.end());

	return query.substr(0, j - query.begin())
		+ " USING ("
		+ attributes + ")"
		+ query.substr(j - query.begin(), query.length());
}

std::string get_matrix(std::string query, std::smatch match)
{
	auto i = query.begin() + match.position() + match.length();
	auto j = get_symbol(i, query.begin(), query.end());

	return std::string(++i, --j);
}

std::string get_matrix_relation(std::string matrix)
{
	auto i = matrix.begin();
	auto j = get_symbol(i, matrix.begin(), matrix.end());

	return std::string(i, j);
}

std::string get_matrix_order(std::string matrix)
{
	auto i = matrix.end() - 1;
	auto j = get_symbol(i, matrix.begin(), matrix.end());

	return std::string(i, j);
}

std::smatch is_tra_query(std::string query)
{
	std::smatch match;
	std::regex_search(query, match, std::regex("(\\W)(tra|TRA)\\W"));
	return match;
}

int main(int argc, char** argv)
{
	std::string query(std::istreambuf_iterator<char>(std::cin), {});
	trim(query);
	clean(query);
	auto match = is_tra_query(query);

	std::string opt;
	for (int i = 1; i < argc; ++i)
	{
		opt += " ";
		opt += argv[i];
	}
	trim(opt);
	clean(opt);

	if (match.position() == query.length())
	{
		std::cout << evaluate_query(query, opt);
		return 0;
	}

	auto matrix = get_matrix(query, match);
	auto matrix_rel = get_matrix_relation(matrix);
	auto matrix_ord = get_matrix_order(matrix);

	if (__debug > 0)
	{
		std::cerr << "Matrix Symbol:     " << matrix     << std::endl
		          << "Matrix Relation:   " << matrix_rel << std::endl
		          << "Matrix Order:      " << matrix_ord << std::endl;
	}

	auto phase_1 = get_phase1_query(matrix_rel, matrix_ord);
	if (__debug > 1)
	{
		std::cerr << "Evaluating:        " << phase_1 << std::endl;
	}
	auto output_1 = evaluate_query(phase_1, "-fcsv");
	auto attr = join_lines(output_1);

	if (__debug > 0)
	{
		std::cerr << "Matrix Attributes: " << attr       << std::endl;
	}

	auto phase_2 = get_phase2_query(query, match, attr);
	if (__debug > 1)
	{
		std::cerr << "Evaluating:        " << phase_2 << std::endl;
	}
	std::cout << evaluate_query(phase_2, opt);

	return 0;
}
