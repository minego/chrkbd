#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

#include <unistd.h>
#include <linux/input.h>

typedef struct input_event input_event;

const struct input_event	syn	= { .type = EV_SYN, .code = SYN_REPORT, .value = 0 };

/* Global options */
int delay = 20000;

static void usage(const char *program)
{
    fprintf(stderr,
			"%s - Swap keys to make the keyboard on the Pixel Slate more sane\n"
			"\n"
			"usage %s [-h | [-d delay]]\n"
			"\n"
			"options:\n"
			"   -h          Show this message and exit\n"
			"   -d          Delay used for key sequences (default: 20000 microseconds)\n"

			, program, program);
}

static int read_event(struct input_event *event)
{
    return fread(event, sizeof(struct input_event), 1, stdin) == 1;
}

static void write_event(const struct input_event *event)
{
    if (fwrite(event, sizeof(struct input_event), 1, stdout) != 1)
        exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
	char				o;
	input_event			event;

	while (-1 != (o = getopt(argc, argv, "hd:"))) {
        switch (o) {
            case 'h':
                usage(argv[0]);
				return EXIT_SUCCESS;

			case 'd':
				delay = atoi(optarg);
				break;
        }
    }


    setbuf(stdin,  NULL);
	setbuf(stdout, NULL);

    while (read_event(&event)) {
        if (event.type == EV_MSC && event.code == MSC_SCAN) {
            continue;
		}

        if (event.type != EV_KEY) {
            write_event(&event);
            continue;
        }

		switch (event.code) {
			case KEY_LEFTMETA:	event.code = KEY_CAPSLOCK;	break;
			case KEY_LEFTCTRL:	event.code = KEY_LEFTMETA;	break;

			default:
				break;
		}

		write_event(&event);
    }
}

