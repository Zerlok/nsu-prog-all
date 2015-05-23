#ifndef __LAYER_DEBUG_H__
#define __LAYER_DEBUG_H__


extern int DEBUG;
extern int LAYER;


#ifdef _DEBUG_IS_ON_

#define DEBUG_START_STR "o "
//#define DEBUG_SAY_STR "~ "
#define DEBUG_END_STR "x "
#define DEBUG_LINE_STR "|  "

#define TOGGLE_DEBUG(argc, argv)(\
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
		int _layer_index;\
		for (_layer_index = 0; _layer_index < LAYER; ++_layer_index)\
			printf(DEBUG_LINE_STR);\
		printf("\n");\
		for (_layer_index = 0; _layer_index < LAYER; ++_layer_index)\
			printf(DEBUG_LINE_STR);\
		printf(DEBUG_START_STR);\
		printf(__VA_ARGS__);\
		printf("\n");\
		++LAYER;\
	}\
})

//		printf(DEBUG_SAY_STR);
#define DEBUG_SAY( ... )(\
{\
	if (DEBUG)\
	{\
		int _layer_index;\
		for (_layer_index = 0; _layer_index < LAYER; ++_layer_index)\
			printf(DEBUG_LINE_STR);\
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
		int _layer_index;\
		for (_layer_index = 0; _layer_index < LAYER - 1; ++_layer_index)\
			printf(DEBUG_LINE_STR);\
		printf(DEBUG_END_STR);\
		printf(__VA_ARGS__);\
		printf("\n");\
		for (_layer_index = 0; _layer_index < LAYER - 1; ++_layer_index)\
			printf(DEBUG_LINE_STR);\
		printf("\n");\
		--LAYER;\
	}\
})


// _DEBUG_IS_ON_ was not defined.
#else

#define TOGGLE_DEBUG( ... )
#define DEBUG_START( ... )
#define DEBUG_SAY( ... )
#define DEBUG_SHOUT( ... )
#define DEBUG_END( ... )

// if DEBUG_ON
#endif

// #define DEBUG_SHOW( array )({ if (DEBUG) { int i; for (i = 0; i < LAYER; i++) printf(DEBUG_LINE_STR); printf("%p %p", array, show_commands_array); show_commands_array(array, stdin); } })
// #define DEBUG_DO( cmd ) { if (DEBUG) cmd; }


// if __LAYER_DEBUG_H__
#endif
