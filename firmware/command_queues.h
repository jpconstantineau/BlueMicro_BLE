#include <stdint.h>
#include <vector>
#include <utility>
#include <algorithm>


typedef uint16_t extended_keycodes_t;
typedef void (*run_command_cb_t)(extended_keycodes_t key);
typedef std::pair <extended_keycodes_t , run_command_cb_t> command_t;
typedef std::vector < command_t > commandlist_t;
typedef std::vector <extended_keycodes_t> commandqueue_t;

typedef std::vector <extended_keycodes_t> keymap_t;

bool command_less (command_t i,command_t j);

#define COMMANDID(COMMAND) (((extended_keycodes_t) COMMAND << 8 ) | 0xAF ) 
#define SETUPCOMMAND(LIST, KEY, COMMAND) {LIST.push_back(std::make_pair(KEY,[](extended_keycodes_t i){ COMMAND;} ));}

#define RUNCOMMANDS(QUEUE, LIST)   {std::for_each(QUEUE.cbegin(), QUEUE.cend(),[LIST](extended_keycodes_t key){ commandlist_t::iterator it = std::find_if(LIST.begin(), LIST.end(),[key](command_t c){return (c.first == key);}); if (it != std::end(LIST)){command_t command = *it; command.second(command.first);} });}

#define SORTCOMMANDS(LIST) {std::sort(LIST.begin(), LIST.end(), command_less);}

#define ADDCOMMAND(QUEUE, COMMAND)  {QUEUE.push_back(COMMAND);}
