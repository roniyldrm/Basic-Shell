#include "shell.hpp"

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;

    Shell shell;
    return shell.run();
}
