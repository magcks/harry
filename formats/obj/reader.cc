
#line 1 "formats/obj/reader.rl"
/*
 * Copyright (C) 2017, Max von Buelow
 * TU Darmstadt - Graphics, Capture and Massively Parallel Computing
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD 3-Clause license. See the LICENSE.txt file for details.
 */

#include <stdexcept>
#include <vector>
#include <string>
#include <cmath>

#include "reader.h"

#include "structs/mixing.h"
#include "structs/types.h"
#include "structs/quant.h"
#include "utils/io.h"
#include "utils/progress.h"

#define BUFSIZE 16384


#line 74 "formats/obj/reader.rl"


namespace obj {
namespace reader {


#line 36 "/home/max/repos/harry/formats/obj/reader.cc"
static const char _ObjParser_actions[] = {
	0, 1, 0, 1, 2, 1, 3, 1, 
	4, 1, 12, 1, 18, 1, 19, 1, 
	20, 1, 21, 1, 22, 1, 23, 1, 
	24, 2, 0, 1, 2, 0, 3, 2, 
	6, 17, 2, 7, 17, 2, 8, 17, 
	2, 9, 10, 2, 11, 12, 2, 13, 
	14, 2, 13, 15, 2, 13, 16, 2, 
	18, 0, 2, 19, 24, 2, 20, 24, 
	2, 21, 24, 2, 23, 24, 3, 5, 
	6, 17, 3, 9, 11, 12, 3, 13, 
	15, 16, 3, 18, 0, 1, 3, 18, 
	0, 3
};

static const short _ObjParser_key_offsets[] = {
	0, 0, 4, 5, 7, 9, 14, 16, 
	21, 26, 28, 35, 42, 44, 45, 46, 
	47, 48, 49, 50, 51, 52, 53, 54, 
	58, 69, 72, 74, 80, 91, 94, 96, 
	102, 113, 116, 118, 126, 139, 140, 143, 
	145, 153, 166, 169, 171, 177, 188, 191, 
	193, 201, 214, 217, 219, 227, 240, 243, 
	245, 253, 257, 259, 261, 267, 276, 278, 
	280, 286, 288, 290, 292, 294, 298, 300, 
	302, 306, 308, 310, 316, 325, 327, 329, 
	335, 337, 339, 341, 343, 347, 349, 351, 
	355, 357, 359, 365, 374, 376, 378, 384, 
	386, 388, 390, 392, 396, 398, 400, 404, 
	406, 408, 412, 419, 421, 423, 427, 429, 
	431, 433, 435, 437, 439, 441, 443, 445, 
	447, 453, 462, 464, 466, 472, 474, 476, 
	478, 480, 484, 486, 488, 492, 494, 496, 
	502, 511, 513, 515, 521, 523, 525, 527, 
	529, 533, 535, 537, 541, 543, 545, 549, 
	556, 558, 560, 564, 566, 568, 570, 572, 
	574, 576, 578, 580, 582, 584, 588, 595, 
	597, 599, 603, 605, 607, 609, 611, 613, 
	615, 617, 619, 621, 632, 635, 637, 643, 
	654, 657, 659, 665, 676, 679, 681, 689, 
	693, 694, 696, 698, 704, 713, 715, 717, 
	723, 725, 727, 729, 731, 735, 737, 739, 
	743, 745, 747, 751, 758, 760, 762, 766, 
	768, 770, 772, 774, 776, 778, 780, 782, 
	784, 786, 790, 797, 799, 801, 805, 807, 
	809, 811, 813, 815, 817, 819, 821, 823, 
	834, 837, 839, 845, 856, 859, 861, 869, 
	882, 883, 886, 888, 896, 900, 902, 904, 
	910, 919, 921, 923, 929, 931, 933, 935, 
	937, 941, 943, 945, 949, 951, 953, 959, 
	968, 970, 972, 978, 980, 982, 984, 986, 
	990, 992, 994, 998, 1000, 1002, 1006, 1013, 
	1015, 1017, 1021, 1023, 1025, 1027, 1029, 1031, 
	1033, 1035, 1037, 1038, 1046, 1048, 1055, 1062, 
	1064, 1070, 1076, 1078, 1083, 1088, 1090, 1094, 
	1106, 1118, 1130, 1142
};

static const char _ObjParser_trans_keys[] = {
	9, 10, 13, 32, 10, 10, 13, 9, 
	32, 9, 32, 45, 48, 57, 48, 57, 
	9, 32, 47, 48, 57, 9, 32, 45, 
	48, 57, 48, 57, 9, 10, 13, 32, 
	47, 48, 57, 9, 10, 13, 32, 45, 
	48, 57, 9, 32, 116, 108, 108, 105, 
	98, 115, 101, 109, 116, 108, 9, 32, 
	110, 116, 9, 32, 43, 45, 46, 73, 
	78, 105, 110, 48, 57, 46, 48, 57, 
	48, 57, 9, 32, 69, 101, 48, 57, 
	9, 32, 43, 45, 46, 73, 78, 105, 
	110, 48, 57, 46, 48, 57, 48, 57, 
	9, 32, 69, 101, 48, 57, 9, 32, 
	43, 45, 46, 73, 78, 105, 110, 48, 
	57, 46, 48, 57, 48, 57, 9, 10, 
	13, 32, 69, 101, 48, 57, 9, 10, 
	13, 32, 43, 45, 46, 73, 78, 105, 
	110, 48, 57, 10, 46, 48, 57, 48, 
	57, 9, 10, 13, 32, 69, 101, 48, 
	57, 9, 10, 13, 32, 43, 45, 46, 
	73, 78, 105, 110, 48, 57, 46, 48, 
	57, 48, 57, 9, 32, 69, 101, 48, 
	57, 9, 32, 43, 45, 46, 73, 78, 
	105, 110, 48, 57, 46, 48, 57, 48, 
	57, 9, 10, 13, 32, 69, 101, 48, 
	57, 9, 10, 13, 32, 43, 45, 46, 
	73, 78, 105, 110, 48, 57, 46, 48, 
	57, 48, 57, 9, 10, 13, 32, 69, 
	101, 48, 57, 9, 10, 13, 32, 43, 
	45, 46, 73, 78, 105, 110, 48, 57, 
	46, 48, 57, 48, 57, 9, 10, 13, 
	32, 69, 101, 48, 57, 9, 10, 13, 
	32, 43, 45, 48, 57, 9, 10, 13, 
	32, 48, 57, 9, 10, 13, 32, 46, 
	69, 101, 48, 57, 78, 110, 70, 102, 
	9, 10, 13, 32, 73, 105, 78, 110, 
	73, 105, 84, 116, 89, 121, 9, 10, 
	13, 32, 65, 97, 78, 110, 9, 10, 
	13, 32, 43, 45, 48, 57, 9, 10, 
	13, 32, 48, 57, 9, 10, 13, 32, 
	46, 69, 101, 48, 57, 78, 110, 70, 
	102, 9, 10, 13, 32, 73, 105, 78, 
	110, 73, 105, 84, 116, 89, 121, 9, 
	10, 13, 32, 65, 97, 78, 110, 9, 
	10, 13, 32, 43, 45, 48, 57, 9, 
	10, 13, 32, 48, 57, 9, 10, 13, 
	32, 46, 69, 101, 48, 57, 78, 110, 
	70, 102, 9, 10, 13, 32, 73, 105, 
	78, 110, 73, 105, 84, 116, 89, 121, 
	9, 10, 13, 32, 65, 97, 78, 110, 
	9, 10, 13, 32, 43, 45, 48, 57, 
	9, 32, 48, 57, 9, 32, 46, 69, 
	101, 48, 57, 78, 110, 70, 102, 9, 
	32, 73, 105, 78, 110, 73, 105, 84, 
	116, 89, 121, 9, 32, 65, 97, 78, 
	110, 9, 32, 43, 45, 48, 57, 9, 
	10, 13, 32, 48, 57, 9, 10, 13, 
	32, 46, 69, 101, 48, 57, 78, 110, 
	70, 102, 9, 10, 13, 32, 73, 105, 
	78, 110, 73, 105, 84, 116, 89, 121, 
	9, 10, 13, 32, 65, 97, 78, 110, 
	9, 10, 13, 32, 43, 45, 48, 57, 
	9, 10, 13, 32, 48, 57, 9, 10, 
	13, 32, 46, 69, 101, 48, 57, 78, 
	110, 70, 102, 9, 10, 13, 32, 73, 
	105, 78, 110, 73, 105, 84, 116, 89, 
	121, 9, 10, 13, 32, 65, 97, 78, 
	110, 9, 10, 13, 32, 43, 45, 48, 
	57, 9, 32, 48, 57, 9, 32, 46, 
	69, 101, 48, 57, 78, 110, 70, 102, 
	9, 32, 73, 105, 78, 110, 73, 105, 
	84, 116, 89, 121, 9, 32, 65, 97, 
	78, 110, 9, 32, 43, 45, 48, 57, 
	9, 32, 48, 57, 9, 32, 46, 69, 
	101, 48, 57, 78, 110, 70, 102, 9, 
	32, 73, 105, 78, 110, 73, 105, 84, 
	116, 89, 121, 9, 32, 65, 97, 78, 
	110, 9, 32, 9, 32, 9, 32, 43, 
	45, 46, 73, 78, 105, 110, 48, 57, 
	46, 48, 57, 48, 57, 9, 32, 69, 
	101, 48, 57, 9, 32, 43, 45, 46, 
	73, 78, 105, 110, 48, 57, 46, 48, 
	57, 48, 57, 9, 32, 69, 101, 48, 
	57, 9, 32, 43, 45, 46, 73, 78, 
	105, 110, 48, 57, 46, 48, 57, 48, 
	57, 9, 10, 13, 32, 69, 101, 48, 
	57, 9, 10, 13, 32, 10, 43, 45, 
	48, 57, 9, 10, 13, 32, 48, 57, 
	9, 10, 13, 32, 46, 69, 101, 48, 
	57, 78, 110, 70, 102, 9, 10, 13, 
	32, 73, 105, 78, 110, 73, 105, 84, 
	116, 89, 121, 9, 10, 13, 32, 65, 
	97, 78, 110, 9, 10, 13, 32, 43, 
	45, 48, 57, 9, 32, 48, 57, 9, 
	32, 46, 69, 101, 48, 57, 78, 110, 
	70, 102, 9, 32, 73, 105, 78, 110, 
	73, 105, 84, 116, 89, 121, 9, 32, 
	65, 97, 78, 110, 9, 32, 43, 45, 
	48, 57, 9, 32, 48, 57, 9, 32, 
	46, 69, 101, 48, 57, 78, 110, 70, 
	102, 9, 32, 73, 105, 78, 110, 73, 
	105, 84, 116, 89, 121, 9, 32, 65, 
	97, 78, 110, 9, 32, 9, 32, 9, 
	32, 43, 45, 46, 73, 78, 105, 110, 
	48, 57, 46, 48, 57, 48, 57, 9, 
	32, 69, 101, 48, 57, 9, 32, 43, 
	45, 46, 73, 78, 105, 110, 48, 57, 
	46, 48, 57, 48, 57, 9, 10, 13, 
	32, 69, 101, 48, 57, 9, 10, 13, 
	32, 43, 45, 46, 73, 78, 105, 110, 
	48, 57, 10, 46, 48, 57, 48, 57, 
	9, 10, 13, 32, 69, 101, 48, 57, 
	9, 10, 13, 32, 43, 45, 48, 57, 
	9, 10, 13, 32, 48, 57, 9, 10, 
	13, 32, 46, 69, 101, 48, 57, 78, 
	110, 70, 102, 9, 10, 13, 32, 73, 
	105, 78, 110, 73, 105, 84, 116, 89, 
	121, 9, 10, 13, 32, 65, 97, 78, 
	110, 9, 10, 13, 32, 43, 45, 48, 
	57, 9, 10, 13, 32, 48, 57, 9, 
	10, 13, 32, 46, 69, 101, 48, 57, 
	78, 110, 70, 102, 9, 10, 13, 32, 
	73, 105, 78, 110, 73, 105, 84, 116, 
	89, 121, 9, 10, 13, 32, 65, 97, 
	78, 110, 9, 10, 13, 32, 43, 45, 
	48, 57, 9, 32, 48, 57, 9, 32, 
	46, 69, 101, 48, 57, 78, 110, 70, 
	102, 9, 32, 73, 105, 78, 110, 73, 
	105, 84, 116, 89, 121, 9, 32, 65, 
	97, 78, 110, 9, 32, 10, 9, 10, 
	13, 32, 45, 47, 48, 57, 48, 57, 
	9, 10, 13, 32, 47, 48, 57, 9, 
	10, 13, 32, 45, 48, 57, 48, 57, 
	9, 10, 13, 32, 48, 57, 9, 32, 
	45, 47, 48, 57, 48, 57, 9, 32, 
	47, 48, 57, 9, 32, 45, 48, 57, 
	48, 57, 9, 32, 48, 57, 9, 10, 
	13, 32, 35, 102, 103, 109, 111, 115, 
	117, 118, 9, 10, 13, 32, 35, 102, 
	103, 109, 111, 115, 117, 118, 9, 10, 
	13, 32, 35, 102, 103, 109, 111, 115, 
	117, 118, 9, 10, 13, 32, 35, 102, 
	103, 109, 111, 115, 117, 118, 9, 10, 
	13, 32, 35, 102, 103, 109, 111, 115, 
	117, 118, 0
};

static const char _ObjParser_single_lengths[] = {
	0, 4, 1, 2, 2, 3, 0, 3, 
	3, 0, 5, 5, 2, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 4, 
	9, 1, 0, 4, 9, 1, 0, 4, 
	9, 1, 0, 6, 11, 1, 1, 0, 
	6, 11, 1, 0, 4, 9, 1, 0, 
	6, 11, 1, 0, 6, 11, 1, 0, 
	6, 4, 2, 0, 4, 7, 2, 2, 
	6, 2, 2, 2, 2, 4, 2, 2, 
	4, 2, 0, 4, 7, 2, 2, 6, 
	2, 2, 2, 2, 4, 2, 2, 4, 
	2, 0, 4, 7, 2, 2, 6, 2, 
	2, 2, 2, 4, 2, 2, 4, 2, 
	0, 2, 5, 2, 2, 4, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 0, 
	4, 7, 2, 2, 6, 2, 2, 2, 
	2, 4, 2, 2, 4, 2, 0, 4, 
	7, 2, 2, 6, 2, 2, 2, 2, 
	4, 2, 2, 4, 2, 0, 2, 5, 
	2, 2, 4, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 0, 2, 5, 2, 
	2, 4, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 9, 1, 0, 4, 9, 
	1, 0, 4, 9, 1, 0, 6, 4, 
	1, 2, 0, 4, 7, 2, 2, 6, 
	2, 2, 2, 2, 4, 2, 2, 4, 
	2, 0, 2, 5, 2, 2, 4, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	0, 2, 5, 2, 2, 4, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 9, 
	1, 0, 4, 9, 1, 0, 6, 11, 
	1, 1, 0, 6, 4, 2, 0, 4, 
	7, 2, 2, 6, 2, 2, 2, 2, 
	4, 2, 2, 4, 2, 0, 4, 7, 
	2, 2, 6, 2, 2, 2, 2, 4, 
	2, 2, 4, 2, 0, 2, 5, 2, 
	2, 4, 2, 2, 2, 2, 2, 2, 
	2, 2, 1, 6, 0, 5, 5, 0, 
	4, 4, 0, 3, 3, 0, 2, 12, 
	12, 12, 12, 12
};

static const char _ObjParser_range_lengths[] = {
	0, 0, 0, 0, 0, 1, 1, 1, 
	1, 1, 1, 1, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 0, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 0, 0, 1, 1, 1, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 1, 1, 1, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 1, 1, 1, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	1, 1, 1, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 1, 
	1, 1, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 1, 1, 
	1, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 1, 1, 1, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 1, 1, 1, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 0, 
	0, 0, 1, 1, 1, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 1, 1, 1, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	1, 1, 1, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	0, 1, 1, 1, 0, 0, 1, 1, 
	1, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 1, 1, 1, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 1, 1, 1, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 0, 
	0, 0, 0, 0
};

static const short _ObjParser_index_offsets[] = {
	0, 0, 5, 7, 10, 13, 18, 20, 
	25, 30, 32, 39, 46, 49, 51, 53, 
	55, 57, 59, 61, 63, 65, 67, 69, 
	74, 85, 88, 90, 96, 107, 110, 112, 
	118, 129, 132, 134, 142, 155, 157, 160, 
	162, 170, 183, 186, 188, 194, 205, 208, 
	210, 218, 231, 234, 236, 244, 257, 260, 
	262, 270, 275, 278, 280, 286, 295, 298, 
	301, 308, 311, 314, 317, 320, 325, 328, 
	331, 336, 339, 341, 347, 356, 359, 362, 
	369, 372, 375, 378, 381, 386, 389, 392, 
	397, 400, 402, 408, 417, 420, 423, 430, 
	433, 436, 439, 442, 447, 450, 453, 458, 
	461, 463, 467, 474, 477, 480, 485, 488, 
	491, 494, 497, 500, 503, 506, 509, 512, 
	514, 520, 529, 532, 535, 542, 545, 548, 
	551, 554, 559, 562, 565, 570, 573, 575, 
	581, 590, 593, 596, 603, 606, 609, 612, 
	615, 620, 623, 626, 631, 634, 636, 640, 
	647, 650, 653, 658, 661, 664, 667, 670, 
	673, 676, 679, 682, 685, 687, 691, 698, 
	701, 704, 709, 712, 715, 718, 721, 724, 
	727, 730, 733, 736, 747, 750, 752, 758, 
	769, 772, 774, 780, 791, 794, 796, 804, 
	809, 811, 814, 816, 822, 831, 834, 837, 
	844, 847, 850, 853, 856, 861, 864, 867, 
	872, 875, 877, 881, 888, 891, 894, 899, 
	902, 905, 908, 911, 914, 917, 920, 923, 
	926, 928, 932, 939, 942, 945, 950, 953, 
	956, 959, 962, 965, 968, 971, 974, 977, 
	988, 991, 993, 999, 1010, 1013, 1015, 1023, 
	1036, 1038, 1041, 1043, 1051, 1056, 1059, 1061, 
	1067, 1076, 1079, 1082, 1089, 1092, 1095, 1098, 
	1101, 1106, 1109, 1112, 1117, 1120, 1122, 1128, 
	1137, 1140, 1143, 1150, 1153, 1156, 1159, 1162, 
	1167, 1170, 1173, 1178, 1181, 1183, 1187, 1194, 
	1197, 1200, 1205, 1208, 1211, 1214, 1217, 1220, 
	1223, 1226, 1229, 1231, 1239, 1241, 1248, 1255, 
	1257, 1263, 1269, 1271, 1276, 1281, 1283, 1287, 
	1300, 1313, 1326, 1339
};

static const short _ObjParser_trans_targs[] = {
	1, 311, 2, 1, 0, 311, 0, 311, 
	2, 3, 5, 5, 0, 5, 5, 6, 
	7, 0, 7, 0, 8, 8, 305, 7, 
	0, 8, 8, 9, 10, 0, 10, 0, 
	11, 312, 298, 11, 299, 10, 0, 11, 
	312, 298, 11, 9, 10, 0, 3, 3, 
	0, 14, 0, 15, 0, 16, 0, 17, 
	0, 12, 0, 19, 0, 20, 0, 21, 
	0, 22, 0, 12, 0, 24, 24, 178, 
	238, 0, 24, 24, 25, 25, 26, 167, 
	175, 167, 175, 166, 0, 26, 166, 0, 
	27, 0, 28, 28, 163, 163, 27, 0, 
	28, 28, 29, 29, 30, 152, 160, 152, 
	160, 151, 0, 30, 151, 0, 31, 0, 
	32, 32, 148, 148, 31, 0, 32, 32, 
	33, 33, 34, 137, 145, 137, 145, 136, 
	0, 34, 136, 0, 35, 0, 36, 313, 
	37, 36, 133, 133, 35, 0, 36, 313, 
	37, 36, 38, 38, 39, 122, 130, 122, 
	130, 121, 0, 313, 0, 39, 121, 0, 
	40, 0, 41, 313, 37, 41, 118, 118, 
	40, 0, 41, 313, 37, 41, 42, 42, 
	43, 107, 115, 107, 115, 106, 0, 43, 
	106, 0, 44, 0, 45, 45, 103, 103, 
	44, 0, 45, 45, 46, 46, 47, 92, 
	100, 92, 100, 91, 0, 47, 91, 0, 
	48, 0, 49, 313, 37, 49, 88, 88, 
	48, 0, 49, 313, 37, 49, 50, 50, 
	51, 77, 85, 77, 85, 76, 0, 51, 
	76, 0, 52, 0, 53, 313, 37, 53, 
	73, 73, 52, 0, 53, 313, 37, 53, 
	54, 54, 55, 62, 70, 62, 70, 61, 
	0, 55, 61, 0, 56, 0, 57, 313, 
	37, 57, 58, 58, 56, 0, 57, 313, 
	37, 57, 0, 59, 59, 0, 60, 0, 
	57, 313, 37, 57, 60, 0, 57, 313, 
	37, 57, 56, 58, 58, 61, 0, 63, 
	63, 0, 64, 64, 0, 57, 313, 37, 
	57, 65, 65, 0, 66, 66, 0, 67, 
	67, 0, 68, 68, 0, 69, 69, 0, 
	57, 313, 37, 57, 0, 71, 71, 0, 
	72, 72, 0, 57, 313, 37, 57, 0, 
	74, 74, 0, 75, 0, 53, 313, 37, 
	53, 75, 0, 53, 313, 37, 53, 52, 
	73, 73, 76, 0, 78, 78, 0, 79, 
	79, 0, 53, 313, 37, 53, 80, 80, 
	0, 81, 81, 0, 82, 82, 0, 83, 
	83, 0, 84, 84, 0, 53, 313, 37, 
	53, 0, 86, 86, 0, 87, 87, 0, 
	53, 313, 37, 53, 0, 89, 89, 0, 
	90, 0, 49, 313, 37, 49, 90, 0, 
	49, 313, 37, 49, 48, 88, 88, 91, 
	0, 93, 93, 0, 94, 94, 0, 49, 
	313, 37, 49, 95, 95, 0, 96, 96, 
	0, 97, 97, 0, 98, 98, 0, 99, 
	99, 0, 49, 313, 37, 49, 0, 101, 
	101, 0, 102, 102, 0, 49, 313, 37, 
	49, 0, 104, 104, 0, 105, 0, 45, 
	45, 105, 0, 45, 45, 44, 103, 103, 
	106, 0, 108, 108, 0, 109, 109, 0, 
	45, 45, 110, 110, 0, 111, 111, 0, 
	112, 112, 0, 113, 113, 0, 114, 114, 
	0, 45, 45, 0, 116, 116, 0, 117, 
	117, 0, 45, 45, 0, 119, 119, 0, 
	120, 0, 41, 313, 37, 41, 120, 0, 
	41, 313, 37, 41, 40, 118, 118, 121, 
	0, 123, 123, 0, 124, 124, 0, 41, 
	313, 37, 41, 125, 125, 0, 126, 126, 
	0, 127, 127, 0, 128, 128, 0, 129, 
	129, 0, 41, 313, 37, 41, 0, 131, 
	131, 0, 132, 132, 0, 41, 313, 37, 
	41, 0, 134, 134, 0, 135, 0, 36, 
	313, 37, 36, 135, 0, 36, 313, 37, 
	36, 35, 133, 133, 136, 0, 138, 138, 
	0, 139, 139, 0, 36, 313, 37, 36, 
	140, 140, 0, 141, 141, 0, 142, 142, 
	0, 143, 143, 0, 144, 144, 0, 36, 
	313, 37, 36, 0, 146, 146, 0, 147, 
	147, 0, 36, 313, 37, 36, 0, 149, 
	149, 0, 150, 0, 32, 32, 150, 0, 
	32, 32, 31, 148, 148, 151, 0, 153, 
	153, 0, 154, 154, 0, 32, 32, 155, 
	155, 0, 156, 156, 0, 157, 157, 0, 
	158, 158, 0, 159, 159, 0, 32, 32, 
	0, 161, 161, 0, 162, 162, 0, 32, 
	32, 0, 164, 164, 0, 165, 0, 28, 
	28, 165, 0, 28, 28, 27, 163, 163, 
	166, 0, 168, 168, 0, 169, 169, 0, 
	28, 28, 170, 170, 0, 171, 171, 0, 
	172, 172, 0, 173, 173, 0, 174, 174, 
	0, 28, 28, 0, 176, 176, 0, 177, 
	177, 0, 28, 28, 0, 179, 179, 0, 
	179, 179, 180, 180, 181, 227, 235, 227, 
	235, 226, 0, 181, 226, 0, 182, 0, 
	183, 183, 223, 223, 182, 0, 183, 183, 
	184, 184, 185, 212, 220, 212, 220, 211, 
	0, 185, 211, 0, 186, 0, 187, 187, 
	208, 208, 186, 0, 187, 187, 188, 188, 
	189, 197, 205, 197, 205, 196, 0, 189, 
	196, 0, 190, 0, 191, 314, 192, 191, 
	193, 193, 190, 0, 191, 314, 192, 191, 
	0, 314, 0, 194, 194, 0, 195, 0, 
	191, 314, 192, 191, 195, 0, 191, 314, 
	192, 191, 190, 193, 193, 196, 0, 198, 
	198, 0, 199, 199, 0, 191, 314, 192, 
	191, 200, 200, 0, 201, 201, 0, 202, 
	202, 0, 203, 203, 0, 204, 204, 0, 
	191, 314, 192, 191, 0, 206, 206, 0, 
	207, 207, 0, 191, 314, 192, 191, 0, 
	209, 209, 0, 210, 0, 187, 187, 210, 
	0, 187, 187, 186, 208, 208, 211, 0, 
	213, 213, 0, 214, 214, 0, 187, 187, 
	215, 215, 0, 216, 216, 0, 217, 217, 
	0, 218, 218, 0, 219, 219, 0, 187, 
	187, 0, 221, 221, 0, 222, 222, 0, 
	187, 187, 0, 224, 224, 0, 225, 0, 
	183, 183, 225, 0, 183, 183, 182, 223, 
	223, 226, 0, 228, 228, 0, 229, 229, 
	0, 183, 183, 230, 230, 0, 231, 231, 
	0, 232, 232, 0, 233, 233, 0, 234, 
	234, 0, 183, 183, 0, 236, 236, 0, 
	237, 237, 0, 183, 183, 0, 239, 239, 
	0, 239, 239, 240, 240, 241, 287, 295, 
	287, 295, 286, 0, 241, 286, 0, 242, 
	0, 243, 243, 283, 283, 242, 0, 243, 
	243, 244, 244, 245, 272, 280, 272, 280, 
	271, 0, 245, 271, 0, 246, 0, 247, 
	315, 248, 247, 268, 268, 246, 0, 247, 
	315, 248, 247, 249, 249, 250, 257, 265, 
	257, 265, 256, 0, 315, 0, 250, 256, 
	0, 251, 0, 252, 315, 248, 252, 253, 
	253, 251, 0, 252, 315, 248, 252, 0, 
	254, 254, 0, 255, 0, 252, 315, 248, 
	252, 255, 0, 252, 315, 248, 252, 251, 
	253, 253, 256, 0, 258, 258, 0, 259, 
	259, 0, 252, 315, 248, 252, 260, 260, 
	0, 261, 261, 0, 262, 262, 0, 263, 
	263, 0, 264, 264, 0, 252, 315, 248, 
	252, 0, 266, 266, 0, 267, 267, 0, 
	252, 315, 248, 252, 0, 269, 269, 0, 
	270, 0, 247, 315, 248, 247, 270, 0, 
	247, 315, 248, 247, 246, 268, 268, 271, 
	0, 273, 273, 0, 274, 274, 0, 247, 
	315, 248, 247, 275, 275, 0, 276, 276, 
	0, 277, 277, 0, 278, 278, 0, 279, 
	279, 0, 247, 315, 248, 247, 0, 281, 
	281, 0, 282, 282, 0, 247, 315, 248, 
	247, 0, 284, 284, 0, 285, 0, 243, 
	243, 285, 0, 243, 243, 242, 283, 283, 
	286, 0, 288, 288, 0, 289, 289, 0, 
	243, 243, 290, 290, 0, 291, 291, 0, 
	292, 292, 0, 293, 293, 0, 294, 294, 
	0, 243, 243, 0, 296, 296, 0, 297, 
	297, 0, 243, 243, 0, 312, 0, 11, 
	312, 298, 11, 300, 302, 301, 0, 301, 
	0, 11, 312, 298, 11, 302, 301, 0, 
	11, 312, 298, 11, 303, 304, 0, 304, 
	0, 11, 312, 298, 11, 304, 0, 8, 
	8, 306, 308, 307, 0, 307, 0, 8, 
	8, 308, 307, 0, 8, 8, 309, 310, 
	0, 310, 0, 8, 8, 310, 0, 1, 
	311, 2, 1, 3, 4, 12, 13, 12, 
	12, 18, 23, 0, 1, 311, 2, 1, 
	3, 4, 12, 13, 12, 12, 18, 23, 
	0, 1, 311, 2, 1, 3, 4, 12, 
	13, 12, 12, 18, 23, 0, 1, 311, 
	2, 1, 3, 4, 12, 13, 12, 12, 
	18, 23, 0, 1, 311, 2, 1, 3, 
	4, 12, 13, 12, 12, 18, 23, 0, 
	0
};

static const char _ObjParser_trans_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 19, 19, 0, 19, 19, 40, 
	74, 0, 43, 0, 46, 46, 46, 9, 
	0, 0, 0, 40, 74, 0, 43, 0, 
	46, 46, 46, 46, 46, 9, 0, 0, 
	0, 0, 0, 40, 74, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 11, 11, 0, 
	0, 0, 0, 0, 25, 25, 1, 0, 
	0, 0, 0, 28, 0, 0, 5, 0, 
	3, 0, 31, 31, 0, 0, 3, 0, 
	0, 0, 25, 25, 1, 0, 0, 0, 
	0, 28, 0, 0, 5, 0, 3, 0, 
	31, 31, 0, 0, 3, 0, 0, 0, 
	25, 25, 1, 0, 0, 0, 0, 28, 
	0, 0, 5, 0, 3, 0, 31, 31, 
	31, 31, 0, 0, 3, 0, 0, 0, 
	0, 0, 25, 25, 1, 0, 0, 0, 
	0, 28, 0, 0, 0, 0, 5, 0, 
	3, 0, 31, 31, 31, 31, 0, 0, 
	3, 0, 0, 0, 0, 0, 25, 25, 
	1, 0, 0, 0, 0, 28, 0, 0, 
	5, 0, 3, 0, 31, 31, 0, 0, 
	3, 0, 0, 0, 25, 25, 1, 0, 
	0, 0, 0, 28, 0, 0, 5, 0, 
	3, 0, 31, 31, 31, 31, 0, 0, 
	3, 0, 0, 0, 0, 0, 25, 25, 
	1, 0, 0, 0, 0, 28, 0, 0, 
	5, 0, 3, 0, 31, 31, 31, 31, 
	0, 0, 3, 0, 0, 0, 0, 0, 
	25, 25, 1, 0, 0, 0, 0, 28, 
	0, 0, 5, 0, 3, 0, 31, 31, 
	31, 31, 0, 0, 3, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 7, 0, 
	70, 70, 70, 70, 7, 0, 31, 31, 
	31, 31, 0, 0, 0, 5, 0, 0, 
	0, 0, 0, 0, 0, 37, 37, 37, 
	37, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	37, 37, 37, 37, 0, 0, 0, 0, 
	0, 0, 0, 34, 34, 34, 34, 0, 
	0, 0, 0, 7, 0, 70, 70, 70, 
	70, 7, 0, 31, 31, 31, 31, 0, 
	0, 0, 5, 0, 0, 0, 0, 0, 
	0, 0, 37, 37, 37, 37, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 37, 37, 37, 
	37, 0, 0, 0, 0, 0, 0, 0, 
	34, 34, 34, 34, 0, 0, 0, 0, 
	7, 0, 70, 70, 70, 70, 7, 0, 
	31, 31, 31, 31, 0, 0, 0, 5, 
	0, 0, 0, 0, 0, 0, 0, 37, 
	37, 37, 37, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 37, 37, 37, 37, 0, 0, 
	0, 0, 0, 0, 0, 34, 34, 34, 
	34, 0, 0, 0, 0, 7, 0, 70, 
	70, 7, 0, 31, 31, 0, 0, 0, 
	5, 0, 0, 0, 0, 0, 0, 0, 
	37, 37, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 37, 37, 0, 0, 0, 0, 0, 
	0, 0, 34, 34, 0, 0, 0, 0, 
	7, 0, 70, 70, 70, 70, 7, 0, 
	31, 31, 31, 31, 0, 0, 0, 5, 
	0, 0, 0, 0, 0, 0, 0, 37, 
	37, 37, 37, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 37, 37, 37, 37, 0, 0, 
	0, 0, 0, 0, 0, 34, 34, 34, 
	34, 0, 0, 0, 0, 7, 0, 70, 
	70, 70, 70, 7, 0, 31, 31, 31, 
	31, 0, 0, 0, 5, 0, 0, 0, 
	0, 0, 0, 0, 37, 37, 37, 37, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 37, 
	37, 37, 37, 0, 0, 0, 0, 0, 
	0, 0, 34, 34, 34, 34, 0, 0, 
	0, 0, 7, 0, 70, 70, 7, 0, 
	31, 31, 0, 0, 0, 5, 0, 0, 
	0, 0, 0, 0, 0, 37, 37, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 37, 37, 
	0, 0, 0, 0, 0, 0, 0, 34, 
	34, 0, 0, 0, 0, 7, 0, 70, 
	70, 7, 0, 31, 31, 0, 0, 0, 
	5, 0, 0, 0, 0, 0, 0, 0, 
	37, 37, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 37, 37, 0, 0, 0, 0, 0, 
	0, 0, 34, 34, 0, 0, 0, 0, 
	0, 0, 82, 82, 55, 11, 11, 11, 
	11, 86, 0, 0, 5, 0, 3, 0, 
	31, 31, 0, 0, 3, 0, 0, 0, 
	25, 25, 1, 0, 0, 0, 0, 28, 
	0, 0, 5, 0, 3, 0, 31, 31, 
	0, 0, 3, 0, 0, 0, 25, 25, 
	1, 0, 0, 0, 0, 28, 0, 0, 
	5, 0, 3, 0, 31, 31, 31, 31, 
	0, 0, 3, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 7, 0, 
	70, 70, 70, 70, 7, 0, 31, 31, 
	31, 31, 0, 0, 0, 5, 0, 0, 
	0, 0, 0, 0, 0, 37, 37, 37, 
	37, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	37, 37, 37, 37, 0, 0, 0, 0, 
	0, 0, 0, 34, 34, 34, 34, 0, 
	0, 0, 0, 7, 0, 70, 70, 7, 
	0, 31, 31, 0, 0, 0, 5, 0, 
	0, 0, 0, 0, 0, 0, 37, 37, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 37, 
	37, 0, 0, 0, 0, 0, 0, 0, 
	34, 34, 0, 0, 0, 0, 7, 0, 
	70, 70, 7, 0, 31, 31, 0, 0, 
	0, 5, 0, 0, 0, 0, 0, 0, 
	0, 37, 37, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 37, 37, 0, 0, 0, 0, 
	0, 0, 0, 34, 34, 0, 0, 0, 
	0, 0, 0, 82, 82, 55, 11, 11, 
	11, 11, 86, 0, 0, 5, 0, 3, 
	0, 31, 31, 0, 0, 3, 0, 0, 
	0, 25, 25, 1, 0, 0, 0, 0, 
	28, 0, 0, 5, 0, 3, 0, 31, 
	31, 31, 31, 0, 0, 3, 0, 0, 
	0, 0, 0, 25, 25, 1, 0, 0, 
	0, 0, 28, 0, 0, 0, 0, 5, 
	0, 3, 0, 31, 31, 31, 31, 0, 
	0, 3, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 7, 0, 70, 70, 70, 
	70, 7, 0, 31, 31, 31, 31, 0, 
	0, 0, 5, 0, 0, 0, 0, 0, 
	0, 0, 37, 37, 37, 37, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 37, 37, 37, 
	37, 0, 0, 0, 0, 0, 0, 0, 
	34, 34, 34, 34, 0, 0, 0, 0, 
	7, 0, 70, 70, 70, 70, 7, 0, 
	31, 31, 31, 31, 0, 0, 0, 5, 
	0, 0, 0, 0, 0, 0, 0, 37, 
	37, 37, 37, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 37, 37, 37, 37, 0, 0, 
	0, 0, 0, 0, 0, 34, 34, 34, 
	34, 0, 0, 0, 0, 7, 0, 70, 
	70, 7, 0, 31, 31, 0, 0, 0, 
	5, 0, 0, 0, 0, 0, 0, 0, 
	37, 37, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 37, 37, 0, 0, 0, 0, 0, 
	0, 0, 34, 34, 0, 0, 0, 0, 
	0, 0, 0, 40, 0, 74, 0, 43, 
	0, 78, 78, 78, 78, 49, 9, 0, 
	0, 0, 0, 0, 40, 74, 0, 43, 
	0, 52, 52, 52, 52, 9, 0, 0, 
	0, 40, 0, 74, 0, 43, 0, 78, 
	78, 49, 9, 0, 0, 0, 40, 74, 
	0, 43, 0, 52, 52, 9, 0, 23, 
	23, 23, 23, 23, 23, 23, 23, 23, 
	23, 23, 23, 0, 67, 67, 67, 67, 
	67, 67, 67, 67, 67, 67, 67, 67, 
	0, 58, 58, 58, 58, 58, 58, 58, 
	58, 58, 58, 58, 58, 0, 64, 64, 
	64, 64, 64, 64, 64, 64, 64, 64, 
	64, 64, 0, 61, 61, 61, 61, 61, 
	61, 61, 61, 61, 61, 61, 61, 0, 
	0
};

static const char _ObjParser_eof_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	21, 13, 17, 15
};

static const int ObjParser_start = 311;
static const int ObjParser_first_final = 311;
static const int ObjParser_error = 0;

static const int ObjParser_en_main = 311;


#line 80 "formats/obj/reader.rl"

typedef float real;
static const mixing::Type REALMT = mixing::FLOAT;
enum Attrs { VERTEX, TEX, NORMAL };

inline int objidx(int n, int size)
{
	if (n == 0) throw std::runtime_error("index cannot be 0");
	if (n > size) throw std::runtime_error("n too big");
	if (n < 0) {
		if (size + n < 0) {
			throw std::runtime_error("n too small");
		}
		return size + n;
	}

	return n - 1;
}

static const int lut_interp[] = { mixing::POS, mixing::TEX, mixing::NORMAL };

#define IL 9 /*std::numeric_limits<mesh::listidx_t>::max()*/
#define IR std::numeric_limits<mesh::regidx_t>::max()

struct OBJReader {
	mesh::Builder &builder;
	mesh::listidx_t attr_lists[3][9]; // VERTEX, TEX, NORMAL
	mesh::regidx_t vtx_reg[9];
	mesh::regidx_t face_reg[256];
	std::vector<std::pair<mesh::listidx_t, mesh::attridx_t>> tex_loc, normal_loc;
	std::vector<std::string> mtllibs;

	OBJReader(mesh::Builder &_builder) : builder(_builder),
		attr_lists{ { IL, IL, IL, IL, IL, IL, IL, IL, IL }, { IL, IL, IL, IL, IL, IL, IL, IL, IL }, { IL, IL, IL, IL, IL, IL, IL, IL, IL } },
		vtx_reg{ IR, IR, IR, IR, IR, IR, IR, IR, IR }
	{
		for (int i = 0; i < 256; ++i) {
			face_reg[i] = IR;
		}
	}

	// helper methods
	int init_attr(Attrs attr, int n)
	{
		mesh::listidx_t &list = attr_lists[attr][n];
		if (list == IL) {
			mixing::Fmt fmt;
			mixing::Interps interps;
			for (int i = 0; i < n; ++i) {
				fmt.add(REALMT);
				int interp = lut_interp[attr];
				if (attr == VERTEX && n > 4) {
					interp = n == 8 && i >= 4 || i >= 3 ? mixing::COLOR : interp;
				}
				interps.append(interp, i);
			}
			list = builder.add_list(fmt, interps, attr == VERTEX ? mesh::attr::VTX : mesh::attr::CORNER);
		}
		return list;
	}
	mesh::attridx_t write_attr(int list, real *coords, int n)
	{
		mesh::attridx_t row = builder.alloc_attr(list);
		for (int i = 0; i < n; ++i) {
			unsigned char *dst = builder.elem(list, row, i);
			std::copy((unsigned char*)(coords + i), (unsigned char*)(coords + i + 1), dst);
		}
		return row;
	}

	// OBJ methods
	void vertex(real *coords, int n)
	{
		mesh::listidx_t list = init_attr(VERTEX, n);
		mesh::attridx_t aidx = write_attr(list, coords, n);

		mesh::regidx_t r = vtx_reg[n];
		if (r == IR) {
			r = vtx_reg[n] = builder.add_vtx_region(1);
			builder.bind_reg_vtxlist(r, 0, list);
		}
		mesh::vtxidx_t vidx = builder.alloc_vtx();
		builder.vtx_reg(vidx, r);
		builder.bind_vtx_attr(vidx, 0, aidx);
	}
	void tex(real *coords, int n)
	{
		mesh::listidx_t list = init_attr(TEX, n);
		mesh::attridx_t aidx = write_attr(list, coords, n);
		tex_loc.push_back(std::make_pair(list, aidx));
	}
	void normal(real *coords, int n)
	{
		mesh::listidx_t list = init_attr(NORMAL, n);
		mesh::attridx_t aidx = write_attr(list, coords, n);
		normal_loc.push_back(std::make_pair(list, aidx));
	}
	void face(bool has_v, int *vi, bool has_t, int *ti, bool has_n, int *ni, int corners)
	{
		if (!has_v) throw std::runtime_error("Face has no vertex index; required for connectivity");
		mesh::listidx_t tex_l = IL, normal_l = IL;

		if (has_t) tex_l = tex_loc[ti[0]].first;
		if (has_n) normal_l = normal_loc[ni[0]].first;

		for (int c = 1; c < corners; ++c) {
			if (has_t && tex_loc[ti[c]].first != tex_l) throw std::runtime_error("Inconsistent texture attribute types in face");
			if (has_n && normal_loc[ni[c]].first != normal_l) throw std::runtime_error("Inconsistent normal attribute types in face");
		}

		int reglookup = (tex_l << 3) | normal_l;
		mesh::regidx_t r = face_reg[reglookup];
		mesh::listidx_t num_attrs = (mesh::listidx_t)has_t + (mesh::listidx_t)has_n;
		mesh::listidx_t tex_a = 0, normal_a = (mesh::listidx_t)has_t;
		if (r == IR) {
			r = face_reg[reglookup] = builder.add_face_region(0, num_attrs);
			if (has_t) builder.bind_reg_cornerlist(r, tex_a, tex_l);
			if (has_n) builder.bind_reg_cornerlist(r, normal_a, normal_l);
		}

		// add face
		mesh::faceidx_t fidx = builder.alloc_face(1, corners);
		builder.face_reg(fidx, r);
		builder.face_begin(corners);
		for (int i = 0; i < corners; ++i) {
			builder.set_org(vi[i]);
			if (has_t) builder.bind_corner_attr(fidx, i, tex_a, tex_loc[ti[i]].second);
			if (has_n) builder.bind_corner_attr(fidx, i, normal_a, normal_loc[ni[i]].second);
		}
		builder.face_end();
	}

	// reader
	void read_obj(std::istream &is, const std::string &dir)
	{
		progress::handle prog;
		prog.start(util::linenum_approx(is));
		builder.init_bindings(0, 1, 2);

		double fraction, denom, sign, val, exp, expmul;
		int idx, idx_sign;
		std::vector<int> fi[3];
		real coords[8];
		int ncoord;
		int vi[3] = { 0 };
		int line = 0;

		char buf[BUFSIZE];
		int cs;

		
#line 920 "/home/max/repos/harry/formats/obj/reader.cc"
	{
	cs = ObjParser_start;
	}

#line 231 "formats/obj/reader.rl"

		while (!is.eof()) {
			char *p = buf;
			is.read(p, BUFSIZE);
			char *pe = p + is.gcount();
			char *eof = is.eof() ? pe : nullptr;

			
#line 934 "/home/max/repos/harry/formats/obj/reader.cc"
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const char *_keys;

	if ( p == pe )
		goto _test_eof;
	if ( cs == 0 )
		goto _out;
_resume:
	_keys = _ObjParser_trans_keys + _ObjParser_key_offsets[cs];
	_trans = _ObjParser_index_offsets[cs];

	_klen = _ObjParser_single_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( (*p) < *_mid )
				_upper = _mid - 1;
			else if ( (*p) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (unsigned int)(_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _ObjParser_range_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( (*p) < _mid[0] )
				_upper = _mid - 2;
			else if ( (*p) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += (unsigned int)((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
	cs = _ObjParser_trans_targs[_trans];

	if ( _ObjParser_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _ObjParser_actions + _ObjParser_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 0:
#line 30 "formats/obj/reader.rl"
	{ sign = 1; val = 0; fraction = 0; denom = 1; exp = 0; expmul = 1; }
	break;
	case 1:
#line 31 "formats/obj/reader.rl"
	{ sign = (*p) == '-' ? -1 : 1; }
	break;
	case 2:
#line 32 "formats/obj/reader.rl"
	{ fraction *= 10; fraction += (*p) - '0'; denom *= 10; }
	break;
	case 3:
#line 33 "formats/obj/reader.rl"
	{ val *= 10; val += (*p) - '0'; }
	break;
	case 4:
#line 34 "formats/obj/reader.rl"
	{ exp *= 10; exp += (*p) - '0'; }
	break;
	case 5:
#line 35 "formats/obj/reader.rl"
	{ expmul = std::pow(10.0, exp); }
	break;
	case 6:
#line 36 "formats/obj/reader.rl"
	{ val += fraction / denom; val *= sign * expmul; }
	break;
	case 7:
#line 37 "formats/obj/reader.rl"
	{ val = NAN; }
	break;
	case 8:
#line 38 "formats/obj/reader.rl"
	{ val = INFINITY * sign; }
	break;
	case 9:
#line 50 "formats/obj/reader.rl"
	{ idx_sign = 0; }
	break;
	case 10:
#line 50 "formats/obj/reader.rl"
	{ idx_sign = 1; }
	break;
	case 11:
#line 50 "formats/obj/reader.rl"
	{ idx = 0; }
	break;
	case 12:
#line 50 "formats/obj/reader.rl"
	{ idx *= 10; idx += (*p) - '0'; }
	break;
	case 13:
#line 50 "formats/obj/reader.rl"
	{ idx = idx_sign ? -idx : idx; }
	break;
	case 14:
#line 52 "formats/obj/reader.rl"
	{ fi[VERTEX].push_back(objidx(idx, vi[VERTEX])); }
	break;
	case 15:
#line 53 "formats/obj/reader.rl"
	{ fi[TEX].push_back(objidx(idx, vi[TEX])); }
	break;
	case 16:
#line 54 "formats/obj/reader.rl"
	{ fi[NORMAL].push_back(objidx(idx, vi[NORMAL])); }
	break;
	case 17:
#line 56 "formats/obj/reader.rl"
	{ coords[ncoord++] = val; }
	break;
	case 18:
#line 57 "formats/obj/reader.rl"
	{ ncoord = 0; }
	break;
	case 19:
#line 63 "formats/obj/reader.rl"
	{ ++vi[VERTEX]; vertex(coords, ncoord); }
	break;
	case 20:
#line 64 "formats/obj/reader.rl"
	{ ++vi[TEX]; tex(coords, ncoord); }
	break;
	case 21:
#line 65 "formats/obj/reader.rl"
	{ ++vi[NORMAL]; normal(coords, ncoord); }
	break;
	case 22:
#line 66 "formats/obj/reader.rl"
	{ fi[0].clear(); fi[1].clear(); fi[2].clear(); }
	break;
	case 23:
#line 66 "formats/obj/reader.rl"
	{ face(!fi[VERTEX].empty(), fi[VERTEX].data(), !fi[TEX].empty(), fi[TEX].data(), !fi[NORMAL].empty(), fi[NORMAL].data(), fi[VERTEX].size()); }
	break;
	case 24:
#line 73 "formats/obj/reader.rl"
	{ prog(line++); }
	break;
#line 1107 "/home/max/repos/harry/formats/obj/reader.cc"
		}
	}

_again:
	if ( cs == 0 )
		goto _out;
	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	if ( p == eof )
	{
	const char *__acts = _ObjParser_actions + _ObjParser_eof_actions[cs];
	unsigned int __nacts = (unsigned int) *__acts++;
	while ( __nacts-- > 0 ) {
		switch ( *__acts++ ) {
	case 19:
#line 63 "formats/obj/reader.rl"
	{ ++vi[VERTEX]; vertex(coords, ncoord); }
	break;
	case 20:
#line 64 "formats/obj/reader.rl"
	{ ++vi[TEX]; tex(coords, ncoord); }
	break;
	case 21:
#line 65 "formats/obj/reader.rl"
	{ ++vi[NORMAL]; normal(coords, ncoord); }
	break;
	case 23:
#line 66 "formats/obj/reader.rl"
	{ face(!fi[VERTEX].empty(), fi[VERTEX].data(), !fi[TEX].empty(), fi[TEX].data(), !fi[NORMAL].empty(), fi[NORMAL].data(), fi[VERTEX].size()); }
	break;
#line 1139 "/home/max/repos/harry/formats/obj/reader.cc"
		}
	}
	}

	_out: {}
	}

#line 239 "formats/obj/reader.rl"

			if (cs == ObjParser_error) throw std::runtime_error("Unable to parse this OBJ file");
		}
		prog.end();
	}
};

void read(std::istream &is, const std::string &dir, mesh::Mesh &mesh)
{
	mesh::Builder builder(mesh);

	OBJReader reader(builder);
	reader.read_obj(is, dir);

	quant::set_bounds(mesh.attrs);

	std::cout << "Used face regions: " << mesh.attrs.num_regs_face() << std::endl;
	std::cout << "Used vertex regions: " << mesh.attrs.num_regs_vtx() << std::endl;
}

}
}

