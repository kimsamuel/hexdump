/* hexdump for a file (offset can be specified) */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define OFFSET 16
#define BYTE_SPACING (3 * (OFFSET - 1) + 2)

int main(int argc, char *argv[])
{
	FILE *fp;
	int pos = 0, n = 0, i;
	unsigned char buffer[OFFSET] = {0};

	if (argc != 2) {
		fprintf(stderr, "usage: hexdump source\n");
		exit(EXIT_FAILURE);
	}

	if ((fp = fopen(argv[1], "rb")) == NULL) {
		fprintf(stderr, "Can't open file\n");
		exit(EXIT_FAILURE);
	}

	printf("Offset  ");
	for (i = 0; i <= BYTE_SPACING - 5; i++) {
		if (i == ((BYTE_SPACING - 5)/ 2)) {
			printf("Bytes");
		} else {
			printf(" ");
		}
	}
	printf("  ");
	for (i = 0; i <= OFFSET - 10; i++) {
		if (i == ((OFFSET - 10) / 2)) {
			printf("Characters");
		} else {
			printf(" ");
		}
	}
	printf("\n");

	printf("------  ");
	for (i = 0; i < BYTE_SPACING; i++) {
		printf("-");
	}
	printf("  ");
	for (i = 0; i < OFFSET; i++) {
		printf("-");
	}

	pos = 0;
	for (;;) {
		printf("\n%06X ", pos += n);
		n = fread(buffer, 1, OFFSET, fp);
		if (n == 0)
			break;
		for (i = 0; i < n; i++) {
			printf(" %02X", buffer[i]);
		}
		for (i = n; i < OFFSET; i++) {
			printf("   ");
		}

		printf("  ");
		for (i = 0; i < n; i++) {
			if (!isprint(buffer[i])) {
				buffer[i] = '.';
			}
			printf("%c", buffer[i]);
		}
	}
	printf("\n");

	fclose(fp);
	return 0;
}
