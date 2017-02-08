typedef struct {
    char *title;
    int width;
    int height;
} Options;

Options parse_args(int argc, char **argv);
