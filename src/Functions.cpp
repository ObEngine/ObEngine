//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "Functions.hpp"

namespace obe
{
	namespace Functions
	{
		int Coord::baseWidth = 1920;
		int Coord::baseHeight = 1080;
		int Coord::width = sf::VideoMode::getDesktopMode().width;
		int Coord::height = sf::VideoMode::getDesktopMode().height;
		double Math::pi = 3.14159265359;

		//Functions::Coord
		int Coord::adaptCamX(int camX, int sizeX) {
			const int S_WIDTH = 1920;
			camX -= S_WIDTH / 2;
			if (camX < 0)
				camX = 0;
			if (camX + S_WIDTH > sizeX)
				camX = sizeX - S_WIDTH;
			camX += S_WIDTH / 2;
			return camX;
		}
		int Coord::adaptCamY(int camY, int sizeY) {
			const int S_HEIGHT = 1080;
			camY -= S_HEIGHT / 2;
			if (camY < 0)
				camY = 0;
			if (camY + S_HEIGHT > sizeY)
				camY = sizeY - S_HEIGHT;
			camY += S_HEIGHT / 2;
			return camY;
		}

		//Functions::File
		std::vector<std::string> File::listDirInDir(std::string path) {
			tinydir_dir dir;
			tinydir_open(&dir, path.c_str());

			std::vector<std::string> fileList;
			while (dir.has_next)
			{
				tinydir_file file;
				tinydir_readfile(&dir, &file);
				if (file.is_dir)
				{
					if (std::string(file.name) != "." && std::string(file.name) != "..") { fileList.push_back(std::string(file.name)); }
				}
				tinydir_next(&dir);
			}
			tinydir_close(&dir);
			return fileList;
		}
		std::vector<std::string> File::listFileInDir(std::string path) {
			tinydir_dir dir;
			tinydir_open(&dir, path.c_str());

			std::vector<std::string> fileList;
			while (dir.has_next)
			{
				tinydir_file file;
				tinydir_readfile(&dir, &file);
				if (!file.is_dir) { fileList.push_back(std::string(file.name)); }
				tinydir_next(&dir);
			}
			tinydir_close(&dir);
			return fileList;
		}
		bool File::fileExists(const std::string& path)
		{
			struct stat buffer;
			bool fileFound = (stat(path.c_str(), &buffer) == 0);
			return fileFound;
		}
		void File::copy(std::string source, std::string target)
		{
			std::ifstream src(source, std::ios::binary);
			std::ofstream dst(target, std::ios::binary);

			dst << src.rdbuf();
		}

		std::string File::separator()
		{
			#ifdef _WIN32
				return "\\";
			#else
				return "/";
			#endif
		}

		std::random_device rd;     // only used once to initialise (seed) engine
		std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)

								   //Functions::Math
		int Math::randint(int min, int max) {

			std::uniform_int_distribution<int> uni(min, max); // guaranteed unbiased
			return uni(rng);
		}
		double Math::randfloat() {
			std::uniform_real_distribution<> dis(0, 1);
			return dis(rng);
		}
		bool Math::isDoubleInt(double& value)
		{
			return (std::trunc(value) == value);
		}

		//Functions::Run
		Run::Parser::Parser(char** start, int size)
		{
			this->start = start;
			this->size = size;
		}
		bool Run::Parser::argumentExists(std::string arg)
		{
			return std::find(start, start + size, arg) != (start + size);
		}
		std::string Run::Parser::getArgumentValue(std::string arg)
		{
			char ** itr = std::find(start, start + size, arg);
			if (itr != (start + size) && ++itr != (start + size))
			{
				return std::string(*itr);
			}
			return "";
		}

		//Functions::String
		void String::removeCharFromString(std::string &str, std::string charToRemove) {
			str.erase(remove(str.begin(), str.end(), charToRemove.c_str()[0]), str.end());
		}
		std::vector<std::string> String::split(const std::string &str, const std::string &delimiters) {
			std::vector<std::string> tokens;
			std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
			std::string::size_type pos = str.find_first_of(delimiters, lastPos);
			while (std::string::npos != pos || std::string::npos != lastPos) {
				tokens.push_back(str.substr(lastPos, pos - lastPos));
				lastPos = str.find_first_not_of(delimiters, pos);
				pos = str.find_first_of(delimiters, lastPos);
			}
			return tokens;
		}
		std::vector<std::string> String::multiSplit(std::string str, std::vector<std::string> seps) {
			for (unsigned int i = 0; i < seps.size(); i++)
				String::replaceStringInPlace(str, seps[i], "~" + seps[i] + "~");
			return String::split(str, "~");
		}
		std::vector<std::string> String::multiSplit(std::string str, std::vector<std::string> sepsBef, std::vector<std::string> sepsAft) {
			for (unsigned int i = 0; i < sepsBef.size(); i++)
				String::replaceStringInPlace(str, sepsBef[i], sepsBef[i] + "~");
			for (unsigned int i = 0; i < sepsAft.size(); i++)
				String::replaceStringInPlace(str, sepsAft[i], "~" + sepsAft[i]);
			return String::split(str, "~");
		}
		std::vector<std::string> String::multiSplit(std::string str, std::vector<std::string> seps, std::vector<std::string> sepsBef, std::vector<std::string> sepsAft) {
			for (unsigned int i = 0; i < sepsBef.size(); i++)
				String::replaceStringInPlace(str, sepsBef[i], sepsBef[i] + "~");
			for (unsigned int i = 0; i < sepsAft.size(); i++)
				String::replaceStringInPlace(str, sepsAft[i], "~" + sepsAft[i]);
			for (unsigned int i = 0; i < seps.size(); i++)
				String::replaceStringInPlace(str, seps[i], "~" + seps[i] + "~");
			return String::split(str, "");
		}
		int String::occurencesInString(std::string str, std::string occur) {
			int occurrences = 0;
			std::string::size_type start = 0;
			while ((start = str.find(occur, start)) != std::string::npos) {
				++occurrences;
				start += occur.length(); // see the note
			}
			return occurrences;
		}
		bool String::isStringAlpha(std::string str) {
			if (str.size() > 0)
				return std::all_of(str.begin(), str.end(), ::isalpha);
			else
				return false;
		}
		bool String::isStringAlphaNumeric(std::string str) {
			if (str.size() > 0)
				return std::all_of(str.begin(), str.end(), ::isalnum);
			else
				return false;
		}
		bool String::isStringInt(std::string str) {
			if (str.size() > 0)
			{
				if (str.substr(0, 1) == "-")
					str = str.substr(1);
				return std::all_of(str.begin(), str.end(), ::isdigit);
			}
			else
				return false;
		}
		bool String::isStringFloat(std::string str) {
			bool isFloat = false;
			if (str.size() > 0)
			{
				if (str.substr(0, 1) == "-")
					str = str.substr(1);
				if (String::occurencesInString(str, ".") == 1)
				{
					isFloat = true;
					String::removeCharFromString(str, ".");
				}
				return (std::all_of(str.begin(), str.end(), ::isdigit) && isFloat);
			}
			else
				return false;
		}
		bool String::isStringNumeric(std::string str)
		{
			return (String::isStringFloat(str) || String::isStringInt(str));
		}

		void String::replaceStringInPlace(std::string& subject, const std::string& search, const std::string& replace) {
			size_t pos = 0;
			while ((pos = subject.find(search, pos)) != std::string::npos) {
				subject.replace(pos, search.length(), replace);
				pos += replace.length();
			}
		}
		std::string String::replaceString(std::string subject, const std::string& search, const std::string &replace) {
			size_t pos = 0;
			while ((pos = subject.find(search, pos)) != std::string::npos) {
				subject.replace(pos, search.length(), replace);
				pos += replace.length();
			}
			return subject;
		}
		bool String::isBetween(const std::string& string, const std::string& bet) {
			return (string.substr(0, bet.size()) == bet && string.substr(string.size() - bet.size(), bet.size()) == bet);
		}
		std::string String::extract(const std::string& base, int start, int end) {
			return base.substr(start, base.size() - start - end);
		}
		std::vector<std::string> String::extractBetween(std::string &str, char delimiter1, char delimiter2)
		{
			std::vector<std::string> strings;
			int start = 0;
			int end = 0;
			bool hasFindStart = false;
			bool hasFind = false;
			for (int i = 0; i < str.size(); i++)
			{
				if (hasFindStart && str[i] == delimiter2)
				{
					hasFindStart = false;
					end = i;
					hasFind = true;
				}
				if (str[i] == delimiter1 && !hasFindStart && !hasFind)
				{
					start = i;
					hasFindStart = true;
				}
				if (hasFind)
				{
					strings.push_back(str.substr(start + 1, end - start - 1));
					hasFind = false;
				}
			}
			for (int i = 0; i < strings.size(); i++)
				String::replaceStringInPlace(str, strings[i], "");
			return strings;
		}
		std::string String::getRandomKey(std::string set, int len)
		{
			std::string r;
			for (int i = 0; i < len; i++) r.push_back(set.at(size_t(Math::randint(0, 100000) % set.size())));
			return r;
		}
		void String::regenerateEncoding(std::string& str)
		{
			std::vector<int> data(str.begin(), str.end());
			//for (int i = 0; i < data.size(); i++) { std::cout << data[i] << " "; }
			//std::cout << std::endl;
			int i = 0; char ch; str = "";
			while (i < data.size()) { if (data[i] == -61) { if (i < data.size() - 1) { data[i] = data[i + 1] + 64; } data.erase(data.begin() + i + 1); } i++; }
			for (int i = 0; i < data.size(); i++) { ch = data[i]; str += ch; }
		}
		std::string String::stringToAsciiCode(std::string & str)
		{
			std::vector<int> data(str.begin(), str.end());
			std::vector<std::string> dataStr;
			std::transform(data.begin(), data.end(), std::back_inserter(dataStr), [](const int& idata) { return std::to_string(idata); });
			return Vector::join(dataStr, ",");
		}

		std::string String::cutBeforeAsciiCode(std::string & str, int asciiCode)
		{
			std::vector<int> data(str.begin(), str.end());
			std::vector<std::string> dataStr;
			for (int i = 0; i < data.size(); i++)
			{
				if (data[i] != asciiCode)
				{
					char a = data[i];
					std::string strbuf;
					std::stringstream strbridge;
					strbridge << a;
					strbridge >> strbuf;
					//std::cout << "Trsf : " << strbuf << std::endl;
					dataStr.push_back(strbuf);
				}
				else
					break;
			}
			return Vector::join(dataStr, ",");
		}

		String::StringExtractor String::extractAllStrings(std::string string)
		{
			bool readingString = false;
			std::vector<std::string> extractedStrings;
			std::vector<std::string> otherComponents;
			std::vector<std::pair<int, int>> indexes;
			std::string currentStack = "";
			for (char chr : string) {
				std::string currentChar(1, chr);
				std::cout << currentChar << std::endl;
				if (currentChar == "\"") {
					if (currentStack.size() > 0) {
						if (readingString) {
							std::cout << "Pushing : " << currentStack << " in extractedStrings" << std::endl;
							extractedStrings.push_back(currentStack);
							indexes.push_back(std::pair<int, int>(0, extractedStrings.size() - 1));
						}
						else {
							std::cout << "Pushing : " << currentStack << " in otherComponents" << std::endl;
							otherComponents.push_back(currentStack);
							indexes.push_back(std::pair<int, int>(1, otherComponents.size() - 1));
						}
					}
					readingString = !readingString;
					currentStack.clear();
				}
				else {
					currentStack += currentChar;
				}
			}
			return std::make_tuple(extractedStrings, otherComponents, indexes);
		}
		bool String::contains(const std::string& string, const std::string& search)
		{
			return (string.find(search) != std::string::npos);
		}

		//Functions::Vector
		std::string Vector::join(std::vector<std::string>& vector, std::string sep, int start, int end)
		{
			std::string result = "";
			if (end >= vector.size())
				end = vector.size();
			if (start >= vector.size() - 1)
				start = vector.size() - 1;
			for (int i = start; i < vector.size() - end; i++)
			{
				if (i != vector.size() - 1)
					result += vector[i] + sep;
				else
					result += vector[i];
			}
			return result;
		}
		void Vector::joinBetween(std::vector<std::string>& vector, std::string joinValue, std::string sep) {
			std::string stack = "";
			bool stacking = false;
			std::vector<int> toErase;
			for (int i = 0; i < vector.size(); i++)
			{
				if (vector.at(i) == joinValue)
				{
					if (stacking)
					{
						stack += vector.at(i);
						vector.at(i) = stack;
						stack = "";
					}
					stacking = !stacking;
				}
				if (stacking)
				{
					stack += vector.at(i) + sep;
					toErase.push_back(i);
				}
			}
			for (int i = toErase.size() - 1; i >= 0; i--)
				vector.erase(vector.begin() + toErase[i]);
		}
		void Vector::mergeNeighboors(std::vector<std::string>& vector, std::string n1, std::string n2, std::string sep, bool strict)
		{
			if (vector.size() > 0)
			{
				std::vector<int> toErase;
				for (int i = 0; i < vector.size() - 1; i++)
				{
					if (strict)
					{
						if (vector.at(i) == n1 && vector.at(i + 1) == n2)
						{
							vector.at(i) = vector.at(i) + sep + vector.at(i + 1);
							toErase.push_back(i + 1);
						}
					}
					else
					{
						if ((vector.at(i) == n1 && vector.at(i + 1) == n2) || (vector.at(i) == n2 && vector.at(i + 1) == n1))
						{
							vector.at(i) = vector.at(i) + sep + vector.at(i + 1);
							toErase.push_back(i + 1);
						}
					}
				}
				for (int i = toErase.size() - 1; i >= 0; i--)
					vector.erase(vector.begin() + toErase[i]);
			}
		}

	}
}