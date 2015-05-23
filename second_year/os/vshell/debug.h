#ifndef __LAYER_DEBUG_H__
#define __LAYER_DEBUG_H__


extern int DEBUG;
extern int LAYER;


#ifdef DEBUG_IS_ON

// ----------- DEBUG MAIN SETUP ----------- //
#define _DEBUG_START_STR_ "o "
#define _DEBUG_END_STR_ "x "
#define _DEBUG_LAYER_STR_ "|  "


// ----------- DEBUG MAIN MACROS ----------- //
#define _DEBUG_PRINT_LAYER_ (\
{\
	int _layer_index;\
	for (_layer_index = 0; _layer_index < LAYER; ++_layer_index)\
		printf(_DEBUG_LAYER_STR_);\
})

#define DEBUG_LAYER (\
{\
	if (DEBUG) _DEBUG_PRINT_LAYER_;\
})

#define SWITCH_DEBUG(argc, argv)(\
{\
	int i;\
	for (i = 1; i < argc; i++)\
		if (!strcmp(argv[i], "-d"))\
			DEBUG = 1;\
})

#define DEBUG_START( ... )(\
{\
	if (DEBUG)\
	{\
		_DEBUG_PRINT_LAYER_;\
		printf("\n");\
		_DEBUG_PRINT_LAYER_;\
		printf(_DEBUG_START_STR_);\
		printf(__VA_ARGS__);\
		printf("\n");\
		++LAYER;\
	}\
})

#define DEBUG_SAY( ... )(\
{\
	if (DEBUG)\
	{\
		_DEBUG_PRINT_LAYER_;\
		printf(__VA_ARGS__);\
	}\
})


#define DEBUG_SHOUT( ... )(\
{\
	if (DEBUG)\
		printf(__VA_ARGS__);\
})

#define DEBUG_END( ... )(\
{\
	if (DEBUG)\
	{\
		--LAYER;\
		_DEBUG_PRINT_LAYER_;\
		printf(_DEBUG_END_STR_);\
		printf(__VA_ARGS__);\
		printf("\n");\
		_DEBUG_PRINT_LAYER_;\
		printf("\n");\
	}\
})

// ----------- DEBUG EXTRA MACROS ----------- //
#define DEBUG_SHOW_CMD(cmd)(\
{\
	if (DEBUG)\
	{\
		_DEBUG_PRINT_LAYER_; printf("Cmd structure:\n");\
		_DEBUG_PRINT_LAYER_; printf(" - Origin      : %s\n", cmd->origin);\
		_DEBUG_PRINT_LAYER_; printf(" - Ins         : %s\n", cmd->ins);\
		_DEBUG_PRINT_LAYER_; printf(" - Outs        : %s\n", cmd->outs);\
		_DEBUG_PRINT_LAYER_; printf(" - Appends     : %s\n", cmd->appends);\
		_DEBUG_PRINT_LAYER_; printf(" - Pipe        : %p\n", cmd->pipe);\
		_DEBUG_PRINT_LAYER_; printf(" - In back     : %s\n", cmd->is_in_background ? "True" : "False");\
		_DEBUG_PRINT_LAYER_; printf(" - Valid       : %s\n", cmd->is_valid ? "True" : "False");\
		_DEBUG_PRINT_LAYER_; printf(" - ArgC        : %d\n", cmd->argc);\
		_DEBUG_PRINT_LAYER_; printf(" - ArgV (last) : %s\n", (cmd->argc > 0) ? cmd->argv[cmd->argc - 1] : cmd->argv[0]);\
	}\
})


// ----------- ELSE ifdef DEBUG_IS_ON ----------- //
#else

#define TOGGLE_DEBUG( ... )
#define DEBUG_START( ... )
#define DEBUG_SAY( ... )
#define DEBUG_SHOUT( ... )
#define DEBUG_LAYER( ... )
#define DEBUG_END( ... )
#define DEBUG_SHOW_CMD( ... )


// ----------- END ifdef DEBUG_IS_ON ----------- //
#endif


// ----------- END ifdef __LAYER_DEBUG_H__ ----------- //
#endif
