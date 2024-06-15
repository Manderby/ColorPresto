#ifndef CP_PREFERENCES_CONTROLLER_INCLUDED
#define CP_PREFERENCES_CONTROLLER_INCLUDED



typedef struct CPPreferencesController CPPreferencesController;

CPPreferencesController* cpAllocPreferencesController(void);
void cpDeallocPreferencesController(CPPreferencesController* con);

void cpShowPreferencesController(CPPreferencesController* con);
void cpUpdatePreferencesController(CPPreferencesController* con);



#endif // CP_PREFERENCES_CONTROLLER_INCLUDED
