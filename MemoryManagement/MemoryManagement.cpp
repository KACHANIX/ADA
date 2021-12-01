#include "MemoryAllocator.h"

int main()
{
	MemoryAllocator allocator;
	allocator.init();

	auto pi = static_cast<int*>(allocator.alloc(sizeof(int)));
	auto pi2 = static_cast<int*>(allocator.alloc(sizeof(int)));
	auto pd = static_cast<double*>(allocator.alloc(sizeof(double)));
	auto pa = static_cast<int*>(allocator.alloc(10 * sizeof(int)));
	allocator.dumpStat();
	allocator.dumpBlocks();
	allocator.free(pa);
	allocator.free(pd);
	allocator.free(pi);
	allocator.free(pi2);
	pi = static_cast<int*>(allocator.alloc(sizeof(int)));
	allocator.free(pi);
	allocator.destroy();


	///////////
	std::cout << std::endl << std::endl << std::endl;
	MemoryAllocator allocator1;
	allocator1.init();

	auto a = static_cast<char*>(allocator1.alloc(7));
	auto b = static_cast<char*>(allocator1.alloc(128));
	auto a1 = static_cast<char*>(allocator1.alloc(129));
	auto a2 = static_cast<char*>(allocator1.alloc(129));
	auto a3 = static_cast<char*>(allocator1.alloc(129));
	auto a4 = static_cast<char*>(allocator1.alloc(129));
	auto a5 = static_cast<char*>(allocator1.alloc(129));
	auto a6 = static_cast<char*>(allocator1.alloc(129));
	auto a7 = static_cast<char*>(allocator1.alloc(129));
	auto a8 = static_cast<char*>(allocator1.alloc(129));
	auto c = static_cast<char*>(allocator1.alloc(550));
	auto d = static_cast<char*>(allocator1.alloc(1020));
	auto e = static_cast<char*>(allocator1.alloc(1024 * 1024 * 11));

	allocator1.dumpStat();
	allocator1.dumpBlocks();
	allocator1.destroy();


	std::cout << std::endl << std::endl << std::endl;
	allocator1.init();

	auto f = static_cast<char*>(allocator1.alloc(7));
	auto g = static_cast<char*>(allocator1.alloc(128));
	auto h = static_cast<char*>(allocator1.alloc(550));
	auto i = static_cast<char*>(allocator1.alloc(1020));
	auto j = static_cast<char*>(allocator1.alloc(1024 * 1024 * 11));

	allocator1.dumpStat();
	allocator1.dumpBlocks();
	allocator1.destroy();
}
