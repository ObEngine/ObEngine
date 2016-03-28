#include "MeltingSaga.hpp"

int main(int argc, char argv[])
{
	//Sauvegarde du log dans log.txt
	std::ofstream out("log.txt");
	std::streambuf *coutbuf = std::cout.rdbuf();
	std::cout.rdbuf(out.rdbuf());

	//startGame();
	editMap("poly2.map.msd");

	return 0;
}