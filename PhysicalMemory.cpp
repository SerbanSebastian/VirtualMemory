#include "PhysicalMemory.hpp"

namespace memo {

	PhysicalMemory::PhysicalMemory() {
	}

	PhysicalMemory::PhysicalMemory(size_t total_frames) {
		if (total_frames > MAX_NUMBER_OF_FRAMES) {
			std::cerr << "[ERROR] Physical Memory size exceeds maximum number of frames\n";
			return;
		}

		this->frames = std::vector<Frame>();
		this->free_frames = std::queue<size_t>();
		for (size_t i = 0; i < total_frames; i++) {
			Frame frame = Frame{ i, false, std::vector<char>(PAGE_SIZE, 0)};
			this->frames.push_back(frame);
			this->free_frames.push(i);
		}

		this->frame_number = total_frames;
	}

	size_t PhysicalMemory::allocate_frame() {
		if (free_frames.empty()) {
			std::cerr << "[ERROR] No free frames available\n";
			return MAX_NUMBER_OF_FRAMES;
		}

		size_t frame_number = free_frames.front();
		free_frames.pop();
		frames[frame_number].is_used = true;
		std::fill(frames[frame_number].data.begin(), frames[frame_number].data.end(), 0);
		return frame_number;
	}
	
	void PhysicalMemory::free_frame(size_t frame_number) {
		if (frame_number >= get_total_frames()) {
			std::cerr << "[ERROR] Frame number out of bounds\n";
			return;
		}
		if (!frames[frame_number].is_used) {
			return;
		}

		frames[frame_number].is_used = false;
		free_frames.push(frame_number);
		return;
	}


	std::vector<char>& PhysicalMemory::get_frame_data(size_t frame_number) {
		return frames[frame_number].data;
	}

	bool PhysicalMemory::is_frame_free(size_t frame_number) const {
		if (frame_number >= get_total_frames()) {
			std::cerr << "[ERROR] Frame number out of bounds\n";
			return false;
		}
		return !frames[frame_number].is_used;
	}

	size_t PhysicalMemory::get_total_frames() const{
		return frame_number;
	}

	size_t PhysicalMemory::get_free_frame_count() const {
		return free_frames.size();
	}

	void PhysicalMemory::set_frame_data(size_t frame_number, const std::vector<char>& data) {
		if (frame_number >= get_total_frames()) {
			std::cerr << "[ERROR] Frame number out of bounds.\n";
			return;
		}

		if(data.size() != PAGE_SIZE) {
			std::cerr << "[ERROR] Data size does not match frame size.\n";
			return;
		}

		frames[frame_number].data = data;
	}

	void PhysicalMemory::modify_frame_data(size_t address, char value) {
		if (frame_number >= get_total_frames()) {
			std::cerr << "[ERROR] Frame number out of bounds.\n";
			return;
		}
		int offset = 0,  frame_number = 0;
		offset = address & 0xFFF;
		frame_number = address >> 12;

		if (offset >= PAGE_SIZE) {
			std::cerr << "[ERROR] Offset exceeds page size.\n";
			return;
		}

		if(!frames[frame_number].is_used) {
			std::cerr << "[ERROR] Attempt to modify an unused frame.\n";
			return;
		}
	}
}