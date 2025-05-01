
#define CAKE_EXT_CMD
#define CAKE_IMPLEMENTATION
#include "cake.h"

void cake_rebuild_urself(const char *program) {
    Cake_CMD cmd = {0};
    cake_cmd_push(&cmd, "clang");
    cake_cmd_push(&cmd, "-Wall", "-Wextra");
    cake_cmd_push(&cmd, "-o", program);
    size_t input_name_size = strlen(program) + 3;
    void *input_name = cake_talloc_poll(input_name_size);
    snprintf(input_name, input_name_size, "%s.c", program);
    cake_cmd_push(&cmd, input_name);
    temp_alloc_size -= input_name_size;
    cake_cmd_print(cmd);
    pid_t cpid = cake_cmd_exec(cmd);
    if (cake_cmd_wait(cpid)) {
        printf("SUCCESS: program rebuild complete\n");
    }
    free(cmd.es);
}

int main(int argc, char **argv) 
{
    (void) argc;
    const char *program = argv[0];
    cake_rebuild_urself(program);
    return 0;
}
