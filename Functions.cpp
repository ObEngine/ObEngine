#include "Functions.hpp"

namespace fn
{
	namespace Coord
	{
		int baseWidth = 1920;
		int baseHeight = 1080;
		int width = sf::VideoMode::getDesktopMode().width;
		int height = sf::VideoMode::getDesktopMode().height;
	}
}

//Functions::Coord
int fn::Coord::adaptCamX(int camX, int sizeX) {
	const int S_WIDTH = 1920;
	camX -= S_WIDTH / 2;
	if (camX < 0)
		camX = 0;
	if (camX + S_WIDTH > sizeX)
		camX = sizeX - S_WIDTH;
	camX += S_WIDTH / 2;
	return camX;
}
int fn::Coord::adaptCamY(int camY, int sizeY) {
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
std::vector<std::string> fn::File::listDirInDir(std::string path) {
	DIR *dir;
	struct dirent *ent;
	std::vector<std::string> fileList;
	dir = opendir(path.c_str());
	if (dir != NULL)
	{
		while ((ent = readdir(dir)) != NULL)
		{
			if (ent->d_type == DT_DIR)
			{
				std::string cName = std::string(ent->d_name);
				if ((cName != ".") && (cName != ".."))
					fileList.push_back(cName);
			}
		}
		closedir(dir);
	}
	else
	{
		std::cout << "Cannot open directory " << path << std::endl;
		exit(EXIT_FAILURE);
	}
	return fileList;
}
std::vector<std::string> fn::File::listFileInDir(std::string path) {
	DIR *dir;
	struct dirent *ent;
	std::vector<std::string> fileList;
	dir = opendir(path.c_str());
	if (dir != NULL)
	{
		while ((ent = readdir(dir)) != NULL)
		{
			if (ent->d_type == DT_REG)
			{
				std::string cName = std::string(ent->d_name);
				if ((cName != ".") && (cName != ".."))
					fileList.push_back(cName);
			}
		}
		closedir(dir);
	}
	else
	{
		std::cout << "Cannot open directory" << path << std::endl;
		exit(EXIT_FAILURE);
	}
	return fileList;
}

std::random_device rd;     // only used once to initialise (seed) engine
std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)

//Functions::Math
int fn::Math::randint(int min, int max) {
	
	std::uniform_int_distribution<int> uni(min, max); // guaranteed unbiased
	return uni(rng);
}
double fn::Math::randfloat() {
	std::uniform_real_distribution<> dis(0, 1);
	return dis(rng);
}
bool fn::Math::isDoubleInt(double& value)
{
	return (std::trunc(value) == value);
}

//Functions::String
void fn::String::removeCharFromString(std::string &str, std::string charToRemove) {
	str.erase(remove(str.begin(), str.end(), charToRemove.c_str()[0]), str.end());
}
std::vector<std::string> fn::String::split(const std::string &str, const std::string &delimiters) {
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
std::vector<std::string> fn::String::multiSplit(std::string str, std::vector<std::string> seps) {
	for (unsigned int i = 0; i < seps.size(); i++)
		fn::String::replaceStringInPlace(str, seps[i], "~" + seps[i] + "~");
	return fn::String::split(str, "~");
}
std::vector<std::string> fn::String::multiSplit(std::string str, std::vector<std::string> sepsBef, std::vector<std::string> sepsAft) {
	for (unsigned int i = 0; i < sepsBef.size(); i++)
		fn::String::replaceStringInPlace(str, sepsBef[i], sepsBef[i] + "~");
	for (unsigned int i = 0; i < sepsAft.size(); i++)
		fn::String::replaceStringInPlace(str, sepsAft[i], "~" + sepsAft[i]);
	return fn::String::split(str, "~");
}
std::vector<std::string> fn::String::multiSplit(std::string str, std::vector<std::string> seps, std::vector<std::string> sepsBef, std::vector<std::string> sepsAft) {
	for (unsigned int i = 0; i < sepsBef.size(); i++)
		fn::String::replaceStringInPlace(str, sepsBef[i], sepsBef[i] + "~");
	for (unsigned int i = 0; i < sepsAft.size(); i++)
		fn::String::replaceStringInPlace(str, sepsAft[i], "~" + sepsAft[i]);
	for (unsigned int i = 0; i < seps.size(); i++)
		fn::String::replaceStringInPlace(str, seps[i], "~" + seps[i] + "~");
	return fn::String::split(str, "");
}
int fn::String::occurencesInString(std::string str, std::string occur) {
	int occurrences = 0;
	std::string::size_type start = 0;
	while ((start = str.find(occur, start)) != std::string::npos) {
		++occurrences;
		start += occur.length(); // see the note
	}
	return occurrences;
}
bool fn::String::isStringAlpha(std::string str) {
	if (str.size() > 0)
		return std::all_of(str.begin(), str.end(), ::isalpha);
	else
		return false;
}
bool fn::String::isStringAlphaNumeric(std::string str) {
	if (str.size() > 0)
		return std::all_of(str.begin(), str.end(), ::isalnum);
	else
		return false;
}
bool fn::String::isStringInt(std::string str) {
	if (str.size() > 0)
	{
		if (str.substr(0, 1) == "-")
			str = str.substr(1);
		return std::all_of(str.begin(), str.end(), ::isdigit);
	}
	else
		return false;
}
bool fn::String::isStringFloat(std::string str) {
	bool isFloat = false;
	if (str.size() > 0)
	{
		if (str.substr(0, 1) == "-")
			str = str.substr(1);
		if (fn::String::occurencesInString(str, ".") == 1)
		{
			isFloat = true;
			fn::String::removeCharFromString(str, ".");
		}
		return (std::all_of(str.begin(), str.end(), ::isdigit) && isFloat);
	}
	else
		return false;
}
bool fn::String::isStringNumeric(std::string str)
{
	return (fn::String::isStringFloat(str) || fn::String::isStringInt(str));
}

void fn::String::replaceStringInPlace(std::string& subject, const std::string& search, const std::string& replace) {
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
}
std::string fn::String::replaceString(std::string subject, const std::string& search, const std::string &replace) {
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return subject;
}
bool fn::String::isBetween(const std::string& string, const std::string& bet) {
	return (string.substr(0, bet.size()) == bet && string.substr(string.size() - bet.size(), bet.size()) == bet);
}
std::string fn::String::extract(const std::string& base, int start, int end) {
	return base.substr(start, base.size() - start - end);
}
std::vector<std::string> fn::String::extractBetween(std::string &str, char delimiter1, char delimiter2)
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
		fn::String::replaceStringInPlace(str, strings[i], "");
	return strings;
}
std::string fn::String::getRandomKey(std::string set, int len)
{
	std::string r;
	for (int i = 0; i < len; i++) r.push_back(set.at(size_t(fn::Math::randint(0, 100000) % set.size())));
	return r;
}

//Functions::Vector
std::string fn::Vector::join(std::vector<std::string>& vector, std::string sep, int start, int end)
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
void fn::Vector::joinBetween(std::vector<std::string>* vector, std::string joinValue, std::string sep) {
	std::string stack = "";
	bool stacking = false;
	std::vector<int> toErase;
	for (int i = 0; i < vector->size(); i++)
	{
		if (vector->at(i) == joinValue)
		{
			if (stacking)
			{
				stack += vector->at(i);
				vector->at(i) = stack;
				stack = "";
			}
			stacking = !stacking;
		}
		if (stacking)
		{
			stack += vector->at(i) + sep;
			toErase.push_back(i);
		}
	}
	for (int i = toErase.size() - 1; i >= 0; i--)
		vector->erase(vector->begin() + toErase[i]);
}
void fn::Vector::mergeNeighboors(std::vector<std::string>* vector, std::string n1, std::string n2, std::string sep, bool strict)
{
	if (vector->size() > 0)
	{
		std::vector<int> toErase;
		for (int i = 0; i < vector->size() - 1; i++)
		{
			if (strict)
			{
				if (vector->at(i) == n1 && vector->at(i + 1) == n2)
				{
					vector->at(i) = vector->at(i) + sep + vector->at(i + 1);
					toErase.push_back(i + 1);
				}
			}
			else
			{
				if ((vector->at(i) == n1 && vector->at(i + 1) == n2) || (vector->at(i) == n2 && vector->at(i + 1) == n1))
				{
					vector->at(i) = vector->at(i) + sep + vector->at(i + 1);
					toErase.push_back(i + 1);
				}
			}
		}
		for (int i = toErase.size() - 1; i >= 0; i--)
			vector->erase(vector->begin() + toErase[i]);
	}
}