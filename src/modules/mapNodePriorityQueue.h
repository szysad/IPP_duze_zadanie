/** @file
 * Interfejs struktury kolejki priorytetowej węzła struktury mapy krajowej.
 *
 * @author Szymon Sadkowski <ss406325@students.mimuw.edu.pl>
 * @date 06.05.19
 */

#ifndef DROGI_MAPNODEPRIORITYQUEUE_H
#define DROGI_MAPNODEPRIORITYQUEUE_H

#include "mapNode.h"

typedef struct {
    int size;
    int capacity;
    MapNode **arr;
} MapNodePriorityQueue;

/**
 * @param[in] size : rozmiar.
 * @return wskażnik na nowo utworzoną strukturę kolejki priorytetowej o podanym rozmiarze, lub NULL jeżeli
 * nie udało zaalokować się pamięci.
 */
MapNodePriorityQueue *MapNodePriorityQueue_new(int size);

/**
 * @brief zwalnia pamięć kolejki priorytetowej.
 * @param[in,out] queue : wskaźnik na strukturę kolejki priorytetowej.
 */
void MapNodePriorityQueue_remove(MapNodePriorityQueue *queue);

/**
 * @brief dodaje element do kolejki priorytetowej.
 * @param[in] queue : wskaźnik na strukturę kolejki priorytetowej.
 * @param mapNode[in] : wskaźnik na struktuę miasta.
 */
void MapNodePriorityQueue_add(MapNodePriorityQueue *queue, MapNode *mapNode);

/**
 * @brief zmienia wartość atrybutu oldestIncludedRoadAge.
 * @param[in,out] queue : wskaźnik na kolejkę proiorytetową.
 * @param[in,out] mapNode : wskaźnik na strukturę miasta do edycji.
 * @param[in] val : nowa wartość atrybutu.
 */
void MapNodePriorityQueue_updateNode(MapNodePriorityQueue *queue, MapNode *mapNode, int val);

/**
 * @brief usuwa z kolejki element o najwyższym priorytecie.
 * @param[in,out] queue : wskaźnik na strukturę niepustej kolejki priorytetowej.
 * @return wskaźnik na usunięte miasto z kolejki priorytetowej.
 */
MapNode *MapNodePriorityQueue_popMin(MapNodePriorityQueue *queue);

/**
 * @param[in] queue : wskaźnik na strukurę drogi krajowej.
 * @return true jeżeli kolejka jest pusta, false w przeciwnym przypadku.
 */
bool MapNodePriorityQueue_isEmpty(MapNodePriorityQueue *queue);

#endif //DROGI_MAPNODEPRIORITYQUEUE_H
