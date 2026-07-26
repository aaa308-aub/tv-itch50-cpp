# DEVELOPER LOG
This log is to explain the decisions I've made throughout the project. Please note that it's not meant to be read like documentation; it's more of a technical diary, so some parts may feel too lengthy. The dates are listed from newest to oldest in the ``DD.MM.YYYY`` format.

### 26.07.2026

* **Deprecated enum-classes:** Using ``enum class`` for strong type safety on day-one of this project was good on paper, but it causes a lot of developer friction for casting between types and writing wrapper-functions to cast after every operation. I had to weigh carefully whether to continue using ``enum class`` or to drop it completely, and I decided that my parser should simply read bytes and output bytes re-aligned and nothing more. It's much easier to maintain this way.

* **Undone coupling of message types:** In the spec, you will see ``Add Order`` messages but with one extra field -- a different type named ``Add Order With MPID Distribution``. Similarly for ``Execute Order`` and ``Execute Order With Price``, or ``Cancel Order`` and ``Delete Order``. Initially I just coupled each pair into a single struct. This wasn't a catastrophic choice, but it complicates things unnecessarily and may confuse the user from their perspective.

* **Tested type-erased handler with function pointers [DISCONTINUED]:** This was to hopefully prevent templating the whole ``Parser`` class and instead template only its constructor, containing the "template virus" so that the user doesn't have to. Sadly, the indirect function calls led to too much overhead: about 12% less throughput. So, meta-programming wins again.

### 20.07.2026

* I came back to this project with greater understanding of memory thanks to other projects. I've done quite a lot of changes the past few days and I've listed them below. I look back at this document a lil' uncanny. On the one hand, it's always good to have a "technical footprint", but on the other, my understanding of a couple things wasn't great. Now that I understand virtual address spaces, page caching, branch predictions, what is and is not cheap to perform, etc. pretty well, reading this document backwards makes me cringe a little; thankfully, noone else is gonna see this... right?

* **Achieved low-latency level speeds:** Through the implementations below, the parser became truly zero-copy and ultra-low-latency. Even copying every single message -- if requested by the user's handler (see below) -- results in over 2.5 GB/s throughput (warm cache, Google benchmark). In the base case where the handler does nothing at all, the parser walks a 13 GB sample in 2 seconds, or with a ~6.5 GB/s throughput.

* **Moved to C++20:** To support the use of ``requires`` and easily find endianness of user's architecture.

* **Implemented handler in a producer-consumer design:** Instead of eagerly parsing each message with all its fields and returning it to the user, now the user can just define a struct/class ``handler``, with methods having specific identifiers: ``onSystemEvent``, ``onStockDirectory``, ``onStockTradingAction`` etc., each taking a view-type struct (see below). These viewers allow the user to either parse only the fields they use, or create a struct using the ``unbox()`` method. As a compromise, I accepted that the parser will be templated and hence defined entirely in ``parser.hpp``. I've looked at many other solutions, and they're all too boilerplate-y and harder to maintain.

* **Removed use of ``std::variant`` and introduced viewers:** Returning and dispatching is far too costly, and I settled on concrete view-types (similar to ``std::string_view``), each owning a base pointer to the message as-is in the feed. Every viewer has field extraction methods (through ``memcpy`` and ``byteswap`` calls) taking as argument a pointer (base + offset). Crucially, since this pointer is always an r-value, the CPU can aggressively extract these fields simultaneously. The compiler may also be replacing the combinations of ``memcpy + byteswap`` and replacing them with a single instruction.

* **Enabled pageing lookahead in ``mmap``:** Just an oversight at the time I created this project. It's fixed now.

* **Made all enum underlying types unsigned integers [DEPRECATED]:** This was necessary to shed a lot of boilerplate and ``static_cast``s. It may have also led to some performance improvements.

### 25.12.2025 -- RELEASE DATE

* Separated code into proper C++ class files (header + source implementation).
* Wrote the ``README`` and verified the instructions and the ``Example Use Case``

### 24.12.2025

* Massive headache. No work today.

### 23.12.2025

* **Reimagined the scope of my parser:** I wanted to turn this into a high-throughput multi-threaded parser. But the fact that we're parsing an all-binary zero-headers file makes it impossible to parse the file in parallel without prior deserialization (i.e. finding all the message offsets). But I also think that the parser, in its current state, is extremely easy to debug should anything go wrong or to modify should NASDAQ ever update their spec. That's why I believe that simple, sequential parsing without prior deserialization is better. I want to move on to something new. It's way more interesting to show what we can do with this data post-parsing instead of trying to parse it faster. I'm also not really interested in building order books right now, so I removed the couple lines I wrote of the ``OrderBook`` and ``OrderBookMaster`` classes that I haven't tested anyway.

* **Wrote namespace ``tv_itch::ios``:** It contains overloaded ``std::ostream& operator<<`` for every single message struct and of course ``MessageVariant``. It also contains overloaded ``to_string`` functions for every single enum class. I decided to keep the padding of MPIDs and stock symbols (to the right by spaces) because they're lined up better this way. Those two enum classes with underlying types ``uint16_t`` and ``uint32_t`` are padded too.

### 22.12.2025

* **Wrote a lightweight memory-mapping class:** It's actually two classes defined in the ``mmap.h`` header: ``MemoryMapWindows`` and ``MemoryMapPosix``, because I want my parser to work both on Windows and on Linux (or on any other POSIX-certified OS while we're at it). A using-directive gives the right class to the user:

```c++
#ifdef _WIN32
using MemoryMap = MemoryMapWindows;
#else
using MemoryMap = MemoryMapPosix;
#endif
```

The ``MemoryMap`` class-alias is read-only in both cases. It returns non-const pointers to ``const uint8_t``, so you can iterate through the mapped file but can't modify it.

* **Avoided bit-shifting and ``reinterpret_cast``:** bit- or byte-shifting isn't inherently bad, but I wanted to avoid it as much as possible during parsing. So instead I use ``std::memcpy`` and built-in byte-swapping functions (determined based on the compiler being used) which is not the same as byte-shifting; it's a single CPU instruction (``BSWAP``) under the hood. I also wanted to avoid ``reinterpret_cast`` and had to be careful when handling ``timestamp`` fields, which are 6-bytes long but must be saved in ``uint64_t``.

* **Linux and big-endian architecture emulation:** I used WSL + QEMU to emulate Linux and big-endian systems, just to verify for correctness. As expected, ``std::memcpy`` works fine when mapping from the big-endian spec to a big-endian system and no additional steps need to be taken. I also verified for timestamp fields (6-byte fields saved in ``uint64_t``). ``MemoryMapPosix`` was also tested. Everything is working as intended.

* **Completed switch from buffer to memory-map:** This completely simplified the entire class. Just a pointer to the mapped file and no buffer or carry, no bounds-checking (other than ``ptr != end``), no overused boolean flags... Just fast and simple iterative parsing.

### 21.12.2025

* **Avoided message struct padding:** Most parsers probably use compiler-specific attributes like ``__attribute__((packed))`` or ``[[gnu::packed]]``. It'll cause cache misalignment, but you can use ``std::memcpy`` to copy everything from the parsed message immediately into the struct. I chose not to do any of this because I prefer portability over compiler-specific micro-optimizations. I'm instead using ``std::memcpy`` on every field individually.

* **Finished parser with message parse functions:** I achieved a parsing speed of about 500 MB/s which is around the same read speed I got with ``std::ifstream``, so this could be (and probably is) a bottleneck. I'm going to switch to memory-mapping anyway.

* **Callback semantics:** Inspired by ``databento``'s API, I simplified callback by leaving it to the user in this fashion:

```c++
    while (parser.nextRecord()) {
        const auto msg = parser.record();
        // ...
    }
```

They must remember that ``msg`` is of type ``std::variant<SystemEvent, StockDirectory, StockTradingAction...>``. ``nextRecord()`` advances to the next record i.e. message and returns true. If no messages are left, It won't advance and will return false instead. ``record()`` simply returns the current message (after advancing through ``nextRecord()``).

### 20.12.2025

* **Getting ``MAX_CARRY_SIZE`` [DEPRECATED]:** It should be >= the greatest message length possible. Currently of length 50, type ``NOII`` (Net Order Imbalance Indicator message). Iterating over enumerators in C++ is not possible (at least not in C++17) so the workaround done to get this max at compile time is too much boilerplate for this simple task. That's why I hardcoded ``MAX_CARRY_SIZE`` to 64. So if NASDAQ ever updates their spec... Well the whole parser would need updating anyway.

* **Using buffer or carry when parsing messages [DEPRECATED]:** Every time a message is parsed, it needs to know whether to read from the buffer or the carry. I tried the following with ``std::variant``:

```c++
using rw_buffer = std::reference_wrapper< std::array<char, BUFFER_SIZE> >;
using rw_carry = std::reference_wrapper< std::array<char, MAX_CARRY_SIZE> >;
using BufferOrCarryRef = std::variant< rw_buffer, rw_carry >;

BufferOrCarryRef MakeBufferOrCarryVariant() {
    if (is_carry) return std::ref(carry);
    else return std::ref(buffer);
}

void parseAddMessage(const bool withMPID) {
    BufferOrCarryRef container = MakeBufferOrCarryVariant();
    // ...
}
```
    
This works and is safe, but dereferencing and iterating over the reference container becomes unreadable as a ``std::variant`` and will cost performance in all hot paths. Instead, we use ``std::array``'s contiguousness to our advantage with a ``char*`` pointer. Since our buffer logic is index-based, we must remember to adjust ``buffer_idx`` after parsing if read from the buffer, because ``buffer_idx`` was not used here. All this leads to an unideal design where some parts use ``buffer_idx`` while others iterate by pointer to ``char``, which can be confusing for readability. I'll consider simplifying this in the future.

* **Added message structs by type and callback function for parser [DEPRECATED]:** Initially, as I wrote on ``19.12.2025``, I wanted to parse only the message types related to adding/canceling/executing orders and "ignore but log" the rest. This is because I was only concerned with building the order book afterward. I believe now this is wrong and that my parser should parse all messages of all types and return them, without concerning itself with what will be done with those messages. Which is why I templated the parser with a ``Callback`` type parameter, which is any callable type. The parser will call it with ``operator()`` and with argument ``MessageStruct``, which is a ``std::variant`` of message structs I created by type: ``AddOrder``, ``CancelOrder``, ``NonCrossTrade``, etc. This way, the logic is all nice and separated between ``Parser`` and ``OrderBookMaster`` and I can easily make an interface class that joins the two cleanly.

* **Enums in ``tv_itch::spec`` [DEPRECATED]:** If I want to parse every single message, this means I have to respect the entire spec. Most message types have alpha fields (usually 1 character) that can take multiple values. I could've just made them all of type ``char`` in my message structs, but I decided to make corresponding enum classes instead and accept that the namespace will become quite bloated.

### 19.12.2025

* Created developer log (this file). I should've done this from the beginning, but better late than never.

* **Project Progression:** I'll start by making a simple, sequential, single-threaded, standard-library-only parser, so that I understand how everything works and then optimize.

* **Code Structure/Layout:** I made a namespace ``tv_itch`` which contains all the enums, classes, helper functions, etc. and tried to keep things simple.

* **Debug Mode and Checks [DEPRECATED]:** I decided not to use some pre-defined debug macro and define my own: ``TV_ITCH50_CPP_DEBUG``, for enabling or disabling code blocks of assertions/other.

* **Containers [DEPRECATED]:** As mentioned before, right now I'm using STL containers and ``std::ifstream``. I may opt for third-party libraries or instead try to make the parser not have any dependencies outside the standard library.

* **Messages:** I chose messages of some types to be parsed, which are the trivial ones: ``AddWithoutMPID``, ``AddWithMPID``, ``Execute``, ``ExecuteWithPrice``, ``Cancel``, ``Delete`` and ``Replace``. For now, the rest will not be parsed but still logged. It's unclear right now what this really means, but it will probably work in a separate thread to not stall the parser.

* **Order Book [DEPRECATED]:** Currently the master order book -- the book which contains every order book for each stock symbol -- is a class named ``OrderBookMaster``, which is a simple wrapper of a map of stock symbols to their respective ``OrderBook`` objects, with the appropriate methods. For speed, I will keep stock symbols of type ``uint64_t``. Initially, I considered giving it a non-owning pointer to my ``Parser`` class, but since each class may function without the other, I decided it's better to make an interface class in the future that joins the two together, taking the output of the parser, writing logs, updating the master order book, etc.

* **Parser [DEPRECATED]:** Currently a class named ``Parser``, its purpose is about what you'd expect. It contains a ``std::ifstream`` and a 64 KB buffer to read from the stream. It has data members like ``buffer_idx``, ``message_length`` and ``message_type`` to keep everything simple and avoid lots of copying. The way the buffer state is handled by the methods of this class is correct but maybe not ideal, in the sense that there is more than one function that calls the ``advanceBuffer`` method, which can be slightly confusing.

* **Handling messages truncated by buffer [DEPRECATED]:** Every time the buffer is read, a message will typically be truncated/sliced at the buffer's boundaries. The ``getMessageInfo`` method handles this by checking if less than 3 bytes remain in the buffer and, if true, copies what's remaining (1 or 2 bytes) into the small carry, calls the ``advanceBuffer`` method and gets the 1 or 2 bytes left. From the first 3 bytes we can find the message length and type, assert that they match (in debug mode), and parse the message itself. Note that ``message_length`` always represents the canonical message length, which includes the message type. Since we already advanced the buffer (for when the slicing happens between the first 3 bytes), there is no need to copy the message itself to the carry -- we can continue parsing normally. In case the message itself is sliced, we can detect that through the boolean  ``bytes_remaining < message_length - 1`` (remember we must deduct the message type byte because we already parsed it).

* **Endianness [DEPRECATED]:** Finding user's endianness is made easier in C++20. In C++17, I tried to use preproc. directives:

```c++
#if defined(TV_ITCH50_CPP_LITTLE_ENDIAN) && defined(TV_ITCH50_CPP_BIG_ENDIAN)
    #error "Endianness of architecture cannot be defined as both big- and little-endian"
#elif !(defined(TV_ITCH50_CPP_LITTLE_ENDIAN) || defined(TV_ITCH50_CPP_BIG_ENDIAN))
    #if defined(_MSC_VER)
        #define TV_ITCH50_CPP_LITTLE_ENDIAN   // Always little-endian with MSVC
    #elif defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__)
        #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
            #define TV_ITCH50_CPP_LITTLE_ENDIAN
        #endif
    #else
        #error "Could not find endianness of architecture. User must manually set endianness"
    #endif
#endif
```
    
But then I decided it's better to simply assume little-endian: ``TV_ITCH50_CPP_LITTLE_ENDIAN``, and tell users to add ``-DTV_ITCH50_CPP_BIG_ENDIAN`` to their compiler commands if they are big-endian, OR add this line to their ``CMakeLists``: ``target_compile_definitions(main PRIVATE TV_ITCH50_CPP_BIG_ENDIAN)``. The ``TV_ITCH50_CPP_LITTLE_ENDIAN`` macro enables code blocks for inverting byte fields. The ``TV_ITCH50_CPP_BIG_ENDIAN`` simply un-defines that macro:

```c++
#ifndef TV_ITCH50_CPP_BIG_ENDIAN
#define TV_ITCH50_CPP_LITTLE_ENDIAN
#endif
```

I believe this is cleaner than making a boolean macro (=1 for true or =0 for false).
