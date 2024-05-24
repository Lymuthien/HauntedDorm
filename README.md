# HauntedDorm

Игра в стиле STS

## XOR-шифрование (используется в hauntedDormGame.cpp в методе QString HauntedDormGame::xorEncryption(QString str). Применяется там же в методах void HauntedDormGame::saveCache(), void HauntedDormGame::readCache())

## Бинарный поиск (используется в room.cpp в методе int Room::binrySearch(const QVector<FloorCage*> arr, const int y). Применяется там же в методе Room::initBotCycle())

## Пирамидальная сортировка (используется в ghost.cpp в методе void Ghost::heapSort(QVector<Room*> roms, int n). Применяется там же в методе void Ghost::findRandomRoom(QVector<Room*>* room, int roomNum))

## Алгоритм Беллмана-Форда (используется в ghost.cpp в методе QVector<int> Ghost::bellmanFord(QVector<Edge>&edges, int numVertices, int source). Применяется там же в методе Ghost::goToHillZone())

## Линейный конгруэнтный метод генерации псевдослучайных чисел (используется в map.cpp в методе long* Map::randNumbers(int n). Применяется там же в методе void Map::initHumanBots())

<<<<<<< develop

=======
>>>>>>> main
