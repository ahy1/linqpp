
#include "linqpp.hpp"

#include <vector>
#include <iostream>

int main()
{
	std::vector<int> iv {1, 2, 3, 4, 5};

	std::cout << "Original sequence:\n";

	auto ivseq = linqpp::make_seq(iv);

	while (!ivseq.at_end()) {
		std::cout << ivseq.get() << '\n';
	}

	std::cout << "Translate:\n";

	auto ivseq2 = linqpp::make_seq(iv).translate(std::function<int(int)>([](auto r) {return r*2;}));

	while (!ivseq2.at_end()) {
		std::cout << ivseq2.get() << '\n';
	}

	std::cout << "Translate with different type:\n";

	auto ivseq3 = linqpp::make_seq(iv).translate([](auto r) {return r*2.1f;});

	while (!ivseq3.at_end()) {
		std::cout << ivseq3.get() << '\n';
	}

	std::cout << "Filter:\n";

	auto ivseq4 = linqpp::make_seq(iv).filter([](auto r) {return r>2;});

	while (!ivseq4.at_end()) {
		std::cout << ivseq4.get() << '\n';
	}

	std::cout << "Skip:\n";

	auto ivseq5 = linqpp::make_seq(iv).skip(1);

	while (!ivseq5.at_end()) {
		std::cout << ivseq5.get() << '\n';
	}

	return 0;
}
