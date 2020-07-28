#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>
#include <memory>
#include <io.h>
#include <fcntl.h>
#include <codecvt>
#include <iomanip>

#define W_WIDTH 1280
#define W_HEIGHT 720

void handle_error(bool error_test, std::wstring error_message)
{
	if (error_test)
	{
		std::wcout << std::endl << error_message << std::endl;
		std::cin.get();
		exit(1);
	}
}

std::vector<std::wstring> readFile(std::wstring path)
{
	std::wifstream file;
	file.open(path);
	handle_error(!file.is_open(), L"Error opening file.");
	std::wstring word;
	std::vector<std::wstring> word_vector;
	std::wcout << "Loading words" << '\n';
	int counter = 0;
	float n_words = 1000.f;
	while (file >> word)
	{
		word_vector.push_back(word);
		std::wcout << std::fixed << std::setprecision(2) << counter*100/n_words << "%" << std::endl;
		counter++;
		if (counter >= n_words)
			break;
	}
	return word_vector;
}

void clearSounds(std::vector<std::shared_ptr<sf::Sound>>& v) {
	v.resize(5);
}

void loadingScreen(sf::RenderWindow& window, sf::Font& font)
{
	sf::Text text("Loading words...", font, 60);
	text.setPosition(sf::Vector2<float>(W_WIDTH / 2 - text.getLocalBounds().width / 2, W_HEIGHT / 2 - text.getLocalBounds().height));
	window.clear(sf::Color::Black);
	window.draw(text);
	window.display();
}

void menuScreen(sf::RenderWindow& window, sf::Font& font)
{
	sf::Text text("Menu", font, 60);
	text.setPosition(sf::Vector2<float>(W_WIDTH / 2 - text.getLocalBounds().width / 2, W_HEIGHT / 2 - text.getLocalBounds().height));
	window.clear(sf::Color::Black);
	window.draw(text);
	window.display();
}

int main(int argc, wchar_t* argv[])
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	std::locale::global(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
	sf::RenderWindow window(sf::VideoMode(W_WIDTH, W_HEIGHT), "Typing...", sf::Style::Close);
	sf::Image icon;
	sf::Font font;
	sf::Text text;
	sf::Text input;
	sf::Text max_height_text;
	sf::SoundBuffer type;
	sf::SoundBuffer wrong;
	sf::SoundBuffer plim;
	std::vector<std::shared_ptr<sf::Sound>> sound_vector;
	std::vector<std::wstring> word_vector;
	handle_error(!type.loadFromFile("type.wav"), L"Error loading sound");
	handle_error(!wrong.loadFromFile("wrong.wav"), L"Error loading sound");
	handle_error(!plim.loadFromFile("plim.wav"), L"Error loading sound");
	handle_error(!icon.loadFromFile("icon.png"), L"Error loading image");
	handle_error(!font.loadFromFile("cour.ttf"), L"Error loading font");
	loadingScreen(window, font);
	srand(time(NULL));
	word_vector = readFile(L"words_br.txt");
	menuScreen(window, font); 
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	window.setVerticalSyncEnabled(true);
	input.setFont(font);
	text.setFont(font);
	text.setString(word_vector[rand() * rand() % (word_vector.size() - 1)]);
	text.setCharacterSize(60);
	input.setCharacterSize(60);
	max_height_text = sf::Text("bg", font, 60); // This text has the max height a text can have, so I use it to keep every text aligned
	text.setPosition(sf::Vector2<float>(W_WIDTH / 2 - text.getLocalBounds().width / 2, W_HEIGHT / 2 - max_height_text.getLocalBounds().height));
	window.clear(sf::Color::Black);
	window.draw(text);
	window.display();
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::TextEntered) // Text typed
			{
				sf::String nextChar = text.getString().substring(0, 1);
				sf::String typedChar = sf::String(event.text.unicode);
				std::shared_ptr<sf::Sound> sound(new sf::Sound);
				sound_vector.insert(sound_vector.begin(), sound);
				if (nextChar == typedChar) // Typed letter matches next letter
				{
					text.setString(text.getString().substring(1, text.getString().getSize() - 1));
					text.setPosition(sf::Vector2<float>(W_WIDTH / 2 - text.getLocalBounds().width / 2, W_HEIGHT / 2 - max_height_text.getLocalBounds().height));
					sound_vector[0]->setBuffer(type);
					sound_vector[0]->play();
				}
				else // Or it doesn't 
				{
					sound_vector[0]->setBuffer(wrong);
					sound_vector[0]->setVolume(30);
					sound_vector[0]->play();
					if (sound_vector.size() > 20)
						clearSounds(sound_vector);
				}
				if (event.key.code == 8) // Backspace was typed
					input.setString(input.getString().substring(0, input.getString().getSize() - 1));
				else if (event.key.code == 27)
					window.close();
				else // Something else was typed
					input.setString(input.getString() + event.text.unicode);
				if (text.getString().isEmpty()) // Word was fully typed
				{
					sound_vector[0]->setBuffer(plim);
					sound_vector[0]->play();
					text.setString(word_vector[(rand() * rand()) % (word_vector.size() - 1)]);
					text.setPosition(sf::Vector2<float>(W_WIDTH / 2 - text.getLocalBounds().width / 2, W_HEIGHT / 2 - max_height_text.getLocalBounds().height));
					clearSounds(sound_vector);
				}
				window.clear(sf::Color::Black);
				window.draw(text);
				window.display();
			}
		}
	}
	return 0;
}