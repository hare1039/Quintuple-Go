#include "basic_type.hpp"

namespace quintuple_go
{

std::array<neighbours, MAP_SIZE> const NAB = {
	neighbours{  -1,  -1,   9,  10,   1,  -1 },
	neighbours{  -1,   0,  10,  11,   2,  -1 },
	neighbours{  -1,   1,  11,  12,   3,  -1 },
	neighbours{  -1,   2,  12,  13,   4,  -1 },
	neighbours{  -1,   3,  13,  14,   5,  -1 },
	neighbours{  -1,   4,  14,  15,   6,  -1 },
	neighbours{  -1,   5,  15,  16,   7,  -1 },
	neighbours{  -1,   6,  16,  17,   8,  -1 },
	neighbours{  -1,   7,  17,  18,  -1,  -1 },
	neighbours{  -1,  -1,  19,  20,  10,   0 },
	neighbours{   0,   9,  20,  21,  11,   1 },
	neighbours{   1,  10,  21,  22,  12,   2 },
	neighbours{   2,  11,  22,  23,  13,   3 },
	neighbours{   3,  12,  23,  24,  14,   4 },
	neighbours{   4,  13,  24,  25,  15,   5 },
	neighbours{   5,  14,  25,  26,  16,   6 },
	neighbours{   6,  15,  26,  27,  17,   7 },
	neighbours{   7,  16,  27,  28,  18,   8 },
	neighbours{   8,  17,  28,  29,  -1,  -1 },
	neighbours{  -1,  -1,  30,  31,  20,   9 },
	neighbours{   9,  19,  31,  32,  21,  10 },
	neighbours{  10,  20,  32,  33,  22,  11 },
	neighbours{  11,  21,  33,  34,  23,  12 },
	neighbours{  12,  22,  34,  35,  24,  13 },
	neighbours{  13,  23,  35,  36,  25,  14 },
	neighbours{  14,  24,  36,  37,  26,  15 },
	neighbours{  15,  25,  37,  38,  27,  16 },
	neighbours{  16,  26,  38,  39,  28,  17 },
	neighbours{  17,  27,  39,  40,  29,  18 },
	neighbours{  18,  28,  40,  41,  -1,  -1 },
	neighbours{  -1,  -1,  42,  43,  31,  19 },
	neighbours{  19,  30,  43,  44,  32,  20 },
	neighbours{  20,  31,  44,  45,  33,  21 },
	neighbours{  21,  32,  45,  46,  34,  22 },
	neighbours{  22,  33,  46,  47,  35,  23 },
	neighbours{  23,  34,  47,  48,  36,  24 },
	neighbours{  24,  35,  48,  49,  37,  25 },
	neighbours{  25,  36,  49,  50,  38,  26 },
	neighbours{  26,  37,  50,  51,  39,  27 },
	neighbours{  27,  38,  51,  52,  40,  28 },
	neighbours{  28,  39,  52,  53,  41,  29 },
	neighbours{  29,  40,  53,  54,  -1,  -1 },
	neighbours{  -1,  -1,  55,  56,  43,  30 },
	neighbours{  30,  42,  56,  57,  44,  31 },
	neighbours{  31,  43,  57,  58,  45,  32 },
	neighbours{  32,  44,  58,  59,  46,  33 },
	neighbours{  33,  45,  59,  60,  47,  34 },
	neighbours{  34,  46,  60,  61,  48,  35 },
	neighbours{  35,  47,  61,  62,  49,  36 },
	neighbours{  36,  48,  62,  63,  50,  37 },
	neighbours{  37,  49,  63,  64,  51,  38 },
	neighbours{  38,  50,  64,  65,  52,  39 },
	neighbours{  39,  51,  65,  66,  53,  40 },
	neighbours{  40,  52,  66,  67,  54,  41 },
	neighbours{  41,  53,  67,  68,  -1,  -1 },
	neighbours{  -1,  -1,  69,  70,  56,  42 },
	neighbours{  42,  55,  70,  71,  57,  43 },
	neighbours{  43,  56,  71,  72,  58,  44 },
	neighbours{  44,  57,  72,  73,  59,  45 },
	neighbours{  45,  58,  73,  74,  60,  46 },
	neighbours{  46,  59,  74,  75,  61,  47 },
	neighbours{  47,  60,  75,  76,  62,  48 },
	neighbours{  48,  61,  76,  77,  63,  49 },
	neighbours{  49,  62,  77,  78,  64,  50 },
	neighbours{  50,  63,  78,  79,  65,  51 },
	neighbours{  51,  64,  79,  80,  66,  52 },
	neighbours{  52,  65,  80,  81,  67,  53 },
	neighbours{  53,  66,  81,  82,  68,  54 },
	neighbours{  54,  67,  82,  83,  -1,  -1 },
	neighbours{  -1,  -1,  84,  85,  70,  55 },
	neighbours{  55,  69,  85,  86,  71,  56 },
	neighbours{  56,  70,  86,  87,  72,  57 },
	neighbours{  57,  71,  87,  88,  73,  58 },
	neighbours{  58,  72,  88,  89,  74,  59 },
	neighbours{  59,  73,  89,  90,  75,  60 },
	neighbours{  60,  74,  90,  91,  76,  61 },
	neighbours{  61,  75,  91,  92,  77,  62 },
	neighbours{  62,  76,  92,  93,  78,  63 },
	neighbours{  63,  77,  93,  94,  79,  64 },
	neighbours{  64,  78,  94,  95,  80,  65 },
	neighbours{  65,  79,  95,  96,  81,  66 },
	neighbours{  66,  80,  96,  97,  82,  67 },
	neighbours{  67,  81,  97,  98,  83,  68 },
	neighbours{  68,  82,  98,  99,  -1,  -1 },
	neighbours{  -1,  -1, 100, 101,  85,  69 },
	neighbours{  69,  84, 101, 102,  86,  70 },
	neighbours{  70,  85, 102, 103,  87,  71 },
	neighbours{  71,  86, 103, 104,  88,  72 },
	neighbours{  72,  87, 104, 105,  89,  73 },
	neighbours{  73,  88, 105, 106,  90,  74 },
	neighbours{  74,  89, 106, 107,  91,  75 },
	neighbours{  75,  90, 107, 108,  92,  76 },
	neighbours{  76,  91, 108, 109,  93,  77 },
	neighbours{  77,  92, 109, 110,  94,  78 },
	neighbours{  78,  93, 110, 111,  95,  79 },
	neighbours{  79,  94, 111, 112,  96,  80 },
	neighbours{  80,  95, 112, 113,  97,  81 },
	neighbours{  81,  96, 113, 114,  98,  82 },
	neighbours{  82,  97, 114, 115,  99,  83 },
	neighbours{  83,  98, 115, 116,  -1,  -1 },
	neighbours{  -1,  -1,  -1, 117, 101,  84 },
	neighbours{  84, 100, 117, 118, 102,  85 },
	neighbours{  85, 101, 118, 119, 103,  86 },
	neighbours{  86, 102, 119, 120, 104,  87 },
	neighbours{  87, 103, 120, 121, 105,  88 },
	neighbours{  88, 104, 121, 122, 106,  89 },
	neighbours{  89, 105, 122, 123, 107,  90 },
	neighbours{  90, 106, 123, 124, 108,  91 },
	neighbours{  91, 107, 124, 125, 109,  92 },
	neighbours{  92, 108, 125, 126, 110,  93 },
	neighbours{  93, 109, 126, 127, 111,  94 },
	neighbours{  94, 110, 127, 128, 112,  95 },
	neighbours{  95, 111, 128, 129, 113,  96 },
	neighbours{  96, 112, 129, 130, 114,  97 },
	neighbours{  97, 113, 130, 131, 115,  98 },
	neighbours{  98, 114, 131, 132, 116,  99 },
	neighbours{  99, 115, 132,  -1,  -1,  -1 },
	neighbours{ 100,  -1,  -1, 133, 118, 101 },
	neighbours{ 101, 117, 133, 134, 119, 102 },
	neighbours{ 102, 118, 134, 135, 120, 103 },
	neighbours{ 103, 119, 135, 136, 121, 104 },
	neighbours{ 104, 120, 136, 137, 122, 105 },
	neighbours{ 105, 121, 137, 138, 123, 106 },
	neighbours{ 106, 122, 138, 139, 124, 107 },
	neighbours{ 107, 123, 139, 140, 125, 108 },
	neighbours{ 108, 124, 140, 141, 126, 109 },
	neighbours{ 109, 125, 141, 142, 127, 110 },
	neighbours{ 110, 126, 142, 143, 128, 111 },
	neighbours{ 111, 127, 143, 144, 129, 112 },
	neighbours{ 112, 128, 144, 145, 130, 113 },
	neighbours{ 113, 129, 145, 146, 131, 114 },
	neighbours{ 114, 130, 146, 147, 132, 115 },
	neighbours{ 115, 131, 147,  -1,  -1, 116 },
	neighbours{ 117,  -1,  -1, 148, 134, 118 },
	neighbours{ 118, 133, 148, 149, 135, 119 },
	neighbours{ 119, 134, 149, 150, 136, 120 },
	neighbours{ 120, 135, 150, 151, 137, 121 },
	neighbours{ 121, 136, 151, 152, 138, 122 },
	neighbours{ 122, 137, 152, 153, 139, 123 },
	neighbours{ 123, 138, 153, 154, 140, 124 },
	neighbours{ 124, 139, 154, 155, 141, 125 },
	neighbours{ 125, 140, 155, 156, 142, 126 },
	neighbours{ 126, 141, 156, 157, 143, 127 },
	neighbours{ 127, 142, 157, 158, 144, 128 },
	neighbours{ 128, 143, 158, 159, 145, 129 },
	neighbours{ 129, 144, 159, 160, 146, 130 },
	neighbours{ 130, 145, 160, 161, 147, 131 },
	neighbours{ 131, 146, 161,  -1,  -1, 132 },
	neighbours{ 133,  -1,  -1, 162, 149, 134 },
	neighbours{ 134, 148, 162, 163, 150, 135 },
	neighbours{ 135, 149, 163, 164, 151, 136 },
	neighbours{ 136, 150, 164, 165, 152, 137 },
	neighbours{ 137, 151, 165, 166, 153, 138 },
	neighbours{ 138, 152, 166, 167, 154, 139 },
	neighbours{ 139, 153, 167, 168, 155, 140 },
	neighbours{ 140, 154, 168, 169, 156, 141 },
	neighbours{ 141, 155, 169, 170, 157, 142 },
	neighbours{ 142, 156, 170, 171, 158, 143 },
	neighbours{ 143, 157, 171, 172, 159, 144 },
	neighbours{ 144, 158, 172, 173, 160, 145 },
	neighbours{ 145, 159, 173, 174, 161, 146 },
	neighbours{ 146, 160, 174,  -1,  -1, 147 },
	neighbours{ 148,  -1,  -1, 175, 163, 149 },
	neighbours{ 149, 162, 175, 176, 164, 150 },
	neighbours{ 150, 163, 176, 177, 165, 151 },
	neighbours{ 151, 164, 177, 178, 166, 152 },
	neighbours{ 152, 165, 178, 179, 167, 153 },
	neighbours{ 153, 166, 179, 180, 168, 154 },
	neighbours{ 154, 167, 180, 181, 169, 155 },
	neighbours{ 155, 168, 181, 182, 170, 156 },
	neighbours{ 156, 169, 182, 183, 171, 157 },
	neighbours{ 157, 170, 183, 184, 172, 158 },
	neighbours{ 158, 171, 184, 185, 173, 159 },
	neighbours{ 159, 172, 185, 186, 174, 160 },
	neighbours{ 160, 173, 186,  -1,  -1, 161 },
	neighbours{ 162,  -1,  -1, 187, 176, 163 },
	neighbours{ 163, 175, 187, 188, 177, 164 },
	neighbours{ 164, 176, 188, 189, 178, 165 },
	neighbours{ 165, 177, 189, 190, 179, 166 },
	neighbours{ 166, 178, 190, 191, 180, 167 },
	neighbours{ 167, 179, 191, 192, 181, 168 },
	neighbours{ 168, 180, 192, 193, 182, 169 },
	neighbours{ 169, 181, 193, 194, 183, 170 },
	neighbours{ 170, 182, 194, 195, 184, 171 },
	neighbours{ 171, 183, 195, 196, 185, 172 },
	neighbours{ 172, 184, 196, 197, 186, 173 },
	neighbours{ 173, 185, 197,  -1,  -1, 174 },
	neighbours{ 175,  -1,  -1, 198, 188, 176 },
	neighbours{ 176, 187, 198, 199, 189, 177 },
	neighbours{ 177, 188, 199, 200, 190, 178 },
	neighbours{ 178, 189, 200, 201, 191, 179 },
	neighbours{ 179, 190, 201, 202, 192, 180 },
	neighbours{ 180, 191, 202, 203, 193, 181 },
	neighbours{ 181, 192, 203, 204, 194, 182 },
	neighbours{ 182, 193, 204, 205, 195, 183 },
	neighbours{ 183, 194, 205, 206, 196, 184 },
	neighbours{ 184, 195, 206, 207, 197, 185 },
	neighbours{ 185, 196, 207,  -1,  -1, 186 },
	neighbours{ 187,  -1,  -1, 208, 199, 188 },
	neighbours{ 188, 198, 208, 209, 200, 189 },
	neighbours{ 189, 199, 209, 210, 201, 190 },
	neighbours{ 190, 200, 210, 211, 202, 191 },
	neighbours{ 191, 201, 211, 212, 203, 192 },
	neighbours{ 192, 202, 212, 213, 204, 193 },
	neighbours{ 193, 203, 213, 214, 205, 194 },
	neighbours{ 194, 204, 214, 215, 206, 195 },
	neighbours{ 195, 205, 215, 216, 207, 196 },
	neighbours{ 196, 206, 216,  -1,  -1, 197 },
	neighbours{ 198,  -1,  -1,  -1, 209, 199 },
	neighbours{ 199, 208,  -1,  -1, 210, 200 },
	neighbours{ 200, 209,  -1,  -1, 211, 201 },
	neighbours{ 201, 210,  -1,  -1, 212, 202 },
	neighbours{ 202, 211,  -1,  -1, 213, 203 },
	neighbours{ 203, 212,  -1,  -1, 214, 204 },
	neighbours{ 204, 213,  -1,  -1, 215, 205 },
	neighbours{ 205, 214,  -1,  -1, 216, 206 },
	neighbours{ 206, 215,  -1,  -1,  -1, 207 }
};

std::array<int, 9> const RATE = {0, 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000};

bool random_break(double p)
{
	static std::mt19937 eng{std::random_device{}()};
	std::uniform_int_distribution<int> dist(0, 100);
	return dist(eng) < 100 * p;
}

int random_in(int max)
{
	static std::mt19937 eng{std::random_device{}()};
	std::uniform_int_distribution<int> dist(0, max);
	return dist(eng);
}

}
