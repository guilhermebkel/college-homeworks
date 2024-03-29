#include <math.h>
#include <algorithm>
#include <iostream>
#include "graph.h"

// Distância euclidiana de a para b.
double getEuclideanDistance (Vertice a, Vertice b) {
    double x = (a.x - b.x);
    double y = (a.y - b.y);

    return sqrt(x*x + y*y);
}

// Coeficiente da reta que passa na origem e p.
double getInclination (Vertice p) {
    return atan2(p.y, p.x);
}

// Coeficiente da reta orientada de p para q.
double getRelativeInclination (Vertice p, Vertice q) {
    return atan2(q.y - p.y, q.x - p.x);
}

// Determina se ao caminhar de a para b e depois de b para c estamos fazendo uma curva à esquerda, à direita, ou seguindo em frente.
int getCurveType (Vertice a, Vertice b, Vertice c) {
    double v = a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);

    if (v < 0) {
        return -1; // left
    }

    if (v > 0) {
        return +1; // right
    }
    
    return 0; // straight
}

float getCurveAngle (Vertice a, Vertice b, Vertice c) {
    float ABx = b.x - a.x;
    float ABy = b.y - a.y;
    float BCx = c.x - b.x;
    float BCy = c.y - b.y;

    float dotProduct = ABx * BCx + ABy * BCy;
    float magnitudeAB = sqrt(ABx * ABx + ABy * ABy);
    float magnitudeBC = sqrt(BCx * BCx + BCy * BCy);

    float angleRad = acos(dotProduct / (magnitudeAB * magnitudeBC));
    float angleDeg = angleRad * 180.0 / M_PI;

    return 180 - angleDeg;
}

void buildFace (std::vector<Vertice> vertices, std::vector<Vertice> *face, int currentVerticeId) {
    Vertice initialVertice = face->at(0);
    Vertice previousVertice = face->at(face->size() - 1);
    Vertice currentVertice = vertices[currentVerticeId];

    std::vector<int> currentNeighborVerticesIds = currentVertice.neighborVerticesIds;

    std::sort(currentNeighborVerticesIds.begin(), currentNeighborVerticesIds.end(), [&](int firstVerticeId, int secondVerticeId) {
        Vertice firstVertice = vertices[firstVerticeId];
        float firstVerticeEuclideanDistance = getEuclideanDistance(initialVertice, firstVertice);

        Vertice secondVertice = vertices[secondVerticeId];
        float secondVerticeEuclideanDistance = getEuclideanDistance(initialVertice, secondVertice);

        if (previousVertice.id == initialVertice.id) {
            return true;
        } else if (firstVerticeEuclideanDistance < secondVerticeEuclideanDistance) {
            return true;
        } else if (firstVerticeEuclideanDistance > secondVerticeEuclideanDistance) {
            return false;
        } else {
            float firstVerticeCurveAngle = getCurveAngle(previousVertice, currentVertice, firstVertice);
            float secondVerticeCurveAngle = getCurveAngle(previousVertice, currentVertice, secondVertice);

            return firstVerticeCurveAngle < secondVerticeCurveAngle;
        }
    });

    if (initialVertice.id == 0) {
        std::cout << initialVertice.label << " - " << previousVertice.label << " " << currentVertice.label << " " << vertices[currentNeighborVerticesIds[0]].label << std::endl;
    }

    int nextVerticeId = currentNeighborVerticesIds[0];

    if (nextVerticeId == initialVertice.id) {
        face->push_back(vertices[nextVerticeId]);
    } else {
        face->push_back(currentVertice);
        buildFace(vertices, face, nextVerticeId);
    }
}

int getExpectedFaceCount (Graph graph) {
    return graph.edgesCount - sizeof(graph.vertices) + 2;
}

