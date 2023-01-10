#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


typedef struct Point {
    int fromStart;
    int elevation;
} POINT;

typedef struct PointsArray {
    int capacity;
    int used;
    POINT * points;
} POINTS_ARRAY;


typedef struct Route {
    int start;
    int finish;
    int elevationA;
    int elevationB;
    int lenght;
    int difference;
} ROUTE;

typedef struct RouteArray {
    int capacity;
    int used;
    ROUTE * routes;
} ROUTE_ARRAY;


POINTS_ARRAY * initPointsArray (int capacity) {
    POINTS_ARRAY * a = (POINTS_ARRAY *) malloc (sizeof(POINTS_ARRAY));
    a->capacity = capacity;
    a->used = 0;
    a->points = (POINT *) malloc (capacity * sizeof(POINT));
    return a;
}

ROUTE_ARRAY * initRouteArray (int capacity) {
    ROUTE_ARRAY * a = (ROUTE_ARRAY *) malloc (sizeof(ROUTE_ARRAY));
    a->capacity = capacity;
    a->used = 0;
    a->routes = (ROUTE *) malloc (capacity * sizeof(ROUTE));
    return a;
}

void addPoint (POINTS_ARRAY * a, int fromStart, int elevation) {
    if (a->used < a->capacity) {
        a->points[a->used].fromStart = fromStart;
        a->points[a->used].elevation = elevation;
        a->used ++;
    } else {
        a->points = (POINT *) realloc (a->points, a->capacity * sizeof(POINT) * 2);
        a->capacity *= 2;
        a->points[a->used].fromStart = fromStart;
        a->points[a->used].elevation = elevation;
        a->used ++;
    }
}

void addRoute (ROUTE_ARRAY * a, int start, int finish, int eA, int eB, int lenght, int difference) {
    
    // chybi automaticka realokace

    a->routes[a->used].start = start;
    a->routes[a->used].finish = finish;
    a->routes[a->used].elevationA = eA;
    a->routes[a->used].elevationB = eB;
    a->routes[a->used].lenght = lenght;
    a->routes[a->used].difference = difference;

    a->used ++;
}

void freePointsArray (POINTS_ARRAY * a) {
    free(a->points);
    free(a);
}

void freeRouteArray (ROUTE_ARRAY * a) {
    free(a->routes);
    free(a);
}

void getInput (POINTS_ARRAY * a) {
    
    // first line
    int tmp;
    scanf("%d", &tmp);
    addPoint(a, 0, tmp);

    while (1) {
        int x, y;
        if (scanf("%d %d", &x, &y) != 2) {
            if (feof(stdin)) {
                return;
            }
            printf("error\n");
            return;
        }
        addPoint(a, x, y);
    }
}

void printArray (POINTS_ARRAY * a) {
    for (int i = 0; i < a->used; i++) {
        printf("%d %d\n", a->points[i].fromStart, a->points[i].elevation);
    }
}


void findBestRouteA (POINTS_ARRAY * points, ROUTE_ARRAY * routes) {

    for (int i = 0; i < points->used; i++) {

        int lenght = 0;
        int difference = 0;

        for (int j = i + 1; j < points->used; j++) {
            lenght += points->points[j].fromStart - points->points[j-1].fromStart;
            difference += points->points[j - 1].elevation - points->points[j].elevation;

            if (difference < 0) {
                continue;
            }

            // pole je prazdne
            if ( routes->used == 0 ) {
                addRoute(routes, points->points[i].fromStart, points->points[j].fromStart,
                points->points[i].elevation, points->points[j].elevation, lenght, difference);
                continue;
            }


            // pridat do pole dalsi trasu
            if (difference == routes->routes[routes->used - 1].difference &&
            lenght == routes->routes[routes->used - 1].lenght) {

                addRoute(routes, points->points[i].fromStart, points->points[j].fromStart,
                points->points[i].elevation, points->points[j].elevation, lenght, difference);

                continue;

            }

            // Nasli jsme nove maximum
            if (difference > routes->routes[routes->used - 1].difference) {

                routes->used = 0;

                addRoute(routes, points->points[i].fromStart, points->points[j].fromStart,
                points->points[i].elevation, points->points[j].elevation, lenght, difference);

                continue;

            }

            if (difference == routes->routes[routes->used - 1].difference && lenght > routes->routes[routes->used - 1].lenght) {

                routes->used = 0;

                addRoute(routes, points->points[i].fromStart, points->points[j].fromStart,
                points->points[i].elevation, points->points[j].elevation, lenght, difference);

                continue;

            }
            
        }

    }

}


void printSolution (ROUTE_ARRAY * a) {

    if (a->used == 0) {
        printf("Nenalezeno\n");
        return;
    }

    printf("%d km, klesani: %d m, varianty: %d\n", a->routes[0].lenght, a->routes[0].difference, a->used);

    for (int i = 0; i < a->used; i++) {
        printf("%d (%d) -> %d (%d)\n", a->routes[i].start, a->routes[i].elevationA, a->routes[i].finish, a->routes[i].elevationB);
    }


}


int main (void) {

    POINTS_ARRAY * points = initPointsArray(2);
    ROUTE_ARRAY * routes = initRouteArray(5);

    getInput(points);

    printArray(points);


    findBestRouteA(points, routes);

    printSolution(routes);

    freePointsArray(points);
    freeRouteArray(routes);

    return 0;

}

