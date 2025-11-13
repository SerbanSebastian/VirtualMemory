#ifndef __PHYSICAL_MEMORY_HPP__
#define __PHYSICAL_MEMORY_HPP__


#include "Constants.hpp"

namespace memo {
	struct Frame {
		size_t number;
		bool is_used;
		std::vector<char> data;
	};

	class PhysicalMemory {
	public:
		PhysicalMemory();
		PhysicalMemory(size_t total_frames);
		size_t allocate_frame();
		void free_frame(size_t frame_number);
		std::vector<char>& get_frame_data(size_t frame_number);
		bool is_frame_free(size_t frame_number) const;
		size_t get_total_frames() const;
		size_t get_free_frame_count() const;
		void set_frame_data(size_t frame_number, const std::vector<char>& data);
		void modify_frame_data(size_t address, char value);
	private:
		size_t frame_number;
		std::queue<size_t> free_frames;
		std::vector<Frame> frames;
	};
}

#endif