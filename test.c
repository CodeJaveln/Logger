#include "logger.h"

int main(void) {
    logger_init("test.log");

    logger_info("This is a log test! I have cool variable here: %s", "wow, I can add extra text!");
    logger_warning("Omg a warning!");
    logger_error("this is not a drill");
    logger_info("Can I add another info at the bottom?");

    logger_close();

    return 0;
}
