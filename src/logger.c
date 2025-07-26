#include "logger.h"

#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#define BUFFER_MAXLEN 4096

static FILE *file_stream = NULL;

int logger_init(const char *log_filename) {
    file_stream = fopen(log_filename, "a");
    if (!file_stream) {
        return -1;
    }

    // We don't care if it fails, it shouldn't.
    (void)logger_info("logger session started");

    return 0;
}

int logger_info(const char *format, ...) {
    if (!file_stream) {
        fprintf(stderr, "called logger_info without running logger_init first\n");
        return -1;
    }
    time_t rawtime;
    struct tm *timeinfo;
    va_list args;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    char buf[BUFFER_MAXLEN];

    strftime(buf, BUFFER_MAXLEN, "%H:%M:%S", timeinfo);

    fprintf(file_stream, "%s: ", buf);

    va_start(args, format);

    vfprintf(file_stream, format, args);

    va_end(args);

    fprintf(file_stream, "\n");

    return 0;
}

int logger_warning(const char *format, ...) {
    if (!file_stream) {
        fprintf(stderr, "called logger_warning without running logger_init first\n");
        return -1;
    }
    time_t rawtime;
    struct tm *timeinfo;
    va_list args;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    char buf[BUFFER_MAXLEN];

    strftime(buf, BUFFER_MAXLEN, "%H:%M:%S", timeinfo);

    // Only change from info!
    fprintf(file_stream, "%s: [WARNING] ", buf);

    va_start(args, format);

    vfprintf(file_stream, format, args);

    va_end(args);

    fprintf(file_stream, "\n");

    return 0;
}

int logger_error(const char *format, ...) {
    if (!file_stream) {
        fprintf(stderr, "called logger_error without running logger_init first\n");
        return -1;
    }
    time_t rawtime;
    struct tm *timeinfo;
    va_list args;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    char buf[BUFFER_MAXLEN];

    strftime(buf, BUFFER_MAXLEN, "%H:%M:%S", timeinfo);

    fprintf(file_stream, "%s: [ERROR] ", buf);

    va_start(args, format);

    vfprintf(file_stream, format, args);

    va_end(args);

    fprintf(file_stream, "\n");

    return 0;
}

void logger_close(void) {
    logger_info("logger session ended\n");

    fclose(file_stream);
}
