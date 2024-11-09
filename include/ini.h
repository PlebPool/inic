#ifndef TOMLC_H
#define TOMLC_H

#include <stddef.h>

int find_value(const char *file_path, const char *section, const char *key,
               char *buf, size_t buflen);

#endif
