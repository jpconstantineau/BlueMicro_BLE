#include "command_queues.h"

// command_less is used for sorting
bool command_less (command_t i,command_t j) { return (i.first<j.first); }
