#include "logger.h"

#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#define BUFFER_MAXLEN 4096

static FILE *file_stream = NULL;

int logger_init(const char *log_filename) {
    if (file_stream) {
        fclose(file_stream);
    }

    file_stream = fopen(log_filename, "a");
    if (!file_stream) {
        return -1;
    }

    // We don't care if it fails, it shouldn't.
    (void)logger_info("logger session started");

    return 0;
}

void logger_close(void) {
    if (!file_stream) {
        fprintf(stderr, "called logger_close with invalid file stream\n");
        return;
    }

    logger_info("logger session ended\n");

    fclose(file_stream);
}

// Add a space first in the level string if not empty, otherwise it would be: "TIME:[WARNING] "
static void logger_log(const char *level, const char *format, va_list args) {
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    char buf[BUFFER_MAXLEN];
    strftime(buf, BUFFER_MAXLEN, "%H:%M:%S", timeinfo);

    fprintf(file_stream, "%s:%s ", buf, level);

    vfprintf(file_stream, format, args);

    fprintf(file_stream, "\n");

    fflush(file_stream);
}

int logger_info(const char *format, ...) {
    if (!file_stream) {
        fprintf(stderr, "called logger_info without running logger_init first\n");
        return -1;
    }

    va_list args;

    va_start(args, format);

    logger_log("", format, args);

    va_end(args);

    return 0;
}

int logger_warning(const char *format, ...) {
    if (!file_stream) {
        fprintf(stderr, "called logger_warning without running logger_init first\n");
        return -1;
    }

    va_list args;

    va_start(args, format);

    logger_log(" [WARNING]", format, args);

    va_end(args);

    return 0;
}

int logger_error(const char *format, ...) {
    if (!file_stream) {
        fprintf(stderr, "called logger_error without running logger_init first\n");
        return -1;
    }

    va_list args;

    va_start(args, format);

    logger_log(" [ERROR]", format, args);

    va_end(args);

    return 0;
}
