#ifndef __DEBUG_H__
#define __DEBUG_H__


extern int DEBUG;
extern int LAYER;


#define DEBUG_START( ... )({\
	if (DEBUG) {\
		int layer_index;\
		for (layer_index = 0; layer_index < LAYER; layer_index++) printf("|  ");\
		printf("\n");\
		for (layer_index = 0; layer_index < LAYER; layer_index++) printf("|  ");\
		printf("o ");\
		printf(__VA_ARGS__);\
		printf("\n");\
		++LAYER;\
	}\
})


#define DEBUG_SAY( ... )({\
	if (DEBUG) {\
		int layer_index;\
		for (layer_index = 0; layer_index < LAYER; layer_index++) printf("|  ");\
		printf("~ ");\
		printf(__VA_ARGS__);\
	}\
})


#define DEBUG_END( ... )({\
	if (DEBUG) {\
		int layer_index;\
		for (layer_index = 0; layer_index < LAYER - 1; layer_index++) printf("|  ");\
		printf("x ");\
		printf(__VA_ARGS__);\
		printf("\n");\
		for (layer_index = 0; layer_index < LAYER - 1; layer_index++) printf("|  ");\
		printf("\n");\
		--LAYER;\
	}\
})


// __DEBUG_H__
#endif
