#include "Plusterm.h"
#include <cctype>
#include <iosfwd>
#include <iostream>
#include <locale.h>
#include <sstream>
#include <string>
#include <Windows.h>

void Plusterm::start()
{
	this->plusterm_main();
}

void Plusterm::plusterm_main()
{
	system("cls");

	setlocale(LC_ALL, "ru-RU");
	system("chcp 1251 > nul 2>&1");

	this->set_static_color("output_default");

	system("title PlusTerm");

	system("cls");

	this->print_title("title");

	for (int i{ 0 }; true; i++)
	{
		std::string user_input{}, user_input_command{}, user_input_text{};

		std::cout << std::endl;

		this->set_static_color("input_default");

		std::cout << "PT |>>> ";
		std::getline(std::cin, user_input);

		//
		std::stringstream ss(user_input);
		ss >> user_input_command;

		std::getline(ss, user_input_text);

		size_t strBegin = user_input_text.find_first_not_of(' ');
		size_t strEnd = user_input_text.find_last_not_of(' ');
		user_input_text.erase(strEnd + 1, user_input_text.size() - strEnd);
		user_input_text.erase(0, strBegin);
		//

		for (int i{ 0 }; i < user_input_command.length(); i++)
		{
			user_input_command[i] = tolower(user_input_command[i]);
		}

		this->run(user_input_command, user_input_text);

		if (is_exit)
		{
			break;
		}
	}

	system("cls");
	system("exit");
}

void Plusterm::run(std::string _command, std::string _text)
{
	this->set_static_color("output_default");

	if (_command == "" || _command == "_plusterm?empty_")
	{
		//nothing
	}
	else if (_command == "_plusterm?undefined_")
	{
		this->info("error", _command, _command);
	}
	else if (_command == "exit" || _command == "quit")
	{
		system("cls");
		system("exit");
		is_exit = true;
	}
	else if (_command == "help" || _command == "?")
	{
		if (_text != "")
		{
			this->info("warning", "������� help �� ��������� ����������", _command);
		}
		std::cout << "������ ������:" << std::endl << std::endl;
		std::cout << "������� [�����] (���������) ||| ��������" << std::endl << "��������� �����: ��������� ����� �������� ; ��� ���� ��������� ����� ��������" << std::endl << "������: ������ �������� ; ������ ������ ��������" << std::endl << std::endl;
		this->help();
	}
	else if (_command == "clear" || _command == "cls")
	{
		system("cls");
		this->set_static_color("output_default");
		this->print_title();
	}
	else if (_command == "print" || _command == "say")
	{
		if (_text != "")
		{
			std::cout << _text << std::endl;
		}
		else
		{
			this->info("error", "�� �� ����� �� ������ ������ ��� ������", _command);
		}
	}
	else if (_command == "get_date" || _command == "date")
	{
		if (_text != "")
		{
			this->info("warning", "������� get_date �� ��������� ����������", _command);
		}
		system("echo %date%");
	}
	else if (_command == "get_time" || _command == "time")
	{
		if (_text != "")
		{
			this->info("warning", "������� get_time �� ��������� ����������", _command);
		}
		system("echo %time%");
	}
	else if (_command == "square_root" || _command == "sqrt")
	{
		/*
		char pStr[]{ 0 };
		for (int i{ 0 }; i < _command.length(); i++)
		{
			pStr[i] = _command[i];
		}
		for (int i = 0; i < strlen(pStr); i++)
		{
			if (!isdigit(pStr[i]))
			{
				this->info("error", "��, ��� �� ����� - �� �����", _command);
			}
			else if (i == _command.length() - 1 && isdigit(pStr[i]))
			{
				std::cout << "���������� ������ �� " << _text << ": " << sqrt(std::stoi(_text)) << std::endl;
			}
		}
		*/

		if (_text != "")
		{
			std::cout << "���������� ������ �� " << _text << ": " << sqrt(std::stoi(_text)) << std::endl;
		}
		else
		{
			this->info("error", "�� �� ����� �����", _command);
		}
	}
	else if (_command == "version" || _command == "ver")
	{
		if (_text != "")
		{
			this->info("warning", "������� plusterm_version �� ��������� ����������", _command);
		}
		print_title("version");
	}
	else if (_command == "cmd")
	{
		if (_text != "")
		{
			this->info("info", "���������� �������� � CMD...", _command);
			std::cout << std::endl;

			system(_text.c_str());

			std::cout << std::endl;
			this->info("info", "������� CMD ���������!", _command);
		}
		else
		{
			std::cout << "������ ����� ������� ����� 'CMD.exe'! ����� ����� ������� � PlusTerm, ������� ������� 'exit'." << std::endl;
			std::cout << "��������! CMD - ��� �� PlusTerm, � CMD �� ��������� �������� PlusTerm." << std::endl << std::endl;

			system("cmd");
		}
	}
	/*else if (_command == "plusterm" || _command == "pt")
	{
		if (_text.find("/*") != std::string::npos)
		{
			system("iarb_plusterm.exe");
		}
		else
		{
			this->info("warning", "������, ��� ��������� PlusTerm ��� �������. ���� �� �� ����� ������ ��������� ��� ���� ��������� PlusTerm ������ �����, ��������� �������� � ���������� /*", _command);
		}
	}*/
	else if (_command == "about")
	{
		this->set_static_color("title_name");
		std::cout << "PlusTerm";
		this->set_static_color("output_default");
		std::cout << std::endl << "����� PlusTerm`a - yarb00." << std::endl << "Discord: @yarb00" << std::endl << "Telegram: @yarb000" << std::endl;
	}
	else if (_command == "web")
	{
		if (_text != "")
		{
			std::string com_{ "start https://\"" + _text + "\"" };
			system(com_.c_str());
		}
		else
		{
			system("start https://\"github.com/yarb00\"");
		}
	}
	else
	{
		this->info("error", "����������� �������");
		std::cout << "����� ������� ������� �� ���������, ��������� �������� \"help\"." << std::endl;
	}
}

void Plusterm::help()
{
	std::cout << "exit ||| ����� �� PlusTerm" << std::endl << "��������� �����: ���" << std::endl << "������: exit" << std::endl << std::endl;
	std::cout << "help ||| ������� ������ ������ (���� ������)" << std::endl << "��������� �����: ���" << std::endl << "������: help" << std::endl << std::endl;
	std::cout << "clear ||| �������� �����" << std::endl << "��������� �����: ���" << std::endl << "������: clear" << std::endl << std::endl;
	std::cout << "print (�����) ||| ������� ��������� �� �����" << std::endl << "��������� �����: ���" << std::endl << "������: print ���� �����!" << std::endl << std::endl;
	std::cout << "date ||| ������� ������� ���� �� �����" << std::endl << "��������� �����: ���" << std::endl << "������: date" << std::endl << std::endl;
	std::cout << "time ||| ������� ������� ����� �� �����" << std::endl << "��������� �����: ���" << std::endl << "������: time" << std::endl << std::endl;
	std::cout << "sqrt (�����) ||| ������� ���������� ������ �� ����� �� �����" << std::endl << "��������� �����: ���" << std::endl << "������: sqrt 9" << std::endl << std::endl;
	std::cout << "ver ||| ������� ������ PlusTerm �� �����" << std::endl << "��������� �����: ���" << std::endl << "������: pt_ver" << std::endl << std::endl;
	std::cout << "cmd (������� CMD) ||| ��������� ������� CMD �� ���������, ���, ��� ���������� ��������� ����� CMD (������������ ��������� ������)" << std::endl << "��������� �����: ���" << std::endl << "������: cmd ; cmd echo Hello, world!" << std::endl << std::endl;
	//std::cout << "pt [�����] ||| ��������� ��������� PlusTerm" << std::endl << "��������� �����: /* - ����������� ������" << std::endl << "������: pt ; pt /*" << std::endl << std::endl;
	std::cout << "about ||| � Plusterm � ��� ������" << std::endl << "��������� �����: ���" << std::endl << "������: about" << std::endl << std::endl;
	std::cout << "web (����� ����� ��� ��������� https) ||| ��������� ���� � �������� �� ���������" << std::endl << "��������� �����: ���" << std::endl << "������: web google.com" << std::endl << std::endl;
}

void Plusterm::print_title(std::string _mode)
{
	if (_mode == "title")
	{
		set_static_color("title_name");
		std::cout << "PlusTerm";
		set_static_color("output_default");
		std::cout << std::endl << "�� yarb00\t(���������: \"about\")" << std::endl << std::endl << "������ { |" << this->plusterm_version << "| }" << std::endl << std::endl << "-----" << std::endl;
	}
	else if (_mode == "version")
	{
		std::cout << "����� ���������� { | " << this->plusterm_version_channel << " | }\t|||\t������ { | " << this->plusterm_version << " | }" << std::endl;
	}
}

void Plusterm::info(std::string _info_level, std::string _info_text, std::string _input_command)
{
	if (_info_level == "error")
	{
		this->set_static_color("output_error");
		std::cout << "������ [" << _input_command << "   /   " << _info_text << "] !" << std::endl;
	}
	else if (_info_level == "warning")
	{
		this->set_static_color("output_warning");
		std::cout << "�������������� [" << _input_command << "   /   " << _info_text << "] !" << std::endl;
	}
	else if (_info_level == "info")
	{
		this->set_static_color("light_blue");
		std::cout << "��������� [" << _input_command << "   /   " << _info_text << "] !" << std::endl;
	}

	set_static_color();
}

//in developing, doesn't work now. use set_static_color() instead
template<int txt = 7, int bg = 0>
std::ostream& set_color(std::ostream& _text)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | txt));
	return _text;
}
//

void Plusterm::set_static_color(std::string _color_mode)
{
	int _text_color{}, _background_color{ 1 };

	if (_color_mode == "input_default")
	{
		_text_color = 7;
	}
	else if (_color_mode == "title_name")
	{
		_text_color = 1;
		_background_color = 7;
	}
	else if (_color_mode == "output_default")
	{
		_text_color = 15;
	}
	else if (_color_mode == "output_error")
	{
		_text_color = 4;
	}
	else if (_color_mode == "output_warning")
	{
		_text_color = 6;
	}
	else if ("light_blue")
	{
		_text_color = 11;
	}

	//
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((_background_color << 4) | _text_color));
	//
}