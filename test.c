#include "logger.h"

int main(void) {
    logger_init("test.log");

    logger_info("This is a log test! I have cool variable here: %d", 420);
    logger_warning("Omg a warning!");
    logger_error("this is not a drill");

    logger_close();

    return 0;
}
