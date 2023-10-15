#ifndef CM_METAMERICS_CONTROLLER_INCLUDED
#define CM_METAMERICS_CONTROLLER_INCLUDED



typedef struct CMMetamericsController CMMetamericsController;

CMMetamericsController* cmAllocMetamericsController(void);
void cmDeallocMetamericsController(CMMetamericsController* con);

void cmShowMetamericsController(CMMetamericsController* con);
void cmUpdateMetamericsController(CMMetamericsController* con);



#endif // CM_METAMERICS_CONTROLLER_INCLUDED
