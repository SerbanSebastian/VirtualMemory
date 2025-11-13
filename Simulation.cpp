#include "PhysicalMemory.hpp"
#include "Process.hpp"
#include "Constants.hpp"

class Simulation {
public:
	Simulation() {};
	void run() {
		std::cout << "-----Simulation initialized-----\n";

		std::ifstream fin("input.txt"); // open here
		if (!fin.is_open()) {
			std::cerr << "[ERROR] Could not open input.txt\n";
			return;
		}

		int number_of_frames;
		fin >> number_of_frames;

		if(number_of_frames <= 0) {
			std::cerr << "[ERROR] Number of frames must be greater than 0.\n";
			return;
		}

		if(number_of_frames > MAX_NUMBER_OF_FRAMES) {
			std::cerr << "[ERROR] Number of frames exceeds maximum limit of " << MAX_NUMBER_OF_FRAMES << ".\n";
			return;
		}

		p_mem = memo::PhysicalMemory(number_of_frames);
		std::string cmd;
		std::string spid;
		std::string aux;
		int pid;
		size_t number_of_pages;

		while (fin >> cmd) {
			if (cmd == "create") {

				fin >> spid;
				pid = std::stoi(spid.substr(1));
				fin >> number_of_pages;
				processes.push_back(memo::Process(number_of_pages, pid, &p_mem));

				std::cout << "Process " << pid << " created with " << number_of_pages << " pages.\n";

				fin >> aux;
			}

			if(cmd == "set") {
				//TO DO
			}

			if (cmd == "destroy") {
				//TO DO
			}
		}

		fin.close(); // explicit close (optional — destructor will also close)
	}
private:
	memo::PhysicalMemory p_mem;
	std::vector<memo::Process> processes;
};

int main(int argc, char* argv[]) {
	Simulation sim;

	sim.run();

	return 0;
}