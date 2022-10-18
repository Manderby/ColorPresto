#ifndef CM_METAMERICS_CONTROLLER_INCLUDED
#define CM_METAMERICS_CONTROLLER_INCLUDED

#ifdef __cplusplus
  extern "C"{
#endif



typedef enum{
  REFERENCE_ILLUMINATION_D50,
  REFERENCE_ILLUMINATION_D55,
  REFERENCE_ILLUMINATION_D65,
  REFERENCE_ILLUMINATION_D75,
  NUMBER_OF_REFERENCE_ILLUMINATIONS
} CMReferenceIlluminationType;



typedef struct CMMetamericsController CMMetamericsController;

CMMetamericsController* cmAllocMetamericsController(void);
void cmDeallocMetamericsController(CMMetamericsController* con);

void cmShowMetamericsController(CMMetamericsController* con);
void cmUpdateMetamericsController(CMMetamericsController* con);



#ifdef __cplusplus
  }
#endif

#endif // CM_METAMERICS_CONTROLLER_INCLUDED
