
#ifdef __cplusplus
  extern "C"{
#endif



typedef struct CMMetamericsController CMMetamericsController;

CMMetamericsController* cmAllocMetamericsController(void);
void cmDeallocMetamericsController(CMMetamericsController* con);

void cmShowMetamericsController(CMMetamericsController* con);
void cmUpdateMetamericsController(CMMetamericsController* con);



#ifdef __cplusplus
  }
#endif
