//  Copyright (c) 2008 David Caldwell,  All Rights Reserved.
#ifndef __GDISK_H__
#define __GDISK_H__

struct command_arg {
    char *name;
    int type;
};
struct command {
    char *name;
    int (*handler)(char **arg);
    char *help;
    struct command_arg *arg;
};

#define C_Optional  0x80
#define C_Flag      0x01
#define C_Number    0x02
#define C_String    0x03
//#define C_Partition 0x04

#include "autolist.h"
#define add_command(name, handler, help, ...) \
    static struct command_arg Unique(__command_arg__)[] = { NULL, 0, ##__VA_ARGS__, NULL, 0 }; \
    static struct command Unique(__command__) = { name, handler, help, &Unique(__command_arg__)[1] }; \
    autolist_add(command, &Unique(__command__))

autolist_declare(struct command *, command);

#endif /* __GDISK_H__ */
