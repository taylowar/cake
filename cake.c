
#define CAKE_EXT_CMD
#define CAKE_EXT_FS
#define CAKE_EXT_STRING
#define CAKE_IMPLEMENTATION
#include "cake.h"

void cake_rebuild_urself(const char *program) {
    Cake_CMD cmd = {0};
    cake_cmd_push(&cmd, "clang");
    cake_cmd_push(&cmd, "-Wall", "-Wextra");
    cake_cmd_push(&cmd, "-o", program);
    size_t input_name_size = strlen(program) + 3;
    void *input_name = cake_temp_alloc(input_name_size);
    snprintf(input_name, input_name_size, "%s.c", program);
    cake_cmd_push(&cmd, input_name);
    cake_cmd_print(cmd);
    pid_t cpid = cake_cmd_exec(cmd);
    if (cake_cmd_wait(cpid)) {
      printf("SUCCESS: program rebuild complete\n");
    }
}

int main(int argc, char **argv) 
{
    (void) argc;
    const char *program = argv[0];
    cake_rebuild_urself(program);
    return 0;
}
