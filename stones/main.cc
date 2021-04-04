#include <random>
#include <iostream>
#include <chrono>
#include <sstream>

	int read_int (const char *question)
	{
		int result;
		std::string inp;
		re: std::cout << question;
		std::getline (std::cin, inp);
		{
			std::stringstream inps {inp};
			inps >> result;
			if (inps.fail()){
				if (std::cin.fail()){
					std::cerr <<"Ошибка ввода-вывода!" << std::endl;
					exit(1);
				}
				std::cout << "Некорректный ввод!" << std::endl;
						goto re;
			}
						else if (not inps.eof()){
							std::cout << "Непонятный мусор в конце ввода!" << std::endl;
							goto re;
						}

						}
		return result;
	}

	int read_int_in_range(const char * question, int min, int max) // @suppress("No return")
		{
			int result;
			for(;;) {
				result = read_int(question);
				if (result>=min and result<=max)
					return result;
				std::cout << "Число должно быть в интервале от " << min << " до " << max << std::endl;
			}
		}


int main(){
	using clk = std::chrono::system_clock;
	std::random_device rd;
	std::minstd_rand rnd{unsigned(clk::now().time_since_epoch().count())};
	std::uniform_int_distribution<> d {15,25};//кол-во камней всего
	std::uniform_int_distribution <> d1{1,3};//кол-во камней можно взять за один ход
	int lvl;
	do{
		unsigned stone_count = d(rnd);//кол-во камней
		lvl = read_int_in_range("Выберите уровень сложности:\n"
										"1.Легкий\n"
										"2.Средний\n"
										"3.Сложный\n"
										"0.Выход\n", 0, 3);
					if (lvl==0){//выход
						return 0;
					}else
		std::cout << "Всего " << stone_count << " камней" << std::endl;
		while(lvl != 4){
		std::cout << "Вы можете взять 1, 2 или 3 камня." << std::endl;
		std::cout << std::endl;
		std::cout << "Сколько камней Вы возьмёте?" << std::endl;
		int x = read_int_in_range("", 1, std::min (3U, stone_count));
		stone_count = stone_count - x;//уменьшить кол-во камней
		if (stone_count < 26){
			std::cout << "Всего " << stone_count << " камней" << std::endl;}
			if (stone_count == 0 || stone_count > 25){//если вы берете последний камень, то вы проиграли
						std::cout << "Вы проиграли\n" << std::endl;
						break;
					} else {
						unsigned count_computer;
						if (stone_count < 5 && lvl != 1){
							switch(stone_count){
								case 4: count_computer = 3; break;
								case 3: count_computer = 2; break;
								case 2: count_computer = 1; break;
							}
						} else {
							if(lvl == 1){
								count_computer = d1(rnd);
							} else if (lvl == 2){
								switch(x){
									case 1: count_computer = 3; break;
									case 2: count_computer = 2; break;
									case 3: count_computer = 1; break;
								}
							} else {
								for(unsigned i = 25; i > 0; i -= 4){
									if (i == stone_count){
										count_computer = d1(rnd);
										break;
									}
									if (stone_count > i){
										count_computer = stone_count - i;
										break;
									}
								}
							}
						}
						stone_count = stone_count - count_computer;
						std::cout << "Компьютер взял " << count_computer << " камня" << std::endl;
						if (stone_count == 0 || stone_count > 25){//если компьютер берет последний камень то вы выиграли
							std::cout << "Вы выиграли\n" << std::endl;
							break;
						}
						std::cout << "Всего " << stone_count << " камней" << std::endl;
					}
			}
		}while(true);
	return 0;
}
