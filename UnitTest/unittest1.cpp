#include "stdafx.h"
#include "CppUnitTest.h"

#include "../BagelScript/memorypool.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(MemoryPoolTest)
	{
	public:
		
		TEST_METHOD(ContinuousMalloc)
		{
			// TODO:  在此输入测试代码
			memset(allocator_array(), 0, SMALL * sizeof(void*));
			Logger::WriteMessage("malloc 10000000 int...\n");
			auto c1 = getMS();
			auto alloc = new _BKE_allocator<1>();
			for (int i = 0; i < 10000000; i++)
				alloc->allocate();
			auto c2 = getMS();
			delete alloc;
			Logger::WriteMessage("Pass\n");
			Logger::WriteMessage("pool malloc cost ");
			Logger::WriteMessage(ToString(c2 - c1).c_str());
			Logger::WriteMessage("ms\n");
		}

		TEST_METHOD(ContinuousMallocRaw)
		{
			void **ptr = new void*[10000000];
			Logger::WriteMessage("malloc 10000000 int...\n");
			auto c3 = getMS();
			for (int i = 0; i < 10000000; i++)
			{
				ptr[i] = malloc(sizeof(int) * 1);
			}
			auto c4 = getMS();
			for (int i = 0; i < 10000000; i++)
			{
				free(ptr[i]);
			}
			delete[] ptr;
			Logger::WriteMessage("Pass\n");
			Logger::WriteMessage("native malloc cost ");
			Logger::WriteMessage(ToString(c4 - c3).c_str());
			Logger::WriteMessage("ms\n");
		}
			
		TEST_METHOD(ContinuousMallocFree)
		{
			// TODO:  在此输入测试代码
			int **ptr = new int*[10000000];
			memset(allocator_array(), 0, SMALL * sizeof(void*));
			Logger::WriteMessage("malloc 10000000 int...\n");
			auto c1 = getMS();
			auto alloc = new _BKE_allocator<1>();
			for (int i = 0; i < 10000000; i++)
			{
				ptr[i] = (int*)alloc->allocate();
			}
			for (int i = 0; i < 10000000; i++)
			{
				alloc->deallocate(ptr[i]);
			}
			delete alloc;
			auto c2 = getMS();
			delete[] ptr;
			Logger::WriteMessage("Pass\n");
			Logger::WriteMessage("pool malloc && free cost ");
			Logger::WriteMessage(ToString(c2 - c1).c_str());
			Logger::WriteMessage("ms\n");
		}

		TEST_METHOD(ContinuousMallocFreeRaw)
		{
			// TODO:  在此输入测试代码
			int **ptr = new int*[10000000];
			Logger::WriteMessage("malloc 10000000 int...\n");
			auto c3 = getMS();
			for (int i = 0; i < 10000000; i++)
			{
				ptr[i] = (int*)malloc(sizeof(int));
			}
			for (int i = 0; i < 10000000; i++)
			{
				free(ptr[i]);
			}
			auto c4 = getMS();
			delete[] ptr;
			Logger::WriteMessage("Pass\n");
			Logger::WriteMessage("native malloc && free cost ");
			Logger::WriteMessage(ToString(c4 - c3).c_str());
			Logger::WriteMessage("ms\n");
		}

		TEST_METHOD(IntesectMallocFree)
		{
			// TODO:  在此输入测试代码
			int **ptr = new int*[10000000];
			memset(allocator_array(), 0, SMALL * sizeof(void*));
			Logger::WriteMessage("malloc 10000000 int...\n");
			auto c1 = getMS();
			auto alloc = new _BKE_allocator<1>();
			for (int i = 0; i < 10000000; i++)
			{
				ptr[i] = (int*)alloc->allocate();
				alloc->deallocate(ptr[i]);
			}
			delete alloc;
			auto c2 = getMS();
			delete[] ptr;
			Logger::WriteMessage("Pass\n");
			Logger::WriteMessage("pool malloc cost ");
			Logger::WriteMessage(ToString(c2 - c1).c_str());
			Logger::WriteMessage("ms\n");
		}

		TEST_METHOD(IntesectMallocFreeRaw)
		{
			// TODO:  在此输入测试代码
			int **ptr = new int*[10000000];
			Logger::WriteMessage("malloc 10000000 int...\n");
			auto c3 = getMS();
			for (int i = 0; i < 10000000; i++)
			{
				ptr[i] = (int*)malloc(sizeof(int));
				free(ptr[i]);
			}
			auto c4 = getMS();
			delete[] ptr;
			Logger::WriteMessage("Pass\n");
			Logger::WriteMessage("native malloc cost ");
			Logger::WriteMessage(ToString(c4 - c3).c_str());
			Logger::WriteMessage("ms\n");
		}

		TEST_METHOD(Shrink)
		{
			// TODO:  在此输入测试代码
			int **ptr = new int*[10000000];
			memset(allocator_array(), 0, SMALL * sizeof(void*));
			auto c1 = getMS();
			auto alloc = new _BKE_allocator<1>();
			for (int i = 0; i < 10000000; i++)
			{
				ptr[i] = (int*)alloc->allocate();
			}
			for (int i = 0; i < 5000000; i++)
			{
				alloc->deallocate(ptr[2 * i + 1]);
			}
			auto c2 = getMS();
			alloc->shrink();
			auto c3 = getMS();
			for (int i = 0; i < 5000000; i++)
			{
				ptr[2 * i + 1] = (int*)alloc->allocate();
			}
			delete alloc;
			auto c4 = getMS();
			for (int i = 0; i < 10000000; i++)
			{
				ptr[i] = (int*)malloc(sizeof(int));
			}
			for (int i = 0; i < 5000000; i++)
			{
				free(ptr[2 * i + 1]);
			}
			for (int i = 0; i < 5000000; i++)
			{
				ptr[2 * i + 1] = (int*)malloc(sizeof(int));
			}
			auto c5 = getMS();
			for (int i = 0; i < 10000000; i++)
			{
				free(ptr[i]);
			}
			delete[] ptr;
			Logger::WriteMessage("Pass\n");
			Logger::WriteMessage("Pass\n");
			Logger::WriteMessage("pool malloc && shrink && malloc cost ");
			Logger::WriteMessage(ToString(c4 - c1).c_str());
			Logger::WriteMessage("ms\n");
			Logger::WriteMessage("shrink cost ");
			Logger::WriteMessage(ToString(c3 - c2).c_str());
			Logger::WriteMessage("ms\n");
			Logger::WriteMessage("native alloc cost ");
			Logger::WriteMessage(ToString(c5 - c4).c_str());
			Logger::WriteMessage("ms\n");
		}

		TEST_METHOD(Shrink2)
		{
			// TODO:  在此输入测试代码
			int **ptr = new int*[10000000];
			void **ptr2 = new void*[10000000];
			memset(allocator_array(), 0, SMALL * sizeof(void*));
			auto c1 = getMS();
			auto alloc = new _BKE_allocator<1>();
			for (int i = 0; i < 10000000; i++)
			{
				ptr[i] = (int*)alloc->allocate();
			}
			for (int i = 0; i < 5000000; i++)
			{
				alloc->deallocate(ptr[i + 2000000]);
			}
			auto c2 = getMS();
			alloc->shrink();
			auto c3 = getMS();
			for (int i = 0; i < 10000000; i++)
			{
				alloc->allocate();
			}
			delete alloc;
			auto c4 = getMS();
			for (int i = 0; i < 10000000; i++)
			{
				ptr[i] = (int*)malloc(sizeof(int));
			}
			for (int i = 0; i < 5000000; i++)
			{
				free(ptr[i + 2000000]);
			}
			for (int i = 0; i < 10000000; i++)
			{
				ptr2[i] = malloc(sizeof(int));
			}
			auto c5 = getMS();
			for (int i = 0; i < 10000000; i++)
			{
				free(ptr2[i]);
			}
			for (int i = 0; i < 2000000; i++)
			{
				free(ptr[i]);
			}
			for (int i = 7000000; i < 10000000; i++)
			{
				free(ptr[i]);
			}
			delete[] ptr;
			delete[] ptr2;
			Logger::WriteMessage("Pass\n");
			Logger::WriteMessage("Pass\n");
			Logger::WriteMessage("pool malloc && shrink && malloc cost ");
			Logger::WriteMessage(ToString(c4 - c1).c_str());
			Logger::WriteMessage("ms\n");
			Logger::WriteMessage("shrink cost ");
			Logger::WriteMessage(ToString(c3 - c2).c_str());
			Logger::WriteMessage("ms\n");
			Logger::WriteMessage("native alloc cost ");
			Logger::WriteMessage(ToString(c5 - c4).c_str());
			Logger::WriteMessage("ms\n");
		}

		TEST_METHOD(NoShrink)
		{
			// TODO:  在此输入测试代码
			int **ptr = new int*[10000000];
			void **ptr2 = new void*[10000000];
			memset(allocator_array(), 0, SMALL * sizeof(void*));
			auto c1 = getMS();
			auto alloc = new _BKE_allocator<1>();
			for (int i = 0; i < 10000000; i++)
			{
				ptr[i] = (int*)alloc->allocate();
			}
			for (int i = 0; i < 5000000; i++)
			{
				alloc->deallocate(ptr[2 * i + 1]);
			}
			//auto c2 = getMS();
			//alloc->shrink();
			//auto c3 = getMS();
			for (int i = 0; i < 10000000; i++)
			{
				alloc->allocate();
			}
			delete alloc;
			auto c4 = getMS();
			for (int i = 0; i < 10000000; i++)
			{
				ptr[i] = (int*)malloc(sizeof(int));
			}
			for (int i = 0; i < 5000000; i++)
			{
				free(ptr[2 * i + 1]);
			}
			for (int i = 0; i < 10000000; i++)
			{
				ptr2[i] = malloc(sizeof(int));
			}
			auto c5 = getMS();
			for (int i = 0; i < 10000000; i++)
			{
				free(ptr2[i]);
			}
			for (int i = 0; i < 5000000; i++)
			{
				free(ptr[2 * i]);
			}
			delete[] ptr;
			delete[] ptr2;
			Logger::WriteMessage("Pass\n");
			Logger::WriteMessage("Pass\n");
			Logger::WriteMessage("pool malloc && free && malloc cost ");
			Logger::WriteMessage(ToString(c4 - c1).c_str());
			Logger::WriteMessage("ms\n");
			//Logger::WriteMessage("shrink cost ");
			//Logger::WriteMessage(ToString(c3 - c2).c_str());
			//Logger::WriteMessage("ms\n");
			Logger::WriteMessage("native alloc cost ");
			Logger::WriteMessage(ToString(c5 - c4).c_str());
			Logger::WriteMessage("ms\n");
		}

		TEST_METHOD(DynamicMallocFree)
		{
			int **ptr = new int*[10000000];
			memset(allocator_array(), 0, SMALL * sizeof(void*));
			Logger::WriteMessage("malloc 10000000 int...\n");
			auto c1 = getMS();
			auto alloc = (_BKE_allocator<10>*)new _BKE_allocator<1>();
			for (int i = 0; i < 10000000; i++)
			{
				ptr[i] = (int*)alloc->dynamic_allocate();
			}
			for (int i = 0; i < 10000000; i++)
			{
				alloc->dynamic_deallocate(ptr[i]);
			}
			delete alloc;
			auto c2 = getMS();
			for (int i = 0; i < 10000000; i++)
			{
				ptr[i] = (int*)malloc(sizeof(int));
			}
			for (int i = 0; i < 10000000; i++)
			{
				free(ptr[i]);
			}
			auto c3 = getMS();
			delete[] ptr;
			Logger::WriteMessage("Pass\n");
			Logger::WriteMessage("Pass\n");
			Logger::WriteMessage("pool malloc && free cost ");
			Logger::WriteMessage(ToString(c2 - c1).c_str());
			Logger::WriteMessage("ms\n");
			Logger::WriteMessage("native malloc && free cost ");
			Logger::WriteMessage(ToString(c3 - c2).c_str());
			Logger::WriteMessage("ms\n");
		}

		TEST_METHOD(DynamicIntesectMallocFree)
		{
			int **ptr = new int*[10000000];
			memset(allocator_array(), 0, SMALL * sizeof(void*));
			Logger::WriteMessage("malloc 10000000 int...\n");
			auto c1 = getMS();
			auto alloc = (_BKE_allocator<10>*)new _BKE_allocator<1>();
			for (int i = 0; i < 10000000; i++)
			{
				ptr[i] = (int*)alloc->dynamic_allocate();
				alloc->dynamic_deallocate(ptr[i]);
			}
			delete alloc;
			auto c2 = getMS();
			for (int i = 0; i < 10000000; i++)
			{
				ptr[i] = (int*)malloc(sizeof(int));
				free(ptr[i]);
			}
			auto c3 = getMS();
			delete[] ptr;
			Logger::WriteMessage("Pass\n");
			Logger::WriteMessage("Pass\n");
			Logger::WriteMessage("pool malloc && free cost ");
			Logger::WriteMessage(ToString(c2 - c1).c_str());
			Logger::WriteMessage("ms\n");
			Logger::WriteMessage("native malloc && free cost ");
			Logger::WriteMessage(ToString(c3 - c2).c_str());
			Logger::WriteMessage("ms\n");
		}

		TEST_METHOD(DiffSizeMallocFree)
		{
			memset(allocator_array(), 0, SMALL * sizeof(void*));
			void **ptr = new void*[2000000];
			void **ptr2 = new void*[2000000];
			void **ptr3 = new void*[2000000];
			void **ptr4 = new void*[2000000];
			void **ptr5 = new void*[2000000];
			Logger::WriteMessage("malloc 10000000 int and double...\n");
			auto c1 = getMS();
			auto alloc = new _BKE_allocator<1>();
			auto alloc2 = new _BKE_allocator<2>();
			auto alloc3 = new _BKE_allocator<3>();
			auto alloc4 = new _BKE_allocator<4>();
			auto alloc5 = new _BKE_allocator<5>();
			for (int i = 0; i < 2000000; i++)
			{
				ptr[i] = alloc->allocate();
				ptr2[i] = alloc2->allocate();
				ptr3[i] = alloc3->allocate();
				ptr4[i] = alloc4->allocate();
				ptr5[i] = alloc5->allocate();
			}
			for (int i = 0; i < 2000000; i++)
			{
				alloc->deallocate(ptr[i]);
				alloc2->deallocate(ptr2[i]);
				alloc3->deallocate(ptr3[i]);
				alloc4->deallocate(ptr4[i]);
				alloc5->deallocate(ptr5[i]);
			}
			delete alloc;
			delete alloc2;
			delete alloc3;
			delete alloc4;
			delete alloc5;
			auto c2 = getMS();
			for (int i = 0; i < 2000000; i++)
			{
				ptr[i] = malloc(4);
				ptr2[i] = malloc(8);
				ptr3[i] = malloc(12);
				ptr4[i] = malloc(16);
				ptr5[i] = malloc(20);
			}
			for (int i = 0; i < 2000000; i++)
			{
				free(ptr[i]);
				free(ptr2[i]);
				free(ptr3[i]);
				free(ptr4[i]);
				free(ptr5[i]);
			}
			auto c3 = getMS();
			delete[] ptr;
			delete[] ptr2;
			delete[] ptr3;
			delete[] ptr4;
			delete[] ptr5;
			Logger::WriteMessage("Pass\n");
			Logger::WriteMessage("Pass\n");
			Logger::WriteMessage("pool malloc && free cost ");
			Logger::WriteMessage(ToString(c2 - c1).c_str());
			Logger::WriteMessage("ms\n");
			Logger::WriteMessage("native malloc && free cost ");
			Logger::WriteMessage(ToString(c3 - c2).c_str());
			Logger::WriteMessage("ms\n");
		}

		TEST_METHOD(DiffSizeIntesectMallocFree)
		{
			memset(allocator_array(), 0, SMALL * sizeof(void*));
			void **ptr = new void*[10000000];
			void **ptr2 = new void*[10000000];
			void **ptr3 = new void*[10000000];
			void **ptr4 = new void*[10000000];
			void **ptr5 = new void*[10000000];
			Logger::WriteMessage("malloc 10000000 int and double...\n");
			auto c1 = getMS();
			auto alloc = new _BKE_allocator<1>();
			auto alloc2 = new _BKE_allocator<2>();
			auto alloc3 = new _BKE_allocator<3>();
			auto alloc4 = new _BKE_allocator<4>();
			auto alloc5 = new _BKE_allocator<5>();
			for (int i = 0; i < 10000000; i++)
			{
				ptr[i] = alloc->allocate();
				ptr2[i] = alloc2->allocate();
				ptr3[i] = alloc3->allocate();
				ptr4[i] = alloc4->allocate();
				ptr5[i] = alloc5->allocate();
				alloc->deallocate(ptr[i]);
				alloc2->deallocate(ptr2[i]);
				alloc3->deallocate(ptr3[i]);
				alloc4->deallocate(ptr4[i]);
				alloc5->deallocate(ptr5[i]);
			}
			delete alloc;
			delete alloc2;
			delete alloc3;
			delete alloc4;
			delete alloc5;
			auto c2 = getMS();
			for (int i = 0; i < 10000000; i++)
			{
				ptr[i] = malloc(4);
				ptr2[i] = malloc(8);
				ptr3[i] = malloc(12);
				ptr4[i] = malloc(16);
				ptr5[i] = malloc(20);
				free(ptr[i]);
				free(ptr2[i]);
				free(ptr3[i]);
				free(ptr4[i]);
				free(ptr5[i]);
			}
			auto c3 = getMS();
			delete[] ptr;
			delete[] ptr2;
			delete[] ptr3;
			delete[] ptr4;
			delete[] ptr5;
			Logger::WriteMessage("Pass\n");
			Logger::WriteMessage("Pass\n");
			Logger::WriteMessage("pool malloc && free cost ");
			Logger::WriteMessage(ToString(c2 - c1).c_str());
			Logger::WriteMessage("ms\n");
			Logger::WriteMessage("native malloc && free cost ");
			Logger::WriteMessage(ToString(c3 - c2).c_str());
			Logger::WriteMessage("ms\n");
		}
	};
}