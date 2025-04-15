
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

	std::cout << "Transform:\n";

	auto ivseq2 = linqpp::make_seq(iv).transform(std::function<int(int)>([](auto r) {return r*2;}));

	while (!ivseq2.at_end()) {
		std::cout << ivseq2.get() << '\n';
	}

	std::cout << "Transform with different type:\n";

	auto ivseq3 = linqpp::make_seq(iv).transform([](auto r) {return r*2.1f;});

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

	std::cout << "Take:\n";

	auto ivseq6 = linqpp::make_seq(iv).take(3);

	while (!ivseq6.at_end()) {
		std::cout << ivseq6.get() << '\n';
	}

	std::cout << "Vector out:\n";

	auto ivseq7 = linqpp::make_seq(iv).take(3).vector();

	for (auto v: ivseq7) {
		std::cout << v << '\n';
	}

	std::cout << "Map out:\n";

	auto ivseq8 = linqpp::make_seq(iv).take(3).map([](auto r){return r;}, [](auto r){return r*r;});

	for (auto v: ivseq8) {
		std::cout << v.first << " " << v.second << '\n';
	}

	return 0;
}
