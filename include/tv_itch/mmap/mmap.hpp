#ifndef TV_ITCH50_CPP_MMAP_HPP
#define TV_ITCH50_CPP_MMAP_HPP


#include <cstddef>
#include <cstdint>
#include <string>


#ifdef _WIN32
#include <windows.h>
#endif


namespace tv_itch::mmap {
// Note that the memory-map classes below are read-only and the data() method returns pointer to const uint8_t
#ifdef _WIN32
class MemoryMapWindows {
public:
	explicit MemoryMapWindows(const std::string& path);

	MemoryMapWindows(const MemoryMapWindows&) = delete;
	MemoryMapWindows& operator=(const MemoryMapWindows&) = delete;

	~MemoryMapWindows();

	[[nodiscard]] const std::uint8_t* data() const noexcept {
		return static_cast<const std::uint8_t*>(data_);
	}

	[[nodiscard]] std::size_t size() const noexcept { return size_; }

private:
	HANDLE file = INVALID_HANDLE_VALUE;
	HANDLE mapping = nullptr;
	void* data_ = nullptr;
	std::size_t size_ = 0;
};


#else
class MemoryMapPosix {
public:
	explicit MemoryMapPosix(const std::string& path);

	MemoryMapPosix(const MemoryMapPosix&) = delete;
	MemoryMapPosix& operator=(const MemoryMapPosix&) = delete;

	~MemoryMapPosix();

	[[nodiscard]] const std::uint8_t* data() const noexcept {
		return static_cast<const std::uint8_t*>(data_);
	}

	[[nodiscard]] std::size_t size() const noexcept { return size_; }

private:
	int fd = -1;
	void* data_ = nullptr;
	std::size_t size_ = 0;
};
#endif


#ifdef _WIN32
using MemoryMap = MemoryMapWindows;
#else
using MemoryMap = MemoryMapPosix;
#endif
}


#endif