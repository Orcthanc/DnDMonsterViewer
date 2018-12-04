#ifndef __PARSER_H__
#define __PARSER_H__

#include "Monster.h"

typedef enum JSONObjectType {
	eJSONObjectTypeNone,
	eJSONObjectTypeDictionaryEntry,
	eJSONObjectTypeDictionary,
	
} JSONObjectType;

typedef struct JSONObject {
	JSONObjectType sType;
} JSONObject;

typedef struct JSONObjectDictionaryEntry {

} JSONObjectDictionaryEntry;

typedef struct JSONObjectDictionary {
	JSONObjectType sType;
	JSONObjectDictionaryEntry** entries;
	uint16_t entry_amount;
} JSONObjectDictionary;

void createDnDMonsterJSON( DnDMonster* monster, const char* path );

#endif
