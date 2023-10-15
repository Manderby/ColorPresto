#ifndef CP_METAMERICS_CONTROLLER_INCLUDED
#define CP_METAMERICS_CONTROLLER_INCLUDED



typedef struct CPMetamericsController CPMetamericsController;

CPMetamericsController* cpAllocMetamericsController(void);
void cpDeallocMetamericsController(CPMetamericsController* con);

void cpShowMetamericsController(CPMetamericsController* con);
void cpUpdateMetamericsController(CPMetamericsController* con);



#endif // CP_METAMERICS_CONTROLLER_INCLUDED
