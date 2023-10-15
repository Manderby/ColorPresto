#ifndef CM_METAMERICS_CONTROLLER_INCLUDED
#define CM_METAMERICS_CONTROLLER_INCLUDED



typedef struct CPMetamericsController CPMetamericsController;

CPMetamericsController* cmAllocMetamericsController(void);
void cmDeallocMetamericsController(CPMetamericsController* con);

void cmShowMetamericsController(CPMetamericsController* con);
void cmUpdateMetamericsController(CPMetamericsController* con);



#endif // CM_METAMERICS_CONTROLLER_INCLUDED
