
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string>
#include <iostream>

#include "../../lsMisc/CommandLineParser.h"
#include "../../lsMisc/UTF16toUTF8.h"
#include "../../lsMisc/stdwin32/stdwin32.h"

#define HAVE_IMAGE_HASH
#define HAVE_VIDEO_HASH
#include <pHash.h>

using namespace Ambiesoft;
using namespace std;
using namespace stdwin32;

int main(int argc, char **argv)
{
	CCommandLineParserW parser;

	bool dct = false;
	parser.AddOption(L"/dct", 0, &dct, ArgEncodingFlags_Default, L"dct method");

	bool decimal = false;
	parser.AddOption(L"/decimal", 0, &decimal, ArgEncodingFlags_Default, L"decimal output");

	bool image = true;
	parser.AddOption(L"/image", 0, &image, ArgEncodingFlags_Default, L"image hash");

	bool video = false;
	parser.AddOption(L"/video", 0, &video, ArgEncodingFlags_Default, L"video hash");

	bool help = false;
	parser.AddOption(L"/h", 0, &help, ArgEncodingFlags_Default, L"show help");
	
	wstring file;
	parser.AddOption(L"", 1, &file, ArgEncodingFlags_Default, L"specify file to calculate hash");

	parser.Parse();

	if (help)
	{
		wcout << parser.getHelpMessage() << endl;
		return 0;
	}
	
	if (file.empty())
	{
		wcerr << L"specify file" << endl;
		return 1;
	}
	
	if (dct)
	{
		if (video)
		{
			int length = 0;
			if (0 == ph_dct_videohash(toStdString(file).c_str(), length))
			{
				printf("%u", length);
				return 0;
			}
			return 1;
		}
	}
}
int main_old(int argc, char **argv) {
	if (argc >= 3 && stricmp(argv[1], "/dct-decimal") == 0) {
		ulong64 hash;
		if (0 == ph_dct_imagehash(argv[2], hash)) {
			printf("%I64u", hash);
			return 0;
		}
		return 1;
	}
	if (argc >= 3 && stricmp(argv[1], "/dct") == 0) {
		ulong64 hash;
		if (0 == ph_dct_imagehash(argv[2], hash)) {
			printf("%16I64x", hash);
			return 0;
		}
		return 1;
	}
	else if (argc >= 3 && stricmp(argv[1], "/mh-decimal") == 0) {
		int cx = 0;
		uint8_t *hash = ph_mh_imagehash(argv[2], cx,
			(argc >= 4) ? (float)strtod(argv[3], NULL) : 2.0f,
			(argc >= 5) ? (float)strtod(argv[4], NULL) : 1.0f
		);
		if (hash != NULL) {
			for (int x = 0; x < cx; x++) {
				if (x != 0) {
					putchar(' ');
				}
				printf("%u", hash[x]);
			}
			return 0;
		}
		return 1;
	}
	else if (argc >= 3 && stricmp(argv[1], "/mh") == 0) {
		int cx = 0;
		uint8_t *hash = ph_mh_imagehash(argv[2], cx,
			(argc >= 4) ? (float)strtod(argv[3], NULL) : 2.0f,
			(argc >= 5) ? (float)strtod(argv[4], NULL) : 1.0f
		);
		if (hash != NULL) {
			for (int x = 0; x < cx; x++) {
				printf("%02x", hash[x]);
			}
			return 0;
		}
		return 1;
	}
	fprintf(stderr,
		"RunpHash /dct         <image.png or image.jpg>\n"
		"RunpHash /dct-decimal <image.png or image.jpg>\n"
		"RunpHash /mh          <image.png or image.jpg> (<alpha> (<level>))\n"
		"RunpHash /mh-decimal  <image.png or image.jpg> (<alpha> (<level>))\n"
	);
	return 1;
}
