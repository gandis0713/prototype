// <mmintrin.h>  MMX
// <xmmintrin.h> SSE
// <emmintrin.h> SSE2
// <pmmintrin.h> SSE3
// <tmmintrin.h> SSSE3
// <smmintrin.h> SSE4.1
// <nmmintrin.h> SSE4.2
// <ammintrin.h> SSE4A
// <wmmintrin.h> AES
// <immintrin.h> AVX, AVX2, FMA

#include <xmmintrin.h>
#include <emmintrin.h>
#include <pmmintrin.h>
#include <smmintrin.h>
#include <nmmintrin.h>
#include <immintrin.h>
#include <chrono>
#include <iostream>
#include <memory>


const unsigned char bin_width_level = 4;
const unsigned char bin_height_level = 4;
const unsigned char bin_depth_level = 1;

const unsigned int ori_width = 400;
const unsigned int ori_height = 400;
const unsigned int ori_depth = 100;

constexpr unsigned int bin_width = ori_width / bin_width_level;
constexpr unsigned int bin_height = ori_height / bin_height_level;
constexpr unsigned int bin_depth = ori_depth / bin_depth_level;

constexpr size_t ori_size = ori_width * ori_height * ori_depth;
constexpr size_t bin_size = bin_width * bin_height * bin_depth;

using DataType = short;

std::chrono::system_clock::time_point start_time;
std::chrono::system_clock::time_point end_time;
std::chrono::duration<double> sec;

__m512i test;

void binning_sisd();

void binning_simd_128();

// void binning_simd_512();

int main()
{
	std::cout << "ori_size : " << ori_size << std::endl;
	std::cout << "bin_size : " << bin_size << std::endl;
	
	binning_sisd();

	binning_simd_128();

	// binning_simd_512();


	return 0;
	
}

void binning_simd_128()
{
	DataType* ori_data = reinterpret_cast<DataType*>(_mm_malloc(ori_size * sizeof(DataType), sizeof(DataType)));
	// std::unique_ptr<DataType[]> ori_data = std::unique_ptr<DataType[]>(new (std::nothrow) DataType[ori_size]);
	for(size_t i = 0; i < ori_size; ++i)
	{
		ori_data[i] = i;
	}
	size_t count = 0;
	for(size_t i = 0; i < ori_size; ++i)
	{
		if(ori_data[i] == 1)
		{
			++count;
		}
	}
	std::cout << "ori count : " << count << std::endl;

	DataType* bin_data = reinterpret_cast<DataType*>(_mm_malloc(bin_size * sizeof(DataType), sizeof(DataType)));
	// std::unique_ptr<DataType[]> bin_data = std::unique_ptr<DataType[]>(new (std::nothrow) DataType[bin_size]);
	for(size_t i = 0; i < bin_size; ++i)
	{
		bin_data[i] = 0;
	}
	count = 0;
	for(size_t i = 0; i < bin_size; ++i)
	{
		if(bin_data[i] == 0)
		{
			++count;
		}
	}
	std::cout << "bin count : " << count << std::endl;

	start_time = std::chrono::system_clock::now();

	__m128i value;

	DataType* ori_data_0 = &ori_data[0];
	DataType* bin_data_0 = &bin_data[0];

	DataType* ori_data_at = ori_data_0;
	DataType* bin_data_at = bin_data_0;

	size_t ori_index = 0;
	size_t bin_index = 0;
	const size_t offset = sizeof(__m128i) / sizeof(DataType);
	for(size_t d = 0; d < bin_depth; d++)
	{
		for(size_t h = 0; h < bin_height; h++)
		{
			for(size_t w = 0; w < bin_width; w += offset)
			{
				ori_index = d * ori_height * ori_width * bin_depth_level + h * ori_width * bin_height_level + w * bin_width_level;
				bin_index = d * bin_height * bin_width + h * bin_width + w;

				// value = _mm_loadu_si128((__m128i *)ori_data_0);
				value = _mm_set_epi16(ori_data_0[ori_index + 7 * bin_width_level],
														  ori_data_0[ori_index + 6 * bin_width_level],
															ori_data_0[ori_index + 5 * bin_width_level],
															ori_data_0[ori_index + 4 * bin_width_level],
															ori_data_0[ori_index + 3 * bin_width_level],
															ori_data_0[ori_index + 2 * bin_width_level],
															ori_data_0[ori_index + 1 * bin_width_level],
															ori_data_0[ori_index]);
				_mm_storeu_si128( reinterpret_cast<__m128i*>(&bin_data_0[bin_index]), value);
			}
		}
	}

	end_time = std::chrono::system_clock::now();
	sec = end_time - start_time;

	// for(size_t i = 0; i < bin_size; ++i)
	// {
	// 	std::cout << "bin_data " << i << " : " << bin_data[i] << std::endl;
	// }

	std::cout << "SIMD 128 time : " << sec.count() << std::endl;

	_mm_free(bin_data);
	_mm_free(ori_data);
}

// void binning_simd_512()
// {
// 	DataType* ori_data = reinterpret_cast<DataType*>(_mm_malloc(ori_size * sizeof(DataType), sizeof(DataType)));
// 	// std::unique_ptr<DataType[]> ori_data = std::unique_ptr<DataType[]>(new (std::nothrow) DataType[ori_size]);
// 	for(size_t i = 0; i < ori_size; ++i)
// 	{
// 		ori_data[i] = i;
// 	}
// 	size_t count = 0;
// 	for(size_t i = 0; i < ori_size; ++i)
// 	{
// 		if(ori_data[i] == 1)
// 		{
// 			++count;
// 		}
// 	}
// 	std::cout << "ori count : " << count << std::endl;

// 	DataType* bin_data = reinterpret_cast<DataType*>(_mm_malloc(bin_size * sizeof(DataType), sizeof(DataType)));
// 	// std::unique_ptr<DataType[]> bin_data = std::unique_ptr<DataType[]>(new (std::nothrow) DataType[bin_size]);
// 	for(size_t i = 0; i < bin_size; ++i)
// 	{
// 		bin_data[i] = 0;
// 	}
// 	count = 0;
// 	for(size_t i = 0; i < bin_size; ++i)
// 	{
// 		if(bin_data[i] == 0)
// 		{
// 			++count;
// 		}
// 	}
// 	std::cout << "bin count : " << count << std::endl;

// 	start_time = std::chrono::system_clock::now();

// 	__m512i value;

// 	DataType* ori_data_0 = &ori_data[0];
// 	DataType* bin_data_0 = &bin_data[0];

// 	DataType* ori_data_at = ori_data_0;
// 	DataType* bin_data_at = bin_data_0;

// 	size_t ori_index = 0;
// 	size_t bin_index = 0;

// 	const size_t offset = sizeof(__m512i) / sizeof(DataType);
// 	std::cout << "offsettime : " << offset << std::endl;
// 	for(size_t d = 0; d < bin_depth; d++)
// 	{
// 		for(size_t h = 0; h < bin_height; h++)
// 		{
// 			for(size_t w = 0; w < bin_width; w += offset)
// 			{
// 				ori_index = d * ori_height * ori_width * bin_depth_level + h * ori_width * bin_height_level + w * bin_width_level;
// 				bin_index = d * bin_height * bin_width + h * bin_width + w;

// 				value = _mm512_set_epi16(ori_data_0[ori_index + 31 * bin_width_level],
// 				  											 ori_data_0[ori_index + 30 * bin_width_level],
// 																 ori_data_0[ori_index + 29 * bin_width_level],
// 																 ori_data_0[ori_index + 28 * bin_width_level],
// 																 ori_data_0[ori_index + 27 * bin_width_level],
// 																 ori_data_0[ori_index + 26 * bin_width_level],
// 																 ori_data_0[ori_index + 25 * bin_width_level],
// 																 ori_data_0[ori_index + 24 * bin_width_level],
// 																 ori_data_0[ori_index + 23 * bin_width_level],
// 																 ori_data_0[ori_index + 22 * bin_width_level],
// 																 ori_data_0[ori_index + 21 * bin_width_level],
// 																 ori_data_0[ori_index + 20 * bin_width_level],
// 																 ori_data_0[ori_index + 19 * bin_width_level],
// 																 ori_data_0[ori_index + 18 * bin_width_level],
// 																 ori_data_0[ori_index + 17 * bin_width_level],
// 																 ori_data_0[ori_index + 16 * bin_width_level],
// 																 ori_data_0[ori_index + 15 * bin_width_level],
// 																 ori_data_0[ori_index + 14 * bin_width_level],
// 																 ori_data_0[ori_index + 13 * bin_width_level],
// 																 ori_data_0[ori_index + 12 * bin_width_level],
// 																 ori_data_0[ori_index + 11 * bin_width_level],
// 																 ori_data_0[ori_index + 10 * bin_width_level],
// 																 ori_data_0[ori_index + 9 * bin_width_level],
// 																 ori_data_0[ori_index + 8 * bin_width_level],
// 																 ori_data_0[ori_index + 7 * bin_width_level],
// 																 ori_data_0[ori_index + 6 * bin_width_level],
// 																 ori_data_0[ori_index + 5 * bin_width_level],
// 																 ori_data_0[ori_index + 4 * bin_width_level],
// 																 ori_data_0[ori_index + 3 * bin_width_level],
// 																 ori_data_0[ori_index + 2 * bin_width_level],
// 																 ori_data_0[ori_index + 1 * bin_width_level],
// 																 ori_data_0[ori_index]);
// 				_mm512_storeu_si512( reinterpret_cast<__m512i*>(&bin_data_0[bin_index]), value);
// 			}
// 		}
// 	}

// 	end_time = std::chrono::system_clock::now();
// 	sec = end_time - start_time;

// 	// for(size_t i = 0; i < bin_size; ++i)
// 	// {
// 	// 	std::cout << "bin_data " << i << " : " << bin_data[i] << std::endl;
// 	// }

// 	std::cout << "SIMD 512 time : " << sec.count() << std::endl;

// 	_mm_free(bin_data);
// 	_mm_free(ori_data);
// }

void binning_sisd()
{

	DataType *ori_data = new (std::nothrow) DataType[ori_size];
	if(ori_data == nullptr)
	{
		std::cout << "ori_data is nullptr" << std::endl;
		return;
	}
	for(size_t i = 0; i < ori_size; ++i)
	{
		ori_data[i] = i;
	}


	DataType *bin_data = new (std::nothrow) DataType[bin_size];
	if(bin_data == nullptr)
	{
		std::cout << "bin_data is nullptr" << std::endl;
		return;
	}
	for(size_t i = 0; i < bin_size; ++i)
	{
		bin_data[i] = 0;
	}

	start_time = std::chrono::system_clock::now();
	size_t ori_index;
	size_t bin_index;
	for(size_t d = 0; d < bin_depth; d++)
	{
		for(size_t h = 0; h < bin_height; h++)
		{
			for(size_t w = 0; w < bin_width; w++)
			{
				ori_index = d * ori_height * ori_width * bin_depth_level + h * ori_width *  bin_height_level + w * bin_width_level;
				bin_index = d * bin_height * bin_width + h * bin_width + w;

				bin_data[bin_index] = 
					ori_data[ori_index];
			}
		}
	}
	// for(size_t i = 0; i < bin_size; ++i)
	// {
	// 	bin_data[i] = ori_data[i];
	// }
	end_time = std::chrono::system_clock::now();
	sec = end_time - start_time;
	std::cout << "SISD time : " << sec.count() << std::endl;

	// size_t count = 0;
	// for(size_t i = 0; i < bin_size; ++i)
	// {
	// 	if(bin_data[i] == 1)
	// 	{
	// 		++count;
	// 	}
	// }
	// std::cout << "count : " << count << std::endl;
}