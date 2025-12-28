# TV-ITCH50-CPP

## Introduction

**What is this?**\
``TV-ITCH50-CPP`` is a lightweight, easy-to-use C++ library for parsing **Nasdaq TotalView-ITCH 5.0** data feeds.

**What's Nasdaq TotalView-ITCH 5.0 (or ITCH for short)?**\
It is a proprietary data feed and protocol that provides the most comprehensive full order book depth for
Nasdaq-listed U.S. equities. Nasdaq is a major U.S. market operator that runs multiple electronic exchanges for
equities and other securities.\
The specification (or spec for short) for ITCH can be found [here](
https://www.nasdaqtrader.com/content/technicalsupport/specifications/dataproducts/NQTVITCHSpecification.pdf).
It is formatted in a long and pure binary sequence as seen [here](
https://www.nasdaqtrader.com/content/technicalSupport/specifications/dataproducts/binaryfile.pdf).
In short, it is a repeating binary sequence of this block: ``[2 bytes for message length][message of that length]``,
where the message's first byte always represents the message type. If read correctly, the message types and lengths
must match those found in the spec.

**How big are binary files from this feed?**\
Since ITCH encompasses thousands of stocks listed across Nasdaq, many of which have high liquidity (i.e. millions
of shares are traded per day), a single day of ITCH data results in very large data files -- typically dozens of
gigabytes. So whichever parser you use must be high-performance, especially if you're a researcher who needs
multi-terabytes of data to cover, say, a full year of trading (which is 250 to 252 trading days).

**What do I need to use this parser?**\
This project prioritizes ease of use and deployment and thus **does not require any third-party libraries to be
installed or built**. You're only required to have a **C++ compiler (version 17 or higher) and preferably CMake
(version  3.20 or higher)** to follow the build instructions below, but you can of course use whatever build system
you like. The parser's been tested thoroughly on Windows and on Linux, but there is no guarantee that it will work
on other operating systems like macOS or FreeBSD, as no testing was done on those systems.

**How is this parser implemented?**\
It's simple, fast and easy to reason about: the parser uses a custom and lightweight memory map, which is basically
a map of virtual addresses to your input data file. This way, we can bypass costly I/O calls and avoid storing chunks
of the data into the RAM and directly use pointers instead. The rest is just simple and clean iteration through the
data file and storing each message in a struct, whose type corresponds to the message type. Since this parser is
meant to be general-purpose, **all structs are not packed, and compiler extensions/other compiler-specific
optimizations are generally avoided,** apart from built-in byteswap functions.

**Where can I get a sample of ITCH data?**\
You may not want to pay fees for this kind of data. Some free samples are provided [here](
https://emi.nasdaq.com/ITCH/Nasdaq%20ITCH/).
But remember that these samples are huge, so make sure you have lots of free space on your computer!

## Build Instructions

Let's keep things simple and not have a headache with build systems. Suppose your project looks like:
```
your-project-folder
├─ main.cpp
├─ CMakeLists.txt
├─ Other things related to your project
```

Open the terminal and make sure you are in your project directory. Then use git to clone this repository:
```commandline
git clone https://github.com/aaa308-aub/tv-itch50-cpp
```

If you don't have git, you can instead just download the files from this repository and copy them into your project.
Just make sure they are inside a folder named ``tv-itch50-cpp`` to match the CMake config below.

The easiest way to build the parser is to include it as a static library in your CMake configuration. Your
project's ``CMakeLists.txt`` should look something like this:
```cmake
cmake_minimum_required(VERSION 3.20) # CMake version 3.20 or above is required
project(your-project-name)

set(CMAKE_CXX_STANDARD 17) # C++17 or above is required
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # If you want

add_subdirectory(tv-itch50-cpp) # You can change the folder name itself and then change it here

add_executable(your-project-name main.cpp)

target_link_libraries(your-project-name tv_itch50_cpp)

target_compile_options(your-project-name PRIVATE -O3) # Or whatever compile options you want

# If your architecture is big-endian, un-comment this command (see below for more details)
#add_definitions(-DTV_ITCH50_CPP_BIG_ENDIAN)
```

Note about endianness: You don't need to know what it means. Just know that, since you probably have a modern CPU
and you're not on some legacy architecture from the 90's, your CPU is "little-endian" and the parser naturally
assumes so. If your CPU is "big-endian," you must un-comment the line above to prevent reading bytes the wrong way.
I recommend to just google your CPU's endianness.

Now you can build like normal (unless you have a C++ IDE that handles it for you):
```
mkdir build
cd build
cmake ..
cmake --build .
```

## How To Use

First, include the parser in your project:
```c++
#include "tv_itch/parser.hpp"
```

Then instantiate it and provide the directory to your sample data file:
```c++
// If sample is in project directory and your project executable is in build folder:
tv_itch::Parser p("../sample_name.NASDAQ_ITCH50");
// Or just write the full path:
tv_itch::Parser p("C:/path/to/your/sample_name.NASDAQ_ITCH50");
// Make sure to use forward slashes, regardless of which operating system you are using
```

If needed, include ``tv_itch::ios`` -- a namespace for outputting messages to ``std::ostream`` or ``std::cout``:
```c++
#include "tv_itch/ios/ios.hpp"
using namespace tv_itch::ios;
```

The parser returns ``MessageVariant`` -- a ``std::variant`` of all message struct types like ``SystemEvent``,
``StockDirectory``, ``AddOrder``, etc. You may want to use these types, which can be included like this:
```c++
#include "tv_itch/spec/messages.hpp"
using MessageVariant = tv_itch::spec::MessageVariant;
```

The namespace ``tv_itch::spec``, as the name suggests, is a one-to-one binding of the entire ITCH spec to the
program.

All alpha fields in the spec namespace are saved as enum classes instead of just ``char`` in order to preserve
meaning of these fields and enforce stronger type-safety. The ``tv_itch::ios`` contains an overloaded ``to_string()``
function for every single enum class and message struct, to convert enum values like ``SharesOfBenificialInterest``
to strings like ``"Shares Of Benificial Interest"`` or to format messages (as comma-separated values).

To use the parser, you only need to know three methods. The ``record()`` method simply returns the last record (i.e.
message) parsed. This same record will be returned until you call the ``nextRecord()`` method, which parses the next
message and sets it as the last record and returns ``true``, or returns ``false`` when you've reached end-of-file or
``EOF`` and the last record remains unchanged. If you want to check ``EOF`` without attempting to advance the parser,
use the ``eof()`` method.

## Example Use Case
    
Let's make a simple program which does the following:
1. A while-loop to parse the first 1 million messages and add them to a vector of ``MessageVariant``s
2. A for-loop that iterates over the whole vector. For each message, we'll check if a message struct is of type
   ``SystemEvent``. If true, we output the ``SystemEventCode`` using the ``to_string()`` function mentioned earlier.
3. In this same for-loop, we'll output every single message onto ``std::cout``.

```c++
#include "tv_itch/parser.hpp"
#include "tv_itch/ios/ios.hpp"
#include "tv_itch/spec/messages.hpp"

#include <iostream>
#include <variant>
#include <vector>

int main() {
	// All message structs live in the namespace spec
	using MessageVariant = tv_itch::spec::MessageVariant;
	using SystemEvent = tv_itch::spec::SystemEvent;

	/*
	 * Open the spec namespace to see how SystemEvent is defined.
	 * Currently, it looks like this:
	 *
	 * SystemEvent {
	 *     std::uint64_t timestamp;
	 *     std::uint16_t stock_locate;
	 *     std::uint16_t tracking_number;
	 *     SystemEventCode event_code;
	 * };
	 *
	 * To save space, a message struct's fields are stored from
	 * largest to smallest in bytes -- not necessarily in
	 * the same order as they're listed in the ITCH spec.
	 *
	 * A SystemEventCode has the following enumerators:
	 * enum class SystemEventCode : char {
	 *     StartOfMessages    = 'O',
	 *     StartOfSystemHours = 'S',
	 *     StartOfMarketHours = 'Q',
	 *     EndOfMarketHours   = 'M',
	 *     EndOfSystemHours   = 'E',
	 *     EndOfMessages      = 'C',
	 * };
	 */

	using namespace tv_itch::ios;

	tv_itch::Parser p("C:/Users/abdal/Downloads/01302020.NASDAQ_ITCH50");
	std::vector<MessageVariant> vec;
	vec.reserve(1'000'000);

	while ( p.nextRecord() && vec.size() < 1'000'000 )
		vec.push_back( p.record() );

	for ( const auto& msg_var : vec ) {
		if ( const auto* msg = std::get_if<SystemEvent>( &msg_var ) )
			std::cout << to_string( msg->event_code ) << "\n";
		// Here you can add else-if statements for other message types if you want

		// No need to get the underlying message type for the operator<< overload
		// below. MessageVariant will dispatch accordingly at compile-time. It is
		// recommended to be familiar with std::variant and its methods.
		std::cout << msg_var << "\n";
	}
}
```