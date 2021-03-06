#include "Launcher/GameType.h"

const char * GameTypes::gameTypeStrings[] = { "Game", "Setup Sound", "Setup Video", "Client", "Server" };
const GameTypes::GameType GameTypes::defaultGameType = GameTypes::Game;

bool GameTypes::isValid(GameType type) {
	return type > Invalid && type < NumberOfGameTypes;
}

bool GameTypes::isValid(int type) {
	return type > static_cast<int>(Invalid) && type < static_cast<int>(NumberOfGameTypes);
}

const char * GameTypes::toString(GameType type) {
	return toString(static_cast<int>(type));
}

const char * GameTypes::toString(int type) {
	if(!isValid(type)) { return "Invalid"; }

	return gameTypeStrings[type];
}

GameTypes::GameType GameTypes::parseFrom(const char * data) {
	if(data == NULL) { return Invalid; }

	GameType type = Invalid;

	char * typeString = Utilities::trimCopyString(data);

	for(int i=0;i<static_cast<int>(NumberOfGameTypes);i++) {
		if(Utilities::compareStringsIgnoreCase(typeString, gameTypeStrings[i]) == 0) {
			type = static_cast<GameType>(i);
			break;
		}
	}

	delete [] typeString;

	return type;
}

GameTypes::GameType GameTypes::parseFrom(const QString & data) {
	QByteArray dataBytes = data.toLocal8Bit();
	return parseFrom(dataBytes.data());
}
