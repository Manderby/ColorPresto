
#define CM_PROTOTYPE(type) typedef struct type type

CM_PROTOTYPE(CMLColorMachine);


#ifdef __cplusplus
  extern "C"{
#endif



CMLColorMachine* cmGetCurrentColorMachine(void);
double cmGetUIScaleFactorForWindow(void* nativeWindowPtr);



#ifdef __cplusplus
  }
#endif
