#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <exception> 
#include <iostream>

const std::string border = "2147483648"; 

template <class T>
std::string to_str(T&& val)
{
	std::stringstream str;
	str << val;
	return str.str();
}


struct CountArgumentError: public std::exception {};
struct WrongArgumentError: public std::exception {};
struct ParenthesisError: public std::exception {};
struct OverflowError: public std::exception {};
struct TooManyArgsError: public std::exception {};


template <class ... Args>
std::string format(const std::string& str, Args&& ... args)
{
	std::vector<std::string> args_vect = {to_str(std::forward<Args>(args)) ...};
	std::string result, buf;
	int max = 0;
	int str_len = str.size();
	int arg_len = args_vect.size();
	bool open_paren = false;
	bool closed_paren = true;
	char c;

	for (int i = 0; i < str_len; i++)
	{
		c = str[i];
		if (closed_paren)
		{
			if (c == '{')
			{
				open_paren = true;
				closed_paren = false;
			}
			else if (c == '}')
			{
				throw ParenthesisError();
			}
			else
			{
				result += str[i];
			}
		}
		else if(open_paren)
		{
			if (std::isdigit(c))
			{
				buf += c;
			}
			else if (c == '}')
			{
				if (buf.empty())
				{
					throw CountArgumentError();
				}
				else if ((buf.size() > border.size()) || ((buf.size() == border.size()) && (buf >= border))){
					buf.clear();
					throw OverflowError();
				}
				else if (std::stoi(buf) >= arg_len || std::stoi(buf) < 0)
				{
					buf.clear();
					throw CountArgumentError();
				}
				else
				{
					open_paren = false;
					closed_paren = true;
					int number = std::stoi(buf);
					if (number > max) max = number;
					result += args_vect[number];
					buf.clear();
				}
			}
			else
			{
				buf.clear();
				throw WrongArgumentError();
			}
		}
	}
	if (open_paren)
	{
		throw ParenthesisError();
	}
	if ((arg_len - 1) > max)
	{
		throw TooManyArgsError();
	}
	return result;
}
