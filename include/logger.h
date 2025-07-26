#ifndef LOGGER_H_
#define LOGGER_H_

#define LOG_OK 0

// Returns 0 on success
int logger_init(const char *log_filename);

int logger_info(const char *format, ...);

int logger_warning(const char *format, ...);

int logger_error(const char *format, ...);

void logger_close(void);

#endif
