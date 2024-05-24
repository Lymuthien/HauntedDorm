# Игра в стиле STS

Реализация игры HauntedDorm

## XOR-шифрование 
Используется в [hauntedDormGame.cpp](https://github.com/Lymuthien/HauntedDorm/blob/main/hauntedDormGame.cpp) в методе QString HauntedDormGame::xorEncryption(QString str). Применяется там же в методах void HauntedDormGame::saveCache(), void HauntedDormGame::readCache())

![XOR](https://github.com/Lymuthien/HauntedDorm/raw/main/resourses/images/readmeImg/xor.png)

## Бинарный поиск 
Используется в [room.cpp](https://github.com/Lymuthien/HauntedDorm/blob/main/room.cpp) в методе int Room::binrySearch(const QVector<FloorCage*> arr, const int y). Применяется там же в методе Room::initBotCycle())

![XOR](https://github.com/Lymuthien/HauntedDorm/raw/main/resourses/images/readmeImg/bins.png)

## Пирамидальная сортировка 
Используется в [ghost.cpp](https://github.com/Lymuthien/HauntedDorm/blob/main/ghost.cpp) в методе void Ghost::heapSort(QVector<Room*> roms, int n). Применяется там же в методе void Ghost::findRandomRoom(QVector<Room*>* room, int roomNum))

![XOR](https://github.com/Lymuthien/HauntedDorm/raw/main/resourses/images/readmeImg/heaps.png)

## Алгоритм Беллмана-Форда 
Используется в [ghost.cpp](https://github.com/Lymuthien/HauntedDorm/blob/main/ghost.cpp) в методе QVector<int> Ghost::bellmanFord(QVector<Edge>&edges, int numVertices, int source). Применяется там же в методе Ghost::goToHillZone())

![XOR](https://github.com/Lymuthien/HauntedDorm/raw/main/resourses/images/readmeImg/bellf.png)

## Линейный конгруэнтный метод генерации псевдослучайных чисел 
Используется в [map.cpp](https://github.com/Lymuthien/HauntedDorm/blob/main/map.cpp) в методе long* Map::randNumbers(int n). Применяется там же в методе void Map::initHumanBots())

![XOR](https://github.com/Lymuthien/HauntedDorm/raw/main/resourses/images/readmeImg/rand.png)
