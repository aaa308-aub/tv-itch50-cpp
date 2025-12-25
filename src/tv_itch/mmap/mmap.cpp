#include "tv_itch/mmap/mmap.hpp"


#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <string>


#ifdef _WIN32
#include <windows.h>
#else
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#endif


namespace tv_itch::mmap {
// Note that the memory-map classes below are read-only and the data() method returns pointer to const uint8_t
#ifdef _WIN32
MemoryMapWindows::MemoryMapWindows(const std::string& path) {
	file = CreateFileA(
	path.c_str(),
	GENERIC_READ,
	FILE_SHARE_READ,
	nullptr,
	OPEN_EXISTING,
	FILE_ATTRIBUTE_NORMAL,
	nullptr
	);
	if (file == INVALID_HANDLE_VALUE)
		throw std::runtime_error("MemoryMapWindows error: CreateFile failed");

	LARGE_INTEGER sz;
	if (!GetFileSizeEx(file, &sz)) {
		CloseHandle(file);
		throw std::runtime_error("MemoryMapWindows error: GetFileSizeEx failed");
	}

	size_ = static_cast<std::size_t>(sz.QuadPart);
	if (size_ == 0)
		throw std::runtime_error("MemoryMapWindows error: file is empty");

	mapping = CreateFileMappingA(
		file,
		nullptr,
		PAGE_READONLY,
		0,
		0,
		nullptr
		);
	if (!mapping) {
		CloseHandle(file);
		throw std::runtime_error("MemoryMapWindows error: CreateFileMapping failed");
	}

	data_ = MapViewOfFile(
		mapping,
		FILE_MAP_READ,
		0,
		0,
		0
		);
	if (!data_) {
		CloseHandle(mapping);
		CloseHandle(file);
		throw std::runtime_error("MemoryMapWindows error: MapViewOfFile failed");
	}
}

MemoryMapWindows::~MemoryMapWindows() {
	if (data_) UnmapViewOfFile(data_);
	if (mapping) CloseHandle(mapping);
	if (file != INVALID_HANDLE_VALUE) CloseHandle(file);
}


#else
MemoryMapPosix::MemoryMapPosix(const std::string& path) {
	fd = ::open(path.c_str(), O_RDONLY);
	if (fd == -1)
		throw std::runtime_error("MemoryMapPosix error: open failed");

	struct stat st;
	if (::fstat(fd, &st) == -1) {
		::close(fd);
		throw std::runtime_error("MemoryMapPosix error: fstat failed");
	}

	size_ = static_cast<std::size_t>(st.st_size);
	if (size_ == 0)
		throw std::runtime_error("MemoryMapPosix error: file is empty");

	data_ = ::mmap(
		nullptr,
		size_,
		PROT_READ,
		MAP_PRIVATE,
		fd,
		0
	);
	if (data_ == MAP_FAILED) {
		::close(fd);
		throw std::runtime_error("MemoryMapPosix error: mmap failed");
	}
}

MemoryMapPosix::~MemoryMapPosix() {
	if (data_ && data_ != MAP_FAILED)
		::munmap(data_, size_);
	if (fd != -1)
		::close(fd);
}
#endif
}