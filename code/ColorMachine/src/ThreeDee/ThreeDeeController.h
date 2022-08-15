
#ifdef __cplusplus
  extern "C"{
#endif



typedef struct CMThreeDeeController CMThreeDeeController;

CMThreeDeeController* cmAllocThreeDeeController(void);
void cmFreeThreeDeeController(CMThreeDeeController* con);

void cmShowThreeDeeController(CMThreeDeeController* con);
void cmUpdateThreeDeeController(CMThreeDeeController* con);



#ifdef __cplusplus
  }
#endif
