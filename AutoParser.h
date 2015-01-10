#ifndef AUTOPARSER_H
#define AUTOPARSER_H

// any line in the parser file that begins with a space or a # is skipped

const char sComment = '#';
const char szDelimiters[] = " ,[]()";

typedef enum AUTO_COMMAND_TOKENS
{
	AUTO_TOKEN_MODE,			// mode block number, number(integer)
	AUTO_TOKEN_BEGIN,			// mark beginning of mode block
	AUTO_TOKEN_END,			    // mark end of mode block
	AUTO_TOKEN_DELAY,			// delay (seconds - float)
	AUTO_TOKEN_LAST
} AUTO_COMMAND_TOKENS;

#endif  // AUTOPARSER_H
