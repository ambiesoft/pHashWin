
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#define HAVE_IMAGE_HASH
#include <pHash.h>

int main(int argc, char **argv) {
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
			for (int x=0; x<cx; x++) {
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
			for (int x=0; x<cx; x++) {
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
